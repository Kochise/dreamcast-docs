/* KallistiOS ##version##

   kernel/net/net_icmp.c

   Copyright (C) 2002 Dan Potter
   Copyright (C) 2005, 2006, 2007 Lawrence Sebald

 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/queue.h>
#include <kos/net.h>
#include <kos/thread.h>
#include <arch/timer.h>
#include <arpa/inet.h>
#include "net_icmp.h"
#include "net_ipv4.h"

CVSID("$Id: net_icmp.c,v 1.2 2002/03/24 00:27:05 bardtx Exp $");

/*
This file implements RFC 792, the Internet Control Message Protocol.
Currently implemented message types are:
   0  - Echo Reply
   8  - Echo

Message types that are not implemented yet (if ever):
   3  - Destination Unreachable
   4  - Source Quench
   5  - Redirect
   11 - Time Exceeded
   12 - Parameter Problem
   14 - Timestamp Reply
   13 - Timestamp
   15 - Information Request
   16 - Information Reply
*/

struct __ping_pkt {
	LIST_ENTRY(__ping_pkt) pkt_list;
	uint8 ip[4];
	uint8 *data;
	int data_sz;
	uint16 icmp_seq;
	uint64 usec;
};

LIST_HEAD(__ping_pkt_list, __ping_pkt);

static struct __ping_pkt_list pings = LIST_HEAD_INITIALIZER(0);
static uint8 pktbuf[1514];
static uint16 icmp_echo_seq = 1;

static void icmp_default_echo_cb(const uint8 *ip, uint16 seq, uint64 delta_us,
                                 uint8 ttl, const uint8* data, int data_sz) {
	printf("%d bytes from %d.%d.%d.%d: icmp_seq=%d ttl=%d time=%.2f ms\n",
	       data_sz, ip[0], ip[1], ip[2], ip[3], seq, ttl,
	       delta_us / 1000.0f);
}

/* The default echo (ping) callback */
net_echo_cb net_icmp_echo_cb = icmp_default_echo_cb;

/* Handle Echo Reply (ICMP type 0) packets */
static void net_icmp_input_0(netif_t *src, ip_hdr_t *ip, icmp_hdr_t *icmp,
                             const uint8 *d, int s) {
	uint64 tmr;
	struct __ping_pkt *ping;
	uint16 seq;

	tmr = timer_us_gettime64();

	LIST_FOREACH(ping, &pings, pkt_list) {
		seq = (d[7] | (d[6] << 8));
		if(ping->icmp_seq == seq) {
			net_icmp_echo_cb((uint8 *)&ip->src, seq, 
			                 tmr - ping->usec, ip->ttl, d, s);

			LIST_REMOVE(ping, pkt_list);
			free(ping->data);
			free(ping);

			return;
		}
	}
}

/* Handle Echo (ICMP type 8) packets */
static void net_icmp_input_8(netif_t *src, ip_hdr_t *ip, icmp_hdr_t *icmp,
                             const uint8 *d, int s) {
	int i;

	/* Set type to echo reply */
	icmp->type = 0;

	/* Swap source and dest ip addresses */
	i = ip->src;
	ip->src = ip->dest;
	ip->dest = i;

	/* Recompute the IP header checksum */
	ip->checksum = 0;
	ip->checksum = net_ipv4_checksum((uint8 *)ip,
	                                 4 * (ip->version_ihl & 0x0f));

	/* Recompute the ICMP header checksum */
	icmp->checksum = 0;
	icmp->checksum = net_ipv4_checksum((uint8 *)icmp, ntohs(ip->length) -
	                                   4 * (ip->version_ihl & 0x0f));

	/* Send it */
	memcpy(pktbuf, ip, 20);
	memcpy(pktbuf + 20, d, ntohs(ip->length) - 4 * (ip->version_ihl & 0x0F));
	net_ipv4_send_packet(src, ip, pktbuf + 20, ntohs(ip->length) -
	                     4 * (ip->version_ihl & 0x0F));
}

