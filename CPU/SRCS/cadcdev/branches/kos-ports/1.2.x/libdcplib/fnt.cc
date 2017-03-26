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

     $Id: fnt.cc,v 1.4 2002/04/11 07:41:08 bardtx Exp $
*/

// Modified for Dreamcast/KOS by Peter Hatch

#include <dcplib/fnt.h>

fntFont::fntFont () {}
fntFont::~fntFont () {}

bool fntTexFont::load (const char *fname)
{
  const char *p;

  for (p = &fname[strlen (fname) - 1]; p != fname && *p != '.' && *p != '/'; p--)
    /* Do nothing */ ;

  if (strcmp (p, ".txf") == 0)
	{
	  return loadTXF (fname);
	}
  else
	{
	  ulSetError (UL_WARNING, "fnt::load: Error - Unrecognised file format for '%s'", fname);
	  return false ;
	}
}


float fntTexFont::low_putch (sgVec3 curpos, float pointsize, float italic, char c, float red, float green, float blue, float alpha)
{
  unsigned int cc = (unsigned char) c;

  /* Auto case-convert if character is absent from font. */

  if (!exists[cc])
	{
	  if (cc >= 'A' && cc <= 'Z')
		{
		  cc = cc - 'A' + 'a';
		}
	  else
		{
		  if (cc >= 'a' && cc <= 'z')
			{
			  cc = cc - 'a' + 'A';
			}
		}

	  if (cc == ' ')
		{
		  curpos [0] += pointsize / 2.0f;
		  return pointsize / 2.0f;
		}
	}

  /*
    We might want to consider making some absent characters from
    others (if they exist): lowercase 'l' could be made into digit '1'
    or letter 'O' into digit '0'...or vice versa. We could also
    make 'b', 'd', 'p' and 'q' by mirror-imaging - this would
    save a little more texture memory in some fonts.
  */

  if (!exists[cc])
    return 0.0f;

  //vertex_ot_t vert;
  pvr_vertex_t vert;

  //vert.oa = vert.or = vert.og = vert.ob = 0.0f;
  vert.oargb = 0;

  //vert.a = alpha;
  //vert.r = red;
  //vert.g = green;
  //vert.b = blue;
  vert.argb = PVR_PACK_COLOR (alpha, red, green, blue);

  //vert.flags = TA_VERTEX_NORMAL;
  vert.flags = PVR_CMD_VERTEX;
  vert.u = t_left[cc];
  vert.v = t_bot[cc];
  vert.x = curpos[0] + v_left[cc] * pointsize;
  vert.y = curpos[1] - v_bot[cc] * pointsize;
  vert.z = curpos[2];
  //ta_commit_vertex (&vert, sizeof (vert) );
  //pvr_list_prim (PVR_LIST_PT_POLY, &vert, sizeof (vert) );  // Not implemented yet
  pvr_prim (&vert, sizeof (vert) );

  //vert.flags = TA_VERTEX_NORMAL;
  vert.v = t_top[cc];
  vert.x = curpos[0] + italic + v_left[cc] * pointsize;
  vert.y = curpos[1] - v_top[cc] * pointsize;
  //ta_commit_vertex (&vert, sizeof (vert) );
  //pvr_list_prim (PVR_LIST_PT_POLY, &vert, sizeof (vert) );  // Not implemented yet
  pvr_prim (&vert, sizeof (vert) );

  //vert.flags = TA_VERTEX_NORMAL;
  vert.u = t_right[cc];
  vert.v = t_bot[cc];
  vert.x = curpos[0] + v_right[cc] * pointsize;
  vert.y = curpos[1] - v_bot[cc] * pointsize;
  //ta_commit_vertex (&vert, sizeof (vert) );
  //pvr_list_prim (PVR_LIST_PT_POLY, &vert, sizeof (vert) );  // Not implemented yet
  pvr_prim (&vert, sizeof (vert) );

  //vert.flags = TA_VERTEX_EOL;
  vert.flags = PVR_CMD_VERTEX_EOL;
  vert.v = t_top[cc];
  vert.x = curpos[0] + italic + v_right[cc] * pointsize;
  vert.y = curpos[1] - v_top[cc] * pointsize;
  //ta_commit_vertex (&vert, sizeof (vert) );
  //pvr_list_prim (PVR_LIST_PT_POLY, &vert, sizeof (vert) );  // Not implemented yet
  pvr_prim (&vert, sizeof (vert) );
  
  float ww = (gap + (fixed_pitch ? width : v_right[cc]) ) * pointsize;
  curpos[0] += ww;
  return ww;
}


