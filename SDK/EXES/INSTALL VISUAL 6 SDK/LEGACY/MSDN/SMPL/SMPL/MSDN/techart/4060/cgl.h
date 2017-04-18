#ifndef __CGL_H__
#define __CGL_H__

#include "animate.h"

class AFX_EXT_CLASS CGL {
public:
	// Construction
	CGL() ;

	// Destruction
	virtual ~CGL() ;

	// Creation
 	BOOL Create(CWnd* pWnd, 
 				int iPixelType 	= 	PFD_TYPE_RGBA,
 				DWORD dwFlags	=	PFD_DOUBLEBUFFER |            // Use double buffer
               						PFD_SUPPORT_OPENGL |          // Use OpenGL
	               					PFD_DRAW_TO_WINDOW );         // Pixel format is for a window.

 	BOOL Create(CDC* pdcMemory,
 				int iPixelType 	= 	PFD_TYPE_RGBA,
 				DWORD dwFlags	=	PFD_SUPPORT_OPENGL |           // Use OpenGL
									PFD_SUPPORT_GDI |
	               					PFD_DRAW_TO_BITMAP );          // Pixel format is for a bitmap.

	void Destroy() ;
	BOOL Init() ;
	BOOL Resize(int cx, int cy) ;
	BOOL Render() ;

	// Attributes
	CPalette* GetPalette() {return m_pPal ;}

	// Operations
 	void MakeCurrent() ; // for CGLImage

 	// Helpful functions
	void OutputGlError(char* label) ; 

protected:
	// Override
	virtual BOOL OnCreate(CWnd* pWnd, PIXELFORMATDESCRIPTOR* pfd) 
					{TRACE0("CGL::OnCreate\r\n") ; return FALSE;}

	virtual BOOL OnResize(int cx, int cy) = 0;
	virtual BOOL OnInit() = 0;
	virtual BOOL OnRender() = 0;

	virtual BOOL OnCreatePaletteCI(LOGPALETTE* pPal) 
				{TRACE0("CGL::OnCreatePaletteCI\r\n") ; return FALSE; }	// Color Index Mode

private:
	// Implementation Member functions

	// Implementation Data Members
	HGLRC m_hrc ; 			//OpenGL Rendering Context
	CDC* m_pdc;
	CPalette* m_pPal ;		//Palette
	CPalette* m_pOldPal ;	

	BOOL m_bDoubleBuffer ; // Controls calling SwapBuffers

	BOOL m_bDrawToBitmap ;

	//
	// Support for generating RGB color palette
	//
	BOOL CreatePalette()	;
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift) ;
 	static unsigned char   m_oneto8[2];
    static unsigned char   m_twoto8[4];
    static unsigned char   m_threeto8[8];
    static int             m_defaultOverride[13];
    static PALETTEENTRY    m_defaultPalEntry[20];
};
#endif