int net_icmp_input(netif_t *src, ip_hdr_t *ip, const uint8 *d, int s) {
	icmp_hdr_t *icmp;
	int i;

	/* Find ICMP header */
	icmp = (icmp_hdr_t*) d;

	/* Check icmp checksum */
	memset(pktbuf, 0, 1514);
	i = icmp->checksum;
	icmp->checksum = 0;
	memcpy(pktbuf, icmp, ntohs(ip->length) - 4 * (ip->version_ihl & 0x0f));
	icmp->checksum = net_ipv4_checksum(pktbuf, (ntohs(ip->length) + 1)  -
	                                   4 * (ip->version_ihl & 0x0f));

	if (i != icmp->checksum) {
		dbglog(DBG_KDEBUG, "net_icmp: icmp with invalid checksum\n");
		return -1;
	}

	switch(icmp->type) {
		case 0: /* Echo reply */
			net_icmp_input_0(src, ip, icmp, d, s);
			break;
		case 3: /* Destination unreachable */
			dbglog(DBG_KDEBUG, "net_icmp: Destination unreachable,"
			       " code %d\n", icmp->code);
			break;

		case 8: /* Echo */
			net_icmp_input_8(src, ip, icmp, d, s);
			break;

		default:
			dbglog(DBG_KDEBUG, "net_icmp: unknown icmp type: %d\n",
			       icmp->type);
	}

	return 0;
}

/* Send an ICMP Echo (PING) packet to the specified device */
int net_icmp_send_echo(netif_t *net, const uint8 ipaddr[4], const uint8 *data,
                       int size) {
	icmp_hdr_t *icmp;
	ip_hdr_t ip;
	struct __ping_pkt *newping;
	int r = -1;
	uint8 databuf[sizeof(icmp_hdr_t) + size];

	icmp = (icmp_hdr_t *)databuf;

	/* Fill in the ICMP Header */
	icmp->type = 8; /* Echo */
	icmp->code = 0;
	icmp->checksum = 0;
	icmp->misc[0] = (uint8) 'D';
	icmp->misc[1] = (uint8) 'C';
	icmp->misc[2] = (uint8) (icmp_echo_seq >> 8);
	icmp->misc[3] = (uint8) (icmp_echo_seq & 0xFF);
	memcpy(databuf + sizeof(icmp_hdr_t), data, size);

	/* Fill in the IP Header */
	ip.version_ihl = 0x45; /* 20 byte header, ipv4 */
	ip.tos = 0;
	ip.length = htons(sizeof(icmp_hdr_t) + size + 20);
	ip.packet_id = 0;
	ip.flags_frag_offs = 0x0040;
	ip.ttl = 64;
	ip.protocol = 1; /* ICMP */
	ip.checksum = 0;

	if(net_ipv4_address(ipaddr) == 0x7F000001)
		ip.src = htonl(net_ipv4_address(ipaddr));
	else
		ip.src = htonl(net_ipv4_address(net->ip_addr));

	ip.dest = htonl(net_ipv4_address(ipaddr));

	/* Compute the ICMP Checksum */
	icmp->checksum = net_ipv4_checksum(databuf, sizeof(icmp_hdr_t) + size);

	/* Compute the IP Checksum */
	ip.checksum = net_ipv4_checksum((uint8 *)&ip, sizeof(ip_hdr_t));

	newping = (struct __ping_pkt*) malloc(sizeof(struct __ping_pkt));
	newping->data = (uint8 *)malloc(size);
	newping->data_sz = size;
	newping->icmp_seq = icmp_echo_seq;
	memcpy(newping->data, data, size);
	memcpy(newping->ip, ipaddr, 4);
	LIST_INSERT_HEAD(&pings, newping, pkt_list);

	++icmp_echo_seq;

	while(r == -1)	{
		newping->usec = timer_us_gettime64();
		r = net_ipv4_send_packet(net, &ip, databuf,
		                         sizeof(icmp_hdr_t) + size);
		thd_sleep(10);
	}

	return 0;
}
