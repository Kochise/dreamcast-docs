/* KallistiGL for KOS ##version##

   glinternal.c
   (c)2001 Dan Potter

   $Id: glinternal.h,v 1.13 2002/09/05 07:36:23 bardtx Exp $
*/

#ifndef __GL_GLINTERNAL_H
#define __GL_GLINTERNAL_H

/* Implementation details; not to be used externally */
#include <GL/gl.h>
#include <dc/pvr.h>
#include <dc/matrix.h>

/* AFAIK, the PowerVR simulates a 32bit depth buffer */
#define DEPTHBUFFER_MAX ((GLfloat)0xffffffff)

/* "Clear color" -- really the background plane color */
extern GLfloat gl_clear_color[4];

/* Capability mask (for glEnable() and glDisable()) */
extern GLbitfield gl_capabilities;

/* Enabled lists (PVR specific) */
extern GLbitfield gl_enabled_lists;

/* Current primitive type (GL_TRIANGLES, etc) */
extern GLenum gl_prim_type;

/* Current polygon context */
extern pvr_poly_cxt_t gl_poly_cxt;

/* Poly header buffer submitted? */
extern GLboolean gl_pbuf_submitted;

/* Current Blend functions */
extern GLint gl_blend_src;
extern GLint gl_blend_dst;

/* Currently selected texture header */
extern pvr_poly_cxt_t *gl_cur_texture;

/* a "null" texture header for colored polys */
extern pvr_poly_cxt_t gl_null_texture;

/* Depth range */
extern GLclampf gl_depthrange_near;
extern GLclampf gl_depthrange_far;

/* Screen size */
extern GLsizei gl_screen_width;
extern GLsizei gl_screen_height;

/* Viewport size */
extern GLint gl_viewport_x1, gl_viewport_y1,
	gl_viewport_width, gl_viewport_height;

/* Viewport mapping */
extern GLfloat gl_viewport_scale[3];
extern GLfloat gl_viewport_offset[3];

/* Scissor clipping */
extern GLint gl_scissor_x;
extern GLint gl_scissor_y;
extern GLsizei gl_scissor_width;
extern GLsizei gl_scissor_height;
extern GLboolean gl_scissor_dirty;

/* Transformation matrices; possibilities are:
   GL_MODELVIEW
   GL_PROJECTION
   GL_TEXTURE
*/
extern matrix_t gl_trans_mats[GL_MATRIX_COUNT]  __attribute__((aligned(32)));
extern int gl_matrix_mode;
extern GLboolean gl_matrix_dirty;

/* Frustum attributes */
typedef struct {
	float left, right, bottom, top, znear, zfar;
} gl_frustum_t;

extern gl_frustum_t gl_frustum;

/* Some happy macros */
#define TXR_ENABLED (gl_capabilities & GL_TEXTURE_2D)
#define AUTOUV_ENABLED (gl_capabilities & GL_KOS_AUTO_UV)
#define FOG_ENABLED (gl_capabilities & GL_FOG)
#define BLEND_ENABLED (gl_capabilities & GL_BLEND)
#define SCISSOR_ENABLED (gl_capabilities & GL_SCISSOR_TEST)
#define USERCLIP_OUTSIDE_ENABLED (gl_capabilities & GL_KOS_USERCLIP_OUTSIDE)
#define MODIFIER_ENABLED (gl_capabilities & GL_KOS_MODIFIER)
#define CHEAP_SHADOW_ENABLED (gl_capabilities & GL_KOS_CHEAP_SHADOW)
#define ZCLIP_ENABLED (gl_capabilities & GL_KOS_NEARZ_CLIPPING)
#define LIGHTING_ENABLED (gl_capabilities & GL_LIGHT0) 

/* Currently active list */
extern GLbitfield gl_active_list;

/* Face culling enabled/disabled */
extern GLboolean gl_cull_face;

/* Front face */
extern GLenum gl_front_face;

/* Culling mode */
extern GLenum gl_cull_mode;

/* Fog Attributes */ 
extern GLfloat gl_fog_color[4];
extern GLfloat gl_fog_density;
extern GLfloat gl_fog_start;
extern GLfloat gl_fog_end;
extern GLfloat gl_fog_index; /* unused */
extern GLenum  gl_fog_mode;

/* Point size */
extern GLfloat gl_point_size; 

/* Vertex buffers
 
   It is important to align the vertex buffers for use with the
   the direct render API. I found 8192 gave the best results, but 32,
   64, and 1024 also worked well. To see cache thrashing in action try
   setting the alignment to 16384 or 32768. The polys per second will
   drop by about half. 
   
   mat_transform seems to work best when the source and destination buffers
   are seperate.  Therefore we have a pre and post transform vertex buffer
   
   I'm quite aware of how wasteful this is.  It's a simple matter that this
   is how you have to treat the PVR to get decent poly drawing rates.
   
   What's needed is a way to collect long vertex [Strips, Fans, Polygons]
   and blast them to the store queue every 16 to 32 verts all the while
   maintaining the proper PVR_CMD_VERTEX and ...EOL requirements.  One
   way might be to keep a copy of the last vertex submitted and toss
   it to the PVR in the glEnd statement. You will have to keep track of
   verts whose z values go < 0 and either clip them to the view frustum or
   cull them entirely.  But you'll have to do this carefully because the PVR
   does not like degenerate triangles or strips. */

typedef struct {
	uint32 flags;
	float x, y, z, w;
	float u, v;
	uint32 argb, oargb;
} gl_vertex_t;

#define VBUF_SIZE 128 
/* Pre-xformed vertex buffer */
extern gl_vertex_t gl_vbuf[VBUF_SIZE] __attribute__((aligned(8192)));
/* Post-xformed vertex buffer */
extern gl_vertex_t gl_xbuf[VBUF_SIZE] __attribute__((aligned(8192)));
extern int gl_vbuf_top;

/* some internal prototypes */
extern void modifier_check_end();
extern void modifier_end();
extern void fix_vfzclip_matrices(); 
extern void vfzclip_check_end();
extern void vfzclip_end();
#endif	/* __GL_GLINTERNAL_H */

