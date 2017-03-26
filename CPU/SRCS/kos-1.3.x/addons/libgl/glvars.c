/* KallistiGL for KOS ##version##

   glvars.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"

CVSID("$Id: glvars.c,v 1.11 2002/06/28 04:52:42 axlen Exp $");

/* Variable definitions */

/* Background clear color (not currently used) */
GLfloat gl_clear_color[4];

/* Capabilities bitfield: toggles for glEnable() / glDisable() */
GLbitfield gl_capabilities;

/* Current primitive type (or -1) */
GLenum gl_prim_type;

/* Current polygon context */
pvr_poly_cxt_t gl_poly_cxt;

/* Poly header buffer submitted? */
GLboolean gl_pbuf_submitted;

/* Current Blend functions */
GLint gl_blend_src = PVR_BLEND_SRCALPHA;
GLint gl_blend_dst = PVR_BLEND_INVSRCALPHA;

/* Currently selected texture */
pvr_poly_cxt_t *gl_cur_texture;

/* Null texture for colored polys */
pvr_poly_cxt_t gl_null_texture;

/* Screen size */
GLsizei gl_screen_width;
GLsizei gl_screen_height;

/* Viewport size */
GLint gl_viewport_x1, gl_viewport_y1,
	gl_viewport_width, gl_viewport_height;

/* Viewport mapping */
GLfloat gl_viewport_scale[3];
GLfloat gl_viewport_offset[3];

/* Scissor clipping */
GLint gl_scissor_x;
GLint gl_scissor_y;
GLsizei gl_scissor_width;
GLsizei gl_scissor_height; 
GLboolean gl_scissor_dirty = GL_FALSE;

/* Depth range */
GLclampf gl_depthrange_near;
GLclampf gl_depthrange_far;

/* Transformation matrices */
matrix_t gl_trans_mats[GL_MATRIX_COUNT] __attribute__((aligned(32)));
int gl_matrix_mode;
GLboolean gl_matrix_dirty;

/* Frustum attributes */
gl_frustum_t gl_frustum;

/* Enabled lists */
GLbitfield gl_enabled_lists;

/* Currently active list */
GLbitfield gl_active_list;

/* Face culling enabled/disabled */
GLboolean gl_cull_face = GL_FALSE;

/* Front face */
GLenum gl_front_face = GL_CCW;

/* Culling mode */
GLenum gl_cull_mode = GL_BACK;

/* Fog Attributes */ 
GLfloat gl_fog_color[4] = {0.5f, 0.5f, 0.5f, 1.0f}; /* r, g, b, a */
GLfloat gl_fog_density = 1.0f;   /* Density >= 0.0 - exp exp2 fog */
GLfloat gl_fog_start = 0.0f;     /* linear fog                    */
GLfloat gl_fog_end = 1.0f;       /* linear fog                    */
GLfloat gl_fog_index = 0.0f;     /* unused                        */
GLenum  gl_fog_mode = GL_EXP;

/* Point size */
GLfloat gl_point_size = 1.0f;

/* Vertex buffers */
/* Pre-xformed vertex buffer */
gl_vertex_t gl_vbuf[VBUF_SIZE] __attribute__((aligned(8192)));
/* Post-xformed vertex buffer */
gl_vertex_t gl_xbuf[VBUF_SIZE] __attribute__((aligned(8192)));
int gl_vbuf_top;

