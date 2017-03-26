
/*
	KGL-X 0.0

	gloparray.c

	(c) 2002 heinrich tillack

	

   under KOS license


*/

#include <GL/gl.h>

#include "glinternal.h"

#if 0
extern void glopColor(GLParam * p) ;
extern void glopVertex(GLParam * p) ;

extern void gl_add_op(GLParam *p);
#endif


int gl_vertex_array_size;
int gl_vertex_array_stride;
GLfloat  *gl_vertex_array;

int gl_normal_array_stride ;
GLfloat *gl_normal_array ;

int gl_color_array_size ;
int gl_color_array_stride;
GLfloat *gl_color_array ;

int gl_texcoord_array_size ;
int gl_texcoord_array_stride;
GLfloat *gl_texcoord_array ;

static GLbitfield gl_client_states=0;

//extern GLfloat vert_u,vert_v;

/* */

void glopArrayElement(GLParam *param) {
    int i;
    int idx = param[1].i;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    if(gl_client_states & COLOR_ARRAY) {
        GLParam p[5];
        int		size = gl_color_array_size;
        i = idx * (size + gl_color_array_stride);
        p[1].f = gl_color_array[i];
        p[2].f = gl_color_array[i + 1];
        p[3].f = gl_color_array[i + 2];
        p[4].f = size > 3 ? gl_color_array[i + 3] : 1.0f;
        glopColor(p);
    }

#if NOT_IMPLEMENTED
    if(gl_client_states & NORMAL_ARRAY) {
        i = idx * (3 + gl_normal_array_stride);
        nx = gl_normal_array[i];
        ny = gl_normal_array[i + 1];
        nz = gl_normal_array[i + 2];
        nw=.....
       }
#endif

       if(gl_client_states & TEXCOORD_ARRAY) {
           int size = gl_texcoord_array_size;
           i = idx * (size + gl_texcoord_array_stride);

           vert_u = gl_texcoord_array[i];
           vert_v = gl_texcoord_array[i + 1];

       }

       if(gl_client_states & VERTEX_ARRAY) {
           GLParam p[5];
           int		size = gl_vertex_array_size;
           i = idx * (size + gl_vertex_array_stride);
           p[1].f = gl_vertex_array[i];
           p[2].f = gl_vertex_array[i + 1];
           p[3].f = size > 2 ? gl_vertex_array[i + 2] : 0.0f;
           p[4].f = size > 3 ? gl_vertex_array[i + 3] : 1.0f;
           glopVertex(p);
       }
   }


   /* */
   void glopEnableClientState( GLParam *p) {
       gl_client_states |= p[1].i;
   }

   /* */
   void glopDisableClientState( GLParam *p) {
       gl_client_states &= p[1].i;
   }

   /* */
   void glopVertexPointer( GLParam *p) {
       gl_vertex_array_size = p[1].i;
       gl_vertex_array_stride = p[2].i;
       gl_vertex_array = (GLfloat*)p[3].p;
   }

   /* */
   void glopColorPointer( GLParam *p) {
       gl_color_array_size = p[1].i;
       gl_color_array_stride = p[2].i;
       gl_color_array = (GLfloat*)p[3].p;
   }

   /* */
   void glopNormalPointer( GLParam *p) {
       gl_normal_array_stride = p[1].i;
       gl_normal_array = (GLfloat*)p[2].p;
   }

   /* */
   void glopTexCoordPointer( GLParam *p) {
       gl_texcoord_array_size = p[1].i;
       gl_texcoord_array_stride = p[2].i;
       gl_texcoord_array = (GLfloat*)p[3].p;
   }
