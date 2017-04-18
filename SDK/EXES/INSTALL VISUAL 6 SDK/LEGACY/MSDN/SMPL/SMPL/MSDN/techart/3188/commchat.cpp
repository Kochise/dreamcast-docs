// commchat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "comclass.h"
#include "npipe.h"
#include "sockets.h"
#include "netbios.h"

#include "protocol.h"


#include "commchat.h"

#include "mainfrm.h"
#include "commcdoc.h"
#include "commcvw.h"
#include "subsplit.h"
#include "splitfrm.h"

#include "browsedi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommchatApp

BEGIN_MESSAGE_MAP(CCommchatApp, CWinApp)
	//{{AFX_MSG_MAP(CCommchatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(ID_STARTCHATCOMM, OnStartChatComm)         
    ON_COMMAND(ID_STARTTRANSFERCOMM, OnStartTransferComm)
	ON_COMMAND(ID_FILE_TRANSFERAFILE, OnFileTransferafile)
	ON_COMMAND(ID_SELECTCOMMUNICATION_NAMEDPIPES, OnSelectcommunicationNamedpipes)
	ON_COMMAND(ID_FILE_OPENACHATCOMMUNICATION, OnFileOpenachatcommunication)
	ON_COMMAND(ID_SELECTCOMMUNICATION_WINSOCKETS, OnSelectcommunicationWinsockets)
	ON_COMMAND(ID_SELECTCOMMUNICATION_NETBIOS, OnSelectcommunicationNetbios)
	//}}AFX_MSG_MAP
	// Standard file based document commands
//	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommchatApp construction

CCommchatApp::CCommchatApp()
{
  m_iCommunicationType = NO_COMMUNICATION;
}

CCommchatApp::~CCommchatApp()
{ 
};

int CCommchatApp::ExitInstance()
{
if (m_iCommunicationType != NO_COMMUNICATION)
 {
  ::TerminateThread(m_hListenThread,0);
  m_ServerReadObject->Close();
  m_ServerWriteObject->Close();
  ::CloseHandle(m_hListenThread);
  delete m_ServerReadObject;
  delete m_ServerWriteObject;
 };
return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CCommchatApp object

CCommchatApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CCommchatApp initialization

BOOL CCommchatApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

    GetSystemInfo(&si);
	SetDialogBkColor();        // set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	AddDocTemplate(new CMultiDocTemplate(IDR_COMMCHTYPE,
			RUNTIME_CLASS(CCommchatDoc),
			RUNTIME_CLASS(csplitframe),        // standard MDI child frame
			RUNTIME_CLASS(CWriterView)));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	m_pMainWnd = pMainFrame;

	// create a new (empty) document
//	OnFileNew();	// only do this when File New is selected...
	  m_MachineNameLength = MAX_COMPUTERNAME_LENGTH+1;
    GetComputerName(m_MachineName,&m_MachineNameLength);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCommchatApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCommchatApp commands

BOOL CCommchatApp::SetupCommunicationObjects(int iType)
{
// be a little careful here -- in "real life," we would need to set aside
// space for all server objects here; maybe later on, we should create the
// server objects on demand...
switch (iType)
{ case COMMUNICATION_NAMEDPIPE: 
       m_ServerReadObject = new CServerNamedPipe("chatread","chatwrit","chatboth");
       m_ServerWriteObject = new CServerNamedPipe("chatread","chatwrit","chatboth");
	   break;
case COMMUNICATION_SOCKET: 
       m_ServerReadObject = new CServerSocket();
       m_ServerWriteObject = new CServerSocket();
	   break;
case COMMUNICATION_NETBIOS:
       m_ServerReadObject = new CServerNetBIOS();
       m_ServerWriteObject = new CServerNetBIOS();
	   break;


  default: 
       {AfxMessageBox("sorry, type not implemented yet...");
	    return FALSE;
	   };
};
if (!(m_ServerWriteObject->Open(NULL,CFile::modeWrite) &&
      m_ServerReadObject->Open(NULL,CFile::modeRead)))
     { delete m_ServerWriteObject;
	   delete m_ServerReadObject;
	   return FALSE;
	 };
return TRUE;

}

// this member function requests a communication with another machine.
// A NULL argument implies that we are the server and have received a
// request from another machine.

