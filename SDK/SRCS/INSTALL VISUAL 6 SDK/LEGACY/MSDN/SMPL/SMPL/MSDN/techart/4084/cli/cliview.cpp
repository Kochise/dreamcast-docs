// npsecvw.cpp : implementation of the CSecCliView class
//

#include "stdafx.h"

#include "common.h"

#include "cliapp.h"

#include "protocol.h"

#include "easyview.h" 
#include "clidoc.h"
#include "cliview.h"

#include "comclass.h"

#include "npipe.h"
#include "cmutex.h"
#include "cfilemap.h"

#include "dbcode.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define ID_LB 0xd000


/////////////////////////////////////////////////////////////////////////////
// CSecCliView

IMPLEMENT_DYNCREATE(CSecCliView, CEasyOutputView)

BEGIN_MESSAGE_MAP(CSecCliView, CEasyOutputView)
	//{{AFX_MSG_MAP(CSecCliView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDS_CONNECT, OnConnect)
	ON_UPDATE_COMMAND_UI(ID_LOCALACCESS_ADDARECORD, OnUpdateLocal)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_ADDARECORD, OnUpdateRemote)
	ON_COMMAND(ID_LOCALACCESS_ADDARECORD, OnLocalaccessAddarecord)
	ON_COMMAND(ID_LOCALACCESS_REMOVEARECORD, OnLocalaccessRemovearecord)
	ON_COMMAND(ID_LOCALACCESS_VIEWCONTENTS, OnLocalaccessViewcontents)
	ON_COMMAND(ID_REMOTEACCESS_ADDARECORD, OnRemoteaccessAddarecord)
	ON_COMMAND(ID_REMOTEACCESS_REMOVEARECORD, OnRemoteaccessRemovearecord)
	ON_COMMAND(ID_REMOTEACCESS_VIEWCONTENTS, OnRemoteaccessViewcontents)
	ON_COMMAND(IDS_DISCONNECT, OnDisconnect)
	ON_COMMAND(ID_LOCALACCESS_CLOSESHAREDDATABASE, OnLocalaccessCloseshareddatabase)
	ON_COMMAND(ID_LOCALACCESS_OPENSHAREDDATABASE, OnLocalaccessOpenshareddatabase)
	ON_UPDATE_COMMAND_UI(IDS_CONNECT, OnUpdateNotRemote)
	ON_UPDATE_COMMAND_UI(ID_LOCALACCESS_OPENSHAREDDATABASE, OnUpdateNotLocal)
	ON_UPDATE_COMMAND_UI(ID_LOCALACCESS_REMOVEARECORD, OnUpdateLocal)
	ON_UPDATE_COMMAND_UI(ID_LOCALACCESS_VIEWCONTENTS, OnUpdateLocal)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_REMOVEARECORD, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_VIEWCONTENTS, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(IDS_DISCONNECT, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(ID_LOCALACCESS_CLOSESHAREDDATABASE, OnUpdateLocal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecCliView construction/destruction

CSecCliView::CSecCliView()
{
}

CSecCliView::~CSecCliView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSecCliView drawing

void CSecCliView::OnDraw(CDC* pDC)
{
	CSecCliDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CSecCliView diagnostics

#ifdef _DEBUG
void CSecCliView::AssertValid() const
{
	CEasyOutputView::AssertValid();
}

void CSecCliView::Dump(CDumpContext& dc) const
{
	CEasyOutputView::Dump(dc);
}

CSecCliDoc* CSecCliView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecCliDoc)));
	return (CSecCliDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecCliView message handlers

int CSecCliView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
 if (CEasyOutputView::OnCreate(lpCreateStruct) == -1) return -1;
 m_cpMutex = new CMutex();
 m_cpPipe = new CClientNamedPipe();
 m_cpFileMap = new CFileMapping();
 m_iOperationMode = OPERATION_MODE_NOT_CONNECTED;
 m_bRemote = FALSE;
 m_bLocal = FALSE;
 return 0;
}

void CSecCliView::OnDestroy() 
{
 if (m_iOperationMode & OPERATION_MODE_REMOTE) OnDisconnect();
 delete m_cpMutex;
 delete m_cpPipe;
 delete m_cpFileMap;
 CEasyOutputView::OnDestroy();
}



#include "browsedi.h"


