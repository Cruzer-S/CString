#ifndef CSTRING_H__
#define CSTRING_H__

#include <stdlib.h>
#include <stdbool.h>

#define _ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define HAS_COMMA(...) _ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define _TRIGGER_PARENTHESIS_(...) ,

#define _ARGCNT1(...) 0
#define _ARGCNT0(...) _ARG16(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define NARGS(...) EXCONCAT(_ARGCNT,ISEMPTY(__VA_ARGS__))(__VA_ARGS__)
 
#define _ISEMPTY(_0, _1, _2, _3) HAS_COMMA(PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define ISEMPTY(...) _ISEMPTY(						\
	/* test if there is just one argument, eventually an empty	\
	 * one */							\
	HAS_COMMA(__VA_ARGS__),						\
	/* test if _TRIGGER_PARENTHESIS_ together with the argument	\
	 * adds a comma */						\
	HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__),			\
	/* test if the argument together with a parenthesis		\
	 * adds a comma */						\
	HAS_COMMA(__VA_ARGS__ (/*empty*/)),				\
	/* test if placing it between _TRIGGER_PARENTHESIS_ and the	\
	 * parenthesis adds a comma */					\
	HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/))	\
)

#define PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _IS_EMPTY_CASE_0001 ,

#define CONCAT(A, B) A ## B
#define EXCONCAT(A, B) CONCAT(A, B)

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
