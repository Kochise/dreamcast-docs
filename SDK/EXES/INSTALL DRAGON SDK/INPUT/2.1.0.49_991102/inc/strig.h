// strig.h
// purpose: to override the standard c library sin() and cos() function
// with a version that takes advantage of the sh4

#ifndef _INC_STRIG
#define _INC_STRIG

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SH4
float    __cdecl coss(float);
float    __cdecl sins(float);

/* Map CRT functions to single-precision versions */

#undef sin
#undef cos

#define sin(x) sins(x)
#define cos(x) coss(x)
#endif

#ifdef __cplusplus
}
#endif

#endif // _INC_SFLOAT
