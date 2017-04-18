/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = assert.h : debug macro define          ;                    */
/*                                                                     */
/*  FUNC = this module do the following functions;                     */
/*         (1) if NDEBUG defined assert(x) = (void)0;                  */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#ifndef _ASSERT_SHC
#define _ASSERT_SHC

#include <stdio.h>
#ifdef NDEBUG
#ifdef assert
#undef assert
#endif
#define assert(x) ((void)0)
#else
#ifdef assert
#undef assert
#endif
#define       assert(x) ( x ? (void) 0 : (fprintf(stderr,\
              "ASSERTION FAILED: "#x" FILE %s,LINE %d \n", \
              __FILE__,__LINE__),abort(),(void)0))
#endif
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

#endif