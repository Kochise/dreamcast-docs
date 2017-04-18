// clipdoc.cpp : implementation of the CClipDoc class
//

#include "stdafx.h"
#include "mfcclip.h"
#include "myobj.h"
#include "myoblist.h"
#include "clipdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipDoc

IMPLEMENT_DYNCREATE(CClipDoc, CDocument)

BEGIN_MESSAGE_MAP(CClipDoc, CDocument)
    //{{AFX_MSG_MAP(CClipDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipDoc construction/destruction

CClipDoc::CClipDoc()
{
    // TODO: add one-time construction code here
}

CClipDoc::~CClipDoc()
{
    m_MyObList.DeleteAll();
}

BOOL CClipDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_MyObList.DeleteAll();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CClipDoc serialization

void CClipDoc::Serialize(CArchive& ar)
{
    m_MyObList.Serialize(ar);
}


/////////////////////////////////////////////////////////////////////////////
// CClipDoc diagnostics

#ifdef _DEBUG
void CClipDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CClipDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipDoc commands
