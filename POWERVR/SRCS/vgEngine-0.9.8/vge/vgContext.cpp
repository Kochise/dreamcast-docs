//
// C++ Implementation: vgContext
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "agg_math_stroke.h"
#include "agg_conv_stroke.h"
#include "agg_conv_dash.h"
#include "agg_conv_curve.h"
#include "agg_path_length.h"

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgInternal.h"
#include "vgColor.h"
#include "vgArray.h"
#include "vgImage.h"
#include "vgMatrix.h"
#include "vgPath.h"
#include "vgSurface.h"
#include "vgContext.h"
#include "vgFontProperty.h"

template <class vertices>
void DumpVertices(vertices& instance)
{
	double x,y;
	instance.rewind(0);
	printf("Start ... %d\n", instance.total_vertices());
	for(int i=0; i<instance.total_vertices(); i++)
	{
		instance.vertex(i, &x, &y);
		printf("%f %f\n", x,y);
	}
	printf("End\n\n");
}

vgContext::vgContext(unsigned width, unsigned height, VGPixelFormat format, void* memory)
:	error(VG_NO_ERROR)
{
	surface = vgSurfaceInterface::Factory( width, height, format, memory );	
	SetRenderingQuality( VG_RENDERING_QUALITY_BETTER );
	clipMinX = 0;
	clipMinY = 0,
	clipWidth = width;
	clipHeight = height;
	saver = new StateSaver;
}

void vgContext::SetRenderingQuality( VGRenderingQuality q )
{
	renderingQuality = q;
	if (q == VG_RENDERING_QUALITY_NONANTIALIASED )
		surface->SetAA( false );
	else
		surface->SetAA( true );
}

vgContext::~vgContext()
{
	delete surface;
	surface = 0;
	delete saver;
	saver = 0;
}

void vgContext::SetError(VGErrorCode e) 
{ 
	if(e == VG_NO_ERROR) 
		error = e; 
}	

// ----------------------------------------------------------------------

bool vgContext::TestPathHit(VGPath path, VGdouble sx, VGdouble sy, bool transform)
{
	agg::rasterizer_scanline_aa<>& rasterizer = surface->GetRasterizer();
	vgPath* pathPtr = (vgPath *)path;
	agg::path_storage& originalPath = pathPtr->path;

    if (transform == true)
		pathUserToSurface.transform( &sx, &sy );

	agg::conv_curve<agg::path_storage> stage1( originalPath );
	agg::conv_transform< agg::conv_curve<agg::path_storage> > convertedPath( stage1, pathUserToSurface );
	rasterizer.add_path( convertedPath );

	rasterizer.filling_rule( fillRule==VG_EVEN_ODD ? agg::fill_even_odd : agg::fill_non_zero );

    return rasterizer.hit_test( (int)sx, (int)sy);
}

void vgContext::DrawPath(VGPath path, VGbitfield paintModes)
{
	agg::rasterizer_scanline_aa<>& rasterizer = surface->GetRasterizer();
	int clip_width = surface->GetWidth();
	int clip_height = surface->GetHeight();
	vgPath* pathPtr = (vgPath *)path;
	agg::path_storage& originalPath = pathPtr->path;

	/*
		PIPELINE:
			1. Transform vertices with affine *
			2. Transform curves to lines
			3. FILL:
				3a. Clip to BOX *
				4a. Render
			   STROKE
				3b. Clip to BOX *
				4b. Dash *
				5b. Stroke *
				6b. Render
	*/		
	
	if (paintModes & VG_FILL_PATH)
	{
		FillPipeline(originalPath);
	}

	if (paintModes & VG_STROKE_PATH)
	{
		StrokePipeline(originalPath);
	}
}

