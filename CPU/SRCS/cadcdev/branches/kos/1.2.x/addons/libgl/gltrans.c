/* KallistiGL for KOS ##version##

   gltrans.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"

#include <assert.h>
#include <string.h>
#include <dc/fmath.h>
#include <dc/matrix.h>

CVSID("$Id: gltrans.c,v 1.13 2002/09/05 07:36:23 bardtx Exp $");

/* Transformation APIs */

/* Modus operandi, as it were

The transformation API will store N matrices, representing the various
GL matrix modes (projection, modelview, texture) and gl_matrix_mode will
point to the currently selected on. All matrix operations will load the matrix
from its array position, perform the math on that matrix, and store it back
into the array.

When gldraw() uses the matrices, it will pull the matrices it needs and
multiply them out in registers before applying them to vectors.

*/

#define DEG2RAD (F_PI / 180.0f)
#define RAD2DEG (180.0f / F_PI)

/* Matrix stacks (move to global?) */
#define MAT_MV_STACK_CNT 32
#define MAT_P_STACK_CNT 2
#define MAT_T_STACK_CNT 2
static matrix_t gl_mat_mv_stack[MAT_MV_STACK_CNT] __attribute__((aligned(32)));
static int gl_mat_mv_stack_top = 0;
static matrix_t gl_mat_p_stack[MAT_P_STACK_CNT] __attribute__((aligned(32)));
static int gl_mat_p_stack_top = 0;
static matrix_t gl_mat_t_stack[MAT_T_STACK_CNT] __attribute__((aligned(32)));
static int gl_mat_t_stack_top = 0;

/* Frustum stack */
static gl_frustum_t gl_frustum_stack[MAT_P_STACK_CNT];
static int gl_frustum_stack_top = 0;

/* Set which matrix we are working on */
void glMatrixMode(GLenum mode) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	gl_matrix_mode = mode;
	gl_matrix_dirty = GL_TRUE;
}

/* Load the identitiy matrix */
void glLoadIdentity(void) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	mat_identity();
	mat_store(gl_trans_mats + gl_matrix_mode);
	gl_matrix_dirty = GL_TRUE;
}

static matrix_t ml __attribute__((aligned(32)));

/* Load an arbitrary matrix */
void glLoadMatrixf(const GLfloat *m) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	memcpy(ml, m, sizeof(matrix_t));

	mat_load(&ml);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

/* Load an arbitrary transposed matrix */
void glLoadTransposeMatrixf(const GLfloat *m) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	ml[0][0] = m[0];
	ml[0][1] = m[4];
	ml[0][2] = m[8];
	ml[0][3] = m[12];
	ml[1][0] = m[1];
	ml[1][1] = m[5];
	ml[1][2] = m[9];
	ml[1][3] = m[13];
	ml[2][0] = m[2];
	ml[2][1] = m[6];
	ml[2][2] = m[10];
	ml[2][3] = m[14];
	ml[3][0] = m[3];
	ml[3][1] = m[7];
	ml[3][2] = m[11];
	ml[3][3] = m[15];

	mat_load(&ml);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

/* Multiply the current matrix by an arbitrary matrix */
void glMultMatrixf(const GLfloat *m) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	memcpy(ml, m, sizeof(matrix_t));

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&ml);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

/* Multiply the current matrix by an arbitrary transposed matrix */
void glMultTransposeMatrixf(const GLfloat *m) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	ml[0][0] = m[0];
	ml[0][1] = m[4];
	ml[0][2] = m[8];
	ml[0][3] = m[12];
	ml[1][0] = m[1];
	ml[1][1] = m[5];
	ml[1][2] = m[9];
	ml[1][3] = m[13];
	ml[2][0] = m[2];
	ml[2][1] = m[6];
	ml[2][2] = m[10];
	ml[2][3] = m[14];
	ml[3][0] = m[3];
	ml[3][1] = m[7];
	ml[3][2] = m[11];
	ml[3][3] = m[15];

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&ml);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

/* Set the depth range */
void glDepthRange(GLclampf n, GLclampf f) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	/* clamp the values... */
	if (n < 0.0f) n = 0.0f;
	if (n > 1.0f) n = 1.0f;
	if (f < 0.0f) f = 0.0f;
	if (f > 1.0f) f = 1.0f;

	gl_depthrange_near = n;
	gl_depthrange_far = f;

	/* Adjust the viewport scale and offset for Z */
	gl_viewport_scale[2] = ((f - n) / 2.0f);
	gl_viewport_offset[2] = (n + f) / 2.0f;
}

