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

void set_string(void)
{
	assert( (cstr1 = cstring_set(cstr1, "hello world! ! !")) );
	assert( (cstr2 = cstring_set(cstr2, cstr1)) );
	assert( (cstr3 = cstring_set(cstr3, "hello world!")) );
}

void replace_string(void)
{
	assert ( !cstring_compare(cstring_replace(cstr1, "! ", '\0'), "helloworld") );
	assert ( !cstring_compare(cstring_replace(cstr3, "o", '0'), "hell0 w0rld!") );
}

void insert_string(void)
{
	printf("%s\n", cstring_get(cstr1));
	printf("%s\n", cstring_get(cstr2));

	assert ( cstring_insert(cstr1, 2, "good") );
	assert ( cstring_insert(cstr2, 5, cstr3) );

	printf("%s\n", cstring_get(cstr1));
	printf("%s\n", cstring_get(cstr2));
}

void trim_string(void)
{
	printf("%s\n", cstring_get(cstr1));
	assert ( cstring_trim(cstr1, 2, 6) );
	printf("%s\n", cstring_get(cstr1));
}

int main(void)
{
	create_cstring();

	compare_string();

	append_string();

	slice_string();

	set_string();

	replace_string();

	insert_string();

	trim_string();

	destroy_string();

	return 0;
}
