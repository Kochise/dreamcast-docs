/*
   Tiki

   plxcompat.cpp

   Copyright (C)2001,2002,2004 Dan Potter
   Copyright (C)2002 Benoit Miller and Paul Boese
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include <assert.h>
#include <string.h>

#include "Tiki/plxcompat.h"
#include "Tiki/tikimath.h"
#include "Tiki/glhdrs.h"
#include "Tiki/texture.h"

using namespace Tiki;
using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;
using namespace Tiki::Math;

#ifndef assert_msg
#define assert_msg(x, y) assert(x)
#endif

////////////////////////////////////////////////////////////////////

void Plxcompat::plx_cxt_texture(Texture * txr) {
	if (txr)
		txr->select();
	else
		Texture::deselect();
}

void Plxcompat::plx_cxt_blending(int src, int dst) {
#if TIKI_PLAT != TIKI_NDS
	glBlendFunc(src, dst);
#endif
}

void Plxcompat::plx_cxt_culling(int type) {
#if TIKI_PLAT != TIKI_NDS
	glCullFace(type);
	glFrontFace(GL_CCW);
#endif
}

/////////////////////////////////////////////////////////////////////

/*
  Most of this file was pulled from KGL's gltrans.c. Why did we do that
  instead of just suggesting linking with KGL to get them? Because:

  1) There are things KGL does that aren't really necessary or germane
     for non-KGL usage, and you're trying to avoid initializing all
     of KGL, right? :)
  2) KGL is a work in progress and is attempting over time to become
     more and more GL compliant. On the other hand, we just want simple
     and working 3D matrix functions.
 */


/* Degrees<->Radians conversion */
#define DEG2RAD ((float)M_PI / 180.0f)
#define RAD2DEG (180.0f / (float)M_PI)

/* Matrix stacks */
#define MAT_MV_STACK_CNT 32
#define MAT_P_STACK_CNT 2
static matrix_t mat_mv_stack[MAT_MV_STACK_CNT];
static int mat_mv_stack_top;
static matrix_t mat_p_stack[MAT_P_STACK_CNT];
static int mat_p_stack_top;

/* Active mode matrices */
static int matrix_mode;
static matrix_t trans_mats[PLX_MAT_COUNT];

/* Screenview parameters */
static vector_t vp, vp_size, vp_scale, vp_offset;
static float vp_z_fudge;
static float depthrange_near, depthrange_far;

/* Set which matrix we are working on */
void Plxcompat::plx_mat3d_mode(int mode) {
	matrix_mode = mode;
}

/* Load the identitiy matrix */
void Plxcompat::plx_mat3d_identity() {
	mat_identity();
	mat_store(trans_mats + matrix_mode);
}

/* Load an arbitrary matrix */
void Plxcompat::plx_mat3d_load(matrix_t * m) {
	memcpy(trans_mats + matrix_mode, m, sizeof(matrix_t));
}

/* Save the matrix (whoa!) */
void Plxcompat::plx_mat3d_store(matrix_t * m) {
	memcpy(m, trans_mats + matrix_mode, sizeof(matrix_t));
}

/* Set the depth range */
void Plxcompat::plx_mat3d_depthrange(float n, float f) {
	/* clamp the values... */
	if (n < 0.0f) n = 0.0f;
	if (n > 1.0f) n = 1.0f;
	if (f < 0.0f) f = 0.0f;
	if (f > 1.0f) f = 1.0f;

	depthrange_near = n;
	depthrange_far = f;

	/* Adjust the viewport scale and offset for Z */
	vp_scale.z = ((f - n) / 2.0f);
	vp_offset.z = (n + f) / 2.0f;
}

