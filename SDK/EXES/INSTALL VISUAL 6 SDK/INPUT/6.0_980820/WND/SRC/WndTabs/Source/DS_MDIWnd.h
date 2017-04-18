/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DS_MDIWnd.h : header file
//

#if !defined(AFX_DS_MDIWND_H__C0A9F8C1_58D8_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_DS_MDIWND_H__C0A9F8C1_58D8_11D1_BC91_0000010016A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDSWindow;

/////////////////////////////////////////////////////////////////////////////
// CDS_MDIWnd window

class CDS_MDIWnd : public CTabManagerWindow
{
    DECLARE_DYNCREATE(CDS_MDIWnd)

// Construction
public:
    CDS_MDIWnd();

// Attributes
public:
    int GetWindowCount() const;

// Operations
public:
    void SendMsgToWindows(UINT msg);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDS_MDIWnd)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CDS_MDIWnd();

    // Generated message map functions
protected:
    //{{AFX_MSG(CDS_MDIWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnMDIEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMDICreate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMDIDestroy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMDIWinChange(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP();

	static BOOL CALLBACK enumWinCounter(HWND hWnd, LPARAM lParam);
	static BOOL CALLBACK enumWinCloser (HWND hWnd, LPARAM lParam);
	static BOOL CALLBACK enumMsgSender (HWND hWnd, LPARAM lParam);

    void PostWinChangeMsg();
    bool m_bWinChangeMsgPending;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DS_MDIWND_H__C0A9F8C1_58D8_11D1_BC91_0000010016A6__INCLUDED_)
