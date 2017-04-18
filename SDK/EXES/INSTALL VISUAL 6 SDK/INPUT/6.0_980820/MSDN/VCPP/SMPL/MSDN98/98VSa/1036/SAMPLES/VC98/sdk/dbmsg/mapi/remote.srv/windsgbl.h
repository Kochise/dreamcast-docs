///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      WINDSGBL.H
//
//  Description
//      Global declarations for providers communicating with the WINDS Sample
//      Server Messaging Host.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#ifndef _WINDSGBL_H
#define _WINDSGBL_H

///////////////////////////////////////////////////////////////////////////////
// General constants
#ifdef UNICODE
#define WINDS_RPC_STRING        unsigned short *
#else
#define WINDS_RPC_STRING        unsigned char *
#endif

// WinDS string for the RPC manual binding functions
// The WinDS service uses RPC over the NAMED PIPES protocols and the
// especific end-points for the protocol are listed below: One for the remote
// administrator and one for the MAPI providers
#define WINDS_RPC_PROTOCOL              TEXT("ncacn_np")
#define WINDS_ADMIN_RPC_ENDPOINT        TEXT("\\pipe\\WINDS-ADMIN")
#define WINDS_PROVIDERS_RPC_ENDPOINT    TEXT("\\pipe\\WINDS")

// WinDS registry key for store permanent information
#define WINDS_ADMIN_REGISTRY_KEY        TEXT("Software\\Microsoft\\PSS MAPI Samples\\WinDS Remote Administrator")
#define WINDS_SERVICE_REGISTRY_KEY      TEXT("System\\CurrentControlSet\\Services\\WindsMessagingHost")

// WinDS administrator subkeys
#define SERVER_SUB_KEY                  TEXT("Default Server")

// WinDS service subkeys
#define DATA_FILE_SUB_KEY               TEXT("Data File")


// Name of the address type of the user in the system and for the transports to register for.
#define WINDS_ADDRESS_TYPE                      TEXT("WINDS")

// Name of the Mailslot we use to send notifications to in the client machine
#define AB_WINDS_NOTIFICATION_MAILSLOT          TEXT("WINDS_AB_NOTIFICATIONS")
#define XP_WINDS_NOTIFICATION_MAILSLOT          TEXT("WINDS_XP_NOTIFICATIONS")
#define MS_WINDS_NOTIFICATION_MAILSLOT          TEXT("WINDS_MS_NOTIFICATIONS")
#define ADMIN_WINDS_NOTIFICATION_MAILSLOT       TEXT("WINDS_ADMIN_NOTIFICATIONS")
#define CLIENT_MAILSLOT_SINK_NAME_FORMAT        TEXT("\\\\.\\mailslot\\%s\\%x")
#define SERVER_MAILSLOT_SINK_NAME_FORMAT        TEXT("\\\\%s\\mailslot\\%s\\%x")

// Bulk download/upload pipe name
#define PIPE_NAME_FORMAT                        TEXT("%s\\pipe\\%d")

// Handy buffer size
#define IO_BUFFERSIZE                   1024

#define WINDS_UNICODE                   0x80000000
#define WINDS_ADMINISTRATOR             0x40000000

#define HIDE_IN_DIR                     0x0001
#define OBJECT_DISABLED                 0x0002

#define ADMIN_RIGHTS                    0x0010
#define DL_OWNED                        0x0010


// Field sizes in the object properties structures
#define MAX_ALIAS_SIZE      16
#define MAX_STRING_SIZE     32
#define MAX_PHONE_SIZE      12
#define MAX_COMMENT_SIZE    79
#define MAX_PASSWORD_SIZE   MAX_ALIAS_SIZE

// Constants for the transports
#define TRANSPORT_MESSAGE_EID_SIZE              MAX_ALIAS_SIZE
#define ENTRYID_DATA_FIELD_SIZE                 MAX_ALIAS_SIZE

