/* KallistiOS ##version##

   tga.c
   (c)2000-2001 Benoit Miller

   TGA image loader.

   20-Jan-2002 Paul Boese:
	flip y-axis so it loads like all the other kos
	image loaders.

   06-Apr-2002 Dan Potter:
	Split into its own library, adapted for kos_img_t
*/

#include <kos.h>
#include <tga/tga.h>
#include <assert.h>

CVSID("$Id: tga.c,v 1.5 2003/03/14 05:53:57 bardtx Exp $");

typedef struct {
	uint8  image_id_length __attribute__((packed));		/* Length of Image ID field */
	uint8  colormap_type __attribute__((packed));		/* Color Map type */
	uint8  image_type __attribute__((packed));		/* Image Type code */
	uint16 colormap_origin __attribute__((packed));		/* Color Map origin */
	uint16 colormap_length __attribute__((packed));		/* Color Map length */
	uint8  colormap_entry_size __attribute__((packed));	/* Color Map entry size */
	uint16 x_origin __attribute__((packed));		/* X origin of image */
	uint16 y_origin __attribute__((packed));		/* Y origin of image */
	uint16 width __attribute__((packed));			/* Image width */
	uint16 height __attribute__((packed));			/* Image height */
	uint8  pixel_size __attribute__((packed));		/* Image pixel size */
	uint8  img_descriptor __attribute__((packed));		/* Image descriptor byte */
} tga_hdr;

/* Loads a TGA file into a kos_img_t struct */
int tga_to_img(const char *fn, kos_img_t *rv) {
	tga_hdr tgah;
	uint32	fd;
	uint8	r, g, b, a;
	int	x, y;
	int	num_bytes;
	uint16	*image;

	assert( rv != NULL );

	/* Open the file */
	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		dbglog(DBG_ERROR, "tga_load(%s): Couldn't open file\n", fn);
		return -1;
	}

	/* Load the TGA header */
	fs_read(fd, &tgah, sizeof(tgah));

	if (tgah.image_type != 2) {
		dbglog(DBG_ERROR, "tga_load(%s): Not an unmapped RGB image\n", fn);
		fs_close(fd);
		return -2;
	}
	if (tgah.pixel_size != 32) {
		dbglog(DBG_ERROR, "tga_load(%s): TGA data is not 32bpp\n", fn);
		fs_close(fd);
		return -3;
	}
	if (tgah.img_descriptor & 0x20) {
		dbglog(DBG_ERROR, "tga_load(%s): Not a TrueVision image\n", fn);
		fs_close(fd);
		return -4;
	}

	/* Setup the output structure */
	rv->w = tgah.width;
	rv->h = tgah.height;
	rv->byte_count = num_bytes = rv->w * rv->h * 2;
	rv->data = malloc(num_bytes);
	rv->fmt = KOS_IMG_FMT(KOS_IMG_FMT_ARGB4444, 0);

	/* Don't care for the image identification field */
	fs_seek(fd, tgah.image_id_length, SEEK_CUR);

	/* Don't care for the color map */
	fs_seek(fd, tgah.colormap_length * tgah.colormap_entry_size, SEEK_CUR);

	/* Read the image */
	image = ((uint16*)(rv->data)) + (tgah.width * tgah.height);
	for (y=0; y<tgah.height; y++) {
		image -= tgah.width;
		for (x=0; x<tgah.width; x++) {
			fs_read(fd, &b, 1);
			fs_read(fd, &g, 1);
			fs_read(fd, &r, 1);
			fs_read(fd, &a, 1);
			
			/* Cheap scaling to ARGB4444 */
			a = a >> 4 & 0x0f;
			r = r >> 4 & 0x0f;
			g = g >> 4 & 0x0f;
			b = b >> 4 & 0x0f;

			/* Store the final pixel */
			image[x] = (a<<12) | (r<<8) | (g<<4) | b;
		}
	}

	/* Close the file */
	fs_close(fd);

	return 0;
}
