/* KallistiOS ##version##

   fs.c
   Copyright (C)2000,2001,2002,2003 Dan Potter

*/

/*

This module manages all of the file system code. Basically the VFS works
something like this:

- The kernel contains path primitives. There is a table of VFS path handlers
  installed by loaded servers. When the kernel needs to open a file, it will
  search this path handler table from the bottom until it finds a handler
  that is willing to take the request. The request is then handed off to
  the handler. (This function is now handled by the name manager.)
- The path handler receives the part of the path that is left after the
  part in the handler table. The path handler should return an internal
  handle for accessing the file. An internal handle of zero is always 
  assumed to mean failure.
- The kernel open function takes this value and wraps it in a structure that
  describes which service handled the request, and its internal handle.
- Subsequent operations go through this abstraction layer to land in the
  right place.

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <kos/fs.h>
#include <kos/thread.h>
#include <kos/mutex.h>
#include <kos/nmmgr.h>

CVSID("$Id: fs.c,v 1.10 2003/07/31 00:39:08 bardtx Exp $");

/* File handle structure; this is an entirely internal structure so it does
   not go in a header file. */
typedef struct fs_hnd {
	vfs_handler_t	*handler;	/* Handler */
	void *		hnd;		/* Handler-internal */
	int		refcnt;		/* Reference count */
} fs_hnd_t;

/* The global file descriptor table */
fs_hnd_t * fd_table[FD_SETSIZE] = { NULL };


/* Internal file commands for root dir reading */
static fs_hnd_t * fs_root_opendir() {
	fs_hnd_t	*hnd;

	hnd = malloc(sizeof(fs_hnd_t));
	hnd->handler = NULL;
	hnd->hnd = 0;
	hnd->refcnt = 0;
	return hnd;
}

/* Not thread-safe right now */
static dirent_t root_readdir_dirent;
static dirent_t *fs_root_readdir(fs_hnd_t * handle) {
	nmmgr_handler_t	*nmhnd;
	nmmgr_list_t	*nmhead;
	int 		cnt;

	cnt = (int)handle->hnd;

	nmhead = nmmgr_get_list();

	LIST_FOREACH(nmhnd, nmhead, list_ent) {
		if (nmhnd->type != NMMGR_TYPE_VFS)
			continue;
		if (!(cnt--))
			break;
	}
	if (nmhnd == NULL)
		return NULL;

	root_readdir_dirent.size = -1;
	if (nmhnd->pathname[0] == '/')
		strcpy(root_readdir_dirent.name, nmhnd->pathname+1);
	else
		strcpy(root_readdir_dirent.name, nmhnd->pathname);
	handle->hnd = (void *)((int)handle->hnd + 1);

	return &root_readdir_dirent;
}

/* This version of open deals with raw handles only. This is below the level
   of file descriptors. It is used by the standard fs_open below. The
   returned handle will have no references attached to it. */
static fs_hnd_t * fs_hnd_open(const char *fn, int mode) {
	nmmgr_handler_t	*nmhnd;
	vfs_handler_t	*cur;
	const char	*cname;
	void		*h;
	fs_hnd_t	*hnd;
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return NULL;

	/* Are they trying to open the root? */
	if (!strcmp(rfn, "/")) {
		if ((mode & O_DIR)) 
			return fs_root_opendir();
		else {
			errno = EISDIR;
			return NULL;
		}
	}

	/* Look for a handler */
	nmhnd = nmmgr_lookup(rfn);
	if (nmhnd == NULL || nmhnd->type != NMMGR_TYPE_VFS) {
		errno = ENOENT;
		return NULL;
	}
	cur = (vfs_handler_t *)nmhnd;

	/* Found one -- get the "canonical" path name */
	cname = rfn + strlen(nmhnd->pathname);

	/* Invoke the handler */
	if (cur->open == NULL) {
		errno = ENOSYS;
		return 0;
	}
	h = cur->open(cur, cname, mode);
	if (h == NULL) return NULL;

	/* Wrap it up in a structure */
	hnd = malloc(sizeof(fs_hnd_t));
	if (hnd == NULL) {
		cur->close(h);
		errno = ENOMEM;
		return NULL;
	}
	hnd->handler = cur;
	hnd->hnd = h;
	hnd->refcnt = 0;

	return hnd;
}

/* Reference a file handle. This should be called when a persistent reference
   to a raw handle is created somewhere. */
static void fs_hnd_ref(fs_hnd_t * ref) {
	assert( ref );
	assert( ref->refcnt < (1 << 30) );
	ref->refcnt++;
}

