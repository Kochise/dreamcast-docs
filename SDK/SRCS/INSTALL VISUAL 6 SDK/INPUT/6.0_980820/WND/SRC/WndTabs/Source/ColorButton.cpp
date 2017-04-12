/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton() : m_cr(RGB(0, 0, 0))
{
    static WORD wBmp[] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
    m_bmp.CreateBitmap(8, 8, 1, 1, &wBmp);
    m_br.CreatePatternBrush(&m_bmp);
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    CRect r(lpDrawItemStruct->rcItem);
    pDC->Draw3dRect(r, ::GetSysColor(COLOR_3DSHADOW),  
        ::GetSysColor(COLOR_3DHILIGHT));
    r.DeflateRect(1, 1);

    if (IsWindowEnabled())
    	pDC->FillSolidRect(&r, m_cr);
    else
    {
        pDC->SetTextColor(m_cr);
        pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE));
        pDC->FillRect(r, &m_br);
    }
}

void CColorButton::PreSubclassWindow() 
{
    ModifyStyle (0, BS_OWNERDRAW, 0);
	CButton::PreSubclassWindow();
}

COLORREF CColorButton::GetColor()
{
    return m_cr;
}

COLORREF CColorButton::SetColor(COLORREF cr)
{
    COLORREF cr_ret = m_cr;
    if (m_cr != cr)
    {
        m_cr = cr;
        Invalidate();
    }
    return cr_ret;
}
