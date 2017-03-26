/**********************************************************************
 *                                                                    *
 * Copyright  2006 Ales a.s.                                          *
 *                                                                    *
 **********************************************************************/

#ifndef _LIBVGE_H
#define _LIBVGE_H

#ifdef __cplusplus
extern "C" {
#endif

#define LIBVGE_VERSION 0x000908

/**
 * @defgroup all vgEngine API
 * @{
*/ 


/**
 * @defgroup datatypes Data types
 * @{
*/ 

typedef double			VGdouble;
typedef signed char		VGbyte;
typedef unsigned char	VGubyte;
typedef short			VGshort;
typedef int				VGint;
typedef unsigned int	VGuint;
typedef unsigned int	VGbitfield;

typedef enum {
  VG_FALSE = 0,
  VG_TRUE  = 1
} VGboolean;

typedef void* VGHandle;

#define VG_INVALID_HANDLE ((VGHandle)0)

/**
 *
 */
typedef enum {
  VG_NO_ERROR,
  VG_BAD_HANDLE_ERROR,
  VG_ILLEGAL_ARGUMENT_ERROR,
  VG_OUT_OF_MEMORY_ERROR,
  VG_OUT_OF_RANGE
} VGErrorCode;

typedef enum {
  VG_RENDERING_QUALITY_NONANTIALIASED,
  VG_RENDERING_QUALITY_FASTER,
  VG_RENDERING_QUALITY_BETTER
} VGRenderingQuality;

typedef enum {
  VG_PIXEL_LAYOUT_UNKNOWN,
  VG_PIXEL_LAYOUT_RGB_VERTICAL,
  VG_PIXEL_LAYOUT_BGR_VERTICAL,
  VG_PIXEL_LAYOUT_RGB_HORIZONTAL,
  VG_PIXEL_LAYOUT_BGR_HORIZONTAL
} VGPixelLayout;

typedef enum {
  VG_PATH_DATATYPE_INVALID,
  VG_PATH_DATATYPE_S_8,
  VG_PATH_DATATYPE_S_16,
  VG_PATH_DATATYPE_S_32,
  VG_PATH_DATATYPE_F,
  VG_PATH_DATATYPE_D
} VGPathDatatype;

/**
  Specifies how to render the endpoint of a line when stroking.
  - VG_CAP_BUTT   start(stop) the line exactly at the start(end) point 
  - VG_CAP_ROUND   use a round ending, the center of the circle is the end point 
  - VG_CAP_SQUARE   use squared ending, the center of the square is the end point
*/ 
typedef enum {
  VG_CAP_BUTT,
  VG_CAP_ROUND,
  VG_CAP_SQUARE
} VGCapStyle;

/**
  Specifies how to render the junction of two lines when stroking.
  - VG_JOIN_MITER use a sharp (angled) corner, see vgLineMiter() 
  - VG_JOIN_ROUND use a rounded join, the center of the circle is the joint point 
  - VG_JOIN_BEVEL use a cut-off join, the join is cut off at half the line width from the joint point
 */
typedef enum {
  VG_JOIN_MITER,
  VG_JOIN_ROUND,
  VG_JOIN_BEVEL
} VGJoinStyle;

/**
  VGFillRule is used to select how paths are filled. For both fill rules, whether or not a point is included
  in the fill is determined by taking a ray from that point to infinity and looking at intersections with 
  the path. The ray can be in any direction, as long as it doesn't pass through the end point of a segment 
  or have a tricky intersection such as intersecting tangent to the path. (Note that filling is not actually 
  implemented in this way. This is just a description of the rule that is applied.)
  
  - VG_EVEN_ODD   Counts the total number of intersections, without regard to the orientation of the contour.
    If the total number of intersections is odd, the point will be filled.
  - VG_NON_ZERO   If the path crosses the ray from left-to-right, counts +1. If the path crosses 
    the ray from right to left, counts -1. (Left and right are determined from the perspective of looking 
    along the ray from the starting point.) If the total count is non-zero, the point will be filled. 
    PS: It is know as Winding rule also.
 */ 
typedef enum {
  VG_EVEN_ODD,
  VG_NON_ZERO
} VGFillRule;

typedef enum {
  VG_STROKE_PATH = (1 << 0),
  VG_FILL_PATH   = (1 << 1)
} VGPaintMode;

typedef enum  
{
  VG_Pixel_Undefined,
  /*
  VG_Pixel_Bgr15,
  VG_Pixel_Bgr16,
  */
  VG_Pixel_Bgra32,
  VG_Pixel_Rgba32,
  VG_Pixel_Argb32,
  VG_Pixel_Abgr32
} VGPixelFormat;

typedef enum {
  VG_BLEND_SRC,
  VG_BLEND_SRC_OVER,
  VG_BLEND_DST_OVER,
  VG_BLEND_SRC_IN,
  VG_BLEND_DST_IN,
  VG_BLEND_MULTIPLY,
  VG_BLEND_SCREEN,
  VG_BLEND_DARKEN,
  VG_BLEND_LIGHTEN,
  VG_BLEND_XOR
} VGBlendMode;
/// @}

/**
  @ingroup image
  Image surfaces provide the ability to render to memory buffers either allocated by vgEngine or by
  the calling code. The supported image formats are those defined in VGPixelFormat.
 */
typedef VGHandle VGImage;


/// @defgroup context Graphic context management
/// @{

/**
 *  VGContext is the main object used when drawing with vgEngine. To draw with vgEngine, you create a VGContext,
 *  set the target surface, and drawing options for the VGContext, create shapes with functions like vgMoveTo()
 *  and vgLineTo(), and then draw shapes with vgDrawPath().
 *  VGContext's can be pushed to a stack via vgSaveContext(). They may then safely be changed, without loosing
 *  the current state. Use vgRestoreContext() to restore to the saved state.
 *
 */
typedef VGHandle VGContext;

VGContext   vgCreateContext(unsigned width, unsigned height, VGPixelFormat format, void* memory);
void        vgDestroyContext(VGContext context);
VGErrorCode vgGetError(VGContext context);
void        vgClear(VGContext context);
void        vgClipBox(VGContext context, VGint x, VGint y, VGint width, VGint height);
void        vgSaveContext(VGContext context);
void        vgRestoreContext(VGContext context);
VGImage     vgContextToImage(VGContext context);

void        vgRenderingQuality(VGContext context, VGRenderingQuality quality );
void        vgBlendMode(VGContext context, VGBlendMode mode);
void        vgClearColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha);
void        vgFillColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha);
void        vgLineColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha);
void        vgTextColor(VGContext context, VGubyte red, VGubyte green, VGubyte blue, VGubyte alpha);
void        vgLineWidth(VGContext context, VGdouble width);
void        vgLineDash(VGContext context, VGdouble dashLen, VGdouble gapLen);
void        vgLineDashPhase(VGContext context, VGdouble phase);
void        vgLineDashReset(VGContext context);
void        vgLineCapStyle( VGContext context, VGCapStyle capStyle );
void        vgLineJoinStyle( VGContext context, VGJoinStyle capStyle );
void        vgLineMiter( VGContext context, VGdouble miter );
void        vgFillRule( VGContext context, VGFillRule rule );
/// @}

