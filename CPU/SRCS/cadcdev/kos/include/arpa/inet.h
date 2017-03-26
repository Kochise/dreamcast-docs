/* KallistiOS ##version##

   arpa/inet.h
   Copyright (C)2006 Lawrence Sebald

*/

#ifndef __ARPA_INET_H
#define __ARPA_INET_H

#include <sys/cdefs.h>
#include <netinet/in.h>

__BEGIN_DECLS

uint32 htonl(uint32 value);
uint32 ntohl(uint32 value);

uint16 htons(uint16 value);
uint16 ntohs(uint16 value);

in_addr_t inet_addr(const char *cp);

__END_DECLS

#endif /* __ARPA_INET_H */
