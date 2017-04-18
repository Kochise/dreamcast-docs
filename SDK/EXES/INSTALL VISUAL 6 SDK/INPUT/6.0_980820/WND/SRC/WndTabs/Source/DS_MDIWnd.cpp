/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DS_MDIWnd.cpp : implementation file
//
// This class handles messages routed to DevStudio's MDI client area window.
// All window creation, destruction and activation events are monitored, and
// the tabs are updated accordingly.


#include "stdafx.h"
#include "WndTabs.h"
#include "TabManagerWindow.h"
#include "TabsWindow.h"
#include "DS_MDIWnd.h"
#include "DSWindow.h"
#include "Config.h"
#include "MainFrame.h"
#include "Extensions.h"
#include "DevStudioWnd.h"
#include "SDK_Supp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDS_MDIWnd

IMPLEMENT_DYNCREATE(CDS_MDIWnd, CSubclassWnd)

CDS_MDIWnd::CDS_MDIWnd()
{
    m_bWinChangeMsgPending = false;
    SetMakeSpace(true);
}

CDS_MDIWnd::~CDS_MDIWnd()
{
}


BEGIN_MESSAGE_MAP(CDS_MDIWnd, CTabManagerWindow)
    //{{AFX_MSG_MAP(CDS_MDIWnd)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_MDIREFRESHMENU, OnMDIEvent)
    ON_MESSAGE(WM_MDISETMENU, OnMDIEvent)

    ON_MESSAGE(WM_MDICREATE, OnMDICreate)
    ON_MESSAGE(WM_MDIDESTROY, OnMDIDestroy)
    ON_MESSAGE(WM_MDIWINCHANGE, OnMDIWinChange)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDS_MDIWnd message handlers

inline void CDS_MDIWnd::PostWinChangeMsg()
{
    static DWORD last_ev_time = 0;

    if ((GetTickCount() - last_ev_time) > 500)
    {
        m_bWinChangeMsgPending = false;
    }
    if (!m_bWinChangeMsgPending)
    {
        m_bWinChangeMsgPending = true;
        PostMessage(WM_MDIWINCHANGE, 0, 0);
        last_ev_time = GetTickCount();
    }
}

LRESULT CDS_MDIWnd::OnMDIEvent(WPARAM wParam, LPARAM lParam)
{
    LRESULT lRetVal = Default();
    PostWinChangeMsg();
    return lRetVal;
}

LRESULT CDS_MDIWnd::OnMDIWinChange(WPARAM wParam, LPARAM lParam)
{
    static bool bForceRepaint = false;

    WT_FN_TRACE("OnMDIWinChange");
    m_bWinChangeMsgPending = false;

    HWND hWnd = (HWND)SendMessage(WM_MDIGETACTIVE, 0, NULL);

    SendWndTabsEvent(WndTabs_Ev_WindowChanged, (int)hWnd);

    if (hWnd)
    {
        // are we really activating a new window?        
        if (pGlobalActiveDSWindow->GetSaferHwnd() == NULL  ||
            hWnd != pGlobalActiveDSWindow->m_hWnd)
        {
            WT_L3_TRACE("Activating HWND=%p\n", hWnd);
            delete pGlobalActiveDSWindow;
            pGlobalActiveDSWindow = NULL;
            pGlobalActiveDSWindow = new CDSWindow(hWnd, pGlobalTabs);

            if (!pGlobalActiveManager)
            {
                pGlobalActiveManager = pGlobalActiveDSWindow;
            }

            pGlobalActiveManager->SetManaging(true);
        }
    }

    if (GetWindowCount() != pGlobalTabs->m_pTabCtrl->GetItemCount())
    {
        bForceRepaint = true;
    }


    if (bForceRepaint)
    {
        WT_L2_TRACE("Force repaint\n");
        pGlobalActiveManager->PostUpdateMessage();
        bForceRepaint = false;
    }
    else
    {
        pGlobalTabs->ResyncActiveTab();
    }
    return 1;
}


LRESULT CDS_MDIWnd::OnMDICreate(WPARAM wParam, LPARAM lParam)
{
    LRESULT lRetVal = Default();

    WT_L3_TRACE("MDICreate %s\n", ((LPMDICREATESTRUCT)lParam)->szTitle);

    if (pGlobalActiveDSWindow->GetSaferHwnd() == NULL)
    {
        PostWinChangeMsg();
    }
    else
    {
        pGlobalActiveManager->PostUpdateMessage();
    }

    return lRetVal;
}

LRESULT CDS_MDIWnd::OnMDIDestroy(WPARAM wParam, LPARAM lParam)
{
    WT_L3_TRACE("MDIDestroy %p\n", wParam);
    LRESULT lRetVal = Default();

    // fail-safe
    if (::GetTopWindow(m_hWnd) == NULL) m_bWinChangeMsgPending = false;

    m_bWinChangeMsgPending = false;
    PostWinChangeMsg();
    return lRetVal;
}

BOOL CDS_MDIWnd::enumWinCounter(HWND hWnd, LPARAM lParam)
{
    if (::GetParent(hWnd) == pGlobalMDIManager->m_hWnd)
        (*((int *)lParam))++;
    return TRUE;
}

BOOL CDS_MDIWnd::enumMsgSender(HWND hWnd, LPARAM lParam)
{
    ::SendMessage(hWnd, lParam, 0, 0);
    return TRUE;
}

int CDS_MDIWnd::GetWindowCount() const
{
    int n = 0;
    ::EnumChildWindows(m_hWnd, enumWinCounter, (LPARAM)&n);
    return n;
}

void CDS_MDIWnd::SendMsgToWindows(UINT msg)
{
    ::EnumChildWindows(m_hWnd, enumMsgSender, msg);
}

void CDS_MDIWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
/*	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState(); //_afxThreadState.GetData();
    CMainFrame *pMainFrame = (CMainFrame *)pTheApp->m_pMainWnd;

    if (pMainFrame->PreTranslateMessage(&pThreadState->m_lastSentMsg))
    {
        return;
    }
*/	
	CTabManagerWindow::OnKeyDown(nChar, nRepCnt, nFlags);
}
