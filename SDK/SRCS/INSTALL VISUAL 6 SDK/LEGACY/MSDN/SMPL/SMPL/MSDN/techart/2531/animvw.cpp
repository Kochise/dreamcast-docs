// animvw.cpp : implementation of the CAnimView class
//

#include "stdafx.h"
#include "gravity.h"
#include "animdoc.h"
#include "animvw.h"
#include "body.h"/*DER -- "animsp.h"*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//
// Constants --- DER 
//          
const UINT G_TIMER = 555 ;

/////////////////////////////////////////////////////////////////////////////
// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, COffScreenDIBView)

BEGIN_MESSAGE_MAP(CAnimView, COffScreenDIBView)
   //{{AFX_MSG_MAP(CAnimView)
   ON_COMMAND(ID_FILE_LOADBKGND, OnFileLoadbkgnd)
   ON_COMMAND(ID_FILE_LOADSPRITE, OnFileLoadsprite)
   ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(IDM_SIMULATE_GO, OnSimulateGo)
	ON_UPDATE_COMMAND_UI(IDM_SIMULATE_GO, OnUpdateSimulateGo)
	ON_COMMAND(IDM_SIMULATE_STOP, OnSimulateStop)
	ON_UPDATE_COMMAND_UI(IDM_SIMULATE_STOP, OnUpdateSimulateStop)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_FILE_LOADSPRITE, OnUpdateFileLoadsprite)
	ON_UPDATE_COMMAND_UI(ID_FILE_LOADBKGND, OnUpdateFileLoadbkgnd)
	ON_COMMAND(IDM_OPTIONS_UNIVERSE, OnOptionsUniverse)
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS_UNIVERSE, OnUpdateOptionsUniverse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimView construction/destruction

CAnimView::CAnimView()
	: m_timer(NULL)
{
}

CAnimView::~CAnimView()
{
}

void CAnimView::OnInitialUpdate()
{
	// In an SDI application the CView object is not destroyed,
	// when a new file is loaded or created so we must reset stuff here.
	if (m_timer) 
	{
		VERIFY(KillTimer(m_timer)) ;
		m_timer = NULL ;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAnimView drawing
// All done by the base class

/////////////////////////////////////////////////////////////////////////////
// CAnimView diagnostics

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
    COffScreenDIBView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
    COffScreenDIBView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
    return (CAnimDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimView message handlers

// Load a new background DIB
void CAnimView::OnFileLoadbkgnd()
{
    CAnimDoc* pDoc = GetDocument();
	if(pDoc->m_bSimulate)
	{
		MessageBeep(0) ;
		return ;
	}

    CDIB *pdib = new CDIB;
    // Show the file open dialog for a DIB
    if (!pdib->Load()) {
        delete pdib;
        return;
    }
    // replace the existing background DIB which will cause
    // the view to create a new offscreen buffer with a new palette
    // and map the DIB to the new palette
    if (!pDoc->SetBkgnd(pdib)) {
        delete pdib;
    }
}

void CAnimView::OnUpdateFileLoadbkgnd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!GetDocument()->m_bSimulate) ;	
}

void CAnimView::OnFileLoadsprite()
{
    CAnimDoc* pDoc = GetDocument();

	if(pDoc->m_bSimulate)
	{
		MessageBeep(0) ;
		return ;
	}

    //DER --- CAnimSprite
    CBody *psprite = new CBody ; //DER -- CAnimSprite;

    // show the file open dialog to load the image
    if (!psprite->Load()) {
        delete psprite;
        return;
    }
    // add the new sprite to the list
    pDoc->AddSprite(psprite);
}   

void CAnimView::OnUpdateFileLoadsprite(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!GetDocument()->m_bSimulate) ;	
}

// Render the image of the background and sprites to the off-screen buffer
void CAnimView::Render(LPRECT pClipRect)
{
    CAnimDoc* pDoc = GetDocument();
    CRect rcDraw;

    // get the background DIB and render it
    CDIB *pdib = pDoc->GetBkgnd();
    if (pdib) {
        pdib->GetRect(&rcDraw);
        if (pClipRect) {
            rcDraw.IntersectRect(pClipRect, &rcDraw);
        }

        // draw the image of the DIB to the os buffer
        pdib->CopyBits(m_pDIB,           // dest DIB
                    rcDraw.left,
                    rcDraw.top,          // dest start point
                    rcDraw.right - rcDraw.left,
                    rcDraw.bottom - rcDraw.top,
                    rcDraw.left, 
                    rcDraw.top);
    }

    // Render the sprite list from the bottom of the list to the top
    // Note that we always clip to the background DIB
    CSpriteList *pList = pDoc->GetSpriteList();
    POSITION pos = pList->GetTailPosition();
    CSprite *pSprite;
    while (pos) {
        pSprite = pList->GetPrev(pos);
        pSprite->Render(m_pDIB, &rcDraw);
    }                 
}

// Render and draw each rectangle in the dirty list then
// reset the list
void CAnimView::RenderAndDrawDirtyList()
{
    POSITION pos;
    CRect *pRect;
    for (pos = m_DirtyList.GetHeadPosition(); pos != NULL;) {
        pRect = m_DirtyList.GetNext(pos); // inc pos
        ASSERT(pRect);
        Render(pRect);
        Draw(NULL, pRect);
    }
    m_DirtyList.RemoveAll();            
}

