/* KallistiOS ##version##

   kos/exports.h
   Copyright (C)2003 Dan Potter

   $Id: exports.h,v 1.1 2003/06/19 04:30:23 bardtx Exp $

*/

#ifndef __KOS_EXPORTS_H
#define __KOS_EXPORTS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* This struct holds one export symbol that will be patched into
   loaded ELF files. */
typedef struct export_sym {
	const char 	* name;
	unsigned long	ptr;
} export_sym_t;

/* These are the platform-independent exports */
extern export_sym_t kernel_symtab[];

/* And these are the arch-specific exports */
extern export_sym_t arch_symtab[];

#ifndef __EXPORTS_FILE
#include <kos/nmmgr.h>
/* This struct defines a symbol table "handler" for nmmgr. */
typedef struct symtab_handler {
	/* Name manager handler header */
	struct nmmgr_handler	nmmgr;

	/* Location of the first entry */
	export_sym_t		* table;
} symtab_handler_t;
#endif

/* Setup our initial exports */
int export_init();

/* Look up a symbol by name. Returns the struct. */
export_sym_t * export_lookup(const char * name);

__END_DECLS

#endif	/* __KOS_EXPORTS_H */

