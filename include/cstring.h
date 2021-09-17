#ifndef CSTRING_H__
#define CSTRING_H__

typedef void *CString;

#define DEFINE_CSTRING_GENERIC(XSTR, NAME, ...)			\
	_Generic((XSTR),					\
		char * const: _cstring_##NAME##_string,		\
		const char *: _cstring_##NAME##_string,		\
		const char * const: _cstring_##NAME##_string,	\
		char *: _cstring_##NAME##_string,		\
		CString: _cstring_##NAME##_string)		\
	(XSTR, ## __VA_ARGS__)

#define cstring_create(XSTR, ...) DEFINE_CSTRING_GENERIC(XSTR, create, ## __VA_ARGS__)
#define cstring_copy(XSTR, ...) DEFINE_CSTRING_GENERIC(XSTR, copy, ## __VA_ARGS__)
#define cstring_append(XSTR, ...) DEFINE_CSTRING_GENERIC(XSTR, append, ## __VA_ARGS__)
#define cstring_assign(XSTR, ...) DEFINE_CSTRING_GENERIC(XSTR, assign, ## __VA_ARGS__)
#define cstring_compare(XSTR, ...) DEFINE_CSTRING_GENERIC(XSTR, compare, ## __VA_ARGS__)

#define CTOS(CSTR) ((char *) CSTR)

CString _cstring_create_string(char *string);
CString _cstring_create_cstring(CString cstring);

CString _cstring_copy_string(CString *origin, char *dest);
CString _cstring_copy_cstring(CString *origin, CString *dest);

int _cstring_append_string(CString origin, char *append);
int _cstring_append_cstring(CString origin, CString *append);

int cstring_length(CString cstring);

int _cstring_compare_string(CString cstr, char* str);
int _cstring_compare_cstring(CString cstr1, CString cstr2);

void cstring_destroy(CString cstring);

#endif