BOOL CCommchatApp::OpenCommunication(const char *pszMachineName, BOOL bAreWeServer)
{ CCommchatDoc* pDocument;
  CDocTemplate* pTemplate = (CDocTemplate*)m_templateList.GetHead();
 // let's first check to see if a communication type has been selected...
  if (m_iCommunicationType == NO_COMMUNICATION)
     { AfxMessageBox("you must select a communication type first!");
	   return FALSE;
	 };
  if (bAreWeServer)
// this is called in response to a remote machine docking... watch out though,
// the protocol should have been set up earlier (AwaitCommunicationAttempt
// should already have been called into the protocol, not the communication...

	 {
      CServerChatProtocol *csProtocol;
      CString *csName;
	  csProtocol=
	       new CServerChatProtocol(m_ServerReadObject->Duplicate(),
	                         m_ServerWriteObject->Duplicate());
	  if (!csProtocol->InitiateConversationAsServer(&csName))
		  {delete csProtocol;
		   SetupListeningThread();
		   return FALSE;
		  };
	  pDocument=(CCommchatDoc *)pTemplate->OpenDocumentFile((const char *)*csName);
	  return (pDocument->SetReaderCommunicationObject(csProtocol,TRUE));
	 };

// we are client...   
  CClientCommunication *csReader,*csWriter;
  CClientChatProtocol *csProtocol;

  switch (m_iCommunicationType)
  { case COMMUNICATION_NAMEDPIPE:
       csReader = new CClientNamedPipe("chatread","chatwrit","chatboth");
       csWriter = new CClientNamedPipe("chatread","chatwrit","chatboth");
	   break;
   case COMMUNICATION_SOCKET: 
       csReader = new CClientSocket();
       csWriter = new CClientSocket();
	   break;
   case COMMUNICATION_NETBIOS: 
       csReader = new CClientNetBIOS();
       csWriter = new CClientNetBIOS();
	   break;

	default: 
	   return FALSE;
  };
   if (csReader->Open(pszMachineName,CFile::modeRead)
	  &&
	  (csWriter->Open(pszMachineName,CFile::modeWrite)))
	 {CClientSelectorProtocol *csProt;
	  csProt = new CClientSelectorProtocol(csReader,csWriter);
	  csProt->SetCommunicationType(CHATTYPE);
	  delete csProt;
	  csProtocol = new CClientChatProtocol(csReader,csWriter);
	  if (csProtocol->InitiateConversationAsClient
	           (m_MachineName,m_MachineNameLength))
	    {pDocument=(CCommchatDoc *)pTemplate->OpenDocumentFile(pszMachineName);
	  	 if (pDocument->SetReaderCommunicationObject(csProtocol,FALSE))
          return TRUE;
	    };
	  delete csProtocol;
	  return FALSE;
	 };
// general failure
     delete csReader;
	 delete csWriter;
     return FALSE;
	
}


CString *CCommchatApp::GetNextMachineName(const char *csArg)
{
// later on, this will be replaced by a nice little browse dialog...
CBrowseDialog cbd;
cbd.m_Title=csArg;
if (cbd.DoModal()==IDCANCEL) return new CString("");
return new CString(cbd.m_TargetName);
}


long WINAPI ListenThreadFn(CCommchatApp *cvTarget)
{
// this thread terminates by outside force (call to TerminateThread())
    int iCommunicationType;
    CServerSelectorProtocol *csProt;
    cvTarget->m_ServerWriteObject->AwaitCommunicationAttempt();
    cvTarget->m_ServerReadObject->AwaitCommunicationAttempt();
	csProt = new CServerSelectorProtocol(cvTarget->m_ServerReadObject,cvTarget->m_ServerWriteObject);
	iCommunicationType = csProt->GetCommunicationType();
    delete csProt;
	switch (iCommunicationType)
	 { case TRANSFERTYPE:
	    cvTarget->m_pMainWnd->PostMessage(WM_COMMAND,ID_STARTTRANSFERCOMM,NULL);
		break;
	   case CHATTYPE:
        cvTarget->m_pMainWnd->PostMessage(WM_COMMAND,ID_STARTCHATCOMM,NULL);
	    break;
	  };
// here allow for multiple communications...
  return(0);
};


BOOL CCommchatApp::SetupListeningThread()
{ unsigned long iThread;
  if (m_iCommunicationType == NO_COMMUNICATION) return FALSE;
  ::CloseHandle(m_hListenThread); // this will fail on the first invocation,
                                // but no big deal...
      m_hListenThread=
       ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ListenThreadFn,
           (void *)this,0,&iThread);

// watch out here: 
return (m_hListenThread != INVALID_HANDLE_VALUE);
}


