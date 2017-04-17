/***
*shsgintr.h - definitions and declarations for SH intrinisc library
*
*Purpose:
*       This file contains constant definitions and external subroutine
*       declarations for the SH intrinisc subroutine library.
*
****/

#ifndef _INC_SHSGINTR
#define _INC_SHSGINTR

#if defined(SH4)

#ifdef __cplusplus
extern "C" {
#endif


void _SinCosA(float * sin_apprx, float * cos_apprx, float input);
void __fsca(float *sin_apprx, float *cos_apprx, int input);

float _InvSqrtA(float input);


#ifdef __cplusplus
}
#endif

#endif //defined(SH4)

#endif //_INC_SHSGINTR
