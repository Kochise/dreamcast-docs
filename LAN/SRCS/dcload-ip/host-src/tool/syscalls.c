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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <utime.h>
#include <dirent.h>
#include "syscalls.h"
#include "dc-io.h"
#include "dcload-types.h"
#include "commands.h"

#ifndef O_BINARY
#define O_BINARY 0
#endif

/* syscalls for dcload-ip
 * 
 * 1. receive all parameters from dc
 * 2. get any data from dc using recv_data (dc passes address/size of buffer)
 * 3. send any data to dc using send_data (dc passess address/size of buffer)
 * 4. send return value to dc
 */

unsigned int dc_order(unsigned int x)
{
    if (x == htonl(x))
	return (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | ((x >> 24) & 0xff);
    else
	return x;
}

void dc_fstat(unsigned char * buffer)
{
    struct stat filestat;
    int retval;
    dcload_stat_t dcstat;
    command_3int_t *command = (command_3int_t *)buffer;
    /* value0 = fd, value1 = addr, value2 = size */

    retval = fstat(ntohl(command->value0), &filestat);
    
    dcstat.st_dev = dc_order(filestat.st_dev);
    dcstat.st_ino = dc_order(filestat.st_ino);
    dcstat.st_mode = dc_order(filestat.st_mode);
    dcstat.st_nlink = dc_order(filestat.st_nlink);
    dcstat.st_uid = dc_order(filestat.st_uid);
    dcstat.st_gid = dc_order(filestat.st_gid);
    dcstat.st_rdev = dc_order(filestat.st_rdev);
    dcstat.st_size = dc_order(filestat.st_size);
    dcstat.st_blksize = dc_order(filestat.st_blksize);
    dcstat.st_blocks = dc_order(filestat.st_blocks);
    dcstat.st_atime_priv = dc_order(filestat.st_atime);
    dcstat.st_mtime_priv = dc_order(filestat.st_mtime);
    dcstat.st_ctime_priv = dc_order(filestat.st_ctime);

    send_data((unsigned char *)&dcstat, ntohl(command->value1), ntohl(command->value2));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_write(unsigned char * buffer)
{
    unsigned char *data;
    int retval;
    command_3int_t *command = (command_3int_t *)buffer;
    /* value0 = fd, value1 = addr, value2 = size */
        
    data = malloc(ntohl(command->value2));

    recv_data(data, ntohl(command->value1), ntohl(command->value2), 1);

    retval = write(ntohl(command->value0), data, ntohl(command->value2));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);

    free(data);
}

void dc_read(unsigned char * buffer)
{
    unsigned char *data;
    int retval;
    command_3int_t *command = (command_3int_t *)buffer;
    /* value0 = fd, value1 = addr, value2 = size */

    data = malloc(ntohl(command->value2));
    retval = read(ntohl(command->value0), data, ntohl(command->value2));

    send_data(data, ntohl(command->value1), ntohl(command->value2));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);

    free(data);
}

