#ifndef CSTRING_H__
#define CSTRING_H__

#include <stdlib.h>
#include <stdbool.h>

#include "Cruzer-S/cmacro/cmacro.h"

#define C2S(C) ( (char *) (C) )

typedef void *CString;

CString cstring_create(char *string);
CString cstring_create_empty();
CString cstring_create_from(CString );

#define cstring_create(...) EXCONCAT(cstring_create_, NARGS(__VA_ARGS__))(__VA_ARGS__)
#define cstring_create_0 cstring_create_empty
#define cstring_create_1(T) (_Generic((T),	\
	void *: cstring_create_from(T),		\
	char *: cstring_create(T),		\
	default: NULL				\
))

bool cstring_compare(CString, CString );
bool cstring_compare_to_string(CString, char *);
bool cstring_ncompare(CString, CString, size_t );
bool cstring_ncompare_to_string(CString ,char *, size_t);

#define cstring_compare(...) EXCONCAT(cstring_compare_, NARGS(__VA_ARGS__))(__VA_ARGS__)
#define cstring_compare_2(A, B) (_Generic((B),		\
	void *: cstring_compare(A, B),			\
	char *: cstring_compare_to_string(A, B),	\
	default: NULL					\
))
#define cstring_compare_3(A, B, C) (_Generic((B),	\
	void *: cstring_ncompare(A, B, C),		\
	char *: cstring_ncompare_to_string(A, B, C),	\
	default: NULL					\
))

CString cstring_append(CString , CString );
CString cstring_append_string(CString , char *);

#define cstring_append(A, B) (_Generic((B),		\
	void *: cstring_append(A, B),			\
	char *: cstring_append_string(A, B),		\
	default: NULL					\
))

CString cstring_slice(CString, size_t, size_t);

CString cstring_clear(CString );

CString cstring_set(CString, CString );
CString cstring_set_to_string(CString, char *);
#define cstring_set(A, B) (_Generic((B),		\
	void *: cstring_set(A, B),			\
	char *: cstring_set_to_string(A, B),		\
	default: NULL					\
))

void cstring_destroy(CString );

#endif
