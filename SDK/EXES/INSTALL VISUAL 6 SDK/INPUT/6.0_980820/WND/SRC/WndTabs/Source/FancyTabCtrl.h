/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// FancyTabCtrl.h : header file
//

#if !defined(AFX_FANCYTABCTRL_H__C1C8C892_5645_4DC0_BD7E_340B4A8A29A3__INCLUDED_)
#define AFX_FANCYTABCTRL_H__C1C8C892_5645_4DC0_BD7E_340B4A8A29A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFancyTabCtrl window

class CFancyTabCtrl : public CTabCtrl
{
// Construction
public:
	CFancyTabCtrl();

// Attributes
public:
    CPoint  m_LastRClickPos;
    CFont * m_pFont;
    int     m_iTabHeight;

// Operations
public:
    virtual void GetExtremeItemRect(CRect& r);

    void SetTabFont(CFont *pFont, BOOL bHasIcons);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFancyTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFancyTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFancyTabCtrl)
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

    virtual void GetCurrentItemRect(CRect& r);        
    virtual void GetLastItemRect(CRect& r);        
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FANCYTABCTRL_H__C1C8C892_5645_4DC0_BD7E_340B4A8A29A3__INCLUDED_)
