/***
*shintr.h - definitions and declarations for SH intrinisc library
*
*Purpose:
*       This file contains constant definitions and external subroutine
*       declarations for the SH intrinisc subroutine library.
*
****/

#ifndef _INC_SHINTR
#define _INC_SHINTR

#if defined(SH4)

#ifdef __cplusplus
extern "C" {
#endif

float * _Xform4dV(float *retval, float *vector, float *matrix);
float * _Xform3dV(float *retval, float *vector, float *matrix);

float * _XDXform4dV(float *src, float *dst);
float * _XDXform3dV(float *src, float *dst);

float  _Dot4dV(float *vector1, float *vector2);
float  _Dot3dVW0(float *vector1, float *vector2);
float  _Dot3dVW1(float *vector1, float *vector2);

float * _Multiply4dM(float *retval, float *m4x4m1, float *m4x4m2);
void _XDMultMatrix(float *matrix);

float * _LoadMatrix(float *matrix);
float * _SaveMatrix(float *matrix);

float fabsf(float input);

float sqrtf(float input);

float __fmac(float i, float m, float n);

void __prefetch(unsigned long *addr);
void __movca(unsigned long value, unsigned long *addr);

float _Convolve(int nelement, float *pstart, float *pend, 
                float *pdata, float *pfilter);

#ifdef __cplusplus
}
#endif

#endif //defined(SH4)

#endif //_INC_SHINTR




