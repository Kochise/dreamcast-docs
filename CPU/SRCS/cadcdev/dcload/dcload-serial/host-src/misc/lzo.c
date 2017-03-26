/* 
 * This file is part of the dcload Dreamcast serial loader
 *
 * Andrew Kieschnick <andrewk@napalm-x.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilzo.h"

#define HEAP_ALLOC(var,size) \
        long __LZO_MMODEL var [ ((size) + (sizeof(long) - 1)) / sizeof(long) ]

static HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);

void usage(void)
{
        printf("usage: lzo <in> <out>\n");
	exit(1);
}

int main(int argc, char *argv[])
{
        int in, out;
	unsigned char * data;
	unsigned char * cdata;
	int r;
	unsigned int length,clength;

        if (argc != 3)
                usage();

        in = open(argv[1], O_RDONLY);

        if (in < 0) {
                perror(argv[1]);
                exit(1);
        }

        out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (out < 0) {
                perror(argv[2]);
                exit(1);
        }

        length = lseek(in, 0, SEEK_END);
        lseek(in, 0, SEEK_SET);

	data = malloc(length);
	cdata = malloc(length+length/64 + 16 + 3);

	read(in, data, length);

	if (lzo_init() != LZO_E_OK)
        {
                printf("lzo_init() failed !!!\n");
                exit(1);
        }
	
	r = lzo1x_1_compress(data,length,cdata,&clength,wrkmem);
        if (r == LZO_E_OK)
                printf("compressed %lu bytes into %lu bytes\n",
		       (long) length, (long) clength);
        else
        {
                /* this should NEVER happen */
                printf("internal error - compression failed: %d\n", r);
                return 2;
        }
        /* check for an incompressible block */
        if (clength >= length)
        {
                printf("This block contains incompressible data.\n");
                return 0;
        }

	write(out, cdata, clength);

	close(in);
	close(out);
	exit(0);
}

