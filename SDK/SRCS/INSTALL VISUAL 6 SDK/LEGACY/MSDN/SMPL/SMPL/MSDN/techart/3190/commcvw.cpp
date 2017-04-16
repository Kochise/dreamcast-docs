// commcvw.cpp : implementation of the CReaderView class
//

#include "stdafx.h"
#include "protocol.h"
#include "commchat.h"

#include "comclass.h"


#include "commcdoc.h"
#include "commcvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReaderView

IMPLEMENT_DYNCREATE(CReaderView, CEditView)

BEGIN_MESSAGE_MAP(CReaderView, CEditView)
	//{{AFX_MSG_MAP(CReaderView)
    ON_MESSAGE(ID_NUKEDOC,OnNukeDoc)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderView construction/destruction

CReaderView::CReaderView()
{
	// TODO: add construction code here
}

CReaderView::~CReaderView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CReaderView drawing

void CReaderView::OnDraw(CDC* pDC)
{
	CCommchatDoc* pDoc = GetDocument();

	// TODO: add draw code here
}



/////////////////////////////////////////////////////////////////////////////
// CReaderView diagnostics

#ifdef _DEBUG
void CReaderView::AssertValid() const
{
	CView::AssertValid();
}

void CReaderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommchatDoc* CReaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommchatDoc)));
	return (CCommchatDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReaderView message handlers


/////////////////////////////////////////////////////////////////////////////
// CWriterView

IMPLEMENT_DYNCREATE(CWriterView, CEditView)

BEGIN_MESSAGE_MAP(CWriterView, CEditView)
	//{{AFX_MSG_MAP(CWriterView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriterView construction/destruction

CWriterView::CWriterView()
{
	// TODO: add construction code here
}

CWriterView::~CWriterView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWriterView drawing

void CWriterView::OnDraw(CDC* pDC)
{
	CCommchatDoc* pDoc = GetDocument();

	// TODO: add draw code here
}

void CWriterView::ReactToChanges()
{
 CString csReceiver;
 int iTextLength = GetEditCtrl().GetWindowTextLength();
 GetEditCtrl().GetWindowText(csReceiver);
 TRY
 {
 GetDocument()->cpProtocol->Write(csReceiver,iTextLength);
 }
 CATCH (CFileException, theException)
 { // ignore
 char szBuf[30];
	    wsprintf(szBuf,"Cause of I/O failure: %d", theException->m_cause);
		AfxMessageBox(szBuf);

 }
 END_CATCH
//MessageBeep(-1);
}



/////////////////////////////////////////////////////////////////////////////
// CWriterView diagnostics

#ifdef _DEBUG
void CWriterView::AssertValid() const
{
	CView::AssertValid();
}

void CWriterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommchatDoc* CWriterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommchatDoc)));
	return (CCommchatDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWriterView message handlers



long WINAPI ReceiveThreadFn(CReaderView *cvTarget)
{ BOOL bThreadAlive = TRUE;
  UINT iResult;

  _try
  {
 while (bThreadAlive) 
  {
    iResult = cvTarget->GetDocument()->cpProtocol->Read(cvTarget->m_lpReceiveBuffer,1000);
	if (iResult == 0)
	 {bThreadAlive = FALSE;
	  continue;
	 };
      cvTarget->GetEditCtrl().SetWindowText(cvTarget->m_lpReceiveBuffer);
	  cvTarget->GetEditCtrl().Invalidate(TRUE);
  };
  }
  _except	(EXCEPTION_EXECUTE_HANDLER)
  {
    iResult = GetExceptionCode();
//char szBuf[30];
//	    wsprintf(szBuf,"Cause of I/O failure: %d", GetExceptionCode());
//		AfxMessageBox(szBuf);

  }

		 ::PostMessage(cvTarget->m_hWnd,ID_NUKEDOC,iResult,NULL);

  return(0);
};


int CReaderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{		if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
// allow for a graceful way to recover if fails here...
    m_hReceiveEditMemory = LocalAlloc(LHND,1000);  // don't hardcode...
	m_lpReceiveBuffer = (char *)LocalLock(m_hReceiveEditMemory);
	m_iMemPointer = 0;

	
	return 0;
}

void CReaderView::StartRunning()
{  unsigned long iThread;
	m_hReceiveThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReceiveThreadFn,(void *)this,0,&iThread);

}


void CReaderView::OnDestroy()
{
	CEditView::OnDestroy();
// RAc -- change that to have the read thread timeout if necessary...
//    TerminateThread(m_hReceiveThread,0);
	WaitForSingleObject(m_hReceiveThread,INFINITE);
	CloseHandle(m_hReceiveThread);
	LocalUnlock(m_hReceiveEditMemory);
	LocalFree(m_hReceiveEditMemory);
	// TODO: Add your message handler code here
	}

long CReaderView::OnNukeDoc(UINT wParam, LONG lParam)
{ //MessageBeep(-1);
  if (!wParam)
  MessageBox("The communication has been interrupted!");
  else
  { LPVOID lpMessageBuffer;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,
	wParam, MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),(LPTSTR)&lpMessageBuffer,0,NULL);
	MessageBox((const char *)lpMessageBuffer,"Communication failed with the following system error:");
	HLOCAL hMem = LocalHandle(lpMessageBuffer);
	LocalUnlock(lpMessageBuffer);
	LocalFree(lpMessageBuffer);
  };

  GetDocument()->OnFileClose();
  return (0);
}

