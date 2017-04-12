/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// BCGSupp.cpp - BCG support classes

#include "stdafx.h"
#include "BCGSupp.h"
#include "Config.h"
#include "MainFrame.h"
#include "DevStudioWnd.h"
#include "WndTabs.h"


#define GETINSTANCE(hWnd)   (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE) 

static HHOOK s_hook      = NULL;
static HHOOK s_hookKB    = NULL;
static HHOOK s_hookMouse = NULL;

static DWORD s_msgThreadID = (DWORD)-1;


inline bool IsTooltipMessage(int message)
{
    return ((message == WM_MOUSEMOVE || message == WM_NCMOUSEMOVE ||
             message == WM_LBUTTONUP || message == WM_RBUTTONUP ||
             message == WM_MBUTTONUP) &&
            (GetKeyState(VK_LBUTTON) >= 0 && GetKeyState(VK_RBUTTON) >= 0 &&
             GetKeyState(VK_MBUTTON) >= 0));
}

static LONG cRefCount = -1;

LRESULT CALLBACK GetMsgProc(
  int iCode,       // hook code
  WPARAM wParam,  // removal flag
  LPARAM lParam   // address of structure with message
)  
{
    MSG * const pMsg = (MSG *)lParam;

    if (wParam != PM_REMOVE         ||
        pMsg->message == WM_TIMER   ||
        !g_pMainFrame)
    {
        // quick exit
        return CallNextHookEx(s_hook, iCode, wParam, lParam);
    }

    WT_ASSERT(g_pMainFrame == pTheApp->m_pMainWnd);
    
    if (InterlockedIncrement(&cRefCount) == 0)
    {
#ifdef _DEBUG
        if (s_msgThreadID != GetCurrentThreadId())
        {
            WT_ASSERT(FALSE);
            goto chain_hook;
        }
#endif

        CFrameWnd *& pRoutingFrame = AfxGetThreadState()->m_pRoutingFrame;
        if (pRoutingFrame  &&  pRoutingFrame->m_hWnd == g_pMainFrame->m_hWnd)
        {
            pRoutingFrame = (CFrameWnd *)g_pDevStudioWnd;
        }
    
        if (pTheApp->m_pMainWnd)
        {
            WT_L4_TRACE("GetMsgProc, wp=%d msg=%d", wParam, ((MSG *)lParam)->message);
            if (iCode == HC_ACTION)
            {
                WT_L4_TRACE(".. routing");
//                CWnd* pWnd = CWnd::FromHandle/*Permanent*/(pMsg->hwnd);
                HWND  hWnd;
//                if (pWnd->GetSafeHwnd())
                if (1)
                {
                    hWnd = pMsg->hwnd;
                    HWND  hWndParent = pTheApp->m_pMainWnd->m_hWnd;
                    while (hWnd  &&  hWnd != hWndParent)
                        hWnd = ::GetParent(hWnd);
                }
                else
                {
                    hWnd = NULL;
                }
                BOOL bRes = false;
                if (hWnd)
                {
//                    if ((pWnd->GetStyle() & WS_CHILD) != 0)
                    {
                        WT_MANAGE_STATE();
                        bRes = g_pMainFrame->PreTranslateMessage(pMsg);
                        if (bRes)
                        {
                            pMsg->message = WM_NULL;
                        }
                    }
                }
                else           
                {
                    if (!IsTooltipMessage(pMsg->message))
                    {
                        if (pMsg->message != WM_SYSKEYUP)
                        {
                            WT_MANAGE_STATE();
                            bRes = g_pMainFrame->PreTranslateMessage(pMsg);
                        }
                        if (bRes)
                        {
                            if (pMsg->message == WM_KEYDOWN  ||
                                pMsg->message == WM_SYSKEYDOWN)
                            {
                                // cloak keystrokes processed by the 
                                // WndTabs accelerators
                                pMsg->message = WM_NULL;
                            }
                            WT_L3_TRACE(" (*)");
                        }
                    }
                }
                if (bRes)
                {
                    WT_L4_TRACE(" - processed\n");
                    goto chain_hook;
                }
            }
            WT_L4_TRACE("\n");
        }
    }
    else
    {
//        MessageBeep(MB_OK);
    }

chain_hook:    
    LRESULT lResult = CallNextHookEx(s_hook, iCode, wParam, lParam);

    InterlockedDecrement(&cRefCount);

    return lResult;
}
 