void CSecCliView::OnConnect() 
{
 CBrowseDialog cbd;
 cbd.m_TargetName="other computer";
 if (cbd.DoModal()==IDCANCEL) return;
 if (!m_cpPipe->Open(cbd.m_TargetName,CFile::modeReadWrite))
  DisplayTextErrorMessage("Open named pipe failed -- %s",m_cpPipe->m_iErrorCode);
 else
 {
  sprintf(m_szDiagnosticMessage,"opened connection with %s",(const char *)cbd.m_TargetName);
  m_iOperationMode |= OPERATION_MODE_REMOTE;
  m_cpDB = new CClientDatabaseProtocol(m_cpPipe);
  AddStringandAdjust(m_szDiagnosticMessage);
 };
 if (m_iOperationMode & OPERATION_MODE_REMOTE) m_bRemote = TRUE;
}

void CSecCliView::OnUpdateLocal(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_iOperationMode & OPERATION_MODE_LOCAL));
}

void CSecCliView::OnUpdateRemote(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_iOperationMode & OPERATION_MODE_REMOTE));
}

#include "dbdialog.h"

void CSecCliView::OnLocalaccessAddarecord() 
{
 CHAINLIST cpElement;
 int iIndex;
 CAddrecordDialog cd;
 if (cd.DoModal() != IDOK) return;
 cpElement.iInsecuredElement = cd.m_Val1;
 cpElement.iSecuredElement = cd.m_Val2;
 if (m_cqQueue->Insert(&iIndex,&cpElement))
 {
  sprintf(m_szDiagnosticMessage,"inserted element; returned index is %d",iIndex);
  AddStringandAdjust(m_szDiagnosticMessage);
 }
 else
  DisplayTextErrorMessage("could not insert element --  %s",m_cqQueue->m_iErrorCode);
}

void CSecCliView::OnLocalaccessRemovearecord() 
{
 int iIndex;
 CDeleteDialog cd;
 if (cd.DoModal() != IDOK) return;
 iIndex = cd.m_DeleteIndex;
 if (m_cqQueue->Remove(iIndex))
 {
  sprintf(m_szDiagnosticMessage,"removed element %d",iIndex);
  AddStringandAdjust(m_szDiagnosticMessage);
 }
 else
  DisplayTextErrorMessage("could not remove element -- %s",m_cqQueue->m_iErrorCode);
}

void CSecCliView::OnLocalaccessViewcontents() 
{
 int iLoop;
 CHAINLIST clElement;
 for (iLoop=1;iLoop<m_cqQueue->GetEntries();iLoop++)
 {
  if (!m_cqQueue->Retrieve(iLoop,&clElement))
  {
   char szTempBuf[60];
   sprintf(szTempBuf,"failed on retrieving element %d -- %%s",iLoop);
   DisplayTextErrorMessage(szTempBuf,m_cqQueue->m_iErrorCode);
  }
  else
  {
   sprintf(m_szDiagnosticMessage,"element %d has values %d and %d",iLoop,clElement.iInsecuredElement,clElement.iSecuredElement);
   AddStringandAdjust(m_szDiagnosticMessage);
  };
 };  // for loop
}

void CSecCliView::OnRemoteaccessAddarecord() 
{
 CHAINLIST cpElement;
 int iIndex;
 CAddrecordDialog cd;
 if (cd.DoModal() != IDOK) return;
 cpElement.iInsecuredElement = cd.m_Val1;
 cpElement.iSecuredElement = cd.m_Val2;
 if (m_cpDB->AddData(&iIndex,&cpElement))
 { 
  sprintf(m_szDiagnosticMessage,"inserted element; returned index is %d",iIndex);
  AddStringandAdjust(m_szDiagnosticMessage);
 }
 else
  DisplayTextErrorMessage("could not insert element -- %s",m_cpDB->m_iErrorCode);
}

void CSecCliView::OnRemoteaccessRemovearecord() 
{
 int iIndex;
 CDeleteDialog cd;
 if (cd.DoModal() != IDOK) return;
 iIndex = cd.m_DeleteIndex;
 if (m_cpDB->RemoveData(iIndex))
 {
  sprintf(m_szDiagnosticMessage,"removed element %d",iIndex);
  AddStringandAdjust(m_szDiagnosticMessage);
 }
 else
  DisplayTextErrorMessage("could not remove element -- %s",m_cpDB->m_iErrorCode);
}

