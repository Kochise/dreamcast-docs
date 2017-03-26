/*
   Tiki

   plxcompat.h

   Copyright (C)2002,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_PLXCOMPAT_H
#define __TIKI_PLXCOMPAT_H

// These convenience methods are just an easier way to submit commands to
// OpenGL. These are based on Parallax's prim.h, matrix.h, and sprite.h files,
// and are mostly shortcut methods for porting old code.

#include "Tiki/color.h"
#include "Tiki/vector.h"
#include "Tiki/matrix.h"
#include "Tiki/glhdrs.h"

namespace Tiki {
namespace GL {

class Texture;

namespace Plxcompat {

////////////////////////////////////////////////////////////////////////////////////
// dr.h

typedef void * plx_dr_state_t;
static inline void plx_dr_init(plx_dr_state_t * t) { }

////////////////////////////////////////////////////////////////////////////////////
// context.h

/**
  Select a texture for use with the context system. If you delete the
  texture this has selected and then try to use contexts without
  setting another texture, you'll probably get some gross garbage
  on your output. Specify a NULL texture here to disable texturing.
 */
void plx_cxt_texture(Texture * txr);

/**
  Set the blending mode to use with the context. What's available is
  platform dependent, but we have defines for DC below.
 */
void plx_cxt_blending(int src, int dst);
// glBlendFunc

/* Constants for blending modes */
#define PLX_BLEND_ZERO		GL_ZERO
#define PLX_BLEND_ONE		GL_ONE
#define PLX_BLEND_DESTCOLOR	GL_DST_COLOR
#define PLX_BLEND_INVDESTCOLOR	GL_ONE_MINUS_DST_COLOR
#define PLX_BLEND_SRCALPHA	GL_SRC_ALPHA
#define PLX_BLEND_INVSRCALPHA	GL_ONE_MINUS_SRC_ALPHA
#define PLX_BLEND_DESTALPHA	GL_DST_ALPHA
#define PLX_BLEND_INVDESTALPHA	GL_ONE_MINUS_DST_ALPHA

/**
  Set the culling mode.
 */
void plx_cxt_culling(int type);
// glCullFace
// glFrontFace

/* Constants for culling modes */
#define PLX_CULL_NONE	GL_FRONT_AND_BACK	/**< Show everything */
#define PLX_CULL_CW	GL_BACK			/**< Remove clockwise polys */
#define PLX_CULL_CCW	GL_FRONT		/**< Remove counter-clockwise polys */

/**
  Submit the selected context for rendering.
 */
static inline void plx_cxt_send(int /*foo*/) { }


////////////////////////////////////////////////////////////////////////////////////
// matrix.h

// This isn't perfect but will catch most uses by client code.
typedef Matrix matrix_t;
typedef Vector vector_t;
typedef Vector point_t;

/* Copy the internal matrix out to a memory one */
void mat_store(matrix_t *out);

/* Copy a memory matrix into the internal one */
void mat_load(matrix_t *out);

/* Clear internal to an identity matrix */
void mat_identity();

/* "Apply" a matrix: multiply a matrix onto the "internal" one */
void mat_apply(matrix_t *src);

/* Transform zero or more sets of vectors using the current internal
   matrix. Each vector is three floats long. */
void mat_transform(vector_t *invecs, vector_t *outvecs, int veccnt, int vecskip);

/* Inline mat_transform which works on the three coordinates passed in;
   this works most efficiently if you've already got the three numbers
   (x,y,z) in the right registers (fr0,fr1,fr2). */
void mat_trans_single(float & x, float & y, float & z);

/* Same as above, but allows an input to and preserves the Z/W value */
void mat_trans_single4(float & x, float & y, float & z, float & w);

/* This is like mat_trans_single, but it leaves z/w instead of 1/w
   for the z component. */
void mat_trans_single3(float & x, float & y, float & z);

/* Transform vector, without any perspective division. */
void mat_trans_nodiv(float & x, float & y, float & z, float & w);

void mat_rotate_x(float r);
void mat_rotate_y(float r);
void mat_rotate_z(float r);
void mat_rotate(float xr, float yr, float zr);
void mat_translate(float x, float y, float z);
void mat_scale(float x, float y, float z);

static inline void plx_mat_store(matrix_t *out) { mat_store(out); }
static inline void plx_mat_load(matrix_t *out) { mat_load(out); }
static inline void plx_mat_identity() { mat_identity(); }
static inline void plx_mat_apply(matrix_t *src) { mat_apply(src); }
static inline void plx_mat_transform(vector_t *invecs, vector_t *outvecs, int veccnt, int vecskip)
	{ mat_transform(invecs, outvecs, veccnt, vecskip); }