/// @defgroup image In-memory graphic image management
/// @{

VGImage       vgCreateImage( unsigned width, unsigned height, VGPixelFormat format, void* memory );
void          vgDestroyImage(VGImage image);
unsigned      vgGetImageWidth(VGImage image);
unsigned      vgGetImageHeight(VGImage image);
VGPixelFormat vgGetImageFormat(VGImage image);
void*         vgGetImageRawData(VGImage image);

/*
void vgClearImage(VGImage image, VGint x, VGint y, VGint width, VGint height);
VGImage vgChildImage(VGImage parent, VGint x, VGint y, VGint width, VGint height);
void vgCopyImage(VGImage dst, VGint dx, VGint dy, VGImage src, VGint sx, VGint sy, VGint width, VGint height);
void vgCopyPixels(VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height);
*/
/// @}

/// @defgroup matrix Matrix manipulation
/// @{
void vgLoadIdentity(VGContext context);
void vgPushMatrix(VGContext context);
void vgPopMatrix(VGContext context);
void vgMultMatrix(VGContext context);
void vgInverseMatrix(VGContext context);
void vgTranslate(VGContext context, VGdouble tx, VGdouble ty);
void vgScale(VGContext context, VGdouble sx, VGdouble sy);
void vgRotate(VGContext context, VGdouble angle);
void vgTransformVerticeToDevice(VGContext context, VGdouble* sx, VGdouble* sy);
void vgTransformSizeToDevice(VGContext context, VGdouble* sx, VGdouble* sy);
void vgTransformVerticeToUser(VGContext context, VGdouble* sx, VGdouble* sy);
void vgTransformSizeToUser(VGContext context, VGdouble* sx, VGdouble* sy);

/// @}

/// @defgroup path Path manipulation
/// @{

/**
  A data structure for holding a path. This data structure serves as the return value for vgCreatePath()
  as well the input value for all path manipulation.  See @group path for hints on how to iterate over
  the actual data within the path. A path data includes both commands and coordinates.
 */
