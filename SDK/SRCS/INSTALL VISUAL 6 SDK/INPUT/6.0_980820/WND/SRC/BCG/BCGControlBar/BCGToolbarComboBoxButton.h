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

// BCGToolbarComboBoxButton.h: interface for the CBCGToolbarComboBoxButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"
#include "BCGToolbarButton.h"

class CBCGToolbarMenuButton;

class BCGCONTROLBARDLLEXPORT CBCGToolbarComboBoxButton : public CBCGToolbarButton  
{
	DECLARE_SERIAL(CBCGToolbarComboBoxButton)

public:
	CBCGToolbarComboBoxButton();
	CBCGToolbarComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0);
	virtual ~CBCGToolbarComboBoxButton();

// Operations:
	int AddItem (LPCTSTR lpszItem, DWORD dwData = 0);
	int GetCount () const;
	LPCTSTR GetItem (int iIndex = -1) const;
	DWORD GetItemData (int iIndex = -1) const;
	int GetCurSel () const
	{
		return m_iSelIndex;
	}
	void RemoveAllItems ();
	BOOL SelectItem (int iIndex, BOOL bNotify = TRUE);
	BOOL SelectItem (DWORD dwData);
	BOOL SelectItem (LPCTSTR lpszText);

	void SetDropDownHeight (int nHeight);

// Overrides:
	virtual CComboBox* CreateCombo (CWnd* pWndParent, const CRect& rect);

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual void Serialize (CArchive& ar);
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd, BOOL bDelay = TRUE);
	virtual void OnChangeParentWnd (CWnd* pWndParent);
	virtual void OnMove ();
	virtual void OnSize (int iSize);
	virtual HWND GetHwnd ()
	{	
		return m_pWndCombo->GetSafeHwnd ();
	}
	virtual BOOL NotifyCommand (int iNotifyCode);
	
	virtual BOOL CanBeStretched () const
	{	
		return TRUE;	
	}
	virtual void OnAddToCustomizePage ();
	virtual HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor);
	virtual BOOL HaveHotBorder () const
	{
		return m_pWndCombo->GetSafeHwnd () == NULL ||
			(m_pWndCombo->GetStyle () & WS_VISIBLE) == 0;
	}

	virtual int OnDrawOnCustomizeList (
			CDC* pDC, const CRect& rect, BOOL bSelected);

	virtual void DuplicateData () {}
	virtual void OnShow (BOOL bShow);
	virtual BOOL ExportToMenuButton (CBCGToolbarMenuButton& menuButton) const;

	virtual void SetStyle (UINT nStyle);

protected:
	void Initialize ();
	void AdjustRect ();

// Attributes:
public:
	CComboBox* GetComboBox () const
	{
		return m_pWndCombo;
	}

	LPCTSTR GetText () const
	{
		return m_strEdit;
	}

	void SetText (LPCTSTR lpszText);

	static CBCGToolbarComboBoxButton* GetByCmd (UINT uiCmd);
	static BOOL SelectItemAll (UINT uiCmd, int iIndex);
	static BOOL SelectItemAll (UINT uiCmd, DWORD dwData);
	static BOOL SelectItemAll (UINT uiCmd, LPCTSTR lpszText);
	static int GetCountAll (UINT uiCmd);
	static int GetCurSelAll (UINT uiCmd);
	static LPCTSTR GetItemAll (UINT uiCmd, int iIndex = -1);
	static DWORD GetItemDataAll (UINT uiCmd, int iIndex = -1);
	static void* GetItemDataPtrAll (UINT uiCmd, int iIndex = -1);
	static LPCTSTR GetTextAll (UINT uiCmd);

protected:
	DWORD				m_dwStyle;
	CComboBox*			m_pWndCombo;

	CStringList			m_lstItems;
	CList<DWORD, DWORD>	m_lstItemData;
	int					m_iWidth;
	int					m_iSelIndex;

	BOOL				m_bHorz;
	CString				m_strEdit;
	CRect				m_rectCombo;

	int					m_nDropDownHeight;
};

#endif // !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)
