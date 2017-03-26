/* ps2-load-ip

   syscalls.c

   Copyright (c)2001 Andrew Kieschnick
   Copyright (c)2002 Dan Potter
   License: GPL

   $Id: syscalls.c,v 1.2 2002/11/02 07:21:30 bardtx Exp $
*/

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

/* #include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <stdarg.h>
#include <dirent.h> */

#include "types.h"
#include "../../host-src/tool/ps2load-types.h"
#include "syscalls.h"
#include "packet.h"
#include "net.h"
#include "smap.h"
#include "commands.h"
#include "string.h"
#include "byteorder.h"
#include "stdio.h"
#include "ps2loadip.h"

#include <stdarg.h>

struct utimbuf {
	int	actime;
	int	modtime;
};

unsigned int syscall_retval;
static ether_header_t * ether;
static ip_header_t * ip;
static udp_header_t * udp;

void syscalls_init() {
	ether = (ether_header_t *)pkt_buf;
	ip = (ip_header_t *)(pkt_buf + ETHER_H_LEN);
	udp = (udp_header_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN);
}

/* send command, enable bb, bb_loop(), then return */

void build_send_packet(int command_len)
{
    unsigned char * command = pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN;

    make_ether(tool_mac, smap_get_mac(), ether);
    make_ip(tool_ip, our_ip, UDP_H_LEN + command_len, 17, ip);
    make_udp(tool_port, 31313, command, command_len, ip, udp);
    smap_start();
    smap_send(pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + command_len);

}

void sc_exit_post();
void sc_exit(void)
{
    command_t * command = (command_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, CMD_EXIT, 4); 
    command->address = htonl(0);
    command->size = htonl(0);
    build_send_packet(COMMAND_LEN);
    smap_stop();
    sc_exit_post();	/* Won't return */
}

int sc_read(int fd, void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_READ, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((uint32)buf);
    command->value2 = htonl(count);
    build_send_packet(sizeof(command_3int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_write(int fd, const void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_WRITE, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((uint32)buf);
    command->value2 = htonl(count);
    build_send_packet(sizeof(command_3int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_open(const char *pathname, int flags, ...)
{
    va_list ap;
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(pathname);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_OPEN, 4); 

    va_start(ap, flags);
    command->value0 = htonl(flags);
    command->value1 = htonl(va_arg(ap, int));
    va_end(ap);

    memcpy(command->string, pathname, namelen+1);
    
    build_send_packet(sizeof(command_2int_string_t)+namelen);
    smap_loop();

    return syscall_retval;
}

int sc_close(int fd)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_CLOSE, 4); 
    command->value0 = htonl(fd);

    build_send_packet(sizeof(command_int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_creat(const char *pathname, int mode)
{
    command_int_string_t * command = (command_int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(pathname);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_CREAT, 4); 

    command->value0 = htonl(mode);

    memcpy(command->string, pathname, namelen+1);
    
    build_send_packet(sizeof(command_int_string_t)+namelen);
    smap_loop();

    return syscall_retval;
}

int sc_link(const char *oldpath, const char *newpath)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen1 = strlen(oldpath);
    int namelen2 = strlen(newpath);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_LINK, 4); 

    memcpy(command->string, oldpath, namelen1 + 1);
    memcpy(command->string + namelen1 + 1, newpath, namelen2 + 1); 
    
    build_send_packet(sizeof(command_string_t)+namelen1+namelen2+1);
    smap_loop();

    return syscall_retval;

}

int sc_unlink(const char *pathname)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(pathname);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_UNLINK, 4); 

    memcpy(command->string, pathname, namelen + 1);
    
    build_send_packet(sizeof(command_string_t)+namelen);
    smap_loop();

    return syscall_retval;
}

int sc_chdir(const char *path)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(path);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_CHDIR, 4); 

    memcpy(command->string, path, namelen + 1);

    build_send_packet(sizeof(command_string_t)+namelen);
    smap_loop();

    return syscall_retval;
}

int sc_chmod(const char *path, int mode)
{
    command_int_string_t * command = (command_int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(path);
 
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_CHMOD, 4); 

    command->value0 = htonl(mode);

    memcpy(command->string, path, namelen+1);
    
    build_send_packet(sizeof(command_int_string_t)+namelen);
    smap_loop();

    return syscall_retval;
}

off_t sc_lseek(int fildes, off_t offset, int whence)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_LSEEK, 4); 
    command->value0 = htonl(fildes);
    command->value1 = htonl(offset);
    command->value2 = htonl(whence);

    build_send_packet(sizeof(command_3int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_fstat(int filedes, ps2load_stat_t *buf)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_FSTAT, 4); 
    command->value0 = htonl(filedes);
    command->value1 = htonl((uint32)buf);
    command->value2 = htonl(sizeof(ps2load_stat_t));
    
    build_send_packet(sizeof(command_3int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_time(int * t)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    if (!console_enabled) return -1;
    
    
    memcpy(command->id, CMD_TIME, 4); 
    build_send_packet(sizeof(command_int_t));
    smap_loop();
    
    return syscall_retval;
}

int sc_stat(const char *file_name, ps2load_stat_t *buf)
{
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(file_name);

    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_STAT, 4); 
    memcpy(command->string, file_name, namelen+1);

    command->value0 = htonl((uint32)buf);
    command->value1 = htonl(sizeof(ps2load_stat_t));
    
    build_send_packet(sizeof(command_2int_string_t)+namelen);
    smap_loop();
    
    return syscall_retval;
}

int sc_utime(const char *filename, struct utimbuf *buf)
{
    command_3int_string_t * command = (command_3int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(filename);
    
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_UTIME, 4); 
    memcpy(command->string, filename, namelen+1);
    
    command->value0 = htonl((uint32)buf);

    if (!buf) {
	command->value1 = htonl(buf->actime);
	command->value2 = htonl(buf->modtime);
    }

    build_send_packet(sizeof(command_3int_string_t)+namelen);
    smap_loop();
    
    return syscall_retval;
}

uint32 sc_opendir(const char *name)
{
    command_string_t * command = (command_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(name);
    
    if (!console_enabled) return 0;
    
    memcpy(command->id, CMD_OPENDIR, 4); 
    memcpy(command->string, name, namelen+1);

    build_send_packet(sizeof(command_string_t)+namelen);
    smap_loop();
    
    return (uint32)syscall_retval;
}

int sc_closedir(uint32 dir)
{
    command_int_t * command = (command_int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    if (!console_enabled) return -1;
    
    memcpy(command->id, CMD_CLOSEDIR, 4); 
    command->value0 = htonl(dir);

    build_send_packet(sizeof(command_int_t));
    smap_loop();
    
    return syscall_retval;
}

ps2load_dirent_t our_dir;

ps2load_dirent_t *sc_readdir(uint32 dir)
{
    command_3int_t * command = (command_3int_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    if (!console_enabled) return 0;
    
    memcpy(command->id, CMD_READDIR, 4); 
    command->value0 = htonl(dir);
    command->value1 = htonl((uint32)&our_dir);
    command->value2 = htonl(sizeof(ps2load_dirent_t));

    build_send_packet(sizeof(command_3int_t));
    smap_loop();
    
    if (syscall_retval)
	return &our_dir;
    else
	return 0;
}
	
int sc_gethostinfo(unsigned int *ip, unsigned int *port)
{
    *ip = tool_ip;
    *port = tool_port;

    return 1;
}

int sc_gsconsprint(const char *buf) {
    gs_printk(buf);
}    
