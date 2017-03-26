/* 
 * This file is part of the dcload Dreamcast ethernet loader
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

#define TARGET1 (unsigned int *)0x8c004000
#define TARGET2 (unsigned int *)0x8c00f400

extern void disable_cache(void);

extern unsigned int binary_dcload_bin_start;
extern unsigned int binary_dcload_bin_size;
extern unsigned int binary_exception_bin_start;
extern unsigned int binary_exception_bin_size;

int main(void)
{
    memcpy(TARGET1, &binary_dcload_bin_start, &binary_dcload_bin_size);
    memcpy(TARGET2, &binary_exception_bin_start, &binary_exception_bin_size);

    disable_cache();
    (*(void (*)()) 0x8c004000) ();

}
