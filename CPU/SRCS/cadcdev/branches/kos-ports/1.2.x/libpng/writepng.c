/* KallistiOS ##version##

   writepng.c
   (c)2002 Jeffrey McBeth

   $Id: writepng.c,v 1.1 2002/03/23 08:12:55 bardtx Exp $
*/


#include <stdio.h>
#include <stdlib.h>

#include "png.h"        /* libpng header; includes zlib.h */

/*
 * Writes png images, assumes RGB888 pixel data
 */

int png_write_data(const char *filename, uint8 *data, uint32 width, uint32 height)
{
  FILE *fp;
  uint32_t i;

  fp = fopen(filename, "wb");
  if (!fp) return -1;
   
  png_structp png_ptr = png_create_write_struct
    (PNG_LIBPNG_VER_STRING, (png_voidp)NULL,
     NULL, NULL);
  if (!png_ptr)
    return false;
  
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) 
  {
    png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
    return false;
  }

  png_init_io(png_ptr, fp);
  
  png_set_filter(png_ptr, 0, PNG_FILTER_VALUE_NONE);
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);
  
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 
               PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, 
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  
  png_bytepp row_pointers = (png_bytepp)malloc(sizeof(png_bytep)*height);
  
  for(i = 0; i < height; i++)
      row_pointers[i] = &data[3*i*width];

  png_set_rows(png_ptr, info_ptr, row_pointers);

  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  
  free(row_pointers);
  fclose(fp);   
  return 0;
}
