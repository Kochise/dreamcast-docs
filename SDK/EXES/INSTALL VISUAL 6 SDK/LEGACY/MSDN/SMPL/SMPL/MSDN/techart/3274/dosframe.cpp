// dosframe.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"

#include "fileview.h"
#include "viewfdoc.h"


#define DOSHEADERS
#include "headers.h"
#undef DOSHEADERS

#include "dosview.h"

#include "childfrm.h"
#include "dosframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDOSFrame

IMPLEMENT_DYNCREATE(CDOSFrame, CChildFrame)

CDOSFrame::CDOSFrame()
{
}

CDOSFrame::~CDOSFrame()
{
}


BEGIN_MESSAGE_MAP(CDOSFrame, CChildFrame)
	//{{AFX_MSG_MAP(CDOSFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDOSFrame message handlers

BOOL CDOSFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
 m_iNumberRows = 2;
 m_iNumberCols = 1;
 m_ViewClass = RUNTIME_CLASS(CDOSView);
 if (!CChildFrame::OnCreateClient(lpcs,pContext)) return FALSE;
  _try 
   {
    CFileView *cfMyPointer = (CFileView *) m_wndSplitter.GetPane(0,0);
    cfMyPointer->FillInTaggedData((unsigned char *)m_AssociatedDocument->AdjustPointerAbsolute(0),&tlDosHeader);
   }
  _except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION?
             EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    { 
     AfxMessageBox("corrupted file; can not display all information");
    }
  return TRUE;
}
