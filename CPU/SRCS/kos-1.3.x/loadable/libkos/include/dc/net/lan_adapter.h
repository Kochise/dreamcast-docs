/* KallistiOS ##version##
 *
 * dc/net/lan_adapter.h
 *
 * (c)2002 Dan Potter
 *
 * $Id: lan_adapter.h,v 1.1 2003/07/31 00:54:04 bardtx Exp $
 */

#ifndef __DC_NET_LAN_ADAPTER_H
#define __DC_NET_LAN_ADAPTER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/net.h>

/* Initialize */
int la_init();

/* Shutdown */
int la_shutdown();

__END_DECLS

#endif	/* __DC_NET_LAN_ADAPTER_H */

