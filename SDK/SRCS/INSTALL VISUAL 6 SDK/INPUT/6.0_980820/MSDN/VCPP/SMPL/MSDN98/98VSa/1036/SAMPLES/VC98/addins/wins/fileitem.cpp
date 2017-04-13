// FileItem.cpp: implementation of the CFileItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FileItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileItem::CFileItem()
{

}

CFileItem::CFileItem(LPCTSTR szDir, LPCTSTR szFile, CRect& rectWnd, BOOL fInDebugger)
{
	m_strDir = szDir;
	m_strFile = szFile;
	m_timeLast = CTime::GetCurrentTime();
	m_rectWndDbg.SetRectEmpty();
	m_rectWnd.SetRectEmpty();
	m_fOpenedInDebug = FALSE;

	if (fInDebugger)
		m_rectWndDbg = rectWnd;
	else
		m_rectWnd = rectWnd;

	m_fInDebugger = fInDebugger;
	m_fNotInDebugger = !fInDebugger; // gets set at refresh...

}


CFileItem::~CFileItem()
{

}


BOOL CFileItem::IsDir(LPCTSTR szDir)
{
	if (m_strDir.CompareNoCase(szDir) == 0)
		return(TRUE);
	return(FALSE);
}

void CFileItem::SetDir(LPCTSTR szDir)
{
	m_strDir = szDir;
	m_strDir.MakeLower();
	m_timeLast = CTime::GetCurrentTime();
}

CString& CFileItem::GetFile()
{
	return(m_strFile);
}

CTime& CFileItem::GetTime()
{
	return(m_timeLast);
}

void CFileItem::SetFile(LPCTSTR szFile)
{
	m_strFile = szFile;
	m_strFile.MakeLower();
	m_timeLast = CTime::GetCurrentTime();
}

BOOL CFileItem::IsFile(LPCTSTR szFile)
{
	if (m_strFile.CompareNoCase(szFile) == 0)
		return(TRUE);
	return(FALSE);
}

CString& CFileItem::GetDir()
{
	return(m_strDir);
}

void CFileItem::Touch(CRect& rectWnd, BOOL fInDebugger, BOOL fTouchTime)
{
	if (fTouchTime)
	{
		m_timeLast = CTime::GetCurrentTime();
	}
	if (fInDebugger)
	{
		m_rectWndDbg = rectWnd;
		if (m_rectWnd.IsRectEmpty())
		{
			m_fOpenedInDebug = TRUE;
		}
	}
	else
	{
		m_rectWnd = rectWnd;
	}
}

CRect& CFileItem::GetDbgRect()
{
	return(m_rectWndDbg);
}

CRect& CFileItem::GetRect()
{
	return(m_rectWnd);
}

BOOL CFileItem::FOpenedInDebug()
{
	return(m_fOpenedInDebug);
}
