#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "cstring.h"

static CString cstr1, cstr2, cstr3;

void create_cstring(void)
{
	cstr1 = cstring_create();
	cstr2 = cstring_create("hello world!");
	cstr3 = cstring_create(cstr2);

	assert( !(cstr1 == NULL || cstr2 == NULL || cstr3 == NULL) );
}

void compare_string(void)
{
	char *compare = "hello";
	const int complen = 5;

	assert( !cstring_compare(cstr2, compare) );
	assert( !cstring_compare(cstr2, compare, complen) );
	assert( !cstring_compare(cstr2, cstr3) );
	assert( !cstring_compare(cstr2, cstr3, complen) );
}

void destroy_string(void)
{
	cstring_destroy(cstr1);
	cstring_destroy(cstr2);
	cstring_destroy(cstr3);
}

void append_string(void)
{
	const char *append = "!!!!";

	assert( (cstr1 = cstring_append(cstr1, cstr2)) );
	assert( (cstr2 = cstring_append(cstr2, cstr2)) );
	assert( (cstr3 = cstring_append(cstr3, "!!!!")) );
}

void slice_string(void)
{
	assert( !cstring_compare(cstring_slice(cstr1, 2, 7), "llo w ") );
	assert( !cstring_compare(cstring_slice(cstr2, 0, 12), "hello world!") );
	assert( !cstring_compare(cstring_slice(cstr3, 11, 16), "!!!!!") );
}

void set_cstring(void)
{
	assert( (cstr1 = cstring_set(cstr1, "hello")) );
	assert( (cstr2 = cstring_set(cstr2, cstr1)) );
	assert( (cstr3 = cstring_set(cstr3, " world!")) );
}

int main(void)
{
	create_cstring();

	compare_string();

	append_string();

	slice_string();

	set_cstring();

	destroy_string();

	return 0;
}
