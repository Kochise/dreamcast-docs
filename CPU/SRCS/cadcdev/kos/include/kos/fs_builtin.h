/* KallistiOS ##version##

   kos/fs_builtin.h
   (c)2000-2001 Dan Potter

   $Id: fs_builtin.h,v 1.3 2002/08/12 18:43:53 bardtx Exp $
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

/* Init func */
int fs_builtin_init();
int fs_builtin_shutdown();

__END_DECLS

#endif	/* __KOS_FS_BUILTIN_H */


