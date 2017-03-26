/* KallistiOS ##version##

   fs_ramdisk.c
   (c)2002 Dan Potter

*/

/*

This module implements a very simple file-based ramdisk file system. What this means 
is that instead of setting up a block of memory as a virtual block device like
many operating systems would do, this file system keeps the directory structure
and file data in allocated chunks of RAM. This also means that the ramdisk can
get as big as the memory available, there's no arbitrary limit.

A note of warning about thread usage here as well. This FS is protected against
thread contention at a file handle and data structure level. This means that the
directory structures and the file handles will never become inconsistent. However,
it is not protected at the individual file level. Because of this limitation, only
one file handle may be open to an individual file for writing at any given time.
If the file is already open for reading, it cannot be written to. Likewise, if
the file is open for writing, you can't open it for reading or writing.

So for example, if you wanted to cache an MP3 in the ramdisk, you'd copy the data
to the ramdisk in write mode, then close the file and let the library re-open it
in read-only mode. You'd then be safe.

So at the moment this is mainly useful as a scratch space for temp files or to
cache data from disk rather than as a general purpose file system.

*/

#include <kos/thread.h>
#include <kos/mutex.h>
#include <kos/fs_ramdisk.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

CVSID("$Id: fs_ramdisk.c,v 1.5 2003/04/24 03:00:02 bardtx Exp $");

/* File definition */
typedef struct rd_file {
	char	* name;		/* File name -- allocated */
	uint32	size;		/* Actual file size */
	int	type;		/* File type */
	int	openfor;	/* Lock constant */
	int	usage;		/* Usage count (unopened is 0) */

	/* For the following two members:
	  - In files, this is a block of allocated memory containing the
	    actual file data. Each time we need to expand it beyond its
	    current capacity, we realloc() with enough to hold the new
	    data plus 4k (to avoid realloc thrashing). All files start
	    out with a 1K block of space.
	  - In directories, this is just a pointer to an rd_dir struct,
	    which is defined below. datasize has no meaning for a 
	    directory. */
	void	* data;		/* Data block pointer */
	uint32	datasize;	/* Size of data block pointer */
	
	LIST_ENTRY(rd_file)	dirlist;	/* Directory list entry */
} rd_file_t;

/* Lock constants */
#define OPENFOR_NOTHING	0	/* Not opened */
#define OPENFOR_READ	1	/* Opened read-only */
#define OPENFOR_WRITE	2	/* Opened read-write */

/* Directory definition -- just basically a list of files we contain */
typedef LIST_HEAD(rd_dir, rd_file) rd_dir_t;

/* Pointer to the root diretctory */
static rd_file_t *root = NULL;
static rd_dir_t  *rootdir = NULL;

/********************************************************************************/
/* File primitives */

#define MAX_RAM_FILES 8

/* File handles.. I could probably do this with a linked list, but I'm just
   too lazy right now. =) */
static struct {
	rd_file_t	* file;		/* ramdisk file struct */
	int		dir;		/* >0 if a directory */
	uint32		ptr;		/* Current read position in bytes */
	dirent_t	dirent;		/* A static dirent to pass back to clients */
} fh[MAX_RAM_FILES];

/* Mutex for file system structs */
static mutex_t * rd_mutex;

/* Search a directory for the named file; return the struct if
   we find it. Assumes we hold rd_mutex. */
static rd_file_t * ramdisk_find(rd_dir_t * parent, const char * name, int namelen) {
	rd_file_t	*f;

	LIST_FOREACH(f, parent, dirlist) {
		if (!strncasecmp(name, f->name, namelen))
			return f;
	}

	return NULL;
}

/* Find a path-named file in the ramdisk. There should not be a
   slash at the beginning, nor at the end. Assumes we hold rd_mutex. */
static rd_file_t * ramdisk_find_path(rd_dir_t * parent, const char * fn, int dir) {
	rd_file_t * f = NULL;
	char * cur;

	/* If the object is in a sub-tree, traverse the tree looking
	   for the right directory */
	while ((cur = strchr(fn, '/'))) {
		/* We've got another part to look at */
		if (cur != fn) {
			/* Look for it in the parent dir.. if it's not a dir
			   itself, something is wrong. */
			f = ramdisk_find(parent, fn, cur - fn);
			if (f == NULL || f->type != STAT_TYPE_DIR)
				return NULL;

			/* Pull out the rd_dir_t pointer */
			parent = (rd_dir_t *)f->data;
			assert( parent != NULL );
		}

		/* Skip the last piece of the pathname */
		fn = cur + 1;
	}

	/* Ok, no more directories */

	/* If there was a remaining file part, then look for it
	   in the dir. */
	if (fn[0] != 0) {
		f = ramdisk_find(parent, fn, strlen(fn));
		if (!dir && f->type == STAT_TYPE_DIR)
			return NULL;
	} else {
		/* We must have been looking for the dir itself */
		if (!dir)
			return NULL;
	}

	return f;
}

