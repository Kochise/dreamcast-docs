///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPWDSR.H
//
//  Description
//      Interface declaraction file for CXPLogon, CXPProvider, CMAPIFolder,
//      and CMAPIStatus.
//      Property tag definitions.
//      Constant definitions.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#ifndef _XPWDSR_H
#define _XPWDSR_H

#define STRICT
#include <WINDOWS.H>
#include <WINDOWSX.H>
#include <MAPIWIN.H>
#include <MAPISPI.H>
#include <MAPIUTIL.H>
#include <MAPIVAL.H>
#include <TNEF.H>

#ifdef _DEBUG
#define ENABLE_DEBUG_OUTPUT     1
#endif // _DEBUG

// Header file for the trace and logging functions.
#include "TRACES.H"

// Common defs used by providers to communicate to the WINDS Sample Messaging Host
#include "COMWINDS.H"

// Config Page Dialog Control IDs Message String ID's
#include "RESOURCE.H"

// Cached stream for the TNEF object
#include "XPSTREAM.H"

// Definition for the helper classes CList and CMsgQueue
#include "XPLIST.H"

/// Names returned in the status object
#define TRANSPORT_DISPLAY_NAME_STRING       TEXT("PSS WINDS Remote Transport")
#define TRANSPORT_DLL_NAME_STRING           TEXT("XPWDSR.DLL")

// Internal provider version
#define TRANSPORT_VERSION_MAJOR             1
#define TRANSPORT_VERSION_MINOR             5

// Name of the stream where the message properties get encoded using TNEF encapsulation
#define TNEF_FILE_NAME                      TEXT("WINMAIL.DAT")

// Bitmask used to modify the PR_STATUS_CODE property in the status row of this
// transport, when the download or upload logic is active.
#define DOWNLOADING_MESSAGES (STATUS_INBOUND_FLUSH | STATUS_INBOUND_ACTIVE)
#define UPLOADING_MESSAGES (STATUS_OUTBOUND_FLUSH | STATUS_OUTBOUND_ACTIVE)

// Window class name used in the timer window
#define TIMER_WND_CLASS     TEXT("WINDS_XP_TIMER")

// This is copied from GENPROP.H in other PSS MAPI sample providers
typedef struct _PRIVATE_ENTRYID
{
    // MAPI-required fields
    BYTE        abFlags[4];     // 4 bytes          // MAPI Flags
    MAPIUID     uidGlobal;      // 16 bytes         // UID Unique for the backend (ie. at the database file level)  (This must be here)
    // Provider-defined fields
    BYTE        bVersion;       // 1 bytes          // Version of the entry ID schema
    BYTE        bObject;        // 1 bytes          // Object type
    BYTE        bPad[2];        // 2 bytes          // Pad to align the structure to 4-bytes boundaries
    DWORD       dwObjID;        // 4 bytes          // Object ID (container or object)
                                // 28 Bytes Total
} PRIVATE_ENTRYID;
#define     ENTRYID_VERSION     1       // Schema version
#define     CB_PRIVATE_EID      28      // Size of the structure above


// The order for this enumarations must match the order of the properties
// in the tag arrays. These arrays are used to access the 
// LPSPropValue arrays returned from MAPI interfaces. The use of enumerations
// hides differences when the number of properties in the tag array increases
// or decreases. It also helps maintain error-free indexing in the use of 
// the prop arrays
enum
{
    //SERVER_NAME           = 0,        // Array Indexes
    //MAILBOX_NAME          = 1,
    //MAILBOX_ID            = 2,
    //USER_NAME             = 3,
    //PASSWORD              = 4,
    //NET_CON               = 5,
    UPLOAD_TIME             = 6,
    HEADER_FILE             = 7,
    GET_HEADERS             = 8,
    NUM_LOGON_PROPERTIES    = 9         // Array size
};

