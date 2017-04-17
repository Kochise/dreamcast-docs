/* 
 * dcload, a Dreamcast serial loader
 *
 * Copyright (C) 2001 Andrew Kieschnick <andrewk@napalm-x.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "scif.h"
#include "minilzo.h"
#include "video.h"

#define NAME "dcload-serial 1.0.4"

#define VIDMODEREG (volatile unsigned int *)0xa05f8044
#define VIDBORDER (volatile unsigned int *)0xa05f8040

extern void disable_cache(void);
extern void go(unsigned int addr);
extern void cdfs_redir_save(void);
extern void cdfs_redir_disable(void);
extern void cdfs_redir_enable(void);

/* buffer for storing compressed data (16384 + 16384 / 64 + 16 + 3 bytes) */
unsigned char *buffer = (unsigned char *) 0x8c009f6c;

/* work memory for compressing data (65536 bytes) */
unsigned char *wrkmem = 0;

#define BOOTED        1
#define NOT_BOOTED   -1
#define IS(a)        ((a) == BOOTED)
#define IS_NOT(a)    ((a) == NOT_BOOTED)
unsigned int booted = NOT_BOOTED;

void assign_wrkmem(unsigned char *user_buffer)
{
    wrkmem = user_buffer;
}

/* converts expevt value to description, used by exception handler */
unsigned char * exception_code_to_string(unsigned int expevt)
{
    switch(expevt) {
    case 0x1e0:
	return "User break";
	break;
    case 0x0e0:
	return "Address error (read)";
	break;
    case 0x040:
	return "TLB miss exception (read)";
	break;
    case 0x0a0:
	return "TLB protection violation exception (read)";
	break;
    case 0x180:
	return "General illegal instruction exception";
	break;
    case 0x1a0:
	return "Slot illegal instruction exception";
	break;
    case 0x800:
	return "General FPU disable exception";
	break;
    case 0x820:
	return "Slot FPU disable exception";
	break;
    case 0x100:
	return "Address error (write)";
	break;
    case 0x060:
	return "TLB miss exception (write)";
	break;
    case 0x0c0:
	return "TLB protection violation exception (write)";
	break;
    case 0x120:
	return "FPU exception";
	break;
    case 0x080:
	return "Initial page write exception";
	break;
    case 0x160:
	return "Unconditional trap (TRAPA)";
	break;
    default:
	return "Unknown exception";
	break;
    }
}

void uint_to_string(unsigned int foo, unsigned char *bar)
{
    char hexdigit[16] = "0123456789abcdef";
    int i;

    for(i=7; i>=0; i--) {
	bar[i] = hexdigit[(foo & 0x0f)];
	foo = foo >> 4;
    }
    bar[8] = 0;
}

void put_uint(unsigned int val)
{
    scif_putchar(val & 0xff);
    scif_putchar((val >> 8) & 0xff);
    scif_putchar((val >> 16) & 0xff);
    scif_putchar((val >> 24) & 0xff);
}

/* set n lines starting at line y to value c */
void clear_lines(unsigned int y, unsigned int n, unsigned int c)
{
    memset((unsigned int *)0xa5000000 + y * 640 / 2, c, n * 640 * 2);
}

/* get an unsigned int from pc */
unsigned int get_uint(void)
{
    unsigned int retval;

    retval = 0;
    retval += (scif_getchar()) << 24;
    retval >>= 8;
    retval += (scif_getchar()) << 24;
    retval >>= 8;
    retval += (scif_getchar()) << 24;
    retval >>= 8;
    retval += (scif_getchar()) << 24;

    scif_putchar(retval & 0xff);
    scif_putchar((retval >> 8) & 0xff);
    scif_putchar((retval >> 16) & 0xff);
    scif_putchar((retval >> 24) & 0xff);

    return retval;
}

/* send an uncompressed data block to the pc from addr */
unsigned int
send_data_block_uncompressed(unsigned char * addr, unsigned int size)
{
    unsigned int i;
    unsigned char *location = addr;
    unsigned char sum = 0;
    unsigned char data;

    scif_putchar('U');
    put_uint(size);

    for (i = 0; i < size; i++) {
	data = *(location++);
	scif_putchar(data);
	sum ^= data;
    }

    scif_putchar(sum);
    data = scif_getchar();

    if (data == 'G')
	return 1;
    else
	return 0;

}

/* send a compressed data block to the pc from addr
 * falls back to uncompressed if compression unavailable or not beneficial
 */
unsigned int
send_data_block_compressed(unsigned char * addr, unsigned int size)
{
    unsigned int i;
    unsigned char *location = addr;
    unsigned char sum = 0;
    unsigned char data;
    unsigned int csize;
    unsigned int sendsize;

    /* send uncompressed if no work memory provided */
    if (!wrkmem)
	return(send_data_block_uncompressed(addr, size));

    /* send uncompressed if too small to bother with */
    if (size < 19)
	return(send_data_block_uncompressed(addr, size));
	
    while (size) {
	if (size > 8192)
	    sendsize = 8192;
	else
	    sendsize = size;
	lzo1x_1_compress(addr, sendsize, buffer, &csize, wrkmem);
	if (csize < sendsize) {
	    /* send compressed */
	    scif_putchar('C');
	    put_uint(csize);
	    data = 'B';
	    while(data != 'G') {
		location = buffer;
		for (i = 0; i < csize; i++) {
		    data = *(location++);
		    scif_putchar(data);
		    sum ^= data;
		}
		
		scif_putchar(sum);
		data = scif_getchar();
	    }
	} else {
	    /* send uncompressed */
	    while(!(send_data_block_uncompressed(addr, sendsize)));
	}
	size -= sendsize;
	addr += sendsize;
    }
    return 1;
}

