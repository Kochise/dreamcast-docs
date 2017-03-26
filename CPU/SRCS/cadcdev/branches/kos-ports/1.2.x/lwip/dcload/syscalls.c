/* 
 * dcload-ip syscalls for dcload-ip lwIP interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <adk@napalm-x.com>
 *
 */

#include <kos.h>
#include <lwip/lwip.h>
#include "dcload-syscalls.h"
#include "dcload-commands.h"
#include "dcload-lwip.h"

unsigned int syscall_retval;

int dcload_lwip_read(int fd, void *buf, size_t count)
{
    struct pbuf * pb;
    command_3int_t * command;
    
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_3int_t), PBUF_RAM);
    command = (command_3int_t *)(pb->payload);

    memcpy(command->id, CMD_READ, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((int)buf);
    command->value2 = htonl(count);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

int dcload_lwip_write(int fd, const void *buf, size_t count)
{
    struct pbuf * pb;
    command_3int_t * command;

    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_3int_t), PBUF_RAM);
    command = (command_3int_t *)(pb->payload);

    memcpy(command->id, CMD_WRITE, 4); 
    command->value0 = htonl(fd);
    command->value1 = htonl((int)buf);
    command->value2 = htonl(count);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

int dcload_lwip_open(const char *pathname, int flags, ...)
{
    struct pbuf * pb;
    va_list ap;
    command_2int_string_t * command;
    int namelen = strlen(pathname);

    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_2int_string_t) + namelen, PBUF_RAM);
    command = (command_2int_string_t *)(pb->payload);
 
    memcpy(command->id, CMD_OPEN, 4); 

    va_start(ap, flags);
    command->value0 = htonl(flags);
    command->value1 = htonl(va_arg(ap, int));
    va_end(ap);

    memcpy(command->string, pathname, namelen+1);
    
    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }
    return syscall_retval;
}

int dcload_lwip_close(int fd)
{
    struct pbuf * pb;
    command_int_t * command;

    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_int_t), PBUF_RAM);
    command = (command_int_t *)(pb->payload);
 
    memcpy(command->id, CMD_CLOSE, 4); 
    command->value0 = htonl(fd);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

int dcload_lwip_link(const char *oldpath, const char *newpath)
{
    struct pbuf * pb;
    command_string_t * command;
    int namelen1 = strlen(oldpath);
    int namelen2 = strlen(newpath);
 
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_string_t) + namelen1 + namelen2 + 1, PBUF_RAM);
    command = (command_string_t *)(pb->payload);

    memcpy(command->id, CMD_LINK, 4); 

    memcpy(command->string, oldpath, namelen1 + 1);
    memcpy(command->string + namelen1 + 1, newpath, namelen2 + 1);
    
    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

int dcload_lwip_unlink(const char *pathname)
{
    struct pbuf * pb;
    command_string_t * command;
    int namelen = strlen(pathname);
 
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_string_t) + namelen, PBUF_RAM);
    command = (command_string_t *)(pb->payload);

    memcpy(command->id, CMD_UNLINK, 4); 

    memcpy(command->string, pathname, namelen + 1);
    
    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

off_t dcload_lwip_lseek(int fildes, off_t offset, int whence)
{
    struct pbuf * pb;
    command_3int_t * command;
    
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_3int_t), PBUF_RAM);
    command = (command_3int_t *)(pb->payload);

    memcpy(command->id, CMD_LSEEK, 4); 
    command->value0 = htonl(fildes);
    command->value1 = htonl(offset);
    command->value2 = htonl(whence);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

int dcload_lwip_stat(const char *file_name, struct dcload_stat *buf)
{
    struct pbuf * pb;
    command_2int_string_t * command;
    int namelen = strlen(file_name);

    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_2int_string_t) + namelen, PBUF_RAM);
    command = (command_2int_string_t *)(pb->payload);

    memcpy(command->id, CMD_STAT, 4); 
    memcpy(command->string, file_name, namelen+1);

    command->value0 = htonl((int)buf);
    command->value1 = htonl(sizeof(struct dcload_stat));
            
    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }

    return syscall_retval;
}

void * dcload_lwip_opendir(const char *name)
{
    struct pbuf * pb;
    command_string_t * command;
    int namelen = strlen(name);
    
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_string_t) + namelen, PBUF_RAM);
    command = (command_string_t *)(pb->payload);

    memcpy(command->id, CMD_OPENDIR, 4); 
    memcpy(command->string, name, namelen+1);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return 0;
    }

    return (void *)syscall_retval;
}

int dcload_lwip_closedir(void *dir)
{
    struct pbuf * pb;
    command_int_t * command;
    
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_int_t), PBUF_RAM);
    command = (command_int_t *)(pb->payload);

    memcpy(command->id, CMD_CLOSEDIR, 4); 
    command->value0 = htonl((int)dir);

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return -1;
    }
    return syscall_retval;
}

struct dcload_dirent our_dir;

struct dcload_dirent *dcload_lwip_readdir(void *dir)
{
    struct pbuf * pb;
    command_3int_t * command;
    
    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_3int_t), PBUF_RAM);
    command = (command_3int_t *)(pb->payload);

    memcpy(command->id, CMD_READDIR, 4); 
    command->value0 = htonl((int)dir);
    command->value1 = htonl((int)&our_dir);
    command->value2 = htonl(sizeof(struct dcload_dirent));

    if (safe_udp_send(dcload_pcb, pb) == ERR_OK) {
	pbuf_free(pb);
	sem_wait(dcload_sem);
    } else {
	pbuf_free(pb);
	return 0;
    }

    if (syscall_retval)
	return &our_dir;
    else
	return 0;
}

void dcload_lwip_exit(void)
{
    struct pbuf *pb;
    command_t * command;

    pb = pbuf_alloc(PBUF_TRANSPORT, sizeof(command_t), PBUF_RAM);
    command = (command_t *)(pb->payload);

    memcpy(command->id, CMD_EXIT, 4);
    command->address = htonl(0);
    command->size = htonl(0);
    
    safe_udp_send(dcload_pcb, pb);
    pbuf_free(pb);
}
