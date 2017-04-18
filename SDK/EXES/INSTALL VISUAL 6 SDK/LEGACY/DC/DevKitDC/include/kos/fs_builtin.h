/* KallistiOS 1.1.6

   kos/fs_builtin.h
   (c)2000-2001 Dan Potter

   $Id: fs_builtin.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __KOS_FS_BUILTIN_H
#define __KOS_FS_BUILTIN_H

/* Definitions for the "built-in" file system */

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/limits.h>
#include <kos/fs.h>

typedef struct {
	char	name[MAX_FN_LEN];	/* File's full path name */
	uint8	*data;			/* Data for the file */
	uint32	size;			/* Data size */
} fs_builtin_ent;


/* Set a table */
int fs_builtin_set_table(fs_builtin_ent *tbl, int cnt);

/* File functions */
uint32	fsb_open(const char *fn, int mode);
void	fsb_close(uint32 hnd);
ssize_t	fsb_read(uint32 hnd, void *buf, size_t cnt);
off_t	fsb_seek(uint32 hnd, off_t offset, int whence);
off_t	fsb_tell(uint32 hnd);
size_t	fsb_total(uint32 hnd);
void*	fsb_mmap(uint32 hnd);

/* Init func */
int fs_builtin_init();
int fs_builtin_shutdown();

__END_DECLS

#endif	/* __KOS_FS_BUILTIN_H */


