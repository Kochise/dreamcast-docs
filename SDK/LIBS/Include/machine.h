/*------------------------------------------------------*/
/* SH C Compiler Ver. 1.0                               */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = machine.h :                                          */
/*   FUNC =                                                      */
/*          ;                                                    */
/*                                                               */
/*                                                               */
/*                                                               */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _MACHINE
#define _MACHINE

#ifdef __MWERKS__
    #include <SH4_mwerks.h>
#else
    #ifdef __GNUC__
        #include <SH4_gnu.h>
    #else
        #include <smachine.h>
        #include <umachine.h>
    #endif /* __GNUC__ */
#endif /* __MWERKS__ */

#endif