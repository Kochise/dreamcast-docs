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

// ImageHash.h: interface for the CImageHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEHASH_H__FBA4F684_D756_11D1_A64E_00A0C93A70EC__INCLUDED_)
#define AFX_IMAGEHASH_H__FBA4F684_D756_11D1_A64E_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CImageHash : public CObject  
{

public:
	CImageHash();
	virtual ~CImageHash();

	void Set (UINT uiCmd, int iImage, BOOL bUserImage);
	int Get (UINT uiCmd, BOOL bUserImage) const;
	void Clear (UINT uiCmd);
	void ClearAll ();

	static int GetImageOfCommand (UINT uiCmd, BOOL bUserImage);

protected:
	CMap<UINT, UINT, int, int>	m_StdImages;
	CMap<UINT, UINT, int, int>	m_UserImages;
};

extern CImageHash	g_ImageHash;

#endif // !defined(AFX_IMAGEHASH_H__FBA4F684_D756_11D1_A64E_00A0C93A70EC__INCLUDED_)
