/*
   Tiki

   texture.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TEXTURE_H
#define __TIKI_TEXTURE_H

#include "object.h"
#include "Tiki/glhdrs.h"

namespace Tiki {
namespace GL {

class Texture : public Object {
public:
	TIKI_OBJECT_DECLS(Texture)

	// This list must be kept in sync with Image.
	// Apparently C++ is too idiotic to allow a cross-class 'using'.
	enum Fmt {
		None = 0,
		RGB888,		/* Interleaved r/g/b bytes (24-bit) */
		ARGB8888,	/* Interleaved a/r/g/b bytes (32-bit) */
		RGB565,		/* r/g/b 5/6/5 (16-bit) */
		ARGB4444,	/* a/r/g/b 4/4/4/4 (16-bit) */
		ARGB1555,	/* a/r/g/b 1/5/5/5 (16-bit) */
		PAL4BPP,	/* Paletted (4-bit) */
		PAL8BPP,	/* Paletted (8-bit) */
		YUV422,		/* y/u/v 4/2/2 (8-bit) */
		BGR565,		/* b/g/r 5/6/5 (16-bit) */
		RGBA8888,	/* Interleaved r/g/b/a bytes (32-bit) */
		Count
	};

	Texture(const string & fn, bool use_alpha);
	Texture(int w, int h, Fmt fmt);
	Texture();
	virtual ~Texture();

	// Load this texture from a file (if it hasn't been done already).
	// useAlpha is a tristate: 0 = no, 1 = yes, -1 = default
	bool loadFromFile(const string & fn, int useAlpha);

	// Create this texture as a canvas.
	bool createCanvas(int w, int h, Fmt fmt);

	// Destroy any resources this texture takes up, and reset it.
	void destroy(bool initial = false);
	
	// Select this texture for GL usage.
	void select();
	
	// Deselect textures for GL usage.
	static void deselect();

	// Attribute sets
	enum FilterType {
		FilterNone = 0,
		FilterBilinear = 1,
		FilterTrilinear1 = 2
	};
	void	setFilter(FilterType filter);

	enum UVMode {
		UVRepeat = 0,
		UVClamp = 1
	};
	void	setUVClamp(UVMode umode, UVMode vmode);

	// Canvas access
	void *	canvasLock();
	void	canvasUnlock();

	// Accessors
	void *	getPtr() const { return m_ptr; }
	int	getW() const { return m_w; }
	int	getH() const { return m_h; }
	Fmt	getPxlfmt() const { return m_fmt; }

private:
	void	convertToGl();

	uint8	* m_ptr;	// Pointer to data in the requested format
	int	m_w, m_h;	// Texture width/height
	Fmt	m_fmt;		// Format spec
	uint8	* m_txrdata;	// Pointer to GL-formatted data
#if TIKI_PLAT != TIKI_NDS
	GLuint	m_gltxr;	// GL texture handle
#else
	int	m_gltxr;	// GL texture handle
#endif
};

};
};

#endif	// __TIKI_TEXTURE_H
