/* 
 * This file is part of the dcload Dreamcast serial loader
 *
 * Copyright (C) 2001 Andrew Kieschnick <andrewk@napalm-xcom>
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

#include "minilzo.h"

extern char binary_dcload_lzo_start[];
extern char binary_exception_lzo_start[];
extern unsigned int binary_dcload_lzo_size[];
extern unsigned int binary_exception_lzo_size[];

#define TARGET1 (char *)0x8c004000
#define TARGET2 (char *)0x8c00f400

extern void disable_cache(void);

int main(void)
{
    unsigned int n;

    lzo_init();

    lzo1x_decompress(binary_dcload_lzo_start, binary_dcload_lzo_size, TARGET1, &n, 0);
    lzo1x_decompress(binary_exception_lzo_start, binary_exception_lzo_size, TARGET2, &n, 0);

    disable_cache();
    (*(void (*)()) 0x8c004000) ();
}
