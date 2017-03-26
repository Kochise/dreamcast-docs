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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <stdarg.h>
#include <dirent.h>
#include "syscalls.h"
#include "packet.h"
#include "net.h"
#include "commands.h"
#include "scif.h"
#include "adapter.h"

unsigned int syscall_retval;
unsigned char* syscall_data;

ether_header_t * ether = (ether_header_t *)pkt_buf;
ip_header_t * ip = (ip_header_t *)(pkt_buf + ETHER_H_LEN);
udp_header_t * udp = (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN);

/* send command, enable bb, bb_loop(), then return */

int strlen(const char *s)
{
    int c = 0;

    while (s[c] != 0)
	c++;
    return c;
}

void build_send_packet(int command_len)
{
    unsigned char * command = pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN;
/*
    scif_puts("build_send_packet\n");
    scif_putchar(command[0]);
    scif_putchar(command[1]);
    scif_putchar(command[2]);
    scif_putchar(command[3]);
    scif_puts("\n");
*/
    make_ether(tool_mac, bb->mac, ether);
    make_ip(tool_ip, our_ip, UDP_H_LEN + command_len, 17, ip);
    make_udp(tool_port, 31313, command, command_len, ip, udp);
    bb->start();
    bb->tx(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + command_len);

}

void dcexit(void)
{
    command_t * command = (command_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_EXIT, 4); 
    command->address = htonl(0);
    command->size = htonl(0);
    build_send_packet(COMMAND_LEN);
    bb->stop();
}

int read(int fd, void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_READ, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl(buf);
    command->value2 = htonl(count);
    build_send_packet(sizeof(command_3int_t));
    bb->loop();
    
    return syscall_retval;
}

int write(int fd, const void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_WRITE, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl(buf);
    command->value2 = htonl(count);
    build_send_packet(sizeof(command_3int_t));
    bb->loop();
    
    return syscall_retval;
}

int open(const char *pathname, int flags, ...)
{
    va_list ap;
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(pathname);
 
    memcpy(command->id, CMD_OPEN, 4); 

    va_start(ap, flags);
    command->value0 = htonl(flags);
    command->value1 = htonl(va_arg(ap, int));
    va_end(ap);

    memcpy(command->string, pathname, namelen+1);
    
    build_send_packet(sizeof(command_2int_string_t)+namelen);
    bb->loop();

    return syscall_retval;
}

int close(int fd)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    memcpy(command->id, CMD_CLOSE, 4); 
    command->value0 = htonl(fd);

    build_send_packet(sizeof(command_int_t));
    bb->loop();
    
    return syscall_retval;
}

int creat(const char *pathname, mode_t mode)
{
    command_int_string_t * command = (command_int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(pathname);
 
    memcpy(command->id, CMD_CREAT, 4); 

    command->value0 = htonl(mode);

    memcpy(command->string, pathname, namelen+1);
    
    build_send_packet(sizeof(command_int_string_t)+namelen);
    bb->loop();

    return syscall_retval;
}

int link(const char *oldpath, const char *newpath)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen1 = strlen(oldpath);
    int namelen2 = strlen(newpath);
 
    memcpy(command->id, CMD_LINK, 4); 

    memcpy(command->string, oldpath, namelen1 + 1);
    memcpy(command->string + namelen1 + 1, newpath, namelen2 + 1); 
    
    build_send_packet(sizeof(command_string_t)+namelen1+namelen2+1);
    bb->loop();

    return syscall_retval;

}

int unlink(const char *pathname)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(pathname);
 
    memcpy(command->id, CMD_UNLINK, 4); 

    memcpy(command->string, pathname, namelen + 1);
    
    build_send_packet(sizeof(command_string_t)+namelen);
    bb->loop();

    return syscall_retval;
}

int chdir(const char *path)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(path);
 
    memcpy(command->id, CMD_CHDIR, 4); 

    memcpy(command->string, path, namelen + 1);

    build_send_packet(sizeof(command_string_t)+namelen);
    bb->loop();

    return syscall_retval;
}

