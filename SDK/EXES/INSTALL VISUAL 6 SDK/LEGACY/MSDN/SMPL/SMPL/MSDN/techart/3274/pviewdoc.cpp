// pviewdoc.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "fileview.h"

#include "pviewdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPViewDoc

IMPLEMENT_DYNCREATE(CPViewDoc, CDocument)

CPViewDoc::CPViewDoc()
{
}

BOOL CPViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
     SetPathName("Process List",FALSE);
	 strcpy(szStatusMessage,"displays the list of currently active processes");

	return TRUE;
}

CPViewDoc::~CPViewDoc()
{
}


BEGIN_MESSAGE_MAP(CPViewDoc, CDocument)
	//{{AFX_MSG_MAP(CPViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CPViewDoc diagnostics

#ifdef _DEBUG
void CPViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPViewDoc serialization

void CPViewDoc::Serialize(CArchive& ar)
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

void CPViewDoc::RefreshProcessList()
{
 UpdateAllViews(NULL);  // this is cheating, but we only have one view here...
};

/////////////////////////////////////////////////////////////////////////////
// CPViewDoc commands



 
