/* KallistiGL for KOS ##version##

   gldepth.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

#include <assert.h>
#include <stdio.h>

CVSID("$Id: gldepth.c,v 1.7 2002/04/03 03:34:22 axlen Exp $");

/* Depth buffer (non-functional, just stubs) */
void glClearDepth(GLclampd depth) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");	
}

void glDepthFunc(GLenum func) {
	/* Note regarding the mapping of OpenGL depth stuff to the PVR2DC:
	   
           The depth compare modes should be "conceptually" the same except
	   for two points:
               1) You have a floating point "Depth buffer" and
               2) DC uses 1/W to compare so 1 (or higher if your clipping
	          is off!) = near and 0=infinity.
           Therefore > or >= is probably what you want for closer objects to be            visible. - Simon Fenney 
	*/
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");	
	switch(func)
	{
	case GL_ALWAYS:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_ALWAYS;
		break;
	case GL_LESS:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_GEQUAL;
		break;
	case GL_NOTEQUAL:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_NOTEQUAL;
		break;
	case GL_LEQUAL:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_GREATER;
		break;
	case GL_GREATER:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_LEQUAL;
		break;
	case GL_EQUAL:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_EQUAL;
		break;
	case GL_GEQUAL:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_LESS;
		break;
	case GL_NEVER:
		gl_poly_cxt.depth.comparison  = PVR_DEPTHCMP_NEVER;
		break;
	default:
		assert_msg(0, "Invalid depth comparison function.");
	}
	
	gl_pbuf_submitted = GL_FALSE;
}

void glDepthMask(GLboolean flag) {
	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");	
	if (flag) {
		gl_poly_cxt.depth.write  = PVR_DEPTHWRITE_ENABLE;
	} else {
		gl_poly_cxt.depth.write  = PVR_DEPTHWRITE_DISABLE;
	}
	gl_pbuf_submitted = GL_FALSE;
}
