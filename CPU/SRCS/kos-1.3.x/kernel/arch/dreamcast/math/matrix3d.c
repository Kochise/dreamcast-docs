/* KallistiOS ##version##

   matrix3d.c
   (c)2000-2002 Dan Potter and Jordan DeLong

   Some 3D utils to use with the matrix functions
   Based on example code by Marcus Comstedt
*/

#include <assert.h>
#include <dc/fmath.h>
#include <dc/matrix.h>
#include <dc/matrix3d.h>

CVSID("$Id: matrix3d.c,v 1.1 2002/09/05 07:32:13 bardtx Exp $");

static matrix_t tr_m __attribute__((aligned(32))) = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void mat_translate(float x, float y, float z) {
	tr_m[3][0] = x;
	tr_m[3][1] = y;
	tr_m[3][2] = z;
	mat_apply(&tr_m);
}

static matrix_t sc_m  __attribute__((aligned(32))) = {
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void mat_scale(float xs, float ys, float zs) {
	sc_m[0][0] = xs;
	sc_m[1][1] = ys;
	sc_m[2][2] = zs;
	mat_apply(&sc_m);
}

static matrix_t rx_m __attribute__((aligned(32))) = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void mat_rotate_x(float r) {
	rx_m[1][1] = rx_m[2][2] = fcos(r);
	rx_m[2][1] = fsin(r);
	rx_m[1][2] = -fsin(r);
	mat_apply(&rx_m);
}

static matrix_t ry_m  __attribute__((aligned(32))) = {
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void mat_rotate_y(float r) {
	ry_m[0][0] = ry_m[2][2] = fcos(r);
	ry_m[2][0] = -fsin(r);
	ry_m[0][2] = fsin(r);
	mat_apply(&ry_m);
}

static matrix_t rz_m  __attribute__((aligned(32))) = {
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void mat_rotate_z(float r) {
	rz_m[0][0] = rz_m[1][1] = fcos(r);
	rz_m[1][0] = fsin(r);
	rz_m[0][1] = -fsin(r);
	mat_apply(&rz_m);
}

void mat_rotate(float xr, float yr, float zr) {
	mat_rotate_x(xr);
	mat_rotate_y(yr);
	mat_rotate_z(zr);
}

/* Some #define's so we can keep the nice looking matrices for reference */
#define XCENTER 0.0f
#define YCENTER 0.0f
#define COT_FOVY_2 1.0f
#define ZNEAR 1.0f
#define ZFAR 100.0f

/* Screen view matrix (used to transform to screen space) */
static matrix_t sv_mat = {
	{ YCENTER,    0.0f,   0.0f,  0.0f },
	{    0.0f, YCENTER,   0.0f,  0.0f },
	{    0.0f,    0.0f,   1.0f,  0.0f },
	{ XCENTER, YCENTER,   0.0f,  1.0f }
};

/* Frustum matrix (does perspective) */
static matrix_t fr_mat = {
	{ COT_FOVY_2,       0.0f,                      0.0f,  0.0f },
	{       0.0f, COT_FOVY_2,                      0.0f,  0.0f },
	{       0.0f,       0.0f, (ZFAR+ZNEAR)/(ZNEAR-ZFAR), -1.0f },
	{       0.0f,       0.0f, 2*ZFAR*ZNEAR/(ZNEAR-ZFAR),  1.0f }
};

void mat_perspective(float xcenter, float ycenter, float cot_fovy_2,
	float znear, float zfar)
{
	/* Setup the screenview matrix */
	sv_mat[0][0] = sv_mat[1][1] = sv_mat[3][1] = ycenter;
	sv_mat[3][0] = xcenter;
	mat_apply(&sv_mat);

	/* Setup the frustum matrix */
	assert( (znear - zfar) != 0 );
	fr_mat[0][0] = fr_mat[1][1] = cot_fovy_2;
	fr_mat[2][2] = (zfar + znear) / (znear - zfar);
	fr_mat[3][2] = 2*zfar*znear / (znear - zfar);
	mat_apply(&fr_mat);
}


/* The following lookat code is based heavily on KGL's gluLookAt */

/* Should these be publically accessible somewhere? */
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

static matrix_t ml __attribute__((aligned(32))) = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};

void mat_lookat(const point_t * eye, const point_t * center, const vector_t * upi) {
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

	ml[0][0] = side.x;
	ml[1][0] = side.y;
	ml[2][0] = side.z;

	ml[0][1] = up.x;
	ml[1][1] = up.y;
	ml[2][1] = up.z;

	ml[0][2] = -forward.x;
	ml[1][2] = -forward.y;
	ml[2][2] = -forward.z;

	mat_apply(&ml);
	mat_translate(-eye->x, -eye->y, -eye->z);
}
