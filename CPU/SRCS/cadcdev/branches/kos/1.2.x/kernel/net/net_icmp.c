/* KallistiOS ##version##

   net/net_icmp.c

   (c)2002 Dan Potter

 */

#include <stdio.h>
#include <string.h>
#include <kos/net.h>
#include "net_icmp.h"

CVSID("$Id: net_icmp.c,v 1.2 2002/03/24 00:27:05 bardtx Exp $");

/*

This is just a simple stand-in stack for if you enable networking but don't
setup an actual stack. All this does is respond to ping packets on a given
interface.

Thanks to AndrewK for these IP structures and the code which I studied to
create this (dc-load-ip).

*/

#define packed __attribute__((packed))
typedef struct {
	uint8	dest[6]		packed;
	uint8	src[6]		packed;
	uint8	type[2]		packed;
} eth_hdr_t;

typedef struct {
	uint8	version_ihl	packed;
	uint8	tos		packed;
	uint16	length		packed;
	uint16	packet_id	packed;
	uint16	flags_frag_offs	packed;
	uint8	ttl		packed;
	uint8	protocol	packed;
	uint16	checksum	packed;
	uint32	src		packed;
	uint32	dest		packed;
} ip_hdr_t;

typedef struct {
	uint8	type		packed;
	uint8	code		packed;
	uint16	checksum	packed;
	uint32	misc		packed;
} icmp_hdr_t;
#undef packed

/* Perform an IP-style checksum on a block of data */
static uint16 checksum(uint16 *data, int words) {
	uint32 sum;
	int i;

	sum = 0;
	for (i=0; i<words; i++) {
		sum += data[i];
		if (sum & 0xffff0000) {
			sum &= 0xffff;
			sum++;
		}
	}

	return ~(sum & 0xffff);
}

static uint16 ntohs(uint16 n) {
	return ((n & 0xff) << 8) | ((n >> 8) & 0xff);
}

static uint8 pktbuf[1514];
int net_icmp_input(netif_t *src, uint8 *pkt, int pktsize) {
	eth_hdr_t	*eth;
	ip_hdr_t	*ip;
	icmp_hdr_t	*icmp;
	int		i;
	uint8		tmp[6];
	
	/* Get pointers */
	eth = (eth_hdr_t*)(pkt + 0);
	ip = (ip_hdr_t*)(pkt + sizeof(eth_hdr_t));

	/* Non-IP */
	if (eth->type[0] != 0x08)
		return 0;

	if (eth->type[1] != 0x00)
		return 0;

	/* Ignore fragments */
	if (ntohs(ip->flags_frag_offs) & 0x3fff)
		return 0;

	/* Check ip header checksum */
	i = ip->checksum;
	ip->checksum = 0;
	ip->checksum = checksum((uint16*)ip, 2*(ip->version_ihl & 0x0f));
	if (i != ip->checksum) {
		dbglog(DBG_KDEBUG, "net_icmp: ip with invalid checksum\n");
		return 0;
	}

	if (ip->protocol != 1)
		return 0;

	/* Find ICMP header */
	icmp = (icmp_hdr_t*)(pkt + sizeof(eth_hdr_t) + 4*(ip->version_ihl & 0x0f));
	
	/* Check icmp checksum */
	memset(pktbuf, 0, ntohs(ip->length) + (ntohs(ip->length) % 2)
		- 4*(ip->version_ihl & 0x0f));
	i = icmp->checksum;
	icmp->checksum = 0;
	memcpy(pktbuf, icmp, ntohs(ip->length) - 4*(ip->version_ihl & 0x0f));
	icmp->checksum = checksum((uint16*)pktbuf,
		(ntohs(ip->length) + 1) / 2 - 2*(ip->version_ihl & 0x0f));
	if (i != icmp->checksum) {
		dbglog(DBG_KDEBUG, "net_icmp: icmp with invalid checksum\n");
	//	return;
	}

	if (icmp->type == 8) {	/* echo request */
		icmp->type = 0;	/* echo reply */

		/* Swap source and dest addresses */
		memcpy(tmp, eth->dest, 6);
		memcpy(eth->dest, eth->src, 6);
		memcpy(eth->src, tmp, 6);

		/* Swap source and dest ip addresses */
		memcpy(&i, &ip->src, 4);
		memcpy(&ip->src, &ip->dest, 4);
		memcpy(&ip->dest, &i, 4);

		/* Recompute the IP header checksum */
		ip->checksum = 0;
		ip->checksum = checksum((uint16*)ip, 2*(ip->version_ihl & 0x0f));

		/* Recompute the ICMP header checksum */
		icmp->checksum = 0;
		icmp->checksum = checksum((uint16*)icmp, ntohs(ip->length)/2 - 2*(ip->version_ihl & 0x0f));

		/* Send it */
		src->if_tx(src, pkt, sizeof(eth_hdr_t) + ntohs(ip->length), NETIF_BLOCK);
	}

	return 0;
}


