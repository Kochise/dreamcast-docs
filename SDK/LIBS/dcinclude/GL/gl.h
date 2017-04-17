#ifndef __GL_GL_H
#define __GL_GL_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* This file was created using Mesa 3-D 3.4's gl.h as a reference. It is not a 
   complete gl.h header, but includes enough to use GL effectively. */

/* This is currently DC specific, so I don't feel toooo bad about this =) */
#include <dc/pvr.h>

/* GL data types */
#include <arch/types.h>
typedef unsigned int	GLenum;
typedef int		GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef int8		GLbyte;		/* 1-byte signed */
typedef int16		GLshort;	/* 2-byte signed */
typedef int32		GLint;		/* 4-byte signed */
typedef uint8		GLubyte;	/* 1-byte unsigned */
typedef uint16		GLushort;	/* 2-byte unsigned */
typedef uint32		GLuint;		/* 4-byte unsigned */
typedef int32		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */

/* For these next two, KOS is generally compiled in m4-single-only, so we
   just use floats for everything anyway. */
typedef float		GLdouble;	/* double precision float */
typedef float		GLclampd;	/* double precision float in [0,1] */

/* Constants */
#define GL_FALSE	0
#define GL_TRUE		1

/* Data types */
#define GL_BYTE			0x1400
#define GL_UNSIGNED_BYTE	0x1401
#define GL_SHORT		0x1402
#define GL_UNSIGNED_SHORT	0x1403
#define GL_INT			0x1404
#define GL_UNSIGNED_INT		0x1405
#define GL_FLOAT		0x1406
#define GL_DOUBLE		0x140A
#define GL_2_BYTES		0x1407
#define GL_3_BYTES		0x1408
#define GL_4_BYTES		0x1409

/* StringName */
#define GL_VENDOR		0x1F00
#define GL_RENDERER		0x1F01
#define GL_VERSION		0x1F02
#define GL_EXTENSIONS		0x1F03

/* Gets */
#define GL_ATTRIB_STACK_DEPTH			0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH		0x0BB1
#define GL_COLOR_CLEAR_VALUE			0x0C22
#define GL_COLOR_WRITEMASK			0x0C23
#define GL_CURRENT_INDEX			0x0B01
#define GL_CURRENT_COLOR			0x0B00
#define GL_CURRENT_NORMAL			0x0B02
#define GL_CURRENT_RASTER_COLOR			0x0B04
#define GL_CURRENT_RASTER_DISTANCE		0x0B09
#define GL_CURRENT_RASTER_INDEX			0x0B05
#define GL_CURRENT_RASTER_POSITION		0x0B07
#define GL_CURRENT_RASTER_TEXTURE_COORDS	0x0B06
#define GL_CURRENT_RASTER_POSITION_VALID	0x0B08
#define GL_CURRENT_TEXTURE_COORDS		0x0B03
#define GL_INDEX_CLEAR_VALUE			0x0C20
#define GL_INDEX_MODE				0x0C30
#define GL_INDEX_WRITEMASK			0x0C21
#define GL_MODELVIEW_MATRIX			0x0BA6
#define GL_MODELVIEW_STACK_DEPTH		0x0BA3
#define GL_NAME_STACK_DEPTH			0x0D70
#define GL_PROJECTION_MATRIX			0x0BA7
#define GL_PROJECTION_STACK_DEPTH		0x0BA4
#define GL_RENDER_MODE				0x0C40
#define GL_RGBA_MODE				0x0C31
#define GL_TEXTURE_MATRIX			0x0BA8
#define GL_TEXTURE_STACK_DEPTH			0x0BA5
#define GL_VIEWPORT				0x0BA2

/* Primitives types: all 0's are unsupported for now */
#define GL_POINTS		1
#define GL_LINES		0 /*2*/
#define GL_LINE_LOOP		0 /*3*/
#define GL_LINE_STRIP		0 /*4*/
#define GL_TRIANGLES		5
#define GL_TRIANGLE_STRIP	6
#define GL_TRIANGLE_FAN		0 /*7*/
#define GL_QUADS		8
#define GL_QUAD_STRIP		9
#define GL_POLYGON		10

