/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// ColorButton.h : header file
//

#if !defined(AFX_COLORBUTTON_H__43268CC1_84DB_11D3_BA51_0000861DFCE7__INCLUDED_)
#define AFX_COLORBUTTON_H__43268CC1_84DB_11D3_BA51_0000861DFCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:
    COLORREF GetColor();
    COLORREF SetColor(COLORREF cr);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

    COLORREF m_cr;        
    CBitmap  m_bmp;
    CBrush   m_br;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__43268CC1_84DB_11D3_BA51_0000861DFCE7__INCLUDED_)