// Called when the document has changed in some way.  We use the lHint
// parameter to work out what we need to do.
// If no hint is defined then we default to repainting everything.
void CAnimView::OnUpdate(CView *pView, LPARAM lHint, CObject *pObj)
{
//    dprintf2("CAnimView::OnUpdate");
    CDIB *pdib;
    CSize size;
    CRect rcFrame;
    CRect rcView;
    CRect rcDraw;
    //DER CAnimSprite 
    CBody *pSprite;
    CFrameWnd* pFrame;
    CAnimDoc* pDoc = GetDocument();

    switch (lHint) {
    case HINT_NEWBKGNDDIB:
        // Create a new off-screen buffer to match the
        // new background DIB
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CDIB)));
        pdib = (CDIB *) pObj;
        CreateFromDIB(pdib);
        // Map the DIB colors to match the palette
        MapDIBColors(pdib);
        // Adjust the frame window to fit the new background
        pFrame = GetParentFrame();
        ASSERT(pFrame != NULL);
        pFrame->GetWindowRect(rcFrame);
        size = rcFrame.Size();
        if (IsWindowVisible()) {
            GetClientRect(rcView);
            size.cx -= (rcView.right - pdib->GetWidth());
            size.cy -= (rcView.bottom - pdib->GetHeight());
        } else {
            size.cx = GetSystemMetrics(SM_CXSCREEN) / 2;
            size.cy = GetSystemMetrics(SM_CYSCREEN) / 2;
        }
        pFrame->SetWindowPos(NULL,
                             0, 0, 
                             size.cx, size.cy,
                             SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
        // Render and paint the whole off-screen buffer to the screen
        Render();
        Draw();
        break;
    case HINT_NEWSPRITE:
  //      dprintf3("  HINT_NEWSPRITE");
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CBody))); //DER was CAnimSprite
        pSprite = (CBody *) pObj; //DER was CAnimSprite
        // map the DIB colors to the os-DIB palette
        pSprite->MapColorsToPalette(m_pPal);
        // Re-render the area occupied by the new sprite
        pSprite->GetRect(&rcDraw);
        Render(&rcDraw);
        Draw(NULL, &rcDraw);
        break;
    case HINT_DIRTY:
        m_DirtyList.Add((CRect *) pObj);
        break;
    case HINT_DIRTYLIST:
    //    dprintf4("  HINT_DIRTYLIST");
        RenderAndDrawDirtyList();
        break;
    default:
        //dprintf3("  (no hint)");
        // just do a complete repaint 
        // from the off-screen DIB to the screen
        Render();
        Draw();
        break;
    }
}


void CAnimView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CAnimDoc* pDoc = GetDocument();
    //CAnimSprite 
    CBody *pSprite = (CBody *) //DER was AnimSprite
        (pDoc->GetSpriteList())->HitTest(point);
    if (pSprite) {
        ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CBody))); //DER was CAnimSprite
        if (pSprite->DoDialog()) {
            pDoc->UpdateAllViews(NULL);
        }
    } else {
        ::MessageBeep(NULL);
    }
}



void CAnimView::OnSimulateGo()
{
	CAnimDoc*pDoc = GetDocument() ;
	if (pDoc->AnySprites())
	{
		if (pDoc->m_bSimulate == FALSE)
		{		
			m_timer = SetTimer(G_TIMER,CUniverse::TIME,NULL) ; 
			if (m_timer != 0)
			{
				pDoc->m_bSimulate	= TRUE ; 			
				return ;
			}		
		}
	}
	MessageBeep(0) ;	
}

void CAnimView::OnUpdateSimulateGo(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetDocument()->m_bSimulate) ;		
}

void CAnimView::OnSimulateStop()
{
	CAnimDoc*pDoc = GetDocument() ;
	if (pDoc->m_bSimulate == TRUE)
	{
		KillTimer(m_timer) ;
		m_timer = NULL ;	
		pDoc->m_bSimulate = FALSE ;			
	}
	else
	{
		MessageBeep(0) ;
	}
}

void CAnimView::OnUpdateSimulateStop(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(!GetDocument()->m_bSimulate) ;		
}

void CAnimView::OnTimer(UINT nIDEvent)
{		
	COffScreenDIBView::OnTimer(nIDEvent);
   CAnimDoc *pDoc = GetDocument();
	ASSERT(pDoc->m_bSimulate == TRUE) ;
   pDoc->UpdateSpritePositions();
}

void CAnimView::OnSize(UINT nType, int cx, int cy)
{
	COffScreenDIBView::OnSize(nType, cx, cy);

	CRect aRect ;
	GetClientRect(aRect) ;		
	CBody::SetUniverseScale(&aRect) ;	
}

void CAnimView::OnDestroy()
{
	if (m_timer) 
	{		
		VERIFY(KillTimer(m_timer)) ;	
		m_timer = NULL ;
	}

	COffScreenDIBView::OnDestroy();		
}



	

void CAnimView::OnOptionsUniverse()
{
	CAnimDoc * pDoc = GetDocument() ;

	if (pDoc->m_bSimulate)
	{
		MessageBeep(0) ;
		return ;
	}
	if (CUniverse::DoUniDialog()) 
	{		
		CRect aRect ;
		GetClientRect(aRect) ;		
		CBody::SetUniverseScale(&aRect) ;		

		pDoc->ResetBodies() ;
		pDoc->SetModifiedFlag() ;
	}
	
}

void CAnimView::OnUpdateOptionsUniverse(CCmdUI* pCmdUI)
{	
	
	pCmdUI->Enable(!GetDocument()->m_bSimulate) ;			
}
