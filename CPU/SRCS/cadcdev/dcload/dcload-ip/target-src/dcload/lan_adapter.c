/*
   DC "Lan Adapter" driver for dc-load-ip
   
   Copyright (C)2002,2003 Dan Potter (NEW BSD LICENSE)
 */

#include "packet.h"
#include "net.h"
#include "adapter.h"
#include "lan_adapter.h"
#include "dcload.h"

typedef volatile unsigned int vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char vuint8;

typedef unsigned char uint8;

/* Some basic macros to assist with register access */
#undef REGL
#undef REGS
#undef REGC
#define REGL(a) (vuint32 *)(a)
#define REGS(a) (vuint16 *)(a)
#define REGC(a) (vuint8 *)(a)

static vuint8 *xpc = REGC(0xa0600000);
static vuint16 *xps = REGS(0xa0600000);
static vuint32 *xpl = REGL(0xa0600000);
#define REG(x) ( xpl[(x) + 0x400/4] & 0xff )
#define REGW(x) ( xpc[(x)*4 + 0x400] )
	
/* This is based on the JLI EEPROM reader from FreeBSD. EEPROM in the
   Sega adapter is a bit simpler than what is described in the Fujitsu
   manual -- it appears to contain only the MAC address and not a base
   address like the manual says. EEPROM is read one bit (!) at a time
   through the EEPROM interface port. */
#define FE_B16_SELECT	0x20		/* EEPROM chip select */
#define FE_B16_CLOCK	0x40		/* EEPROM shift clock */
#define FE_B17_DATA	0x80		/* EEPROM data bit */
static void net_strobe_eeprom() {
	REGW(16) = FE_B16_SELECT;
	REGW(16) = FE_B16_SELECT | FE_B16_CLOCK;
	REGW(16) = FE_B16_SELECT | FE_B16_CLOCK;
	REGW(16) = FE_B16_SELECT;
}
static void net_read_eeprom(uint8 *data) {
	uint8 save16, save17, val;
	int n, bit;

	/* Save the current value of the EEPROM registers */
	save16 = REG(16);
	save17 = REG(17);

	/* Read bytes from EEPROM, two per iteration */
	for (n=0; n<3; n++) {
		/* Reset the EEPROM interface */
		REGW(16) = 0;
		REGW(17) = 0;

		/* Start EEPROM access */
		REGW(16) = FE_B16_SELECT;
		REGW(17) = FE_B17_DATA;
		net_strobe_eeprom();

		/* Pass the iteration count as well as a READ command */
		val = 0x80 | n;
		for (bit=0x80; bit != 0x00; bit>>=1) {
			REGW(17) = (val & bit) ? FE_B17_DATA : 0;
			net_strobe_eeprom();
		}
		REGW(17) = 0;

		/* Read a byte */
		val = 0;
		for (bit=0x80; bit != 0x00; bit>>=1) {
			net_strobe_eeprom();
			if (REG(17) & FE_B17_DATA)
				val |= bit;
		}
		*data++ = val;

		/* Read one more byte */
		val = 0;
		for (bit=0x80; bit != 0x00; bit>>=1) {
			net_strobe_eeprom();
			if (REG(17) & FE_B17_DATA)
				val |= bit;
		}
		*data++ = val;
	}
}

/* To select a register bank */
#define SETBANK(x) do { \
	int i = (REG(7) & ~0x0c) | ((x) << 2); \
	REGW(7) = i; \
} while(0)

static int bb_started = 0;

/* Libdream-style sleep function */
static void net_sleep_ms(int ms) {
	int i, j, cnt;
	vuint32 *a05f688c = (vuint32*)0xa05f688c;

	cnt = 0x1800 * 0x58e * ms / 1000;
	for (i=0; i<cnt; i++)
		(void)*a05f688c;
}

/* #define DEBUG(s) scif_puts(s) */
#define DEBUG(s)