void fntTexFont::setGlyph (char c, float tex_left, float tex_right, float tex_bot, float tex_top, float vtx_left, float vtx_right, float vtx_bot, float vtx_top)
{
  unsigned int cc = (unsigned char) c;

  exists[cc] = true;

  t_left[cc] = tex_left;
  t_right[cc] = tex_right;
  t_bot[cc] = tex_bot;
  t_top[cc] = tex_top;

  v_left[cc] = vtx_left;
  v_right[cc] = vtx_right;
  v_bot[cc] = vtx_bot;
  v_top[cc] = vtx_top;
}


bool fntTexFont::getGlyph (char c, float *tex_left, float *tex_right, float *tex_bot, float *tex_top, float *vtx_left, float *vtx_right, float *vtx_bot, float *vtx_top)
{
  unsigned int cc = (unsigned char) c;

  if (!exists[cc])
	return false;

  if (tex_left != NULL)
	*tex_left = t_left[cc];
  if (tex_right != NULL)
	*tex_right = t_right[cc];
  if (tex_bot != NULL)
	*tex_bot = t_bot[cc];
  if (tex_top != NULL)
	*tex_top = t_top[cc];

  if (vtx_left != NULL)
	*vtx_left = v_left[cc];
  if (vtx_right != NULL)
	*vtx_right = v_right[cc];
  if (vtx_bot != NULL)
	*vtx_bot = v_bot[cc];
  if (vtx_top != NULL)
	*vtx_top = v_top[cc];

  return true ;
}


void fntTexFont::getBBox ( const char *s, float pointsize, float italic, float *left, float *right, float *bot , float *top)
{
  float h_pos = 0.0f;
  float v_pos = 0.0f;
  float l, r, b, t;
  float max_r, max_b;

  l = r = max_r = b = max_b = t = 0.0f ;

  while (*s != '\0')
	{
	  if (*s == '\n')
		{
		  r = h_pos = 0.0f;
		  v_pos -= 1.333f;
		  s++;
		  continue;
		}

	  unsigned int cc = (unsigned char) *(s++);

	  if (!exists[cc])
		{
		  if (cc >= 'A' && cc <= 'Z')
			cc = cc - 'A' + 'a';
		  else
			if (cc >= 'a' && cc <= 'z')
			  cc = cc - 'a' + 'A';
  
		  if (cc == ' ')
			{
			  r += 0.5f;
			  h_pos += 0.5f;

			  if (max_r < r)
				max_r = r ;

			  continue;
			}
		}

	  if (!exists[cc])
		continue ;

	  if (italic >= 0)
		{
		  if (l > h_pos + v_left[cc])
			l = h_pos + v_left [cc];
		  if ( r < gap + h_pos + v_right[cc] + italic)
			r = gap + h_pos + v_right[cc] + italic;
		}
	  else
		{
		  if (l > h_pos + v_left [cc] + italic)
			l = h_pos + v_left [cc] + italic;
		  if (r < gap + h_pos + v_right[cc] + italic)
			r = gap + h_pos + v_right[cc];
		}

	  if (b > v_pos + v_bot[cc])
		b = v_pos + v_bot[cc];
	  if (t < v_pos + v_top[cc])
		t = v_pos + v_top[cc];

	  if ( max_b > b )
		max_b = b;
	  if ( max_r < r )
		max_r = r;

	  h_pos += gap + (fixed_pitch ? width : v_right[cc]);
	}

  if (left  != NULL )
	*left = l * pointsize;
  if (right != NULL )
	*right = r * pointsize;
  if (top   != NULL )
	*top = t * pointsize;
  if (bot   != NULL )
	*bot = b * pointsize;
}


void fntTexFont::puts (sgVec3 curpos, float pointsize, float italic, const char *s, float red, float green, float blue, float alpha)
{
  SGfloat origx = curpos[0];
	
  if (!bound)
    bind_texture (PVR_FILTER_NONE);

  while (*s != '\0')
	{
	  if (*s == '\n')
		{
		  curpos[0] = origx;
		  curpos[1] += pointsize * 1.333f;
		}
	  else
		{
		  low_putch (curpos, pointsize, italic, *s, red, green, blue, alpha);
		}
	  s++ ;
	}
}
