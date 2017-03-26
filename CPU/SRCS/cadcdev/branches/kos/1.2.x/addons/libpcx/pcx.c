/* KallistiOS ##version##

   pcx.c
   (c)2000-2001 Dan Potter

   PCX image loader
*/

#include <kos.h>
#include <pcx/pcx.h>
#include <assert.h>

CVSID("$Id: pcx.c,v 1.3 2003/03/14 05:53:57 bardtx Exp $");

typedef struct {
	char   mfg;               /* manufacturer, always 0xa0		*/
	char   ver;               /* encoder version number (5)		*/
	char   enc;               /* encoding code, always 1		*/
	char   bpp;               /* bits per pixel, 8 in mode 0x13	*/
	uint16 xmin,ymin;         /* image origin, usually 0,0		*/
	uint16 xmax,ymax;         /* image dimensions			*/
	uint16 hres;              /* horizontal resolution value	*/
	uint16 vres;              /* vertical resolution value		*/
	char   pal[48];           /* palette (not in mode 0x13)		*/
	char   reserved;          /* who knows?				*/
	char   clrplanes;         /* number of planes, 1 in mode 0x13	*/
	uint16 bpl;               /* bytes per line, 80 in mode 0x13	*/
	uint16 pltype;            /* Grey or Color palette flag		*/
	char   filler[58];        /* Zsoft wanted a 128 byte header	*/
} pcx_hdr;


/* Loads a PCX file into a kos_img_t struct */
int pcx_to_img(const char *fn, kos_img_t *rv) {
	pcx_hdr	pcxh;
	uint32	fd;
	int	bytes = 0;	/* counts unpacked bytes */
	uint8	c;		/* byte being processed */
	int	runlen, i;	/* length of packet */
	int	num_bytes;
	uint8	*pcxpal;
	uint8	*image;
	int	r, g, b, v;
	uint16	*pxls;

	assert( rv != NULL );

	/* Open the file */
	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		printf("pcx_load(%s): Couldn't open file\r\n", fn);
		return -1;
	}

	/* Load the PCX header */
	fs_read(fd, &pcxh, sizeof(pcxh));
	if (pcxh.bpp != 8) {
		printf("pcx_load(%s): PCX data is not 8bpp\r\n", fn);
		fs_close(fd);
		return -2;
	}

	/* Setup the output structure */
	rv->w = pcxh.xmax + 1;
	rv->h = pcxh.ymax + 1;
	num_bytes = rv->w * rv->h;
	/* printf("pcx_load(%s): image %08x is %dx%d (%d bytes)\r\n", fn, rv, rv->width, rv->height, num_bytes); */
	pxls = (uint16 *)malloc(num_bytes * 2);
	rv->data = (void *)pxls;
	rv->fmt = KOS_IMG_FMT(KOS_IMG_FMT_RGB565, 0);
	rv->byte_count = 2 * rv->w * rv->h;

	/* Do the RLE decoding (allocate a temp buffer + palette) */
	image = malloc(num_bytes + 768);
	if (image == NULL) {
		printf("pcx_load(%s): Can't allocate temp space of %d bytes\r\n", fn, num_bytes);
		fs_close(fd);
		free(rv->data);
		return -3;
	}

	/* printf("  decoding into buffer at %08x\r\n", image); */
	do {
		fs_read(fd, &c, 1);	/* Read one byte */

		if ((c & 0xc0) == 0xc0) {	/* high 2 bits set is packet */
			runlen = (c & 0x3f);	/* AND off the high bits */
			fs_read(fd, &c, 1);
			while(runlen--)
				image[bytes++] = c;
		}
		else
			image[bytes++] = c;
	} while (bytes < num_bytes);
	

	/* Load the palette */
	fs_read(fd, &c, 1);		/* This is a marker before the palette */
	pcxpal = image + num_bytes;
	fs_read(fd, pcxpal, 768);
	fs_close(fd);
	
	/* Decode the image into RGB565 */
	for (i=0; i<num_bytes; i++) {
		v = image[i];
		r = pcxpal[v*3+0];
		g = pcxpal[v*3+1];
		b = pcxpal[v*3+2];
			
		v = (((r >> 3) & 0x1f) << 11)
			| (((g >> 2) & 0x3f) << 5)
			| (((b >> 3) & 0x1f) << 0);
		pxls[i] = v;
	}

	/* Free temp buffers */
	free(image);
	
	return 0;
}
