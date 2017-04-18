// 16bitdoc.cpp : implementation of the C16bitDoc class
//

#include "stdafx.h"
#include "16bit.h"

#include "16bitdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C16bitDoc

IMPLEMENT_DYNCREATE(C16bitDoc, CDocument)

BEGIN_MESSAGE_MAP(C16bitDoc, CDocument)
	//{{AFX_MSG_MAP(C16bitDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C16bitDoc construction/destruction

C16bitDoc::C16bitDoc()
{
}

C16bitDoc::~C16bitDoc()
{
}

BOOL C16bitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// C16bitDoc serialization

void C16bitDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// C16bitDoc diagnostics

#ifdef _DEBUG
void C16bitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C16bitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C16bitDoc commands
