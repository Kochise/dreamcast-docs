/***
*stdlib.h - declarations/definitions for *ALL* CORELIBC functions
*
*    Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*    This include file contains the function declarations for
*    ALL CORELIBC functions 
*
****/

#ifndef _INC_STDLIB
#define _INC_STDLIB

#define COREDLL_CRT 1

#ifdef __cplusplus
extern "C" {
#endif

/* Define _CRTAPI1 (for compatibility with the NT SDK) */
#ifndef _CRTAPI1
#if     _MSC_VER >= 800 && _M_IX86 >= 300
#define _CRTAPI1 __cdecl
#else
#define _CRTAPI1
#endif
#endif

/* Define _CRTAPI2 (for compatibility with the NT SDK) */
#ifndef _CRTAPI2
#if     _MSC_VER >= 800 && _M_IX86 >= 300
#define _CRTAPI2 __cdecl
#else
#define _CRTAPI2
#endif
#endif

#ifndef _CRTIMP
#if defined(COREDLL) || !defined(UNDER_CE)
#define _CRTIMP
#else
#define _CRTIMP __declspec(dllimport)
#endif
#endif

typedef unsigned int   size_t;
#if ! defined(_WCHAR_T_DEFINED)			// part of C++ standard, now
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED 1
#endif
typedef wchar_t        wint_t;
typedef wchar_t        wctype_t;

#ifndef _TIME_T_DEFINED
typedef unsigned long  time_t;
#define _TIME_T_DEFINED 	/* avoid multiple def's of time_t */
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined (_M_CEE)
	typedef struct { void* p[4]; } va_list;
#else
	typedef char *va_list;
#endif

// Malloc function prototypes, MALLOC.H
_CRTIMP void   __cdecl free(void *);
_CRTIMP void * __cdecl malloc(size_t);
size_t __cdecl _msize(void *);
_CRTIMP void * __cdecl realloc(void *, size_t);

// implemented by compiler
void * __cdecl _alloca(size_t);

// process exit functions
void __cdecl exit (int code);
void __cdecl _exit (int code);
void __cdecl _cexit(void);
void __cdecl _c_exit (void);
int __cdecl atexit(void (__cdecl *)(void));

#if !__STDC__
/* Non-ANSI names for compatibility */
#define alloca  _alloca
#endif  /* __STDC__*/

#if defined(_M_MRX000) || defined(_M_PPC) || defined(_M_ALPHA)
#pragma intrinsic(_alloca)
#endif

// Widechar string functions, originally from STRING.H
_CRTIMP wchar_t * __cdecl wcscat(wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl wcschr(const wchar_t *, wchar_t);
_CRTIMP int       __cdecl wcscmp(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl wcscpy(wchar_t *, const wchar_t *);
_CRTIMP size_t    __cdecl wcscspn(const wchar_t *, const wchar_t *);
_CRTIMP size_t    __cdecl wcslen(const wchar_t *); 
_CRTIMP size_t    __cdecl mbstowcs(wchar_t *wcstr, const char *mbstr, size_t count);
_CRTIMP size_t    __cdecl wcstombs(char *mbstr, const wchar_t *wcstr, size_t count);
_CRTIMP wchar_t * __cdecl wcsncat(wchar_t *, const wchar_t *, size_t);
_CRTIMP int       __cdecl wcsncmp(const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl wcsncpy(wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl wcspbrk(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl wcsrchr(const wchar_t *, wchar_t);
_CRTIMP size_t    __cdecl wcsspn(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl wcsstr(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl wcstok(wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl _wcsdup(const wchar_t *);
_CRTIMP int       __cdecl _wcsicmp(const wchar_t *, const wchar_t *);
_CRTIMP int       __cdecl _wcsnicmp(const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl _wcsnset(wchar_t *, wchar_t, size_t);
_CRTIMP wchar_t * __cdecl _wcsrev(wchar_t *);
_CRTIMP wchar_t * __cdecl _wcsset(wchar_t *, wchar_t);
_CRTIMP wchar_t * __cdecl _wcslwr(wchar_t *);
_CRTIMP wchar_t * __cdecl _wcsupr(wchar_t *);

// Non STDC old names for above
#define wcsdup    _wcsdup
#define wcsicmp   _wcsicmp
#define wcsnicmp  _wcsnicmp
#define wcsnset   _wcsnset
#define wcsrev    _wcsrev
#define wcsset    _wcsset
#define wcslwr    _wcslwr
#define wcsupr    _wcsupr

// ANSI string functions, originally from STRING.H
size_t __cdecl strlen(const char *);
int    __cdecl strcmp(const char *, const char *);
char * __cdecl strcat(char *, const char *);
char * __cdecl strcpy(char *, const char *);

_CRTIMP char * __cdecl strchr(const char *, int);
_CRTIMP size_t __cdecl strcspn(const char *, const char *);
_CRTIMP char * __cdecl strncat(char *, const char *, size_t);
_CRTIMP int    __cdecl strncmp(const char *, const char *, size_t);
_CRTIMP char * __cdecl strncpy(char *, const char *, size_t);
_CRTIMP char * __cdecl strstr(const char *, const char *);
_CRTIMP char * __cdecl strtok(char *, const char *);

#ifndef UNDER_CE
_CRTIMP char *  __cdecl strpbrk(const char *, const char *);
_CRTIMP char *  __cdecl strrchr(const char *, int);
_CRTIMP size_t  __cdecl strspn(const char *, const char *);
_CRTIMP char *  __cdecl _strdup(const char *);
_CRTIMP int     __cdecl _stricmp(const char *, const char *);
_CRTIMP int     __cdecl _strnicmp(const char *, const char *, size_t);
_CRTIMP char *  __cdecl _strnset(char *, int, size_t);
_CRTIMP char *  __cdecl _strrev(char *);
_CRTIMP char *  __cdecl _strset(char *, int);
_CRTIMP char *  __cdecl _strlwr(char *);
_CRTIMP char *  __cdecl _strupr(char *);
#endif

// Mem functions, originally from MEMORY.H
int    __cdecl memcmp(const void *, const void *, size_t);
void * __cdecl memcpy(void *, const void *, size_t);
void * __cdecl memset(void *, int, size_t);

_CRTIMP void * __cdecl memchr(const void *, int, size_t);
_CRTIMP int    __cdecl _memicmp(const void *, const void *, unsigned int);
_CRTIMP void * __cdecl _memccpy(void *, const void *, int, unsigned int);
_CRTIMP void * __cdecl memmove(void *, const void *, size_t);

// Data structures used by iswXXXX macros, originally from CTYPE.H
extern _CRTIMP const unsigned short  _ctype[];
extern _CRTIMP const unsigned short *_pctype;
extern _CRTIMP const wctype_t *_pwctype;

// Bit masks used by iswXXX macros, CTYPE.H
#define _UPPER      0x1    /* upper case letter */
#define _LOWER      0x2    /* lower case letter */
#define _DIGIT      0x4    /* digit[0-9] */
#define _SPACE      0x8    /* tab, carriage return, newline, */
#define _PUNCT      0x10    /* punctuation character */
#define _CONTROL    0x20    /* control character */
#define _BLANK      0x40    /* space char */
#define _HEX        0x80    /* hexadecimal digit */
#define _ALPHA      (0x0100|_UPPER|_LOWER)    /* alphabetic character */

// character classification function prototypes, CTYPE.H
_CRTIMP int     iswctype(wint_t, wctype_t);
_CRTIMP wchar_t towupper(wchar_t);
_CRTIMP wchar_t towlower(wchar_t);

// the character classification macro definitions, CTYPE.H
#ifndef UNDER_CE
_CRTIMP int __cdecl _isctype(int, int);
#define isalpha(_c)      ( _isctype(_c,_ALPHA) )
#define isupper(_c)      ( _isctype(_c,_UPPER) )
#define islower(_c)      ( _isctype(_c,_LOWER) )
#define isdigit(_c)      ( _isctype(_c,_DIGIT) )
#define isxdigit(_c)     ( _isctype(_c,_HEX) )
#define isspace(_c)      ( _isctype(_c,_SPACE) )
#define ispunct(_c)      ( _isctype(_c,_PUNCT) )
#define isalnum(_c)      ( _isctype(_c,_ALPHA|_DIGIT) )
#define isprint(_c)      ( _isctype(_c,_BLANK|_PUNCT|_ALPHA|_DIGIT) )
#define isgraph(_c)      ( _isctype(_c,_PUNCT|_ALPHA|_DIGIT) )
#define iscntrl(_c)      ( _isctype(_c,_CONTROL) )
#define isascii(_c)      ( (unsigned)(_c) < 0x80 )
#endif

#define iswalpha(_c)     ( iswctype(_c,_ALPHA) )
#define iswupper(_c)     ( iswctype(_c,_UPPER) )
#define iswlower(_c)     ( iswctype(_c,_LOWER) )
#define iswdigit(_c)     ( iswctype(_c,_DIGIT) )
#define iswxdigit(_c)    ( iswctype(_c,_HEX) )
#define iswspace(_c)     ( iswctype(_c,_SPACE) )
#define iswpunct(_c)     ( iswctype(_c,_PUNCT) )
#define iswalnum(_c)     ( iswctype(_c,_ALPHA|_DIGIT) )
#define iswprint(_c)     ( iswctype(_c,_BLANK|_PUNCT|_ALPHA|_DIGIT) )
#define iswgraph(_c)     ( iswctype(_c,_PUNCT|_ALPHA|_DIGIT) )
#define iswcntrl(_c)     ( iswctype(_c,_CONTROL) )
#define iswascii(_c)     ( (unsigned)(_c) < 0x80 )
#define isleadbyte(_c)   ( IsDBCSLeadByte(_c))

// STDIO constant defns 
#define _MAX_PATH    MAX_PATH

// EOF constants
#define EOF  (-1)
#define WEOF (wint_t)(0xFFFF)

// Seek method constants, STDIO.H
#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

// mode constants for _setmode()
#define _O_TEXT 	0x4000	/* file mode is text (translated) */
#define _O_BINARY	0x8000	/* file mode is binary (untranslated) */

// FILE is an opaque handle in Win CE. Users have no access to the internals
#ifndef _FILE_DEFINED
typedef void FILE;
#define _FILE_DEFINED
#endif

#if _INTEGRAL_MAX_BITS >= 64
typedef __int64 fpos_t;
#else
typedef long fpos_t;
#endif

// Std handle defns
#define stdin  _getstdfilex(0)
#define stdout _getstdfilex(1)
#define stderr _getstdfilex(2)

// @CESYSGEN IF COREDLL_CORESTRA
// ANSI String formatting functions
_CRTIMP int    __cdecl sscanf(const char *, const char *, ...);
_CRTIMP int    __cdecl sprintf(char *, const char *, ...);
_CRTIMP int    __cdecl vsprintf(char *, const char *, va_list);
_CRTIMP int    __cdecl _snprintf(char *, size_t, const char *, ...);
_CRTIMP int    __cdecl _vsnprintf(char *, size_t, const char *, va_list);
// @CESYSGEN ENDIF

// Always present since wsprintfW (used by kernel) redirects to these
_CRTIMP int __cdecl swprintf(wchar_t *, const wchar_t *, ...);
_CRTIMP int __cdecl vswprintf(wchar_t *, const wchar_t *, va_list);
_CRTIMP int __cdecl _snwprintf(wchar_t *, size_t, const wchar_t *, ...);
_CRTIMP int __cdecl _vsnwprintf(wchar_t *, size_t, const wchar_t *, va_list);

// @CESYSGEN IF COREDLL_CORESTRW
// WIDE String formatting functions
_CRTIMP int __cdecl swscanf(const wchar_t *, const wchar_t *, ...);
// @CESYSGEN ENDIF

// @CESYSGEN IF COREDLL_CORESIOA

// ANSI Stdin/Out functions & macros
_CRTIMP int    __cdecl scanf(const char *, ...);
_CRTIMP int    __cdecl printf(const char *, ...);
_CRTIMP int    __cdecl vprintf(const char *, va_list);
_CRTIMP int    __cdecl getchar(void);
_CRTIMP char * __cdecl gets(char *);
_CRTIMP int    __cdecl putchar(int);
_CRTIMP int    __cdecl puts(const char *); 

// ANSI functions for Stdin/out and/or general buffered file handling
_CRTIMP int    __cdecl fgetc(FILE *);
_CRTIMP char * __cdecl fgets(char *, int, FILE *);
_CRTIMP int    __cdecl fputc(int, FILE *);
_CRTIMP int    __cdecl fputs(const char *, FILE *);
_CRTIMP int    __cdecl ungetc(int, FILE *);

// ANSI functions for general buffered file handling
_CRTIMP FILE * __cdecl fopen(const char *, const char *);
_CRTIMP int    __cdecl fscanf(FILE *, const char *, ...);
_CRTIMP int    __cdecl fprintf(FILE *, const char *, ...);
_CRTIMP int    __cdecl vfprintf(FILE *, const char *, va_list);

#define getc(_stream)     fgetc(_stream)
#define putc(_i, _stream) fputc(_i, _stream)

// @CESYSGEN ENDIF

// @CESYSGEN IF COREDLL_CORESIOA || COREDLL_CORESIOW

// functions for general buffered file handling in either ANSI or Wide
_CRTIMP FILE*  __cdecl _getstdfilex(int);
_CRTIMP int    __cdecl fclose(FILE *);
_CRTIMP int    __cdecl _fcloseall(void);
_CRTIMP size_t __cdecl fread(void *, size_t, size_t, FILE *);
_CRTIMP size_t __cdecl fwrite(const void *, size_t, size_t, FILE *);
_CRTIMP int    __cdecl fflush(FILE *);
_CRTIMP int    __cdecl _flushall(void);
_CRTIMP int    __cdecl feof(FILE *);
_CRTIMP int    __cdecl ferror(FILE *);
_CRTIMP void   __cdecl clearerr(FILE *);
_CRTIMP int    __cdecl fgetpos(FILE *, fpos_t *);
_CRTIMP int    __cdecl fsetpos(FILE *, const fpos_t *);
_CRTIMP int    __cdecl fseek(FILE *, long, int);
_CRTIMP long   __cdecl ftell(FILE *);
_CRTIMP void*  __cdecl _fileno(FILE *);
_CRTIMP int    __cdecl _setmode(FILE *, int mode);
_CRTIMP FILE*  __cdecl _wfdopen(void*, const wchar_t*);
_CRTIMP FILE*  __cdecl _wfreopen(const wchar_t *path, const wchar_t *mode, FILE *stream);
// old names
#define fcloseall _fcloseall
#define fileno    _fileno
#define flushall  _flushall

// @CESYSGEN ENDIF

// @CESYSGEN IF COREDLL_CORESIOW

// WIDE Stdin/Out functions & macros
_CRTIMP int __cdecl wscanf(const wchar_t *, ...);
_CRTIMP int __cdecl wprintf(const wchar_t *, ...);
_CRTIMP int __cdecl vwprintf(const wchar_t *, va_list);
_CRTIMP wint_t __cdecl getwchar(void);
_CRTIMP wint_t __cdecl putwchar(wint_t);
_CRTIMP wchar_t * __cdecl _getws(wchar_t *);
_CRTIMP int __cdecl _putws(const wchar_t *);

// WIDE functions for Stdin/out and/or general buffered file handling
_CRTIMP wint_t __cdecl fgetwc(FILE *);
_CRTIMP wint_t __cdecl fputwc(wint_t, FILE *);
_CRTIMP wint_t __cdecl ungetwc(wint_t, FILE *);
_CRTIMP wchar_t * __cdecl fgetws(wchar_t *, int, FILE *);
_CRTIMP int __cdecl fputws(const wchar_t *, FILE *);

#define getwc(_stm)             fgetwc(_stm)
#define putwc(_c,_stm)          fputwc(_c,_stm)

// WIDE functions for general buffered file handling
_CRTIMP FILE * __cdecl _wfopen(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl fwscanf(FILE *, const wchar_t *, ...);
_CRTIMP int __cdecl fwprintf(FILE *, const wchar_t *, ...);
_CRTIMP int __cdecl vfwprintf(FILE *, const wchar_t *, va_list);

// @CESYSGEN ENDIF

// min and max macros, STDLIB.H
#define __max(a,b)    (((a) > (b)) ? (a) : (b))
#define __min(a,b)    (((a) < (b)) ? (a) : (b))

// Conversion function prototypes, STDLIB.H
#ifndef UNDER_CE
_CRTIMP double __cdecl strtod(const char *, char **);
_CRTIMP long   __cdecl strtol(const char *, char **, int);
_CRTIMP unsigned long __cdecl strtoul(const char *, char **, int);
_CRTIMP __int64 __cdecl _atoi64(const char *);
#endif
_CRTIMP int    __cdecl atoi(const char *);
_CRTIMP double __cdecl atof(const char *);
_CRTIMP long   __cdecl atol(const char *);
char * __cdecl _itoa(int, char *, int);
char * __cdecl _ltoa(long, char *, int);
char * __cdecl _ultoa(unsigned long, char *, int);
char * __cdecl _ecvt(double, int, int *, int *);
char * __cdecl _fcvt(double, int, int *, int *);
char * __cdecl _gcvt(double, int, char *);
_CRTIMP int    __cdecl tolower(int);
_CRTIMP int    __cdecl toupper(int);
_CRTIMP double __cdecl wcstod(const wchar_t *, wchar_t **);
_CRTIMP long   __cdecl wcstol(const wchar_t *, wchar_t **, int);
wchar_t * __cdecl _ultow (unsigned long, wchar_t *, int);
wchar_t * __cdecl _itow (int, wchar_t *, int);
wchar_t * __cdecl _ltow (long, wchar_t *, int);
_CRTIMP long      __cdecl _wtol(const wchar_t *);
_CRTIMP __int64   __cdecl _wtoll(const wchar_t *);
unsigned long __cdecl wcstoul(const wchar_t *, wchar_t **, int);
#define _wtoi   _wtol
#define _wtoi64 _wtoll

// Extended logical Ops functions, STDLIB.H
unsigned long __cdecl _lrotl(unsigned long, int);
unsigned long __cdecl _lrotr(unsigned long, int);
unsigned int  __cdecl _rotl(unsigned int, int);
unsigned int  __cdecl _rotr(unsigned int, int);

// Other misc STDLIB functions
_CRTIMP void   __cdecl _swab(char *, char *, int);
_CRTIMP int    __cdecl rand(void);
_CRTIMP void   __cdecl srand(unsigned int);
void   __cdecl qsort(void *, size_t, size_t, int (__cdecl *)(const void *, const void *));
double __cdecl difftime(time_t, time_t);

// Maximum value that can be returned by the rand function.
#define RAND_MAX 0x7fff

// onexit() defns, STDLIB.H
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
typedef int (__cdecl * _onexit_t)(void);
#define onexit_t _onexit_t

// Data structure & function definitions for div and ldiv runtimes, STDLIB.H
typedef struct _div_t {
    int quot;
    int rem;
} div_t;

typedef struct _ldiv_t {
    long quot;
    long rem;
} ldiv_t;

div_t  __cdecl div(int, int);
ldiv_t __cdecl ldiv(long, long);

// Limits originally from LIMITS.H
#define CHAR_BIT     8        /* number of bits in a char */
#define SCHAR_MIN    (-128)        /* minimum signed char value */
#define SCHAR_MAX    127        /* maximum signed char value */
#define UCHAR_MAX    0xff        /* maximum unsigned char value */

#ifndef _CHAR_UNSIGNED
#define CHAR_MIN    SCHAR_MIN    /* mimimum char value */
#define CHAR_MAX    SCHAR_MAX    /* maximum char value */
#else
#define CHAR_MIN    0
#define CHAR_MAX    UCHAR_MAX
#endif    /* _CHAR_UNSIGNED */

#define MB_LEN_MAX  2        /* max. # bytes in multibyte char */
#define SHRT_MIN    (-32768)    /* minimum (signed) short value */
#define SHRT_MAX    32767     /* maximum (signed) short value */
#define USHRT_MAX   0xffff    /* maximum unsigned short value */
#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX     2147483647    /* maximum (signed) int value */
#define UINT_MAX    0xffffffff    /* maximum unsigned int value */
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX    2147483647L    /* maximum (signed) long value */
#define ULONG_MAX   0xffffffffUL    /* maximum unsigned long value */

#if    _INTEGRAL_MAX_BITS >= 8
#define _I8_MIN     (-127i8 - 1)    /* minimum signed 8 bit value */
#define _I8_MAX     127i8        /* maximum signed 8 bit value */
#define _UI8_MAX    0xffui8    /* maximum unsigned 8 bit value */
#endif

#if    _INTEGRAL_MAX_BITS >= 16
#define _I16_MIN    (-32767i16 - 1)    /* minimum signed 16 bit value */
#define _I16_MAX    32767i16    /* maximum signed 16 bit value */
#define _UI16_MAX   0xffffui16    /* maximum unsigned 16 bit value */
#endif

#if    _INTEGRAL_MAX_BITS >= 32
#define _I32_MIN    (-2147483647i32 - 1) /* minimum signed 32 bit value */
#define _I32_MAX    2147483647i32 /* maximum signed 32 bit value */
#define _UI32_MAX   0xffffffffui32 /* maximum unsigned 32 bit value */
#endif

#if    _INTEGRAL_MAX_BITS >= 64
/* minimum signed 64 bit value */
#define _I64_MIN    (-9223372036854775807i64 - 1)
/* maximum signed 64 bit value */
#define _I64_MAX      9223372036854775807i64
/* maximum unsigned 64 bit value */
#define _UI64_MAX      0xffffffffffffffffui64
#endif

#if    _INTEGRAL_MAX_BITS >= 128
/* minimum signed 128 bit value */
#define _I128_MIN    (-170141183460469231731687303715884105727i128 - 1)
/* maximum signed 128 bit value */
#define _I128_MAX      170141183460469231731687303715884105727i128
/* maximum unsigned 128 bit value */
#define _UI128_MAX      0xffffffffffffffffffffffffffffffffui128
#endif

// Defns from FLOAT.H
#define DBL_DIG        15            /* # of decimal digits of precision */
#define DBL_EPSILON    2.2204460492503131e-016 /* smallest such that 1.0+DBL_EPSILON != 1.0 */
#define DBL_MANT_DIG   53            /* # of bits in mantissa */
#define DBL_MAX        1.7976931348623158e+308 /* max value */
#define DBL_MAX_10_EXP 308            /* max decimal exponent */
#define DBL_MAX_EXP    1024            /* max binary exponent */
#define DBL_MIN        2.2250738585072014e-308 /* min positive value */
#define DBL_MIN_10_EXP (-307)            /* min decimal exponent */
#define DBL_MIN_EXP    (-1021)         /* min binary exponent */
#define _DBL_RADIX     2            /* exponent radix */
#define _DBL_ROUNDS    1            /* addition rounding: near */

#define FLT_DIG        6            /* # of decimal digits of precision */
#define FLT_EPSILON    1.192092896e-07F    /* smallest such that 1.0+FLT_EPSILON != 1.0 */
#define FLT_GUARD      0
#define FLT_MANT_DIG   24            /* # of bits in mantissa */
#define FLT_MAX        3.402823466e+38F    /* max value */
#define FLT_MAX_10_EXP 38            /* max decimal exponent */
#define FLT_MAX_EXP    128            /* max binary exponent */
#define FLT_MIN        1.175494351e-38F    /* min positive value */
#define FLT_MIN_10_EXP (-37)            /* min decimal exponent */
#define FLT_MIN_EXP    (-125)            /* min binary exponent */
#define FLT_NORMALIZE  0
#define FLT_RADIX      2            /* exponent radix */
#define FLT_ROUNDS     1            /* addition rounding: near */

#define LDBL_DIG        DBL_DIG         /* # of decimal digits of precision */
#define LDBL_EPSILON    DBL_EPSILON        /* smallest such that 1.0+LDBL_EPSILON != 1.0 */
#define LDBL_MANT_DIG   DBL_MANT_DIG        /* # of bits in mantissa */
#define LDBL_MAX        DBL_MAX         /* max value */
#define LDBL_MAX_10_EXP DBL_MAX_10_EXP        /* max decimal exponent */
#define LDBL_MAX_EXP    DBL_MAX_EXP        /* max binary exponent */
#define LDBL_MIN        DBL_MIN         /* min positive value */
#define LDBL_MIN_10_EXP DBL_MIN_10_EXP        /* min decimal exponent */
#define LDBL_MIN_EXP    DBL_MIN_EXP        /* min binary exponent */
#define _LDBL_RADIX     DBL_RADIX        /* exponent radix */
#define _LDBL_ROUNDS    DBL_ROUNDS        /* addition rounding: near */

// Abstract User Control Word Mask and bit definitions
#define _MCW_EM         0x0008001f        /* interrupt Exception Masks */
#define _EM_INEXACT     0x00000001        /*   inexact (precision) */
#define _EM_UNDERFLOW   0x00000002        /*   underflow */
#define _EM_OVERFLOW    0x00000004        /*   overflow */
#define _EM_ZERODIVIDE  0x00000008        /*   zero divide */
#define _EM_INVALID     0x00000010        /*   invalid */
#define _MCW_RC         0x00000300        /* Rounding Control */
#define _RC_NEAR        0x00000000        /*   near */
#define _RC_DOWN        0x00000100        /*   down */
#define _RC_UP          0x00000200        /*   up */
#define _RC_CHOP        0x00000300        /*   chop */

// Abstract User Status Word bit definitions
#define _SW_INEXACT     0x00000001        /* inexact (precision) */
#define _SW_UNDERFLOW   0x00000002        /* underflow */
#define _SW_OVERFLOW    0x00000004        /* overflow */
#define _SW_ZERODIVIDE  0x00000008        /* zero divide */
#define _SW_INVALID     0x00000010        /* invalid */

#if ! defined (_M_CEE)

// i386 specific definitions
#define _MCW_PC       0x00030000        /* Precision Control */
#define _PC_64        0x00000000        /*    64 bits */
#define _PC_53        0x00010000        /*    53 bits */
#define _PC_24        0x00020000        /*    24 bits */
#define _MCW_IC       0x00040000        /* Infinity Control */
#define _IC_AFFINE    0x00040000        /*   affine */
#define _IC_PROJECTIVE  0x00000000        /*   projective */
#define _EM_DENORMAL    0x00080000        /* denormal exception mask (_control87 only) */
#define _SW_DENORMAL    0x00080000        /* denormal status bit */

// MIPS R4000 and SH4 specific definitions
#ifdef  _M_SH
#define _MCW_DN     0x00040000      /* Denormal Control (SH4)   */
#define _DN_FLUSH   0x00040000      /*   flush to zero (SH4)    */
#else
#define _MCW_DN     0x01000000      /* Denormal Control (R4000) */
#define _DN_FLUSH   0x01000000      /*   flush to zero (R4000)  */
#endif
#define _DN_SAVE    0x00000000        /*   save */


// initial Control Word value
#ifdef    _M_IX86
#define _CW_DEFAULT ( _RC_NEAR + _PC_64 + _EM_INVALID + _EM_ZERODIVIDE + _EM_OVERFLOW + _EM_UNDERFLOW + _EM_INEXACT )
#elif defined(_M_SH) || defined(_M_MRX000)
#define _CW_DEFAULT ( _RC_NEAR + _PC_53 + _EM_INVALID + _EM_ZERODIVIDE + _EM_OVERFLOW + _EM_UNDERFLOW + _EM_INEXACT )
#endif

#endif	// ! _M_CEE

// invalid subconditions (_SW_INVALID also set)
#define _SW_UNEMULATED      0x0040    /* unemulated instruction */
#define _SW_SQRTNEG         0x0080    /* square root of a neg number */
#define _SW_STACKOVERFLOW   0x0200    /* FP stack overflow */
#define _SW_STACKUNDERFLOW  0x0400    /* FP stack underflow */

//  Floating point error signals and return codes
#define _FPE_INVALID        0x81
#define _FPE_DENORMAL       0x82
#define _FPE_ZERODIVIDE     0x83
#define _FPE_OVERFLOW       0x84
#define _FPE_UNDERFLOW      0x85
#define _FPE_INEXACT        0x86
#define _FPE_UNEMULATED     0x87
#define _FPE_SQRTNEG        0x88
#define _FPE_STACKOVERFLOW  0x8a
#define _FPE_STACKUNDERFLOW 0x8b
#define _FPE_EXPLICITGEN    0x8c    /* raise( SIGFPE ); */

// Floating point function prototypes
unsigned int __cdecl _clearfp(void);
unsigned int __cdecl _controlfp(unsigned int,unsigned int);
unsigned int __cdecl _statusfp(void);
void         __cdecl _fpreset(void);
#define _clear87    _clearfp
#define _status87   _statusfp

// IEEE recommended functions
double __cdecl _copysign (double, double);
double __cdecl _chgsign (double);
double __cdecl _scalb(double, long);
double __cdecl _logb(double);
double __cdecl _nextafter(double, double);
int    __cdecl _finite(double);
int    __cdecl _isnan(double);
int    __cdecl _fpclass(double);

#define _FPCLASS_SNAN    0x0001    /* signaling NaN */
#define _FPCLASS_QNAN    0x0002    /* quiet NaN */
#define _FPCLASS_NINF    0x0004    /* negative infinity */
#define _FPCLASS_NN    0x0008    /* negative normal */
#define _FPCLASS_ND    0x0010    /* negative denormal */
#define _FPCLASS_NZ    0x0020    /* -0 */
#define _FPCLASS_PZ    0x0040    /* +0 */
#define _FPCLASS_PD    0x0080    /* positive denormal */
#define _FPCLASS_PN    0x0100    /* positive normal */
#define _FPCLASS_PINF    0x0200    /* positive infinity */

typedef float _FP32;
typedef double _FP64;
typedef short _I16;
typedef int	_I32;
typedef unsigned short _U16;
typedef unsigned int _U32;

typedef struct {
    unsigned long W[4];
} _U32ARRAY;

typedef struct {
    unsigned short W[5];
} _FP80;

typedef struct {
    unsigned long W[4];
} _FP128;

typedef struct {
    unsigned long W[2];
} _I64;

typedef struct {
    unsigned long W[2];
} _U64;

typedef struct {
    unsigned short W[5];
} _BCD80;

typedef struct {
    union {
		_FP32	     Fp32Value;
		_FP64	     Fp64Value;
		_FP80	     Fp80Value;
		_FP128	     Fp128Value;
		_I16	     I16Value;
		_I32	     I32Value;
		_I64	     I64Value;
		_U16	     U16Value;
		_U32	     U32Value;
		_U64	     U64Value;
		_BCD80	     Bcd80Value;
		char	     *StringValue;
		int	     CompareValue;
		_U32ARRAY    U32ArrayValue;
    } Value;
    unsigned int OperandValid : 1;
    unsigned int Format : 4;
} _FPIEEE_VALUE;

typedef struct {
    unsigned int Inexact : 1;
    unsigned int Underflow : 1;
    unsigned int Overflow : 1;
    unsigned int ZeroDivide : 1;
    unsigned int InvalidOperation : 1;
} _FPIEEE_EXCEPTION_FLAGS;

typedef struct {
    unsigned int RoundingMode : 2;
    unsigned int Precision : 3;
    unsigned int Operation :12;
    _FPIEEE_EXCEPTION_FLAGS Cause;
    _FPIEEE_EXCEPTION_FLAGS Enable;
    _FPIEEE_EXCEPTION_FLAGS Status;
    _FPIEEE_VALUE Operand1;
    _FPIEEE_VALUE Operand2;
    _FPIEEE_VALUE Result;
} _FPIEEE_RECORD;

typedef struct _EXCEPTION_POINTERS *PEXCEPTION_POINTERS;

int _fpieee_flt(unsigned long exc_code, PEXCEPTION_POINTERS p, int handler(_FPIEEE_RECORD *));

// Non-ANSI names for compatibility
#define DBL_RADIX        _DBL_RADIX
#define DBL_ROUNDS       _DBL_ROUNDS
#define LDBL_RADIX       _LDBL_RADIX
#define LDBL_ROUNDS      _LDBL_ROUNDS
#define MCW_EM           _MCW_EM
#define EM_INVALID       _EM_INVALID
#define EM_ZERODIVIDE    _EM_ZERODIVIDE
#define EM_OVERFLOW      _EM_OVERFLOW
#define EM_UNDERFLOW     _EM_UNDERFLOW
#define EM_INEXACT       _EM_INEXACT

#if ! defined (_M_CEE)

#define EM_DENORMAL      _EM_DENORMAL
#define SW_DENORMAL      _SW_DENORMAL
#define MCW_IC           _MCW_IC
#define IC_AFFINE        _IC_AFFINE
#define IC_PROJECTIVE    _IC_PROJECTIVE
#define MCW_PC           _MCW_PC
#define PC_24            _PC_24
#define PC_53            _PC_53
#define PC_64            _PC_64

#endif // ! _M_CEE

#define MCW_RC           _MCW_RC
#define RC_CHOP          _RC_CHOP
#define RC_UP            _RC_UP
#define RC_DOWN          _RC_DOWN
#define RC_NEAR          _RC_NEAR
#define CW_DEFAULT       _CW_DEFAULT
#define SW_INVALID       _SW_INVALID
#define SW_ZERODIVIDE    _SW_ZERODIVIDE
#define SW_OVERFLOW      _SW_OVERFLOW
#define SW_UNDERFLOW     _SW_UNDERFLOW
#define SW_INEXACT       _SW_INEXACT
#define SW_UNEMULATED    _SW_UNEMULATED
#define SW_SQRTNEG       _SW_SQRTNEG
#define SW_STACKOVERFLOW   _SW_STACKOVERFLOW
#define SW_STACKUNDERFLOW  _SW_STACKUNDERFLOW
#define FPE_INVALID        _FPE_INVALID
#define FPE_DENORMAL     _FPE_DENORMAL
#define FPE_ZERODIVIDE   _FPE_ZERODIVIDE
#define FPE_OVERFLOW     _FPE_OVERFLOW
#define FPE_UNDERFLOW    _FPE_UNDERFLOW
#define FPE_INEXACT      _FPE_INEXACT
#define FPE_UNEMULATED   _FPE_UNEMULATED
#define FPE_SQRTNEG        _FPE_SQRTNEG
#define FPE_STACKOVERFLOW  _FPE_STACKOVERFLOW
#define FPE_STACKUNDERFLOW _FPE_STACKUNDERFLOW
#define FPE_EXPLICITGEN    _FPE_EXPLICITGEN

double _frnd(double);
double _fsqrt(double);

// defns from MATH.H
// definition of _exception struct - this struct is passed to the matherr
// routine when a floating point exception is detected
struct _exception {
    int type;        /* exception type - see below */
    char *name;        /* name of function where error occured */
    double arg1;        /* first argument to function */
    double arg2;        /* second argument (if any) to function */
    double retval;        /* value to be returned by function */
    } ;

// Non-ANSI name for compatibility
#define exception _exception

// definition of a _complex struct to be used by those who use cabs and
// want type checking on their argument
struct _complex {
    double x,y;    /* real and imaginary parts */
    } ;

// Non-ANSI name for compatibility
#define complex _complex

// definitions of _HUGE and HUGE_VAL - respectively the XENIX and ANSI names
// for a value returned in case of error by a number of the floating point
// math routines
// @CESYSGEN IF !REMOVE_DRAGON
_CRTIMP
// @CESYSGEN ENDIF
extern double _HUGE;
#define HUGE_VAL _HUGE

// MATH.H func defns
int       __cdecl abs(int);
long      __cdecl labs(long);
double    __cdecl acos(double);
double    __cdecl asin(double);
double    __cdecl atan(double);
double    __cdecl atan2(double, double);
double    __cdecl cos(double);
double    __cdecl cosh(double);
double    __cdecl exp(double);
double    __cdecl fabs(double);
double    __cdecl fmod(double, double);
double    __cdecl log(double);
double    __cdecl log10(double);
double    __cdecl pow(double, double);
double    __cdecl sin(double);
double    __cdecl sinh(double);
double    __cdecl sqrt(double);
double    __cdecl tan(double);
double    __cdecl tanh(double);
double    __cdecl _cabs(struct _complex);
double    __cdecl ceil(double);
double    __cdecl floor(double);
double    __cdecl frexp(double, int *);
double    __cdecl _hypot(double, double);
double    __cdecl _j0(double);
double    __cdecl _j1(double);
double    __cdecl _jn(int, double);
double    __cdecl ldexp(double, int);
_CRTIMP int       __cdecl _matherr(struct _exception *);
double    __cdecl modf(double, double *);
double    __cdecl _y0(double);
double    __cdecl _y1(double);
double    __cdecl _yn(int, double);

// MATH.H macros -- oldnames
#define acosl(x)    ((long double)acos((double)(x)))
#define asinl(x)    ((long double)asin((double)(x)))
#define atanl(x)    ((long double)atan((double)(x)))
#define atan2l(x,y) ((long double)atan2((double)(x), (double)(y)))
#define ceill(x)    ((long double)ceil((double)(x)))
#define cosl(x)     ((long double)cos((double)(x)))
#define coshl(x)    ((long double)cosh((double)(x)))
#define expl(x)     ((long double)exp((double)(x)))
#define fabsl(x)    ((long double)fabs((double)(x)))
#define floorl(x)   ((long double)floor((double)(x)))
#define fmodl(x,y)  ((long double)fmod((double)(x), (double)(y)))
#define frexpl(x,y) ((long double)frexp((double)(x), (y)))
#define hypotl(x,y) ((long double)hypot((double)(x), (double)(y)))
#define ldexpl(x,y) ((long double)ldexp((double)(x), (y)))
#define logl(x)     ((long double)log((double)(x)))
#define log10l(x)   ((long double)log10((double)(x)))
#define _matherrl   _matherr
#define modfl(x,y)  ((long double)modf((double)(x), (double *)(y)))
#define powl(x,y)   ((long double)pow((double)(x), (double)(y)))
#define sinl(x)     ((long double)sin((double)(x)))
#define sinhl(x)    ((long double)sinh((double)(x)))
#define sqrtl(x)    ((long double)sqrt((double)(x)))
#define tanl(x)     ((long double)tan((double)(x)))
#define tanhl(x)    ((long double)tanh((double)(x)))

#ifdef MIPS

#define va_start(ap,v) ap  = (va_list)&v + sizeof(v)
#define va_end(list) ( list = (va_list)0 )
#define va_arg(list, mode) ((mode *)(list =\
 (char *) ((((int)list + (__builtin_alignof(mode)<=4?3:7)) &\
 (__builtin_alignof(mode)<=4?-4:-8))+sizeof(mode))))[-1]

#elif defined(PPC)

// PPC uses 8-byte alignment of 8-byte quantities
#define	_ALIGNIT(ap,t) 	((((int)(ap))+(sizeof(t)<8?3:7)) & (sizeof(t)<8?~3:~7))

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap = (char *) (_ALIGNIT(ap, t) + _INTSIZEOF(t))) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

#elif defined (_M_CEE)

extern void __cdecl   __va_start(va_list*, ...);
extern void* __cdecl  __va_arg(va_list*, ...);
extern void __cdecl   __va_end(va_list*);

#define va_start(ap,v)  (__va_start(&ap, &v, sizeof(v), __builtin_alignof(v), &v))
#define va_arg(ap,t)    (*((t*)__va_arg(&ap, sizeof(t), __builtin_alignof(t), (t*)0)))
#define va_end(ap)      (__va_end(&ap))

#else

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

#endif

// Processor-dependent setjmp defns
#ifdef x86

#define setjmp    _setjmp
#define _JBLEN    16

#elif defined(SHx) || defined(MIPS)

#define setjmp        _setjmp
#define _JBLEN        32

#elif defined(PPC)

#define setjmp		  _setjmp
#define _JBLEN        64

#elif defined(ARM)

#define setjmp		  _setjmp
#define _JBLEN        11

#elif defined(_M_CEE)

#define setjmp		  _setjmp
#define _JBLEN        64

#endif

// SETJMP: define the buffer type for holding the state information
typedef  int  jmp_buf[_JBLEN];

// SETJMP: function prototypes
int __cdecl _setjmp(jmp_buf);
void __cdecl longjmp(jmp_buf, int);

#ifdef __cplusplus
}
#endif

#endif    /* _INC_STDLIB */