/* Set the viewport */
void Plxcompat::plx_mat3d_viewport(int x1, int y1, int width, int height) {
	vp.x = (float)x1;
	vp.y = (float)y1;
	vp_size.x = (float)width;
	vp_size.y = (float)height;

	/* Calculate the viewport scale and offset */
	vp_scale.x = (float)width / 2.0f;
	vp_offset.x = vp_scale.x + (float)x1;
	vp_scale.y = (float)height / 2.0f;
	vp_offset.y = vp_scale.y + (float)y1;
	vp_scale.z = (depthrange_far -depthrange_near) / 2.0f;
	vp_offset.z = (depthrange_near + depthrange_far) / 2.0f;

	/* FIXME: Why does the depth value need some nudging?
         * This makes polys with Z=0 work.
	 */
	vp_offset.z += 0.0001f;
}

/* Setup perspective */
void Plxcompat::plx_mat3d_perspective(float angle, float aspect, 
	float znear, float zfar)
{
	float xmin, xmax, ymin, ymax;

	ymax = znear * ftan(angle * F_PI / 360.0f);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	plx_mat3d_frustum(xmin, xmax, ymin, ymax, znear, zfar);
}

static float mf_init[] = {
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 0.0f, 0.0f
};
static matrix_t mf(mf_init);

void Plxcompat::plx_mat3d_frustum(float left, float right,
	float bottom, float top,
	float znear, float zfar)
{
	float x, y, a, b, c, d;

	assert(znear > 0.0f);
	x = (2.0f * znear) / (right - left);
	y = (2.0f * znear) / (top - bottom);
	a = (right + left) / (right - left);
	b = (top + bottom) / (top - bottom);
	c = -(zfar + znear) / (zfar - znear);
	d = -(2.0f * zfar * znear) / (zfar - znear);

	mf.matrix[0][0] = x;
	mf.matrix[2][0] = a;
	mf.matrix[1][1] = y;
	mf.matrix[2][1] = b;
	mf.matrix[2][2] = c;
	mf.matrix[3][2] = d;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&mf);
	mat_store(trans_mats + matrix_mode);
}

void Plxcompat::plx_mat3d_push() {
	switch (matrix_mode)
	{
	case PLX_MAT_MODELVIEW:
		assert_msg(mat_mv_stack_top < MAT_MV_STACK_CNT, "Modelview stack overflow.");
		if (mat_mv_stack_top >= MAT_MV_STACK_CNT) return;

		memcpy(mat_mv_stack + mat_mv_stack_top,
			trans_mats + matrix_mode,
			sizeof(matrix_t));
		mat_mv_stack_top++;
		break;
	case PLX_MAT_PROJECTION:
		assert_msg(mat_p_stack_top < MAT_P_STACK_CNT, "Projection stack overflow.");
		if (mat_p_stack_top >= MAT_P_STACK_CNT) return;

		memcpy(mat_p_stack + mat_p_stack_top,
			trans_mats + matrix_mode,
			sizeof(matrix_t));
		mat_p_stack_top++;
		break;
	default:
		assert_msg( 0, "Invalid matrix type" );
	}
}

void Plxcompat::plx_mat3d_pop() {
	switch(matrix_mode)
	{
	case PLX_MAT_MODELVIEW:
		assert_msg(mat_mv_stack_top > 0, "Modelview stack underflow.");
		if (mat_mv_stack_top <= 0) return;

		mat_mv_stack_top--;
		memcpy(trans_mats + matrix_mode,
			mat_mv_stack + mat_mv_stack_top,
			sizeof(matrix_t));
		break;
	case PLX_MAT_PROJECTION:
		assert_msg(mat_p_stack_top > 0, "Projection stack underflow.");
		if (mat_p_stack_top <= 0) return;

		mat_p_stack_top--;
		memcpy(trans_mats + matrix_mode,
			mat_p_stack + mat_p_stack_top,
			sizeof(matrix_t));
		break;
	default:
		assert_msg( 0, "Invalid matrix type" );
	}
}

