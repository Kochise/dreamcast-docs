// dldetvw.cpp : implementation of the CMatrixView class
//

#include "stdafx.h"
#include "dldetect.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixView

IMPLEMENT_DYNCREATE(CMatrixView, CView)

BEGIN_MESSAGE_MAP(CMatrixView, CView)
	//{{AFX_MSG_MAP(CMatrixView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_NET_FINDNETINVARIANTS, OnNetFindnetinvariants)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixView construction/destruction

CMatrixView::CMatrixView()
{
	// TODO: add construction code here
}

CMatrixView::~CMatrixView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView drawing

void CMatrixView::OnDraw(CDC* pDC)
{
	CPetriNetDoc* pDoc = GetDocument();

	// TODO: add draw code here
}



/////////////////////////////////////////////////////////////////////////////
// CMatrixView diagnostics

#ifdef _DEBUG
void CMatrixView::AssertValid() const
{
	CView::AssertValid();
}

void CMatrixView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPetriNetDoc* CMatrixView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPetriNetDoc)));
	return (CPetriNetDoc *) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatrixView message handlers

int CMatrixView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_hMemory=NULL;
	CRect rectClient;
	GetClientRect(&rectClient);
	GetClientRect(&rectClient);
	rectClient.InflateRect(1,1);

	VERIFY(m_EditCtrl.Create(WS_CHILD | WS_VISIBLE| WS_BORDER | WS_VSCROLL|
	       WS_HSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | DS_LOCALEDIT,
		   rectClient, this, 1));

	CFont aFont;
	aFont.CreateStockObject(SYSTEM_FIXED_FONT);
	m_EditCtrl.SetFont(&aFont,FALSE);
	m_EditCtrl.ShowWindow(SW_SHOWNORMAL);
	GetDocument()->cmvAttachedView=this;
	return (0);
}
	
	// TODO: Add your specialized creation code here
	


void CMatrixView::OnDestroy()
{
    m_EditCtrl.DestroyWindow();
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CMatrixView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_EditCtrl.MoveWindow(-1,-1,cx+1,cy+1);
	
	// TODO: Add your message handler code here
	
}

// this code must be beautified...

#define DumpToArchive(archive,string) archive.Write(string,strlen(string))

void CMatrixView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
CPetriNetDoc* pDoc=GetDocument();
matrix *hisMatrix=pDoc->m_mCurrentMatrix;
int iRow,iColumn;
int iPosition=0;
char WhiteSpace[]=" ";
char LineFeed[]="\r\n";
char chToken[10];
if (hisMatrix==NULL) return;
CMemFile cmfBuffer;
CArchive ca(&cmfBuffer,CArchive::store);
memset(chToken,'\0',10);
DumpToArchive(ca,"        ");
for (iColumn=0;iColumn<hisMatrix->iColumns;iColumn++)
{ sprintf(chToken,"%.5s ",GetDocument()->GrabNameFromNet(FALSE,iColumn));
  DumpToArchive(ca,chToken);
};
  DumpToArchive(ca,LineFeed);

for (iRow=0;iRow<hisMatrix->iRows;iRow++)
 {sprintf(chToken,"%.5s ",GetDocument()->GrabNameFromNet(TRUE,iRow));
  DumpToArchive(ca,chToken);
  for (iColumn=0;iColumn<hisMatrix->iColumns;iColumn++)
   {sprintf(chToken,"%5d",hisMatrix->GetElement(iRow,iColumn));
	DumpToArchive(ca,chToken);
	DumpToArchive(ca,WhiteSpace);

   };
 	DumpToArchive(ca,LineFeed);
 };
// since the C runtime routines treat \0 as an end-of-string, trying to
// dump '\0' into the archive gives us all kinds of trouble; but we need
// to terminate the edit box's text with 0 so that it is displayed 
// correctly...I bail out the weird way here by allocating to innocent space bytes at
// the end end replacing them with 0s afterwards. This is bound to get me a
// hack-of-the-week award!!!
DumpToArchive(ca,"  ");
ca.Close();
if (m_hMemory!=NULL) free(m_hMemory);
m_hMemory=malloc(cmfBuffer.GetLength());
if (!m_hMemory) return;
cmfBuffer.SeekToBegin();
CArchive ca1(&cmfBuffer,CArchive::load);

ca1.Read((char *)m_hMemory,cmfBuffer.GetLength());
((char *)m_hMemory)[cmfBuffer.GetLength()-sizeof(char)]='\0';

m_EditCtrl.SetWindowText((char *)m_hMemory);
m_EditCtrl.Invalidate(TRUE);


}



void CMatrixView::OnNetFindnetinvariants()
{  CInvariantDoc *cpnNewDoc;
   matrix *mtTemp=GetDocument()->m_mCurrentMatrix->Copy();
   if (mtTemp == (matrix *)0)
    {AfxMessageBox("Problem copying the matrix...");
	 return;
	};
	matrix *mtTemp1=mtTemp->FindNullSpace();
	delete (mtTemp);
   if (mtTemp1 == (matrix *)0)
    {AfxMessageBox("Could not determine null space of matrix...");
	 return;
	};

	cpnNewDoc = (CInvariantDoc *)theApp.m_pInvTemplate->OpenDocumentFile(NULL);
	cpnNewDoc->SetTitle("Net invariants for "+GetDocument()->GetTitle());
    cpnNewDoc->m_mCurrentMatrix=mtTemp1;
	cpnNewDoc->cnvAttachedView=GetDocument()->cnvAttachedView;
	cpnNewDoc->cmvAttachedView->OnUpdate(NULL,0,NULL);
}

void CMatrixView::OnActivateView(BOOL bActivated, CView* pA,CView *pD)
{
GetDocument()->ReflectChanges();
CView::OnActivateView(bActivated, pA, pD);
} 
