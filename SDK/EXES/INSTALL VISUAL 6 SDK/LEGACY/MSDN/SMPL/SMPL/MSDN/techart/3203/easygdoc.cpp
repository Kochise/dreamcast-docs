// easygdoc.cpp : implementation of the CEasyglDoc class
//

#include "stdafx.h"
#include "easygl.h"

#include "easygdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyglDoc

IMPLEMENT_DYNCREATE(CEasyglDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyglDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyglDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyglDoc construction/destruction

CEasyglDoc::CEasyglDoc()
{
	// TODO: add one-time construction code here

}

CEasyglDoc::~CEasyglDoc()
{
}

BOOL CEasyglDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyglDoc serialization

void CEasyglDoc::Serialize(CArchive& ar)
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
// CEasyglDoc diagnostics

#ifdef _DEBUG
void CEasyglDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyglDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyglDoc commands
