/* KGL-X 0.2

   glapi.c


   (c) 2002 heinrich tillack

   under KOS license
*/

/*

	glapi.c defines thos glxxx(*) functions which
	could be or actually are part of a displaylist.

	XXX TO DO: glFog*() ??!
*/

#include "kfeatures.h"



#include "glinternal.h"

#include <assert.h>

extern void gl_add_op(GLParam *p);

/* glBegin / glEnd */

void glBegin(GLenum mode) {

    GLParam p[2];

    p[0].op=OP_Begin;
    p[1].i=mode;

    gl_add_op(p);
}

void glEnd(void) {
    GLParam p[1];

    p[0].op=OP_End;

    gl_add_op(p);
}



/* Vertex */

void glVertex4f(GLfloat x, GLfloat y, GLfloat z,GLfloat w) {
    GLParam p[5];

    p[0].op=OP_Vertex;
    p[1].f=x;
    p[2].f=y;
    p[3].f=z;
    p[4].f=w;

    gl_add_op(p);
}

void glVertex4fv(GLfloat *v) {
    glVertex4f(v[0], v[1], v[2], v[3]);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    glVertex4f(x,y,z,1.0f);
}

void glVertex3fv(GLfloat *v) {
    glVertex4f(v[0], v[1], v[2], 1.0f);
}

void glVertex2f(GLfloat x,GLfloat y) {
    glVertex4f(x, y, 0.0f,1.0f);
}

void glVertex2fv(GLfloat *v) {
    glVertex4f(v[0], v[1], 0.0f,1.0f);
}

/* Normal */

void  glNormal3f(float x,float y,float z)
{
    GLParam p[4];

    p[0].op=OP_Normal;
    p[1].f=x;
    p[2].f=y;
    p[3].f=z;

    gl_add_op(p);
}

void glNormal3fv( GLfloat  *v)
{
    glNormal3f(v[0],v[1],v[2]);
}

/* Color */

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {

    GLParam p[5];

    p[0].op=OP_Color;
    p[1].f=red;
    p[2].f=green;
    p[3].f=blue;
    p[4].f=alpha;

    gl_add_op(p);
}

void glColor4fv( GLfloat *v) {

    GLParam p[5];

    p[0].op=OP_Color;
    p[1].f=v[0];
    p[2].f=v[1];
    p[3].f=v[2];
    p[4].f=v[3];

    gl_add_op(p);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    glColor4f(red,green,blue,1.0f);
}

void glColor3fv( GLfloat *v)
{
    glColor4f(v[0],v[1],v[2],1.0f);
}


void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {

    glColor4f((float)red/255,(float)green/255,(float)blue/255,(float)alpha/255);
}



void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    glColor4f((float)red/255,(float)green/255,(float)blue/255,1);
}

// void glColor3ubv( GLubyte *v) {
// 	SET_COLOR(v[0],v[1],v[2],0xff);
// }

// void glColor4ubv( GLubyte *v) {
// 	SET_COLOR(v[0],v[1],v[2],v[3]);
// }

/* TexCoord */

void  glTexCoord2f(GLfloat s, GLfloat t)
{
    GLParam p[3];

    p[0].op=OP_TexCoord;
    p[1].f=s;
    p[2].f=t;

    gl_add_op(p);
}

void glTexCoord2fv( GLfloat *v)
{
    glTexCoord2f(v[0],v[1]);
}

// void glEdgeFlag(int flag)
// {
//   GLParam p[2];

//   p[0].op=OP_EdgeFlag;
//   p[1].i=flag;

//   gl_add_op(p);
// }


/* Depth */

// /* Depth buffer (non-functional, just stubs) */
// void glClearDepth(GLclampd depth) {

// }

// void glDepthFunc(GLenum func) {

//     GLParam p[2];

//     p[0].op=OP_DepthFunc;
//     p[1].i=func;


//     gl_add_op(p);

// }

// void glDepthMask(GLboolean flag) {

//     GLParam p[2];

//     p[0].op=OP_DepthMask;
//     //XXX conversion ok?
//     p[1].i=(int)flag;


//     gl_add_op(p);

// }

/* Transform */

void glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    GLParam p[4];

    p[0].op=OP_Translatef;
    p[1].f=x;
    p[2].f=y;
    p[3].f=z;

    gl_add_op(p);
}



