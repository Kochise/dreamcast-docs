#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include "resource.h"
//
// Construct the CScene object  
//
CScene::CScene()
	: m_ptOrg(0,0)
{
	m_RotatingObject = Box ;

	m_angle[Box].cx = 30 ;
	m_angle[Box].cy = 70 ;
	m_angle[Pyramid].cx = 150 ;
	m_angle[Pyramid].cy = 120 ;
	m_angle[Dodec].cx = 30 ;
	m_angle[Dodec].cy = 70 ;

   // Texture
   m_bDecalMode = TRUE ;
   m_bTexture = TRUE ;
}

//
// Destruct the CScene Object
//
CScene::~CScene()
{
}

//
// Adjust the coordinate mapping to a new size
//
BOOL CScene::OnResize(int cx, int cy)
{
	//
	// Set up mapping 3-D coordinates to the 2-D screen
	//
	GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	OutputGlError("Clear") ;
	glMatrixMode(GL_PROJECTION); OutputGlError("MatrixMode") ;
	glLoadIdentity();
	gluPerspective(30.0, gldAspect, 1.0, 10.0);
	glViewport(m_ptOrg.x, m_ptOrg.y, cx, cy);
	
	return TRUE ;
}

//
// Initialize OpenGL for the scene.
//
BOOL CScene::OnInit()
{
	// Faster than using glScale.
	GLdouble size = 0.5 ;
	GLdouble dsize = 0.35 ; // Size for Dodecadedron

	// Enable depth calculations
	glEnable(GL_DEPTH_TEST);  		OutputGlError("glEnable (GL_DEPTH_TEST);") ;

	// Set the material color to follow the current color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;

	// Enable lighting calculations
	glEnable(GL_LIGHTING) ; 		OutputGlError("glEnable (GL_LIGHTING);") ;
	glEnable(GL_LIGHT0) ;			OutputGlError("glEnable (GL_LIGHT0) ;") ;
	
	//
	// Texture Mapping 
	//
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   // Textures repeat.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   // Set tecturing mode to Decal or Modulate
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 
               m_bDecalMode ? GL_DECAL : GL_MODULATE);

   // Low quality, but faster speed.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   // Load and scale the textures...
	m_imageTexMap.Load(IDR_TEXTURE_1) ;
	m_imageTexMap.TexMapScalePow2(this) ;  

	m_imageMSDN.Load(IDR_TEXTURE_2) ;
	m_imageMSDN.TexMapScalePow2(this) ;

	m_imageHoney.Load(IDR_TEXTURE_3) ;
	m_imageHoney.TexMapScalePow2(this) ;

	m_imageEgypt.Load(IDR_TEXTURE_4) ;
	m_imageEgypt.TexMapScalePow2(this) ;
      
	// Set the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;

	//
	// Build a display list for the cube.
	//    
	BoxList(Box, size) ;			   

	//
	// Build a display list for the pyramid.
	//
	PyramidList(Pyramid, size) ;

	//
	// Build display list for Dodecahedron
	//
	DodecList(Dodec, dsize) ;

	return TRUE ;
}

//
// Render the Scene.
//
BOOL CScene::OnRender()
{
	// Set up some colors
	static GLdouble red[3] = {0.8, 0.0, 0.0 } ; 
	static GLdouble green[3] = {0.0, 0.75, 0.0} ;
	static GLdouble purple[3] = {1.0, 0.14, 0.6667} ; 

   // Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //
   // Draw the box.
   //		
   glMatrixMode(GL_MODELVIEW); 	OutputGlError("MatrixMode") ;
	
	// Translate and rotate the axis.
	glLoadIdentity();
   glTranslated(0.5, 0.5, -4.5 ); 
   glRotated(m_angle[Box].cx, 1.0, 0.0, 0.0);
   glRotated(m_angle[Box].cy, 0.0, 1.0, 0.0);

	// Change the current color to green.
	glColor3dv(green) ;

	// Draw the box.
	glCallList(Box) ;

	//
	// Draw the pyramid.
	//
	glLoadIdentity();
   glTranslated(-0.7, 0.5, -4.5 );
 	glRotated(m_angle[Pyramid].cx, 1.0, 0.0, 0.0);
   glRotated(m_angle[Pyramid].cy, 0.0, 1.0, 0.0);

	glColor3dv(purple) ;
	glCallList(Pyramid) ;

  	//
	// Draw the Dodecahedron.
	//
	glLoadIdentity();
   glTranslated(0.0, 0.0, -2.5 );
 	glRotated(m_angle[Dodec].cx, 1.0, 0.0, 0.0);
   glRotated(m_angle[Dodec].cy, 0.0, 1.0, 0.0);

	glColor3dv(red) ;
	glCallList(Dodec) ;

   //
   // Flush the drawing pipeline.
   //
   glFlush();	

	return TRUE ;
}

//
// Rotate the current shape.
//
void CScene::Rotate()
{
	m_angle[m_RotatingObject].cx += 10 ;
	m_angle[m_RotatingObject].cy += 10 ;
	if (m_angle[m_RotatingObject].cx >= 360) m_angle[m_RotatingObject].cx = 0 ;
	if (m_angle[m_RotatingObject].cy >= 360) m_angle[m_RotatingObject].cy = 0 ;
}

////////////////////////////////////////////////////////////////////////////////////
//
// Texture Mapping Code
//

//
// Load a DIB to convert to a texture map 
//
BOOL CScene::GetTextureMap()
{
    CString strFile;    
    // Show an open file dialog to get the name
    CFileDialog dlg   (TRUE,    // open
                       NULL,    // no default extension
                       NULL,    // no initial file name
                       OFN_FILEMUSTEXIST
                       | OFN_HIDEREADONLY,
                       "Image files (*.DIB, *.BMP)|*.DIB;*.BMP|All files (*.*)|*.*||");	 
    if (dlg.DoModal() == IDOK)
    {
    	strFile = dlg.GetPathName();
		m_imageTexMap.Load((LPCTSTR)strFile) ;

		m_imageTexMap.TexMapScalePow2(this) ;  
		BoxList(Box, 0.5) ; // Recreate Box Display list.
		return TRUE ;
    }
	return FALSE ;  
}

//
// True - turns texturing on 
//
void CScene::SetTextureMode(BOOL bState)
{
   m_bTexture = bState; 
   BoxList(Box, 0.5) ;
}

//
// True = Decal. False = Modulate
//
void CScene::SetDecalMode(BOOL bState /*= TRUE*/)
{ 
   m_bDecalMode = bState; 
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 
              m_bDecalMode ? GL_DECAL : GL_MODULATE);
   BoxList(Box, 0.5) ;
}

//
// Repeat texture if the w or h is < 128 pixels
//
double CScene::setTexRep(CGLImage& rImage)
{
   int w = rImage.GetWidth() ;
   int h = rImage.GetHeight() ;

   if ( (w >= 128) || (h >= 128))
      return 1.0 ;
   else
      return 5.0 ;
}
