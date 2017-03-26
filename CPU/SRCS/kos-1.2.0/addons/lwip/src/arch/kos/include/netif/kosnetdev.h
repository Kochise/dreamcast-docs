/*
 */
#ifndef __KOSNETDEV_H__
#define __KOSNETDEV_H__

#include <kos/net.h>
#include "lwip/netif.h"
#include "lwip/pbuf.h"

void kosnetdev_init(struct lwipif *netif);
void kosnetdev_set_netif(struct lwipif * lwif, netif_t * n);

#endif /* __KOSNETDEV_H__ */
