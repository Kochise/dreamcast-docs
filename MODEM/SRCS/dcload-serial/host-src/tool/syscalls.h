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

#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

void dc_fstat(void);
void dc_write(void);
void dc_read(void);
void dc_open(void);
void dc_close(void);
void dc_creat(void);
void dc_link(void);
void dc_unlink(void);
void dc_chdir(void);
void dc_chmod(void);
void dc_lseek(void);
void dc_time(void);
void dc_stat(void);
void dc_utime(void);

void dc_opendir(void);
void dc_readdir(void);
void dc_closedir(void);

void dc_cdfs_redir_read_sectors(int isofd);

void dc_gdbpacket(void);

#endif