void CSecCliView::OnRemoteaccessViewcontents() 
{
 int iLoop;
 CHAINLIST clElement;
 int iNumberofEntries;
 if (m_cpDB->GetEntries(&iNumberofEntries))
 for (iLoop=1;iLoop<iNumberofEntries;iLoop++)
 {
  if (!m_cpDB->RetrieveData(iLoop,&clElement))
  { char szTempBuf[60];
  sprintf(szTempBuf,"failed on retrieving element %d -- %%s",iLoop);
  DisplayTextErrorMessage(szTempBuf,m_cpDB->m_iErrorCode);
  }
  else
  {
  sprintf(m_szDiagnosticMessage,"element %d has values %d and %d",iLoop,clElement.iInsecuredElement,clElement.iSecuredElement);
  AddStringandAdjust(m_szDiagnosticMessage);
  };
 }  // for loop
 else 
  DisplayTextErrorMessage("problem accessing the data base -- %s",m_cpDB->m_iErrorCode);
}

void CSecCliView::OnDisconnect() 
{
 m_cpDB->Terminate();
 m_cpDB->Close();
 m_cpPipe->Close();
 delete(m_cpDB);
 AddStringandAdjust("closed connection with remote server");
 m_iOperationMode &= ~OPERATION_MODE_REMOTE;
}

void CSecCliView::OnLocalaccessCloseshareddatabase() 
{
 m_cpFileMap->ReleasePointer();
 m_cpFileMap->Close();
 AddStringandAdjust("closed shared database");
 m_iOperationMode &= ~OPERATION_MODE_LOCAL;
}

void CSecCliView::OnLocalaccessOpenshareddatabase() 
{
 char szBuf[MAXMAPPINGNAME];
 sprintf(szBuf,SHAREDMAPPINGNAME);
 if (!m_cpFileMap->Open(szBuf))
  DisplayTextErrorMessage("Opening the file mapping failed -- %s",m_cpFileMap->m_iErrorCode);
 else
 {
  AddStringandAdjust("successfully opened the file mapping");
  m_lpSharedMemory=m_cpFileMap->ObtainPointer();
  if (!m_lpSharedMemory)
   DisplayTextErrorMessage("creating a mapping failed -- %s",m_cpFileMap->m_iErrorCode);
  else 
  { 
   sprintf(m_szDiagnosticMessage,"successfully created mapping of file at %8x",m_lpSharedMemory);
   AddStringandAdjust(m_szDiagnosticMessage);
   unsigned long iFileSizeHigh, iFileSize;
   iFileSize=GetFileSize(m_cpFileMap,&iFileSizeHigh);
   if (m_cpMutex->Open(MUTEXNAME))
    AddStringandAdjust("opened mutex");
   else
    DisplayTextErrorMessage("could not open mutex (there is no synchronization) -- %s",m_cpMutex->m_iErrorCode);
   m_cqQueue = new ChainedQueue(m_lpSharedMemory,iFileSize,m_cpMutex);
   m_iOperationMode |= OPERATION_MODE_LOCAL;
  };
 };
 if (m_iOperationMode & OPERATION_MODE_LOCAL) 
  m_bLocal = TRUE;
}


void CSecCliView::OnUpdateNotRemote(CCmdUI* pCmdUI) 
{
 pCmdUI->Enable(!(m_iOperationMode & OPERATION_MODE_REMOTE));
}

void CSecCliView::OnUpdateNotLocal(CCmdUI* pCmdUI) 
{
 pCmdUI->Enable(!(m_iOperationMode & OPERATION_MODE_LOCAL));
}

LPSTR CSecCliView::ObtainErrorFromCode(DWORD dwErrorCode)
{ 
 LPVOID lpMessageBuffer;
 FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,
 dwErrorCode, MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),(LPTSTR)&lpMessageBuffer,0,NULL);
 GetLastError();
 LPSTR lpReturn = (LPSTR) lpMessageBuffer;
 int iLen = strlen(lpReturn);
 int iLoop;
 for (iLoop=0;iLoop<iLen;iLoop++)
  if (iscntrl(lpReturn[iLoop]))
    lpReturn[iLoop] = ' ';
 return lpReturn;
};

void CSecCliView::DisplayTextErrorMessage(LPSTR lpString, DWORD dwErrorCode)
{
 // note: the string must have been cleared to only contain one format element, %s
 LPSTR lpErrorText = ObtainErrorFromCode(dwErrorCode);
 sprintf(m_szDiagnosticMessage,lpString,lpErrorText);
 LocalFree(lpErrorText);
 AddStringandAdjust(m_szDiagnosticMessage);
};