void Plxcompat::plx_mat3d_peek() {
	switch(matrix_mode)
	{
	case PLX_MAT_MODELVIEW:
		assert_msg(mat_mv_stack_top > 0, "Modelview stack underflow.");
		if (mat_mv_stack_top <= 0) return;

		memcpy(trans_mats + matrix_mode,
			mat_mv_stack + mat_mv_stack_top - 1,
			sizeof(matrix_t));
		break;
	case PLX_MAT_PROJECTION:
		assert_msg(mat_p_stack_top > 0, "Projection stack underflow.");
		if (mat_p_stack_top <= 0) return;

		memcpy(trans_mats + matrix_mode,
			mat_p_stack + mat_p_stack_top - 1,
			sizeof(matrix_t));
		break;
	default:
		assert_msg( 0, "Invalid matrix type" );
	}
}

static float mr_init[] = {
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t mr(mr_init);

void Plxcompat::plx_mat3d_rotate(float angle, float x, float y, float z) {
	float rcos = fcos(angle * DEG2RAD);
	float rsin = fsin(angle * DEG2RAD);
	float invrcos = (1.0f - rcos);
	float mag = fsqrt(x*x + y*y + z*z);
	float xx, yy, zz, xy, yz, zx;

	if (mag < 1.0e-6) {
		/* Rotation vector is too small to be significant */
		return;
	}

	/* Normalize the rotation vector */
	x /= mag;
	y /= mag;
	z /= mag;

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = (x * y * invrcos);
	yz = (y * z * invrcos);
	zx = (z * x * invrcos);

	/* Generate the rotation matrix */
	mr.matrix[0][0] = xx + rcos * (1.0f - xx);
	mr.matrix[2][1] = yz - x * rsin;
	mr.matrix[1][2] = yz + x * rsin;

	mr.matrix[1][1] = yy + rcos * (1.0f - yy);
	mr.matrix[2][0] = zx + y * rsin;
	mr.matrix[0][2] = zx - y * rsin;

	mr.matrix[2][2] = zz + rcos * (1.0f - zz);
	mr.matrix[1][0] = xy - z * rsin;
	mr.matrix[0][1] = xy + z * rsin;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&mr);
	mat_store(trans_mats + matrix_mode);
}

static float ms_init[] = {
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t ms(ms_init);

void Plxcompat::plx_mat3d_scale(float x, float y, float z) {
        ms.matrix[0][0] = x;
	ms.matrix[1][1] = y;
	ms.matrix[2][2] = z;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&ms);
	mat_store(trans_mats + matrix_mode);
}

static float mt_init[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t mt(mt_init);

void Plxcompat::plx_mat3d_translate(float x, float y, float z) {
	mt.matrix[3][0] = x;
	mt.matrix[3][1] = y;
	mt.matrix[3][2] = z;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&mt);
	mat_store(trans_mats + matrix_mode);
}

static void normalize(vector_t * p) {
	float r;

	r = fsqrt( p->x*p->x + p->y*p->y + p->z*p->z );
	if (r == 0.0) return;

	p->x /= r;
	p->y /= r;
	p->z /= r;
}

static void cross(const vector_t * v1, const vector_t * v2, vector_t * r) {
	r->x = v1->y*v2->z - v1->z*v2->y;
	r->y = v1->z*v2->x - v1->x*v2->z;
	r->z = v1->x*v2->y - v1->y*v2->x;
}

static float ml_init[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t ml(ml_init);

void Plxcompat::plx_mat3d_lookat(const point_t * eye, const point_t * center, const vector_t * upi) {
	point_t forward, side, up;

	forward.x = center->x - eye->x;
	forward.y = center->y - eye->y;
	forward.z = center->z - eye->z;

	up.x = upi->x;
	up.y = upi->y;
	up.z = upi->z;

	normalize(&forward);

	/* Side = forward x up */
	cross(&forward, &up, &side);
	normalize(&side);

	/* Recompute up as: up = side x forward */
	cross(&side, &forward, &up);

	ml.matrix[0][0] = side.x;
	ml.matrix[1][0] = side.y;
	ml.matrix[2][0] = side.z;

	ml.matrix[0][1] = up.x;
	ml.matrix[1][1] = up.y;
	ml.matrix[2][1] = up.z;

	ml.matrix[0][2] = -forward.x;
	ml.matrix[1][2] = -forward.y;
	ml.matrix[2][2] = -forward.z;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&ml);
	mat_translate(-eye->x, -eye->y, -eye->z);
	mat_store(trans_mats + matrix_mode);
}

