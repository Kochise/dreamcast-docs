// ModelviewDoc.cpp : implementation of the CModelviewDoc class
//

#include "stdafx.h"
#include "Modelview.h"

#include "ModelviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelviewDoc

IMPLEMENT_DYNCREATE(CModelviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CModelviewDoc, CDocument)
	//{{AFX_MSG_MAP(CModelviewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelviewDoc construction/destruction

CModelviewDoc::CModelviewDoc()
{
	// TODO: add one-time construction code here

}

CModelviewDoc::~CModelviewDoc()
{
}

BOOL CModelviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CModelviewDoc serialization

void CModelviewDoc::Serialize(CArchive& ar)
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
// CModelviewDoc diagnostics

#ifdef _DEBUG
void CModelviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModelviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelviewDoc commands
