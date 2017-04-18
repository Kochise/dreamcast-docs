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

// BCGShowAllButton.h: interface for the CBCGShowAllButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGSHOWALLBUTTON_H__DE028D43_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_)
#define AFX_BCGSHOWALLBUTTON_H__DE028D43_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGToolbarMenuButton.h"

class CBCGShowAllButton : public  CBCGToolbarMenuButton  
{
	DECLARE_DYNCREATE(CBCGShowAllButton)

public:
	CBCGShowAllButton();
	virtual ~CBCGShowAllButton();

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd, BOOL bDelay = TRUE);
	virtual BOOL OpenPopupMenu (CWnd* pWnd = NULL);
	virtual BOOL OnToolHitTest (const CWnd* pWnd, TOOLINFO* pTI);
};

#endif // !defined(AFX_BCGSHOWALLBUTTON_H__DE028D43_36EB_11D3_95C5_00A0C9289F1B__INCLUDED_)
