/*
   Tiki

   image.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/image.h"
#include <assert.h>

void Image::convertTo(Fmt dst) {
	// Right now we only handle RGBA8888 to ARGB8888, RGB888, RGB565, ARGB1555, and ARGB4444.
	if (this->fmt != RGBA8888) {
		Debug::printf("Image::convertTo -- source image is not RGBA8888\n");
		return;
	}

	// RGBA8888->ARGB8888 is an easy special case.
	if (dst == ARGB8888) {
		for (uint32 y=0; y<h; y++) {
			for (uint32 x=0; x<w; x++) {
				uint8 * pixel = data + y*w*4+x;
				uint8 alpha = pixel[3];
				pixel[3] = pixel[2];
				pixel[2] = pixel[1];
				pixel[1] = pixel[0];
				pixel[0] = alpha;
			}
		}
		return;
	}
	
	// How many bytes per pixel is the new format?
	int bpp;
	switch(dst) {
	case RGB888:
		bpp = 3; break;
	case RGB565:
	case ARGB1555:
	case ARGB4444:
		bpp = 2; break;
	default:
		assert( false );
		return;
	}
	
	// New buffer we'll dump into.
	uint8 * newbuf = new uint8[w*h*bpp];
	
#define LOAD565(r, g, b) (((r>>3)<<11) | ((g>>2)<<5) | ((b>>3)))
#define LOAD1555(r, g, b, a) (((a>>7)<<15)|((r>>3)<<10)|((g>>3)<<5)|((b>>3)))
#define LOAD4444(r, g, b, a) (((a>>4)<<12)|((r>>4)<<8)|((g>>4)<<4)|((b>>4)))

	for (uint32 y=0; y<h; y++) {
		uint8 * srcrow = data + w*y*4;
		uint8 * dstrow = newbuf + w*y*bpp;
		for (uint32 x=0; x<w; x++) {
			switch(dst) {
			case RGB888:
				dstrow[x*3+0] = srcrow[x*4+0];
				dstrow[x*3+1] = srcrow[x*4+1];
				dstrow[x*3+2] = srcrow[x*4+2];
				break;
			case RGB565:
				((uint16*)dstrow)[x] = LOAD565(srcrow[x*4+0], srcrow[x*4+1], srcrow[x*4+2]);
				break;
			case ARGB1555:
				((uint16*)dstrow)[x] = LOAD1555(srcrow[x*4+0], srcrow[x*4+1], srcrow[x*4+2], srcrow[x*4+3]);
				break;
			case ARGB4444:
				((uint16*)dstrow)[x] = LOAD4444(srcrow[x*4+0], srcrow[x*4+1], srcrow[x*4+2], srcrow[x*4+3]);
				break;
			default: break;
			}
		}
	}
#undef LOAD565
#undef LOAD1555
#undef LOAD4444

	delete[] data;
	data = newbuf;
	byteCount = w*h*bpp;
	fmt = dst;
}


