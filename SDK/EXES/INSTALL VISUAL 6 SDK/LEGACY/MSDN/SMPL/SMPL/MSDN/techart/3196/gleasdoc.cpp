// gleasdoc.cpp : implementation of the CGLEasyDoc class
//

#include "stdafx.h"
#include "gleasy.h"

#include "gleasdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLEasyDoc

IMPLEMENT_DYNCREATE(CGLEasyDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLEasyDoc, CDocument)
	//{{AFX_MSG_MAP(CGLEasyDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLEasyDoc construction/destruction

CGLEasyDoc::CGLEasyDoc()
{
	// TODO: add one-time construction code here

}

CGLEasyDoc::~CGLEasyDoc()
{
}

BOOL CGLEasyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGLEasyDoc serialization

void CGLEasyDoc::Serialize(CArchive& ar)
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
// CGLEasyDoc diagnostics

#ifdef _DEBUG
void CGLEasyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLEasyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLEasyDoc commands
