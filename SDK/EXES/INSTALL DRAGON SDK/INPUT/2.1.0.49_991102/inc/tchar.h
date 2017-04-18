/***
*tchar.h - definitions for generic international text functions
*
*       Copyright (c) 1991-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*	This file has been completely revamped to support the full set of CRT-like
*   functionality exported by COREDLL in Birch, and *only* those functions
*
****/

#ifndef _INC_TCHAR
#define _INC_TCHAR

// We require <windef.h> to pull in defns of __TEXT, TCHAR etc from winnt.h
#include <windef.h>
// This CE version of TCHAR.H is a companion to the CE version of STDLIB.H
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

// Basic defn of __TEXT & TEXT already done in winnt.h (reqd by this file)
// Also TCHAR, PTSTR, LPTSTR, LPCTSTR already defined in winnt.h
#define __T(x)      __TEXT(x)
#define _T(x)       __TEXT(x)
typedef LPCTSTR		PCTSTR;

#ifdef  UNICODE
/* ++++++++++++++++++++ UNICODE ++++++++++++++++++++ */

#define _TEOF       WEOF

#define _tmain      wmain

#ifdef UNDER_CE
#	define _tWinMain   WinMain // On CE it's always WinMain
#else
#	define _tWinMain   wWinMain
#endif

/* Formatted i/o */
#define _tprintf    wprintf
#define _ftprintf   fwprintf
#define _stprintf   swprintf
#define _sntprintf  _snwprintf
#define _vtprintf   vwprintf
#define _vftprintf  vfwprintf
#define _vstprintf  vswprintf
#define _vsntprintf _vsnwprintf
#define _tscanf     wscanf
#define _ftscanf    fwscanf
#define _stscanf    swscanf

/* Unformatted i/o */
#define _fgettc     fgetwc
#define _fgetts     fgetws
#define _fputtc     fputwc
#define _fputts     fputws
#define _gettc      getwc
#define _gettchar   getwchar
#define _getts      _getws
#define _puttc      putwc
#define _puttchar   putwchar
#define _putts      _putws
#define _ungettc    ungetwc

// Stdio functions
#define _tfopen     _wfopen

/* String conversion functions */
#define _tcstod     wcstod
#define _tcstol     wcstol
#define _tcstoul    wcstoul

#define _itot       _itow
#define _ltot       _ltow
#define _ultot      _ultow
#define _ttoi       _wtoi
#define _ttol       _wtol
#define _ttoi64     _wtoi64

/* String functions */
#define _tcscat     wcscat
#define _tcschr     wcschr
#define _tcscmp     wcscmp
#define _tcscpy     wcscpy
#define _tcscspn    wcscspn
#define _tcslen     wcslen
#define _tcsclen    wcslen

#define _tcsncat    wcsncat
#define _tcsnccat   wcsncat
#define _tcsnccmp   wcsncmp
#define _tcsncmp    wcsncmp
#define _tcsncpy    wcsncpy
#define _tcsnccpy   wcsncpy
#define _tcspbrk    wcspbrk
#define _tcsrchr    wcsrchr
#define _tcsspn     wcsspn
#define _tcsstr     wcsstr
#define _tcstok     wcstok
#define _tcsdup     _wcsdup
#define _tcsicmp    _wcsicmp
#define _tcsncicmp  _wcsnicmp
#define _tcsnicmp   _wcsnicmp
#define _tcsnset    _wcsnset
#define _tcsncset   _wcsnset
#define _tcsrev     _wcsrev
#define _tcsset     _wcsset

#define _tcslwr     _wcslwr
#define _tcsupr     _wcsupr

// ctype functions
#define _istalpha   iswalpha
#define _istupper   iswupper
#define _istlower   iswlower
#define _istdigit   iswdigit
#define _istxdigit  iswxdigit
#define _istspace   iswspace
#define _istpunct   iswpunct
#define _istalnum   iswalnum
#define _istprint   iswprint
#define _istgraph   iswgraph
#define _istcntrl   iswcntrl
#define _istascii   iswascii

#define _totupper   towupper
#define _totlower   towlower

#define _istlegal(_c)   	(1)
#define _istlead(_c)    	(0)
#define _istleadbyte(_c)    (0)

#else   /* ndef UNICODE */

/* ++++++++++++++++++++ SBCS (MBCS in Not supported) ++++++++++++++++++++ */

#define _TEOF       EOF

/* Program */
#define _tmain      main
#define _tWinMain   WinMain


/* Formatted i/o */
#define _tprintf    printf
#define _ftprintf   fprintf
#define _stprintf   sprintf
#define _sntprintf  _snprintf
#define _vtprintf   vprintf
#define _vftprintf  vfprintf
#define _vstprintf  vsprintf
#define _vsntprintf _vsnprintf
#define _tscanf     scanf
#define _ftscanf    fscanf
#define _stscanf    sscanf

/* Unformatted i/o */
#define _fgettc     fgetc
#define _fgetts     fgets
#define _fputtc     fputc
#define _fputts     fputs
#define _gettc      getc
#define _gettchar   getchar
#define _getts      gets
#define _puttc      putc
#define _puttchar   putchar
#define _putts      puts
#define _ungettc    ungetc

// Stdio functions
#define _tfopen     _wfopen

// String conversion functions
#ifndef UNDER_CE
// NYI in SBCS for CE
#define _tcstod     strtod
#define _tcstol     strtol
#define _tcstoul    strtoul
#endif

#define _itot       _itoa
#define _ltot       _ltoa
#define _ultot      _ultoa
#define _ttoi       atoi
#define _ttol       atol

#ifndef UNDER_CE
#define _ttoi64   atoi64 //NYI in CE in SBCS
#endif

/* String functions */
#define _tcscat     strcat
#define _tcschr     strchr
#define _tcscmp     strcmp
#define _tcscpy     strcpy
#define _tcscspn    strcspn
#define _tcslen     strlen
#define _tcsclen    strlen

#define _tcsncat    strncat
#define _tcsnccat   strncat
#define _tcsnccmp   strncmp
#define _tcsncmp    strncmp
#define _tcsncpy    strncpy
#define _tcsnccpy   strncpy

#ifndef UNDER_CE
// NYI in CE in SBCS
#define _tcspbrk    strpbrk
#define _tcsrchr    strrchr
#define _tcsspn     strspn
#endif

#define _tcsstr     strstr
#define _tcstok     strtok

#ifndef UNDER_CE
// NYI in CE in SBCS
#define _tcsdup     _strdup
#define _tcsicmp    _stricmp
#define _tcsncicmp  _strnicmp
#define _tcsnicmp   _strnicmp
#define _tcsnset    _strnset
#define _tcsncset   _strnset
#define _tcsrev     _strrev
#define _tcsset     _strset
#define _tcslwr     _strlwr
#define _tcsupr     _strupr
#endif

// ctype functions
#ifndef UNDER_CE
// NYI in CE in SBCS
#define _istalpha   isalpha
#define _istupper   isupper
#define _istlower   islower
#define _istdigit   isdigit
#define _istxdigit  isxdigit
#define _istspace   isspace
#define _istpunct   ispunct
#define _istalnum   isalnum
#define _istprint   isprint
#define _istgraph   isgraph
#define _istcntrl   iscntrl
#define _istascii   isascii
#define _totupper   toupper
#define _totlower   tolower
#endif

#define _istlegal(_c)   	(1)
#define _istlead(_c)    	(0)
#define _istleadbyte(_c)    (0)

#endif  /* UNICODE */

#ifdef __cplusplus
}
#endif

#endif  /* _INC_TCHAR */

