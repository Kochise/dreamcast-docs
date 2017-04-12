/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// SubclassWnd.h : header file
//

#if !defined(AFX_SUBCLASSWND_H__BE917122_5C03_11D3_BA1A_000000000000__INCLUDED_)
#define AFX_SUBCLASSWND_H__BE917122_5C03_11D3_BA1A_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSubclassWnd window

class CSubclassWnd : public CWnd
{
    DECLARE_DYNCREATE(CSubclassWnd)

// Construction
public:
	CSubclassWnd(HWND hWndSubclass = NULL);

// Attributes
public:
    HWND m_Saved_hWnd;

    bool m_bIsSubclassed;

// Operations
public:
    void DoSubclass(HWND hWndSubclass = NULL);
    void DoUnsubclass();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubclassWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSubclassWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSubclassWnd)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCLASSWND_H__BE917122_5C03_11D3_BA1A_000000000000__INCLUDED_)
