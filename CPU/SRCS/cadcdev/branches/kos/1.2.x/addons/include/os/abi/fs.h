/* KallistiOS ##version##

   os/abi/fs.h
   (c)2000 Dan Potter

   $Id: fs.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $
*/

#ifndef __OS_ABI_FS_H
#define __OS_ABI_FS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>
#include <kos/fs.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	file_t		(*open)(const char *fn, int mode);
	void		(*close)(file_t hnd);
	ssize_t		(*read)(file_t hnd, void *buffer, size_t cnt);
	ssize_t		(*write)(file_t hnd, const void *buffer, size_t cnt);
	off_t		(*seek)(file_t hnd, off_t offset, int whence);
	off_t		(*tell)(file_t hnd);
	size_t		(*total)(file_t hnd);
	dirent_t*	(*readdir)(file_t hnd);
	int		(*ioctl)(file_t hnd, void *data, size_t size);
	int		(*rename)(const char *fn1, const char *fn2);
	int		(*unlink)(const char *fn);
	int		(*chdir)(const char *fn);
	void *		(*mmap)(file_t fd);
	const char *	(*getwd)();
	uint32		padding0[32 - 13];
	
	int		(*handler_add)(const char *prefix, vfs_handler *hnd);
	int		(*handler_remove)(const vfs_handler *hnd);
} abi_fs_t;

__END_DECLS

#endif	/* __OS_ABI_FS_H */

