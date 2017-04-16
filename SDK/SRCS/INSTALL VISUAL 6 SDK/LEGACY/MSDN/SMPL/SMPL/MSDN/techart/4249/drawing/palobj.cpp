// palobj.cpp : implementation file
//

#include "stdafx.h"
#include "Drawing.h"
#include "palobj.h"
#include "ids.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPalObj

IMPLEMENT_DYNCREATE(CColorPalObj, CCmdTarget)

CColorPalObj::CColorPalObj()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
    m_hdcActive = NULL;
    m_hpalOld = NULL;
}

CColorPalObj::~CColorPalObj()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CColorPalObj::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CColorPalObj, CCmdTarget)
	//{{AFX_MSG_MAP(CColorPalObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CColorPalObj, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CColorPalObj)
	DISP_PROPERTY_EX(CColorPalObj, "hPal", GetHPal, SetNotSupported, VT_I4)
	DISP_FUNCTION(CColorPalObj, "CreateColorCube", CreateColorCube, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CColorPalObj, "Draw", Draw, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CColorPalObj, "MakeIdentity", MakeIdentity, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CColorPalObj, "CreateFromImage", CreateFromImage, VT_BOOL, VTS_DISPATCH)
	DISP_FUNCTION(CColorPalObj, "Apply", Apply, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CColorPalObj, "Remove", Remove, VT_EMPTY, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CColorPalObj, "ColorPalette", 0x68fca73, 0x6dff, 0x11ce, 0x9e, 0xfe, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

/////////////////////////////////////////////////////////////////////////////
// CColorPalObj message handlers

BOOL CColorPalObj::CreateColorCube() 
{
	// Create a color cube palette
    if (!m_Pal.CreateWash()) {
        TRACE("Failed to create color cube\n");
        return FALSE;
    }

    // Make it an identiy palette
    if (!m_Pal.SetSysPalColors()) {
        TRACE("Failed to make identity palette\n");
        return FALSE;
    }

	return TRUE;
}

long CColorPalObj::GetHPal() 
{
	// Return the GDI palette object handle
	return (long)(m_Pal.m_hObject);
}

void CColorPalObj::Draw(long hDC, long x1, long y1, long x2, long y2) 
{
	CRect rc (x1, y1, x2, y2);
    m_Pal.Draw((HDC)hDC, &rc);

}

void CColorPalObj::MakeIdentity() 
{
    m_Pal.SetSysPalColors();
}

BOOL CColorPalObj::CreateFromImage(LPDISPATCH pDispatch) 
{
    ASSERT(pDispatch);
    IDrawSurfObj dso;
    dso.AttachDispatch(pDispatch, FALSE);
    BITMAPINFO* pBMI = (BITMAPINFO*) (dso.GetBitmapInfo());
    ASSERT(pBMI);
	return m_Pal.Create(pBMI);
}

void CColorPalObj::Apply(long hDC) 
{
    ASSERT(hDC);
	// We can only save one previous state
    ASSERT(m_hdcActive == NULL);
    m_hpalOld = ::SelectPalette((HDC)hDC, (HPALETTE)(m_Pal.m_hObject), FALSE);
    ::RealizePalette((HDC)hDC);
    m_hdcActive = (HDC)hDC;
}

void CColorPalObj::Remove(long hDC) 
{
	ASSERT(m_hdcActive == (HDC)hDC);
    ::SelectPalette(m_hdcActive, m_hpalOld, FALSE);
    m_hdcActive = NULL;
    m_hpalOld = NULL;
}
