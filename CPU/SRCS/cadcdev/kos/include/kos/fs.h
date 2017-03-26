/* KallistiOS ##version##

   kos/fs.h
   Copyright (C)2000,2001,2002,2003 Dan Potter

   $Id: fs.h,v 1.11 2003/07/31 00:38:00 bardtx Exp $

*/

#ifndef __KOS_FS_H
#define __KOS_FS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <sys/types.h>
#include <kos/limits.h>
#include <time.h>
#include <sys/queue.h>

#include <kos/nmmgr.h>

/* Directory entry; all handlers must conform to this interface */
typedef struct kos_dirent {
	int	size;
	char	name[MAX_FN_LEN];
	time_t	time;
	uint32	attr;
} dirent_t;

/* File status information; like dirent, this is not the same as the *nix
   variation but it has similar information. */
struct vfs_handler;
typedef struct /*stat*/ {
	struct vfs_handler	* dev;		/* The VFS handler for this file/dir */
	uint32			unique;		/* A unique identifier on the VFS for this file/dir */
	uint32			type;		/* File/Dir type */
	uint32			attr;		/* Attributes */
	off_t			size;		/* Total file size, if applicable */
	time_t			time;		/* Last access/mod/change time (depends on VFS) */
} stat_t;

/* stat_t.unique */
#define STAT_UNIQUE_NONE	0	/* Constant to use denoting the file has no unique ID */

/* stat_t.type */
#define STAT_TYPE_NONE		0	/* Unknown / undefined / not relevant */
#define STAT_TYPE_FILE		1	/* Standard file */
#define STAT_TYPE_DIR		2	/* Standard directory */
#define STAT_TYPE_PIPE		3	/* A virtual device of some sort (pipe, socket, etc) */
#define STAT_TYPE_META		4	/* Meta data */

/* stat_t.attr */
#define STAT_ATTR_NONE		0x00	/* No attributes */
#define STAT_ATTR_R		0x01	/* Read-capable */
#define STAT_ATTR_W		0x02	/* Write-capable */
#define STAT_ATTR_RW		(STAT_ATTR_R | STAT_ATTR_W)	/* Read/Write capable */

/* File descriptor type */
typedef int file_t;

/* Invalid file handle constant (for open failure, etc) */
#define FILEHND_INVALID	((file_t)-1)

/* Handler interface; all VFS handlers must implement this interface. */
typedef struct vfs_handler {
	/* Name manager handler header */
	nmmgr_handler_t		nmmgr;

	/* Some VFS-specific pieces */
	int	cache;			/* Allow VFS cacheing; 0=no, 1=yes */
	void	* privdata;		/* Pointer to private data for the handler */

	/* Open a file on the given VFS; return a unique identifier */
	void *	(*open)(struct vfs_handler * vfs, const char *fn, int mode);

	/* Close a previously opened file */
	void	(*close)(void * hnd);

	/* Read from a previously opened file */
	ssize_t	(*read)(void * hnd, void *buffer, size_t cnt);

	/* Write to a previously opened file */
	ssize_t	(*write)(void * hnd, const void *buffer, size_t cnt);

	/* Seek in a previously opened file */
	off_t	(*seek)(void * hnd, off_t offset, int whence);

	/* Return the current position in a previously opened file */
	off_t	(*tell)(void * hnd);

	/* Return the total size of a previously opened file */
	size_t	(*total)(void * hnd);

	/* Read the next directory entry in a directory opened with O_DIR */
	dirent_t* (*readdir)(void * hnd);

	/* Execute a device-specific call on a previously opened file */
	int	(*ioctl)(void * hnd, void *data, size_t size);

	/* Rename/move a file on the given VFS */
	int	(*rename)(struct vfs_handler * vfs, const char *fn1, const char *fn2);

	/* Delete a file from the given VFS */
	int	(*unlink)(struct vfs_handler * vfs, const char *fn);

	/* "Memory map" a previously opened file */
	void*	(*mmap)(void * fd);

	/* Perform an I/O completion (async I/O) for a previously opened file */
	int	(*complete)(void * fd, ssize_t * rv);

	/* Get status information on a file on the given VFS */
	int	(*stat)(struct vfs_handler * vfs, const char * fn, stat_t * rv);

	/* Make a directory on the given VFS */
	int	(*mkdir)(struct vfs_handler * vfs, const char * fn);

	/* Remove a directory from the given VFS */
	int	(*rmdir)(struct vfs_handler * vfs, const char * fn);
} vfs_handler_t;

/* This is the number of distinct file descriptors the global table
   has in it. */
#define FD_SETSIZE	1024

/* This is the private struct that will be used as raw file handles
   underlying descriptors. */
struct fs_hnd;

/* The kernel-wide file descriptor table. These will reference to open files. */
extern struct fs_hnd * fd_table[FD_SETSIZE];

/* Open modes */
#include <sys/fcntl.h>
#if 0
#define O_RDONLY	1		/* Read only */
#define O_RDWR		2		/* Read-write */
#define O_APPEND	3		/* Append to an existing file */
#define O_WRONLY	4		/* Write-only */
#endif
//#define O_MODE_MASK	7		/* Mask for mode numbers */
#define O_MODE_MASK	0x0f		/* Mask for mode numbers */
//#define O_TRUNC		0x0100		/* Truncate */
#define O_ASYNC		0x0200		/* Open for asynchronous I/O */
//#define O_NONBLOCK	0x0400		/* Open for non-blocking I/O */
#define O_DIR		0x1000		/* Open as directory */
#define O_META		0x2000		/* Open as metadata */

/* Seek modes */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Standard file descriptor functions */
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
int	fs_complete(file_t fd, ssize_t * rv);
int	fs_stat(const char * fn, stat_t * rv);
int	fs_mkdir(const char * fn);
int	fs_rmdir(const char * fn);
file_t	fs_dup(file_t oldfd);
file_t	fs_dup2(file_t oldfd, file_t newfd);

/* Call this function to create a "transient" file descriptor. What this
   does for you is let you setup ad-hoc VFS integration for libs that
   have their own open mechanism (e.g., TCP/IP sockets). It could also be
   used to do things like generic resource management. Calling this
   function is functionally identical to fs_open, except it doesn't
   require registering a full VFS or doing a name lookup. */
file_t	fs_open_handle(vfs_handler_t * vfs, void * hnd);

/* These two functions are used to reveal "internal" info about a file
   descriptor, so that libraries can provide their own facilities using
   VFS-sponsored file descriptors (e.g., TCP/IP bind, connect, etc). */
vfs_handler_t * fs_get_handler(file_t fd);
void * fs_get_handle(file_t fd);

/* Returns the working directory of the current thread */
const char *fs_getwd();

/* Couple of util functions */

/* Copies a file from 'src' to 'dst'. The amount of the file
   actually copied without error is returned. */
ssize_t	fs_copy(const char * src, const char * dst);

/* Opens a file, allocates enough RAM to hold the whole thing,
   reads it into RAM, and closes it. The caller owns the allocated
   memory (and must free it). The file size is returned, or -1
   on failure; on success, out_ptr is filled with the address
   of the loaded buffer, and on failure it is set to NULL. */
ssize_t fs_load(const char * src, void ** out_ptr);

/* VFS init */
int	fs_init();
void 	fs_shutdown();

__END_DECLS

#endif	/* __KOS_FS_H */

