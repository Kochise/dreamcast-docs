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

// BCGMouseManager.h: interface for the CBCGMouseManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGMOUSEMANAGER_H__0A141F65_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
#define AFX_BCGMOUSEMANAGER_H__0A141F65_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGMouseManager : public CObject
{
	DECLARE_SERIAL(CBCGMouseManager)

public:
	CBCGMouseManager();
	virtual ~CBCGMouseManager();

// Operations:
public:
	BOOL AddView (int iViewId, UINT uiViewNameResId, UINT uiIconId = 0);
	BOOL AddView (int iId, LPCTSTR lpszViewName, UINT uiIconId = 0);
	UINT GetViewDblClickCommand (int iId) const;

	BOOL LoadState (LPCTSTR lpszProfileName = NULL);
	BOOL SaveState (LPCTSTR lpszProfileName = NULL);

// Customization operations:
	void GetViewNames (CStringList& listOfNames) const;
	int GetViewIdByName (LPCTSTR lpszName) const;
	UINT GetViewIconId (int iViewId) const;

	void SetCommandForDblClick (int iViewId, UINT uiCmd);

// Overrides:
protected:
	virtual void Serialize (CArchive& ar);

// Attributes:
protected:
	CMap<CString, LPCTSTR, int, int> 	m_ViewsNames;
	CMap<int, int, UINT, UINT>			m_ViewsToCommands;
	CMap<int, int, UINT, UINT>			m_ViewsToIcons;
};

extern CBCGMouseManager*	g_pMouseManager;

#endif // !defined(AFX_BCGMOUSEMANAGER_H__0A141F65_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