/* Find the parent directory and file name in the path-named file */
static int ramdisk_get_parent(rd_dir_t * parent, const char * fn, rd_dir_t ** dout, const char **fnout) {
	const char	* p;
	char		* pname;
	rd_file_t	* f;
	
	p = strrchr(fn, '/');
	if (p == NULL) {
		*dout = parent;
		*fnout = fn;
	} else {
		pname = (char *)malloc((p - fn) + 1);
		strncpy(pname, fn, p - fn);
		pname[p - fn] = 0;

		f = ramdisk_find_path(parent, pname, 1);
		free(pname);
		if (!f)
			return -1;

		*dout = (rd_dir_t *)f->data;
		*fnout = p+1;
		assert( *dout != NULL );
	}
	return 0;
}

/* Create a path-named file in the ramdisk. There should not be a
   slash at the beginning, nor at the end. Assumes we hold rd_mutex. */
static rd_file_t * ramdisk_create_file(rd_dir_t * parent, const char * fn, int dir) {
	rd_file_t	* f;
	rd_dir_t	* pdir;
	const char	* p;

	/* First, find the parent dir */
	if (ramdisk_get_parent(parent, fn, &pdir, &p) < 0)
		return NULL;
	
	/* Now add a file to the parent */
	f = (rd_file_t *)malloc(sizeof(rd_file_t));
	f->name = strdup(p);
	f->size = 0;
	f->type = dir ? STAT_TYPE_DIR : STAT_TYPE_FILE;
	f->openfor = OPENFOR_NOTHING;
	f->usage = 0;
	if (!dir) {
		f->data = malloc(1024);
		f->datasize = 1024;
	} else {
		f->data = malloc(sizeof(rd_dir_t));
		f->datasize = 0;
	}

	LIST_INSERT_HEAD(pdir, f, dirlist);

	return f;
}

/* Open a file or directory */
static file_t ramdisk_open(vfs_handler_t * vfs, const char *fn, int mode) {
	file_t		fd = -1;
	rd_file_t	*f;
	int		mm = mode & O_MODE_MASK;

	mutex_lock(rd_mutex);

	/* Are we trying to do something stupid? */
	if ((mode & O_DIR) && mm != O_RDONLY)
		goto error_out;

	/* Look for the file */
	assert( root != NULL );
	if (fn[0] == 0) {
		f = root;
	} else {
		f = ramdisk_find_path(rootdir, fn + 1, mode & O_DIR);
		if (f == NULL) {
			/* Are we planning to write anyway? */
			if (mm != O_RDONLY && !(mode & O_DIR)) {
				/* Create a new file */
				f = ramdisk_create_file(rootdir, fn + 1, mode & O_DIR);
				if (f == NULL)
					goto error_out;
			} else
				goto error_out;
		}
	}

	/* Find a free file handle */
	for (fd=1; fd<MAX_RAM_FILES; fd++)
		if (fh[fd].file == NULL)
			break;

	/* Did we find it? */
	if (fd >= MAX_RAM_FILES) {
		fd = -1;
		goto error_out;
	}

	/* Is the file already open for write? */
	if (f->openfor == OPENFOR_WRITE)
		goto error_out;

	/* Fill the basic fd structure */
	fh[fd].file = f;
	fh[fd].dir = mode & O_DIR;

	/* The rest require a bit more thought */
	switch (mm) {
	case O_RDONLY:
		f->openfor = OPENFOR_READ;
		fh[fd].ptr = 0;
		break;
	case O_RDWR:
	case O_WRONLY:
	case O_APPEND:
		if (f->openfor == OPENFOR_READ)
			goto error_out;
		f->openfor = OPENFOR_WRITE;
		if (mm == O_RDWR)
			fh[fd].ptr = 0;
		else
			fh[fd].ptr = f->size;
		break;
	default:
		assert_msg( false, "Unknown file mode" );
	}
	
	/* If we're opening with O_TRUNC, kill the existing contents */
	if (mm != O_RDONLY && (mode & O_TRUNC)) {
		free(f->data);
		f->data = malloc(1024);
		f->datasize = 1024;
		f->size = 0;
		fh[fd].ptr = 0;
	}

	/* If we opened a dir, then ptr is actually a pointer to the first
	   file entry. */
	if (mode & O_DIR) {
		fh[fd].ptr = (uint32)LIST_FIRST((rd_dir_t *)f->data);
	}

	/* Increase the usage count */
	f->usage++;

	/* Should do it... */
	mutex_unlock(rd_mutex);
	return fd;
	
error_out:
	if (fd != -1)
		fh[fd].file = NULL;
	mutex_unlock(rd_mutex);
	return FILEHND_INVALID;
}

