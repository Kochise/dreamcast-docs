/*
 -  C M C C L I . H
 -
 *  Purpose:
 *      Header file for the sample mail client based on CMC.
 *
 */

#ifndef CMC_H
//#include <xcmc.h>
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

/* Menu Item IDs */

#define IDM_LOGON           100
#define IDM_LOGOFF          101
#define IDM_EXIT            102
#define IDM_COMPOSE_CMC     103
#define IDM_COMPOSE_CUSTOM  104
#define IDM_READ            105
#define IDM_ADDRBOOK        106
#define IDM_ABOUT           107

/* Resource IDs */

#define ICON_NOMAIL     200
#define ICON_MAIL       201
#define IDREAD          300
#define IDREADA         301
#define IDUNREAD        302
#define IDUNREADA       303


/* Address Book Control IDs */

#define IDT_ADDRESS     101
#define IDC_ADDRESS     102
#define IDT_LIST        103
#define IDC_LIST        104
#define IDC_ADD         105
#define IDC_REMOVE      106


/* Compose Note Control IDs */

#define IDC_SEND        101
#define IDC_RESOLVE     102
#define IDC_ATTACH      103
#define IDC_OPTIONS     104
#define IDC_ADDRBOOK    105
#define IDT_TO          106
#define IDC_TO          107
#define IDT_CC          108
#define IDC_CC          109
#define IDT_SUBJECT     110
#define IDC_SUBJECT     111
#define IDC_NOTE        112
#define IDC_LINE1       113
#define IDC_LINE2       114


/* InBox Control IDs */

#define IDT_MSG         101
#define IDC_MSG         102
#define IDC_NEW         103
#define IDC_READ        104
#define IDC_DELETE      105
#define IDC_CLOSE       106


/* ReadNote Control IDs */

#define IDC_SAVECHANGES 101
#define IDC_SAVEATTACH  102
#define IDC_REPLY       103
#define IDC_REPLYALL    104
#define IDC_FORWARD     105
#define IDT_RFROM       106
#define IDT_RDATE       107
#define IDT_RTO         108
#define IDT_RCC         109
#define IDT_RSUBJECT    110
#define IDC_RFROM       111
#define IDC_RDATE       112
#define IDC_RTO         113
#define IDC_RCC         114
#define IDC_RSUBJECT    115
#define IDC_READNOTE    116
#define IDT_ATTACHMENT  117
#define IDC_ATTACHMENT  118
#define IDC_LINE3       119
#define IDC_LINE4       120


/* Options Control IDs */

#define IDC_RETURN      101
#define IDC_PRIORITY    102
#define IDC_URGENT      103
#define IDC_NORMAL      104
#define IDC_LOW         105


/* About Box Control IDs */

#define IDC_VERSION     101
#define IDC_STATIC1     102
#define IDC_STATIC2     103
#define IDC_STATIC3     104


/* String Table IDs */

#define CMC_E_MAX 40

#define IDS_LOGONFAIL           (CMC_E_MAX + 1)
#define IDS_ADDRBOOKFAIL        (CMC_E_MAX + 2)
#define IDS_RESOLVEFAIL         (CMC_E_MAX + 3)
#define IDS_UNRESOLVEDNAMES     (CMC_E_MAX + 4)
#define IDS_SENDERROR           (CMC_E_MAX + 5)
#define IDS_NORECIPS            (CMC_E_MAX + 6)
#define IDS_SAVEATTACHERROR     (CMC_E_MAX + 7)
#define IDS_READFAIL            (CMC_E_MAX + 8)
#define IDS_MAKENEWFAIL         (CMC_E_MAX + 9)

#define IDS_FILTER              (CMC_E_MAX + 50)

/* Manifest Constants */

#define ADDR_MAX            128
#define MAXUSERS            10
#define TO_EDIT_MAX         512
#define CC_EDIT_MAX         512
#define SUBJECT_EDIT_MAX    128
#define NOTE_LINE_MAX       1024
#define FILE_ATTACH_MAX     32

/* Message Box styles */

#define MBS_ERROR           (MB_ICONSTOP | MB_OK)
#define MBS_INFO            (MB_ICONINFORMATION | MB_OK)
#define MBS_OOPS            (MB_ICONEXCLAMATION | MB_OK)

/* Structure Definitions */

typedef struct _msgid FAR *LPMSGID;

typedef struct _msgid
{
    CMC_message_reference   *message_reference;
    CMC_string              from;
    CMC_string              subject;
    CMC_time                time_sent;
    CMC_boolean             fHasAttach;
    CMC_boolean             fRead;
    LPMSGID                 lpPrev;
    LPMSGID                 lpNext;
} MSGID;

/* Function Prototypes */

int  PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
void DeinitApplication(void);
BOOL InitSimpleCMC (void);
void DeinitSimpleCMC(void);
long FAR PASCAL MainWndProc(HWND, UINT, UINT, LPARAM);
BOOL FAR PASCAL AboutDlgProc(HWND, UINT, UINT, LONG);
BOOL FAR PASCAL InBoxDlgProc(HWND, UINT, UINT, LONG);
BOOL FAR PASCAL ReadMailDlgProc(HWND, UINT, UINT, LONG);
BOOL FAR PASCAL DetailsDlgProc (HWND, UINT, UINT, LONG);
BOOL FAR PASCAL ComposeDlgProc (HWND, UINT, UINT, LONG);
BOOL FAR PASCAL OptionsDlgProc (HWND, UINT, UINT, LONG);
void SecureMenu(HWND hWnd, BOOL fBeforeLogon);
     
