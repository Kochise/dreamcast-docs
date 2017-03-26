/* KallistiOS ##version##

   fs_romdisk.c
   (c)2001-2002 Dan Potter

*/

/*

This module implements the Linux ROMFS file system for reading a pre-made boot romdisk.

To create a romdisk image, you will need the program "genromfs". This program was designed
for Linux but ought to compile under Cygwin. The source for this utility can be found
on sunsite.unc.edu in /pub/Linux/system/recovery/, or as a package under Debian "genromfs".

*/

#include <arch/types.h>
#include <kos/thread.h>
#include <kos/mutex.h>
#include <kos/fs_romdisk.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

CVSID("$Id: fs_romdisk.c,v 1.9 2002/10/26 08:20:10 bardtx Exp $");

/* Header definitions from Linux ROMFS documentation; all integer quantities are
   expressed in big-endian notation. Unfortunately the ROMFS guys were being
   clever and made this header a variable length depending on the size of
   the volume name *groan*. Its size will be a multiple of 16 bytes though. */
typedef struct {
	char	magic[8];		/* Should be "-rom1fs-" */
	uint32	full_size;		/* Full size of the file system */
	uint32	checksum;		/* Checksum */
	char	volume_name[16];	/* Volume name (zero-terminated) */
} romdisk_hdr_t;

/* File header info; note that this header plus filename must be a multiple of
   16 bytes, and the following file data must also be a multiple of 16 bytes. */
typedef struct {
	uint32	next_header;		/* Offset of next header */
	uint32	spec_info;		/* Spec info */
	uint32	size;			/* Data size */
	uint32	checksum;		/* File checksum */
	char	filename[16];		/* File name (zero-terminated) */
} romdisk_file_t;


