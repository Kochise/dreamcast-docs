////////////////////////////////////////////////////////////////
// Implementation of the three view classes in VIEW3
//
#include "stdafx.h"
#include "view3.h"
#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBaseView, CView)

BEGIN_MESSAGE_MAP(CBaseView, CView)
   //{{AFX_MSG_MAP(CBaseView)
   ON_COMMAND(ID_FILE_EDIT, OnFileEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBaseView::CBaseView()
{
}

CBaseView::~CBaseView()
{
}

//////////////////
// Dialog to edit the document contents (a text string).
//
class CFileEditDlg : public CDialog {
public:
   CString  m_sText;
   CFileEditDlg(CWnd* pParent = NULL) : CDialog(IDD_FILEEDIT, pParent) { }
   virtual void DoDataExchange(CDataExchange* pDX) {
      CDialog::DoDataExchange(pDX);
      DDX_Text(pDX, IDC_EDIT1, m_sText);
      DDV_MaxChars(pDX, m_sText, 255);
   }
};

//////////////////
// Handle "File Edit" command
//
void CBaseView::OnFileEdit() 
{
   CView3Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   CFileEditDlg dlg;
   dlg.m_sText = pDoc->GetText();
   if (dlg.DoModal() == IDOK)
      pDoc->SetText(dlg.m_sText);
}

//////////////////////////////////////////////////////////////////////
// The three views follow. Each one implements OnDraw a different way.

IMPLEMENT_DYNCREATE(CView1, CBaseView)
IMPLEMENT_DYNCREATE(CView2, CBaseView)
IMPLEMENT_DYNCREATE(CView3, CBaseView)

//////////////////
// Draw document contents as ASCII text
//
void CView1::OnDraw(CDC* pDC)
{
   CView3Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   CString s = pDoc->GetText();
   CRect rc;
   GetClientRect(&rc);
   pDC->DrawText(s, &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//////////////////
// Draw document contents as binary 1's and 0's
//
void CView2::OnDraw(CDC* pDC)
{
   CView3Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   // It's overkill to recompute this on every draw, but who cares? 
   // CPU cycles are cheap, and you gotta give that fan a reason to spin!
   //
   CString s;
   for (LPCSTR p = pDoc->GetText(); *p; p++) {  // for each character:
      for (int bit=0; bit<8; bit++)             //   for each bit:
         s += (*p & 1<<bit) ? '1' : '0';        //     append 0 or 1
      s+= ' ';                                  //   space between chars
   }
   CRect rc;
   GetClientRect(&rc);
   pDC->DrawText(s, s.GetLength(), &rc, DT_LEFT|DT_WORDBREAK);
}

//////////////////
// Draw document contents as vertical stripes like a bar code
//
void CView3::OnDraw(CDC* pDC)
{
   CView3Doc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   CRect rc;
   GetClientRect(&rc);
   int x=0, bottom = rc.Height();
   for (LPCSTR p = pDoc->GetText(); *p; p++) {  // for each character:
      for (int bit=0; bit<8; bit++) {           //   for each bit:
         if (*p & 1<<bit) {                     //     if bit is ON:
            pDC->MoveTo(x, 0);                  //       draw a..
            pDC->LineTo(x, bottom);             //       ..vertical line
         }
         x++;                                   //   next x-pixel
      }
   }
}
