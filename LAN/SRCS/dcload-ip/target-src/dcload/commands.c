#include "commands.h"
#include "packet.h"
#include "net.h"
#include "video.h"
#include "adapter.h"
#include "syscalls.h"
#include "cdfs.h"
#include "dcload.h"
#include "go.h"
#include "disable.h"
#include "scif.h"

unsigned int our_ip;
unsigned int tool_ip;
unsigned char tool_mac[6];
unsigned short tool_port;

#define NAME "dcload-ip " DCLOAD_VERSION
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    unsigned int load_address;
    unsigned int load_size;
    unsigned char map[16384];
} bin_info_t;

bin_info_t bin_info;

unsigned char buffer[COMMAND_LEN + 1024]; /* buffer for response */
command_t * response = (command_t *)buffer;

void cmd_reboot(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    booted = 0;
    running = 0;

    disable_cache();
    go(0x8c004000);
}

void cmd_execute(ether_header_t * ether, ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    if (!running) {
	tool_ip = ntohl(ip->src);
	tool_port = ntohs(udp->src);
	memcpy(tool_mac, ether->src, 6);
	our_ip = ntohl(ip->dest);

	make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
	make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
	bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
	
	if (!booted)
	    disp_info();
	else
	    disp_status("executing...");
	
	if (ntohl(command->size)&1)
	    *(unsigned int *)0x8c004004 = 0xdeadbeef; /* enable console */
	else
	    *(unsigned int *)0x8c004004 = 0xfeedface; /* disable console */
	if (ntohl(command->size)>>1)
	    cdfs_redir_enable();
	
	bb->stop();
	
	running = 1;

	disable_cache();
	go(ntohl(command->address));
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
    bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

    if (!running) {
	if (!booted)
	    disp_info();
	disp_status("receiving data...");
    }
}
 
void cmd_partbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{ 
    int index = 0;

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
	command->size = htonl(min(bin_info.load_size - i * 1024, 1024));
    }
    
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

    if (!running) {
	if (!booted)
	    disp_info();
	disp_status("idle...");
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
	bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + bytes_thistime);
	ptr += bytes_thistime;
    }
    
    memcpy(response->id, CMD_DONEBIN, 4);
    response->address = htonl(0);
    response->size = htonl(0);
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);
}

void cmd_sendbin(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    our_ip = ntohl(ip->dest);

    if (!running) {
	if (!booted)
	    disp_info();
	disp_status("sending data...");
    }
    
    cmd_sendbinq(ip, udp, command);

    if (!running) {
	disp_status("idle...");
    }
}

void cmd_version(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    int i;

    i = strlen("DCLOAD-IP " DCLOAD_VERSION) + 1;
    memcpy(response, command, COMMAND_LEN);
    strcpy(response->data, "DCLOAD-IP " DCLOAD_VERSION);
    make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN + i, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
    make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) response, COMMAND_LEN + i, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
    bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN + i);
}

void cmd_retval(ip_header_t * ip, udp_header_t * udp, command_t * command)
{
    if (running) {
	make_ip(ntohl(ip->src), ntohl(ip->dest), UDP_H_LEN + COMMAND_LEN, 17, (ip_header_t *)(pkt_buf + ETHER_H_LEN));
	make_udp(ntohs(udp->src), ntohs(udp->dest),(unsigned char *) command, COMMAND_LEN, (ip_header_t *)(pkt_buf + ETHER_H_LEN), (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN));
	bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + COMMAND_LEN);

	bb->stop();

	syscall_retval = ntohl(command->address);
	syscall_data = command->data;
	escape_loop = 1;
    }
}
