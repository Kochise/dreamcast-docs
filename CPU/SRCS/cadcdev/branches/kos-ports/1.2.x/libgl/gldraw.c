/* KallistiGL for KOS ##version##

   gldraw.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <dc/pvr.h>

CVSID("$Id: gldraw.c,v 1.23 2002/09/05 07:36:23 bardtx Exp $");

/* internal prototypes */
static void send_user_clip();

/* Drawing functions */

/* This portion of the pipeline will change drastically */

/* Current vertex attributes (move to global?) */
static GLuint vert_rgba = 0xffffffff;
static GLfloat vert_u = 0.0f, vert_v = 0.0f;

/* Make sure the proper matrices are in the matrix registers */
static void fix_matrices() {
	if (gl_matrix_dirty) {
		mat_identity();
		glKosMatrixApply(GL_KOS_SCREENVIEW);
		glKosMatrixApply(GL_PROJECTION);
		glKosMatrixApply(GL_MODELVIEW);

		gl_matrix_dirty = GL_FALSE;
	}
}

/* Negative 1/w values annoy the pvr, so check for them */
static inline int check_w(gl_vertex_t *vert, int n) {
	int i;

	for(i=0; i<n; i++)
	        if (vert[i].z < 0) return 0;
	return 1;
}

static short xor[2][2] ={
	{1,0}, /* FFCW, FFCCW */
	{0,1}  /* BFCW, BFCCW */
};
/* GL_POINTS always visible! */
static void end_points() {
	int i;
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	float size1 = (xor[(gl_cull_mode == GL_BACK)][(gl_front_face == GL_CCW)]) ? 
gl_point_size : -gl_point_size;
	float size2 = ABS(size1);

	pvr_dr_init(dr_state);

	/* Should be one point in the buffer */
	assert_msg(gl_vbuf_top >= 1, "Need at least one point.");

	/* create a point using a quad */
	memcpy(&gl_vbuf[1], &gl_vbuf[0], sizeof(gl_vertex_t));
	memcpy(&gl_vbuf[2], &gl_vbuf[0], sizeof(gl_vertex_t));
	memcpy(&gl_vbuf[3], &gl_vbuf[0], sizeof(gl_vertex_t));

	gl_vbuf[3].flags = PVR_CMD_VERTEX_EOL;
	mat_transform((vector_t*)&gl_vbuf[0].x, (vector_t*)&gl_xbuf[0].x, 4, sizeof(gl_vertex_t));

	gl_xbuf[0].x += size1;
	gl_xbuf[0].y += size2;
	gl_xbuf[1].x += size1;
	gl_xbuf[1].y -= size2;
	gl_xbuf[2].x -= size1;
	gl_xbuf[2].y += size2;
	gl_xbuf[3].x -= size1;
	gl_xbuf[3].y -= size2;

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, 4))
		for (i=0; i<4; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_vbuf[i].u;
			vert->v     = gl_vbuf[i].v;
			vert->argb  = gl_vbuf[i].argb;
			vert->oargb = gl_vbuf[i].oargb;
			pvr_dr_commit(vert);
		}
}

static void end_triangles() {
	int i;
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be three points in the buffer */
	assert_msg(gl_vbuf_top == 3, "Wrong number of vertices.");

	gl_vbuf[2].flags = PVR_CMD_VERTEX_EOL;
	/* mat_transform((vector_t*)&gl_vbuf[0].x, (vector_t*)&gl_xbuf[0].x, 3, 
sizeof(gl_vertex_t)); */

	for (i=0; i<gl_vbuf_top; i++) {
		float x = gl_vbuf[i].x, y = gl_vbuf[i].y, z = gl_vbuf[i].z, w = 1.0f;
		mat_trans_single4(x, y, z, w);
		gl_xbuf[i].x = x;
		gl_xbuf[i].y = y;
		if (w == 1.0f)
			gl_xbuf[i].z = ((gl_viewport_scale[2] * z) + gl_viewport_offset[2]);
		else
			gl_xbuf[i].z = w;
	}

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, 3))
		for (i=0; i<3; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_vbuf[i].u;
			vert->v     = gl_vbuf[i].v;
			vert->argb  = gl_vbuf[i].argb;
			vert->oargb = gl_vbuf[i].oargb;
			pvr_dr_commit(vert);
		}
}

