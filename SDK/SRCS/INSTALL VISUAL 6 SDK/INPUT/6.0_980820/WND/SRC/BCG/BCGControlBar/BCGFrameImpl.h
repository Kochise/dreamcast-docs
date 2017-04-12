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

// BCGFrameImpl.h: interface for the CBCGFrameImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
#define AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBCGToolBar;
class CBCGMenuBar;
class CBCGPopupMenu;

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGFrameImpl
{
	friend class CBCGToolBar;
	friend class CBCGMDIFrameWnd;
	friend class CBCGFrameWnd;
	friend class CBCGOleIPFrameWnd;
	friend class CBCGMenuBar;
	friend class CBCGToolbarsPage;
	friend class CBCGWorkspace;
	friend class CBCGPopupMenu;
	friend class CBCGMiniDockFrameWnd;

public:
	CBCGFrameImpl(CFrameWnd* pFrame);
	virtual ~CBCGFrameImpl();

// Attributes:
public:
	const CBCGMenuBar* GetMenuBar () const
	{
		return m_pMenuBar;
	}

protected:
	UINT				m_uiUserToolbarFirst;
	UINT				m_uiUserToolbarLast;

	CObList				m_listUserDefinedToolbars;
	CObList				m_listTearOffToolbars;

	CString				m_strControlBarRegEntry;

	CBCGMenuBar*		m_pMenuBar;
	HMENU				m_hDefaultMenu;
	CFrameWnd*			m_pFrame;
	UINT				m_nIDDefaultResource;

// Operations
protected:

	static UINT GetFreeCtrlBarID (UINT uiFirstID, UINT uiLastID,
							const CObList& lstCtrlBars);

	// User-defined toolbars:
	void InitUserToobars (LPCTSTR lpszRegEntry, UINT uiUserToolbarFirst, UINT uiUserToolbarLast);
	void LoadUserToolbars ();
	void SaveUserToolbars (BOOL bFrameBarsOnly = FALSE);

	const CBCGToolBar* CreateNewToolBar (LPCTSTR lpszName);
	BOOL DeleteToolBar (CBCGToolBar* pToolBar);

	// Tear-off toolbars:
	void AddTearOffToolbar (CControlBar* pToolBar);
	void RemoveTearOffToolbar (CControlBar* pToolBar);

	void LoadTearOffMenus ();
	void SaveTearOffMenus (BOOL bFrameBarsOnly = FALSE);

	void OnCloseFrame();
	void OnLoadFrame();
	void RestorePosition(CREATESTRUCT& cs);

	BOOL IsDockStateValid (const CDockState& state);
	BOOL IsUserDefinedToolbar (const CBCGToolBar* pToolBar) const;

	void SetMenuBar (CBCGMenuBar* pMenuBar);
	CBCGToolBar* GetUserBarByIndex (int iIndex) const;

	void DockControlBarLeftOf(CControlBar* pBar, CControlBar* pLeftOf);

	void SetupToolbarMenu (	CMenu& menu, 
							const UINT uiViewUserToolbarCmdFirst,
							const UINT uiViewUserToolbarCmdLast);

	BOOL ProcessKeyboard (int nKey);
	BOOL ProcessMouseClick (UINT uiMsg, POINT pt, HWND hwnd);
	BOOL ProcessMouseMove (POINT pt);

	void FrameEnableDocking(CFrameWnd * pFrame, DWORD dwDockStyle);

	BOOL OnShowPopupMenu (CBCGPopupMenu* pMenuPopup, CFrameWnd* pWndFrame);
	BOOL OnMenuChar (UINT nChar);

	void SetDockState (const CDockState& state);

	static BOOL IsHelpKey (LPMSG lpMsg);
};

#endif // !defined(AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
