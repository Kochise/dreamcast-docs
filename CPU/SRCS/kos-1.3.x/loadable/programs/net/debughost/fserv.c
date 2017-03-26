/* KallistiOS ##version##

   fserv.c
   Copyright (C)2003 Dan Potter

   $Id: fserv.c,v 1.1 2003/07/18 08:13:27 bardtx Exp $
*/

#include <kos.h>
#include <string.h>
#include <errno.h>
#include "debug.h"

///////////////////////////////////////////////////////////////////

static nconn_t * nc;
static mutex_t * mutex;

typedef struct {
	uint32		magic;
	dirent_t	* dirlist;
	int		dirsize;
	int		cur;
} dirquery_t;

///////////////////////////////////////////////////////////////////

static void * fserv_opendir(const char * fn) {
	char	buf[256], * sz;
	void	* rfd = NULL;
	int	i, cnt;
	dirquery_t	* dq;

	mutex_lock(mutex);

	if (*fn == 0)
		fn = "/";

	// Send a listdir request
	sprintf(buf, "ListDir: %s\r\n", fn);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get back the result
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Parse the line
	if (!strncmp(buf, "Error", 5)) {
		errno = atoi(buf + 7);
		goto out;
	}
	cnt = atoi(buf + 4);

	// Alloc space for stuff
	dq = calloc(1, sizeof(dirquery_t));
	dq->magic = 0xdeadbeef;
	dq->dirlist = calloc(cnt, sizeof(dirent_t));
	dq->dirsize = cnt;
	dq->cur = 0;

	// Now read each entry
	for (i=0; i<cnt; i++) {
		// Read a line
		if (net_read_line(nc->fservsock, buf, 256) < 0) {
			free(dq->dirlist);
			free(dq);
			errno = EIO;
			goto out;
		}

		// Split it
		sz = strchr(buf, '/');
		if (sz == NULL) {
			tty_printf("fserv: malformed listdir line '%s'\n", buf);
			continue;
		}
		*sz = 0; sz++;

		// Copy out the pieces
		dq->dirlist[i].size = atoi(sz);
		strcpy(dq->dirlist[i].name, buf);
		dq->dirlist[i].time = 0;
		dq->dirlist[i].attr = 0;
	}

	// Send back the dirquery as the handle
	rfd = (void *)dq;

out:
	mutex_unlock(mutex);
	return rfd;
}

static void * fserv_open(vfs_handler_t * vfs, const char *fn, int mode) {
	char buf[256];
	int rfd = 0;
	
	// Are they asking for a dir?
	if (mode & O_DIR)
		return fserv_opendir(fn);

	mutex_lock(mutex);

	// Send an open request
	sprintf(buf, "Open: %s %d\r\n", fn, mode);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get back the file descriptor
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Parse the line
	if (!strncmp(buf, "Error", 5)) {
		errno = atoi(buf + 7);
		goto out;
	}

	rfd = atoi(buf + 4);

out:
	mutex_unlock(mutex);
	return (void *)rfd;
}

static void fserv_close(void * h) {
	char buf[256];

	// Is it a dirquery?
	// XXX: this is hacky but should work most of the time
	if ((ptr_t)h > 10000 && !((ptr_t)h & ~3)) {
		dirquery_t * dq = (dirquery_t *)h;
		if (dq->magic == 0xdeadbeef) {
			free(dq->dirlist);
			free(dq);
			return;
		}
	}

	mutex_lock(mutex);

	// Send a close request
	sprintf(buf, "Close: %d\r\n", (int)h);
	if (net_write_line(nc->fservsock, buf) >= 0) {
		// Read the response (and ignore)
		net_read_line(nc->fservsock, buf, 256);
	}

	mutex_unlock(mutex);
}

static ssize_t fserv_read(void * h, void *obuf, size_t cnt) {
	char buf[256];
	ssize_t rv = -1;

	mutex_lock(mutex);

	// Send a read request
	sprintf(buf, "Read: %d %d\r\n", (int)h, cnt);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get the response
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Was it an error?
	if (!strncmp(buf, "Error: ", 7)) {
		// Get the errno code
		errno = atoi(buf + 7);
		goto out;
	}

	// Ok, parse out the return value
	rv = atoi(buf + 4);

	// And read the data
	if (net_read_reliably(nc->fservsock, obuf, rv) < 0) {
		errno = EIO;
		rv = -1;
	}

out:
	mutex_unlock(mutex);
	return rv;
}

