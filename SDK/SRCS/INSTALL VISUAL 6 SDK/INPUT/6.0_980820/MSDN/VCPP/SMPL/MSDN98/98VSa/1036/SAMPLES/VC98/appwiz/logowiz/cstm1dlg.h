// cstm1dlg.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog
//
// This class handles the one custom step that is included in
// "My Logo Appwizard".  You will have a class much like this
// one for every custom step in your custom AppWizard.

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	int     m_nLogoSpot;
	int     m_nPressMe;
	//}}AFX_DATA
protected:
	int     m_nLogoWidth;       // logo dimensions
	int     m_nLogoHeight;
	int     m_nPressWidth;      // 'press me' button dimensions
	int     m_nPressHeight;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void SetSymbol(BOOL bWriteSymbol, LPCTSTR strName);
protected:
	void DrawLogo(int nOldID, int nNewID);
	void DrawBitmap(CDC* pdc, int nBitmapID, int nLocID);
	void EraseBitmap(CDC* pdc, int nLocID);
	void GetBitmapRect(int nLocID, LPRECT rect);
	int GetDlgBitmapID();
	void SetBitmapSize(int nID, int* width, int* height);
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnPressMe();
	//}}AFX_MSG
	afx_msg void OnLogoClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
