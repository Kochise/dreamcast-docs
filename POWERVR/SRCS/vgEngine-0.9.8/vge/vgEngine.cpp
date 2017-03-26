//
// C++ Implementation: vg_engine
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

/*
	TODO:
	* matrix operation
	* VGMatrix, push/pop
	* rect, roundrect
	* polygon
	* path
	* text
	* cap, join, miter
	* fill rule
	* blend mode
	* dash line
	- pixel layout
	* clear
	* clip rect
	- parametrizovat format s poskytovatelov bufera (bmp, pixmap, ..)
*/

#include "agg_path_length.h"
#include "agg_bounding_rect.h"
#include "agg_conv_transform.h"

#include "vgEngine.h"
#include "vgConfig.h"
#include "vgInternal.h"
#include "vgColor.h"
#include "vgArray.h"
#include "vgImage.h"
#include "vgMatrix.h"
#include "vgPath.h"
#include "vgContext.h"
#include "vgSurface.h"
#include "vgFontProperty.h"

/**
 *  @example example1.cpp
 *  @example example2.cpp
 *  @example example3.cpp
 *  @example example4.cpp
 */

/**
 * @param context the given graphic context
 * Returns error code for context and reset error state to VG_NO_ERROR.
 */
VGErrorCode vgGetError(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	VGErrorCode error = contextPtr->error;
	contextPtr->error = VG_NO_ERROR;
	
	return error;
}

/**
 * Set color for vgClear() operation.
 * @param context the given graphic context
 * @param red the value of the red component in range from 0 to 255.
 * @param green the value of the green component in range from 0 to 255.
 * @param blue the value of the blue component in range from 0 to 255.
 * @param alpha the value of the alpha component (i.e. transparency) in range from 0 (transparent) to 255 (opaque).
 */
void vgClearColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->clearColor.set(red, green, blue, alpha);
}

/**
 * @return VGImage object used by context.
 */
VGImage vgContextToImage(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	return contextPtr->surface->GetBuffer();
}

/**
 * Set the color for all FILL operation.
 * @param context the given graphic context
 * @param red the value of the red component in range from 0 to 255.
 * @param green the value of the green component in range from 0 to 255.
 * @param blue the value of the blue component in range from 0 to 255.
 * @param alpha the value of the alpha component (i.e. transparency) in range from 0 (transparent) to 255 (opaque).
 */
void vgFillColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->fillColor.set(red, green, blue, alpha);
}

/**
 * Set the color for all STROKE (LINE) operation.
 * @param context the given graphic context
 * @param red the value of the red component in range from 0 to 255.
 * @param green the value of the green component in range from 0 to 255.
 * @param blue the value of the blue component in range from 0 to 255.
 * @param alpha the value of the alpha component (i.e. transparency) in range from 0 (transparent) to 255 (opaque).
 */
void vgLineColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->lineColor.set(red, green, blue, alpha);
}

/**
 * Set the color for all text operation.
 * @param context the given graphic context
 * @param red the value of the red component in range from 0 to 255.
 * @param green the value of the green component in range from 0 to 255.
 * @param blue the value of the blue component in range from 0 to 255.
 * @param alpha the value of the alpha component (i.e. transparency) in range from 0 (transparent) to 255 (opaque).
 */
void vgTextColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->textColor.set(red, green, blue, alpha);
}

/**
 * @param context the given graphic context
 * @param width set the width of stroke in device pixels, the range is from 0.01 to 1024.0
 */
void vgLineWidth(VGContext context, VGdouble width)
{
	DECLARE_CONTEXT_PTR;
	
	if (width<0.01 || width>1024.0)
	{
		contextPtr->SetError(VG_OUT_OF_RANGE);
		return;
	}
	contextPtr->strokeLineWidth = width;
}

void vgSaveContext(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->saver->Save( contextPtr );
}

void vgRestoreContext(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->saver->Restore( contextPtr );
}

// --------------------------------------------------------------------------------------

