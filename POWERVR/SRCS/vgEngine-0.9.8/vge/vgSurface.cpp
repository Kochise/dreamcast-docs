//
// C++ Implementation: vgSurface
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
#include "agg_renderer_scanline.h"
#include "agg_renderer_primitives.h"

#include "agg_rasterizer_outline_aa.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_u.h"
#include "agg_scanline_p.h"
#include "agg_scanline_bin.h"
#include "agg_rasterizer_scanline_aa.h"

#include "agg_pixfmt_rgb.h"
#include "agg_pixfmt_rgb_packed.h"
#include "agg_pixfmt_rgba.h"
#include "agg_pixfmt_gray.h"

#include "agg_conv_curve.h"
#include "agg_conv_contour.h"
#include "agg_font_freetype.h"

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgInternal.h"
#include "vgColor.h"
#include "vgImage.h"
#include "vgSurface.h"
#include "vgFontProperty.h"

#if VGE_CONFIG_COMP_OP  
// ROP, only 32bit fmt support custom blending
//typedef agg::pixfmt_rgb565 PIXFMT_RGB565;
//typedef agg::pixfmt_rgb555 PIXFMT_RGB555;
typedef agg::pixfmt_custom_blend_rgba< agg::comp_op_adaptor_rgba< agg::rgba8, agg::order_rgba >, agg::rendering_buffer> PIXFMT_RGBA32;
typedef agg::pixfmt_custom_blend_rgba< agg::comp_op_adaptor_rgba< agg::rgba8, agg::order_argb >, agg::rendering_buffer> PIXFMT_ARGB32;
typedef agg::pixfmt_custom_blend_rgba< agg::comp_op_adaptor_rgba< agg::rgba8, agg::order_abgr >, agg::rendering_buffer> PIXFMT_ABGR32;
typedef agg::pixfmt_custom_blend_rgba< agg::comp_op_adaptor_rgba< agg::rgba8, agg::order_bgra >, agg::rendering_buffer> PIXFMT_BGRA32;
#else 
// bez ROP, ALPHA blending or COPY
//typedef agg::pixfmt_rgb565 PIXFMT_RGB565;
//typedef agg::pixfmt_rgb555 PIXFMT_RGB555;
typedef agg::pixfmt_rgba32 PIXFMT_RGBA32;
typedef agg::pixfmt_argb32 PIXFMT_ARGB32;
typedef agg::pixfmt_abgr32 PIXFMT_ABGR32;
typedef agg::pixfmt_bgra32 PIXFMT_BGRA32;
#endif

template <typename PIXFMT, VGPixelFormat type>
	class FGSurface : public vgSurfaceInterface
{
	public:
		typedef PIXFMT self_type;
		typedef agg::renderer_base<PIXFMT> my_renderer_base;
		typedef agg::renderer_scanline_aa_solid<my_renderer_base> renderer_aa;
		typedef agg::renderer_scanline_bin_solid<my_renderer_base> renderer_bin;
		typedef agg::renderer_primitives<my_renderer_base> renderer_primitives;
		typedef typename my_renderer_base::color_type color_type;

		FGSurface(int w=0, int h=0, void* ptr=0)
		: 	buffer(w, h, type, ptr),
			pix(*buffer.GetRender()),
			rb(pix),
			ren_aa(rb),
			ren_bin(rb),
			ren_primitives(rb)
		{
			color_type c;
			c.clear();
			rb.clear( c );
		}

#if VGE_CONFIG_COMP_OP
		virtual void SetROP(VGBlendMode rop)
		{
			switch( rop )
			{
				case VG_BLEND_SRC:
					pix.comp_op( agg::comp_op_src );
					return;
				case VG_BLEND_SRC_OVER:
					pix.comp_op( agg::comp_op_src_over );
					return;
				case VG_BLEND_DST_OVER:
					pix.comp_op( agg::comp_op_dst_over );
					return;
				case VG_BLEND_SRC_IN:
					pix.comp_op( agg::comp_op_src_in );
					return;
				case VG_BLEND_DST_IN:
					pix.comp_op( agg::comp_op_dst_in );
					return;
				case VG_BLEND_MULTIPLY:
					pix.comp_op( agg::comp_op_multiply );
					return;
				case VG_BLEND_SCREEN:
					pix.comp_op( agg::comp_op_screen );
					return;
				case VG_BLEND_DARKEN:
					pix.comp_op( agg::comp_op_darken );
					return;
				case VG_BLEND_LIGHTEN:
					pix.comp_op( agg::comp_op_lighten );
					return;
				case VG_BLEND_XOR:
					pix.comp_op( agg::comp_op_xor );
					return;
			}
		}
#endif
				
		inline color_type convert_color(const vgColor& color)
		{
			return color_type(agg::rgba8(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()));
		}
		
		virtual unsigned GetWidth() const { return buffer.GetWidth(); }
		virtual unsigned GetHeight() const { return buffer.GetHeight(); }

		virtual vgImage* GetBuffer() { return &buffer; }
		virtual void Render(const vgColor& color)
		{
			if (antialiasing == true)
			{
				ren_aa.color( convert_color(color) );
				render_scanlines(rasterizer, scanlines, ren_aa);
			}
			else
			{
				ren_bin.color( convert_color(color) );
				render_scanlines(rasterizer, scanlines, ren_bin);
			}
        }

		virtual void Text(double x, double y, const char* txt, vgFontProperty* font, const vgColor& textColor )
		{
			draw_text(rasterizer, scanlines, ren_aa, ren_bin, x, y, txt, font, textColor);
		}

