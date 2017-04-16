#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include <math.h>

#define COLORINDEX 1 // Use color-index mode code when COLORINDEX is 1.

//
// OnResize
//
BOOL CScene::OnResize(int cx, int cy)
{
    //
    // Set up the mapping of 3-space to screen space
    //
    GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	OutputGlError("Clear") ;
    glMatrixMode(GL_PROJECTION); OutputGlError("MatrixMode") ;
    glLoadIdentity();
    gluPerspective(30.0, gldAspect, 1.0, 10.0);
    glViewport(0, 0, cx, cy);

	return TRUE ;
}

//
// OnInit
//
BOOL CScene::OnInit()
{
	// Faster than using glScale.
	GLdouble size = 0.5 ;
	GLdouble dsize = 0.35 ; // Size for Dodecadedron

	
	// Enable depth calculations
    glEnable(GL_DEPTH_TEST);  		OutputGlError("glEnable (GL_DEPTH_TEST);") ;

#if COLORINDEX
	// Set material properties.
    GLfloat matShiny[] = { 120.0f };
    glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);
#else
	// Set the material color to follow the current color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;
#endif

	// Enable lighting calculations
	glEnable(GL_LIGHTING) ; 		OutputGlError("glEnable (GL_LIGHTING) ;") ;
	glEnable(GL_LIGHT0) ;			OutputGlError("glEnable (GL_LIGHT0) ;") ;

	// Set the color to clear the screen
#if COLORINDEX
	glClearIndex(0.0f) ;
