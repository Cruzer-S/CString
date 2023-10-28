#include "cstring.h"

#undef cstring_create
#undef cstring_compare
#undef cstring_append
#undef cstring_set

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

struct cstring {
	size_t memsize;
	size_t length;
	/* char string[length + 1]; */
};

#define SSIZE ( sizeof(struct cstring) )
#define TO_STRING(STRUCT) ( (char *) (((void *) (STRUCT)) + SSIZE) )
#define TO_STRUCT(STRING) ( (struct cstring *) (STRING - SSIZE) )
#define REMAIN_LEN(STRUCT) ( (STRUCT)->memsize - SSIZE - ((STRUCT)->length + 1) )
/******************************************************************************
 * cstring_create series                                                      *
 *****************************************************************************/
CString cstring_create(char *string)
{
	struct cstring *cstring;
	size_t length, memsize;

	length = strlen(string);
	memsize = SSIZE + length + 1;

	cstring = malloc(memsize);
	if (cstring == NULL)
		return NULL;

	cstring->length = length;
	cstring->memsize = memsize;

	memcpy(TO_STRING(cstring), string, length + 1);

	return TO_STRING(cstring);
}

CString cstring_create_from(CString o)
{
	struct cstring *new, *origin = TO_STRUCT(o);

	new = malloc(origin->memsize);
	if (new == NULL)
		return NULL;

	memcpy(new, origin, origin->memsize);

	return TO_STRING(new);
}

CString cstring_create_empty(void)
{
	struct cstring *cstring;

	cstring = malloc(SSIZE + 1);
	if (cstring == NULL)
		return NULL;

	cstring->length = 0;
	cstring->memsize = SSIZE + 1;

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
	struct cstring *origin = TO_STRUCT(o), *target = TO_STRUCT(t);

	if (origin->length != target->length)
		return false;

	return !memcmp(TO_STRING(origin), TO_STRING(target), length);
}

bool cstring_ncompare_to_string(CString origin, char *target, size_t length)
{
	return !memcmp(origin, target, length);
}

bool cstring_compare_to_string(CString o, char *target)
{
	struct cstring *origin = TO_STRUCT(o);
	size_t target_len = strlen(target);

	if (origin->length != target_len)
		return false;

	return !memcmp(TO_STRING(origin), target, origin->length);
}
/******************************************************************************
 * cstring_compare series                                                     *
 *****************************************************************************/
CString cstring_append(CString o, CString a)
{
	struct cstring *origin = TO_STRUCT(o), *append = TO_STRUCT(a);
	void *(*function)(void *, const void *, size_t);

	if (REMAIN_LEN(origin) < append->length) {
		struct cstring *new_origin;
		size_t total_len;	

		total_len = SSIZE + origin->length;
		total_len += append->length + 1;

		new_origin = realloc(origin, total_len);
		if (new_origin == NULL)
			return NULL;

		origin = new_origin;
		origin->memsize = total_len;
	}

	function = (origin == append) ? memmove : memcpy;
	function(
		TO_STRING(origin) + origin->length,
		TO_STRING(append),
		append->length + 1
	);

	origin->length = origin->length + append->length;

	return TO_STRING(origin);
}

CString cstring_append_string(CString o, char *append)
{
	struct cstring *origin = TO_STRUCT(o);
	size_t append_len = strlen(append);

	if (REMAIN_LEN(origin) < append_len) {
		struct cstring *new_origin;
		size_t total_len;

		total_len = SSIZE + origin->length;
		total_len += append_len + 1;

		new_origin = realloc(origin, total_len);
		if (new_origin == NULL)
			return NULL;

		origin = new_origin;
		origin->memsize = total_len;
	}

	memcpy(TO_STRING(origin), append, append_len + 1);
	origin->length = origin->length + append_len;

	return origin;
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

	if (cstring->memsize - SSIZE < length) {
		cstring = realloc(cstring, length + SSIZE);
		if (cstring == NULL)
			return NULL;

		cstring->memsize = length + SSIZE;
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

size_t cstring_length(CString cstring)
{
	return TO_STRUCT(cstring)->length;
}
