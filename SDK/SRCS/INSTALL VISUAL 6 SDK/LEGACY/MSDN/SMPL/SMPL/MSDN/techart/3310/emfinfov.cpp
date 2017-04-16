// emfinfov.cpp : implementation file
//

#include "stdafx.h"
#include "metavw1.h"

#include "metavdoc.h"
#include "emfinfov.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define SIZEOFWORD  sizeof(WORD)
#define SIZEOFDWORD sizeof(DWORD)
#define SIZEOFRECT  sizeof(RECTL)
#define SIZEOFSIZE  sizeof(SIZE)
DWORD DWORDMASK = (DWORD)(~0);
WORD  WORDMASK = (WORD)(~0);

struct HEADERFIELDS
{							
  char szFieldName[50];
  UINT uiSize;
} HeaderFields[15] = {"iType\t\t%lu", SIZEOFDWORD,
                 	 "nSize\t\t%lu", SIZEOFDWORD,
                 	 "rclBounds\tleft %ld top %ld right %ld bottom %ld", SIZEOFRECT,
 				 	 "rclFrame\tleft %ld top %ld right %ld bottom %ld",	SIZEOFRECT,
 				 	 "dSignature\t%lX", SIZEOFDWORD,
 				 	 "nVersion\t%lu", SIZEOFDWORD,
 				 	 "nBytes\t\t%lu", SIZEOFDWORD,
 				 	 "nRecords\t%lu", SIZEOFDWORD,
 				 	 "nHandles\t%lu", SIZEOFWORD,
 				 	 "sReserved\tduh...", SIZEOFWORD,
 				 	 "nDescription\t%lu", SIZEOFDWORD,
 				 	 "offDescription\t%lu", SIZEOFDWORD,
 				 	 "nPalEntries\t%lu", SIZEOFDWORD,
 				 	 "szlDevice\tcx %ld cy %ld", SIZEOFSIZE,
 				 	 "szlMillimeters\tcx %ld cy %ld", SIZEOFSIZE};

/////////////////////////////////////////////////////////////////////////////
// CEMFInfoView

IMPLEMENT_DYNCREATE(CEMFInfoView, CView)

CEMFInfoView::CEMFInfoView()
{
}

CEMFInfoView::~CEMFInfoView()
{
}


BEGIN_MESSAGE_MAP(CEMFInfoView, CView)
	//{{AFX_MSG_MAP(CEMFInfoView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEMFInfoView drawing

void CEMFInfoView::OnDraw(CDC* pDC)
{
    CMetavw1Doc* pDoc = GetDocument();
	RECT rc;
	LPBYTE pb = m_pbEmfHeader;
    char Str[50];
    TEXTMETRIC tm;

	pDC->GetTextMetrics(&tm);
    int nLineSpacing = tm.tmHeight + tm.tmExternalLeading;
	GetClientRect(&rc);
	for (int nYOrg = 0, i = 0; i < 15; nYOrg += nLineSpacing, i++)
	{
	  rc.top = nYOrg;
	  DWORD dwMask = (HeaderFields[i].uiSize >= SIZEOFDWORD) ? DWORDMASK : WORDMASK;
	  DWORD dwVal = (dwMask == DWORDMASK) ? *(LPDWORD)pb & dwMask : *(LPWORD)pb & dwMask; 

      switch (HeaderFields[i].uiSize)
   	  {
		  case SIZEOFWORD:
		  case SIZEOFDWORD:
	        wsprintf(Str, HeaderFields[i].szFieldName, dwVal);
		    break;
		  case SIZEOFSIZE:
	        wsprintf(Str, HeaderFields[i].szFieldName, dwVal, 
	                *(LPDWORD)(pb + SIZEOFDWORD) & dwMask);
		    break;
		  case SIZEOFRECT:
	        wsprintf(Str, HeaderFields[i].szFieldName, dwVal, 
	                *(LPDWORD)(pb + SIZEOFDWORD) & dwMask, 
	                *(LPDWORD)(pb + 2 * SIZEOFDWORD) & dwMask, 
	                *(LPDWORD)(pb + 3 * SIZEOFDWORD) & dwMask);
		    break;
		  default:
		    break;
	  }

	  pDC->DrawText((LPCTSTR)Str, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_EXPANDTABS);
	  pb += HeaderFields[i].uiSize;
	}  
}

/////////////////////////////////////////////////////////////////////////////
// CEMFInfoView diagnostics

#ifdef _DEBUG
void CEMFInfoView::AssertValid() const
{
	CView::AssertValid();
}

void CEMFInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMetavw1Doc* CEMFInfoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMetavw1Doc)));
	return (CMetavw1Doc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CEMFInfoView message handlers

int CEMFInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CMetavw1Doc* pDoc = GetDocument();
	LPENHMETAHEADER pEMFHdr = pDoc->m_cemf.GetEMFHeader();

	m_pbEmfHeader = (LPBYTE)malloc(sizeof(ENHMETAHEADER));
	if (m_pbEmfHeader) {
	  memcpy(m_pbEmfHeader, pEMFHdr, sizeof(ENHMETAHEADER));
	}

	return 0;
}


void CEMFInfoView::OnDestroy() 
{
	CView::OnDestroy();
	if (m_pbEmfHeader)
	  free(m_pbEmfHeader);	
	
}
