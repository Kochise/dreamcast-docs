/* 
 * This file is part of the dcload Dreamcast serial loader
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

extern void load_data_block_general(unsigned char *addr,
                                         unsigned int size, unsigned int verbose);
extern unsigned int send_data_block_compressed(unsigned char * addr,
                                               unsigned int size);
extern unsigned int get_uint(void);
extern int put_uint(unsigned int val);

int gdStatus;

struct TOC {
  unsigned int entry[99];
  unsigned int first, last;
  unsigned int dunno;
};

int gdGdcReqCmd(int cmd, int *param)
{
    struct TOC *toc;
    int i;

    switch (cmd) {
    case 16: /* read sectors */
	scif_putchar(19);
	put_uint(param[0]); /* starting sector */
	put_uint(param[1]); /* number of sectors */
	load_data_block_general((unsigned char *)param[2], param[1]*2048, 0);
	param[3] = 0;
	gdStatus = 2;
	return 0;
	break;
    case 19: /* read toc */
	toc = (struct TOC *)param[1];
	toc->entry[0] = 0x41000096; /* CTRL = 4, ADR = 1, LBA = 150 */
	for(i=1; i<99; i++)
	    toc->entry[i] = -1;
	toc->first = 0x41010000; /* first = track 1 */
	toc->last = 0x41010000; /* last = track 1 */
	gdStatus = 2;
	return 0;
	break;
    case 24: /* init disc */
	gdStatus = 2;
	return 0;
	break;
    default:
	gdStatus = 0;
	return -1;
	break;
    }

}

void gdGdcExecServer(void)
{
}

int gdGdcGetCmdStat(int f, int *status)
{
    if (gdStatus == 0)
	status[0] = 0;
    return gdStatus;
}

void gdGdcGetDrvStat(int *param)
{
    param[1] = 32;
}

int gdGdcChangeDataType(int *param)
{
    return 0;
}

void gdGdcInitSystem(void)
{
}

