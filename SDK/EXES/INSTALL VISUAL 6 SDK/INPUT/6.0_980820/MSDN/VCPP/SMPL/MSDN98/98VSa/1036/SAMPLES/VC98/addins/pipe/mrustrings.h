// MRUStrings.h: interface for the CMRUStrings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_)
#define AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMRUStrings  
{
public:
	BOOL Create(HKEY hKeyParent, LPCTSTR lpszKeyName, CString& strName);
	BOOL SetString(int i, CString& strVal);
	BOOL GetString(int i, CString& strVal);
	BOOL Create(CRegKey& key, CString& strName);
	CMRUStrings();
	virtual ~CMRUStrings();

protected:
	CString m_strName;
	int m_cElementsMax;
	CRegKey m_regKey;
};

#endif // !defined(AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_)
