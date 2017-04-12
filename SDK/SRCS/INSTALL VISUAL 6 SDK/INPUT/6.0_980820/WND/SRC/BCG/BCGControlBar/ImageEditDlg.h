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

#if !defined(AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
#define AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImageEditDlg.h : header file
//

#include "bcgcontrolbar.h"
#include "ColorSelector.h"
#include "ImagePaintArea.h"
#include "bcgtoolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGImageEditDlg dialog

class BCGCONTROLBARDLLEXPORT CBCGImageEditDlg : public CDialog
{
	friend CImagePaintArea;

// Construction
public:
	CBCGImageEditDlg(CBitmap* pBitmap, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBCGImageEditDlg)
	enum { IDD = IDD_BCGBARRES_IMAGE_EDITOR };
	CStatic	m_wndPaletteBarLocation;
	CStatic	m_wndPreview;
	CImagePaintArea	m_wndLargeDrawArea;
	CColorSelector	m_wndColor;
	//}}AFX_DATA

// Operations:
protected:
	BOOL OnPickColor (COLORREF color);

	void SetMode (CImagePaintArea::IMAGE_EDIT_MODE mode)
	{
		m_wndLargeDrawArea.SetMode (mode);
	}

	CImagePaintArea::IMAGE_EDIT_MODE GetMode () const
	{
		return m_wndLargeDrawArea.GetMode ();
	}

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGImageEditDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCGImageEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnColors();
	afx_msg void OnBcgToolClear();
	afx_msg void OnBcgToolCopy();
	afx_msg void OnBcgToolPaste();
	afx_msg void OnUpdateBcgToolPaste(CCmdUI* pCmdUI);
	afx_msg void OnBcgToolEllipse();
	afx_msg void OnBcgToolFill();
	afx_msg void OnBcgToolLine();
	afx_msg void OnBcgToolPen();
	afx_msg void OnBcgToolPick();
	afx_msg void OnBcgToolRect();
	afx_msg void OnUpdateBcgToolEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolPen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolPick(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolRect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

// Attributes:
	CBitmap*					m_pBitmap;
	CSize						m_sizeImage;

	CRect						m_rectPreviewFrame;
	CRect						m_rectPreviewImage;

	CBCGToolBar					m_wndPaletteBar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEEDITDLG_H__07E27535_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
