// glpaldoc.cpp : implementation of the CGLpalDoc class
//

#include "stdafx.h"
#include "glpal.h"

#include "glpaldoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLpalDoc

IMPLEMENT_DYNCREATE(CGLpalDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLpalDoc, CDocument)
	//{{AFX_MSG_MAP(CGLpalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLpalDoc construction/destruction

CGLpalDoc::CGLpalDoc()
{
	// TODO: add one-time construction code here

}

CGLpalDoc::~CGLpalDoc()
{
}

BOOL CGLpalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGLpalDoc serialization

void CGLpalDoc::Serialize(CArchive& ar)
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
// CGLpalDoc diagnostics

#ifdef _DEBUG
void CGLpalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLpalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLpalDoc commands
