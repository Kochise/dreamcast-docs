/*
 -  C L I E N T . H
 -
 *  Purpose:
 *      Header file for the sample mail client based on Extended MAPI.
 *
 *      Copyright 1995, Microsoft Corporation. All Rights Reserved.
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__


/* Menu Item IDs */

#define IDM_LOGON       100
#define IDM_LOGOFF      101
#define IDM_EXIT        102
#define IDM_READ        103
#define IDM_SEND        104
#define IDM_ABOUT       105
#define IDM_OPEN        106
#define IDM_HIER        107

#define IDM_ROUTE       108

#define IDM_NEWFORM     109
/* Resource IDs */

#define ICON_NOMAIL     200
#define ICON_MAIL       201
#define IDB_ENVELOPE    300


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
#define IDC_LINE1       -1
#define IDC_LINE2       -1
#define IDC_CATTACHMENT 113
#define IDT_CATTACHMENT -1


#define IDC_ADDROUTESLIP 115

//RouteNote control IDs
#define IDC_RTCC            101
#define IDT_RTCC            -1
#define IDT_RTSUBJECT           -1
#define IDC_RTSUBJECT           102
#define IDC_RTNOTE          103
#define IDC_RTROUTE         104
#define IDC_RTATTACH            105
#define IDC_RTEDITROUTESLIP 106
#define IDC_RTATTACHLIST        107
#define IDT_RTATTACHLIST        108
#define IDC_RTSAVEATTACH        109
#define IDC_RTDELATTACH         110

/* InBox Control IDs */

#define IDT_MSG         101
#define IDC_MSG         102
#define IDC_NEW         103
#define IDC_READ        104
#define IDC_DELETE      105
#define IDC_CLOSE       106
#define IDC_DOWN                107     // Hierarchy Table only
#define IDC_FLUSH       108

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


/* Options Control IDs */

#define IDC_RETURN      101


/* Details Control IDs */

#define IDT_NAME        100
#define IDC_NAME        101
#define IDT_TYPE        102
#define IDC_TYPE        103
#define IDT_ADDR        104
#define IDC_ADDR        105

/* About Box Control IDs */

#define IDC_VERSION             101



/* Route Box Control IDs*/

#define IDC_ROUTE               100            
#define IDC_ADDRLISTOLD         101
#define IDC_ADDRLISTACTIVE      102
#define IDC_ADDADDR             103
#define IDC_REMOVEADDR          104
#define IDC_MOVEUP              105
#define IDC_MOVEDOWN            106
#define IDC_STATIC                      -1

#define LENGTHOLD        80
#define LENGTHACTIVE 80
#define LBLENGTH (LENGTHOLD + LENGTHACTIVE) /*sum of the lengths of the two listboxes in RouteNote DlgBox*/
#define DELTA 5  /*distance between the bottom of the first LB and the top of the second
                    DELATA is not used directly in the .rc file. it has to be calculated manualy*/
#define LBX 70  /* The x coordinate of the left edges of the listboxes*/
#define DELTAX 140 /*the width of the listboxes*/
#define OLDY   5        /*the y coordinate of the top of the first listbox*/
#define MINY   40 /*the min height of a listbox*/



/* String Table IDs */

#define MAPI_ERROR_MAX          30

#define IDS_LOGONFAIL           (MAPI_ERROR_MAX + 1)
#define IDS_ADDRBOOKFAIL        (MAPI_ERROR_MAX + 2)
#define IDS_RESOLVEFAIL         (MAPI_ERROR_MAX + 3)
#define IDS_UNRESOLVEDNAMES     (MAPI_ERROR_MAX + 4)
#define IDS_SENDERROR           (MAPI_ERROR_MAX + 5)
#define IDS_DETAILS_TOO_MANY    (MAPI_ERROR_MAX + 6)
#define IDS_DETAILSFAIL         (MAPI_ERROR_MAX + 7)
#define IDS_NORECIPS            (MAPI_ERROR_MAX + 8)
#define IDS_SAVEATTACHERROR     (MAPI_ERROR_MAX + 9)
#define IDS_READFAIL            (MAPI_ERROR_MAX + 10)
#define IDS_STORETBLFAIL        (MAPI_ERROR_MAX + 11)
#define IDS_QUERYROWFAIL        (MAPI_ERROR_MAX + 12)
#define IDS_OPENSTOREFAIL       (MAPI_ERROR_MAX + 13)
#define IDS_STATUSTBLFAIL       (MAPI_ERROR_MAX + 14)
#define IDS_OPENFOLDERFAIL      (MAPI_ERROR_MAX + 15)
#define IDS_GETRCVFAIL          (MAPI_ERROR_MAX + 16)
#define IDS_SETRCVFAIL          (MAPI_ERROR_MAX + 17)
#define IDS_SETPROPFAIL         (MAPI_ERROR_MAX + 18)
#define IDS_NOENTRYID           (MAPI_ERROR_MAX + 19)
#define IDS_OPERATION           (MAPI_ERROR_MAX + 20)
#define IDS_NODEFAULTSTORE      (MAPI_ERROR_MAX + 21)
#define IDS_SETCOLFAIL          (MAPI_ERROR_MAX + 22)
#define IDS_CRTOUTMSG                   (MAPI_ERROR_MAX + 23)
#define IDS_SHOWFORM                    (MAPI_ERROR_MAX + 24)
#define IDS_OPENAB                              (MAPI_ERROR_MAX + 25)
#define IDS_INIDIAG                             (MAPI_ERROR_MAX + 26)
#define IDS_UNXERR                              (MAPI_ERROR_MAX + 27)
#define IDS_OPENOUTF                    (MAPI_ERROR_MAX + 28)
#define IDS_MAPIINIF                    (MAPI_ERROR_MAX + 29)
#define IDS_OPENSTOREWARN               (MAPI_ERROR_MAX + 30)
#define IDS_OPENABWARN                  (MAPI_ERROR_MAX + 31)
#define IDS_LASTRECIP                   (MAPI_ERROR_MAX + 32)

