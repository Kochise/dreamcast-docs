/* KallistiOS ##version##

   flashrom.c
   Copyright (c)2003 Dan Potter
*/

/*

  This module implements the stuff enumerated in flashrom.h. 

  Writing to the flash is disabled by default. To re-enable it, uncomment
  the #define below.

  Thanks to Marcus Comstedt for the info about the flashrom and syscalls.

 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dc/flashrom.h>
#include <arch/irq.h>

CVSID("$Id: flashrom.c,v 1.4 2003/03/10 01:45:31 bardtx Exp $");

/* This is the fateful define. Re-enable this at the peril of your
   Dreamcast's soul ;) */
/* #define ENABLE_WRITES 1 */


/* First, implementation of the syscall wrappers. */

int flashrom_info(int part, int * start_out, int * size_out) {
	int	(*sc)(int, uint32*, int, int);
	uint32	ptrs[2];
	int	rv;

	*((uint32 *)&sc) = *((uint32 *)0x8c0000b8);
	if (sc(part, ptrs, 0, 0) == 0) {
		*start_out = ptrs[0];
		*size_out = ptrs[1];
		rv = 0;
	} else
		rv = -1;
	return rv;
}

int flashrom_read(int offset, void * buffer_out, int bytes) {
	int	(*sc)(int, void*, int, int);
	int	rv;

	*((uint32 *)&sc) = *((uint32 *)0x8c0000b8);
	rv = sc(offset, buffer_out, bytes, 1);
	return rv;
}

int flashrom_write(int offset, void * buffer, int bytes) {
#ifdef ENABLE_WRITES
	int	(*sc)(int, void*, int, int);
	int	old, rv;

	old = irq_disable();
	*((uint32 *)&sc) = *((uint32 *)0x8c0000b8);
	rv = sc(offset, buffer, bytes, 2);
	irq_restore(old);
	return rv;
#else
	return -1;
#endif
}

int flashrom_delete(int offset) {
#ifdef ENABLE_WRITES
	int	(*sc)(int, int, int, int);
	int	old, rv;

	old = irq_disable();
	*((uint32 *)&sc) = *((uint32 *)0x8c0000b8);
	rv = sc(offset, 0, 0, 3);
	irq_restore(old);
	return rv;
#else
	return -1;
#endif
}



/* Higher level stuff follows */

/* Internal function calculates the checksum of a flashrom block. Thanks
   to Marcus Comstedt for this code. */
static int flashrom_calc_crc(uint8 * buffer) {
	int i, c, n = 0xffff;

	for (i=0; i<62; i++) {
		n ^= buffer[i] << 8;
		for (c=0; c<8; c++) {
			if (n & 0x8000)
				n = (n << 1) ^ 4129;
			else
				n = (n << 1);
		}
	}

	return (~n) & 0xffff;
}


