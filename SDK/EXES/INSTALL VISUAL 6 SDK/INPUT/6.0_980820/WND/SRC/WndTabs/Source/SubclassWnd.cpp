/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// SubclassWnd.cpp : implementation file
//
// This is the base class for all subclassed windows.  It gives subclassed
// windows the ability to temporarily unsubclass themselves.


#include "stdafx.h"
#include "wndtabs.h"
#include "SubclassWnd.h"
#include "DontShowAgainDlg.h"
#include "Config.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubclassWnd

IMPLEMENT_DYNCREATE(CSubclassWnd, CWnd)

CSubclassWnd::CSubclassWnd(HWND hWndSubclass) : 
    m_Saved_hWnd(hWndSubclass), m_bIsSubclassed(false)
{
}

CSubclassWnd::~CSubclassWnd()
{
    DoUnsubclass();
}


BEGIN_MESSAGE_MAP(CSubclassWnd, CWnd)
	//{{AFX_MSG_MAP(CSubclassWnd)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSubclassWnd message handlers


/////////////////////////////////////////////////////////////////////////////
// CSubclassWnd operations

void CSubclassWnd::DoUnsubclass()
{
    // work-around for embedded windows:
    // if you open an external document (such as a WinWord file), WinWord
    // will destroy the window but our m_hWnd won't be updated
    if (!::IsWindow(m_hWnd))
    {
        m_hWnd = NULL;
        m_bIsSubclassed = false;
        return;
    }

    ASSERT_VALID(this);

    if (m_hWnd  &&  m_bIsSubclassed)
    {
        if (::GetWindowLong(m_hWnd, GWL_WNDPROC) == (LONG)AfxGetAfxWndProc()

            // patch to support the MouseImp utility 
            // (http://www.tv4studios.com/mouseimp/index.html)
            // patch courtesy of Goran Mitrovic [gmit@fly.srk.fer.hr]
            || ::GetModuleHandle("MImp.dll")
            || ::GetModuleHandle("MIPro.dll")

            )
        {
            UnsubclassWindow();
        }
        else
        {
            // someone subclassed after us (very bad!) - we'll unsubclass
            // anyway, hope for the best, and keep on going...

            // make a sound (even in release builds)
            MessageBeep(MB_ICONEXCLAMATION);

#ifdef _DEBUG
            // this is serious enough to warrent an intrusive error message
            // box, but only in the debug build so regular users won't be
            // bothered
            AfxMessageBox(IDS_ERR_DOUBLE_SUBCLASS, MB_OK | MB_ICONEXCLAMATION);
#endif
            CDontShowAgainDlg::DoMessageBox(IDS_UNSUBCLASS_ERR, 
                cfg_bShowUnsubclassErr);

            // log it
            WT_L1_TRACE("\nTrying to unsubclass a window that was "
                  "subclassed by someone else.  Class=%s\n",
                  this->GetRuntimeClass()->m_lpszClassName);

            UnsubclassWindow();
        }
        m_bIsSubclassed = false;
    }
}

void CSubclassWnd::DoSubclass(HWND hWndSubclass /*=NULL*/)
{
    ASSERT_VALID(this);
    ASSERT(!hWndSubclass  ||  ::IsWindow(hWndSubclass));

    if (hWndSubclass)
    {
        m_Saved_hWnd = hWndSubclass;
    }

    if (m_Saved_hWnd  &&  !m_bIsSubclassed)
    {
        SubclassWindow(m_Saved_hWnd);
        m_bIsSubclassed = true;
    }
}

// this handler "undoes" CWnd's default help-handling overrides
BOOL CSubclassWnd::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return Default();
}
