//
// C++ Implementation: vgFontProperty
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <assert.h>

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgInternal.h"

#include "vgFontProperty.h"

#if VGE_CONFIG_FREETYPE

vgFontProperty::vgFontProperty(int size, Text_Render_Mode _mode)
: m_feng(), m_fman(m_feng), m_curves(m_fman.path_adaptor()), m_contour(m_curves)
{
	m_curves.approximation_scale(2.0);
	m_contour.auto_detect_orientation(false);

	SetFontRendering( _mode );
	SetSize( size );
	SetHinting( true );
	SetKerning( true );

    initialised = false;
}

vgFontProperty::vgFontProperty(const char* fontFilename, int size, Text_Render_Mode _mode)
: m_feng(), m_fman(m_feng), m_curves(m_fman.path_adaptor()), m_contour(m_curves)
{
	m_curves.approximation_scale(2.0);
	m_contour.auto_detect_orientation(false);

	SetFontRendering( _mode );
	SetSize( size );
	SetHinting( true );
	SetKerning( true );

    initialised = false;

    BuildFontFace(fontFilename);
}

bool vgFontProperty::BuildFontFace(const char* fontFilename)
{
	agg::glyph_rendering gren = agg::glyph_ren_native_mono;

	switch( mode )
	{
		case Text_Render_Mode_Mono:
			gren = agg::glyph_ren_native_mono;
			break;
		case Text_Render_Mode_Gray:
			gren = agg::glyph_ren_native_gray8;
			break;
		case Text_Render_Mode_Outline:
			gren = agg::glyph_ren_outline;
			break;
		case Text_Render_Mode_Agg_Mono:
			gren = agg::glyph_ren_agg_mono;
			break;
		case Text_Render_Mode_Agg_Gray:
			gren = agg::glyph_ren_agg_gray8;
			break;
	}

    initialised = m_feng.load_font( fontFilename, 0, gren);

	if (initialised == true)
	{
		m_feng.hinting(m_hinting);
		m_feng.height(m_height);
		m_feng.width(m_width);
#if VGE_CONFIG_Y_GROWS_TO_DOWN		
		m_feng.flip_y( true );
#else		
		m_feng.flip_y( false );
#endif		
        return initialised;
	}
    return initialised;
}

void vgFontProperty::SetRotation(double rotate) 
{  
	if (rotate)
	{
		agg::trans_affine mtx;
		mtx *= agg::trans_affine_rotation( agg::deg2rad(rotate) );
		m_feng.transform(mtx);
	}	
}

FontEngine& vgFontProperty::GetFontEngine()
{
    return m_feng;
}

FontCacheManager& vgFontProperty::GetFontCacheManager()
{
    return m_fman;
}

vgFontProperty::~vgFontProperty()
{
}
#endif
