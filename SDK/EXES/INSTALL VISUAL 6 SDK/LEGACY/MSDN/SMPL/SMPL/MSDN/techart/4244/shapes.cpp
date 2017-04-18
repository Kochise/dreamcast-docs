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
   dTexRep = setTexRep(m_imageTexMap[0]) ;
   m_imageTexMap[0].TexImage2D(this) ;
   glBegin(GL_QUADS); // right  - ccw
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

   dTexRep = setTexRep(m_imageTexMap[1]) ;
   m_imageTexMap[1].TexImage2D(this) ;
   glBegin(GL_QUADS);	//left - ccw
      glNormal3d( 0.0,  0.0, -size);
      glTexCoord2d(0.0, 0.0) ;
      glVertex3d(-size, -size, -size);

      glTexCoord2d(dTexRep, 0.0) ;
      glVertex3d(-size,  size, -size);	                   

      glTexCoord2d(dTexRep, dTexRep) ;
      glVertex3d( size,  size, -size);

      glTexCoord2d(0.0, dTexRep) ;
      glVertex3d( size, -size, -size);
   glEnd();

   dTexRep = setTexRep(m_imageTexMap[2]) ;
   m_imageTexMap[2].TexImage2D(this) ;
   glBegin(GL_QUADS); //Font - ccw
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

   dTexRep = setTexRep(m_imageTexMap[3]) ;
   m_imageTexMap[3].TexImage2D(this) ;
   glBegin(GL_QUADS);  //Back 	- ccw
      glNormal3d(size,  0.0,  0.0);
      glTexCoord2d(0.0, 0.0) ;
      glVertex3d(size, -size, -size);

      glTexCoord2d(dTexRep, 0.0) ;
      glVertex3d(size,  size, -size);

      glTexCoord2d(dTexRep, dTexRep) ;
      glVertex3d(size,  size,  size);
 
      glTexCoord2d(0.0, dTexRep) ;
      glVertex3d(size, -size,  size);            
   glEnd();

   dTexRep = setTexRep(m_imageTexMap[4]) ;
   m_imageTexMap[4].TexImage2D(this) ;           
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

   dTexRep = setTexRep(m_imageTexMap[5]) ;
   m_imageTexMap[5].TexImage2D(this) ;
   glBegin(GL_QUADS);	//Bottom   - ccw
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
         
	glEndList() ;			   
}
