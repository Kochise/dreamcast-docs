#ifndef __DC_IO_H__
#define __DC_IO_H__

void recv_data(void *data, unsigned int dcaddr, unsigned int total, unsigned int quiet);
void send_data(unsigned char *addr, unsigned int dcaddr, unsigned int size);

int recv_response(unsigned char *buffer, int timeout);
void send_command(unsigned char *command, unsigned int addr, unsigned int size, unsigned char *data, unsigned int dsize);
#endif


