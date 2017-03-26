#ifndef __IMAGELOAD_H__
#define __IMAGELOAD_H__

#include <kos.h>
#include <imageload/jitterdefs.h>

#include <stdio.h>

typedef enum
{
  IMG_FILE_GUESS,
  IMG_FILE_JPEG,
  IMG_FILE_PNG,
  IMG_FILE_BMP,
  IMG_FILE_PCX
} IMG_FILE;

typedef enum
{
  IMG_ALPHA_NONE,
  IMG_ALPHA_MASK,
  IMG_ALPHA_KEYED,
  IMG_ALPHA_FULL
} IMG_ALPHA;

typedef enum
{
  IMG_DITHER_NONE,
  IMG_DITHER_JITTER
} IMG_DITHER;


typedef struct
{
  IMG_FILE type;
  IMG_ALPHA alpha;
  uint32 key;
  IMG_DITHER dither;
  uint32 dither_width;
  uint32 dither_height;
  uint32 noise;
} IMG_INFO;

#define IMG_INFO_DEFAULTS {IMG_FILE_GUESS,IMG_ALPHA_NONE,0,IMG_DITHER_NONE,0,0,0}

/* At some point these functions will return success/failure */
int img_load_data(FILE *f, IMG_INFO *info, kos_img_t *img);

int img_load_file(const char *filename, IMG_INFO *info, kos_img_t *img);

/* Jitter Functions */

/* Call to initialize jitter table at runtime
 * if you run the makejitter program before you compile, you can
 * create a jitter table at compile time
 */
void jitter_init(void);
uint8 jitter(uint8 c, uint8 n, uint8 shift, uint8 noise, uint16 x, uint16 y);

/* Format specific loaders */

uint32 readbmp_init(FILE *infile);
uint8 *readbmp_get_image(uint32 *pChannels, uint32 *pRowbytes,
                         uint32 *pWidth, uint32 *pHeight);
void readbmp_cleanup(void);

uint32 readpng_init(FILE *infile);
uint8 *readpng_get_image(uint32 *pChannels, uint32 *pRowbytes,
                         uint32 *pWidth, uint32 *pHeight);
void readpng_cleanup(void);

uint32 readjpeg_init(FILE *infile);
uint8 *readjpeg_get_image(uint32 *pChannels, uint32 *pRowbytes,
                         uint32 *pWidth, uint32 *pHeight);
void readjpeg_cleanup(void);

uint32 readpcx_init(FILE *infile);
uint8 *readpcx_get_image(uint32 *pChannels, uint32 *pRowbytes,
			 uint32 *pWidth, uint32 *pHeight);
void readpcx_cleanup(void);
#endif
