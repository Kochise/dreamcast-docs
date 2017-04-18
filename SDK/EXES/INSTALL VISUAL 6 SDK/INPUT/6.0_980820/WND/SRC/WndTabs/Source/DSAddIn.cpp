/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DSAddIn.cpp : implementation file
//

#include "stdafx.h"
#include "WndTabs.h"
#include "Commands.h"
#include "DSAddIn.h"
#include "Commands.h"
#include "Config.h"
#include "TabsWindow.h"
#include "TabManagerWindow.h"
#include "DevStudioWnd.h"
#include "DS_MDIWnd.h"
#include "Options.h"
#include "Extensions.h"
#include "MainFrame.h"
#include "BugReportsDlg.h"
#include "DontShowAgainDlg.h"
#include "DSWindow.h"
#include "VCVerMgr.h"

#include "AddInComm\AddInComm.h"
#include "AddInComm\AICLoader.h"

#include "..\WndTabsSdk\WndTabsInt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD             g_CommonControlsVer;
long              g_dwCookie;
CDevStudioWnd    *g_pDevStudioWnd = NULL;
CMainFrame       *g_pMainFrame = NULL;

extern int AddInCallback(LPCTSTR pCmd);

// 1. the method name must be the command name
// 2. the commands must appear below in the order of their toolbar buttons
const AddInCmd AddInCommands[] =
{
    { _T("WTHeaderFlip"), IDC_HEADERFLIP, true  },
    { _T("WTSetCurrDir"), IDC_SETCURRDIR, true  },
    { _T("WTOpenAsText"), IDC_OPENASTEXT, true  },
    { _T("WTHelp"),       IDS_HELP,       true  },
    { _T("WTAbout"),      IDC_ABOUT,      false },
    { _T("WTOptions"),    IDC_OPTIONS,    true  },
    { _T("WTRenumber"),   IDC_RENUMBER,   true  },
    { _T("WTReorder"),    IDC_REORDER,    true  },
    { _T("WTGroupPrev"),  IDC_GROUP_PREV, true  },
    { _T("WTGroupNext"),  IDC_GROUP_NEXT, true  },
    { _T("WTGoToTab1"),   IDC_GOTOTAB1,   false },
    { _T("WTGoToTab2"),   IDC_GOTOTAB2,   false },
    { _T("WTGoToTab3"),   IDC_GOTOTAB3,   false },
    { _T("WTGoToTab4"),   IDC_GOTOTAB4,   false },
    { _T("WTGoToTab5"),   IDC_GOTOTAB5,   false },
    { _T("WTGoToTab6"),   IDC_GOTOTAB6,   false },
    { _T("WTGoToTab7"),   IDC_GOTOTAB7,   false },
    { _T("WTGoToTab8"),   IDC_GOTOTAB8,   false },
    { _T("WTGoToTab9"),   IDC_GOTOTAB9,   false }
};
const int cAddInCommands = countof(AddInCommands);

#ifdef EXPIRES
CTime s_now        = CTime::GetCurrentTime();
CTime s_expiration = CTime(EXPIRES, 0, 0, 0);
#endif


#if _MSC_VER <= 1100    // for VC 5 (from shlwapi.h)
    struct DLLVERSIONINFO
    {
        DWORD cbSize;
        DWORD dwMajorVersion;  // Major version
        DWORD dwMinorVersion;  // Minor version
        DWORD dwBuildNumber;   // Build number
        DWORD dwPlatformID;    // DLLVER_PLATFORM
    };
    typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);
#endif

static DWORD GetDllVersion(LPCTSTR lpszDllName)
{
    HINSTANCE hinstDll;
    DWORD dwVersion = 0;

    hinstDll = LoadLibrary(lpszDllName);
	
    if(hinstDll)
    {
        DLLGETVERSIONPROC pDllGetVersion;

        pDllGetVersion = (DLLGETVERSIONPROC) 
            GetProcAddress(hinstDll, "DllGetVersion");

        if(pDllGetVersion)
        {
            DLLVERSIONINFO dvi;
            HRESULT hr;

            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);

            hr = (*pDllGetVersion)(&dvi);

            if(SUCCEEDED(hr))
            {
                dwVersion = PACKVERSION(dvi.dwMajorVersion, 
                                        dvi.dwMinorVersion);
            }
        }
        
        FreeLibrary(hinstDll);
    }
    return dwVersion;
}