LRESULT CALLBACK KeyboardProc(
  int iCode,       // hook code
  WPARAM wParam,  // virtual-key code
  LPARAM lParam   // keystroke-message information
)  
{
    WT_L4_TRACE("KeyboardProc, kb=%d ", wParam);
    if (iCode == HC_ACTION)
    {
        // If this is a repeat or the key is being released, ignore it.
        if (!(lParam & 0x80000000 || lParam & 0x40000000))
        {
            WT_L4_TRACE(".. routing");
            MSG msg;
            msg.hwnd = g_pDevStudioWnd->m_hWnd;
            msg.lParam = lParam;
            msg.wParam = wParam;
            msg.message = WM_KEYDOWN;
            WT_MANAGE_STATE();
            if (((CMainFrame *)pTheApp->m_pMainWnd)->PreTranslateMessage(&msg))
            {
                WT_L4_TRACE(" - processed\n");
                CallNextHookEx(s_hookKB, iCode, wParam, lParam);
                return 1;
            }
        }
    }
    WT_L4_TRACE("\n");
    
    return CallNextHookEx(s_hookKB, iCode, wParam, lParam);
}
 
LRESULT CALLBACK MouseProc(
  int iCode,       // hook code
  WPARAM wParam,  
  LPARAM lParam   
)  
{
    WT_L4_TRACE("MouseProc, msg=%d ", wParam);
    MOUSEHOOKSTRUCT& mhs = *(MOUSEHOOKSTRUCT *)lParam;
    
    if (iCode >= 0)
    {
        WT_L4_TRACE(".. routing");
        MSG msg;
        msg.hwnd = pTheApp->m_pMainWnd->m_hWnd;// g_pDevStudioWnd->m_hWnd;
        msg.wParam = mhs.dwExtraInfo;
        pTheApp->m_pMainWnd->ScreenToClient(&mhs.pt);
        msg.lParam = MAKELONG(mhs.pt.x, mhs.pt.y);
        msg.message = wParam;
        WT_MANAGE_STATE();
        if (((CMainFrame *)pTheApp->m_pMainWnd)->PreTranslateMessage(&msg))
        {
            WT_L4_TRACE(" - processed\n");
            CallNextHookEx(s_hookMouse, iCode, wParam, lParam);
            return 1;
        }
    }
    WT_L4_TRACE("\n");
    
    return CallNextHookEx(s_hookMouse, iCode, wParam, lParam);
}
 
void StopBCGHooks()
{
    if (s_hook)      UnhookWindowsHookEx(s_hook);
    if (s_hookKB)    UnhookWindowsHookEx(s_hookKB);
    if (s_hookMouse) UnhookWindowsHookEx(s_hookMouse);
    s_hook      = NULL;
    s_hookKB    = NULL;
    s_hookMouse = NULL;
    s_msgThreadID = (DWORD)-1;
}

void ResetBCGHooks()
{
    WT_L2_TRACE("Resetting hooks\n");
    WT_ASSERT(s_msgThreadID == -1  ||  s_msgThreadID == GetCurrentThreadId());
    StopBCGHooks();
    s_msgThreadID = GetCurrentThreadId();
    HINSTANCE hInst = (HINSTANCE)GETINSTANCE(g_pDevStudioWnd->m_hWnd);
    s_hook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, 
        NULL, GetCurrentThreadId());
    s_hookKB = s_hookMouse = 0;
//    s_hookKB = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hInst, 0);
//    s_hookMouse = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseProc, hInst, 0);
}



/////////////////////////////////////////////////////////////////////////////
// CWTMenuBar

IMPLEMENT_SERIAL(CWTMenuBar, CBCGMenuBar, VERSIONABLE_SCHEMA | 1)

BEGIN_MESSAGE_MAP(CWTMenuBar, CBCGMenuBar)
    //{{AFX_MSG_MAP(CWTMenuBar)
    ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CWTMenuBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    WT_FN_TRACE("CWTMenuBar::OnCreate");

    m_pLastHit = NULL;
    m_nLastHit = -1;
    m_ToolTipCtrl.Create(this, WS_VISIBLE | TTS_ALWAYSTIP);
    m_ToolTipCtrl.AddTool(this, "test");

    return CBCGMenuBar::OnCreate(lpCreateStruct);
}

