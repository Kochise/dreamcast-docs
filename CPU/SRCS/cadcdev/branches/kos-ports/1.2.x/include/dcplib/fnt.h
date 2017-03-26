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

     $Id: fnt.h,v 1.1 2003/02/27 03:46:29 bardtx Exp $
*/

// Modified for Dreamcast/KOS by Peter Hatch

#ifndef _FNT_H_
#define _FNT_H_  1

#include <kos.h>
#include "sg.h"

const int FNTMAX_CHAR = 256;

class fntFont
{
public:
  fntFont () ;

  virtual ~fntFont () ;

  /*  Pure virtuals aren't working currently... :(
  virtual void getBBox (const char *s, float pointsize, float italic, float *left, float *right, float *bot , float *top) = 0;
  virtual void putch (sgVec3 curpos, float pointsize, float italic, char c, float red, float green, float blue, float alpha) = 0;
  virtual void puts (sgVec3 curpos, float pointsize, float italic, const char *s, float red, float green, float blue, float alpha) = 0;
  virtual void begin () = 0;
  virtual void end () = 0;

  virtual bool load (const char *fname) = 0;

  virtual void setFixedPitch (bool fix) = 0;
  virtual bool isFixedPitch () const = 0;

  virtual void setWidth (float w) = 0;
  virtual void setGap (float g) = 0;

  virtual float getWidth () const = 0;
  virtual float getGap () const = 0;

  virtual bool hasGlyph (char c) = 0;
  */
  virtual void getBBox (const char *s, float pointsize, float italic, float *left, float *right, float *bot, float *top) {}
  virtual void putch (sgVec3 curpos, float pointsize, float italic, char c, float red, float green, float blue, float alpha) {}
  virtual void puts (sgVec3 curpos, float pointsize, float italic, const char *s, float red, float green, float blue, float alpha) {}
  virtual void begin (int filter_mode) {}
  virtual void end () {}

  virtual bool load (const char *fname) { return false; }

  virtual void setFixedPitch (bool fix) {}
  virtual bool isFixedPitch () const { return false; }

  virtual void setWidth (float w) {}
  virtual void setGap (float g) {}

  virtual float getWidth () const { return 0.0f; }
  virtual float getGap () const { return 0.0f; }

  virtual bool hasGlyph (char c) { return false; }
};


class fntTexFont : public fntFont
{
private:
  //uint32 texture;
  pvr_ptr_t texture;
  uint32 tex_width;
  uint32 tex_height;

  bool bound;
  bool fixed_pitch;

  float width; /* The width of a character in fixed-width mode */
  float gap; /* Set the gap between characters */

  bool exists[FNTMAX_CHAR]; /* true if character exists in tex-map */

  /*
    The quadrilaterals that describe the characters
    in the font are drawn with the following texture
    and spatial coordinates. The texture coordinates
    are in (S,T) space, with (0,0) at the bottom left
    of the image and (1,1) at the top-right.

    The spatial coordinates are relative to the current
    'cursor' position. They should be scaled such that
    1.0 represent the height of a capital letter. Hence,
    characters like 'y' which have a descender will be
    given a negative v_bot. Most capitals will have
    v_bot==0.0 and v_top==1.0.
  */

  /* Texture coordinates */

  float t_top  [FNTMAX_CHAR]; /* Top    edge of each character [0..1] */
  float t_bot  [FNTMAX_CHAR]; /* Bottom edge of each character [0..1] */
  float t_left [FNTMAX_CHAR]; /* Left   edge of each character [0..1] */
  float t_right[FNTMAX_CHAR]; /* Right  edge of each character [0..1] */

  /* Vertex coordinates. */

  float v_top  [FNTMAX_CHAR];
  float v_bot  [FNTMAX_CHAR];
  float v_left [FNTMAX_CHAR];
  float v_right[FNTMAX_CHAR];

  void bind_texture (int filter_mode)
	{
	  // PSH OPTIMIZE: it would probably make sense to only compile the header once, and store it as a class variable, instead of recalculating it every time.

	assert( texture != NULL );
      pvr_poly_cxt_t polyContext;
	  pvr_poly_hdr_t polyHeader;

	  pvr_poly_cxt_txr (&polyContext, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444 | PVR_TXRFMT_TWIDDLED | PVR_TXRFMT_VQ_ENABLE, tex_width, tex_height, texture, filter_mode);
	  pvr_poly_compile (&polyHeader, &polyContext);
	  //pvr_list_prim (PVR_LIST_TR_POLY, &polyHeader, sizeof(polyHeader)); // Not implemented yet
	  pvr_prim (&polyHeader, sizeof (polyHeader) );
	}

  float low_putch (sgVec3 curpos, float pointsize, float italic, char c, float red, float green, float blue, float alpha);

