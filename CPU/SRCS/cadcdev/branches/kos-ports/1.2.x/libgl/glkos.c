/* KallistiGL for KOS ##version##

   glkos.c
   (c)2001 Dan Potter
*/

#include <stdio.h>
#include <string.h>
#include <dc/video.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

CVSID("$Id: glkos.c,v 1.14 2002/09/05 07:36:23 bardtx Exp $");

/* KOS-specific APIs */

int glKosInit() {
	GLfloat w, h;
	static pvr_stats_t pvr_stats;

	if (pvr_get_stats(&pvr_stats)) {
		dbglog(DBG_ERROR, "gl: glKosInit - No PVR lists enabled!");
		return -1;
	}

	/* Pre-initialize all the globals */
	gl_clear_color[0] =
		gl_clear_color[1] =
		gl_clear_color[2] =
		gl_clear_color[3] = 0.0f;
	gl_capabilities = 0;
	gl_prim_type = 0;
	gl_pbuf_submitted = GL_FALSE;

	gl_enabled_lists = pvr_stats.enabled_list_mask | GL_LIST_END;
	gl_active_list = GL_LIST_NONE;

	/* Reset all matrices */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* Setup the basic polygon context */
	pvr_poly_cxt_col(&gl_poly_cxt, PVR_LIST_OP_POLY);
	/* Adjust context for GL conformance */
	gl_poly_cxt.gen.culling = PVR_CULLING_NONE;

	/* Make a NULL Texture */
	pvr_poly_cxt_col(&gl_null_texture, PVR_LIST_OP_POLY);
	gl_cur_texture = &gl_null_texture;
	
	glKosGetScreenSize(&w, &h);
	/* The screen w & h is used internally by some functions */
	gl_screen_width = (GLsizei)w; gl_screen_height = (GLsizei)h;
	
	/* Initialize the viewport */
	glDepthRange(0.0f, 1.0f);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/* Initialize the scissor test rectangle */
	glScissor(0, 0, (GLsizei)w, (GLsizei)h);
	
	/* Initialize fog */
	glFogi(GL_FOG_MODE, GL_EXP);

	return 0;
}

void glKosShutdown() {
}

void glKosGetScreenSize(GLfloat *w, GLfloat *h) {
	*w = vid_mode->width;
	*h = vid_mode->height;
}

static void _gl_list_begin(uint32 list) {
	pvr_list_begin(list);
	gl_poly_cxt.list_type = list;
}

void glKosBeginFrame() {
	uint32 tmp_list;
	
        pvr_wait_ready();
	pvr_scene_begin();
	gl_pbuf_submitted = GL_FALSE;
	gl_active_list = GL_LIST_FIRST;

	/* we can't assume GL_LIST_OPAQUE_POLY is the first enabled list
	   anymore! Advance to the first enabled list if opaque list is
	   not first already. */
	tmp_list = gl_active_list;
	if (!(gl_active_list&gl_enabled_lists)) {
		do {
			tmp_list = gl_active_list = (gl_active_list << 1);
			tmp_list &= gl_enabled_lists;
		} while(tmp_list==0);
	}
	
	switch(gl_active_list) {
	case GL_LIST_OPAQUE_POLY:
		_gl_list_begin(PVR_LIST_OP_POLY);
		break;
	case GL_LIST_OPAQUE_MOD:
		_gl_list_begin(PVR_LIST_OP_MOD);
		break;
	case GL_LIST_TRANS_POLY:
		_gl_list_begin(PVR_LIST_TR_POLY);
		break;
	case GL_LIST_TRANS_MOD:
		_gl_list_begin(PVR_LIST_TR_MOD);
		break;
	case GL_LIST_PUNCHTHRU:
		_gl_list_begin(PVR_LIST_PT_POLY);
		break;
	case GL_LIST_END:
		/* no lists were enabled!?! */
		dbglog(DBG_ERROR, "gl: no lists enabled in glKosBeginFrame!");
		/* this is probably a bailout condition! */
		break;
	}
}

void glKosFinishFrame() {
	while (gl_active_list != GL_LIST_NONE)
		glKosFinishList();
	pvr_scene_finish();
}

void glKosFinishList() {
	uint32 tmp_list;
	
	if (gl_active_list ==  GL_LIST_NONE)
		return;

	pvr_list_finish();

	/* Advance to the next list */
	tmp_list = gl_active_list;
	do {
		tmp_list = gl_active_list = (gl_active_list << 1);
		tmp_list &= gl_enabled_lists;
	} while(tmp_list==0);

	switch(gl_active_list) {
	case GL_LIST_OPAQUE_MOD:
		_gl_list_begin(PVR_LIST_OP_MOD);
		break;
	case GL_LIST_TRANS_POLY:
		_gl_list_begin(PVR_LIST_TR_POLY);
		break;
	case GL_LIST_TRANS_MOD:
		_gl_list_begin(PVR_LIST_TR_MOD);
		break;
	case GL_LIST_PUNCHTHRU:
		_gl_list_begin(PVR_LIST_PT_POLY);
		break;
	case GL_LIST_END:
		gl_active_list = GL_LIST_NONE;
	}
	
	/* We haven't submitted the new poly headers */
	gl_pbuf_submitted = GL_FALSE;
}

/* This can be used for KGL Direct Rendering: applies one of the GL
   matrices to the matrix registers and lets you do whatever you
   want after that. */
static matrix_t msv __attribute__((aligned(32))) = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};
void glKosMatrixApply(GLenum mode) {
	gl_matrix_dirty = GL_TRUE;
	if (mode < GL_KOS_SCREENVIEW) {
		mat_apply(gl_trans_mats + mode);
	} else {
		msv[0][0] = gl_viewport_scale[0];
		msv[1][1] = -gl_viewport_scale[1];
		msv[3][0] = gl_viewport_offset[0];
		msv[3][1] = gl_screen_height - gl_viewport_offset[1];
		mat_apply(&msv);
	}
}

/* A matrix clear function, for completeness */
void glKosMatrixIdent() {
	gl_matrix_dirty = GL_TRUE;
	mat_identity();
}

/* Tell KGL that the poly header is dirty again (i.e., you did something
   manually that it doesn't know about) */
void glKosPolyHdrDirty() {
	gl_pbuf_submitted = GL_FALSE;
}

/* Tell KGL that the matrix registers are dirty (i.e., you did something
   manually that it doesn't know about). Note that this does not include
   the above functions because those already take this step. */
void glKosMatrixDirty() {
	gl_matrix_dirty = GL_TRUE;
}