enum
{
    ROOT_CONTAINER_ID       = 0xFFFFFFFF,
    GATEWAY_CONTAINERS_ID   = 0xFFFFFFFE,
    FAX_CONTAINER_ID        = 0xFFFFFFFD,   // Don't change the order of this (see STORAGE.CPP (ReadABContainerInfo) in the WINDS project)
    SMTP_CONTAINER_ID       = 0xFFFFFFFC,
    EXCHANGE_CONTAINER_ID   = 0xFFFFFFFB,
    GAL_CONTAINER_ID        = 0xFFFFFFFA
};

typedef enum _WINDS_AB_OBJTYPE
{
    UNDEFINED_OBJECT_TYPE       = 0,
    SERVER_USER_MAILBOX         = 1,    // Don't change the order or the values
    SERVER_DISTRIBUTION_LIST    = 2,
    GATEWAY_RECIPIENT           = 3,
    PUBLIC_FOLDER               = 4
} WINDS_AB_OBJTYPE;

typedef struct _PUBLIC_FOLDER_INFO_A
{
    char        szFolderName[MAX_STRING_SIZE+4];
    char        szComments[MAX_COMMENT_SIZE+4];
    DWORD       dwObjID;
    FILETIME    ftCreationTime;
    FILETIME    ftLastModTime;
    DWORD       dwMessageStorageSize;
    DWORD       dwMessageCount;
    DWORD       pdwMessagesIDs;
} PUBLIC_FOLDER_INFO_A, *PPUBLIC_FOLDER_INFO_A;

typedef struct _PUBLIC_FOLDER_INFO_W
{
    WCHAR       szFolderName[MAX_STRING_SIZE+4];
    WCHAR       szComments[MAX_COMMENT_SIZE+4];
    DWORD       dwObjID;
    FILETIME    ftCreationTime;
    FILETIME    ftLastModTime;
    DWORD       dwMessageStorageSize;
    DWORD       dwMessageCount;
    DWORD       pdwMessagesIDs;
} PUBLIC_FOLDER_INFO_W, *PPUBLIC_FOLDER_INFO_W;

typedef struct _PF_MESSAGE_PROPERTIES_A
{
    char    szAuthor[MAX_ALIAS_SIZE+4];
    DWORD   dwObjID;
} PF_MESSAGE_PROPERTIES_A, *PPF_MESSAGE_PROPERTIES_A;

typedef struct _PF_MESSAGE_PROPERTIES_W
{
    WCHAR   szAuthor[MAX_ALIAS_SIZE+4];
    DWORD   dwObjID;
} PF_MESSAGE_PROPERTIES_W, *PPF_MESSAGE_PROPERTIES_W;


typedef struct _MAILBOX_INFO_A
{
    char    szMailboxName[MAX_ALIAS_SIZE+1];
    char    szFullName[MAX_STRING_SIZE+1];
    char    szJobTitle[MAX_STRING_SIZE+1];
    char    szOffice[MAX_STRING_SIZE+1];
    char    szPhone[MAX_PHONE_SIZE+1];
    char    szAltPhone[MAX_PHONE_SIZE+1];
    char    szFax[MAX_PHONE_SIZE+1];
    char    szPassword[MAX_ALIAS_SIZE+1];
    char    szCompany[MAX_STRING_SIZE+1];
    char    szDepartment[MAX_STRING_SIZE+1];
    char    szComments[MAX_COMMENT_SIZE+1];
    char    szManagerName[MAX_STRING_SIZE+1];
    char    szManagerAlias[MAX_STRING_SIZE+1];
    DWORD   dwManagerID;
    DWORD   dwObjID;
    DWORD   dwFlags;
} MAILBOX_INFO_A, *PMAILBOX_INFO_A;