/* Unreference a file handle. Should be called when a persistent reference
   to a raw handle is no longer applicable. This function may destroy the
   file handle, so under no circumstances should you presume that it will
   still exist later. */
static void fs_hnd_unref(fs_hnd_t * ref) {
	assert( ref );
	assert( ref->refcnt > 0 );
	ref->refcnt--;

	if (ref->refcnt == 0) {
		if (ref->handler != NULL) {
			if (ref->handler->close == NULL) return;
			ref->handler->close(ref->hnd);
		}
		free(ref);
	}
}

/* Assigns a file descriptor (index) to a file handle (pointer). Will auto-
   reference the handle, and unrefs on error. */
static int fs_hnd_assign(fs_hnd_t * hnd) {
	int i;

	fs_hnd_ref(hnd);

	/* XXX Not thread-safe! */
	for (i=0; i<FD_SETSIZE; i++)
		if (!fd_table[i])
			break;
	if (i >= FD_SETSIZE) {
		fs_hnd_unref(hnd);
		errno = EMFILE;
		return -1;
	}
	fd_table[i] = hnd;

	return i;
}

int fs_fdtbl_destroy() {
	int i;

	for (i=0; i<FD_SETSIZE; i++) {
		if (fd_table[i])
			fs_hnd_unref(fd_table[i]);
		fd_table[i] = NULL;
	}

	return 0;
}

/* Attempt to open a file, given a path name. Follows the process described
   in the above comments. */
file_t fs_open(const char *fn, int mode) {
	fs_hnd_t * hnd;

	/* First try to open the file handle */
	hnd = fs_hnd_open(fn, mode);
	if (!hnd)
		return -1;

	/* Ok, that succeeded -- now look for a file descriptor. */
	return fs_hnd_assign(hnd);
}

/* See header for comments */
file_t fs_open_handle(vfs_handler_t * vfs, void * vhnd) {
	fs_hnd_t * hnd;

	/* Wrap it up in a structure */
	hnd = malloc(sizeof(fs_hnd_t));
	if (hnd == NULL) {
		errno = ENOMEM;
		return -1;
	}
	hnd->handler = vfs;
	hnd->hnd = vhnd;
	hnd->refcnt = 0;

	/* Ok, that succeeded -- now look for a file descriptor. */
	return fs_hnd_assign(hnd);
}

vfs_handler_t * fs_get_handler(file_t fd) {
	/* Make sure it exists */
	if (!fd_table[fd]) {
		errno = EBADF;
		return NULL;
	}

	return fd_table[fd]->handler;
}

void * fs_get_handle(file_t fd) {
	/* Make sure it exists */
	if (!fd_table[fd]) {
		errno = EBADF;
		return NULL;
	}

	return fd_table[fd]->hnd;
}

file_t fs_dup(file_t oldfd) {
	/* Make sure it exists */
	if (!fd_table[oldfd]) {
		errno = EBADF;
		return -1;
	}

	return fs_hnd_assign(fd_table[oldfd]);
}

file_t fs_dup2(file_t oldfd, file_t newfd) {
	if (!fd_table[oldfd]) {
		errno = EBADF;
		return -1;
	}

	if (fd_table[newfd])
		fs_close(newfd);
	fd_table[newfd] = fd_table[oldfd];
	fs_hnd_ref(fd_table[newfd]);

	return newfd;
}

/* Returns a file handle for a given fd, or NULL if the parameters
   are not valid. */
static fs_hnd_t * fs_map_hnd(file_t fd) {
	if (fd < 0 || fd >= FD_SETSIZE) {
		errno = EBADF;
		return NULL;
	}
	if (!fd_table[fd]) {
		errno = EBADF;
		return NULL;
	}

	return fd_table[fd];
}

/* Close a file and clean up the handle */
void fs_close(file_t fd) {
	fs_hnd_t * hnd = fs_map_hnd(fd);
	if (!hnd) return;

	/* Deref it and remove it from our table */
	fs_hnd_unref(hnd);
	fd_table[fd] = NULL;
}

/* The rest of these pretty much map straight through */
ssize_t fs_read(file_t fd, void *buffer, size_t cnt) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->read == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->read(h->hnd, buffer, cnt);
}

ssize_t fs_write(file_t fd, const void *buffer, size_t cnt) {
	fs_hnd_t *h;

	// XXX This is a hack to make newlib printf work because it
	// doesn't like fs_pty. I'll figure out why later...
	if (fd == 1 || fd == 2) {
		dbgio_write_buffer_xlat((const uint8 *)buffer, cnt);
		return cnt;
	}

	h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->write == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->write(h->hnd, buffer, cnt);
}

