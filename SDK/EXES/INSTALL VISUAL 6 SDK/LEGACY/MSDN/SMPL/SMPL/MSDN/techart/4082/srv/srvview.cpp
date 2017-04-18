// npscevw.cpp : implementation of the CSecSrvView class
//

#include "stdafx.h"

#include "common.h"
#include "srvapp.h"

#include "srvdoc.h"
#include "easyview.h"
#include "srvview.h"

#include "comclass.h"


#include "sec.h"
#include "npipe.h"

#include "cmutex.h"
#include "cfilemap.h"

#include "dbcode.h"

#include "protocol.h"

#include "examstff.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define ID_LB 0xd000

// HANDLE hMainThread;   /// RAc -- this is for test purposes ONLY...

/////////////////////////////////////////////////////////////////////////////
// CSecSrvView

IMPLEMENT_DYNCREATE(CSecSrvView, CEasyOutputView)

BEGIN_MESSAGE_MAP(CSecSrvView, CEasyOutputView)
	//{{AFX_MSG_MAP(CSecSrvView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDS_MUTEXPERMISSIONS, OnMutexpermissions)
	ON_COMMAND(IDS_PERMISSIONS, OnPermissions)
	ON_COMMAND(IDS_WAITTOCONNECT, OnWaittoconnect)
	ON_COMMAND(ID_DATABASE_ADDARECORD, OnDatabaseAddarecord)
	ON_COMMAND(ID_DATABASE_REMOVEARECORD, OnDatabaseRemovearecord)
	ON_COMMAND(ID_DATABASE_VIEWCONTENTS, OnDatabaseViewcontents)
	ON_COMMAND(ID_FILEMAPPINGS_PERMISSIONS, OnFilemappingsPermissions)
	ON_COMMAND(ID_FILE_CANCELWAIT, OnFileCancelwait)
	ON_UPDATE_COMMAND_UI(ID_FILE_CANCELWAIT, OnUpdateFileCancelwait)
	ON_UPDATE_COMMAND_UI(IDS_WAITTOCONNECT, OnUpdateWaittoconnect)
	ON_COMMAND(IDS_DATABASE_PERMISSIONS, OnDatabasePermissions)
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
 if (m_bThreadIsActive)
 {
  m_cpPipe->CancelCommunicationAttempt();
  TerminateThread(m_hThread,0);
//  WaitForSingleObject(m_hThread,INFINITE);
  CloseHandle(m_hThread);
 };

	// TODO: Add your specialized code here and/or call the base class
 if (m_cpPipe) 
 {
  m_cpPipe->Close();
  delete m_cpPipe;
 };
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
 delete m_cqQueue;
 SetSpecificPrivilegeInAccessToken("SeAuditPrivilege",FALSE); 

 CEasyOutputView::OnDestroy();
}

int CSecSrvView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
 if (!SetSpecificPrivilegeInAccessToken("SeAuditPrivilege",TRUE)) return -1;

 m_bThreadIsActive = FALSE;
 if (CEasyOutputView::OnCreate(lpCreateStruct) == -1)
  return -1;
// create all kinds of stuff here. 
 m_cpPipe = new CSecuredNamedPipe();
 if (!m_cpPipe->Open(NULL,CFile::modeReadWrite))
  DisplayTextErrorMessage("open named pipe failed -- %s",m_cpPipe->m_iErrorCode);
 else
  AddStringandAdjust("Created named pipe");
 m_cpMutex = new CSecuredMutex(MUTEXNAME);   // error return here?
 AddStringandAdjust("Created mutex...");
 m_cpFileMap = new CSecuredFileMapping(SHAREDMAPPINGNAME,MAPPINGSIZE);  // create a test mapping here...
 AddStringandAdjust("Created shared memory...");
 m_lpSharedMem = m_cpFileMap->ObtainPointer();      
 if (!m_lpSharedMem)
  AddStringandAdjust("could not obtain pointer in shared memory");
 else
  AddStringandAdjust("obtained pointer in shared memory");
// let's assume that everything worked out well here.	
 m_cqQueue = new ServerChainedQueue(m_lpSharedMem,MAPPINGSIZE,m_cpMutex,m_cpPipe);
 AddStringandAdjust("created database...");
 return 0;
}

void CSecSrvView::OnPermissions() 
{
 if (!m_cpPipe->AddSecurity(STANDARD_RIGHTS_ALL|GENERIC_ALL|SPECIFIC_RIGHTS_ALL|
                             FILE_ALL_ACCESS|FILE_CREATE_PIPE_INSTANCE,"named pipe security"))
  DisplayTextErrorMessage("could not set security on named pipe -- %s",m_cpPipe->m_iSecErrorCode);
 else
  AddStringandAdjust("security on named pipe set");
}


