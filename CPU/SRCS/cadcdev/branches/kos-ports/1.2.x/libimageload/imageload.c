#include <imageload/imageload.h>

#include <string.h>
#include <malloc.h>

#define LOAD565(r, g, b) (((r>>3)<<11) | ((g>>2)<<5) | ((b>>3)))
#define LOAD1555(r, g, b, a) (((a>>7)<<15)|((r>>3)<<10)|((g>>3)<<5)|((b>>3)))
#define LOAD4444(r, g, b, a) (((a>>4)<<12)|((r>>4)<<8)|((g>>4)<<4)|((b>>4)))
#define LOAD8888(r, g, b, a) ((a<<24)|(r<<16)|(g<<8)|(b))

IMG_FILE img_guess(const char *filename)
{
  uint32 len = strlen(filename);
  const char *end = &filename[len-3];
  if (strncasecmp(end,"jpg",3) == 0)
    return IMG_FILE_JPEG;
  if (strncasecmp(end,"png",3) == 0)
    return IMG_FILE_PNG;
  if (strncasecmp(end,"bmp",3) == 0)
    return IMG_FILE_BMP;
  if (strncasecmp(end,"pcx",3) == 0)
    return IMG_FILE_PCX;
  return IMG_FILE_GUESS;
}

void
img_copy_texture(uint16 *dest, uint8 *source, uint32 channels, uint32 stride,
                 const IMG_INFO *info, uint32 w, uint32 h)
{
  uint32 i,j;
  uint16 *destRow;
  uint8 *pRow;
  uint8 r,g,b;
  
  for(i = 0; i < h; i++)
  {
    pRow = &source[i*stride];
    destRow = &dest[i*w];
    
    if (channels == 3)
    {
      switch(info->alpha)
        {
        case IMG_ALPHA_NONE:
          for(j = 0; j < w; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*3],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*3+1],1,2,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*3+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*3];
              g = pRow[j*3+1];
              b = pRow[j*3+2];
            }
            destRow[j] = LOAD565(r,g,b);
          }
          break;
        case IMG_ALPHA_MASK:
          for(j = 0; j < w; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*3],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*3+1],1,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*3+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*3];
              g = pRow[j*3+1];
              b = pRow[j*3+2];
            }
            destRow[j] = LOAD1555(r,g,b,255);
          }
          break;
        case IMG_ALPHA_FULL:
          for(j = 0; j < w; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*3],0,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*3+1],1,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*3+2],2,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*3];
              g = pRow[j*3+1];
              b = pRow[j*3+2];
            }
            destRow[j] = LOAD4444(r,g,b,255);
          }
          break;
        case IMG_ALPHA_KEYED:
          for(j = 0; j < w; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*3],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*3+1],1,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*3+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*3];
              g = pRow[j*3+1];
              b = pRow[j*3+2];
            }
            if (info->key == LOAD8888(pRow[j*3],pRow[j*3+1],pRow[j*3+2],0))
              destRow[j] = LOAD1555(r,g,b,0);
            else
              destRow[j] = LOAD1555(r,g,b,255);
          }
      }
    }
    else if (channels == 4)
    {
      switch(info->alpha)
        {
        case IMG_ALPHA_NONE:
          for(j = 0; j < h; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*4],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*4+1],1,2,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*4+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*4];
              g = pRow[j*4+1];
              b = pRow[j*4+2];
            }
            destRow[j] = LOAD565(r, g, b);
          }
          break;
        case IMG_ALPHA_MASK:
          for(j = 0; j < h; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*4],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*4+1],1,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*4+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*4];
              g = pRow[j*4+1];
              b = pRow[j*4+2];
            }
            destRow[j] = LOAD1555(r,g,b,pRow[j*4+3]);
          }
          break;
        case IMG_ALPHA_FULL:
          for(j = 0; j < h; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*4],0,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*4+1],1,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*4+2],2,4,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*4];
              g = pRow[j*4+1];
              b = pRow[j*4+2];
            }
            destRow[j] = LOAD4444(r,g,b,pRow[j*4+3]);
          }
          break;
        case IMG_ALPHA_KEYED:
          for(j = 0; j < h; j++)
          {
            if (info->dither == IMG_DITHER_JITTER)
            {
              r = jitter(pRow[j*4],0,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              g = jitter(pRow[j*4+1],1,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
              b = jitter(pRow[j*4+2],2,3,info->noise,
                         i%info->dither_height,j%info->dither_width);
            }
            else
            {
              r = pRow[j*4];
              g = pRow[j*4+1];
              b = pRow[j*4+2];
            }
            if (info->key == LOAD8888(pRow[j*4],pRow[j*4+1],pRow[j*4+2],0))
              destRow[j] = LOAD1555(r,g,b,0);
            else
              destRow[j] = LOAD1555(r,g,b,pRow[j*4+3]);
          }
          break;
        }
    }
  }
}

int img_load_file(const char *filename, IMG_INFO *info, kos_img_t *img)
{
  FILE *f = fopen(filename,"rb");

  if (info->type == IMG_FILE_GUESS)
    info->type = img_guess(filename);

  img_load_data(f,info,img);
      
  fclose(f);

  return 0;
}

int img_load_data(FILE *f, IMG_INFO *info, kos_img_t *img)
{
  uint32 channels, rowBytes;
  uint8 *data = NULL;
  uint8 allocate = 0;
  
  if (info == NULL)
  {
    allocate = 1;
    info = (IMG_INFO *)malloc(sizeof(IMG_INFO));
    memset(&info,0,sizeof(IMG_INFO));
  }

  
  switch(info->type)
  {
    case IMG_FILE_GUESS:
      return -1;
      break;
    case IMG_FILE_JPEG:
    {
      readjpeg_init(f);
      data = readjpeg_get_image(&channels, &rowBytes, &img->w, &img->h);
      readjpeg_cleanup();
      break;
    }
    case IMG_FILE_PNG:
    {
      readpng_init(f);
      data = readpng_get_image(&channels, &rowBytes, &img->w, &img->h);
      readpng_cleanup();
      break;
    }
    case IMG_FILE_BMP:
    {
      readbmp_init(f);
      data = readbmp_get_image(&channels, &rowBytes, &img->w, &img->h);
      readbmp_cleanup();
      break;
    }

    case IMG_FILE_PCX:
    {
      readpcx_init(f);
      data = readpcx_get_image(&channels, &rowBytes, &img->w, &img->h);
      readpcx_cleanup();
      break;
    }
  }

  if (info->dither_width == 0)
    info->dither_width = img->w;
  if (info->dither_height == 0)
    info->dither_height = img->h;

  img->data = (uint16 *)malloc(sizeof(uint16)*img->w*img->h);
  img->byte_count = sizeof(uint16)*img->w*img->h;
  img_copy_texture(img->data, data, channels, rowBytes, info,
                   img->w, img->h);

  free(data);

  if (allocate)
  {
    free(info);
  }

  switch(info->alpha)
  {
   case IMG_ALPHA_NONE:
    img->fmt = KOS_IMG_FMT(KOS_IMG_FMT_RGB565, 0);
    break;
   case IMG_ALPHA_MASK:
    img->fmt = KOS_IMG_FMT(KOS_IMG_FMT_ARGB1555, 0);
    break;
   case IMG_ALPHA_KEYED:
    img->fmt = KOS_IMG_FMT(KOS_IMG_FMT_ARGB1555, 0);
    break;
   case IMG_ALPHA_FULL:
    img->fmt = KOS_IMG_FMT(KOS_IMG_FMT_ARGB4444, 0);
    break;
  }
  
  return 0;
}
