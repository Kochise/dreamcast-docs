/* ps2-load-ip

   ps2-io.h

   Copyright (c)2000-2001 Andrew Kieschnick
   License: GPL

   $Id: ps2-io.h,v 1.1 2002/10/30 06:22:50 bardtx Exp $
*/
            
#ifndef __PS2_IO_H__
#define __PS2_IO_H__

void recv_data(void *data, unsigned int dcaddr, unsigned int total, unsigned int quiet);
void send_data(unsigned char *addr, unsigned int dcaddr, unsigned int size);

int recv_response(unsigned char *buffer, int timeout);
void send_command(unsigned char *command, unsigned int addr, unsigned int size, unsigned char *data, unsigned int dsize);
#endif