#define IDS_IPM                 (MAPI_ERROR_MAX + 42)
#define IDS_IPM_COMMENT         (MAPI_ERROR_MAX + 43)
#define IDS_INBOX               (MAPI_ERROR_MAX + 44)
#define IDS_INBOX_COMMENT       (MAPI_ERROR_MAX + 45)
#define IDS_OUTBOX              (MAPI_ERROR_MAX + 46)
#define IDS_OUTBOX_COMMENT      (MAPI_ERROR_MAX + 47)
#define IDS_SENTMAIL            (MAPI_ERROR_MAX + 48)
#define IDS_SENTMAIL_COMMENT    (MAPI_ERROR_MAX + 49)
#define IDS_FILTER              (MAPI_ERROR_MAX + 50)
#define IDS_OPENOUTB                    (MAPI_ERROR_MAX + 51)

/* Manifest Constants */

#define MBS_ERROR           (MB_ICONSTOP | MB_OK)
#define MBS_INFO            (MB_ICONINFORMATION | MB_OK)
#define MBS_OOPS            (MB_ICONEXCLAMATION | MB_OK)

/* Structure Definitions */

typedef struct _msgid *LPMSGID;

typedef struct _msgid
{
    ULONG           cbEID;
    LPENTRYID       lpEID;
    BOOL        fHasAttach;
    BOOL        fUnRead;
    LPSTR       lpszFrom;
    LPSTR       lpszSubject;
    LPSTR       lpszDateRec;
    LPMSGID     lpPrev;
    LPMSGID     lpNext;
} MSGID;

typedef struct _inboxdata
{
    LPMSGID         lpMsgIdList;
    LPMAPIFOLDER pfld;
} INBOXDATA, FAR * LPINBOXDATA;


typedef struct _oar *LPOAR;

typedef struct _oar
{
    LPOAR                   lpNext;
    LPOAR                   lpPrev;
    ULONG                   cValues;
    LPSPropValue    lpProps;
} OAR;

/* Types of MAPI Tables shown by common dialog */
enum {
    iStores,
    iHierarchy
};

/* Data structure used by CommonDlgProc */
typedef struct {
    int             iDlgType;       // dialog type.  see "enum" above
    LPOAR           poarHead;       // chain of rows within the dialog
    ULONG           cbEntryID;
    LPENTRYID       lpEntryID;
} DIALOGDATA, FAR * LPDIALOGDATA;



/* Globals */
extern LPMAPISESSION pses;
extern LPADRBOOK pabAddrB;
extern LPMDB pmdb;
extern HANDLE hInst;
extern HCURSOR hWaitCur;
extern LPMAPIFOLDER pfldOutBox;
extern LPSPropValue pvalSentMailEID;
/* Function Prototypes */

int  PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
void DeinitApplication(void);
BOOL ClientLogon(HWND);
VOID ClientLogoff(HWND);
BOOL InitMAPI (HWND);
void DeinitMAPI();
LPMDB OpenDefaultStore(HWND); 
long FAR PASCAL MainWndProc(HWND, UINT, UINT, LPARAM);
BOOL CALLBACK CommonDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK InBoxDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ComposeDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ReadMailDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK OptionsDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DetailsDlgProc(HWND, UINT, WPARAM, LPARAM);
void    MakeMessageBox(HWND, SCODE, UINT, LPMAPIERROR, UINT);
HRESULT HrCreateChildFolder (HWND, LPMAPIFOLDER, ULONG, ULONG, LPTSTR, ULONG, LPMAPIFOLDER FAR *);
VOID    PopulateStores ( HWND hDlg, LPOAR FAR * ppoarHead, int idlgType, ULONG cb, LPENTRYID lpeid);
VOID    FreeOarList (LPOAR FAR *ppoarHead);
VOID    DrawOarItem (DRAWITEMSTRUCT FAR * pdis, int idlgType);
VOID    PopulateMessages( HWND hDlg, LPINBOXDATA pibData );
LPMSGID MakeMsgNode(LPSRow);
LPMSGID FindNode (LPMSGID lpMsgHead, LPENTRYID pEntryID, ULONG cbEntryID);
void    InsertMsgNode(LPMSGID, LPMSGID *);
void    DeleteMsgNode(LPMSGID, LPMSGID *);
void    FreeMsgList(LPMSGID);
void    LogSendMail(ULONG);
void    ToggleMenuState(HWND, BOOL);   
void    FormatMessageID(ULONG, LPBYTE, LPSTR);
void    FormatFILETIME(FILETIME *, LPSTR);
LPDIALOGDATA CreateDialogData(int iDlgType);
BOOL READ_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
BOOL READ_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void INBOX_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
LONG MAIN_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL Common_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
HRESULT DeliverNow(HWND hWnd);
void SecureMenu(HWND hWnd, BOOL fBeforeLogon);



#endif 
