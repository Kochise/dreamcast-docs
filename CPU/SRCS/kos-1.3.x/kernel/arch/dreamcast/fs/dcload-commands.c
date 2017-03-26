/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-commands.c

   Copyright (C)2001 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible 
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#include <dc/fs_dclnative.h>
#include "dcload-commands.h"
#include "dcload-packet.h"
#include "dcload-net.h"
#include "dcload-syscalls.h"

/* #include "commands.h"
#include "packet.h"
#include "net.h"
#include "video.h"
#include "rtl8139.h"
#include "syscalls.h"
#include "cdfs.h"
#include "dcload.h"
#include "go.h"
#include "disable.h"
#include "scif.h" */

#define NAME "dcload-ip-native 1.0.3"

typedef struct {
    unsigned int load_address;
    unsigned int load_size;
    unsigned char map[16384];
} bin_info_t;

static bin_info_t bin_info;

static unsigned char buffer[COMMAND_LEN + 1024]; /* buffer for response */
static command_t * response = (command_t *)buffer;

/* void cmd_reboot(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    booted = 0;
    running = 0;

    disable_cache();
    go(0x8c004000);
} */

void dcln_cmd_loadbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    bin_info.load_address = ntohl(command->address);
    bin_info.load_size = ntohl(command->size);
    memset(bin_info.map, 0, 16384);

    dcln_our_ip = ntohl(ip->dest);
    
    dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
    dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
    dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
}
 
void dcln_cmd_partbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{ 
    int index = 0;

    memcpy((unsigned char *)ntohl(command->address), command->data, ntohl(command->size));
    
    index = (ntohl(command->address) - bin_info.load_address) >> 10;
    bin_info.map[index] = 1;
}

void dcln_cmd_donebin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int i;
    
    for(i = 0; i < (bin_info.load_size + 1023)/1024; i++)
	if (!bin_info.map[i])
	    break;
    if ( i == (bin_info.load_size + 1023)/1024 ) {
	command->address = htonl(0);
	command->size = htonl(0);
    }	else {
	command->address = htonl( bin_info.load_address + i * 1024);
	if ( i == ( bin_info.load_size + 1023)/1024 - 1)
	    command->size = htonl(bin_info.load_size % 1024);
	else
	    command->size = htonl(1024);
    }
    
    dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
    dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
    dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
}

void dcln_cmd_sendbinq(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int numpackets, i;
    unsigned char *ptr;
    unsigned int bytes_left;
    unsigned int bytes_thistime;

    bytes_left = ntohl(command->size);
    numpackets = (ntohl(command->size)+1023) / 1024;
    ptr = (unsigned char *)ntohl(command->address);
    
    memcpy(response->id, DCLN_CMD_SENDBIN, 4);
    for(i = 0; i < numpackets; i++) {
	if (bytes_left >= 1024)
	    bytes_thistime = 1024;
	else
	    bytes_thistime = bytes_left;
	bytes_left -= bytes_thistime;
		
	response->address = htonl((unsigned int)ptr);
	memcpy(response->data, ptr, bytes_thistime);
	response->size = htonl(bytes_thistime);
	dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN + bytes_thistime, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
	dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN + bytes_thistime, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
	dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + bytes_thistime);
	ptr += bytes_thistime;
    }
    
    memcpy(response->id, DCLN_CMD_DONEBIN, 4);
    response->address = htonl(0);
    response->size = htonl(0);
    dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
    dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
    dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
}

void dcln_cmd_sendbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    dcln_our_ip = ntohl(ip->dest);
    dcln_cmd_sendbinq(ip, udp, command);
}

void dcln_cmd_version(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int i;

    i = strlen(NAME) + 1;
    memcpy(response, command, COMMAND_LEN);
    strcpy(response->data, NAME);
    dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN + i, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
    dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN + i, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
    dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + i);
}

void dcln_cmd_retval(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
	dcln_make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN));
	dcln_make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN), (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN));
	dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

	dcln_syscall_retval = ntohl(command->address);
	dcln_escape_loop = 1;
}
