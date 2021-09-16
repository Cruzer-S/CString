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

CString _cstring_create_string(char *string)
{
	CString cstring;
	struct header *header;
	int len;

	len = strlen(string) + 1;
	if (len < HEADER_SIZE)
		len = HEADER_SIZE;

	cstring = malloc(DEFAULT_SIZE + len);
	if (cstring == NULL)
		return NULL;

	header = GET_HEADER(cstring);
	header->allocated = header->used = len;

	memcpy(GET_STRING(header), string, len);

	return GET_STRING(header);
}

CString _cstring_create_cstring(CString cstring)
{
	return _cstring_create_string(CTOS(cstring));
}

static int cstring_get_newsize(int current)
{
	int newsize = (current / INCREMENT_SIZE) + 1;

	newsize = newsize * INCREMENT_SIZE;

	return newsize;
}

CString _cstring_assign_string(CString *origin, char *dest)
{
	struct header *header;
	int destlen;

	header = GET_HEADER(*origin);
	destlen = strlen(dest) + 1;

	if (header->allocated < destlen) {
		char *newptr;
		int newsize;

		newsize = cstring_get_newsize(destlen);
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

CString _cstring_assign_cstring(CString *origin, CString *dest)
{
	return _cstring_assign_string(origin, CTOS(dest));
}

int _cstring_append_string(char *string)
{
	return 0;
}

int _cstring_append_cstring(CString cstring)
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

