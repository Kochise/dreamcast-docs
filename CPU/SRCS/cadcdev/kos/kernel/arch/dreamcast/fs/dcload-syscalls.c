/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-net.c

   Copyright (C)2001 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

/* #include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <stdarg.h>
#include <dirent.h> */

#include <string.h>
#include <dc/fs_dclnative.h>
#include "dcload-syscalls.h"
#include "dcload-packet.h"
#include "dcload-net.h"
#include "dcload-commands.h"

static ether_header_t * ether = (ether_header_t *)dcln_pkt_buf;
static ip_header_t * ip = (ip_header_t *)(dcln_pkt_buf + ETHER_H_LEN);
static udp_header_t * udp = (udp_header_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN);

/* send command, enable bb, bb_loop(), then return */

void dcln_build_send_packet(int command_len)
{
    unsigned char * command = dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN;
/*
    scif_puts("build_send_packet\n");
    scif_putchar(command[0]);
    scif_putchar(command[1]);
    scif_putchar(command[2]);
    scif_putchar(command[3]);
    scif_puts("\n");
*/
    dcln_make_ether(dcln_tool_mac, dcln_our_mac, ether);
    dcln_make_ip(dcln_tool_ip, dcln_our_ip, UDP_H_LEN + command_len, 17, ip);
    dcln_make_udp(dcln_tool_port, 31313, command, command_len, ip, udp);
    dcln_tx(dcln_pkt_buf, ETHER_H_LEN + IP_H_LEN + UDP_H_LEN + command_len);
}

void dcln_exit(void)
{
    command_t * command = (command_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_EXIT, 4); 
    command->address = htonl(0);
    command->size = htonl(0);
    dcln_build_send_packet(COMMAND_LEN);
}

int dcln_read(int fd, void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_READ, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((uint32)buf);
    command->value2 = htonl(count);
    dcln_build_send_packet(sizeof(command_3int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_write(int fd, const void *buf, size_t count)
{
    command_3int_t * command = (command_3int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_WRITE, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((uint32)buf);
    command->value2 = htonl(count);
    dcln_build_send_packet(sizeof(command_3int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_open(const char *pathname, int flags, int perms)
{
    command_2int_string_t * command = (command_2int_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    int namelen = strlen(pathname);
 
    memcpy(command->id, DCLN_CMD_OPEN, 4); 

    command->value0 = htonl(flags);
    command->value1 = htonl(perms);

    memcpy(command->string, pathname, namelen+1);
    
    dcln_build_send_packet(sizeof(command_2int_string_t)+namelen);
    dcln_rx_loop();

    return dcln_syscall_retval;
}

int dcln_close(int fd)
{
    command_int_t * command = (command_int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    memcpy(command->id, DCLN_CMD_CLOSE, 4); 
    command->value0 = htonl(fd);

    dcln_build_send_packet(sizeof(command_int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_link(const char *oldpath, const char *newpath)
{
    command_string_t * command = (command_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen1 = strlen(oldpath);
    int namelen2 = strlen(newpath);
 
    memcpy(command->id, DCLN_CMD_LINK, 4); 

    memcpy(command->string, oldpath, namelen1 + 1);
    memcpy(command->string + namelen1 + 1, newpath, namelen2 + 1); 
    
    dcln_build_send_packet(sizeof(command_string_t)+namelen1+namelen2+1);
    dcln_rx_loop();

    return dcln_syscall_retval;

}

int dcln_unlink(const char *pathname)
{
    command_string_t * command = (command_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(pathname);
 
    memcpy(command->id, DCLN_CMD_UNLINK, 4); 

    memcpy(command->string, pathname, namelen + 1);
    
    dcln_build_send_packet(sizeof(command_string_t)+namelen);
    dcln_rx_loop();

    return dcln_syscall_retval;
}

int dcln_chdir(const char *path)
{
    command_string_t * command = (command_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(path);
 
    memcpy(command->id, DCLN_CMD_CHDIR, 4); 

    memcpy(command->string, path, namelen + 1);

    dcln_build_send_packet(sizeof(command_string_t)+namelen);
    dcln_rx_loop();

    return dcln_syscall_retval;
}

off_t dcln_lseek(int fildes, off_t offset, int whence)
{
    command_3int_t * command = (command_3int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_LSEEK, 4); 
    command->value0 = htonl(fildes);
    command->value1 = htonl(offset);
    command->value2 = htonl(whence);

    dcln_build_send_packet(sizeof(command_3int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

time_t dcln_time(time_t * t)
{
    command_int_t * command = (command_int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    
    memcpy(command->id, DCLN_CMD_TIME, 4); 
    dcln_build_send_packet(sizeof(command_int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_stat(const char *file_name, dcload_stat_t *buf)
{
    command_2int_string_t * command = (command_2int_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(file_name);

    memcpy(command->id, DCLN_CMD_STAT, 4); 
    memcpy(command->string, file_name, namelen+1);

    command->value0 = htonl((uint32)buf);
    command->value1 = htonl(sizeof(struct stat));
    
    dcln_build_send_packet(sizeof(command_2int_string_t)+namelen);
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_opendir(const char *name)
{
    command_string_t * command = (command_string_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    int namelen = strlen(name);
    
    memcpy(command->id, DCLN_CMD_OPENDIR, 4); 
    memcpy(command->string, name, namelen+1);

    dcln_build_send_packet(sizeof(command_string_t)+namelen);
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

int dcln_closedir(int dir)
{
    command_int_t * command = (command_int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_CLOSEDIR, 4); 
    command->value0 = htonl(dir);

    dcln_build_send_packet(sizeof(command_int_t));
    dcln_rx_loop();
    
    return dcln_syscall_retval;
}

static dcload_dirent_t our_dir;

dcload_dirent_t *dcln_readdir(int dir)
{
    command_3int_t * command = (command_3int_t *)(dcln_pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);
    
    memcpy(command->id, DCLN_CMD_READDIR, 4); 
    command->value0 = htonl(dir);
    command->value1 = htonl((uint32)&our_dir);
    command->value2 = htonl(sizeof(struct dirent));

    dcln_build_send_packet(sizeof(command_3int_t));
    dcln_rx_loop();
    
    if (dcln_syscall_retval)
	return &our_dir;
    else
	return 0;
}
	
size_t dcln_gdbpacket(const char *in_buf, size_t in_size, char *out_buf, size_t out_size)
{
    command_2int_string_t * command = (command_2int_string_t *)(pkt_buf + ETHER_H_LEN + IP_H_LEN + UDP_H_LEN);

    memcpy(command->id, CMD_GDBPACKET, 4);
    command->value0 = htonl(in_size);
    command->value1 = htonl(out_size);
    memcpy(command->string, in_buf, in_size);
    dcln_build_send_packet(sizeof(command_2int_string_t)-1 + in_size);
    dcln_rx_loop();

    memcpy(out_buf, dcln_syscall_data, dcln_syscall_retval);

    return dcln_syscall_retval;
}
