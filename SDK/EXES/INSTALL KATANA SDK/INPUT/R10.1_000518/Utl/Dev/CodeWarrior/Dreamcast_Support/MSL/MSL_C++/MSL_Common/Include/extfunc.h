/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  extfunc.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_EXTFUNC_H
#define MSIPL_EXTFUNC_H

#include <mcompile.h>

#include <functional>    // hh 971220 fixed MOD_INCLUDE
#include <extmath.h>     // hh 971220 fixed MOD_INCLUDE

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

//
// Extended functors provided for
// class valarray implementation 
//
template <class T>
struct __msipl_not : unary_function<T, T> {
    T operator () (const T& x) const { return !x; }
};

template <class T>
struct __msipl_complement : unary_function<T, T> {
    T operator () (const T& x) const { return ~x; }
};

template <class T>
struct __msipl_bitwise_and : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x & y; }
};

template <class T>
struct __msipl_bitwise_or : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x | y; }
};

template <class T>
struct __msipl_and : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x && y; }
};

template <class T>
struct __msipl_or : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x || y; }
};

template <class T>
struct __msipl_caret : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x ^ y; }
};

template <class T>
struct __msipl_shift_left : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x << y; }
};

template <class T>
struct __msipl_shift_right : binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const { return x >> y; }
};

template <class T>
struct __msipl_absolute: unary_function<T, T> {
    // Is this overloaded ??
    T operator () (const T& x) const { return abs (x); }  // hh 980206 changed fabs to abs
};

#ifndef _No_Floating_Point

template <class T>
struct __msipl_sine: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_sin (x); }
};

template <class T>
struct __msipl_cosine: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_cos (x); }
};

template <class T>
struct __msipl_tangent: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_tan (x); }
};

template <class T>
struct __msipl_arcsin: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_asin (x); }
};

template <class T>
struct __msipl_arccos: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_acos (x); }
};

template <class T>
struct __msipl_arctan: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_atan (x); }
};

template <class T>
struct __msipl_logarithm: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_log (x); }
};

template <class T>
struct __msipl_logarithm10: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_log10 (x); }
};

template <class T>
struct __msipl_sqroot: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_sqrt ((double)x); }
};

null_template
struct __msipl_sqroot<float> : unary_function<float, float> {
    float operator () (const float& x) const { return __msipl_sqrt (x); }
};

null_template
struct __msipl_sqroot<long double> 
: unary_function<long double, long double> {
    long double operator () (const long double& x) const
    { return __msipl_sqrt (x); }
};

template <class T>
struct __msipl_exponential: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_exp (x); }
};

template <class T>
struct __msipl_arctan2: binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const
    { return __msipl_atan2 (x, y); }
};

template <class T>
struct __msipl_power: binary_function<T, T, T> {
    T operator () (const T& x, const T& y) const
    { return __msipl_pow ((double)x, (double)y); }
};

null_template
struct __msipl_power<int> : binary_function<int, int, int> {
    int operator () (const int& x, const int& y) const
    { 
         float f = __msipl_pow ((float)x, (float)y);
         int i = (int)f;
         return i;
     }
};

null_template
struct __msipl_power<float> : binary_function<float, float, float> {
    float operator () (const float& x, const float& y) const
    { return __msipl_pow (x,y); }
};

null_template
struct __msipl_power<long double>
: binary_function<long double, long double, long double> {
    long double operator () (const long double& x, const long double& y) const
    { return __msipl_pow (x,y); }
};

template <class T>
struct __msipl_sineh: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_sinh (x); }
};

template <class T>
struct __msipl_cosineh: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_cosh (x); }
};

template <class T>
struct __msipl_tangenth: unary_function<T, T> {
    T operator () (const T& x) const { return __msipl_tanh (x); }
};

#endif // _No_Floating_Point

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_EXTFUNC_H */

// hh 971220 fixed MOD_INCLUDE
// hh 980206 changed fabs to abs
// hh 980408 wrapped in #ifndef _No_Floating_Point
