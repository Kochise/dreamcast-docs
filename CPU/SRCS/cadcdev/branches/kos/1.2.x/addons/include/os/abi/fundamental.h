/* KallistiOS ##version##

   os/abi/fundamental.h
   (c)2000-2001 Dan Potter

   $Id: fundamental.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ABI_FUNDAMENTAL_H
#define __OS_ABI_FUNDAMENTAL_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	int	(*printf)(const char *fmt, ...);	/* printf */
	uint32	padding1[16-1];

	void*	(*malloc)(size_t size);			/* malloc */
	void	(*free)(void *ptr);
	void*	(*memalign)(size_t size, size_t align);
	uint32	padding2[16-3];

	/* Internal OS Debug Usage ONLY */
	int	(*debug)(int i);				/* misc debug function */
} abi_fundamental_t;

__END_DECLS

#endif	/* __OS_ABI_FUNDAMENTAL_H */