// ID array of property tags for the trannsport
const static SizedSPropTagArray(NUM_LOGON_PROPERTIES, sptLogonProps) =
{
    NUM_LOGON_PROPERTIES,
    {
        PR_SMP_REMOTE_SERVER,           // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 0)
        PR_SMP_MAILBOX_NAME,            // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 1)
        PR_SMP_MAILBOX_ID,              // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 2)
        PR_SMP_USER_NAME,               // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 3)
        PR_SMP_MAILBOX_PASSWORD,        // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 4)
        PR_SMP_CONNECTION_TYPE,         // DON'T CHANGE THE ORDER OF THIS PROPERTY  (position 5)
        PR_SMP_UPLOAD_TIME,
        PR_SMP_HEADERS_FILENAME,
        PR_SMP_GET_HEADERS
    }
};

// Idle state of the transport
typedef enum _TRANSPORT_STATE
{
    WAITING,                // Waiting for the deferred submission time to arrive to send deferred messages
    READY,                  // Ready to accept re-submission of deferred messages
    SENDING,                // The transport is sending deferred messages
    HEADERS_AND_DOWNLOAD,   // Get the latest list of message headers and download messages from the server
    PENDING_RETURN_CODE,    // A remote operation has finished and the result code is pending to be returned to a remote viewer
    PROCESSING_TIMER_EVENT, // Download the message headers as a response to the scheduled action
} TRANSPORT_STATE;

typedef enum _REMOTE_ACTION
{
    REMOTE_ACTION_DOWNLOADING_MSGS,
    REMOTE_ACTION_PROCESSING_MSGS,
    REMOTE_ACTION_HEADER_REFRESH,
    REMOTE_ACTION_IDLE
} REMOTE_ACTION;

// Indexes of the identity property array
enum
{
    XPID_NAME,              // Array Indexes
    XPID_EID,
    XPID_SEARCH_KEY,
    NUM_IDENTITY_PROPS      // Array size
};

// Indexes of the properties in each row in the contents table of the remote mailbag folder.
enum
{
    HDR_EID,                // Array Indexes
    HDR_SNDR,
    HDR_REPR,
    HDR_DISP_TO,
    HDR_SUBJ,
    HDR_CLASS,
    HDR_FLAGS,
    HDR_SIZE,
    HDR_PRIOR,
    HDR_IMPORTANCE,
    HDR_SENS,
    HDR_TIME,
    HDR_STAT,
    HDR_DOWNLOAD_TIME,
    HDR_HASATTACH,
    HDR_OBJ_TYPE,
    HDR_INST_KEY,
    HDR_NORM_SUBJ,
    NUM_HDR_PROPS           // Array size
};
static const SizedSPropTagArray(NUM_HDR_PROPS, sptFldContents) =
{
    NUM_HDR_PROPS,
    {
        PR_ENTRYID,                 // Index column in the contents table
        PR_SENDER_NAME,
        PR_SENT_REPRESENTING_NAME,
        PR_DISPLAY_TO,
        PR_SUBJECT,
        PR_MESSAGE_CLASS,
        PR_MESSAGE_FLAGS,
        PR_MESSAGE_SIZE,
        PR_PRIORITY,
        PR_IMPORTANCE,
        PR_SENSITIVITY,
        PR_MESSAGE_DELIVERY_TIME,
        PR_MSG_STATUS,
        PR_MESSAGE_DOWNLOAD_TIME,
        PR_HASATTACH,
        PR_OBJECT_TYPE,
        PR_INSTANCE_KEY,
        PR_NORMALIZED_SUBJECT,
    }
};

// Available properties in the folder object 
#define NUM_FOLDER_PROPS        12
static const SizedSPropTagArray (NUM_FOLDER_PROPS, sptFolderProps) =
{
    NUM_FOLDER_PROPS,
    {
        PR_ACCESS,
        PR_ACCESS_LEVEL,
        PR_CONTENT_COUNT,
        PR_ASSOC_CONTENT_COUNT,
        PR_FOLDER_TYPE,
        PR_OBJECT_TYPE,
        PR_SUBFOLDERS,
        PR_CREATION_VERSION,
        PR_CURRENT_VERSION,
        PR_CREATION_TIME,
        PR_DISPLAY_NAME,
        PR_DISPLAY_TYPE
    }
};


