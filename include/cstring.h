#ifndef CSTRING_H__
#define CSTRING_H__

#include <stdlib.h>
#include <stdbool.h>

#include "Cruzer-S/cmacro/cmacro.h"

#define C2S(C) ( (char *) (C) )

typedef void *CString;

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
	void *: cstring_create_from(T),		\
	char *: cstring_create(T),		\
	default: NULL				\
))

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

size_t cstring_length(CString );

#endif
