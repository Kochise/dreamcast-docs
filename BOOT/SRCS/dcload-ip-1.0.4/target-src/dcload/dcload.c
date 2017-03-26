/* 
 * dcload, a Dreamcast ethernet loader
 *
 * Copyright (C) 2001 Andrew Kieschnick <andrewk@austin.rr.com>
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

/* uncomment following line to enable crappy screensaver (it just blanks) */
/* #define SCREENSAVER */

#include "scif.h"
#include "video.h"
#include "packet.h"
#include "commands.h"
#include "adapter.h"
#include "net.h"
#include "cdfs.h"

#define NAME "dcload-ip " DCLOAD_VERSION

#define VIDMODEREG (volatile unsigned int *)0xa05f8044
#define VIDBORDER (volatile unsigned int *)0xa05f8040

unsigned int booted = 0;
unsigned int running = 0;

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

void uchar_to_string(unsigned int foo, unsigned char *bar)
{
    char hexdigit[16] = "0123456789abcdef";
    int i;

    bar[1] = hexdigit[foo & 0x0f];
    bar[0] = hexdigit[foo >> 4];
}

/* set n lines starting at line y to value c */
void clear_lines(unsigned int y, unsigned int n, unsigned int c)
{
    unsigned short * vmem = (unsigned short *)(0xa5000000 + y*640*2);
    n = n * 640;
    while (n-- > 0)
    	*vmem++ = c;
}

void draw_progress(unsigned int current, unsigned int total)
{
    unsigned char current_string[9];
    unsigned char total_string[9];

    uint_to_string(total, total_string);
    uint_to_string(current, current_string);
    clear_lines(120, 24, 0x0100);
    draw_string(30, 174, "(", 0xffff);
    draw_string(42, 174, current_string, 0xffff);
    draw_string(138, 174, "/", 0xffff);
    draw_string(150, 174, total_string, 0xffff);
    draw_string(246, 174, ")", 0xffff);
}

void setup_video(unsigned int mode, unsigned int color)
{
    init_video(check_cable(), mode);
    clrscr(color);
}

void error_bb(unsigned char *msg)
{
    setup_video(0,0x2000);
    draw_string(30, 54, NAME, 0xffff);
    draw_string(30, 78, msg, 0xffff);
    while(1);
}

unsigned char *mac_string = "de:ad:be:ef:ba:be";
unsigned char *ip_string = "00.00.00.00";

void disp_info(void)
{
    int c;
    unsigned char *ip = (unsigned char *)&our_ip;

    setup_video(0,0x0100);
    draw_string(30, 54, NAME, 0xffff);
    draw_string(30, 78, bb->name, 0xffff);
    draw_string(30, 102, mac_string, 0xffff);
    for(c = 0; c < 4; c++)
	uchar_to_string(ip[3-c], &ip_string[c*3]);
    draw_string(30, 126, ip_string, 0xffff);
    booted = 1;
}

void disp_status(const char * status) {
    clear_lines(150, 24, 0x0100);
    draw_string(30, 150, status, 0xffff);
}

void set_ip(void)
{
    int i;
    int c;
    unsigned char *ip = (unsigned char *)&our_ip;

    i = 0;
    c = 0;
    
    while(DREAMCAST_IP[c] != 0) {
	if (DREAMCAST_IP[c] != '.') {
	    ip[i] *= 10;
	    ip[i] += DREAMCAST_IP[c] - '0';
	}
	else
	    i++;
	c++;
    }

    our_ip = ntohl(our_ip);

}


int main(void)
{
    unsigned char crap;
    unsigned int addr;
    unsigned int size;
    unsigned int console;
    unsigned int start;

    running = 0;

/*    scif_init(115200); */

    if (adapter_detect() < 0)
	error_bb("NO ETHERNET ADAPTER DETECTED!");

    for(start = 0; start < 6; start++)
      uchar_to_string(bb->mac[start], mac_string + start*3);

    set_ip();

    cdfs_redir_save(); /* will only save value once */
    cdfs_redir_disable();

    if (!booted) {
	disp_info();
    } else
	booted = 0;
/*
    scif_puts(NAME);
    scif_puts("\n");
*/
    while (1) {
	*VIDBORDER = 0;

	if (booted) {
	    disp_status("idle...");
	}

	bb->loop();
    }
}
