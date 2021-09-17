#include "cstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define GET_HEADER(CSTR) ((struct header *) ((CSTR) - HEADER_SIZE))
#define GET_STRING(HEADER) ((char *) ((HEADER) + HEADER_SIZE))

#define DEFAULT_SIZE 1024
#define INCREMENT_SIZE (DEFAULT_SIZE * 4)
#define HEADER_SIZE sizeof(struct header)

struct header {
	int allocated;
	int used;
};

static int measure_alloc_size(int string_len);

CString _cstring_create_string(char *string)
{
	CString cstring;
	struct header *header;
	int alloc_size;
	int string_len;

	string_len = strlen(string) + 1;
	alloc_size = measure_alloc_size(string_len);

	cstring = malloc(alloc_size);
	if (cstring == NULL)
		return NULL;

	header = GET_HEADER(cstring);
	header->allocated = header->used = string_len;

	memcpy(GET_STRING(header), string, string_len);

	return GET_STRING(header);
}

CString _cstring_create_cstring(CString cstring)
{
	return _cstring_create_string(CTOS(cstring));
}

CString _cstring_copy_string(CString *origin, char *dest)
{
	struct header *header;
	int destlen;

	header = GET_HEADER(*origin);
	destlen = strlen(dest) + 1;

	if (header->allocated < destlen) {
		char *newptr;
		int newsize;

		newsize = measure_alloc_size(destlen);
		header = realloc(header, newsize);
		if (header == NULL)
			return NULL;

		if (GET_STRING(header) != *origin)
			*origin = GET_STRING(header);

		header->allocated = newsize;
	}

	header->used = destlen;

	memcpy(GET_STRING(header), dest, destlen);

	return GET_STRING(header);
}

CString _cstring_copy_cstring(CString *origin, CString *dest)
{
	return _cstring_copy_string(origin, CTOS(dest));
}

int _cstring_append_string(CString *origin, char *append)
{
	struct header *header;
	int appendlen, require;

	header = GET_HEADER(origin);
	appendlen = strlen(append) + 1;

	// both `appendlen` and `header->used` include null-character
	require = appendlen + header->used - 1;

	if (require > header->allocated) {
		realloc(header, cstring_get_newsize(require));
	}

	return 0;
}

int _cstring_append_cstring(CString origin, CString *append)
{
	return 0;
}

int cstring_length(CString cstring)
{
	return GET_HEADER(cstring)->used;
}

int _cstring_compare_string(CString cstr, char* str)
{
	return 0;
}

int _cstring_compare_cstring(CString cstr1, CString cstr2)
{
	return 0;
}

void cstring_destroy(CString cstring)
{
	free(GET_HEADER(cstring));
}

// ====================================================================================
static int measure_alloc_size(int string_len)
{
	int newsize = (string_len / INCREMENT_SIZE) + 1;

	newsize = newsize * INCREMENT_SIZE;

	return newsize + HEADER_SIZE;
}
