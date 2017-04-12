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

// BCGControlBarImpl.h: interface for the CBCGControlBarImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGCONTROLBARIMPL_H__F8388FA2_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_)
#define AFX_BCGCONTROLBARIMPL_H__F8388FA2_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGControlBarImpl  
{
	friend class CBCGToolBar;
	friend class CBCGDialogBar;
	friend class CBCGSizingControlBar;

public:
	CBCGControlBarImpl(CControlBar* pBar);
	virtual ~CBCGControlBarImpl();

// Attributes:
protected:
	CControlBar*	m_pBar;

// Operations:
protected:
	void CalcNcSize (NCCALCSIZE_PARAMS FAR* lpncsp);

	void DrawNcArea ();
	void DrawBorders(CDC* pDC, CRect& rect);
	BOOL GetBackgroundFromParent (CDC* pDC);

	static void DrawGripper (CDC* pDC, CRect rectGripper, BOOL bHorz);
};

#endif // !defined(AFX_BCGCONTROLBARIMPL_H__F8388FA2_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_)
