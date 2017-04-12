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

// BCGToolbarMenuButtonsButton.h: interface for the CBCGToolbarMenuButtonsButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARMENUBUTTONSBUTTON_H__A6E1AD74_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARMENUBUTTONSBUTTON_H__A6E1AD74_D511_11D1_A64D_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGToolbarButton.h"

class CBCGToolbarMenuButtonsButton : public CBCGToolbarButton  
{
	DECLARE_DYNCREATE(CBCGToolbarMenuButtonsButton)

public:
	CBCGToolbarMenuButtonsButton();
	CBCGToolbarMenuButtonsButton(UINT uiCmdId);
	virtual ~CBCGToolbarMenuButtonsButton();

// Overrides:
	virtual void Serialize (CArchive& /*ar*/)
	{
		ASSERT (FALSE);
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE,
						BOOL bDrawBorder = TRUE,
						BOOL bGrayDisabledButtons = TRUE);

	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL CanBeStored () const			{	return FALSE;	}
	virtual BOOL HaveHotBorder () const			{	return FALSE;	}

	virtual void CopyFrom (const CBCGToolbarButton& src);

// Attributes:
public:
	UINT	m_uiSystemCommand;
};

#endif // !defined(AFX_BCGTOOLBARMENUBUTTONSBUTTON_H__A6E1AD74_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
