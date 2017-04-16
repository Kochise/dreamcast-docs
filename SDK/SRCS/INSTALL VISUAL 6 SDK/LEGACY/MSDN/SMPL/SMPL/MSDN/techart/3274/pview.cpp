// pview.cpp : implementation file
//

//#include    <windows.h>


#include "stdafx.h"


#include "viewfile.h"

#include "fileview.h"

#include "pview.h"

#include "plist.h"




#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPView

IMPLEMENT_DYNCREATE(CPView, CFileView)

CPView::CPView()
{ m_bRefreshing=-1;
}

CPView::~CPView()
{
}


BEGIN_MESSAGE_MAP(CPView, CFileView)
	//{{AFX_MSG_MAP(CPView)
	ON_COMMAND(WMC_REFRESH, RefreshProcessList)
	ON_MESSAGE(WMC_NEXTENTRY, AddEntry)
	ON_MESSAGE(WMC_FINISHED, ListFinished)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPView drawing

void CPView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPView diagnostics

#ifdef _DEBUG
void CPView::AssertValid() const
{
	CView::AssertValid();
}

void CPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPView message handlers


void CPView::RefreshProcessList()
{  if (InterlockedIncrement(&m_bRefreshing) >0) return;
   ClearWindow();
   CPerfData cpData;
	cpData.Initialize(this);

}

long CPView::AddEntry(UINT wParam,LONG lPARAM)
{ HANDLE hMem = (HANDLE)wParam;
  LPSTR lpMem = (LPSTR)LocalLock(hMem);
  AddStringandAdjust(lpMem);
  LocalUnlock(hMem);
  LocalFree(hMem);
  return 0;
};

long CPView::ListFinished(UINT wParam, LONG lParam)
{ MessageBeep(-1);
  InterlockedDecrement(&m_bRefreshing);
  return 0;
};


int CPView::ExtractProcessId(char *cArg)
{ // this code is kinda weird, but then again...
  int iResult;
  if (sscanf(cArg,"%x",&iResult)==1)
     return iResult;
  else return 0;
};

void CPView::DispatchDoubleClick(int iVal)
{ 
  if (AfxMessageBox("Kill Process?",MB_OKCANCEL) == IDOK)
   {CPerfData cpData;
    if (!cpData.KillProcessEntry(ExtractProcessId(m_Selection)))
      AfxMessageBox("Could not kill process...");
	else
    RefreshProcessList();
   };

};

void CPView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	RefreshProcessList();	
	
}


