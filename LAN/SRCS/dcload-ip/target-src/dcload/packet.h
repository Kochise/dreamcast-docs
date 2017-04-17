#ifndef __PACKET_H__
#define __PACKET_H__


typedef struct {
  unsigned char dest[6];
  unsigned char src[6];
  unsigned char type[2];
} ether_header_t;

typedef struct {
  unsigned char version_ihl __attribute__ ((packed));
  unsigned char tos __attribute__ ((packed));
  unsigned short length __attribute__ ((packed));
  unsigned short packet_id __attribute__ ((packed));
  unsigned short flags_frag_offset __attribute__ ((packed));
  unsigned char ttl __attribute__ ((packed));
  unsigned char protocol __attribute__ ((packed));
  unsigned short checksum __attribute__ ((packed));
  unsigned int src __attribute__ ((packed));
  unsigned int dest __attribute__ ((packed));
} ip_header_t;

typedef struct {
  unsigned short src __attribute__ ((packed));
  unsigned short dest __attribute__ ((packed));
  unsigned short length __attribute__ ((packed));
  unsigned short checksum __attribute__ ((packed));
  unsigned char  data[1] __attribute__ ((packed));
} udp_header_t;

typedef struct {
  unsigned char type __attribute__ ((packed));
  unsigned char code __attribute__ ((packed));
  unsigned short checksum __attribute__ ((packed));
  unsigned int misc __attribute__ ((packed));
} icmp_header_t;

typedef struct {
  unsigned short hw_addr_space __attribute__ ((packed));
  unsigned short proto_addr_space __attribute__ ((packed));
  unsigned char hw_addr_len __attribute__ ((packed));
  unsigned char proto_addr_len __attribute__ ((packed));
  unsigned short opcode __attribute__ ((packed));
  unsigned char hw_sender[6] __attribute__ ((packed));
  unsigned char proto_sender[4] __attribute__ ((packed));
  unsigned char hw_target[6] __attribute__ ((packed));
  unsigned char proto_target[4] __attribute__ ((packed));
} arp_header_t;

typedef struct {
  unsigned int src_ip __attribute__ ((packed));
  unsigned int dest_ip __attribute__ ((packed));
  unsigned char zero __attribute__ ((packed));
  unsigned char protocol __attribute__ ((packed));
  unsigned short udp_length __attribute__ ((packed));
  unsigned short src_port __attribute__ ((packed));
  unsigned short dest_port __attribute__ ((packed));
  unsigned short length __attribute__ ((packed));
  unsigned short checksum __attribute__ ((packed));
  unsigned char data[1] __attribute__ ((packed));
} ip_udp_pseudo_header_t;

unsigned short checksum(unsigned short *buf, int count);
void make_ether(char *dest, char *src, ether_header_t *ether);
void make_ip(int dest, int src, int length, char protocol, ip_header_t *ip);
void make_udp(unsigned short dest, unsigned short src, unsigned char * data, int length, ip_header_t *ip, udp_header_t *udp);

#define ntohl bswap32
#define htonl bswap32
#define ntohs bswap16
#define htons bswap16

#define ETHER_H_LEN 14
#define IP_H_LEN    20
#define UDP_H_LEN   8
#define ICMP_H_LEN  8
#define ARP_H_LEN   28

#endif
