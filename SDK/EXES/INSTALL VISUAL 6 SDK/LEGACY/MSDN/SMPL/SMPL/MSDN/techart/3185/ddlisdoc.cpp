// ddlisdoc.cpp : implementation of the CDdlistDoc class
//

#include "stdafx.h"
#include "ddlist.h"
#include "strlist.h"
#include "ddlisdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDdlistDoc

IMPLEMENT_DYNCREATE(CDdlistDoc, CDocument)

BEGIN_MESSAGE_MAP(CDdlistDoc, CDocument)
    //{{AFX_MSG_MAP(CDdlistDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDdlistDoc construction/destruction

CDdlistDoc::CDdlistDoc()
{
    // TODO: add one-time construction code here
}

CDdlistDoc::~CDdlistDoc()
{
    m_StrList.DeleteAll();
}

BOOL CDdlistDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // Put some random strings in the doc
    m_StrList.DeleteAll();
    for (int i = 0; i < rand() % 20; i++) {
        char buf[64];
        sprintf(buf, "String #%d", rand());
        CString* pStr = new CString(buf);
        m_StrList.AddTail(pStr);
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDdlistDoc serialization

void CDdlistDoc::Serialize(CArchive& ar)
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
// CDdlistDoc diagnostics

#ifdef _DEBUG
void CDdlistDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CDdlistDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDdlistDoc commands
