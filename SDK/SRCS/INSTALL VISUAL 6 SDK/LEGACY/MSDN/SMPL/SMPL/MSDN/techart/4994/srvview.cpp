// npscevw.cpp : implementation of the CSecSrvView class
//

#include "stdafx.h"

#include "common.h"
#include "srvapp.h"

#include "srvdoc.h"
#include "easyview.h"
#include "srvview.h"

#include "comclass.h"


#include "npipe.h"


#include "cmutex.h"
#include "cfilemap.h"

#include "dbcode.h"

#include "protocol.h"

#include "client.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define ID_LB 0xd000


/////////////////////////////////////////////////////////////////////////////
// CSecSrvView

IMPLEMENT_DYNCREATE(CSecSrvView, CEasyOutputView)

BEGIN_MESSAGE_MAP(CSecSrvView, CEasyOutputView)
	//{{AFX_MSG_MAP(CSecSrvView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_DATABASE_ADDARECORD, OnDatabaseAddarecord)
	ON_COMMAND(ID_DATABASE_REMOVEARECORD, OnDatabaseRemovearecord)
	ON_COMMAND(ID_DATABASE_VIEWCONTENTS, OnDatabaseViewcontents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecSrvView construction/destruction

CSecSrvView::CSecSrvView()
{
}

CSecSrvView::~CSecSrvView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSecSrvView drawing

void CSecSrvView::OnDraw(CDC* pDC)
{
	CSecSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CSecSrvView diagnostics

#ifdef _DEBUG
void CSecSrvView::AssertValid() const
{
	CEasyOutputView::AssertValid();
}

void CSecSrvView::Dump(CDumpContext& dc) const
{
	CEasyOutputView::Dump(dc);
}

CSecSrvDoc* CSecSrvView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecSrvDoc)));
	return (CSecSrvDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecSrvView message handlers


void CSecSrvView::OnDestroy() 
{
 m_bFinished=TRUE;
 if (m_cpMutex) 
 {
  m_cpMutex->Close();
  delete m_cpMutex;
 };
 if (m_cpFileMap)
 {
  m_cpFileMap->ReleasePointer();
  m_cpFileMap->Close();
  delete m_cpFileMap;
 };
  delete m_Protocol;
  delete m_cqQueue;
 for (int iLoop=0;iLoop<MAXCLIENTCOUNT;iLoop++)
 {
 m_ciClientBlock[iLoop].Client_hPipe->Close();
 delete (m_ciClientBlock[iLoop].Client_hPipe);  
 };
   
 WaitForSingleObject(m_hConnectThread,INFINITE);
 CEasyOutputView::OnDestroy();
}

#define WORKERTHREADCOUNT 5

int CSecSrvView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
 if (CEasyOutputView::OnCreate(lpCreateStruct) == -1)
  return -1;
// create all kinds of stuff here.
// beautify this code later on...
 m_bFinished=FALSE;
 m_Protocol = new CServerDatabaseProtocol(WORKERTHREADCOUNT);
 for (int iLoop=0;iLoop<MAXCLIENTCOUNT;iLoop++)
 {
 m_ciClientBlock[iLoop].Client_hPipe = 
   new CServerNamedPipe(MAXCLIENTCOUNT);
 if (!m_ciClientBlock[iLoop].Client_hPipe->Open
      (NULL,CFile::modeReadWrite))
  DisplayTextErrorMessage("open named pipe failed -- %s",
          m_ciClientBlock[iLoop].Client_hPipe->m_iErrorCode);
 else
 {
  sprintf(m_szBuf,"Created named pipe %i",iLoop);
  AddStringandAdjust(m_szBuf);
  m_Protocol->Associate((HANDLE)m_ciClientBlock[iLoop].Client_hPipe->m_hFile,iLoop);
 };
};
 
 m_cpMutex = new CServerMutex(MUTEXNAME);   // error return here?
 AddStringandAdjust("Created mutex...");
 m_cpFileMap = new CServerFileMapping(SHAREDMAPPINGNAME,MAPPINGSIZE);  // create a test mapping here...
 AddStringandAdjust("Created shared memory...");
 m_lpSharedMem = m_cpFileMap->ObtainPointer();      
 if (!m_lpSharedMem)
  AddStringandAdjust("could not obtain pointer in shared memory");
 else
  AddStringandAdjust("obtained pointer in shared memory");
// let's assume that everything worked out well here.
  m_cqQueue=new ServerChainedQueue(m_lpSharedMem,MAPPINGSIZE,
                         m_cpMutex);
	
 return 0;
}

