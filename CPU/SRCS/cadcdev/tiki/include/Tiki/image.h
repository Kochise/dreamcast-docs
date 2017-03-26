/*
   Tiki

   image.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_IMAGE_H
#define __TIKI_IMAGE_H

#include "Tiki/tikitypes.h"
#include "Tiki/refcnt.h"

namespace Tiki {

class Image : public RefCnt {
public:
	Image() {
		data = NULL;
		w = h = 0;
		fmt = None;
		byteCount = 0;
	}
	virtual ~Image() {
		delete[] data;
	}
	
	// This list must be kept in sync with Texture.
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

	// Convert this image to another format.
	void convertTo(Fmt dst);

	uint8	* data;
	uint32	w, h;
	Fmt	fmt;
	uint32	byteCount;
};

}

#endif	// __TIKI_IMAGE_H

