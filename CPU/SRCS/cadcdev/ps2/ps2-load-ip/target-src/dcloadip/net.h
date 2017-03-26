/* ps2-load-ip

   net.h

   Copyright (c)2000-2001 Andrew Kieschnick
   License: GPL

   $Id: net.h,v 1.1 2002/10/30 05:34:12 bardtx Exp $
*/

#ifndef __NET_H__
#define __NET_H__

#include "packet.h"

void process_broadcast(unsigned char *pkt, int len);
void process_icmp(ether_header_t *ether, ip_header_t *ip, icmp_header_t *icmp);
void process_udp(ether_header_t *ether, ip_header_t *ip, udp_header_t *udp);
void process_mine(unsigned char *pkt, int len);
void process_pkt(unsigned char *pkt, int len);
void net_init();

extern unsigned char pkt_buf[1514];

extern unsigned int our_ip;

#endif
