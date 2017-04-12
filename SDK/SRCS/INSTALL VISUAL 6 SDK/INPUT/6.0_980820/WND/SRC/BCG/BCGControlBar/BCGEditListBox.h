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

#if !defined(AFX_BCGEDITLISTBOX_H__80D80812_B943_11D3_A713_009027900694__INCLUDED_)
#define AFX_BCGEDITLISTBOX_H__80D80812_B943_11D3_A713_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGEditListBox.h : header file
//

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"
#include "BCGButton.h"

#define BGCEDITLISTBOX_BTN_NEW			0x0001
#define BGCEDITLISTBOX_BTN_DELETE		0x0002
#define BGCEDITLISTBOX_BTN_UP			0x0004
#define BGCEDITLISTBOX_BTN_DOWN			0x0008

#define BGCEDITLISTBOX_BTN_NEW_ID		(UINT)(-11)
#define BGCEDITLISTBOX_BTN_DELETE_ID	(UINT)(-12)
#define BGCEDITLISTBOX_BTN_UP_ID		(UINT)(-13)
#define BGCEDITLISTBOX_BTN_DOWN_ID		(UINT)(-14)

/////////////////////////////////////////////////////////////////////////////
// CBCGEditListBase window - edit list control abstract base class
// 
class BCGCONTROLBARDLLEXPORT CBCGEditListBase : public CStatic
{
// Construction
protected:
	CBCGEditListBase();

	CList<CBCGButton*, CBCGButton*>	m_lstButtons;
	CList<DWORD, DWORD>				m_lstKeyAccell;
	CMap<int,int,UINT,UINT>			m_mapButtonIDs;
	CSize							m_sizeButton;
	CRect							m_rectCaption;
	UINT							m_uiStandardBtns;
	BOOL							m_bNewItem;
	CFont							m_font;
	BOOL							m_bIsActualDelete;	// Indicated that Items is really deletd, not moved

// Operations
public:
	BOOL SetStandardButtons (UINT uiBtns =
		BGCEDITLISTBOX_BTN_NEW | BGCEDITLISTBOX_BTN_DELETE | BGCEDITLISTBOX_BTN_UP | BGCEDITLISTBOX_BTN_DOWN);

	BOOL AddButton (UINT uiImageResId, LPCTSTR lpszTooltip = NULL,
					WORD wKeyAccelerator = 0,
					BYTE fVirt = 0,
					UINT uiButtonID = 0);

	BOOL EnableButton (int iButtonNum, BOOL bEnable = TRUE);

	int GetButtonsCount () const
	{
		return m_lstButtons.GetCount ();
	}

	UINT GetButtonID (int iButtonNum) const;
	int GetButtonNum (UINT uiID) const;

	//-------------------------------------------------------------
	// These methods should be implemented in the actual edit list:
	//-------------------------------------------------------------
	virtual int AddItem (const CString& strIext, DWORD dwData = 0, int iIndex = -1) = 0;
	virtual BOOL RemoveItem (int iIndex) = 0;
	virtual int GetCount () const = 0;

	virtual int GetSelItem () const = 0;
	virtual BOOL SelectItem (int iItem) = 0;

	virtual CString GetItemText (int iIndex) const = 0;
	virtual void SetItemText (int iIndex, const CString& strText) = 0;
	virtual DWORD GetItemData (int iIndex) const = 0;
	virtual void SetItemData (int iIndex, DWORD dwData) = 0;

	virtual BOOL EditItem (int iIndex) = 0;

protected:
	void Init ();
	int GetStdButtonNum (UINT uiStdBtn) const;
	void AdjustLayout ();

// Overrides
public:
	virtual void OnClickButton (int iButton);
	virtual void OnKey (WORD wKey, BYTE fFlags);
	virtual void OnEndEditLabel (LPCTSTR lpszLabel);
	virtual int OnGetImage (LV_ITEM* /*pItem*/)
	{
		return -1;
	}
	
	virtual void OnSelectionChanged () {}

	// "Standard" action overrides
	virtual BOOL OnBeforeRemoveItem (int /*iItem*/)	{	return TRUE;	}
	virtual void OnAfterAddItem (int /*iItem*/) {}
	virtual void OnAfterRenameItem (int /*iItem*/) {}
	virtual void OnAfterMoveItemUp (int /*iItem*/) {}
	virtual void OnAfterMoveItemDown (int /*iItem*/) {}

protected:
	virtual void CreateNewItem ();

	virtual HWND GetListHwnd () const = 0;
	virtual CWnd* OnCreateList () = 0;
	virtual void OnSizeList () = 0;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGEditListBase)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGEditListBase();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGEditListBase)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
    afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBCGEditListBox window

class BCGCONTROLBARDLLEXPORT CBCGEditListBox : public CBCGEditListBase
{
// Construction
public:
	CBCGEditListBox();

// Attributes
public:
	CListCtrl*	m_pWndList;	// Embedded list control

// Operations
public:
	virtual int AddItem (const CString& strIext, DWORD dwData = 0, int iIndex = -1);
	virtual BOOL RemoveItem (int iIndex);
	virtual int GetCount () const;

	virtual int GetSelItem () const;
	virtual BOOL SelectItem (int iItem);

	virtual CString GetItemText (int iIndex) const;
	virtual DWORD GetItemData (int iIndex) const;
	virtual void SetItemData (int iIndex, DWORD dwData);

	virtual BOOL EditItem (int iIndex);

protected:
	virtual HWND GetListHwnd () const
	{
		return m_pWndList->GetSafeHwnd ();
	}

	virtual CWnd* OnCreateList ();
	virtual void OnSizeList ();
	virtual void SetItemText (int iIndex, const CString& strText);

// Overrides
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGEditListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGEditListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGEditListBox)
	//}}AFX_MSG
	afx_msg void OnKeyDown (LPNMLVKEYDOWN pKeyDown, LRESULT* pResult);
	afx_msg void OnDblclkList (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGEDITLISTBOX_H__80D80812_B943_11D3_A713_009027900694__INCLUDED_)
