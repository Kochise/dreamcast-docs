//  CGL.h : Header file for the OpenGL class.
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __CGL_H__
#define __CGL_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

/////////////////////////////////////////////////////////////////////////////
// CGL

class CGL
{
public:
	// Construction
	CGL() ;

	// Destruction
	virtual ~CGL() ;

	BOOL Create(HDC hdcMemory,
				int iPixelType  =   PFD_TYPE_RGBA,
				DWORD dwFlags   =   PFD_SUPPORT_OPENGL |    // Use OpenGL
									PFD_SUPPORT_GDI |
									PFD_DRAW_TO_BITMAP );   // Pixel format is for a bitmap.

	void Destroy() ;

	// Attributes
	HPALETTE GetPalette() {return m_hPal ;}

	// Operations
	void MakeCurrent() ; // for CGLImage
	BOOL IsCurrent() ;

	// Helpful functions
	void OutputGlError(char* label) ;

private:
	// Implementation Data Members
	HGLRC m_hrc ;           //OpenGL Rendering Context
	HDC m_hdc;
	HPALETTE m_hPal ;       //Palette
	HPALETTE m_hOldPal ;

	BOOL m_bDoubleBuffer ; // Controls calling SwapBuffers
	BOOL m_bDrawToBitmap ;

	// Support for generating RGB color palette
	BOOL CreatePalette()    ;
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift) ;
	static unsigned char   m_oneto8[2];
	static unsigned char   m_twoto8[4];
	static unsigned char   m_threeto8[8];
	static int             m_defaultOverride[13];
	static PALETTEENTRY    m_defaultPalEntry[20];
};
#endif
