/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// BugReportsDlg.h : header file
//

#if !defined(AFX_BUGREPORTSDLG_H__68AD0084_7420_11D3_BA45_0000861DFCE7__INCLUDED_)
#define AFX_BUGREPORTSDLG_H__68AD0084_7420_11D3_BA45_0000861DFCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HHSupp.h"

/////////////////////////////////////////////////////////////////////////////
// CBugReportsDlg dialog

class CBugReportsDlg : public CHHDialog
{
// Construction
public:
	CBugReportsDlg(CWnd* pParent = NULL);   // standard constructor

    static CString GetSysSummary();
    static CString MakeSupportMailURL();

// Dialog Data
	//{{AFX_DATA(CBugReportsDlg)
	enum { IDD = IDD_BUGREPORTS };
	CBCGButton	m_CopyBtn;
	CHyperLink	m_MailLink;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBugReportsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static CString GetOSVersion();

	// Generated message map functions
	//{{AFX_MSG(CBugReportsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUGREPORTSDLG_H__68AD0084_7420_11D3_BA45_0000861DFCE7__INCLUDED_)
