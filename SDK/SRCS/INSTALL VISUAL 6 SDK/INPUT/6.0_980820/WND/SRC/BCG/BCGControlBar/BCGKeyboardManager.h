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

// BCGKeyboardManager.h: interface for the CBCGKeyboardManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_)
#define AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGKeyboardManager : public CObject
{
	friend class _KBD_TERM;

// Constructor/Destructor:
public:
	CBCGKeyboardManager();
	virtual ~CBCGKeyboardManager();

// Operattion:
public:
	BOOL LoadState (LPCTSTR lpszProfileName = NULL, CFrameWnd* pDefaultFrame = NULL);
	BOOL SaveState (LPCTSTR lpszProfileName = NULL, CFrameWnd* pDefaultFrame = NULL);

	BOOL UpdateAcellTable (CMultiDocTemplate* pTemplate, LPACCEL lpAccel, int nSize,
		CFrameWnd* pDefaultFrame = NULL);
	BOOL UpdateAcellTable (CMultiDocTemplate* pTemplate, HACCEL hAccelNew, CFrameWnd* pDefaultFrame = NULL);

	void ResetAll ();

	static BOOL FindDefaultAccelerator (UINT uiCmd, CString& str, CFrameWnd* pWndFrame,
										BOOL bIsDefaultFrame);
	static UINT TranslateCharToUpper (const UINT nChar);

	static void CleanUp ();

protected:
	BOOL SaveAccelaratorState (LPCTSTR lpszProfileName,
		UINT uiResId, HACCEL hAccelTable);
	BOOL LoadAccelaratorState (LPCTSTR lpszProfileName, 
		UINT uiResId, HACCEL& hAccelTable);
	
	static void SetAccelTable (LPACCEL& lpAccel, HACCEL& hAccelLast, int& nSize,
								const HACCEL hAccelCur);

	static LPACCEL	m_lpAccelDefault;	// Main frame acceleration table 
	static LPACCEL	m_lpAccel;			// Child frame acceleration table
	static int		m_nAccelDefaultSize;
	static int		m_nAccelSize;
	static HACCEL	m_hAccelDefaultLast;
	static HACCEL	m_hAccelLast;
};

extern CBCGKeyboardManager*	g_pKeyboardManager;

#endif // !defined(AFX_BCGKEYBOARDMANAGER_H__916B7A45_556A_11D2_B110_FD3F2C81B152__INCLUDED_)
