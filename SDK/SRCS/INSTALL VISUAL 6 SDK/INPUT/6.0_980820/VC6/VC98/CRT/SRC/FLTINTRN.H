/***
*fltintrn.h - contains declarations of internal floating point types,
*             routines and variables
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Declares floating point types, routines and variables used
*       internally by the C run-time.
*
*       [Internal]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_FLTINTRN
#define _INC_FLTINTRN

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <cruntime.h>


/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef CRTDLL
#define _CRTIMP __declspec(dllexport)
#else  /* CRTDLL */
#ifdef _DLL
#define _CRTIMP __declspec(dllimport)
#else  /* _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */


/* Define __cdecl for non-Microsoft compilers */

#if (!defined (_MSC_VER) && !defined (__cdecl))
#define __cdecl
#endif  /* (!defined (_MSC_VER) && !defined (__cdecl)) */

/*
 * For MS C for the x86 family, disable the annoying "long double is the
 * same precision as double" warning
 */

#ifdef _M_IX86
#pragma warning(disable:4069)
#endif  /* _M_IX86 */

/*
 * structs used to fool the compiler into not generating floating point
 * instructions when copying and pushing [long] double values
 */

#ifndef DOUBLE

typedef struct {
        double x;
} DOUBLE;

#endif  /* DOUBLE */

#ifndef LONGDOUBLE

typedef struct {
#if defined (_M_MRX000) || defined (_M_ALPHA) || defined (_M_PPC) || defined (_M_MPPC)
        /*
         * No long double type for MIPS, ALPHA, PPC. or PowerMac
         */
        double x;
#else  /* defined (_M_MRX000) || defined (_M_ALPHA) || defined (_M_PPC) || defined (_M_MPPC) */
        /*
         * Assume there is a long double type
         */
        long double x;
#endif  /* defined (_M_MRX000) || defined (_M_ALPHA) || defined (_M_PPC) || defined (_M_MPPC) */
} LONGDOUBLE;

#endif  /* LONGDOUBLE */

/*
 * typedef for _fltout
 */

typedef struct _strflt
{
        int sign;             /* zero if positive otherwise negative */
        int decpt;            /* exponent of floating point number */
        int flag;             /* zero if okay otherwise IEEE overflow */
        char *mantissa;       /* pointer to mantissa in string form */
}
        *STRFLT;


/*
 * typedef for _fltin
 */

typedef struct _flt
{
        int flags;
        int nbytes;          /* number of characters read */
        long lval;
        double dval;         /* the returned floating point number */
}
        *FLT;


#ifdef _MAC
/*
 * typedef for _fltinl
 */

typedef struct _fltl
{
        int flags;
        int nbytes;          /* number of characters read */
        long lval;
        long double ldval;           /* the returned floating point number */
}
        *FLTL;
#endif  /* _MAC */

/* floating point conversion routines, keep in sync with mrt32\include\convert.h */

char *_cftoe(double *, char *, int, int);
char *_cftof(double *, char *, int);
void __cdecl _fptostr(char *, int, STRFLT);

#ifdef _MT

STRFLT  __cdecl _fltout2( double, STRFLT, char * );
FLT     __cdecl _fltin2( FLT , const char *, int, int, int );

#else  /* _MT */

STRFLT  __cdecl _fltout( double );
FLT     __cdecl _fltin( const char *, int, int, int );
#ifdef _MAC
FLTL    __cdecl _fltinl( const char *, int, int, int );
#endif  /* _MAC */

#endif  /* _MT */


/*
 * table of pointers to floating point helper routines
 *
 * We can't specify the prototypes for the entries of the table accurately,
 * since different functions in the table have different arglists.
 * So we declare the functions to take and return void (which is the
 * correct prototype for _fptrap(), which is what the entries are all
 * initialized to if no floating point is loaded) and cast appropriately
 * on every usage.
 */

typedef void (* PFV)(void);
extern PFV _cfltcvt_tab[6];

typedef void (* PF0)(DOUBLE*, char*, int, int, int);
#define _cfltcvt(a,b,c,d,e) (*((PF0)_cfltcvt_tab[0]))(a,b,c,d,e)

typedef void (* PF1)(char*);
#define _cropzeros(a)       (*((PF1)_cfltcvt_tab[1]))(a)

typedef void (* PF2)(int, char*, char*);
#define _fassign(a,b,c)     (*((PF2)_cfltcvt_tab[2]))(a,b,c)

typedef void (* PF3)(char*);
#define _forcdecpt(a)       (*((PF3)_cfltcvt_tab[3]))(a)

typedef int (* PF4)(DOUBLE*);
#define _positive(a)        (*((PF4)_cfltcvt_tab[4]))(a)

typedef void (* PF5)(LONGDOUBLE*, char*, int, int, int);
#define _cldcvt(a,b,c,d,e)  (*((PF5)_cfltcvt_tab[5]))(a,b,c,d,e)


#ifdef _M_IX86
#pragma warning(default:4069)
#endif  /* _M_IX86 */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_FLTINTRN */
