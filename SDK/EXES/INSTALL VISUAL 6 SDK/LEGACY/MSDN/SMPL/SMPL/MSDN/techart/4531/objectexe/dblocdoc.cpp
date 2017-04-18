// DBLocdoc.cpp : implementation of the CDBLocalDoc class
//

#include "stdafx.h"
#include "DBLocal.h"

#include "DBLocdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBLocalDoc

IMPLEMENT_DYNCREATE(CDBLocalDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBLocalDoc, CDocument)
	//{{AFX_MSG_MAP(CDBLocalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBLocalDoc construction/destruction

CDBLocalDoc::CDBLocalDoc()
{
	// TODO: add one-time construction code here
	((CDBLocalApp*) AfxGetApp())->m_pLastDoc=this;
}

CDBLocalDoc::~CDBLocalDoc()
{
}

BOOL CDBLocalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDBLocalDoc serialization

void CDBLocalDoc::Serialize(CArchive& ar)
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
// CDBLocalDoc diagnostics

#ifdef _DEBUG
void CDBLocalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBLocalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBLocalDoc commands
