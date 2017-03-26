/*------------------------------------------------------*/
/* SH SERIES C Compiler Ver. 1.0                        */
/* Copyright (c) 1992 Hitachi,Ltd.                      */
/* Licensed material of Hitachi,Ltd.                    */
/*------------------------------------------------------*/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = stddef :                                                    */
/*                                                                     */
/*  FUNC = this module do the following functions                      */
/*                                                                     */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
#ifndef _STDDEF_SHC
#define _STDDEF_SHC

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef int ptrdiff_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#ifndef  NULL
#ifdef  __cplusplus
#define  NULL           (0)
#else
#define  NULL           ((void *)0)
#endif
#endif

#ifndef  offsetof
#define  offsetof(type,id) ((char *)(&(((type *)NULL)->id))  -    \
                            (char *)((type *)NULL))
#endif

#ifndef  errno
#define  errno          _errno
#endif

#endif