#else
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
#endif

	//
	// Build a display list for the cube.
	//    
	glNewList(Box, GL_COMPILE) ; 
	 	//
	    // Draw the six faces of the cube.
	    //
	    glBegin(GL_POLYGON); // right
			glNormal3d(  0.0,  0.0,  size);
	        glVertex3d( size,  size, size); 
	        glVertex3d(-size,  size, size);            
	        glVertex3d(-size, -size, size);           
	        glVertex3d( size, -size, size);            
	    glEnd();

	    glBegin(GL_POLYGON);	//left
			glNormal3d( 0.0,  0.0, -size);
	        glVertex3d( size,  size, -size);
	        glVertex3d( size, -size, -size);           
	        glVertex3d(-size, -size, -size);          
	        glVertex3d(-size,  size, -size);           
	    glEnd();

	    glBegin(GL_POLYGON); //Font
			glNormal3d(-size,  0.0,  0.0);
	        glVertex3d(-size,  size,  size);
	        glVertex3d(-size,  size, -size);           
	        glVertex3d(-size, -size, -size);          
	        glVertex3d(-size, -size,  size);           
	    glEnd();

	    glBegin(GL_POLYGON);  //Back
			glNormal3d(size,  0.0,  0.0);
	        glVertex3d(size,  size,  size);
	        glVertex3d(size, -size,  size);            
	        glVertex3d(size, -size, -size);           
	        glVertex3d(size,  size, -size);            
	    glEnd();

	    glBegin(GL_POLYGON);  //Top
			glNormal3d( 0.0, size,  0.0);
	        glVertex3d(-size, size, -size);
	        glVertex3d(-size, size,  size);            
	        glVertex3d( size, size,  size);             
	        glVertex3d( size, size, -size);            
	    glEnd();

	    glBegin(GL_POLYGON);	//Bottom
			glNormal3d( 0.0, -size,  0.0);
	        glVertex3d(-size, -size, -size);
	        glVertex3d( size, -size, -size);           
	        glVertex3d( size, -size,  size);            
	        glVertex3d(-size, -size,  size);           
	    glEnd();
	glEndList() ;			   

	//
	// Build a display list for the pyramid.
	//
	glNewList(Pyramid, GL_COMPILE) ; OutputGlError("glNewList: Pyramid") ;
 	//
    // Draw the pyramid
    //
    	glBegin(GL_POLYGON); 
			glNormal3d(-size,-size,-size) ;
			glVertex3d( size,-size,-size) ; //2
			glVertex3d(-size,-size, size) ;	//3
			glVertex3d(-size, size,-size) ;	//4
		glEnd() ;

    	glBegin(GL_POLYGON); 
			glNormal3d(-size, size, size) ;
			glVertex3d( size, size, size) ; //1
			glVertex3d(-size, size,-size) ;	//4
			glVertex3d(-size,-size, size) ;	//3
		glEnd() ;

    	glBegin(GL_POLYGON); 
			glNormal3d( size, size,-size) ;
			glVertex3d( size, size, size) ; //1
			glVertex3d( size,-size,-size) ; //2
			glVertex3d(-size, size,-size) ;	//4
		glEnd() ;

    	glBegin(GL_POLYGON); 
			glNormal3d( size,-size, size) ;
			glVertex3d( size, size, size) ; //1
			glVertex3d(-size,-size, size) ;	//3
			glVertex3d( size,-size,-size) ; //2
		glEnd() ;

	glEndList() ;

	//
	// Build isplay list for Dodecahedron
	//
	GLdouble t = ((sqrt(5) - 1.0) / 2.0) ; 
	GLdouble tt = t*t ;
	t *= dsize ;
	tt *= dsize ;

	glNewList(Dodec, GL_COMPILE) ; OutputGlError("glNewList: Dodec") ;
    	glBegin(GL_POLYGON); // Face 0
			glNormal3d(0, dsize, t) ;
			glVertex3d(  t,    t,    t) ; // Vertex  0
			glVertex3d( tt,dsize,    0) ; // Vertex  7
			glVertex3d(-tt,dsize,    0) ; // Vertex  8
			glVertex3d( -t,    t,    t) ; // Vertex 15
			glVertex3d(  0,   tt,dsize) ; // Vertex  4
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 1
			glNormal3d(0, dsize, -t) ;
			glVertex3d(  0,   tt,-dsize) ; // Vertex 10
			glVertex3d( -t,    t,    -t) ; // Vertex  9
			glVertex3d(-tt,dsize,     0) ; // Vertex  8
			glVertex3d(	tt,dsize,     0) ; // Vertex  7
			glVertex3d(  t,    t,    -t) ; // Vertex  6
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 2
			glNormal3d(dsize, t, 0) ;
			glVertex3d(    t,    t,   t) ; // Vertex  0
			glVertex3d(dsize,    0,  tt) ; // Vertex  1
			glVertex3d(dsize,    0, -tt) ; // Vertex  5
			glVertex3d(	   t,    t,  -t) ; // Vertex  6
			glVertex3d(   tt,dsize,   0) ; // Vertex  7
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 3
			glNormal3d(dsize, -t, 0) ;
			glVertex3d(dsize,     0,  tt) ; // Vertex  1
			glVertex3d(    t,    -t,   t) ; // Vertex  2
			glVertex3d(   tt,-dsize,   0) ; // Vertex 12
			glVertex3d(	   t,    -t,  -t) ; // Vertex 11
			glVertex3d(dsize,     0, -tt) ; // Vertex  5
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 4
			glNormal3d(0, -dsize, -t) ;
			glVertex3d(  t,    -t,    -t) ; // Vertex 11
			glVertex3d( tt,-dsize,     0) ; // Vertex 12
			glVertex3d(-tt,-dsize,     0) ; // Vertex 13
			glVertex3d( -t,    -t,    -t) ; // Vertex 16
			glVertex3d(  0,   -tt,-dsize) ; // Vertex 17
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 5
			glNormal3d(0, -dsize, t) ;
			glVertex3d( -t,    -t,    t) ; // Vertex 18
			glVertex3d(-tt,-dsize,    0) ; // Vertex 13
			glVertex3d( tt,-dsize,    0) ; // Vertex 12
			glVertex3d(  t,    -t,    t) ; // Vertex  2
			glVertex3d(  0,   -tt,dsize) ; // Vertex  3
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 6
			glNormal3d(t, 0, dsize) ;
			glVertex3d(    0,  tt,dsize) ; // Vertex  4
			glVertex3d(    0, -tt,dsize) ; // Vertex  3
			glVertex3d(    t,  -t,    t) ; // Vertex  2
			glVertex3d(dsize,   0,   tt) ; // Vertex  1
			glVertex3d(    t,   t,    t) ; // Vertex  0
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 7
			glNormal3d(-t, 0, dsize) ;
			glVertex3d(     0, -tt,dsize) ; // Vertex  3
			glVertex3d(     0,  tt,dsize) ; // Vertex  4
			glVertex3d(    -t,   t,    t) ; // Vertex 15
			glVertex3d(-dsize,   0,   tt) ; // Vertex 14
			glVertex3d(    -t,  -t,    t) ; // Vertex 18
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 8
			glNormal3d(t, 0, -dsize) ;
			glVertex3d(    0, -tt,-dsize) ; // Vertex 17
			glVertex3d(    0,  tt,-dsize) ; // Vertex 10
			glVertex3d(    t,   t,    -t) ; // Vertex  6
			glVertex3d(dsize,   0,   -tt) ; // Vertex  5
			glVertex3d(    t,  -t,    -t) ; // Vertex 11
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 9
			glNormal3d(-t, 0, -dsize) ;
			glVertex3d(    -t,   t,    -t) ; // Vertex  9
			glVertex3d(     0,  tt,-dsize) ; // Vertex 10
			glVertex3d(     0, -tt,-dsize) ; // Vertex 17
			glVertex3d(    -t,    -t,  -t) ; // Vertex 16
			glVertex3d(-dsize,   0,   -tt) ; // Vertex 19
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 10
			glNormal3d(-dsize, t, 0) ;
			glVertex3d(   -tt,dsize,   0) ; // Vertex  8
			glVertex3d(    -t,    t,  -t) ; // Vertex  9
			glVertex3d(-dsize,    0, -tt) ; // Vertex 19
			glVertex3d(-dsize,    0,  tt) ; // Vertex 14
			glVertex3d(    -t,    t,   t) ; // Vertex 15
		glEnd() ;

    	glBegin(GL_POLYGON); // Face 11
			glNormal3d(-dsize, -t, 0) ;
			glVertex3d(-dsize,     0, -tt) ; // Vertex 19
			glVertex3d(    -t,    -t,  -t) ; // Vertex 16
			glVertex3d(   -tt,-dsize,   0) ; // Vertex 13
			glVertex3d(    -t,    -t,   t) ; // Vertex 18
			glVertex3d(-dsize,     0,  tt) ; // Vertex 14
		glEnd() ;
	glEndList() ;

	return TRUE ;
}

