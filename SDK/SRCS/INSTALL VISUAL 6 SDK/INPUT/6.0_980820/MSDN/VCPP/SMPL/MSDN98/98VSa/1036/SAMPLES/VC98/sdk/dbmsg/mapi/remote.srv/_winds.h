///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      _WINDS.H
//
//  Description
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#ifndef _WINDS_H
#define _WINDS_H

#define STRICT
#include <WINDOWS.H>
#include "WINDSGBL.H"
#include "WINDSRC.H"

#ifdef _DEBUG
#define ENABLE_DEBUG_OUTPUT     1
#endif // _DEBUG
#define TRACES_NO_MAPI          1

#include "TRACES.H"

#define WINDS_DATABASE_VERSION          6

// Buffers and pipe symbolic constants.
#define READ_TIME_OUT       INFINITE
#define WRITE_TIME_OUT      INFINITE
#define GENERAL_TIME_OUT    INFINITE

#define MIN_PIPE_NUMBER                 0x00000001
#define MAX_PIPE_NUMBER                 0x00FFFFFF

#define ELEMENTS_TO_FETCH   25

typedef enum _ACTION
{
    IO_IDLE,
    IO_OPEN_STORAGE_FILE,
    IO_LOAD_MAILBOX_NAMES,
    IO_CREATE_NEW_MAILBOX,
    IO_REMOVE_MAILBOX,
    IO_EMPTY_MAILBOX,
    IO_GET_MAILBOX_PROPERTIES,
    IO_SET_MAILBOX_PROPERTIES,

    // Message Transport services
    IO_COPY_MSG_FROM_FILE,
    IO_COPY_MSG_TO_FILE,
    IO_MOVE_MSG_TO_FILE,
    IO_COPY_HEADERS_TO_FILE,
    IO_DELETE_MSG_IN_MAILBOX,
    IO_CHECK_PENDING_MESSAGES,
    IO_MOVE_NEXT_MSG_TO_FILE,

    // Address Book services
    IO_GET_CONTAINER_RECIPIENTS,
    IO_CREATE_DISTRIBUTION_LIST,
    IO_DELETE_DISTRIBUTION_LIST,
    IO_GET_DL_PROPERTIES,
    IO_SET_DL_PROPERTIES,
    IO_GET_GW_CONTAINER_COUNT,

    // Public folder services
    IO_CREATE_PUBLIC_FOLDER,
    IO_DELETE_PUBLIC_FOLDER,
    IO_GET_PF_PROPERTIES,
    IO_SET_PF_PROPERTIES,
    IO_CREATE_PF_NEW_MESSAGE,
    IO_DELETE_PF_MESSAGE,
    IO_OPEN_PF_MESSAGE,
    IO_MODIFY_PF_MESSAGE,

    // Remote Administrator
    IO_ADMIN_GET_SERVER_MAILBOXES,
    IO_ADMIN_GET_SERVER_DISTLISTS,
    
    // Helper actions for the notification mechanism
    IO_SENT_SHUTDOWN_NOTIFICATION,
    IO_RESTORE_CLIENT_NOTIFICATIONS
} ACTION;

typedef struct _IOTHREADINFO
{
    BOOL                    fAppIsTerminating;
    BOOL                    fCloseHandle;
    ACTION                  Action;
    HANDLE                  hResumeEvent;
    HANDLE                  hActionCompleted;
    HANDLE                  hTmpFile;
    TCHAR                   szObject[MAX_ALIAS_SIZE+1];
    TCHAR                   szHeader[IO_BUFFERSIZE];
    PMAILBOX_INFO           pMBInfo;
    PDIST_LIST_INFO         pDLInfo;
    PPUBLIC_FOLDER_INFO     pPFInfo;
    DWORD                   dwObjID;
    HRESULT *               phLastError;
    DWORD *                 pdwData;
    PWINDS_NOTIFICATION     pNotif;
} IOTHREADINFO, *PIOTHREADINFO;

typedef struct _DBINFO_DATA
{
    DWORD dwVersion;
} DBINFO_DATA;

// This is the structure with the information that gets written to the
// system registry database to save per-OS-USER-session information
typedef struct tagAPP_OPTIONS
{
    DWORD       cbSize;
    TCHAR       szDataFile[256];
} APP_OPTIONS;

#define SERVER_PIPE_NAME_FORMAT     TEXT("\\\\.\\pipe\\%d")

#define NAME_FORMAT_SIZE        32

