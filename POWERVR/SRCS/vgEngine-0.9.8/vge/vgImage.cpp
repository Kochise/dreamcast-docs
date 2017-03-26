//
// C++ Implementation: vgImage
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgInternal.h"
#include "vgImage.h"

vgImage::vgImage(int w, int h, VGPixelFormat pix, void* ptr)
{
	width = w;
	height = h;
	pixfmt = pix;

	Allocate(ptr);
}

vgImage::vgImage(const vgImage& old)
{
	width = old.width;
	height = old.height;
	pixfmt = old.pixfmt;
	Allocate(0);
}

void vgImage::Allocate(void *ptr)
{
	int size_of = GetPixelSize();

	if (ptr == 0)
	{
		allocated = calloc(width * height + 16, size_of);
		image = (unsigned char *) (((unsigned long)allocated|15)+1);
		do_free = true;
	}
	else
	{
		allocated = ptr;
		image = (unsigned char* ) allocated;
		do_free = false;
	}

	assert(allocated);
	
#if VGE_CONFIG_Y_GROWS_TO_DOWN
	render = new agg::rendering_buffer( image, width, height, width*size_of);
#else
	render = new agg::rendering_buffer( image, width, height, -(width*size_of));
#endif
}

vgImage::~vgImage()
{
	if (do_free)
		free(allocated);
	allocated = 0;
	delete render;
	render = 0;
}