//
// OnRender
//
BOOL CScene::OnRender()
{
#if COLORINDEX
	// Set up material color ramps.
	GLfloat matRed[] = {80.0f, 111.0f, 143.0f } ;
	GLfloat matGreen[] = {144.0f, 175.0f, 207.0f } ;
	GLfloat matPurple[] = {16.0f, 47.0f, 79.0f } ;	
#else	
	// Set up some colors
	static GLdouble red[3] = {0.8, 0.0, 0.0 } ; 
	static GLdouble green[3] = {0.0, 0.75, 0.0} ;
	static GLdouble purple[3] = {1.0, 0.14, 0.6667} ; 
#endif

	// Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // Draw the box.
    //		
    glMatrixMode(GL_MODELVIEW); 	OutputGlError("MatrixMode") ;
	
	// Translate and rotate the axis.
	glLoadIdentity();
    glTranslated(0.5, 0.5, -4.5 ); 
    glRotated(30/*m_angle[Box].cx*/, 1.0, 0.0, 0.0);
    glRotated(70/*m_angle[Box].cy*/, 0.0, 1.0, 0.0);

	// Change the current color to green.
#if COLORINDEX
	glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, matGreen) ;	
#else
	glColor3dv(green) ;
#endif

	// Draw the box.
	glCallList(Box) ;

	//
	// Draw the pyramid.
	//
	glLoadIdentity();
    glTranslated(-0.7, 0.5, -4.5 );
 	glRotated(150/*m_angle[Pyramid].cx*/, 1.0, 0.0, 0.0);
    glRotated(120/*m_angle[Pyramid].cy*/, 0.0, 1.0, 0.0);

