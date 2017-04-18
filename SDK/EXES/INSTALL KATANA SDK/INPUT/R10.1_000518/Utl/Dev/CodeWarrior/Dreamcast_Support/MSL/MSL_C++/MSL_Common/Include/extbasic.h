/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  extbasic.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef  MSIPL_MATHBASIC_H
#define  MSIPL_MATHBASIC_H 

#include <mcompile.h>

#include <cfloat>    // hh 971220 fixed MOD_C_INCLUDE

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifndef _No_Floating_Point

MSIPL_STD_BEGIN
 
//
// constants for extended math libary
//
const long double MODENA_M_PI = 3.14159265358979323846L;
const long double MODENA_R_PI = 0.31830988618379067154L;

int __msi_fabs (int);

float __msi_adx (float X, int N);
float __msi_aint (float X);
float __msi_fabs (float);
float __msi_float (int N);
float __msi_setxp (float X, int N);
float __msi_getexpbigx (float);
float __msi_getymax (float);
float __msi_getexpsmlx (float);
 
double __msi_adx (double X, int N);
double __msi_aint (double X);
double __msi_fabs (double);
double __msi_double (int N);
double __msi_setxp (double X, int N);
double __msi_getexpbigx (double);
double __msi_getymax (double);
double __msi_getexpsmlx (double);

long double __msi_adx (long double X, int N);
long double __msi_aint (long double X);
long double __msi_fabs (long double);
long double __msi_longdouble (int N);
long double __msi_setxp (long double X, int N);
long double __msi_getexpbigx (long double);
long double __msi_getymax (long double);
long double __msi_getexpsmlx (long double);

int __msi_intrnd (float X);
int __msi_intrnd (double X);
int __msi_intrnd (long double X);

int __msi_intxp (float X);
int __msi_intxp (double X);
int __msi_intxp (long double X);

int __msi_int (float X);
int __msi_int (long double X);
int __msi_int (double X);

int __msi_noiter (float);
int __msi_noiter (double);
int __msi_noiter (long double);

int __msi_nobits (float);
int __msi_nobits (double);
int __msi_nobits (long double);

int __msi_neg (int);

MSIPL_STD_END

#endif // _No_Floating_Point

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_EXTBASIC_H */

// hh 971220 fixed MOD_C_INCLUDE
// hh 980408 wrapped up in #ifndef _No_Floating_Point
