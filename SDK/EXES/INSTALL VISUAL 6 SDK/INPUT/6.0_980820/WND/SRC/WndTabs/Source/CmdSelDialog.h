/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// CmdSelDialog.h : header file
//

#if !defined(AFX_CMDSELDIALOG_H__C0B609B0_0B4D_4207_B941_F91456026656__INCLUDED_)
#define AFX_CMDSELDIALOG_H__C0B609B0_0B4D_4207_B941_F91456026656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCmdSelDialog dialog

class CCmdSelDialog : public CDialog
{
// Construction
public:
	CCmdSelDialog(CWnd* pParent = NULL);   // standard constructor
    ~CCmdSelDialog();

// Dialog Data
	//{{AFX_DATA(CCmdSelDialog)
	enum { IDD = IDD_CMD_SEL };
	CListBox	m_wndCommandsList;
	CListBox	m_wndCategoryList;
	CString	m_strButtonDescription;
	//}}AFX_DATA

    int m_iCurrCommandID;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdSelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdSelDialog)
	afx_msg void OnSelchangeCommandList();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCategory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    class CBCGToolbarCustomize *m_pDlgCust;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDSELDIALOG_H__C0B609B0_0B4D_4207_B941_F91456026656__INCLUDED_)
