// fwtesdoc.cpp : implementation of the CFwtestDoc class
//

#include "stdafx.h"
#include "fwtest.h"

#include "fwtesdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFwtestDoc

IMPLEMENT_DYNCREATE(CFwtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CFwtestDoc, CDocument)
	//{{AFX_MSG_MAP(CFwtestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFwtestDoc construction/destruction

CFwtestDoc::CFwtestDoc()
{
	// TODO: add one-time construction code here
}

CFwtestDoc::~CFwtestDoc()
{
}

BOOL CFwtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFwtestDoc serialization

void CFwtestDoc::Serialize(CArchive& ar)
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
// CFwtestDoc diagnostics

#ifdef _DEBUG
void CFwtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFwtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFwtestDoc commands
