/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TabManagerWindow.cpp : implementation file
//
// This class is used to subclass DevStudio's windows.  It allows the 
// plug-in to monitor various messages that reach the window.
// TabManagerWindow is mainly responsible for moving and sizing the tabs
// window to it's appropriate position relative to the DevStudio window.
// The DevStudio window is also resized if needed.
//

#include "stdafx.h"
#include "wndtabs.h"
#include "TabManagerWindow.h"
#include "DS_MDIWnd.h"
#include "Options.h"
#include "TabsWindow.h"
#include "Commands.h"
#include "Config.h"
#include "DevStudioWnd.h"
#include "SDK_Supp.h"
#include "DontShowAgainDlg.h"
#include "DSAddin.h"
#include "DSWindow.h"
#include "AddInComm\AddInComm.h"
#include "MainFrame.h"
#include "SetupWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow

IMPLEMENT_DYNCREATE(CTabManagerWindow, CSubclassWnd)

CTabManagerWindow::CTabManagerWindow(HWND hSubclassWindow) :
    m_bDirty        (false),
    m_bManaging     (false), 
    m_bMakeSpace    (false), 
    CSubclassWnd(hSubclassWindow)
{
    m_LastPos = m_Border = CRect(0, 0, 0, 0);
    UpdateTabSize();
    DoSubclass();
}

CTabManagerWindow::~CTabManagerWindow()
{
    if (pGlobalActiveManager == this)
    {
       pGlobalActiveManager = NULL;
    }
    SetManaging(FALSE);
    DoUnsubclass();
}


BEGIN_MESSAGE_MAP(CTabManagerWindow, CSubclassWnd)
    //{{AFX_MSG_MAP(CTabManagerWindow)
    ON_WM_WINDOWPOSCHANGING()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
    ON_MESSAGE(WM_DOWIZARD, OnDoWizard)
    ON_MESSAGE(WM_LAZYINIT, OnLazyInit)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow message handlers

void CTabManagerWindow::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
    CSubclassWnd::OnWindowPosChanging(lpwndpos);

    if (m_bManaging)
    {
        CRect WndRect(lpwndpos->x, 
                      lpwndpos->y, 
                      lpwndpos->x + lpwndpos->cx,
                      lpwndpos->y + lpwndpos->cy);

        if (lpwndpos->flags & (SWP_NOSIZE | SWP_NOMOVE))
        {
            CRect WndRectOld;
            GetWindowRect(WndRectOld);
            GetParent()->ScreenToClient(WndRectOld);
            if (lpwndpos->flags & SWP_NOSIZE)
            {
                WndRect.bottom = WndRect.top  + WndRectOld.Height();
                WndRect.right  = WndRect.left + WndRectOld.Width();
            }
            if (lpwndpos->flags & SWP_NOMOVE)
            {
                WndRect.OffsetRect(WndRectOld.left - lpwndpos->x, 
                                   WndRectOld.top  - lpwndpos->y);
            }
        }

        if (WndRect != m_LastPos)
        {
            UpdateTabSizeAndPosition(WndRect);
            lpwndpos->x  = WndRect.left;
            lpwndpos->y  = WndRect.top;
            lpwndpos->cx = WndRect.right - WndRect.left;
            lpwndpos->cy = WndRect.bottom - WndRect.top;
            m_LastPos = WndRect;
        }
    }
}

// Though it isn't so apparent why the tab manager should have anything to
// do with the setup wizard, a little digging around will show you that this
// is due to thread synchronization and other stuff.
// See SplashDialog.cpp
LRESULT CTabManagerWindow::OnDoWizard(WPARAM wParam, LPARAM lParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (wParam == 0x1234  &&  (lParam & 0xFFF0) == 0x4320)
    {
        bool bDoWizard = true;

        VERIFY_OK(pGlobalTabs->m_pApplication->EnableModeless(VARIANT_FALSE));

        // the installation program will set this variable to 2 if it is 
        // already found in the registry (indicating that the program is 
        // already installed)
        if (cfg_iDoWizAtStartup > 1)
        {
/*            AfxMessageBox(IDS_WELCOME_UPDATE, MB_OK | MB_ICONINFORMATION);
            if (AfxMessageBox(IDS_WELCOME_UPDATE2, 
                MB_YESNO | MB_ICONQUESTION) != IDYES)
            {
                bDoWizard = false;
            }
*/        }

        if (bDoWizard)
        {
            CBitmap bmpWatermark;
            CBitmap bmpHeader;
            VERIFY(bmpWatermark.LoadBitmap(IDB_SW_BACKDROP));
            VERIFY(bmpHeader.LoadBitmap(IDB_SW_BANNER));
            CSetupWizard wiz(bmpWatermark, bmpHeader);
            theApp.Focus();
            wiz.DoModal();
            theApp.UnFocus();
        }

        cfg_iDoWizAtStartup = 0;

        VERIFY_OK(pGlobalTabs->m_pApplication->EnableModeless(VARIANT_TRUE));
    }
    
    return 0;
}

