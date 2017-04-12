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

// BCGToolbarRegularMenuButton.h: interface for the CBCGToolbarRegularMenuButton class.
// By Sven Ritter
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARREGULARMENUBUTTON_H__0321FCC6_8BD5_11D3_A711_0090274409AC__INCLUDED_)
#define AFX_BCGTOOLBARREGULARMENUBUTTON_H__0321FCC6_8BD5_11D3_A711_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGToolbarMenuButton.h"

class BCGCONTROLBARDLLEXPORT CBCGToolbarRegularMenuButton : public CBCGToolbarMenuButton  
{
	DECLARE_SERIAL (CBCGToolbarRegularMenuButton)

public:
	virtual BOOL OnClick (CWnd* pWnd, BOOL bDelay = TRUE);
};

#endif // !defined(AFX_BCGTOOLBARREGULARMENUBUTTON_H__0321FCC6_8BD5_11D3_A711_0090274409AC__INCLUDED_)