/* Util function to reverse the byte order of a uint32 */
static uint32 ntohl_32(const void *data) {
	const uint8 *d = (const uint8*)data;
	return (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | (d[3] << 0);
}

/********************************************************************************/

/* A list of the following */
struct rd_image;
typedef LIST_HEAD(rdi_list, rd_image) rdi_list_t;

/* A single mounted romdisk image; a pointer to one of these will be in our
   VFS struct for each mount. */
typedef struct rd_image {
	LIST_ENTRY(rd_image) list_ent;	/* List entry */

	int			own_buffer;	/* Do we own the image buffer? */
	const uint8		* image;	/* The actual image */
	const romdisk_hdr_t	* hdr;		/* Pointer to the header */
	uint32			files;		/* Offset in the image to the files area */
	vfs_handler_t		* vfsh;		/* Our VFS mount struct */
} rd_image_t;

/* Global list of mounted romdisks */
static rdi_list_t romdisks;

/********************************************************************************/
/* File primitives */

/* File handles.. I could probably do this with a linked list, but I'm just
   too lazy right now. =) */
static struct {
	uint32		index;		/* romfs image index */
	int		dir;		/* >0 if a directory */
	uint32		ptr;		/* Current read position in bytes */
	uint32		size;		/* Length of file in bytes */
	dirent_t	dirent;		/* A static dirent to pass back to clients */
	rd_image_t	* mnt;		/* Which mount instance are we using? */
} fh[MAX_RD_FILES];

/* Mutex for file handles */
static mutex_t * fh_mutex = NULL;

/* Given a filename and a starting romdisk directory listing (byte offset),
   search for the entry in the directory and return the byte offset to its
   entry. */
static uint32 romdisk_find_object(rd_image_t * mnt, const char *fn, int fnlen, int dir, uint32 offset) {
	uint32			i, ni, type;
	const romdisk_file_t	*fhdr;

	i = offset;
	do {
		/* Locate the entry, next pointer, and type info */
		fhdr = (const romdisk_file_t *)(mnt->image + i);
		ni = ntohl_32(&fhdr->next_header);
		type = ni & 0x0f;
		ni = ni & 0xfffffff0;

		/* Check the type */
		if (!dir) {
			if ((type & 3) != 2) {
				i = ni;
				if (!i)
					break;
				else
					continue;
			}
		} else {
			if ((type & 3) != 1) {
				i = ni;
				if (!i)
					break;
				else
					continue;
			}
		}
		
		/* Check filename */
		if (!strncasecmp(fhdr->filename, fn, fnlen)) {
			/* Match: return this index */
			return i;
		}
		
		i = ni;
	} while (i != 0);

	/* Didn't find it */
	return 0;
}

/* Locate an object anywhere in the image, starting at the root, and
   expecting a fully qualified path name. This is analogous to the
   find_object_path in iso9660.

   fn:		object filename (absolute path)
   dir:		0 if looking for a file, 1 if looking for a dir

   It will return an offset in the romdisk image for the object. */
static uint32 romdisk_find(rd_image_t * mnt, const char *fn, int dir) {
	const char		*cur;
	uint32			i;
	const romdisk_file_t	*fhdr;

	/* If the object is in a sub-tree, traverse the trees looking
	   for the right directory. */
	i = mnt->files;
	while ((cur = strchr(fn, '/'))) {
		if (cur != fn) {
			i = romdisk_find_object(mnt, fn, cur - fn, 1, i);
			if (i == 0) return 0;
			fhdr = (const romdisk_file_t *)(mnt->image + i);
			i = ntohl_32(&fhdr->spec_info);
		}
		fn = cur+1;
	}

	/* Locate the file in the resulting directory */
	if (*fn) {
		i = romdisk_find_object(mnt, fn, strlen(fn), dir, i);
		return i;
	} else {
		if (!dir)
			return 0;
		else
			return i;
	}
}

/* Open a file or directory */
static file_t romdisk_open(vfs_handler_t * vfs, const char *fn, int mode) {
	uint32			fd;
	uint32			filehdr;
	const romdisk_file_t	*fhdr;
	rd_image_t		*mnt = (rd_image_t *)vfs->privdata;

	/* Make sure they don't want to open things as writeable */
	if ((mode & O_MODE_MASK) != O_RDONLY)
		return FILEHND_INVALID;
	
	/* No blank filenames */
	if (fn[0] == 0)
		fn = "";

	/* Look for the file */
	filehdr = romdisk_find(mnt, fn + 1, mode & O_DIR);
	if (filehdr == 0)
		return 0;

	/* Find a free file handle */
	mutex_lock(fh_mutex);
	for (fd=0; fd<MAX_RD_FILES; fd++)
		if (fh[fd].index == 0) {
			fh[fd].index = -1;
			break;
		}
	mutex_unlock(fh_mutex);
	if (fd >= MAX_RD_FILES)
		return FILEHND_INVALID;
	
	/* Fill the fd structure */
	fhdr = (const romdisk_file_t *)(mnt->image + filehdr);
	fh[fd].index = filehdr + sizeof(romdisk_file_t) + (strlen(fhdr->filename)/16)*16;
	fh[fd].dir = (mode & O_DIR) ? 1 : 0;
	fh[fd].ptr = 0;
	fh[fd].size = ntohl_32(&fhdr->size);
	fh[fd].mnt = mnt;
	
	return fd;
}

/* Close a file or directory */
static void romdisk_close(file_t fd) {
	/* Check that the fd is valid */
	if (fd < MAX_RD_FILES) {
		/* No need to lock the mutex: this is an atomic op */
		fh[fd].index = 0;
	}
}

/* Read from a file */
static ssize_t romdisk_read(file_t fd, void *buf, size_t bytes) {
	/* Check that the fd is valid */
	if (fd >= MAX_RD_FILES || fh[fd].index == 0 || fh[fd].dir)
		return -1;

	/* Is there enough left? */
	if ((fh[fd].ptr + bytes) > fh[fd].size)
		bytes = fh[fd].size - fh[fd].ptr;

	/* Copy out the requested amount */
	memcpy(buf, fh[fd].mnt->image + fh[fd].index + fh[fd].ptr, bytes);
	fh[fd].ptr += bytes;

	return bytes;
}

/* Seek elsewhere in a file */
static off_t romdisk_seek(file_t fd, off_t offset, int whence) {
	/* Check that the fd is valid */
	if (fd>=MAX_RD_FILES || fh[fd].index==0 || fh[fd].dir)
		return -1;

	/* Update current position according to arguments */
	switch (whence) {
		case SEEK_SET:
			fh[fd].ptr = offset;
			break;
		case SEEK_CUR:
			fh[fd].ptr += offset;
			break;
		case SEEK_END:
			fh[fd].ptr = fh[fd].size + offset;
			break;
		default:
			return -1;
	}
	
	/* Check bounds */
	if (fh[fd].ptr < 0) fh[fd].ptr = 0;
	if (fh[fd].ptr > fh[fd].size) fh[fd].ptr = fh[fd].size;
	
	return fh[fd].ptr;
}

/* Tell where in the file we are */
static off_t romdisk_tell(file_t fd) {
	if (fd>=MAX_RD_FILES || fh[fd].index==0 || fh[fd].dir)
		return -1;

	return fh[fd].ptr;
}

/* Tell how big the file is */
static size_t romdisk_total(file_t fd) {
	if (fd>=MAX_RD_FILES || fh[fd].index==0 || fh[fd].dir)
		return -1;

	return fh[fd].size;
}

/* Read a directory entry */
static dirent_t *romdisk_readdir(file_t fd) {
	romdisk_file_t	*fhdr;
	int		type;
	
	if (fd>=MAX_RD_FILES || fh[fd].index==0 || !fh[fd].dir)
		return NULL;

	if (fh[fd].index == 0)
		return NULL;

	/* Get the current file header */
	fhdr = (romdisk_file_t *)(fh[fd].mnt->image + fh[fd].index + fh[fd].ptr);

	/* Update the pointer */
	fh[fd].ptr = ntohl_32(&fhdr->next_header);
	type = fh[fd].ptr & 0x0f;
	fh[fd].ptr = fh[fd].ptr & 0xfffffff0;
	if (fh[fd].ptr == 0)
		fh[fd].index = 0;
	else
		fh[fd].ptr = fh[fd].ptr - fh[fd].index;

	/* Copy out the requested data */
	strcpy(fh[fd].dirent.name, fhdr->filename);
	fh[fd].dirent.time = 0;
	if ((type & 3) == 1) {
		fh[fd].dirent.attr = O_DIR;
		fh[fd].dirent.size = -1;
	} else {
		fh[fd].dirent.attr = 0;
		fh[fd].dirent.size = ntohl_32(&fhdr->size);
	}

	return &fh[fd].dirent;
}

static void *romdisk_mmap(file_t fd) {
	if (fd>=MAX_RD_FILES || fh[fd].index==0)
		return NULL;

	/* Can't really help the loss of "const" here */
	return (void *)(fh[fd].mnt->image + fh[fd].index);
}

/* This is a template that will be used for each mount */
static vfs_handler_t vh = {
	{ 0 },			/* name */
	0, 0, NULL,		/* In-kernel, no cacheing, privdata */
	VFS_LIST_INIT,		/* List */
	
	romdisk_open,
	romdisk_close,
	romdisk_read,
	NULL,
	romdisk_seek,
	romdisk_tell,
	romdisk_total,
	romdisk_readdir,
	NULL,
	NULL,
	NULL,
	romdisk_mmap
};

/* Are we initialized? */
static int initted = 0;

/* Initialize the file system */
int fs_romdisk_init() {
	if (initted)
		return 0;

	/* Init our list of mounted images */
	LIST_INIT(&romdisks);

	/* Reset fd's */
	memset(fh, 0, sizeof(fh));
	
	/* Mark the first as active so we can have an error FD of zero */
	fh[0].index = -1;
	
	/* Init thread mutexes */
	fh_mutex = mutex_create();

	initted = 1;

	return 0;
}

/* De-init the file system; also unmounts any mounted images. */
int fs_romdisk_shutdown() {
	rd_image_t *n, *c;

	if (!initted)
		return 0;

	/* Go through and free all the romdisk mount entries */
	c = LIST_FIRST(&romdisks);
	while (c != NULL) {
		n = LIST_NEXT(c, list_ent);

		dbglog(DBG_DEBUG, "fs_romdisk: unmounting image at %p from %s\n",
			c->image, c->vfsh->prefix);
		if (c->own_buffer)
			dbglog(DBG_DEBUG, "   (and also freeing its image buffer)\n");

		fs_handler_remove(c->vfsh);
		if (c->own_buffer)
			free((void *)c->image);
		free(c->vfsh);
		free(c);
		
		c = n;
	}

	/* Free mutex */
	if (fh_mutex != NULL)
		mutex_destroy(fh_mutex);
	fh_mutex = NULL;

	initted = 0;

	return 0;
}

/* Mount a romdisk image; must have called fs_romdisk_init() earlier.
   Also note that we do _not_ take ownership of the image data if
   own_buffer is 0, so if you malloc'd that buffer, you must
   also free it after the unmount. If own_buffer is non-zero, then
   we free the buffer when it is unmounted. */
int fs_romdisk_mount(const char * mountpoint, const uint8 *img, int own_buffer) {
	const romdisk_hdr_t	* hdr;
	rd_image_t 		* mnt;
	vfs_handler_t		* vfsh;

	/* Are we initted? */
	if (!initted)
		return -1;

	/* Check the image and print some info about it */
	hdr = (const romdisk_hdr_t *)img;
	if (strncmp(img, "-rom1fs-", 8)) {
		dbglog(DBG_ERROR, "Rom disk image at %p is not a ROMFS image\n", img);
		return -1;
	} else {
		dbglog(DBG_DEBUG, "fs_romdisk: mounting image at %p at %s\n", img, mountpoint);
	}

	/* Create a mount struct */
	mnt = (rd_image_t *)malloc(sizeof(rd_image_t));
	mnt->own_buffer = own_buffer;
	mnt->image = img;
	mnt->hdr = hdr;
	mnt->files = sizeof(romdisk_hdr_t)
		+ (strlen(hdr->volume_name) / 16) * 16;

	/* Make a VFS struct */
	vfsh = (vfs_handler_t *)malloc(sizeof(vfs_handler_t));
	memcpy(vfsh, &vh, sizeof(vfs_handler_t));
	vfsh->privdata = (void *)mnt;
	mnt->vfsh = vfsh;

	/* Add it to our mount list */
	LIST_INSERT_HEAD(&romdisks, mnt, list_ent);

	/* Register with VFS */
	return fs_handler_add(mountpoint, vfsh);
}

/* Unmount a romdisk image */
int fs_romdisk_unmount(const char * mountpoint) {
	rd_image_t	* n;
	int		found = 0;

	LIST_FOREACH(n, &romdisks, list_ent) {
		if (!strcmp(mountpoint, n->vfsh->prefix)) {
			found = 1;
			break;
		}
	}

	if (found) {
		/* Remove it from the mount list */
		LIST_REMOVE(n, list_ent);

		dbglog(DBG_DEBUG, "fs_romdisk: unmounting image at %p from %s\n",
			n->image, n->vfsh->prefix);
		if (n->own_buffer)
			dbglog(DBG_DEBUG, "   (and also freeing its image buffer)\n");

		/* Unmount it */
		fs_handler_remove(n->vfsh);

		/* If we own the buffer, free it */
		if (n->own_buffer)
			free((void *)n->image);

		/* Free the structs */
		free(n->vfsh);
		free(n);

		return 0;
	} else
		return -1;
}

