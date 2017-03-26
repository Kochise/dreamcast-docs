/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/dcload-commands.h

   Copyright (C)2001 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.

   Adapted to KOS by Dan Potter.

*/

#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

#define DCLN_CMD_EXIT     "DC00"
#define DCLN_CMD_FSTAT    "DC01"
#define DCLN_CMD_WRITE    "DD02"
#define DCLN_CMD_READ     "DC03"
#define DCLN_CMD_OPEN     "DC04"
#define DCLN_CMD_CLOSE    "DC05"
#define DCLN_CMD_CREAT    "DC06"
#define DCLN_CMD_LINK     "DC07"
#define DCLN_CMD_UNLINK   "DC08"
#define DCLN_CMD_CHDIR    "DC09"
#define DCLN_CMD_CHMOD    "DC10"
#define DCLN_CMD_LSEEK    "DC11"
#define DCLN_CMD_TIME     "DC12"
#define DCLN_CMD_STAT     "DC13"
#define DCLN_CMD_UTIME    "DC14"
#define DCLN_CMD_BAD      "DC15"
#define DCLN_CMD_OPENDIR  "DC16"
#define DCLN_CMD_CLOSEDIR "DC17"
#define DCLN_CMD_READDIR  "DC18"
#define DCLN_CMD_CDFSREAD "DC19"

extern int dcln_syscall_retval;

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

void dcln_build_send_packet(int command_len);
void dcln_exit();
int dcln_read(int fd, void * buf, size_t count);
int dcln_write(int fd, const void *buf, size_t count);
int dcln_open(const char *pathname, int flags, int perms);
int dcln_close(int fd);
int dcln_link(const char *oldpath, const char *newpath);
int dcln_unlink(const char *pathname);
int dcln_chdir(const char *path);
off_t dcln_lseek(int fildes, off_t offset, int whence);
time_t dcln_time(time_t * t);
int dcln_stat(const char *file_name, dcload_stat_t *buf);
int dcln_opendir(const char *name);
int dcln_closedir(int dir);
dcload_dirent_t *dcln_readdir(int dir);

__END_DECLS

#endif
