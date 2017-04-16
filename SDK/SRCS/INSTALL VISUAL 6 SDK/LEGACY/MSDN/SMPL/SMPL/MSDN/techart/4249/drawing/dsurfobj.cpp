// dsurfobj.cpp : implementation file
//

#include "stdafx.h"
#include "Drawing.h"
#include "ids.h"
#include "dsurfobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawSurfObj

IMPLEMENT_DYNCREATE(CDrawSurfObj, CCmdTarget)

CDrawSurfObj::CDrawSurfObj()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CDrawSurfObj::~CDrawSurfObj()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CDrawSurfObj::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CDrawSurfObj, CCmdTarget)
	//{{AFX_MSG_MAP(CDrawSurfObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrawSurfObj, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CDrawSurfObj)
	DISP_PROPERTY_EX(CDrawSurfObj, "Width", GetWidth, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CDrawSurfObj, "Height", GetHeight, SetNotSupported, VT_I4)
	DISP_PROPERTY_EX(CDrawSurfObj, "hDC", GetHDC, SetNotSupported, VT_I4)
	DISP_FUNCTION(CDrawSurfObj, "LoadFile", LoadFile, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CDrawSurfObj, "Draw", Draw, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CDrawSurfObj, "MapToPalette", MapToPalette, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CDrawSurfObj, "GetBitmapInfo", GetBitmapInfo, VT_I4, VTS_NONE)
	DISP_FUNCTION(CDrawSurfObj, "CreateNew", CreateNew, VT_BOOL, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CDrawSurfObj, "CopyWithTransparency", CopyWithTransparency, VT_EMPTY, VTS_DISPATCH VTS_I4 VTS_I4)
	DISP_FUNCTION(CDrawSurfObj, "GetDIBSurface", GetDIBSurface, VT_I4, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CDrawSurfObj, "DrawingSurface", 0x68fca75, 0x6dff, 0x11ce, 0x9e, 0xfe, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

/////////////////////////////////////////////////////////////////////////////
// CDrawSurfObj message handlers

BOOL CDrawSurfObj::LoadFile(LPCTSTR pszFile) 
{
	return m_ds.Load(pszFile);
}

void CDrawSurfObj::Draw(long hDC, long x, long y) 
{
    m_ds.Draw((HDC)hDC, x, y);
}

BOOL CDrawSurfObj::MapToPalette(long hPal) 
{
	if (!hPal) return FALSE;
	return m_ds.MapColorsToPalette((HPALETTE)hPal);
}

long CDrawSurfObj::GetBitmapInfo() 
{
	// BUGBUG: Internal use only.
    // This returns a pointer to the bitmap info
	return (long) m_ds.GetBitmapInfoAddress();
}

BOOL CDrawSurfObj::CreateNew(long width, long height, long hPal) 
{
	return m_ds.Create(width, height, (HPALETTE)hPal);
}

long CDrawSurfObj::GetWidth() 
{
	return m_ds.GetWidth();
}

long CDrawSurfObj::GetHeight() 
{
	return m_ds.GetHeight();
}

long CDrawSurfObj::GetHDC() 
{
	return (long) (m_ds.GetHDC());
}

long CDrawSurfObj::GetDIBSurface() 
{
	// BUGBUG: Internal use only.
    // This returns a pointer to the CDIBSurface object
	return (long) &m_ds;
}

void CDrawSurfObj::CopyWithTransparency(LPDISPATCH pDispatch, long x, long y) 
{
    ASSERT(pDispatch);
    IDrawSurfObj dso;
    dso.AttachDispatch(pDispatch, FALSE);

    // Get a pointer to the destination DIB surface
    CDIBSurface* pds = (CDIBSurface*) (dso.GetDIBSurface());
    ASSERT(pds);
    ASSERT(pds->IsKindOf(RUNTIME_CLASS(CDIBSurface)));

    // Get the pixel color of the top-left corner
    BYTE* p = (BYTE*) m_ds.GetPixelAddress(0, 0);
    ASSERT(p);

    // flush the GDI queue
    ::GdiFlush();

    // Clip to the destination rectangle
    int xs = 0;
    int ys = 0;
    int xd = x;
    int yd = y;
    int ws = m_ds.GetWidth();
    int hs = m_ds.GetHeight();
    int wd = pds->GetWidth();
    int hd = pds->GetHeight();
    int d;
    if (x < 0) {
        d = -x;
        xd = 0;
        ws -= d;
        xs += d;
    }
    if ((x + ws) > wd) {
        d = x + ws - wd;
        ws -= d;
    }
    if (y < 0) {
        d = -y;
        yd = 0;
        hs -= d;
        ys += d;
    }
    if ((y + hs) > hd) {
        d = y + hs - hd;
        hs -= d;
    }

    if (ws <= 0) return;
    if (hs <= 0) return;
    
    // Copy the bits
    m_ds.CopyBits(pds,
                  xd, yd,
                  ws, hs,
                  xs, ys,
                  PALETTEINDEX(*p));

	return;
}

