// TemMedoc.cpp : implementation of the CTemMemPtrDoc class
//

#include "stdafx.h"
#include "TemMemPtr.h"

#include "TemMedoc.h"

#include "TheDialog.h"
#include "TemplateDialog.h"

//#include "Solution2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrDoc

IMPLEMENT_DYNCREATE(CTemMemPtrDoc, CDocument)

BEGIN_MESSAGE_MAP(CTemMemPtrDoc, CDocument)
	//{{AFX_MSG_MAP(CTemMemPtrDoc)
	ON_COMMAND(ID_CALLIT_FROMDOC, OnCallitFromdoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrDoc construction/destruction

CTemMemPtrDoc::CTemMemPtrDoc()
{
	// TODO: add one-time construction code here

}

CTemMemPtrDoc::~CTemMemPtrDoc()
{
}

BOOL CTemMemPtrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrDoc serialization

void CTemMemPtrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrDoc diagnostics

#ifdef _DEBUG
void CTemMemPtrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTemMemPtrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTemMemPtrDoc commands

void CTemMemPtrDoc::OnCallitFromdoc() 
{
   CTemplateDialog<CTemMemPtrDoc> aDlg ;
   aDlg.SetObjectPtr(this) ;
   aDlg.SetMemFunctPtr(&CTemMemPtrDoc::CalledByDialog) ;
	aDlg.DoModal() ;
		
}


CString& CTemMemPtrDoc::CalledByDialog()
{
   return CString("Hello from the Doc class.") ;
}


