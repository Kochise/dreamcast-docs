/*
     PLIB - A Suite of Portable Game Libraries
     Copyright (C) 2001  Steve Baker
 
     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Library General Public
     License as published by the Free Software Foundation; either
     version 2 of the License, or (at your option) any later version.
 
     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Library General Public License for more details.
 
     You should have received a copy of the GNU Library General Public
     License along with this library; if not, write to the Free
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 
     For further information visit http://plib.sourceforge.net

     $Id: fntTXF.cc,v 1.5 2002/11/06 07:16:03 bardtx Exp $
*/

// Modified for Dreamcast/KOS by Peter Hatch

#include "fntLocal.h"

/*
int x_twiddle (int x)
{
  int newX = 0;
  for (int i = 1; i < 32; ++i)
	{
	  if (x & i)
		nexX += i * i * 2;
	}
  return newX;
}
int y_twiddle (int y)
{
  int newY = 0;
  for (int i = 1; i < 32; ++i)
	{
	  if (y & i)
		newY += i * i;
	}
}

void txr_load_twiddle (void * src, pvr_ptr_t dst, uint32 width, uint32 height)
{
  // This only works for square textures.
  uint32 * xValues = (uint32*)malloc (width * 4);
  uint16 *srcTexture = (uint16*)src;
  uint16 *dstTexture = (uint16*)malloc (width * height * 2);
  
  for (int y = 0; y < height; j++)
	{
	  for (int x = 0; x < width; i++)
		{
		  dstTexture[x + y * width] = srcTexture[x_twiddle (x) + y_twiddle (y)];
		}
	}
}
*/

void twiddle_texture (uint16 * src, uint16 * dst, int& index, uint32 size, uint32 x, uint32 y, uint32 texWidth)
{
  if (size > 1)
	{
	  int halfSize = size / 2;
	  twiddle_texture (src, dst, index, halfSize, x, y, texWidth);
	  twiddle_texture (src, dst, index, halfSize, x, y + halfSize, texWidth);
	  twiddle_texture (src, dst, index, halfSize, x + halfSize, y, texWidth);
	  twiddle_texture (src, dst, index, halfSize, x + halfSize, y + halfSize, texWidth);
	}
  else
	{
	  dst[index++] = src[x + y * texWidth];
	}
}

void txr_load_twiddle (void * src, pvr_ptr_t dst, uint32 width, uint32 height)
{
  uint16 *twiddledTexture = (uint16*)malloc (width * height * 2);
  int index = 0;
  if (width < height)
	{
	  for (int x = 0; x < (int)height; x += width)
		{
		  twiddle_texture ((uint16*)src, twiddledTexture, index, width, x, 0, width);
		}
	}
  else
	{
	  for (int y = 0; y < (int)width; y += height)
		{
		  twiddle_texture ((uint16*)src, twiddledTexture, index, height, 0, y, width);
		}
	}
  //twiddle_texture ((uint16*)src, twiddledTexture, index, width, 0, 0, width);
  pvr_txr_load (twiddledTexture, dst, width * height * 2);
  free (twiddledTexture);
}

void txr_load_vq_bitmap (void * src, pvr_ptr_t dst, uint32 width, uint32 height, uint16 color0, uint16 color1)
{
  int textureSize = 2048 + (width * height) / 2;
  uint8 *texture = new uint8[textureSize];
  memset (texture, 0x00, textureSize);
  uint16 *codebook = (uint16*)texture;

  // Initialize the codebook
  for (int i = 0; i < 16; i++)
	{
	  codebook[i * 4 + 0] = (i & 1) ? color1 : color0;
	  codebook[i * 4 + 1] = (i & 2) ? color1 : color0;
	  codebook[i * 4 + 2] = (i & 4) ? color1 : color0;
	  codebook[i * 4 + 3] = (i & 8) ? color1 : color0;
	}
  // Initialize the indices into codebook
  uint8 *bitmap = (uint8*)src;
  // This won't work if width isn't evenly divisible by 8.
  uint32 stride = width / 8;
  for (int i = 0; i < (int)height; i++)
	{
	  for (int j = 0; j < (int)stride; ++j)
		{
		  uint8 bitmapValue = bitmap[i * stride + j];
		  texture[2048 + ((i * stride + j) * 2)    ] = bitmapValue & 0x0F;
		  texture[2048 + ((i * stride + j) * 2) + 1] = (bitmapValue & 0xF0) >> 4;
		}
	}
  pvr_txr_load (texture, dst, textureSize);
  delete[] texture;
}

void twiddle_bitmap_texture (uint8 * src, uint8 * dst, int& index, uint32 size, uint32 x, uint32 y, uint32 texWidth)
{
  if (size > 1)
	{
	  int halfSize = size / 2;
	  twiddle_bitmap_texture (src, dst, index, halfSize, x, y, texWidth);
	  twiddle_bitmap_texture (src, dst, index, halfSize, x, y + halfSize, texWidth);
	  twiddle_bitmap_texture (src, dst, index, halfSize, x + halfSize, y, texWidth);
	  twiddle_bitmap_texture (src, dst, index, halfSize, x + halfSize, y + halfSize, texWidth);
	}
  else
	{
	  int srcIndex = x + y * texWidth;
	  int srcValue = src[srcIndex >> 3];
	  srcValue = (srcValue >> (srcIndex & 7)) & 1;
	  dst[index >> 3] |= srcValue << (index & 7);
	  ++index;
	}
}

