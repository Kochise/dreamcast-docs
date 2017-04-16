// commchat.h : main header file for the COMMCHAT application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CServerCommunication;
class CFileTransferProtocol;

// this list should be updated for all the object typed we provide

#define NO_COMMUNICATION 0
#define COMMUNICATION_NAMEDPIPE 1
#define COMMUNICATION_SOCKET 2
#define COMMUNICATION_NETDDE 3
#define COMMUNICATION_NETBIOS 4
#define COMMUNICATION_DLC 5

/////////////////////////////////////////////////////////////////////////////
// CCommchatApp:
// See commchat.cpp for the implementation of this class
//

class CCommchatApp : public CWinApp
{
private:
    HANDLE m_hListenThread;
	char m_MachineName[MAX_COMPUTERNAME_LENGTH+1];
	unsigned long m_MachineNameLength;
    int iCurrentMachineEntry;
    SYSTEM_INFO si;
	int m_iCommunicationType;


public:

    CString *GetNextMachineName(const char *);


    CServerCommunication *m_ServerReadObject;
	CServerCommunication *m_ServerWriteObject;
	CCommchatApp();
    ~CCommchatApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();
    BOOL SetupCommunicationObjects(int iType);
    BOOL SetupListeningThread();
	BOOL OpenCommunication(const char *pszMachineName, BOOL bAreWeServer);
	BOOL OpenCommunicationForTransfer(const char *csNextMachine, BOOL bAreWeServer);
	BOOL DoTheFileTransfer(CFileTransferProtocol *csProtocol);
    BOOL DoTheFileReceive(CFileTransferProtocol *csProtocol);
	void InitializeCommunications(int);


// Implementation

	//{{AFX_MSG(CCommchatApp)
	afx_msg void OnAppAbout();
    afx_msg void OnStartChatComm();         
    afx_msg void OnStartTransferComm();
	afx_msg void OnFileTransferafile();
	afx_msg void OnSelectcommunicationNamedpipes();
	afx_msg void OnFileOpenachatcommunication();
	afx_msg void OnSelectcommunicationWinsockets();
	afx_msg void OnSelectcommunicationNetbios();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
