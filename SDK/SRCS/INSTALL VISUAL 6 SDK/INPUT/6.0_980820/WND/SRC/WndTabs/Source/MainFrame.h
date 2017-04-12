/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// MainFrame.h : header file
//

#if !defined(AFX_MAINFRAME_H__B208E8A0_6980_411A_9089_97FA47F05AD0__INCLUDED_)
#define AFX_MAINFRAME_H__B208E8A0_6980_411A_9089_97FA47F05AD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WndTabsSDK\WTSDKDefs.h"
#include "BCGSupp.h"

class CShellContextMenu;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame frame

class CMainFrame : public CBCGFrameWnd
{
    friend class CDevStudioWnd;
    
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame(); 
	virtual ~CMainFrame();

// Attributes
public:
	CWTMenuBar m_wndMenuBar;
    static WTSDK_CommandContext *m_pCmdCtx;
    CShellContextMenu *m_pSCM;
	CMenu m_scm;
    bool m_bCanClose;

//    CBCGToolBarImages m_AddOnImages;
    CBCGToolBar       m_wndAddOnToolbar;

// Operations
public:
    void DoCloseGroup(bool bInverse = false);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
    void CopyStringToClipboard(LPCTSTR str);
    void DoCloseAll(HWND hWndExcept = NULL);

	BOOL GetShellMenuItem(const CBCGToolbarMenuButton* pMenuButton, CMenu*& pMenu, int& item);
	virtual void OnClosePopupMenu (CBCGPopupMenu*);
    virtual BOOL OnShowPopupMenu(CBCGPopupMenu *);
	virtual BOOL OnDrawMenuImage(CDC* pDC,
        const CBCGToolbarMenuButton* pMenuButton, 
		const CRect& rectImage);
    virtual void OnDrawMenuLogo(CDC* pDC, CBCGPopupMenu* pMenu, 
        const CRect& rectLogo);

    CFont m_fontVertCaption;

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnOptions();
	afx_msg void OnCustomize();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRenumber();
	afx_msg void OnReorder();
	afx_msg void OnUpdateRenumber(CCmdUI* pCmdUI);
	afx_msg void OnUpdateReorder(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	afx_msg void OnAbout();
	afx_msg void OnIdleUpdateCmdUI();
	afx_msg void OnSave();
	afx_msg void OnSaveall();
	afx_msg void OnSelect();
	afx_msg void OnSetcurrdir();
	afx_msg void OnRoattr();
	afx_msg void OnProperties();
	afx_msg void OnOpenastext();
	afx_msg void OnMinimizeAll();
	afx_msg void OnHeaderflip();
	afx_msg void OnCopypath();
	afx_msg void OnCopyfilename();
	afx_msg void OnCopyfilenameNoPath();
	afx_msg void OnCopydoc();
	afx_msg void OnClosegroup();
	afx_msg void OnCloseallexcept();
	afx_msg void OnCloseall();
	afx_msg void OnCmdClose();
	afx_msg void OnUpdateOpenastext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeaderflip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdMustHaveFileAndDoc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdMustHaveOpenWindows(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdMustHaveFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdMustHaveDoc(CCmdUI* pCmdUI);
    afx_msg void OnUpdateCmdMustHaveTextDoc(CCmdUI* pCmdUI);
	afx_msg void OnSaveGroup();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnOpenfolder();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGroupNext();
	afx_msg void OnGroupPrev();
	afx_msg void OnUpdateCmdGroupPrevNext(CCmdUI* pCmdUI);
	afx_msg void OnSmarthelp();
	afx_msg void OnUpdateSmarthelp(CCmdUI* pCmdUI);
	afx_msg void OnTabNext();
	afx_msg void OnTabPrev();
	//}}AFX_MSG
    afx_msg void OnAddOnCmd(UINT nID);
    afx_msg void OnGoToTab(UINT nID);
    afx_msg void OnUpdateAddOnCmd(CCmdUI* pCmdUI);
	afx_msg LRESULT OnMenubarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnCustomizeHelp(WPARAM, LPARAM);
	afx_msg void OnShellContextCmd(UINT nID);
    afx_msg LRESULT OnSelectMenuItem (WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSetMessageString (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppCommand(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
private:
	static CMenu* FindExactMenuItem(CMenu* pMenu, int idx, UINT nID, CString text);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__B208E8A0_6980_411A_9089_97FA47F05AD0__INCLUDED_)