// Indexes of the properties we extracting of a message being
// submitted to generate the remote server message header.
enum
{
    MSG_DISP_TO,            // Array Indexes
    MSG_SUBJECT,
    MSG_CLASS,
    MSG_FLAGS,
    MSG_SIZE,
    MSG_PRIORITY,
    MSG_IMPORTANCE,
    MSG_SENSITIVITY,
    MSG_DR_REPORT,
    NUM_MSG_PROPS           // Array size
};
static const SizedSPropTagArray(NUM_MSG_PROPS, sptPropsForHeader) =
{
    NUM_MSG_PROPS,
    {
        PR_DISPLAY_TO,
        PR_SUBJECT,
        PR_MESSAGE_CLASS,
        PR_MESSAGE_FLAGS,
        PR_MESSAGE_SIZE,
        PR_PRIORITY,
        PR_IMPORTANCE,
        PR_SENSITIVITY,
        PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED
    }
};

#define OUT_MSG_PROPS 2
static const SizedSPropTagArray(OUT_MSG_PROPS, sptOutMsgProps) =
{
    OUT_MSG_PROPS,
    {
        PR_SENDER_ENTRYID,
        PR_SENT_REPRESENTING_NAME
    }
};

// Used to generate one-off's for the sender of newly received messages
enum
{
    NEW_SENDER_NAME,
    NEW_SENDER_EMAIL,
    NEW_SENT_NAME,
    NEW_SENT_EMAIL,
    NEW_MSG_FLAGS,
    NUM_NEW_MSG_PROPS
};
static const SizedSPropTagArray(NUM_NEW_MSG_PROPS, sptNewMsgProps) =
{
    NUM_NEW_MSG_PROPS,
    {
        PR_SENDER_NAME,
        PR_SENDER_EMAIL_ADDRESS,
        PR_SENT_REPRESENTING_NAME,
        PR_SENT_REPRESENTING_EMAIL_ADDRESS,
        PR_MESSAGE_FLAGS
    }
};

// Used to generate transport-computed properties on received mail messages
#define MSG_RECIP_PROPS     2
static const SizedSPropTagArray(MSG_RECIP_PROPS, sptMsgRecipProps) =
{
    MSG_RECIP_PROPS,
    {
        PR_EMAIL_ADDRESS,
        PR_RECIPIENT_TYPE
    }
};
// Indexes to order the recipient's table of messages being submitted
enum
{
    RECIP_ROWID,
    RECIP_NAME,
    RECIP_EMAIL_ADR,
    RECIP_TYPE,
    RECIP_RESPONSIBILITY,
    RECIP_DELIVER_TIME,
    RECIP_REPORT_TIME,
    RECIP_REPORT_TEXT,
    TABLE_RECIP_PROPS
};
const static SizedSPropTagArray (TABLE_RECIP_PROPS, sptRecipTable) =
{
    TABLE_RECIP_PROPS,
    {
        PR_ROWID,
        PR_DISPLAY_NAME,
        PR_EMAIL_ADDRESS,
        PR_RECIPIENT_TYPE,
        PR_RESPONSIBILITY,
        PR_DELIVER_TIME,
        PR_REPORT_TIME,
        PR_REPORT_TEXT
    }
};


// Available properties in the status object of this provider
#define NUM_STATUS_OBJECT_PROPS    13
const static SizedSPropTagArray (NUM_STATUS_OBJECT_PROPS, sptStatusObj) =
{
    NUM_STATUS_OBJECT_PROPS,
    {
        PR_OBJECT_TYPE,
        PR_STATUS_CODE,
        PR_PROVIDER_DISPLAY,
        PR_PROVIDER_DLL_NAME,
        PR_RESOURCE_METHODS,
        PR_RESOURCE_FLAGS,
        PR_RESOURCE_TYPE,
        PR_STATUS_STRING,
        PR_DISPLAY_NAME,
        PR_IDENTITY_DISPLAY,
        PR_IDENTITY_ENTRYID,
        PR_IDENTITY_SEARCH_KEY,
        PR_CURRENT_VERSION
    }
};

