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

#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#define CMD_EXIT     "DC00"
#define CMD_FSTAT    "DC01"
#define CMD_WRITE    "DD02"
#define CMD_READ     "DC03"
#define CMD_OPEN     "DC04"
#define CMD_CLOSE    "DC05"
#define CMD_CREAT    "DC06"
#define CMD_LINK     "DC07"
#define CMD_UNLINK   "DC08"
#define CMD_CHDIR    "DC09"
#define CMD_CHMOD    "DC10"
#define CMD_LSEEK    "DC11"
#define CMD_TIME     "DC12"
#define CMD_STAT     "DC13"
#define CMD_UTIME    "DC14"
#define CMD_BAD      "DC15"
#define CMD_OPENDIR  "DC16"
#define CMD_CLOSEDIR "DC17"
#define CMD_READDIR  "DC18"
#define CMD_CDFSREAD "DC19"
#define CMD_GDBPACKET "DC20"

extern unsigned int syscall_retval;
extern unsigned char* syscall_data;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int value0 __attribute__ ((packed));
  unsigned int value1 __attribute__ ((packed));
  unsigned int value2 __attribute__ ((packed));
} command_3int_t;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int value0 __attribute__ ((packed));
  unsigned int value1 __attribute__ ((packed));
  unsigned char string[1] __attribute__ ((packed));
} command_2int_string_t;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int value0 __attribute__ ((packed));
} command_int_t;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int value0 __attribute__ ((packed));
  unsigned char string[1] __attribute__ ((packed));
} command_int_string_t;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned char string[1] __attribute__ ((packed));
} command_string_t;

typedef struct {
  unsigned char id[4] __attribute__ ((packed));
  unsigned int value0 __attribute__ ((packed));
  unsigned int value1 __attribute__ ((packed));
  unsigned int value2 __attribute__ ((packed));
  unsigned char string[1] __attribute__ ((packed));
} command_3int_string_t;

void build_send_packet(int command_len);

#endif