/*
	1. Transform vertices with affine *
	2. Transform curves to lines
	3. Clip to BOX *
	4. Render
*/
#if 1
void vgContext::StrokePipeline(agg::path_storage& originalPath)
{
	agg::rasterizer_scanline_aa<>& rasterizer = surface->GetRasterizer();

	agg::conv_curve<agg::path_storage> stage1( originalPath );
	agg::conv_transform< agg::conv_curve<agg::path_storage> > convertedPath( stage1, pathUserToSurface );
	agg::conv_clip_polyline< agg::conv_transform< agg::conv_curve<agg::path_storage> > > clipper(convertedPath);

	clipper.clip_box(clipMinX, clipMinY, clipWidth, clipHeight);

#if VGE_CONFIG_DASHED_LINE
	agg::conv_dash< agg::conv_clip_polyline< agg::conv_transform< agg::conv_curve<agg::path_storage> > > > dasher(clipper);
	agg::conv_stroke< agg::conv_dash< agg::conv_clip_polyline< agg::conv_transform< agg::conv_curve<agg::path_storage> > > > > stroker( dasher );

	if (strokeDashSize)
	{
		for( unsigned i = 0; i < strokeDashSize; i += 2 )
		{
			dasher.add_dash( strokeDashPattern[i], strokeDashPattern[i+1] );
		}
		dasher.dash_start( strokeDashPhase );
	}
	else
	{
		dasher.add_dash( 2000000000, 0 );
		dasher.dash_start( 0 );
	}
#else
	agg::conv_stroke< agg::conv_clip_polyline< agg::conv_transform< agg::conv_curve<agg::path_storage> > > > stroker( clipper );
#endif
	
	enum agg::line_cap_e cap = agg::butt_cap;
	switch( strokeCapStyle )
	{
		case VG_CAP_BUTT:
			cap = agg::butt_cap;
			break;
		case VG_CAP_ROUND:
			cap = agg::round_cap;
			break;
		case VG_CAP_SQUARE:
			cap = agg::square_cap;
			break;
	}

	agg::line_join_e join = agg::miter_join;
	switch( strokeJoinStyle )
	{
		case VG_JOIN_MITER:
			join = agg::miter_join;
			break;
		case VG_JOIN_ROUND:
			join = agg::round_join;
			break;
		case VG_JOIN_BEVEL:
			join = agg::bevel_join;
			break;
	}
	
	stroker.width( strokeLineWidth );
	stroker.line_cap( cap );
	stroker.line_join( join );
	stroker.miter_limit( strokeMiterLimit );
		
	rasterizer.add_path( stroker );
#if VGE_CONFIG_COMP_OP
	surface->SetROP( blendMode );
#endif
	surface->Render(lineColor);
}
#else
void vgContext::StrokePipeline(agg::path_storage& originalPath)
{
	agg::rasterizer_scanline_aa<>& rasterizer = surface->GetRasterizer();

	agg::conv_transform< agg::path_storage > convertedPath( originalPath, pathUserToSurface );
	agg::conv_clip_polyline< agg::conv_transform< agg::path_storage> > clipper(convertedPath);

	clipper.clip_box(clipMinX, clipMinY, clipWidth, clipHeight);

	agg::conv_stroke< agg::conv_clip_polyline< agg::conv_transform< agg::path_storage> > > stroker( clipper );
	stroker.width( strokeLineWidth );
		
	rasterizer.add_path( stroker );
	surface->Render(lineColor);
}
#endif

void vgContext::FillPipeline(agg::path_storage& originalPath)
{
	agg::rasterizer_scanline_aa<>& rasterizer = surface->GetRasterizer();
	int clip_width = surface->GetWidth();
	int clip_height = surface->GetHeight();

	agg::conv_curve<agg::path_storage> stage1( originalPath );
	agg::conv_transform< agg::conv_curve<agg::path_storage> > convertedPath( stage1, pathUserToSurface );
	agg::conv_clip_polygon< agg::conv_transform< agg::conv_curve<agg::path_storage> > > clipper(convertedPath);

	clipper.clip_box(clipMinX, clipMinY, clipWidth, clipHeight);

	// premapuj VG na AGG
	rasterizer.filling_rule( fillRule==VG_EVEN_ODD ? agg::fill_even_odd : agg::fill_non_zero );
	rasterizer.add_path( clipper );

#if VGE_CONFIG_COMP_OP
	surface->SetROP( blendMode );
#endif	
	surface->Render(fillColor);
}

// *************************************************************************\