/* Close a file or directory */
static void ramdisk_close(file_t fd) {
	rd_file_t	*f;

	mutex_lock(rd_mutex);
	
	/* Check that the fd is valid */
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL) {
		f = fh[fd].file;
		fh[fd].file = NULL;

		/* Decrease the usage count */
		f->usage--;
		assert( f->usage >= 0 );

		/* If the usage count is back to 0, then no one has the file
		   open. Remove the openfor status. */
		if (f->usage == 0)
			f->openfor = OPENFOR_NOTHING;
	}

	mutex_unlock(rd_mutex);
}

/* Read from a file */
static ssize_t ramdisk_read(file_t fd, void *buf, size_t bytes) {
	ssize_t rv = -1;
	
	mutex_lock(rd_mutex);
	
	/* Check that the fd is valid */
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir) {
		/* Is there enough left? */
		if ((fh[fd].ptr + bytes) > fh[fd].file->size)
			bytes = fh[fd].file->size - fh[fd].ptr;

		/* Copy out the requested amount */
		memcpy(buf, ((uint8 *)fh[fd].file->data) + fh[fd].ptr, bytes);
		fh[fd].ptr += bytes;

		rv = bytes;
	}

	mutex_unlock(rd_mutex);
	return rv;
}

/* Write to a file */
static ssize_t ramdisk_write(file_t fd, const void *buf, size_t bytes) {
	ssize_t rv = -1;
	
	mutex_lock(rd_mutex);
	
	/* Check that the fd is valid */
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir && fh[fd].file->openfor == OPENFOR_WRITE) {
		/* Is there enough left? */
		if ((fh[fd].ptr + bytes) > fh[fd].file->datasize) {
			/* We need to realloc the block */
			void * np = realloc(fh[fd].file->data, (fh[fd].ptr + bytes) + 4096);
			if (np == NULL)
				goto error_out;

			fh[fd].file->data = np;
			fh[fd].file->datasize = (fh[fd].ptr + bytes) + 4096;
		}

		/* Copy out the requested amount */
		memcpy(((uint8 *)fh[fd].file->data) + fh[fd].ptr, buf, bytes);
		fh[fd].ptr += bytes;

		if (fh[fd].file->size < fh[fd].ptr) {
			fh[fd].file->size = fh[fd].ptr;
		}

		rv = bytes;
	}

error_out:
	mutex_unlock(rd_mutex);
	return rv;
}

/* Seek elsewhere in a file */
static off_t ramdisk_seek(file_t fd, off_t offset, int whence) {
	off_t rv = -1;

	mutex_lock(rd_mutex);
	
	/* Check that the fd is valid */
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir) {
		/* Update current position according to arguments */
		switch (whence) {
		case SEEK_SET:
			fh[fd].ptr = offset;
			break;
		case SEEK_CUR:
			fh[fd].ptr += offset;
			break;
		case SEEK_END:
			fh[fd].ptr = fh[fd].file->size + offset;
			break;
		default:
			return -1;
		}
	
		/* Check bounds */
		if (fh[fd].ptr < 0) fh[fd].ptr = 0;
		if (fh[fd].ptr > fh[fd].file->size) fh[fd].ptr = fh[fd].file->size;

		rv = fh[fd].ptr;
	}

	mutex_unlock(rd_mutex);
	return rv;
}

/* Tell where in the file we are */
static off_t ramdisk_tell(file_t fd) {
	off_t rv = -1;

	mutex_lock(rd_mutex);

	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir)
		rv = fh[fd].ptr;

	mutex_unlock(rd_mutex);
	return rv;
}

/* Tell how big the file is */
static size_t ramdisk_total(file_t fd) {
	off_t rv = -1;

	mutex_lock(rd_mutex);

	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir)
		rv = fh[fd].file->size;

	mutex_unlock(rd_mutex);
	return rv;
}

/* Read a directory entry */
static dirent_t *ramdisk_readdir(file_t fd) {
	rd_file_t	* f;
	dirent_t	* rv = NULL;

	mutex_lock(rd_mutex);
	
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && fh[fd].ptr != 0 && fh[fd].dir) {
		/* Find the current file and advance to the next */
		f = (rd_file_t *)fh[fd].ptr;
		fh[fd].ptr = (uint32)LIST_NEXT(f, dirlist);
		
		/* Copy out the requested data */
		strcpy(fh[fd].dirent.name, f->name);
		fh[fd].dirent.time = 0;
		if (f->type == STAT_TYPE_DIR) {
			fh[fd].dirent.attr = O_DIR;
			fh[fd].dirent.size = -1;
		} else {
			fh[fd].dirent.attr = 0;
			fh[fd].dirent.size = f->size;
		}

		rv = &fh[fd].dirent;
	}

	mutex_unlock(rd_mutex);

	return rv;
}

