// animtdoc.cpp : implementation of the CAnimTestDoc class
//

#include "stdafx.h"
#include "animtest.h"
#include "animtvw.h"
#include "animtdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimTestDoc

IMPLEMENT_DYNCREATE(CAnimTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimTestDoc, CDocument)
    //{{AFX_MSG_MAP(CAnimTestDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimTestDoc construction/destruction

CAnimTestDoc::CAnimTestDoc()
{
    m_pPal = NULL;
}

CAnimTestDoc::~CAnimTestDoc()
{
    if (m_pPal) delete m_pPal;
}

BOOL CAnimTestDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    if (!Restart(320, 240)) return FALSE;
    // Resize the main frame window to fit the background image
    CAnimTestView* pView = GetView();
    ASSERT(pView);
    pView->GetParentFrame()->RecalcLayout();
    pView->ResizeParentToFit(FALSE); // Try shrinking first
    pView->ResizeParentToFit(TRUE); // Let's be daring
    return TRUE;
}

BOOL CAnimTestDoc::Restart(int w, int h)
{
    // Define the minimum size
    if ((w < 320) || (h < 240)) {
        w = 320;
        h = 240;
    }

    // Create a wash palette
    if (m_pPal) delete m_pPal;
    m_pPal = new CDIBPal;
    ASSERT(m_pPal);
    m_pPal->CreateWash();
    m_pPal->SetSysPalColors();

    // Create a DIB for the background
    m_dibBkgnd.Create(w, h, m_pPal);

    // Create a new os-buffer
    CAnimTestView* pView = GetView();
    ASSERT(pView);
    if (!pView->Create(w, h, m_pPal)) {
        return FALSE;
    }

    UpdateAllViews(NULL);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAnimTestDoc serialization

void CAnimTestDoc::Serialize(CArchive& ar)
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
// CAnimTestDoc diagnostics

#ifdef _DEBUG
void CAnimTestDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CAnimTestDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimTestDoc commands

CAnimTestView* CAnimTestDoc::GetView()
{
    POSITION pos;
    pos = GetFirstViewPosition();
    ASSERT(pos);
    CAnimTestView *pView = (CAnimTestView *)GetNextView(pos);
    ASSERT(pView);
    ASSERT(pView->IsKindOf(RUNTIME_CLASS(CAnimTestView)));
    return pView;
}
