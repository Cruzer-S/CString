#include "cstring.h"

#undef cstring_create
#undef cstring_compare
#undef cstring_append
#undef cstring_set

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

struct cstring {
	size_t memsize;
	size_t length;
	/* char string[length + 1]; */
};

#define TO_STRING(STRUCT) ( (char *) ( (void *) (STRUCT) + sizeof(struct cstring) ) )
#define TO_STRUCT(STRING) ( (struct cstring *) ((STRING) - sizeof(struct cstring) ) )

/******************************************************************************
 * cstring_create series                                                      *
 *****************************************************************************/
CString cstring_create(char *string)
{
	struct cstring *cstring;
	size_t length, memsize;

	length = strlen(string);
	memsize = sizeof(struct cstring) + length + 1;

	cstring = malloc(memsize);
	if (cstring == NULL)
		return NULL;

	cstring->length = length;
	cstring->memsize = memsize;

	memcpy(TO_STRING(cstring), string, length + 1);

	return TO_STRING(cstring);
}

CString cstring_create_from(CString cstring)
{
	struct cstring *new, *origin;

	origin = TO_STRUCT(cstring);

	new = malloc(origin->memsize);
	if (new == NULL)
		return NULL;

	memcpy(new, TO_STRUCT(origin), origin->memsize);

	return TO_STRING(new);
}

CString cstring_create_empty(void)
{
	struct cstring *cstring = malloc(sizeof(struct cstring) + 1);
	if (cstring == NULL)
		return NULL;

	cstring->length = 0;
	cstring->memsize = sizeof(struct cstring) + 1;

	TO_STRING(cstring)[0] = '\0';

	return TO_STRING(cstring);
}
/******************************************************************************
 * cstring_compare series                                                     *
 *****************************************************************************/
bool cstring_compare(CString o, CString t)
{
	struct cstring *origin = TO_STRUCT(o), *target = TO_STRUCT(t);

	if (origin->length != target->length)
		return false;

	return !memcmp(TO_STRING(origin), TO_STRING(target), origin->length);
}

bool cstring_ncompare(CString o, CString t, size_t length)
{
	struct cstring *origin, *target;

	cstr1 = TO_STRUCT(c1);
	cstr2 = TO_STRUCT(c2);

	if (cstr1->length <= length && cstr2->length <= length)
		if (cstr1->length != cstr2->length)
			return false;

	return !memcmp(c1, c2, length);
}

bool cstring_ncompare_to_string(CString c, char *s, size_t length)
{
	struct cstring *cstr = TO_STRUCT(c);
	size_t slen = strlen(s);

	if (cstr->length <= length && slen <= length)
		if (cstr->length != slen)
			return false;

	return !memcmp(c, s, length);
}

bool cstring_compare_to_string(CString c, char *s)
{
	struct cstring *cstring = TO_STRUCT(c);
	size_t length = strlen(s);

	if (cstring->length != length)
		return false;

	return !memcmp(c, s, length);
}

CString cstring_append(CString c1, CString c2)
{
	struct cstring *cstr1 = TO_STRUCT(c1),
		       *cstr2 = TO_STRUCT(c2);
	struct cstring *result;
	char *copy = NULL;

	int prev_len = cstr1->length;
	int apnd_len = prev_len + cstr2->length;

	if (c1 == c2) {
		copy = malloc(cstr2->length);
		if (copy == NULL)
			return NULL;

		memcpy(copy, c2, cstr2->length);
	}

	if (cstr1->memsize - sizeof(struct cstring) < apnd_len + 1) {
		result = realloc(cstr1, sizeof(struct cstring) + apnd_len + 1);
		if (result == NULL) {
			if (copy != NULL)
				free(copy);

			return NULL;
		}
	}

	result->length = apnd_len;
	memcpy(TO_STRING(result) + prev_len, copy == NULL ? c2 : copy, apnd_len - prev_len + 1);

	free(copy);

	return TO_STRING(result);
}

CString cstring_append_string(CString c, char *s)
{
	struct cstring *cstring = TO_STRUCT(c);
	struct cstring *result;

	int prev_len = cstring->length;
	int apnd_len = prev_len + strlen(s);

	if (cstring->memsize - sizeof(struct cstring) < apnd_len + 1) {
		result = realloc(cstring, sizeof(struct cstring) + apnd_len + 1);
		if (result == NULL)
			return NULL;
	}

	result->length = apnd_len;
	memcpy(TO_STRING(result) + prev_len, s, apnd_len - prev_len + 1);

	return TO_STRING(result);
}


CString cstring_set(CString c1, CString c2)
{
	struct cstring *cstr1 = TO_STRUCT(c1),
		       *cstr2 = TO_STRUCT(c2);

	if (c1 == c2)
		return c1;

	if (cstr1->memsize < cstr2->memsize) {
		cstr1 = realloc(cstr1, cstr2->memsize);
		if (cstr1 == NULL)
			return NULL;
	
		cstr1->memsize = cstr2->memsize;
	}

	cstr1->length = cstr2->length;

	memcpy(TO_STRING(cstr1), c2, cstr2->length + 1);

	return TO_STRING(cstr1);
}

CString cstring_set_to_string(CString c, char *s)
{
	struct cstring *cstring = TO_STRUCT(c);
	int length = strlen(s);

	if (cstring->memsize - sizeof(struct cstring) < length) {
		cstring = realloc(cstring, length + sizeof(struct cstring));
		if (cstring == NULL)
			return NULL;

		cstring->memsize = length + sizeof(struct cstring);
	}

	cstring->length = length;
	memcpy(TO_STRING(cstring), s, length + 1);

	return TO_STRING(cstring);
}

CString cstring_slice(CString c, size_t s, size_t e)
{
	struct cstring *cstring = TO_STRUCT(c);

	if (s > cstring->length || e > cstring->length)
		return NULL;

	if (s >= e)
		return NULL;

	memcpy(TO_STRING(cstring), &TO_STRING(cstring)[s], e - s);
	TO_STRING(cstring)[e - 1] = '\0';

	cstring->length = e - s;

	return c;
}

CString cstring_clear(CString c)
{
	struct cstring *cstring = TO_STRUCT(c);

	cstring->length = 0;
	C2S(c)[0] = '\0';

	return NULL;
}

void cstring_destroy(CString c)
{
	free(TO_STRUCT(c));
}