void txr_load_twiddle_vq_bitmap (void * src, pvr_ptr_t dst, uint32 width, uint32 height, uint16 color0, uint16 color1)
{
  uint8 *twiddledTexture = (uint8*)malloc (width * height / 4);
  memset (twiddledTexture, 0, width * height / 4);
  int index = 0;
  if (width < height)
	{
	  for (int x = 0; x < (int)height; x += width)
		{
		  twiddle_bitmap_texture ((uint8*)src, twiddledTexture, index, width, x, 0, width);
		}
	}
  else
	{
	  for (int y = 0; y < (int)width; y += height)
		{
		  twiddle_bitmap_texture ((uint8*)src, twiddledTexture, index, height, 0, y, width);
		}
	}
  //twiddle_bitmap_texture ((uint8*)src, twiddledTexture, index, width, 0, 0, width);
  txr_load_vq_bitmap (twiddledTexture, dst, width, height, color0, color1);
  free (twiddledTexture);
}

FILE *curr_image_fd;
int isSwapped = false;

bool fntTexFont::loadTXF (const char *fname)
{
  FILE *fd;

  if ( (fd = fopen (fname, "rb") ) == NULL)
	{
	  ulSetError (UL_WARNING, "fntLoadTXF: Failed to open '%s' for reading.", fname);
	  return false;
	}

  curr_image_fd = fd;

  unsigned char magic[4];

  if ( (int)fread (&magic, sizeof (unsigned int), 1, fd ) != 1)
	{
	  ulSetError (UL_WARNING, "fntLoadTXF: '%s' an empty file!", fname);
	  return false;
	}

  if (magic[0] != 0xFF || magic[1] != 't' || magic[2] != 'x' || magic[3] != 'f')
	{
	  ulSetError ( UL_WARNING, "fntLoadTXF: '%s' is not a 'txf' font file.", fname);
	  return false;
	}

  isSwapped = false;
  int endianness = _fnt_readInt ();

  isSwapped = (endianness != 0x12345678);

  int format = _fnt_readInt ();
  tex_width = _fnt_readInt ();
  tex_height = _fnt_readInt ();
  int max_height = _fnt_readInt ();
  _fnt_readInt ();
  int num_glyphs = _fnt_readInt ();

  int w = tex_width;
  int h = tex_height;

  float xstep = 0.5f / (float) w;
  float ystep = 0.5f / (float) h;

  /*
    Load the TXF_Glyph array
  */

  TXF_Glyph glyph;

  for (int i = 0; i < num_glyphs; i++)
	{
	  glyph.ch = _fnt_readShort ();

	  glyph.w = _fnt_readByte ();
	  glyph.h = _fnt_readByte ();
	  glyph.x_off = _fnt_readByte ();
	  glyph.y_off = _fnt_readByte ();
	  glyph.step = _fnt_readByte ();
	  glyph.unknown = _fnt_readByte ();
	  glyph.x = _fnt_readShort ();
	  glyph.y = _fnt_readShort ();

	  setGlyph ( (char)   glyph.ch,
				 (float) glyph.x                / (float) w + xstep,
				 (float)(glyph.x + glyph.w)     / (float) w + xstep,
				 (float) glyph.y                / (float) h + ystep,
				 (float)(glyph.y + glyph.h)     / (float) h + ystep,
				 (float) glyph.x_off            / (float) max_height,
				 (float)(glyph.x_off + glyph.w) / (float) max_height,
				 (float) glyph.y_off            / (float) max_height,
				 (float)(glyph.y_off + glyph.h) / (float) max_height);
	}

  exists[' '] = false;

  /*
    Load the image part of the file
  */

  switch (format)
	{
    case FNT_BYTE_FORMAT:
	{
	  ulSetError ( UL_WARNING, "fntLoadTXF: Byte format texture no longer supported ('%s').", fname);
	  return false;

	  /*
	  unsigned char *orig = new unsigned char [ntexels];

	  if ( (int)fread (orig, 1, ntexels, fd) != ntexels)
        {
          ulSetError ( UL_WARNING, "fntLoadTXF: Premature EOF in '%s'.", fname);
          return false;
        }

	  teximage = new uint8 [ntexels * 2];

	  for (int i = 0; i < ntexels; i++)
        {
		  uint8 argb = orig [i] >> 4;
		  argb = argb + (argb << 4);
          teximage [i * 2] = argb;
          teximage [i * 2 + 1] = argb;
        }

	  delete orig;
	  */
	}
	break;
   
    case FNT_BITMAP_FORMAT:
	{
	  uint32 bitmapSize = w * h / 8;
	  uint8 *bitmap = new uint8[bitmapSize];

	  if ( (int)fread (bitmap, 1, bitmapSize, fd) != (int)bitmapSize)
        {
          delete bitmap;
          ulSetError (UL_WARNING, "fntLoadTXF: Premature EOF in '%s'.", fname);
          return false;
      	}

	  texture = pvr_mem_malloc (2048 + (w * h) / 2);
	  txr_load_twiddle_vq_bitmap (bitmap, texture, w, h, 0x0000, 0xFFFF);

	  delete bitmap;
	}
	break;

    default:
      ulSetError (UL_WARNING, "fntLoadTXF: Unrecognised format type in '%s'.", fname);
      return false;
	}

  fclose (fd);

  fixed_pitch = false;

  return true;
}