void CCommchatApp::OnStartTransferComm()
{
	// TODO: Add your command handler code here
    OpenCommunicationForTransfer(NULL,TRUE);
	
}


void CCommchatApp::OnStartChatComm()
{
	// TODO: Add your command handler code here
    OpenCommunication(NULL,TRUE);
	
}

// called by the client side

void CCommchatApp::OnFileTransferafile()
{CString *csNextMachine;
 iCurrentMachineEntry = -1;
 csNextMachine=GetNextMachineName("transfer a file to machine");
  if (*csNextMachine == "") return;	 
	 if (!OpenCommunicationForTransfer((const char *)*csNextMachine,FALSE))
	    AfxMessageBox("Could not establish communication...");
		 delete csNextMachine;
}

BOOL CCommchatApp::OpenCommunicationForTransfer(const char *csNextMachine, BOOL bAreWeServer)
{ BOOL bRetVal = FALSE; 

 if (bAreWeServer)
  {	  
      CServerFileTransferProtocol *csProtocol;
	  csProtocol=
	       new CServerFileTransferProtocol(m_ServerReadObject->Duplicate(),
	                                 m_ServerWriteObject->Duplicate());
	  bRetVal = (csProtocol->Open(NULL,0) && DoTheFileReceive(csProtocol));
	delete csProtocol;
    SetupListeningThread();
	if (!bRetVal)
	 AfxMessageBox("file receive failes!");
	 else AfxMessageBox("file receive completed!");
	return bRetVal;
  }
  else
  {
  CClientCommunication *csReader,*csWriter;
  switch (m_iCommunicationType)
  { case COMMUNICATION_NAMEDPIPE:
       csReader = new CClientNamedPipe("chatread","chatwrit","chatboth");
       csWriter = new CClientNamedPipe("chatread","chatwrit","chatboth");
	   break;
    case COMMUNICATION_SOCKET: 
       csReader = new CClientSocket();
       csWriter = new CClientSocket();
	   break;
    case COMMUNICATION_NETBIOS:
       csReader = new CClientNetBIOS();
       csWriter = new CClientNetBIOS();
	   break;

	default: 
	   return FALSE;
  };

    if (csReader->Open(csNextMachine,CFile::modeRead)
	  &&
	  (csWriter->Open(csNextMachine,CFile::modeWrite)))

	 {CClientSelectorProtocol *csProt;
	  csProt = new CClientSelectorProtocol(csReader,csWriter); // will be deleted implicitly
	  csProt->SetCommunicationType(TRANSFERTYPE);
	  delete csProt; 
	  CClientFileTransferProtocol *csProtocol;
	  csProtocol = new CClientFileTransferProtocol(csReader,csWriter);
	  bRetVal = (csProtocol->Open(m_MachineName,m_MachineNameLength) && DoTheFileTransfer(csProtocol));
	  delete csProtocol;
     }
	 else
	 {bRetVal = FALSE;
	  delete csReader;
	  delete csWriter;
	 };
  };
   if (!bRetVal) AfxMessageBox("file transfer failed!");
   else AfxMessageBox("file transfer completed!");
     return bRetVal;

}

#define MAXBUFSIZE 4096	


BOOL CCommchatApp::DoTheFileTransfer(CFileTransferProtocol *csProtocol)
{  CFile cfSource;
   BOOL bVerifyOurSide = TRUE;
   BOOL bVerifyTheirSide = FALSE;
   HANDLE hFileMapping;
 															  
   CFileDialog  csDialog(TRUE);
   csDialog.m_ofn.lpstrFilter = "All files\0*.*\0\0";
   csDialog.m_ofn.lpstrTitle = "Select file to transfer";
   csDialog.m_ofn.Flags |= OFN_FILEMUSTEXIST;
   if (IDOK != csDialog.DoModal())
     bVerifyOurSide = FALSE;
   else
    { if (!cfSource.Open(csDialog.GetPathName(),CFile::modeReadWrite))
      bVerifyOurSide = FALSE;
	};
	bVerifyTheirSide = csProtocol->LastMinuteCheckSender(bVerifyOurSide);
    if (bVerifyTheirSide)
	 {int iFileSize;
	  hFileMapping=CreateFileMapping((HANDLE)cfSource.m_hFile,NULL,PAGE_READWRITE,0,0,NULL);
	   iFileSize=cfSource.GetLength();
	   csProtocol->SetLength(iFileSize);
	  int iLoop = 0;
    LPVOID lpFileMap = MapViewOfFile(hFileMapping,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
		if (lpFileMap == (LPVOID) 0)
		    {GetLastError();
			 CloseHandle(hFileMapping);
			 return FALSE;
			};
     TRY
	   {
       csProtocol->Write(lpFileMap,iFileSize);
	   }
	  CATCH (CFileException, theException)
	  { LPVOID lpMessageBuffer;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,
	    theException->m_cause, MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),(LPTSTR)&lpMessageBuffer,0,NULL);
	    ::MessageBox(m_pMainWnd->m_hWnd,(const char *)lpMessageBuffer,"File transfer failed with the following system error:",MB_OK);
	    HLOCAL hMem = LocalHandle(lpMessageBuffer);
	    LocalUnlock(lpMessageBuffer);
	    LocalFree(lpMessageBuffer);
		bVerifyTheirSide = FALSE;
      };

	  END_CATCH
	   UnmapViewOfFile(lpFileMap);
	};
    if (bVerifyOurSide)
      {CloseHandle(hFileMapping);
       cfSource.Close();
	  };
	
  return bVerifyTheirSide;
}

