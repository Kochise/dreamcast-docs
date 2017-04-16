// threadlibtestDoc.cpp : implementation of the CThreadlibtestDoc class
//

#include "stdafx.h"
#include "threadlibtest.h"

#include "threadlibtestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestDoc

IMPLEMENT_DYNCREATE(CThreadlibtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CThreadlibtestDoc, CDocument)
	//{{AFX_MSG_MAP(CThreadlibtestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestDoc construction/destruction

CThreadlibtestDoc::CThreadlibtestDoc()
{
}

CThreadlibtestDoc::~CThreadlibtestDoc()
{
}

BOOL CThreadlibtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestDoc serialization

void CThreadlibtestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestDoc diagnostics

#ifdef _DEBUG
void CThreadlibtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThreadlibtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestDoc commands