#if COLORINDEX
	glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, matPurple) ;	
#else
	glColor3dv(purple) ;
#endif
	glCallList(Pyramid) ;

  	//
	// Draw the Dodecahedron.
	//
	glLoadIdentity();
    glTranslated(0.0, 0.0, -2.5 );
 	glRotated(30 /*m_angle[Dodec].cx*/, 1.0, 0.0, 0.0);
    glRotated(70 /*m_angle[Dodec].cy*/, 0.0, 1.0, 0.0);

#if COLORINDEX
	glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, matRed) ;	
#else
	glColor3dv(red) ;
#endif
	glCallList(Dodec) ;

    //
    // Flush the drawing pipeline.
    //
    glFlush();	

	return TRUE ;
}

//
// OnCreatePaletteCI - Build the color ramps for Color-index mode.
//
BOOL CScene::OnCreatePaletteCI(LOGPALETTE* pPal)
{
	// Code assumes a 256 color palette 

	// Black
	pPal->palPalEntry[0].peRed  = 0;
	pPal->palPalEntry[0].peGreen= 0	  ;
	pPal->palPalEntry[0].peBlue = 0;

	// White
	pPal->palPalEntry[255].peRed  = 255 ;
	pPal->palPalEntry[255].peGreen= 255	  ;
	pPal->palPalEntry[255].peBlue = 255;

	// Purple Ramp
	for (int i=0; i< 32; i++)
	{
		// 15 to 47 is a linear ramp from black to purple		
		pPal->palPalEntry[16+i].peRed  = 255* i / 32 ;
		pPal->palPalEntry[16+i].peGreen= 0	  ;
		pPal->palPalEntry[16+i].peBlue = 255* i / 32 ;

		// 48 to 79 is a linear ramp from purple to white
		pPal->palPalEntry[48+i].peRed  = 255 ;
		pPal->palPalEntry[48+i].peGreen= 255* i / 32 ;
		pPal->palPalEntry[48+i].peBlue = 255 ;
	}

	// Red Ramp
	for (i=0; i< 32; i++)
	{		
		// 80 to 111 is a linear ramp from black to red
		pPal->palPalEntry[80+i].peRed  = 255* i / 32 ;
		pPal->palPalEntry[80+i].peGreen= 0	  ;
		pPal->palPalEntry[80+i].peBlue = 0 ;

		// 112 to 143 is a linear ramp from red to white
		pPal->palPalEntry[112+i].peRed  = 255 ;
		pPal->palPalEntry[112+i].peGreen= 255 * i / 32 ;
		pPal->palPalEntry[112+i].peBlue = 255 * i / 32 ;
	}

	// Green Ramp
	for (i=0; i< 32; i++)
	{		
		// 144 to 175 is a linear ramp from black to green
		pPal->palPalEntry[144+i].peRed  = 0;
		pPal->palPalEntry[144+i].peGreen= 255 * i / 32 ;
		pPal->palPalEntry[144+i].peBlue = 0 ;

		// 176 to 207 is a linear ramp from green to white
		pPal->palPalEntry[176+i].peRed  = 255 * i / 32  ;
		pPal->palPalEntry[176+i].peGreen= 255  ;
		pPal->palPalEntry[176+i].peBlue = 255 * i / 32 ;
	}

	return TRUE ;	
}
