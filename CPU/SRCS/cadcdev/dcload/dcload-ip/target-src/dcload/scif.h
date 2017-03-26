/* 
 * This file is part of the dcload Dreamcast serial loader
 *
 * Copyright (C) 2000 Andrew Kieschnick <andrewk@austin.rr.com>
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

#ifndef __SCIF_H__
#define __SCIF_H__

/* serial mode register */
#define SCSMR2  (volatile unsigned short *) 0xffe80000

/* bit rate register */
#define SCBRR2  (volatile unsigned char *)  0xffe80004

/* serial control register */
#define SCSCR2  (volatile unsigned short *) 0xffe80008

/* transmit fifo data register */
#define SCFTDR2 (volatile unsigned char *)  0xffe8000c

/* serial status register */
#define SCFSR2  (volatile unsigned short *) 0xffe80010

/* receive fifo data register */
#define SCFRDR2 (volatile unsigned char *)  0xffe80014

/* fifo control register */
#define SCFCR2  (volatile unsigned short *) 0xffe80018

/* fifo data count register */
#define SCFDR2  (volatile unsigned short *) 0xffe8001c

/* serial port register */
#define SCSPTR2 (volatile unsigned short *) 0xffe80020

/* line status register */
#define SCLSR2  (volatile unsigned short *) 0xffe80024

void scif_flush(void);
void scif_init(int bps);
unsigned char scif_getchar(void);
unsigned int scif_isdata(void);
void scif_putchar(unsigned char foo);
void scif_puts(unsigned char *foo);

#endif
