#include <stdio.h>
#include <stdlib.h>

#include "cstring.h"

#define ERROR(FMT, ...) fprintf(stderr, FMT, ## __VA_ARGS__), exit(EXIT_FAILURE)

int main(void)
{
	CString cstr1, cstr2;

	cstr1 = cstring_create("hello");
	if (cstr1 == NULL)
		ERROR("cstring_create() error");

	cstring_destroy(cstr1);

	return 0;
}
