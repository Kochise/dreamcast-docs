/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: arp.c,v 1.2 2002/06/11 05:32:27 bardtx Exp $
 *
 */

#include "lwip/debug.h"
#include "lwip/inet.h"
#include "netif/arp.h"
#include "lwip/ip.h"

#if LWIP_DHCP
#  include "lwip/dhcp.h"
#endif


#define ARP_MAXAGE 2  /* 120 * 10 seconds = 20 minutes. */

#define HWTYPE_ETHERNET 1

#define ARP_REQUEST 1
#define ARP_REPLY 2

/* MUST be compiled with "pack structs" or equivalent! */
PACK_STRUCT_BEGIN
struct arp_hdr {
  PACK_STRUCT_FIELD(struct eth_hdr ethhdr);
  PACK_STRUCT_FIELD(u16_t hwtype);
  PACK_STRUCT_FIELD(u16_t proto);
  PACK_STRUCT_FIELD(u16_t _hwlen_protolen);
  PACK_STRUCT_FIELD(u16_t opcode);
  PACK_STRUCT_FIELD(struct eth_addr shwaddr);
  PACK_STRUCT_FIELD(struct ip_addr sipaddr);
  PACK_STRUCT_FIELD(struct eth_addr dhwaddr);
  PACK_STRUCT_FIELD(struct ip_addr dipaddr);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

#define ARPH_HWLEN(hdr) (NTOHS((hdr)->_hwlen_protolen) >> 8)
#define ARPH_PROTOLEN(hdr) (NTOHS((hdr)->_hwlen_protolen) & 0xff)


#define ARPH_HWLEN_SET(hdr, len) (hdr)->_hwlen_protolen = HTONS(ARPH_PROTOLEN(hdr) | ((len) << 8))
#define ARPH_PROTOLEN_SET(hdr, len) (hdr)->_hwlen_protolen = HTONS((len) | (ARPH_HWLEN(hdr) << 8))

PACK_STRUCT_BEGIN
struct ethip_hdr {
  PACK_STRUCT_FIELD(struct eth_hdr eth);
  PACK_STRUCT_FIELD(struct ip_hdr ip);
};
PACK_STRUCT_END

struct arp_entry {
  struct ip_addr ipaddr;
  struct eth_addr ethaddr;
  u8_t ctime;
};

static struct arp_entry arp_table[ARP_TABLE_SIZE];
static u8_t ctime;

/*-----------------------------------------------------------------------------------*/
void
arp_init(void)
{
  u8_t i;
  
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    ip_addr_set(&(arp_table[i].ipaddr),
		IP_ADDR_ANY);
  }
}
/*-----------------------------------------------------------------------------------*/
void
arp_tmr(void)
{
  u8_t i;
  
  ++ctime;
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    if(!ip_addr_isany(&arp_table[i].ipaddr) &&       
       ctime - arp_table[i].ctime >= ARP_MAXAGE) {
      DEBUGF(ARP_DEBUG, ("arp_timer: expired entry %d.\n", i));
      ip_addr_set(&(arp_table[i].ipaddr),
		  IP_ADDR_ANY);
    }
  }  
}
/*-----------------------------------------------------------------------------------*/
void
add_arp_entry(struct ip_addr *ipaddr, struct eth_addr *ethaddr)
{
  u8_t i, j, k;
  u8_t maxtime;
  
  /* Walk through the ARP mapping table and try to find an entry to
     update. If none is found, the IP -> MAC address mapping is
     inserted in the ARP table. */
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    
    /* Only check those entries that are actually in use. */
    if(!ip_addr_isany(&arp_table[i].ipaddr)) {
      /* Check if the source IP address of the incoming packet matches
         the IP address in this ARP table entry. */
      if(ip_addr_cmp(ipaddr, &arp_table[i].ipaddr)) {
	/* An old entry found, update this and return. */
	for(k = 0; k < 6; ++k) {
	  arp_table[i].ethaddr.addr[k] = ethaddr->addr[k];
	}
	arp_table[i].ctime = ctime;
	return;
      }
    }
  }

  /* If we get here, no existing ARP table entry was found, so we
     create one. */

  /* First, we try to find an unused entry in the ARP table. */
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    if(ip_addr_isany(&arp_table[i].ipaddr)) {
      break;
    }
  }

  /* If no unused entry is found, we try to find the oldest entry and
     throw it away. */
  if(i == ARP_TABLE_SIZE) {
    maxtime = 0;
    j = 0;
    for(i = 0; i < ARP_TABLE_SIZE; ++i) {
      if(ctime - arp_table[i].ctime > maxtime) {
	maxtime = ctime - arp_table[i].ctime;
	j = i;
      }
    }
    i = j;
  }

  /* Now, i is the ARP table entry which we will fill with the new
     information. */
  ip_addr_set(&arp_table[i].ipaddr, ipaddr);
  for(k = 0; k < 6; ++k) {
    arp_table[i].ethaddr.addr[k] = ethaddr->addr[k];
  }
  arp_table[i].ctime = ctime;
  return;

}
/*-----------------------------------------------------------------------------------*/
void
arp_ip_input(struct lwipif *netif, struct pbuf *p)
{
  struct ethip_hdr *hdr;
  
  hdr = p->payload;
  
  /* Only insert/update an entry if the source IP address of the
     incoming IP packet comes from a host on the local network. */
  if(!ip_addr_maskcmp(&(hdr->ip.src), &(netif->ip_addr), &(netif->netmask))) {
    return;
  }
  DEBUGF(ARP_DEBUG, ("arp_ip_input: updating ARP table.\n"));
  add_arp_entry(&(hdr->ip.src), &(hdr->eth.src));
}
/*-----------------------------------------------------------------------------------*/
struct pbuf *
arp_arp_input(struct lwipif *netif, struct eth_addr *ethaddr, struct pbuf *p)
{
  struct arp_hdr *hdr;
  u8_t i;
  
  if(p->tot_len < sizeof(struct arp_hdr)) {
    DEBUGF(ARP_DEBUG, ("arp_arp_input: packet too short (%d/%d)\n", p->tot_len, sizeof(struct arp_hdr)));
    pbuf_free(p);
    return NULL;
  }

  hdr = p->payload;
  
  switch(htons(hdr->opcode)) {
  case ARP_REQUEST:
    /* ARP request. If it asked for our address, we send out a
       reply. */
    DEBUGF(ARP_DEBUG, ("arp_arp_input: ARP request\n"));
    if(ip_addr_cmp(&(hdr->dipaddr), &(netif->ip_addr))) {
      hdr->opcode = htons(ARP_REPLY);

      ip_addr_set(&(hdr->dipaddr), &(hdr->sipaddr));
      ip_addr_set(&(hdr->sipaddr), &(netif->ip_addr));

      for(i = 0; i < 6; ++i) {
	hdr->dhwaddr.addr[i] = hdr->shwaddr.addr[i];
	hdr->shwaddr.addr[i] = ethaddr->addr[i];
	hdr->ethhdr.dest.addr[i] = hdr->dhwaddr.addr[i];
	hdr->ethhdr.src.addr[i] = ethaddr->addr[i];
      }

      hdr->hwtype = htons(HWTYPE_ETHERNET);
      ARPH_HWLEN_SET(hdr, 6);
      
      hdr->proto = htons(ETHTYPE_IP);
      ARPH_PROTOLEN_SET(hdr, sizeof(struct ip_addr));      
      
      hdr->ethhdr.type = htons(ETHTYPE_ARP);      
      return p;
    }
    break;
  case ARP_REPLY:    
    /* ARP reply. We insert or update the ARP table. */
    DEBUGF(ARP_DEBUG, ("arp_arp_input: ARP reply\n"));
    if(ip_addr_cmp(&(hdr->dipaddr), &(netif->ip_addr))) {
      add_arp_entry(&(hdr->sipaddr), &(hdr->shwaddr));
#if (LWIP_DHCP && DHCP_DOES_ARP_CHECK)
      dhcp_arp_reply(&hdr->sipaddr);
#endif      
    }
    break;
  default:
    DEBUGF(ARP_DEBUG, ("arp_arp_input: unknown type %d\n", htons(hdr->opcode)));
    break;
  }

  pbuf_free(p);
  return NULL;
}
/*-----------------------------------------------------------------------------------*/
struct eth_addr *
arp_lookup(struct ip_addr *ipaddr)
{
  u8_t i;
  
  for(i = 0; i < ARP_TABLE_SIZE; ++i) {
    if(ip_addr_cmp(ipaddr, &arp_table[i].ipaddr)) {
      return &arp_table[i].ethaddr;
    }
  }
  return NULL;  
}
/*-----------------------------------------------------------------------------------*/
struct pbuf *
arp_query(struct lwipif *netif, struct eth_addr *ethaddr, struct ip_addr *ipaddr)
{
  struct arp_hdr *hdr;
  struct pbuf *p;
  u8_t i;

  p = pbuf_alloc(PBUF_LINK, sizeof(struct arp_hdr), PBUF_RAM);
  if(p == NULL) {
    return NULL;
  }

  hdr = p->payload;
  
  hdr->opcode = htons(ARP_REQUEST);

  for(i = 0; i < 6; ++i) {
    hdr->dhwaddr.addr[i] = 0x00;
    hdr->shwaddr.addr[i] = ethaddr->addr[i];
  }
  
  ip_addr_set(&(hdr->dipaddr), ipaddr);
  ip_addr_set(&(hdr->sipaddr), &(netif->ip_addr));

  hdr->hwtype = htons(HWTYPE_ETHERNET);
  ARPH_HWLEN_SET(hdr, 6);

  hdr->proto = htons(ETHTYPE_IP);
  ARPH_PROTOLEN_SET(hdr, sizeof(struct ip_addr));

  for(i = 0; i < 6; ++i) {
    hdr->ethhdr.dest.addr[i] = 0xff;
    hdr->ethhdr.src.addr[i] = ethaddr->addr[i];
  }
  
  hdr->ethhdr.type = htons(ETHTYPE_ARP);      
  return p;
}
/*-----------------------------------------------------------------------------------*/




