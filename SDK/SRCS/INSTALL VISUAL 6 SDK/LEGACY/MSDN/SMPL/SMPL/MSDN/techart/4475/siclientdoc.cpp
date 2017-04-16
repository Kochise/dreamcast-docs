// SIClientDoc.cpp : implementation of the CClientDoc class
//

#include "stdafx.h"
#include "SIClient.h"

#include "SIClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDoc

IMPLEMENT_DYNCREATE(CClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CClientDoc, CDocument)
	//{{AFX_MSG_MAP(CClientDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CClientDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

static const IID IID_IClient =
{ 0xbb4559f2, 0xfe63, 0x11ce, { 0x9b, 0x3f, 0x0, 0xaa, 0x0, 0x3b, 0x6, 0xf4 } };

BEGIN_INTERFACE_MAP(CClientDoc, CDocument)
	INTERFACE_PART(CClientDoc, IID_IClient, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDoc construction/destruction

CClientDoc::CClientDoc()
{
	EnableAutomation();

	AfxOleLockApp();
}

CClientDoc::~CClientDoc()
{
	AfxOleUnlockApp();
}

BOOL CClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CClientDoc serialization

void CClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CClientDoc diagnostics

#ifdef _DEBUG
void CClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientDoc commands
