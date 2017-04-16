// myglview.cpp : implementation of the CMyglView class
//
#include "stdafx.h"
#include <windows.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include "drawgl.h"
#include "COpenGL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static GLfloat radius;
static RECT	oldrect;

GLvoid DrawScene(RECT rc)
{
    COpenGL gl;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
      glTranslatef(0.0f, 0.0f, -radius);

      drawCone();

      drawPyramid();
    glPopMatrix();
    glFinish();

    HDC hdc = gl.wglGetCurrentDC();
    SwapBuffers(hdc);

}


GLvoid initialize(HWND hWnd)
{
    GLfloat	aspect;
    GLdouble near_plane = 3.0;
    GLdouble far_plane = 7.0;
    GLdouble maxObjectSize = 3.0;

    GetClientRect(hWnd, &oldrect);

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClearDepth( 1.0 );

    glEnable(GL_DEPTH_TEST);

    glMatrixMode( GL_PROJECTION );
    aspect = (GLfloat) oldrect.right / oldrect.bottom;;
    gluPerspective( 45.0, aspect, near_plane, far_plane );
    glMatrixMode( GL_MODELVIEW );

    radius = (GLfloat)(near_plane + maxObjectSize/2.0);
}

GLvoid resize(HWND hWnd)
{
    RECT	rect;

    GetClientRect(hWnd, &rect);

    glViewport(0, 0, rect.right, rect.bottom);

    if((oldrect.right > rect.right) || (oldrect.bottom > rect.bottom))
	PostMessage (hWnd, WM_PAINT, 0, 0L);

    oldrect.right = rect.right;
    oldrect.bottom = rect.bottom;
}

GLvoid drawCone(GLvoid)
{
    GLUquadricObj *quadObj;

    glColor3d(0.0, 1.0, 0.0);

    glPushMatrix();
	glTranslated(-1.0, 0.0, 0.0);
        quadObj = gluNewQuadric();
        gluQuadricDrawStyle(quadObj, GLU_FILL);
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluCylinder(quadObj, 1.0, 0.0, 1.0, 20, 10);
        gluDeleteQuadric(quadObj);
    glPopMatrix();

}

GLvoid drawPyramid(GLvoid)
{

    glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	    glColor3d(1.0, 0.0, 0.0);
	    glVertex3d(0.0, 1.0, 0.0);
	    glColor3d(0.0, 1.0, 0.0);
	    glVertex3d(-1.0, 0.0, 0.0);
	    glColor3d(0.0, 0.0, 1.0);
	    glVertex3d(0.0, 0.0, 1.0);
	    glColor3d(0.0, 1.0, 0.0);
	    glVertex3d(1.0, 0.0, 0.0);
	glEnd();
    glPopMatrix();
}
