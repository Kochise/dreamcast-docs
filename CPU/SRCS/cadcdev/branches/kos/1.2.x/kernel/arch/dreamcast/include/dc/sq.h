/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/sq.h
   (C)2000-2001 Andrew Kieschnick

   $Id: sq.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $
*/


#ifndef __DC_SQ_H
#define __DC_SQ_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

#define QACR0 (*(volatile unsigned int *)(void *)0xff000038)
#define QACR1 (*(volatile unsigned int *)(void *)0xff00003c)

/* clears n bytes at dest, dest must be 32-byte aligned */
void sq_clr(void *dest, int n);

/* copies n bytes from src to dest, dest must be 32-byte aligned */
void * sq_cpy(void *dest, void *src, int n);

/* fills n bytes at s with byte c, s must be 32-byte aligned */
void * sq_set(void *s, uint32 c, int n);

/* fills n bytes at s with short c, s must be 32-byte aligned */
void * sq_set16(void *s, uint32 c, int n);

/* fills n bytes at s with int c, s must be 32-byte aligned */
void * sq_set32(void *s, uint32 c, int n);

__END_DECLS

#endif

