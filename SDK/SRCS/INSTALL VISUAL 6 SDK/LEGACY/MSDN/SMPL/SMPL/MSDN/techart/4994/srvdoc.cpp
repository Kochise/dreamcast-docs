// npscedoc.cpp : implementation of the CSecSrvDoc class
//

#include "stdafx.h"
#include "srvapp.h"

#include "srvdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecSrvDoc

IMPLEMENT_DYNCREATE(CSecSrvDoc, CDocument)

BEGIN_MESSAGE_MAP(CSecSrvDoc, CDocument)
	//{{AFX_MSG_MAP(CSecSrvDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecSrvDoc construction/destruction

CSecSrvDoc::CSecSrvDoc()
{
}

CSecSrvDoc::~CSecSrvDoc()
{
}

BOOL CSecSrvDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSecSrvDoc serialization

void CSecSrvDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSecSrvDoc diagnostics

#ifdef _DEBUG
void CSecSrvDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSecSrvDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecSrvDoc commands
