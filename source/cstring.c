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
	size_t allocate;
	size_t length;

	char *string;
};

#define GET_ALLOC_SIZE(LEN) (						\
	(((LEN) / CSTRING_ALLOCATE_CHUNK_SIZE)				\
       + ((LEN) % CSTRING_ALLOCATE_CHUNK_SIZE) != 0)			\
	* CSTRING_ALLOCATE_CHUNK_SIZE					\
)

#define IS_COLLAPSED(ORIGIN, TARGET, RANGE) (				\
	((ORIGIN) <= (TARGET)) && ((TARGET) < (ORIGIN) + (RANGE))	\
)

/******************************************************************************
 * cstring_create series                                                      *
 *****************************************************************************/
CString cstring_create(char *string)
{
	CString cstring;

	cstring = malloc(sizeof(struct cstring));
	if (cstring == NULL)
		return NULL;

	cstring->length = strlen(string) + 1;
	cstring->allocate = GET_ALLOC_SIZE(cstring->length);

	cstring->string = malloc(cstring->allocate);
	if (cstring->string == NULL) {
		free(cstring);
		return NULL;
	}

	memcpy(cstring->string, string, cstring->length);

	return cstring;
}

CString cstring_create_from(CString origin)
{
	CString new;

	new = malloc(sizeof(struct cstring));
	if (new == NULL)
		return NULL;

	new->allocate = GET_ALLOC_SIZE(origin->length);
	new->length = origin->length;

	new->string = malloc(new->allocate);
	if (new->string == NULL) {
		free(new);
		return NULL;
	}
	
	memcpy(new->string, origin->string, origin->length);

	return new;
}

CString cstring_create_empty(void)
{
	CString cstring;

	cstring = malloc(sizeof(struct cstring));
	if (cstring == NULL)
		return NULL;

	cstring->string = malloc(CSTRING_ALLOCATE_CHUNK_SIZE);
	if (cstring->string == NULL) {
		free(cstring);
		return NULL;
	}

	cstring->allocate = CSTRING_ALLOCATE_CHUNK_SIZE;
	cstring->length = 1;

	*cstring->string = '\0';

	return cstring;
}
/******************************************************************************
 * cstring_compare series                                                     *
 *****************************************************************************/
bool cstring_compare(CString origin, CString target)
{
	if (origin->length != target->length)
		return false;

	return memcmp(origin->string, target->string, origin->length);
}

bool cstring_ncompare(CString origin, CString target, size_t length)
{
	return memcmp(origin->string, target->string, length);
}

bool cstring_ncompare_to_string(CString origin, char *target, size_t length)
{
	return memcmp(origin->string, target, length);
}

bool cstring_compare_to_string(CString origin, char *target)
{
	size_t target_len = strlen(target);

	if (origin->length != target_len)
		return false;

	return memcmp(origin->string, target, origin->length);
}
/******************************************************************************
 * cstring_compare series                                                     *
 *****************************************************************************/
CString cstring_append(CString origin, CString append)
{
	size_t total_len = (origin->length - 1) + append->length;
	void *(*func)(void *, const void *, size_t);

	if (origin->allocate < total_len) {
		char *new_string = realloc(
			origin->string, GET_ALLOC_SIZE(total_len)
		);

		if (new_string == NULL)
			return NULL;

		origin->string = new_string;
	}

	func = IS_COLLAPSED(origin->string, append->string, origin->length)
	     ? memmove : memcpy;

	func(&origin->string[origin->length - 1], append->string, append->length);
	origin->length = total_len;

	return origin;
}

CString cstring_append_string(CString origin, char *append)
{
	size_t append_len = strlen(append) + 1;
	size_t total_len = (origin->length - 1) + append_len;
	void *(*func)(void *, const void *, size_t);

	if (origin->allocate < total_len) {
		char *new_string = realloc(
			origin->string, GET_ALLOC_SIZE(total_len)
		);

		if (new_string == NULL)
			return NULL;

		origin->string = new_string;
	}

	func = IS_COLLAPSED(origin->string, append, origin->length)
	     ? memmove : memcpy;

	func(&origin->string[origin->length - 1], append, append_len);
	origin->length = total_len;

	return origin;
}
/******************************************************************************
 * cstring_set series                                                         *
 *****************************************************************************/
CString cstring_set(CString origin, CString target)
{
	void *(*func)(void *, const void *, size_t);

	if (origin->allocate < target->length) {
		char *new_string = realloc(
			origin->string, GET_ALLOC_SIZE(target->length)
		);

		if (new_string == NULL)
			return NULL;

		origin->string = new_string;
	}

	func = IS_COLLAPSED(origin->string, target->string, origin->length)
	     ? memmove : memcpy;

	func(origin->string, target->string, target->length);
	origin->length = target->length;

	return origin;
}

CString cstring_set_to_string(CString origin, char *target)
{
	size_t target_len = strlen(target) + 1;
	void *(*func)(void *, const void *, size_t);

	if (origin->allocate < target_len) {
		char *new_string = realloc(
			origin->string, GET_ALLOC_SIZE(target_len)
		);

		if (new_string == NULL)
			return NULL;

		origin->string = new_string;
	}

	func = IS_COLLAPSED(origin->string, target, origin->length)
	     ? memmove : memcpy;

	func(origin->string, target, target_len);
	origin->length = target_len;

	return origin;
}
/******************************************************************************
 * cstring_### series                                                         *
 *****************************************************************************/
CString cstring_slice(CString cstring, size_t start, size_t end)
{
	memmove(cstring->string, &cstring->string[start], end - start);

	cstring->string[end - start] = '\0';

	return cstring;
}

void cstring_destroy(CString cstring)
{
	free(cstring->string);
	free(cstring);
}

size_t cstring_length(CString cstring)
{
	return cstring->length - 1;
}

char *cstring_get(CString cstring)
{
	return cstring->string;
}
