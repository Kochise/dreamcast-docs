#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "CSceneDodec.h"

#include "shapes.h"

//
// OnResize - Set up projection from 3-D to 2-D. 
//
BOOL CSceneDodec::OnResize(int cx, int cy)
{
   GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
   OutputGlError("Clear") ;
   glMatrixMode(GL_PROJECTION); OutputGlError("MatrixMode") ;
   glLoadIdentity();
   gluPerspective(30.0, gldAspect, 1.0, 10.0);
   glViewport(0, 0, cx, cy);

	return TRUE ;
}

//
// OnInit - Initialize OpenGL.
//
BOOL CSceneDodec::OnInit()
{
	// Faster than using glScale.
	GLdouble dsize = 0.35 ; // Size for Dodecadedron

	// Enable depth calculations
   glEnable(GL_DEPTH_TEST);  		OutputGlError("glEnable (GL_DEPTH_TEST);") ;

	// Set the material color to follow the current color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;

	// Enable lighting calculations
	glEnable(GL_LIGHTING) ; 		OutputGlError("glEnable (GL_LIGHTING) ;") ;
	glEnable(GL_LIGHT0) ;			OutputGlError("glEnable (GL_LIGHT0) ;") ;
	
	// Set the color to clear the screen
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f) ;

	//
	// Build display list for Dodecahedron. See shapes.cpp for DodecList.
	//
	DodecList(1, dsize) ;

	return TRUE ;
}

//
// OnRender - Render the image.
//
BOOL CSceneDodec::OnRender()
{
   // Set up some colors
   static GLdouble red[3] = {0.8, 0.0, 0.0 } ; 
   static GLdouble green[3] = {0.0, 0.75, 0.0} ;
   static GLdouble purple[3] = {1.0, 0.14, 0.6667} ; 

   // Clear the color and depth buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW); 	OutputGlError("MatrixMode") ;

   //
   // Draw the Dodecahedron.
   //
   glLoadIdentity();
   glTranslated(0.0, 0.0, -2.5 );
   glRotated(30 /*m_angle[Dodec].cx*/, 1.0, 0.0, 0.0);
   glRotated(70 /*m_angle[Dodec].cy*/, 0.0, 1.0, 0.0);

   glColor3dv(red) ;
   glCallList(1) ;

   //
   // Flush the drawing pipeline.
   //
   glFlush();	

	return TRUE ;
}