static void end_triangle_strip() {
	int i;
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be at least 3 points in the buffer */
	assert_msg(gl_vbuf_top >= 3, "Need at least three vertices.");

	gl_vbuf[gl_vbuf_top-1].flags = PVR_CMD_VERTEX_EOL;
	/* mat_transform((vector_t*)&gl_vbuf[0].x, (vector_t*)&gl_xbuf[0].x, 
gl_vbuf_top, sizeof(gl_vertex_t)); */

	for (i=0; i<gl_vbuf_top; i++) {
		float x = gl_vbuf[i].x, y = gl_vbuf[i].y, z = gl_vbuf[i].z, w = 1.0f;
		mat_trans_single4(x, y, z, w);
		gl_xbuf[i].x = x;
		gl_xbuf[i].y = y;
		if (w == 1.0f)
			gl_xbuf[i].z = ((gl_viewport_scale[2] * z) + gl_viewport_offset[2]);
		else
			gl_xbuf[i].z = w;
	}

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, gl_vbuf_top))
		for (i=0; i<gl_vbuf_top; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_vbuf[i].u;
			vert->v     = gl_vbuf[i].v;
			vert->argb  = gl_vbuf[i].argb;
			vert->oargb = gl_vbuf[i].oargb;
			pvr_dr_commit(vert);
		}
}

static void end_quads() {
	int i, j, order[4] = {3, 0, 2, 1};
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be four points in the buffer */
	assert_msg(gl_vbuf_top == 4, "Wrong number of vertices.");

	gl_vbuf[order[3]].flags = PVR_CMD_VERTEX_EOL;
	/* mat_transform((vector_t*)&gl_vbuf[0].x, (vector_t*)&gl_xbuf[0].x, 4, 
sizeof(gl_vertex_t)); */

	for (i=0; i<gl_vbuf_top; i++) {
		float x = gl_vbuf[i].x, y = gl_vbuf[i].y, z = gl_vbuf[i].z, w = 1.0f;
		mat_trans_single4(x, y, z, w);
		gl_xbuf[i].x = x;
		gl_xbuf[i].y = y;
		if (w == 1.0f)
			gl_xbuf[i].z = ((gl_viewport_scale[2] * z) + gl_viewport_offset[2]);
		else
			gl_xbuf[i].z = w;
	}

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, 4))
		for (i=0; i<4; i++) {
			j = order[i];
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[j].flags;
			vert->x     = gl_xbuf[j].x;
			vert->y     = gl_xbuf[j].y;
			vert->z     = gl_xbuf[j].z;
			vert->u     = gl_vbuf[j].u;
			vert->v     = gl_vbuf[j].v;
			vert->argb  = gl_vbuf[j].argb;
			vert->oargb = gl_vbuf[j].oargb;
			pvr_dr_commit(vert);
		}
}

static void end_quad_strip() {
	int i;
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be at least 4 points in the buffer */
	assert_msg(gl_vbuf_top >= 4, "Need at least four vertices.");

	/* OpenGL specs that any dangling vertex be chopped, which
	we have to do since we're rendering as a tri-strip. */
	if(gl_vbuf_top & 0x0001)
		gl_vbuf_top--;

	gl_vbuf[gl_vbuf_top-1].flags = PVR_CMD_VERTEX_EOL;

	for (i=0; i<gl_vbuf_top; i++) {
		float x = gl_vbuf[i].x, y = gl_vbuf[i].y, z = gl_vbuf[i].z, w = 1.0f;
		mat_trans_single4(x, y, z, w);
		gl_xbuf[i].x = x;
		gl_xbuf[i].y = y;
		if (w == 1.0f)
			gl_xbuf[i].z = ((gl_viewport_scale[2] * z) + gl_viewport_offset[2]);
		else
			gl_xbuf[i].z = w;
	}

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, gl_vbuf_top))
		for (i=0; i<gl_vbuf_top; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_vbuf[i].u;
			vert->v     = gl_vbuf[i].v;
			vert->argb  = gl_vbuf[i].argb;
			vert->oargb = gl_vbuf[i].oargb;
			pvr_dr_commit(vert);
		}
}

static void end_polygon() {
	int i, j_frn, j_bck;
	volatile pvr_vertex_t	*vert;
	gl_vertex_t	*gl_tvbuf;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be at least 3 points in the buffer */
	assert_msg(gl_vbuf_top >= 3, "Need at least three vertices.");

	/* Have to alter linear vertex order to staggered Triangle strip order
	   performance will suffer, but it does on all cards. */

	gl_tvbuf = malloc(sizeof(gl_vertex_t) * (gl_vbuf_top));
	assert_msg(gl_tvbuf != NULL, "Not enough memory for GL_POLYGON");

	gl_tvbuf[0] = gl_vbuf[0];
	gl_tvbuf[1] = gl_vbuf[1];

	i = 2;					/* the first 2 vertices are in proper order. */
	j_frn = i;
	j_bck = gl_vbuf_top - 1;

	do {
		gl_tvbuf[i++] = gl_vbuf[j_bck];	/* move data */
		if (i < gl_vbuf_top) {
			gl_tvbuf[i++] = gl_vbuf[j_frn];
			j_frn++;
			j_bck--;
		}
	} while (i < gl_vbuf_top);

	memcpy(gl_vbuf, gl_tvbuf, sizeof(gl_vertex_t) * gl_vbuf_top);
	free(gl_tvbuf);

	gl_vbuf[gl_vbuf_top-1].flags = PVR_CMD_VERTEX_EOL;

	for (i=0; i<gl_vbuf_top; i++) {
		float x = gl_vbuf[i].x, y = gl_vbuf[i].y, z = gl_vbuf[i].z, w = 1.0f;
		mat_trans_single4(x, y, z, w);
		gl_xbuf[i].x = x;
		gl_xbuf[i].y = y;
		if (w == 1.0f)
			gl_xbuf[i].z = ((gl_viewport_scale[2] * z) + gl_viewport_offset[2]);
		else
			gl_xbuf[i].z = w;
	}

	/* Throw it all to the TA using direct render */
	if (check_w(gl_xbuf, gl_vbuf_top))
		for (i=0; i<gl_vbuf_top; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_vbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_vbuf[i].u;
			vert->v     = gl_vbuf[i].v;
			vert->argb  = gl_vbuf[i].argb;
			vert->oargb = gl_vbuf[i].oargb;
			pvr_dr_commit(vert);
		}
}

