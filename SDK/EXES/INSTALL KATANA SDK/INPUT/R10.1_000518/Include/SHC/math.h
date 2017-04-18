/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = math :                                               */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _MATH_SHC
#define _MATH_SHC

#ifndef ERANGE
#define ERANGE  1100
#endif

#ifndef EDOM
#define EDOM    1101
#endif

#ifndef ENUM
#define ENUM    1208
#endif

extern volatile int _errno;
extern const double _HUGE_VAL;
#define HUGE_VAL  _HUGE_VAL

#ifdef __cplusplus
extern "C" {
#endif
extern double frexp(double, int *);
extern double ldexp(double, int );
extern double modf(double, double *);
extern double ceil(double);

#ifdef _SH4
#ifdef _FPS
#define  fabs  _builtin_fabsf
#else
#define  fabs  _builtin_fabs
#endif
#else
#if defined(_SH2E)|defined(_SH3E)
#ifdef _FLT
#define  fabs  _builtin_fabsf
#else
extern double fabs(double);
#endif
#else
extern double fabs(double);
#endif
#endif

extern double floor(double);
extern double fmod(double, double);

extern double acos(double);
extern double asin(double);
extern double atan(double);
extern double atan2(double,double);
extern double cos(double);
extern double sin(double);
extern double tan(double);
extern double cosh(double);
extern double tanh(double);
extern double sinh(double);
extern double exp(double);
extern double log(double);
extern double log10(double);
extern double pow(double,double);

#ifdef _COMPLEX_
extern double sqrt(double);
#else
#ifdef _SH4
#ifdef _FPS
#define  sqrt  _builtin_sqrtf
#else
#define  sqrt  _builtin_sqrt
#endif
#else
#ifdef _SH3E
#ifdef _FLT
#define  sqrt  _builtin_sqrtf
#else
extern double sqrt(double);
#endif
#else
extern double sqrt(double);
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif