/* KallistiOS ##version##

   kos/fs.h
   (c)2000-2001 Dan Potter

   $Id: fs.h,v 1.9 2002/10/01 03:19:59 bardtx Exp $

*/

#ifndef __KOS_FS_H
#define __KOS_FS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <time.h>
#include <sys/queue.h>

/* Directory entry; all handlers must conform to this interface */
typedef struct dirent {
	int	size;
	char	name[MAX_FN_LEN];
	time_t	time;
	uint32	attr;
} dirent_t;

/* File status information; like dirent, this is not the same as the *nix
   variation but it has similar information. */
struct vfs_handler_str;
typedef struct stat {
	struct vfs_handler_str	* dev;		/* The VFS handler for this file/dir */
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

/* File handle type */
typedef uint32 file_t;

/* Invalid file handle constant (for open failure, etc) */
#define FILEHND_INVALID	((file_t)0)

/* Pre-define list types */
struct vfs_handler;
typedef LIST_HEAD(vfs_list, vfs_handler) vfs_list_t;

/* List entry initializer for static structs */
#define VFS_LIST_INIT { NULL }

/* Handler interface; all VFS handlers must implement this interface. */
typedef struct vfs_handler {
	char	prefix[MAX_FN_LEN];	/* Path prefix */
	int	pid;			/* Process table ID for handler (0 == static) */
	int	cache;			/* Allow VFS cacheing; 0=no, 1=yes */
	void	* privdata;		/* Pointer to private data for the handler */
	LIST_ENTRY(vfs_handler)	list_ent;	/* Linked list entry */

	/* Open a file on the given VFS; return a unique identifier */
	file_t	(*open)(struct vfs_handler * vfs, const char *fn, int mode);

	/* Close a previously opened file */
	void	(*close)(file_t hnd);

	/* Read from a previously opened file */
	ssize_t	(*read)(file_t hnd, void *buffer, size_t cnt);

	/* Write to a previously opened file */
	ssize_t	(*write)(file_t hnd, const void *buffer, size_t cnt);

	/* Seek in a previously opened file */
	off_t	(*seek)(file_t hnd, off_t offset, int whence);

	/* Return the current position in a previously opened file */
	off_t	(*tell)(file_t hnd);

	/* Return the total size of a previously opened file */
	size_t	(*total)(file_t hnd);

	/* Read the next directory entry in a directory opened with O_DIR */
	dirent_t* (*readdir)(file_t hnd);

	/* Execute a device-specific call on a previously opened file */
	int	(*ioctl)(file_t hnd, void *data, size_t size);

	/* Rename/move a file on the given VFS */
	int	(*rename)(struct vfs_handler * vfs, const char *fn1, const char *fn2);

	/* Delete a file from the given VFS */
	int	(*unlink)(struct vfs_handler * vfs, const char *fn);

	/* "Memory map" a previously opened file */
	void*	(*mmap)(file_t fd);

	/* Perform an I/O completion (async I/O) for a previously opened file */
	int	(*complete)(file_t fd, ssize_t * rv);

	/* Get status information on a file on the given VFS */
	int	(*stat)(struct vfs_handler * vfs, const char * fn, stat_t * rv);

	/* Make a directory on the given VFS */
	int	(*mkdir)(struct vfs_handler * vfs, const char * fn);

	/* Remove a directory from the given VFS */
	int	(*rmdir)(struct vfs_handler * vfs, const char * fn);
} vfs_handler_t;


/* Open modes */
#define O_RDONLY	1		/* Read only */
#define O_RDWR		2		/* Read-write */
#define O_APPEND	3		/* Append to an existing file */
#define O_WRONLY	4		/* Write-only */
#define O_MODE_MASK	7		/* Mask for mode numbers */
#define O_TRUNC		0x0100		/* Truncate */
#define O_ASYNC		0x0200		/* Open for asynchronous I/O */
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
int	fs_complete(file_t fd, ssize_t * rv);
int	fs_stat(const char * fn, stat_t * rv);
int	fs_mkdir(const char * fn);
int	fs_rmdir(const char * fn);

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

/* Add/Remove a VFS module */
int	fs_handler_add(const char *prefix, vfs_handler_t *hnd);
int	fs_handler_remove(const vfs_handler_t *hnd);

/* VFS init */
int	fs_init();
void 	fs_shutdown();

__END_DECLS

#endif	/* __KOS_FS_H */