typedef struct _MAILBOX_INFO_W
{
    WCHAR   szMailboxName[MAX_ALIAS_SIZE+1];
    WCHAR   szFullName[MAX_STRING_SIZE+1];
    WCHAR   szJobTitle[MAX_STRING_SIZE+1];
    WCHAR   szOffice[MAX_STRING_SIZE+1];
    WCHAR   szPhone[MAX_PHONE_SIZE+1];
    WCHAR   szAltPhone[MAX_PHONE_SIZE+1];
    WCHAR   szFax[MAX_PHONE_SIZE+1];
    WCHAR   szPassword[MAX_ALIAS_SIZE+1];
    WCHAR   szCompany[MAX_STRING_SIZE+1];
    WCHAR   szDepartment[MAX_STRING_SIZE+1];
    WCHAR   szComments[MAX_COMMENT_SIZE+1];
    WCHAR   szManagerName[MAX_STRING_SIZE+1];
    WCHAR   szManagerAlias[MAX_STRING_SIZE+1];
    DWORD   dwManagerID;
    DWORD   dwObjID;
    DWORD   dwFlags;
} MAILBOX_INFO_W, *PMAILBOX_INFO_W;

typedef struct _DIST_LIST_INFO_A
{
    char                szDLAlias[MAX_ALIAS_SIZE+1];
    char                szDLFullName[MAX_STRING_SIZE+1];
    DWORD               dwObjID;
    DWORD               dwFlags;
    char                szOwnerAlias[MAX_ALIAS_SIZE+1];
    char                szOwnerName[MAX_STRING_SIZE+1];
    DWORD               dwOwnerID;
    char                szComments[MAX_COMMENT_SIZE+1];
    DWORD               dwMemberCount;
    LPVOID              pMembers;
} DIST_LIST_INFO_A, *PDIST_LIST_INFO_A;

typedef struct _DIST_LIST_INFO_W
{
    WCHAR               szDLAlias[MAX_ALIAS_SIZE+1];
    WCHAR               szDLFullName[MAX_STRING_SIZE+1];
    DWORD               dwObjID;
    DWORD               dwFlags;
    WCHAR               szOwnerAlias[MAX_ALIAS_SIZE+1];
    WCHAR               szOwnerName[MAX_STRING_SIZE+1];
    DWORD               dwOwnerID;
    WCHAR               szComments[MAX_COMMENT_SIZE+1];
    DWORD               dwMemberCount;
    LPVOID              pMembers;
} DIST_LIST_INFO_W, *PDIST_LIST_INFO_W;

// UNICODE/ANSI macro for the structures
#ifdef UNICODE
#error WINDS: UNICODE has not been implemented yet. IrvingD 9/11/95
#define MAILBOX_INFO                MAILBOX_INFO_W
#define PMAILBOX_INFO               PMAILBOX_INFO_W
#define DIST_LIST_INFO              DIST_LIST_INFO_W
#define PDIST_LIST_INFO             PDIST_LIST_INFO_W
#define PUBLIC_FOLDER_INFO          PUBLIC_FOLDER_INFO_W
#define PPUBLIC_FOLDER_INFO         PPUBLIC_FOLDER_INFO_W
#define PF_MESSAGE_PROPERTIES       PF_MESSAGE_PROPERTIES_W
#define PPF_MESSAGE_PROPERTIES      PPF_MESSAGE_PROPERTIES_W
#else
#define MAILBOX_INFO                MAILBOX_INFO_A
#define PMAILBOX_INFO               PMAILBOX_INFO_A
#define DIST_LIST_INFO              DIST_LIST_INFO_A
#define PDIST_LIST_INFO             PDIST_LIST_INFO_A
#define PUBLIC_FOLDER_INFO          PUBLIC_FOLDER_INFO_A
#define PPUBLIC_FOLDER_INFO         PPUBLIC_FOLDER_INFO_A
#define PF_MESSAGE_PROPERTIES       PF_MESSAGE_PROPERTIES_A
#define PPF_MESSAGE_PROPERTIES      PPF_MESSAGE_PROPERTIES_A
#endif

typedef union _WINDS_OBJS_INFO
{
    DWORD               dwFlags;
    MAILBOX_INFO        MB;
    DIST_LIST_INFO      DL;
    PUBLIC_FOLDER_INFO  PF;
} WINDS_OBJS_INFO;

