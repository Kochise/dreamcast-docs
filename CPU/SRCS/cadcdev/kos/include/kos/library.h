/* KallistiOS ##version##

   include/kos/library.h
   Copyright (C)2003 Dan Potter

   $Id$

*/

#ifndef __KOS_LIBRARY_H
#define __KOS_LIBRARY_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/thread.h>
#include <kos/elf.h>
#include <kos/fs.h>

/* Pre-define list/queue types */
struct klibrary;
TAILQ_HEAD(klqueue, klibrary);
LIST_HEAD(kllist, klibrary);

/* Thread IDs are ok for us */
typedef tid_t libid_t;

/* Structure describing one loaded library. Each lib basically consists of
   a set of loaded program code and a set of standard exported entry points. */
typedef struct klibrary {
	/* Library list handle */
	LIST_ENTRY(klibrary)	list;

	/* Kernel library id */
	libid_t	libid;

	/* Flags */
	uint32	flags;

	/* ELF program image for this library */
	elf_prog_t image;

	/* The library's reference count. If it is opened more than once, this
	   will go to >1 values. The library is actually shut down and removed
	   if this reaches zero. */
	int refcnt;

	/* Standard library entry points. Every loaded library must provide
	   at least these things. */

	/* Return a pointer to a string containing the library's symbolic
	   name. Must work before calling lib_open. */
	const char * (*lib_get_name)();

	/* Return an integer containing the library's version ID. Must work
	   before calling lib_open. */
	uint32 (*lib_get_version)();

	/* "Open" the library (i.e., init and/or increase ref count). Return
	   >= 0 value here to signal success. If failure is signaled on the
	   first lib_open, it is assumed we can remove this library from memory. */
	int (*lib_open)(struct klibrary * lib);

	/* "Close" the library (i.e., dec ref count and/or shut down). Return
	   >= 0 on success or < 0 on failure. */
	int (*lib_close)(struct klibrary * lib);
} klibrary_t;

/* Library flag values */
#define LIBRARY_DEFAULTS	0	/* Defaults: no flags */

/* Library list; note: do not manipulate directly */
extern struct kllist library_list;

/* Given a library ID, locates the lib structure */
klibrary_t *library_by_libid(libid_t libid);

/* New library shell function. When you want to load a new library, this
   function will handle that for you. This will generally only be used by
   the library code internally. */
klibrary_t *library_create(int flags);

/* Given a library handle, this function removes the library from the library
   list. Any remaining resources assigned to this library will be freed. This
   will generally only be used by the library code internally. */
int library_destroy(klibrary_t *lib);

/* Try to open a library by symbolic name. If the library open fails, then
   attempt to load the library from the given filename. If this fails, then
   return NULL for error. On success, return a handle to the library;
   lib_open will already have been called. */
klibrary_t * library_open(const char * name, const char * fn);

/* Look up a library by name without trying to load or open it. This is
   useful if you want to open a library in one place and not have to keep
   track of the handle to close it later. */
klibrary_t * library_lookup(const char * name);

/* Close a previously opened library. If this fails, return < 0 for error. If
   it succeeds, return > 0; lib_close will already have been called, and the
   library may have been destroyed as well (do NOT try to use it again). */
int library_close(klibrary_t * lib);

/* Retrieve library's libid (runtime ID) */
libid_t library_get_libid(klibrary_t * lib);

/* Retrieve library's reference count */
int library_get_refcnt(klibrary_t * lib);

/* Retrieve library's name */
const char * library_get_name(klibrary_t * lib);

/* Retrieve library's version */
uint32 library_get_version(klibrary_t * lib);

/* Init */
int library_init();

/* Shutdown */
void library_shutdown();

__END_DECLS

#endif	/* __KOS_LIBRARY_H */

