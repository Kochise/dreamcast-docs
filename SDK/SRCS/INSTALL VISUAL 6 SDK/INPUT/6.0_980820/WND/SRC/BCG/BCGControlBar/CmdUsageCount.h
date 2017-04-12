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

// CmdUsageCount.h: interface for the CCmdUsageCount class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDUSAGECOUNT_H__B7BDB593_32E1_11D3_A724_0090274409AC__INCLUDED_)
#define AFX_CMDUSAGECOUNT_H__B7BDB593_32E1_11D3_A724_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

class CCmdUsageCount : public CObject  
{
public:
	CCmdUsageCount();
	virtual ~CCmdUsageCount();

	virtual void Serialize (CArchive& ar);

	void AddCmd (UINT uiCmd);
	void Reset ();

	UINT GetCount (UINT uiCmd) const;
	BOOL HasEnouthInformation () const;

	BOOL IsFreqeuntlyUsedCmd (UINT uiCmd) const;

	static BOOL SetOptions (UINT nStartCount, UINT nMinUsagePercentage);

protected:
	CMap<UINT, UINT, UINT, UINT>	m_CmdUsage;
	UINT							m_nTotalUsage;

	static UINT						m_nStartCount;
	static UINT						m_nMinUsagePercentage;
};

#endif // !defined(AFX_CMDUSAGECOUNT_H__B7BDB593_32E1_11D3_A724_0090274409AC__INCLUDED_)