typedef struct _AB_ENTRY_INFO
{
    WINDS_OBJS_INFO     Info;
    WINDS_AB_OBJTYPE    Type;
} AB_ENTRY_INFO, *PAB_ENTRY_INFO;


///////////////////////////////////////////////////////////////////////////////
// Message Transport Support

// Command numbers for telling the remote server what to do (from a transport)
typedef enum tagMID
{
    MSG_DOWNLOAD, 
    MSG_DELETE,
    MSG_MOVE,
    OP_STARTED,
    OP_COMPLETE,
    OP_FAILED,
    GOODBYE,
    UNMARKED
} MID;

// Command message header

typedef union _MSG_HDR_INFO
{
    BYTE    EID[TRANSPORT_MESSAGE_EID_SIZE];
    ULONG   ulMsgLen;
} MSG_HDR_INFO;

typedef struct _MSG_HDR
{
    MID             ulMID;
    MSG_HDR_INFO    Info;
} MSG_HDR;

///////////////////////////////////////////////////////////////////////////////
// Client/Server notification support 

enum
{
    WINDS_NOTIF_ON_USER         = 0x0001,
    WINDS_NOTIF_ON_XP           = 0x0002,
    WINDS_NOTIF_ON_AB           = 0x0004,
    WINDS_NOTIF_ON_MS           = 0x0008
};

typedef enum _WINDS_NOTIF_EVENT
{
    GENERAL_NOTIF_MIN           = 0x0000,
    LOGGED_USER_PROPS_CHANGED   = 0x0000,
    SERVER_IS_SHUTTING_DOWN     = 0x0001,
    SERVER_HAS_RESTARTED        = 0x0002,
    RESET_LINKS_WITH_SERVER     = 0x0003,
    GENERAL_NOTIF_MAX           = 0x000F,

    XP_NOTIF_MIN                = 0x0010,
    XP_NEW_MAIL_ARRIVED         = 0x0010,
    XP_NOTIF_MAX                = 0x00F0,

    AB_NOTIF_MIN                = 0x0100,
    AB_USER_ADDED               = 0x0100,
    AB_USER_MODIFIED            = 0x0200,
    AB_USER_DELETED             = 0x0300,
    AB_DL_ADDED                 = 0x0400,
    AB_DL_MODIFIED              = 0x0500,
    AB_DL_DELETED               = 0x0600,
    AB_GET_LOCAL_ABDATA_NOW     = 0x0700,
    AB_NOTIF_MAX                = 0x0F00,

    MS_NOTIF_MIN                = 0x1000,
    MS_MESSAGE_ADDED            = 0x1000,
    MS_MESSAGE_MODIFIED         = 0x2000,
    MS_MESSAGE_DELETED          = 0x3000,
    MS_FOLDER_ADDED             = 0x4000,
    MS_FOLDER_MODIFIED          = 0x5000,
    MS_FOLDER_DELETED           = 0x6000,
    MS_NOTIF_MAX                = 0xF000

} WINDS_NOTIF_EVENT;

typedef struct _WINDS_NOTIFICATION
{
    WINDS_NOTIF_EVENT   Event;
    FILETIME            ftEventTime;
    WINDS_OBJS_INFO     Info;
} WINDS_NOTIFICATION, *PWINDS_NOTIFICATION;

///////////////////////////////////////////////////////////////////////////////
// Generic exception class for C++'s throw and catch

class CException
{
public:
    CException()
    {
        m_hResult = E_FAIL;
    }
    CException (HRESULT hResult)
    {
        if (0 == hResult)
        {
            hResult = E_FAIL;
        }
        m_hResult = hResult;
    }
    inline HRESULT WINAPI GetError()
    {
        return m_hResult;
    }
private:
    HRESULT m_hResult;
};

#endif // _WINDSGBL_H

// End of file for WINDSGBL.H
