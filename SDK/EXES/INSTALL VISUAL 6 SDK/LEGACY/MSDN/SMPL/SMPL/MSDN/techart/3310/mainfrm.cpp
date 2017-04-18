// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "metavw1.h"
#include "metavdoc.h"
#include "emfinfov.h"
#include "metavvw.h"
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
	ON_COMMAND(ID_VIEW_INFO, OnViewInfo)
	ON_COMMAND(ID_VIEW_PICTURE, OnViewPicture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
	
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_OPEN,
		ID_SEPARATOR,
	ID_EDIT_COPY,
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
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

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

void CMainFrame::OnViewInfo() 
{
  CreateOrActivateFrame(theApp.pEMFInfoTemplate, RUNTIME_CLASS(CEMFInfoView));
}	

void CMainFrame::OnViewPicture() 
{
  CreateOrActivateFrame(theApp.pDocTemplate, RUNTIME_CLASS(CMetavw1View));
}

void CMainFrame::CreateOrActivateFrame(CDocTemplate* pTemplate, 
    CRuntimeClass* pViewClass)
{
    // If a view (specified by pViewClass) already exists,
    // activate the MDI child window containing the view.
    // Otherwise, create a new view for the document.

    CMDIChildWnd* pMDIActive = MDIGetActive();
    ASSERT(pMDIActive != NULL);
    CDocument* pDoc = pMDIActive->GetActiveDocument();
    ASSERT(pDoc != NULL);

    CView* pView;
    POSITION pos = pDoc->GetFirstViewPosition();
    while (pos)
    {
        pView = pDoc->GetNextView(pos);
        if (pView->IsKindOf(pViewClass))
        {
            pView->GetParentFrame()->ActivateFrame();
            return;
        }
    }

    CMDIChildWnd* pNewFrame
        = (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));

    if (pNewFrame == NULL)
        return;     // not created

    ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
    pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
}
