/* KallistiGL for KOS ##version##

   glnzclip.c
   (c)2002 Paul Boese

   Near Z Clipped primatives
*/

/* This is experimental and subject to change - Currently only supports
   GL_TRIANGLES.

   Note: this file was originally named glvfzclip.c.  Not entirely
   correct. My Oops!
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"
#include "glclip.h"	/* Trilinear's inline near z clipper code */

#include <assert.h>
#include <dc/matrix.h>
#include <dc/pvr.h>

CVSID("$Id:");

/* Some local tranform stuff.  It is generally faster to clip and
   light verts in view-space. The transform has been broken into
   two pieces to make that possibe. */
static matrix_t mvp __attribute__((aligned(32)));

/* Make sure the proper matrices are in the matrix registers */
void fix_vfzclip_matrices() {
	if (gl_matrix_dirty) {
		mat_load(gl_trans_mats + GL_PROJECTION);
		mat_apply(gl_trans_mats + GL_MODELVIEW);
		mat_store(&mvp);

		gl_matrix_dirty = GL_FALSE;
	}
}

static uint32 frms = 0;
/* translate verts from model-space to view-space */
static void xltmodel(gl_vertex_t *invert, gl_vertex_t *outvert, int num) {
	int i;
	gl_vertex_t *ip, *op;
	
	for (i=0; i<num; i++) {
		ip = &invert[i];
		op = &outvert[i];
		
		/* Transform the vertex position by the MVP matrices - assume invert.w is always 1.0 */
		op->x = (mvp[0][0] * ip->x) + (mvp[1][0] * ip->y) + (mvp[2][0] * ip->z) + (mvp[3][0] * ip->w);
		op->y = (mvp[0][1] * ip->x) + (mvp[1][1] * ip->y) + (mvp[2][1] * ip->z) + (mvp[3][1] * ip->w);
		op->z = (mvp[0][2] * ip->x) + (mvp[1][2] * ip->y) + (mvp[2][2] * ip->z) + (mvp[3][2] * ip->w);
		op->w = (mvp[0][3] * ip->x) + (mvp[1][3] * ip->y) + (mvp[2][3] * ip->z) + (mvp[3][3] * ip->w);

		/* copy other attributes */
		op->flags = ip->flags;
		op->u     = ip->u;
		op->v     = ip->v;
		op->argb  = ip->argb;
		op->oargb = ip ->oargb;

		if ((frms++)%20000 == 0)
			printf("z=%03.3f, w=%03.3f\n", op->z, op->w); 
	}
}

/* translate verts from view-space to the screen */
static void xltview(gl_vertex_t *invert, gl_vertex_t *outvert, int num) {
	int i;
	gl_vertex_t *ip, *op;
	
	for (i=0; i<num; i++) {
		ip = &invert[i];
		op = &outvert[i];

		/* perspective divide */
		op->x = (ip->x /= ip->w);
		op->y = (ip->y /= ip->w);
		op->z = (ip->z /= ip->w);

		/* Perform viewport mapping (note: this implicitly flips the y-axis) */
		op->x = (gl_viewport_scale[0] * op->x) + gl_viewport_offset[0];
		op->y = gl_screen_height - ((gl_viewport_scale[1] * op->y) + gl_viewport_offset[1]);
		op->z = (ip->w == 1.0) ? (gl_viewport_scale[2] * op->z) + gl_viewport_offset[2] : 1.0f / ip->w;
	}
}

static void end_triangles() {
	int i, rslt;
	volatile pvr_vertex_t	*vert;
	pvr_dr_state_t	dr_state;

	pvr_dr_init(dr_state);

	/* Should be three points in the buffer */
	assert_msg(gl_vbuf_top == 3, "Wrong number of vertices.");

	xltmodel(gl_vbuf, gl_xbuf, 3);
	rslt = ZClipTex(gl_xbuf); 
	xltview(gl_xbuf, gl_xbuf, rslt);
	
	/* Throw it all to the TA using direct render */
	if (rslt!=0) {
		gl_xbuf[rslt-1].flags = PVR_CMD_VERTEX_EOL;
		for (i=0; i<rslt; i++) {
			vert = pvr_dr_target(dr_state);
			vert->flags = gl_xbuf[i].flags;
			vert->x     = gl_xbuf[i].x;
			vert->y     = gl_xbuf[i].y;
			vert->z     = gl_xbuf[i].z;
			vert->u     = gl_xbuf[i].u;
			vert->v     = gl_xbuf[i].v;
			vert->argb  = gl_xbuf[i].argb;
			vert->oargb = gl_xbuf[i].oargb;
			pvr_dr_commit(vert);
		}
	}
}

void vfzclip_check_end() {
	/* What type of primitive was it? */
	switch(gl_prim_type) {
	case GL_POINTS:
		//end_points();
		assert_msg(0, "GL_POINTS not supported");
		gl_vbuf_top = 0;
		break;
	case GL_TRIANGLES:
		if (gl_vbuf_top == 3) {
			end_triangles();
			gl_vbuf_top = 0;
		}
		break;
	case GL_TRIANGLE_STRIP:
		assert_msg(0, "GL_TRIANGE_STRIP not supported");
		break;
	case GL_QUADS:
		assert_msg(0, "GL_QUADS not supported");
		if (gl_vbuf_top == 4) {
			//end_quads();
			gl_vbuf_top = 0;
		}
		break;
	case GL_QUAD_STRIP:
		assert_msg(0, "GL_QUAD_STRIP not supported");
		break;
	case GL_POLYGON:
		assert_msg(0, "GL_POLYGON not supported");
		break;
	default:
		assert_msg(0, "gl_prim_type: Unknown primitive type.");
	}
}

void vfzclip_end(void) {
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

