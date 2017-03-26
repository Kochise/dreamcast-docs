/* KallistiOS ##version##

   kos_img.c
   (c)2002 Dan Potter

   Based on Andrew's jpeg_to_texture routine, but loads into a
   KOS plat-independent image.
*/

         
#include <kos.h>
#include <assert.h>
#include "jpeglib.h"

/* Load a JPEG into a KOS PIImage */
int jpeg_to_img(const char *filename, int scale, kos_img_t * rv) {
	int		i;
	uint16		* ourbuffer;
	uint16		* temp_tex;

	/* This struct contains the JPEG decompression parameters and pointers to
	 * working space (which is allocated as needed by the JPEG library).
	 */
	struct jpeg_decompress_struct cinfo;
    
	struct jpeg_error_mgr jerr;
    
	/* More stuff */
	FILE		* infile;		/* Source file */
	JSAMPARRAY	buffer;			/* Output row buffer */
	int		row_stride;		/* physical row width in output buffer */

	assert( rv != NULL );
    
	/* In this example we want to open the input file before doing anything else,
	 * so that the setjmp() error recovery below can assume the file is open.
	 * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	 * requires it in order to read binary files.
	 */
        
	if ((infile = fopen(filename, "r")) == 0) {
		dbglog(DBG_ERROR, "jpeg_to_img: can't open '%s'\n", filename);
		return -1;
	}
    
	/* Step 1: allocate and initialize JPEG decompression object */
    
	/* We set up the normal JPEG error routines */
	cinfo.err = jpeg_std_error(&jerr);
    
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);
    
	/* Step 2: specify data source (eg, a file) */
	jpeg_stdio_src(&cinfo, (FILE*)infile);
    
	/* Step 3: read file parameters with jpeg_read_header() */
	(void)jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	 *   (a) suspension is not possible with the stdio data source, and
	 *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	 * See libjpeg.doc for more info.
	 */

	/* Allocate the output buffers */
	rv->w = cinfo.image_width;
	rv->h = cinfo.image_height;
	rv->data = (void *)( temp_tex = (uint16 *)malloc(rv->w * rv->h * 2) );
	rv->fmt = KOS_IMG_FMT(KOS_IMG_FMT_RGB565, 0);
	rv->byte_count = rv->w * rv->h * 2;
	ourbuffer = (uint16 *)malloc(rv->w * 2);
    
	/* Step 4: set parameters for decompression */
	assert( scale == 1 || scale == 2 || scale == 4 || scale == 8 );
	cinfo.scale_denom = scale; /* must be 1, 2, 4, or 8 */

	/* Step 5: Start decompressor */
	(void)jpeg_start_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	 * with the stdio data source.
	 */
    
	/* We may need to do some setup of our own at this point before reading
	 * the data.  After jpeg_start_decompress() we have the correct scaled
	 * output image dimensions available, as well as the output colormap
	 * if we asked for color quantization.
	 * In this example, we need to make an output work buffer of the right size.
	 */ 
	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;

	/* Make a one-row-high sample array that will go away when done with image */
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    
	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */
    
	/* Here we use the library's state variable cinfo.output_scanline as the
	 * loop counter, so that we don't have to keep track ourselves.
	 */
	while (cinfo.output_scanline < cinfo.output_height) {
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
	 	* Here the array is only one element long, but you could ask for
	 	* more than one scanline at a time if that's more convenient.
	 	*/
		(void)jpeg_read_scanlines(&cinfo, buffer, 1);

		for(i=0; i<row_stride/3; i++)
			ourbuffer[i] = ((buffer[0][i*3]>>3)<<11) + ((buffer[0][i*3+1]>>2)<<5) + (buffer[0][i*3+2]>>3);

		memcpy(temp_tex + cinfo.image_width*(cinfo.output_scanline-1), ourbuffer, 2*row_stride/3); 
	}

	/* Step 7: Finish decompression */
	(void)jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	 * with the stdio data source.
	 */
    
	/* Step 8: Release JPEG decompression object */
	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);
    
	/* After finish_decompress, we can close the input file.
	 * Here we postpone it until after no more JPEG errors are possible,
	 * so as to simplify the setjmp error logic above.  (Actually, I don't
	 * think that jpeg_destroy can do an error exit, but why assume anything...)
	 */
	fclose(infile);
    
	/* At this point you may want to check to see whether any corrupt-data
	 * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	 */

	free(ourbuffer);

	/* And we're done! */
	return 0;
}

