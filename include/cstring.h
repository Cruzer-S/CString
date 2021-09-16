#ifndef CSTRING_H__
#define CSTRING_H__

typedef void *CString;

#define DEFINE_CSTRING_GENERIC(XSTR, NAME)			\
	_Generic((XSTR),					\
		char * const: _cstring_##NAME##_string		\
		const char *: _cstring_##NAME##_string		\
		const char * const: _cstring_##NAME##_string	\
		char *: _cstring_##NAME##_string		\
		CString: _cstring_##NAME##_string		\
	(XSTR)

#define cstring_create(XSTR) DEFINE_CSTRING_GENERIC(XSTR, create)
#define cstring_assign(XSTR) DEFINE_CSTRING_GENERIC(XSTR, assign)
#define cstring_append(XSTR) DEFINE_CSTRING_GENERIC(XSTR, append)
#define cstring_compare(XSTR) DEFINE_CSTRING_GENERIC(XSTR, compare)

CString _cstring_create_string(char *string);
CString _cstring_create_cstring(CString cstring);

int _cstring_assign_string(char *string);
int _cstring_assign_cstring(CString cstring);

int _cstring_append_string(char *string);
int _cstring_append_cstring(CString cstring);

int cstring_length(CString cstring);

int _cstring_compare_string(CString cstr, char* str);
int _cstring_compare_cstring(CString cstr1, CString cstr2);

CString cstring_destroy(CString cstring);

#endif