void dc_open(unsigned char * buffer)
{
  int retval;
  int flags;
  int ourflags = 0;
  int mode;
  command_2int_string_t *command = (command_2int_string_t *)buffer;
  /* value0 = flags value1 = mode string = name */
  
  /* translate flags */
  
  if (ntohl(command->value0) & 0x0001)
    ourflags |= O_WRONLY;
  if (ntohl(command->value0) & 0x0002)
    ourflags |= O_RDWR;
  if (ntohl(command->value0) & 0x0008)
    ourflags |= O_APPEND;
  if (ntohl(command->value0) & 0x0200)
    ourflags |= O_CREAT;
  if (ntohl(command->value0) & 0x0400)
    ourflags |= O_TRUNC;
  if (ntohl(command->value0) & 0x0800)
    ourflags |= O_EXCL;
  
  retval = open(command->string, ourflags | O_BINARY, ntohl(command->value1));

  send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_close(unsigned char * buffer)
{
    int retval;
    command_int_t *command = (command_int_t *)buffer;

    retval = close(ntohl(command->value0));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_creat(unsigned char * buffer)
{
    int namelen;
    unsigned char *pathname;
    int retval;
    int mode;
    command_int_string_t *command = (command_int_string_t *)buffer;

    retval = creat(command->string, ntohl(command->value0));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_link(unsigned char * buffer)
{
    unsigned char *pathname1, *pathname2;
    int retval;
    command_string_t *command = (command_string_t *)buffer;

    pathname1 = command->string;
    pathname2 = &command->string[strlen(command->string)+1];

    retval = link(pathname1, pathname2);

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_unlink(unsigned char * buffer)
{
    int retval;
    command_string_t *command = (command_string_t *)buffer;

    retval = unlink(command->string);

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_chdir(unsigned char * buffer)
{
    int retval;
    command_string_t *command = (command_string_t *)buffer;

    retval = chdir(command->string);

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_chmod(unsigned char * buffer)
{
    int retval;
    command_int_string_t *command = (command_int_string_t *)buffer;
    
    retval = chmod(command->string, ntohl(command->value0));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_lseek(unsigned char * buffer)
{
    int filedes;
    int offset;
    int whence;
    int retval;
    command_3int_t *command = (command_3int_t *)buffer;

    retval = lseek(ntohl(command->value0), ntohl(command->value1), ntohl(command->value2));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_time(unsigned char * buffer)
{
    time_t t;

    time(&t);

    send_command(CMD_RETVAL, t, t, NULL, 0);
}

void dc_stat(unsigned char * buffer)
{
    struct stat filestat;
    int retval;
    dcload_stat_t dcstat;
    command_2int_string_t *command = (command_2int_string_t *)buffer;

    retval = stat(command->string, &filestat);

    dcstat.st_dev = dc_order(filestat.st_dev);
    dcstat.st_ino = dc_order(filestat.st_ino);
    dcstat.st_mode = dc_order(filestat.st_mode);
    dcstat.st_nlink = dc_order(filestat.st_nlink);
    dcstat.st_uid = dc_order(filestat.st_uid);
    dcstat.st_gid = dc_order(filestat.st_gid);
    dcstat.st_rdev = dc_order(filestat.st_rdev);
    dcstat.st_size = dc_order(filestat.st_size);
    dcstat.st_blksize = dc_order(filestat.st_blksize);
    dcstat.st_blocks = dc_order(filestat.st_blocks);
    dcstat.st_atime_priv = dc_order(filestat.st_atime);
    dcstat.st_mtime_priv = dc_order(filestat.st_mtime);
    dcstat.st_ctime_priv = dc_order(filestat.st_ctime);

    send_data((unsigned char *)&dcstat, ntohl(command->value0), ntohl(command->value1));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_utime(unsigned char * buffer)
{
    struct utimbuf tbuf;
    int retval;
    command_3int_string_t *command = (command_3int_string_t *)buffer;

    if (ntohl(command->value0)) {

	tbuf.actime = ntohl(command->value1);
	tbuf.modtime = ntohl(command->value2);

	retval = utime(command->string, &tbuf);
    } else {
	retval = utime(command->string, 0);
    }
    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_opendir(unsigned char * buffer)
{
    DIR *somedir;
    command_string_t *command = (command_string_t *)buffer;

    somedir = opendir(command->string);

    send_command(CMD_RETVAL, (unsigned int)somedir, (unsigned int)somedir, NULL, 0);
}

void dc_closedir(unsigned char * buffer)
{
    int retval;
    command_int_t *command = (command_int_t *)buffer;

    retval = closedir((DIR *) ntohl(command->value0));

    send_command(CMD_RETVAL, retval, retval, NULL, 0);
}

void dc_readdir(unsigned char * buffer)
{
    struct dirent *somedirent;
    dcload_dirent_t dcdirent;
    command_3int_t *command = (command_3int_t *)buffer;

    somedirent = readdir((DIR *)ntohl(command->value0));

    if (somedirent) {
#ifdef __APPLE__
	dcdirent.d_ino = dc_order(somedirent->d_fileno);
	dcdirent.d_off = dc_order(0);
	dcdirent.d_reclen = dc_order(somedirent->d_reclen);
	dcdirent.d_type = dc_order(somedirent->d_type);
#else
	dcdirent.d_ino = dc_order(somedirent->d_ino);
# ifdef _WIN32
	dcdirent.d_off = dc_order(0);
	dcdirent.d_reclen = dc_order(0);
	dcdirent.d_type = dc_order(0);
# else
	dcdirent.d_off = dc_order(somedirent->d_off);
	dcdirent.d_reclen = dc_order(somedirent->d_reclen);
	dcdirent.d_type = dc_order(somedirent->d_type);
# endif
#endif
	strcpy(dcdirent.d_name, somedirent->d_name);
	
	send_data((unsigned char *)&dcdirent, ntohl(command->value1), ntohl(command->value2));
    }
    
    send_command(CMD_RETVAL, (unsigned int)somedirent, (unsigned int)somedirent, NULL, 0);
}

void dc_cdfs_redir_read_sectors(int isofd, unsigned char * buffer)
{
    int start;
    unsigned char * buf;
    command_3int_t *command = (command_3int_t *)buffer;

    start = ntohl(command->value0) - 150;

    lseek(isofd, start * 2048, SEEK_SET);

    buf = malloc(ntohl(command->value2));

    read(isofd, buf, ntohl(command->value2));

    send_data(buf, ntohl(command->value1), ntohl(command->value2));

    send_command(CMD_RETVAL, 0, 0, NULL, 0);
}

#define GDBBUFSIZE 1024
extern int gdb_server_socket;

void dc_gdbpacket(unsigned char * buffer)
{
    size_t in_size, out_size;

    static int socket_fd = -1;
    static char gdb_buf[GDBBUFSIZE];

    int count, size, retval;

    if (gdb_server_socket < 0) {
	send_command(CMD_RETVAL, -1, -1, NULL, 0);
	return;
    }

    if (socket_fd < 0) {
	printf( "waiting for gdb client connection...\n" );
	if ( (socket_fd = accept( gdb_server_socket, NULL, NULL )) < 0) {
	    perror("error accepting gdb server connection");
	    return;
	}
    }

    command_2int_string_t *command = (command_2int_string_t *)buffer;
    /* value0 = in_size, value1 = out_size, string = packet */

    retval = 0;

    in_size = ntohl(command->value0);
    out_size = ntohl(command->value1);

    if (in_size)
	write(socket_fd, command->string, in_size);

    if (out_size) {
	retval = read(socket_fd, gdb_buf, out_size > GDBBUFSIZE ? GDBBUFSIZE : out_size);
	if (retval == 0)
	    socket_fd = -1;
    }

    send_command(CMD_RETVAL, retval, retval, gdb_buf, retval);
}
