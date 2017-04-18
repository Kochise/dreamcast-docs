///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      COMWINDS.CPP
//
//  Description
//      This file implement the RPC code to talk to the WINDS Sample Server
//      Messaging Host.
//      Here we also implement common code used by providers in the service
//      that talking to WINDS and that share similiar configuration UI.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "COMWINDS.H"

// Remark this line to turn verbose tracing OFF
#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)   
#endif // DO_INFO_TRACES

typedef struct tagSELECTED_MAILBOX_INFO
{
    HANDLE  hPipe;
    HRESULT hLastError;
    LPTSTR  szMailBoxName;
    LPTSTR  szDisplayName;
    LPTSTR  szPassword;
    DWORD * pdwMailboxID;
} SELECTED_MAILBOX_INFO;

HINSTANCE ghUIControl = NULL;
typedef BOOL (WINAPI CTL3DFUNCTION) (HINSTANCE hInstance);
typedef CTL3DFUNCTION *LPCTL3DFUNCTION;
typedef BOOL (WINAPI CTL3DSUBCLASS) (HWND hDlg, DWORD dwFlags);
typedef CTL3DSUBCLASS *LPCTL3DSUBCLASS;

LPCTL3DFUNCTION pfn3DRegister = NULL, pfn3DUnregister = NULL, pfn3DAutoSubclass = NULL;
LPCTL3DSUBCLASS pfnDlgSubclassEx = NULL;

LPFREEBUFFER pfnMAPIFreeBuffer;

extern "C"
{
    void STDAPICALLTYPE BrowseMailboxes
                    (CUIMAPIProp *              pObj,
                     HWND                       hOwnerWnd,
                     HINSTANCE                  hInstance);
    void STDAPICALLTYPE ConfigChangePassword
                    (CUIMAPIProp *              pObj,
                     HWND                       hOwnerWnd,
                     HINSTANCE                  hInstance);
    HRESULT WINAPI ShowServerAccounts
                    (HWND                       hOwnerWnd,
                     HINSTANCE                  hInstance,
                     LPTSTR                     szServerName,
                     LPTSTR                     szMailboxName,
                     LPTSTR                     szFullName,
                     LPTSTR                     szPassword,
                     DWORD *                    pdwMailboxID);
    BOOL CALLBACK PasswordDlgProc
                    (HWND                       hDlg,
                     UINT                       message,
                     WPARAM                     wParam, 
                     LPARAM                     lParam);
    BOOL CALLBACK EnterMBPasswordDlgProc
                    (HWND                       hDlg,
                     UINT                       message,
                     WPARAM                     wParam, 
                     LPARAM                     lParam);
    BOOL CALLBACK SelectMailBoxDlgProc
                    (HWND                       hDlg,
                     UINT                       message,
                     WPARAM                     wParam, 
                     LPARAM                     lParam);
    void WINAPI TogglePage
                    (HWND                       hDlg,
                     UINT                       iPage,
                     BOOL                       fState);                    
    HRESULT WINAPI LogonServerMailbox
                    (LPTSTR                     szServerName,
                     LPTSTR                     szMailboxName,
                     LPTSTR                     szDisplayName,
                     LPTSTR                     szPassword,
                     DWORD *                    pdwMailboxID);
};

HRESULT WINAPI LogonServerMailboxAndSetNotif
                    (LPTSTR                     szServerName,
                     LPTSTR                     szMailboxName,
                     LPTSTR                     szDisplayName,
                     LPTSTR                     szPassword,
                     DWORD *                    pdwMailboxID,
                     DWORD                      dwNotifMask,
                     DWORD &                    dwConnectID);

// Static data for the transport provider configuration property sheets
TCHAR szFilter[] = TEXT("*"); // "*" to allow any character
TCHAR szTimeFilter[] = TEXT("[0-9:]");
TCHAR szPhoneFilter[] = TEXT("[0-9-]");
TCHAR szBlank[] = TEXT("");

extern TCHAR gszProviderName[];

// Control description structures
DTBLLABEL       DtLabel      = { sizeof(DTBLLABEL),       fMapiUnicode};
DTBLGROUPBOX    DtGroupBox   = { sizeof(DTBLGROUPBOX),    fMapiUnicode};
DTBLPAGE        DtPage       = { sizeof(DTBLPAGE),        fMapiUnicode};
DTBLEDIT        DtServer     = { sizeof(DTBLEDIT),        fMapiUnicode, MAX_STRING_SIZE, PR_SMP_REMOTE_SERVER};
DTBLEDIT        DtUserName   = { sizeof(DTBLEDIT),        fMapiUnicode, MAX_STRING_SIZE, PR_SMP_USER_NAME};
DTBLEDIT        DtMBAlias    = { sizeof(DTBLEDIT),        fMapiUnicode, MAX_ALIAS_SIZE,  PR_SMP_MAILBOX_NAME};
DTBLBUTTON      DtBrowseMB   = { sizeof(DTBLBUTTON),      fMapiUnicode, PR_SMP_BROWSE_MB};
DTBLBUTTON      DtChangePW   = { sizeof(DTBLBUTTON),      fMapiUnicode, PR_SMP_CHANGE_PASSWORD};
DTBLRADIOBUTTON DtLANConnect = { sizeof(DTBLRADIOBUTTON), fMapiUnicode, 2, PR_SMP_CONNECTION_TYPE, LAN_CONNECT };
DTBLRADIOBUTTON DtREMConnect = { sizeof(DTBLRADIOBUTTON), fMapiUnicode, 2, PR_SMP_CONNECTION_TYPE, OFFLINE_CONNECT };

// Keys for field the we are going to update dynamically and we
// want MAPI's property pages to pick the changes on thes
#define ALIAS_KEY_VALUE     "UI_CONTROL_ALIAS"
#define ALIAS_KEY           ((LPBYTE)ALIAS_KEY_VALUE)
#define CB_ALIAS_KEY        sizeof(ALIAS_KEY_VALUE)

#define NAME_KEY_VALUE      "UI_CONTROL_NAME"
#define NAME_KEY            ((LPBYTE)NAME_KEY_VALUE)
#define CB_NAME_KEY         sizeof(NAME_KEY_VALUE)

// Description table for the controls
DTCTL UserConfigPage[] =
{
    { DTCT_PAGE,        0,           NULL,      0,            NULL,     0,                   &DtPage       },
    { DTCT_EDIT,        DT_REQUIRED, NULL,      0,            szFilter, IDC_SERVERNAME,      &DtServer     },
    { DTCT_EDIT,        DT_REQUIRED, ALIAS_KEY, CB_ALIAS_KEY, szFilter, IDC_MAILBOXNAME,     &DtMBAlias    },
    { DTCT_BUTTON,      0,           NULL,      0,            NULL,     IDC_BROWSE_MB,       &DtBrowseMB   },
    { DTCT_EDIT,        DT_REQUIRED, NAME_KEY,  CB_NAME_KEY,  szFilter, IDC_USER_NAME,       &DtUserName   },
    { DTCT_BUTTON,      0,           NULL,      0,            NULL,     IDC_CHANGE_PASSWORD, &DtChangePW   },
    { DTCT_RADIOBUTTON, DT_SET_IMMEDIATE,NULL,  0,            NULL,     IDC_CONNECT_ONLINE,  &DtLANConnect },
    { DTCT_RADIOBUTTON, DT_SET_IMMEDIATE,NULL,  0,            NULL,     IDC_CONNECT_OFFLINE, &DtREMConnect },
    { DTCT_LABEL,       0,           NULL,      0,            NULL,     IDC_STATIC1,         &DtLabel      },
    { DTCT_LABEL,       0,           NULL,      0,            NULL,     IDC_STATIC2,         &DtLabel      },
    { DTCT_GROUPBOX,    0,           NULL,      0,            NULL,     IDC_STATIC3,         &DtGroupBox   },
    { DTCT_GROUPBOX,    0,           NULL,      0,            NULL,     IDC_STATIC4,         &DtGroupBox   },
    { DTCT_GROUPBOX,    0,           NULL,      0,            NULL,     IDC_STATIC5,         &DtGroupBox   }
};

// Global data used in the WizardDlgProc function
LPMAPIPROP pPropObj = NULL;
BOOL fInitalizeControls, fDownloadMBList;

extern "C"
{
    HINSTANCE            ghInstance = NULL;
    WIZARDENTRY          WizardEntry;    
    SERVICEWIZARDDLGPROC WizardDlgProc;   
};

///////////////////////////////////////////////////////////////////////////////
//    IsWINDSServerAvailable()
//
//    Parameters
//      szServer        Pointer to a string with the name of the remote
//                      server to verify
//
//    Purpose
//      This functions makes remote procedure call to a server to make sure
//      the remote machine is available.
//      The remote server must be running the WINDS sample server messaging
//      host because that is the server procedure that will answer the
//      RPC call.
//
//    Return Value
//      TRUE if the server was found, FALSE otherwise.
//
BOOL WINAPI IsWINDSServerAvailable (LPTSTR szServer)
{
    // We the user didn't supply a server, then fail.
    if (!szServer)
    {
        TraceMessage ("IsWINDSServerAvailable: No server name?");
        return FALSE;
    }
    HCURSOR hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
    // Before we make an RPC call, we must initialize the RPC runtime
    // binding handle with the server
    HRESULT hResult = BindToServer (szServer);
    if (!hResult)
    {
        RpcTryExcept
        {
            // Call the server.
            hResult = RemoteIsServerRunning();
        }
        RpcExcept(1)
        {
            // If we got here is because there was an error while call was made
            // or when it was about to be made.
            hResult = RpcExceptionCode();
            if (RPC_S_SERVER_UNAVAILABLE == hResult)
            {
                hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
            }
            else
            {
                hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
            }
        }
        RpcEndExcept
        TraceResult ("IsWINDServerAvailable", hResult);
    }
    SetCursor (hCursor);
    return (S_OK == hResult ? TRUE : FALSE);
}

