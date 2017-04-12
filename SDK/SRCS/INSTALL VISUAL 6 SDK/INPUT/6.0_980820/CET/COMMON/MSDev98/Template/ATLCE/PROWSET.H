// [!RowsetFile] : Declaration of the [!Rowset]

[!if=(FileExists, "FALSE")]
#ifndef __[!Rowset]_H_
#define __[!Rowset]_H_
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

class C[!ShortName]WindowsFile: 
	public WIN32_FIND_DATA
{
public:

BEGIN_PROVIDER_COLUMN_MAP(C[!ShortName]WindowsFile)
	PROVIDER_COLUMN_ENTRY("FileAttributes", 1, dwFileAttributes)
	PROVIDER_COLUMN_ENTRY("FileSizeHigh", 2, nFileSizeHigh)
	PROVIDER_COLUMN_ENTRY("FileSizeLow", 3, nFileSizeLow)
	PROVIDER_COLUMN_ENTRY("FileName", 4, cFileName)
	PROVIDER_COLUMN_ENTRY("AltFileName", 5, cAlternateFileName)
END_PROVIDER_COLUMN_MAP()

};

// [!Command]
class ATL_NO_VTABLE [!Command] : 
[!if=(ThreadingModel, "Single")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Apartment")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Both")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if=(ThreadingModel, "Free")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
	public IAccessorImpl<[!Command]>,
	public ICommandTextImpl<[!Command]>,
	public ICommandPropertiesImpl<[!Command]>,
	public IObjectWithSiteImpl<[!Command]>,
	public IConvertTypeImpl<[!Command]>,
	public IColumnsInfoImpl<[!Command]>

{
public:

BEGIN_COM_MAP([!Command])
	COM_INTERFACE_ENTRY(ICommand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IAccessor)
	COM_INTERFACE_ENTRY(ICommandProperties)
	COM_INTERFACE_ENTRY2(ICommandText, ICommand)
	COM_INTERFACE_ENTRY(IColumnsInfo)
	COM_INTERFACE_ENTRY(IConvertType)
END_COM_MAP()

// ICommand
public:

	HRESULT FinalConstruct()
	{
		HRESULT hr = CConvertHelper::FinalConstruct();
		if (FAILED (hr))
			return hr;
		hr = IAccessorImpl<[!Command]>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CUtlProps<[!Command]>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<[!Command]>::FinalRelease();
	}

	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, 
						  LONG * pcRowsAffected, IUnknown ** ppRowset);

	static ATLCOLUMNINFO* GetColumnInfo([!Command]* pv, ULONG* pcInfo)
	{
		return C[!ShortName]WindowsFile::GetColumnInfo(pv,pcInfo);
	}

BEGIN_PROPSET_MAP([!Command])
	BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
		PROPERTY_INFO_ENTRY(IAccessor)
		PROPERTY_INFO_ENTRY(IColumnsInfo)
		PROPERTY_INFO_ENTRY(IConvertType)
		PROPERTY_INFO_ENTRY(IRowset)
		PROPERTY_INFO_ENTRY(IRowsetIdentity)
		PROPERTY_INFO_ENTRY(IRowsetInfo)
		PROPERTY_INFO_ENTRY(IRowsetLocate)
		PROPERTY_INFO_ENTRY(BOOKMARKS)
		PROPERTY_INFO_ENTRY(BOOKMARKSKIPPED)
		PROPERTY_INFO_ENTRY(BOOKMARKTYPE)
		PROPERTY_INFO_ENTRY(CANFETCHBACKWARDS)
		PROPERTY_INFO_ENTRY(CANHOLDROWS)
		PROPERTY_INFO_ENTRY(CANSCROLLBACKWARDS)
		PROPERTY_INFO_ENTRY(LITERALBOOKMARKS)
		PROPERTY_INFO_ENTRY(ORDEREDBOOKMARKS)
	END_PROPERTY_SET(DBPROPSET_ROWSET)
END_PROPSET_MAP()

};

class [!Rowset] : public CRowsetImpl< [!Rowset], C[!ShortName]WindowsFile, [!Command]>
{
public:

	HRESULT Execute(DBPARAMS * pParams, LONG* pcRowsAffected)
	{
		USES_CONVERSION;
		BOOL bFound = FALSE;
		HANDLE hFile;

		LPTSTR  szDir = (m_strCommandText == _T("")) ? _T("*.*") : OLE2T(m_strCommandText);

		C[!ShortName]WindowsFile wf;
		hFile = FindFirstFile(szDir, &wf);
		if (hFile == INVALID_HANDLE_VALUE)
			return DB_E_ERRORSINCOMMAND;
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


[!if=(FileExists, "FALSE")]
#endif //__[!Rowset]_H_
[!endif]
