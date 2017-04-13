// FileItem.h: interface for the CFileItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FileItem_H__08822C83_41B8_11D1_82B9_00A0C91BC942__INCLUDED_)
#define AFX_FileItem_H__08822C83_41B8_11D1_82B9_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileItem  
{
public:
	BOOL FOpenedInDebug();
	CRect& GetRect();
	CRect& GetDbgRect();
	void Touch(CRect& rectWnd, BOOL fInDebugger, BOOL fTouchTime);
	CString& GetDir();
	BOOL IsFile(LPCTSTR szFile);
	void SetFile(LPCTSTR szFile);
	CTime& GetTime();
	CString& GetFile();
	void SetDir(LPCTSTR szDir);
	BOOL IsDir(LPCTSTR szDir);
	CFileItem();
	CFileItem(LPCTSTR szDir,LPCTSTR szFile, CRect& rectWnd, BOOL fInDebugger);
	virtual ~CFileItem();

protected:
	BOOL m_fOpenedInDebug;
	int m_iViewType;
	CString m_strFile;
	CTime m_timeLast;
	CString m_strDir;
	CRect m_rectWnd;
	CRect m_rectWndDbg;
	BOOL m_fInDebugger;
	BOOL m_fNotInDebugger;
};

#endif // !defined(AFX_FileItem_H__08822C83_41B8_11D1_82B9_00A0C91BC942__INCLUDED_)
