/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = setjmp.h :                                ;                 */
/*                                                                     */
/*  FUNC = this module do the following functions    ;                 */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#ifndef _SETJMP_SHC
#define _SETJMP_SHC

#if defined(_SH2E)|defined(_SH3E)||defined(_SH4)
typedef int jmp_buf[38];
#else
typedef int jmp_buf[20];
#endif
#ifdef _SH4
typedef int jmp_buf_a[54];
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);
#ifdef _SH4
extern int setjmp_a(jmp_buf);
extern void longjmp_a(jmp_buf, int);
#endif
#ifdef __cplusplus
}
#endif

extern volatile int _errno;

#ifndef SEQERR
#define SEQERR     1108
#endif

#endif