static inline void plx_mat_tfip_3d(float & x, float & y, float & z) { mat_trans_single(x, y, z); }
static inline void plx_mat_tfip_3dw(float & x, float & y, float & z, float & w) { mat_trans_single4(x, y, z, w); }
static inline void plx_mat_tfip_2d(float & x, float & y, float & z) { mat_trans_single3(x, y, z); }

static inline void plx_mat_rotate_x(float r) { mat_rotate_x(r); }
static inline void plx_mat_rotate_y(float r) { mat_rotate_y(r); }
static inline void plx_mat_rotate_z(float r) { mat_rotate_z(r); }
static inline void plx_mat_rotate(float xr, float yr, float zr) { mat_rotate(xr, yr, zr); }
static inline void plx_mat_translate(float x, float y, float z) { mat_translate(x, y, z); }
static inline void plx_mat_scale(float x, float y, float z) { mat_scale(x, y, z); }

/* The 3D matrix operations, somewhat simplified from KGL. All of these use
   the matrix regs, but do not primarily keep their values in them. To get
   the values out into the matrix regs (and usable) you'll want to set
   everything up and then call plx_mat3d_apply(). */

/** Call before doing anything else, or after switching video
    modes to setup some basic parameters. */
void plx_mat3d_init(int width, int height);

/** Set which matrix we are working on */
void plx_mat3d_mode(int mode);

/* Constants for plx_mat3d_mode and plx_mat3d_apply */
static const int PLX_MAT_PROJECTION = 0;
static const int PLX_MAT_MODELVIEW = 1;
static const int PLX_MAT_SCREENVIEW = 2;
static const int PLX_MAT_SCRATCH = 3;
static const int PLX_MAT_WORLDVIEW = 4;
static const int PLX_MAT_COUNT = 5;

/** Load an identity matrix */
void plx_mat3d_identity();

/** Load a raw matrix */
void plx_mat3d_load(matrix_t * src);

/** Save a raw matrix */
void plx_mat3d_store(matrix_t * src);

/** Setup viewport parameters */
void plx_mat3d_viewport(int x1, int y1, int width, int height);

void plx_mat3d_depthrange(float n, float f);

/** Setup a perspective matrix */
void plx_mat3d_perspective(float angle, float aspect, float znear, float zfar);

/** Setup a frustum matrix */
void plx_mat3d_frustum(float left, float right, float bottom, float top, float znear, float zfar);

/** Push a matrix on the stack */
void plx_mat3d_push();

/** Pop a matrix from the stack and reload it */
void plx_mat3d_pop();

/** Reload a matrix from the top of the stack, but don't pop it */
void plx_mat3d_peek();

/** Rotation */
void plx_mat3d_rotate(float angle, float x, float y, float z);

/** Scaling */
void plx_mat3d_scale(float x, float y, float z);

/** Translation */
void plx_mat3d_translate(float x, float y, float z);

/** Do a camera "look at" */
void plx_mat3d_lookat(const point_t * eye, const point_t * center, const vector_t * up);

/** Apply a matrix from one of the matrix modes to the matrix regs */
void plx_mat3d_apply(int mode);

/** Manually apply a matrix */
void plx_mat3d_apply_mat(matrix_t * src);

/** Apply all the matrices for a normal 3D scene */
void plx_mat3d_apply_all();


////////////////////////////////////////////////////////////////////////////////////
// prim.h

static const int PLX_VERT = 0;
static const int PLX_VERT_EOS = 1;

typedef struct {
	int     flags;
	float   x, y, z;
	float   u, v;
	uint32  argb;
	uint32  oargb;		// no one is using this.. probably..
} plx_vertex_t;

// Incoming Z coords will be divided by this number, to ensure they
// stay inside the ortho depth limits.
static const float zscale = 1000.0f;

#define PRIMPRE() do { \
	if (!stripping) \
		glBegin(GL_TRIANGLE_STRIP); \
} while(0)

#define PRIMPOST(flags) do { \
	if (flags == PLX_VERT_EOS) { \
		glEnd(); \
		stripping = false; \
	} else { \
		stripping = true; \
	} \
} while(0)

