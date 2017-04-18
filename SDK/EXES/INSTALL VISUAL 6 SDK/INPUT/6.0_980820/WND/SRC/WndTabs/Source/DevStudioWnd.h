/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DevStudioWnd.h : header file
//

#if !defined(AFX_DEVSTUDIOWND_H__BE917121_5C03_11D3_BA1A_000000000000__INCLUDED_)
#define AFX_DEVSTUDIOWND_H__BE917121_5C03_11D3_BA1A_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubclassWnd.h"

#define PATH_DS_INCLUDE     "$(DS_INCLUDE)"
#define PATH_DS_LIB         "$(DS_LIB)"
#define PATH_DS_EXEC        "$(DS_EXEC)"
#define PATH_DS_SOURCE      "$(DS_SOURCE)"
#define PATH_WORKSPACE      "$(WORKSPACE)"
#define PATH_ACTIVE_PRJ     "$(ACTIVE_PRJ)"
#define PATH_ALL_PRJS       "$(ALL_PRJS)"



/////////////////////////////////////////////////////////////////////////////
// CDevStudioWnd window

class CDevStudioWnd : public CSubclassWnd
{
    DECLARE_DYNCREATE(CDevStudioWnd)

// Construction
public:
	CDevStudioWnd(HWND hWndDevStudio);

// Attributes
public:
    CString m_cTitle;

    bool m_bInDebuggingSession;
    CString m_sCloseDebWndPath;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevStudioWnd)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

//	virtual BOOL PreTranslateMessage(MSG* pMsg);
    static LRESULT CALLBACK HookWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

// Implementation
public:
	virtual ~CDevStudioWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDevStudioWnd)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
    afx_msg LRESULT OnGetWindowText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

    void OnEndDebugSession();        
    void OnStartDebugSession();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVSTUDIOWND_H__BE917121_5C03_11D3_BA1A_000000000000__INCLUDED_)