BOOL CWTMenuBar::PreCreateWindow(CREATESTRUCT& cs)
{
	return CBCGMenuBar::PreCreateWindow(cs);
}

void CWTMenuBar::DoTooltipRelay(CPoint& point)
{
    MSG msg = AfxGetThreadState()->m_lastSentMsg;
    msg.time = 0;

    TOOLINFO ti; memset(&ti, 0, sizeof(TOOLINFO));
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_IDISHWND;
    ti.hwnd = m_hWnd;
    ti.uId = (UINT)m_hWnd;
    if (!m_ToolTipCtrl.SendMessage(TTM_GETTOOLINFO, 0, (LPARAM)&ti))
    {
        ASSERT(ti.uFlags == TTF_IDISHWND);
        ASSERT(ti.hwnd == m_hWnd);
        ASSERT(ti.uId == (UINT)m_hWnd);
        VERIFY(m_ToolTipCtrl.SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti));
    }

    // determine which tool was hit
    TOOLINFO tiHit; memset(&tiHit, 0, sizeof(TOOLINFO));
    tiHit.cbSize = sizeof(tiHit); //sizeof(AFX_OLDTOOLINFO);
    int nHit = OnToolHitTest(point, &tiHit);

    m_ToolTipCtrl.Activate(TRUE);
    // build new toolinfo and if different than current, register it
    CWnd* pHitWnd = nHit == -1 ? NULL : this;
    if (m_nLastHit != nHit || m_pLastHit != pHitWnd)
    {
        if (nHit != -1)
        {
            // add new tool and activate the tip
            ti = tiHit;
            ti.uFlags &= ~(TTF_NOTBUTTON|TTF_ALWAYSTIP);
            if (m_nFlags & WF_TRACKINGTOOLTIPS)
                ti.uFlags |= TTF_TRACK;
            VERIFY(m_ToolTipCtrl.SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti));
        }
        else
        {
            m_ToolTipCtrl.DelTool(this);
        }
        m_pLastHit = pHitWnd;
        m_nLastHit = nHit;
    }
    else
    {
        m_ToolTipCtrl.RelayEvent(&msg);
    }

    if ((tiHit.lpszText != LPSTR_TEXTCALLBACK) && (tiHit.hinst == 0))
        free(tiHit.lpszText);
}

void CWTMenuBar::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos)
{
    DWORD dwStyle = GetBarStyle();
    if (IS_HORIZONTAL(cfg_iOrientation))
    {
        dwStyle |= CBRS_BORDER_BOTTOM;
        if (!IsFloating())
        {
            dwStyle &= ~CBRS_BORDER_RIGHT;
        }
        else
        {
            dwStyle |= CBRS_BORDER_RIGHT;
        }
    }
    else
    {
        dwStyle &= ~CBRS_BORDER_RIGHT;
        if (!IsFloating())
        {
            dwStyle &= ~(CBRS_BORDER_BOTTOM | CBRS_BORDER_3D);
        }
        else
        {
            dwStyle |= CBRS_BORDER_BOTTOM;
        }
    }
    SetBarStyle(dwStyle);
    EnableToolTips(FALSE);
    CBCGMenuBar::OnWindowPosChanging(lpwndpos);
}

CSize CWTMenuBar::CalcLayout(DWORD dwMode, int nLength)
{
    CSize sz = CBCGMenuBar::CalcLayout(dwMode, nLength);

    if ((dwMode & (LM_HORZDOCK | LM_VERTDOCK)) &&
        pTheApp->m_pMainWnd->GetSafeHwnd())
    {
        CRect r;
        pTheApp->m_pMainWnd->GetWindowRect(r);
        if (dwMode & LM_HORZDOCK)
            sz.cy = r.Height() + 1;
        else
            sz.cx = r.Width() + 3;

        BOOL bVert = (dwMode & LM_VERTDOCK) || ((dwMode & LM_HORZ) == 0);

        if (!bVert)
        {
            CRect rect;
            GetClientRect(rect);
            WrapToolBar (rect.Width(), rect.Height());
        }

    }
    return sz;
}

