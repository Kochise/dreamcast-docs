/* KallistiOS ##version##

   netif/kosnetif.h
   Copyright (C)2003 Dan Potter

   $Id: kosnetif.h,v 1.1 2003/06/23 04:59:34 bardtx Exp $
*/

#ifndef __KOSNETIF_H
#define __KOSNETIF_H

#include "lwip/netif.h"
#include "netif/etharp.h"

err_t kosnetif_init(struct netif *netif);

#endif /* __KOSNETIF_H */
