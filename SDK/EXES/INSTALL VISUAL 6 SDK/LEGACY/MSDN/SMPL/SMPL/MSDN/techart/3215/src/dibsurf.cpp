// dibsurf.cpp : implementation of the CDIBSurface class
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBSurface

// These static variables are all initialized before any objects are constructed
BOOL CDIBSurface::m_bUseCreateDIBSection = TestPlatform();
BOOL CDIBSurface::m_bUseWinG;
WinGCreateDCProc* CDIBSurface::m_pWinGCDCProc;
WinGCreateBitmapProc* CDIBSurface::m_pWinGCBProc;
WinGSetDIBColorTableProc* CDIBSurface::m_pWinGSDCTProc;
WinGBitBltProc* CDIBSurface::m_pWinGBBProc;
WinGStretchBltProc* CDIBSurface::m_pWinGSBProc;

static BOOL bForceWinG = FALSE; // set TRUE to always use WinG

// This static member function checks that the run-time platform supports
// CreateDIBSection or has WinG installed with Win32s
BOOL CDIBSurface::TestPlatform()
{
    // Set the initial pesimistic state
    m_bUseCreateDIBSection = FALSE;
    m_bUseWinG = FALSE;
    m_pWinGCDCProc = NULL;
    m_pWinGCBProc = NULL;
    m_pWinGSDCTProc = NULL;
    m_pWinGBBProc = NULL;
    m_pWinGSBProc = NULL;

    if (bForceWinG == FALSE) {
        // See if we are on Win32s which exports CreateDIBSection but does not support it
        DWORD dwVer = GetVersion();
        if ((dwVer & 0x800000FF) != 0x080000003) {
            // Not on Win32s so we can use CreateDIBSection.
            m_bUseCreateDIBSection = TRUE;
            return TRUE;
        }
    }
     
    // See if WinG has been installed
    HANDLE hMod = ::LoadLibrary("WING32");
    if (hMod) {
        m_pWinGCDCProc = (WinGCreateDCProc*) GetProcAddress((HMODULE) hMod,
                                                 "WinGCreateDC");
        m_pWinGCBProc = (WinGCreateBitmapProc*) GetProcAddress((HMODULE) hMod,
                                                 "WinGCreateBitmap");
        m_pWinGSDCTProc = (WinGSetDIBColorTableProc*) GetProcAddress((HMODULE) hMod,
                                                 "WinGSetDIBColorTable");
        m_pWinGBBProc = (WinGBitBltProc*) GetProcAddress((HMODULE) hMod,
                                                 "WinGBitBlt");
        m_pWinGSBProc = (WinGStretchBltProc*) GetProcAddress((HMODULE) hMod,
                                                 "WinGStretchBlt");
        if (m_pWinGCDCProc && m_pWinGCBProc && m_pWinGSDCTProc 
            && m_pWinGBBProc && m_pWinGSBProc) {
            m_bUseWinG = TRUE;
        }
    }
    
    // If we failed to find CreateDIBSection or WinG we're toast.
    if (!m_bUseCreateDIBSection && !m_bUseWinG) {
        AfxMessageBox("This application runs on Windows NT Version 3.5 or later,"
                      " Windows 95 or Windows 3.1 systems which have the "
                      " Win32s and WinG libraries installed.");
        AfxAbort();
    }

    return m_bUseCreateDIBSection;
}

IMPLEMENT_SERIAL(CDIBSurface, CDIB, 0)

CDIBSurface::CDIBSurface()
{
    m_hPal = NULL;
    m_hbmBuffer = NULL;
    m_hbmOld = NULL;

    if (m_bUseCreateDIBSection) {
        m_dcBuffer.CreateCompatibleDC(NULL);
    } else if (m_bUseWinG) {
        HDC hdc = (*m_pWinGCDCProc)();
        ASSERT(hdc);
        m_dcBuffer.Attach(hdc);
    } else {
        ASSERT(0); // shouldn't get this far
    }
}

CDIBSurface::~CDIBSurface()
{
    // The m_hPal is not our object - don't delete it.
    if (m_hbmOld) {
        ::SelectObject(m_dcBuffer.GetSafeHdc(), m_hbmOld);
    }
    if (m_hbmBuffer) ::DeleteObject(m_hbmBuffer);
}

/*
@mfunc BOOL | CDIBSurface | Create | Create a new surface.
@syntax BOOL Create(int cx, int cy, CPalette* pPal = NULL);
@syntax BOOL Create(int cx, int cy, HPALETTE hPal);
@parm int | cx | The width in pixels.
@parm int | cy | The height in pixels.
@parm CPalette* | pPal | An optional pointer to a palette to use.
@parm HPALETTE | hPal | Handle to a palette.
@rdesc The return value is TRUE if the surface is created, FALSE if not.
@comm The surface created can be drawn to using GDI operations or by
direct manipulation of the pixels.  If a palette is provided, the palette 
must remain valid for the lifetime of the surface.
@xref <c CDIBSurface>
*/