/**
 *  Creates an empty path object.
 */
VGPath vgCreatePath(void)
{
	return (VGPath) new vgPath;
}

//! Clears the current path. After this call there will be no path and no current point.
//!  @param path a path previously returned by either vgCreatePath().
void vgClearPath(VGPath path)
{
	((vgPath *) path)->clear();
}

/**
  Immediately releases all memory associated with path. After a call to vgDestroyPath() the path pointer 
  is no longer valid and should not be used further. 
  @NOTE: vgDestroyPath function should only be called with a pointer to a VGPath returned by a cairo function.
  @param path a path previously returned by either vgCreatePath().
 */ 
void vgDestroyPath(VGPath path)
{
	delete (vgPath *) path;
}

/**
  Append the path onto the current path. The path may be either the return value from one of vgCreatePath(). 
  See VGPath for details on how the path data object should be initialized.
  @param dstPath :   path to append
  @param srcPath :   path to be appended
 */
void vgAppendPath(VGPath dstPath, VGPath srcPath)
{
	vgPath* dst = ((vgPath *) dstPath);
	vgPath* src = ((vgPath *) srcPath);
	
	dst->append(src);
}

void vgTransformPath(VGContext context, VGPath dstPath, VGPath srcPath)
{
	DECLARE_CONTEXT_PTR;
	vgPath* dst = ((vgPath *) dstPath);
	vgPath* src = ((vgPath *) srcPath);
	dst->transform(src, contextPtr->pathUserToSurface);	
}

void vgDrawPath(VGContext context, VGPath path, VGbitfield paintModes)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->DrawPath(path, paintModes);
}

VGdouble vgPathLength(VGPath path)
{
	return agg::path_length<agg::path_storage>( ((vgPath*)path)->path );
}

void vgPathBounds(VGPath path, VGdouble * minX, VGdouble * minY, VGdouble * width, VGdouble * height)
{
	agg::bounding_rect_single<agg::path_storage, VGdouble>(((vgPath*)path)->path, 0, minX, minY, width, height);

	// Do correction
	*width -= *minX;
	*height -= *minY;
}

void vgPathTransformedBounds(VGContext context, VGPath path, VGdouble * minX, VGdouble * minY, VGdouble * width, VGdouble * height)
{
	DECLARE_CONTEXT_PTR;

	// Build transformation pipeline
	agg::conv_transform< agg::path_storage> transformer( ((vgPath*)path)->path, contextPtr->pathUserToSurface );
	agg::bounding_rect_single< agg::conv_transform< agg::path_storage>, VGdouble >( transformer, 0, minX, minY, width, height);

	// Do correction
	*width -= *minX;
	*height -= *minY;
}

/**
 * Test that desired point (sx,sy) is into the path.
 * @param sx is X coordinate in a user coordinate space.
 * @param sy is Y coordinate in a user coordinate space.
 */
void vgPathHit(VGContext context, VGPath path, VGdouble sx, VGdouble sy)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->TestPathHit(path, sx, sy, false);
}

/**
 * Test that desired point (sx,sy) is into the path.
 * @param sx is X coordinate in a device coordinate space.
 * @param sy is Y coordinate in a device coordinate space.
 */
void vgPathTransformedHit(VGContext context, VGPath path, VGdouble sx, VGdouble sy)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->TestPathHit(path, sx, sy, true);
}

/**
 * Emits the command MOVETO[X,Y] to the given path.
 * @param path the path to store command
 * @param x x coordinate
 * @param y y coordinate
 */
void vgMoveTo(VGPath dstPath, VGdouble x, VGdouble y)
{
	vgPath* p = (vgPath*) dstPath;
	p->move_to(x,y);
}

void vgMoveRel(VGPath dstPath, VGdouble dx, VGdouble dy)
{
	vgPath* p = (vgPath*) dstPath;
	p->move_rel(dx,dy);
}

void vgLineTo(VGPath dstPath, VGdouble x, VGdouble y)
{
	vgPath* p = (vgPath*) dstPath;
	p->line_to(x,y);
}

