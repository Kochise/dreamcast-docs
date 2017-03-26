/* KallistiGL for KOS ##version##

   glfog.c
   (c)2002 Paul Boese
*/


#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"

#include <assert.h>
#include <dc/pvr.h>

CVSID("$Id: glfog.c,v 1.2 2002/04/03 03:36:15 axlen Exp $");

#define TEST_EQ_4V(a,b)  ((a)[0] == (b)[0] && 	\
			  (a)[1] == (b)[1] &&	\
			  (a)[2] == (b)[2] &&	\
			  (a)[3] == (b)[3])

/* Convert GLint in [-2147483648,2147483647] to GLfloat in [-1.0,1.0] */
#define INT_TO_FLOAT(I)		((2.0F * (I) + 1.0F) * (1.0F/4294967294.0F))

		
/* prototypes */
void Fogfv( GLenum pname, const GLfloat *params );
void DCFogfv( GLenum pname, const GLfloat *params );


/* functions */
void glFogf(GLenum pname, GLfloat param)
{
   glFogfv(pname, &param);
}


void glFogi(GLenum pname, GLint param )
{
   GLfloat fparam = (GLfloat) param;
   glFogfv(pname, &fparam);
}


void glFogiv(GLenum pname, const GLint *params )
{
   GLfloat p[4];
   switch (pname) {
      case GL_FOG_MODE:
      case GL_FOG_DENSITY:
      case GL_FOG_START:
      case GL_FOG_END:
      case GL_FOG_INDEX:
	 p[0] = (GLfloat) *params;
	 break;
      case GL_FOG_COLOR:
	 p[0] = INT_TO_FLOAT( params[0] );
	 p[1] = INT_TO_FLOAT( params[1] );
	 p[2] = INT_TO_FLOAT( params[2] );
	 p[3] = INT_TO_FLOAT( params[3] );
	 break;
      default:
         /* Error will be caught later in Fogfv */
         ;
   }
   glFogfv(pname, p);
}


void glFogfv( GLenum pname, const GLfloat *params )
{
	GLenum m;

	assert_msg(!gl_prim_type, "Not allowed within glBegin/glEnd pair.");
	switch (pname) {
		case GL_FOG_MODE:
			m = (GLenum) (GLint) *params;
			switch (m) {
				case GL_LINEAR:
				case GL_EXP:
				case GL_EXP2:
				break;
			default:
				assert_msg(0, "Unknown fog mode.");
				return;
			}
			if (gl_fog_mode == m)
				return;
			/* flush vertices here */
			gl_fog_mode = m;
			break;
		case GL_FOG_DENSITY:
			if (*params<0.0) {
				assert_msg(0, "Invalid value - fog density < zero.");
				return;
			}
			if (gl_fog_density == *params)
				return;
			/* flush vertices here */
			gl_fog_density = *params;
			break;
		case GL_FOG_START:
			if (gl_fog_start == *params)
				return;
			/* flush vertices here */
			gl_fog_start = *params;
			break;
		case GL_FOG_END:
			if (gl_fog_end == *params)
				return;
			/* flush vertices here */
			gl_fog_end = *params;
			break;
		case GL_FOG_INDEX:
			if (gl_fog_index == *params)
				return;
			/* flush vertices here */
			gl_fog_index = *params;
			break;
		case GL_FOG_COLOR:
			if (TEST_EQ_4V(gl_fog_color, params))
				return;
			/* flush vertices here */
			gl_fog_color[0] = params[0];
			gl_fog_color[1] = params[1];
			gl_fog_color[2] = params[2];
			gl_fog_color[3] = params[3];
			break;
		default:
			assert_msg(0, "Invalid parameter.");
			return;
	}
	DCFogfv( pname, params );
}

/* DC specific interface for fog */

void fog_table_color4fv(GLfloat *v) {
	pvr_fog_table_color(*(v+3), *v, *(v+1), *(v+2)); 
}

/* void fog_set_vertex_color4fv(GLfloat *v) {
	pvr_fog_vertex_color(*(v+3), *v, *(v+1), *(v+2));
} */

void DCFogfv( GLenum pname, const GLfloat *params ) {
	
	/* Just drop thru here and setup DC registers using dcutils fog.
	**
	** Future Note:
	** We should have a GL_KOS_FOG_TYPE enum that will give the user
	** a choice of GL_KOS_FOG_TABLE, GL_KOS_FOG_VERTEX, and maybe
	** GL_KOS_FOG_TABLE2
	*/	
	switch (pname) {
		case GL_FOG_START:
		case GL_FOG_END:
			pvr_fog_far_depth(gl_fog_end);
		case GL_FOG_INDEX:
		case GL_FOG_DENSITY:
		case GL_FOG_COLOR:
			fog_table_color4fv(gl_fog_color);
			/* fog_set_vertex_color4fv(gl_fog_color); */
		case GL_FOG_MODE:
			switch (gl_fog_mode) {
				case GL_EXP:
					pvr_fog_table_exp(gl_fog_density);
					break;
				case GL_EXP2:
					pvr_fog_table_exp2(gl_fog_density);
					break;
				case GL_LINEAR:
					pvr_fog_table_linear(gl_fog_start, gl_fog_end);
					break;
			}
	 	default:
			;
	}
}