// Create a new surface. The palette pointer is copied.
BOOL CDIBSurface::Create(int cx, int cy, CPalette* pPal)
{
    HPALETTE hPal = NULL;
    if (pPal) hPal = (HPALETTE)pPal->m_hObject;
    return Create(cx, cy, hPal);
}
BOOL CDIBSurface::Create(int cx, int cy, HPALETTE hPal)
{
    if (!m_bUseCreateDIBSection && !m_bUseWinG) {
        TRACE("CDIBSurface: Invalid create call\n");
        return FALSE;
    }
    ASSERT(cx > 0);
    ASSERT(cy > 0);

    // Create a BITMAPINFO structure to describe the DIB
    BITMAPINFO* pBMI;
    int iSize = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
    pBMI = (BITMAPINFO*) malloc(iSize);
    if (!pBMI) {
        TRACE("Out of memory for DIB header");
        return FALSE;
    }
    memset(pBMI, 0, iSize);

    // fill in the header info 
    BITMAPINFOHEADER* pBIH = (BITMAPINFOHEADER*) pBMI;
    pBIH->biSize = sizeof(BITMAPINFOHEADER);
    pBIH->biWidth = cx;
    pBIH->biHeight = cy;
    pBIH->biPlanes = 1;
    pBIH->biBitCount = 8; // 8bpp
    pBIH->biCompression = BI_RGB;

    // get the palette color table
    int iColors = 0;
    if (hPal) {
        ::GetObject(hPal, sizeof(iColors), &iColors); // get num colors

        LOGPALETTE* pLP = (LOGPALETTE*) malloc(sizeof(LOGPALETTE)
                                               + 255 * sizeof(PALETTEENTRY));
        ASSERT(pLP);
        pLP->palVersion = 0x300;
        pLP->palNumEntries = iColors;
        PALETTEENTRY* pPE = pLP->palPalEntry;
        if (iColors) {
            ::GetPaletteEntries(hPal, 0, iColors, pPE);

            // copy the palette colors to the header 
            RGBQUAD* pct = (RGBQUAD*)(((BYTE *)(pBMI)) + sizeof(BITMAPINFOHEADER));
            for (int i = 0; i < iColors; i++) {
                pct->rgbRed = pPE[i].peRed;    
                pct->rgbGreen = pPE[i].peGreen;    
                pct->rgbBlue = pPE[i].peBlue;
                pct++;
            }
            pBMI->bmiHeader.biClrUsed = iColors;   
        }
    } // end if (hPal)

    // Copy the palette so we can use it to do screen drawing
    m_hPal = hPal;

    // delete any old buffer bitmap
    if (m_hbmOld) {
        ::SelectObject(m_dcBuffer.GetSafeHdc(), m_hbmOld);
        m_hbmOld = NULL;
    }                
    if (m_hbmBuffer) {
        ::DeleteObject(m_hbmBuffer);
        m_hbmBuffer = NULL;
    }

    BOOL bResult = FALSE;
    BYTE *pBits = NULL;
    if (m_bUseCreateDIBSection) {
        CDC dc;
        dc.CreateCompatibleDC(NULL);
        HPALETTE hPalOld = NULL;
        if (m_hPal) {
            hPalOld = ::SelectPalette(dc.GetSafeHdc(), m_hPal, FALSE);
            ::RealizePalette(dc.GetSafeHdc());
        }
        m_hbmBuffer = CreateDIBSection(dc.GetSafeHdc(),
                                       pBMI,
                                       DIB_RGB_COLORS,
                                       (VOID **) &pBits,
                                       NULL,
                                       0);
        if (hPalOld) ::SelectPalette(dc.GetSafeHdc(), hPalOld, FALSE);
        ASSERT(m_hbmBuffer);
        ASSERT(pBits);
        dc.DeleteDC();
        // Wrap this object around the buffer
        bResult = CDIB::Create(pBMI, pBits);
    } else if (m_bUseWinG) {
        // Note: WinG DCs are non-paletized so don't sel/rel palette
#if 0
        HDC hDC = m_dcBuffer.GetSafeHdc();
#else
        HDC hDC = (*m_pWinGCDCProc)();
#endif
        ASSERT(hDC);
        m_hbmBuffer = (*m_pWinGCBProc)(hDC,
                                      pBMI,
                                      (VOID **)&pBits);
        if(!m_hbmBuffer) {
            char buf[256];
            sprintf(buf, 
                    "WinG failed to create a %d x %d %d bpp %d color bitmap."
                    " The application will terminate.",
                    pBMI->bmiHeader.biWidth, pBMI->bmiHeader.biHeight,
                    pBMI->bmiHeader.biBitCount, pBMI->bmiHeader.biClrUsed);
            AfxMessageBox(buf);
            AfxAbort();
            return FALSE;
        }
        ASSERT(pBits);
        // Create the CDIB object from the buffer
        bResult = CDIB::Create(pBMI, pBits);

        // Set the colors from the palette
        if (m_hPal) MapColorsToPalette(m_hPal);
        RGBQUAD* pct = (RGBQUAD*)(((BYTE *)(pBMI)) + sizeof(BITMAPINFOHEADER));
        (*m_pWinGSDCTProc)(m_dcBuffer.GetSafeHdc(),
                          0,
                          iColors,
                          pct);
        
    } else {
        ASSERT(0);
    }

    // select the new bitmap into the buffer DC
    if (m_hbmBuffer) {
        m_hbmOld = (HBITMAP)::SelectObject(m_dcBuffer.GetSafeHdc(), m_hbmBuffer);
    }
     
    if (!bResult) {
        TRACE("Failed to create os dib");
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSurface message handlers

/*
@mfunc void | CDIBSurface | Draw | Draw a section of the off-screen
image buffer to the screen.
@syntax void Draw(CDC* pDC);
@syntax void Draw(HDC hDC);
@parm CDC* | pDC | The CDC object to draw to.
@parm HDC | hDC | The DC to draw to.
@rdesc There is no return value.
@comm The entire surface is drawn to the top-left corner of the supplied
CDC.
@xref <c CDIBSurface>
*/

// Draw the entire image buffer to the screen.
void CDIBSurface::Draw(CDC* pDC)
{
    BitBlt(pDC, 
           0, 0, 
           GetWidth(), GetHeight(),                         
           0, 0);
}

void CDIBSurface::Draw(HDC hDC, int x, int y)
{
    BitBlt(hDC, 
           x, y, 
           GetWidth(), GetHeight(),                         
           0, 0);
}

/*
@mfunc void | CDIBSurface | BitBlt | Blt a rectangle of the surface to
a given CDC.
@syntax void BitBlt(CDC* pDC, int xd, int yd, int w, int h, int xs, int ys);
@syntax void BitBlt(HDC hDC, int xd, int yd, int w, int h, int xs, int ys);
@parm CDC* | pDC | The CDC to draw to.
@parm HDC | hDC | The DC to draw to.
@parm int | xd | The x coordinate of the top-left corner of the
destination rectangle.
@parm int | yd | The y coordinate of the top-left corner of the
destination rectangle.
@parm int | w | The width of the rectangle to copy.
@parm int | h | The height of the rectangle to copy.
@parm int | xs | The x coordinate of the top-left corner of the
source rectangle.
@parm int | ys | The y coordinate of the top-left corner of the
source rectangle.
@rdesc There is no return value.
@comm The rectangle defined is copied from the source to the 
destination.
@xref <c CDIBSurface>
*/

void CDIBSurface::BitBlt(CDC* pDC, int xd, int yd, int w, int h,
                         int xs, int ys)
{
    BitBlt(pDC->GetSafeHdc(), xd, yd, w, h, xs, ys);
}

void CDIBSurface::BitBlt(HDC hDC, int xd, int yd, int w, int h,
                         int xs, int ys)
{

#if 0  // shouldn't be doing this here. Caller should do this
    // if we have a palette, select and realize it
    HPALETTE hPalOld = NULL;
    if(m_hPal) {
        hPalOld = ::SelectPalette(hDC, m_hPal, 0);
        ::RealizePalette(hDC);
    }
#endif

    if (m_bUseCreateDIBSection) {
        // Note: you do not need to select the palette into
        // the memory DC because the DIB section is using palette
        // index values not colors
        ::BitBlt(hDC,
                 xd, yd,
                 w, h,
                 m_dcBuffer.GetSafeHdc(),
                 xs, ys,
                 SRCCOPY);
    } else if (m_bUseWinG) {
        (*m_pWinGBBProc)(hDC,
                         xd, yd,
                         w, h,
                         m_dcBuffer.GetSafeHdc(),
                         xs, ys);
    } else {
        ASSERT(0); // arrrrgh!
    }

#if 0
    // select old palette if we altered it
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);
#endif
}

/*
@mfunc void | CDIBSurface | StretchBlt | Blt a rectangle of the surface to
a given CDC.
@syntax void StretchBlt(CDC* pDC, int xd, int yd, int wd, int hd,
int xs, int ys, int ws, int hs);
@parm CDC* | pDC | The CDC to draw to.
@parm int | xd | The x coordinate of the top-left corner of the
destination rectangle.
@parm int | yd | The y coordinate of the top-left corner of the
destination rectangle.
@parm int | wd | The width of the destination rectangle.
@parm int | hd | The height of the destination rectangle.
@parm int | xs | The x coordinate of the top-left corner of the
source rectangle.
@parm int | ys | The y coordinate of the top-left corner of the
source rectangle.
@parm int | ws | The width of the source rectangle.
@parm int | hs | The height of the source rectangle.
@rdesc There is no return value.
@comm The rectangle defined is copied from the source to the 
destination.
@xref <c CDIBSurface>
*/

void CDIBSurface::StretchBlt(CDC* pDC, int xd, int yd, int wd, int hd,
                         int xs, int ys, int ws, int hs)
{
#if 0
    // if we have a palette, select and realize it
    CPalette *ppalOld = NULL;
    if(m_hPal) {
        ppalOld = pDC->SelectPalette(m_pPal, 0);
        pDC->RealizePalette();
    }
#endif
    if (m_bUseCreateDIBSection) {
        // Note: you do not need to select the palette into
        // the memory DC because the DIB section is using palette
        // index values not colors
        pDC->StretchBlt(xd, yd,
                        wd, hd,
                        &m_dcBuffer,
                        xs, ys,
                        ws, hs,
                        SRCCOPY);
    } else if (m_bUseWinG) {
        (*m_pWinGSBProc)(pDC->GetSafeHdc(),
                         xd, yd,
                         wd, hd,
                         m_dcBuffer.GetSafeHdc(),
                         xs, ys,
                         ws, hs);
    } else {
        ASSERT(0); // arrrrgh!
    }
#if 0
    // select old palette if we altered it
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);
#endif
}