static inline void glColoru32(uint32 argb) {
	uint8 r = (uint8)((argb >> 16) & 0xff);
	uint8 g = (uint8)((argb >> 8) & 0xff);
	uint8 b = (uint8)((argb >> 0) & 0xff);
	uint8 a = (uint8)((argb >> 24) & 0xff);
#if TIKI_PLAT != TIKI_NDS
	glColor4ub(r, g, b, a);
#else
	glColor3f(r, g, b);
#endif
}

// This function will handle the meat of the Parallax emulation. Note
// that it's invalid with this design to have cross-module vertex submission
// within a single strip, but that generally shouldn't be happening anyway.
static bool stripping = false;
static inline void plx_prim(plx_vertex_t * vert, int size = 0) {
	PRIMPRE();
	glColoru32(vert->argb);
	glTexCoord2f(vert->u, vert->v);
	glVertex3f(vert->x, vert->y, vert->z / zscale);
	PRIMPOST(vert->flags);
}

void plx_xform(float & x, float & y, float & z);
static inline void plx_xform(plx_vertex_t * vert) {
	plx_xform(vert->x, vert->y, vert->z);
}
static inline uint32 plx_pack_color(float a, float r, float g, float b) {
	return Color::pack(a, r, g, b);
}


/**
  This simple primitive function will fill a vertex structure for
  you from parameters. It uses floating point numbers for the color
  values and no u/v coordinates. The "vert" parameter may be a DR target.
 */
static inline void plx_vert_fnn(plx_vertex_t * vert, int flags, float x, float y, float z,
	float a, float r, float g, float b)
{
	vert->flags = flags;
	vert->x = x;
	vert->y = y;
	vert->z = z;
	vert->u = vert->v = 0.0f;
	vert->argb = plx_pack_color(a, r, g, b);
	vert->oargb = 0;
}

/**
  Like plx_vert_fnn, but it takes a pre-packed integer color value.
 */
static inline void plx_vert_inn(plx_vertex_t * vert, int flags, float x, float y, float z,
	uint32 color)
{
	vert->flags = flags;
	vert->x = x;
	vert->y = y;
	vert->z = z;
	vert->u = vert->v = 0.0f;
	vert->argb = color;
	vert->oargb = 0;
}

/**
  Like plx_vert_fnn, but it takes u/v texture coordinates as well.
 */
static inline void plx_vert_ffn(plx_vertex_t * vert, int flags, float x, float y, float z,
	float a, float r, float g, float b, float u, float v)
{
	vert->flags = flags;
	vert->x = x;
	vert->y = y;
	vert->z = z;
	vert->u = u;
	vert->v = v;
	vert->argb = plx_pack_color(a, r, g, b);
	vert->oargb = 0;
}

/**
  Like plx_vert_fnn, but it takes u/v texture coordinates and a pre-packed integer
  color value.
 */
static inline void plx_vert_ifn(plx_vertex_t * vert, int flags, float x, float y, float z,
	uint32 color, float u, float v)
{
	vert->flags = flags;
	vert->x = x;
	vert->y = y;
	vert->z = z;
	vert->u = u;
	vert->v = v;
	vert->argb = color;
	vert->oargb = 0;
}

/****************************************************** PLX_PRIM VERTEX ****/
// In PX, these are pretty much all implemented as GL at the low level.

/**
  Like plx_vert_fnp, but submits the point using plx_prim.
 */
