/*      
   Tsunami for KallistiOS ##version##
        
   texture.h

   (c)2002 Dan Potter

   $Id: texture.h,v 1.3 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_TEXTURE_H
#define __TSUNAMI_TEXTURE_H

#include "refcnt.h"
#include <plx/texture.h>

class Texture : public RefCnt {
public:
	Texture(const char *fn, bool use_alpha, bool yflip = false);
	Texture(int w, int h, int fmt);
	Texture();
	virtual ~Texture();

	// Load this texture from a file (if it hasn't been done already)
	bool loadFromFile(const char *fn, bool use_alpha, bool yflip);
	
	// Submit one of the poly headers
	void sendHdr(int list);

	// Attribute sets
	enum FilterType {
		FilterNone = PLX_FILTER_NONE,
		FilterBilinear = PLX_FILTER_BILINEAR
	};
	void	setFilter(FilterType filter);

	enum UVMode {
		UVRepeat = PLX_UV_REPEAT,
		UVClamp = PLX_UV_CLAMP
	};
	void	setUVClamp(UVMode umode, UVMode vmode);

	// Accessors
	pvr_ptr_t	getPtr() const { return m_txr->ptr; }
	int		getW() const { return m_txr->w; }
	int		getH() const { return m_txr->h; }
	int		getPxlfmt() const { return m_txr->fmt; }
	operator plx_texture_t * const() { return m_txr; }

private:

	plx_texture_t	* m_txr;
};

#endif	/* __TSUNAMI_TEXTURE_H */
