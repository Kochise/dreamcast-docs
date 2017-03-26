/* KallistiOS ##version##

   readpcx.c

   PCX image loader (_heavily_ stolen from Dan Potters code)
 */

#include <kos.h>

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

FILE *pcxfile;

uint32 readpcx_init(FILE *infile)
{
  pcxfile = infile;
  return 0;
}

uint8 *readpcx_get_image(uint32 *pChannels, uint32 *pRowBytes,
                         uint32 *pWidth, uint32 *pHeight)
{
  pcx_hdr header;
  uint32 bytesRead;
  uint8 *preImage;
  uint8 *image;
  uint8 *palette;
  uint32 numBytes;
  uint32 i;
  uint8 pixel;
  uint8 runlen;
  
  bytesRead = fread(&header, sizeof(pcx_hdr), 1, pcxfile);

  if (header.bpp != 8)
    return NULL;

  *pWidth = header.xmax+1;
  *pHeight = header.ymax+1;
  *pChannels = 3;
  *pRowBytes = *pChannels * *pWidth;
  numBytes = *pWidth * *pHeight;

  preImage = malloc(numBytes);

  for(i = 0; i < numBytes;)
  {
    fread(&pixel, sizeof(uint8), 1, pcxfile);

    if (pixel & 0xc0)
    {
      runlen = (pixel & 0x3f);
      fread(&pixel, sizeof(uint8), 1, pcxfile);
      while(runlen--)
        preImage[i++] = pixel;
    }
    else
      preImage[i++] = pixel;

  }

  fread(&pixel, sizeof(uint8), 1, pcxfile);
  palette = malloc(768);

  fread(palette, 768, 1, pcxfile);

  image = malloc(numBytes * *pChannels);
  for(i = 0; i < numBytes; i++)
  {
    image[i*(*pChannels)+0] = palette[preImage[i]*3+0];
    image[i*(*pChannels)+1] = palette[preImage[i]*3+1];
    image[i*(*pChannels)+2] = palette[preImage[i]*3+2];
  }
  
  free(palette);
  free(preImage);
  return image;
}

void readpcx_cleanup(void)
{
  pcxfile = NULL;
  return;
}
