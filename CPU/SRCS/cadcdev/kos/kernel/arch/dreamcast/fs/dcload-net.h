/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-net.h

   Copyright (C)2003 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#ifndef __NET_H__
#define __NET_H__

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

void dcln_process_pkt(unsigned char *pkt, int len);
void dcln_tx(uint8 * pkt, int len);
void dcln_rx_loop();

extern uint32 dcln_our_ip;
extern uint8 dcln_our_mac[6];
extern uint8 dcln_pkt_buf[1600];

__END_DECLS

#endif