/* Reset the lan adapter and verify that it's there and alive */
static int bb_detect() {
	int i, type;

	DEBUG("bb_detect entered\r\n");

	if (bb_started > 0) {
		DEBUG("bb_detect exited, already started\r\n");
		return 0;
	}

	if (bb_started != 0) {
		clear_lines(168, 24, 0);
		draw_string(30, 168, "bb_detect() called out of sequence!", 0xf800);
		for (;;)
			;
	}
	
	/* Reset the interface */
	xpc[0x0480] = 0;
	xpc[0x0480] = 1;
	xpc[0x0480] = 0;

	/* Give it a few ms to come back */
	net_sleep_ms(100);

	/* Read the chip type and verify it */
	type = (REG(7) >> 6) & 3;
	if (type != 2) {
		DEBUG("bb_detect exited, detection failed\r\n");
		return -1;
	}

	/* That should do */
	DEBUG("bb_detect exited, success\r\n");
	bb_started = 1;
	return 0;
}

/* Reset the lan adapter and set it up for send/receive */
static int bb_init() {
	int i, type;
	uint8 mac[6];

	DEBUG("bb_init started\r\n");

	if (bb_started == 2) {
		DEBUG("bb_init exited, already done\r\n");
		return 0;
	}
		
	if (bb_started == 0) {
		if (!bb_detect()) {
			DEBUG("bb_init exited, bb_detect() failed\r\n");
			return -1;
		}
	}
	
	/* Clear interrupt status */
	REGW(0) = 0xff;
	REGW(1) = 0xff;

	/* Power down chip */
	net_sleep_ms(2);
	REGW(7) = REG(7) & ~0x20;
	net_sleep_ms(2);

	/* Disable rx/tx */
	net_sleep_ms(2);
	REGW(6) = REG(6) | 0x80;
	net_sleep_ms(2);

	/* Power up the chip */
	net_sleep_ms(2);
	REGW(7) = REG(7) | 0x20;
	net_sleep_ms(2);

	/* Read the chip type */
	type = (REG(7) >> 6) & 3;
	if (type != 2) {
		DEBUG("bb_init exited, type check failed\r\n");
		return -1;
	}

	/* Read the EEPROM data */
	net_read_eeprom(mac);

	/* Select BANK0 and write the MAC address */
	SETBANK(0);
	net_sleep_ms(2);
	for (i=0; i<6; i++) {
		REGW(i+8) = mac[i];
	}

	/* Copy it into the adapter structure for dcload */
	memcpy(adapter_la.mac, mac, 6);
	
	/* Clear the multicast address */
	SETBANK(1);
	for (i=0; i<6; i++)
		REGW(i+8) = 0;

	/* Select the BMPR bank for normal operation */
	SETBANK(2);
	REGW(10) = 0;
	REGW(11) = 0x03;
	REGW(12) = 0;
	REGW(13) = 0;
	REGW(14) = 0;
	REGW(15) = 0xff;

	/* Set non-promiscuous mode (use 0x03 for promiscuous) */
	REGW(5) = (REG(5) | 0x02) & ~0x01;

	/* Enable transmitter / receiver */
	REGW(6) = REG(6) & ~0x80;

	DEBUG("bb_init exited, success\r\n");
	bb_started = 2;
	return 0;
}

/* Start lan adapter */
void bb_start() {
	DEBUG("bb_start entered\r\n");

	if (bb_started != 3) {
		DEBUG("bb_start exited, state != 3\r\n");
		return;
	}

	/* Set non-promiscuous mode (use 0x03 for promiscuous) */
	REGW(5) = (REG(5) | 0x02) & ~0x01;

	bb_started = 2;
	DEBUG("bb_start exited\r\n");
}

/* Stop lan adapter */
void bb_stop() {
	DEBUG("bb_stop entered\r\n");
	
	if (bb_started != 2) {
		DEBUG("bb_stop exited, state != 2\r\n");
		return;
	}

	/* Make sure we aren't transmitting currently */
	while (REG(10) & 0x7f)
		net_sleep_ms(2);

	/* Disable all receive */
	REGW(5) = (REG(5) & ~0x03);
	
	bb_started = 3;
	DEBUG("bb_stop exited\r\n");
}

