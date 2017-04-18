// ctlredoc.cpp : implementation of the CCtlregDoc class
//

#include "stdafx.h"
#include "ctlreg.h"

#include "ctlredoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtlregDoc

IMPLEMENT_DYNCREATE(CCtlregDoc, CDocument)

BEGIN_MESSAGE_MAP(CCtlregDoc, CDocument)
	//{{AFX_MSG_MAP(CCtlregDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtlregDoc construction/destruction

CCtlregDoc::CCtlregDoc()
{
}

CCtlregDoc::~CCtlregDoc()
{
}

BOOL CCtlregDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCtlregDoc serialization

void CCtlregDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCtlregDoc diagnostics

#ifdef _DEBUG
void CCtlregDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCtlregDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCtlregDoc commands
