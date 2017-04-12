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

#if !defined(AFX_BCGREGISTRY_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
#define AFX_BCGREGISTRY_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Shane Martin
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    shane.kim@kaiserslautern.netsurf.de
/////////////////////////////////////////////////////////////////////////////
#include <winreg.h>

#define REG_RECT	0x0001
#define REG_POINT	0x0002

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGRegistry : public CObject
{
// Construction
public:
	CBCGRegistry (BOOL bAdmin, BOOL bReadOnly);
	virtual ~CBCGRegistry();

	struct REGINFO
	{
		LONG lMessage;
		DWORD dwType;
		DWORD dwSize;
	}
	m_Info;

// Operations
public:
	BOOL ReadKeyValues(CStringArray& Values);
	BOOL VerifyKey (LPCTSTR pszPath);
	BOOL VerifyValue (LPCTSTR pszValue);
	BOOL CreateKey (LPCTSTR pszPath);
	BOOL Open (LPCTSTR pszPath);
	void Close();

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteKey (LPCTSTR pszPath, BOOL bAdmin = FALSE);

	BOOL Write (LPCTSTR pszKey, int iVal);
	BOOL Write (LPCTSTR pszKey, DWORD dwVal);
	BOOL Write (LPCTSTR pszKey, LPCTSTR pszVal);
	BOOL Write (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Write (LPCTSTR pszKey, CByteArray& bcArray);
	BOOL Write (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Write (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Write (LPCTSTR pszKey, CWordArray& wcArray);
	BOOL Write (LPCTSTR pszKey, const CRect& rect);
	BOOL Write (LPCTSTR pszKey, LPPOINT& lpPoint);
	BOOL Write (LPCTSTR pszKey, LPBYTE pData, UINT nBytes);
	BOOL Write (LPCTSTR pszKey, CObList& list);
	BOOL Write (LPCTSTR pszKey, CObject& obj);
	BOOL Write (LPCTSTR pszKey, CObject* pObj);

	BOOL Read (LPCTSTR pszKey, int& iVal);
	BOOL Read (LPCTSTR pszKey, DWORD& dwVal);
	BOOL Read (LPCTSTR pszKey, CString& sVal);
	BOOL Read (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Read (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Read (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Read (LPCTSTR pszKey, CWordArray& wcArray);
	BOOL Read (LPCTSTR pszKey, CByteArray& bcArray);
	BOOL Read (LPCTSTR pszKey, LPPOINT& lpPoint);
	BOOL Read (LPCTSTR pszKey, CRect& rect);
	BOOL Read (LPCTSTR pszKey, BYTE** ppData, UINT* pBytes);
	BOOL Read (LPCTSTR pszKey, CObList& list);
	BOOL Read (LPCTSTR pszKey, CObject& obj);
	BOOL Read (LPCTSTR pszKey, CObject*& pObj);

	BOOL ReadSubKeys(CStringArray& SubKeys);

protected:

	HKEY		m_hKey;
	CString		m_sPath;
	const BOOL	m_bReadOnly;
};

#endif // #if !defined(AFX_BCGREGISTRY_H__A6E1AD76_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
