/* KallistiOS ##version##

   kernel/net/net_ipv4.h
   Copyright (C) 2005, 2007 Lawrence Sebald

*/

#ifndef __LOCAL_NET_IPV4_H
#define __LOCAL_NET_IPV4_H

/* These structs are from AndrewK's dcload-ip. */
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
	uint32 src_addr    packed;
	uint32 dst_addr    packed;
	uint8 zero         packed;
	uint8 proto        packed;
	uint16 length      packed;
	uint16 src_port    packed;
	uint16 dst_port    packed;
	uint16 hdrlength   packed;
	uint16 checksum    packed;
	uint8 data[1]      packed;
} ip_pseudo_hdr_t;
#undef packed

uint16 net_ipv4_checksum(const uint8 *data, int bytes);
int net_ipv4_send_packet(netif_t *net, ip_hdr_t *hdr, const uint8 *data, int size);
int net_ipv4_input(netif_t *src, const uint8 *pkt, int pktsize);

#endif /* __LOCAL_NET_IPV4_H */