static void check_end() {
	/* What type of primitive was it? */
	switch(gl_prim_type) {
	case GL_POINTS:
		end_points();
		gl_vbuf_top = 0;
		break;
	case GL_TRIANGLES:
		if (gl_vbuf_top == 3) {
			end_triangles();
			gl_vbuf_top = 0;
		}
		break;
	case GL_TRIANGLE_STRIP:
		break;
	case GL_QUADS:
		if (gl_vbuf_top == 4) {
			end_quads();
			gl_vbuf_top = 0;
		}
		break;
	case GL_QUAD_STRIP:
		break;
	case GL_POLYGON:
		break;
	default:
		assert_msg(0, "gl_prim_type: Unknown primitive type.");
	}
}

static pvr_poly_hdr_t polyhdr;

void send_poly_hdr(void) {

	if (TXR_ENABLED) {
		memcpy(&gl_poly_cxt.txr, &gl_cur_texture->txr, sizeof(gl_poly_cxt.txr));
	}

	switch(gl_active_list) {
	case GL_LIST_OPAQUE_POLY:
		gl_poly_cxt.gen.alpha = PVR_ALPHA_DISABLE;
		gl_poly_cxt.txr.alpha = PVR_TXRALPHA_ENABLE;
		gl_poly_cxt.blend.src = PVR_BLEND_ONE;
		gl_poly_cxt.blend.dst = PVR_BLEND_ZERO;
		break;
	case GL_LIST_OPAQUE_MOD:
		break;
	case GL_LIST_TRANS_POLY:
	case GL_LIST_PUNCHTHRU:
		gl_poly_cxt.gen.alpha = PVR_ALPHA_ENABLE;
		gl_poly_cxt.txr.alpha = PVR_TXRALPHA_ENABLE;
		gl_poly_cxt.blend.src = gl_blend_src;
		gl_poly_cxt.blend.dst = gl_blend_dst;
		break;
	case GL_LIST_TRANS_MOD:
		break;
	}
	/* Set states that we couldn't before */
	if (gl_cull_face)
	{
		if (gl_cull_mode == GL_BACK)
			if (gl_front_face == GL_CW)
				gl_poly_cxt.gen.culling = PVR_CULLING_CCW;
			else
				gl_poly_cxt.gen.culling = PVR_CULLING_CW;
		else
			if (gl_front_face == GL_CCW)
				gl_poly_cxt.gen.culling = PVR_CULLING_CCW;
			else
				gl_poly_cxt.gen.culling = PVR_CULLING_CW;
	} else
		gl_poly_cxt.gen.culling = PVR_CULLING_NONE;

	pvr_poly_compile(&polyhdr, &gl_poly_cxt);
	pvr_prim(&polyhdr, sizeof(pvr_poly_hdr_t));
}

/* This can be used for KGL Direct Rendering */
void glKosPolyHdrSend() {
	send_poly_hdr();
}

void glBegin(GLenum mode) {
	/* Submit the user clip rectangle (if necessary) */
	if (gl_scissor_dirty) {
		send_user_clip();
		gl_scissor_dirty = GL_FALSE;
	}

	/* Submit the poly buffer (if necessary) */
	if (!gl_pbuf_submitted) {
		send_poly_hdr();
		gl_pbuf_submitted = GL_TRUE;
	}
	if (ZCLIP_ENABLED || LIGHTING_ENABLED)
		fix_vfzclip_matrices();
	else
		fix_matrices();

	gl_prim_type = mode;
	gl_vbuf_top = 0;
}

