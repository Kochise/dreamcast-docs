// VCDradoc.cpp : implementation of the CVCDrawDoc class
//

#include "stdafx.h"
#include "VCDraw.h"

#include "VCDradoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVCDrawDoc

IMPLEMENT_DYNCREATE(CVCDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CVCDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CVCDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVCDrawDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CVCDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDrawDoc construction/destruction

CVCDrawDoc::CVCDrawDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CVCDrawDoc::~CVCDrawDoc()
{
	AfxOleUnlockApp();
}

BOOL CVCDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVCDrawDoc serialization

void CVCDrawDoc::Serialize(CArchive& ar)
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
// CVCDrawDoc diagnostics

#ifdef _DEBUG
void CVCDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVCDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVCDrawDoc commands