static inline void plx_vert_fnp(int flags, float x, float y, float z, float a, float r, float g, float b) {
	PRIMPRE();
#if TIKI_PLAT != TIKI_NDS
	glColor4f(r, g, b, a);
#else
	glColor3f(r, g, b);
#endif
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/**
  Like plx_vert_inn, but submits the point using plx_prim.
 */
static inline void plx_vert_inp(int flags, float x, float y, float z, uint32 color) {
	PRIMPRE();
	glColoru32(color);
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/**
  Like plx_vert_indm3, but uses plx_prim.
 */
static inline void plx_vert_inpm3(int flags, float x, float y, float z, uint32 color) {
	PRIMPRE();
	glColoru32(color);
	plx_xform(x, y, z);
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/**
  Like plx_vert_ifpm3, but uses plx_prim.
 */
static inline void plx_vert_ifpm3(int flags, float x, float y, float z, uint32 color, float u, float v) {
	PRIMPRE();
	glColoru32(color);
	glTexCoord2f(u, v);
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/**
  Like plx_vert_ffn, but submits the point using plx_prim.
 */
static inline void plx_vert_ffp(int flags, float x, float y, float z,
	float a, float r, float g, float b, float u, float v)
{
	PRIMPRE();
#if TIKI_PLAT != TIKI_NDS
	glColor4f(r, g, b, a);
#else
	glColor3f(r, g, b);
#endif
	glTexCoord2f(u, v);
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/**
  Like plx_vert_ifn, but submits the point using plx_prim.
 */
static inline void plx_vert_ifp(int flags, float x, float y, float z, uint32 color, float u, float v) {
	PRIMPRE();
	glColoru32(color);
	glTexCoord2f(u, v);
	glVertex3f(x, y, z / zscale);
	PRIMPOST(flags);
}

/********************************************************* DR VERTEX ****/
// In PX, these are just wrappers for the p versions.

/**
  Like plx_vert_fnn, but submits the point using DR.
 */
static inline void plx_vert_fnd(plx_dr_state_t * state, int flags, float x, float y, float z,
	float a, float r, float g, float b)
{
	plx_vert_fnp(flags, x, y, z, a, r, g, b);
}

/**
  Like plx_vert_inn, but submits the point using DR.
 */
static inline void plx_vert_ind(plx_dr_state_t * state, int flags, float x, float y, float z,
	uint32 color)
{
	plx_vert_inp(flags, x, y, z, color);
}

/**
  Like plx_vert_ffn, but submits the point using DR.
 */
static inline void plx_vert_ffd(plx_dr_state_t * state, int flags, float x, float y, float z,
	float a, float r, float g, float b, float u, float v)
{
	plx_vert_ffp(flags, x, y, z, a, r, g, b, u, v);
}

/**
  Like plx_vert_ifn, but submits the point using DR.
 */
static inline void plx_vert_ifd(plx_dr_state_t * state, int flags, float x, float y, float z,
	uint32 color, float u, float v)
{
	plx_vert_ifp(flags, x, y, z, color, u, v);
}

/**
  Like plx_vert_ind, but also transforms via the active matrices for 3D
 */
static inline void plx_vert_indm3(plx_dr_state_t * state, int flags, float x, float y, float z,
	uint32 color)
{
	plx_vert_inpm3(flags, x, y, z, color);
}

/**
  Like plx_vert_ifd, but also transforms via the active matrices for 3D
 */
static inline void plx_vert_ifdm3(plx_dr_state_t * state, int flags, float x, float y, float z,
	uint32 color, float u, float v)
{
	plx_vert_ifpm3(flags, x, y, z, color, u, v);
}


////////////////////////////////////////////////////////////////////////////////////
// sprite.h

/**
  Submit a quad using the given coordinates, color, and UV values via
  DR. The coordinates are at the center point.
 */
static inline void plx_spr_fnd(plx_dr_state_t * state,
	float wi, float hi,
	float x, float y, float z,
	float a, float r, float g, float b)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	plx_vert_ffd(state, PLX_VERT,
		x - w, y + h, z,
		a, r, g, b,
		0.0f, 1.0f);
	plx_vert_ffd(state, PLX_VERT,
		x - w, y - h, z,
		a, r, g, b,
		0.0f, 0.0f);
	plx_vert_ffd(state, PLX_VERT,
		x + w, y + h, z,
		a, r, g, b,
		1.0f, 1.0f);
	plx_vert_ffd(state, PLX_VERT_EOS,
		x + w, y - h, z,
		a, r, g, b,
		1.0f, 0.0f);
}

/**
  Like plx_spr_fnd, but with integer color.
 */
static inline void plx_spr_ind(plx_dr_state_t * state,
	float wi, float hi,
	float x, float y, float z,
	uint32 color)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	plx_vert_ifd(state, PLX_VERT,
		x - w, y + h, z,
		color,
		0.0f, 1.0f);
	plx_vert_ifd(state, PLX_VERT,
		x - w, y - h, z,
		color,
		0.0f, 0.0f);
	plx_vert_ifd(state, PLX_VERT,
		x + w, y + h, z,
		color,
		1.0f, 1.0f);
	plx_vert_ifd(state, PLX_VERT_EOS,
		x + w, y - h, z,
		color,
		1.0f, 0.0f);
}

/**
  Like plx_spr_fnd, but using matrix math.
 */
static inline void plx_spr_fmd(plx_dr_state_t * state,
	float wi, float hi,
	float xi, float yi, float zi,
	float a, float r, float g, float b)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	float x, y, z;

	x = xi-w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffd(state, PLX_VERT,
		x, y, z,
		a, r, g, b,
		0.0f, 1.0f);

	x = xi-w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffd(state, PLX_VERT,
		x, y, z,
		a, r, g, b,
		0.0f, 0.0f);

	x = xi+w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffd(state, PLX_VERT,
		x, y, z,
		a, r, g, b,
		1.0f, 1.0f);

	x = xi+w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffd(state, PLX_VERT_EOS,
		x, y, z,
		a, r, g, b,
		1.0f, 0.0f);
}

/**
  Like plx_spr_fmd, but using integer colors.
 */
static inline void plx_spr_imd(plx_dr_state_t * state,
	float wi, float hi,
	float xi, float yi, float zi,
	uint32 color)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	float x, y, z;

	x = xi-w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifd(state, PLX_VERT,
		x, y, z,
		color,
		0.0f, 1.0f);

	x = xi-w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifd(state, PLX_VERT,
		x, y, z,
		color,
		0.0f, 0.0f);

	x = xi+w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifd(state, PLX_VERT,
		x, y, z,
		color,
		1.0f, 1.0f);

	x = xi+w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifd(state, PLX_VERT_EOS,
		x, y, z,
		color,
		1.0f, 0.0f);
}

/**************************************************** PVR_PRIM VERSIONS ***/

/**
  Like plx_spr_fnd, but using pvr_prim.
 */
static inline void plx_spr_fnp(
	float wi, float hi,
	float x, float y, float z,
	float a, float r, float g, float b)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	plx_vert_ffp(PLX_VERT,
		x - w, y + h, z,
		a, r, g, b,
		0.0f, 1.0f);
	plx_vert_ffp(PLX_VERT,
		x - w, y - h, z,
		a, r, g, b,
		0.0f, 0.0f);
	plx_vert_ffp(PLX_VERT,
		x + w, y + h, z,
		a, r, g, b,
		1.0f, 1.0f);
	plx_vert_ffp(PLX_VERT_EOS,
		x + w, y - h, z,
		a, r, g, b,
		1.0f, 0.0f);
}

