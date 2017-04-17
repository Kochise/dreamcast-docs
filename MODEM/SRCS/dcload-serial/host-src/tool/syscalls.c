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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <utime.h>
#include <dirent.h>
#include <arpa/inet.h>
#include "syscalls.h"
#include "dc-io.h"

#ifndef O_BINARY
#define O_BINARY 0
#endif

void dc_fstat(void)
{
    int filedes;
    struct stat filestat;
    int retval;

    filedes = recv_uint();

    retval = fstat(filedes, &filestat);

    send_uint(filestat.st_dev);
    send_uint(filestat.st_ino);
    send_uint(filestat.st_mode);
    send_uint(filestat.st_nlink);
    send_uint(filestat.st_uid);
    send_uint(filestat.st_gid);
    send_uint(filestat.st_rdev);
    send_uint(filestat.st_size);
    send_uint(filestat.st_blksize);
    send_uint(filestat.st_blocks);
    send_uint(filestat.st_atime);
    send_uint(filestat.st_mtime);
    send_uint(filestat.st_ctime);

    send_uint(retval);

}

void dc_write(void)
{
    int filedes;
    unsigned char *data;
    int retval;
    int count;

    filedes = recv_uint();
    count = recv_uint();

    data = malloc(count);
    recv_data(data, count, 0);

    retval = write(filedes, data, count);

    send_uint(retval);

    free(data);

}

void dc_read(void)
{
    int filedes;
    unsigned char *data;
    int retval;
    int count;

    filedes = recv_uint();
    count = recv_uint();

    data = malloc(count);
    retval = read(filedes, data, count);

    send_data(data, count, 0);

    send_uint(retval);

    free(data);
}

void dc_open(void)
{
    int namelen;
    unsigned char *pathname;
    int retval;
    int flags;
    int ourflags = 0;
    int mode;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    flags = recv_uint();
    mode = recv_uint();

    /* translate flags */

    if (flags & 0x0001)
	ourflags |= O_WRONLY;
    if (flags & 0x0002)
	ourflags |= O_RDWR;
    if (flags & 0x0008)
	ourflags |= O_APPEND;
    if (flags & 0x0200)
	ourflags |= O_CREAT;
    if (flags & 0x0400)
	ourflags |= O_TRUNC;
    if (flags & 0x0800)
	ourflags |= O_EXCL;

    retval = open(pathname, ourflags | O_BINARY, mode);

    send_uint(retval);

    free(pathname);
}

void dc_close(void)
{
    int filedes;
    int retval;

    filedes = recv_uint();

    retval = close(filedes);

    send_uint(retval);
}

void dc_creat(void)
{
    int namelen;
    unsigned char *pathname;
    int retval;
    int mode;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    mode = recv_uint();

    retval = creat(pathname, mode);

    send_uint(retval);

    free(pathname);
}

void dc_link(void)
{
    int namelen1, namelen2;
    unsigned char *pathname1, *pathname2;
    int retval;

    namelen1 = recv_uint();
    pathname1 = malloc(namelen1);

    recv_data(pathname1, namelen1, 0);

    namelen2 = recv_uint();
    pathname2 = malloc(namelen2);

    recv_data(pathname2, namelen2, 0);

    retval = link(pathname1, pathname2);

    send_uint(retval);

    free(pathname1);
    free(pathname2);
}

void dc_unlink(void)
{
    int namelen;
    unsigned char *pathname;
    int retval;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    retval = unlink(pathname);

    send_uint(retval);

    free(pathname);
}

void dc_chdir(void)
{
    int namelen;
    unsigned char *pathname;
    int retval;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    retval = chdir(pathname);

    send_uint(retval);

    free(pathname);
}

void dc_chmod(void)
{
    int namelen;
    unsigned char *pathname;
    int retval;
    int mode;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    mode = recv_uint();

    retval = chmod(pathname, mode);

    send_uint(retval);

    free(pathname);
}

void dc_lseek(void)
{
    int filedes;
    int offset;
    int whence;
    int retval;

    filedes = recv_uint();
    offset = recv_uint();
    whence = recv_uint();

    retval = lseek(filedes, offset, whence);

    send_uint(retval);
}

void dc_time(void)
{
    time_t t;

    time(&t);

    send_uint(t);
}

