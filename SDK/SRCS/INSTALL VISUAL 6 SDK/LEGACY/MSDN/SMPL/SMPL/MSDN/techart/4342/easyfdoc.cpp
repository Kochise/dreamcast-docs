// EasyFdoc.cpp : implementation of the CEasyFontDoc class
//

#include "stdafx.h"
#include "EasyFont.h"

#include "EasyFdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyFontDoc

IMPLEMENT_DYNCREATE(CEasyFontDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyFontDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyFontDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyFontDoc construction/destruction

CEasyFontDoc::CEasyFontDoc()
{
	// TODO: add one-time construction code here

}

CEasyFontDoc::~CEasyFontDoc()
{
}

BOOL CEasyFontDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEasyFontDoc serialization

void CEasyFontDoc::Serialize(CArchive& ar)
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
// CEasyFontDoc diagnostics

#ifdef _DEBUG
void CEasyFontDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyFontDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyFontDoc commands
