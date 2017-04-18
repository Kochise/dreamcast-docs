/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 3.0                        */
/* Copyright (c) 1992,1995 Hitachi,Ltd.                 */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = smachine.h :                                        */
/*   FUNC = ;                                                    */
/*   CLAS = UNIT ;                                               */
/*   END ;                                                       */
/*****************************************************************/
#ifndef _SMACHINE_SHC
#define _SMACHINE_SHC

#define set_imask(mask)             _builtin_set_imask(mask)
#define get_imask()                 _builtin_get_imask()
#define set_cr(cr)                  _builtin_set_cr(cr)
#define get_cr()                    _builtin_get_cr()
#define set_vbr(base)               _builtin_set_vbr(base)
#define get_vbr()                   _builtin_get_vbr()
#define sleep()                     _builtin_sleep()

#endif