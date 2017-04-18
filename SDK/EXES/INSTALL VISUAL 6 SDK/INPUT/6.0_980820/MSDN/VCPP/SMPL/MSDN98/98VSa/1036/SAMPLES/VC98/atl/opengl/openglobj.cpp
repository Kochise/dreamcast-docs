// OpenGLObj.cpp : Implementation of COpenGLApp and DLL registration.
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

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLObj.h"
#include "glaux.h"

#pragma comment(lib, "winmm.lib")

/////////////////////////////////////////////////////////////////////////////
//

unsigned char threeto8[8] =
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] =
{
	0, 255
};

static int defaultOverride[13] =
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] =
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

void COpenGLObj::CreateContext(HDC hdc, RECT& rc)
{
	PIXELFORMATDESCRIPTOR pfd;
	GLfloat     fMaxObjSize, fAspect;
	GLfloat     fNearPlane, fFarPlane;

	if (!bSetupPixelFormat(hdc))
		return;

	CreateRGBPalette(hdc);

	::SelectPalette(hdc, m_hPal, FALSE);
	::RealizePalette(hdc);

	int n = ::GetPixelFormat(hdc);
	::DescribePixelFormat(hdc, n, sizeof(pfd), &pfd);


	m_hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, m_hrc);

	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);

	if (rc.bottom)
		fAspect = (GLfloat)rc.right/rc.bottom;
	else    // don't divide by zero, not that we should ever run into that...
		fAspect = 1.0f;
	fNearPlane = 3.0f;
	fFarPlane = 20.0f;
	fMaxObjSize = 3.0f;
	m_fRadius = fNearPlane + fMaxObjSize / 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, fAspect, fNearPlane, fFarPlane);
	glMatrixMode(GL_MODELVIEW);
}

LRESULT COpenGLObj::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Won't be here unless we just got activated and created a window
	HDC hdc = GetDC();
	RECT rc;
	GetClientRect(&rc);
	CreateContext(hdc, rc);
	// SetTimer(1, 33, NULL);
	SetTimer(1, 33);
	joySetThreshold(JOYSTICKID1, 10);
	if (joySetCapture(m_hWnd, JOYSTICKID1, 30, TRUE) == JOYERR_NOERROR)
		m_bstrCaption = _T("Joystick Mode");
	m_bActive = TRUE;
	return 0;
}

LRESULT COpenGLObj::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bActive = FALSE;
	KillTimer(1);

	joyReleaseCapture(JOYSTICKID1);

	::wglMakeCurrent(NULL,  NULL);

	if (m_hrc)
	{
		::wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
	return 0;
}

LRESULT COpenGLObj::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetCapture();
	m_bMouseCaptured = TRUE;
	m_xPos = (short)LOWORD(lParam);  // horizontal position of cursor
	m_yPos = (short)HIWORD(lParam);  // vertical position of cursor
	return 0;
}

LRESULT COpenGLObj::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bMouseCaptured = FALSE;
	ReleaseCapture();
	return 0;
}

LRESULT COpenGLObj::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bMouseCaptured)
	{
		int xPos = (short)LOWORD(lParam);  // horizontal position of cursor
		int yPos = (short)HIWORD(lParam);  // vertical position of cursor
		GLfloat fNearPlane = 3.0f;
		GLfloat fFarPlane = 7.0f;
		GLfloat fMaxObjSize = 3.0f;
		m_fRadius += (float)(m_xPos - xPos)/100.0f;
		m_xPos = xPos;
		m_yPos = yPos;
	}
	return 0;
}

HRESULT COpenGLObj::OnDraw(ATL_DRAWINFO& di)
{
	HDC hdc = di.hdcDraw;
	RECT& rc = *(RECT*)di.prcBounds;

	::SelectPalette(hdc, m_hPal, FALSE);
	::RealizePalette(hdc);

	wglMakeCurrent(hdc, m_hrc);

	glClearColor(0.0f, 0.0f, 0.0f, 10.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();

		glTranslatef(0.0f, 0.0f, -m_fRadius);
		glRotatef(m_wAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_wAngleY, 0.0f, 1.0f, 0.0f);
		glRotatef(m_wAngleZ, 0.0f, 0.0f, 1.0f);

		m_wAngleX -= (float(joyposY - 32768) / 32768.0f) * 20.0f;
		m_wAngleY -= (float(joyposX - 32768) / 32768.0f) * 20.0f;
		m_wAngleZ += 1.0f;

		glBegin(GL_QUAD_STRIP);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f,  -0.5f);

			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

		glEnd();

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);

			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

		glEnd();

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f,  -0.5f);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);
		auxWireSphere(2.5);

	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	SetTextColor(hdc, RGB(128,128,255));
	SetBkMode(hdc, TRANSPARENT);
	USES_CONVERSION;
	LPCTSTR lpsz = OLE2T(m_bstrCaption);
	DrawText(hdc, lpsz, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	return 1;
}


BOOL COpenGLObj::bSetupPixelFormat(HDC hdc)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == 0 )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE)
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}


unsigned char COpenGLObj::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
	unsigned char val;

	val = (unsigned char) (i >> shift);
	switch (nbits)
	{

	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];

	default:
		return 0;
	}
}


void COpenGLObj::CreateRGBPalette(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	int n, i;

	if (m_pPal)
		return;

	n = ::GetPixelFormat(hdc);
	::DescribePixelFormat(hdc, n, sizeof(pfd), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		m_pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

		ATLASSERT(m_pPal != NULL);

		m_pPal->palVersion = 0x300;
		m_pPal->palNumEntries = n;
		for (i=0; i<n; i++)
		{
			m_pPal->palPalEntry[i].peRed =
					ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
			m_pPal->palPalEntry[i].peGreen =
					ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
			m_pPal->palPalEntry[i].peBlue =
					ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
			m_pPal->palPalEntry[i].peFlags = 0;
		}

		/* fix up the palette to include the default GDI palette */
		if ((pfd.cColorBits == 8)                           &&
			(pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
		   )
		{
			for (i = 1 ; i <= 12 ; i++)
				m_pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
		}

		m_hPal = ::CreatePalette((LPLOGPALETTE)m_pPal);
//        delete pPal;

		::SelectPalette(hdc, m_hPal, FALSE);
		::RealizePalette(hdc);
	}
}
