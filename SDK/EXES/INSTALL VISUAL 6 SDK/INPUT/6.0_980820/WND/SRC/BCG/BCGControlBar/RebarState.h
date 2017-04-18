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

// RebarManager.h: interface for the CRebarManager class.
// By Nick Hodapp
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGREBARMANAGER_H__872AD541_859C_11D3_8735_FCF55404122E__INCLUDED_)
#define AFX_BCGREBARMANAGER_H__872AD541_859C_11D3_8735_FCF55404122E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGRebarState  
{
private:

	static BOOL CALLBACK LoadRebarStateProc(HWND hwnd, LPARAM lParam);
	static BOOL CALLBACK SaveRebarStateProc(HWND hwnd, LPARAM lParam);

public:
	static void LoadState (CString& strKey, CFrameWnd* pFrrame);
	static void SaveState (CString& strKey, CFrameWnd* pFrrame);
};

#endif // !defined(AFX_BCGREBARMANAGER_H__872AD541_859C_11D3_8735_FCF55404122E__INCLUDED_)
