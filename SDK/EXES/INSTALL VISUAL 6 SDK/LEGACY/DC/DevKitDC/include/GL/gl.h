#ifndef __GL_GL_H
#define __GL_GL_H

/* This file was created using Mesa 3-D 3.4's gl.h as a reference. It is not a 
   complete gl.h header, but includes enough to use KallistiGL effectively. */

#include <sys/cdefs.h>
__BEGIN_DECLS

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

/* Primitives types: all 0's are unsupported for now */
#define GL_POINTS		0 /*1*/
#define GL_LINES		0 /*2*/
#define GL_LINE_LOOP		0 /*3*/
#define GL_LINE_STRIP		0 /*4*/
#define GL_TRIANGLES		5
#define GL_TRIANGLE_STRIP	0 /*6*/
#define GL_TRIANGLE_FAN		0 /*7*/
#define GL_QUADS		8
#define GL_QUAD_STRIP		0 /*9*/
#define GL_POLYGON		0 /*10*/

#define GL_CULL_FACE            0x0B44
#define GL_FRONT                0x0404
#define GL_BACK                 0x0405

/* Matrix modes */
#define GL_MATRIX_MODE		0x0BA0
#define GL_MATRIX_MODE_FIRST	1
#define GL_MODELVIEW		1
#define GL_PROJECTION		2
#define GL_TEXTURE		3
#define GL_MATRIX_COUNT		4

/* "Depth buffer" -- we don't actually support a depth buffer because
   the PVR does all of that internally. But these constants are to
   ease porting. */
#define GL_NEVER		0
#define GL_LESS			0
#define GL_EQUAL		0
#define GL_LEQUAL		0x0203
#define GL_GREATER		0
#define GL_NOTEQUAL		0
#define GL_GEQUAL		0
#define GL_ALWAYS		0
#define GL_DEPTH_TEST		0
#define GL_DEPTH_BITS		0
#define GL_DEPTH_CLEAR_VALUE	0
#define GL_DEPTH_FUNC		0
#define GL_DEPTH_RANGE		0
#define GL_DEPTH_WRITEMASK	0
#define GL_DEPTH_COMPONENT	0

/* Lighting constants */
#define GL_LIGHTING		0x0b50
#define GL_LIGHT0		0x0001
#define GL_LIGHT1		0x0002
#define GL_LIGHT2		0x0004
#define GL_LIGHT3		0x0008
#define GL_LIGHT4		0x0010
#define GL_LIGHT5		0x0020
#define GL_LIGHT6		0x0040
#define GL_LIGHT7		0x0080
#define GL_AMBIENT		0x1200
#define GL_DIFFUSE		0x1201
#define GL_SPECULAR		0
#define GL_SHININESS		0
#define GL_EMISSION		0
#define GL_POSITION		0x1203
#define GL_SHADE_MODEL		0x0b54
#define GL_SMOOTH		0x1d01

/* Hints */
#define GL_PERSPECTIVE_CORRECTION_HINT	0x0c50
#define GL_NICEST			0x1102

/* Misc bitfield things; we don't really use these either */
#define GL_COLOR_BUFFER_BIT	0
#define GL_DEPTH_BUFFER_BIT	0

/* Blending: not sure how we'll use these yet; the PVR supports a few
   of these so we'll want to eventually */
#define GL_BLEND		2
#define GL_BLEND_SRC		2
#define GL_BLEND_DST		3

/* Misc texture constants */
#define GL_TEXTURE_2D		1		/* capability bit */
#define GL_KOS_AUTO_UV		0x8000		/* capability bit */
#define GL_TEXTURE_MIN_FILTER	1
#define GL_TEXTURE_MAG_FILTER	1
#define GL_TEXTURE_FILTER	GL_TEXTURE_MIN_FILTER
#define GL_FILTER_NONE		TA_NO_FILTER
#define GL_FILTER_BILINEAR	TA_BILINEAR_FILTER

/* Texture format definitions (yes, these vary from real GL) */
#define GL_ARGB1555		TA_ARGB1555
#define GL_RGB565		TA_RGB565
#define GL_ARGB4444		TA_ARGB4444
#define GL_YUV422		TA_YUV422
#define GL_BUMP			TA_BUMP
#define GL_ARGB1555_TWID	TA_ARGB1555_TWID
#define GL_RGB565_TWID		TA_RGB565_TWID
#define GL_ARGB4444_TWID	TA_ARGB4444_TWID
#define GL_YUV422_TWID		TA_YUV422_TWID
#define GL_BUMP_TWID		TA_BUMP_TWID

/* KOS-specific defines */
#define GL_LIST_NONE		0x00
#define GL_LIST_FIRST		0x01
#define GL_LIST_OPAQUE_POLY	0x01	/* PVR2 modes */
#define GL_LIST_TRANS_POLY	0x02
#define GL_LIST_OPAQUE_MOD	0x04
#define GL_LIST_TRANS_MOD	0x08
#define GL_LIST_PUNCHTHRU	0x10
#define GL_LIST_COUNT		5

/* KOS-specific APIs */
int glKosInit();		/* Call before using GL */
void glKosShutdown();		/* Call after finishing with it */
void glKosGetScreenSize(GLfloat *x, GLfloat *y);	/* Get screen size */
void glKosBeginFrame();		/* Begin frame sequence */
void glKosFinishFrame();	/* Finish frame sequence */
void glKosFinishList();		/* Finish with the current list */

/* Miscellaneous APIs */
void glClearColor(GLclampf red,
	GLclampf green,
	GLclampf blue,
	GLclampf alpha);

void glClear(GLbitfield mask);

void glEnable(GLenum cap);

void glDisable(GLenum cap);

void glCullFace(GLenum mode);

void glFlush();

void glHint(GLenum target, GLenum mode);

/* Depth buffer (non-functional, just stubs) */
void glClearDepth(GLclampd depth);

void glDepthFunc(GLenum func);

/* Transformation */
void glMatrixMode(GLenum mode);

void glOrtho(GLdouble left, GLdouble right,
	GLdouble bottom, GLdouble top,
	GLdouble near_val, GLdouble far_val);

void glViewPort(GLint x, GLint y,
	GLsizei width, GLsizei height);

void glPushMatrix(void);

void glPopMatrix(void);

void glLoadIdentity(void);

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

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

void glTexCoord2f(GLfloat s, GLfloat t);


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
		uint32 txr_address);

void glTexParameteri(GLenum target, GLenum pname, GLint param);

/* Lighting */
void glShadeModel(GLenum mode);

__END_DECLS

#endif	/* __GL_GL_H */

