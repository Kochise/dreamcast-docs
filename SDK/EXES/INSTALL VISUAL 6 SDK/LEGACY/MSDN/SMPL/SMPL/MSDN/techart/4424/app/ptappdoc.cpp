// ptappdoc.cpp : implementation of the CPtappDoc class
//

#include "stdafx.h"
#include "ptapp.h"

#include "ptappdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtappDoc

IMPLEMENT_DYNCREATE(CPtappDoc, CDocument)

BEGIN_MESSAGE_MAP(CPtappDoc, CDocument)
	//{{AFX_MSG_MAP(CPtappDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtappDoc construction/destruction

CPtappDoc::CPtappDoc()
{
}

CPtappDoc::~CPtappDoc()
{
}

BOOL CPtappDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPtappDoc serialization

void CPtappDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPtappDoc diagnostics

#ifdef _DEBUG
void CPtappDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPtappDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPtappDoc commands