/* FrontFaceDirection */
#define GL_CW			0x0900
#define GL_CCW			0x0901

#define GL_CULL_FACE            0x0B44
#define GL_FRONT                0x0404
#define GL_BACK                 0x0405

/* Scissor box */
#define GL_SCISSOR_TEST		0x0008		/* capability bit */
#define GL_KOS_USERCLIP_OUTSIDE 0x4000		/* capability bit */
#define GL_SCISSOR_BOX		0x0C10

/* Matrix modes */
#define GL_MATRIX_MODE		0x0BA0
#define GL_MATRIX_MODE_FIRST	1
#define GL_MODELVIEW		1
#define GL_PROJECTION		2
#define GL_TEXTURE		3
#define GL_MATRIX_COUNT		4

/* Special KOS "matrix mode" (for glKosMatrixApply only) */
#define GL_KOS_SCREENVIEW	0x100

/* "Depth buffer" -- we don't actually support a depth buffer because
   the PVR does all of that internally. But these constants are to
   ease porting. */
#define GL_NEVER		0x0200
#define GL_LESS			0x0201
#define GL_EQUAL		0x0202
#define GL_LEQUAL		0x0203
#define GL_GREATER		0x0204
#define GL_NOTEQUAL		0x0205
#define GL_GEQUAL		0x0206
#define GL_ALWAYS		0x0207

#define GL_DEPTH_TEST		0
#define GL_DEPTH_BITS		0
#define GL_DEPTH_CLEAR_VALUE	0
#define GL_DEPTH_FUNC		0
#define GL_DEPTH_RANGE		0
#define GL_DEPTH_WRITEMASK	0
#define GL_DEPTH_COMPONENT	0

/* Lighting constants */
#define GL_LIGHTING		0x0b50
#define GL_LIGHT0		0x0010		/* capability bit */
#define GL_LIGHT1		0x0000
#define GL_LIGHT2		0x0000
#define GL_LIGHT3		0x0000
#define GL_LIGHT4		0x0000
#define GL_LIGHT5		0x0000
#define GL_LIGHT6		0x0000
#define GL_LIGHT7		0x0000
#define GL_AMBIENT		0x1200
#define GL_DIFFUSE		0x1201
#define GL_SPECULAR		0
#define GL_SHININESS		0
#define GL_EMISSION		0
#define GL_POSITION		0x1203
#define GL_SHADE_MODEL		0x0b54
#define GL_FLAT			0x1d00
#define GL_SMOOTH		0x1d01

/* Fog */
#define GL_FOG			0x0004		/* capability bit */
#define GL_FOG_MODE		0x0B65
#define GL_FOG_DENSITY		0x0B62
#define GL_FOG_COLOR		0x0B66
#define GL_FOG_INDEX		0x0B61
#define GL_FOG_START		0x0B63
#define GL_FOG_END		0x0B64
#define GL_LINEAR		0x2601
#define GL_EXP			0x0800
#define GL_EXP2			0x0801

/* Hints */
#define GL_FOG_HINT			0x0C54
#define GL_PERSPECTIVE_CORRECTION_HINT	0x0c50
#define GL_POINT_SMOOTH_HINT		0x0C51
#define GL_LINE_SMOOTH_HINT		0x0C52
#define GL_POLYGON_SMOOTH_HINT		0x0C53
#define GL_DONT_CARE			0x1100
#define GL_FASTEST			0x1101
#define GL_NICEST			0x1102

/* Misc bitfield things; we don't really use these either */
#define GL_COLOR_BUFFER_BIT	0
#define GL_DEPTH_BUFFER_BIT	0

/* Blending: not sure how we'll use these yet; the PVR supports a few
   of these so we'll want to eventually */
#define GL_BLEND		0x0002		/* capability bit */
#define GL_BLEND_SRC		2
#define GL_BLEND_DST		3

