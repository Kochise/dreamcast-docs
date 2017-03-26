/* 
 * dcload-ip syscalls for dcload-ip lwip interface
 *
 * Copyright (C) 2002 Andrew Kieschnick <andrewk@austin.rr.com>
 *
 */

#ifndef __DCLOAD_LWIP_SYSCALLS_H__
#define __DCLOAD_LWIP_SYSCALLS_H__

#include <kos.h>

#define CMD_EXIT     "DC00"
#define CMD_FSTAT    "DC01" /* not called from dcload-ip lwip */
#define CMD_WRITE    "DD02"
#define CMD_READ     "DC03"
#define CMD_OPEN     "DC04"
#define CMD_CLOSE    "DC05"
#define CMD_CREAT    "DC06" /* not called from dcload-ip lwip */
#define CMD_LINK     "DC07"
#define CMD_UNLINK   "DC08"
#define CMD_CHDIR    "DC09" /* not called from dcload-ip lwip */
#define CMD_CHMOD    "DC10" /* not called from dcload-ip lwip */
#define CMD_LSEEK    "DC11"
#define CMD_TIME     "DC12" /* not called from dcload-ip lwip */
#define CMD_STAT     "DC13"
#define CMD_UTIME    "DC14" /* not called from dcload-ip lwip */
#define CMD_BAD      "DC15" /* not called from dcload-ip lwip */
#define CMD_OPENDIR  "DC16"
#define CMD_CLOSEDIR "DC17"
#define CMD_READDIR  "DC18"
#define CMD_CDFSREAD "DC19" /* not called from dcload-ip lwip */

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

int dcload_lwip_read(int fd, void *buf, size_t count);
int dcload_lwip_write(int fd, const void *buf, size_t count);
int dcload_lwip_open(const char *pathname, int flags, ...);
int dcload_lwip_close(int fd);
int dcload_lwip_link(const char *oldname, const char *newname);
int dcload_lwip_unlink(const char *pathname);
off_t dcload_lwip_lseek(int fildes, off_t offset, int whence);
int dcload_lwip_stat(const char *file_name, struct dcload_stat *buf);
void * dcload_lwip_opendir(const char *name);
int dcload_lwip_closedir(void *dir);
struct dcload_dirent *dcload_lwip_readdir(void *dir);
void dcload_lwip_exit(void);
int dcload_lwip_syscall(unsigned int syscall, ...);

extern unsigned int syscall_retval;

#endif