/*
@mfunc void | CDIBSurface | SetPalette | Set a new palette.
@syntax void SetPalette(CPalette* pPal);
@parm CPalette* | pPal | Pointer to the new palette.
@rdesc There is no return value.
@xref <c CDIBSurface>
*/

void CDIBSurface::SetPalette(CPalette* pPal)
{
    SetPalette((HPALETTE)pPal->m_hObject);
}

void CDIBSurface::SetPalette(HPALETTE hPal)
{
    ASSERT(hPal);
    m_hPal = hPal;

    // get the colors from the palette
    int iColors = 0;
    ::GetObject(m_hPal, sizeof(iColors), &iColors);
    ASSERT(iColors > 0);
    PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
    ::GetPaletteEntries(m_hPal, 0, iColors, pPE);

    // Build a table of RGBQUADS
    RGBQUAD* pRGB = new RGBQUAD[iColors];
    ASSERT(pRGB);
    for (int i = 0; i < iColors; i++) {
        pRGB[i].rgbRed = pPE[i].peRed;
        pRGB[i].rgbGreen = pPE[i].peGreen;
        pRGB[i].rgbBlue = pPE[i].peBlue;
        pRGB[i].rgbReserved = 0;
    }
    
    if (m_bUseCreateDIBSection) {
        ::SetDIBColorTable(m_dcBuffer.GetSafeHdc(),
                           0, iColors,
                           pRGB);
    } else if (m_bUseWinG) {
        (*m_pWinGSDCTProc)(m_dcBuffer.GetSafeHdc(),
                          0, iColors,
                          pRGB);
    } else {
        ASSERT(0); // arrrrgh!
    }

    delete [] pRGB;
    delete [] pPE;
}