// Stand-alone helper functions (C style)
extern "C"
{
    HRESULT WINAPI DoLogonDlg
                    (PCFGDLG                    pCfgDialog);
    MSGSERVICEENTRY ServiceEntry;
    HRESULT WINAPI GetMAPIError
                    (LPMAPIERROR *              ppMAPIError,
                     ULONG                      ulFlags,
                     HRESULT                    hError,
                     HINSTANCE                  hInstance);
    BOOL WINAPI ParseTime
                    (LPTSTR                     pszTime,
                     WORD *                     pwHour,
                     WORD *                     pwMinute);
    void WINAPI GetTimeString
                    (LPTSTR                     pszTime,
                     FILETIME                   FileTime);
    extern LPALLOCATEBUFFER    gpfnAllocateBuffer;  // MAPIAllocateBuffer function
    extern LPALLOCATEMORE      gpfnAllocateMore;    // MAPIAllocateMore function    
    extern LPFREEBUFFER        gpfnFreeBuffer;      // MAPIFreeBuffer function      
}

// Forward class declarations
class CMAPIFolder;
class CList;

class CMAPIStatus : public IMAPIStatus
{
friend CXPLogon;
friend CList;
public:
///////////////////////////////////////////////////////////////////////////////
// Interface virtual member functions
//
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};

    MAPI_IMAPIPROP_METHODS(IMPL);
    MAPI_IMAPISTATUS_METHODS(IMPL);

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this transport
//
    
///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
//
public :
    CMAPIStatus     (CXPLogon *                 pLogon,
                     LPPROFSECT                 pProfSectObj);
    ~CMAPIStatus    ();

///////////////////////////////////////////////////////////////////////////////
// Data members
//
private :
    ULONG           m_cRef;
    CXPLogon *      m_pLogon;
    CMAPIFolder *   m_pHeaderFolder;
    LPPROFSECT      m_pProfSectObj;
};

class  CMAPIFolder : public IMAPIFolder
{
friend CXPLogon;
friend CMAPIStatus;
friend CList;
public:
///////////////////////////////////////////////////////////////////////////////
// Interface virtual member functions
//
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    STDMETHODIMP_(ULONG) Release();
    MAPI_IMAPIPROP_METHODS(IMPL);
    MAPI_IMAPICONTAINER_METHODS(IMPL);
    MAPI_IMAPIFOLDER_METHODS(IMPL);

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this class
//
    STDMETHODIMP FillContentsTable
                    (LPTSTR                     pszHeaderFilename);
    STDMETHODIMP CopyTableToFile
                    ();

///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
//
public :
    CMAPIFolder     (CMAPIStatus *              pStatusObj,
                     CXPLogon *                 pLogonObj);
    ~CMAPIFolder    ();

///////////////////////////////////////////////////////////////////////////////
// Data members
//
private :
    ULONG           m_cRef;
    CXPLogon *      m_pLogon;
    CMAPIStatus *   m_pStatusObj;
    LPTABLEDATA     m_pTableData;
    BOOL            m_fNoHeadersFile;
    FILETIME        m_ftLastUpdate;
};

