/**********************************************
*     Microsoft System Management Server      *
*     Copyright(c) Microsoft Corp., 1994      *
**********************************************/

/* DBCS definitions
//    dbcsstr.h - Definistions about DBCS
//
// Purpose:
//    contains DBCS unique table and
//    definition of checking for DBCS character.
//
// Revision History:
//    02/14/94    MSKK Tetsua Initial version
//    03/22/94    MSKK Atsusk
//                     change strupr to _strupr, strlwr to _strlwr, and so on.
*/

#ifndef _DBCSSTR_INCLUDED_
#define _DBCSSTR_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

extern  unsigned char _DBCSLeadByteTable[];

#ifdef __TURBOC__
  #if (__TURBOC__ < 0x300)
    #define _OS2
    #define _far far
  #endif
#endif

#if defined(_M_I86MM) || defined(_M_I86LM)    /* for MSC */ \
 || defined(__MEDIUM__) || defined(__LARGE__) /* for TC/BC */   /* far code */
#define __FAR__ _far
#else
#define __FAR__
#endif

int __FAR__ WHATISCHAR( const char __FAR__ *, const unsigned int );
int __FAR__ _GetSystemDrive( void );


char __FAR__ * __FAR__ __mbsncpy( char __FAR__ *, const char __FAR__ *, int );
char __FAR__ * __FAR__ __mbsncat( char __FAR__ *, const char __FAR__ *, int );
int __FAR__ __mbsicmp( const char __FAR__ *, const char __FAR__ * );
int __FAR__ __mbsnicmp( const char __FAR__ *, const char __FAR__ *, int );


#define ISDBCS(c) ((_DBCSLeadByteTable)[(unsigned char) (c)])
#ifndef _CHAR_DBCS_INCLUDED_
#define _CHAR_DBCS_INCLUDED_
#define CHAR_SBCS 0
#define CHAR_DBCS_LEAD  1
#define CHAR_DBCS_TAIL  2
#endif  /* _CHAR_DBCS_INCLUDED_ */

//JAPAN start
/* for Single Byte Japanese Character */
#define ISKANA(c) (0x0A0 <= (c) && 0x0DF >= (c))
//JAPAN end


/*
// The following string functions should use
// multi-bytes string functions.
// So, we should defined the followings.
*/

#if defined(_NTWIN) || defined(_NTCONSOLE) || defined(WIN32)
#include  <mbstring.h>
#define strstr(s1,s2) (char *)_mbsstr((unsigned char *)s1, (unsigned char *)s2)
#define strchr(s1,i1) (char *)_mbschr((unsigned char *)s1, i1)
#define strtok(s1,s2) (char *)_mbstok((unsigned char *)s1, (unsigned char *)s2)
#define strcspn(s1,s2)  _mbscspn((unsigned char *)s1, (unsigned char *)s2)
#define strpbrk(s1,s2)  (char *)_mbspbrk((unsigned char *)s1, (unsigned char *)s2)
#define strspn(s1,s2) _mbsspn((unsigned char *)s1, (unsigned char *)s2)
#define _strupr(s1) (char *)_mbsupr((unsigned char *)s1)
#define _strlwr(s1) (char *)_mbslwr((unsigned char *)s1)
#define _strrev(s1) (char *)_mbsrev((unsigned char *)s1)
#define _stricmp(s1,s2) _mbsicmp((unsigned char *)s1, (unsigned char *)s2)
#define _strcmpi(s1,s2) _mbsicmp((unsigned char *)s1, (unsigned char *)s2)
#define strrchr(s1,i1)  (char *)_mbsrchr((unsigned char *)s1, i1)
/*
#define _strnicmp _mbsnicmp
#define strlen  _mbslen
#define strcat  _mbscat
#define strcpy  _mbscpy
#define strcmp  _mbscmp
#define _strset _mbsset
#define strncat _mbsncat
#define strncpy _mbsncpy
#define strncmp _mbsncmp
#define _strnset  _mbsnset
*/
#elif (defined(_DOS) || defined(_WINDOWS)) && !defined(_OS2)
#include  <mbstring.h>
#define strstr  _mbsstr
#define strchr  _mbschr
#define strtok  _mbstok
#define strcspn _mbscspn
#define strpbrk _mbspbrk
#define strspn  _mbsspn
#define _strupr _mbsupr
#define _strlwr _mbslwr
#define _strrev _mbsrev
#define _stricmp  _mbsicmp
#define _strcmpi  _mbsicmp
#define strrchr _mbsrchr
#define _fstrstr  _fmbsstr
#define _fstrchr  _fmbschr
#define _fstrtok  _fmbstok
#define _fstrupr _fmbsupr
#define _fstrlwr _fmbslwr
#define _fstricmp  _fmbsicmp
#define _fstrcmpi  _fmbsicmp
#define _fstrrchr _fmbsrchr
/*
#define _strnicmp _mbsnicmp
#define strlen  _mbslen
#define strcat  _mbscat
#define strcpy  _mbscpy
#define strcmp  _mbscmp
#define _strset _mbsset
#define strncat _mbsncat
#define strncpy _mbsncpy
#define strncmp _mbsncmp
#define _strnset  _mbsnset
*/
#elif defined(_OS2)
#include  <jstring.h>
#define strstr
#define strchr  jstrchr
#define strtok  jstrtok
#define strcspn
#define strpbrk
#define strspn
#define _strupr
#define _strlwr
#define _strrev
#define stricmp __mbsicmp
#define strcmpi __mbsicmp
#define _strnicmp
#define strrchr
/*
#define strlen  _mbslen
#define strcat  _mbscat
#define strcpy  _mbscpy
#define strcmp  _mbscmp
#define _strset _mbsset
#define strncat _mbsncat
#define strncpy _mbsncpy
#define strncmp _mbsncmp
#define _strnset  _mbsnset
*/
#else
#error not defined _DOS, _OS2, or _NTWIN
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _DBCSSTR_INCLUDED_ */

/*** End of 'dbcsstr.h' ***/