#define GL_ZERO			0
#define GL_ONE			1
#define GL_SRC_COLOR		0x0300
#define GL_ONE_MINUS_SRC_COLOR	0x0301
#define GL_SRC_ALPHA		0x0302
#define GL_ONE_MINUS_SRC_ALPHA	0x0303
#define GL_DST_ALPHA		0x0304
#define GL_ONE_MINUS_DST_ALPHA	0x0305
#define GL_DST_COLOR		0x0306
#define GL_ONE_MINUS_DST_COLOR	0x0307
/*#define GL_SRC_ALPHA_SATURATE	0x0308 unsupported */

/* Misc texture constants */
#define GL_TEXTURE_2D		0x0001		/* capability bit */
#define GL_KOS_AUTO_UV		0x8000		/* capability bit */
#define GL_TEXTURE_WRAP_S	0x2802
#define GL_TEXTURE_WRAP_T	0x2803
#define GL_TEXTURE_MIN_FILTER	1
#define GL_TEXTURE_MAG_FILTER	1
#define GL_TEXTURE_FILTER	GL_TEXTURE_MIN_FILTER
#define GL_FILTER_NONE		0
#define GL_FILTER_BILINEAR	1
#define GL_REPEAT		0x2901
#define GL_CLAMP		0x2900

/* Texture Environment */
#define GL_TEXTURE_ENV_MODE	0x2200
#define GL_REPLACE		0
#define GL_MODULATE		1
#define GL_DECAL		2
#define GL_MODULATEALPHA	3

/* Texture format definitions (yes, these vary from real GL) */
#define GL_ARGB1555		(PVR_TXRFMT_ARGB1555 | PVR_TXRFMT_NONTWIDDLED)
#define GL_RGB565		(PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED)
#define GL_ARGB4444		(PVR_TXRFMT_ARGB4444 | PVR_TXRFMT_NONTWIDDLED)
#define GL_YUV422		(PVR_TXRFMT_YUV422 | PVR_TXRFMT_NONTWIDDLED)
#define GL_BUMP			(PVR_TXRFMT_BUMP | PVR_TXRFMT_NONTWIDDLED)
#define GL_ARGB1555_TWID	PVR_TXRFMT_ARGB1555
#define GL_RGB565_TWID		PVR_TXRFMT_RGB565
#define GL_ARGB4444_TWID	PVR_TXRFMT_ARGB4444
#define GL_YUV422_TWID		PVR_TXRFMT_YUV422
#define GL_BUMP_TWID		PVR_TXRFMT_BUMP
#define GL_VQ_ENABLE		PVR_TXRFMT_VQ_ENABLE

/* KOS-specific defines */
#define GL_LIST_NONE		0x00
#define GL_LIST_FIRST		0x01
#define GL_LIST_OPAQUE_POLY	0x01		/* PVR2 modes */
#define GL_LIST_OPAQUE_MOD	0x02
#define GL_LIST_TRANS_POLY	0x04
#define GL_LIST_TRANS_MOD	0x08
#define GL_LIST_PUNCHTHRU	0x10
#define GL_LIST_END		0x20		/* no more lists */
#define GL_LIST_COUNT		5

/* KOS-DCPVR-Modifier-specific '?primatives?'*/
#define GL_KOS_MODIFIER_OTHER_POLY	PVR_MODIFIER_OTHER_POLY
#define GL_KOS_MODIFIER_FIRST_POLY	PVR_MODIFIER_FIRST_POLY
#define GL_KOS_MODIFIER_LAST_POLY	PVR_MODIFIER_LAST_POLY

/* Applied to primatives that will be affected by modifier volumes
   or cheap shadows */
#define GL_KOS_MODIFIER		0x2000		/* capability bit */
#define GL_KOS_CHEAP_SHADOW	0x1000		/* capability bit */

/* KOS near Z-CLIPPING */
#define GL_KOS_NEARZ_CLIPPING		0x0020		/* capability bit */