void glRotatef(GLfloat angle,
               GLfloat x, GLfloat y, GLfloat z) {

    GLParam p[5];

    p[0].op=OP_Rotatef;
    p[1].f=angle;
    p[2].f=x;
    p[3].f=y;
    p[4].f=z;

    gl_add_op(p);
}


void glScalef(GLfloat x, GLfloat y, GLfloat z) {

    GLParam p[4];

    p[0].op=OP_Scalef;
    p[1].f=x;
    p[2].f=y;
    p[3].f=z;

    gl_add_op(p);
}

/* Texture */

void glBindTexture(GLenum type, GLuint texture) {

    GLParam p[3];

    p[0].op=OP_BindTexture;
    p[1].i=(int)type;
    p[2].ui=(unsigned int)texture;

    gl_add_op(p);

}

/* Misc API */
void glPolygonMode (GLenum face, GLenum mode)
{
    GLParam p[3];

    p[0].op=OP_PolygonMode;

    p[1].i=face;
    p[2].i=mode;

    gl_add_op(p);

}


/* Special Functions */


void glCallList( GLuint list )
{
    GLParam p[2];

    p[0].op=OP_CallList;
    p[1].ui=list;

    gl_add_op(p);
}


/* Non standard functions */

void glDebug(int mode)
{
    kos_print_flag=mode;
}



/* Arrays */

/* */
inline void glArrayElement(GLint i) {
    GLParam p[2];
    p[0].op = OP_ArrayElement;
    p[1].i = i;
    gl_add_op(p);
}

/* */
void glDrawArrays( GLenum mode, GLint first, GLsizei count )
{
    int i;

    glBegin(mode);
    for(i=first;i<first+count;i++) {
        glArrayElement(i);
    }
    glEnd();
}

/* */
void glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices )
{
    int i;
    const GLint *index;


    assert((type==GL_INT)||(type==GL_UNSIGNED_INT));
    assert(indices!=(GLvoid*)0);

    index = indices;

    glBegin(mode);
    for(i=0;i<count;i++) {
        glArrayElement(index[i]);
    }
    glEnd();
}
/* */
void  glEnableClientState(GLenum array) {
    GLParam p[2];
    p[0].op = OP_EnableClientState;

    switch(array) {
    case GL_VERTEX_ARRAY:			p[1].i = VERTEX_ARRAY; break;
    case GL_NORMAL_ARRAY:			p[1].i = NORMAL_ARRAY; break;
    case GL_COLOR_ARRAY:			p[1].i = COLOR_ARRAY; break;
    case GL_TEXTURE_COORD_ARRAY:	p[1].i = TEXCOORD_ARRAY; break;
    default:						assert(0); break;
    }

    gl_add_op(p);
}


/* */
void  glDisableClientState(GLenum array) {
    GLParam p[2];
    p[0].op = OP_DisableClientState;

    switch(array) {
    case GL_VERTEX_ARRAY:			p[1].i = ~VERTEX_ARRAY; break;
    case GL_NORMAL_ARRAY:			p[1].i = ~NORMAL_ARRAY; break;
    case GL_COLOR_ARRAY:			p[1].i = ~COLOR_ARRAY; break;
    case GL_TEXTURE_COORD_ARRAY:	p[1].i = ~TEXCOORD_ARRAY; break;
    default:						assert(0); break;
    }

    gl_add_op(p);
}


/* */
void  glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    GLParam p[4];
    assert(type == GL_FLOAT);
    p[0].op = OP_VertexPointer;
    p[1].i = size;
    p[2].i = stride;
    p[3].p = (void *) pointer;
    gl_add_op(p);
}


/* */
void  glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    GLParam p[4];
    assert(type == GL_FLOAT);
    p[0].op = OP_ColorPointer;
    p[1].i = size;
    p[2].i = stride;
    p[3].p = (void *) pointer;
    gl_add_op(p);
}


/* FIXME:unused */
void  glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer) {
    GLParam p[3];
    assert(type == GL_FLOAT);
    p[0].op = OP_NormalPointer;
    p[1].i = stride;
    p[2].p = (void *) pointer;
    //gl_add_op(p);
}


/* */
void  glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
    GLParam p[4];
    assert(type == GL_FLOAT);
    assert(size>0 && size<=2);

    p[0].op = OP_TexCoordPointer;
    p[1].i = size;
    p[2].i = stride;
    p[3].p = (void *) pointer;
}
