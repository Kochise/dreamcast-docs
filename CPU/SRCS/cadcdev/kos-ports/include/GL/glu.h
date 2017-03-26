#ifndef __GL_GLU_H
#define __GL_GLU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <GL/gl.h>

#define GLU_FALSE	0
#define GLU_TRUE	1

void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear,
	GLfloat zFar);

void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
          GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy,
          GLfloat upz);

__END_DECLS

#endif	/* __GL_GLU_H */

