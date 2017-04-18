/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// ShortcutsDlg.h : header file
//

#if !defined(AFX_SHORTCUTSDLG_H__4DB77639_30CF_4728_B9FC_48F98F43FC42__INCLUDED_)
#define AFX_SHORTCUTSDLG_H__4DB77639_30CF_4728_B9FC_48F98F43FC42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShortcutsDlg dialog

class CShortcutsBase
{
public:
    CShortcutsBase();
    ~CShortcutsBase();

    int     m_nAccelSize;
    HACCEL  m_hAccelTable;
    LPACCEL m_lpAccel;

    void ApplyAccelChanges();
    void SetHKInAccel(int idCmd, int iVK, int iHKMod, CString& sConflicts);
    bool UnsetHKInAccel(int idCmd);

    static void ShowConflicts(const CString& sConflicts);

    static int HKMod2ACCELMod(int iHKMod);
    static int ACCELMod2HKMod(int iAccelMod);

    static CString GetCmdName(int idCmd);
};

class CShortcutsDlg : public CDialog, CShortcutsBase
{
// Construction
public:
	CShortcutsDlg(CWnd* pParent = NULL);   // standard constructor
    ~CShortcutsDlg();

// Dialog Data
	//{{AFX_DATA(CShortcutsDlg)
	enum { IDD = IDD_SHORTCUTS };
	CBCGButton	m_SuggestedBtn;
	CBCGButton	m_ClearBtn;
	CBCGButton	m_SetBtn;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnCancel();

// Implementation
protected:

    CHotKeyCtrl *GetHKCtrl(UINT idCmd);
    void UpdateDlgFromAccel();
    void UpdateAccelFromDlgData();

	// Generated message map functions
	//{{AFX_MSG(CShortcutsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void DoUpdateDlgItems();
	afx_msg void OnShowSuggested();
	afx_msg void OnClearShortcuts();
	afx_msg void OnSetShortcuts();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTSDLG_H__4DB77639_30CF_4728_B9FC_48F98F43FC42__INCLUDED_)