static ssize_t fserv_write(void * h, const void *ibuf, size_t cnt) {
	char buf[256];
	ssize_t rv = -1;

	mutex_lock(mutex);

	// Send a write request
	sprintf(buf, "Write: %d %d\r\n", (int)h, cnt);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// And write the data
	if (net_write_reliably(nc->fservsock, ibuf, cnt) < 0) {
		errno = EIO;
		rv = -1;
	}

	// Get the response
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Was it an error?
	if (!strncmp(buf, "Error: ", 7)) {
		// Get the errno code
		errno = atoi(buf + 7);
		goto out;
	}

	// Ok, parse out the return value
	rv = atoi(buf + 4);

out:
	mutex_unlock(mutex);
	return rv;
}

static off_t fserv_seek(void * h, off_t offset, int whence) {
	char buf[256];
	ssize_t rv = -1;

	mutex_lock(mutex);

	// Send a seek request
	sprintf(buf, "Seek: %d %d %d\r\n", (int)h, offset, whence);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get the response
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Was it an error?
	if (!strncmp(buf, "Error: ", 7)) {
		// Get the errno code
		errno = atoi(buf + 7);
		goto out;
	}

	// Ok, parse out the return value
	rv = atoi(buf + 4);

out:
	mutex_unlock(mutex);
	return rv;
}

static off_t fserv_tell(void * h) {
	char buf[256];
	ssize_t rv = -1;

	mutex_lock(mutex);

	// Send a non-seeking seek request
	sprintf(buf, "Seek: %d 0 1\r\n", (int)h);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get the response
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Was it an error?
	if (!strncmp(buf, "Error: ", 7)) {
		// Get the errno code
		errno = atoi(buf + 7);
		goto out;
	}

	// Ok, parse out the return value
	rv = atoi(buf + 4);

out:
	mutex_unlock(mutex);
	return rv;
}

static size_t fserv_total(void * h) {
	char buf[256];
	ssize_t rv = -1;

	mutex_lock(mutex);

	// Send a total request
	sprintf(buf, "Total: %d\r\n", (int)h);
	if (net_write_line(nc->fservsock, buf) < 0) {
		errno = EIO;
		goto out;
	}

	// Get the response
	if (net_read_line(nc->fservsock, buf, 256) < 0) {
		errno = EIO;
		goto out;
	}

	// Was it an error?
	if (!strncmp(buf, "Error: ", 7)) {
		// Get the errno code
		errno = atoi(buf + 7);
		goto out;
	}

	// Ok, parse out the return value
	rv = atoi(buf + 4);

out:
	mutex_unlock(mutex);
	return rv;
}

static dirent_t *fserv_readdir(void * h) {
	dirquery_t * dq = (dirquery_t *)h;

	if (dq->magic != 0xdeadbeef) {
		errno = EINVAL;
		return NULL;
	}

	// At the end yet?
	if (dq->cur >= dq->dirsize)
		return NULL;

	// Find the next entry
	return dq->dirlist + (dq->cur++);
}

static int fserv_rename(vfs_handler_t * vfs, const char *fn1, const char *fn2) {
	return -1;
}

static int fserv_unlink(vfs_handler_t * vfs, const char *fn) {
	return -1;
}

///////////////////////////////////////////////////////////////////

static vfs_handler_t vh = {
	{
		"/pc",
		0,
		0x00010000,
		0,
		NMMGR_TYPE_VFS,
		NMMGR_LIST_INIT
	},

	0, NULL,

	fserv_open,
	fserv_close,
	fserv_read,
	fserv_write,
	fserv_seek,
	fserv_tell,
	fserv_total,
	fserv_readdir,
	NULL,		// ioctl
	fserv_rename,
	fserv_unlink,
	NULL		// mmap
};

static int active = 0;

int fserv_init(nconn_t * inc) {
	if (active) {
		tty_printf("fserv: already active!\n");
		return -1;
	}

	active = 1;
	nc = inc;
	mutex = mutex_create();
	tty_printf("fserv: active for client %d\n", nc->socket);
	
	return nmmgr_handler_add(&vh.nmmgr);
}

int fserv_shutdown() {
	int i = nc->socket;

	nmmgr_handler_remove(&vh.nmmgr);
	nc = NULL;
	mutex_destroy(mutex);
	active = 0;

	tty_printf("fserv: shut down for client %d\n", i);
	
	return 0;
}
