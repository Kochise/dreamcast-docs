/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TabManagerWindow.h : header file
//

#if !defined(AFX_TABMANAGERWINDOW_H__616A6550_C284_11D2_BC92_0000010016A6__INCLUDED_)
#define AFX_TABMANAGERWINDOW_H__616A6550_C284_11D2_BC92_0000010016A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubclassWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTabManagerWindow window

class CTabManagerWindow : public CSubclassWnd
{
    DECLARE_DYNCREATE(CTabManagerWindow)

    friend class CTabsWindow;

// Construction
public:
	CTabManagerWindow(HWND hSubclassWindow = NULL);

// Attributes
public:
    virtual bool  SetManaging (bool bManaging);
	virtual bool  SetMakeSpace(bool bMakeSpace);
	virtual CRect SetBorder(CRect Border);

    bool  GetManaging()  { return m_bManaging; }
    bool  GetMakeSpace() { return m_bMakeSpace; }
    CRect GetBorder()    { return m_Border; }

// Operations
public:
    void PostUpdateMessage();
    void SetDirty();
    bool CheckTabCount();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabManagerWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnWizard();
	virtual ~CTabManagerWindow();

	// Generated message map functions
protected:
	bool  m_bMakeSpace;
	bool  m_bManaging;
	CRect m_Border;
    CRect m_LastPos;
	int   m_iTabHeight;
	int   m_iTabWidth;
    UINT  m_idTimer;
    UINT  m_iTimerCount;
    bool  m_bDirty;

    void ForceRedraw();
	void ReclameTabSpace();
    void UpdateTabSizeAndPosition(CRect& WndRect);
	void UpdateTabSize();

    virtual CSize CalcTabsSize(SnapOrientations o) const;
    virtual bool CalcTabsPosition(CRect& WndRect, CRect& TabsRect, 
        SnapOrientations o) const;

    //{{AFX_MSG(CTabManagerWindow)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
    afx_msg LRESULT OnDoWizard(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLazyInit(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateTabs(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABMANAGERWINDOW_H__616A6550_C284_11D2_BC92_0000010016A6__INCLUDED_)
