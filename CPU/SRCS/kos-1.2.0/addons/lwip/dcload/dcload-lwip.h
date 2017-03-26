/* 
 * dcload-ip lwIP interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <adk@napalm-x.com>
 *
 */

#ifndef __DCLOAD_LWIP_H__
#define __DCLOAD_LWIP_H__

#include <kos.h>
#include <lwip/lwip.h>

extern struct udp_pcb *dcload_pcb;
extern semaphore_t *dcload_sem;

/* "safe" udp send - ensures dc-tool host is in arp cache prior to sending */
err_t safe_udp_send(struct udp_pcb *pcb, struct pbuf *p);

/* initialize dcload-ip lwip interface, lwip already initialized */
int dcload_lwip_init(void);

/* initialize lwip and dcload-ip using information from dcload-ip */
int lwip_init_dcload(void);

#endif