		virtual void clear(const vgColor& color)
		{
			rb.clear( convert_color(color) );
		}
		
		virtual void line(int x, int y, int x2, int y2, bool drawLastPoint, const vgColor& color)
		{
			ren_primitives.line_color(convert_color(color));
			ren_primitives.line(x<<8, y<<8, x2<<8, y2<<8, drawLastPoint);
		}
        virtual void rectangle(int x1, int y1, int x2, int y2, const vgColor& color)
		{
			ren_primitives.line_color(convert_color(color));
			ren_primitives.rectangle(x1, y1, x2, y2);
		}
        virtual void solid_rectangle(int x1, int y1, int x2, int y2, const vgColor& fillColor)
		{
			ren_primitives.fill_color(convert_color(fillColor));
			ren_primitives.solid_rectangle(x1, y1, x2, y2);
		}
        virtual void outlined_rectangle(int x1, int y1, int x2, int y2, const vgColor& color, const vgColor& fillColor)
		{
			ren_primitives.line_color(convert_color(color));
			ren_primitives.fill_color(convert_color(fillColor));
			ren_primitives.outlined_rectangle(x1, y1, x2, y2);
		}
        virtual void ellipse(int x, int y, int rx, int ry, const vgColor& color)
		{
			ren_primitives.line_color(convert_color(color));
			ren_primitives.ellipse(x, y, rx, ry);
		}
        virtual void solid_ellipse(int x, int y, int rx, int ry, const vgColor& fillColor)
		{
			ren_primitives.fill_color(convert_color(fillColor));
			ren_primitives.solid_ellipse(x, y, rx, ry);
		}
        virtual void outlined_ellipse(int x, int y, int rx, int ry, const vgColor& color, const vgColor& fillColor)
		{
			ren_primitives.line_color(convert_color(color));
			ren_primitives.fill_color(convert_color(fillColor));
			ren_primitives.outlined_ellipse(x, y, rx, ry);
		}
		
	private:
		vgImage		 			buffer;
		PIXFMT 					pix;
		my_renderer_base 		rb;
		renderer_aa 			ren_aa;
		renderer_bin 			ren_bin;
		renderer_primitives		ren_primitives;
		agg::scanline_p8 		scanlines;
		
		template<class Rasterizer, class Scanline, class RenSolid, class RenBin>
		unsigned draw_text(Rasterizer& ras, Scanline& sl,
							RenSolid& ren_solid, RenBin& ren_bin,
							double x, double y,
							const char* text,
							vgFontProperty* font,
							const vgColor& textColor )
		{
#if VGE_CONFIG_FREETYPE
			unsigned num_glyphs = 0;

			if (font->IsInitialised() == true)
			{
//				FontEngine& m_feng = font->GetFontEngine();
				const char* p = text;
				//double y0 = y;

				while(*p)
				{
					FontCacheManager& m_fman = font->GetFontCacheManager();
					const agg::glyph_cache* glyph = m_fman.glyph(*p);

					if(glyph)
					{
						m_fman.init_embedded_adaptors(glyph, x, y);

						// urob nativnu farbu
						agg::rgba8 foreground( textColor.GetRed(), textColor.GetGreen(), textColor.GetBlue(), textColor.GetAlpha() );

						switch(glyph->data_type)
						{
							default: break;
							case agg::glyph_data_mono:
								ren_solid.color( foreground );
								agg::render_scanlines(m_fman.mono_adaptor(), m_fman.mono_scanline(), ren_bin);
								break;

							case agg::glyph_data_gray8:
								ren_solid.color( foreground );
								agg::render_scanlines(m_fman.gray8_adaptor(), m_fman.gray8_scanline(), ren_solid);
								break;
						}

						// increment pen position
						x += glyph->advance_x;
						y += glyph->advance_y;
						++num_glyphs;
					}
					++p;
				}
			}
			return num_glyphs;
#else
			return 0;
#endif
		}
};

//typedef FGSurface<PIXFMT_RGB565, VG_Pixel_Bgr16>  FGSurface16;
//typedef FGSurface<PIXFMT_RGB555, VG_Pixel_Bgr15>  FGSurface15;
typedef FGSurface<PIXFMT_RGBA32, VG_Pixel_Rgba32> FGSurface32rgba;
typedef FGSurface<PIXFMT_ARGB32, VG_Pixel_Argb32> FGSurface32argb;
typedef FGSurface<PIXFMT_ABGR32, VG_Pixel_Abgr32> FGSurface32abgr;
typedef FGSurface<PIXFMT_BGRA32, VG_Pixel_Bgra32> FGSurface32bgra;

vgSurfaceInterface* vgSurfaceInterface::Factory( unsigned w, unsigned h, VGPixelFormat format, void* memory )
{
	switch( format )
	{
		default:
/*		case VG_Pixel_Bgr15:
			return new FGSurface15( w, h, memory );
		case VG_Pixel_Bgr16:
			return new FGSurface16( w, h, memory );
*/		case VG_Pixel_Bgra32:
			return new FGSurface32bgra( w, h, memory );
		case VG_Pixel_Rgba32:
			return new FGSurface32rgba( w, h, memory );
		case VG_Pixel_Argb32:
			return new FGSurface32argb( w, h, memory );
		case VG_Pixel_Abgr32:
			return new FGSurface32abgr( w, h, memory );
	}
	return 0;
}

