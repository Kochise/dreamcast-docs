/* KallistiOS ##version##
   
   kos/netcfg.h
   Copyright (C)2003 Dan Potter

   $Id: netcfg.h,v 1.1 2003/07/15 07:58:28 bardtx Exp $

*/

#ifndef __KOS_NETCFG_H
#define __KOS_NETCFG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Network configuration info. This holds the information about how we
   will start the networking and what settings to use. */
typedef struct netcfg {
	uint32	ip;
	uint32	gateway;
	uint32	netmask;
	char	driver[64];	// Program filename
} netcfg_t;

// Load a network config from a specific file.
int netcfg_load_from(const char * fn, netcfg_t * out);

// Load a network config. Tries the VMUs first, then the current
// directory, and finally /cd.
int netcfg_load(netcfg_t * out);

// Save a network config to a specific file.
int netcfg_save_to(const char * fn, const netcfg_t * cfg);

// Save a network config. Always goes for the first available VMU.
int netcfg_save(const netcfg_t * cfg);

__END_DECLS

#endif	/* __KOS_NETCFG_H */

