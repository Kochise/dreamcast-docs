//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************
//
// This code is based on Ivan Zhakov (vanya@mail.axon.ru)'s
// MDI Windows Manager dialog 
// http://codeguru.developer.com/doc_view/WindowsManager.shtml
//

#if !defined(AFX_BCGWINDOWSMANAGERDLG_H__014E9113_B3C3_11D3_A712_009027900694__INCLUDED_)
#define AFX_BCGWINDOWSMANAGERDLG_H__014E9113_B3C3_11D3_A712_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGWindowsManagerDlg.h : header file
//

#include "bcgcontrolbar.h"
#include "bcgbarres.h"

class CBCGMDIFrameWnd;


BCGCONTROLBARDLLEXPORT extern UINT WM_BCGWINDOW_HELP; //WDW
/////////////////////////////////////////////////////////////////////////////
// CBCGWindowsManagerDlg dialog

class BCGCONTROLBARDLLEXPORT CBCGWindowsManagerDlg : public CDialog
{
// Construction
public:
	CBCGWindowsManagerDlg(CBCGMDIFrameWnd* pMDIFrame, BOOL bHelpButton = FALSE);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBCGWindowsManagerDlg)
	enum { IDD = IDD_BCGBARRES_WINDOWS_DLG };
	CListBox	m_wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGWindowsManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void			MDIMessage(UINT uMsg,WPARAM flag);
	void			FillWindowList(void);
	void			SelActive(void);
	void			UpdateButtons(void);

	CBCGMDIFrameWnd*	m_pMDIFrame;
	const BOOL			m_bHelpButton;

	// Generated message map functions
	//{{AFX_MSG(CBCGWindowsManagerDlg)
	afx_msg void OnActivate();
	afx_msg void OnSave();
	afx_msg void OnClose();
	afx_msg void OnCascade();
	afx_msg void OnTilehorz();
	afx_msg void OnTilevert();
	afx_msg void OnMinimize();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBcgbarresList();
	afx_msg void OnBcgbarresWindowHelp();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGWINDOWSMANAGERDLG_H__014E9113_B3C3_11D3_A712_009027900694__INCLUDED_)
