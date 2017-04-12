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

#if !defined(AFX_BCGANIMCTRL_H__6891655B_66D7_11D3_A740_0090274409AC__INCLUDED_)
#define AFX_BCGANIMCTRL_H__6891655B_66D7_11D3_A740_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGAnimCtrl.h : header file
//

#ifndef BCG_NO_ANIMCONTROL

#include "bcgcontrolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGAnimCtrl window

class BCGCONTROLBARDLLEXPORT CBCGAnimCtrl : public CStatic
{
	DECLARE_DYNAMIC(CBCGAnimCtrl)

// Construction
public:
	CBCGAnimCtrl();

// Attributes
public:
	BOOL IsRunning () const
	{
		return m_bIsRunning;
	}

protected:
	CSize		m_sizeFrame;
	COLORREF	m_clrBack;
	CImageList	m_imagesAnim;
	CImageList*	m_pImagesAnim;
	int			m_iCurrFrame;
	int			m_iFrameCount;
	BOOL		m_bIsRunning;
	UINT		m_uiFrameRate;

// Operations
public:
	BOOL SetBitmap (UINT uiBmpId, int nFrameWidth, 
		COLORREF clrTransparent = RGB (255, 0, 255), // Use (COLORREF) -1 for opaque
		BOOL bSizeToContent = TRUE);
	BOOL SetBitmap (CImageList* pImagesAnim, BOOL bSizeToContent = TRUE);

	BOOL Play (UINT uiFrameRate = 0);
	BOOL Stop ();

	void SetFrameRate (UINT uiFrameRate);

	UINT GetFrameRate () const
	{
		return m_uiFrameRate;
	}

	void SetBackColor (COLORREF clrBack)	// (-1) - Transparent
	{
		m_clrBack = clrBack;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGAnimCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGAnimCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGAnimCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // BCG_NO_ANIMCONTROL

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGANIMCTRL_H__6891655B_66D7_11D3_A740_0090274409AC__INCLUDED_)