/*
@mfunc void | CDIBSurface | Load | Load the surface from a file.
@syntax BOOL Load(const char* pszFileName);
@parm const char* | pszFileName | The name of the file to load the DIB from.
@rdesc The return value is TRUE if the DIB is loaded, FALSE if not.
@comm The file may be in either Windows DIB format or Presentation
Manager DIB format.
@xref <c CDIBSurface>
*/
BOOL CDIBSurface::Load(const char* pszFileName/*=NULL*/)
{
    // BUGBUG: This is pretty inefficient and is only done
    // because it's difficult to create a shareable dib section
    // before we've loaded the dib image and found out how
    // big it is

    // Create a dummy DIB
    CDIB dib;
    if (!dib.Load(pszFileName)) return FALSE;

    // And palette
    CDIBPal pal;
    pal.Create(&dib);

    // Create a DIBSurface the same size as the DIB
    if (!Create(dib.GetWidth(), dib.GetHeight(), &pal)) return FALSE;

    // Copy the dib image to the dibsurface
    dib.CopyBits(this, 
                 0, 0,
                 dib.GetWidth(), dib.GetHeight(),
                 0, 0);

    return TRUE;
}

BOOL CDIBSurface::MapColorsToPalette(CPalette *pPal)
{
    return CDIBSurface::MapColorsToPalette((HPALETTE)pPal->m_hObject);
}

BOOL CDIBSurface::MapColorsToPalette(HPALETTE hPal)
{
    // map the image colors
    if (!CDIB::MapColorsToPalette(hPal)) return FALSE;
    // Update the DIB section color table
    SetPalette(hPal);
    return TRUE;
}

