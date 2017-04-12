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

#if !defined(AFX_BCGCOLORBUTTON_H__FEA34C6D_5D34_461C_9403_95C23C0B6F4A__INCLUDED_)
#define AFX_BCGCOLORBUTTON_H__FEA34C6D_5D34_461C_9403_95C23C0B6F4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGColorButton.h : header file
//

#ifndef BCG_NO_COLOR

#include "BCGButton.h"
#include "BCGColorBar.h"

class CColorPopup;

/////////////////////////////////////////////////////////////////////////////
// CBCGColorButton window

class BCGCONTROLBARDLLEXPORT CBCGColorButton : public CBCGButton
{
	friend class CBCGColorBar;

	DECLARE_DYNAMIC(CBCGColorButton)

// Construction
public:
	CBCGColorButton();

// Attributes
public:
	COLORREF GetColor () const
	{
		return m_Color;
	}

	void SetColor (COLORREF color /* -1 - automatic*/);

	void SetColumnsNumber (int nColumns)
	{
		m_nColumns = nColumns;
	}

	void EnableAutomaticButton (LPCTSTR lpszLabel, COLORREF colorAutomatic, BOOL bEnable = TRUE);
	void EnableOtherButton (LPCTSTR lpszLabel, BOOL bAltColorDlg = TRUE, BOOL bEnable = TRUE);
	
	void SetDocumentColors (LPCTSTR lpszLabel, CList<COLORREF,COLORREF>& lstColors);

	static void SetColorName (COLORREF color, const CString& strName)
	{
		CBCGColorBar::SetColorName (color, strName);
	}

protected:
	void UpdateColor (COLORREF color);

protected:
	COLORREF					m_Color;
	COLORREF					m_ColorAutomatic;
	CArray<COLORREF, COLORREF>	m_Colors;
	CList<COLORREF,COLORREF>	m_lstDocColors;
	int							m_nColumns;
	CColorPopup*				m_pPopup;

	CString						m_strOtherText;
	CString						m_strDocColorsText;
	CString						m_strAutoColorText;

	BOOL						m_bAltColorDlg;

// Operations
public:
	void SetPalette (CPalette* pPalette);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGColorButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGColorButton();
	virtual CSize SizeToContent (BOOL bCalcOnly = FALSE);

protected:
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);
	virtual void OnDrawBorder (CDC* pDC, CRect& rectClient, UINT uiState);
	virtual void OnDrawFocusRect (CDC* pDC, const CRect& rectClient);
	
	virtual void OnShowColorPopup ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGColorButton)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // BCG_NO_COLOR

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCOLORBUTTON_H__FEA34C6D_5D34_461C_9403_95C23C0B6F4A__INCLUDED_)
