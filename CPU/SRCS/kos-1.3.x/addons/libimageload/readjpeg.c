#include <stdio.h>
#include "../libjpeg/jpeglib.h"

static struct jpeg_decompress_struct cinfo;
static struct jpeg_error_mgr jerr;

uint32 readjpeg_init(FILE *infile)
{
    /* Step 1: allocate and initialize JPEG decompression object */
    
    /* We set up the normal JPEG error routines */
    cinfo.err = jpeg_std_error(&jerr);
    
    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    
    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, infile);    

    (void) jpeg_read_header(&cinfo, TRUE);
    
    /* Step 4: set parameters for decompression */
    
    cinfo.scale_denom = 1; /* must be 1, 2, 4, or 8 */

    /* Step 5: Start decompressor */
    (void) jpeg_start_decompress(&cinfo);
    
    return 0;
}

/* load n x n textures from jpegs */

uint8 *readjpeg_get_image(uint32 *pChannels, uint32 *pRowbytes, uint32 *pWidth, uint32 *pHeight)
{
  uint32 i;
  uint8 *ourbuffer;
  JSAMPARRAY buffer;

  *pRowbytes = cinfo.output_width * cinfo.output_components;
  *pChannels = cinfo.output_components;
  *pWidth = cinfo.output_width;
  *pHeight = cinfo.output_height;
  
  ourbuffer = (uint8 *)malloc(*pRowbytes**pHeight);

  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, *pRowbytes, 1);

  for(i = 0; i < cinfo.output_height; i++)
  {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    memcpy(&ourbuffer[i**pRowbytes], buffer[0], *pRowbytes);
  }
  
  return ourbuffer;
}

void readjpeg_cleanup(void)
{
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}
