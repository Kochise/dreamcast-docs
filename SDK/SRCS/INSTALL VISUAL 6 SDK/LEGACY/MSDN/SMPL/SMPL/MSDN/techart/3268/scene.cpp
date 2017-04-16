#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include "resource.h" // for IDR_SPLASH

#include <math.h>

CScene::CScene()
: m_sizeScene(0,0)
{
}

CScene::~CScene()
{
}

//
// OnCreate
//
BOOL CScene::OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd)
{
	// Turn double buffering off, so we can watch bitmap draw.
	pfd->dwFlags &= ~PFD_DOUBLEBUFFER ;		
	return TRUE ;
}

//
// OnResize
//
BOOL CScene::OnResize(int cx, int cy)
{
    //
    // Sets the screen so you can use pixel co-ordinates
    //
	glLoadIdentity() ;
	gluOrtho2D(0, cx, cy, 0) ;
	glViewport(0, 0, cx, cy);

	//
	// Save the size.
	//
	m_sizeScene.cx = cx ;
	m_sizeScene.cy = cy ;

	return TRUE ;
}

//
// OnInit
//
BOOL CScene::OnInit()
{
	// Setup state
	glShadeModel(GL_FLAT) ;
    glDisable (GL_DEPTH_TEST);
    glDisable (GL_ALPHA_TEST);
	
	// Clear the color and depth buffers
	glClearColor(0.0F,0.0F,0.0F, 0.0f) ;

	// Load an image as a resource.
	m_anImage.Load(IDR_SPLASH) ;

	return TRUE ;
}

//
// OnRender
//
BOOL CScene::OnRender()
{
	// Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set rastor position.
	//
	GLint y = min(m_anImage.GetHeight(),  m_sizeScene.cy) ; 
	glRasterPos2i(0, y) ;	// Raster position should be on screen to be visible.

	//
	// Draw the Image.
	//
	m_anImage.DrawPixels(this) ;

    //
    // Flush the drawing pipeline.
    //
    glFlush();	

	return TRUE ;
}
