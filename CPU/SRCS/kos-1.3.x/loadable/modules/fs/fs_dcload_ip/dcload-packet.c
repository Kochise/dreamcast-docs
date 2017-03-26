/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-packet.c

   Copyright (C)2001 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#include "dcload-packet.h"

unsigned short dcln_checksum(unsigned short *buf, int count)
{
    unsigned long sum = 0;

    while (count--) {
	sum += *buf++;
	if (sum & 0xffff0000) {
	    sum &= 0xffff;
	    sum++;
	}
    }
     return ~(sum & 0xffff);
}

void dcln_make_ether(char *dest, char *src, ether_header_t *ether)
{
    memcpy(ether->dest, dest, 6);
    memcpy(ether->src, src, 6);
    ether->type[0] = 8;
    ether->type[1] = 0;
}

void dcln_make_ip(int dest, int src, int length, char protocol, ip_header_t *ip)
{
    ip->version_ihl = 0x45;
    ip->tos = 0;
    ip->length = htons(20 + length);
    ip->packet_id = 0;
    ip->flags_frag_offset = htons(0x4000);
    ip->ttl = 0x40;
    ip->protocol = protocol;
    ip->checksum = 0;
    ip->src = htonl(src);
    ip->dest = htonl(dest);

    ip->checksum = dcln_checksum((unsigned short *)ip, sizeof(ip_header_t)/2);
}

/* umm.... :) */
static unsigned char crap[1514];

void dcln_make_udp(unsigned short dest, unsigned short src, unsigned char * data, int length, ip_header_t *ip, udp_header_t *udp)
{
  ip_udp_pseudo_header_t *pseudo = (ip_udp_pseudo_header_t *)crap;

  udp->src = htons(src);
  udp->dest = htons(dest);
  udp->length = htons(length + 8);
  udp->checksum = 0;
  memcpy(udp->data, data, length);

  pseudo->src_ip = ip->src;
  pseudo->dest_ip = ip->dest;
  pseudo->zero = 0;
  pseudo->protocol = ip->protocol;
  pseudo->udp_length = udp->length;
  pseudo->src_port = udp->src;
  pseudo->dest_port = udp->dest;
  pseudo->length = udp->length;
  pseudo->checksum = 0;
  memset(pseudo->data, 0, length + (length%2));
  memcpy(pseudo->data, udp->data, length);

  udp->checksum = dcln_checksum((unsigned short *)pseudo, (sizeof(ip_udp_pseudo_header_t) + length)/2);
  if (udp->checksum == 0)
      udp->checksum = 0xffff;
}
