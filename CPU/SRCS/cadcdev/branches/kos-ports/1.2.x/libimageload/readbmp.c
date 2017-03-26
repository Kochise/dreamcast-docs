#include <kos.h>

#include <stdio.h>
#include <stdlib.h>

#include <imageload/imageload.h>

#pragma pack(1)

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

typedef struct { 
  uint16    bfType; 
  uint32   bfSize; 
  uint16    bfReserved1; 
  uint16    bfReserved2; 
  uint32   bfOffBits; 
} BITMAPFILEHEADER; 

typedef struct { 
  uint32 bcSize; 
  uint16 bcWidth; 
  uint16 bcHeight; 
  uint16 bcPlanes; 
  uint16 bcBitCount; 
} BITMAPCOREHEADER;

typedef struct tagBITMAPINFOHEADER {
    uint32  biSize;          
    int32  biWidth;         
    int32  biHeight;        
    uint16   biPlanes;        
    uint16   biBitCount;      
    uint32  biCompression;   
    uint32  biSizeImage;     
    int32  biXPelsPerMeter; 
    int32  biYPelsPerMeter; 
    uint32  biClrUsed;       
    uint32  biClrImportant;  
} BITMAPINFOHEADER;
 
typedef struct 
{
  uint8 rgbBlue;
  uint8 rgbGreen;
  uint8 rgbRed;
  uint8 rgbAlpha;
}RGBQUAD;
#pragma pack()


FILE *bmpfile;

uint32 readbmp_init(FILE *infile)
{
  bmpfile = infile;
  return 0;
}

