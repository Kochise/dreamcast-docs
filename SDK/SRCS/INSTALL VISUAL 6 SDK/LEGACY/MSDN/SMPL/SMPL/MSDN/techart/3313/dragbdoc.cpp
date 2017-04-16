// dragbdoc.cpp : implementation of the CDragbezDoc class
//

#include "stdafx.h"
#include "dragbez.h"

#include "dragbdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragbezDoc

IMPLEMENT_DYNCREATE(CDragbezDoc, CDocument)

BEGIN_MESSAGE_MAP(CDragbezDoc, CDocument)
	//{{AFX_MSG_MAP(CDragbezDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragbezDoc construction/destruction

CDragbezDoc::CDragbezDoc()
{
	// TODO: add one-time construction code here

}

CDragbezDoc::~CDragbezDoc()
{
}

BOOL CDragbezDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDragbezDoc serialization

void CDragbezDoc::Serialize(CArchive& ar)
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
// CDragbezDoc diagnostics

#ifdef _DEBUG
void CDragbezDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDragbezDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragbezDoc commands
