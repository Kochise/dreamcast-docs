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

// BCGOutlookButton.h: interface for the CBCGOutlookButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGOUTLOOKBUTTON_H__EF4340F6_720D_11D3_A746_0090274409AC__INCLUDED_)
#define AFX_BCGOUTLOOKBUTTON_H__EF4340F6_720D_11D3_A746_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGToolbarButton.h"

class CBCGOutlookBar;

class CBCGOutlookButton : public CBCGToolbarButton  
{
	friend class CBCGOutlookBar;

	DECLARE_SERIAL(CBCGOutlookButton)

public:
	CBCGOutlookButton();
	virtual ~CBCGOutlookButton();

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual void OnChangeParentWnd (CWnd* pWndParent);

	virtual BOOL CanBeDropped (CBCGToolBar* pToolbar);
	virtual void SetImage (int iImage);

	virtual void Serialize (CArchive& ar);

protected:
	void ShadowRect (CDC* pDC, CRect& rect);

protected:
	CBCGOutlookBar*	m_pWndParentBar;
	UINT			m_uiPageID;
	CSize			m_sizeImage;
	BOOL			m_bIsWholeText;
};

#endif // !defined(AFX_BCGOUTLOOKBUTTON_H__EF4340F6_720D_11D3_A746_0090274409AC__INCLUDED_)