class CXPLogon : public IXPLogon
{
public:
///////////////////////////////////////////////////////////////////////////////
// Interface virtual member functions
//
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
    MAPI_IXPLOGON_METHODS(IMPL);

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this transport
//
public :
    STDMETHODIMP InitializeStatusRow
                    (ULONG                      ulFlags = 0);
    STDMETHODIMP SetIdentityProps
                    ();
    STDMETHODIMP DownloadMessageHeaders
                    ();
    STDMETHODIMP MakeSearchKey
                    (LPVOID                     pParentMemBlock,
                     LPTSTR                     pszAddress,
                     ULONG *                    pcbSearchKey,
                     LPBYTE *                   ppSearchKey);
    STDMETHODIMP GrowAddressList
                    (LPADRLIST *                ppAdrList,
                     ULONG                      ulResizeBy,
                     ULONG *                    pulOldAndNewCount);
    STDMETHODIMP SendMailMessage
                    (LPMESSAGE                  pMsgObj,
                     LPSRowSet                  pRecipRows);
    STDMETHODIMP SetIncomingProps
                    (LPMESSAGE                  pMsgObj,
                     PLIST_NODE                 pNode);
    BOOL WINAPI GetMsgTempFileName
                    (LPTSTR                     pszFileName);
    BOOL WINAPI IsValidAddress
                    (LPTSTR                     pszAddress,
                     LPTSTR *                   ppszServer,
                     LPTSTR *                   ppszMailbox);
    BOOL WINAPI LoadStatusString
                    (LPTSTR                     pString,
                     UINT                       uStringSize);
    void WINAPI InitializeTransportStatusFlags
                    (ULONG                      ulFlags);
    void WINAPI UpdateStatus
                    (BOOL                       fAddValidate = FALSE,
                     BOOL                       fValidateOkState = FALSE);
    void WINAPI UpdateProgress
                    (long                       lPercentComplete,
                     REMOTE_ACTION              raFlag);
    void WINAPI SetSessionFlags
                    (ULONG *                    pulFlags);
    void WINAPI CreateMsgHeaderTextLine
                    (LPSPropValue               pProps,
                     LPTSTR                     pszBuffer,
                     FILETIME &                 time);
    void WINAPI SetOutgoingProps
                    (LPMESSAGE                  pMsgObj,
                     FILETIME                   ft);
    void WINAPI CheckForUnfinishedDownloads
                    ();
    void WINAPI InitializeTimer
                    ();
    void WINAPI StopUploadTimer
                    ();
    void WINAPI StartUploadTimer
                    ();
    inline BOOL WINAPI SetUploadTime
                    (FILETIME                   ftUploads)
                    { SYSTEMTIME st;
                     FileTimeToSystemTime (&ftUploads, &st);
                     BOOL fChanged = FALSE;
                     if (m_stDelivTime.wHour != st.wHour || m_stDelivTime.wMinute != st.wMinute)
                     { fChanged = TRUE; }
                     m_stDelivTime = st;
                     return fChanged; }
    inline void WINAPI AddStatusBits
                    (DWORD dwNewBits) { m_ulTransportStatus |= dwNewBits; }
    inline void WINAPI RemoveStatusBits
                    (DWORD dwOldBits) { m_ulTransportStatus &= ~dwOldBits; }
    inline void WINAPI SetTransportState
                    (TRANSPORT_STATE NewState) { m_TransportState = NewState; }
    inline DWORD WINAPI GetTransportStatusCode
                    () { return m_ulTransportStatus; }
    inline LPTABLEDATA WINAPI GetRemoteFolderTableData
                    () { return m_pStatusObj->m_pHeaderFolder->m_pTableData; }
    inline TRANSPORT_STATE WINAPI GetTransportState
                    () { return m_TransportState; }
    inline HINSTANCE WINAPI GetInstance
                    () { return m_hInstance; }
    inline LPTSTR WINAPI GetLocalHeadersCache
                    () { return m_szHeaders; }
    inline LPTSTR WINAPI GetServerName
                    () { return m_szServer; }
    inline void WINAPI SetServerName
                    (LPTSTR                     szNewServer)
                    { lstrcpy (m_szServer, szNewServer); }
    inline LPTSTR WINAPI GetAccountName
                    () { return m_UserInfo.szMailboxName; }
    inline BOOL WINAPI PendingIncoming
                    () { return m_List.AreTherePendingDownloads(); }
    inline void WINAPI SetAccountProps
                    (LPTSTR                     szAccountName,
                     DWORD                      dwAccountID,
                     LPTSTR                     szUserName,
                     LPTSTR                     szPassword)
                    { lstrcpy (m_UserInfo.szMailboxName, szAccountName);
                      lstrcpy (m_UserInfo.szFullName, szUserName);
                      lstrcpy (m_UserInfo.szPassword, szPassword);
                      m_UserEID.dwObjID = dwAccountID;
                      LPSPropValue pOldProps = m_pIdentityProps;
                      if (S_OK == SetIdentityProps())
                      {
                          gpfnFreeBuffer (pOldProps);
                      }
                      wsprintf (m_szAddress, TEXT("%s\\%s"), m_szServer, m_UserInfo.szMailboxName);}
private:
    void WINAPI CheckSpoolerYield
                    (BOOL                       fReset = FALSE);
    void WINAPI EmptyInboundQueue
                    ();
    STDMETHODIMP ProcessHeaders
                    ();
    inline void WINAPI DecomposeAddress
                    (LPTSTR                     pszAddress,
                     LPTSTR *                   ppszServer,
                     LPTSTR *                   ppszMailbox)
                    {
                        // The 2 is to avoid the expected first two characters
                        strtok (&pszAddress[2], "\\");
                        *ppszServer = pszAddress;
                        *ppszMailbox = strtok (NULL, "\\");
                    }
    inline void WINAPI RecomposeAddress
                    (LPTSTR                     pszServer,
                     LPTSTR                     pszMailbox,
                     LPTSTR                     pszAddress)
                    {
                        // pszAddress must have previouly been decomposed with
                        // CXPLogon::DecomposeAddress
                        pszAddress[lstrlen (pszServer)] = '\\';
                    }

    
///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
public :
    CXPLogon        (HINSTANCE                  hInstance,
                     LPMAPISUP                  pSupObj,
                     LPTSTR                     pszHeadersFile,
                     BOOL                       fGetHeaders,
                     PMAILBOX_INFO              pUserMailboxInfo,
                     DWORD                      dwMailboxID,
                     LPTSTR                     pszRemoteServer,
                     HANDLE                     hUIMutex);
    ~CXPLogon       ();

///////////////////////////////////////////////////////////////////////////////
// Data members
private :
    // Object implementation internal data
    ULONG               m_cRef;
    HINSTANCE           m_hInstance;
    CList               m_List;
    BOOL                m_fABWDSInstalled;
public :
    LPMAPISUP           m_pSupObj;
    HANDLE              m_hUIMutex;
    HRESULT             m_hRemoteActionErr;
    BOOL                m_fCancelPending;
    CMAPIStatus *       m_pStatusObj;

private :
    // Remote headers
    TCHAR               m_szHeaders[_MAX_PATH];
    BOOL                m_fGetHeaders;

