// fileview.cpp : implementation file
//

#include "stdafx.h"
#include "viewfile.h"
#include "viewfdoc.h"
#include "pviewdoc.h"

#include "fileview.h"
#include "headers.h"

extern CViewfileApp theApp;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

IMPLEMENT_DYNCREATE(CFileView, CView)

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

#define ID_LB 0xd000

BEGIN_MESSAGE_MAP(CFileView, CView)
    ON_LBN_DBLCLK(ID_LB,OnLBDoubleClicked)
	//{{AFX_MSG_MAP(CFileView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CFileView diagnostics

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileView message handlers


void CFileView::OnSize(UINT nType, int cx, int cy) 
{
 CView::OnSize(nType, cx, cy);
 m_LB.SetHorizontalExtent(m_iLongestStringSizeInPixels);
 if (m_LB.m_hWnd)
 m_LB.SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER);
}

// helper functions

BOOL CFileView::IsMyKindOfFile(BYTE *lpImage)
{ 
  return FALSE;     // hopefully this gets never called... 
};


int CFileView::FillInSizedString(BYTE *lpTarget, BYTE *lpSource)
{
 BYTE bSize;
 bSize = *lpSource++;
 strncpy((char *)lpTarget,(char *)lpSource,bSize);
 lpTarget[bSize]='\0';
 return (int) bSize;
}

void CFileView::FillInTaggedData(BYTE *lpMem, TAGGEDLISTSTRUCT *lpTemplate)
{
 int iLoop, iMemoryPointer;			    
 iMemoryPointer = 0;
 for (iLoop = 0; iLoop<lpTemplate->iNumberofEntries; iLoop++)
 {
  int iValue;
  switch (lpTemplate->teItem[iLoop].iLength)
  { case (sizeof(BYTE)):
      iValue = lpMem[iMemoryPointer];
	  break;
    case (sizeof(WORD)):
      iValue = ((WORD *)&(lpMem[iMemoryPointer]))[0];
	  break;
    case (sizeof(int)):
      iValue = ((int *)&(lpMem[iMemoryPointer]))[0];
	  break;
    default:; //we have to come up with something here...
  };
  wsprintf(m_szBuf,lpTemplate->teItem[iLoop].tlString,iValue);
  AddStringandAdjust(m_szBuf);
  iMemoryPointer+=lpTemplate->teItem[iLoop].iLength;
 };
}

void CFileView::FillInFlatStructures(PHEADERTEMPLATE pTemplate, unsigned char* pPointers)
{ 
 BYTE iCurrentSize;
 AddStringandAdjust(pTemplate->pszHeading);
 do 
  { 
    iCurrentSize = pPointers[0];
    if (!iCurrentSize) break;
    strncpy(m_szBuf,(const char *)&pPointers[1],iCurrentSize);
    m_szBuf[iCurrentSize]='\0';
	wsprintf(m_szBuf,pTemplate->pszTemplate,m_szBuf,((WORD *)(&pPointers[iCurrentSize+1]))[0]);
	AddStringandAdjust(m_szBuf);
	pPointers+=iCurrentSize;
	pPointers+=sizeof(WORD)+sizeof(BYTE);
  }
  while (TRUE); // the break statement bails us out here...

};

void CFileView::FillInChainedStructures(int iEntries, PHEADERTEMPLATE pTemplate,WORD *pPointers,unsigned char *pBase)
{ 
  int iLoop;
  BYTE *pGoryDetails;
  AddStringandAdjust(pTemplate->pszHeading);
  for (iLoop=0;iLoop<iEntries;iLoop++)
   {
    pGoryDetails=pBase+pPointers[iLoop];
    strncpy(m_szBuf,(const char *)&pGoryDetails[1],pGoryDetails[0]);
	m_szBuf[pGoryDetails[0]] = '\0';
// this is ugly because here we make an assumption as to how many parameters there
// are to the wsprintf call -- let's meditate if there isn't a more generic way to do it...
	wsprintf(m_szBuf,pTemplate->pszTemplate,m_szBuf);
	AddStringandAdjust(m_szBuf);
   };
};
    

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CView::OnCreate(lpCreateStruct) == -1)
   return -1;
  m_LB.Create(LBS_NOINTEGRALHEIGHT|WS_VISIBLE|/*WS_CHILD|*/WS_HSCROLL|WS_VSCROLL|LBS_NOTIFY,CRect(20,20,20,20),this,ID_LB);
  m_cfFixedFont = new CFont();
  m_cfFixedFont->CreateStockObject(ANSI_FIXED_FONT);
  m_LB.SetFont(m_cfFixedFont);
  LOGFONT lfCurrentFont;
  m_cfFixedFont->GetObject(sizeof(LOGFONT),&lfCurrentFont);
  m_iFontWidth = lfCurrentFont.lfWidth;  // should be good enough...
  m_iLongestStringSizeInPixels = 0;
  return 0;
}

void CFileView::ClearWindow()
{
 m_LB.ResetContent();
};

void CFileView::AddStringandAdjust(char *cString)
{   
  ComputeNewHorizontalExtent(m_iFontWidth*strlen(cString));
  m_LB.AddString(cString);
};

void CFileView::OnDestroy() 
{   
  delete m_cfFixedFont;
  CView::OnDestroy();
}

void CFileView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{	
  CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (GetDocument()->IsKindOf(RUNTIME_CLASS(CPViewDoc))) 
  theApp.SetStatusBarText(((CPViewDoc *)GetDocument())->szStatusMessage);
   else
  theApp.SetStatusBarText(((CViewfileDoc *)GetDocument())->szStatusMessage);
}

afx_msg void CFileView::OnLBDoubleClicked()
{ 
  DispatchDoubleClick(m_LB.GetText(m_LB.GetCurSel(),m_Selection));
};

// just to satisfy the IMPLEMENT_DYNACREATE macro...

void CFileView::DispatchDoubleClick(int iVal)
{
}; 


void CFileView::OnDraw(CDC* pDC) 
{
}
