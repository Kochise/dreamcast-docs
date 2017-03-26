/* Basic packet routines for communicating with a GDB compatible stub */

#include <stdlib.h>
#include <malloc.h>
#include "serial.h"

#define DEBUG printf

/* Sends one packet to a GDB compatible stub. No RLE is performed. This
   is a port back from my Python code. */
void sc_packet_send(char* packet) {
	int packetlen = strlen(packet);
	// DEBUG("Sending packet: %s\n", packet);
	/* Retry until we get a positive response */
	while(1) {
		int checksum, i;
		char buf[16];
		
		ser_putch('$');
		checksum = 0;
		
		for (i=0; i<packetlen; i++) {
			ser_putch(packet[i]);
			checksum += packet[i];
		}
		
		ser_putch('#');
		sprintf(buf, "%02x", checksum & 0xff);
		ser_putch(buf[0]); ser_putch(buf[1]);
		
		i = ser_getch();
		if (i == '+') break;
	}
}


/* Waits for one packet from a GDB compatible stub. No RLE decoding is
   performed. This is a port back from my Python code. Make sure your
   receive buffer is big enough!! */
void sc_packet_recv(char* buffer, int maxlen) {
	/* Wait around for start char, ignore all others */
	while (ser_getch() != '$')
		;

	/* Retry until we get a good checksum */
	while(1) {
		int checksum, xmitcsum, ocnt, ch;
		char buf[16];
		
		/* Read until a # */
		buffer[0] = '\0';
		ocnt = 0; checksum = 0;
		while(1) {
			ch = ser_getch();
			if (ch == '$') break;
			if (ch == '#') break;
			checksum += ch;
 			buffer[ocnt++] = ch;
			if (ocnt >= maxlen) {
				DEBUG("error: buffer overflow in packet_recv\n");
				ser_putch('-');
				return;
			}
		}
		
		/* If we find another packet start, make another go */
		if (ch == '$') continue;
		
		/* Null-terminate it */
		buffer[ocnt] = '\0';
		
		/* Otherwise it's probably a checksum */
		buf[0] = ser_getch();
		buf[1] = ser_getch();
		buf[2] = '\0';
		xmitcsum = strtol(buf, NULL, 16);

		/* If it doesn't match, try again */
		if (xmitcsum != (checksum & 0xff)) {
			ser_putch('-');
			continue;
		} else {
			ser_putch('+');
			// DEBUG("Received packet: %s\n", buffer);
			return;
		}
	}
}



/* Connect to the remote host */
int sc_connect_to_remote() {
	char buffer[256];
	
	ser_putch('+');			/* Acknowledge any signal packets */
	sc_packet_send("?");		/* Ask for what happened */
	sc_packet_recv(buffer, 256);	/* Get the init packet */
	
	return 0;
}


/* Request memory read */
int sc_read_memory(int address, int len, char *buffer) {
	char packet[64], *memhex;
	int i;
	
	/* Request memory read */
	sprintf(packet, "m%08x,%04x", address, len);
	sc_packet_send(packet);
	
	/* Process the returned info (+10 is just to make sure) */
	memhex = malloc(len*2 + 10);
	sc_packet_recv(memhex, len*2 + 10);
	
	for (i=0; i<len; i++) {
		char mini[3] = {0};
		int v;
		mini[0] = memhex[i*2+0];
		mini[1] = memhex[i*2+1];
		v = strtol(mini, NULL, 16);
		buffer[i] = v;
	}

	free(memhex);
	
	return 0;
}


/* Request memory write */
void sc_write_memory(int address, int len, char *buffer) {
	/* Construct a write packet */
	char *packet = malloc(1+8+1+4+1+2*len+10);
	int i;
	
	sprintf(packet, "M%08x,%04x:", address, len);
	for (i=0; i<len; i++) {
		unsigned char rb = buffer[i];
		sprintf(packet+1+8+1+4+1+i*2, "%02x", (int)rb);
	}
	sc_packet_send(packet);
	
	/* Check the return status */
	sc_packet_recv(packet, 10);
	if (strcmp(packet, "OK")) {
		DEBUG("error writing memory location: %s\n", packet);
	}
	
	free(packet);
}





