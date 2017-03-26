/* KallistiOS ##version##

   kos/nmmgr.h
   Copyright (C)2003 Dan Potter

   $Id: nmmgr.h,v 1.1 2003/06/19 04:30:23 bardtx Exp $

*/

#ifndef __KOS_NMMGR_H
#define __KOS_NMMGR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <sys/queue.h>

/* Pre-define list types */
struct nmmgr_handler;
typedef LIST_HEAD(nmmgr_list, nmmgr_handler) nmmgr_list_t;

/* List entry initializer for static structs */
#define NMMGR_LIST_INIT { NULL }

/* Handler interface; all name handlers' must structs must begin with this
   prefix. If the handler conforms to some particular interface, then the
   struct must more specifically be of that type. */
typedef struct nmmgr_handler {
	char	pathname[MAX_FN_LEN];	/* Path name */
	int	pid;			/* Process table ID for handler (0 == static) */
	uint32	version;		/* Version code */
	uint32	flags;			/* Bitmask of flags */
	uint32	type;			/* Type of handler */
	LIST_ENTRY(nmmgr_handler)	list_ent;	/* Linked list entry */
} nmmgr_handler_t;

/* Version codes ('version') have two pieces: a major and minor revision.
   A major revision (top 16 bits) means that the interfaces are totally
   incompatible. A minor revision (lower 16 bits) diffrentiates between
   mostly-compatible but newer/older revisions of the implementing code. */

/* Flag bits */
#define NMMGR_FLAGS_NEEDSFREE	0x00000001	/* We need to free() this struct on remove */

/* Name handler types. All "system" types are defined below 0x10000. */
#define NMMGR_TYPE_UNKNOWN	0x0000		/* ? */
#define NMMGR_TYPE_VFS		0x0010		/* Mounted file system */
#define NMMGR_TYPE_BLOCKDEV	0x0020		/* Block device */
#define NMMGR_TYPE_SINGLETON	0x0030		/* Singleton service (e.g., /dev/irq) */
#define NMMGR_TYPE_SYMTAB	0x0040		/* Symbol table */
#define NMMGR_SYS_MAX		0x10000		/* Here and above are user types */

/* Given a pathname, return the name handler corresponding to it
   (or NULL if there is none). */
nmmgr_handler_t * nmmgr_lookup(const char *name);

/* Get the head element of our name list. This is for READ-ONLY PURPOSES ONLY. */
nmmgr_list_t * nmmgr_get_list();

/* Add/Remove a name handler module */
int	nmmgr_handler_add(nmmgr_handler_t *hnd);
int	nmmgr_handler_remove(nmmgr_handler_t *hnd);

/* Name manager init */
int	nmmgr_init();
void 	nmmgr_shutdown();

__END_DECLS

#endif	/* __KOS_NMMGR_H */

