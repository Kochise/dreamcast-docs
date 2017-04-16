// metavdoc.cpp : implementation of the CMetavw1Doc class
//

#include "stdafx.h"
#include "metavw1.h"
//#include "cemf.h"

#include "metavdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetavw1Doc

IMPLEMENT_DYNCREATE(CMetavw1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMetavw1Doc, CDocument)
	//{{AFX_MSG_MAP(CMetavw1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetavw1Doc construction/destruction

CMetavw1Doc::CMetavw1Doc()
{
}

CMetavw1Doc::~CMetavw1Doc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMetavw1Doc serialization

void CMetavw1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	  m_cemf.Load(m_szPathName);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMetavw1Doc diagnostics

#ifdef _DEBUG
void CMetavw1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMetavw1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMetavw1Doc commands

BOOL CMetavw1Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	m_szPathName = lpszPathName;

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return TRUE;
}