  bool loadTXF (const char *fname);

public:
  fntTexFont () : fntFont (), texture (0), tex_width (0), tex_height (0), bound (false), fixed_pitch (true), width (1.0f), gap (0.1f)
	{
	  memset (exists, false, FNTMAX_CHAR * sizeof (int) );
	  texture = NULL;
	}

  fntTexFont (const char *fname) : fntFont (), texture (0), tex_width (0), tex_height (0), bound (false), fixed_pitch (true), width (1.0f), gap (0.1f)
	{
	  memset (exists, false, FNTMAX_CHAR * sizeof (int) );
	  texture = NULL;
	  load (fname);
	}

  fntTexFont(const fntTexFont & other) {
  	assert(false);
  }

  ~fntTexFont ()
	{
	  if (tex_width > 0)
		{
		  assert( texture != NULL );
		  pvr_mem_free (texture);
		}
	}

  bool load (const char *fname);

  void setFixedPitch (bool fix)
	{
	  fixed_pitch = fix;
	} 
  bool isFixedPitch () const
    {
	  return fixed_pitch;
	} 

  void setWidth (float w)
	{
	  width = w;
	} 
  void setGap (float g)
	{
	  gap = g;
	} 

  float getWidth () const
	{
	  return width;
	} 
  float getGap () const
	{
	  return gap;
	} 

  void setGlyph (char c, float tex_left, float tex_right, float tex_bot, float tex_top, float vtx_left, float vtx_right, float vtx_bot, float vtx_top);

  bool getGlyph (char c, float *tex_left = NULL, float *tex_right = NULL, float *tex_bot = NULL, float *tex_top = NULL, float *vtx_left = NULL, float *vtx_right = NULL, float *vtx_bot = NULL, float *vtx_top = NULL);

  bool hasGlyph (char c)
	{
	  return getGlyph (c);
	}

  void getBBox (const char *s, float pointsize, float italic, float *left, float *right, float *bot, float *top);

  void begin (int filter_mode)
	{
	  bind_texture (filter_mode);
	  bound = true;
	}

  void end ()
	{
	  bound = false ;
	}

  void puts (sgVec3 curpos, float pointsize, float italic, const char *s, float red, float green, float blue, float alpha);

  void putch (sgVec3 curpos, float pointsize, float italic, char c, float red, float green, float blue, float alpha)
	{
	  if (!bound)
		{
		  bind_texture (PVR_FILTER_NONE);
		}
	  low_putch (curpos, pointsize, italic, c, red, green, blue, alpha);
	}
};


class fntRenderer
{
  fntFont *font;

  sgVec3 curpos;

  float pointsize;
  float italic;

  float red, green, blue, alpha;

  int filter_mode;

public:
  fntRenderer () : pointsize (10.0f), italic (0.0f), red (1.0f), green (1.0f), blue (1.0f), alpha (1.0f), filter_mode (PVR_FILTER_NONE)
	{
	  start2f ( 0.0f, 0.0f );
	  font = NULL ;
	}

  void start3fv (sgVec3 pos)
	{
	  sgCopyVec3 (curpos, pos);
	}
  void start2fv (sgVec2 pos)
	{
	  sgCopyVec2 (curpos, pos);
	  curpos[2] = 512.0f;
	}
  void start2f (float x, float y )
	{
	  sgSetVec3 (curpos, x, y, 512.0f);
	}
  void start3f (float x, float y, float z)
	{
	  sgSetVec3 (curpos, x, y, z);
	}

  void getCursor (float *x, float *y, float *z) const
	{
	  if (x != 0)
		*x = curpos [0];
	  if (y != 0)
		*y = curpos [1];
	  if (z != 0)
		*z = curpos [2];
	}

  void setFont (fntFont *f)
	{
	  font = f;
	}
  fntFont *getFont () const
	{
	  return font;
	}

  void setSlant (float i)
	{
	  italic = i;
	} 
  void setPointSize (float p)
	{
	  pointsize = p;
	}

  float getSlant () const
	{
	  return italic;
	} 
  float getPointSize () const
	{
	  return pointsize;
	} 

  void setColor (float r, float g, float b, float a = 1.0f)
	{
	  red = r;
	  green = g;
	  blue = b;
	  alpha = a;
	}
  void getColor (float *r, float *g, float *b, float *a = NULL)
	{
	  if (r != 0)
		*r = red;
	  if (g != 0)
		*g = green;
	  if (b != 0)
		*b = blue;
	  if (a != 0)
		*a = alpha;
	}

  int getFilterMode ()
	{
	  return filter_mode;
	}
  void setFilterMode (int fm)
	{
	  filter_mode = fm;
	}
  
  void begin () 
	{
	  font->begin (filter_mode);
	}
  void end ()
	{
	  font->end ();
	}

  void putch (char c)
	{
	  font->putch (curpos, pointsize, italic, c, red, green, blue, alpha);
	}
  void puts (const char *s)
	{
	  font->puts (curpos, pointsize, italic, s, red, green, blue, alpha);
	}
};

#endif
