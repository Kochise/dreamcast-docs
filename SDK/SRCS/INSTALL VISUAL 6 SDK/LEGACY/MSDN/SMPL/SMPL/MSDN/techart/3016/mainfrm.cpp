// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "math.h"
#include "fwtest.h"
#include "dlgpanel.h"
#include "dlgpanfm.h"
#include "rotary.h"
#include "updnctl.h"
#include "scopefra.h"
#include "panelfra.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(ID_TEST_SCOPE1, OnTestScopeCreate)
    ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
    ON_COMMAND(ID_TEST_CTLPANEL, OnTestCtlpanel)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
    // same order as in the bitmap 'toolbar.bmp'
    ID_FILE_NEW,
    ID_FILE_OPEN,
    ID_FILE_SAVE,
        ID_SEPARATOR,
    ID_EDIT_CUT,
    ID_EDIT_COPY,
    ID_EDIT_PASTE,
        ID_SEPARATOR,
    ID_FILE_PRINT,
    ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_pData0 = NULL;
    m_iPoints0 = 0;
    m_pData1 = NULL;
    m_iPoints1 = 0;
    m_dInterval = 1.0 / 11025.0;
    GenerateData();
}

CMainFrame::~CMainFrame()
{
    if (m_pPal) delete m_pPal;
    if (m_pData0) delete m_pData0;
    if (m_pData1) delete m_pData1;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    // Create a wash palette to use
    m_pPal = new CDIBPal;
    ASSERT(m_pPal);
    m_pPal->CreateWash();

    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.Create(this) ||
        !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
        !m_wndToolBar.SetButtons(buttons,
          sizeof(buttons)/sizeof(UINT)))
    {
        TRACE("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE("Failed to create status bar\n");
        return -1;      // fail to create
    }

    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::GenerateData()
{
    if (m_pData0) delete m_pData0;
    if (m_pData1) delete m_pData1;
    double dFreq = 1000; // 1 kHz
    double dTime = 0.1; // 100 ms burst
    double dPhase = 0.0;
    double dPI = 4.0 * atan(1.0);
    double dPhaseStep = dPI * 2 * dFreq * m_dInterval;
    // normalize the step just in case we went crazy
    while (dPhaseStep >= dPI * 2) dPhaseStep -= dPI * 2;
    int iSamples = (int)ceil(dTime / m_dInterval);
    m_pData0 = new double[iSamples];
    m_pData1 = new double[iSamples];
    m_iPoints0 = iSamples;
    m_iPoints1 = iSamples;
    double* p0 = m_pData0;
    double* p1 = m_pData1;
    for (int i = 0; i < iSamples; i++) {
        *p0++ = sin(dPhase);
        if (dPhase < dPI) {
            *p1++ = 1.0;
        } else {
            *p1++ = -1.0;
        }
        dPhase += dPhaseStep;
        if (dPhase >= dPI * 2) dPhase -= dPI * 2;
    }
}


BOOL CMainFrame::OnQueryNewPalette()
{
    // We are going active or the system palette has changed
    // so realize our palette
    if (m_pPal) {
        CDC* pDC = GetDC();
        CPalette *pOldPal = pDC->SelectPalette(m_pPal, FALSE);
        UINT u = pDC->RealizePalette();
        ReleaseDC(pDC);
        if (u != 0) {
            // some colors changed so we need to do a repaint
            InvalidateRect(NULL, TRUE); // repaint the lot
        }
    }
    return TRUE; // Windows ignores this
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}


void CMainFrame::OnTestScopeCreate()
{
    // Create a new scope window
    CScopeFrame* pScope = new CScopeFrame;
    ASSERT(pScope);
    CRect rc(10, 10, 400, 300);
    pScope->Create("Scope",
                   rc,
                   this,
                   IDR_SCOPE,
                   m_pPal);
    pScope->MDIActivate();
    pScope->SetData(m_pData0, m_iPoints0, m_dInterval, 0); 
    pScope->SetData(m_pData1, m_iPoints1, m_dInterval, 1); 
}
void CMainFrame::OnTestCtlpanel()
{
    // Create a new control panel window
    CPanelFrame* pPanel = new CPanelFrame;
    ASSERT(pPanel);
    CRect rc(10, 10, 400, 300);
    pPanel->Create("Panel",
                   rc,
                   this,
                   IDD_CTLPANEL, // dlg box res id
                   IDR_PANEL, // icon res id
                   m_pPal);
    pPanel->MDIActivate();
}

