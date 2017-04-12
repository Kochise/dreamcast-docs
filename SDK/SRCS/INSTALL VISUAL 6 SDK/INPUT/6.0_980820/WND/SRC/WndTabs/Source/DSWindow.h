/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DSWindow.h : header file
//

#if !defined(AFX_DSWINDOW_H__6A06C13A_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_DSWINDOW_H__6A06C13A_4748_11D1_BC91_0000010016A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDSWindow window

class CTabsWindow;

class CDSWindow : public CTabManagerWindow
{
    DECLARE_DYNAMIC(CDSWindow)

// Construction
public:
    CDSWindow(HWND hDSWindow, CTabsWindow *pTabsWnd);

// Attributes
public:
    bool SetManaging(bool bManaging);
    HWND GetSaferHwnd();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDSWindow)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CDSWindow();

    // Generated message map functions
protected:

    //{{AFX_MSG(CDSWindow)
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnDestroy();
	//}}AFX_MSG
    afx_msg LRESULT OnSetWindowText(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP();

    void PostNcDestroy();

    int   m_cResizeRef;  // reference counting for resize handler
    BOOL  m_bLastZoom;
    int   m_Modified;
    SnapOrientations m_LastOrientation;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSWINDOW_H__6A06C13A_4748_11D1_BC91_0000010016A6__INCLUDED_)