void CheckKeyBindings()
{
    CRegKey key;
    DWORD dw;
    bool bAsked = false;

    if (key.Open(HKEY_CURRENT_USER, DS6_ADDIN_KEY) != ERROR_SUCCESS)
    {
        return;
    }

    if (key.Open(HKEY_CURRENT_USER, DS6_AUT_KEY) != ERROR_SUCCESS)
    {
        return;
    }

    CString sBindings;
    if (cfg_bShowKeyBindingsWarn)
    {
        for (int i = 0; i < cAddInCommands; i++)
        {
            if (key.QueryValue(dw, AddInCommands[i].szCommand) == ERROR_SUCCESS)
            {
                if (!sBindings.IsEmpty())
                {
                    sBindings += ", ";
                }
                sBindings += AddInCommands[i].szCommand;
            }
        }
    }

    if (!sBindings.IsEmpty())
    {
        CString msg, s;
        AfxLoadString(IDS_WARN_KEY_BINDINGS, msg.GetBuffer(1024), 1024);
        msg.ReleaseBuffer();
        msg.Replace("%1", sBindings);
        s.LoadString(IDS_DONT_CHECK_CONDITION_AGAIN);
        if (CDontShowAgainDlg::DoMessageBox(msg,
            cfg_bShowKeyBindingsWarn, MB_YESNO | MB_ICONEXCLAMATION, s)
            == IDYES)
        {
            theApp.m_bDoDeleteVS6KeyBindings = true;
            AfxMessageBox(IDS_RESTART_FOR_KEYBINDING,
                MB_OK | MB_ICONINFORMATION);
        }
    }

    ACCEL *lpAccel = NULL;
    if (key.QueryValue(dw, "WWHeaderFlip") == ERROR_SUCCESS  ||
        key.QueryValue(dw, "VisualAssistOpenMatchingFile") == ERROR_SUCCESS)
    {
        // look for IDC_HEADERFLIP binding
        HACCEL hAccel = g_pMainFrame->m_hAccelTable;
        const int sz = ::CopyAcceleratorTable(hAccel, NULL, 0);
        lpAccel = new ACCEL [sz];
        ::CopyAcceleratorTable (hAccel, lpAccel, sz);
        for (int i = 0; i < sz; ++i)
        {
            ACCEL& a = lpAccel[i];
            if (a.cmd == IDC_HEADERFLIP)
            {
                CDontShowAgainDlg::DoMessageBox(IDS_WARN_OTHER_FLIPPER,
                    cfg_bShowWWhizFlipWarn, MB_OK | MB_ICONEXCLAMATION);
                break;
            }
        }
    }
    delete [] lpAccel;
}