long WINAPI PipeThreadFunction(void *vArg) 
{
 CSecSrvView *cvTarget = (CSecSrvView *)vArg;

 while (!cvTarget->m_bFinished)
 {
  for (int iLoop=0;iLoop<=MAXCLIENTCOUNT;iLoop++)
   if (cvTarget->m_ciClientBlock[iLoop].Client_hPipe->GetStatus()==STATUS_NOT_CONNECTED)
    break;
  if (iLoop==MAXCLIENTCOUNT)
  {
   cvTarget->AddStringandAdjust("no free slots left to accept communication");
   continue;
  };
 char szDiagnosticMessage[255];
 sprintf(szDiagnosticMessage,"channel %i waiting to connect...",iLoop);
 cvTarget->AddStringandAdjust(szDiagnosticMessage); 
 if (!cvTarget->m_ciClientBlock[iLoop].Client_hPipe->AwaitCommunicationAttempt())
 {
  if (cvTarget->m_ciClientBlock[iLoop].Client_hPipe->m_iErrorCode==ERROR_OPERATION_ABORTED)
   {
    continue;
   }; 
  cvTarget->DisplayTextErrorMessage("Open named pipe failed -- %s",cvTarget->m_ciClientBlock[iLoop].Client_hPipe->m_iErrorCode);
 }
 else
 {
  sprintf(szDiagnosticMessage,"Client connected on channel %i",iLoop);
  cvTarget->AddStringandAdjust(szDiagnosticMessage);
// set up a new client object to receive
// notifications from the pipe
 CClientObject *cpNewClient=
 new CClientObject(cvTarget->m_ciClientBlock[iLoop].Client_hPipe,cvTarget->m_cqQueue);
 cvTarget->m_ciClientBlock[iLoop].Client_ClientObject= cpNewClient;
 cvTarget->m_Protocol->Associate(cpNewClient,iLoop);
 };
 }; // while
 return 0;
}

void CSecSrvView::OnWaittoconnect() 
{
 DWORD id; 
 HANDLE hConnectThread;
 m_hConnectThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)PipeThreadFunction,(void *)this,CREATE_SUSPENDED,&id);
 SetThreadPriority(m_hConnectThread,THREAD_PRIORITY_BELOW_NORMAL);
 ResumeThread(m_hConnectThread);
}

#include "dbdialog.h"

void CSecSrvView::OnDatabaseAddarecord() 
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
  DisplayTextErrorMessage("local insert failed -- %s",m_cqQueue->m_iErrorCode);
}


void CSecSrvView::OnDatabaseRemovearecord() 
{
 int iIndex;
 CDeleteDialog cd;
 if (cd.DoModal() != IDOK) return;
 iIndex = cd.m_DeleteIndex;
// add code here to retrieve the index interactively
 if (m_cqQueue->Remove(iIndex))
 {
  sprintf(m_szDiagnosticMessage,"removed element %d",iIndex);
  AddStringandAdjust(m_szDiagnosticMessage);
 }
 else
  DisplayTextErrorMessage("local remove failed -- %s",m_cqQueue->m_iErrorCode);
}

void CSecSrvView::OnDatabaseViewcontents() 
{
 int iLoop;
 CHAINLIST clElement;
 for (iLoop=1;iLoop<m_cqQueue->GetEntries();iLoop++)
 {
  if (!m_cqQueue->Retrieve(iLoop,&clElement))
  { 
   char szTempBuffer[60];
   sprintf(szTempBuffer,"failed on retrieving element %d -- %%s",iLoop);
   DisplayTextErrorMessage(szTempBuffer,m_cqQueue->m_iErrorCode);
  }
  else
  {
   sprintf(m_szDiagnosticMessage,"element %d has values %d and %d",iLoop,clElement.iInsecuredElement,clElement.iSecuredElement);
   AddStringandAdjust(m_szDiagnosticMessage);
  };
 };  // for loop
}

LPSTR CSecSrvView::ObtainErrorFromCode(DWORD dwErrorCode)
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

void CSecSrvView::DisplayTextErrorMessage(LPSTR lpString, DWORD dwErrorCode)
{
 // note: the string must have been cleared to only contain one format element, %s
 LPSTR lpErrorText = ObtainErrorFromCode(dwErrorCode);
 sprintf(m_szDiagnosticMessage,lpString,lpErrorText);
 LocalFree(lpErrorText);
 AddStringandAdjust(m_szDiagnosticMessage);
};


void CSecSrvView::OnInitialUpdate() 
{
	CEasyOutputView::OnInitialUpdate();
	
	OnWaittoconnect();
	
}