int flashrom_get_block(int partid, int blockid, uint8 * buffer_out) {
	int	start, size;
	int	bmcnt;
	char	magic[18];
	uint8	* bitmap;
	int	i, rv;

	/* First, figure out where the partition is located. */
	if (flashrom_info(partid, &start, &size) < 0)
		return -2;

	/* Verify the partition */
	if (flashrom_read(start, magic, 18) < 0) {
		dbglog(DBG_ERROR, "flashrom_get_block: can't read part %d magic\n", partid);
		return -3;
	}
	if (strncmp(magic, "KATANA_FLASH____", 16) || *((uint16*)(magic+16)) != partid) {
		bmcnt = *((uint16*)(magic+16));
		magic[16] = 0;
		dbglog(DBG_ERROR, "flashrom_get_block: invalid magic '%s' or id %d in part %d\n", magic, bmcnt, partid);
		return -4;
	}

	/* We need one bit per 64 bytes of partition size. Figure out how
	   many blocks we have in this partition (number of bits needed). */
	bmcnt = size / 64;

	/* Round it to an even 64-bytes (64*8 bits). */
	bmcnt = (bmcnt + (64*8)-1) & ~(64*8 - 1);

	/* Divide that by 8 to get the number of bytes from the end of the
	   partition that the bitmap will be located. */
	bmcnt = bmcnt / 8;

	/* This is messy but simple and safe... */
	if (bmcnt > 65536) {
		dbglog(DBG_ERROR, "flashrom_get_block: bogus part %p/%d\n", (void *)start, size);
		return -5;
	}
	bitmap = (uint8 *)malloc(bmcnt);

	if (flashrom_read(start+size-bmcnt, bitmap, bmcnt) < 0) {
		dbglog(DBG_ERROR, "flashrom_get_block: can't read part %d bitmap\n", partid);
		rv = -6; goto ex;
	}

	/* Go through all the allocated blocks, and look for the latest one
	   that has a matching logical block ID. We'll start at the end since
	   that's easiest to deal with. Block 0 is the magic block, so we
	   won't check that. */
	for (i=0; i<bmcnt*8; i++) {
		// Little shortcut
		if (bitmap[i / 8] == 0)
			i += 8;
		
		if (bitmap[i / 8] & (0x80 >> (i % 8)))
			break;
	}

	/* All blocks unused -> file not found. Note that this is probably
	   a very unusual condition. */
	if (i == 0) {
		rv = -1; goto ex;
	}

	i--;	/* 'i' was the first unused block, so back up one */
	for ( ; i>0; i--) {
		/* Read the block; +1 because bitmap block zero is actually
		   _user_ block zero, which is physical block 1. */
		if (flashrom_read(start+(i+1)*64, buffer_out, 64) < 0) {
			dbglog(DBG_ERROR, "flashrom_get_block: can't read part %d phys block %d\n", partid, i+1);
			rv = -6; goto ex;
		}

		/* Does the block ID match? */
		if (*((uint16*)buffer_out) != blockid)
			continue;

		/* Check the checksum to make sure it's valid */
		bmcnt = flashrom_calc_crc(buffer_out);
		if (bmcnt != *((uint16*)(buffer_out+62))) {
			dbglog(DBG_WARNING, "flashrom_get_block: part %d phys block %d has invalid checksum %04x (should be %04x)\n",
				partid, i+1, *((uint16*)(buffer_out+62)), bmcnt);
			continue;
		}

		/* Ok, looks like we got it! */
		rv = 0; goto ex;
	}

	/* Didn't find anything */
	rv = -1;
	
ex:
	free(bitmap);
	return rv;
}

/* This internal function returns the system config block. As far as I
   can determine, this is always partition 2, logical block 5. */
static int flashrom_load_syscfg(uint8 * buffer) {
	return flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_SYSCFG, buffer);
}

/* Structure of the system config block (as much as we know anyway). */
typedef struct {
	uint16	block_id;	/* Should be 5 */
	uint8	date[4];	/* Last set time (secs since 1/1/1950 in LE) */
	uint8	unk1;		/* Unknown */
	uint8	lang;		/* Language ID */
	uint8	mono;		/* Mono/stereo setting */
	uint8	autostart;	/* Auto-start setting */
	uint8	unk2[4];	/* Unknown */
	uint8	padding[50];	/* Should generally be all 0xff */
} syscfg_t;

int flashrom_get_syscfg(flashrom_syscfg_t * out) {
	uint8 buffer[64];
	syscfg_t *sc = (syscfg_t *)buffer;

	/* Get the system config block */
	if (flashrom_load_syscfg(buffer) < 0)
		return -1;

	/* Fill in values from it */
	out->language = sc->lang;
	out->audio = sc->mono == 1 ? 0 : 1;
	out->autostart = sc->autostart == 1 ? 0 : 1;

	return 0;
}

int flashrom_get_region() {
	int start, size;
	char region[6] = { 0 };

	/* Find the partition */
	if (flashrom_info(FLASHROM_PT_SYSTEM, &start, &size) < 0) {
		dbglog(DBG_ERROR, "flashrom_get_region: can't find partition 0\n");
		return -1;
	}

	/* Read the first 5 characters of that partition */
	if (flashrom_read(start, region, 5) < 0) {
		dbglog(DBG_ERROR, "flashrom_get_region: can't read partition 0\n");
		return -1;
	}

	/* Now compare against known codes */
	if (!strcmp(region, "00000"))
		return FLASHROM_REGION_JAPAN;
	else if (!strcmp(region, "00110"))
		return FLASHROM_REGION_US;
	else if (!strcmp(region, "00211"))
		return FLASHROM_REGION_EUROPE;
	else {
		dbglog(DBG_WARNING, "flashrom_get_region: unknown code '%s'\n", region);
		return FLASHROM_REGION_UNKNOWN;
	}
}

/* Structure of the ISP config blocks (as much as we know anyway). 
   Thanks to Sam Steele for this info. */