void vgLineRel(VGPath dstPath, VGdouble dx, VGdouble dy)
{
	vgPath* p = (vgPath*) dstPath;
	p->line_rel(dx,dy);
}

void vgQuadricTo(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve3(dx_ctrl, dy_ctrl, dx_to, dy_to);
}

void vgQuadricTo2f(VGPath dstPath, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve3(dx_to, dy_to);
}

void vgQuadricRel(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve3_rel(dx_ctrl, dy_ctrl, dx_to, dy_to);
}

void vgCubicTo(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_ctrl2, VGdouble dy_ctrl2, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve4(dx_ctrl, dy_ctrl, dx_ctrl2, dy_ctrl2, dx_to, dy_to);
}

void vgCubicTo4f(VGPath dstPath, VGdouble dx_ctrl2, VGdouble dy_ctrl2, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve4(dx_ctrl2, dy_ctrl2, dx_to, dy_to);
}

void vgCubicRel(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_ctrl2, VGdouble dy_ctrl2, VGdouble dx_to, VGdouble dy_to)
{
	vgPath* p = (vgPath*) dstPath;
	p->curve4_rel(dx_ctrl, dy_ctrl, dx_ctrl2, dy_ctrl2, dx_to, dy_to);
}

/**
  Adds a line segment to the path from the current point to the beginning of the current sub-path, (the most 
  recent point passed to vgMoveTo()), and closes this sub-path. After this call the current point will be 
  at the joined endpoint of the sub-path. The behavior of vgClosePath() is distinct from simply calling 
  vgLineTo() with the equivalent coordinate in the case of stroking. When a closed sub-path is stroked, 
  there are no caps on the ends of the sub-path. Instead, there is a line join connecting the final 
  and initial segments of the sub-path. If there is no current point before the call to vgClosePath,
  this function will have no effect. 
  @param dstPath a path previously returned by either vgCreatePath().
 */
void vgClosePath(VGPath dstPath)
{
	vgPath* p = (vgPath*) dstPath;
	p->close_polygon();
}

void vgEndPath(VGPath dstPath)
{
	vgPath* p = (vgPath*) dstPath;
	p->end_poly();
}

// ----------------------------------------------------------------------------------

/**

 */
VGErrorCode vguArc(VGPath path, VGdouble cx, VGdouble cy, VGdouble rx, VGdouble ry, VGdouble startAngle, VGdouble angleExtent, VGint arcType)
{
	vgPath* p = (vgPath*) path;
	bool ccw = arcType & VGU_ARC_CW;

	arcType = (arcType & ~VGU_ARC_CW );
	
	if((arcType != VGU_ARC_OPEN && arcType != VGU_ARC_CHORD && arcType != VGU_ARC_PIE) || rx <= 0.0f || ry <= 0.0f)
		return VG_ILLEGAL_ARGUMENT_ERROR;

	p->arc(cx, cy, rx, ry, startAngle, angleExtent, (VGUArcType)arcType, ccw );
			
	return VG_NO_ERROR; // FIXME
}

VGErrorCode vguEllipse(VGPath path, VGdouble cx, VGdouble cy, VGdouble width, VGdouble height)
{
	vgPath* p = (vgPath*) path;
	
	if((width <= 0.0f) || (height <= 0.0f))
		return VG_ILLEGAL_ARGUMENT_ERROR;

	p->ellipse(cx, cy, width, height);
			
	return VG_NO_ERROR; // FIXME
}

VGErrorCode vguRect(VGPath path, VGdouble x, VGdouble y, VGdouble width, VGdouble height)
{
	vgPath* p = (vgPath*) path;
	
	if((width <= 0.0f) || (height <= 0.0f))
		return VG_ILLEGAL_ARGUMENT_ERROR;

	p->rectangle(x, y, width, height);
			
	return VG_NO_ERROR; // FIXME
}

