/* KallistiGL for KOS ##version##

   glmisc.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

CVSID("$Id: glmisc.c,v 1.17 2002/07/08 05:28:28 axlen Exp $");

/* Miscellaneous APIs */

/* Set the background clear color */
void glClearColor(GLclampf red,
		GLclampf green,
		GLclampf blue,
		GLclampf alpha) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	gl_clear_color[0] = CLAMP01(red);
	gl_clear_color[1] = CLAMP01(green);
	gl_clear_color[2] = CLAMP01(blue);
	gl_clear_color[3] = CLAMP01(alpha);
	pvr_set_bg_color(gl_clear_color[0]*gl_clear_color[3],
			gl_clear_color[1]*gl_clear_color[3],
			gl_clear_color[2]*gl_clear_color[3]);
}

/* NOP: there's nothing to clear on the PVR2 */
void glClear(GLbitfield mask) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
}

/* Set front face */
void glFrontFace(GLenum mode) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(mode) {
	case GL_CW:
	case GL_CCW:
		gl_front_face = mode;
		gl_pbuf_submitted = GL_FALSE;
		break;
	}
}

/* Set face culling mode */
void glCullFace(GLenum mode) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(mode) {
	case GL_FRONT:
	case GL_BACK:
		gl_cull_mode = mode;
		gl_pbuf_submitted = GL_FALSE;
		break;
	}
}

/* Enable / disable capabilities */
void glEnable(GLenum cap) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(cap) {
	case GL_TEXTURE_2D:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.txr.enable = PVR_TEXTURE_ENABLE;
		break;
	case GL_BLEND:
		if (gl_active_list != GL_LIST_TRANS_POLY) {
			dbglog(DBG_ERROR, "gl: invalid list to enable GL_BLEND inside");
			return;
		}
		break;
	case GL_CULL_FACE:
		gl_pbuf_submitted = GL_FALSE;
	        gl_cull_face = GL_TRUE;
	        break;
	case GL_FOG:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.fog_type = PVR_FOG_TABLE;
		break;
	case GL_SCISSOR_TEST:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.clip_mode = PVR_USERCLIP_INSIDE;
		if (USERCLIP_OUTSIDE_ENABLED)
			gl_capabilities &= ~((GLbitfield)GL_KOS_USERCLIP_OUTSIDE);
		break;
	case GL_KOS_USERCLIP_OUTSIDE:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.clip_mode = PVR_USERCLIP_OUTSIDE;
		if (SCISSOR_ENABLED)
			gl_capabilities &= ~((GLbitfield)GL_SCISSOR_TEST);
		break;
	case GL_KOS_MODIFIER:
		assert_msg(0, "GL_KOS_MODIFER not implemented");
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.fmt.modifier = PVR_MODIFIER_ENABLE;
		break;
	case GL_KOS_CHEAP_SHADOW:
		assert_msg(0, "GL_KOS_CHEAP_SHADOW not implemented");
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.modifier_mode = PVR_MODIFIER_CHEAP_SHADOW;
		break;
	case GL_KOS_NEARZ_CLIPPING:
		gl_matrix_dirty = GL_TRUE;
		break;
	case GL_LIGHT0:
		assert_msg(0, "GL_LIGHTi not implemented");
		break;
	}

	gl_capabilities |= (GLbitfield)cap;
}

void glDisable(GLenum cap) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(cap) {
	case GL_TEXTURE_2D:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.txr.enable = PVR_TEXTURE_DISABLE;
		break;
	case GL_BLEND:
		if (gl_active_list == GL_LIST_TRANS_POLY) {
			dbglog(DBG_ERROR, "gl: invalid list to disable GL_BLEND inside");
			return;
		}
		break;
	case GL_CULL_FACE:
		gl_pbuf_submitted = GL_FALSE;
	        gl_cull_face = GL_FALSE;
	        break;
	case GL_FOG:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.fog_type = PVR_FOG_DISABLE;
		break;
	case GL_SCISSOR_TEST:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.clip_mode = PVR_USERCLIP_DISABLE;
		if (USERCLIP_OUTSIDE_ENABLED)
			gl_capabilities &= ~((GLbitfield)GL_KOS_USERCLIP_OUTSIDE);
		break;
	case GL_KOS_USERCLIP_OUTSIDE:
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.clip_mode = PVR_USERCLIP_DISABLE;
		if (SCISSOR_ENABLED)
			gl_capabilities &= ~((GLbitfield)GL_SCISSOR_TEST);
		break;
	case GL_KOS_MODIFIER:
		assert_msg(0, "GL_KOS_MODIFER not implemented");
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.fmt.modifier = PVR_MODIFIER_DISABLE;
		break;
	case GL_KOS_CHEAP_SHADOW:
		assert_msg(0, "GL_KOS_CHEAP_SHADOW not implemented");
		gl_pbuf_submitted = GL_FALSE;
		gl_poly_cxt.gen.modifier_mode = PVR_MODIFIER_NORMAL;
		break;
	case GL_KOS_NEARZ_CLIPPING:
		gl_matrix_dirty = GL_TRUE;
		break;
	case GL_LIGHT0:
		assert_msg(0, "GL_LIGHTi not implemented");
		break;
	}

	gl_capabilities &= ~((GLbitfield)cap);
}

/* We have no rendering pipeline yet, so this is a NOP */
void glFlush() {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
}

/* There aren't any useful hints to set yet, so this is a NOP */
void glHint(GLenum target, GLenum mode) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
}

void glPointSize(GLfloat size) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	gl_point_size = CLAMP(size, 0.0f, 100.0f);
}

/* These strings should go somewhere else */
const GLubyte *glGetString(GLenum name) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch(name) {
		case GL_VENDOR:
			return "Cryptic Allusions";

		case GL_RENDERER:
			return "KallistiOS";

		case GL_VERSION:
			return "1.1";

		case GL_EXTENSIONS:
			return "GL_ARB_transpose_matrix ";
	}

	return "";
}

/* A limited view into the guts of KGL  - This will change! */
void glGetFloatv(GLenum pname, GLfloat *params) {
	int i, j;
	matrix_t *pmat = (matrix_t*)params;

	switch(pname) {
	case GL_MODELVIEW_MATRIX:
		for (i=0; i<4; i++)
			for (j=0; j<4; j++)
				(*pmat)[i][j] = gl_trans_mats[GL_MODELVIEW][i][j];
			break;
	case GL_PROJECTION_MATRIX:
		for (i=0; i<4; i++)
			for (j=0; j<4; j++)
				(*pmat)[i][j] = gl_trans_mats[GL_PROJECTION][i][j];
			break;
	case GL_TEXTURE_MATRIX:
		for (i=0; i<4; i++)
			for (j=0; j<4; j++)
				(*pmat)[i][j] = gl_trans_mats[GL_TEXTURE][i][j];
			break;
	default:
		assert_msg(0, "not glGet param not implemented");
	}
}