static int total_pkts_rx = 0, total_pkts_tx = 0;

/* static void draw_total() {
	char buffer[16];

	uint_to_string(total_pkts_rx, buffer);
	clear_lines(120, 24, 0);
	draw_string(0, 120, "RX: ", 0xffe0);
	draw_string(4*12, 120, buffer, 0xffff);

	uint_to_string(total_pkts_tx, buffer);
	clear_lines(144, 24, 0);
	draw_string(0, 144, "TX: ", 0xffe0);
	draw_string(4*12, 144, buffer, 0xffff);
} */

/* Transmit a packet */
/* Note that it's technically possible to queue up more than one packet 
   at a time for transmission, but this is the simple way. */
static int bb_tx(unsigned char *pkt, int len) {
	int i;
	char buffer[16];

	DEBUG("bb_tx entered\r\n");

	if (bb_started != 2) {
		clear_lines(168, 24, 0);
		draw_string(30, 168, "bb_tx() called out of sequence!", 0xf800);
		for (;;)
			;
	}

	/* Wait for queue to empty */
	while (REG(10) & 0x7f)
		net_sleep_ms(2);

	/* clear_lines(192, 24, 0);
	uint_to_string(len, buffer);
	draw_string(0, 192, buffer, 0xffff); */

	/* Is the length less than the minimum? */
	if (len < 0x60)
		len = 0x60;

	/* Poke the length */
	REGW(8) = (len & 0x00ff);
	REGW(8) = (len & 0xff00) >> 8;

	/* Write the packet */
	for (i=0; i<len; i++)
		REGW(8) = pkt[i];

	/* Start the transmitter */
	net_sleep_ms(2);
	REGW(10) = 1 | 0x80;	/* 1 packet, 0x80 = start */

	total_pkts_tx++;
	/* if (!running)
		draw_total(); */

	DEBUG("bb_tx exited\r\n");
	return 1;
}

/* Check for received packets */
static int bb_rx() {
	int i, status, len, count;

	DEBUG("bb_rx entered\r\n");

	if (bb_started != 2) {
		clear_lines(168, 24, 0);
		draw_string(30, 168, "bb_rx() called out of sequence!", 0xf800);
		for (;;)
			;
	}
	
	for (count = 0; ; count++) {
		/* Is the buffer empty? */
		if (REG(5) & 0x40) {
			DEBUG("bb_rx exited, no more packets\r\n");
			return count;
		}

		/* Get the receive status byte */
		status = REG(8);
		(void)REG(8);

		/* Get the packet length */
		len = REG(8);
		len |= REG(8) << 8;

		/* Check for errors */
		if ( (status & 0xF0) != 0x20 ) {
			DEBUG("bb_rx exited: error\r\n");
			return -1;
		}

		/* Read the packet */
		if (len > 1514) {
			DEBUG("bb_rx exited: big packet\r\n");
			return -2;
		}
		for (i=0; i<len; i++) {
			current_pkt[i] = REG(8);
		}

		/* Submit it for processing */
		process_pkt(current_pkt, len);

		total_pkts_rx++;
		/* if (!running)
			draw_total(); */
	}

	return count;
}

/* Loop doing something interesting */
static void bb_loop() {
	int result;

	DEBUG("bb_loop entered\r\n");
		
	while (!escape_loop) {
		/* Check for received packets */
		result = bb_rx();
		if (result < 0 && !running) {
			clear_lines(320, 24, 0x0100);
			draw_string(30, 320, "receive error!", 0xffff);
		}
	}

	DEBUG("bb_loop exited\r\n");

	escape_loop = 0;
}

adapter_t adapter_la = {
	"Lan Adapter (HIT-0300)",
	{ 0 },		// Mac address
	bb_detect,
	bb_init,
	bb_start,
	bb_stop,
	bb_loop,
	bb_tx
};
