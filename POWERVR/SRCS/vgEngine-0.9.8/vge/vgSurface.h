//
// C++ Interface: vgSurface
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "agg_path_storage.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_conv_clip_polyline.h"
#include "agg_conv_clip_polygon.h"


class vgImage;

class vgFontProperty;

class vgSurfaceInterface
{
	protected:
		agg::rasterizer_scanline_aa<> rasterizer;
		bool					antialiasing;
	public:
		vgSurfaceInterface()
		{
			SetAA( true );
			rasterizer.auto_close( false );
		}
		virtual ~vgSurfaceInterface() {}

		static vgSurfaceInterface* Factory(  unsigned w, unsigned h, VGPixelFormat format, void* memory = 0 );

		virtual vgImage* GetBuffer() {}
		virtual void Render(const vgColor& color) {}
		virtual void Text(double x, double y, const char* txt, vgFontProperty* font, const vgColor& textColor ) {}

		void SetAA(bool aa) { antialiasing = aa; }
		agg::rasterizer_scanline_aa<>& GetRasterizer() { return rasterizer; } 
		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;
		virtual void clear(const vgColor& color) = 0;
#if VGE_CONFIG_COMP_OP		
		virtual void SetROP(VGBlendMode rop) = 0;
#endif				
		virtual void line(int x, int y, int x2, int y2, bool drawLastPoint, const vgColor& color) = 0;
        virtual void rectangle(int x1, int y1, int x2, int y2, const vgColor& color) = 0;
        virtual void solid_rectangle(int x1, int y1, int x2, int y2, const vgColor& fillColor) = 0;
        virtual void outlined_rectangle(int x1, int y1, int x2, int y2, const vgColor& color, const vgColor& fillColor) = 0;
        virtual void ellipse(int x, int y, int rx, int ry, const vgColor& color) = 0;
        virtual void solid_ellipse(int x, int y, int rx, int ry, const vgColor& fillColor) = 0;
        virtual void outlined_ellipse(int x, int y, int rx, int ry, const vgColor& color, const vgColor& fillColor) = 0;
};