VGErrorCode vguRoundRect(VGPath path, VGdouble x, VGdouble y, VGdouble width, VGdouble height, VGdouble radius)
{
	vgPath* p = (vgPath*) path;

	if((width <= 0.0f) || (height <= 0.0f) || (radius <= 0.0f))
		return VG_ILLEGAL_ARGUMENT_ERROR;

	p->roundRectangle(x, y, width, height, radius);
			
	return VG_NO_ERROR; // FIXME
}

VGErrorCode vguPolygon(VGPath path, VGPathDatatype dataType, const void* points, VGint count, VGboolean close)
{
	vgPath* p = (vgPath*) path;
	
	if((points == 0) || (count <= 0) || (dataType<VG_PATH_DATATYPE_S_8) || (dataType>VG_PATH_DATATYPE_D) )
		return VG_ILLEGAL_ARGUMENT_ERROR;

	p->polygon(dataType, points, count, close);
			
	return VG_NO_ERROR; // FIXME
}

/**
 * Creates new graphic context with these defaults:
 * - fill rule: VG_EVEN_ODD
 * - blend mode: VG_BLEND_SRC_OVER
 * - line width: 1.0f
 * - line cap style: VG_CAP_BUTT
 * - line join style:  VG_JOIN_MITER
 * - miter limit: 4.0f
 * - clear color: (0,0,0,0) (black)
 * - fill color: (255,255,255,255) (white)
 * - line color: (0,0,255,255) (green)
 * @param w width of surface in pixels
 * @param h height of surface in pixels
 * @param format pixel format
 * @param memory raw data memory of the surface
 */
VGContext vgCreateContext( unsigned w, unsigned h, VGPixelFormat format, void* memory )
{
	vgContext* instance = new vgContext( w,h,format, memory );
	return instance;
}

/**
 * Destroys graphic context.
 */ 
void vgDestroyContext(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	delete contextPtr;
}


VGFontProperty vgMakeFontProperty(const char* fontFilename, VGint size)
{
#if VGE_CONFIG_FREETYPE
	return (VGFontProperty) new vgFontProperty(fontFilename, size );
#else
	return 0;
#endif
}

void vgFontRotation(VGFontProperty font, VGdouble angle)
{
#if VGE_CONFIG_FREETYPE
	((vgFontProperty *)font)->SetRotation(angle);
#endif	
}

void vgDestroyFontProperty(VGFontProperty font)
{
#if VGE_CONFIG_FREETYPE
	delete (vgFontProperty *)font;
#endif
}

void vgDrawText(VGContext context, VGdouble x, VGdouble y, const char* text, VGFontProperty font )
{
#if VGE_CONFIG_FREETYPE
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->surface->Text(x, y, text, (vgFontProperty*) font, contextPtr->textColor);
#endif
}

void vgDrawLine(VGContext context, VGdouble x, VGdouble y, VGdouble x2, VGdouble y2, bool drawLastPoint)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->pathUserToSurface.transform( &x2, &y2 );
	contextPtr->surface->line( (int)(x+0.5), (int)(y+0.5), (int)(x2+0.5), (int)(y2+0.5), drawLastPoint, contextPtr->lineColor);
}

void vgDrawRect(VGContext context, VGdouble x, VGdouble y, VGdouble x2, VGdouble y2)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->pathUserToSurface.transform( &x2, &y2 );
	contextPtr->surface->rectangle((int)(x+0.5), (int)(y+0.5), (int)(x+x2+0.5), (int)(y+y2+0.5), contextPtr->lineColor);
}

void vgFillRect(VGContext context, VGdouble x, VGdouble y, VGdouble x2, VGdouble y2)
{
	DECLARE_CONTEXT_PTR;
	x2 += x;
	y2 += y;
	contextPtr->pathUserToSurface.transform( &x2, &y2 );
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->surface->solid_rectangle((int)(x+0.5), (int)(y+0.5), (int)(x2+0.5), (int)(y2+0.5), contextPtr->fillColor);
}

