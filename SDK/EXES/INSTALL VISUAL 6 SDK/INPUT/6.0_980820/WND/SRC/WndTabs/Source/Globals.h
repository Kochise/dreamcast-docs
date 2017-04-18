/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// program wide constants and declarations

#ifndef __GLOBALS_H
#define __GLOBALS_H

// size constants
#define TAB_BORDER_HEIGHT       3            // non text part
#define TAB_ROW_HEIGHT          5            // tab row height

// configuration constants
#define VKS1To9                 0
#define VKSF1ToF9               1

// user messages
#define WM_DOWIZARD             (WM_APP + 0x12)
#define WM_UPDATETABS           (WM_APP + 0x13)
#define WM_MDIWINCHANGE         (WM_APP + 0x14)
#define WM_CHECKNEWVER          (WM_APP + 0x15)
#define WM_LAZYINIT             (WM_APP + 0x16)

// flags for popup menus
#define TPM_FLAGS               (TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD)

// enumerations
enum SnapStates                 { ssMDI = 0, ssWindow };
enum SnapOrientations           { soTop = 0, soBottom, soLeft, soRight };
enum TabOrdering                { toMDI = 0, toAlphabetic, toControlled };
enum FontTypes                  { ftSerif = 0, ftSansSerif };
enum InetBackForward            { bfIgnore = 0, bfCycleGroup = 1, bfCtrlTabOrder = 2, bfTabOrder = 3 };

#define IS_HORIZONTAL(o) ((o) == soTop  ||  (o) == soBottom)

#define MENU_NAME_CLOSE_BTN _T("Z] Close Button Menu")

// class declarations
class CDSWindow;
class CTabsWindow;
class CDevStudioWnd;
class CDS_MDIWnd;
class CTabManagerWindow;

// global variables
extern CWinApp *                pTheApp;
extern CTabManagerWindow *      pGlobalActiveManager;
extern CDSWindow *              pGlobalActiveDSWindow;
extern CDS_MDIWnd *             pGlobalMDIManager;
extern CTabsWindow *            pGlobalTabs;

extern BOOL              g_bUseWndTabsExt;
extern CString           g_cVersion;           // ver. string from resource
extern DWORD             g_CommonControlsVer;  // COMCTL32.DLL version
extern CDevStudioWnd*    g_pDevStudioWnd;      // DevStudio main window
extern class CMainFrame *g_pMainFrame;
extern long              g_dwCookie;
extern int               g_cTabRows;
extern bool              g_bResetLanguage;

// misc
#define PACKVERSION(major, minor) MAKELONG(minor, major)
#define countof(arr)  (sizeof(arr)/sizeof(arr[0]))

// find a DevStudio child window:
extern HWND GetHWND(LPCTSTR cTitle);        
extern HWND GetHWND(CComBSTR& bStr);
extern HWND GetHWND(IGenericWindow *pWindow);

// returns version information about a specified file
CString LoadVersionString(LPCTSTR path);

// VC5 compatible replace function
inline void CString_Replace(CString& cStr, LPCTSTR cToReplace, 
                            LPCTSTR cWithWhat)
{
    int nPos = cStr.Find(cToReplace);
    if (nPos >= 0)
    {
        CString cRight = cStr.Mid(nPos + _tcslen(cToReplace));
        cStr = cStr.Left(nPos);
        cStr += cWithWhat + cRight;
    }
}

// DEFAULT_UNREACHABLE macro by Michael Dunn [mdunn@inreach.com]

// some SDKs have a simpler version of this macro already defined
#ifdef DEFAULT_UNREACHABLE  
#undef DEFAULT_UNREACHABLE
#endif 

// define the macro
#ifdef _DEBUG
#define DEFAULT_UNREACHABLE default: ASSERT(0); break
#elif _MSC_VER >= 1200
#define DEFAULT_UNREACHABLE default: __assume(0); break
#else
#define DEFAULT_UNREACHABLE default: break
#endif


#endif  // __GLOBALS_H
