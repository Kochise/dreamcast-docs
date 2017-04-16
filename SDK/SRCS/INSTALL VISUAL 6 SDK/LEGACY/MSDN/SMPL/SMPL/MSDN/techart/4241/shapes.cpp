#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include <math.h>

void CScene::BoxList(int id, GLdouble size)
{
   GLdouble dTexRep ;
	//
	// Build a display list for the cube.
	//    
	glNewList(id, GL_COMPILE) ; 
	 	//
	    // Draw the six faces of the cube.
	    //
		dTexRep = setTexRep(m_imageEgypt) ;
		m_imageEgypt.TexImage2D(this) ;
		if (m_bTexture) glEnable(GL_TEXTURE_2D);    
		glBegin(GL_QUADS); // right  - cw
         glNormal3d(  0.0,  0.0,  size);
         glTexCoord2d(0.0, 0.0) ;
         glVertex3d(-size, -size, size);

         glTexCoord2d(dTexRep, 0.0) ;
         glVertex3d( size, -size, size);            

         glTexCoord2d(dTexRep, dTexRep) ;
         glVertex3d( size,  size, size);

         glTexCoord2d(0.0, dTexRep) ;
         glVertex3d(-size,  size, size);            	                   	         
      glEnd();
		glDisable(GL_TEXTURE_2D);   

	   glBegin(GL_POLYGON);	//left
         glNormal3d( 0.0,  0.0, -size);
         glVertex3d(-size, -size, -size);
         glVertex3d(-size,  size, -size);	                   
         glVertex3d( size,  size, -size);
         glVertex3d( size, -size, -size);
      glEnd();

		dTexRep = setTexRep(m_imageTexMap) ;
		m_imageTexMap.TexImage2D(this) ;
		if (m_bTexture) glEnable(GL_TEXTURE_2D);    
		glBegin(GL_QUADS); //Font - cw
         glNormal3d(-size,  0.0,  0.0);
         glTexCoord2d(0.0, 0.0) ;
         glVertex3d(-size, -size, -size);
       
         glTexCoord2d(dTexRep, 0.0) ;
         glVertex3d(-size, -size,  size); 
       
         glTexCoord2d(dTexRep, dTexRep) ;
         glVertex3d(-size,  size,  size);

         glTexCoord2d(0.0, dTexRep) ;
         glVertex3d(-size,  size, -size);           
      glEnd();
      glDisable(GL_TEXTURE_2D);   

      glBegin(GL_POLYGON);  //Back -- Don't see it 
      glNormal3d(size,  0.0,  0.0);
         glVertex3d(size, -size, -size);
         glVertex3d(size,  size, -size);
         glVertex3d(size,  size,  size);
         glVertex3d(size, -size,  size);            
      glEnd();

		dTexRep = setTexRep(m_imageHoney) ;
		m_imageHoney.TexImage2D(this) ;           
		if (m_bTexture) glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);  //Top
         glNormal3d( 0.0, size,  0.0);
         glTexCoord2d(0.0, 0.0) ;
         glVertex3d(-size, size, -size); //ul - ccw

         glTexCoord2d(dTexRep, 0.0 ) ;	         
         glVertex3d(-size, size,  size); //ll

         glTexCoord2d(dTexRep, dTexRep) ;
         glVertex3d( size, size,  size); //lr

         glTexCoord2d(0.0, dTexRep) ;
         glVertex3d( size, size, -size); //ur           
      glEnd();

		dTexRep = setTexRep(m_imageMSDN) ;
		m_imageMSDN.TexImage2D(this) ;
		glBegin(GL_QUADS);	//Bottom
         glNormal3d( 0.0, -size,  0.0);	                   	                    
         glTexCoord2d(0.0, 0.0) ;
         glVertex3d(-size, -size, -size);

         glTexCoord2d(dTexRep, 0.0 ) ;
         glVertex3d( size, -size, -size);

         glTexCoord2d(dTexRep, dTexRep) ;
         glVertex3d( size, -size,  size);

         glTexCoord2d(0.0, dTexRep) ;
         glVertex3d(-size, -size,  size);	                   
      glEnd();
		glDisable(GL_TEXTURE_2D); 
         
	glEndList() ;			   
}

void CScene::PyramidList(int id, GLdouble size)
{
	//
	// Build a display list for the pyramid.
	//
	glNewList(id, GL_COMPILE) ;
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
}

void CScene::DodecList(int id, GLdouble dsize)
{
	GLdouble t = ((sqrt(5) - 1.0) / 2.0) ; 
	GLdouble tt = t*t ;
	t *= dsize ;
	tt *= dsize ;

	glNewList(id, GL_COMPILE) ;
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
}
