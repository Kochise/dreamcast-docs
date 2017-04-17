/************************************************************************
*                                                                       *
*   commdlg.h -- This module defines the 32-Bit Common Dialog APIs      *
*                                                                       *
*   Copyright (c) 1992-1998, Microsoft Corp. All rights reserved.       *
*                                                                       *
************************************************************************/
#ifndef _INC_COMMDLG
#define _INC_COMMDLG

#include <pshpack1.h>         /* Assume byte packing throughout */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#if(WINVER >= 0x0400)
#ifdef __cplusplus

#ifndef SNDMSG
#ifndef UNDER_CE
#define SNDMSG ::SendMessage
#else  // UNDER_CE
#define SNDMSG SendMessage
#endif // !UNDER_CE
#endif // !SNDMSG

#else   // __cplusplus

#ifndef SNDMSG
#define SNDMSG SendMessage
#endif

#endif // __cplusplus 
#endif // WINVER >= 0x0400 

// Fileopen Edit Control IDs 
#define edt1  0x0480
#define edt2  0x0481

typedef UINT (APIENTRY *LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

typedef struct tagOFNA {
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCSTR       lpstrFilter;
   LPSTR        lpstrCustomFilter; // not supported
   DWORD        nMaxCustFilter;  // not supported
   DWORD        nFilterIndex;
   LPSTR        lpstrFile;
   DWORD        nMaxFile;
   LPSTR        lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCSTR       lpstrInitialDir;
   LPCSTR       lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCSTR       lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCSTR       lpTemplateName;
} OPENFILENAMEA, *LPOPENFILENAMEA;
typedef struct tagOFNW {
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCWSTR      lpstrFilter;
   LPWSTR       lpstrCustomFilter;
   DWORD        nMaxCustFilter;
   DWORD        nFilterIndex;
   LPWSTR       lpstrFile;
   DWORD        nMaxFile;
   LPWSTR       lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCWSTR      lpstrInitialDir;
   LPCWSTR      lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCWSTR      lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCWSTR      lpTemplateName;
} OPENFILENAMEW, *LPOPENFILENAMEW;
#ifdef UNICODE
typedef OPENFILENAMEW OPENFILENAME;
typedef LPOPENFILENAMEW LPOPENFILENAME;
#else
typedef OPENFILENAMEA OPENFILENAME;
typedef LPOPENFILENAMEA LPOPENFILENAME;
#endif // UNICODE


// @CESYSGEN IF COREDLL_FILEOPEN
// @CESYSGEN ENDIF

#define OFN_READONLY		     0x00000001
#define OFN_OVERWRITEPROMPT          0x00000002
#define OFN_HIDEREADONLY             0x00000004
#define OFN_NOCHANGEDIR              0x00000008
#define OFN_SHOWHELP                 0x00000010
#define OFN_ENABLEHOOK               0x00000020
#define OFN_ENABLETEMPLATE           0x00000040
#define OFN_ENABLETEMPLATEHANDLE     0x00000080
#define OFN_NOVALIDATE               0x00000100
#define OFN_ALLOWMULTISELECT         0x00000200
#define OFN_EXTENSIONDIFFERENT       0x00000400
#define OFN_PATHMUSTEXIST            0x00000800
#define OFN_FILEMUSTEXIST            0x00001000
#define OFN_CREATEPROMPT             0x00002000
#define OFN_SHAREAWARE               0x00004000
#define OFN_NOREADONLYRETURN         0x00008000
#define OFN_NOTESTFILECREATE         0x00010000
#define OFN_NONETWORKBUTTON          0x00020000
#define OFN_NOLONGNAMES              0x00040000     // force no long names for 4.x modules
#if(WINVER >= 0x0400)
#define OFN_EXPLORER                 0x00080000     // new look commdlg
#define OFN_NODEREFERENCELINKS       0x00100000
#define OFN_LONGNAMES                0x00200000     // force long names for 3.x modules
#endif /* WINVER >= 0x0400 */



// Return values for the registered message sent to the hook function
// when a sharing violation occurs.  OFN_SHAREFALLTHROUGH allows the
// filename to be accepted, OFN_SHARENOWARN rejects the name but puts
// up no warning (returned when the app has already put up a warning
// message), and OFN_SHAREWARN puts up the default warning message
// for sharing violations.
//
// Note:  Undefined return values map to OFN_SHAREWARN, but are
//        reserved for future use.

#define OFN_SHAREFALLTHROUGH     2
#define OFN_SHARENOWARN          1
#define OFN_SHAREWARN            0

typedef UINT (APIENTRY *LPCCHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

#if(WINVER >= 0x0400)
// Structure used for all OpenFileName notifications
typedef struct _OFNOTIFYW
{
        NMHDR           hdr;
        LPOPENFILENAMEW lpOFN;
        LPWSTR          pszFile;        // May be NULL
} OFNOTIFYW, FAR *LPOFNOTIFYW;
typedef struct _OFNOTIFYA
{
        NMHDR           hdr;
        LPOPENFILENAMEA lpOFN;
        LPSTR           pszFile;        // May be NULL
} OFNOTIFYA, FAR *LPOFNOTIFYA;
#ifdef UNICODE
typedef OFNOTIFYW OFNOTIFY;
typedef LPOFNOTIFYW LPOFNOTIFY;
#else
typedef OFNOTIFYA OFNOTIFY;
typedef LPOFNOTIFYA LPOFNOTIFY;
#endif // UNICODE

#define CDN_FIRST   (0U-601U)
#define CDN_LAST    (0U-699U)

// Notifications when Open or Save dialog status changes
#define CDN_INITDONE            (CDN_FIRST - 0x0000)
#define CDN_SELCHANGE           (CDN_FIRST - 0x0001)
#define CDN_FOLDERCHANGE        (CDN_FIRST - 0x0002)
#define CDN_SHAREVIOLATION      (CDN_FIRST - 0x0003)
#define CDN_HELP                (CDN_FIRST - 0x0004)
#define CDN_FILEOK              (CDN_FIRST - 0x0005)
#define CDN_TYPECHANGE          (CDN_FIRST - 0x0006)

#define CDM_FIRST       (WM_USER + 100)
#define CDM_LAST        (WM_USER + 200)

// Messages to query information from the Open or Save dialogs

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETSPEC             (CDM_FIRST + 0x0000)
#define CommDlg_OpenSave_GetSpecA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetSpecW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecW
#else
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecA
#endif // !UNICODE

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETFILEPATH         (CDM_FIRST + 0x0001)
#define CommDlg_OpenSave_GetFilePathA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetFilePathW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathW
#else
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathA
#endif // !UNICODE

// lParam = pointer to text buffer that gets filled in
// wParam = max number of characters of the text buffer (including NULL)
// return = < 0 if error; number of characters needed (including NULL)
#define CDM_GETFOLDERPATH       (CDM_FIRST + 0x0002)
#define CommDlg_OpenSave_GetFolderPathA(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)
#define CommDlg_OpenSave_GetFolderPathW(_hdlg, _psz, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)
#ifdef UNICODE
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathW
#else
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathA
#endif // !UNICODE

// lParam = pointer to ITEMIDLIST buffer that gets filled in
// wParam = size of the ITEMIDLIST buffer
// return = < 0 if error; length of buffer needed
#define CDM_GETFOLDERIDLIST     (CDM_FIRST + 0x0003)
#define CommDlg_OpenSave_GetFolderIDList(_hdlg, _pidl, _cbmax) \
        (int)SNDMSG(_hdlg, CDM_GETFOLDERIDLIST, (WPARAM)_cbmax, (LPARAM)(LPVOID)_pidl)

// lParam = pointer to a string
// wParam = ID of control to change
// return = not used
#define CDM_SETCONTROLTEXT      (CDM_FIRST + 0x0004)
#define CommDlg_OpenSave_SetControlText(_hdlg, _id, _text) \
        (void)SNDMSG(_hdlg, CDM_SETCONTROLTEXT, (WPARAM)_id, (LPARAM)(LPSTR)_text)

// lParam = not used
// wParam = ID of control to change
// return = not used
#define CDM_HIDECONTROL         (CDM_FIRST + 0x0005)
#define CommDlg_OpenSave_HideControl(_hdlg, _id) \
        (void)SNDMSG(_hdlg, CDM_HIDECONTROL, (WPARAM)_id, 0)

// lParam = pointer to default extension (no dot)
// wParam = not used
// return = not used
#define CDM_SETDEFEXT           (CDM_FIRST + 0x0006)
#define CommDlg_OpenSave_SetDefExt(_hdlg, _pszext) \
        (void)SNDMSG(_hdlg, CDM_SETDEFEXT, 0, (LPARAM)(LPSTR)_pszext)
#endif /* WINVER >= 0x0400 */

#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mcommdlg.h>
#endif
#endif

typedef UINT (APIENTRY *LPCCHOOKPROC) (HWND, UINT, WPARAM, LPARAM);

typedef struct tagCHOOSECOLOR  {
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   COLORREF     rgbResult;
   COLORREF*    lpCustColors;
   DWORD        Flags;
   LPARAM       lCustData;
   LPCCHOOKPROC lpfnHook;
   LPCTSTR      lpTemplateName;
} CHOOSECOLOR , *LPCHOOSECOLOR ;

BOOL  APIENTRY ChooseColor (LPCHOOSECOLOR );

#define CC_RGBINIT               0x00000001
#define CC_FULLOPEN              0x00000002
#define CC_PREVENTFULLOPEN       0x00000004
#define CC_ENABLEHOOK            0x00000010
#define CC_ENABLETEMPLATE        0x00000020
#define CC_ENABLETEMPLATEHANDLE  0x00000040
#if(WINVER >= 0x0400)
#define CC_SOLIDCOLOR            0x00000080
#define CC_ANYCOLOR              0x00000100
#endif /* WINVER >= 0x0400 */

// **************************************************
// PrintDlg is now obsolete!!!
// It is included only for backwards compatability
// Use PageSetupDlg from now on
// **************************************************
typedef UINT (APIENTRY *LPPRINTHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef struct tagPD  {
   DWORD            cbStruct;
   HWND             hwndOwner;
   HDC              hdc;
   DWORD            dwFlags;
   RECT             rcMinMargin;
   RECT             rcMargin;
   HINSTANCE        hinst;
   LPARAM           lCustData;
   LPPRINTHOOKPROC  pfnPrintHook;
   LPCTSTR          pszPrintTemplateName;
   HGLOBAL          hglbPrintTemplateResource;
} PRINTDLG , *LPPRINTDLG ;

BOOL  APIENTRY     PrintDlg (LPPRINTDLG);
// Out only
#define PD_SELECTALLPAGES                 0x00000001
#define PD_SELECTSELECTION                0x00000002
#define PD_SELECTDRAFTMODE                0x00000008
#define PD_SELECTA4                       0x00000010
#define PD_SELECTLETTER                   0x00000020
#define PD_SELECTINFRARED                 0x00000040 
#define PD_SELECTSERIAL                   0x00000080

// In only
#define PD_DISABLEPAPERSIZE               0x00000100
#define PD_DISABLEPRINTRANGE              0x00000200
#define PD_DISABLEMARGINS                 0x00000400
#define PD_DISABLEORIENTATION             0x00000800
#define PD_RETURNDEFAULTDC                0x00002000
#define PD_ENABLEPRINTHOOK                0x00004000
#define PD_ENABLEPRINTTEMPLATE            0x00008000
#define PD_ENABLEPRINTTEMPLATEHANDLE      0x00010000
#define PD_TITLE						  0x00020000

// In-Out
#define PD_SELECTPORTRAIT                 0x00040000
#define PD_SELECTLANDSCAPE                0x00080000
#define PD_MARGINS                        0x00100000
#define PD_INTHOUSANDTHSOFINCHES          0x00200000
#define PD_INHUNDREDTHSOFMILLIMETERS      0x00400000
#define PD_MINMARGINS                     0x00800000

// New in Birch: Out-only
#define PD_SELECTPARALLEL				  0x01000000
#define PD_SELECTNETWORK				  0x02000000
#define PD_SELECTLEGAL					  0x04000000
#define PD_SELECTB5						  0x08000000
#define PD_SELECTPRINTINCOLOR			  0x10000000

// **************************************************
// PrintDlg is now obsolete!!!
// It is included only for backwards compatability
// Use PageSetupDlg from now on
// **************************************************

typedef struct tagDEVNAMES {
   WORD wDriverOffset;
   WORD wDeviceOffset;
   WORD wOutputOffset;
   WORD wDefault;
} DEVNAMES;

typedef DEVNAMES * LPDEVNAMES;

#define DN_DEFAULTPRN      0x0001

DWORD APIENTRY     CommDlgExtendedError(VOID);

typedef UINT (APIENTRY* LPPAGEPAINTHOOK)( HWND, UINT, WPARAM, LPARAM );
typedef UINT (APIENTRY* LPPAGESETUPHOOK)( HWND, UINT, WPARAM, LPARAM );

// only wide types supported in CE - include for synchronization with nt .h
typedef struct tagPSDA
{
    DWORD           lStructSize;
    HWND            hwndOwner;
    HGLOBAL         hDevMode;
    HGLOBAL         hDevNames;
    DWORD           Flags;
    POINT           ptPaperSize;
    RECT            rtMinMargin;
    RECT            rtMargin;
    HINSTANCE       hInstance;
    LPARAM          lCustData;
    LPPAGESETUPHOOK lpfnPageSetupHook;
    LPPAGEPAINTHOOK lpfnPagePaintHook;
    LPCSTR          lpPageSetupTemplateName;
    HGLOBAL         hPageSetupTemplate;
} PAGESETUPDLGA, * LPPAGESETUPDLGA;
typedef struct tagPSDW
{
    DWORD           lStructSize;
    HWND            hwndOwner;
    HGLOBAL         hDevMode;
    HGLOBAL         hDevNames;
    DWORD           Flags;
    POINT           ptPaperSize; // ignored in CE
    RECT            rtMinMargin;
    RECT            rtMargin;
    HINSTANCE       hInstance;
    LPARAM          lCustData;
    LPPAGESETUPHOOK lpfnPageSetupHook;
    LPPAGEPAINTHOOK lpfnPagePaintHook; // ignored in CE
    LPCWSTR         lpPageSetupTemplateName;
    HGLOBAL         hPageSetupTemplate;
} PAGESETUPDLGW, * LPPAGESETUPDLGW;
#ifdef UNICODE
typedef PAGESETUPDLGW PAGESETUPDLG;
typedef LPPAGESETUPDLGW LPPAGESETUPDLG;
#else
typedef PAGESETUPDLGA PAGESETUPDLG;
typedef LPPAGESETUPDLGA LPPAGESETUPDLG;
#endif // UNICODE

BOOL APIENTRY PageSetupDlgA( LPPAGESETUPDLGA );
BOOL APIENTRY PageSetupDlgW( LPPAGESETUPDLGW );
#ifdef UNICODE
#define PageSetupDlg  PageSetupDlgW
#else
#define PageSetupDlg  PageSetupDlgA
#endif // !UNICODE

#define PSD_DEFAULTMINMARGINS             0x00000000 // default (printer's)
#define PSD_INWININIINTLMEASURE           0x00000000 // 1st of 4 possible

#define PSD_MINMARGINS                    0x00000001 // use caller's
#define PSD_MARGINS                       0x00000002 // use caller's
#define PSD_INTHOUSANDTHSOFINCHES         0x00000004 // 2nd of 4 possible
#define PSD_INHUNDREDTHSOFMILLIMETERS     0x00000008 // 3rd of 4 possible
#define PSD_DISABLEMARGINS                0x00000010
#define PSD_DISABLEPRINTER                0x00000020
// #define PSD_NOWARNING                  0x00000080 // not used in CE
#define PSD_DISABLEORIENTATION            0x00000100
#define PSD_DISABLEPAPER                  0x00000200
#define PSD_RETURNDEFAULT                 0x00000400
// #define PSD_SHOWHELP                   0x00000800 // not used in CE
#define PSD_ENABLEPAGESETUPHOOK           0x00002000
#define PSD_ENABLEPAGESETUPTEMPLATE       0x00008000
#define PSD_ENABLEPAGESETUPTEMPLATEHANDLE 0x00020000
// #define PSD_ENABLEPAGEPAINTHOOK        0x00040000 // not used in CE
// #define PSD_DISABLEPAGEPAINTING        0x00080000 // not used in CE
// #define PSD_NONETWORKBUTTON            0x00200000 // not used in CE

// new in Win CE - print range flags
#define PSD_DISABLEPRINTRANGE		      0x10000000
#define PSD_RANGESELECTION				  0x20000000

// Errors returned by CommDlgExtendedError()

#define CDERR_DIALOGFAILURE   0xFFFF

#define CDERR_GENERALCODES     0x0000
#define CDERR_STRUCTSIZE       0x0001
#define CDERR_INITIALIZATION   0x0002
#define CDERR_NOTEMPLATE       0x0003
#define CDERR_NOHINSTANCE      0x0004
#define CDERR_LOADSTRFAILURE   0x0005
#define CDERR_FINDRESFAILURE   0x0006
#define CDERR_LOADRESFAILURE   0x0007
#define CDERR_LOCKRESFAILURE   0x0008
#define CDERR_MEMALLOCFAILURE  0x0009
#define CDERR_MEMLOCKFAILURE   0x000A
#define CDERR_NOHOOK           0x000B
#define CDERR_REGISTERMSGFAIL  0x000C

#define PDERR_PRINTERCODES     0x1000
#define PDERR_SETUPFAILURE     0x1001
#define PDERR_PARSEFAILURE     0x1002
#define PDERR_RETDEFFAILURE    0x1003
#define PDERR_LOADDRVFAILURE   0x1004
#define PDERR_GETDEVMODEFAIL   0x1005
#define PDERR_INITFAILURE      0x1006
#define PDERR_NODEVICES        0x1007
#define PDERR_NODEFAULTPRN     0x1008
#define PDERR_DNDMMISMATCH     0x1009
#define PDERR_CREATEICFAILURE  0x100A
#define PDERR_PRINTERNOTFOUND  0x100B
#define PDERR_DEFAULTDIFFERENT 0x100C

// WinCE specific
#define CDERR_REGISTRYFAILURE  0x0100
#define PDERR_NOPORTS          PDERR_NODEVICES
#define PDERR_NOPRINTERS       PDERR_NODEFAULTPRN
#define PDERR_CREATEDCFAILURE  PDERR_CREATEICFAILURE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#include <poppack.h>
#endif  /* !_INC_COMMDLG */
