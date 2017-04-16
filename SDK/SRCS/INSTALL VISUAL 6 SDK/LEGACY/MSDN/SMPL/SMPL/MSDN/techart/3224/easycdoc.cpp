// EasyCdoc.cpp : implementation of the CEasyCIDoc class
//

#include "stdafx.h"
#include "EasyCI.h"

#include "EasyCdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyCIDoc

IMPLEMENT_DYNCREATE(CEasyCIDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyCIDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyCIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyCIDoc construction/destruction

CEasyCIDoc::CEasyCIDoc()
{
	// TODO: add one-time construction code here

}

CEasyCIDoc::~CEasyCIDoc()
{
}

BOOL CEasyCIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyCIDoc serialization

void CEasyCIDoc::Serialize(CArchive& ar)
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
// CEasyCIDoc diagnostics

#ifdef _DEBUG
void CEasyCIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyCIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyCIDoc commands
