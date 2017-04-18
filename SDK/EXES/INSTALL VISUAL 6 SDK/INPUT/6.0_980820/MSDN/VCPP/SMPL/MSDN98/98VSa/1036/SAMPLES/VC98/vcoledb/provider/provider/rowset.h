// Rowset.h : Declaration of the CRowset
//
// This is a part of the ActiveX Template Library.
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#ifndef __ROWSET_H_
#define __ROWSET_H_

#include "resource.h"       // main symbols

class CWindowsFile:
	public WIN32_FIND_DATA
{
public:

BEGIN_PROVIDER_COLUMN_MAP(CWindowsFile)
	PROVIDER_COLUMN_ENTRY("FileAttributes", 1, dwFileAttributes)
	PROVIDER_COLUMN_ENTRY("FileSizeHigh", 2, nFileSizeHigh)
	PROVIDER_COLUMN_ENTRY("FileSizeLow", 3, nFileSizeLow)
	PROVIDER_COLUMN_ENTRY("FileName", 4, cFileName)
	PROVIDER_COLUMN_ENTRY("AltFileName", 5, cAlternateFileName)
END_PROVIDER_COLUMN_MAP()

};

class CWinRegKey
{
public:

BEGIN_PROVIDER_COLUMN_MAP(CWinRegKey)
	PROVIDER_COLUMN_ENTRY("Key Name", 1, m_szRegKey)
END_PROVIDER_COLUMN_MAP()

	WCHAR m_szRegKey[256];
};

// CDirCommand
class ATL_NO_VTABLE CDirCommand :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IAccessorImpl<CDirCommand>,
	public ICommandTextImpl<CDirCommand>,
	public ICommandPropertiesImpl<CDirCommand>,
	public IObjectWithSiteImpl<CDirCommand>,
	public IConvertTypeImpl<CDirCommand>,
	public IColumnsInfoImpl<CDirCommand>
{
public:

	HRESULT FinalConstruct()
	{
		HRESULT hr = CConvertHelper::FinalConstruct();
		if (FAILED (hr))
			return hr;
		hr = IAccessorImpl<CDirCommand>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CUtlProps<CDirCommand>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<CDirCommand>::FinalRelease();
	}

	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
						  LONG * pcRowsAffected, IUnknown ** ppRowset);

	static ATLCOLUMNINFO* GetColumnInfo(CDirCommand* pv, ULONG* pcInfo)
	{
		USES_CONVERSION;

		const int cbRegHeader = 5;
		TCHAR szRegHeader[cbRegHeader];
		CDirCommand* pCommand = (CDirCommand*)pv;
		lstrcpyn(szRegHeader, OLE2T(pCommand->m_strCommandText), cbRegHeader);

		if (lstrcmpi(szRegHeader, _T("REG:")) == 0)
			return CWinRegKey::GetColumnInfo(pv,pcInfo);
		else
			return CWindowsFile::GetColumnInfo(pv,pcInfo);
	}

BEGIN_PROPSET_MAP(CDirCommand)
	BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
		PROPERTY_INFO_ENTRY(IAccessor)
		PROPERTY_INFO_ENTRY(IColumnsInfo)
		PROPERTY_INFO_ENTRY(IConvertType)
		PROPERTY_INFO_ENTRY(IRowset)
		PROPERTY_INFO_ENTRY(IRowsetIdentity)
		PROPERTY_INFO_ENTRY(IRowsetInfo)
		PROPERTY_INFO_ENTRY(CANFETCHBACKWARDS)
		PROPERTY_INFO_ENTRY(CANHOLDROWS)
		PROPERTY_INFO_ENTRY(CANSCROLLBACKWARDS)
	END_PROPERTY_SET(DBPROPSET_ROWSET)
END_PROPSET_MAP()

BEGIN_COM_MAP(CDirCommand)
	COM_INTERFACE_ENTRY(ICommand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IAccessor)
	COM_INTERFACE_ENTRY(ICommandProperties)
	COM_INTERFACE_ENTRY2(ICommandText, ICommand)
	COM_INTERFACE_ENTRY(IColumnsInfo)
	COM_INTERFACE_ENTRY(IConvertType)
END_COM_MAP()

public:

};


class CRegRowset : public CRowsetImpl<CRegRowset, CWinRegKey, CDirCommand>
{
public:

