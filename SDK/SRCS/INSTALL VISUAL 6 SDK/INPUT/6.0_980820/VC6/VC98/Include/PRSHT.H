
/*****************************************************************************\
*                                                                             *
* prsht.h - - Interface for the Windows Property Sheet Pages                  *
*                                                                             *
* Version 1.0                                                                 *
*                                                                             *
* Copyright 1991-1998, Microsoft Corp.      All rights reserved.          *
*                                                                             *
\*****************************************************************************/

#ifndef _PRSHT_H_
#define _PRSHT_H_

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#else
#if (_WIN32_IE < 0x0400) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0500)
#error _WIN32_IE setting conflicts with _WIN32_WINNT setting
#endif
#endif

//
// Define API decoration for direct importing of DLL references.
//
#ifndef WINCOMMCTRLAPI
#if !defined(_COMCTL32_) && defined(_WIN32)
#define WINCOMMCTRLAPI DECLSPEC_IMPORT
#else
#define WINCOMMCTRLAPI
#endif
#endif // WINCOMMCTRLAPI

#ifndef CCSIZEOF_STRUCT
#define CCSIZEOF_STRUCT(structname, member)  (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))
#endif

//
// For compilers that don't support nameless unions
//
#ifndef DUMMYUNIONNAME
#ifdef NONAMELESSUNION
#define DUMMYUNIONNAME   u
#define DUMMYUNIONNAME2  u2
#define DUMMYUNIONNAME3  u3
#define DUMMYUNIONNAME4  u4
#define DUMMYUNIONNAME5  u5
#else
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#define DUMMYUNIONNAME4
#define DUMMYUNIONNAME5
#endif
#endif // DUMMYUNIONNAME

