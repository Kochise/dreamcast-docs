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

#ifndef __GLOBAL_DATA_H
#define __GLOBAL_DATA_H

/////////////////////////////////////////////////////////////////////////////
// Auxiliary System/Screen metrics

struct GLOBAL_DATA
{
	// solid brushes with convenient gray colors and system colors
	HBRUSH hbrBtnHilite, hbrBtnShadow;

	// color values of system colors used for CToolBar
	COLORREF clrBtnFace, clrBtnShadow, clrBtnHilite;
	COLORREF clrBtnText, clrWindowFrame;
	COLORREF clrBtnDkShadow, clrBtnLight;
	COLORREF clrGrayedText;
	COLORREF clrHilite;
	COLORREF clrTextHilite;
	COLORREF clrHotText;

	CBrush	brBtnFace;
	CBrush	brHilite;
	CBrush	brLight;
	CBrush	brBlack;

	HCURSOR	m_hcurStretch;
	HCURSOR	m_hcurStretchVert;
	HCURSOR	m_hcurHand;

	HICON	m_hiconTool;

	// Toolbar and menu fonts:
	CFont	fontRegular;
	CFont	fontBold;
	CFont	fontUnderline;
	CFont	fontVert;
	CFont	fontVertCaption;

	BOOL	bIsWindowsNT4;
	int		m_nBitsPerPixel;

// Implementation
	GLOBAL_DATA();
	~GLOBAL_DATA();

	void UpdateSysColors();
	void UpdateFonts();

	BOOL SetMenuFont (LPLOGFONT lpLogFont, BOOL bHorz);

	int GetTextHeight (BOOL bHorz = TRUE)
	{
		return bHorz ? m_nTextHeightHorz : m_nTextHeightVert;
	}

	void CleanUp ();

protected:

	void UpdateTextMetrics ();
	HBITMAP CreateDitherBitmap (HDC hDC);
	
	int	m_nTextHeightHorz;
	int	m_nTextHeightVert;
};

extern GLOBAL_DATA globalData;

void AFXAPI AfxDeleteObject(HGDIOBJ* pObject);

/////////////////////////////////////////////////////////////////////////////

#endif // __GLOBAL_DATA_H
