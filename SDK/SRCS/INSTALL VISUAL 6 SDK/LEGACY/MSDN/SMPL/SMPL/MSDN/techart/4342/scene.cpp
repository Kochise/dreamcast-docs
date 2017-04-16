#include "stdafx.h"
#include <ctype.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLlib.h"
#include "Scene.h"

#include "resource.h"
#include "fontparamdlg.h"


CScene::CScene()
{
	// Initialize Default Angles	
	m_angle.cx = 0 ;
	m_angle.cy = 0 ;

	// Initialize Default Font Structure
	m_logFontDefault.lfHeight 		= -10 ;
	m_logFontDefault.lfWidth 		= 0 ;
	m_logFontDefault.lfEscapement 	= 0 ;
	m_logFontDefault.lfOrientation 	= 0 ;
	m_logFontDefault.lfWeight 		= FW_NORMAL ;
	m_logFontDefault.lfItalic 		= FALSE ;
	m_logFontDefault.lfUnderline 	= FALSE ;
	m_logFontDefault.lfStrikeOut 	= FALSE ;
	m_logFontDefault.lfCharSet		= ANSI_CHARSET ;
	m_logFontDefault.lfOutPrecision = OUT_TT_PRECIS ;
	m_logFontDefault.lfClipPrecision= CLIP_DEFAULT_PRECIS ;
	m_logFontDefault.lfQuality 		= PROOF_QUALITY ;
	m_logFontDefault.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN ;
	strcpy(m_logFontDefault.lfFaceName, "Arial") ;  

	// Create Default Font
	BOOL bResult =
	m_FontDefault.CreateFontIndirect(&m_logFontDefault) ;
	ASSERT(bResult) ;

	// Setup wglGetFontOutline Parameters
	m_iFormat 		= m_iFormatDefault 		= WGL_FONT_POLYGONS ;
	m_fDeviation 	= m_fDeviationDefault 	= 0.0f ;
	m_fExtrusion 	= m_fExtrusionDefault 	= 0.1f ;
	m_theString 	= m_theStringDefault 	= "OpenGL" ;

	// Create Selected Font Based on Default Font
	m_pFontSelected = new CFont;
	m_pFontSelected->CreateFontIndirect(&m_logFontDefault) ;

	// Display list varaibles.
	m_iFirstChar = 33 ;
	m_iLastChar = 126 ;
	m_iNumberChars = m_iLastChar - m_iFirstChar ;

	m_iDisplayListStart = 0 ;
	m_iDisplayListBase = 0 ;

}

//
//
//
CScene::~CScene()
{
	if (m_pFontSelected) delete m_pFontSelected ;
}

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
   glViewport(0, 0, cx, cy);

	return TRUE ;
}

//
//
//
BOOL CScene::OnInit()
{
	// Enable depth calculations
   glEnable(GL_DEPTH_TEST);  		OutputGlError("glEnable (GL_DEPTH_TEST);") ;

	// Set the material color to follow the current color
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;

   // Set Position of Light
   float fLightPosition[3] = {-1.0f, -1.0f, 1.0f} ;
   glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition) ;

	// Enable lighting calculations
	glEnable(GL_LIGHTING) ; 		OutputGlError("glEnable (GL_LIGHTING) ;") ;
	glEnable(GL_LIGHT0) ;			OutputGlError("glEnable (GL_LIGHT0) ;") ;
	
	// Set the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;

	//
	// 3D Text Support
	//
	
	Create3DFont(); // Make the 3D Font picked by the user.		
	//
	// Build the MSDN Letters
	//

	// Get the current DC.
	HDC hdc = wglGetCurrentDC();
	CDC* pdc = CDC::FromHandle(hdc) ;

	// Select in the default font...
	CFont* pOldFont = (CFont*)pdc->SelectObject(&m_FontDefault) ;

	//GLYPHMETRICSFLOAT agmfMSDN[MSDN_COUNT] ;

	// Do them separately
	for (int i = 0 ; i < MSDN_COUNT ; i ++)
	{
		BOOL bResult = 
		wglUseFontOutlines(	hdc,
							__toascii(MSDN_STRING[i]),		// First character
							1,				// Number
							MSDN_DISPLAYLIST+i,	// Starting Display list number
							0.0f,				// Deviation
							0.1f,				// Extrusion
							WGL_FONT_POLYGONS,	// Format or WGL_FONT_LINES
							&m_agmfMSDN[i]) ;				// Information pointer

		ASSERT(bResult) ;
	}

	// Cleanup.	
	if (pOldFont) pdc->SelectObject(pOldFont) ;
	return TRUE ;
}

