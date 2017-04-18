// cgl.cpp :
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

#include <windows.h>
#include "util.h"

#include "cgl.h"

/////////////////////////////////////////////////////////////////////////////
// Constructor

CGL::CGL()
{
	m_hrc = NULL;
	m_hdc = NULL;
	m_hPal = NULL;
	m_hOldPal = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

CGL::~CGL()
{
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////
// Destroy

void CGL::Destroy()
{
	if (m_hOldPal)
	{
		// Select in old palette.
		::SelectPalette(m_hdc, m_hOldPal, 0);
		m_hOldPal = NULL;
	}

	if (m_hPal)
	{
		// Delete palette.
		::DeleteObject(m_hPal);
		m_hPal = NULL;
	}

	if (m_hrc)
	{
		// Delete rendering context.
		if (m_hrc == wglGetCurrentContext())
			wglMakeCurrent(NULL,NULL);

		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
//  Create: use PFD_DRAW_TO_BITMAP

BOOL CGL::Create(HDC hdcMemory, int iPixelType, DWORD dwFlags)
{
	m_hdc = hdcMemory;
	HBITMAP hBitmap = (HBITMAP)::GetCurrentObject(hdcMemory, OBJ_BITMAP);

	BITMAP bmInfo;
	::GetObject(hBitmap, sizeof(BITMAP), &bmInfo);

	ASSERT(bmInfo.bmPlanes == 1);
	ASSERT((bmInfo.bmBitsPixel == 8) || (bmInfo.bmBitsPixel == 16)
		|| (bmInfo.bmBitsPixel == 24));

	// Fill in the Pixel Format Descriptor

	PIXELFORMATDESCRIPTOR pfd;
   memset(&pfd,0, sizeof(PIXELFORMATDESCRIPTOR));
   pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
   pfd.nVersion = 1;                            // Version number
   pfd.dwFlags =  dwFlags;
   pfd.iPixelType = iPixelType;
   pfd.cColorBits = (BYTE)bmInfo.bmBitsPixel;
   pfd.cDepthBits = 32;                     // 32-bit depth buffer
   pfd.iLayerType = PFD_MAIN_PLANE;         // Layer type

	ASSERT( (dwFlags & PFD_DRAW_TO_BITMAP));
	ASSERT( !(dwFlags & PFD_DOUBLEBUFFER));
	ASSERT( (iPixelType == PFD_TYPE_RGBA) ||
		(iPixelType == PFD_TYPE_COLORINDEX));

	// Chose the pixel format.
	int nPixelFormat = ::ChoosePixelFormat(m_hdc, &pfd);
	if (nPixelFormat == 0)
	{
		TRACE("ChoosePixelFormat Failed %d\r\n",GetLastError());
		return FALSE;
	}
	TRACE("Pixel Format %d\r\n", nPixelFormat);

	// Set the pixel format.
	BOOL bResult = ::SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	if (!bResult)
	{
		TRACE("SetPixelFormat Failed %d\r\n",GetLastError());
		return FALSE;
	}

	// Create the palette
	CreatePalette();

	// Create a rendering context.
	m_hrc = ::wglCreateContext(m_hdc);
	if (!m_hrc)
	{
		TRACE("wglCreateContext Failed %x\r\n", GetLastError());
		return FALSE;
	}

	// Window size is 0,0 here. Don't wglMakeCurrent.
	// wglMakeCurrent will be called in Resize

	// A dibsection should set the color palette after this call.
	//  m_pDibSurf->SetPalette(m_pPal); // DIBSECTION
	//  if (m_pPal) setPaletteDIB();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Helper Functions
// MakeCurrent

void CGL::MakeCurrent()
{
	ASSERT(m_hrc);
	ASSERT(m_hdc);

	if (m_hrc != ::wglGetCurrentContext())
	{
		// Make the rendering context m_hrc current
		BOOL bResult = ::wglMakeCurrent(m_hdc, m_hrc);
		ASSERT(bResult);
	}
}

/////////////////////////////////////////////////////////////////////////////
// IsCurrent

BOOL CGL::IsCurrent()
{
	return ( (m_hrc == wglGetCurrentContext()) &&
			 (m_hdc == wglGetCurrentDC()) );
}

/////////////////////////////////////////////////////////////////////////////
//  OutputGlError

void CGL::OutputGlError(char* label)
{
	GLenum errorno = glGetError();
	if (errorno != GL_NO_ERROR)
	{
		assert(0);
	}
}
