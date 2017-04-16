// viewfdoc.cpp : implementation of the CViewfileDoc class
//

#include "stdafx.h"
#include "viewfile.h"

//#include <windows.h>    // for the file mapping stuff

#include "viewfdoc.h"

#include "headers.h"

#include "fileview.h"

#include "leview.h"
#include "neview.h"
#include "rawview.h"
#include "peview.h"
#include "dosview.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CViewfileApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CViewfileDoc

IMPLEMENT_DYNCREATE(CViewfileDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewfileDoc, CDocument)
	//{{AFX_MSG_MAP(CViewfileDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewfileDoc construction/destruction

CViewfileDoc::CViewfileDoc()
{
	// TODO: add one-time construction code here

}

CViewfileDoc::~CViewfileDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CViewfileDoc serialization

void CViewfileDoc::Serialize(CArchive& ar)
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
// CViewfileDoc diagnostics

#ifdef _DEBUG
void CViewfileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewfileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewfileDoc commands



// helper functions

BYTE *CViewfileDoc::AdjustPointerRelative(int iOffset)
{ 
  m_iCurrentPointer+=iOffset;
  return &m_lpImage[m_iCurrentPointer];
};

BYTE *CViewfileDoc::AdjustPointerAbsolute(int iPosition)
{ 
  m_iCurrentPointer=iPosition;
  return &m_lpImage[m_iCurrentPointer];
};

// let's see if we can get by without these...

BOOL CViewfileDoc::RetrieveBytesAtCurrentPosition(BYTE *lpTarget, int iLength)
{ 
  memcpy(lpTarget,&m_lpImage[m_iCurrentPointer],iLength);
  return TRUE;
};

BOOL CViewfileDoc::RetrieveBytesAtAbsolutePosition(BYTE *lpPosition, BYTE *lpTarget, int iLength)
{ 
  return FALSE;
};

BOOL CViewfileDoc::OnOpenDocument(LPCTSTR lpszFileName)
{
  m_csFileName = (CString *)0;
  if (INVALID_HANDLE_VALUE==(m_hFile=CreateFile(lpszFileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
					   	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)))
  {
   AfxMessageBox("File Open failed - check if the path name provided is correct!",MB_OK);
   return(FALSE);
  };
  m_hFileMapping = CreateFileMapping(m_hFile,NULL,PAGE_READONLY,0,0,NULL);
  if (!m_hFileMapping) 
  {
   AfxMessageBox("Could not create file mapping -- possible security problem",MB_OK);
   CloseHandle(m_hFile);
   return(FALSE);
  };
  m_lpImage = (BYTE *)MapViewOfFile(m_hFileMapping,FILE_MAP_READ,0,0,0);
  if (!m_lpImage) 
  {
   CloseHandle(m_hFileMapping);
   CloseHandle(m_hFile);
   AfxMessageBox("Could not map view of file -- possible memory problem",MB_OK);
   return(FALSE);
  };

  theApp.AddToRecentFileList(lpszFileName);
  m_csFileName = new CString(lpszFileName);
  SetPathName(lpszFileName);
  m_iCurrentPointer = 0;
  DWORD dwFileSizeHigh;
  m_iFileSize = GetFileSize(m_hFile,&dwFileSizeHigh);

// initially, the document is associated with a raw view. Now we need to determine the type of 
// the executable and create an appropriate view.

  CFrameWnd *pNewFrame=NULL;
  
  // first check to see if there is a DOS header
   if (CDOSView::IsMyKindOfFile(m_lpImage))
      {
        wsprintf(szStatusMessage,"DOS signature found for %s",lpszFileName);
        pNewFrame = theApp.m_pDOSTemplate->CreateNewFrame(this,NULL);
		if (pNewFrame)
        theApp.m_pDOSTemplate->InitialUpdateFrame(pNewFrame, this, TRUE);
      }

 // now look for additional info. Note that a DOS header has already been created here...
   if (CPEView::IsMyKindOfFile(m_lpImage))
      {
	    wsprintf(szStatusMessage,"PE signature found for %s",lpszFileName);
        pNewFrame = theApp.m_pPETemplate->CreateNewFrame(this,NULL);
        if (pNewFrame)
        theApp.m_pPETemplate->InitialUpdateFrame(pNewFrame, this, TRUE);
      }
   else if (CNEView::IsMyKindOfFile(m_lpImage)) 
      {
        wsprintf(szStatusMessage,"NE signature found for %s",lpszFileName);
        pNewFrame = theApp.m_pNETemplate->CreateNewFrame(this,NULL);
        if (pNewFrame)
        theApp.m_pNETemplate->InitialUpdateFrame(pNewFrame, this, TRUE);
      }
   else if (CLEView::IsMyKindOfFile(m_lpImage))
      {
        wsprintf(szStatusMessage,"LE signature found for %s",lpszFileName);
        pNewFrame = theApp.m_pLETemplate->CreateNewFrame(this,NULL);
        if (pNewFrame)
        theApp.m_pLETemplate->InitialUpdateFrame(pNewFrame, this, TRUE);
      }
      else if (!pNewFrame)
      {
        wsprintf(szStatusMessage,"No known signature found for %s",lpszFileName);
		pNewFrame = NULL;
      };
   m_PriorityFrame=pNewFrame; // last frame created...
   return TRUE;
};

void CViewfileDoc::ActivateTheRightFrame()
{
 if (!m_PriorityFrame)
  {POSITION ps=GetFirstViewPosition();
   m_PriorityFrame = GetNextView(ps)->GetParentFrame();
  };
  m_PriorityFrame->ActivateFrame(SW_SHOWNORMAL);

};

void CViewfileDoc::OnCloseDocument()
{
 UnmapViewOfFile(m_lpImage);
 CloseHandle(m_hFileMapping);
 CloseHandle(m_hFile);
 strcpy(szStatusMessage,"");
 theApp.SetStatusBarText(szStatusMessage);
 CDocument::OnCloseDocument();
}

	