/* KOS-specific APIs */
int glKosInit();		/* Call before using GL */
void glKosShutdown();		/* Call after finishing with it */
void glKosGetScreenSize(GLfloat *x, GLfloat *y);	/* Get screen size */
void glKosBeginFrame();		/* Begin frame sequence */
void glKosFinishFrame();	/* Finish frame sequence */
void glKosFinishList();		/* Finish with the current list */
void glKosMatrixIdent();	/* Set the DC's matrix regs to an identity */
void glKosMatrixApply(GLenum mode);	/* Apply one of the GL matrices to the DC's matrix regs */
void glKosMatrixDirty();	/* Set matrix regs as dirtied */
void glKosPolyHdrDirty();	/* Set poly header context as dirtied */
void glKosPolyHdrSend();	/* Send the current KGL poly header */

/* Miscellaneous APIs */
void glClearColor(GLclampf red,
	GLclampf green,
	GLclampf blue,
	GLclampf alpha);

void glClear(GLbitfield mask);

void glEnable(GLenum cap);

void glDisable(GLenum cap);

void glFrontFace(GLenum mode);

void glCullFace(GLenum mode);

void glFlush();

void glHint(GLenum target, GLenum mode);

void glPointSize(GLfloat size);

const GLubyte *glGetString(GLenum name);

void glGetFloatv(GLenum pname, GLfloat *param);

/* Blending functions */
void glBlendFunc(GLenum sfactor, GLenum dfactor);

/* Depth buffer (non-functional, just stubs) */
void glClearDepth(GLclampd depth);

void glDepthMask(GLboolean flag);

void glDepthFunc(GLenum func);

/* Transformation */
void glMatrixMode(GLenum mode);

void glFrustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat znear, GLfloat zfar);

void glOrtho(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat znear, GLfloat zfar);

void glDepthRange(GLclampf n, GLclampf f);

void glViewport(GLint x, GLint y,
	GLsizei width, GLsizei height);

void glPushMatrix(void);

void glPopMatrix(void);

void glLoadIdentity(void);

void glLoadMatrixf(const GLfloat *m);

void glLoadTransposeMatrixf(const GLfloat *m);

void glMultMatrixf(const GLfloat *m);

void glMultTransposeMatrixf(const GLfloat *m);

void glRotatef(GLfloat angle,
	GLfloat x, GLfloat y, GLfloat z);

void glScalef(GLfloat x, GLfloat y, GLfloat z);

void glTranslatef(GLfloat x, GLfloat y, GLfloat z);

/* Display lists */
/* (need to complete) */

/* Drawing functions */
void glBegin(GLenum mode);

void glEnd(void);

void glVertex3f(GLfloat x, GLfloat y, GLfloat z);

void glVertex3fv(GLfloat *v);

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);

void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);

void glColor3fv(GLfloat *v); 

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void glColor4fv(GLfloat *v); 

void glTexCoord2f(GLfloat s, GLfloat t);

void glTexCoord2fv(GLfloat *v);

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);

/* Texture API */
void glGenTextures(GLsizei n, GLuint *textures);

void glDeleteTextures(GLsizei n, const GLuint *textures);

void glBindTexture(GLenum target, GLuint texture);

void glTexImage2D(GLenum target, GLint level,
		GLint internalFormat,
		GLsizei width, GLsizei height,
		GLint border, GLenum format, GLenum type,
		const GLvoid *pixels);

void glKosTex2D(GLint internal_fmt, GLsizei width, GLsizei height,
		pvr_ptr_t txr_address);

void glTexEnvi(GLenum target, GLenum pname, GLint param);

void glTexParameteri(GLenum target, GLenum pname, GLint param);

/* Lighting */
void glShadeModel(GLenum mode);

/* Fog */
void glFogf( GLenum pname, GLfloat param );

void glFogi( GLenum pname, GLint param );

void glFogfv( GLenum pname, const GLfloat *params );

void glFogiv( GLenum pname, const GLint *params );

/* Modifier Volumes - currently non-functional */
void glKosModBegin(GLenum mode);

void glKosModEnd(void);

void glKosModVolume9f(GLfloat ax, GLfloat ay, GLfloat az,
		   GLfloat bx, GLfloat by, GLfloat bz,
		   GLfloat cx, GLfloat cy, GLfloat cz);

__END_DECLS

#endif	/* __GL_GL_H */

