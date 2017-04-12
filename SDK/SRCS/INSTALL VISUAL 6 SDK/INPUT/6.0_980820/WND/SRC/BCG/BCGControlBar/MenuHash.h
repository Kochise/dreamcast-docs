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

// MenuHash.h: interface for the CMenuHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_)
#define AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

class CBCGToolBar;

class CMenuHash
{
public:
	CMenuHash();
	virtual ~CMenuHash();

	BOOL SaveMenuBar (HMENU hMenu, CBCGToolBar* pBar);
	BOOL LoadMenuBar (HMENU hMenu, CBCGToolBar* pBar) const;

	void CleanUp ();

protected:
	CMap<HMENU, HMENU&, HANDLE, HANDLE&>	m_StoredMenues;
};

extern CMenuHash	g_menuHash;

#endif // !defined(AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_)
