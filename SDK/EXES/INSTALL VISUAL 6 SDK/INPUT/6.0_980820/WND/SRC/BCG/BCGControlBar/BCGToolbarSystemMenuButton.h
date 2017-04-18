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

// BCGToolbarSystemMenuButton.h: interface for the CBCGToolbarSystemMenuButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARSYSTEMMENUBUTTON_H__9BE97874_D37C_11D1_A649_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARSYSTEMMENUBUTTON_H__9BE97874_D37C_11D1_A649_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGToolbarMenuButton.h"

class CBCGToolbarSystemMenuButton : public CBCGToolbarMenuButton  
{
	DECLARE_SERIAL(CBCGToolbarSystemMenuButton)

public:
	CBCGToolbarSystemMenuButton();
	CBCGToolbarSystemMenuButton (HMENU hSystemMenu, HICON hSystemIcon);
	virtual ~CBCGToolbarSystemMenuButton();

// Overrides:
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);
	virtual void OnDblClick (CWnd* pWnd);
	virtual BOOL CanBeStored () const			{	return FALSE;	}
	virtual BOOL HaveHotBorder () const			{	return FALSE;	}
	virtual void Serialize (CArchive& /*ar*/)	{	ASSERT (FALSE);	}

	virtual void CreateFromMenu (HMENU hMenu);
	virtual HMENU CreateMenu () const;

// Attributes:
public:
	HICON GetSysMenuIcon () const
	{
		return m_hSysMenuIcon;
	}

	HMENU GetSysMenu () const
	{
		return m_hSystemMenu;
	}

protected:
	HICON	m_hSysMenuIcon;
	HMENU	m_hSystemMenu;
};

#endif // !defined(AFX_BCGTOOLBARSYSTEMMENUBUTTON_H__9BE97874_D37C_11D1_A649_00A0C93A70EC__INCLUDED_)