static int ramdisk_unlink(vfs_handler_t * vfs, const char *fn) {
	rd_file_t	* f;
	int		rv = -1;

	mutex_lock(rd_mutex);

	/* Find the file */
	f = ramdisk_find_path(rootdir, fn, 0);
	if (f) {
		/* Make sure it's not in use */
		if (f->usage == 0) {
			/* Free its data */
			free(f->name);
			free(f->data);

			/* Remove it from the parent list */
			LIST_REMOVE(f, dirlist);

			/* Free the entry itself */
			free(f);
			rv = 0;
		}
	}
	
	mutex_unlock(rd_mutex);
	return rv;
}

static void * ramdisk_mmap(file_t fd) {
	void * rv = NULL;
	
	mutex_lock(rd_mutex);
	
	if (fd < MAX_RAM_FILES && fh[fd].file != NULL && !fh[fd].dir) {
		rv = fh[fd].file->data;
	}

	mutex_unlock(rd_mutex);

	return rv;
}

/* Put everything together */
static vfs_handler_t vh = {
	{ "ramdisk" },		/* name */
	0, 0, NULL,		/* In-kernel, no cacheing, privdata */
	VFS_LIST_INIT,		/* List */

	ramdisk_open,
	ramdisk_close,
	ramdisk_read,
	ramdisk_write,
	ramdisk_seek,
	ramdisk_tell,
	ramdisk_total,
	ramdisk_readdir,
	NULL,			/* ioctl */
	NULL,			/* rename XXX */
	ramdisk_unlink,
	ramdisk_mmap,
	NULL,			/* complete */
	NULL,			/* stat XXX */
	NULL,			/* mkdir XXX */
	NULL			/* rmdir XXX */
};

/* Attach a piece of memory to a file. This works somewhat like open for
   writing, but it doesn't actually attach the file to an fd, and it starts
   out with data instead of being blank. */
int fs_ramdisk_attach(const char * fn, void * obj, size_t size) {
	file_t		fd;
	rd_file_t	*f;
	
	/* First of all, open a file for writing. This'll save us a bunch
	   of duplicated code. */
	fd = ramdisk_open(&vh, fn, O_WRONLY | O_TRUNC);
	if (fd == FILEHND_INVALID)
		return -1;

	/* Ditch the data block we had and replace it with the user one. */
	f = fh[fd].file;
	free(f->data);
	f->data = obj;
	f->datasize = size;
	f->size = size;

	/* Close the file */
	ramdisk_close(fd);

	return 0;
}

/* Does the opposite of attach. This again piggybacks on open. */
int fs_ramdisk_detach(const char * fn, void ** obj, size_t * size) {
	file_t		fd;
	rd_file_t	*f;
	
	/* First of all, open a file for reading. This'll save us a bunch
	   of duplicated code. */
	fd = ramdisk_open(&vh, fn, O_RDONLY);
	if (fd == FILEHND_INVALID)
		return -1;

	/* Pull the data block and put it in the user parameters. */
	assert( obj != NULL );
	assert( size != NULL );

	f = fh[fd].file;
	*obj = f->data;
	*size = f->size;

	/* Ditch the data block we had and replace it with a fake one. */
	f->data = malloc(64);
	f->datasize = 64;
	f->size = 64;

	/* Close the file */
	ramdisk_close(fd);

	/* Unlink the file */
	ramdisk_unlink(&vh, fn);

	return 0;
}

/* Initialize the file system */
int fs_ramdisk_init() {
	/* Create an empty root dir */
	rootdir = (rd_dir_t *)malloc(sizeof(rd_dir_t));
	LIST_INIT(rootdir);
	root = (rd_file_t *)malloc(sizeof(rd_file_t));
	root->name = "/";
	root->size = 0;
	root->type = STAT_TYPE_DIR;
	root->openfor = OPENFOR_NOTHING;
	root->usage = 0;
	root->data = rootdir;
	root->datasize = 0;

	/* Reset fd's */
	memset(fh, 0, sizeof(fh));
	
	/* Init thread mutexes */
	rd_mutex = mutex_create();

	/* Register with VFS */
	return fs_handler_add("/ram", &vh);
}

/* De-init the file system */
int fs_ramdisk_shutdown() {
	rd_file_t *f1, *f2;
	/* For now assume there's only the root dir, since mkdir and
	   rmdir aren't even implemented... */
	f1 = LIST_FIRST(rootdir);
	while (f1) {
		f2 = LIST_NEXT(f1, dirlist);
		free(f1->name);
		free(f1->data);
		free(f1);
		f1 = f2;
	}

	free(rootdir);
	free(root);
	   
	mutex_destroy(rd_mutex);
	return fs_handler_remove(&vh);
}



