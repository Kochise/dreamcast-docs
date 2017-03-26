#include "commands.h"
#include "packet.h"
#include "adapter.h"
#include "scif.h"
#include "net.h"

unsigned char broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

void process_broadcast(unsigned char *pkt, int len)
{
    ether_header_t *ether_header = (ether_header_t *)pkt;
    arp_header_t *arp_header = (arp_header_t *)(pkt + ETHER_H_LEN);
    unsigned char tmp[10];
    unsigned int ip = htonl(our_ip);

    if (ether_header->type[1] != 0x06) /* ARP */
	return;    

    /* hardware address space = ethernet */
    if (arp_header->hw_addr_space != 0x0100)
	return;

    /* protocol address space = IP */
    if (arp_header->proto_addr_space != 0x0008)
	return;

    if (arp_header->opcode == 0x0100) { /* arp request */
	if (our_ip == 0) /* return if we don't know our ip */
	    return;
	if (!memcmp(arp_header->proto_target, &ip, 4)) { /* for us */
	    /* put src hw address into dest hw address */
	    memcpy(ether_header->dest, ether_header->src, 6);
	    /* put our hw address into src hw address */
	    memcpy(ether_header->src, bb->mac, 6);
	    arp_header->opcode = 0x0200; /* arp reply */
	    /* swap sender and target addresses */
	    memcpy(tmp, arp_header->hw_sender, 10);
	    memcpy(arp_header->hw_sender, arp_header->hw_target, 10);
	    memcpy(arp_header->hw_target, tmp, 10);
	    /* put our hw address into sender hw address */
	    memcpy(arp_header->hw_sender, bb->mac, 6);
	    /* transmit */
	    bb->tx(pkt, ETHER_H_LEN + ARP_H_LEN);
	}
    }
}

unsigned char pkt_buf[1514];

void process_icmp(ether_header_t *ether, ip_header_t *ip, icmp_header_t *icmp)
{
  unsigned int i;
  unsigned char tmp[6];

  memset(pkt_buf, 0, ntohs(ip->length) + (ntohs(ip->length)%2) - 4*(ip->version_ihl & 0x0f));

  /* check icmp checksum */
  i = icmp->checksum;
  icmp->checksum = 0;
  memcpy(pkt_buf, icmp, ntohs(ip->length) - 4*(ip->version_ihl & 0x0f));
  icmp->checksum = checksum((unsigned short *)pkt_buf, (ntohs(ip->length)+1)/2 - 2*(ip->version_ihl & 0x0f));
  if (i != icmp->checksum)
    return;
  
  if (icmp->type == 8) { /* echo request */
    icmp->type = 0; /* echo reply */
    /* swap src and dest hw addresses */
    memcpy(tmp, ether->dest, 6);
    memcpy(ether->dest, ether->src, 6);
    memcpy(ether->src, tmp, 6);
    /* swap src and dest ip addresses */
    memcpy(&i, &ip->src, 4);
    memcpy(&ip->src, &ip->dest, 4);
    memcpy(&ip->dest, &i, 4);
    /* recompute ip header checksum */
    ip->checksum = 0;
    ip->checksum = checksum((unsigned short *)ip, 2*(ip->version_ihl & 0x0f));
    /* recompute icmp checksum */
    icmp->checksum = 0;
    icmp->checksum = checksum((unsigned short *)icmp, ntohs(ip->length)/2 - 2*(ip->version_ihl & 0x0f));
    /* transmit */
    bb->tx(ether, ETHER_H_LEN + ntohs(ip->length));
  }
}

typedef struct {
    unsigned int load_address;
    unsigned int load_size;
    unsigned char map[16384];
} bin_info_t;

bin_info_t bin_info;

