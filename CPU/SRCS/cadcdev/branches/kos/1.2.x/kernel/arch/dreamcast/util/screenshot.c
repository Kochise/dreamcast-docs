/* KallistiOS ##version##
  
   screenshot.c
   (c)2002 Dan Potter
 */

#include <stdio.h>
#include <stdlib.h>
#include <dc/video.h>
#include <kos/fs.h>
#include <arch/irq.h>

CVSID("$Id: screenshot.c,v 1.3 2003/02/14 08:13:18 bardtx Exp $");

/*

Provides a very simple screen shot facility (dumps raw RGB PPM files from the
currently viewed framebuffer).

Destination file system must be writeable and have enough free space.

Assumes display is in 16-bit mode.

*/

int vid_screen_shot(const char *destfn) {
	file_t	f;
	int	i, bsize;
	uint8	*buffer;
	uint16	pixel;
	uint8	r, g, b;
	char	header[256];
	uint32	save;

	/* Allocate a new buffer so we can blast it all at once */
	bsize = vid_mode->width * vid_mode->height * 3;
	buffer = (uint8 *)malloc(bsize);
	if (buffer == NULL) {
		dbglog(DBG_ERROR, "video_screen_shot: can't allocate ss memory\n");
		return -1;
	}

	/* Disable interrupts */
	save = irq_disable();

	/* Write out each 16-bit pixel as 24 bits */
	for (i=0; i<vid_mode->width*vid_mode->height; i++) {
		pixel = vram_s[i];
		r = ((pixel >> 11) & 0x1f) << 3;
		g = ((pixel >> 5) & 0x3f) << 2;
		b = ((pixel >> 0) & 0x1f) << 3;
		buffer[i*3+0] = r;
		buffer[i*3+1] = g;
		buffer[i*3+2] = b;
	}

	irq_restore(save);

	/* Open output file */
	f = fs_open(destfn, O_WRONLY | O_TRUNC);
	if (!f) {
		dbglog(DBG_ERROR, "video_screen_shot: can't open output file '%s'\n", destfn);
		free(buffer);
		return -1;
	}

	/* Write a small header */
	sprintf(header, "P6\n#KallistiOS Screen Shot\n%d %d\n255\n", vid_mode->width, vid_mode->height);
	if (fs_write(f, header, strlen(header)) != strlen(header)) {
		dbglog(DBG_ERROR, "video_screen_shot: can't write header to output file '%s'\n", destfn);
		fs_close(f);
		free(buffer);
		return -1;
	}

	/* Write the data */
	if (fs_write(f, buffer, bsize) != (ssize_t)bsize) {
		dbglog(DBG_ERROR, "video_screen_shot: can't write data to output file '%s'\n", destfn);
		fs_close(f);
		free(buffer);
		return -1;
	}

	fs_close(f);
	free(buffer);

	return 0;
}
