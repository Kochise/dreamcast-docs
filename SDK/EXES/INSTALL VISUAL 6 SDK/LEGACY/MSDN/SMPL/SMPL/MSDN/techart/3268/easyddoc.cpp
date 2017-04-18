// EasyDdoc.cpp : implementation of the CEasyDIBDoc class
//

#include "stdafx.h"
#include "EasyDIB.h"

#include "EasyDdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyDIBDoc

IMPLEMENT_DYNCREATE(CEasyDIBDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyDIBDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyDIBDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyDIBDoc construction/destruction

CEasyDIBDoc::CEasyDIBDoc()
{
	// TODO: add one-time construction code here

}

CEasyDIBDoc::~CEasyDIBDoc()
{
}

BOOL CEasyDIBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyDIBDoc serialization

void CEasyDIBDoc::Serialize(CArchive& ar)
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
// CEasyDIBDoc diagnostics

#ifdef _DEBUG
void CEasyDIBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyDIBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyDIBDoc commands