BOOL CCommchatApp::DoTheFileReceive(CFileTransferProtocol *csProtocol)
{ CFile cfTarget;
  BOOL bVerifyOurSide = TRUE;
  BOOL bVerifyTheirSide = FALSE;
// here display the file save box, grab the file etc.
     CFileDialog csDialog(FALSE);
     csDialog.m_ofn.lpstrFilter = "All files\0*.*\0\0";
     csDialog.m_ofn.lpstrTitle = "Select file name to receive";

	 if (csDialog.DoModal() != IDOK)
	  	bVerifyOurSide = FALSE;
	 else
	   {
        if (!cfTarget.Open(csDialog.GetPathName(),CFile::modeWrite|CFile::modeCreate))
		    bVerifyOurSide = FALSE;
	   };
	 bVerifyTheirSide = csProtocol->LastMinuteCheckReceiver(bVerifyOurSide);
// we read at most MAXBUFSIZE characters...
if (bVerifyTheirSide)
{int iFileSize = csProtocol->GetLength();
 int iLoop = 0;
 HLOCAL hBuf;
 char *szBuf;

 hBuf=LocalAlloc(LPTR,iFileSize);
 szBuf = (char *)LocalLock(hBuf);
       TRY
	   {
        csProtocol->Read(szBuf,iFileSize); 
	    cfTarget.Write(szBuf,iFileSize);

	   }
	  CATCH (CFileException, theException)
	  { LPVOID lpMessageBuffer;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,
	    theException->m_cause, MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),(LPTSTR)&lpMessageBuffer,0,NULL);
	    ::MessageBox(m_pMainWnd->m_hWnd,(const char *)lpMessageBuffer,"File receive failed with the following system error:",MB_OK);
	    LocalFree(lpMessageBuffer);
		bVerifyTheirSide = FALSE;
      };

	  END_CATCH
 LocalUnlock(hBuf);
 LocalFree(hBuf);
    
   
};
if (bVerifyOurSide) cfTarget.Close();
   return bVerifyTheirSide;
} 	

void CCommchatApp::OnSelectcommunicationNetbios() 
{ 
InitializeCommunications(COMMUNICATION_NETBIOS);
};

void CCommchatApp::OnSelectcommunicationWinsockets() 
{
InitializeCommunications(COMMUNICATION_SOCKET);
};

void CCommchatApp::OnSelectcommunicationNamedpipes() 
{
InitializeCommunications(COMMUNICATION_NAMEDPIPE);
};

void CCommchatApp::InitializeCommunications(int iType)
{
if (m_iCommunicationType != NO_COMMUNICATION)
  {AfxMessageBox("you have already selected a communication type...");
   return;
  };
    if (!SetupCommunicationObjects(iType))
	  {AfxMessageBox("could not create server communication objects...");
	   return;
	  };
m_iCommunicationType = iType;

    if (!SetupListeningThread())
      AfxMessageBox("Could not create listening thread");

};

void CCommchatApp::OnFileOpenachatcommunication() 
{
    iCurrentMachineEntry=-1;

CString *csNextMachine;
csNextMachine=GetNextMachineName("Open a chat communication with");
     if (*csNextMachine=="") return;
	 if (!OpenCommunication((const char *)*csNextMachine,FALSE))
	    AfxMessageBox("Could not establish communication...");
	 delete csNextMachine;	 


	// TODO: Add your command handler code here
	
}