uint8 *readbmp_get_image(uint32 *pChannels, uint32 *pRowbytes,
                         uint32 *pWidth, uint32 *pHeight)
{
  BITMAPINFOHEADER bitmapInfo;
  BITMAPFILEHEADER bitmapFile;
  RGBQUAD *colorTable;
  uint32 nNumColors;
  uint8 *ourbuffer, *imageBuffer, *buffer;
  uint32 rmask = 0xff, gmask = 0xff, bmask = 0xff;
  uint32 rshift = 0, gshift = 0, bshift = 0;
  uint32 skip, r, g, b, k;
  uint32 x, y;
  uint8 byte;
  
  /* read the BITMAPFILEHEADER */
  uint32 bytesRead = fread(&bitmapFile, 1, sizeof(BITMAPFILEHEADER), bmpfile);
  if ( bytesRead != sizeof(BITMAPFILEHEADER) ||
       bitmapFile.bfType != 0x4d42 /* 'BM' */)
  {
    return NULL;
  }

  /* for now, don't even deal with CORE headers */
  bytesRead = fread(&bitmapInfo, 1, sizeof(BITMAPINFOHEADER), bmpfile);
  if ( bytesRead != sizeof(BITMAPINFOHEADER) ||
       bitmapInfo.biSize == sizeof(BITMAPCOREHEADER))
  {	
    return NULL;
  }

  nNumColors = bitmapInfo.biClrUsed;
  if (nNumColors == 0)
    if (bitmapInfo.biBitCount != 24)
      nNumColors = 1 << bitmapInfo.biBitCount;	/* standard size table */

  /*	fill in some default values if they are zero */
  if (bitmapInfo.biClrUsed == 0)
    bitmapInfo.biClrUsed = nNumColors;

  if (bitmapInfo.biSizeImage == 0)
  {
    /* the magic below is to meet the windows alignment requirements. */
    bitmapInfo.biSizeImage = ((((bitmapInfo.biWidth * bitmapInfo.biBitCount) + 31) & ~31) >> 3)
      * bitmapInfo.biHeight;
  }

  /* read the color table */
  colorTable = malloc(sizeof(RGBQUAD)*nNumColors);
  bytesRead = fread(colorTable, 1, sizeof(RGBQUAD)*nNumColors, bmpfile);

  if (bytesRead != nNumColors*sizeof(RGBQUAD))
  {
    free(colorTable);
    return NULL;
  }

  if (bitmapFile.bfOffBits != 0)
    fseek(bmpfile,bitmapFile.bfOffBits,SEEK_SET);
  
  imageBuffer = malloc(sizeof(uint8)*bitmapInfo.biSizeImage);
  buffer = imageBuffer;
  bytesRead = fread(buffer, 1, bitmapInfo.biSizeImage, bmpfile);
  
  if ( bytesRead != bitmapInfo.biSizeImage*sizeof(uint8))
  {
    free(colorTable);
    free(imageBuffer);
    return NULL;
  }

  *pChannels = 3;
  *pRowbytes = bitmapInfo.biWidth**pChannels;
  *pWidth = bitmapInfo.biWidth;
  *pHeight = bitmapInfo.biHeight;
  ourbuffer = (uint8*)malloc(*pRowbytes**pHeight);
  
  if (bitmapInfo.biCompression == BI_BITFIELDS) 
  {
    int bit;
    rmask = ((unsigned int *)colorTable)[0];
    gmask = ((unsigned int *)colorTable)[1];
    bmask = ((unsigned int *)colorTable)[2];
    for (bit = bitmapInfo.biBitCount - 1; bit >= 0; bit--) 
    {
      if (bmask & (1 << bit))
        bshift = bit;
      if (gmask & (1 << bit))
        gshift = bit;
      if (rmask & (1 << bit))
        rshift = bit;
    }  
  }
  else if (bitmapInfo.biBitCount == 16) 
  {
    rmask = 0x7C00;
    gmask = 0x03E0;
    bmask = 0x001F;
    rshift = 10;
    gshift = 5;
    bshift = 0;
  }
  else if (bitmapInfo.biBitCount == 32) 
  {
    rmask = 0x00FF0000;
    gmask = 0x0000FF00;
    bmask = 0x000000FF;
    rshift = 16;
    gshift = 8;
    bshift = 0;
  }
	
  /* for now we will not handle RLE encoded data */

  if (bitmapInfo.biBitCount == 4) 
  {
    if (bitmapInfo.biCompression == BI_RLE4)
    {
      free(colorTable);
      free(imageBuffer);
      free(ourbuffer);
      return NULL;
    }
    else
    if (bitmapInfo.biCompression == BI_RGB) 
    {
      skip = ((((bitmapInfo.biWidth + 7) / 8) * 8) - bitmapInfo.biWidth) / 2;
      byte = 0;
      for (y = 0; y < bitmapInfo.biHeight; y++) 
      {
        for (x = 0; x < bitmapInfo.biWidth; x++) 
        {
          if ((x & 1) == 0)
            byte = *(buffer++);
          k = (byte & 0xF0) >> 4;
          ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x] = colorTable[k].rgbRed;
          ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+1] = colorTable[k].rgbGreen;
          ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+2] = colorTable[k].rgbBlue;
          byte <<= 4;
        }
        buffer += skip;
      }
    }
  }
  if (bitmapInfo.biBitCount == 8) 
  {
    if (bitmapInfo.biCompression == BI_RLE8)
    {
      free(colorTable);
      free(imageBuffer);
      free(ourbuffer);
      return NULL;
    }
    else 
      if (bitmapInfo.biCompression == BI_RGB) 
      {
        skip = (((bitmapInfo.biWidth + 3) / 4) * 4) - bitmapInfo.biWidth;
        for (y = 0; y < bitmapInfo.biHeight; y++) 
        {
          for (x = 0; x < bitmapInfo.biWidth; x++) 
          {
            byte = *(buffer++);
            ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x] = colorTable[byte].rgbRed;
            ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+1] = colorTable[byte].rgbGreen;
            ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+2] = colorTable[byte].rgbBlue;
          }
          buffer += skip;
        }
      }
  }
  else if (bitmapInfo.biBitCount == 16) 
  {
    skip = (((bitmapInfo.biWidth * 16 + 31) / 32) * 4) - (bitmapInfo.biWidth * 2);
    for (y = 0; y < bitmapInfo.biHeight; y++) 
    {
      for (x = 0; x < bitmapInfo.biWidth; x++) 
      {
        r = ((uint16)(*buffer) & rmask) >> rshift;
        g = ((uint16)(*buffer) & gmask) >> gshift;
        b = ((uint16)(*(buffer++)) & bmask) >> bshift;

        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x] = r;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+1] = g;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+2] = b;
      }
      buffer += skip;
    }
  }
  else if (bitmapInfo.biBitCount == 24) 
  {
    skip = (4 - ((bitmapInfo.biWidth * 3) % 4)) & 3;
    for (y = 0; y < bitmapInfo.biHeight; y++) 
    {
      for (x = 0; x < bitmapInfo.biWidth; x++) 
      {
        b = *(buffer++);
        g = *(buffer++);
        r = *(buffer++);

        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x] = r;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+1] = g;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+2] = b;
      }
      buffer += skip;
    }
  }
  else if (bitmapInfo.biBitCount == 32) 
  {
    skip = (((bitmapInfo.biWidth * 32 + 31) / 32) * 4) - (bitmapInfo.biWidth * 4);
    for (y = 0; y < bitmapInfo.biHeight; y++) 
    {
      for (x = 0; x < bitmapInfo.biWidth; x++) 
      {
        r = ((uint32)(*buffer) & rmask) >> rshift;
        g = ((uint32)(*buffer) & gmask) >> gshift;
        b = ((uint32)(*buffer) & bmask) >> bshift;

        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x] = r;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+1] = g;
        ourbuffer[(bitmapInfo.biHeight-y-1)**pRowbytes+3*x+2] = b;
        
        buffer+=2;
      }
      buffer += skip;
    }
  }

  free(colorTable);
  free(imageBuffer);

  return ourbuffer;
}

void readbmp_cleanup(void)
{
  bmpfile = NULL;
  return;
}