void process_udp(ether_header_t *ether, ip_header_t *ip, udp_header_t *udp)
{
  ip_udp_pseudo_header_t *pseudo;
  unsigned short i;
  command_t *command;

  pseudo = (ip_udp_pseudo_header_t *)pkt_buf;
  pseudo->src_ip = ip->src;
  pseudo->dest_ip = ip->dest;
  pseudo->zero = 0;
  pseudo->protocol = ip->protocol;
  pseudo->udp_length = udp->length;
  pseudo->src_port = udp->src;
  pseudo->dest_port = udp->dest;
  pseudo->length = udp->length;
  pseudo->checksum = 0;
  memset(pseudo->data, 0, ntohs(udp->length) - 8 + (ntohs(udp->length)%2));
  memcpy(pseudo->data, udp->data, ntohs(udp->length) - 8);

  /* checksum == 0 means no checksum */
  if (udp->checksum != 0)
      i = checksum((unsigned short *)pseudo, (sizeof(ip_udp_pseudo_header_t) + ntohs(udp->length) - 9 + 1)/2);
  else
      i = 0;
  /* checksum == 0xffff means checksum was really 0 */
  if (udp->checksum == 0xffff)
      udp->checksum = 0;

  if (i != udp->checksum) {
/*    scif_puts("UDP CHECKSUM BAD\n"); */
    return;
  }

  make_ether(ether->src, ether->dest, (ether_header_t *)pkt_buf);

  command = (command_t *)udp->data;

  if (!memcmp(command->id, CMD_EXECUTE, 4)) {
      cmd_execute(ether, ip, udp, command);
  }

  if (!memcmp(command->id, CMD_LOADBIN, 4)) {
      cmd_loadbin(ip, udp, command);
  }
  
  if (!memcmp(command->id, CMD_PARTBIN, 4)) {
      cmd_partbin(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_DONEBIN, 4)) {
      cmd_donebin(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_SENDBINQ, 4)) {
      cmd_sendbinq(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_SENDBIN, 4)) {
      cmd_sendbin(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_VERSION, 4)) {
      cmd_version(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_RETVAL, 4)) {
      cmd_retval(ip, udp, command);
  }

  if (!memcmp(command->id, CMD_REBOOT, 4)) {
      cmd_reboot(ip, udp, command);
  }
}

void process_mine(unsigned char *pkt, int len)
{
    ether_header_t *ether_header = (ether_header_t *)pkt;
    ip_header_t *ip_header = (ip_header_t *)(pkt + 14);
    icmp_header_t *icmp_header;
    udp_header_t *udp_header;
    ip_udp_pseudo_header_t *ip_udp_pseudo_header;
    unsigned char tmp[6];
    int i;
    
    if (ether_header->type[1] != 0x00)
	return;

    /* ignore fragmented packets */

    if (ntohs(ip_header->flags_frag_offset) & 0x3fff)
	return;
    
    /* check ip header checksum */
    i = ip_header->checksum;
    ip_header->checksum = 0;
    ip_header->checksum = checksum((unsigned short *)ip_header, 2*(ip_header->version_ihl & 0x0f));
    if (i != ip_header->checksum)
      return;

    switch (ip_header->protocol) {
    case 1: /* icmp */
	icmp_header = (icmp_header_t *)(pkt + ETHER_H_LEN + 4*(ip_header->version_ihl & 0x0f));
	process_icmp(ether_header, ip_header, icmp_header);
	break;
    case 17: /* udp */
      udp_header = (udp_header_t *)(pkt + ETHER_H_LEN + 4*(ip_header->version_ihl & 0x0f));
      process_udp(ether_header, ip_header, udp_header);
    default:
      break;
    }
}

void process_pkt(unsigned char *pkt, int len)
{
    ether_header_t *ether_header = (ether_header_t *)pkt;

    if (ether_header->type[0] != 0x08)
	return;

    if (!memcmp(ether_header->dest, broadcast, 6)) {
	process_broadcast(pkt, len);
	return;
    }

    if (!memcmp(ether_header->dest, bb->mac, 6)) {
	process_mine(pkt, len);
	return;
    }
}