void vgDrawEllipse(VGContext context, VGdouble x, VGdouble y, VGdouble rx, VGdouble ry)
{
	DECLARE_CONTEXT_PTR;
	VGdouble refX = 0, refY = 0;
	contextPtr->pathUserToSurface.transform( &refX, &refY );
	
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->pathUserToSurface.transform( &rx, &ry );
	contextPtr->surface->ellipse((int)(x+0.5), (int)(y+0.5), (int)(rx+0.5-refX), (int)(ry+0.5-refY), contextPtr->lineColor);
}
		
void vgFillEllipse(VGContext context, VGdouble x, VGdouble y, VGdouble rx, VGdouble ry)
{
	DECLARE_CONTEXT_PTR;
	VGdouble refX = 0, refY = 0;
	contextPtr->pathUserToSurface.transform( &refX, &refY );
	
	contextPtr->pathUserToSurface.transform( &x, &y );
	contextPtr->pathUserToSurface.transform( &rx, &ry );
	contextPtr->surface->solid_ellipse((int)(x+0.5), (int)(y+0.5), (int)(rx+0.5-refX), (int)(ry+0.5-refY), contextPtr->fillColor);
}

void vgRenderingQuality( VGContext context, VGRenderingQuality quality )
{
	DECLARE_CONTEXT_PTR;
	contextPtr->SetRenderingQuality( quality );
}

void vgLineDash(VGContext context, VGdouble dashLen, VGdouble gapLen)
{
	DECLARE_CONTEXT_PTR;
	if (contextPtr->strokeDashSize < ContextBase::MAX_DASH_LEN-2)
	{
		contextPtr->strokeDashPattern[contextPtr->strokeDashSize++] = dashLen;
		contextPtr->strokeDashPattern[contextPtr->strokeDashSize++] = gapLen;
	}
}

void vgLineDashPhase(VGContext context, VGdouble phase)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->strokeDashPhase = phase;
}

void vgLineDashReset(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->strokeDashSize = 0;
}

/**
  Sets the current line cap style within the vgEngine context. See enum VGCapStyle for details about how 
  the available line cap styles are drawn. As with the other stroke parameters, the current line cap style
  is examined by vgDrawPath(), but does not have any effect during path construction.
  @param context a vgEngine context
  @param capStyle a cap style, specified as a VGCapStyle
 */ 
void vgLineCapStyle( VGContext context, VGCapStyle capStyle )
{
	DECLARE_CONTEXT_PTR;
	contextPtr->strokeCapStyle = capStyle;
}

/**
  Sets the current line join style within the vgEngine context. See enum VGJoinStyle for details
  about how the available line join styles are drawn. As with the other stroke parameters, 
  the current line join style is examined by vgDrawPath(), but does not have any effect
  during path construction.
  @param context a vgEngine context 
  @param joinStyle a line joint style
 */
void vgLineJoinStyle( VGContext context, VGJoinStyle joinStyle )
{	
	DECLARE_CONTEXT_PTR;
	contextPtr->strokeJoinStyle = joinStyle;
}

/**
  Sets the current miter limit within the cairo context. 
  If the current line join style is set to VG_JOIN_MITER (see vgLineJoinStyle()), the miter limit is used 
  to determine whether the lines should be joined with a bevel instead of a miter. vgEngine divides 
  the length of the miter by the line width. If the result is greater than the miter limit, the style 
  is converted to a bevel. As with the other stroke parameters, the current line miter limit is examined 
  by vgDrawPath(), but does not have any effect during path construction.
  @param context a vgEngine context 
  @param miter a line miter to set
 */ 
void vgLineMiter( VGContext context, VGdouble miter )
{
	DECLARE_CONTEXT_PTR;
	contextPtr->strokeMiterLimit = miter;
}

/**
  Set the current fill rule within the vgEngine context. The fill rule is used to determine which regions 
  are inside or outside a complex (potentially self-intersecting) path. The current fill rule affects 
  both vgDrawPath and vgClipBox. See enum VGFillRule for details on the semantics of each available fill rule.
  @param context a vgEngine context
  @param rule a fill rule, specified as a VGFillRule
 */ 
