/* KallistiOS ##version##

   kos/iovec.h
   Copyright (C)2001 Dan Potter

   $Id: iovec.h,v 1.1 2002/02/09 06:15:42 bardtx Exp $

*/

#ifndef __KOS_IOVEC_H
#define __KOS_IOVEC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stddef.h>

typedef struct iovec {
	char	*iov_base;	/* Base address */
	size_t	iov_len;	/* Length */
} iovec_t;

__END_DECLS

#endif	/* __KOS_IOVEC_H */