    // Transport activity state
    ULONG               m_ulTransportStatus;
    TRANSPORT_STATE     m_TransportState;
    REMOTE_ACTION       m_raAction;

    // Server information
    TCHAR               m_szServer[MAX_STRING_SIZE+1];
    
    // User information and identity on the WINDS messaging server
    MAILBOX_INFO        m_UserInfo;
    PRIVATE_ENTRYID     m_UserEID;
    TCHAR               m_szAddress[64];
public :
    LPSPropValue        m_pIdentityProps;

private :
    // Deferred delivery and timer logic
    SYSTEMTIME          m_stDelivTime;
    HWND                m_hTimerWnd;
public :
    UINT                m_uTimerID;
};

class CXPProvider : public IXPProvider
{
friend CXPLogon;
friend CMAPIStatus;
friend CMAPIFolder;
public:
///////////////////////////////////////////////////////////////////////////////
// Interface virtual member functions
//
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
    MAPI_IXPPROVIDER_METHODS(IMPL);

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this class
//
    
///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
//
public :
    CXPProvider     (HINSTANCE                  hInst);
    ~CXPProvider    ();

///////////////////////////////////////////////////////////////////////////////
// Data members
//
private :
    ULONG               m_cRef;
    CRITICAL_SECTION    m_csTransport;
    HINSTANCE           m_hInstance;
};

#endif // _XPWDSR_H

// End of file for XPWDSR.H
