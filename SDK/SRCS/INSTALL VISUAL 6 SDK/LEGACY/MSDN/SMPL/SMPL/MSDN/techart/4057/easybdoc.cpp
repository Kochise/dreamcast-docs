// EasyBdoc.cpp : implementation of the CEasyBitDoc class
//

#include "stdafx.h"
#include "EasyBit.h"

#include "EasyBdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyBitDoc

IMPLEMENT_DYNCREATE(CEasyBitDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyBitDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyBitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyBitDoc construction/destruction

CEasyBitDoc::CEasyBitDoc()
{
}

CEasyBitDoc::~CEasyBitDoc()
{
}

BOOL CEasyBitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyBitDoc serialization

void CEasyBitDoc::Serialize(CArchive& ar)
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
// CEasyBitDoc diagnostics

#ifdef _DEBUG
void CEasyBitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyBitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyBitDoc commands
