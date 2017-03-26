/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.1                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = mathf                                                */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _MATHF_SHC
#define _MATHF_SHC

#ifdef __cplusplus
extern "C" {
#endif
extern float frexpf(float, int *);
extern float ldexpf(float, int);
extern float modff(float, float *);
extern float ceilf(float);
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)
#ifdef _FPD
#define  fabsf  _builtin_fabs
#else
#define  fabsf  _builtin_fabsf
#endif
#else
extern float fabsf(float);
#endif
extern float floorf(float);
extern float fmodf(float, float);
extern float acosf(float);
extern float asinf(float);
extern float atanf(float);
extern float atan2f(float,float);
extern float cosf(float);
extern float sinf(float);
extern float tanf(float);
extern float coshf(float);
extern float tanhf(float);
extern float sinhf(float);
extern float expf(float);
extern float logf(float);
extern float log10f(float);
extern float powf(float,float);
#if defined(_SH3E)|defined(_SH4)
#ifdef _FPD
#define  sqrtf  _builtin_sqrt
#else
#define  sqrtf  _builtin_sqrtf
#endif
#else
extern float sqrtf(float);
#endif
#ifdef __cplusplus
}
#endif

#endif