/* KallistiOS 0.80

   os/abi/serial.h
   (c)2001 Dan Potter

   $Id: serial.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __OS_ABI_SERIAL_H
#define __OS_ABI_SERIAL_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>
#include <kos/dbgio.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	void		(*write)(uint8 *data, int len);
	void		(*read)(uint8 *data, int len);
	void		(*flush)();
} abi_serial_t;

__END_DECLS

#endif	/* __OS_ABI_SERIAL_H */

