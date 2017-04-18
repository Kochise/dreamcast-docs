/* KallistiOS 1.1.6

   sys/iovec.h
   (c)2001 Dan Potter

   $Id: iovec.h,v 1.2 2002/01/05 07:23:33 bardtx Exp $

*/

#ifndef __SYS_IOVEC_H
#define __SYS_IOVEC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stddef.h>

typedef struct iovec {
	char	*iov_base;	/* Base address */
	size_t	iov_len;	/* Length */
} iovec_t;

__END_DECLS

#endif	/* __SYS_IOVEC_H */

