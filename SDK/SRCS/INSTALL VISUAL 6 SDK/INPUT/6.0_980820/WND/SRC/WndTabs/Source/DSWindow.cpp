/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DSWindow.cpp : implementation file
//
// This is a specialized tab manager window used to subclassed DevStudio
// document windows.  It's main responsibility is to manage the difference
// between zoomed and normal window states (zoomed windows require room
// for the tabs).
//


#include "stdafx.h"
#include "WndTabs.h"
#include "Commands.h"
#include "TabManagerWindow.h"
#include "TabsWindow.h"
#include "Options.h"
#include "Commands.h"
#include "DSWindow.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SWP_NOEVERYTHING  \
    (SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE)


/////////////////////////////////////////////////////////////////////////////
// CDSWindow

IMPLEMENT_DYNAMIC(CDSWindow, CTabManagerWindow)

CDSWindow::CDSWindow(HWND hDSWindow, CTabsWindow *pTabsWnd) : 
    CTabManagerWindow(hDSWindow), m_Modified(-1)
{
    m_cResizeRef = 0;
}

CDSWindow::~CDSWindow()
{
    if (pGlobalActiveDSWindow == this)
    {
       pGlobalActiveDSWindow = NULL;
    }
}


BEGIN_MESSAGE_MAP(CDSWindow, CTabManagerWindow)
    //{{AFX_MSG_MAP(CDSWindow)
    ON_WM_WINDOWPOSCHANGING()
    ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_SETTEXT, OnSetWindowText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDSWindow message handlers

void CDSWindow::OnDestroy() 
{
    if (m_bManaging)
    {
        pGlobalTabs->ShowWindow(SW_HIDE);
    }

    CTabManagerWindow::OnDestroy();
}

void CDSWindow::PostNcDestroy() 
{
    if (pGlobalActiveDSWindow == this)
    {
        pGlobalActiveDSWindow = NULL;
        delete this;
    }

    CTabManagerWindow::PostNcDestroy();
}

void CDSWindow::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
    if (GetManaging() &&
        (lpwndpos->flags & (SWP_NOMOVE | SWP_NOSIZE)) != 
        (SWP_NOMOVE | SWP_NOSIZE))
    {
        if (IsZoomed()  ||  
            cfg_iOrientation != m_LastOrientation)
        {
            m_LastOrientation = SnapOrientations(cfg_iOrientation);

            // Zoomed windows need to be resized to make room for the 
            //  tabs.  They also need a border.
            if (m_bLastZoom)
            {
                int cyCaption = GetSystemMetrics(SM_CYCAPTION) + 4;

                switch (cfg_iOrientation)
                {
                    case soLeft:
                        SetBorder(CRect(5, cyCaption, 0, 2));
                        break;

                    case soRight:
                        SetBorder(CRect(0, cyCaption, 5, 2));
                        break;
                
                    case soBottom:
                        SetBorder(CRect(4, 0, 0, 3));
                        break;
                }

                SetMakeSpace(true);
            }
            else
            {
                SetBorder(CRect(0, 0, 0, 0));
                SetMakeSpace(false);
            }
        }

        m_bLastZoom = IsZoomed();
    }

    CTabManagerWindow::OnWindowPosChanging(lpwndpos);
}


LRESULT CDSWindow::OnSetWindowText(WPARAM wParam, LPARAM lParam)
{
    int     newMod;
    LRESULT lRetVal = Default();
    CString cTitle;

    GetWindowText(cTitle);

    newMod = (cTitle.Right(2) == " *");

    // m_Modified: -1: unknown, 0: false, 1: true
    if (m_Modified != newMod)
    {
        if (m_Modified >= 0  &&  !pGlobalTabs->m_bAboutToUpdate)
            pGlobalActiveManager->PostUpdateMessage();
        m_Modified = newMod;
    }

    return lRetVal;
}



/////////////////////////////////////////////////////////////////////////////
// CDSWindow attributes

bool CDSWindow::SetManaging(bool bManaging)
{
    if (m_bManaging != bManaging)  // switch?
    {
        if (bManaging)
        {
            m_bLastZoom = FALSE;
            m_LastOrientation = SnapOrientations(999);  // force resize
        }
        else
        {
            pGlobalTabs->ShowWindow(SW_HIDE);
        }
    }

    return CTabManagerWindow::SetManaging(bManaging);
}

// needed for compatibility with Visual Assist 
HWND CDSWindow::GetSaferHwnd()
{
    if (!this) return NULL;
    return ::IsWindow(m_hWnd)? m_hWnd : NULL;
}
