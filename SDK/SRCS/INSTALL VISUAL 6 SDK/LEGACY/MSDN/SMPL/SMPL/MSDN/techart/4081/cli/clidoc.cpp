// npsecdoc.cpp : implementation of the CSecCliDoc class
//

#include "stdafx.h"
#include "cliapp.h"

#include "clidoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecCliDoc

IMPLEMENT_DYNCREATE(CSecCliDoc, CDocument)

BEGIN_MESSAGE_MAP(CSecCliDoc, CDocument)
	//{{AFX_MSG_MAP(CSecCliDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecCliDoc construction/destruction

CSecCliDoc::CSecCliDoc()
{
}

CSecCliDoc::~CSecCliDoc()
{
}

BOOL CSecCliDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSecCliDoc serialization

void CSecCliDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSecCliDoc diagnostics

#ifdef _DEBUG
void CSecCliDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSecCliDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecCliDoc commands
