// mfctrdoc.cpp : implementation of the CMfctrackDoc class
//

#include "stdafx.h"
#include "mfcprop.h"

#include "mfctrdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctrackDoc

IMPLEMENT_DYNCREATE(CMfctrackDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfctrackDoc, CDocument)
	//{{AFX_MSG_MAP(CMfctrackDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctrackDoc construction/destruction

CMfctrackDoc::CMfctrackDoc()
{
	// TODO: add one-time construction code here

}

CMfctrackDoc::~CMfctrackDoc()
{
}

BOOL CMfctrackDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackDoc serialization

void CMfctrackDoc::Serialize(CArchive& ar)
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
// CMfctrackDoc diagnostics

#ifdef _DEBUG
void CMfctrackDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfctrackDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctrackDoc commands
