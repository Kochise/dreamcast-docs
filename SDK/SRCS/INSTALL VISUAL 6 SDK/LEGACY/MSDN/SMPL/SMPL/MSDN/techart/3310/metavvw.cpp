// metavvw.cpp : implementation of the CMetavw1View class
//

#include "stdafx.h"
#include "metavw1.h"

#include "metavdoc.h"
#include "metavvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetavw1View

IMPLEMENT_DYNCREATE(CMetavw1View, CView)

BEGIN_MESSAGE_MAP(CMetavw1View, CView)
	//{{AFX_MSG_MAP(CMetavw1View)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetavw1View construction/destruction

CMetavw1View::CMetavw1View()
{
  m_fDraw = TRUE;
  m_uiTimer = 0;
  m_fFullDragOn = FullDragOn();
}

CMetavw1View::~CMetavw1View()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMetavw1View drawing

void CMetavw1View::OnDraw(CDC* pDC)
{
   CMetavw1Doc* pDoc = GetDocument();

   //flag to prevent drawing in response to full-drag sizing
   //see OnSize() and FullDragOn() in this module
   if (m_fDraw) 
   {
     //if either printing or print previewing the rect is
     //provided by CPrintInfo in OnPreparePrinting 
     if (pDC->IsPrinting()) 
     {
	     pDoc->m_cemf.Draw(pDC, &m_rectDraw);
	 }
	 else 
	 {
	    GetClientRect(&m_rectDraw);
   	    pDoc->m_cemf.Draw(pDC, &m_rectDraw);
	 }
   }
}
												
/////////////////////////////////////////////////////////////////////////////
// CMetavw1View printing

void CMetavw1View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
  m_rectDraw = pInfo->m_rectDraw;
  OnDraw(pDC);		
}

BOOL CMetavw1View::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
	DoPreparePrinting(pInfo);
	//set number of pages shown in preview. This must be done
	//after calling DoPreparePrinting
	pInfo->m_nNumPreviewPages = 1;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMetavw1View diagnostics

#ifdef _DEBUG
void CMetavw1View::AssertValid() const
{
	CView::AssertValid();
}

void CMetavw1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMetavw1Doc* CMetavw1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMetavw1Doc)));
	return (CMetavw1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OnTimer
//
// will only get called if timer was set in response
// to sizing window if fulldrag option was enabled
// by the user via the control panel
void CMetavw1View::OnTimer(UINT nIDEvent) 
{
	m_fDraw = TRUE;	
	m_uiTimer = 0;
	KillTimer(1);
	InvalidateRect(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// OnSize
//
// if the fulldrag option has been enabled by the user, a one shot timer
// is set. This timer is used to delay the rendering of metafiles in response
// to wm_paint messages sent during sizing. ie: the wm_timer message will sit
// in the message que until sizing is done. The flag m_fDraw is set here and
// blocks rendering in the OnPaint function.
void CMetavw1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	//only do this if fulldrag is enabled
	if (m_fFullDragOn)
	{
	  if (!m_uiTimer)
  	    KillTimer(1);
	  m_uiTimer = SetTimer(1, 100, NULL);
	  m_fDraw = FALSE;	
	}
}

/////////////////////////////////////////////////////////////////////////////
// FullDragOn
//
// reads the registry to determine if the user selected the full-drag option
// in the control panel, desktop applet.
BOOL CMetavw1View::FullDragOn()
{
  HKEY hkey = NULL;
  DWORD dwType;
  long lResult;
  LPSTR lpszDataBuf;
  DWORD cbData = 0;

  lResult = RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0,
                              KEY_READ, &hkey);
  if (hkey)	
  {
    //obtain size of key
    lResult = RegQueryValueEx(hkey, "DragFullWindows", NULL, &dwType, NULL, &cbData);
	//alloc sufficient memory for key value
	lpszDataBuf = (LPSTR)malloc(cbData * sizeof(char));
	//get the key value
    lResult = RegQueryValueEx(hkey, "DragFullWindows", NULL, &dwType, (LPBYTE)lpszDataBuf, &cbData);
	return (*lpszDataBuf == '1');
  }
  return FALSE;
} 

/////////////////////////////////////////////////////////////////////////////
// OnEditCopy
//
void CMetavw1View::OnEditCopy() 
{
    CMetavw1Doc* pDoc = GetDocument();
	HENHMETAFILE hemf = pDoc->m_cemf.GetEMFHandle();
	HENHMETAFILE hemfcopy;
	
	if (!OpenClipboard()) return;
	if (!::EmptyClipboard()) return;
	
	UINT uiEnhSize = ::GetEnhMetaFileBits(hemf, 0, NULL);
	LPBYTE lpEMF = (LPBYTE)malloc(uiEnhSize);

	if (lpEMF && GetEnhMetaFileBits(hemf, uiEnhSize, lpEMF)) {
	  hemfcopy = SetEnhMetaFileBits(uiEnhSize, lpEMF);
  	  SetClipboardData(CF_ENHMETAFILE, hemfcopy);
	}
	CloseClipboard();

	if (lpEMF)
	  free(lpEMF);
}
	                          
/*    OLD IMPLEMENTATION OF ONDRAW. KEEP IT FOR PURPOSES OF WRITING ARTICLE
   CMetavw1Doc* pDoc = GetDocument();
   //this rect structure is static because in print preview
   //you want to grab clipping rectangle the first time it
   //is drawn on the screen. Making it static enables this
   //as you will see below
 //  static RECT rect = {0,0,0,0};
 //  RECT ScreenRect;

   //flag to prevent drawing in response to full-drag sizing
   //see OnSize() and FullDragOn() in this module
   if (m_fDraw)
   {
     if (pDC->m_bPrinting) {
	     pDoc->m_cemf.Draw(pDC, &m_rectDraw);
	 }
	 else {
	    GetClientRect(&m_rectDraw);
   	    pDoc->m_cemf.Draw(pDC, &m_rectDraw);
	 }
	  if (pDC->m_bPrinting)
	  {
  	     if (!m_bInPreview)
		 {
		   //printing to printer. Get the correct printable area
           pDC->GetClipBox(&rect);
		 }
		 else
		 {
		   //remember, rect is static, so...we can further initialize it
		   //here. If the bottom component is still equal to 0 then go
		   //ahead and grab the clip rect. Continue to use this as the
		   //user is zooming on the print preview. The CPreviewDC class
		   //will take care of scaling the rect.
		   if (rect.bottom == 0)
		     pDC->GetClipBox(&rect);
		 }
	     pDoc->m_cemf.Draw(pDC, &rect);
	  }
	  else
	  {
	    //reset rect to 0 for the next time the user is print previewing
        memset(&rect, 0, sizeof(RECT));
	    GetClientRect(&ScreenRect);
   	    pDoc->m_cemf.Draw(pDC, &ScreenRect);
	  }
   }
}
												
*/


