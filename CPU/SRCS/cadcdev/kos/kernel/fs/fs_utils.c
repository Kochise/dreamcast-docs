/* KallistiOS ##version##

   fs_utils.c
   Copyright (C)2002 Dan Potter

*/

/*

A couple of helpful utility functions for VFS usage.
XXX This probably belongs in something like libc...

*/

#include <kos/fs.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

CVSID("$Id: fs_utils.c,v 1.2 2002/08/19 08:10:07 bardtx Exp $");

/* Copies a file from 'src' to 'dst'. The amount of the file
   actually copied without error is returned. */
ssize_t fs_copy(const char * src, const char * dst) {
	char	*buff;
	ssize_t	left, total, r;
	file_t	fs, fd;

	/* Try to open both files */
	fs = fs_open(src, O_RDONLY);
	if (fs == FILEHND_INVALID) {
		return -1;
	}

	fd = fs_open(dst, O_WRONLY | O_TRUNC);
	if (fd == FILEHND_INVALID) {
		fs_close(fs);
		return -2;
	}

	/* Get the source size */
	left = fs_total(fs);
	total = 0;

	/* Allocate a buffer */
	buff = malloc(65536);

	/* Do the copy */
	while (left > 0) {
		r = fs_read(fs, buff, 65536);
		if (r <= 0)
			break;
		fs_write(fd, buff, r);
		left -= r;
		total += r;
	}

	/* Free the buffer */
	free(buff);

	/* Close both files */
	fs_close(fs);
	fs_close(fd);

	return total;
}

/* Opens a file, allocates enough RAM to hold the whole thing,
   reads it into RAM, and closes it. The caller owns the allocated
   memory (and must free it). The file size is returned, or -1  
   on failure; on success, out_ptr is filled with the address    
   of the loaded buffer. */
ssize_t fs_load(const char * src, void ** out_ptr) {
	file_t	f;
	void	* data;
	uint8	* out;
	ssize_t	total, left, r;

	assert( out_ptr != NULL );
	*out_ptr = NULL;

	/* Try to open the file */
	f = fs_open(src, O_RDONLY);
	if (f == FILEHND_INVALID)
		return -1;

	/* Get the size and alloc a buffer */
	left = fs_total(f);
	total = 0;
	data = malloc(left);
	out = (uint8 *)data;

	/* Load the data */
	while (left > 0) {
		r = fs_read(f, out, left);
		if (r <= 0)
			break;
		left -= r;
		total += r;
		out += r;
	}

	/* Did we get it all? If not, realloc the buffer */
	if (left > 0) {
		*out_ptr = realloc(data, total);
		if (*out_ptr == NULL)
			*out_ptr = data;
	} else
		*out_ptr = data;

	fs_close(f);

	return total;
}
