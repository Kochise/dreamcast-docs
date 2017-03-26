/*
* This code is licenced under 
* the General Public Licence
* version 2
*
* Copyright Adrian McMenamin 2006
* <adrian@mcmen.demon.co.uk>
* See also http://newgolddream.dyndns.info/cgi-bin/cvsweb
* 
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of version 2 of the GNU General Public License as published by
* the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#ifndef _ASM_DREAMCAST_AICA
#define _ASM_DREAMCAST_AICA

#ifdef MACH_DREAMCAST
/* SPU memory and register constants etc */
#define G2_FIFO 0xa05f688c
#define AICA_MEMORY_BASE 0xA0800000
#define ARM_RESET_REGISTER 0xA0702C00
#define AICA_REGISTER_BASE 0xA0700000

/* AICA channels stuff */
#define AICA_CONTROL_POINT 0xA0810000
#define AICA_CONTROL_CHANNEL_SAMPLE_NUMBER 0xA0810008
#define AICA_MEMORY_SIZE 0x200000
#define AICA_CHANNEL0_CONTROL_OFFSET 0x10004
#endif

#endif