void glEnd(void) {
	if (MODIFIER_ENABLED) {
		modifier_end();
		return;
	} else if (ZCLIP_ENABLED || LIGHTING_ENABLED) {
		vfzclip_end();
		return;
	}

	/* What type of primitive was it? */
	switch(gl_prim_type) {
	case GL_POINTS:
		break;
	case GL_TRIANGLES:
		break;
	case GL_TRIANGLE_STRIP:
		end_triangle_strip();
		break;
	case GL_QUADS:
		break;
	case GL_QUAD_STRIP:
		end_quad_strip();
		break;
	case GL_POLYGON:
		end_polygon();
		break;
	default:
		assert_msg(0, "gl_prim_type: Unknown primitive type.");
	}
	gl_prim_type = 0;
}

static float autouv[4][2] = {
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f}
};

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
	gl_vbuf[gl_vbuf_top].flags = PVR_CMD_VERTEX;

	gl_vbuf[gl_vbuf_top].x = x;
	gl_vbuf[gl_vbuf_top].y = y;
	gl_vbuf[gl_vbuf_top].z = z;
	gl_vbuf[gl_vbuf_top].w = 1.0f;
	if (AUTOUV_ENABLED) {
		vert_u = autouv[gl_vbuf_top][0];
		vert_v = autouv[gl_vbuf_top][1];
	}
	gl_vbuf[gl_vbuf_top].u = vert_u;
	gl_vbuf[gl_vbuf_top].v = vert_v;
	gl_vbuf[gl_vbuf_top].argb = vert_rgba;
	gl_vbuf[gl_vbuf_top].oargb = 0xff000000;

	gl_vbuf_top++;
	assert_msg(gl_vbuf_top < VBUF_SIZE, "Vertex buffer overflow");

	if (MODIFIER_ENABLED) 
		modifier_check_end();
	else if (ZCLIP_ENABLED || LIGHTING_ENABLED)
		vfzclip_check_end();
	else
		check_end();
}

void glVertex3fv(GLfloat *v) {
        glVertex3f(*v, *(v+1), *(v+2));
}

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
}

void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
	vert_rgba = (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
	vert_rgba = (0xff << 24) |
		((uint32)(red * 0xff) << 16) |
		((uint32)(green * 0xff) << 8) |
		((uint32)(blue * 0xff));
}

void glColor3fv(GLfloat *v) {
        glColor3f(*v, *(v+1), *(v+2));
}

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	vert_rgba = ((uint32)(alpha * 0xff) << 24) |
		((uint32)(red * 0xff) << 16) |
		((uint32)(green * 0xff) << 8) |
		((uint32)(blue * 0xff));
}

void glColor4fv(GLfloat *v) {
        glColor4f(*v, *(v+1), *(v+2), *(v+3));
}

void glTexCoord2f(GLfloat s, GLfloat t) {
	vert_u = s;
	vert_v = t;
}

void glTexCoord2fv(GLfloat *v) {
	vert_u = *v;
	vert_v = *(v+1);
}

static pvr_poly_hdr_t user_clip = {
        PVR_CMD_USERCLIP, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000
};

static void send_user_clip() {
	pvr_prim(&user_clip, sizeof(pvr_poly_hdr_t));
}
/* Setup the hardware user clip rectangle. It will be sent during glBegin.

   The minimum clip rectangle is a 32x32 area which is dependent on the tile
   size use by the tile accelerator. The PVR swithes off rendering to tiles
   outside or inside the defined rectangle dependant upon the 'clipmode' 
bits
   in the polygon header.

   Clip rectangles therefore must have a size that is some multiple of 32.

   	glScissor(0, 0, 32, 32) allows only the 'tile' in the lower left
	hand corner of the screen to be modified and glScissor(0, 0, 0, 0)
	disallows modification to all 'tiles' on the screen.
*/
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
	GLint minx, miny, maxx, maxy;

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	assert((width >= 0) && (height >= 0));
	gl_scissor_x = x;
	gl_scissor_y = y;
	gl_scissor_width = CLAMP(width, 0, gl_screen_width);
	gl_scissor_height = CLAMP(height, 0, gl_screen_height);

	minx = gl_scissor_x;
	/* force the origin to the lower left-hand corner of the screen */
	miny = /**/(gl_screen_height - gl_scissor_height) - /**/ gl_scissor_y;
	maxx = (gl_scissor_width + minx);
	maxy = (gl_scissor_height + miny);

	/* load command structure while mapping screen coords to TA tiles */
	user_clip.d1 = CLAMP(minx/32, 0, gl_screen_width/32);
	user_clip.d2 = CLAMP(miny/32, 0, gl_screen_height/32);
	user_clip.d3 = CLAMP((maxx/32)-1, 0, gl_screen_width/32);
	user_clip.d4 = CLAMP((maxy/32)-1, 0, gl_screen_height/32);

	gl_scissor_dirty = GL_TRUE;
	gl_pbuf_submitted = GL_FALSE;
}