// This is called when the user first loads the add-in, and on start-up
//  of each subsequent Developer Studio session
STDMETHODIMP CDSAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
        long dwCookie, VARIANT_BOOL* OnConnection)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    WT_FN_TRACE_PARAMS("OnConnection", "%p, %p, %d, %p", pApp);

    CFrameWnd *& pRoutingFrame = AfxGetThreadState()->m_pRoutingFrame;
    pRoutingFrame = NULL;

    HWND hWnd, hMDIWnd, hDevStudioWnd, hDesktopWnd = ::GetDesktopWindow();

    m_pCommands = NULL;

#ifdef EXPIRES
    if (s_now >= s_expiration)
    {
        CString msg;
        int verMaj, verMin, verExtra;
        char buf[25];
        sscanf(g_cVersion, "%d.%d %s %d", &verMaj, &verMin, buf, &verExtra);
        AfxFormatString1(msg, IDS_VER_EXPIRED, buf);
        while (AfxMessageBox(msg, MB_OK | MB_ICONSTOP | MB_TOPMOST) != IDOK) {}
        *OnConnection = VARIANT_FALSE;
        RETURN_INT(S_OK);
    }
#endif

    if (g_VCVer == Unknown)
    {
        WT_L1_TRACE("Unknown VC Version\n");
        if (AfxMessageBox(
            "Your version of Visual Studio was not be recognized.\n"
            "WndTabs may not function correctly.", 
            MB_OKCANCEL | MB_ICONEXCLAMATION | MB_TOPMOST) != IDOK)
        {
            *OnConnection = VARIANT_FALSE;
            RETURN_INT(S_OK);
        }
    }

    pApp->put_Active(VARIANT_FALSE);
    pApp->put_Active(VARIANT_TRUE);
    hWnd = ::GetActiveWindow();
    while (hWnd  &&  hWnd != hDesktopWnd)
    {
        hDevStudioWnd = hWnd;
        hWnd = ::GetParent(hWnd);
    }
    WT_L1_TRACE("Found DevStudio window, hwnd=%p\n", hDevStudioWnd);
    g_pDevStudioWnd = new CDevStudioWnd(hDevStudioWnd);

    // this is so DDE activation won't kill MSDEV:
    g_pDevStudioWnd->EnableWindow(FALSE);    

    CMainFrame *pMainFrame = new CMainFrame;
    if (!pMainFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPED))
    {
        WT_L1_TRACE("Frame failed to load!\n");
        *OnConnection = VARIANT_FALSE;
        RETURN_INT(S_OK);
    }
    g_pMainFrame = pMainFrame;
    pMainFrame->m_wndAddOnToolbar.RemoveAllButtons();
    pMainFrame->ModifyStyle(WS_CAPTION | WS_BORDER, 0/*WS_CHILD*/, SWP_NOACTIVATE);
    pMainFrame->ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, WS_EX_PALETTEWINDOW, SWP_NOACTIVATE);
    pMainFrame->MoveWindow(-100, -100, -100, -100);
    theApp.m_pMainWnd = pMainFrame;    


    // bind to extensions library
    g_pDevStudioWnd->SetActiveWindow();
    WT_L1_TRACE("Init extensions\n");
    const BOOL bLastUseWndTabsExt = g_bUseWndTabsExt;
    g_bUseWndTabsExt = InitExtensions();
    if (g_bUseWndTabsExt)
    {
        WT_L1_TRACE("Activate extensions\n");
        VERIFY_OK(pApp->EnableModeless(VARIANT_FALSE));
        g_bUseWndTabsExt = ActivateExtensions();
        VERIFY_OK(pApp->EnableModeless(VARIANT_FALSE));
    }
    WT_L1_TRACE("g_bUseWndTabsExt is %d, inited=%d, active=%d, err=%d\n", 
        g_bUseWndTabsExt,
        GetExtensionsInited(),
        GetExtensionsActive(),
        GetExtensionsErr());
    if (GetExtensionsErr() == IDS_XERR_OVERUSE)
    {
        WT_MANAGE_STATE();
        CDontShowAgainDlg::DoMessageBox(IDS_WARN_MULTI_USE_REG, 
            cfg_bShowMultiUseReg, MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        WT_MANAGE_STATE();
        if (!g_bUseWndTabsExt  &&  bLastUseWndTabsExt)
        {
            AfxMessageBox(IDS_NO_MORE_WTX, 
                MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
        }
    }

    g_pDevStudioWnd->SetActiveWindow();

    cfg_bDisableSplash &= g_bUseWndTabsExt;

    WT_L3_TRACE("Starting init thread\n");
    BeginInitThread();

    ////////////////////
    // test version of common controls library.  we need at least 5.80
    g_CommonControlsVer = GetDllVersion(TEXT("comctl32.dll"));
    if (g_CommonControlsVer < PACKVERSION(5, 80))
    {
        {
            CString msg;

            msg.LoadString(IDS_DLLVERERROR);
            msg.Format(msg, HIWORD(g_CommonControlsVer), 
                LOWORD(g_CommonControlsVer));
            AfxMessageBox(msg, MB_OK | MB_ICONSTOP | MB_TOPMOST);
        }

        WT_L1_TRACE("Bad comctl32.dll version\n");
GracefulExit:        
        ForceEndInitThread();
        *OnConnection = VARIANT_FALSE;
        RETURN_INT(S_OK);
    }
    ////////////////////

    // Load the AddInComm Library -- 
    // aiclLoadAICLibrary() can fail, but we don't care, because thanks to
    // the loader, we could still call all the AIC functions (they'll simply
    // do nothing and return NULL)
    aiclUseDebugLibrary(FALSE); // always load AIC.mod, never AICD.mod
    if (aiclLoadAICLibrary(AfxGetInstanceHandle()) != true)
    {
        WT_L1_TRACE("Could not load AIC!\n");
        AfxMessageBox(IDS_ERR_AIC_REQUIRED, MB_OK | MB_ICONSTOP | MB_TOPMOST);
        goto GracefulExit;
    }

    int verMaj, verMin, verExtra = 10;
    AICGetDllVersion(verMaj, verMin, verExtra);
    // look for AIC version >= 1.4.0
    if (verMaj <= 1  &&  verMin < 4)
    {
        WT_L1_TRACE("Wrong AIC version=%d.%d!\n", verMaj, verMin);
        AfxMessageBox(IDS_ERR_WRONG_AIC, MB_OK | MB_ICONSTOP | MB_TOPMOST);
        goto GracefulExit;
    }

    // Store info passed to us
    IApplication* pApplication = NULL;
    if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
        || pApplication == NULL)
    {
        WT_L1_TRACE("QueryInterface(IID_IApplication) failed!\n");
        goto GracefulExit;
    }

    // == NO GRACEFUL EXISTS BEYOND THIS POINT ==

    m_dwCookie = dwCookie;
    g_dwCookie = dwCookie;

    // Create command dispatch, send info back to DevStudio
    CCommandsObj::CreateInstance(&m_pCommands);
    m_pCommands->AddRef();

    // The QueryInterface above AddRef'd the Application object.  It will
    //  be Release'd in CCommand's destructor.
    m_pCommands->SetApplicationObject(pApplication);

    // (see stdafx.h for the definition of VERIFY_OK)

    VERIFY_OK(pApplication->SetAddInInfo((long) AfxGetInstanceHandle(),
        (LPDISPATCH) m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, 
        m_dwCookie));

    // Inform DevStudio of the commands we implement

    VARIANT_BOOL    bRet;
    CString         strCmdString;
    CComBSTR        bszCmdString, bszMethod;

    for (int i = 0; i < cAddInCommands; i++)
    {
        strCmdString.LoadString(AddInCommands[i].idCmdString);
        const int pos = strCmdString.Find('\n');
        if (pos > 0)
        {
            strCmdString.Delete(0, pos);
        }
        strCmdString = AddInCommands[i].szCommand + strCmdString;
        bszCmdString = strCmdString;
        bszMethod    = AddInCommands[i].szCommand;
        VERIFY_OK(pApplication->
            AddCommand(bszCmdString, bszMethod, i, m_dwCookie, &bRet));

        if (bRet == VARIANT_FALSE)
		{
			// AddCommand failed because a command with this name already
			//  exists.  You may try adding your command under a different name.
			//  Or, you can fail to load as we will do here.
		}
    }

    // make sure the wizard runs if this is the first time the user
    // selects WndTabs in the add-ins dialog
    if (bFirstTime == VARIANT_TRUE)
    {
        cfg_iDoWizAtStartup = 1;
    }

    // find the MDI client area window
    {
        char cClassName[256];

        hMDIWnd = g_pDevStudioWnd->GetTopWindow()->m_hWnd;
        ::GetClassName(hMDIWnd, (LPTSTR)cClassName, sizeof(cClassName));
        while (strcmp(cClassName, "MDIClient") != 0)
        {
            hMDIWnd = ::GetNextWindow(hMDIWnd, GW_HWNDNEXT);
            WT_ASSERT(hMDIWnd);
            GetClassName(hMDIWnd, (LPTSTR)cClassName, sizeof(cClassName));
        }
    }
    WT_L1_TRACE("Found MDI client window, hwnd=%p\n", hMDIWnd);

    g_pDevStudioWnd->SetActiveWindow();


    // create the tabs window
    WT_L2_TRACE("Creating tabs window...\n");
    pGlobalTabs = new CTabsWindow(m_pCommands);
    pGlobalTabs->Create(g_pDevStudioWnd, 
        RBS_BANDBORDERS | RBS_AUTOSIZE | RBS_FIXEDORDER | RBS_DBLCLKTOGGLE, 
        WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | 
        CBRS_TOP | CBRS_SIZE_FIXED, AFX_IDW_REBAR );
    pMainFrame->EnableToolTips();

/*    pGlobalTabs->CreateEx(WS_EX_NOPARENTNOTIFY, NULL, "Tabs", 
        WS_CHILD | WS_CLIPSIBLINGS, CRect(0, 0, 1, 1), g_pDevStudioWnd, 0);
*/    WT_L2_TRACE("... done\n");
    
//    pGlobalTabs->LoadFrame(IDR_MAINFRAME, WS_CHILD| WS_CLIPSIBLINGS, g_pDevStudioWnd);
    pGlobalTabs->SetWindowPos(
        CWnd::FromHandle(hMDIWnd)->GetWindow(GW_HWNDPREV), 
        0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    pGlobalTabs->SetWindowText("WndTabs");
    pMainFrame->SetWindowText("WndTabs Frame");
    pMainFrame->ShowWindow(SW_SHOW);

    // make sure that all MDI window events (especially size changes...)
    //  pass through our handlers
    pGlobalMDIManager->DoSubclass(hMDIWnd);

    if (cfg_iSnap == ssMDI)
    {
        // set the the manager (MDI snap)
        pGlobalActiveManager = pGlobalMDIManager;
        pGlobalActiveManager->SetManaging(true);
    }

    HADDIN hAddIn;
    char buf[25];
    sscanf(g_cVersion, "%d.%d %s %d", &verMaj, &verMin, buf, &verExtra);
    hAddIn = AICRegisterAddIn("WndTabs", verMaj, verMin, verExtra, 
        AddInCallback);

    // the following function is available only if the user has AIC v1.2.0
    // or above.  to our advantage: it's defined as a "non-critical" function
    // to the loader, so if the user has AIC v.1.1.x (for some reason), this
    // will simply do nothing
    AICSetAddInVersionString(hAddIn, g_cVersion);

    WT_L1_TRACE(CBugReportsDlg::GetSysSummary());
    WT_L1_TRACE("\n");

    *OnConnection = VARIANT_TRUE;

    RETURN_INT(S_OK);
}

// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    WT_FN_TRACE_PARAMS("OnDisonnection", "%d", bLastTime);

    ForceEndInitThread();

    CCommands::Cleanup();

    delete CMainFrame::m_pCmdCtx;

    WT_L1_TRACE("Unregistering from AddInComm\n");
    HADDIN hAddin = AICGetAddIn("WndTabs");
    if (hAddin) AICUnregisterAddIn(hAddin);

    if (m_pCommands != NULL)
    {
        WT_L1_TRACE("UnadviseFromEvents\n");
        m_pCommands->UnadviseFromEvents();
        m_pCommands->Release();
        m_pCommands = NULL;
    }

    WT_L1_TRACE("Ending extensions...\n");
    EndExtensions();
    WT_L1_TRACE("Extensions closed\n");

    WT_L1_TRACE("Deleting g_pDevStudioWindow... ");
    delete g_pDevStudioWnd;
    WT_L1_TRACE("done\n");

    RETURN_INT(S_OK);
}
