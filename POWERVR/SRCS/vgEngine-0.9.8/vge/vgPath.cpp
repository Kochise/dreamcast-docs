//
// C++ Implementation: vgPath
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
#include "vgColor.h"
#include "vgArray.h"
#include "vgMatrix.h"
#include "vgPath.h"
#include "vgImage.h"
#include "vgContext.h"
#include "vgSurface.h"

#include "agg_arc.h"
#include "agg_rounded_rect.h"

vgPath::vgPath() 
{
}

vgPath::~vgPath()
{
}

unsigned vgPath::append(vgPath* srcPath)	//throws bad_alloc
{
	assert(srcPath);
	path.join_path(srcPath->path, path.start_new_path());
}

unsigned vgPath::transform(vgPath* srcPath, const VGMatrix& matrix)	//throws bad_alloc
{
	assert(srcPath);
	unsigned pid = append( srcPath );
	path.transform( matrix, pid );
}

// -------------------------------------------------------------------------------

void vgPath::line(VGdouble x0, VGdouble y0, VGdouble x1, VGdouble y1)
{
    path.move_to(x0, y0);
    path.line_to(x1, y1);
}

void vgPath::arc(VGdouble x,  VGdouble y, VGdouble rx, VGdouble ry, VGdouble start, VGdouble end, VGUArcType arcType, bool ccw)
{
	agg::arc arc( x, y, rx, ry, start * (M_PI / 180.0), end * (M_PI / 180.0), ccw );
	arc.approximation_scale(1);
	
	path.concat_path(arc);
	
	if (arcType == VGU_ARC_CHORD)
	{
		path.close_polygon();
	}
	else if (arcType == VGU_ARC_PIE)
	{
		path.line_to(x,y);
		path.close_polygon();
	}
}

void vgPath::ellipse(VGdouble x,  VGdouble y, VGdouble rx, VGdouble ry)
{
	agg::bezier_arc arc(x, y, rx, ry, 0, 2*M_PI );
	path.concat_path(arc);
	path.close_polygon();
}

void vgPath::rectangle(VGdouble x,  VGdouble y, VGdouble w, VGdouble h)
{
	path.move_to(x,y);
	path.line_to(x+w, y);
	path.line_to(x+w, y+h);
	path.line_to(x, y+h);
	path.close_polygon();
}

void vgPath::roundRectangle(VGdouble x,  VGdouble y, VGdouble w, VGdouble h, VGdouble r)
{
    agg::rounded_rect rc(x, y, x+w, y+h, r);
    rc.normalize_radius();
//    rc.approximation_scale(worldToScreen(1.0) * g_approxScale);
    path.concat_path(rc);
}

#define DO_VERTEX_LOOP(type) \
	{ \
		double x = ((type *)points)[0]; \
		double y = ((type *)points)[1]; \
		move_to(x,y); \
	} \
	for(int i = 1; i < count; i++) \
	{ \
		double x = ((type *)points)[i*2 ]; \
		double y = ((type *)points)[i*2+1]; \
		line_to(x,y); \
	}
	
void vgPath::polygon(VGPathDatatype dataType, const void* points, VGint count, VGboolean doClose)
{
	switch( dataType )
	{
		case VG_PATH_DATATYPE_S_8:
			DO_VERTEX_LOOP(char);
			break;
		case VG_PATH_DATATYPE_S_16:
			DO_VERTEX_LOOP(short);
			break;
		case VG_PATH_DATATYPE_S_32:
			DO_VERTEX_LOOP(int);
			break;
		case VG_PATH_DATATYPE_F:
			DO_VERTEX_LOOP(float);
			break;
		case VG_PATH_DATATYPE_D:
			DO_VERTEX_LOOP(double);
			break;
		default:
			assert( !"vgPath::polygon(): unknown data type of vertexes!" );
	};
		
	if (doClose == true)
		close_polygon();
}

