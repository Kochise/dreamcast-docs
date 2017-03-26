#ifndef __NET_H__
#define __NET_H__

void process_broadcast(unsigned char *pkt, int len);
void process_icmp(ether_header_t *ether, ip_header_t *ip, icmp_header_t *icmp);
void process_udp(ether_header_t *ether, ip_header_t *ip, udp_header_t *udp);
void process_mine(unsigned char *pkt, int len);
void process_pkt(unsigned char *pkt, int len);

extern unsigned char pkt_buf[1514];

extern unsigned int our_ip;

#endif
