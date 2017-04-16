// leview.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
#include "fileview.h"
#include "leview.h"

#include "headers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLEView

IMPLEMENT_DYNCREATE(CLEView, CFileView)

CLEView::CLEView()
{
}

CLEView::~CLEView()
{
}


BEGIN_MESSAGE_MAP(CLEView, CFileView)
	//{{AFX_MSG_MAP(CLEView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLEView drawing

void CLEView::OnDraw(CDC* pDC)
{
 CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLEView diagnostics

#ifdef _DEBUG
void CLEView::AssertValid() const
{
 CView::AssertValid();
}

void CLEView::Dump(CDumpContext& dc) const
{
 CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLEView message handlers

void CLEView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
  CFileView::OnInitialUpdate();
  GetParentFrame()->SetWindowText("LE file header: "+GetDocument()->GetPathName());

}

void CLEView::DispatchDoubleClick(int iVal)
{
};

BOOL CLEView::IsMyKindOfFile(BYTE *lpImage)
{        
 return (*(USHORT *)lpImage == IMAGE_DOS_SIGNATURE) &&
        (LOWORD (*(DWORD *)NTSIGNATURE (lpImage)) == IMAGE_OS2_SIGNATURE_LE);
};