static float msv_init[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t msv(msv_init);

/* Apply a matrix */
void Plxcompat::plx_mat3d_apply(int mode) {
	if (mode != PLX_MAT_SCREENVIEW) {
		mat_apply(trans_mats + mode);
	} else {
		msv.matrix[0][0] = vp_scale.x;
		msv.matrix[1][1] = -vp_scale.y;
		msv.matrix[3][0] = vp_offset.x;
		msv.matrix[3][1] = vp_size.y - vp_offset.y;
		mat_apply(&msv);
	}
}

static float mam_init[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static matrix_t mam(mam_init);

void Plxcompat::plx_mat3d_apply_mat(matrix_t * mat) {
	memcpy(&mam, mat, sizeof(matrix_t));
	mat_load(trans_mats + matrix_mode);
	mat_apply(&mam);
	mat_store(trans_mats + matrix_mode);
}

void Plxcompat::plx_mat3d_apply_all() {
	mat_identity();

	msv.matrix[0][0] = vp_scale.x;
	msv.matrix[1][1] = -vp_scale.y;
	msv.matrix[3][0] = vp_offset.x;
	msv.matrix[3][1] = vp_size.y - vp_offset.y;
	mat_apply(&msv);

	mat_apply(trans_mats + PLX_MAT_PROJECTION);
	mat_apply(trans_mats + PLX_MAT_WORLDVIEW);
	mat_apply(trans_mats + PLX_MAT_MODELVIEW);
}

/* Init */
void Plxcompat::plx_mat3d_init(int width, int height) {
	int i;

	/* Setup all the matrices */
	mat_identity();
	for (i=0; i<PLX_MAT_COUNT; i++)
		mat_store(trans_mats + i);
	matrix_mode = PLX_MAT_PROJECTION;
	mat_mv_stack_top = 0;
	mat_p_stack_top = 0;

	/* Setup screen w&h */
	plx_mat3d_depthrange(0.0f, 1.0f);
	plx_mat3d_viewport(0, 0, width, height);
	vp_z_fudge = 0.0f;
}


//////////////////////////////////////////////////////////////////////////////////



/*
static float zscale = 1000.0f;
static int stripping = 0;
void Plxcompat::plx_prim(plx_vertex_t * vert, int size) {
	if (!stripping)
		glBegin(GL_TRIANGLE_STRIP);
	uint8 r = (uint8)((vert->argb >> 16) & 0xff);
	uint8 g = (uint8)((vert->argb >> 8) & 0xff);
	uint8 b = (uint8)((vert->argb >> 0) & 0xff);
	uint8 a = (uint8)((vert->argb >> 24) & 0xff);
	glColor4ub(r, g, b, a);
	glTexCoord2f(vert->u, vert->v);
	glVertex3f(vert->x, vert->y, vert->z / zscale);
	stripping = 1;
	if (vert->flags == PLX_VERT_EOS) {
		glEnd();
		stripping = 0;
	}
} */

static matrix_t g_mat;

void Plxcompat::mat_identity() {
	memset(&g_mat, 0, sizeof(matrix_t));
	g_mat.matrix[0][0] = 1.0f;
	g_mat.matrix[1][1] = 1.0f;
	g_mat.matrix[2][2] = 1.0f;
	g_mat.matrix[3][3] = 1.0f;
}

#define mat_mult(mat, inputw) \
	float ix = x, iy = y, iz = z, iw = (inputw); \
	float nx, ny, nz, nw; \
	nx = ix * mat.matrix[0][0] + iy * mat.matrix[1][0] + iz * mat.matrix[2][0] + iw * mat.matrix[3][0]; \
	ny = ix * mat.matrix[0][1] + iy * mat.matrix[1][1] + iz * mat.matrix[2][1] + iw * mat.matrix[3][1]; \
	nz = ix * mat.matrix[0][2] + iy * mat.matrix[1][2] + iz * mat.matrix[2][2] + iw * mat.matrix[3][2]; \
	nw = ix * mat.matrix[0][3] + iy * mat.matrix[1][3] + iz * mat.matrix[2][3] + iw * mat.matrix[3][3];

void Plxcompat::mat_trans_single(float & x, float & y, float & z) {
	mat_mult(g_mat, 1.0f);
	if (nw == 0.0f)
		nw = 1.0f;
	z = 1.0f / nw;
	x = nx * z;
	y = ny * z;
}

void Plxcompat::plx_xform(float & x, float & y, float & z) {
	mat_trans_single(x, y, z);
}

void Plxcompat::mat_trans_single3(float & x, float & y, float & z) {
	mat_mult(g_mat, 1.0f);
	if (nw == 0.0f)
		nw = 1.0f;
	iw = 1.0f / nw;
	x = nx * iw;
	y = ny * iw;
	z = nz * iw;
}

void Plxcompat::mat_trans_single4(float & x, float & y, float & z, float & w) {
	mat_mult(g_mat, 1.0f);
	if (nw == 0.0f)
		nw = 1.0f;
	iw = 1.0f / nw;
	x = nx * iw;
	y = ny * iw;
	z = nz * iw;
	w = iw;
}

void Plxcompat::mat_trans_nodiv(float & x, float & y, float & z, float & w) {
	mat_mult(g_mat, w);
	x = nx;
	y = ny;
	z = nz;
	w = nw;
}

void Plxcompat::mat_apply(matrix_t * mat) {
	matrix_t nm;

	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			nm.matrix[i][j] = 0;
			for (int k=0; k<4; k++)
				nm.matrix[i][j] += mat->matrix[i][k] * g_mat.matrix[k][j];
		}
	}
	
	mat_load(&nm);
}