int chmod(const char *path, mode_t mode)
{
    command_int_string_t * command = (command_int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(path);
 
    memcpy(command->id, CMD_CHMOD, 4); 

    command->value0 = htonl(mode);

    memcpy(command->string, path, namelen+1);
    
    build_send_packet(sizeof(command_int_string_t)+namelen);
    bb->loop();

    return syscall_retval;
}

off_t lseek(int fildes, off_t offset, int whence)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_LSEEK, 4); 
    command->value0 = htonl(fildes);
    command->value1 = htonl(offset);
    command->value2 = htonl(whence);

    build_send_packet(sizeof(command_3int_t));
    bb->loop();
    
    return syscall_retval;
}

int fstat(int filedes, struct stat *buf)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_FSTAT, 4); 
    command->value0 = htonl(filedes);
    command->value1 = htonl(buf);
    command->value2 = htonl(sizeof(struct stat));
    
    build_send_packet(sizeof(command_3int_t));
    bb->loop();
    
    return syscall_retval;
}

time_t time(time_t * t)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    
    memcpy(command->id, CMD_TIME, 4); 
    build_send_packet(sizeof(command_int_t));
    bb->loop();
    
    return syscall_retval;
}

int stat(const char *file_name, struct stat *buf)
{
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(file_name);

    memcpy(command->id, CMD_STAT, 4); 
    memcpy(command->string, file_name, namelen+1);

    command->value0 = htonl(buf);
    command->value1 = htonl(sizeof(struct stat));
    
    build_send_packet(sizeof(command_2int_string_t)+namelen);
    bb->loop();
    
    return syscall_retval;
}

int utime(const char *filename, struct utimbuf *buf)
{
    command_3int_string_t * command = (command_3int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(filename);
    
    memcpy(command->id, CMD_UTIME, 4); 
    memcpy(command->string, filename, namelen+1);
    
    command->value0 = htonl(buf);

    if (!buf) {
	command->value1 = htonl(buf->actime);
	command->value2 = htonl(buf->modtime);
    }

    build_send_packet(sizeof(command_3int_string_t)+namelen);
    bb->loop();
    
    return syscall_retval;
}

DIR * opendir(const char *name)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(name);
    
    memcpy(command->id, CMD_OPENDIR, 4); 
    memcpy(command->string, name, namelen+1);

    build_send_packet(sizeof(command_string_t)+namelen);
    bb->loop();
    
    return (DIR *)syscall_retval;
}

int closedir(DIR *dir)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_CLOSEDIR, 4); 
    command->value0 = htonl(dir);

    build_send_packet(sizeof(command_int_t));
    bb->loop();
    
    return syscall_retval;
}

struct dirent our_dir;

struct dirent *readdir(DIR *dir)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_READDIR, 4); 
    command->value0 = htonl(dir);
    command->value1 = htonl(&our_dir);
    command->value2 = htonl(sizeof(struct dirent));

    build_send_packet(sizeof(command_3int_t));
    bb->loop();
    
    if (syscall_retval)
	return &our_dir;
    else
	return 0;
}
	
int gethostinfo(unsigned int *ip, unsigned int *port)
{
    *ip = tool_ip;
    *port = tool_port;

    return our_ip;
}

size_t gdbpacket(const char *in_buf, unsigned int size_pack, char* out_buf)
{
    size_t in_size = size_pack >> 16, out_size = size_pack & 0xffff;
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    memcpy(command->id, CMD_GDBPACKET, 4);
    command->value0 = htonl(in_size);
    command->value1 = htonl(out_size);
    memcpy(command->string, in_buf, in_size);
    build_send_packet(sizeof(command_2int_string_t)-1 + in_size);
    bb->loop();
    
    if (syscall_retval <= out_size)
	memcpy(out_buf, syscall_data, syscall_retval);

    return syscall_retval;
}
