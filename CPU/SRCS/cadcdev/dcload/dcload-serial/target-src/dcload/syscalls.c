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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <stdarg.h>
#include <dirent.h>
#include "scif.h"

extern void load_data_block_general(unsigned char *addr,
					 unsigned int size, unsigned int verbose);
extern unsigned int send_data_block_compressed(unsigned char * addr,
					       unsigned int size);
extern unsigned int get_uint(void);

extern int put_uint(unsigned int val);

int strlen(const char *s)
{
    int c = 0;

    while (s[c] != 0)
	c++;
    return c;
}

void dcexit(void)
{
    scif_putchar(0);
    scif_flush();
}

int read(int fd, void *buf, size_t count)
{
    scif_putchar(3);
    put_uint(fd);
    put_uint(count);
    load_data_block_general(buf, count, 0);
    return (get_uint());
}

int write(int fd, const void *buf, size_t count)
{
    scif_putchar(2);
    put_uint(fd);
    put_uint(count);
    send_data_block_compressed(buf, count);
    return (get_uint());
}

int open(const char *pathname, int flags, ...)
{
    va_list ap;
    int namelen = strlen(pathname) + 1;

    va_start(ap, flags);
    scif_putchar(4);
    put_uint(namelen);
    send_data_block_compressed(pathname, namelen);
    put_uint(flags);
    put_uint(va_arg(ap, int));
    va_end(ap);
    return (get_uint());
}

int close(int fd)
{
    scif_putchar(5);

    put_uint(fd);
    return (get_uint());
}

int creat(const char *pathname, mode_t mode)
{
    int namelen = strlen(pathname) + 1;

    scif_putchar(6);
    put_uint(namelen);
    send_data_block_compressed(pathname, namelen);
    put_uint(mode);
    return (get_uint());
}

int link(const char *oldpath, const char *newpath)
{
    int namelen1 = strlen(oldpath) + 1;
    int namelen2 = strlen(newpath) + 1;

    scif_putchar(7);
    put_uint(namelen1);
    send_data_block_compressed(oldpath, namelen1);
    put_uint(namelen2);
    send_data_block_compressed(newpath, namelen2);
    return (get_uint());
}

int unlink(const char *pathname)
{
    int namelen = strlen(pathname) + 1;

    scif_putchar(8);
    put_uint(namelen);
    send_data_block_compressed(pathname, namelen);
    return (get_uint());
}

int chdir(const char *path)
{
    int namelen = strlen(path) + 1;

    scif_putchar(9);
    put_uint(namelen);
    send_data_block_compressed(path, namelen);
    return (get_uint());
}

int chmod(const char *path, mode_t mode)
{
    int namelen = strlen(path) + 1;

    scif_putchar(10);
    put_uint(namelen);
    send_data_block_compressed(path, namelen);
    put_uint(mode);
    return (get_uint());
}

off_t lseek(int fildes, off_t offset, int whence)
{
    scif_putchar(11);
    put_uint(fildes);
    put_uint(offset);
    put_uint(whence);
    return (get_uint());
}

int fstat(int filedes, struct stat *buf)
{
    scif_putchar(1);
    put_uint(filedes);

    buf->st_dev = get_uint();
    buf->st_ino = get_uint();
    buf->st_mode = get_uint();
    buf->st_nlink = get_uint();
    buf->st_uid = get_uint();
    buf->st_gid = get_uint();
    buf->st_rdev = get_uint();
    buf->st_size = get_uint();
    buf->st_blksize = get_uint();
    buf->st_blocks = get_uint();
    buf->st_atime = get_uint();
    buf->st_mtime = get_uint();
    buf->st_ctime = get_uint();

    return (get_uint());
}

time_t time(time_t * t)
{
    scif_putchar(12);

    if (t) {
	*t = get_uint();
	return *t;
    }
    return (get_uint());
}

int stat(const char *file_name, struct stat *buf)
{
    int namelen = strlen(file_name) + 1;

    scif_putchar(13);
    put_uint(namelen);
    send_data_block_compressed(file_name, namelen);

    buf->st_dev = get_uint();
    buf->st_ino = get_uint();
    buf->st_mode = get_uint();
    buf->st_nlink = get_uint();
    buf->st_uid = get_uint();
    buf->st_gid = get_uint();
    buf->st_rdev = get_uint();
    buf->st_size = get_uint();
    buf->st_blksize = get_uint();
    buf->st_blocks = get_uint();
    buf->st_atime = get_uint();
    buf->st_mtime = get_uint();
    buf->st_ctime = get_uint();

    return (get_uint());
}

int utime(const char *filename, struct utimbuf *buf)
{
    int namelen = strlen(filename) + 1;

    scif_putchar(14);
    put_uint(namelen);
    send_data_block_compressed(filename, namelen);
    if (buf) {
	put_uint(1);
	put_uint(buf->actime);
	put_uint(buf->modtime);
	return (get_uint());
    }
    put_uint(0);
    return (get_uint());
}

DIR * opendir(const char *name)
{
    int namelen = strlen(name) + 1;

    scif_putchar(16);
    put_uint(namelen);
    send_data_block_compressed(name, namelen);
    return(get_uint());
}

int closedir(DIR *dir)
{
    scif_putchar(17);
    put_uint(dir);
    return(get_uint());
}
 
struct dirent *readdir(DIR *dir)
{
    static struct dirent ourdirent;
    int namelen;

    scif_putchar(18);
    
    put_uint(dir);

    if (get_uint()) {
	ourdirent.d_ino = get_uint();
	ourdirent.d_off = get_uint();
	ourdirent.d_reclen = get_uint();
	ourdirent.d_type = get_uint();
	namelen = get_uint();
	load_data_block_general(ourdirent.d_name, namelen, 0);
	
	return &ourdirent;
    } else
	return 0;
}
	
size_t gdbpacket(const char *in_buf, unsigned int size_pack, char* out_buf)
{
    size_t in_size = size_pack >> 16, out_size = size_pack & 0xffff, ret_size;

    scif_putchar(20);

    put_uint(in_size);
    put_uint(out_size);

    if (in_size)
	send_data_block_compressed(in_buf, in_size);
    
    ret_size = get_uint();

    if (ret_size && ret_size <= out_size)
	load_data_block_general(out_buf, ret_size, 0);

    return ret_size;
}