/**
  Like plx_spr_ind, but using pvr_prim.
 */
static inline void plx_spr_inp(
	float wi, float hi,
	float x, float y, float z,
	uint32 color)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	plx_vert_ifp(PLX_VERT,
		x - w, y + h, z,
		color,
		0.0f, 1.0f);
	plx_vert_ifp(PLX_VERT,
		x - w, y - h, z,
		color,
		0.0f, 0.0f);
	plx_vert_ifp(PLX_VERT,
		x + w, y + h, z,
		color,
		1.0f, 1.0f);
	plx_vert_ifp(PLX_VERT_EOS,
		x + w, y - h, z,
		color,
		1.0f, 0.0f);
}

/**
  Like plx_spr_fmd, but using pvr_prim.
 */
static inline void plx_spr_fmp(
	float wi, float hi,
	float xi, float yi, float zi,
	float a, float r, float g, float b)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	float x, y, z;

	x = xi-w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffp(PLX_VERT,
		x, y, z,
		a, r, g, b,
		0.0f, 1.0f);

	x = xi-w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffp(PLX_VERT,
		x, y, z,
		a, r, g, b,
		0.0f, 0.0f);

	x = xi+w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffp(PLX_VERT,
		x, y, z,
		a, r, g, b,
		1.0f, 1.0f);

	x = xi+w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ffp(PLX_VERT_EOS,
		x, y, z,
		a, r, g, b,
		1.0f, 0.0f);
}

/**
  Like plx_spr_imd, but using pvr_prim.
 */
static inline void plx_spr_imp(
	float wi, float hi,
	float xi, float yi, float zi,
	uint32 color)
{
	float w = wi / 2.0f;
	float h = hi / 2.0f;
	float x, y, z;

	x = xi-w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifp(PLX_VERT,
		x, y, z,
		color,
		0.0f, 1.0f);

	x = xi-w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifp(PLX_VERT,
		x, y, z,
		color,
		0.0f, 0.0f);

	x = xi+w; y = yi+h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifp(PLX_VERT,
		x, y, z,
		color,
		1.0f, 1.0f);

	x = xi+w; y = yi-h; z = zi;
	plx_mat_tfip_2d(x, y, z);
	plx_vert_ifp(PLX_VERT_EOS,
		x, y, z,
		color,
		1.0f, 0.0f);
}


}
}
}

#endif	// __TIKI_PLXCOMPAT_H

