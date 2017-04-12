/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#include "stdafx.h"
#include "WndTabs.h"
#include "Utils.h"
#include "Config.h"
#include "Imports.h"
#include "AddInComm\AICLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// doesn't have a .dll extension so we can easily put in the addins directory
#define DLLNAME  _T("WndTabsExt.mod")

fnInitWndTabsExt_t *    pfnInitWndTabsExt     = NULL;
fnActivateWndTabsExt_t* pfnActivateWndTabsExt = NULL;
fnEndWndTabsExt_t *     pfnEndWndTabsExt      = NULL;
fnSetLogger_t *         pfnSetLogger          = NULL;
CString                 g_sRegUserName;

// module locals
static HINSTANCE s_hInstDLL = NULL;
static int       s_iErr     = 0;
static bool      s_bActive  = false;
static fnblock   s_fnBlock;

#define DO_WNDTABSEXT_ASSERTS(fn)    \
    ASSERT(s_bActive);               \
    ASSERT(g_bUseWndTabsExt);        \
    ASSERT(cfg_bUseWTTabCtrl);       \
    ASSERT(s_fnBlock.pfn##fn);       \



static void TranslateExtErr(WNDTABSEXTERR err, int deferr)
{
    switch (err)
    {
        case EXT_ERR_OK:
            s_iErr = 0;
            break;

        case EXT_ERR_OVERUSE:
            s_iErr = IDS_XERR_OVERUSE;
            break;

        case EXT_ERR_EXPIRED:
            s_iErr = IDS_XERR_EXPIRED;
            break;

        case EXT_ERR_ILLEGAL_REG:
            s_iErr = IDS_XERR_REGISTRATION;
            break;

        case EXT_ERR_GENERAL:
            s_iErr = IDS_XERR_GENERAL;
            break;

        default:
            s_iErr = deferr;
            break;
    }
}

BOOL InitExtensions()
{
    WNDTABSEXTERR err;

    // already inited?
    if (s_hInstDLL)
        return true;

    ZeroMemory(&s_fnBlock, sizeof(s_fnBlock));

    s_iErr = 0;

    // switch to our own directory to assure that the module will be found
    CPushCurrentDirectory pushDir;
    GoToModuleDirectory(AfxGetInstanceHandle());

    s_hInstDLL = AfxLoadLibrary(DLLNAME);

    if (!s_hInstDLL)
    {
        s_iErr = IDS_XERR_DLLLOAD;
        goto err;
    }

    char verbuf[256];
    aiclGetModuleVersion(DLLNAME, (LPSTR)verbuf);
    if (strcmp(verbuf, g_cVersion) != 0  &&  0)
    {
        s_iErr = IDS_XERR_VERSION;
        goto err;
    }

#define LOAD_FN(f)                                         \
    pfn##f = (fn##f##_t *)GetProcAddress(s_hInstDLL, #f);  \
    if (!pfn##f)                                           \
    {                                                      \
        s_iErr = IDS_XERR_BADDLL;                          \
        goto err;                                          \
    }

    LOAD_FN(InitWndTabsExt);
    LOAD_FN(ActivateWndTabsExt);
    LOAD_FN(EndWndTabsExt);
    LOAD_FN(SetLogger);

    (*pfnSetLogger)(g_pTheLogger);

    err = (*pfnInitWndTabsExt)();
    TranslateExtErr(err, IDS_XERR_DLLLOAD);
    if (s_iErr)
        goto err;

    return TRUE;

err:
    if (s_hInstDLL)
    {
        if (pfnEndWndTabsExt) (*pfnEndWndTabsExt)();
        AfxFreeLibrary(s_hInstDLL);
        s_hInstDLL = NULL;
    }
    return FALSE;
}

BOOL ActivateExtensions(int iForceMode /*= false*/)
{
    if (s_bActive  &&  !iForceMode)
        return TRUE;

//    bForceReg &= s_bActive;

    if (!InitExtensions())
        return FALSE;

    WNDTABSEXTERR err = pfnActivateWndTabsExt((CWnd *)g_pDevStudioWnd, 
        &s_fnBlock, g_sRegUserName, iForceMode);
    if (!s_bActive  ||  err != EXT_ERR_OK)
    {
        TranslateExtErr(err, IDS_XERR_REGISTRATION);
        if (s_iErr)
        {
            if (iForceMode  &&  s_iErr != IDS_XERR_REGISTRATION)
            {   
                CString msg;
                msg.LoadString(s_iErr);
                msg.Insert(0, "Registration failed.  The error was:\n\n");
                AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);
            }
            return FALSE;
        }
    }

    s_bActive = true;

    return TRUE;
}

void EndExtensions()
{
    if (s_hInstDLL)
    {
        if (pfnEndWndTabsExt)
            (*pfnEndWndTabsExt)();
        AfxFreeLibrary(s_hInstDLL);

        // reset values (in case user reactivates the add-in)
        s_bActive  = false;
        s_hInstDLL = NULL;
        s_iErr     = 0;
    }
}


int GetExtensionsErr()
{
    return s_iErr;
}

bool GetExtensionsInited()
{
    return (s_hInstDLL != NULL);
}

bool GetExtensionsActive()
{
    return s_bActive;
}

// exported extensions
CFancyTabCtrl *NewWTTabCtrl()
{
    DO_WNDTABSEXT_ASSERTS(NewWTTabCtrl);

    return (*s_fnBlock.pfnNewWTTabCtrl)();
}

void SetWTTabCtrlColors(CFancyTabCtrl *pCtrl, COLORREF clrReg, COLORREF clrSel)
{
    DO_WNDTABSEXT_ASSERTS(SetWTTabCtrlColors);

    (*s_fnBlock.pfnSetWTTabCtrlColors)(pCtrl, clrReg, clrSel);
}

void WTTabCtrlSetFlags(CFancyTabCtrl *pCtrl, int flags)
{
    DO_WNDTABSEXT_ASSERTS(WTTabCtrlSetFlags);

    (*s_fnBlock.pfnWTTabCtrlSetFlags)(pCtrl, flags);
}

bool WTTabCtrlIsGroupSection(CFancyTabCtrl *pCtrl, POINT pt)
{
    DO_WNDTABSEXT_ASSERTS(WTTabCtrlIsGroupSection);

    return (*s_fnBlock.pfnWTTabCtrlIsGroupSection)(pCtrl, pt);
}

void WTTabCtrlSetTabOverlay(CFancyTabCtrl *pCtrl, int iTab, HICON hIcon, 
                            bool bAutoDelete)
{
    DO_WNDTABSEXT_ASSERTS(WTTabCtrlSetTabOverlay);

    (*s_fnBlock.pfnWTTabCtrlSetTabOverlay)(pCtrl, iTab, hIcon, bAutoDelete);
}

void WTTabCtrlRefresh(CFancyTabCtrl *pCtrl)
{
    DO_WNDTABSEXT_ASSERTS(WTTabCtrlRefresh);

    s_fnBlock.pfnWTTabCtrlRefresh(pCtrl);
}

int WTTabCtrlGetGroupInfo(CFancyTabCtrl *pCtrl, int *pInfo)
{
    DO_WNDTABSEXT_ASSERTS(WTTabCtrlGetGroupInfo);

    return s_fnBlock.pfnWTTabCtrlGetGroupInfo(pCtrl, pInfo);
}