///////////////////////////////////////////////////////////////////////////////
//    ShowServerAccounts()
//
//    Parameters
//      hOwnerWnd       Handle to a parent window. If NULL we don't display a
//                      list of available mailboxes in the server.
//      hInstance       Handle to the instance of the DLL where the dialog
//                      resource is located
//      szServerName    Name of the server we are going to make an RPC call to
//      szMailboxName   Where we return the name of the mailbox selected.
//      szFullName      Where we return the name of the owner of the
//                      mailbox seleted.
//      szPassword      Where we return the password of the mailbox seleted
//      pdwMailboxID    Where we return the ID of the mailbox seleted
//
//    Purpose
//      This function displays a list of available mailboxes in the server.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI ShowServerAccounts (HWND        hOwnerWnd,
                                   HINSTANCE   hInstance,
                                   LPTSTR      szServerName,
                                   LPTSTR      szMailboxName,
                                   LPTSTR      szFullName,
                                   LPTSTR      szPassword,
                                   DWORD *     pdwMailboxID)
{
    ASSERT (hOwnerWnd);
    ASSERT (hInstance);
    ASSERT (szServerName);
    ASSERT (szMailboxName);
    ASSERT (szFullName);
    ASSERT (szPassword);
    ASSERT (pdwMailboxID);
    HRESULT hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    long lPipeNumber;
    HANDLE hPipe;
    TCHAR szPipeName[64];
    SELECTED_MAILBOX_INFO info = { 0 };
    RpcTryExcept
    {
        hResult = RemoteGetAllAccounts (&lPipeNumber);
        if (S_OK == hResult)
        {
            wsprintf (szPipeName, PIPE_NAME_FORMAT, szServerName, lPipeNumber);
            hPipe = CreateFile (szPipeName,
                                GENERIC_READ,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                TraceResult ("ShowServerAccounts: Failed to open pipe to server", hResult);
            }
            else
            {
                info.hPipe = hPipe;
                info.hLastError = E_FAIL;
                info.szDisplayName = szFullName;
                info.szMailBoxName = szMailboxName;
                info.szPassword = szPassword;
                info.pdwMailboxID = pdwMailboxID;
                hResult = DialogBoxParam (hInstance,
                                          MAKEINTRESOURCE(IDD_SELECTMB),
                                          hOwnerWnd,
                                          SelectMailBoxDlgProc,
                                          (LPARAM)&info);
                if (-1 == hResult)
                {
                    hResult = info.hLastError;
                }
                else
                {
                    if (FALSE == hResult)
                    {
                        hResult = MAPI_E_USER_CANCEL;
                    }
                    else
                    {
                        hResult = S_OK;
                    }
                }
                CloseHandle (hPipe);
            }
        }
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("ShowServerAccounts", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    LogonServerMailbox()
//
//    Parameters
//      szServerName        Name of the server where are connecting to.
//      szMailboxName       Name of the mailbox we are attempting to access
//      szDisplayName       Name of the owner of the mailbox
//      szPassword          Password to access the mailbox
//      pdwMailboxID        Where we return the ID of the mailbox as stored
//                          on the server
//
//    Purpose
//      This function makes a connection to the remote server and makes sure
//      we can access it with the given password. Upon success, the remote
//      call returns us the full name of the owner of the mailbox and the
//      ID of the recipient.
//      
//    Return Value
//      An HRESULT
//
HRESULT WINAPI LogonServerMailbox (LPTSTR   szServerName,
                                   LPTSTR   szMailboxName,
                                   LPTSTR   szDisplayName,
                                   LPTSTR   szPassword,
                                   DWORD *  pdwMailboxID)
{
    ASSERT (szServerName);
    ASSERT (szMailboxName);
    ASSERT (szDisplayName);
    ASSERT (szPassword);
    ASSERT (pdwMailboxID);
    HRESULT hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteLogonMailBox ((WINDS_RPC_STRING)szMailboxName,
                                      (WINDS_RPC_STRING)szPassword,
                                      (WINDS_RPC_STRING)szDisplayName,
                                      pdwMailboxID);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("LogonServerMailbox", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    LogonServerMailboxAndSetNotif()
//
//    Parameters
//      szServerName       Name of the server where are connecting to.
//      szMailboxName      Name of the mailbox we are attempting to access
//      szDisplayName      Name of the owner of the mailbox
//      szPassword         Password to access the mailbox
//      pdwMailboxID        Where we return the ID of the mailbox as stored
//                          on the server
//      dwNotifMask         Mask of events the loggin service is intersted in.
//      dwConnectID         Where we return the connection number the server
//                          assigned to us.
//
//    Purpose
//      In addition to what LogonServerMailbox() does, this function also
//      instructs the remote server to set up a notification link with us
//      to advise us of changes in the server's data or the server state.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI LogonServerMailboxAndSetNotif (LPTSTR    szServerName,
                                              LPTSTR    szMailboxName,
                                              LPTSTR    szDisplayName,
                                              LPTSTR    szPassword,
                                              DWORD *   pdwMailboxID,
                                              DWORD     dwNotifMask,
                                              DWORD &   dwConnectID)
{
    ASSERT (szServerName);
    ASSERT (szMailboxName);
    ASSERT (szDisplayName);
    ASSERT (szPassword);
    ASSERT (pdwMailboxID);

    // Get the computer name of us (the client) so that the server can
    // create the mailslot name appropiately.
    TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    HRESULT hResult;
    DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
    if (!GetComputerName (szComputerName, &dwNameSize))
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("LogonServerMailboxAndSetNotif: Failed to get the computer name", hResult);
    }
    else
    {
        hResult = BindToServer (szServerName);
    }
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteLogonMailBoxAndSetNotif ((WINDS_RPC_STRING)szMailboxName,
                                                 (WINDS_RPC_STRING)szPassword,
                                                 (WINDS_RPC_STRING)szDisplayName,
                                                 pdwMailboxID,
                                                 (WINDS_RPC_STRING)szComputerName,
                                                 dwNotifMask,
                                                 &dwConnectID);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("LogonServerMailboxAndSetNotif", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    TerminateServerNotifications()
//
//    Parameters
//      szServerName           Name of the server we want to terminate
//                              connections with.
//      dwConnectionID          Connection ID assigned to us in that server
//
//    Purpose
//      Tell the server that this provider is shutting down an it show remove
//      it from the list of advise clients.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI TerminateServerNotifications (LPTSTR     szServerName,
                                             DWORD      dwConnectionID)
{
    // If the connection is zero, there is nothing to do here.
    if (0 == dwConnectionID)
    {
        return S_OK;
    }
    TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    HRESULT hResult;
    DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
    if (!GetComputerName (szComputerName, &dwNameSize))
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("TerminateServerNotifications: Failed to get the computer name", hResult);
    }
    else
    {
        hResult = BindToServer (szServerName);
    }
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteTerminateNotif ((WINDS_RPC_STRING)szComputerName, dwConnectionID);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("TerminateServerNotifications", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    ResetServerNotifications()
//
//    Parameters
//      szServerName        Name of the remote server
//      szMailboxName       Name of the owner mailbox where the notifations
//                          are set
//      dwNotifMask         Mask of events the service is interested in.
//      pdwConnectionID     Where the server returns the new connection number
//
//    Purpose
//      This function is called in response to a notification sent by the
//      server to advise clients that they need to reset the notification
//      because the old connection is no longer valid.
//      The server send this notification periodically to make sure the advise
//      client he sending notifications to are still around.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI ResetServerNotifications (LPTSTR     szServerName,
                                         LPTSTR     szMailboxName,
                                         DWORD      dwNotifMask,
                                         DWORD *    pdwConnectionID)
{
    // The connections with the server is dead anyways so 0 the connection ID even we fail.
    *pdwConnectionID = 0;
    TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    HRESULT hResult;
    DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
    if (!GetComputerName (szComputerName, &dwNameSize))
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("ResetServerNotifications: Failed to get the computer name", hResult);
    }
    else
    {
        hResult = BindToServer (szServerName);
    }
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteValidateNotif ((WINDS_RPC_STRING)szComputerName,
                                       (WINDS_RPC_STRING)szMailboxName,
                                       dwNotifMask,
                                       pdwConnectionID);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("ResetServerNotifications", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    GetHeadersFromServer()
//
//    Parameters
//      szServerName   Name of the server we are going to make an RPC call to
//      szMailbox      Mailbox for which we are going to retrieve the
//                      headers for.
//      szHeaderFile   The name of the local file where we will copy the
//                      message headers found in the remote mailbox
//
//    Purpose
//      This function makes an RPC call to the remote server host to retrieve
//      the message header information of a particular mailbox. The headers
//      found are save to a local file and then used to fill the contents
//      table of the remote folder object we return to a client remote
//      viewer application.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI GetHeadersFromServer (LPTSTR szServerName,
                                     LPTSTR szMailbox,
                                     LPTSTR szHeaderFile)
{
    HANDLE hFile, hPipe;
    DWORD dwBytesWrite, dwBytesRead;
    BYTE abBuffer[IO_BUFFERSIZE];
    long lPipeNumber;
    HRESULT hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    HCURSOR hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
    RpcTryExcept
    {
        hResult = RemoteOpenHeaderDownloadPipe ((WINDS_RPC_STRING)szMailbox, &lPipeNumber);
        if (S_OK == hResult)
        {
            wsprintf ((LPTSTR)abBuffer, PIPE_NAME_FORMAT,szServerName, lPipeNumber);
            hPipe = CreateFile ((LPTSTR)abBuffer,
                                GENERIC_READ,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                TraceResult ("GetHeadersFromServer: Failed to open pipe to server", hResult);
            }
            else
            {
                hFile = CreateFile (szHeaderFile,
                                    GENERIC_WRITE,
                                    0,
                                    NULL,
                                    CREATE_ALWAYS,
                                    FILE_FLAG_SEQUENTIAL_SCAN,
                                    NULL);
                if (INVALID_HANDLE_VALUE == hFile)
                {
                    hResult = HRESULT_FROM_WIN32(GetLastError());
                    TraceResult ("GetHeadersFromServer: Failed to open local headers file", hResult);
                }
                else
                {
                    do
                    {
                        // Read the pipe handle.
                        if (!ReadFile (hPipe, abBuffer, IO_BUFFERSIZE, &dwBytesRead, NULL))
                        {
                            hResult = HRESULT_FROM_WIN32(GetLastError());
                            if (HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE)   != hResult &&   // For Windows NT
                                HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED) != hResult)     // For Windows 95
                            {
                                // There was an error and we can't continue
                                TraceResult ("GetHeadersFromServer: Failed to read from the pipe", hResult);
                            }
                            else
                            {
                                // If the pipe was broken, it means the server finished writing
                                // to the it, so we are finished reading from it.
                                hResult = S_OK;
                            }
                        }
                        if (dwBytesRead)
                        {
                            if (!WriteFile (hFile, abBuffer, dwBytesRead, &dwBytesWrite, NULL))
                            {
                                hResult = HRESULT_FROM_WIN32(GetLastError());
                                TraceResult ("GetHeadersFromServer: Failed to write to local header file", hResult);
                            }
                        }
                    } while (dwBytesRead && !hResult);
                    CloseHandle (hFile);
                }
                CloseHandle (hPipe);
            }
        }
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    // Terminate connections with the remote server
    BindToServer (NULL);
    SetCursor (hCursor);
    TraceResult ("GetHeadersFromServer", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    OpenServerUploadPipe()
//
//    Parameters
//      hMsgFile            Handle to the local TNEF file with the message to
//                          upload
//      szServerName       String with the name of the remote server
//      szRecipMailbox     String with the name of the mailbox where the
//                          message will be uploaded.
//
//    Purpose
//      This function uploads a file to a server. The file must have been
//      opened by the caller and a handle to it must have been passed in
//      hMsgFile. The function will bind to the server (the name is is
//      szServerName).
//      This functions makes a remote procedure call to a server to request
//      the a pipe to upload the data through.
//      The remote server must be running the WINDS sample server messaging
//      host because that is the server procedure that will answer the
//      RPC call.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI OpenServerUploadPipe (LPTSTR     szServerName,
                                     LPTSTR     szSenderMailbox,
                                     HANDLE     hMsgFile,
                                     LPTSTR     szConnectionInfo,
                                     BOOL *     pfErrorInTheServer)
{
    *pfErrorInTheServer = FALSE;
    HANDLE hPipe;
    char szPipeName[64];
    DWORD dwBytesWrite, dwBytesRead;
    BYTE abBuffer[IO_BUFFERSIZE];
    long lPipeNumber, hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteOpenMsgUploadPipe ((WINDS_RPC_STRING)szSenderMailbox,
                                           &lPipeNumber,
                                           (WINDS_RPC_STRING)szConnectionInfo);
        if (!hResult)
        {
            wsprintf (szPipeName, PIPE_NAME_FORMAT, szServerName, lPipeNumber);
            hPipe = CreateFile (szPipeName,
                                GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                TraceResult ("OpenServerUploadPipe: Failed to open pipe to server", hResult);
            }
            else
            {
                do
                {
                    if (!ReadFile (hMsgFile, abBuffer, IO_BUFFERSIZE, &dwBytesRead, NULL))
                    {
                        hResult = HRESULT_FROM_WIN32(GetLastError());
                        TraceResult ("OpenServerUploadPipe: Failed to read local msg file", hResult);
                    }
                    if (dwBytesRead)
                    {
                        if (!WriteFile (hPipe, abBuffer, dwBytesRead, &dwBytesWrite, NULL))
                        {
                            hResult = HRESULT_FROM_WIN32(GetLastError());
                            TraceResult ("OpenServerUploadPipe: Failed to write to the pipe", hResult);
                        }
                    }
                } while (dwBytesRead && !hResult);
                CloseHandle (hPipe);
            }
        }
        else
        {
            if (hResult)
            {
                *pfErrorInTheServer = TRUE;
            }
        }
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            *pfErrorInTheServer = TRUE;
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("OpenServerUploadPipe", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    SendMsgToAccount()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI SendMsgToAccount (LPTSTR    szServerName,
                                 LPTSTR    szRecipMailbox,
                                 LPTSTR    szHeader,
                                 LPTSTR    szConnectionInfo,
                                 BOOL *    pfErrorInTheServer)
{
    *pfErrorInTheServer = FALSE;
    long hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteSendMsgToAccount ((WINDS_RPC_STRING)szRecipMailbox,
                                          (WINDS_RPC_STRING)szHeader,
                                          (WINDS_RPC_STRING)szConnectionInfo);
        if (hResult)
        {
            *pfErrorInTheServer = TRUE;
        }
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            *pfErrorInTheServer = TRUE;
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("SendMsgToAccount", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    FinishUploadConnection()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI FinishUploadConnection (LPTSTR   szServerName,
                                       LPTSTR   szConnectionInfo)
{
    long hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteFinishUpload ((WINDS_RPC_STRING)szConnectionInfo);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    TraceResult ("FinishUploadConnection", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    OpenRemoteServerDownLoadPipe()
//
//    Parameters                        
//      szServer   Name of the server we are downloading the message from
//      szMBox     Name of the mailbox we are downloading from.
//      phPipe      Pointer where I return the handle to the opened named
//                  pipe to the server machine.
//
//    Purpose
//      Makes an RPC to the remote server which sets up a pipe
//      over which the download occurs. The RPC returns to the
//      client (us) the pipe's ID that the server creates. We
//      then connect to the pipe.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI OpenRemoteServerDownLoadPipe (LPTSTR     szServer,
                                             LPTSTR     szMBox,
                                             HANDLE *   phPipe)
{
    ASSERT (szServer);
    ASSERT (szMBox);
    HRESULT hResult = BindToServer (szServer);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        ULONG ulPipeNum;
        hResult = RemoteOpenMsgDownloadPipe ((WINDS_RPC_STRING)szMBox, &ulPipeNum);
        if (!hResult)
        {
            TCHAR szPipeName[_MAX_PATH];
            HANDLE hPipe;
            // Construct the download pipe name
            wsprintf (szPipeName, PIPE_NAME_FORMAT, szServer, ulPipeNum);
            // Create our endpoint and connect    
            hPipe = CreateFile (szPipeName, 
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
            }
            else
            {
                *phPipe = hPipe;
            }
        }
    }
    RpcExcept(1)
    {        
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    // Terminate connections with the remote server
    BindToServer (NULL);
    TraceResult ("OpenRemoteServerDownLoadPipe", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    SelectMailBoxDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      Displays a dialog with all available mailboxes in the remote machine
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK SelectMailBoxDlgProc (HWND    hDlg,
                                    UINT    message,
                                    WPARAM  wParam, 
                                    LPARAM  lParam)
{
    static SELECTED_MAILBOX_INFO * pInfo;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                HWND hCtl = GetDlgItem (hDlg, IDC_LIST);
                int nTabStops[3];
                nTabStops[0] = 75;
                nTabStops[1] = 1000; // Off the screen
                nTabStops[2] = 1015; // Off the screen
                ListBox_SetTabStops (hCtl, sizeof(nTabStops)/sizeof(int), nTabStops);
                pInfo = (SELECTED_MAILBOX_INFO *)lParam;
                TCHAR szFormated[256];
                AB_ENTRY_INFO abEntry = { 0 };
                DWORD dwLastError = 0, dwBytesRead = 0;
                do
                {
                    // Read the pipe handle.
                    if (!ReadFile (pInfo->hPipe, &abEntry, sizeof(AB_ENTRY_INFO), &dwBytesRead, NULL))
                    {
                        dwLastError = HRESULT_FROM_WIN32(GetLastError());
                        if (HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE)   != dwLastError &&   // For Windows NT
                            HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED) != dwLastError)     // For Windows 95
                        {
                            // There was an error and we can't continue
                            TraceResult ("SelectMailBoxDlgProc: Failed to read from the pipe", dwLastError);
                        }
                        else
                        {
                            // If the pipe was broken, it means the server finished writing
                            // to the it, so we are finished reading from it.
                            dwLastError = 0;
                        }
                    }
                    else
                    {
                        wsprintf (szFormated,
                                  TEXT("%s\t%s\t%s\t%d"),
                                  abEntry.Info.MB.szMailboxName,
                                  abEntry.Info.MB.szFullName,
                                  abEntry.Info.MB.szPassword,
                                  abEntry.Info.MB.dwObjID);
                        ListBox_AddString (hCtl, szFormated);
                    }
                } while (dwBytesRead && !dwLastError);
                if (!dwLastError)
                {
                    if (pfnDlgSubclassEx)
                    {
                        pfnDlgSubclassEx (hDlg, CTL3D_ALL);
                    }
                    return TRUE;
                }
                pInfo->hLastError = dwLastError;
                EndDialog (hDlg, -1);
            }
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_LIST :
                    if (LBN_DBLCLK != HIWORD(wParam))
                    {
                        break;
                    }
                case IDOK :
                    {
                        TCHAR szBuffer[256];
                        LPTSTR pStr;
                        HWND hCtl = GetDlgItem (hDlg, IDC_LIST);
                        int i = ListBox_GetCurSel (hCtl);
                        if (i != LB_ERR)
                        {
                            ListBox_GetText (hCtl, i, szBuffer);
                            pStr = strtok (szBuffer, "\t");
                            lstrcpy (pInfo->szMailBoxName, pStr);
                            pStr = strtok (NULL, "\t");
                            lstrcpy (pInfo->szDisplayName, pStr);
                            pStr = strtok (NULL, "\t");
                            lstrcpy (pInfo->szPassword, pStr);
                            pStr = strtok (NULL, "\t");
                            *(pInfo->pdwMailboxID) = (DWORD)atol (pStr);
                        }
                        else
                        {
                            PrivateMessageBox (IDS_MSG_SELECT_MB_NAME, hDlg);
                            return FALSE;
                        }
                    }
                case IDCANCEL :
                    EndDialog (hDlg, (LOWORD(wParam) == IDCANCEL ? FALSE : TRUE));
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    ChangeMBServerPassword()
//
//    Parameters
//      szServerName        Name of the server machine we are connecting to
//      szMailboxName       Name of the mailbox where the password will
//                          be changed.
//      szOldPassword       Old password of the mailbox
//      szNewPassword       New password for the mailbox
//
//    Purpose
//      Changes the access password in the specified mailbox in
//      the specified server.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI ChangeMBServerPassword (LPTSTR   szServerName,
                                       LPTSTR   szMailboxName,
                                       LPTSTR   szOldPassword,
                                       LPTSTR   szNewPassword)
{
    if (BindToServer (szServerName))
    {
        return FALSE;
    }
    HRESULT hResult;
    RpcTryExcept
    {
        hResult = RemoteChangePassword ((WINDS_RPC_STRING)szMailboxName,
                                        (WINDS_RPC_STRING)szOldPassword,
                                        (WINDS_RPC_STRING)szNewPassword);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    BindToServer (NULL);
    TraceResult ("ChangeMBServerPassword", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    PrivateMessageBox()
//
//    Parameters
//      ids             String ID of a string in the resource string table
//      hOwnerWnd       Window who will own the Message Box
//      uFlags          Flags (options) for the message box
//      
//    Purpose
//      This function display a message box with a string loaded from the
//      string table of this app. The ID of the string is passed in the ids
//      parameter. The dialog box is modal with respect to the window
//      identified in hOwnerWnd. The options to display the dialog box are
//      passed in uFlags
//      
//    Return Value
//      ID of the button pressed in the message box dialog box
//      
int WINAPI PrivateMessageBox (UINT          ids,
                              HWND          hOwnerWnd,
                              UINT          uFlags,
                              HINSTANCE     hInst)
{
    int nResponse = -1; // Default response
    // Get the string from the string table. The size of the buffer is the
    // maximum number of character allowed in the character buffer, without
    // the accounting for the NULL terminator
    if (NULL == hInst)
    {
        hInst = ghInstance;
    }
    ASSERT (hInst);
    TCHAR szBuffer[256];
    if (LoadString (hInst, ids, szBuffer, 255))
    {
        if (!(MB_ICONSTOP & uFlags))
        {
            uFlags |= MB_ICONINFORMATION;
        }
        // Show the message box and get the ID of the button pressed
        nResponse = MessageBox (hOwnerWnd,
                                szBuffer,
                                gszProviderName,
                                uFlags |
                                MB_SETFOREGROUND |
                                MB_SYSTEMMODAL);
    }
    return nResponse;
}

///////////////////////////////////////////////////////////////////////////////
//    IsValidServerName()
//
//    Parameters
//      szServerName       Pointer to a string with the UNC name of a
//                          network or local server
//    Purpose
//      Check the string for a server name and determines if the name is a
//      valid UNC name for a network server
//
//    Return Value
//      TRUE if the server name is valid, FALSE otherwise.
//      
BOOL WINAPI IsValidServerName (LPTSTR szServerName)
{
    // Server name need to be at least "\\x"
    if (lstrlen(szServerName) < 3)
    {
        return FALSE;
    }
    // The first two character in the string must be "\". This is standard
    // UNC (Universal Naming Convention) for server names
    if (szServerName[0] != '\\' || szServerName[1] != '\\')
    {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    BindToServer()
//
//    Parameters
//      [IN]    szServer   Name of the remote server to which we will bind
//                          for RPC calls. If this pointer is NULL, we
//                          unbind from that server.
//
//    Purpose
//      This function makes the necessary calls to the RPC runtime library
//      to bind to the remote server so that we can start RPC function calls.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI BindToServer (LPTSTR szServer)
{
    static unsigned char * szStringBinding = NULL;
    static char szLastServer[32] = { 0 };

    // If a server name was given, we compare to the current server that we are
    // already bounded to. If we are connected return the call.
    if (szServer)
    {
        if (0 == lstrcmpi (szLastServer, szServer))
        {
            if (szStringBinding)
            {
                return 0;
            }
        }
        else
        {
            // Save the name of the server in the static buffer
            lstrcpy (szLastServer, szServer);
        }
    }

    RPC_STATUS status = 0;
    if (szStringBinding) // Unbind only if bound
    {
        status = RpcStringFree (&szStringBinding);
        TraceRPCError  ("BindToServer: RpcStringFree failed", status);
        if (!status)
        {
            szStringBinding = NULL;
            status = RpcBindingFree (&hWINDSREM);  // hWINDSREM is defined in WINDS.H and WINDS.ACF
            TraceRPCError  ("BindToServer: RpcBindingFree failed", status);
        }
    }
    // If this is NULL, then we don't need to bind to anything.
    if (!szServer)
    {
        szLastServer[0] = 0;
        return 0;
    }
    if (!status)
    {
        status = RpcStringBindingCompose (NULL,
                                          (WINDS_RPC_STRING)WINDS_RPC_PROTOCOL,
                                          (WINDS_RPC_STRING)szServer,
                                          (WINDS_RPC_STRING)WINDS_PROVIDERS_RPC_ENDPOINT,
                                          NULL,
                                          &szStringBinding);
        TraceRPCError  ("BindToServer: RpcStringBindingCompose failed", status);
        if (!status)
        {
            status = RpcBindingFromStringBinding (szStringBinding, &hWINDSREM); // hWINDSREM is defined in WINDS.H and WINDS.ACF
            TraceRPCError ("BindToServer: RpcBindingFromStringBinding failed", status);
        }
    }
    if (status)
    {
        szLastServer[0] = 0;
        status = MAKE_HRESULT(1, FACILITY_RPC, status);;
    }
    return status;
}

///////////////////////////////////////////////////////////////////////////////
//    TerminateRemoteConnections()
//
//    Parameters
//      None.
//
//    Purpose
//      Termintes the binding links in the RPC runtime library to the remote
//      server after a sequence of RPC calls.
//
//    Return Value
//      None
//
void WINAPI TerminateRemoteConnections()
{
    BindToServer (NULL);
}

///////////////////////////////////////////////////////////////////////////////
//    midl_user_allcate()
//
//    Parameters
//      len     Size (in bytes) of the memory block to allocate for the
//              RPC object
//
//    Purpose
//      Allocates memory as needed by the RPC runtime library.
//      The stubs or runtime libraries may need to allocate memory.
//      By convention, they call a user-specified function named
//      midl_user_allocate.
//
//    Return Value
//      Pointer to a block of memory of len byte in size
//
void __RPC_FAR * __RPC_API midl_user_allocate (size_t len)
{
    LPVOID pVoid = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, (DWORD)len);
    if (NULL == pVoid)
    {
        TraceMessage ("midl_user_allocate: Failed to allocated RPC memory block");
    }
    return pVoid;
}

///////////////////////////////////////////////////////////////////////////////
//    midl_user_free()
//
//    Parameters
//      ptr     Pointer to memory block to release
//
//    Purpose
//      Free memory as needed by the RPC runtime library.
//      The stubs or runtime libraries may need to free memory.
//      By convention, they call a user-specified function named
//      midl_user_free.
//
//    Return Value
//      None
//
void __RPC_API midl_user_free (void __RPC_FAR * ptr)
{
    HeapFree (GetProcessHeap(), 0, ptr);
}

///////////////////////////////////////////////////////////////////////////////
//    CUIMAPIProp::CUIMAPIProp()
//
//    Parameters
//      hInstance           Instance of the DLL where this provider is
//      pfnAllocateBuffer   MAPI allocation function
//      pfnAllocateMore     MAPI allocation function
//      pfnFreeBuffer       MAPI allocation function
//      fReadOnly           Weather or not the UI is in read-only mode
//
//    Purpose
//      Constructor of the class.
//
//    Return Value
//      None.
//
CUIMAPIProp::CUIMAPIProp (HINSTANCE             hInstance,
                          LPALLOCATEBUFFER      pfnAllocateBuffer,
                          LPALLOCATEMORE        pfnAllocateMore,
                          LPFREEBUFFER          pfnFreeBuffer,
                          BOOL                  fReadOnly)
{
    // Save in global pointer
    pfnMAPIFreeBuffer = pfnFreeBuffer;

    // Use MAPI's IMAPIProp in-memory implementation to do the actual
    // work of store the properties. If we fail to create this, we throw
    // and exception, to new creator of this object must have the
    // construction of this object protected within a try-catch block.
    HRESULT hResult = CreateIProp ((LPIID)&IID_IMAPIPropData,
                                   pfnAllocateBuffer,
                                   pfnAllocateMore,
                                   pfnFreeBuffer,
                                   NULL,
                                   &m_pImpObj);
    if (hResult)
    {   
        TraceResult ("CUIMAPIProp: CreateIProp failed to create IPropData object", hResult);
        throw CException (hResult);
    }
    m_hInstance = hInstance;
    m_fReadOnly = fReadOnly;
    m_cRef = 1;
    m_ulCustomPropTag = 0;
    m_pfnCallBack = NULL;
    m_pTableData = NULL;
    InitializeCriticalSection (&m_csObj);
}

///////////////////////////////////////////////////////////////////////////////
//    CUIMAPIProp::OpenProperty()
//
//    Parameters
//      { Refer to the MAPI documentation for parameter description }
//
//    Purpose
//      Open the property for the BUTTON control on the display table. We
//      only allow the IID_IMAPIControl interface specified in this method.
//      If we have the property specified, create a new IMAPIControl
//      interface and return it to the caller.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CUIMAPIProp::OpenProperty (ULONG       ulPropTag,
                                        LPCIID      piid,
                                        ULONG       ulInterfaceOptions,
                                        ULONG       ulFlags,
                                        LPUNKNOWN * ppUnk)
{
    Validate_IMAPIProp_OpenProperty (this,
                                     ulPropTag, 
                                     piid,
                                     ulInterfaceOptions,
                                     ulFlags,
                                     ppUnk);
    if (IID_IMAPIControl != *piid)
    {
        return E_NOINTERFACE;
    }
    LPBUTTONCALLBACK pfnCallBack = NULL;
    switch (ulPropTag)
    {
        case PR_SMP_BROWSE_MB :
            pfnCallBack = BrowseMailboxes;
            break;
        case PR_SMP_CHANGE_PASSWORD :
            pfnCallBack = ConfigChangePassword;
            break;
        default :
            // We allow client of CUIMAPIProp to set one custom property
            // that is not know internally and a custom callback.
            if (m_ulCustomPropTag == ulPropTag)
            {
                pfnCallBack = m_pfnCallBack;
            }
    }
    if (NULL == pfnCallBack)
    {
        return MAPI_E_NOT_FOUND;
    }
    CMAPIControl * pControl = new CMAPIControl (this, pfnCallBack, m_fReadOnly);
    if (!pControl)
    {
        return E_OUTOFMEMORY;
    }
    *ppUnk = (LPUNKNOWN)pControl;
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    EnterMBPasswordDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      Display a dialog where the user enters the password for a mailbox
//      on the server.
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK EnterMBPasswordDlgProc (HWND    hDlg,
                                      UINT    message,
                                      WPARAM  wParam, 
                                      LPARAM  lParam)
{
    static LPTSTR szStoredPassword;
    static LPTSTR szReturningBuffer;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // On this message only, the lParam is an argument passed by the
                // caller who instantiated this dialog.
                LPSPropValue pProps = (LPSPropValue)lParam;
                SetWindowText (GetDlgItem (hDlg, IDC_MAILBOXNAME), pProps[0].Value.LPSZ);
                SetWindowText (GetDlgItem (hDlg, IDC_USER_NAME), pProps[1].Value.LPSZ);
                szStoredPassword = pProps[2].Value.LPSZ;
                szReturningBuffer = pProps[3].Value.LPSZ;
                Edit_LimitText (GetDlgItem (hDlg, IDC_PASSWORD), MAX_PASSWORD_SIZE);
                // If this value is false, we should disable the BROWSE button to prevent
                // users from changing the mailbox.
                if (FALSE == pProps[4].Value.b)
                {
                    EnableWindow (GetDlgItem (hDlg, IDC_BROWSE_MB), FALSE);
                }
                if (pfnDlgSubclassEx)
                {
                    pfnDlgSubclassEx (hDlg, CTL3D_ALL);
                }
            }
            return TRUE;
        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_BROWSE_MB :
                    EndDialog (hDlg, IDC_BROWSE_MB);
                    break;
                case IDOK :
                    // Get the password and do a CASE-SENSITIVE comparison of the stored and entered psswords.
                    GetWindowText (GetDlgItem (hDlg, IDC_PASSWORD), szReturningBuffer, MAX_PASSWORD_SIZE);
                    if (szStoredPassword && (0 != lstrcmp (szReturningBuffer, szStoredPassword)))
                    {
                        MessageBeep (MB_ICONEXCLAMATION);
                        PrivateMessageBox (IDS_MSG_INVALID_MB_PASSWORD, hDlg);
                        SetFocus (GetDlgItem (hDlg, IDC_PASSWORD));
                        return TRUE;
                    }
                    // else fall through
                case IDCANCEL :
                    EndDialog (hDlg, (LOWORD(wParam) == IDCANCEL ? FALSE : TRUE));
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    PasswordDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      Display a dialog where the user enters a new password for the mailbox.
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK PasswordDlgProc (HWND    hDlg,
                               UINT    message,
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static LPTSTR * pszPasswords;
    switch (message)
    {   
        case WM_INITDIALOG :
            // On this message only, the lParam is an argument passed by the
            // caller who instantiated this dialog.
            pszPasswords = (LPTSTR *)lParam;
            // Limit the fields the user can type in.
            Edit_LimitText  (GetDlgItem (hDlg, IDC_PASSWORD), MAX_PASSWORD_SIZE);
            Edit_LimitText  (GetDlgItem (hDlg, IDC_PASSWORD_CONFIRM), MAX_PASSWORD_SIZE);
            Edit_LimitText  (GetDlgItem (hDlg, IDC_OLD_PASSWORD), MAX_PASSWORD_SIZE);
            if (pfnDlgSubclassEx)
            {
                pfnDlgSubclassEx (hDlg, CTL3D_ALL);
            }
            return TRUE;
        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDOK :
                    {
                        // Get and verify the OLD password
                        TCHAR szConfirm[MAX_PASSWORD_SIZE+1],  szOldPassword[MAX_PASSWORD_SIZE+1];
                        if (!GetWindowText (GetDlgItem (hDlg, IDC_OLD_PASSWORD), szOldPassword, MAX_PASSWORD_SIZE+1))
                        {
                            MessageBeep (MB_ICONEXCLAMATION);
                            PrivateMessageBox (IDS_MSG_NEED_OLD_PASSWORD, hDlg);
                            SetFocus (GetDlgItem (hDlg, IDC_OLD_PASSWORD));
                            return TRUE;
                        }
                        if (lstrcmp (szOldPassword, pszPasswords[1]))
                        {
                            MessageBeep (MB_ICONEXCLAMATION);
                            PrivateMessageBox (IDS_MSG_OLD_PASSWORD_NO_MATCH, hDlg);
                            SetWindowText (GetDlgItem (hDlg, IDC_OLD_PASSWORD), szBlank);
                            SetFocus (GetDlgItem (hDlg, IDC_OLD_PASSWORD));
                            return TRUE;
                        }
                        // Get the NEW password
                        if (!GetWindowText (GetDlgItem (hDlg, IDC_PASSWORD), pszPasswords[0], MAX_PASSWORD_SIZE+1))
                        {
                            MessageBeep (MB_ICONEXCLAMATION);
                            PrivateMessageBox (IDS_MSG_NEED_PASSWORD, hDlg);
                            SetFocus (GetDlgItem (hDlg, IDC_PASSWORD));
                            return TRUE;
                        }
                        // Get the NEW password (CONFIRM)
                        if (!GetWindowText (GetDlgItem (hDlg, IDC_PASSWORD_CONFIRM), szConfirm, MAX_PASSWORD_SIZE+1))
                        {
                            MessageBeep (MB_ICONEXCLAMATION);
                            PrivateMessageBox (IDS_MSG_NEED_PASSWORD_CONFIRM, hDlg);
                            SetFocus (GetDlgItem (hDlg, IDC_PASSWORD_CONFIRM));
                            return TRUE;
                        }
                        // Compare (case-sensitive) the instances of the new password typed in
                        if (lstrcmp (szConfirm, pszPasswords[0]))
                        {
                            MessageBeep (MB_ICONEXCLAMATION);
                            PrivateMessageBox (IDS_MSG_NEW_PASSWORD_NO_MATCH, hDlg);
                            SetWindowText (GetDlgItem (hDlg, IDC_PASSWORD), szBlank);
                            SetWindowText (GetDlgItem (hDlg, IDC_PASSWORD_CONFIRM), szBlank);
                            SetFocus (GetDlgItem (hDlg, IDC_PASSWORD));
                            return TRUE;
                        }
                    }
                case IDCANCEL :
                    EndDialog (hDlg, (IDOK == LOWORD(wParam) ? TRUE : FALSE));
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    BrowseMailboxes()
//
//    Parameters
//      pObj            Pointer to our IMAPIProp implementation (CUIMAPIProp)
//                      passed in to the DoConfidPropSheet() function
//      hOwnerWnd       The owner of any window we display
//      hInstance       The instance of this DLL
//
//    Purpose
//      This function get called by our implementation of
//      IMAPIControl::Active() by a user hitting a "Browse"
//      on the provider configuration property sheet.
//      Display a dialog box with all the mailboxes in the remote system
//
//    Return Value
//      None
//
void STDAPICALLTYPE BrowseMailboxes (CUIMAPIProp *  pObj,
                                     HWND           hOwnerWnd,
                                     HINSTANCE      hInstance)
{
    TCHAR szDisplayName[MAX_STRING_SIZE+1], szMailboxName[MAX_ALIAS_SIZE+1];
    TCHAR szStoredPassword[MAX_PASSWORD_SIZE+1], szEnterPassword[MAX_PASSWORD_SIZE+1];
    LPSPropValue pProp = NULL;
    DWORD dwMailboxID;
    SPropTagArray sptServer;
    sptServer.cValues = 1;
    sptServer.aulPropTag[0] = PR_SMP_REMOTE_SERVER;
    ULONG cValues;
    // Get the server name the user may have typed in the edit field
    HRESULT hResult = pObj->GetProps (&sptServer, fMapiUnicode, &cValues, &pProp);
    if (FAILED(hResult) || MAPI_W_ERRORS_RETURNED == hResult)
    {
        pfnMAPIFreeBuffer (pProp);
        PrivateMessageBox (IDS_MSG_NEED_SERVER_NAME, hOwnerWnd);
        return;
    }
    ASSERT (pProp->ulPropTag == PR_SMP_REMOTE_SERVER);
    TCHAR szServer[MAX_STRING_SIZE+1];
    lstrcpy (szServer, pProp->Value.LPSZ);
    pfnMAPIFreeBuffer (pProp);
    // Validate the server
    if (!IsValidServerName (szServer))
    {
        MessageBeep (MB_ICONEXCLAMATION);
        PrivateMessageBox (IDS_MSG_INVALID_SERVER_NAME, hOwnerWnd);
        return;
    }
    if (!IsWINDSServerAvailable (szServer))
    {
        PrivateMessageBox (IDS_MSG_SERVER_NOT_FOUND, hOwnerWnd);
        return;
    }
    // Show the list of mailboxes in the server. If the user hit OK, process the selected entry.
Restart:
    if (S_OK == ShowServerAccounts  (hOwnerWnd,
                                     hInstance,
                                     szServer,
                                     szMailboxName,
                                     szDisplayName,
                                     szStoredPassword,
                                     &dwMailboxID))
    {
        // Set the selected mailbox properties in the property object
        SPropValue spvProps[5] = { 0 };
        spvProps[0].ulPropTag = PR_SMP_MAILBOX_NAME;
        spvProps[0].Value.LPSZ = szMailboxName;
        spvProps[1].ulPropTag = PR_SMP_USER_NAME;
        spvProps[1].Value.LPSZ = szDisplayName;
        spvProps[2].ulPropTag = PR_SMP_MAILBOX_PASSWORD;
        spvProps[2].Value.LPSZ = szStoredPassword;
        spvProps[3].ulPropTag = PR_SMP_MAILBOX_PASSWORD;
        spvProps[3].Value.LPSZ = szEnterPassword;
        spvProps[4].Value.b = TRUE; // Activate the "BROWSE" button on the dialog below
        // Before continuing, the user must verify it's access to the mailbox by typing the correct password
        int nAnswer = DialogBoxParam (hInstance,  
                                      MAKEINTRESOURCE(IDD_ENTER_PASSWORD),
                                      hOwnerWnd,
                                      EnterMBPasswordDlgProc,
                                      (LPARAM)spvProps);
        if (IDC_BROWSE_MB == nAnswer)
        {
            goto Restart;
        }
        if (TRUE == nAnswer)
        {
            // Access is verified, continue
            spvProps[3].ulPropTag = PR_SMP_MAILBOX_ID;
            spvProps[3].Value.l = dwMailboxID;
            pObj->SetProps (4, spvProps, NULL);
            // Now we must tell the property sheet handler to re-read the data for
            // this field from the IMAPIProp object any of the DTCTL members with a key, for a notification on them.
            for (ULONG iRow=0; ; iRow++)
            {
                LPSRow pRow;
                LPSPropValue pControlID;
                hResult = pObj->m_pTableData->HrEnumRow (iRow, &pRow);
                if (hResult || !pRow)
                {
                    TraceResult ("BrowseMailboxes: Traversing the display table", hResult);
                    return;
                }
                pControlID = PpropFindProp (pRow->lpProps, pRow->cValues, PR_CONTROL_ID);
                if (pControlID->Value.bin.cb)
                {
                    pObj->m_pTableData->HrNotify (0, 1, pControlID);
                }
                pfnMAPIFreeBuffer (pRow);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    ConfigChangePassword()
//
//    Parameters
//      pObj            Pointer to our IMAPIProp implementation (CUIMAPIProp)
//                      passed in to the DoConfidPropSheet() function
//      hOwnerWnd       The owner of any window we display
//      hInstance       The instance of this DLL
//
//    Purpose
//      This function get called by our implementation of
//      IMAPIControl::Active() by a user hitting a "Change Mailbox Password"
//      on the provider configuration property sheet.
//      Display a dialog box where the user can change the password of the
//      mailbox.
//
//    Return Value
//      None
//
void STDAPICALLTYPE ConfigChangePassword (CUIMAPIProp * pObj, HWND hOwnerWnd, HINSTANCE hInstance)
{
    const static SizedSPropTagArray(3, sptServerAndPass) =
    {
        3,
        {
            PR_SMP_REMOTE_SERVER,
            PR_SMP_MAILBOX_NAME,
            PR_SMP_MAILBOX_PASSWORD
        }
    };
    TCHAR szOldPassword[MAX_PASSWORD_SIZE+1], szNewPassword[MAX_PASSWORD_SIZE+1];
    TCHAR szServer[MAX_STRING_SIZE+1], szMBName[MAX_STRING_SIZE+1];
    LPTSTR aszPasswords[2] = { 0 };
    ULONG cValues;
    LPSPropValue pProp = NULL;
    SPropValue spvNewPassword = { 0 };
    // Get the server and mailbox information for the property object
    HRESULT hResult = pObj->GetProps ((LPSPropTagArray)&sptServerAndPass, fMapiUnicode, &cValues, &pProp);
    if (FAILED(hResult) || MAPI_W_ERRORS_RETURNED == hResult)
    {
        pfnMAPIFreeBuffer (pProp);
        PrivateMessageBox (IDS_MSG_NEED_SERVER_NAME, hOwnerWnd);
        return;
    }
    ASSERTMSG (pProp[0].ulPropTag == PR_SMP_REMOTE_SERVER, "Where is PR_SMP_REMOTE_SERVER?!?!");
    ASSERTMSG (pProp[1].ulPropTag == PR_SMP_MAILBOX_NAME, "Where is PR_SMP_MAILBOX_NAME?!?!");
    ASSERTMSG (pProp[2].ulPropTag == PR_SMP_MAILBOX_PASSWORD, "Where is PR_SMP_MAILBOX_PASSWORD?!?!");
    lstrcpy (szServer, pProp[0].Value.LPSZ);
    lstrcpy (szMBName, pProp[1].Value.LPSZ);
    lstrcpy (szOldPassword, pProp[2].Value.LPSZ);
    pfnMAPIFreeBuffer (pProp);
    // Validate the server name and availability
    if (!IsValidServerName (szServer))
    {
        MessageBeep (MB_ICONEXCLAMATION);
        PrivateMessageBox (IDS_MSG_INVALID_SERVER_NAME, hOwnerWnd);
        return;
    }
    if (!IsWINDSServerAvailable (szServer))
    {
        PrivateMessageBox (IDS_MSG_SERVER_NOT_FOUND, hOwnerWnd);
        return;
    }
    aszPasswords[0] = szNewPassword;
    aszPasswords[1] = szOldPassword;

    // Show the dialog where the user can change the information
    if (TRUE == DialogBoxParam (hInstance,
                                MAKEINTRESOURCE(IDD_NEW_PASSWORD),
                                hOwnerWnd,
                                PasswordDlgProc,
                                (LPARAM)&aszPasswords))
    {
        // If the user is ok call the server
        if (S_OK == ChangeMBServerPassword (szServer, szMBName, szOldPassword, szNewPassword))
        {
            // If the change was successfull, save the new password in the property object.
            spvNewPassword.ulPropTag = PR_SMP_MAILBOX_PASSWORD;
            spvNewPassword.Value.LPSZ = szNewPassword;
            pObj->SetProps (1, &spvNewPassword, NULL);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    PingRemoteServer()
//
//    Parameters
//      hOwnerWnd       Handle to a windows that owns any UI done by
//                      this provider
//      pProps          An array of SPropValue structures with the logon
//                      properties of the service. The first 5 properties
//                      must be the standard properties for a WINDS service
//                      and they must be in the standard order (see COMWINDS.H)
//
//    Purpose
//      Make a quick connection to the server verifying a mailbox access
//      with the current password and name.
//
//    Return Value
//      TRUE if the connection was successful, or the user does not care that
//      the server is offline.
//      FALSE if the user wants to change the configuration properties again.
//
BOOL WINAPI PingRemoteServer (HWND hOwnerWnd, LPSPropValue pProps)
{
    BOOL fPingedOK = TRUE;
    DWORD dwMsgIDS = 0, dwMailboxID;
    TCHAR szServerUserFullName[MAX_STRING_SIZE+1];
    HRESULT hLogonError;
    CharUpper (pProps[SERVER_NAME].Value.LPSZ);
    // Try to connect to the server and see if it is around
    if (IsWINDSServerAvailable (pProps[SERVER_NAME].Value.LPSZ))
    {
        hLogonError = LogonServerMailbox (pProps[SERVER_NAME].Value.LPSZ,
                                          pProps[MAILBOX_NAME].Value.LPSZ,
                                          szServerUserFullName,
                                          pProps[PASSWORD].Value.LPSZ,
                                          &dwMailboxID);
        if (hLogonError)
        {
            switch (hLogonError)
            {
                case HRESULT_FROM_WIN32 (ERROR_NO_SUCH_USER) :
                    dwMsgIDS = IDS_MSG_CONFIG_INVALID_USER;
                    break;
                case HRESULT_FROM_WIN32 (ERROR_BAD_USERNAME) :
                    dwMsgIDS = IDS_MSG_CONFIG_INVALID_USER_NAME;
                    break;
                case HRESULT_FROM_WIN32 (ERROR_INVALID_PASSWORD) :
                    dwMsgIDS = IDS_MSG_INVALID_MB_PASSWORD;
                    break;
                default :
                    dwMsgIDS = IDS_MSG_CONFIG_NO_CONNECT;
                    break;
            }
            PrivateMessageBox (dwMsgIDS, hOwnerWnd);
            fPingedOK = FALSE;
        }
    }
    else
    {
        if (IDNO == PrivateMessageBox (IDS_MSG_NO_SERVER_GO_OFFLINE, hOwnerWnd, MB_YESNO | MB_ICONSTOP))
        {
            // The user wants to re-enter the name of the remote server
            fPingedOK = FALSE;
        }
    }
    return fPingedOK;
}

///////////////////////////////////////////////////////////////////////////////
//    DoServerLogon()
//
//    Parameters
//      pMBInfo             Pointer to the mailbox info structure where this
//                          function returns the mailbox information of the
//                          user logging in.
//      pProps              An array of SPropValue structures with the logon
//                          properties of the service. The first 5 properties
//                          must be the standard properties for a WINDS
//                          service and they must be in the standard order
//                          (see COMWINDS.H)
//      pProfileObj         Profile object to which this function write
//                          changes, if any are required based on the latest
//                          information comming down from the server or
//                          entered by the user in the configuration dialog.
//      fUIAllowed          Weather or not the function is allowed to display
//                          any UI of information or request input from
//                          the user.
//      hOwnerWnd           Handle to the window that owns any UI displayed.
//      fSetNotification    Weather or not to set notifications with the
//                          remote server
//      dwNotifMask         Mask of events this provider is intersted in
//                          receiving.
//      pdwConnectID        Where I return the connection ID returned by
//                          the server
//      fOffLineOK          Flag that indicates that the caller does not
//                          want to be bother with a "server offline"
//                          notification/UI and that we should return success
//                          even if the server could not be reached.
//
//    Purpose
//      This function does a complete logon to the server with the
//      information passed in the pProps arguments. The function makes a
//      remote call to the server to request access to a mailbox. If
//      access is not granted we display messages and if needed, display the
//      appropiate dialog boxes for reconfiguration or change of password.
//      If the server was off-line, but the user does not mind, we return
//      MAPI_W_NO_SERVICE.
//      If the server is off-line, but no UI is allowed we return
//      MAPI_E_NETWORK_ERROR.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI DoServerLogon (PMAILBOX_INFO pMBInfo,
                              LPSPropValue  pProps,
                              LPPROFSECT    pProfileObj,
                              BOOL          fUIAllowed,
                              HWND          hOwnerWnd,
                              BOOL          fSetNotification,
                              DWORD         dwNotifMask,
                              DWORD *       pdwConnectID,
                              BOOL          fOffLineOK)
{
    ASSERT (PR_SMP_REMOTE_SERVER == pProps[SERVER_NAME].ulPropTag);
    ASSERT (PR_SMP_MAILBOX_NAME == pProps[MAILBOX_NAME].ulPropTag);
    ASSERT (PR_SMP_MAILBOX_ID == pProps[MAILBOX_ID].ulPropTag);
    ASSERT (PR_SMP_USER_NAME == pProps[USER_NAME].ulPropTag);
    ASSERT (PR_SMP_MAILBOX_PASSWORD == pProps[PASSWORD].ulPropTag);
    
    pMBInfo->dwObjID = pProps[MAILBOX_ID].Value.l;
    lstrcpy (pMBInfo->szMailboxName, pProps[MAILBOX_NAME].Value.LPSZ);
    lstrcpy (pMBInfo->szFullName, pProps[USER_NAME].Value.LPSZ);
    lstrcpy (pMBInfo->szPassword, pProps[PASSWORD].Value.LPSZ);
    
    SPropValue spvProps[5] = { 0 };
    DWORD dwMsgIDS = 0, dwStyle = MB_YESNO | MB_ICONSTOP, dwMailboxID;
    HRESULT hLogonError;
    long nResponse;

    // Try to connect to the server and see if it is around
    if (IsWINDSServerAvailable (pProps[SERVER_NAME].Value.LPSZ))
    {
RestartMailboxLogon:
        if (fSetNotification)
        {
            hLogonError = LogonServerMailboxAndSetNotif (pProps[SERVER_NAME].Value.LPSZ,
                                                         pMBInfo->szMailboxName,
                                                         pMBInfo->szFullName,
                                                         pMBInfo->szPassword,
                                                         &dwMailboxID,
                                                         dwNotifMask,
                                                         *pdwConnectID);
        }
        else
        {
            hLogonError = LogonServerMailbox (pProps[SERVER_NAME].Value.LPSZ,
                                              pMBInfo->szMailboxName,
                                              pMBInfo->szFullName,
                                              pMBInfo->szPassword,
                                              &dwMailboxID);
        }
        if (hLogonError)
        {
            if (fUIAllowed)
            {
                switch (hLogonError)
                {
                    case HRESULT_FROM_WIN32 (ERROR_NO_SUCH_USER) :
                        dwMsgIDS = IDS_MSG_LOGON_INVALID_USER;
                        break;
                    case HRESULT_FROM_WIN32 (ERROR_BAD_USERNAME) :
                        dwMsgIDS = IDS_MSG_LOGON_INVALID_USER_NAME;
                        break;
                    case HRESULT_FROM_WIN32 (ERROR_INVALID_PASSWORD) :
                        dwMsgIDS = IDS_MSG_INVALID_MB_PASSWORD;
                        dwStyle = MB_OK | MB_ICONSTOP;
                        break;
                    default :
                        dwMsgIDS = IDS_MSG_LOGON_NO_CONNECT;
                        break;
                }
                if (dwMsgIDS)
                {
                    PrivInitialize3DCtl (ghInstance);
                    nResponse = PrivateMessageBox (dwMsgIDS, hOwnerWnd, dwStyle);
                    if (IDYES == nResponse && hLogonError != HRESULT_FROM_WIN32 (ERROR_INVALID_PASSWORD))
                    {
                        return S_FALSE;
                    }
                    if (hLogonError == HRESULT_FROM_WIN32 (ERROR_INVALID_PASSWORD))
                    {
                        spvProps[0].ulPropTag = PR_SMP_MAILBOX_NAME;
                        spvProps[0].Value.LPSZ = pMBInfo->szMailboxName;
                        spvProps[1].ulPropTag = PR_SMP_USER_NAME;
                        spvProps[1].Value.LPSZ = pMBInfo->szFullName;
                        spvProps[2].ulPropTag = PR_SMP_MAILBOX_PASSWORD;
                        spvProps[2].Value.LPSZ = NULL;
                        spvProps[3].ulPropTag = PR_SMP_MAILBOX_PASSWORD;
                        spvProps[3].Value.LPSZ = pMBInfo->szPassword;
                        spvProps[4].Value.b = FALSE; // De-activate the "BROWSE" button on the dialog below
                        ASSERT (NULL != ghInstance);
                        nResponse = DialogBoxParam (ghInstance,  
                                                    MAKEINTRESOURCE(IDD_ENTER_PASSWORD),
                                                    hOwnerWnd,
                                                    EnterMBPasswordDlgProc,
                                                    (LPARAM)spvProps);
                        if (FALSE == nResponse)
                        {
                            return MAPI_E_EXTENDED_ERROR;
                        }
                        else
                        {
                            goto RestartMailboxLogon;
                        }
                    }
                }
            }
            else
            {
                return hLogonError;
            }
        }
        else
        {
            ULONG ulProps = 0;
            // If any of this properties that came from the server is different to
            // what we have stored on the profile, then set them back for the next session.
            if (lstrcmp (pProps[USER_NAME].Value.LPSZ, pMBInfo->szFullName))
            {
                spvProps[ulProps].ulPropTag = PR_SMP_USER_NAME;
                spvProps[ulProps++].Value.LPSZ = pMBInfo->szFullName;
            }
            if (lstrcmp (pProps[PASSWORD].Value.LPSZ, pMBInfo->szPassword))
            {
                spvProps[ulProps].ulPropTag = PR_SMP_MAILBOX_PASSWORD;
                spvProps[ulProps++].Value.LPSZ = pMBInfo->szPassword;
            }
            if (dwMailboxID != pProps[MAILBOX_ID].Value.ul)
            {
                spvProps[ulProps].ulPropTag = PR_SMP_MAILBOX_ID;
                spvProps[ulProps++].Value.l = dwMailboxID;
            }
            if (ulProps)
            {
                HRESULT hResult = pProfileObj->SetProps (ulProps, spvProps, NULL);
                TraceResult ("DoServerLogon: Could not set last-minute props", hResult);
            }
        }
    }
    else
    {
        // If the caller says that is OK to be offline, then return.
        if (fOffLineOK)
        {
            return S_OK;
        }
        if (fUIAllowed)
        {
            PrivInitialize3DCtl (ghInstance);
            if (IDYES == PrivateMessageBox (IDS_MSG_NO_SERVER_ONLINE, hOwnerWnd, MB_YESNO))
            {
                // The user wants to re-enter the name of the remote server
                return MAPI_W_NO_SERVICE;
            }
        }
        else
        {
            return MAPI_E_NETWORK_ERROR;
        }
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    WizardEntry()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Returns the name of the resource where the controls for the wizard
//      pages are defined and outlined. The Wizard gives us a pointer to an
//      IMAPIProp object. We will release this object after we are finished
//      in the dialog procedure of our configuration pages.
//
//    Return Value
//      S_OK always.
//
ULONG STDAPICALLTYPE WizardEntry (HINSTANCE     hProviderDLLInstance,
                                  LPTSTR *      ppcsResourceName,
                                  DLGPROC *     ppDlgProc,
                                  LPMAPIPROP    pMapiProp,
                                  LPVOID        pSupObj)
{   
    InfoTrace ("WizardEntry function called");
    // Quick sanity check on the input parameters
    ASSERT (ppcsResourceName);
    ASSERT (pMapiProp);
    ASSERT (ppDlgProc);
    ASSERT (hProviderDLLInstance);
    // The resource name needs to be an actual text string not
    // something generated with the MAKEINTRESOURCE() macro
    const static TCHAR szTemplate[] = TEXT("WIZARD_PAGES");
    *ppcsResourceName = (LPTSTR)szTemplate;
    *ppDlgProc = (DLGPROC)WizardDlgProc;
    pPropObj = pMapiProp;
    pPropObj->AddRef();
    ghInstance = hProviderDLLInstance;

    fInitalizeControls = fDownloadMBList = TRUE;
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    WizardDlgProc()
//
//    Parameters
//      { Refer to MAPI and Win32 SDK Documentation on this method }
//
//    Purpose
//      This is the function that the profile wizard will call while
//      interacting with our configuration pages.
//
//    Return Value
//      TRUE if we handle a message, FALSE if we don't or there was an error
//      in the data
//
BOOL STDAPICALLTYPE WizardDlgProc (HWND           hDlg,
                                   UINT           message,
                                   WPARAM         wParam,
                                   LPARAM         lParam)
{
    static SPropValue spvWizardProps[WIZARD_PROPERTIES] = { 0 };
    static TCHAR szDisplayName[MAX_STRING_SIZE+1];
    static TCHAR szServerName[MAX_STRING_SIZE+1];
    static TCHAR szMailboxName[MAX_ALIAS_SIZE+1];
    static TCHAR szStoredPassword[MAX_PASSWORD_SIZE+1];
    static TCHAR szEnterPassword[MAX_PASSWORD_SIZE+1];
    static DWORD dwMailboxID;
    static UINT iPageNum;
    switch (message)
    {
        case WM_INITDIALOG:
            // If the control have not been initialized do so
            if (fInitalizeControls)
            {
                // Send output to a console window BUT NOT to the COM1
                InitTraces (TRACES_CONSOLE | TRACES_NO_COM_OUTPUT);
                dwMailboxID = 0;
                // Set the flag to avoid re-initialization
                fInitalizeControls = FALSE;
                // Limit the maximum number of character users can enter for the mailbox PASSWORD
                Edit_LimitText  (GetDlgItem (hDlg, IDC_PASSWORD), MAX_PASSWORD_SIZE);
                PrivInitialize3DCtl (ghInstance);
                iPageNum = 0;
            }
            return TRUE;

        case WIZ_QUERYNUMPAGES :
            // Return the number of pages the our provider needs to display
            return (BOOL)2;

        case WM_CLOSE :
            pPropObj->Release();
            pPropObj = NULL;
            PrivUninitialize3DCtl (ghInstance);
            // Close down the log file/com port/console window/etc.
            UnInitTraces();
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_BROWSE_MB :
                    if (S_OK == ShowServerAccounts  (hDlg,
                                                     ghInstance,
                                                     szServerName,
                                                     szMailboxName,
                                                     szDisplayName,
                                                     szStoredPassword,
                                                     &dwMailboxID))
                    {
                        SetWindowText (GetDlgItem (hDlg, IDC_MAILBOXNAME), szMailboxName);
                        SetWindowText (GetDlgItem (hDlg, IDC_USER_NAME), szDisplayName);
                    }
                    return TRUE;

                case WIZ_NEXT:
                    switch (iPageNum)
                    {
                        // We are about to leave a page in each of the 
                        // following cases. Here we should get the data from
                        // the controls in that page, validate it if necessary
                        // and copy the validated data into the property array
                        case 0:
                            break;

                        case 1:
                            if (!GetWindowText (GetDlgItem (hDlg, IDC_SERVERNAME),
                                                szServerName,
                                                sizeof(szServerName)))
                            {
                                MessageBeep (MB_ICONEXCLAMATION);
                                PrivateMessageBox (IDS_MSG_NEED_SERVER_NAME, hDlg);
                                return FALSE;
                            }
                            if (!IsValidServerName (szServerName))
                            {
                                MessageBeep (MB_ICONEXCLAMATION);
                                PrivateMessageBox (IDS_MSG_INVALID_SERVER_NAME, hDlg);
                                return FALSE;
                            }
                            if (!IsWINDSServerAvailable (szServerName))
                            {
                                PrivateMessageBox (IDS_MSG_SERVER_NOT_FOUND, hDlg);
                                return FALSE;
                            }
                            if (fDownloadMBList)
                            {
                                if (S_OK == ShowServerAccounts  (hDlg,
                                                                 ghInstance,
                                                                 szServerName,
                                                                 szMailboxName,
                                                                 szDisplayName,
                                                                 szStoredPassword,
                                                                 &dwMailboxID))
                                {
                                    SetWindowText (GetDlgItem (hDlg, IDC_MAILBOXNAME), szMailboxName);
                                    SetWindowText (GetDlgItem (hDlg, IDC_USER_NAME), szDisplayName);
                                    fDownloadMBList = FALSE;
                                }
                                else
                                {
                                    return FALSE;
                                }
                            }
                            break;

                        case 2:
                            if (!GetWindowTextLength (GetDlgItem (hDlg, IDC_PASSWORD)))
                            {
                                MessageBeep (MB_ICONEXCLAMATION);
                                PrivateMessageBox (IDS_MSG_SELECT_MB_NAME, hDlg);
                                SetFocus (GetDlgItem (hDlg, IDC_BROWSE_MB));
                                return FALSE;
                            }
                            if (!GetWindowText (GetDlgItem (hDlg, IDC_PASSWORD), szEnterPassword, sizeof(szEnterPassword)))
                            {
                                MessageBeep (MB_ICONEXCLAMATION);
                                PrivateMessageBox (IDS_MSG_NEED_PASSWORD, hDlg);
                                SetFocus (GetDlgItem (hDlg, IDC_PASSWORD));
                                return FALSE;
                            }
                            if (lstrcmp (szEnterPassword, szStoredPassword))
                            {
                                MessageBeep (MB_ICONEXCLAMATION);
                                PrivateMessageBox (IDS_MSG_INVALID_MB_PASSWORD, hDlg);
                                SetFocus (GetDlgItem (hDlg, IDC_PASSWORD));
                                return FALSE;
                            }
                            spvWizardProps[SERVER_NAME].ulPropTag  = PR_SMP_REMOTE_SERVER;
                            spvWizardProps[SERVER_NAME].Value.LPSZ = szServerName;
                            spvWizardProps[MAILBOX_NAME].ulPropTag  = PR_SMP_MAILBOX_NAME;
                            spvWizardProps[MAILBOX_NAME].Value.LPSZ = szMailboxName;
                            spvWizardProps[MAILBOX_ID].ulPropTag  = PR_SMP_MAILBOX_ID;
                            spvWizardProps[MAILBOX_ID].Value.l = dwMailboxID;
                            spvWizardProps[USER_NAME].ulPropTag  = PR_SMP_USER_NAME;
                            spvWizardProps[USER_NAME].Value.LPSZ = szDisplayName;
                            spvWizardProps[PASSWORD].ulPropTag  = PR_SMP_MAILBOX_PASSWORD;
                            spvWizardProps[PASSWORD].Value.LPSZ = szStoredPassword;
                            // Since this is the last page in our configuration
                            // we must save the obtained data into the
                            // IMAPIProp object that the wizard gave us. In
                            // turn this data will be saved in the profile
                            // section of this provider
                            ASSERT (pPropObj);
                            if (pPropObj)
                            {
                                HRESULT hResult = pPropObj->SetProps (WIZARD_PROPERTIES, spvWizardProps, NULL);
                                if (hResult)
                                {
                                    // Something went wrong
                                    TraceResult ("WizardDlgPrc: Failed to set props", hResult);
                                    return FALSE;
                                }
                            }
                            break;

                        default:
                            // We should not get here. No pages after three
                            ASSERT (FALSE);
                            break;
                    }
                    // Disable the page we were in and enable the next one
                    // before it is display by the wizard
                    TogglePage (hDlg, iPageNum, FALSE);
                    TogglePage (hDlg, ++iPageNum, TRUE);
                    return TRUE;

                case WIZ_PREV:
                    // Disable the page we were in and enable the next one
                    // before it is display by the wizard
                    TogglePage (hDlg, iPageNum, FALSE);
                    TogglePage (hDlg, --iPageNum, TRUE);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    TogglePage()
//
//    Parameters
//      hDlg        Handle to the dialogs where the controls are located
//      iPage       Number of the page we are going to toggle
//      fState      State of the controls: TRUE shows them, FALSE hides them
//
//    Purpose
//      This function will hide or show the controls for the page number
//      specified in the iPage parameter.
//
//    Return Value
//      None
//
void WINAPI TogglePage (HWND hDlg, UINT iPage, BOOL fState)
{
    // What page is it?
    HWND hEditCtl = NULL;
    switch (iPage)
    {
        // Toggle the controls that should be displayed for a particular page
        case 1 :
            EnableWindow (GetDlgItem (hDlg, IDC_STATIC1), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_STATIC1), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_INFO1), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_INFO1), fState ? SW_SHOW : SW_HIDE);
            hEditCtl = GetDlgItem (hDlg, IDC_SERVERNAME);
            break;

        case 2 :
            EnableWindow (GetDlgItem (hDlg, IDC_STATIC2), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_STATIC2), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_STATIC3), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_STATIC3), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_STATIC4), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_STATIC4), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_INFO2), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_INFO2), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_MAILBOXNAME), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_MAILBOXNAME), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_USER_NAME), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_USER_NAME), fState ? SW_SHOW : SW_HIDE);
            EnableWindow (GetDlgItem (hDlg, IDC_BROWSE_MB), fState);
            ShowWindow   (GetDlgItem (hDlg, IDC_BROWSE_MB), fState ? SW_SHOW : SW_HIDE);
            hEditCtl = GetDlgItem (hDlg, IDC_PASSWORD); // We want the button to have the focus by default
            break;
    }
    if (hEditCtl)
    {
        EnableWindow (hEditCtl, fState);
        ShowWindow   (hEditCtl, fState ? SW_SHOW : SW_HIDE);
        if (fState)
        {
            SetFocus (hEditCtl);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    MergeConfigProps()
//
//    Parameters
//      ulCfgProps      Number of properties for configuration
//      pCfgProps       Array of properties to configure the provider
//      pLogonProps     Array of properties found in the profile section of
//                      this service provider
//
//    Purpose
//      This function merges a property array that the user (or configuration
//      application) passed into ServiceEntry with the property array of
//      the provider, stored in the profile. This merged array is what
//      either gets passed into the configuration dialog (if UI is allowed)
//      and gets written out to the profile section for the service provider.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI MergeConfigProps (ULONG                  ulCfgProps,
                                 LPSPropValue           pCfgProps,
                                 LPSPropValue           pLogonProps)
{
    while (ulCfgProps--)
    {
        // For the particular property found, set the proptag (in case
        // the one in the profile was not valid), and the value. The
        // value will be the value passed in the configuration prop array.
        switch (pCfgProps[ulCfgProps].ulPropTag)
        {
            case PR_SMP_REMOTE_SERVER :
                if (FALSE == IsValidServerName (pCfgProps[ulCfgProps].Value.LPSZ))
                {
                    return E_INVALIDARG;
                }
                pLogonProps[SERVER_NAME] = pCfgProps[ulCfgProps];
                break;
            case PR_SMP_USER_NAME :
                pLogonProps[USER_NAME] = pCfgProps[ulCfgProps];
                break;
            case PR_SMP_MAILBOX_NAME :
                pLogonProps[MAILBOX_NAME] = pCfgProps[ulCfgProps];
                break;
            case PR_SMP_MAILBOX_ID :
                pLogonProps[MAILBOX_ID] = pCfgProps[ulCfgProps];
                break;
            case PR_SMP_MAILBOX_PASSWORD :
                pLogonProps[PASSWORD] = pCfgProps[ulCfgProps];
                break;
        }
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    OpenServiceProfileSection()
//
//    Parameters
//      pSupObj         Pointer to the provider support object
//      ppProfSectObj   Where we return a pointer to the service profile
//                      section of the provider
//      pfnFreeBuffer   MAPI memory allocation function
//
//    Purpose
//      This function opens the profile section of this service, where the
//      properties of a WINDS provider (AB, MS, or XP) are stored.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI OpenServiceProfileSection (LPMAPISUP    pSupObj,
                                          LPPROFSECT * ppProfSectObj,
                                          LPFREEBUFFER pfnFreeBuffer)
{
    SPropTagArray sptService = { 1, { PR_SERVICE_UID } };
    LPPROFSECT pProvProfSectObj;
    ULONG cValues;
    LPSPropValue pProp;
    // Get the PROVIDER profile section
    HRESULT hResult = pSupObj->OpenProfileSection (NULL,
                                                   MAPI_MODIFY,
                                                   &pProvProfSectObj);
    if (!hResult)
    {
        // Get the UID of the profile section of the service where this provider is installed
        hResult = pProvProfSectObj->GetProps (&sptService, fMapiUnicode, &cValues, &pProp);
        if (SUCCEEDED(hResult))
        {
            if (S_OK == hResult)
            {
                // Now, with the obtained UID, open the profile section of the service
                ASSERTMSG (PR_SERVICE_UID == pProp->ulPropTag, "Where is PR_SERVICE_UID");
                hResult = pSupObj->OpenProfileSection ((LPMAPIUID)pProp->Value.bin.lpb,
                                                       MAPI_MODIFY,
                                                       ppProfSectObj);
            }
            else
            {
                hResult = E_FAIL;
            }
            pfnFreeBuffer (pProp);
        }
        pProvProfSectObj->Release();
    }
    TraceResult ("OpenServiceProfileSection", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    PrivInitialize3DCtl()
//
//    Parameters
//      hInstance   Handle to the instance the control 3d library will
//                  subclass
//
//    Purpose
//      This function dynamically binds to the CTL3D library for UI apperance
//      on Windows NT. On Windows 95 the library may or may not be on the
//      system. We do this to have a single binary file that works on
//      Windows NT and Windows 95 and ensure that the WINDS service DLL loads
//      correctly in both platforms.
//      The CTL3D provider a less disparate user interface between the two OS's
//
//    Return Value
//      None
//
void WINAPI PrivInitialize3DCtl (HINSTANCE hInstance)
{
    if (NULL == ghUIControl)
    {
        ghUIControl = LoadLibrary (TEXT("CTL3D32.DLL"));
        if (ghUIControl)
        {
            pfn3DRegister = (LPCTL3DFUNCTION)GetProcAddress (ghUIControl, TEXT("Ctl3dRegister"));
            pfn3DUnregister = (LPCTL3DFUNCTION)GetProcAddress (ghUIControl, TEXT("Ctl3dUnregister"));
            pfn3DAutoSubclass = (LPCTL3DFUNCTION)GetProcAddress (ghUIControl, TEXT("Ctl3dAutoSubclass"));
            pfnDlgSubclassEx = (LPCTL3DSUBCLASS)GetProcAddress (ghUIControl, TEXT("Ctl3dSubclassDlgEx"));
            
            if (pfn3DRegister &&
                pfn3DUnregister &&
                pfn3DAutoSubclass &&
                pfnDlgSubclassEx)
            {
                pfn3DRegister (hInstance);
                pfn3DAutoSubclass (hInstance);
            }
            else
            {
                PrivUninitialize3DCtl (hInstance);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    PrivUninitialize3DCtl()
//
//    Parameters
//      hInstance   Handle to the instance the control 3d library will
//                  de-attach from.
//
//    Purpose
//      Unregister the 3D UI control stuff and unload the library of the
//      3D controls.
//
//    Return Value
//      None
//
void WINAPI PrivUninitialize3DCtl (HINSTANCE hInstance)
{
    if (ghUIControl)
    {
        if (pfn3DUnregister)
        {
            pfn3DUnregister (hInstance);
        }
        FreeLibrary (ghUIControl);
        ghUIControl = NULL;
        pfn3DRegister = NULL;
        pfn3DUnregister = NULL;
        pfn3DAutoSubclass = NULL;
        pfnDlgSubclassEx = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CheckForPendingMessages()
//
//    Parameters
//      szServerName        Name of the server we are going to connect
//      szMailboxName       Name of the mailbox we are going to check
//      pulMsgWaiting       Number of messages waiting for download
//
//    Purpose
//      This function queries the remote server for how many messages are
//      waiting in the specified mailbox.
//      If there are not messages waiting, the function return S_FALSE.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI CheckForPendingMessages (LPTSTR  szServerName,
                                        LPTSTR  szMailboxName,
                                        ULONG * pulMsgWaiting)
{
    HRESULT hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    RpcTryExcept
    {
        hResult = RemoteCheckNewMail ((WINDS_RPC_STRING)szMailboxName, pulMsgWaiting);
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    #ifdef _DEBUG
    if (hResult && S_FALSE != hResult)
    {
        TraceResult ("CheckForPendingMessages", hResult);
    }
    #endif // _DEBUG
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    GetNextMailboxMsg()
//
//    Parameters
//      szServerName        Name of the server we are going to connect
//      szMailboxName       Name of the mailbox we are going to get the
//                          messages from
//      szLocalMsgFile      Name of the local file where the message
//                          should be placed.
//
//    Purpose
//      This function connect to the server an request the next message to
//      be downloaded for the mailbox specified in call. If there are no
//      more messages to download, we return S_FALSE.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI GetNextMailboxMsg (LPTSTR szServerName,
                                  LPTSTR szMailboxName,
                                  LPTSTR szLocalMsgFile)
{
    HRESULT hResult = BindToServer (szServerName);
    if (hResult)
    {
        return hResult;
    }
    long lPipeNumber;
    HANDLE hPipe, hFile;
    TCHAR szPipeName[64];
    BYTE abBuffer[IO_BUFFERSIZE];
    DWORD dwBytesRead, dwBytesWritten;
    RpcTryExcept
    {
        hResult = RemoteOpenOneMsgDownloadPipe ((WINDS_RPC_STRING)szMailboxName, &lPipeNumber);
        if (!hResult)
        {
            wsprintf (szPipeName, PIPE_NAME_FORMAT, szServerName, lPipeNumber);
            hPipe = CreateFile (szPipeName,
                                GENERIC_READ,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                TraceResult ("GetHeadersFromServer: Failed to open pipe to server", hResult);
            }
            else
            {
                hFile = CreateFile (szLocalMsgFile,
                                    GENERIC_WRITE,
                                    0,
                                    NULL,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                                    NULL);
                if (INVALID_HANDLE_VALUE == hFile)
                {
                    hResult = HRESULT_FROM_WIN32(GetLastError());
                    TraceResult ("GetNextMailboxMsg: Failed to open local headers file", hResult);
                }
                else
                {
                    do
                    {
                        // Read the pipe handle.
                        if (!ReadFile (hPipe, abBuffer, IO_BUFFERSIZE, &dwBytesRead, NULL))
                        {
                            hResult = HRESULT_FROM_WIN32(GetLastError());
                            if (HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE)   != hResult &&   // For Windows NT
                                HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED) != hResult)     // For Windows 95
                            {
                                // There was an error and we can't continue
                                TraceResult ("GetNextMailboxMsg: Failed to read from the pipe", hResult);
                            }
                            else
                            {
                                // If the pipe was broken, it means the server finished writing
                                // to the it, so we are finished reading from it.
                                hResult = S_OK;
                            }
                        }
                        if (dwBytesRead)
                        {
                            if (!WriteFile (hFile, abBuffer, dwBytesRead, &dwBytesWritten, NULL))
                            {
                                hResult = HRESULT_FROM_WIN32(GetLastError());
                                TraceResult ("GetNextMailboxMsg: Failed to write to local header file", hResult);
                            }
                        }
                    } while (dwBytesRead && !hResult);
                    CloseHandle (hFile);
                }
                CloseHandle (hPipe);
            }
        }
    }
    RpcExcept(1)
    {
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    #ifdef _DEBUG
    if (hResult && S_FALSE != hResult)
    {
        TraceResult ("GetNextMailboxMsg", hResult);
    }
    #endif // _DEBUG
    return hResult;
}

// End of file for COMWINDS.CPP