void Plxcompat::mat_load(matrix_t * mat) {
	memcpy(&g_mat, mat, sizeof(matrix_t));
}

void Plxcompat::mat_store(matrix_t * mat) {
	memcpy(mat, &g_mat, sizeof(matrix_t));
}

void Plxcompat::mat_scale(float xs, float ys, float zs) {
	float sc_m_init[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	matrix_t sc_m(sc_m_init);
	sc_m.matrix[0][0] = xs;
	sc_m.matrix[1][1] = ys;
	sc_m.matrix[2][2] = zs;
	mat_apply(&sc_m);
}

void Plxcompat::mat_translate(float x, float y, float z) {
	float mt_init[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	matrix_t mt(mt_init);
	mt.matrix[3][0] = x;
	mt.matrix[3][1] = y;
	mt.matrix[3][2] = z;

	mat_apply(&mt);
}

void Plxcompat::mat_rotate_z(float r) {
	float rz_m_init[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	matrix_t rz_m(rz_m_init);
	rz_m.matrix[0][0] = rz_m.matrix[1][1] = fcos(r);
	rz_m.matrix[1][0] = fsin(r);
	rz_m.matrix[0][1] = -fsin(r);
	mat_apply(&rz_m);
}

void Plxcompat::mat_transform(vector_t *invecs, vector_t *outvecs, int veccnt, int vecskip) {
	for (int i=0; i<veccnt; i++) {
		*outvecs = *invecs;
		mat_trans_single(
			outvecs->x,
			outvecs->y,
			outvecs->z);
		invecs = (vector_t *)(((uint8 *)invecs) + vecskip);
		outvecs = (vector_t *)(((uint8 *)outvecs) + vecskip);
	}
}






