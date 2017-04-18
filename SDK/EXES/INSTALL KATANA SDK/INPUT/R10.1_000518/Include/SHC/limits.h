/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = limits.h :                                                  */
/*                                                                     */
/*  FUNC = this module do the following functions                      */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#ifndef _LIMITS_SHC
#define _LIMITS_SHC

#define       CHAR_BIT                8
#define       CHAR_MAX              127
#define       CHAR_MIN           (-128)
#define       SCHAR_MAX             127
#define       SCHAR_MIN          (-128)
#define       UCHAR_MAX             255
#define       SHRT_MAX            32767
#define       SHRT_MIN         (-32768)
#define       USHRT_MAX           65535
#define       INT_MAX        2147483647
#define       INT_MIN    (-2147483647-1)
#define       UINT_MAX      4294967295u
#define       LONG_MAX       2147483647
#define       LONG_MIN   (-2147483647L-1L)
#define       ULONG_MAX     4294967295u

#endif