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

#if !defined(AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_)
#define AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGDockBar.h : header file
//

#include "BCGSizingControlBar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGDockBar dummy class for access to protected members

class CBCGDockBar : public CDockBar
{
	friend class CBCGMenuBar;
	friend class CBCGSizingControlBar;
	friend class CBCGToolbarCustomize;
	friend class CBCGMiniDockFrameWnd;

	void SetCustomizationMode (BOOL bCustMode)
	{
		ASSERT_VALID (this);

#ifndef BCG_NO_SIZINGBAR

		CWnd* pWndChild = GetWindow (GW_CHILD);
		while (pWndChild != NULL)
		{
			CBCGSizingControlBar* pWndSizingCb = DYNAMIC_DOWNCAST (CBCGSizingControlBar, 
				pWndChild);

			if (pWndSizingCb != NULL)
			{
				pWndSizingCb->SetCustomizationMode (bCustMode);
			}

			pWndChild = pWndChild->GetNextWindow ();
		}

#endif // BCG_NO_SIZINGBAR

	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGDOCKBAR_H__9440A463_E272_11D1_A089_00A0C9B05590__INCLUDED_)
