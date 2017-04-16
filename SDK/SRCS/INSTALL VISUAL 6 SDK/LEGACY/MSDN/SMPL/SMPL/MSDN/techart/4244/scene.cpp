#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include "resource.h"

#include <stdlib.h>
#include <time.h>
#include <memory.h>

CScene::CScene()
{
	m_angle.cx = 30 ;
	m_angle.cy = 70 ;
	m_angle.cz = 0 ;

	m_change.cx = m_change.cy = m_change.cz = 10 ;
}

CScene::~CScene()
{
}


BOOL CScene::OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd)
{
	pfd->cDepthBits = 16 ; // 16-bit depth buffer
	return TRUE ;
}


BOOL CScene::OnResize(int cx, int cy)
{
   //
   // Set up mapping 3-D coordinates to the 2-D screen
   //
   GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	glMatrixMode(GL_PROJECTION); OutputGlError("MatrixMode") ;
   glLoadIdentity();
   gluPerspective(30.0, gldAspect, 1.0, 10.0);
	glTranslated(0.0, 0.0, -4.0) ;
	glViewport(0,0, cx, cy);
	
	return TRUE ;
}

//
//
//
BOOL CScene::OnInit()
{
	// Enable depth calculations
   glEnable(GL_DEPTH_TEST);  		OutputGlError("glEnable (GL_DEPTH_TEST);") ;

#if 0 
   // Decal mode doesn't need lighting so turn off for some more speed...
     
	// Set the material color to follow the current color
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
   glEnable(GL_COLOR_MATERIAL) ;

	// Enable lighting calculations
   glEnable(GL_LIGHTING) ; 		OutputGlError("glEnable (GL_LIGHTING) ;") ;
   glEnable(GL_LIGHT0) ;			OutputGlError("glEnable (GL_LIGHT0) ;") ;
#endif

	//
	// Culling
	//
	glEnable(GL_CULL_FACE) ;
			
	//
	// Texture Mapping stuff
	//
   glEnable(GL_TEXTURE_2D);    OutputGlError("Enable Texturing") ;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	CString strDefault(_T("--DEFAULT--")) ; 
	CString strPath ;
	CString strSection ;
	CString strIniName ;
	strSection.LoadString(IDS_PROFILE_SECTION) ;	
	strIniName.LoadString(IDS_PROFILE_INI) ;

	LPCTSTR key[6] =  {	_T("Face1"), _T("Face2"), _T("Face3"), 
                        _T("Face4"), _T("Face5"), _T("Face6")} ;
	
	int iIDs[6]  =  {	IDR_DEFAULT_TEXTURE_1, IDR_DEFAULT_TEXTURE_2, IDR_DEFAULT_TEXTURE_3,
                     IDR_DEFAULT_TEXTURE_4, IDR_DEFAULT_TEXTURE_5, IDR_DEFAULT_TEXTURE_6} ; 

	LPTSTR buffer ;

	for(int i = 0 ; i < 6 ; i++)
	{
		buffer = strPath.GetBufferSetLength(512) ;
		::GetPrivateProfileString(strSection,
								key[i],
								strDefault, 
								buffer,
								512,
								strIniName) ;
		strPath.ReleaseBuffer() ;

		if ( (strPath == strDefault) ||
			 (strPath.IsEmpty()) )
		{		
			m_imageTexMap[i].Load(iIDs[i]) ; 
		}
		else
		{
			if (!m_imageTexMap[i].Load(strPath))
			{
				MessageBeep(0) ;
				TRACE0("Failed to load bitmap.\r\n") ;
				m_imageTexMap[i].Load(iIDs[i]) ; 
			}
				
		}
		m_imageTexMap[i].TexMapScalePow2(this) ;  
	}

	// Set the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;

	//
	// Build a display list for the cube.
	//    
	BoxList(Box, 0.3) ;			   

	// Set up some colors
   //	static GLdouble green[3] = {0.0, 0.75, 0.0} ;

   glMatrixMode(GL_MODELVIEW); 	OutputGlError("MatrixMode") ;
	glLoadIdentity();
   // glTranslated(0.0, 0.0, -4.0 );

   //	glColor3dv(green) ;

	return TRUE ;
}

//
//
//
BOOL CScene::OnRender()
{
   // Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Translate and rotate the axis.

	glPushMatrix() ;
   glRotated(m_angle.cx, 1.0, 0.0, 0.0);
   glRotated(m_angle.cy, 0.0, 1.0, 0.0);
	glRotated(m_angle.cz, 0.0, 0.0, 1.0) ;

	// Draw the box.
	glCallList(Box) ;

	glPopMatrix() ;

	return TRUE ;
}

//
//
//
void CScene::Rotate()
{
	srand(clock() & 0xffff);
   rand();

	m_angle.cx += m_change.cx ; 
	m_angle.cy += m_change.cy ; 
	m_angle.cz += m_change.cz ; 
	if (m_angle.cx >= 360) m_angle.cx = 0 ;
	if (m_angle.cy >= 360) m_angle.cy = 0 ;
	if (m_angle.cz >= 360) m_angle.cz = 0 ;
}

//
// Modify the rotation when we hit a wall.
//
void CScene::Bounce()
{
	m_change.cx = int(((double)rand() / (double)RAND_MAX) * 20.0);
	m_change.cy = int(((double)rand() / (double)RAND_MAX) * 20.0);
	m_change.cy = int(((double)rand() / (double)RAND_MAX) * 20.0);
}
////////////////////////////////////////////////////////////////////////////////////
//
// Texture Mapping Code
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
