#ifndef __GL_GLU_H
#define __GL_GLU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <GL/gl.h>

#define GLU_FALSE	0
#define GLU_TRUE	1

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear,
	GLdouble zFar);

__END_DECLS

#endif	/* __GL_GLU_H */

