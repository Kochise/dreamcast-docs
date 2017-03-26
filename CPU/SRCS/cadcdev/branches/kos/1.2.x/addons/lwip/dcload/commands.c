/* 
 * dcload-ip commands for dcload-ip lwIP interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <adk@napalm-x.com>
 *
 */

#include <kos.h>
#include <lwip/lwip.h>
#include "dcload-commands.h"
#include "dcload-syscalls.h"
#include "dcload-lwip.h"

typedef struct {
    unsigned int load_address;
    unsigned int load_size;
    unsigned char map[16384];
} bin_info_t;

static bin_info_t bin_info;

void cmd_loadbin(struct udp_pcb *pcb, struct pbuf *p, command_t * command)
{
    bin_info.load_address = ntohl(command->address);
    bin_info.load_size = ntohl(command->size);
    memset(bin_info.map, 0, 16384);
    
    pbuf_realloc(p, COMMAND_LEN);

    safe_udp_send(pcb, p);
}
 
void cmd_partbin(struct udp_pcb *pcb, struct pbuf *p, command_t * command)
{ 
    int index = 0;

    memcpy((unsigned char *)ntohl(command->address), command->data, ntohl(command->size));
    
    index = (ntohl(command->address) - bin_info.load_address) >> 10;
    bin_info.map[index] = 1;
}

void cmd_donebin(struct udp_pcb *pcb, struct pbuf *p, command_t * command)
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
	    command->size = htonl(bin_info.load_size % 1024) ? htonl(bin_info.load_size % 1024) : htonl(1024);
	else
	    command->size = htonl(1024);
    }

    pbuf_realloc(p, COMMAND_LEN);
    safe_udp_send(pcb, p);
}

void cmd_sendbinq(struct udp_pcb *pcb, struct pbuf *p, command_t * command)
{
    int numpackets, i;
    unsigned char *ptr;
    unsigned int bytes_left;
    unsigned int bytes_thistime;
    struct pbuf *pb;
    command_t *response;

    bytes_left = ntohl(command->size);
    numpackets = (ntohl(command->size)+1023) / 1024;
    ptr = (unsigned char *)ntohl(command->address);
    
    for(i = 0; i < numpackets; i++) {
	if (bytes_left >= 1024)
	    bytes_thistime = 1024;
	else
	    bytes_thistime = bytes_left;
	bytes_left -= bytes_thistime;
		
	pb = pbuf_alloc(PBUF_TRANSPORT, COMMAND_LEN + bytes_thistime, PBUF_RAM);

	response = (command_t *)(pb->payload);
	memcpy(response->id, CMD_SENDBIN, 4);

	response->address = htonl((unsigned int)ptr);
	memcpy(response->data, ptr, bytes_thistime);
	response->size = htonl(bytes_thistime);
	
	safe_udp_send(pcb, pb);

	ptr += bytes_thistime;

	pbuf_free(pb);
    }

    pb = pbuf_alloc(PBUF_TRANSPORT, COMMAND_LEN, PBUF_RAM);
    response = (command_t *)(pb->payload);
    
    memcpy(response->id, CMD_DONEBIN, 4);
    response->address = htonl(0);
    response->size = htonl(0);

    safe_udp_send(pcb, pb);

    pbuf_free(pb);
}

void cmd_retval(struct udp_pcb *pcb, struct pbuf *p, command_t * command)
{
    pbuf_realloc(p, COMMAND_LEN);
    safe_udp_send(pcb, p);
	
    syscall_retval = ntohl(command->address);

    sem_signal(dcload_sem);
}
