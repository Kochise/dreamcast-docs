/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __IMPORTS_H
#define __IMPORTS_H

// functions available from the extension library
extern "C" {

enum WNDTABSEXTERR
{
    EXT_ERR_OK          =    0,
    EXT_ERR_GENERAL     =   -1,
    EXT_ERR_ILLEGAL_REG =   -2,
    EXT_ERR_OVERUSE     =   -3,
    EXT_ERR_EXPIRED     =   -4
};

// flags
const int WTXF_STRIP_FIRST_GROUP_CHAR   = 1;
const int WTXF_ALL_SPECIAL              = 2;  // all tabs are considered groups
const int WTXF_TAB_CLOSE_BUTTON         = 4;
const int WTXF_SORT_MINI_TB             = 8;

// notifications
const int WTXN_TAB_CLOSE                = 100000;
const int WTXN_R_TAB_CLOSE              = 100001;

class CFancyTabCtrl;

typedef struct 
{
    CDECL CFancyTabCtrl *(*pfnNewWTTabCtrl)();
    CDECL void (*pfnSetWTTabCtrlColors)(CFancyTabCtrl *pCtrl, COLORREF clrReg, COLORREF clrSel);
    CDECL bool (*pfnWTTabCtrlIsGroupSection)(CFancyTabCtrl *pCtrl, POINT pt);
    CDECL void (*pfnWTTabCtrlSetFlags)(CFancyTabCtrl *pCtrl, int flags);
    CDECL void (*pfnWTTabCtrlSetTabOverlay)(CFancyTabCtrl *pCtrl, int iTab, HICON hIcon, bool bAutoDelete);
    CDECL void (*pfnWTTabCtrlRefresh)(CFancyTabCtrl *pCtrl);
    CDECL int  (*pfnWTTabCtrlGetGroupInfo)(CFancyTabCtrl *pCtrl, int *pInfo);
} fnblock;

class CLogger;

CDECL typedef void (fnSetLogger_t)(CLogger *pLogger);
CDECL typedef WNDTABSEXTERR (fnInitWndTabsExt_t)();
CDECL typedef WNDTABSEXTERR (fnActivateWndTabsExt_t)(CWnd *pDevStudioWnd, fnblock *pfnBlock, CString &sRegUser, int iForceMode);
CDECL typedef void (fnEndWndTabsExt_t)();

#define WM_TABINFOUPDATE    (WM_APP+20)


} // extern "C"


// functions available from the private library
bool IsCustomizing();
void DoCustomize(CFrameWnd *pFrameWnd);
void BeginInitThread();
void ForceEndInitThread();

#endif  // __IMPORTS_H