//
//
//
BOOL CScene::OnRender()
{
   // Set up some colors
   static GLdouble red[3] = {0.8, 0.0, 0.0 } ; 
   static GLdouble green[3] = {0.0, 0.75, 0.0} ;
   static GLdouble purple[3] = {1.0, 0.14, 0.6667} ; 
   
   static GLubyte byPink[3] = {196, 0, 196} ;
   static GLubyte byTeal[3] = {0, 153, 168} ;
   static GLubyte byBlue[3] = {42, 38, 215} ;
   static GLubyte byGreen[3] = {0, 171, 82} ;

   // Clear the color and depth buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW); 	OutputGlError("MatrixMode") ;

   glLoadIdentity();
   glTranslated(-m_dCenterOffset /*1.7*/, 0.20, -4.4 );
   glRotated(m_angle.cx, 1.0, 0.0, 0.0);

   glColor3dv(purple) ;
	glListBase(m_iDisplayListBase) ; //NOTE CAN THIS BE NEGATIVE????
	glCallLists(m_theString.GetLength(),
				GL_UNSIGNED_BYTE,
				(LPCTSTR)m_theString ) ;

   //
   //
   double widthMN = (m_agmfMSDN[0].gmfCellIncX + m_agmfMSDN[0].gmfCellIncX) * 0.5 ;

   glLoadIdentity();
   glTranslated(0.0, -0.65, -3.0 );
   glRotated(m_angle.cy, 0.0, 1.0, 0.0);
   glTranslated(-widthMN, 0.0, 0.0) ;

   glScaled(0.5, 0.5, 0.5) ;

	glColor3ubv(byPink) ;
	glCallList(MSDN_DISPLAYLIST) ;
   glColor3ubv(byTeal) ;
	glCallList(MSDN_DISPLAYLIST+1) ;
	glColor3ubv(byBlue) ;			   
	glCallList(MSDN_DISPLAYLIST+2) ;
   glColor3ubv(byGreen) ;
	glCallList(MSDN_DISPLAYLIST+3) ;

   //
   // Flush the drawing pipeline.
   //
   glFlush();	

   return TRUE ;
}

//
//
//
void CScene::Rotate()
{
	m_angle.cx += 10 ;
	m_angle.cy += 10 ;
	if (m_angle.cx >= 360) m_angle.cx = 0 ;
	if (m_angle.cy >= 360) m_angle.cy = 0 ;
}


void CScene::Create3DFont()
{
	// Delete existing display list numbers ;
	if (m_iDisplayListStart != 0 )
	{	
		// Detelete the existing lists.
		glDeleteLists(m_iDisplayListStart, m_iNumberChars) ;
	}

	// Generate new display lists.
	m_iDisplayListStart = glGenLists(m_iNumberChars) ;
	m_iDisplayListBase = m_iDisplayListStart - m_iFirstChar ; // Does this work???

   // Get the DC for the current rendering context.	
	HDC hdc = wglGetCurrentDC();
	CDC* pdc = CDC::FromHandle(hdc) ;

	// Select the font.
	CFont* pOldFont = (CFont*)pdc->SelectObject(m_pFontSelected) ;
	
	// Generate the display lists...
	GLYPHMETRICSFLOAT agmf[128]; // Fixed size...

	BOOL bResult = 
	wglUseFontOutlines(	hdc,
						m_iFirstChar,		// First character
						m_iNumberChars,		// Number
						m_iDisplayListStart,	// Starting Display list number
						m_fDeviation,		// Deviation
						m_fExtrusion,		// Extrusion
						m_iFormat,			// Format or WGL_FONT_LINES
						agmf) ;				// Information pointer

	if (!bResult)
	{
		TRACE("Error in wglUseFontOutlines.\r\n") ;
	}

	if (pOldFont) pdc->SelectObject(pOldFont) ;

   // Calculate the Center of the string:
   int iLen = m_theString.GetLength() ;
   m_dCenterOffset = 0 ;
   for (int i = 0 ; i < iLen  ; i++)
   {
      m_dCenterOffset += agmf[__toascii(m_theString[i])-m_iFirstChar].gmfCellIncX  ;
   }
   m_dCenterOffset /= 2 ;
}

//
//
//
void CScene::DoDialog(CWnd* pWnd)
{
	CFontParamDlg aDlg ;

	// Setup Dialog Data
	aDlg.m_iFormatRadio = FormatAsInt(m_iFormat) ;
	aDlg.m_fDeviation = m_fDeviation;
	aDlg.m_fExtrusion = m_fExtrusion;
	aDlg.m_theString = m_theString;

	// Setup Font Information....
	m_pFontSelected->GetObject(sizeof(LOGFONT), &aDlg.m_logFont) ;

	// Setup Defaults
	aDlg.m_iFormatDefault 		= FormatAsInt(m_iFormatDefault) ;
	aDlg.m_fDeviationDefault  	= m_fDeviationDefault ;
	aDlg.m_fExtrusionDefault 	= m_fExtrusionDefault ;
	aDlg.m_theStringDefault 	= m_theStringDefault ;

	aDlg.m_pLogFontDefault = &m_logFontDefault ;


	if (aDlg.DoModal() == IDOK)
	{
		m_iFormat = IntAsFormat(aDlg.m_iFormatRadio) ;
		m_fDeviation = aDlg.m_fDeviation;
		m_fExtrusion = aDlg.m_fExtrusion;
		m_theString = aDlg.m_theString;		

		// Font
		delete m_pFontSelected ;
		m_pFontSelected = new CFont;
		m_pFontSelected->CreateFontIndirect(&aDlg.m_logFont) ;

		Create3DFont() ;
		pWnd->Invalidate() ;
		pWnd->UpdateWindow() ;
	}
}
