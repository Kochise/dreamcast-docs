/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  extmath.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_EXTMATH_H
#define MSIPL_EXTMATH_H

#include <mcompile.h>

#include <cstdio>     // hh 971220 fixed MOD_C_INCLUDE
#include <cassert>    // hh 971220 fixed MOD_C_INCLUDE
#include <cmath>      // hh 971220 fixed MOD_C_INCLUDE  // hh 980210 moved out of extern "C"

#ifdef MSIPL_USE_EXTERNAL_MATHLIB
extern "C" {
#endif

#ifdef MSIPL_USE_EXTERNAL_MATHLIB
}
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifndef _No_Floating_Point

MSIPL_STD_BEGIN
 
//
// For reporting errors
//
void  __msipl_report_error (const char* s);

//
// Extended math Library
//
#ifndef MSIPL_USE_EXTERNAL_MATHLIB

float __msipl_sin  (float);
float __msipl_cos  (float);
float __msipl_tan  (float);
float __msipl_exp  (float);
float __msipl_log  (float);
float __msipl_sqrt (float);
float __msipl_asin (float);
float __msipl_acos (float);
float __msipl_sinh (float);
float __msipl_cosh (float);
float __msipl_tanh (float);
float __msipl_atan (float);
float __msipl_cotan (float);
float __msipl_log10 (float);
float __msipl_pow  (float, float);
float __msipl_atan2 (float, float);

long double __msipl_sin  (long double);
long double __msipl_cos  (long double);
long double __msipl_tan  (long double);
long double __msipl_exp  (long double);
long double __msipl_log  (long double);
long double __msipl_sqrt (long double);
long double __msipl_asin (long double);
long double __msipl_acos (long double);
long double __msipl_sinh (long double);
long double __msipl_cosh (long double);
long double __msipl_tanh (long double);
long double __msipl_atan (long double);
long double __msipl_cotan (long double);
long double __msipl_log10 (long double);
long double __msipl_pow  (long double, long double);
long double __msipl_atan2 (long double, long double);

double __msipl_sin  (double);
double __msipl_cos  (double);
double __msipl_tan  (double);
double __msipl_exp  (double);
double __msipl_log  (double);
double __msipl_sqrt (double);
double __msipl_asin (double);
double __msipl_acos (double);
double __msipl_sinh (double);
double __msipl_cosh (double);
double __msipl_tanh (double);
double __msipl_atan (double);
double __msipl_cotan (double);
double __msipl_log10 (double);
double __msipl_pow  (double, double);
double __msipl_atan2 (double, double);

#else

#define  __msipl_pow    pow
#define  __msipl_sin    sin
#define  __msipl_cos    cos
#define  __msipl_tan    tan
#define  __msipl_exp    exp
#define  __msipl_log    log
#define  __msipl_sqrt   sqrt
#define  __msipl_asin   asin
#define  __msipl_acos   acos
#define  __msipl_sinh   sinh
#define  __msipl_cosh   cosh
#define  __msipl_tanh   tanh
#define  __msipl_atan   atan
#define  __msipl_cotan  cotan
#define  __msipl_log10  log10
#define  __msipl_atan2  atan2

#endif /* MSIPL_USE_EXTERNAL_MATHLIB */

MSIPL_STD_END

#endif // _No_Floating_Point

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_EXTMATH_H */

// hh 971220 fixed MOD_C_INCLUDE
// hh 980210 moved <cmath> out of extern "C"
// hh 980408 wrapped up in #ifndef _No_Floating_Point
