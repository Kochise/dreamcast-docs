// mygldoc.cpp : implementation of the CMyglDoc class
//

#include "stdafx.h"
#include "mygl.h"

#include "mygldoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyglDoc

IMPLEMENT_DYNCREATE(CMyglDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyglDoc, CDocument)
	//{{AFX_MSG_MAP(CMyglDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyglDoc construction/destruction

CMyglDoc::CMyglDoc()
{
	// TODO: add one-time construction code here
}

CMyglDoc::~CMyglDoc()
{
}

BOOL CMyglDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMyglDoc serialization

void CMyglDoc::Serialize(CArchive& ar)
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
// CMyglDoc diagnostics

#ifdef _DEBUG
void CMyglDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyglDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyglDoc commands
