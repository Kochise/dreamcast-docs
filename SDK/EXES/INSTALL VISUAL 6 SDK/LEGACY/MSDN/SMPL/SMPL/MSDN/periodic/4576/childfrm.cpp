#include "stdafx.h"
#include "view3.h"
#include "doc.h"
#include "view.h"
#include "ChildFrm.h"
#include "DynTempl.h"

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
   //{{AFX_MSG_MAP(CChildFrame)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChildFrame::CChildFrame()
{
}

CChildFrame::~CChildFrame()
{
}

//////////////////
// Display the view type in the window title
//
void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
   // First let MFC do standard title
   CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
   
   CDocument* pDoc = GetActiveDocument();
   if (pDoc) {
      CDynViewDocTemplate* pTemplate = 
         (CDynViewDocTemplate*)pDoc->GetDocTemplate();
      ASSERT_KINDOF(CDynViewDocTemplate, pTemplate);
      ASSERT_VALID(pTemplate);

      CBaseView* pView = (CBaseView*)GetActiveView();
      const DYNAMICVIEWINFO* pInfo = pTemplate->GetViewInfo(pView);
      if (pInfo) {
         char text[256];
         GetWindowText(text, sizeof(text));  // Get MFC title..
         strcat(text, " As ");               // and append " As [viewName]"
         strcat(text, pInfo->name);          // ..
         SetWindowText(text);                // change frame title
      }
   }
}
