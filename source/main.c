#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "cstring.h"

static CString cstr1, cstr2, cstr3;

void create_cstring()
{
	cstr1 = cstring_create();
	cstr2 = cstring_create("hello world!");
	cstr3 = cstring_create(cstr2);

	if (cstr1 == NULL || cstr2 == NULL || cstr3 == NULL)
		assert("Failed to create cstring");
}

void print_cstring()
{
	printf("cstr1: %s\n", C2S(cstr1));
	printf("cstr2: %s\n", C2S(cstr2));
	printf("cstr3: %s\n", C2S(cstr3));
}

void compare_string()
{
	char *compare = "hello";
	int complen = 5;

	if (cstring_compare(cstr2, compare))
		assert("Failed to compare string");
	
	printf("\"%s\" != \"%s\"\n", C2S(cstr2), compare);

	if ( !cstring_compare(cstr2, compare, complen) )
		assert("Failed to compare string");

	printf("\"%.*s\" == \"%.*s\"\n", complen, C2S(cstr2), complen, compare);

	if ( !cstring_compare(cstr2, cstr3) )
		assert("Failed to compare string");

	printf("\"%s\" == \"%s\"\n", C2S(cstr2), C2S(cstr3));

	if ( !cstring_compare(cstr2, cstr3, complen) )
		assert("Failed to compare string");

	printf("\"%.*s\" == \"%.*s\"\n", complen, C2S(cstr2), complen, C2S(cstr3));
}

void clear_cstring()
{
	cstring_clear(cstr1);
	cstring_clear(cstr2);
	cstring_clear(cstr3);
}

void destroy_string()
{
	cstring_destroy(cstr1);
	cstring_destroy(cstr2);
	cstring_destroy(cstr3);
}

void append_string()
{
	char *append = "!!!!";

	cstr1 = cstring_append(cstr1, cstr2);
	if (cstr1 == NULL)
		assert("Failed to append string");

	cstr2 = cstring_append(cstr2, cstr2);
	if (cstr2 == NULL)
		assert("Failed to append string");

	cstr3 = cstring_append(cstr3, "!!!!");
	if (cstr2 == NULL)
		assert("Failed to append string");
}

void set_cstring()
{
	cstr1 = cstring_set(cstr1, "hello");
	if (cstr1 == NULL)
		assert("Failed to set string");

	cstr2 = cstring_set(cstr2, cstr1);
	if (cstr2 == NULL)
		assert("Failed to set string");

	cstr3 = cstring_set(cstr3, " world!");
	if (cstr3 == NULL)
		assert("Failed to set string");
}

void slice_cstring()
{
	cstr1 = cstring_slice(cstr1, 1, 5);
	if (cstr1 == NULL)
		assert("Failed to slice string");

	cstr2 = cstring_slice(cstr2, 1, 2);
	if (cstr2 == NULL)
		assert("Failed to slice string");

	cstr3 = cstring_slice(cstr3, 1, 6);
	if (cstr3 == NULL)
		assert("Failed to slice string");
}

int main(void)
{
	printf("# Create CString\n");
	create_cstring();
	print_cstring();

	putchar('\n');
	
	printf("# Compare CString\n");
	compare_string();

	putchar('\n');

	printf("# Append CString\n");
	append_string();
	print_cstring();

	putchar('\n');

	printf("# Clear CString\n");
	clear_cstring();
	print_cstring();

	putchar('\n');

	printf("# Set CString\n");
	set_cstring();
	print_cstring();

	putchar('\n');

	printf("# Slice CString\n");
	slice_cstring();
	print_cstring();

	destroy_string();

	return 0;
}
