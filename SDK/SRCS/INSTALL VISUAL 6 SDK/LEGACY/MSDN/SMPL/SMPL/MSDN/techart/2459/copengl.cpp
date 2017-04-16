// implementation 
//
//
#include "stdafx.h"
#include "COpenGL.h"
#include <gl\gl.h>
#include <gl\glu.h>

#define MAX_GENERIC_PFD (1*8+4*4)
#define MIN_GENERIC_PFD 1

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Static member data initialization

  unsigned char COpenGL::m_threeto8[8] = {
    0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
  };
  unsigned char COpenGL::m_twoto8[4] = {
    0, 0x55, 0xaa, 0xff
  };
  unsigned char COpenGL::m_oneto8[2] = {
    0, 255
  };
  int COpenGL::m_defaultOverride[13] = {
    0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
  };

  PALETTEENTRY COpenGL::m_defaultPalEntry[20] = {
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
  
/////////////////////////////////////////////////////////////////////////////
// Constructor

COpenGL::COpenGL(HDC hdc, PIXELFORMATDESCRIPTOR *pfd)
{
  m_hdc = hdc;
  m_hglrc = NULL;
  m_fIsInitialized = FALSE;

  if (pfd != NULL)
    Init(pfd);
}

void COpenGL::Init(PIXELFORMATDESCRIPTOR *pfd)
{
  memcpy(&m_PixFmtDesc, pfd, sizeof(PIXELFORMATDESCRIPTOR));
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

COpenGL::~COpenGL()
{
}
   
/////////////////////////////////////////////////////////////////////////////
// Utility functions

BOOL COpenGL::GetGLRC(HDC hdc)
{ 
   BOOL bRet = TRUE;

   m_maxpfd = GetMaxPFIndex(m_hdc);

   if (SetupPixelFormat(hdc, &m_PixFmtDesc))
   {
     if ((m_hglrc = wglCreateContext(hdc)) != NULL)
	 {
	   if (!wglMakeCurrent(hdc, m_hglrc))
	   {
	     wglDeleteContext(m_hglrc);
		 bRet = FALSE;
	   }
	 }
	 else bRet = FALSE;
   }
   else 
     bRet = FALSE;

   return bRet;
}

BOOL COpenGL::ReleaseGLRC(HWND hwnd)
{
  BOOL bRet = TRUE;
  HDC   hdc;
  HGLRC hglrc;
  
  if (hglrc = wglGetCurrentContext())
  {
    //
    //get the DC associated with the rendering context
    //
    hdc = wglGetCurrentDC();
    //
    //make the rendering context not current.
    //
    wglMakeCurrent(NULL, NULL);
    //
    //nuke the DC
    //
    ::ReleaseDC(hwnd, hdc);
	//
	//nuke the rendering context
	//
	wglDeleteContext(hglrc);
  }	 
  else bRet = FALSE;
  return bRet;
}

int COpenGL::GetMaxPFIndex(HDC hdc)
{
  PIXELFORMATDESCRIPTOR pfd;
  
  int ipfdmax = DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  return (ipfdmax);
}

BOOL COpenGL::IsNativeIndex(HDC hdc, int idx)
{
  ASSERT (hdc);
  ASSERT (idx > 0);

  BOOL bRet = FALSE;
  PIXELFORMATDESCRIPTOR pfd;
  int ipfdmax = DescribePixelFormat(hdc, idx, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  if (pfd.dwFlags & PFD_DRAW_TO_WINDOW)
    bRet = TRUE;
  return (bRet);
}

BOOL COpenGL::IsDeviceIndex(HDC hdc, int idx)
{
  ASSERT (hdc);
  ASSERT (idx > 0);

  BOOL bRet = FALSE;
  PIXELFORMATDESCRIPTOR pfd;
  int ipfdmax = DescribePixelFormat(hdc, idx, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  if (!(pfd.dwFlags & PFD_GENERIC_FORMAT))
    bRet = TRUE;
  return (bRet);
}


BOOL COpenGL::SetupPixelFormat(HDC hdc, PIXELFORMATDESCRIPTOR *pPFD)
{
   BOOL bRet = TRUE;
   int pixelformat;
	
   if (!(pixelformat = ChoosePixelFormat(hdc, pPFD)))
     bRet = FALSE;

   if (!SetPixelFormat(hdc, pixelformat, pPFD))
     bRet = FALSE;

   if (bRet)
     CreateRGBPalette(hdc);

   return bRet;
}

int COpenGL::GetCurPFDIndex()
{
  int icuridx = GetPixelFormat(wglGetCurrentDC());
  return (icuridx);
  
}

unsigned char COpenGL::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val;

    val = (unsigned char) (i >> shift);
    switch (nbits) {

    case 1:
        val &= 0x1;
        return m_oneto8[val];

    case 2:
        val &= 0x3;
        return m_twoto8[val];

    case 3:
        val &= 0x7;
        return m_threeto8[val];

    default:
        return 0;
    }
}


void COpenGL::CreateRGBPalette(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n, i;
	HPALETTE ghpalOld, ghPalette = (HPALETTE) 0;

    n = GetPixelFormat(hDC);
    DescribePixelFormat(hDC, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE) {
        n = 1 << pfd.cColorBits;
        pPal = (PLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) +
                n * sizeof(PALETTEENTRY));
        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
        for (i=0; i<n; i++) {
            pPal->palPalEntry[i].peRed =
                    ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen =
                    ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue =
                    ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags = 0;
        }

        /* fix up the palette to include the default GDI palette */	
        if ((pfd.cColorBits == 8)                           &&
            (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
            (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
            (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
           ) {
            for (i = 1 ; i <= 12 ; i++)
                pPal->palPalEntry[m_defaultOverride[i]] = m_defaultPalEntry[i];
        }

        ghPalette = ::CreatePalette(pPal);
        LocalFree(pPal);

        ghpalOld = ::SelectPalette(hDC, ghPalette, FALSE);
        n = RealizePalette(hDC);
    }
} 

///////////////////////////////////////////////////////////////////////////////////
// Win32 pixel format and buffering API wrappers

int COpenGL::ChoosePixelFormat(HDC hdc, PIXELFORMATDESCRIPTOR *ppfd)
{
  ASSERT (hdc);
  ASSERT (ppfd);

  int iRet = 0;

  if ((::GetObjectType(hdc) == OBJ_DC) && ppfd)
    iRet = ::ChoosePixelFormat(hdc, ppfd);
  return (iRet);
}

int COpenGL::DescribePixelFormat(HDC hdc, int iPixelFormat, 
                                 UINT nBytes, 
                                 PIXELFORMATDESCRIPTOR *ppfd)
{
  ASSERT (hdc);

  int iRet = 0;
  //
  //don't bother validating iPixelFormat, nBytes and ppfd as
  //it is OK to have them 0, 0, NULL when trying to get the 
  //maximum PF index
  //
  if ((::GetObjectType(hdc) == OBJ_DC))
    iRet = ::DescribePixelFormat(hdc, iPixelFormat, nBytes, ppfd);
  return (iRet);
}

int COpenGL::GetPixelFormat(HDC hdc)
{
  ASSERT (hdc);

  int iRet = 0;

  if (::GetObjectType(hdc) == OBJ_DC)
    iRet = ::GetPixelFormat(hdc);
  return (iRet);
}

BOOL COpenGL::SetPixelFormat(HDC hdc, int iPixelFormat, PIXELFORMATDESCRIPTOR *ppfd)
{
  ASSERT (hdc);
  ASSERT (iPixelFormat);
  ASSERT (ppfd);

  DWORD dwErr;

  BOOL bRet = FALSE;

  if ((::GetObjectType(hdc) == OBJ_DC) && iPixelFormat > 0 && ppfd)
    bRet = ::SetPixelFormat(hdc, iPixelFormat, ppfd);

  if (!bRet)
    dwErr = GetLastError();
  return (bRet);
}

BOOL COpenGL::SwapBuffers(HDC hdc)
{
  ASSERT (hdc);

  BOOL bRet = FALSE;

  if (::GetObjectType(hdc) == OBJ_DC)
    bRet = ::SwapBuffers(hdc);
  return (bRet);
}


///////////////////////////////////////////////////////////////////////////////////
// wgl function wrappers

HGLRC COpenGL::wglCreateContext(HDC hdc)
{
  ASSERT (hdc);

  HGLRC hglrc = NULL;

  if (::GetObjectType(hdc) == OBJ_DC)
    hglrc = ::wglCreateContext(hdc);
  //
  //if rendering context successfully created
  //then assign to the member variable m_hglrc
  //
  if (hglrc)
    m_hglrc = hglrc;

  return (hglrc);
}

BOOL COpenGL::wglDeleteContext(HGLRC hglrc)
{
  ASSERT (hglrc);

  BOOL bRet = FALSE;

  if (hglrc)
    bRet = ::wglDeleteContext(hglrc);
  return (bRet);
}

HGLRC COpenGL::wglGetCurrentContext(void)
{
  return(::wglGetCurrentContext());
}

HDC COpenGL::wglGetCurrentDC(void)
{
  return(::wglGetCurrentDC());
}

BOOL COpenGL::wglMakeCurrent(HDC hdc, HGLRC hglrc)
{
  ASSERT(hdc >= NULL);
  ASSERT(hglrc >= NULL);

  BOOL bRet = FALSE;
  //
  //hdc and hglrc may be NULL if you are attempting
  //to make the current rc not current
  //
  bRet = ::wglMakeCurrent(hdc, hglrc);
  return (bRet);
}

BOOL COpenGL::wglUseFontBitmaps(HDC hdc, DWORD first, DWORD count, DWORD listbase)
{
  ASSERT (hdc);
  ASSERT (first >= 0);
  ASSERT (count);
  ASSERT (listbase >= 0);

  BOOL bRet = FALSE;

  if ((::GetObjectType(hdc) == OBJ_DC) && first >= 0 && count > 0 && listbase >= 0)
    bRet = ::wglUseFontBitmaps(hdc, first, count, listbase);
  return (bRet);
}

