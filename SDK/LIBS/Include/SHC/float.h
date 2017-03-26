/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = float :                                              */
/*   FUNC = limit about float type  and double type ;            */
/*                                                               */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _FLOAT_SHC
#define _FLOAT_SHC

extern const float       _FLT_MAX_VAL;
extern const float       _FLT_MIN_VAL;
extern const double      _DBL_MAX_VAL;
extern const double      _DBL_MIN_VAL;
extern const long double _LDBL_MAX_VAL;
extern const long double _LDBL_MIN_VAL;

#ifndef _FPD

#define FLT_RADIX             2
#if defined(_SH2E)|defined(_SH3E)|(defined(_SH4)&!defined(_RON))
#define FLT_ROUNDS            0
#define FLT_GUARD             0
#else
#define FLT_ROUNDS            1
#define FLT_GUARD             1
#endif
#define FLT_NORMALIZE         1
#define FLT_MAX               _FLT_MAX_VAL
#define FLT_MIN               _FLT_MIN_VAL
#define FLT_MAX_EXP         127
#if defined(_SH2E)|defined(_SH3E)|(defined(_SH4)&!defined(_DON))
#define FLT_MIN_EXP       (-126)
#else
#define FLT_MIN_EXP       (-149)
#endif
#define FLT_MAX_10_EXP       38
#if defined(_SH2E)|defined(_SH3E)|(defined(_SH4)&!defined(_DON))
#define FLT_MIN_10_EXP     (-38)
#else
#define FLT_MIN_10_EXP     (-44)
#endif
#define FLT_DIG               6
#define FLT_MANT_DIG         24
#define FLT_EXP_DIG           8
#if defined(_SH2E)|defined(_SH3E)|(defined(_SH4)&!defined(_RON))
#define FLT_POS_EPS 1.1920928955078125e-7f
#if defined(_DON)
#define FLT_NEG_EPS 1.4012984643248171e-45f
#else
#define FLT_NEG_EPS 1.1754943508222876e-38f
#endif
#else
#define FLT_POS_EPS 5.9604648328104311e-8f
#define FLT_NEG_EPS 2.9802324164052156e-8f
#endif
#define FLT_POS_EPS_EXP    (-23)
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)
#define FLT_NEG_EPS_EXP    (-126)
#else
#define FLT_NEG_EPS_EXP    (-24)
#endif

#endif


#if defined(_FLT)|defined(_FPS)

#define DBL_RADIX           FLT_RADIX
#define DBL_ROUNDS          FLT_ROUNDS
#define DBL_GUARD           FLT_GUARD
#define DBL_NORMALIZE       FLT_NORMALIZE
#define DBL_MAX            _FLT_MAX_VAL
#define DBL_MIN            _FLT_MIN_VAL
#define DBL_MAX_EXP         FLT_MAX_EXP
#define DBL_MIN_EXP         FLT_MIN_EXP
#define DBL_MAX_10_EXP      FLT_MAX_10_EXP
#define DBL_MIN_10_EXP      FLT_MIN_10_EXP
#define DBL_DIG             FLT_DIG
#define DBL_MANT_DIG        FLT_MANT_DIG
#define DBL_EXP_DIG         FLT_EXP_DIG
#define DBL_POS_EPS         FLT_POS_EPS
#define DBL_NEG_EPS         FLT_NEG_EPS
#define DBL_POS_EPS_EXP     FLT_POS_EPS_EXP
#define DBL_NEG_EPS_EXP     FLT_NEG_EPS_EXP

#else