// Name string format for the OLE sub storages of the object database
#define DBINFO_STREAM           OLESTR("DATABASE INFO")
#define OBJ_ID_POOL_STREAM      OLESTR("OBJECT ID POOL")
#define USER_PROPERTIES         OLESTR("USER PROPERTIES")
#define HEADERS_STORAGE         OLESTR("HEADERS")
#define MSGS_STORAGE            OLESTR("MESSAGES")
#define MSG_STREAM_FORMAT       OLESTR("MSG %X")
#define HEADER_STREAM_FORMAT    OLESTR("HEADER %X")
// Server Distribution List Support
#define DISTRIBUTION_LISTS      OLESTR("_DISTRIBUTION LISTS")
#define DL_PROPS                OLESTR("DL PROPERTIES")
#define DL_MEMBERS              OLESTR("DL MEMBERS")
// Gateway Support
#define FOREIGN_DIRECTORIES     OLESTR("_GATEWAYS")
#define GW_OUTBOX               OLESTR("_GATEWAY OUT")
#define GW_INBOX                OLESTR("_GATEWAY IN")
#define SMTP_GATEWAY            OLESTR("SMTP")
#define EXCHANGE_GATEWAY        OLESTR("EXCHANGE")
#define FAX_GATEWAY             OLESTR("FAX")
// Public Folders Support
#define PUBLIC_FOLDERS_ROOT     OLESTR("_PUBLIC FOLDERS ROOT")
#define FOLDER_PROPS_STREAM     OLESTR("FOLDER PROPERTIES")
#define PUBLIC_FOLDER           OLESTR("FOLDER %X")

#define CREATE_FLAGS    (STGM_CREATE | STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE)
#define OPEN_FLAGS      (STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE)

#define MAINDLGCLASS    TEXT("WindsDlgClass")

extern "C"
{
    extern IOTHREADINFO g_IOInfo;
    extern TCHAR g_szDataFile[];
    extern HRESULT g_hServerState;
    extern CRITICAL_SECTION g_csIOInfo;
    extern CRITICAL_SECTION g_csNotifLinks;
    extern CRITICAL_SECTION g_csServiceState;
    extern CRITICAL_SECTION g_csPipeID;
    extern DWORD g_dwNextPipeID;
    extern BOOL g_fRunningAsNTService;
    extern HINSTANCE ghInstance;
    extern HANDLE    ghHeap;

    HRESULT WINAPI CreateDLsDirectory
                        (LPSTORAGE                  pStorage);
    HRESULT WINAPI CreateGatewayDirectories
                        (LPSTORAGE                  pStorage);
    HRESULT WINAPI CreatePublicFoldersDirectory
                        (LPSTORAGE                  pStorage);
    HRESULT WINAPI GetObjectProp
                        (DWORD                      dwObjID,
                         DWORD *                    pdwObjType,
                         MAILBOX_INFO *             pMailboxInfo);
    HRESULT WINAPI GetServiceState
                        ();
    HRESULT WINAPI AnsiToUnicode
                        (LPSTR                      szStr,
                         LPWSTR                     wcStr,
                         ULONG                      cchUnicode);
    HRESULT WINAPI UnicodeToAnsi
                        (LPWSTR                     wcStr,
                         LPSTR                      szStr,
                         ULONG                      cchAnsi);
    DWORD WINAPI GetNextPipeID
                        ();
    void WINAPI ReleaseSyncObj
                        ();
    void WINAPI LoadSettingsFromRegistry
                        ();
    void WINAPI SaveSettingsToRegistry
                        ();
    void WINAPI RemoveAllNotifLinks
                        ();
    void WINAPI NotifyClients
                        (PWINDS_NOTIFICATION        pNotif);
    
    HRESULT WINAPI GetLocalTempFileName
                        (LPTSTR                     szTmpFileName);
    HRESULT WINAPI FileCopy 
                        (HANDLE,
                         HANDLE,
                         DWORD);
    HRESULT WINAPI WaitForClientConnection
                        (HANDLE                     hPipe,
                         DWORD                      dwTimeOut);
    DWORD WINAPI WorkingIOProc
                        ();
    DWORD WINAPI ClientNotifThreadProc
                        (PWINDS_NOTIFICATION        pNotif);
};

typedef struct _OBJLIST_NODE
{
    struct _OBJLIST_NODE *      pNext;              // 4
    DWORD                       dwObjID;            // 4
    WINDS_AB_OBJTYPE            ObjType;            // 4
    TCHAR                       szObjAlias[20];     // 20
                                   // Structure size = 32
} OBJLIST_NODE, *POBJLIST_NODE;

class CObjectList
{
public:
    STDMETHODIMP Insert
                    (DWORD                      dwObjID,
                     LPTSTR                     pObjName,
                     WINDS_AB_OBJTYPE           ObjType);
    STDMETHODIMP Delete
                    (DWORD                      dwObjID);
    STDMETHODIMP FindObjFromID
                    (DWORD                      dwObjID,
                     LPTSTR                     pObjName,
                     WINDS_AB_OBJTYPE *         pObjType);
    STDMETHODIMP FindObjFromName
                    (WINDS_AB_OBJTYPE           ObjType,
                     LPTSTR                     pObjName,
                     DWORD *                    pdwObjID);
    STDMETHODIMP FindObjAndTypeFromName
                    (LPTSTR                     pObjName,
                     WINDS_AB_OBJTYPE *         pObjType,
                     DWORD *                    pdwObjID);
    BOOL WINAPI IsAliasNameAvailable
                    (LPTSTR                     pObjName);

public:
    CObjectList();
    ~CObjectList();

private:
    HANDLE              m_hHeap;
    CRITICAL_SECTION    m_csObj;
    POBJLIST_NODE       m_pHead;
};

extern CObjectList GlobalObjectMap;

#endif // _WINDS_H

// End of file for WINDS.H
