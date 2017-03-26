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
#define NETCFG_METHOD_DHCP	0
#define NETCFG_METHOD_STATIC	1
#define NETCFG_METHOD_PPPOE	4
#define NETCFG_SRC_VMU		0
#define NETCFG_SRC_FLASH	1
#define NETCFG_SRC_CWD		2
#define NETCFG_SRC_CDROOT	3
typedef struct netcfg {
	int	src;			// Config source
	int	method;			// Configuration method
	uint32	ip;			// IP addresses
	uint32	gateway;
	uint32	netmask;
	uint32	broadcast;
	uint32	dns[2];			// DNS servers
	char	hostname[64];		// DHCP hostname
	char	email[64];		// E-Mail address
	char	smtp[64];		// SMTP server
	char	pop3[64];		// POP3 server
	char	pop3_login[64];		// POP3 login name
	char	pop3_passwd[64];	// POP3 password
	char	proxy_host[64];		// Proxy server hostname
	int	proxy_port;		// Proxy server port
	char	ppp_login[64];		// PPP login
	char	ppp_passwd[64];		// PPP password
	char	driver[64];		// Driver program filename (if any)
} netcfg_t;

// Load a network config from a specific file.
int netcfg_load_from(const char * fn, netcfg_t * out);

// Load a network config from the DC flash.
int netcfg_load_flash(netcfg_t * out);

// Load a network config. Tries the VMUs first, then the current
// directory, and finally /cd.
int netcfg_load(netcfg_t * out);

// Save a network config to a specific file.
int netcfg_save_to(const char * fn, const netcfg_t * cfg);

// Save a network config. Always goes for the first available VMU.
int netcfg_save(const netcfg_t * cfg);

__END_DECLS

#endif	/* __KOS_NETCFG_H */

