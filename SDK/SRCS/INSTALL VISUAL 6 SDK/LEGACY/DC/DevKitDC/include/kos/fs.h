/* KallistiOS 1.1.6

   kos/fs.h
   (c)2000-2001 Dan Potter

   $Id: fs.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __KOS_FS_H
#define __KOS_FS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>

/* Directory entry; all handlers must conform to this interface */
typedef struct {
	int	size;
	char	name[MAX_FN_LEN];
	uint32	time;
	uint32	attr;
} dirent_t;

/* File handle type */
typedef uint32 file_t;

/* Handler interface; all VFS handlers must implement this interface. */
typedef struct vfs_handler_str {
	char	prefix[MAX_FN_LEN];	/* Path prefix */
	int	pid;			/* Process table ID for handler (0 == static) */
	int	cache;			/* Allow VFS cacheing; 0=no, 1=yes */
	struct vfs_handler_str *next;	/* Linked list pointer */	

	file_t	(*open)(const char *fn, int mode);
	void	(*close)(file_t hnd);
	ssize_t	(*read)(file_t hnd, void *buffer, size_t cnt);
	ssize_t	(*write)(file_t hnd, const void *buffer, size_t cnt);
	off_t	(*seek)(file_t hnd, off_t offset, int whence);
	off_t	(*tell)(file_t hnd);		/* like ftell() */
	size_t	(*total)(file_t hnd);		/* total file size */
	dirent_t* (*readdir)(file_t hnd);	/* Directories and files are the same here */
	int	(*ioctl)(file_t hnd, void *data, size_t size);	/* Device-specific call */
	int	(*rename)(const char *fn1, const char *fn2);	/* Rename and move files */
	int	(*unlink)(const char *fn);			/* Delete files */
	void*	(*mmap)(file_t fd);			/* "memory map" a file */
} vfs_handler;


/* Open modes */
#define O_RDONLY	1		/* Read only */
#define O_RDWR		2		/* Read-write */
#define O_APPEND	3		/* Append to an existing file */
#define O_WRONLY	4		/* Write-only */
#define O_MODE_MASK	7		/* Mask for mode numbers */
#define O_DIR		0x1000		/* Open as directory */
#define O_META		0x2000		/* Open as metadata */

/* Seek modes */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Standard file functions */
file_t	fs_open(const char *fn, int mode);
void	fs_close(file_t hnd);
ssize_t	fs_read(file_t hnd, void *buffer, size_t cnt);
ssize_t	fs_write(file_t hnd, const void *buffer, size_t cnt);
off_t	fs_seek(file_t hnd, off_t offset, int whence);
off_t	fs_tell(file_t hnd);
size_t	fs_total(file_t hnd);
dirent_t* fs_readdir(file_t hnd);
int	fs_ioctl(file_t hnd, void *data, size_t size);
int	fs_rename(const char *fn1, const char *fn2);
int	fs_unlink(const char *fn);
int	fs_chdir(const char *fn);
void*	fs_mmap(file_t hnd);

const char *fs_getwd();

/* Add/Remove a VFS module */
int	fs_handler_add(const char *prefix, vfs_handler *hnd);
int	fs_handler_remove(const vfs_handler *hnd);

/* VFS init */
int	fs_init();
void 	fs_shutdown();

__END_DECLS

#endif	/* __KOS_FS_H */

