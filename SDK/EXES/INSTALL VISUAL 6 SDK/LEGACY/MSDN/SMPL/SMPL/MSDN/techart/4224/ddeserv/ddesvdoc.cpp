// DDESvdoc.cpp : implementation of the CDDEServDoc class
//

#include "stdafx.h"
#include "DDEServ.h"

#include "DDESvdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDEServDoc

IMPLEMENT_DYNCREATE(CDDEServDoc, CDocument)

BEGIN_MESSAGE_MAP(CDDEServDoc, CDocument)
	//{{AFX_MSG_MAP(CDDEServDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDEServDoc construction/destruction

CDDEServDoc::CDDEServDoc()
{
	// TODO: add one-time construction code here

}

CDDEServDoc::~CDDEServDoc()
{
}

BOOL CDDEServDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDDEServDoc serialization

void CDDEServDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDDEServDoc diagnostics

#ifdef _DEBUG
void CDDEServDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDDEServDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDDEServDoc commands