void dc_stat(void)
{
    int namelen;
    unsigned char *filename;
    struct stat filestat;
    int retval;

    namelen = recv_uint();

    filename = malloc(namelen);

    recv_data(filename, namelen, 0);

    retval = stat(filename, &filestat);

    send_uint(filestat.st_dev);
    send_uint(filestat.st_ino);
    send_uint(filestat.st_mode);
    send_uint(filestat.st_nlink);
    send_uint(filestat.st_uid);
    send_uint(filestat.st_gid);
    send_uint(filestat.st_rdev);
    send_uint(filestat.st_size);
    send_uint(filestat.st_blksize);
    send_uint(filestat.st_blocks);
    send_uint(filestat.st_atime);
    send_uint(filestat.st_mtime);
    send_uint(filestat.st_ctime);

    send_uint(retval);

    free(filename);
}

void dc_utime(void)
{
    unsigned char *pathname;
    int namelen;
    struct utimbuf tbuf;
    int foo;
    int retval;

    namelen = recv_uint();

    pathname = malloc(namelen);

    recv_data(pathname, namelen, 0);

    foo = recv_uint();

    if (foo) {

	tbuf.actime = recv_uint();
	tbuf.modtime = recv_uint();

	retval = utime(pathname, &tbuf);
    } else {
	retval = utime(pathname, 0);
    }
    send_uint(retval);

    free(pathname);
}

void dc_opendir(void)
{
    DIR *somedir;
    unsigned char *dirname;
    int namelen;

    namelen = recv_uint();

    dirname = malloc(namelen);

    recv_data(dirname, namelen, 0);

    somedir = opendir(dirname);

    send_uint((unsigned int)somedir);

    free(dirname);
}

void dc_closedir(void)
{
    DIR *somedir;
    int retval;

    somedir = (DIR *) recv_uint();

    retval = closedir(somedir);
    
    send_uint(retval);
}

void dc_readdir(void)
{
    DIR *somedir;
    struct dirent *somedirent;

    somedir = (DIR *) recv_uint();

    somedirent = readdir(somedir);
    
    if (somedirent) {
	send_uint(1);
	send_uint(somedirent->d_ino);
#ifdef _WIN32
	send_uint(0);
	send_uint(0);
	send_uint(0);
#else	
#ifdef __APPLE_CC__
	send_uint(0);
#else
	send_uint(somedirent->d_off);
#endif
	send_uint(somedirent->d_reclen);
	send_uint(somedirent->d_type);
#endif	
	send_uint(strlen(somedirent->d_name)+1);
	send_data(somedirent->d_name, strlen(somedirent->d_name)+1, 0);
    } else 
	send_uint(0);
}

void dc_cdfs_redir_read_sectors(int isofd)
{
    int start;
    int num;
    unsigned char * buf;

    start = recv_uint();
    num = recv_uint();

    start -= 150; 

    lseek(isofd, start * 2048, SEEK_SET);

    buf = malloc(num * 2048);

    read(isofd, buf, num * 2048);

    send_data(buf, num * 2048, 0);
}

#define GDBBUFSIZE 1024
extern int gdb_server_socket;

void dc_gdbpacket(void)
{
    size_t in_size, out_size;

    static int socket_fd = -1;
    static char gdb_buf[GDBBUFSIZE];

    int count, size, retval = 0;

    in_size = recv_uint();
    out_size = recv_uint();

    if (in_size)
	recv_data(gdb_buf, in_size > GDBBUFSIZE ? GDBBUFSIZE : in_size, 0);

    if (gdb_server_socket < 0) {
	send_uint(-1);
	return;
    }

    if (socket_fd < 0) {
	printf( "waiting for gdb client connection...\n" );
	if ( (socket_fd = accept( gdb_server_socket, NULL, NULL )) < 0) {
	    perror("error accepting gdb server connection");
	    send_uint(-1);
	    return;
	}
    }

    if (in_size)
	write(socket_fd, gdb_buf, in_size);

    if (out_size) {
	retval = read(socket_fd, gdb_buf, out_size > GDBBUFSIZE ? GDBBUFSIZE : out_size);
	if (retval == 0)
	    socket_fd = -1;
    }

    send_uint(retval);
    if (retval > 0)
	send_data(gdb_buf, retval, 0);
}
