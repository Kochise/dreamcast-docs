/* ps2-load-ip

   commands.c
   
   Copyright (c)2000-2001 Andrew Kieschnick
   Copyright (c)2002 Dan Potter
   License: GPL

   $Id: commands.c,v 1.4 2002/11/03 06:57:13 bardtx Exp $
*/
         


#include "commands.h"
#include "packet.h"
#include "net.h"
#include "fb_support.h"
#include "stdio.h"
#include "smap.h"
#include "ps2loadip.h"
#include "go.h"
#include "byteorder.h"
#include "var_cache.h"
#include "syscalls.h"

unsigned int our_ip;
unsigned int tool_ip;
unsigned char tool_mac[6];
unsigned short tool_port;

#define NAME "ps2-load-ip 1.0.1"

typedef struct {
    unsigned int load_address;
    unsigned int load_size;
    unsigned char map[16384];
} bin_info_t;

bin_info_t bin_info;

unsigned char buffer[COMMAND_LEN + 1024]; /* buffer for response */
command_t * response;

void cmd_init() {
	response = (command_t *)buffer;
}

void cmd_reboot(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    go_reboot();
}

void ps2lip_vectors();

void cmd_execute(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    if (!running) {
	tool_ip = ntohl(ip->src);
	tool_port = ntohs(udp->src);
	memcpy(tool_mac, ether->src, 6);
	our_ip = ntohl(ip->dest);

	make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
	make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
	smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

	console_enabled = ntohl(command->size)&1;
	((uint32 *)&ps2lip_vectors)[1] = console_enabled;

	gs_printf(LCD_LOADMSG_FG, "cmd_execute: Executing program at %08x%s\n", ntohl(command->address),
		console_enabled ? " (w/console)" : "");

	smap_stop();
	
	running = 1;
	lcd_setattrs(LCD_RUN_FG, LCD_DEFAULT_BG);

	// Flush all the caches
	flush_caches();

	// Use the asm trampoline
	go(ntohl(command->address));

	lcd_setattrs(LCD_DEFAULT_FG, LCD_DEFAULT_BG);
	running = 0;
	reset_eth = 1;
	console_enabled = 0;
	((uint32 *)&ps2lip_vectors)[1] = 0;

	lcd_refresh();
	gs_printf(LCD_LOADMSG_FG, "cmd_execute: Program finished executing.\n");
    }
}

void cmd_loadbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    bin_info.load_address = ntohl(command->address);
    bin_info.load_size = ntohl(command->size);
    memset(bin_info.map, 0, 16384);

    our_ip = ntohl(ip->dest);
    
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

    if (!running) {
	gs_printf(LCD_LOADMSG_FG, "cmd_loadbin: Receiving data...\n");
    }
}
 
void cmd_partbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{ 
    int index = 0;

    /* gs_printf(LCD_LOADMSG_FG, "cmd_partbin: writing data to %08x, len %d\n",
    	ntohl(command->address), ntohl(command->size)); */

    memcpy((unsigned char *)ntohl(command->address), command->data, ntohl(command->size));
    
    index = (ntohl(command->address) - bin_info.load_address) >> 10;
    bin_info.map[index] = 1;
}

void cmd_donebin(ip_header_t * ip, udp_header_t * udp, command_t * command)
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
    
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

    if (!running) {
	gs_printf(LCD_LOADMSG_FG, "cmd_donebin: Finished receiving\n");
    }
}

void cmd_sendbinq(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int numpackets, i;
    unsigned char *ptr;
    unsigned int bytes_left;
    unsigned int bytes_thistime;

    bytes_left = ntohl(command->size);
    numpackets = (ntohl(command->size)+1023) / 1024;
    ptr = (unsigned char *)ntohl(command->address);

    memcpy(response->id, CMD_SENDBIN, 4);
    for(i = 0; i < numpackets; i++) {
	if (bytes_left >= 1024)
	    bytes_thistime = 1024;
	else
	    bytes_thistime = bytes_left;
	bytes_left -= bytes_thistime;
		
	response->address = htonl((unsigned int)ptr);
	memcpy(response->data, ptr, bytes_thistime);
	response->size = htonl(bytes_thistime);
	make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN + bytes_thistime, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
	make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN + bytes_thistime, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
	smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + bytes_thistime);
	ptr += bytes_thistime;
    }

    memcpy(response->id, CMD_DONEBIN, 4);
    response->address = htonl(0);
    response->size = htonl(0);
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
}

void cmd_sendbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    our_ip = ntohl(ip->dest);

    if (!running) {
        gs_printf(LCD_LOADMSG_FG, "cmd_sendbin: sending data...\n");
    }
    
    cmd_sendbinq(ip, udp, command);

    if (!running) {
        gs_printf(LCD_LOADMSG_FG, "cmd_sendbin: done\n");
    }
}

void cmd_version(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int i;

    i = strlen(NAME) + 1;
    memcpy(response, command, COMMAND_LEN);
    strcpy(response->data, NAME);
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN + i, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN + i, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + i);
}

void cmd_retval(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    if (running) {
	make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
	make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
	smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

	smap_stop();

	syscall_retval = ntohl(command->address);
	escape_loop = 1;
    }
}