/* Set the GL viewport */
void glViewport(GLint x, GLint y,
		GLsizei width, GLsizei height) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	gl_viewport_x1 = x;
	gl_viewport_y1 = y;
	gl_viewport_width = width;
	gl_viewport_height = height;

	/* Calculate the viewport scale and offset */
	gl_viewport_scale[0] = (GLfloat)width / 2.0f;
	gl_viewport_offset[0] = gl_viewport_scale[0] + (GLfloat)x;
	gl_viewport_scale[1] = (GLfloat)height / 2.0f;
	gl_viewport_offset[1] = gl_viewport_scale[1] + (GLfloat)y;
	gl_viewport_scale[2] = (gl_depthrange_far - gl_depthrange_near) / 2.0f;
	gl_viewport_offset[2] = (gl_depthrange_near + gl_depthrange_far) / 2.0f;

	/* Flip the Y-axis */
	//gl_viewport_scale[1] *= -1.0f;

	/* FIXME: Why does the depth value need some nudging?
         * This makes polys with Z=0 work.
	 */
	gl_viewport_offset[2] += 0.0001f;
}

/* Located here for now */
void gluPerspective(GLfloat angle, GLfloat aspect, 
	GLfloat znear, GLfloat zfar) {

	GLfloat xmin, xmax, ymin, ymax;

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	ymax = znear * ftan(angle * F_PI / 360.0f);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, znear, zfar);
}

static matrix_t mf __attribute__((aligned(32))) = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, -1.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f }
};

void glFrustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat znear, GLfloat zfar) {

	GLfloat x, y, a, b, c, d;

	gl_frustum.left = left;
	gl_frustum.right = right;
	gl_frustum.bottom = bottom;
	gl_frustum.top = top;
	gl_frustum.znear = znear;
	gl_frustum.zfar = zfar;
	
	assert(znear > 0.0f);
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	x = (2.0f * znear) / (right - left);
	y = (2.0f * znear) / (top - bottom);
	a = (right + left) / (right - left);
	b = (top + bottom) / (top - bottom);
	c = -(zfar + znear) / (zfar - znear);
	d = -(2.0f * zfar * znear) / (zfar - znear);

	mf[0][0] = x;
	mf[2][0] = a;
	mf[1][1] = y;
	mf[2][1] = b;
	mf[2][2] = c;
	mf[3][2] = d;

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&mf);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

static matrix_t mo __attribute__((aligned(32))) = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void glOrtho(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat znear, GLfloat zfar) {

	GLfloat x, y, z;
	GLfloat tx, ty, tz;

	gl_frustum.znear = 0.001;
	gl_frustum.zfar = 100;
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	x = 2.0f / (right - left);
	y = 2.0f / (top - bottom);
	z = -2.0f / (zfar - znear);
	tx = -(right + left) / (right - left);
	ty = -(top + bottom) / (top - bottom);
	tz = -(zfar + znear) / (zfar - znear);

	mo[0][0] = x;
	mo[1][1] = y;
	mo[2][2] = z;
	mo[3][0] = tx;
	mo[3][1] = ty;
	mo[3][2] = tz;

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&mo);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

void glPushMatrix(void) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch (gl_matrix_mode)
	{
	case GL_MODELVIEW:
		assert_msg(gl_mat_mv_stack_top < MAT_MV_STACK_CNT, "Modelview stack overflow.");
		memcpy(gl_mat_mv_stack + gl_mat_mv_stack_top,
			gl_trans_mats + gl_matrix_mode,
			sizeof(matrix_t));
		gl_mat_mv_stack_top++;
		break;
	case GL_PROJECTION:
		assert_msg(gl_mat_p_stack_top < MAT_P_STACK_CNT, "Projection stack overflow.");
		memcpy(gl_mat_p_stack + gl_mat_p_stack_top,
			gl_trans_mats + gl_matrix_mode,
			sizeof(matrix_t));
		gl_mat_p_stack_top++;
		memcpy(gl_frustum_stack + gl_frustum_stack_top,
			&gl_frustum,
			sizeof(gl_frustum_t));
		gl_frustum_stack_top++;
		break;
	case GL_TEXTURE:
		assert_msg(gl_mat_t_stack_top < MAT_T_STACK_CNT, "Texture stack overflow.");
		memcpy(gl_mat_t_stack + gl_mat_t_stack_top,
			gl_trans_mats + gl_matrix_mode,
			sizeof(matrix_t));
		gl_mat_t_stack_top++;
		break;
	}
}

