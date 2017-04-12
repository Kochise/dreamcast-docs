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

#if !defined(AFX_BCGOUTLOOKBAR_H__D92D40D4_BD73_11D1_A63F_00A0C93A70EC__INCLUDED_)
#define AFX_BCGOUTLOOKBAR_H__D92D40D4_BD73_11D1_A63F_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// bcgoutlookbar.h : header file
//

#include "BCGToolbar.h"
#include "BCGToolbarImages.h"
#include "BCGOutlookButton.h"
#include "BCGButton.h"

class CBCGOutlookBarPage;

/////////////////////////////////////////////////////////////////////////////
// CBCGOutlookBar window

class BCGCONTROLBARDLLEXPORT CBCGOutlookBar : public CBCGToolBar
{
	DECLARE_DYNAMIC(CBCGOutlookBar)

// Construction
public:
	CBCGOutlookBar();
	virtual ~CBCGOutlookBar();

// Operations
public:
	//--------------------
	// Add/remove buttons:
	//--------------------
	BOOL AddButton (UINT uiImage, LPCTSTR lpszLabel, UINT iIdCommand, UINT uiPageID = (UINT)-1, int iInsertAt = -1);
	BOOL AddButton (UINT uiImage, UINT uiLabel, UINT iIdCommand, UINT uiPageID = (UINT)-1, int iInsertAt = -1);
	BOOL AddButton (LPCTSTR szBmpFileName, LPCTSTR szLabel, UINT iIdCommand, UINT uiPageID = (UINT)-1, int iInsertAt = -1);

	BOOL RemoveButton (UINT iIdCommand, UINT uiPageID = (UINT)-1 /* -1 - remove from all pages*/);

	//---------------
	// Pages support:
	//---------------
	BOOL AddPage (	UINT uiPageId,				// Unique page ID
					LPCTSTR lpszPageLabel,		// Page label
					CWnd* pWndPageCtrl = NULL,	// Page embedded control
					int iInsertAt = -1);
	BOOL RemovePage (UINT uiPageId);
	void RemoveAllPages ();

	void SetActivePage (UINT uiPageID, BOOL bAnimate = FALSE);
	UINT GetActivePageID () const
	{
		return m_uiActivePageID;
	}

	void SetPageName (UINT uiPageID, LPCTSTR lpszPageLabel);
	LPCTSTR GetPageName (UINT uiPageID) const;

	CWnd* GetPageControl (UINT uiPageID) const;
	UINT PageFromPoint (const CPoint& pt) const;

	BOOL StartAddPage		(UINT uiNewPageID, LPCTSTR lpszNewPageDefaultName);
	BOOL StartRenamePage	(UINT uiPageID);

	//--------------
	// General look:
	//--------------
	void SetTextColor (COLORREF clrRegText, COLORREF clrSelText = 0/* Obsolete*/);
	void SetTransparentColor (COLORREF color);
	void SetBackImage (UINT uiImageID);
	void SetBackColor (COLORREF color);

	void EnableSplitter (BOOL bEnable = TRUE);
	void EnableAnimation (BOOL bEnable = TRUE);

protected:
	BOOL InternalAddButton (int iImageIndex, LPCTSTR szLabel, UINT iIdCommand, UINT uiPageID = (UINT)-1, int iInsertAt = -1);
	int	 AddBitmapImage (HBITMAP hBitmap);

	void ScrollUp ();
	void ScrollDown ();

	void SetSplitterRect ();
	void ShowInvertSplitter ();
	void StopTracking ();

	void DrawTracker (CDC *pDC, const CRect& rectTracker);
	CBCGOutlookBarPage* GetPage (UINT uiPageID) const;
	CBCGOutlookBarPage* GetPageFromPoint (const CPoint& point) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGOutlookBar)
	public:
	virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID);
	//}}AFX_VIRTUAL

	virtual CSize CalcFixedLayout (BOOL bStretch, BOOL bHorz);
	virtual void RemoveAllButtons ();

	virtual void AdjustLocations ();
	virtual void DoPaint(CDC* pDC);
	virtual int HitTest(CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual CBCGToolbarButton* CreateDroppedButton (COleDataObject* pDataObject);
	virtual int FindDropIndex (const CPoint point, CRect& rectDrag) const;

	virtual BOOL EnableContextMenuItems (CBCGToolbarButton* pButton, CMenu* pPopup);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void OnActivatePage () {}

// Implementation

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGOutlookBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSysColorChange();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes
public:
	COLORREF GetRegularColor () const
	{
		return m_clrRegText;
	}

	BOOL IsDrawShadedHighlight () const
	{
		return m_bDrawShadedHighlight;
	}

	BOOL IsBackgroundTexture () const
	{
		return m_bmpBack.GetCount () != 0;
	}

	BOOL IsAnimation () const
	{
		return m_bEnableAnimation;
	}

protected:
	COLORREF			m_clrRegText;
	COLORREF			m_clrTransparentColor;
	COLORREF			m_clrBackColor;

	BOOL				m_bEnableSplitter;
	BOOL				m_bEnableAnimation;

	int					m_nSize;	// Width or Height, orientation dependable
	CRect				m_rectWorkArea;

	CSize				m_csImage;
	CBCGToolBarImages	m_bmpBack;
	UINT				m_uiBackImageId;

	CBCGButton			m_btnUp;
	CBCGButton			m_btnDown;
	int					m_iScrollOffset;
	int					m_iFirstVisibleButton;
	BOOL				m_bScrollDown;

	CBCGToolBarImages	m_Images;
	BOOL				m_bDrawShadedHighlight;

	CRect				m_rectSplitter;
	CRect				m_rectMoveSplitterScreen;
	BOOL				m_bIsTracking;
	int					m_nSplitterOffset;

	UINT				m_uiActivePageID;
	UINT				m_uiEditedPageID;
	UINT				m_uiDelayedPageID;
	CObList				m_lstPages;	// List of CBCGOutlookBarPage
	CRect				m_rectActivePageBtn;

	CEdit*				m_pInPlaceEdit;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGOUTLOOKBAR_H__D92D40D4_BD73_11D1_A63F_00A0C93A70EC__INCLUDED_)
