// mywnd.cpp : implementation file
//

#include "stdafx.h"
#include "pop3.h"
#include "mywnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWnd

CMyWnd::CMyWnd()
{
    m_uiTimer = 0;
    m_iBackMode = theApp.GetProfileInt("Config",
                                       "Background",
                                       BACK_BLACK);
}

CMyWnd::~CMyWnd()
{
}

BEGIN_MESSAGE_MAP(CMyWnd, CAnimWnd)
	//{{AFX_MSG_MAP(CMyWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// Window creation and sizing

BOOL CMyWnd::Create()
{
    // create the palette we want to use
    switch (m_iBackMode) {
    case BACK_SCREEN: {
        HDC hdcScreen = ::GetDC(NULL);
        CDC dcScreen;
        dcScreen.Attach(hdcScreen);
        // create a palette for the current screen condition
        // allocate a log pal and fill it with the color table info
        LOGPALETTE* pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) 
                         + 256 * sizeof(PALETTEENTRY));
        ASSERT(pPal);
        pPal->palVersion = 0x300; // Windows 3.0
        pPal->palNumEntries = (WORD) 256; // table size
        GetSystemPaletteEntries(hdcScreen, 
                                0,
                                256,
                                pPal->palPalEntry);
        m_Pal.CreatePalette(pPal);
        free(pPal);
        } break;

    case BACK_BLACK:
    default:
        m_Pal.CreateWash();
        m_Pal.SetSysPalColors();
        break;
    }

    if (!CAnimWnd::Create(&m_Pal)) {
        return FALSE;
    }
    
    m_uiTimer = SetTimer(1, 100, NULL);
    return TRUE;                 
}

int CMyWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CAnimWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_dsBackground.Create(lpCreateStruct->cx,
                          lpCreateStruct->cy,
                          &m_Pal);

    CDC* pdcBkGnd = m_dsBackground.GetDC();
    switch (m_iBackMode) {
    case BACK_SCREEN: {
        // Fill the background image with the current screen image
        HDC hdcScreen = ::GetDC(NULL);
        CDC dcScreen;
        dcScreen.Attach(hdcScreen);
        CPalette* pOldPal1 = (CPalette*)dcScreen.SelectObject(&m_Pal);
        dcScreen.RealizePalette();
        pdcBkGnd->BitBlt(0, 0,
                         ::GetSystemMetrics(SM_CXSCREEN),
                         ::GetSystemMetrics(SM_CYSCREEN),
                         &dcScreen,
                         0, 0,
                         SRCCOPY);
        dcScreen.SelectObject(pOldPal1);
        dcScreen.Detach();
        } break;

    case BACK_BLACK:
    default:
        // Fill the background with black
        CBrush br(PALETTERGB(0, 0, 0));
        CRect rc(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);
        pdcBkGnd->FillRect(&rc, &br);
        break;
    }

    // Load the sprites
    m_spGui.Load(IDR_DIB_GUI);
    m_spGui.MapColorsToPalette(&m_Pal);
    InsertSprite(&m_spGui);

    m_spHeads.Load(IDR_DIB_HEADS);
    m_spHeads.MapColorsToPalette(&m_Pal);
    m_spHeads.SetNumCellRows(12);
    InsertSprite(&m_spHeads);

	return 0;
}

void CMyWnd::OnDestroy() 
{
    if (m_uiTimer) KillTimer(1);
}

/////////////////////////////////////////////////////////////////////////////
// Rendering and Drawing

void CMyWnd::Render(RECT* pClipRect)
{
    // Compute the clip box
    CRect rcDraw;
    m_dsBackground.GetRect(&rcDraw);
    if (pClipRect) {
        rcDraw.IntersectRect(&rcDraw, pClipRect);
    }

    // Copy the background to the buffer
    m_dsBackground.CopyBits(&m_dsBuffer,
                       rcDraw.left, rcDraw.top,
                       rcDraw.right - rcDraw.left, rcDraw.bottom - rcDraw.top,
                       rcDraw.left, rcDraw.top);

    // Call base class to render the sprites
    CAnimWnd::RenderSprites(pClipRect);
}

void CMyWnd::OnSize(UINT nType, int cx, int cy) 
{
	CAnimWnd::OnSize(nType, cx, cy);
	
	m_spGui.SetPosition(0, cy - m_spGui.GetHeight());
    m_spHeads.SetPosition(0, 0);
	
}

void CMyWnd::OnTimer(UINT nIDEvent) 
{
    int sw = ::GetSystemMetrics(SM_CXSCREEN);
    int sh = ::GetSystemMetrics(SM_CYSCREEN);

    int w = m_spGui.GetWidth();
    int h = m_spGui.GetHeight();
    int x = m_spGui.GetX() + 2;
    int y = m_spGui.GetY() - 4;
    if (x > sw) x = -w;
    if ((y + h) < 0) y = sh;
    m_spGui.SetPosition(x, y);

    w = m_spGui.GetWidth();
    h = m_spGui.GetHeight();
    x = m_spHeads.GetX() + 1;
    y = m_spHeads.GetY() + 2;
    int p = m_spHeads.GetCellRow() + 1;
    if (x > sw) x = -w;
    if (y > sh) y = -h;
    if (p >= m_spHeads.GetNumCellRows()) p = 0;
    m_spHeads.SetPosition(x, y);
    m_spHeads.SetCellRow(p);

    RenderAndDrawDirtyList();
}


