/* KallistiOS ##version##

   readpng.c
   (c)2002 Jeffrey McBeth

   $Id: readpng.c,v 1.4 2003/04/05 23:21:22 bardtx Exp $
*/


#include <stdio.h>
#include <stdlib.h>

#include "png.h"        /* libpng header; includes zlib.h */
#include "readpng.h"    /* typedefs, common macros, public prototypes */

/* This struct will hold our PNG info during procesing */
typedef struct {
	png_structp	png_ptr;
	png_infop	info_ptr;
} readpng_structs_t;

void readpng_version_info(void)
{
    fprintf(stderr, "   Compiled with libpng %s; using libpng %s.\n",
      PNG_LIBPNG_VER_STRING, png_libpng_ver);
    fprintf(stderr, "   Compiled with zlib %s; using zlib %s.\n",
      ZLIB_VERSION, zlib_version);
}


/* return value = 0 for success, 1 for bad sig, 2 for bad IHDR, 4 for no mem */

void * readpng_init(FILE *infile)
{
    uint8 sig[8];
    readpng_structs_t * strs = malloc(sizeof(readpng_structs_t));
    memset(strs, 0, sizeof(readpng_structs_t));

    /* first do a quick check that the file really is a PNG image; could
     * have used slightly more general png_sig_cmp() function instead */

    fread(sig, 1, 8, infile);
    if (!png_check_sig(sig, 8)) {
        free(strs);
        return NULL;   /* bad signature */
    }

    /* could pass pointers to user-defined error handlers instead of NULLs: */

    strs->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!strs->png_ptr) {
        free(strs);
        return NULL;   /* out of memory */
    }

    strs->info_ptr = png_create_info_struct(strs->png_ptr);
    if (!strs->info_ptr) {
        png_destroy_read_struct(&strs->png_ptr, NULL, NULL);
        free(strs);
        return NULL;   /* out of memory */
    }

    png_init_io(strs->png_ptr, infile);
    png_set_sig_bytes(strs->png_ptr, 8);  /* we already read the 8 signature bytes */

    png_read_info(strs->png_ptr, strs->info_ptr);  /* read all PNG info up to image data */

    /* OK, that's all we need for now; return happy */

    return (void *)strs;
}

uint8 *readpng_get_image(void * strsv, uint32 *pChannels, uint32 *pRowbytes, uint32 *pWidth, uint32 *pHeight)
{
    readpng_structs_t * strs = (readpng_structs_t *)strsv;

  png_uint_32  width, height;
  int  bit_depth, color_type;
  uint8  *image_data = NULL;
  png_uint_32  i, rowbytes;
  png_bytepp  row_pointers = NULL;


    /* alternatively, could make separate calls to png_get_image_width(),
     * etc., but want bit_depth and color_type for later [don't care about
     * compression_type and filter_type => NULLs] */

  png_get_IHDR(strs->png_ptr, strs->info_ptr, &width, &height, &bit_depth, &color_type,
               NULL, NULL, NULL);

  *pWidth = width;
  *pHeight = height;

    /* expand palette images to RGB, low-bit-depth grayscale images to 8 bits,
     * transparency chunks to full alpha channel; strip 16-bit-per-sample
     * images to 8 bits per sample; and convert grayscale to RGB[A] */

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(strs->png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand(strs->png_ptr);
    if (png_get_valid(strs->png_ptr, strs->info_ptr, PNG_INFO_tRNS))
        png_set_expand(strs->png_ptr);
    if (bit_depth == 16)
        png_set_strip_16(strs->png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(strs->png_ptr);

    /* all transformations have been registered; now update info_ptr data,
     * get rowbytes and channels, and allocate image memory */

    png_read_update_info(strs->png_ptr, strs->info_ptr);

    *pRowbytes = rowbytes = png_get_rowbytes(strs->png_ptr, strs->info_ptr);
    *pChannels = (int)png_get_channels(strs->png_ptr, strs->info_ptr);

    if ((image_data = (uint8 *)malloc(rowbytes*height)) == NULL) {
        png_destroy_read_struct(&strs->png_ptr, &strs->info_ptr, NULL);
        return NULL;
    }
    if ((row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep))) == NULL) {
        png_destroy_read_struct(&strs->png_ptr, &strs->info_ptr, NULL);
        free(image_data);
        image_data = NULL;
        return NULL;
    }

    Trace((stderr, "readpng_get_image:  channels = %d, rowbytes = %ld, height = %ld\n", *pChannels, rowbytes, height));


    /* set the individual row_pointers to point at the correct offsets */

    for (i = 0;  i < height;  ++i)
        row_pointers[i] = image_data + i*rowbytes;

    /* now we can go ahead and just read the whole image */

    png_read_image(strs->png_ptr, row_pointers);

    free(row_pointers);
    row_pointers = NULL;

    png_read_end(strs->png_ptr, NULL);

    return image_data;
}


void readpng_cleanup(void * strsv)
{
    readpng_structs_t * strs = (readpng_structs_t *)strsv;

    png_destroy_read_struct(&strs->png_ptr, &strs->info_ptr, NULL);
    free(strs);
}
