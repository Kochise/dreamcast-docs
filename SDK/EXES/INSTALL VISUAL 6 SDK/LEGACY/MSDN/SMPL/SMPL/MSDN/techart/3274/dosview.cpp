// dosview.cpp : implementation file
//

#include "stdafx.h"

#include "headers.h"


#include "viewfile.h"
#include "fileview.h"
#include "dosview.h"

#include "viewfdoc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDOSView

IMPLEMENT_DYNCREATE(CDOSView, CFileView)

CDOSView::CDOSView()
{
}

CDOSView::~CDOSView()
{
}


BEGIN_MESSAGE_MAP(CDOSView, CFileView)
	//{{AFX_MSG_MAP(CDOSView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDOSView drawing

void CDOSView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDOSView diagnostics

#ifdef _DEBUG
void CDOSView::AssertValid() const
{
	CView::AssertValid();
}

void CDOSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDOSView message handlers

void CDOSView::OnInitialUpdate() 
{
  CFileView::OnInitialUpdate();
  GetParentFrame()->SetWindowText("DOS file header: "+GetDocument()->GetPathName());
}

void CDOSView::DispatchDoubleClick(int iVal)
{
};

BOOL CDOSView::IsMyKindOfFile(BYTE *lpImage)
{ 
 return (*(USHORT *)lpImage == IMAGE_DOS_SIGNATURE);
};

