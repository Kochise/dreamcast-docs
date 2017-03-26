//
// C++ Interface: vgFontProperty
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#if VGE_CONFIG_FREETYPE

#include "agg_conv_contour.h"
#include "agg_font_freetype.h"


enum Text_Render_Mode {
	Text_Render_Mode_Mono,
	Text_Render_Mode_Gray,
	Text_Render_Mode_Outline,
	Text_Render_Mode_Agg_Mono,
	Text_Render_Mode_Agg_Gray,
};
/*
enum Font_Face {
	Font_Face_Arial,	
	Font_Face_Times,	
	Font_Face_Verdana,	
	Font_Face_Courier,	
	
	Font_Face_Last
};
*/
typedef agg::font_engine_freetype_int32 FontEngine;
typedef agg::font_cache_manager<FontEngine> FontCacheManager;

typedef agg::conv_contour<agg::conv_curve<FontCacheManager::path_adaptor_type> > contour_type;

class vgFontProperty
{
		FontEngine m_feng;
		FontCacheManager m_fman;
		// Pipeline to process the vectors glyph paths (curves + contour)
		agg::conv_curve<FontCacheManager::path_adaptor_type> m_curves;
		contour_type 			m_contour;

		Text_Render_Mode 		mode;
		double					m_height;
		double					m_width;
		bool					m_hinting;
		bool					m_kerning;
        bool					initialised;

	public:
		vgFontProperty(int size = 12, Text_Render_Mode mode = Text_Render_Mode_Agg_Gray);
		vgFontProperty(const char* fontFilename, int size, Text_Render_Mode mode = Text_Render_Mode_Agg_Gray);
		~vgFontProperty();

		void SetFontRendering( Text_Render_Mode _mode ) { mode = _mode; }
		void SetSize(int sz) { m_height = m_width = sz; }
		void SetRotation(double rotate);
		void SetHinting(bool hint) { m_hinting = hint; }
		void SetKerning(bool kern) { m_kerning = kern; }

		bool GetKerning() { return m_kerning; }

        bool BuildFontFace(const char* fontFilename);
        bool IsInitialised() { return initialised; }
        FontEngine& GetFontEngine();
        FontCacheManager& GetFontCacheManager();
        contour_type& GetContour() { return m_contour; }
};

#else
typedef VGHandle VGFontProperty;
#endif