void SaveFileAttachments(HWND, CMC_attachment FAR *);
void MakeDisplayNameStr(LPSTR, CMC_enum, ULONG, CMC_recipient FAR *);
ULONG CopyAttachment (CMC_attachment FAR *,CMC_attachment FAR *,CMC_attachment FAR *);
CMC_return_code ResolveFriendlyNames (HWND, LPSTR, CMC_enum, ULONG *, CMC_recipient FAR * *);
CMC_return_code CopyRecipient (CMC_recipient FAR *,CMC_recipient FAR *,CMC_recipient FAR *);
CMC_return_code SaveMsgChanges (HWND,CMC_message far *);
CMC_return_code MakeNewMessage (CMC_message far *, CMC_flags);
CMC_return_code GetNextFile (HWND, ULONG, ULONG *, CMC_attachment FAR * *);
BOOL FNameInList (LPSTR, ULONG, CMC_recipient FAR *);

void DrawMsgItem (DRAWITEMSTRUCT *);
void DrawMsgIcon(HDC , HBITMAP , int , int , int , int);

LPMSGID MakeMsgNode (CMC_message_summary FAR *);
LPMSGID FindNode (LPMSGID, CMC_message_reference FAR *);
void    InsertMsgNode (LPMSGID, LPMSGID *);
void    DeleteMsgNode (LPMSGID, LPMSGID *);
void    FreeMsgList (LPMSGID);

void ConvertDateRec (CMC_time far *, LPSTR);
void MakeMessageBox(HWND, ULONG, UINT, UINT);
void ToggleMenuState(HWND, BOOL);
void LogSendMail(ULONG ulResult);

BOOL fCMCInstalled(void);

/* CMC functions */

extern HINSTANCE    hlibCMC;

typedef CMC_return_code (FAR PASCAL *LPFNCMCQUERYCONFIGURATION)
    (CMC_session_id session, CMC_enum item,CMC_buffer reference,CMC_extension FAR *config_extensions);

extern LPFNCMCQUERYCONFIGURATION lpfnCMCQueryConfiguration;

#define CMCQueryConfiguration           (*lpfnCMCQueryConfiguration)


typedef CMC_return_code (FAR PASCAL *LPFNCMCLOGON)(
    CMC_string              service,
    CMC_string              user,
    CMC_string              password,
    CMC_enum                character_set,
    CMC_ui_id               ui_id,
    CMC_uint16              caller_cmc_version,
    CMC_flags               logon_flags,
    CMC_session_id FAR      *session,
    CMC_extension FAR       *logon_extensions
);

extern LPFNCMCLOGON lpfnCMCLogon;

#define CMCLogon            (*lpfnCMCLogon)

typedef CMC_return_code (FAR PASCAL *LPFNCMCLOGOFF)(
    CMC_session_id          session,
    CMC_ui_id               ui_id,
    CMC_flags               logoff_flags,
    CMC_extension FAR       *logoff_extensions
);

extern LPFNCMCLOGOFF lpfnCMCLogoff;

#define CMCLogoff           (*lpfnCMCLogoff)


typedef CMC_return_code (FAR PASCAL *LPFNCMCFREE)(
    CMC_buffer              memory
);

extern LPFNCMCFREE lpfnCMCFree;

#define CMCFree     (*lpfnCMCFree)

typedef CMC_return_code (FAR PASCAL *LPFNCMCLOOKUP)(
    CMC_session_id          session,
    CMC_recipient FAR       *recipient_in,
    CMC_flags               look_up_flags,
    CMC_ui_id               ui_id,
    CMC_uint32 FAR          *count,
    CMC_recipient FAR * FAR *recipient_out,
    CMC_extension FAR       *look_up_extensions
);

extern LPFNCMCLOOKUP lpfnCMCLookUp;

#define CMCLookUp (*lpfnCMCLookUp)


typedef CMC_return_code (FAR PASCAL *LPFNCMCLIST)(
    CMC_session_id          session,
    CMC_string              message_type,
    CMC_flags               list_flags,
    CMC_message_reference   *seed,
    CMC_uint32 FAR          *count,
    CMC_ui_id               ui_id,
    CMC_message_summary FAR * FAR *result,
    CMC_extension FAR       *list_extensions
);

extern LPFNCMCLIST lpfnCMCList;

#define CMCList  (*lpfnCMCList)

typedef CMC_return_code (FAR PASCAL *LPFNCMCSEND)(
    CMC_session_id          session,
    CMC_message FAR         *message,
    CMC_flags               send_flags,
    CMC_ui_id               ui_id,
    CMC_extension FAR       *send_extensions
);

extern LPFNCMCSEND lpfnCMCSend;

#define CMCSend (*lpfnCMCSend)

typedef CMC_return_code (FAR PASCAL *LPFNCMCREAD)(
    CMC_session_id          session,
    CMC_message_reference   *message_reference,
    CMC_flags               read_flags,
    CMC_message FAR * FAR   *message,
    CMC_ui_id               ui_id,
    CMC_extension FAR       *read_extensions
);

extern LPFNCMCREAD lpfnCMCRead;

#define CMCRead (*lpfnCMCRead)

typedef CMC_return_code (FAR PASCAL *LPFNCMCACTON)(
    CMC_session_id          session,
    CMC_message_reference   *message_reference,
    CMC_enum                operation,
    CMC_flags               act_on_flags,
    CMC_ui_id               ui_id,
    CMC_extension FAR       *act_on_extensions
);

extern LPFNCMCACTON lpfnCMCActOn;

#define CMCActOn (*lpfnCMCActOn)