void draw_progress(unsigned int current, unsigned int total)
{
    unsigned char current_string[9];
    unsigned char total_string[9];

    uint_to_string(total, total_string);
    uint_to_string(current, current_string);
    clear_lines(72, 24, 0);
    draw_string(0, 72, "(", 0xffff);
    draw_string(12, 72, current_string, 0xffff);
    draw_string(108, 72, "/", 0xffff);
    draw_string(120, 72, total_string, 0xffff);
    draw_string(216, 72, ")", 0xffff);
}

void
load_data_block_general(unsigned char * addr, unsigned int total, unsigned int verbose)
{
    unsigned char type, sum, ok;
    unsigned int size, newsize, realtotal;
    unsigned char *tmp = buffer;
    int i;
    unsigned char *data = addr;

    if (verbose)
	realtotal = total;
    
    while (total) {

	if (verbose)
	    draw_progress(realtotal - total, realtotal);
	
	type = scif_getchar();
	
	size = get_uint();
	
        switch (type) {
        case 'U':               /* uncompressed */
	    for(i=0; i<size; i++)
		*(data++) = scif_getchar();
	    sum = scif_getchar();
	    scif_putchar('G');
            total -= size;
            break;
        case 'C':               /* compressed */
	    for(i=0; i<size; i++)
		tmp[i] = scif_getchar();
	    sum = scif_getchar();
            if (lzo1x_decompress(tmp, size, data, &newsize, 0) == LZO_E_OK) {
                ok = 'G';
		scif_putchar(ok);
                total -= newsize;
                (unsigned char *) data += newsize;
            } else {
                ok = 'B';
		scif_putchar(ok);
            }
            break;
        default:
            break;
        }
    }
    if (verbose)
	draw_progress(realtotal - total, realtotal);
}

void setup_video(unsigned int mode, unsigned int color)
{
    init_video(check_cable(), mode);
    clrscr(color);
}

int main(void)
{
    unsigned char crap;
    unsigned int addr;
    unsigned int size;
    unsigned int console;
    unsigned int start;

    scif_init(SERIALSPEED);

    cdfs_redir_save(); /* will only save value once */
    cdfs_redir_disable();

    if (IS_NOT(booted)) {
	setup_video(0,0);
	draw_string(0, 24, NAME, 0xffff);
	booted = BOOTED;
    } else {
	booted = NOT_BOOTED;
    }

    lzo_init();

    wrkmem = 0;

    while (1) {
	*VIDBORDER = 0x00ffffff;
	if (IS(booted)) {
	    clear_lines(48, 24, 0);
	    draw_string(0, 48, "idle...", 0xffff);
	}

	crap = scif_getchar();
	scif_putchar(crap);

	switch(crap) {
	case 'A': /* execute */
	    if (IS_NOT(booted)) {
		setup_video(0,0);
		draw_string(0, 24, NAME, 0xffff);
		booted = BOOTED;
	    }
	    clear_lines(48, 24, 0);
	    draw_string(0, 48, "executing...", 0xffff);
	    addr = get_uint();
	    console = get_uint();
	    
	    if (console)
		*(unsigned int *)0x8c004004 = 0xdeadbeef; /* enable console */
	    else
		*(unsigned int *)0x8c004004 = 0xfeedface; /* disable console */
	    
	    scif_flush();
	    disable_cache();
	    go(addr);
	    break;
	case 'B': /* load binary */
	    if (IS_NOT(booted)) {
		setup_video(0,0);
		draw_string(0, 24, NAME, 0xffff);
		booted = BOOTED;
	    }
	    clear_lines(48, 24, 0);
	    draw_string(0, 48, "receiving data...",
			0xffffffff);
	    addr = get_uint();
	    size = get_uint();
	    load_data_block_general((unsigned char *)addr, size, 1);
	    break;
	case 'D': /* send uncompressed binary */
	    if (IS_NOT(booted)) {
		setup_video(0,0);
		draw_string(0, 24, NAME, 0xffff);
		booted = BOOTED;
	    }
	    clear_lines(48, 24, 0);
	    draw_string(0, 48, "sending uncompressed data...",
			0xffffffff);
	case 'E': /* send uncompressed binary, don't write to screen */
	    addr = get_uint();
	    size = get_uint();
	    send_data_block_uncompressed((unsigned char *)addr, size);
	    break;
	case 'F': /* send compressed binary */
	    if (IS_NOT(booted)) {
		setup_video(0,0);
		draw_string(0, 24, NAME, 0xffff);
		booted = BOOTED;
	    }
	    clear_lines(48, 24, 0);
	    draw_string(0, 48, "sending compressed data...",
			0xffffffff);
	case 'G': /* send compressed binary, don't write to screen */
	    addr = get_uint();
	    size = get_uint();
	    wrkmem = (unsigned char *)get_uint();
	    send_data_block_compressed((unsigned char *)addr, size);
	    wrkmem = 0;
	    break;
	case 'H': /* enable cdfs redir */
	    cdfs_redir_enable();
	    break;
	case 'S': /* change serial speed */
	    addr = get_uint();
	    scif_flush();
	    scif_init(addr);
	    addr = get_uint();
	    put_uint(addr);
	    break;
	case 'V': /* version */
	    scif_puts(NAME);
	    scif_puts("\n");
	    break;
	default:
	    scif_init(SERIALSPEED);
	    break;
	}
    }
}
