/* KallistiGL for KOS ##version##

   glmodifier.c
   (c)2002 Paul Boese

   NOTE:  This module is experimental, incomplete, and non-working
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <dc/matrix.h>
#include <dc/pvr.h>

CVSID("$Id");

volatile pvr_modifier_vol_t *volume;
static pvr_modifier_vol_t vol_vbuf, vol_xbuf;
pvr_dr_state_t	dr_state;
static GLint mod_type = -1;

/* local buffer for textured, packed-color, affected by modifier vertex */
pvr_vertex_tpcm_t vert_xbuf = { 
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000
};

/* Negative 1/w values annoy the pvr, so check for them */
static inline int check_w(pvr_vertex_t *vert, int n) {
	int i;

	for(i=0; i<n; i++)
	        if (vert[i].z < 0) return 0;
	return 1;
}

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

static pvr_poly_hdr_t mod_hdr = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000
};

void send_mod_hdr(void) {
	mod_hdr.cmd = PVR_CMD_MODIFIER;
	mod_hdr.mode1 = (mod_type << PVR_TA_PM1_MODIFIERINST_SHIFT) & PVR_TA_PM1_MODIFIERINST_MASK;

	switch(gl_active_list) {
	case GL_LIST_OPAQUE_MOD:
		mod_hdr.cmd |= (PVR_LIST_OP_MOD << PVR_TA_CMD_TYPE_SHIFT) & PVR_TA_CMD_TYPE_MASK;
		break;
		case GL_LIST_TRANS_MOD:
		mod_hdr.cmd |= (PVR_LIST_TR_MOD << PVR_TA_CMD_TYPE_SHIFT) & PVR_TA_CMD_TYPE_MASK;
		break;
	default:
		assert_msg(0, "wrong list specified");
		break;		
	}
	pvr_prim(&mod_hdr, sizeof(pvr_poly_hdr_t));
}

void glKosModBegin(GLenum mode) {
	assert_msg(0,"not implemented");
	mod_type = mode;
	//pvr_dr_init(dr_state);
	send_mod_hdr();
	fix_matrices();
}

void glKosModEnd(void) {
	assert_msg(0,"not implemented");
	mod_type = -1;
}

void glKosModVolume9f(GLfloat ax, GLfloat ay, GLfloat az,
		   GLfloat bx, GLfloat by, GLfloat bz,
		   GLfloat cx, GLfloat cy, GLfloat cz) {

	assert_msg(0,"not implemented");
	vol_vbuf.flags = PVR_CMD_VERTEX_EOL;
	vol_vbuf.ax = ax;
	vol_vbuf.ay = ay;
	vol_vbuf.az = az;
	vol_vbuf.bx = bx;
	vol_vbuf.by = by;
	vol_vbuf.bz = bz;
	vol_vbuf.cx = cx;
	vol_vbuf.cy = cy;
	vol_vbuf.cz = cz;
	mat_transform((vector_t*)&vol_vbuf.ax, (vector_t*)&vol_xbuf.ax, 3, sizeof(vector_t));

	/* Can't use the alternating store queues cuz we're sending
	 * 64 bytes at once with this vertex type
	 */
	vol_xbuf.flags = vol_vbuf.flags;
	vol_xbuf.d1 = vol_xbuf.d2 = vol_xbuf.d3 = 0;
	vol_xbuf.d4 = vol_xbuf.d5 = vol_xbuf.d6 = 0; 
	pvr_prim(&vol_xbuf, sizeof(pvr_modifier_vol_t));
	//printf("[%2.2f, %2.2f]\n", cz, vol_xbuf.cz);
}

static void end_quads() {
	int i, j, order[4] = {3, 0, 2, 1};

	/* Should be four points in the buffer */
	assert_msg(gl_vbuf_top == 4, "Wrong number of vertices.");

	gl_vbuf[order[3]].flags = PVR_CMD_VERTEX_EOL;
	/* mat_transform((vector_t*)&gl_vbuf[0].x, (vector_t*)&gl_xbuf[0].x, 4, 
sizeof(pvr_vertex_t)); */

	for (i=0; i<4; i++) {
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
			vert_xbuf.flags     = gl_vbuf[j].flags;
			vert_xbuf.x         = gl_xbuf[j].x;
			vert_xbuf.y         = gl_xbuf[j].y;
			vert_xbuf.z         = gl_xbuf[j].z;
			vert_xbuf.u0        = gl_vbuf[j].u;
			vert_xbuf.v0        = gl_vbuf[j].v;
			vert_xbuf.argb0     = gl_vbuf[j].argb;
			vert_xbuf.oargb0    = gl_vbuf[j].oargb;
			vert_xbuf.u1        = 0.0f;
			vert_xbuf.v1        = 0.0f;
			vert_xbuf.argb1     = 0xff00ff00;
			vert_xbuf.oargb1    = 0xffff0000;
			pvr_prim(&vert_xbuf, sizeof(pvr_vertex_tpcm_t));
		}
}

void modifier_check_end() {
	/* What type of primitive was it? */
	switch(gl_prim_type) {
	case GL_POINTS:
		//end_points();
		gl_vbuf_top = 0;
		break;
	case GL_TRIANGLES:
		if (gl_vbuf_top == 3) {
			//end_triangles();
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

void modifier_end(void) {
	/* What type of primitive was it? */
	switch(gl_prim_type) {
	case GL_POINTS:
		break;
	case GL_TRIANGLES:
		break;
	case GL_TRIANGLE_STRIP:
		//end_triangle_strip();
		break;
	case GL_QUADS:
		break;
	case GL_QUAD_STRIP:
		//end_quad_strip();
		break;
	case GL_POLYGON:
		//end_polygon();
		break;
	default:
		assert_msg(0, "gl_prim_type: Unknown primitive type.");
	}
	gl_prim_type = 0;
}