typedef  VGHandle VGPath;

VGPath   vgCreatePath(void);
void     vgClearPath(VGPath path);
void     vgDestroyPath(VGPath path);
void     vgAppendPath(VGPath dstPath, VGPath srcPath);
void     vgTransformPath(VGContext context, VGPath dstPath, VGPath srcPath);
VGdouble vgPathLength(VGPath path);
void     vgPathBounds(VGPath path, VGdouble * minX, VGdouble * minY, VGdouble * width, VGdouble * height);
void     vgPathTransformedBounds(VGContext context, VGPath path, VGdouble * minX, VGdouble * minY, VGdouble * width, VGdouble * height);
void     vgPathHit(VGContext context, VGPath path, VGdouble sx, VGdouble sy);
void     vgPathTransformedHit(VGContext context, VGPath path, VGdouble sx, VGdouble sy);
void     vgClosePath(VGPath dstPath);
void     vgEndPath(VGPath dstPath);

void     vgMoveTo(VGPath dstPath, VGdouble x, VGdouble y);
void     vgMoveRel(VGPath dstPath, VGdouble dx, VGdouble dy);
void     vgLineTo(VGPath dstPath, VGdouble x, VGdouble y);
void     vgLineRel(VGPath dstPath, VGdouble dx, VGdouble dy);
void     vgQuadricTo(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_to, VGdouble dy_to);
void     vgQuadricRel(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble dx_to, VGdouble dy_to);
void     vgQuadricTo2f(VGPath dstPath, VGdouble dx_to, VGdouble dy_to);

void     vgCubicTo(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble x_ctrl2, VGdouble y_ctrl2, VGdouble dx_to, VGdouble dy_to);
void     vgCubicRel(VGPath dstPath, VGdouble dx_ctrl, VGdouble dy_ctrl, VGdouble x_ctrl2, VGdouble y_ctrl2, VGdouble dx_to, VGdouble dy_to);
void     vgCubicTo4f(VGPath dstPath, VGdouble x_ctrl2, VGdouble y_ctrl2, VGdouble dx_to, VGdouble dy_to);

void     vgDrawPath(VGContext context, VGPath path, VGbitfield paintModes);
/// @}

/// @defgroup primitives Graphic primitive drawing
/// These primitives doesn't support antialiasing, line width and dashes, but they speeds up to 20 times.
/// @{
void     vgDrawLine(VGContext context, VGdouble x, VGdouble y, VGdouble x2, VGdouble y2, bool drawLastPoint);
void     vgDrawRect(VGContext context, VGdouble x, VGdouble y, VGdouble w, VGdouble h);
void     vgFillRect(VGContext context, VGdouble x, VGdouble y, VGdouble w, VGdouble h);
void     vgDrawEllipse(VGContext context, VGdouble x, VGdouble y, VGdouble rx, VGdouble ry);
void     vgFillEllipse(VGContext context, VGdouble x, VGdouble y, VGdouble rx, VGdouble ry);
/// @}

/// @defgroup text Text manipulation
/// @{

typedef        VGHandle VGFontProperty;

VGFontProperty vgMakeFontProperty(const char* fontFilename, VGint size);
void           vgFontRotation(VGFontProperty font, VGdouble angle);
void           vgDestroyFontProperty(VGFontProperty font);
void           vgDrawText(VGContext context, VGdouble x, VGdouble y, const char* text, VGFontProperty font );
/// @}

// -----------------------------------------------------------------------------------

/// @defgroup utility Utility
/// @{

typedef enum {
  VGU_ARC_OPEN,
  VGU_ARC_CHORD,
  VGU_ARC_PIE
} VGUArcType;

typedef enum {
  VGU_ARC_CCW = 0x0000,
  VGU_ARC_CW  = 0x0200,
} VGUArcSweep;

VGErrorCode vguPolygon(VGPath path, VGPathDatatype dataType, const void* points, VGint count, VGboolean doClose);
VGErrorCode vguRect(VGPath path, VGdouble x, VGdouble y, VGdouble width, VGdouble height);
VGErrorCode vguRoundRect(VGPath path, VGdouble x, VGdouble y, VGdouble width, VGdouble height, VGdouble radius);
VGErrorCode vguEllipse(VGPath path, VGdouble cx, VGdouble cy, VGdouble width, VGdouble height);
VGErrorCode vguArc(VGPath path, VGdouble x, VGdouble y, VGdouble width, VGdouble height, VGdouble startAngle, VGdouble angleExtent, VGint arcType);
/// @}
/// @}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
