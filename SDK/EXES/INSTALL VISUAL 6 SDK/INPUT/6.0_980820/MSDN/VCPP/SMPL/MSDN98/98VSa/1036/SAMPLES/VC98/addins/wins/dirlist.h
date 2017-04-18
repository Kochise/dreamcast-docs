// DirList.h: interface for the CDirList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRLIST_H__9C9E8F4C_A970_11D0_8CAF_000000000000__INCLUDED_)
#define AFX_DIRLIST_H__9C9E8F4C_A970_11D0_8CAF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "FileItem.h"

class CDirList : public CObject  
{
public:
	void Reset();
	int Count();
	CFileItem * GetNextPos(POSITION& p);
	POSITION GetHeadPosition();
	BOOL FAddDir(LPCTSTR strDir, LPCTSTR strFile, CRect& rectWnd, BOOL fInDebugger, BOOL fTouch = TRUE);
	CDirList();
	virtual ~CDirList();
	CList<CFileItem *, CFileItem *> m_dirList;
protected:
};

#endif // !defined(AFX_DIRLIST_H__9C9E8F4C_A970_11D0_8CAF_000000000000__INCLUDED_)
