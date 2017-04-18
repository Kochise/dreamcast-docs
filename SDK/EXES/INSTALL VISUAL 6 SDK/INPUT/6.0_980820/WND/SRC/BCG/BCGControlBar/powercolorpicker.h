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
// Created by Martha Creedle

#if !defined(AFX_POWERCOLORPICKER_H__97753CC6_8513_47F3_B096_1D59D20E13FC__INCLUDED_)
#define AFX_POWERCOLORPICKER_H__97753CC6_8513_47F3_B096_1D59D20E13FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PowerColorPicker.h : header file
//

#ifndef BCG_NO_COLOR

#include "bcgcontrolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGColorPickerCtrl window

class BCGCONTROLBARDLLEXPORT CBCGColorPickerCtrl : public CButton
{
// Construction
public:
	CBCGColorPickerCtrl();
	virtual ~CBCGColorPickerCtrl();

// Attributes
public:

	enum COLORTYPE { CURRENT, LUMINANCE, PICKER, HEX, HEX_GREYSCALE };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGColorPickerCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetType (COLORTYPE colorType);
	void SetPalette (CPalette*	pPalette);

	void SetRGB(COLORREF ref);
	void SetOriginalColor (COLORREF ref);
	
	COLORREF GetRGB () const
	{
		return m_colorNew;
	}

	void SetHLS (double hue,double luminance, double saturation, BOOL bInvalidate = TRUE);
	void GetHLS (double *hue,double *luminance, double *saturation);

	void SetLuminanceBarWidth	(int w);

	double GetHue() const		{	return m_dblHue;	};
	double GetLuminance() const	{	return m_dblLum;	};
	double GetSaturation() const{	return m_dblSat;	};
	COLORREF GetColor() const	{	return m_colorNew;	};

	void SetHue(double Hue)					{	m_dblHue = Hue;			};
	void SetLuminance(double Luminance)		{	m_dblLum = Luminance;	};
	void SetSaturation(double Saturation)	{	m_dblSat = Saturation;	};
	void SetColor(COLORREF Color)			{	m_colorNew = Color;		};

	void SelectCellHexagon(BYTE R, BYTE G, BYTE B);

protected:
	void CreateHexagon ();
	void CreateHexGreyScaleBar ();

	void DrawHex (CDC* pDC);
	void DrawPicker (CDC* pDC);
	void DrawLuminanceBar(CDC* pDC);

	int GetAngleFromPoint(int nX, int nY);
	virtual void DrawCursor (CDC* pDC, const CRect& rect);

 	BOOL SelectCellHexagon (int x, int y);

	double LumFromPoint (int nY);
	int PointFromLum (double dblLum);

	CPoint GetCursorPos ();
	CRect GetCursorRect ();

	void NotifyParent ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGColorPickerCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
    COLORTYPE m_COLORTYPE;

	double		m_dblLum, m_dblSat, m_dblHue;
	COLORREF	m_colorNew;
	COLORREF	m_colorOriginal;

	int			m_nLumBarWidth;

	CPalette*	m_pPalette;
	CBitmap		m_bmpPicker;

	CObArray	m_arCells;	// Array of CCellObj's
};

COLORREF HLStoRGB_ONE( double H, double L, double S );
COLORREF HLStoRGB_TWO( double H, double L, double S );
static double HuetoRGB(double m1, double m2, double h );
BYTE HueToRGB(float rm1, float rm2, float rh);
void RGBtoHSL( COLORREF rgb, double *H, double *S, double *L );

#endif // BCG_NO_COLOR

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERCOLORPICKER_H__97753CC6_8513_47F3_B096_1D59D20E13FC__INCLUDED_)
