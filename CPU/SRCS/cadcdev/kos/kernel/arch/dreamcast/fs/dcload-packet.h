/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-net.h

   Copyright (C)2003 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#ifndef __PACKET_H__
#define __PACKET_H__

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <endian.h>

#define __PACKED__ __attribute__((packed))

typedef struct {
	uint8	dest[6];
	uint8	src[6];
	uint8	type[2];
} ether_header_t;

typedef struct {
	uint8	version_ihl		__PACKED__;
	uint8	tos			__PACKED__;
	uint16	length			__PACKED__;
	uint16	packet_id		__PACKED__;
	uint16	flags_frag_offset	__PACKED__;
	uint8	ttl			__PACKED__;
	uint8	protocol		__PACKED__;
	uint16	checksum		__PACKED__;
	uint32	src			__PACKED__;
	uint32	dest			__PACKED__;
} ip_header_t;

typedef struct {
	uint16	src			__PACKED__;
	uint16	dest			__PACKED__;
	uint16	length			__PACKED__;
	uint16	checksum		__PACKED__;
	uint8	data[0]			__PACKED__;
} udp_header_t;

typedef struct {
	uint8	type			__PACKED__;
	uint8	code			__PACKED__;
	uint16	checksum		__PACKED__;
	uint32	misc			__PACKED__;
} icmp_header_t;

typedef struct {
	uint16	hw_addr_space		__PACKED__;
	uint16	proto_addr_space	__PACKED__;
	uint8	hw_addr_len		__PACKED__;
	uint8	proto_addr_len		__PACKED__;
	uint16	opcode			__PACKED__;
	uint8	hw_sender[6]		__PACKED__;
	uint8	proto_sender[4]		__PACKED__;
	uint8	hw_target[6]		__PACKED__;
	uint8	proto_target[4]		__PACKED__;
} arp_header_t;

typedef struct {
	uint32	src_ip			__PACKED__;
	uint32	dest_ip			__PACKED__;
	uint8	zero			__PACKED__;
	uint8	protocol		__PACKED__;
	uint16	udp_length		__PACKED__;
	uint16	src_port		__PACKED__;
	uint16	dest_port		__PACKED__;
	uint16	length			__PACKED__;
	uint16	checksum		__PACKED__;
	uint8	data[0]			__PACKED__;
} ip_udp_pseudo_header_t;

uint16 dcln_checksum(uint16 *buf, int count);
void dcln_make_ether(char *dest, char *src, ether_header_t *ether);
void dcln_make_ip(int dest, int src, int length, char protocol, ip_header_t *ip);
void dcln_make_udp(uint16 dest, uint16 src, uint8 * data, int length, ip_header_t *ip, udp_header_t *udp);

#define ETHER_H_LEN 14
#define IP_H_LEN    20
#define UDP_H_LEN   8
#define ICMP_H_LEN  8
#define ARP_H_LEN   28

#endif
__END_DECLS