void glPopMatrix(void) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(gl_matrix_mode)
	{
	case GL_MODELVIEW:
		assert_msg(gl_mat_mv_stack_top > 0, "Modelview stack underflow.");
		gl_mat_mv_stack_top--;
		memcpy(gl_trans_mats + gl_matrix_mode,
			gl_mat_mv_stack + gl_mat_mv_stack_top,
			sizeof(matrix_t));
		break;
	case GL_PROJECTION:
		assert_msg(gl_mat_p_stack_top > 0, "Projection stack underflow.");
		gl_mat_p_stack_top--;
		memcpy(gl_trans_mats + gl_matrix_mode,
			gl_mat_p_stack + gl_mat_p_stack_top,
			sizeof(matrix_t));
		gl_frustum_stack_top--;
		memcpy(&gl_frustum,
			gl_frustum_stack + gl_frustum_stack_top,
			sizeof(gl_frustum_t));
		break;
	case GL_TEXTURE:
		assert_msg(gl_mat_t_stack_top > 0, "Texture stack underflow.");
		gl_mat_t_stack_top--;
		memcpy(gl_trans_mats + gl_matrix_mode,
			gl_mat_t_stack + gl_mat_t_stack_top,
			sizeof(matrix_t));
		break;
	}

	gl_matrix_dirty = GL_TRUE;
}

static matrix_t mr __attribute__((aligned(32))) = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void glRotatef(GLfloat angle,
		GLfloat x, GLfloat y, GLfloat z) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	GLfloat rcos = fcos(angle * DEG2RAD);
	GLfloat rsin = fsin(angle * DEG2RAD);
	GLfloat invrcos = (1.0f - rcos);
	GLfloat mag = fsqrt(x*x + y*y + z*z);
	GLfloat xx, yy, zz, xy, yz, zx;

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
	mr[0][0] = xx + rcos * (1.0f - xx);
	mr[2][1] = yz - x * rsin;
	mr[1][2] = yz + x * rsin;

	mr[1][1] = yy + rcos * (1.0f - yy);
	mr[2][0] = zx + y * rsin;
	mr[0][2] = zx - y * rsin;

	mr[2][2] = zz + rcos * (1.0f - zz);
	mr[1][0] = xy - z * rsin;
	mr[0][1] = xy + z * rsin;

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&mr);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

static matrix_t ms __attribute__((aligned(32))) = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void glScalef(GLfloat x, GLfloat y, GLfloat z) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
        ms[0][0] = x;
	ms[1][1] = y;
	ms[2][2] = z;

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&ms);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

static matrix_t mt __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void glTranslatef(GLfloat x, GLfloat y, GLfloat z) {

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
        mt[3][0] = x;
	mt[3][1] = y;
	mt[3][2] = z;

	mat_load(gl_trans_mats + gl_matrix_mode);
	mat_apply(&mt);
	mat_store(gl_trans_mats + gl_matrix_mode);

	gl_matrix_dirty = GL_TRUE;
}

/* XXX - these should be in glu */
void normalize(float v[3])
{
    float r;

    r = fsqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    if (r == 0.0) return;

    v[0] /= r;
    v[1] /= r;
    v[2] /= r;
}

void cross(float v1[3], float v2[3], float result[3])
{
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

static matrix_t ml __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

/* XXX - should move to glu */
void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
	  GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy,
	  GLfloat upz)
{
    float forward[3], side[3], up[3];

    assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    up[0] = upx;
    up[1] = upy;
    up[2] = upz;

    normalize(forward);

    /* Side = forward x up */
    cross(forward, up, side);
    normalize(side);

    /* Recompute up as: up = side x forward */
    cross(side, forward, up);

    ml[0][0] = side[0];
    ml[1][0] = side[1];
    ml[2][0] = side[2];

    ml[0][1] = up[0];
    ml[1][1] = up[1];
    ml[2][1] = up[2];

    ml[0][2] = -forward[0];
    ml[1][2] = -forward[1];
    ml[2][2] = -forward[2];

    mat_load(gl_trans_mats + gl_matrix_mode);
    mat_apply(&ml);
    mat_store(gl_trans_mats + gl_matrix_mode);

    glTranslatef(-eyex, -eyey, -eyez);
}
