//////////////////////////////////////////////////////////////////////////////
// SketchPad.h		- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- Header file for sketch pad dialog						//
//////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKETCHPAD_H__BCE02A24_71B4_11D1_B887_00AA00C0803B__INCLUDED_)
#define AFX_SKETCHPAD_H__BCE02A24_71B4_11D1_B887_00AA00C0803B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSketchPad : public CDialog
{
	int				m_PenSize;

	BOOL			m_bDrawing,
					m_bSaved,
					m_bBitmapLoaded,
					m_bFirstDraw;


	CPen			*m_pDrawingPen,
					*m_pErasingPen;

	LPBYTE			m_lpData;
	long			m_nDataSize;

	CPoint			m_Line[2];

	LPBITMAPINFO	m_lpbi;

	HWND			m_CommandWnd;

public:
	void	LoadSketch();
	void	SetData(LPBYTE lpData, long nSize);
	long	GetDataSize();
	LPBYTE	GetData();
	void	SaveSketch();
	void	OnEraseMode();
	void	OnDrawMode();
	void	OnClear();
	void	OnPenDecrease();
	void	OnPenIncrease();
	void	OnSave();

	CSketchPad(CWnd* pParent = NULL);   
	virtual ~CSketchPad();

	//{{AFX_DATA(CSketchPad)
	enum { IDD = IDD_SKETCH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSketchPad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CSketchPad)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKETCHPAD_H__BCE02A24_71B4_11D1_B887_00AA00C0803B__INCLUDED_)
