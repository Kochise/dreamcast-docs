// MRUStrings.cpp: implementation of the CMRUStrings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pipe.h"
#include "MRUStrings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMRUStrings::CMRUStrings()
{
}

CMRUStrings::~CMRUStrings()
{

}

BOOL CMRUStrings::Create(CRegKey &key, CString& strName)
{
	BOOL fOK = TRUE;

	m_regKey = key;
	m_strName = strName;

	return(fOK);
}

BOOL CMRUStrings::GetString(int i, CString& strVal)
{
	CString strT;
	unsigned long lSize;
	BOOL fOK = FALSE;
	long lRes;

	strT.Format(_T("%s%d"), m_strName, i);
	strVal.Empty();
	lRes = m_regKey.QueryValue(strVal.GetBuffer(_MAX_PATH), strT, &lSize);
	strVal.ReleaseBuffer();
	fOK = !strVal.IsEmpty();	
	return(fOK);
}

BOOL CMRUStrings::SetString(int i, CString &strVal)
{
	CString strT;
	BOOL fOK = FALSE;
	long lRes;

	strT.Format(_T("%s%d"), m_strName, i);
	lRes = m_regKey.SetValue(strVal, strT);
	return(lRes == ERROR_SUCCESS);
}

BOOL CMRUStrings::Create(HKEY hKeyParent, LPCTSTR lpszKeyName, CString &strName)
{
	long lRes;

	lRes = m_regKey.Create(hKeyParent, lpszKeyName);
	m_strName = strName;
	return(lRes == ERROR_SUCCESS);
}