void CWTMenuBar::CalculateCustomizeButton()
{
    static CString sBlank = "";

    if (IsFloating() == FALSE)
    {
        SetRedraw(FALSE);
        CSize sz;
        CRect r;
        BOOL bHorz = IS_HORIZONTAL(cfg_iOrientation);
        GetClientRect(r);
        if (m_pCustomizeBtn != NULL)
        {
            EnableCustomizeButton(FALSE, -1, sBlank);
            AdjustLayout();
        }
        sz = CalcSize(!bHorz);
        if (( bHorz  &&  sz.cx > (r.Width()  - 1))  ||
            (!bHorz  &&  sz.cy > (r.Height() - 1)))
        {
            EnableCustomizeButton(TRUE, -1, sBlank);
        }
        AdjustLayout();
        SetRedraw(TRUE);
        RedrawWindow();
    }
}

int CWTMenuBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ASSERT_VALID(this);
    // use toolbar handler
    return CBCGToolBar::OnToolHitTest(point, pTI);
}


// there is a problem on multiple monitor systems: dragging the toolbar 
// causes a crash.
// this function returns true is there is a danger of that happening.
bool CWTMenuBar::WillCrashOnMultipleMonitors(CPoint pt)
{
	ClientToScreen(&pt);
    if (pt.x < 0  ||  pt.y < 0)
    {
        return true;
    }
    return false;
}


void CWTMenuBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);

    // this should fix the problem with multiple monitor configurations
	if (m_pDockBar != NULL  &&  OnToolHitTest(point, NULL) == -1)
	{
        // if reached here, then this will be a drag operation
        if (WillCrashOnMultipleMonitors(point))
        {
            return;
        }
    }
	
	CBCGMenuBar::OnLButtonDown(nFlags, point);
}


void CWTMenuBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    if (WillCrashOnMultipleMonitors(point))
    {
        AfxMessageBox(IDS_CANT_UNDOCK, MB_OK | MB_ICONINFORMATION);
        return;
    }
	
	CBCGMenuBar::OnLButtonDblClk(nFlags, point);
}

void CWTMenuBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);
	
	CBCGMenuBar::OnLButtonUp(nFlags, point);
}

void CWTMenuBar::OnMButtonDown(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);
	
	CBCGMenuBar::OnMButtonDown(nFlags, point);
}

void CWTMenuBar::OnMButtonUp(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);
	
	CBCGMenuBar::OnMButtonUp(nFlags, point);
}

void CWTMenuBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);
	
	CBCGMenuBar::OnMouseMove(nFlags, point);
}

void CWTMenuBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	DoTooltipRelay(point);
	
	CBCGMenuBar::OnRButtonDown(nFlags, point);
}

void CWTMenuBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
    DoTooltipRelay(point);
	
	CBCGMenuBar::OnRButtonUp(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrameHolder


BEGIN_MESSAGE_MAP(CMainFrameHolder, CWnd)
    //{{AFX_MSG_MAP(CMainFrameHolder)
    ON_WM_CREATE()
    ON_WM_WINDOWPOSCHANGED()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMainFrameHolder::SetMF(CFrameWnd *pWndMF)
{
    m_pWndMF = pWndMF;
    m_pWndMF->SetParent(this);
}
int CMainFrameHolder::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    int iRetVal = CWnd::OnCreate(lpCreateStruct);
    return iRetVal;
}

void CMainFrameHolder::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos)
{
    if (m_pWndMF)
    {
        const BOOL bHorz = IS_HORIZONTAL(cfg_iOrientation);
        CRect r;
        GetWindowRect(r);
        ScreenToClient(r);
        CSize sz;
        if (bHorz)
        {
            r.top -= 2;
            r.bottom += 1;
        }
        else
        {
            r.top -= 2;
            r.bottom += 2;
        }

        CMainFrame *pFrame = (CMainFrame *)m_pWndMF;
        if (pFrame)
        {
            m_pWndMF->MoveWindow(r);
            pFrame->m_wndMenuBar.CalculateCustomizeButton();
            m_pWndMF->RecalcLayout(FALSE);
        }

    }
}