void vgFillRule( VGContext context, VGFillRule rule )
{
	DECLARE_CONTEXT_PTR;
	contextPtr->fillRule = rule;
}

void vgBlendMode(VGContext context, VGBlendMode mode)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->blendMode = mode;
}

void vgClipBox(VGContext context, VGint x, VGint y, VGint width, VGint height)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->clipMinX = x;	
	contextPtr->clipMinY = y;	
	contextPtr->clipWidth = width;	
	contextPtr->clipHeight = height;	
}

/**
 * Clear the framebuffer pixels in context with color given by vgClearColor().
 * @param context the given graphic context
 */
void vgClear(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->surface->clear( contextPtr->clearColor );
}

/**
 * Creates an image surface for the provided pixel data. The output buffer must be kept around until 
 * the VGImage is destroyed by call to vgDestroyImage. The initial contents of buffer is cleared.
 * @param format the format of pixels in the buffer 
 * @param width  the width of the image to be stored in the buffer 
 * @param height the height of the image to be stored in the buffer 
 * @param memory a pointer to a buffer supplied by the application in which to write contents. If pointer 
 *               is a NULL pointer, sufficient memory will be allocated.
 * @returns      a pointer to the newly created surface. The caller owns the surface and should 
 *               call vgDestroyImage when done with it. This function always returns a valid pointer.
 */
VGImage vgCreateImage(VGPixelFormat format, VGint width, VGint height, void* memory)
{
	return new vgImage(width, height, format, memory);
}

/**
 * Destroy Image surface (and it's memory if needed - was explicitly allocated (null pointer
 * passed as 'memory' parameter for vgCreateImage() ).
 */
void vgDestroyImage(VGImage image)
{
	delete (vgImage *)image;
}

/**
 * @return width of the context image surface in poixels.
 */
unsigned vgGetImageWidth(VGImage image)
{
    return ((vgImage *)image)->GetWidth();
}

/**
 * @return height of the context image surface in poixels.
 */
unsigned vgGetImageHeight(VGImage image)
{
    return ((vgImage *)image)->GetHeight();
}

VGPixelFormat vgGetImageFormat(VGImage image)
{
	return ((vgImage *)image)->GetPixelFormat();
}

void* vgGetImageRawData(VGImage image)
{
	return ((vgImage *)image)->GetImage();
}

void vgClearImage(VGImage image, VGint x, VGint y, VGint width, VGint height)
{
	// TODO
}

VGImage vgChildImage(VGImage parent, VGint x, VGint y, VGint width, VGint height)
{
	// TODO
}

void vgCopyImage(VGImage dst, VGint dx, VGint dy, VGImage src, VGint sx, VGint sy, VGint width, VGint height)
{
	// TODO
}

void vgCopyPixels(VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height)
{
	// TODO
}

// ---------------------------------------------------------------------------

/**
 * Load the current matrix from array of six VGDouble values.
 * The values are ordered: sx, shy, shx, sy, tx and ty.
 */ 
void vgLoadMatrix(VGContext context, const VGdouble * m) 
{ 
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.load_from(m);
}

/**
 * Store the current matrix to the array of six VGDouble values.
 * The values are ordered: sx, shy, shx, sy, tx and ty.
 */ 
void vgGetMatrix(VGContext context, VGdouble * m) 
{ 
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.store_to(m);
}

/**
 * Initializes matrix to a transformation that scales by sx and sy in the X and Y dimensions, respectively.
 * @param sx scale factor in the X direction 
 * @param sy scale factor in the Y direction 
 */ 
void vgScale(VGContext context, VGdouble sx, VGdouble sy)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.scale( sx, sy );
}

/**
 *  Modifies matrix to be an identity transformation.
 */ 
void vgLoadIdentity(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.reset();
}

