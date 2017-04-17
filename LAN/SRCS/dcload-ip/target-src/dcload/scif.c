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

#include "scif.h"

#define BORDER_FLASH
#define VIDBORDER (volatile unsigned int *)0xa05f8040

void scif_flush()
{
    int v;

    *SCFSR2 &= 0xbf;
    while (!((v = *SCFSR2) & 0x40));
    *SCFSR2 = v & 0xbf;
}

void scif_init(int bps)
{
    int i;

    *SCSCR2 = 0x0;		/* clear TE and RE bits in SCSCR2 */
    *SCFCR2 = 0x6;		/* set TFRST and RFRST bits in SCFCR2 */
    *SCSMR2 = 0x0;		/* set data transfer format 8n1 */
    *SCBRR2 = (50 * 1000000) / (32 * bps) - 1;	/* set bit rate */

    for (i = 0; i < 100000; i++);	/* delay at least 1 bit interval */

    *SCFCR2 = 12;
    *SCFCR2 = 0x8;		/* set MCE in SCFCR2 */
    *SCSPTR2 = 0;
    *SCFSR2 = 0x60;
    *SCLSR2 = 0;
    *SCSCR2 = 0x30;		/* set TE and RE bits in SCSCR2 */

    for (i = 0; i < 100000; i++);
}

unsigned char scif_getchar(void)
{
    unsigned char foo;

#ifdef BORDER_FLASH
    *VIDBORDER = ~(*VIDBORDER & 0x00ffffff);
#endif

    while (!(*SCFSR2 & 0x2));	/* check RDF */
    foo = *SCFRDR2;		/* read data */
    *SCFSR2 &= 0xfffd;		/* clear RDF */
    return foo;

}

unsigned int scif_isdata(void)
{
    return (*SCFSR2 & 0x2);
}

void scif_putchar(unsigned char foo)
{

#ifdef BORDER_FLASH
    *VIDBORDER = ~(*VIDBORDER & 0x00ffffff);
#endif

    while (!(*SCFSR2 & 0x20));	/* check TDFE */
    *SCFTDR2 = foo;		/* send data */
    *SCFSR2 &= 0xff9f;		/* clear TDFE and TEND */
}

void scif_puts(unsigned char *foo)
{
    int i = 0;

    while (foo[i] != 0) {
	scif_putchar(foo[i]);
	if (foo[i] == '\n')
	    scif_putchar('\r');
	i++;
    }
}
