/* 
 * dcload-ip lwIP interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <adk@napalm-x.com>
 *
 */

#include <kos.h>
#include <lwip/lwip.h>
#include <netif/arp.h>
#include "dcload-commands.h"
#include "dcload-syscalls.h"

struct udp_pcb *dcload_pcb;
semaphore_t *dcload_sem;

static struct ip_addr host_ip;
static struct eth_addr host_mac;
static int we_know_mac = 0;

/* get host information from dcload-ip */
static unsigned int dcload_gethostinfo(unsigned int *ip, unsigned int *port)
{
    if (*DCLOADMAGICADDR == DCLOADMAGICVALUE)
        return dcloadsyscall(19, ip, port);
    else
      return 0xffffffff;
}

/* dcload-ip udp receive callback */
static void dcload_lwip_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    command_t * command;

    if (memcmp(addr, &host_ip, sizeof(struct ip_addr)) == 0) {
	command = (command_t *)(p->payload);

	if (!memcmp(command->id, CMD_LOADBIN, 4))
	    cmd_loadbin(pcb, p, command);
	
	if (!memcmp(command->id, CMD_PARTBIN, 4))
	    cmd_partbin(pcb, p, command);
	
	if (!memcmp(command->id, CMD_DONEBIN, 4))
	    cmd_donebin(pcb, p, command);
	
	if (!memcmp(command->id, CMD_SENDBINQ, 4))
	    cmd_sendbinq(pcb, p, command);
	
	if (!memcmp(command->id, CMD_SENDBIN, 4))
	    cmd_sendbinq(pcb, p, command);
	
	if (!memcmp(command->id, CMD_RETVAL, 4))
	    cmd_retval(pcb, p, command);
	
	if (!memcmp(command->id, CMD_REBOOT, 4)) {
	    fs_dcload_shutdown();
	    arch_exit();
	}
    }
    pbuf_free(p);
}

/* ensure dc-tool host is in arp cache */
static void dcload_lwip_arp_cache(void)
{
    struct eth_addr *ea = NULL;
    struct pbuf *p;
    struct udp_pcb *discard_pcb;

    if (we_know_mac)
	add_arp_entry(&host_ip, &host_mac);
    else {
	/* allocate a UDP pcb for sending some harmless packets (discard) */
	discard_pcb = udp_new();
	udp_connect(discard_pcb, &host_ip, 9);
	
	while(ea == NULL) {
	    /* force a lookup */
	    p = pbuf_alloc(PBUF_IP, 0, PBUF_RAM);
	    udp_send(discard_pcb, p);
	    pbuf_free(p);
	    
	    /* allow time for reply to arrive */
	    thd_pass();
	    
	    ea = arp_lookup(&host_ip);
	}
	/* deallocate the UDP pcb */
	udp_remove(discard_pcb);
	
	memcpy(&host_mac, ea, sizeof(struct eth_addr));
	we_know_mac = 1;
    }
}

err_t safe_udp_send(struct udp_pcb *pcb, struct pbuf *p)
{
    err_t rv;

    dcload_lwip_arp_cache();
    rv = udp_send(pcb, p);

    return rv;
}

/* stop dcload-ip lwip */
static void dcload_lwip_shutdown(void)
{
    fs_dcload_shutdown();
    dcload_lwip_syscall(DCLOAD_EXIT);
}

/* initialize dcload-ip lwip interface, lwip already initialized */
int dcload_lwip_init(void)
{
  unsigned int our_ip, tool_ip, tool_port;
  unsigned char a,b,c,d;

  our_ip = dcload_gethostinfo(&tool_ip, &tool_port);

  if (our_ip != 0xffffffff) {

      dcload_sem = sem_create(0);
      
      a = (tool_ip >> 24) & 0xff;
      b = (tool_ip >> 16) & 0xff;
      c = (tool_ip >> 8) & 0xff;
      d = (tool_ip) & 0xff;
      
      IP4_ADDR(&host_ip, a,b,c,d);
      
      dcload_pcb = udp_new();
      udp_bind(dcload_pcb, IP_ADDR_ANY, 31313);
      udp_connect(dcload_pcb, &host_ip, tool_port);
      udp_recv(dcload_pcb, dcload_lwip_recv, NULL);

      dcload_lwip_arp_cache();

      atexit(dcload_lwip_shutdown);
      fs_dcload_init_lwip(dcload_lwip_syscall);

      return 0;
  }
  return -1;
}

/* initialize lwip and dcload-ip using information from dcload-ip */
int lwip_init_dcload(void)
{
  unsigned int our_ip, tool_ip, tool_port;
  unsigned char a,b,c,d;
  struct ip_addr ipaddr, netmask;

  our_ip = dcload_gethostinfo(&tool_ip, &tool_port);

  if (our_ip != 0xffffffff) {

      a = (our_ip >> 24) & 0xff;
      b = (our_ip >> 16) & 0xff;
      c = (our_ip >> 8) & 0xff;
      d = (our_ip) & 0xff;
      
      IP4_ADDR(&ipaddr, a,b,c,d);
      IP4_ADDR(&netmask, 255,255,255,0);

      if (lwip_init_static(&ipaddr, &netmask, &ipaddr) < 0)
	  return -1;

      dcload_sem = sem_create(0);
      
      a = (tool_ip >> 24) & 0xff;
      b = (tool_ip >> 16) & 0xff;
      c = (tool_ip >> 8) & 0xff;
      d = (tool_ip) & 0xff;
      
      IP4_ADDR(&host_ip, a,b,c,d);
      
      dcload_pcb = udp_new();
      udp_bind(dcload_pcb, IP_ADDR_ANY, 31313);
      udp_connect(dcload_pcb, &host_ip, tool_port);
      udp_recv(dcload_pcb, dcload_lwip_recv, NULL);

      dcload_lwip_arp_cache();

      atexit(dcload_lwip_shutdown);
      fs_dcload_init_lwip(dcload_lwip_syscall);

      return 0;
  }
  return -1;
}