typedef struct {
	union {
		struct {
			// Block 0xE0
			uint16	blockid;	// Should be 0xE0
			uint8	prodname[4];	// SEGA
			uint8	unk1;		// 0x13
			uint8	method;
			uint8	unk2[2];	// 0x00 0x00
			uint8	ip[4];		// These are all in big-endian notation
			uint8	nm[4];
			uint8	bc[4];
			uint8	dns1[4];
			uint8	dns2[4];
			uint8	gw[4];
			uint8	unk3[4];	// All zeros
			char	hostname[24];	// Host name
			uint16	crc;
		} e0;

		struct {
			// Block E2
			uint16	blockid;	// Should be 0xE2
			uint8	unk[12];
			char	email[48];
			uint16	crc;
		} e2;

		struct {
			// Block E4
			uint16	blockid;	// Should be 0xE4
			uint8	unk[32];
			char	smtp[28];
			uint16	crc;
		} e4;

		struct {
			// Block E5
			uint16	blockid;	// Should be 0xE5
			uint8	unk[36];
			char	pop3[24];
			uint16	crc;
		} e5;

		struct {
			// Block E6
			uint16	blockid;	// Should be 0xE6
			uint8	unk[40];
			char	pop3_login[20];
			uint16	crc;
		} e6;

		struct {
			// Block E7
			uint16	blockid;	// Should be 0xE7
			uint8	unk[12];
			char	pop3_passwd[32];
			char	proxy_host[16];
			uint16	crc;
		} e7;

		struct {
			// Block E8
			uint16	blockid;	// Should be 0xE8
			uint8	unk1[48];
			uint16	proxy_port;
			uint16	unk2;
			char	ppp_login[8];
			uint16	crc;
		} e8;

		struct {
			// Block E9
			uint16	blockid;	// Should be 0xE9
			uint8	unk[40];
			char	ppp_passwd[20];
			uint16	crc;
		} e9;
	};
} isp_settings_t;

int flashrom_get_ispcfg(flashrom_ispcfg_t * out) {
	uint8		buffer[64];
	isp_settings_t	* isp = (isp_settings_t *)buffer;
	int		found = 0;

	// Clean out the output config buffer.
	memset(out, 0, sizeof(flashrom_ispcfg_t));

	// Get the E0 config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_IP_SETTINGS, buffer) >= 0) {
		// Fill in values from it
		out->method = isp->e0.method;
		memcpy(out->ip, isp->e0.ip, 4);
		memcpy(out->nm, isp->e0.nm, 4);
		memcpy(out->bc, isp->e0.bc, 4);
		memcpy(out->gw, isp->e0.gw, 4);
		memcpy(out->dns[0], isp->e0.dns1, 4);
		memcpy(out->dns[1], isp->e0.dns2, 4);
		memcpy(out->hostname, isp->e0.hostname, 24);

		out->ip_valid = 1;
		found++;
	}

	// Get the email config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_EMAIL, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->email, isp->e2.email, 48);

		out->email_valid = 1;
		found++;
	}

	// Get the smtp config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_SMTP, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->smtp, isp->e4.smtp, 28);

		out->smtp_valid = 1;
		found++;
	}

	// Get the pop3 config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_POP3, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->pop3, isp->e5.pop3, 24);

		out->pop3_valid = 1;
		found++;
	}

	// Get the pop3 login config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_POP3LOGIN, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->pop3_login, isp->e6.pop3_login, 20);

		out->pop3_login_valid = 1;
		found++;
	}

	// Get the pop3 passwd config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_POP3PASSWD, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->pop3_passwd, isp->e7.pop3_passwd, 32);
		memcpy(out->proxy_host, isp->e7.proxy_host, 16);

		out->pop3_passwd_valid = 1;
		found++;
	}

	// Get the PPP login config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_PPPLOGIN, buffer) >= 0) {
		// Fill in the values from it
		out->proxy_port = isp->e8.proxy_port;
		memcpy(out->ppp_login, isp->e8.ppp_login, 8);

		out->ppp_login_valid = 1;
		found++;
	}

	// Get the PPP passwd config block
	if (flashrom_get_block(FLASHROM_PT_BLOCK_1, FLASHROM_B1_PPPPASSWD, buffer) >= 0) {
		// Fill in the values from it
		memcpy(out->ppp_passwd, isp->e9.ppp_passwd, 20);

		out->ppp_passwd_valid = 1;
		found++;
	}

	return found > 0 ? 0 : -1;
}