#define DBL_RADIX             2
#if defined(_SH4)&!defined(_RON)
#define DBL_ROUNDS            0
#define DBL_GUARD             0
#else
#define DBL_ROUNDS            1
#define DBL_GUARD             1
#endif
#define DBL_NORMALIZE         1
#define DBL_MAX               _DBL_MAX_VAL
#define DBL_MIN               _DBL_MIN_VAL
#define DBL_MAX_EXP        1023
#if defined(_SH4)&!defined(_DON)
#define DBL_MIN_EXP      (-1022)
#else
#define DBL_MIN_EXP      (-1074)
#endif
#define DBL_MAX_10_EXP      308
#if defined(_SH4)&!defined(_DON)
#define DBL_MIN_10_EXP    (-308)
#else
#define DBL_MIN_10_EXP    (-323)
#endif
#define DBL_DIG              15
#define DBL_MANT_DIG         53
#define DBL_EXP_DIG          11
#if defined(_SH4)&!defined(_RON)
#define DBL_POS_EPS 2.2204460492503131e-16
#if defined(_DON)
#define DBL_NEG_EPS 4.9406564584124655e-324
#else
#define DBL_NEG_EPS 2.2250738585072014e-308
#endif
#else
#define DBL_POS_EPS 1.1102230246251567e-16
#define DBL_NEG_EPS 5.5511151231257834e-17
#endif
#define DBL_POS_EPS_EXP    (-52)
#ifdef _SH4
#ifdef _RON
#define DBL_NEG_EPS_EXP    (-53)
#else
#ifdef _DON
#define DBL_NEG_EPS_EXP    (-1023)
#else
#define DBL_NEG_EPS_EXP    (-1022)
#endif
#endif
#else
#define DBL_NEG_EPS_EXP    (-53)
#endif

#ifdef _FPD
#define FLT_RADIX           DBL_RADIX
#define FLT_ROUNDS          DBL_ROUNDS
#define FLT_GUARD           DBL_GUARD
#define FLT_NORMALIZE       DBL_NORMALIZE
#define FLT_MAX            _DBL_MAX_VAL
#define FLT_MIN            _DBL_MIN_VAL
#define FLT_MAX_EXP         DBL_MAX_EXP
#define FLT_MIN_EXP         DBL_MIN_EXP
#define FLT_MAX_10_EXP      DBL_MAX_10_EXP
#define FLT_MIN_10_EXP      DBL_MIN_10_EXP
#define FLT_DIG             DBL_DIG
#define FLT_MANT_DIG        DBL_MANT_DIG
#define FLT_EXP_DIG         DBL_EXP_DIG
#define FLT_POS_EPS         DBL_POS_EPS
#define FLT_NEG_EPS         DBL_NEG_EPS
#define FLT_POS_EPS_EXP     DBL_POS_EPS_EXP
#define FLT_NEG_EPS_EXP     DBL_NEG_EPS_EXP
#endif

#endif


#ifdef _FLT
#define LDBL_RADIX             2
#define LDBL_ROUNDS            1
#define LDBL_GUARD             1
#define LDBL_NORMALIZE         1
#define LDBL_MAX               _LDBL_MAX_VAL
#define LDBL_MIN               _LDBL_MIN_VAL
#define LDBL_MAX_EXP        1023
#define LDBL_MIN_EXP      (-1074)
#define LDBL_MAX_10_EXP      308
#define LDBL_MIN_10_EXP    (-323)
#define LDBL_DIG              15
#define LDBL_MANT_DIG         53
#define LDBL_EXP_DIG          11
#define LDBL_POS_EPS 1.1102230246251567e-16
#define LDBL_NEG_EPS 5.5511151231257834e-17
#define LDBL_POS_EPS_EXP    (-52)
#define LDBL_NEG_EPS_EXP    (-53)
#else
#define LDBL_RADIX          DBL_RADIX
#define LDBL_ROUNDS         DBL_ROUNDS
#define LDBL_GUARD          DBL_GUARD
#define LDBL_NORMALIZE      DBL_NORMALIZE
#define LDBL_MAX            DBL_MAX
#define LDBL_MIN            DBL_MIN
#define LDBL_MAX_EXP        DBL_MAX_EXP
#define LDBL_MIN_EXP        DBL_MIN_EXP
#define LDBL_MAX_10_EXP     DBL_MAX_10_EXP
#define LDBL_MIN_10_EXP     DBL_MIN_10_EXP
#define LDBL_DIG            DBL_DIG
#define LDBL_MANT_DIG       DBL_MANT_DIG
#define LDBL_EXP_DIG        DBL_EXP_DIG        
#define LDBL_POS_EPS        DBL_POS_EPS
#define LDBL_NEG_EPS        DBL_NEG_EPS
#define LDBL_POS_EPS_EXP    DBL_POS_EPS_EXP    
#define LDBL_NEG_EPS_EXP    DBL_NEG_EPS_EXP    
#endif

#endif