#ifdef __cplusplus
extern "C" {
#endif


#ifndef SNDMSG
#ifdef __cplusplus
#ifndef _MAC
#define SNDMSG ::SendMessage
#else
#define SNDMSG ::AfxSendMessage
#endif
#else
#ifndef _MAC
#define SNDMSG SendMessage
#else
#define SNDMSG AfxSendMessage
#endif
#endif
#endif // ifndef SNDMSG

#define MAXPROPPAGES            100

struct _PSP;
typedef struct _PSP FAR* HPROPSHEETPAGE;

#ifndef MIDL_PASS
struct _PROPSHEETPAGEA;
struct _PROPSHEETPAGEW;
#endif

typedef UINT (CALLBACK FAR * LPFNPSPCALLBACKA)(HWND hwnd, UINT uMsg, struct _PROPSHEETPAGEA FAR *ppsp);
typedef UINT (CALLBACK FAR * LPFNPSPCALLBACKW)(HWND hwnd, UINT uMsg, struct _PROPSHEETPAGEW FAR *ppsp);

#ifdef UNICODE
#define LPFNPSPCALLBACK         LPFNPSPCALLBACKW
#else
#define LPFNPSPCALLBACK         LPFNPSPCALLBACKA
#endif

#define PSP_DEFAULT                0x00000000
#define PSP_DLGINDIRECT            0x00000001
#define PSP_USEHICON               0x00000002
#define PSP_USEICONID              0x00000004
#define PSP_USETITLE               0x00000008
#define PSP_RTLREADING             0x00000010

#define PSP_HASHELP                0x00000020
#define PSP_USEREFPARENT           0x00000040
#define PSP_USECALLBACK            0x00000080
#define PSP_PREMATURE              0x00000400

#if (_WIN32_IE >= 0x0400)
//----- New flags for wizard97 --------------
#define PSP_HIDEHEADER             0x00000800
#define PSP_USEHEADERTITLE         0x00001000
#define PSP_USEHEADERSUBTITLE      0x00002000
//-------------------------------------------
#endif


#define PSPCB_RELEASE           1
#define PSPCB_CREATE            2

#define PROPSHEETPAGEA_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEA, pcRefParent)
#define PROPSHEETPAGEW_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEW, pcRefParent)

typedef struct _PROPSHEETPAGEA {
        DWORD           dwSize;
        DWORD           dwFlags;
        HINSTANCE       hInstance;
        union {
            LPCSTR          pszTemplate;
#ifdef _WIN32
            LPCDLGTEMPLATE  pResource;
#else
            const VOID FAR *pResource;
#endif
        } DUMMYUNIONNAME;
        union {
            HICON       hIcon;
            LPCSTR      pszIcon;
        } DUMMYUNIONNAME2;
        LPCSTR          pszTitle;
        DLGPROC         pfnDlgProc;
        LPARAM          lParam;
        LPFNPSPCALLBACKA pfnCallback;
        UINT FAR * pcRefParent;

#if (_WIN32_IE >= 0x0400)
        LPCSTR pszHeaderTitle;    // this is displayed in the header
        LPCSTR pszHeaderSubTitle; //
#endif
} PROPSHEETPAGEA, FAR *LPPROPSHEETPAGEA;
typedef const PROPSHEETPAGEA FAR *LPCPROPSHEETPAGEA;

typedef struct _PROPSHEETPAGEW {
        DWORD           dwSize;
        DWORD           dwFlags;
        HINSTANCE       hInstance;
        union {
            LPCWSTR          pszTemplate;
#ifdef _WIN32
            LPCDLGTEMPLATE  pResource;
#else
            const VOID FAR *pResource;
#endif
        }DUMMYUNIONNAME;
        union {
            HICON       hIcon;
            LPCWSTR      pszIcon;
        }DUMMYUNIONNAME2;
        LPCWSTR          pszTitle;
        DLGPROC         pfnDlgProc;
        LPARAM          lParam;
        LPFNPSPCALLBACKW pfnCallback;
        UINT FAR * pcRefParent;
        
#if (_WIN32_IE >= 0x0400)
        LPCWSTR pszHeaderTitle;    // this is displayed in the header
        LPCWSTR pszHeaderSubTitle; ///
#endif
} PROPSHEETPAGEW, FAR *LPPROPSHEETPAGEW;
typedef const PROPSHEETPAGEW FAR *LPCPROPSHEETPAGEW;

#ifdef UNICODE
#define PROPSHEETPAGE           PROPSHEETPAGEW
#define LPPROPSHEETPAGE         LPPROPSHEETPAGEW
#define LPCPROPSHEETPAGE        LPCPROPSHEETPAGEW
#define PROPSHEETPAGE_V1_SIZE PROPSHEETPAGEW_V1_SIZE
#else
#define PROPSHEETPAGE           PROPSHEETPAGEA
#define LPPROPSHEETPAGE         LPPROPSHEETPAGEA
#define LPCPROPSHEETPAGE        LPCPROPSHEETPAGEA
#define PROPSHEETPAGE_V1_SIZE PROPSHEETPAGEA_V1_SIZE
#endif


#define PSH_DEFAULT             0x00000000
#define PSH_PROPTITLE           0x00000001
#define PSH_USEHICON            0x00000002
#define PSH_USEICONID           0x00000004
#define PSH_PROPSHEETPAGE       0x00000008
#define PSH_WIZARDHASFINISH     0x00000010
#define PSH_WIZARD              0x00000020
#define PSH_USEPSTARTPAGE       0x00000040
#define PSH_NOAPPLYNOW          0x00000080
#define PSH_USECALLBACK         0x00000100
#define PSH_HASHELP             0x00000200
#define PSH_MODELESS            0x00000400
#define PSH_RTLREADING          0x00000800
#define PSH_WIZARDCONTEXTHELP   0x00001000

#if (_WIN32_IE >= 0x0400)
//----- New flags for wizard97 -----------
#define PSH_WIZARD97            0x00002000  
// 0x00004000 was not used by any previous release
#define PSH_WATERMARK           0x00008000
#define PSH_USEHBMWATERMARK     0x00010000  // user pass in a hbmWatermark instead of pszbmWatermark
#define PSH_USEHPLWATERMARK     0x00020000  //
#define PSH_STRETCHWATERMARK    0x00040000  // stretchwatermark also applies for the header
#define PSH_HEADER              0x00080000
#define PSH_USEHBMHEADER        0x00100000
#define PSH_USEPAGELANG         0x00200000  // use frame dialog template matched to page
//----------------------------------------
#endif


typedef int (CALLBACK *PFNPROPSHEETCALLBACK)(HWND, UINT, LPARAM);

#define PROPSHEETHEADERA_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETHEADERA, pfnCallback)
#define PROPSHEETHEADERW_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETHEADERW, pfnCallback)

typedef struct _PROPSHEETHEADERA {
        DWORD           dwSize;
        DWORD           dwFlags;
        HWND            hwndParent;
        HINSTANCE       hInstance;
        union {
            HICON       hIcon;
            LPCSTR      pszIcon;
        }DUMMYUNIONNAME;
        LPCSTR          pszCaption;

        UINT            nPages;
        union {
            UINT        nStartPage;
            LPCSTR      pStartPage;
        }DUMMYUNIONNAME2;
        union {
            LPCPROPSHEETPAGEA ppsp;
            HPROPSHEETPAGE FAR *phpage;
        }DUMMYUNIONNAME3;
        PFNPROPSHEETCALLBACK pfnCallback;

#if (_WIN32_IE >= 0x0400)
        union {
            HBITMAP hbmWatermark;
            LPCSTR pszbmWatermark;
        } DUMMYUNIONNAME4;
        HPALETTE hplWatermark;
        union {
            HBITMAP hbmHeader;     // Header  bitmap shares the palette with watermark
            LPCSTR pszbmHeader;
        } DUMMYUNIONNAME5;
#endif
} PROPSHEETHEADERA, FAR *LPPROPSHEETHEADERA;

typedef const PROPSHEETHEADERA FAR *LPCPROPSHEETHEADERA;

typedef struct _PROPSHEETHEADERW {
        DWORD           dwSize;
        DWORD           dwFlags;
        HWND            hwndParent;
        HINSTANCE       hInstance;
        union {
            HICON       hIcon;
            LPCWSTR     pszIcon;
        }DUMMYUNIONNAME;
        LPCWSTR         pszCaption;


        UINT            nPages;
        union {
            UINT        nStartPage;
            LPCWSTR     pStartPage;
        }DUMMYUNIONNAME2;
        union {
            LPCPROPSHEETPAGEW ppsp;
            HPROPSHEETPAGE FAR *phpage;
        }DUMMYUNIONNAME3;
        PFNPROPSHEETCALLBACK pfnCallback;

#if (_WIN32_IE >= 0x0400)
        union {
            HBITMAP hbmWatermark;
            LPCWSTR pszbmWatermark;
        } DUMMYUNIONNAME4;
        HPALETTE hplWatermark;
        union {
            HBITMAP hbmHeader;
            LPCWSTR pszbmHeader;
        } DUMMYUNIONNAME5;
#endif
} PROPSHEETHEADERW, FAR *LPPROPSHEETHEADERW;
typedef const PROPSHEETHEADERW FAR *LPCPROPSHEETHEADERW;

#ifdef UNICODE
#define PROPSHEETHEADER         PROPSHEETHEADERW
#define LPPROPSHEETHEADER       LPPROPSHEETHEADERW
#define LPCPROPSHEETHEADER      LPCPROPSHEETHEADERW
#define PROPSHEETHEADER_V1_SIZE PROPSHEETHEADERW_V1_SIZE
#else
#define PROPSHEETHEADER         PROPSHEETHEADERA
#define LPPROPSHEETHEADER       LPPROPSHEETHEADERA
#define LPCPROPSHEETHEADER      LPCPROPSHEETHEADERA
#define PROPSHEETHEADER_V1_SIZE PROPSHEETHEADERA_V1_SIZE
#endif


#define PSCB_INITIALIZED  1
#define PSCB_PRECREATE    2

WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageA(LPCPROPSHEETPAGEA);
WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(LPCPROPSHEETPAGEW);
WINCOMMCTRLAPI BOOL           WINAPI DestroyPropertySheetPage(HPROPSHEETPAGE);
WINCOMMCTRLAPI int            WINAPI PropertySheetA(LPCPROPSHEETHEADERA);
WINCOMMCTRLAPI int            WINAPI PropertySheetW(LPCPROPSHEETHEADERW);

#ifdef UNICODE
#define CreatePropertySheetPage  CreatePropertySheetPageW
#define PropertySheet            PropertySheetW
#else
#define CreatePropertySheetPage  CreatePropertySheetPageA
#define PropertySheet            PropertySheetA
#endif



typedef BOOL (CALLBACK FAR * LPFNADDPROPSHEETPAGE)(HPROPSHEETPAGE, LPARAM);
typedef BOOL (CALLBACK FAR * LPFNADDPROPSHEETPAGES)(LPVOID, LPFNADDPROPSHEETPAGE, LPARAM);


typedef struct _PSHNOTIFY
{
    NMHDR hdr;
    LPARAM lParam;
} PSHNOTIFY, FAR *LPPSHNOTIFY;

#define PSN_FIRST               (0U-200U)
#define PSN_LAST                (0U-299U)


#define PSN_SETACTIVE           (PSN_FIRST-0)
#define PSN_KILLACTIVE          (PSN_FIRST-1)
// #define PSN_VALIDATE            (PSN_FIRST-1)
#define PSN_APPLY               (PSN_FIRST-2)
#define PSN_RESET               (PSN_FIRST-3)
// #define PSN_CANCEL              (PSN_FIRST-3)
#define PSN_HELP                (PSN_FIRST-5)
#define PSN_WIZBACK             (PSN_FIRST-6)
#define PSN_WIZNEXT             (PSN_FIRST-7)
#define PSN_WIZFINISH           (PSN_FIRST-8)
#define PSN_QUERYCANCEL         (PSN_FIRST-9)
#if (_WIN32_IE >= 0x0400)
#define PSN_GETOBJECT           (PSN_FIRST-10)
#endif // 0x0400

#define PSNRET_NOERROR              0
#define PSNRET_INVALID              1
#define PSNRET_INVALID_NOCHANGEPAGE 2


#define PSM_SETCURSEL           (WM_USER + 101)
#define PropSheet_SetCurSel(hDlg, hpage, index) \
        SNDMSG(hDlg, PSM_SETCURSEL, (WPARAM)index, (LPARAM)hpage)


#define PSM_REMOVEPAGE          (WM_USER + 102)
#define PropSheet_RemovePage(hDlg, index, hpage) \
        SNDMSG(hDlg, PSM_REMOVEPAGE, index, (LPARAM)hpage)


#define PSM_ADDPAGE             (WM_USER + 103)
#define PropSheet_AddPage(hDlg, hpage) \
        SNDMSG(hDlg, PSM_ADDPAGE, 0, (LPARAM)hpage)


#define PSM_CHANGED             (WM_USER + 104)
#define PropSheet_Changed(hDlg, hwnd) \
        SNDMSG(hDlg, PSM_CHANGED, (WPARAM)hwnd, 0L)


#define PSM_RESTARTWINDOWS      (WM_USER + 105)
#define PropSheet_RestartWindows(hDlg) \
        SNDMSG(hDlg, PSM_RESTARTWINDOWS, 0, 0L)


#define PSM_REBOOTSYSTEM        (WM_USER + 106)
#define PropSheet_RebootSystem(hDlg) \
        SNDMSG(hDlg, PSM_REBOOTSYSTEM, 0, 0L)


#define PSM_CANCELTOCLOSE       (WM_USER + 107)
#define PropSheet_CancelToClose(hDlg) \
        PostMessage(hDlg, PSM_CANCELTOCLOSE, 0, 0L)


#define PSM_QUERYSIBLINGS       (WM_USER + 108)
#define PropSheet_QuerySiblings(hDlg, wParam, lParam) \
        SNDMSG(hDlg, PSM_QUERYSIBLINGS, wParam, lParam)


#define PSM_UNCHANGED           (WM_USER + 109)
#define PropSheet_UnChanged(hDlg, hwnd) \
        SNDMSG(hDlg, PSM_UNCHANGED, (WPARAM)hwnd, 0L)


#define PSM_APPLY               (WM_USER + 110)
#define PropSheet_Apply(hDlg) \
        SNDMSG(hDlg, PSM_APPLY, 0, 0L)


#define PSM_SETTITLEA           (WM_USER + 111)
#define PSM_SETTITLEW           (WM_USER + 120)

#ifdef UNICODE
#define PSM_SETTITLE            PSM_SETTITLEW
#else
#define PSM_SETTITLE            PSM_SETTITLEA
#endif

#define PropSheet_SetTitle(hDlg, wStyle, lpszText)\
        SNDMSG(hDlg, PSM_SETTITLE, wStyle, (LPARAM)(LPCTSTR)lpszText)


#define PSM_SETWIZBUTTONS       (WM_USER + 112)
#define PropSheet_SetWizButtons(hDlg, dwFlags) \
        PostMessage(hDlg, PSM_SETWIZBUTTONS, 0, (LPARAM)dwFlags)


#define PSWIZB_BACK             0x00000001
#define PSWIZB_NEXT             0x00000002
#define PSWIZB_FINISH           0x00000004
#define PSWIZB_DISABLEDFINISH   0x00000008


#define PSM_PRESSBUTTON         (WM_USER + 113)
#define PropSheet_PressButton(hDlg, iButton) \
        PostMessage(hDlg, PSM_PRESSBUTTON, (WPARAM)iButton, 0)


#define PSBTN_BACK              0
#define PSBTN_NEXT              1
#define PSBTN_FINISH            2
#define PSBTN_OK                3
#define PSBTN_APPLYNOW          4
#define PSBTN_CANCEL            5
#define PSBTN_HELP              6
#define PSBTN_MAX               6



#define PSM_SETCURSELID         (WM_USER + 114)
#define PropSheet_SetCurSelByID(hDlg, id) \
        SNDMSG(hDlg, PSM_SETCURSELID, 0, (LPARAM)id)


#define PSM_SETFINISHTEXTA      (WM_USER + 115)
#define PSM_SETFINISHTEXTW      (WM_USER + 121)

#ifdef UNICODE
#define PSM_SETFINISHTEXT       PSM_SETFINISHTEXTW
#else
#define PSM_SETFINISHTEXT       PSM_SETFINISHTEXTA
#endif

#define PropSheet_SetFinishText(hDlg, lpszText) \
        SNDMSG(hDlg, PSM_SETFINISHTEXT, 0, (LPARAM)lpszText)


#define PSM_GETTABCONTROL       (WM_USER + 116)
#define PropSheet_GetTabControl(hDlg) \
        (HWND)SNDMSG(hDlg, PSM_GETTABCONTROL, 0, 0)

#define PSM_ISDIALOGMESSAGE     (WM_USER + 117)
#define PropSheet_IsDialogMessage(hDlg, pMsg) \
        (BOOL)SNDMSG(hDlg, PSM_ISDIALOGMESSAGE, 0, (LPARAM)pMsg)

#define PSM_GETCURRENTPAGEHWND  (WM_USER + 118)
#define PropSheet_GetCurrentPageHwnd(hDlg) \
        (HWND)SNDMSG(hDlg, PSM_GETCURRENTPAGEHWND, 0, 0L)

#define ID_PSRESTARTWINDOWS     0x2
#define ID_PSREBOOTSYSTEM       (ID_PSRESTARTWINDOWS | 0x1)


#define WIZ_CXDLG               276
#define WIZ_CYDLG               140

#define WIZ_CXBMP               80

#define WIZ_BODYX               92
#define WIZ_BODYCX              184

#define PROP_SM_CXDLG           212
#define PROP_SM_CYDLG           188

#define PROP_MED_CXDLG          227
#define PROP_MED_CYDLG          215

#define PROP_LG_CXDLG           252
#define PROP_LG_CYDLG           218



#ifdef __cplusplus
}
#endif


#endif  // _PRSHT_H_