long WINAPI PipeThreadFunction(CSecSrvView *cvTarget) 
{ 
 char szDiagnosticMessage[255];
 CServerDatabaseProtocol *cpProt;
 BOOL bFinished;
 ServerChainedQueue *cqTheQueue = cvTarget->m_cqQueue;
 if (!cvTarget->m_cpPipe->AwaitCommunicationAttempt())
 { 
  cvTarget->DisplayTextErrorMessage("Open named pipe failed -- %s",cvTarget->m_cpPipe->m_iErrorCode);
  goto ErrorExit;
 }
 else
 {
  sprintf(szDiagnosticMessage,"Open named pipe succeeded");
  cvTarget->AddStringandAdjust(szDiagnosticMessage);
 }
 cpProt = new CServerDatabaseProtocol(cvTarget->m_cpPipe);
 if (!cpProt->Open("",CFile::modeReadWrite)) // we are server...
  goto ErrorExit;
 int iCommand,iIndex;
 CHAINLIST cpElement;
 bFinished=FALSE;
 while (!bFinished)  // we'll break out of this loop later...
 {
  if (!cpProt->AcceptCommand(&iCommand,&cpElement,&iIndex))
  { 
   cvTarget->DisplayTextErrorMessage("accepting command from named pipe failed -- %s",cpProt->m_iErrorCode);
   bFinished = TRUE;
   continue;
  };
  switch (iCommand)
  { 
   case CMD_EXIT:
    cvTarget->AddStringandAdjust("Client terminated connection!");
    bFinished=TRUE;
    break;
   case CMD_GETENTRIES:
    cpProt->Acknowledge(cqTheQueue->GetEntries());
    break;
   case CMD_ADDRECORD:
    if (!cqTheQueue->SafeInsert(&iIndex,&cpElement))
    {
     cvTarget->DisplayTextErrorMessage("Remote insert failed; propagating error code -- %s",cqTheQueue->m_iErrorCode);
     cpProt->Fail(cqTheQueue->m_iErrorCode);
    }
    else
    {
     cpProt->Acknowledge(iIndex);
     cvTarget->AddStringandAdjust("Remote insert succeeded!");
    };
    break;
   case CMD_DELETERECORD:
    if (!cqTheQueue->SafeRemove(iIndex))
    { 
     cvTarget->DisplayTextErrorMessage("Remote remove failed; propagating error code -- %s",cqTheQueue->m_iErrorCode);
     cpProt->Fail(cqTheQueue->m_iErrorCode);
    }
	else
	{
     cpProt->Acknowledge(0);
     cvTarget->AddStringandAdjust("remote remove succeeded!");
    };
	break;
   case CMD_RETRIEVERECORD:
    if (!cqTheQueue->SafeRetrieve(iIndex,&cpElement))
    {
     cvTarget->DisplayTextErrorMessage("Remote retrieve failed; propagating error code -- %s",cqTheQueue->m_iErrorCode);
     cpProt->Fail(cqTheQueue->m_iErrorCode);
    }
    else
    { 
	 cpProt->Acknowledge(cpElement.iInsecuredElement);
     cpProt->Acknowledge(cpElement.iSecuredElement);
     cvTarget->AddStringandAdjust("remote retrieve succeeded!");
	};
    break;
   }; // switch
 };	// while
 cpProt->Close();
 delete (cpProt);
 cvTarget->m_cpPipe->CloseInstance();
ErrorExit:
 CloseHandle(cvTarget->m_hThread);
 cvTarget->m_bThreadIsActive = FALSE;
 return 0;
};	// thread fn


void CSecSrvView::OnWaittoconnect() 
{ 
 DWORD id;
 m_bThreadIsActive = TRUE;
 AddStringandAdjust("waiting to connect...");
 m_hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)PipeThreadFunction,this,CREATE_SUSPENDED,&id);
 SetThreadPriority(m_hThread,THREAD_PRIORITY_BELOW_NORMAL);
 ResumeThread(m_hThread);
}

void CSecSrvView::OnMutexpermissions() 
{
 if (!m_cpMutex->AddSecurity(MUTEX_ALL_ACCESS,"mutex security"))
  DisplayTextErrorMessage("could not set security on mutex -- %s",m_cpMutex->m_iSecErrorCode);
 else
  AddStringandAdjust("security set on the mutex");
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

void CSecSrvView::OnFilemappingsPermissions()  
{
 if (!m_cpFileMap->AddSecurity(GENERIC_ALL|STANDARD_RIGHTS_REQUIRED,"file mapping security"))
  DisplayTextErrorMessage("could not set security on shared file -- %s",m_cpFileMap->m_iSecErrorCode);
 else 
  AddStringandAdjust("security set on shared file");
}

void CSecSrvView::OnFileCancelwait() 
{
 m_cpPipe->CancelCommunicationAttempt();
}

void CSecSrvView::OnUpdateFileCancelwait(CCmdUI* pCmdUI) 
{
 pCmdUI->Enable(m_cpPipe->GetStatus()&STATUS_CONNECTION_PENDING);	
}

void CSecSrvView::OnUpdateWaittoconnect(CCmdUI* pCmdUI) 
{
 pCmdUI->Enable(!(m_cpPipe->GetStatus()&(STATUS_CONNECTED|STATUS_CONNECTION_PENDING)));	
}

void CSecSrvView::OnDatabasePermissions() 
{
 if (!m_cqQueue->AddSecurity(GENERIC_WRITE,"database security"))
  DisplayTextErrorMessage("could not set security on the database -- %s",m_cqQueue->m_iSecErrorCode);
 else 
  AddStringandAdjust("security set on database");
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