static void DumpExtraLogInfo()
{
    WT_L1_TRACE("--- Configuration Variables ---\n");

#ifdef CFG_VAR
#undef CFG_VAR
#undef CFG_STR
#endif
#define CFG_VAR(name, type, var, defval) \
    WT_L1_TRACE(iformat, #name, var);
    #define CFG_STR(name, var, defval) \
    WT_L1_TRACE(sformat, #name, var);

    static const char * const iformat = "%-20s = %x\n";
    static const char * const sformat = "%-20s = %s\n";
#include "CfgVars.h"

    WT_L1_TRACE("-------------------------------\n"
                "--- Registered Addins ---------\n");

    int vermaj, vermin, verextra;
    const int addins = AICGetAddInCount();
    HADDIN *pAddins = new HADDIN[addins];
    AICGetAddInList(pAddins);
    for (int i = addins - 1; i >= 0; --i)
    {
        const HADDIN& hAddin = pAddins[i];
        AICGetAddInVersion(hAddin, vermaj, vermin, verextra);
        WT_L1_TRACE("%s ver %d.%d.%d", AICGetAddInName(hAddin),
            vermaj, vermin, verextra);
        LPCSTR pVerStr = AICGetAddInVersionString(hAddin);
        if (pVerStr)
        {
            WT_L1_TRACE(" (%s)\n", pVerStr);
        }
        else
        {
            WT_L1_TRACE("\n");
        }
    }
    delete [] pAddins;
    WT_L1_TRACE("-------------------------------\n");
}


// called about 1.5 seconds after the DevStudio initialization of WndTabs
LRESULT CTabManagerWindow::OnLazyInit(WPARAM wParam, LPARAM lParam)
{
    WT_FN_TRACE("OnLazyInit");

    CheckKeyBindings();

    if (cfg_iDoWizAtStartup)
    {
        PostMessage(WM_DOWIZARD, 0x1234, 0x4321);
    }

    if (g_pTheLogger->GetTraceLevel() > 0)
    {
        DumpExtraLogInfo();
    }

    // this is a perfect time to sniff around for addons
    Sleep(1500);
    RefreshActiveAddonsList();

    return 0;
}

// This timer event is used to periodically check that the tabs are in sync.
// with the current window list.  Since a full tab update takes time and
// may cause unwanted flicker, it is done only every 10 timer calls.  In all
// other cases, the tabs are updated if the number of windows isn't the same
// as the number of tabs (see below).
void CTabManagerWindow::OnTimer(UINT nIDEvent) 
{
    // first, a sanity check:
    ASSERT(this == pGlobalActiveManager);    
    ASSERT(pGlobalTabs);

    CSubclassWnd::OnTimer(nIDEvent);

    // fail safe
    static DWORD last_ticks = GetTickCount();
    if (GetTickCount() - last_ticks > 5000  ||  
        GetTickCount() < last_ticks)
    {
        last_ticks = GetTickCount();
        pGlobalTabs->m_iLockUpdates = 0;
    }

    if (nIDEvent == m_idTimer  &&  pGlobalTabs->m_pTabCtrl  &&
        pGlobalTabs->m_pTabCtrl->GetSafeHwnd())
    {
        if (++m_iTimerCount >= cfg_iRefreshInterval  &&  cfg_bAutoRefresh)
        {
            // Refresh at the given auto-refresh rate.  Sometimes things like
            // asterisks on tabs aren't updated, and we can compensate for
            // that by forcing the tabs to update
            pGlobalTabs->m_iLockUpdates = 0; /* force update */
            PostUpdateMessage();
            m_iTimerCount = 0;

            // if we reached here, then the dirty update interval (1 sec)
            // is slower than the tab update interval, and is therefore
            // not needed
//            m_bDirty = false;
        }
        else
        {
            if ((m_iTimerCount % 10) == 0  &&  m_bDirty)
            {
                // new patch: dirty flag allows delayed update of tabs
                // updated every 1 second
                pGlobalTabs->m_iLockUpdates = 1; /* no updates */
                pGlobalTabs->m_pCommands->FlashWindows(true);
                pGlobalTabs->m_iLockUpdates = 0; /* force update */
                PostUpdateMessage();
                m_bDirty = false;
            }
            else
            {
                // Quick check: update only if the number of windows changed.  
                // When the user causes a docked DevStudio window (i.e. 
                // Output, Disassembly, etc.) to open or close, we get no 
                // direct notification.  In some circumstances, the only 
                // evidence that anything changed is the fact that the number
                // of windows isn't the same as the number of tabs.
                // This check is preformed every 1/2 second.
                if (0  &&  (m_iTimerCount % 5) == 0)
                {
                    CheckTabCount();
                }
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow attributes

// true/false - is this object is responsible for handling the tabs.
// We will always have two tab managers: the MDI tab manager and the 
// subclassed DevStudio window.  Only one of them actually manages the tabs
// (according to the user's preference).
bool CTabManagerWindow::SetManaging(bool bManaging)
{
    WT_FN_TRACE_PARAMS("SetManaging", "%d", bManaging);

    if (m_hWnd == NULL)
        return m_bManaging;

    if (cfg_iOrientation != soBottom  &&  cfg_iOrientation != soTop)
    {
        cfg_iOrientation = soBottom;
    }

    WT_L1_TRACE("Currently %smanaging\n", (char *)(m_bManaging? "" : "not "));
    if (bManaging == m_bManaging)
        return m_bManaging;

    bool bOldVal = m_bManaging;
    m_bManaging = bManaging;

    static CString sOldActiveWinName;
    if (pGlobalActiveDSWindow->GetSafeHwnd())
    {
        pGlobalActiveDSWindow->GetWindowText(sOldActiveWinName);
    }

    m_LastPos.SetRectEmpty();

    UpdateTabSize();
    
    // add/remove the tabs
    if (m_bManaging)
    {
        ForceRedraw();
        pGlobalTabs->UpdateReBar();
/*        if (pGlobalMDIManager)
            pGlobalMDIManager->SendMessage(WM_MDIWINCHANGE);
*/        m_idTimer = SetTimer(101, 100, NULL);
        m_iTimerCount = 0;
    }
    else
    {
        if (m_idTimer)
        {
            KillTimer(m_idTimer);
            m_idTimer = 0;
        }

        // reclaim space used by the tabs
        ReclameTabSpace();
    }

    if (pGlobalMDIManager)
        pGlobalMDIManager->SendMessage(WM_MDIWINCHANGE);

    // restore name - the changes could have removed an asterisk
    if (pGlobalActiveDSWindow->GetSafeHwnd())
    {
        pGlobalActiveDSWindow->SetWindowText(sOldActiveWinName);
    }

    if (m_bManaging)
    {
        pGlobalTabs->CheckRowCount();
    }

    return bOldVal;
}

// true  - the manager shrinks the window so that both the tabs and
//         the window occupy the original area of the window
// false - the tabs are aligned along side the window
bool CTabManagerWindow::SetMakeSpace(bool bMakeSpace)
{
    if (m_bMakeSpace == bMakeSpace)
        return bMakeSpace;

    if (m_bManaging)
    {
        if (bMakeSpace)
        {
            ForceRedraw();
        }
        else
        {
            ReclameTabSpace();
        }
    }
    
    bool bOldVal = m_bMakeSpace;
    m_bMakeSpace = bMakeSpace;

    return bOldVal;
}

// Call SetBorder() to set an empty border around the tabs.  The tab
// window reads the border values from the tab manager and repaints
// accordingly.
CRect CTabManagerWindow::SetBorder(CRect Border)
{
    CRect OldBorder = m_Border;

    if (Border != m_Border)
    {
        bool bOldManaging = SetManaging(false);
        m_Border = Border;
        UpdateTabSize();
        SetManaging(bOldManaging);
    }

    return OldBorder;
}


/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow operations

void CTabManagerWindow::PostUpdateMessage()
{
    if (!this) return;
//    ASSERT_VALID(this);
//    ASSERT_VALID(pGlobalTabs);
    ASSERT(pGlobalActiveManager == this);
    ASSERT(pGlobalTabs != NULL);
    ASSERT(::IsWindow(pGlobalTabs->m_hWnd));
    
    // make sure we don't have multiple update messages in the queue if we
    // hadn't updated yet:
    pGlobalTabs->m_iLockUpdates++;

//  pGlobalTabs->UpdateTabs();
    pGlobalTabs->PostMessage(WM_UPDATETABS);
}

void CTabManagerWindow::SetDirty()
{
    m_bDirty      = true;
    m_iTimerCount = 0;    
}


/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow protected operations

// Checks if there are as many tabs as windows, and updates if needed.
// Useful in cases where DevStudio removes it's own undocked windows (such
// as Disassembly or Output), since we get no notification of it, and must
// check for it somehow
bool CTabManagerWindow::CheckTabCount()
{
    long                               cWindows;
    CComPtr<IDispatch>                 pDisp;
    CComQIPtr<IWindows, &IID_IWindows> pWindows;

    ASSERT(pGlobalTabs);

    if (pGlobalTabs->m_pTabCtrl)
    {
        pGlobalTabs->m_pApplication->get_Windows(&pDisp);
        pWindows = pDisp;
        pDisp = NULL;
        pWindows->get_Count(&cWindows);
        if (pGlobalTabs->m_pTabCtrl->GetItemCount() != cWindows)
        {
            PostUpdateMessage();
            return false;
        }
    }

    return true;
}

void CTabManagerWindow::ForceRedraw()
{
    // we want to make sure the OnWindowPosChanging handler is called
    CRect WndRect;
    GetWindowRect(&WndRect);
    GetParent()->ScreenToClient(&WndRect);
    MoveWindow(WndRect, TRUE);
}

void CTabManagerWindow::ReclameTabSpace()
{
    if (m_bMakeSpace)
    {
        CRect WndRect, TabsRect;
        GetWindowRect(&WndRect);
        pGlobalTabs->GetWindowRect(TabsRect);
        GetParent()->ScreenToClient(&WndRect);

        switch (cfg_iOrientation)
        {
            case soLeft:
                WndRect.left -= TabsRect.Width();
                break;

            case soRight:
                WndRect.right += TabsRect.Width();                
                break;

            case soTop:
                WndRect.top -= TabsRect.Height();
                break;

            case soBottom:
                WndRect.bottom += TabsRect.Height();
                break;

            DEFAULT_UNREACHABLE;
        }
        
        MoveWindow(WndRect, TRUE);
    }
}

void CTabManagerWindow::UpdateTabSizeAndPosition(CRect& WndRect)
{
    CRect TabsRect;

    if (!CalcTabsPosition(WndRect, TabsRect, SnapOrientations(cfg_iOrientation)))
        return;

    UpdateTabSize();

    pGlobalTabs->GetParent()->ScreenToClient(&TabsRect);
    CRect r;
    pGlobalTabs->GetWindowRect(r);
    pGlobalTabs->GetParent()->ScreenToClient(r);
    if (r != TabsRect)
    {
        pGlobalTabs->SetWindowPos(&wndBottom, 
            TabsRect.left, 
            TabsRect.top, 
            TabsRect.right - TabsRect.left,
            TabsRect.bottom - TabsRect.top,
            SWP_DRAWFRAME);

        // force redraw
        pGlobalTabs->RedrawWindow();     
        PostUpdateMessage();
    }
    pGlobalTabs->ShowWindow(SW_SHOW);
}

// TabsRect is returned in screen coordinates
bool CTabManagerWindow::CalcTabsPosition(CRect &WndRect, CRect &TabsRect,
    SnapOrientations o) const
{
    if (WndRect.top == WndRect.bottom)
        return false;

    CSize szTabs = CalcTabsSize(o);

    TabsRect = WndRect;

    switch (o)
    {
        case soLeft:
            if (m_bMakeSpace) 
                WndRect.left += szTabs.cx;
            else
                TabsRect.left -= szTabs.cx;

            TabsRect.right = TabsRect.left + szTabs.cx;
            break;

        case soRight:
            if (m_bMakeSpace) 
                WndRect.right -= szTabs.cx;
            else
                TabsRect.right += szTabs.cx;

            TabsRect.left = TabsRect.right - szTabs.cx;
            break;

        case soTop:
            if (m_bMakeSpace) 
                WndRect.top += szTabs.cy;
            else
                TabsRect.top -= szTabs.cy;

            TabsRect.bottom = TabsRect.top + szTabs.cy;
            break;

        case soBottom:
            if (m_bMakeSpace) 
                WndRect.bottom -= szTabs.cy;
            else
                TabsRect.bottom += szTabs.cy;

            TabsRect.top = TabsRect.bottom - szTabs.cy;
            break;

        DEFAULT_UNREACHABLE;
    }

    GetParent()->ClientToScreen(&TabsRect);

    return true;
}

CSize CTabManagerWindow::CalcTabsSize(SnapOrientations o) const
{
    if (!pGlobalTabs)
    {
        return CSize(0, 0);
    }

    const bool bIsHorizontal = IS_HORIZONTAL(o);
    const int  iMinHeight    = pGlobalTabs->m_pTabCtrl->m_iTabHeight;

    CSize sz;

    const int iRowHeight = TAB_BORDER_HEIGHT + 
        (iMinHeight) * g_cTabRows;

    if (bIsHorizontal)
    {
        sz.cy = iRowHeight + m_Border.left + m_Border.right + 4 + 2;
        sz.cx = 0;
    }
    else
    {
        sz.cx = iRowHeight + m_Border.top + m_Border.bottom + 4;
        sz.cy = 0;
    }

    ASSERT(sz.cx >= 0);
    ASSERT(sz.cy >= 0);

    return sz;
}

void CTabManagerWindow::UpdateTabSize()
{
    CSize szTab = CalcTabsSize(SnapOrientations(cfg_iOrientation));

    m_iTabHeight = szTab.cy;
    m_iTabWidth  = szTab.cx;
}