/**
 * Push the current matrix on the matrix stack.
 */ 
void vgPushMatrix(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->matrixStack.push_back( contextPtr->pathUserToSurface );
}

/**
 * Pop the matrix on the top of matrix stack to the current matrix.
 */ 
void vgPopMatrix(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface = contextPtr->matrixStack.pop_back();
}
						
/**
 * Multiplies the affine transformations on top of stack and current together and stores the result in current. 
 * 1. pathUserToSurface = pathUserToSurface * MatrixOnStack
 * 2. PopMatrix
 */
void vgMultMatrix(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface *= contextPtr->matrixStack.pop_back();
}

/**
 * Changes matrix to be the inverse of it's original value. Not all transformation matrices have inverses; 
 * if the matrix collapses points together (it is degenerate), then it has no inverse and this function 
 * will fail.
 * 1. PushMatrix
 * 2. pathUserToSurface = inverse of pathUserToSurface
 */
void vgInverseMatrix(VGContext context)
{
	DECLARE_CONTEXT_PTR;
	vgPushMatrix(context);
	contextPtr->pathUserToSurface = ~contextPtr->pathUserToSurface;
}

/**
 * Applies a translation by tx, ty to the transformation in matrix. The effect of the new transformation 
 * is to first translate the coordinates by tx and ty, then apply the original transformation 
 * to the coordinates.
 * @param tx amount to translate in the X direction
 * @param ty amount to translate in the Y direction
 */ 
void vgTranslate(VGContext context, VGdouble tx, VGdouble ty)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.translate(tx, ty);	
}

/**
 * Initialized matrix to a transformation that rotates by degrees. 
 * @param angle angle of rotation, in degrees. The direction of rotation is defined such that positive 
 *        angles rotate in the direction from the positive X axis toward the positive Y axis. 
 *        With the default axis orientation of vgEngine, positive angles rotate in a clockwise direction.
 */ 
void vgRotate(VGContext context, VGdouble angle)
{
	DECLARE_CONTEXT_PTR;
	VGdouble a = agg::deg2rad(angle);
	contextPtr->pathUserToSurface.rotate(a);
}

/**
 *  Transforms the vertice from user to device coords (sx, sy) by matrix.
 *  @param sx X position. An in/out parameter
 *  @param sy Y position. An in/out parameter
 */ 
void vgTransformVerticeToDevice(VGContext context, VGdouble* sx, VGdouble* sy)
{
	DECLARE_CONTEXT_PTR;
	contextPtr->pathUserToSurface.transform( sx, sy );
}

/**
 *  Transforms the size from user to device coords (sx, sy) by matrix.
 *  @param sx a width. An in/out parameter
 *  @param sy a height. An in/out parameter
 */ 
void vgTransformSizeToDevice(VGContext context, VGdouble* sx, VGdouble* sy)
{
	DECLARE_CONTEXT_PTR;
	
	double refX = 0, refY = 0;
	
	contextPtr->pathUserToSurface.transform( &refX, &refY );
	contextPtr->pathUserToSurface.transform( sx, sy );
	
	*sx = *sx - refX;
	*sy = *sy - refY;
}

/**
 *  Transforms the vertice from device to user coords (sx, sy) by matrix.
 *  @param sx X position. An in/out parameter
 *  @param sy Y position. An in/out parameter
 */ 
void vgTransformVerticeToUser(VGContext context, VGdouble* sx, VGdouble* sy)
{
	vgInverseMatrix( context );
	vgTransformVerticeToDevice( context, sx, sy );
	vgPopMatrix( context );
}

/**
 *  Transforms the size from device to user coords (sx, sy) by matrix.
 *  @param sx a width. An in/out parameter
 *  @param sy a height. An in/out parameter
 */ 
void vgTransformSizeToUser(VGContext context, VGdouble* sx, VGdouble* sy)
{
	vgInverseMatrix( context );
	vgTransformSizeToDevice( context, sx, sy );
	vgPopMatrix( context );
}