off_t fs_seek(file_t fd, off_t offset, int whence) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->seek == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->seek(h->hnd, offset, whence);
}

off_t fs_tell(file_t fd) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->tell == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->tell(h->hnd);
}

size_t fs_total(file_t fd) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->total == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->total(h->hnd);
}

dirent_t *fs_readdir(file_t fd) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return NULL;
	if (h->handler == NULL) return fs_root_readdir(h);
	if (h->handler->readdir == NULL) {
		errno = EINVAL;
		return NULL;
	}
	errno = 0;
	return h->handler->readdir(h->hnd);
}

int fs_ioctl(file_t fd, void *data, size_t size) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->ioctl == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->ioctl(h->hnd, data, size);
}

static vfs_handler_t * fs_verify_handler(const char * fn) {
	nmmgr_handler_t	*nh;

	nh = nmmgr_lookup(fn);
	if (nh == NULL || nh->type != NMMGR_TYPE_VFS)
		return NULL;
	else
		return (vfs_handler_t *)nh;
}

int fs_rename(const char *fn1, const char *fn2) {
	vfs_handler_t	*fh1, *fh2;
	char		rfn1[PATH_MAX], rfn2[PATH_MAX];
	
	if (!realpath(fn1, rfn1) || !realpath(fn2, rfn2))
		return -1;

	/* Look for handlers */
	fh1 = fs_verify_handler(rfn1);
	if (fh1 == NULL) {
		errno = ENOENT;
		return -1;
	}
	
	fh2 = fs_verify_handler(rfn2);
	if (fh2 == NULL) {
		errno = ENOENT;
		return -1;
	}
	
	if (fh1 != fh2) {
		errno = EXDEV;
		return -1;
	}

	if (fh1->rename)
		return fh1->rename(fh1, rfn1+strlen(fh1->nmmgr.pathname),
			rfn2+strlen(fh1->nmmgr.pathname));
	else {
		errno = EINVAL;
		return -1;
	}
}

int fs_unlink(const char *fn) {
	vfs_handler_t	*cur;
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return -1;

	/* Look for a handler */
	cur = fs_verify_handler(rfn);
	if (cur == NULL) return 1;

	if (cur->unlink)
		return cur->unlink(cur, rfn+strlen(cur->nmmgr.pathname));
	else {
		errno = EINVAL;
		return -1;
	}
}

int fs_chdir(const char *fn) {
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return -1;

	thd_set_pwd(thd_get_current(), rfn);
	return 0;
}

const char *fs_getwd() {
	return thd_get_pwd(thd_get_current());
}

void *fs_mmap(file_t fd) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return NULL;
	if (h->handler == NULL || h->handler->mmap == NULL) {
		errno = EINVAL;
		return NULL;
	}
	return h->handler->mmap(h->hnd);
}

int fs_complete(file_t fd, ssize_t * rv) {
	fs_hnd_t *h = fs_map_hnd(fd);

	if (h == NULL) return -1;
	if (h->handler == NULL || h->handler->complete == NULL) {
		errno = EINVAL;
		return -1;
	}
	return h->handler->complete(h->hnd, rv);
}

int fs_stat(const char * fn, stat_t * rv) {
	vfs_handler_t	*cur;
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return -1;

	/* Look for a handler */
	cur = fs_verify_handler(rfn);
	if (cur == NULL) return -1;

	if (cur->stat)
		return cur->stat(cur, rfn+strlen(cur->nmmgr.pathname), rv);
	else {
		errno = EINVAL;
		return -1;
	}
}

int fs_mkdir(const char * fn) {
	vfs_handler_t	*cur;
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return -1;

	/* Look for a handler */
	cur = fs_verify_handler(rfn);
	if (cur == NULL) return -1;

	if (cur->mkdir)
		return cur->mkdir(cur, rfn+strlen(cur->nmmgr.pathname));
	else {
		errno = EINVAL;
		return -1;
	}
}

int fs_rmdir(const char * fn) {
	vfs_handler_t	*cur;
	char		rfn[PATH_MAX];

	if (!realpath(fn, rfn))
		return -1;

	/* Look for a handler */
	cur = fs_verify_handler(rfn);
	if (cur == NULL) return -1;

	if (cur->rmdir)
		return cur->rmdir(cur, rfn+strlen(cur->nmmgr.pathname));
	else {
		errno = EINVAL;
		return -1;
	}
}


/* Initialize FS structures */
int fs_init() {
	return 0;
}

void fs_shutdown() {
}
