// npsecvw.cpp : implementation of the CSecCliView class
//

#include "stdafx.h"

#include "common.h"

#include "cliapp.h"


#include "easyview.h" 
#include "clidoc.h"

#include "dbcode.h"

#include "cliview.h"

#include "comclass.h"

#include "npipe.h"
#include "cmutex.h"
#include "cfilemap.h"

#include "protocol.h"


//#include "dbcode.h"



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
	ON_COMMAND(ID_REMOTEACCESS_ADDARECORD, OnRemoteaccessAddarecord)
	ON_COMMAND(ID_REMOTEACCESS_REMOVEARECORD, OnRemoteaccessRemovearecord)
	ON_COMMAND(ID_REMOTEACCESS_VIEWCONTENTS, OnRemoteaccessViewcontents)
	ON_COMMAND(IDS_DISCONNECT, OnDisconnect)
	ON_UPDATE_COMMAND_UI(IDS_CONNECT, OnUpdateNotRemote)
	ON_COMMAND(IDM_100TRANSACT, On100transact)
	ON_COMMAND(IDM_1000DELETES, On1000deletes)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_REMOVEARECORD, OnUpdateRemote)
	ON_COMMAND(IDM_BATCH, OnBatch)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_VIEWCONTENTS, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(IDS_DISCONNECT, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(ID_REMOTEACCESS_ADDARECORD, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(IDM_1000DELETES, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(IDM_BATCH, OnUpdateRemote)
	ON_UPDATE_COMMAND_UI(IDM_100TRANSACT, OnUpdateRemote)
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


void CSecCliView::OnUpdateRemote(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_iOperationMode & OPERATION_MODE_REMOTE));
}

#include "dbdialog.h"


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


void CSecCliView::OnUpdateNotRemote(CCmdUI* pCmdUI) 
{
 pCmdUI->Enable(!(m_iOperationMode & OPERATION_MODE_REMOTE));
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

#define DELAY 10

void CSecCliView::On100transact() 
{
 LARGE_INTEGER liStart,liEnd;
 for (int iLoop=0;iLoop<TRANSACTIONS;iLoop++)
 {
  m_clStuff[iLoop].iSecuredElement=rand();
  m_clStuff[iLoop].iInsecuredElement=rand();
 };
 m_liAddSum.LowPart=m_liAddSum.HighPart=0;
 for (iLoop=0;iLoop<TRANSACTIONS;iLoop++)
  {
  QueryPerformanceCounter(&liStart);
  m_cpDB->AddData(&m_iIndices[iLoop],&m_clStuff[iLoop]);
  QueryPerformanceCounter(&liEnd);
  // This is to allow clients to overlap their
  // transactions
  Sleep(rand()%DELAY);
  m_liAddSum.HighPart=liEnd.HighPart-liStart.HighPart;
  m_liAddSum.LowPart=liEnd.LowPart-liStart.LowPart;
  };
 sprintf(m_szBuf,"Performance adding records: average %d %8ld, sum %d %8ld",
         m_liAddSum.HighPart/TRANSACTIONS,m_liAddSum.LowPart/TRANSACTIONS,
         m_liAddSum.HighPart,m_liAddSum.LowPart);
 AddStringandAdjust(m_szBuf);	
}

void CSecCliView::On1000deletes() 
{
 LARGE_INTEGER liStart,liEnd;
 m_liDeleteSum.LowPart=m_liDeleteSum.HighPart=0;
 for (int iLoop=0;iLoop<TRANSACTIONS;iLoop++)
 {
  QueryPerformanceCounter(&liStart);
  m_cpDB->RemoveData(m_iIndices[iLoop]);
  QueryPerformanceCounter(&liEnd);

  // This is to allow clients to overlap their
  // transactions
  Sleep(rand()%DELAY);
  m_liDeleteSum.HighPart=liEnd.HighPart-liStart.HighPart;
  m_liDeleteSum.LowPart=liEnd.LowPart-liStart.LowPart;
  };
 sprintf(m_szBuf,"Performance deleting records: average %d %8ld, sum %d %8ld",
         m_liDeleteSum.HighPart/TRANSACTIONS,m_liDeleteSum.LowPart/TRANSACTIONS,
         m_liDeleteSum.HighPart,m_liDeleteSum.LowPart);
 AddStringandAdjust(m_szBuf);		
}

#define BATCHRUNS 10

void CSecCliView::OnBatch() 
{ LARGE_INTEGER liAdd,liDelete;
  liAdd.LowPart=liAdd.HighPart=0;
  liDelete.LowPart=liDelete.HighPart=0;
	for (int iLoop=0; iLoop<BATCHRUNS; iLoop++)
    {
     On100transact();
     liAdd.LowPart+=m_liAddSum.LowPart;
     liAdd.HighPart+=m_liAddSum.HighPart;
     On1000deletes();
     liDelete.LowPart+=m_liDeleteSum.LowPart;
     liDelete.HighPart+=m_liDeleteSum.HighPart;
    };
  sprintf(m_szBuf,"overall performance adding: %d %8ld",
     liAdd.HighPart,liAdd.LowPart);
  AddStringandAdjust(m_szBuf);
  sprintf(m_szBuf,"overall performance deleting: %d %8ld",
     liDelete.HighPart,liDelete.LowPart);
  AddStringandAdjust(m_szBuf);
}

void CSecCliView::OnInitialUpdate() 
{
	CEasyOutputView::OnInitialUpdate();
	
}

