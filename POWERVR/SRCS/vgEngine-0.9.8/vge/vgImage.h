//
// C++ Interface: vgImage
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "agg_basics.h"
#include "agg_rendering_buffer.h"

class vgImage
{
		void*	allocated;
		unsigned char *	image;
		bool	do_free;
		int		width;
		int 	height;
		VGPixelFormat	pixfmt;
		agg::rendering_buffer *render;

		int GetPixelSize()
		{
			switch(pixfmt)
			{
/*				case VG_Pixel_Bgr15:
				case VG_Pixel_Bgr16:
					return 2;
*/				case VG_Pixel_Rgba32:
				case VG_Pixel_Argb32:
				case VG_Pixel_Abgr32:
				case VG_Pixel_Bgra32:
					return 4;
			}
			return 4;
		}
		void Allocate(void *ptr);
	public:
		vgImage(int w, int h, VGPixelFormat pix, void* ptr=0);
		vgImage(const vgImage& old);
		vgImage* Clone() { return new vgImage (*this); }
		virtual ~vgImage();

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }
		VGPixelFormat GetPixelFormat() const { return pixfmt; }
		agg::rendering_buffer* GetRender() const { return render; }
		unsigned char* GetImage() const { return image; }
};

