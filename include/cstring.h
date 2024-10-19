#ifndef CSTRING_H__
#define CSTRING_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include "Cruzer-S/cmacro/cmacro.h"

#define CSTRING_ALLOCATE_CHUNK_SIZE BUFSIZ

typedef struct cstring *CString;

/* if the `string` is `NULL` or not a null terminated string,
 * then the result of the function is undefined.
 */
CString cstring_create(char *string);
CString cstring_create_empty(void);
/* if the `cstring` is `NULL`, then the result of the function is undefined. */
CString cstring_create_from(CString cstring);

#define cstring_create(...) EXCONCAT(cstring_create_, NARGS(__VA_ARGS__))(__VA_ARGS__)
#define cstring_create_0 cstring_create_empty
#define cstring_create_1(T) (_Generic((T),	\
	CString: cstring_create_from,		\
	char *: cstring_create,			\
	default: NULL				\
)(T))

/* Both `origin` and `target` have to be created by `cstring_create_###`,
 * if not so, the result of the function is undefined.
 */
bool cstring_compare(CString origin, CString target);
bool cstring_compare_to_string(CString origin, char *target);
/* `length` must be less than or equal to the length of the `target`
 * (without '\0'). if not so, the result of the function is undefined.
 */
bool cstring_ncompare(CString origin, CString target, size_t length);
/* - `length` must be less than or equal to the length of `target`
 *   (without '\0'). if not so, behavior of the function is undefined.
 *
 * - `target` have to be null terminated string. Otherwise, the result of the
 *   function is undefined.
 */
bool cstring_ncompare_to_string(CString origin, char *target, size_t length);

#define cstring_compare(...) EXCONCAT(cstring_compare_, NARGS(__VA_ARGS__))(__VA_ARGS__)
#define cstring_compare_2(A, B) (_Generic((B),		\
	CString: cstring_compare,			\
	char *: cstring_compare_to_string,		\
	default: NULL					\
)(A, B))
#define cstring_compare_3(A, B, C) (_Generic((B),	\
	CString: cstring_ncompare,			\
	char *: cstring_ncompare_to_string,		\
	default: NULL					\
)(A, B, C))

CString cstring_append(CString , CString );
CString cstring_append_string(CString , char *);

#define cstring_append(A, B) (_Generic((B),		\
	CString: cstring_append,			\
	char *: cstring_append_string,			\
	default: NULL					\
)(A, B))

#define cstring_get(...) EXCONCAT(cstring_get_, NARGS(__VA_ARGS__))(__VA_ARGS__)
#define cstring_get_1 cstring_get
#define cstring_get_2 cstring_get_at
char *cstring_get(CString );
char cstring_get_at(CString, size_t );

ptrdiff_t cstring_index(CString, char );

CString cstring_set(CString, CString );
CString cstring_set_to_string(CString, char *);
#define cstring_set(A, B) (_Generic((B),		\
	CString: cstring_set,				\
	char *: cstring_set_to_string,			\
	default: NULL					\
)(A, B))

CString cstring_slice(CString , size_t , size_t );

CString cstring_replace(CString , const char *, char );

CString cstring_insert_string(CString, size_t , char *);
CString cstring_insert_cstring(CString, size_t , CString );
#define cstring_insert(A, L, B) (_Generic((B),		\
	CString: cstring_insert_cstring,		\
	char *: cstring_insert_string,			\
	default: NULL					\
)(A, L, B))

void cstring_destroy(CString );

size_t cstring_length(CString );

#endif
