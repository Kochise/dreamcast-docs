// EasyTdoc.cpp : implementation of the CEasyTexDoc class
//

#include "stdafx.h"
#include "EasyTex.h"

#include "EasyTdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyTexDoc

IMPLEMENT_DYNCREATE(CEasyTexDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyTexDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyTexDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyTexDoc construction/destruction

CEasyTexDoc::CEasyTexDoc()
{
	// TODO: add one-time construction code here

}

CEasyTexDoc::~CEasyTexDoc()
{
}

BOOL CEasyTexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyTexDoc serialization

void CEasyTexDoc::Serialize(CArchive& ar)
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
// CEasyTexDoc diagnostics

#ifdef _DEBUG
void CEasyTexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyTexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyTexDoc commands