	static HKEY HKeyFromString(LPTSTR szToken)
	{
		struct keymap
		{
			LPCTSTR lpsz;
			HKEY hkey;
		};
		static const keymap map[] = {
			{_T("HKCR"), HKEY_CLASSES_ROOT},
			{_T("HKCU"), HKEY_CURRENT_USER},
			{_T("HKLM"), HKEY_LOCAL_MACHINE},
			{_T("HKU"),  HKEY_USERS},
			{_T("HKPD"), HKEY_PERFORMANCE_DATA},
			{_T("HKDD"), HKEY_DYN_DATA},
			{_T("HKCC"), HKEY_CURRENT_CONFIG},
			{_T("HKEY_CLASSES_ROOT"), HKEY_CLASSES_ROOT},
			{_T("HKEY_CURRENT_USER"), HKEY_CURRENT_USER},
			{_T("HKEY_LOCAL_MACHINE"), HKEY_LOCAL_MACHINE},
			{_T("HKEY_USERS"), HKEY_USERS},
			{_T("HKEY_PERFORMANCE_DATA"), HKEY_PERFORMANCE_DATA},
			{_T("HKEY_DYN_DATA"), HKEY_DYN_DATA},
			{_T("HKEY_CURRENT_CONFIG"), HKEY_CURRENT_CONFIG}
		};

		for (int i=0;i<sizeof(map)/sizeof(keymap);i++)
		{
			if (!lstrcmpi(szToken, map[i].lpsz))
				return map[i].hkey;
		}
		return NULL;
	}

	HRESULT Execute(DBPARAMS *, LONG* pcRowsAffected)
	{
		USES_CONVERSION;
		CWinRegKey wrk;

		LPTSTR szKeyBegin = OLE2T(&(m_strCommandText[4]));
		LPTSTR szRootKey, szSubKey;

		int cbKey = lstrlen(szKeyBegin);
		int i=0;
		while (szKeyBegin[i] != '\\' && i < cbKey)
			i++;
		if (i < cbKey)
		{
			szRootKey = (TCHAR*)_alloca(sizeof(TCHAR)*(i+1));
			lstrcpyn(szRootKey, szKeyBegin, i+1);
			szSubKey = (TCHAR*)_alloca(sizeof(TCHAR)*(cbKey - i + 1));
			lstrcpy(szSubKey, szKeyBegin+i+1);
		}
		else
		{
			szRootKey = szKeyBegin;
			szSubKey = NULL;
		}


		HKEY hKey = CRegRowset::HKeyFromString(szRootKey);
		CRegKey rk;
		rk.Open(hKey, szSubKey, KEY_READ);

		DWORD dwIndex = 0;
		TCHAR szTemp[256];
		while (::RegEnumKey(rk.m_hKey,dwIndex, szTemp, 256) == ERROR_SUCCESS)
		{
			lstrcpyW(wrk.m_szRegKey, T2W(szTemp));
			if (!m_rgRowData.Add(wrk))
				return E_OUTOFMEMORY;
			dwIndex++;
		}

		if (pcRowsAffected != NULL)
			*pcRowsAffected = dwIndex;
		return S_OK;
	}
};

class CDirRowset :
	public CRowsetImpl< CDirRowset, CWindowsFile, CDirCommand>
{
public:
	// Implementation
	HRESULT ValidateCommandID(DBID* pTableID, DBID* pIndexID)
	{
		HRESULT hr = _RowsetBaseClass::ValidateCommandID(pTableID, pIndexID);
		if (hr != S_OK)
			return hr;

		if (pIndexID != NULL)
			return DB_E_NOINDEX;    // We don't support indexes

		return S_OK;
	}

	HRESULT Execute(DBPARAMS *, LONG* pcRowsAffected)
	{
		USES_CONVERSION;
		HANDLE hFile = INVALID_HANDLE_VALUE;

		LPTSTR  szDir = (m_strCommandText == _T("")) ? _T("*.*") : OLE2T(m_strCommandText);

		CWindowsFile wf;
		hFile = FindFirstFile(szDir, &wf);
		if (hFile == INVALID_HANDLE_VALUE)
			return DB_E_NOTABLE;
		LONG cFiles = 1;
		BOOL bMoreFiles = TRUE;
		while (bMoreFiles)
		{
			if (!m_rgRowData.Add(wf))
				return E_OUTOFMEMORY;

			bMoreFiles = FindNextFile(hFile, &wf);
			cFiles++;
		}
		FindClose(hFile);
		if (pcRowsAffected != NULL)
			*pcRowsAffected = cFiles;
		return S_OK;
	}
};


#endif //__ROWSET_H_
