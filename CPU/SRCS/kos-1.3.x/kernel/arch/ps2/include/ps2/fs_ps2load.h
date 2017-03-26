/* KallistiOS ##version##

   kernel/arch/ps2/include/ps2/fs_ps2load.h
   Copyright (c)2002 Andrew Kieschnick
   Copyright (c)2002 Dan Potter

*/

#ifndef __PS2_FS_PS2LOAD_H
#define __PS2_FS_PS2LOAD_H

/* Definitions for the "dcload" file system */

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

/* dcload magic value */
#define PS2LOADMAGICVALUE 0xdeadbeef
#define PS2LOADBLOCKPTR  ((uint32 *)0x81fff800)

/* Available ps2load console commands */

#define PS2LOAD_READ		0
#define PS2LOAD_WRITE		1
#define PS2LOAD_OPEN		2
#define PS2LOAD_CLOSE		3
#define PS2LOAD_CREAT		4
#define PS2LOAD_LINK		5
#define PS2LOAD_UNLINK		6
#define PS2LOAD_CHDIR		7
#define PS2LOAD_CHMOD		8 
#define PS2LOAD_LSEEK		9
#define PS2LOAD_FSTAT		10
#define PS2LOAD_TIME		11
#define PS2LOAD_STAT		12
#define PS2LOAD_UTIME		13
#define PS2LOAD_GSCONSPRINT	14
#define PS2LOAD_EXIT		15
#define PS2LOAD_OPENDIR		16
#define PS2LOAD_CLOSEDIR	17
#define PS2LOAD_READDIR		18

/* ps2load dirent */

struct ps2load_dirent {
  long            d_ino;  /* inode number */
  off_t           d_off;  /* offset to the next dirent */
  unsigned short  d_reclen;/* length of this record */
  unsigned char   d_type;         /* type of file */
  char            d_name[256];    /* filename */
};

typedef struct ps2load_dirent ps2load_dirent_t;

/* ps2load stat */

struct  ps2load_stat { 
  unsigned short st_dev;
  unsigned short st_ino;
  int st_mode;
  unsigned short st_nlink;
  unsigned short st_uid;
  unsigned short st_gid;
  unsigned short st_rdev;
  long st_size;
  long st_atime;
  long st_spare1;
  long st_mtime;
  long st_spare2;
  long st_ctime;
  long st_spare3;
  long st_blksize;
  long st_blocks;
  long st_spare4[2];
};

typedef struct ps2load_stat ps2load_stat_t;

#define S_IFDIR 0040000 /* directory */

/* Printk replacement */
void ps2load_printk(const char *str);

/* File functions */
uint32	ps2load_open(vfs_handler_t * vfs, const char *fn, int mode);
void	ps2load_close(uint32 hnd);
ssize_t	ps2load_read(uint32 hnd, void *buf, size_t cnt);
off_t	ps2load_seek(uint32 hnd, off_t offset, int whence);
off_t	ps2load_tell(uint32 hnd);
size_t	ps2load_total(uint32 hnd);
dirent_t* ps2load_readdir(uint32 hnd);
int     ps2load_rename(vfs_handler_t * vfs, const char *fn1, const char *fn2);
int     ps2load_unlink(vfs_handler_t * vfs, const char *fn);

/* Init func */
void fs_ps2load_init_console();
int fs_ps2load_init();
int fs_ps2load_shutdown();

/* Init func for ps2load-ip + lwIP */
int fs_ps2load_init_lwip(void *p);

__END_DECLS

#endif	/* __PS2_FS_PS2LOAD_H */


