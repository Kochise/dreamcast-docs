// Session.h : Declaration of the [!Session]

[!if=(FileExists, "FALSE")]
#ifndef __[!Session]_H_
#define __[!Session]_H_

#include "resource.h"       // main symbols
#include "[!RowsetFile]"
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, RowsetFile)]
[!endif]

class [!Session]TRSchemaRowset;
class [!Session]ColSchemaRowset;
class [!Session]PTSchemaRowset;

/////////////////////////////////////////////////////////////////////////////
// [!Session]
class ATL_NO_VTABLE [!Session] : 
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
	public IGetDataSourceImpl<[!Session]>,
	public IOpenRowsetImpl<[!Session]>,
	public ISessionPropertiesImpl<[!Session]>,
	public IObjectWithSiteSessionImpl<[!Session]>,
	public IDBSchemaRowsetImpl<[!Session]>,
	public IDBCreateCommandImpl<[!Session], [!Command]>
{
public:
	[!Session]()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}

	STDMETHOD(OpenRowset)(IUnknown *pUnk, DBID *pTID, DBID *pInID, REFIID riid,
					   ULONG cSets, DBPROPSET rgSets[], IUnknown **ppRowset)
	{
		[!Rowset]* pRowset;
		return CreateRowset(pUnk, pTID, pInID, riid, cSets, rgSets, ppRowset, pRowset);
	}


BEGIN_PROPSET_MAP([!Session])
	BEGIN_PROPERTY_SET(DBPROPSET_SESSION)
		PROPERTY_INFO_ENTRY(SESS_AUTOCOMMITISOLEVELS)
	END_PROPERTY_SET(DBPROPSET_SESSION)
END_PROPSET_MAP()

BEGIN_COM_MAP([!Session])
	COM_INTERFACE_ENTRY(IGetDataSource)
	COM_INTERFACE_ENTRY(IOpenRowset)
	COM_INTERFACE_ENTRY(ISessionProperties)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IDBCreateCommand)
	COM_INTERFACE_ENTRY(IDBSchemaRowset)
END_COM_MAP()

BEGIN_SCHEMA_MAP([!Session])
	SCHEMA_ENTRY(DBSCHEMA_TABLES, [!Session]TRSchemaRowset)
	SCHEMA_ENTRY(DBSCHEMA_COLUMNS, [!Session]ColSchemaRowset)
	SCHEMA_ENTRY(DBSCHEMA_PROVIDER_TYPES, [!Session]PTSchemaRowset)
END_SCHEMA_MAP()

};

class [!Session]TRSchemaRowset : 
	public CRowsetImpl< [!Session]TRSchemaRowset, CTABLESRow, [!Session]>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		USES_CONVERSION;
		C[!ShortName]WindowsFile wf;
		CTABLESRow trData;
		lstrcpyW(trData.m_szType, OLESTR("TABLE"));
		lstrcpyW(trData.m_szDesc, OLESTR("The Directory Table"));

		HANDLE hFile = INVALID_HANDLE_VALUE;
		TCHAR szDir[MAX_PATH + 1];
		DWORD cbCurDir = GetCurrentDirectory(MAX_PATH, szDir);
		lstrcat(szDir, _T("\\*.*"));
		hFile = FindFirstFile(szDir, &wf);
		if (hFile == INVALID_HANDLE_VALUE)
			return E_FAIL; // User doesn't have a c:\ drive
		FindClose(hFile);
		lstrcpynW(trData.m_szTable, T2OLE(szDir), SIZEOF_MEMBER(CTABLESRow, m_szTable));
		if (!m_rgRowData.Add(trData))
			return E_OUTOFMEMORY;
		*pcRowsAffected = 1;
		return S_OK;
	}

};


class [!Session]ColSchemaRowset : 
	public CRowsetImpl< [!Session]ColSchemaRowset, CCOLUMNSRow, [!Session]>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		USES_CONVERSION;
		C[!ShortName]WindowsFile wf;
		HANDLE hFile = INVALID_HANDLE_VALUE;
		TCHAR szDir[MAX_PATH + 1];
		DWORD cbCurDir = GetCurrentDirectory(MAX_PATH, szDir);
		lstrcat(szDir, _T("\\*.*"));
		hFile = FindFirstFile(szDir, &wf);
		if (hFile == INVALID_HANDLE_VALUE)
			return E_FAIL; // User doesn't have a c:\ drive
		FindClose(hFile);// szDir has got the tablename

		DBID dbid;
		memset(&dbid, 0, sizeof(DBID));
		dbid.uName.pwszName = T2OLE(szDir);
		dbid.eKind = DBKIND_NAME;
		return InitFromRowset < _RowsetArrayType > (m_rgRowData, &dbid, NULL, m_spUnkSite, pcRowsAffected);
	}
};

class [!Session]PTSchemaRowset : 
	public CRowsetImpl< [!Session]PTSchemaRowset, CPROVIDER_TYPERow, [!Session]>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		return S_OK;
	}
};

[!if=(FileExists, "FALSE")]
#endif //__[!Session]_H_
[!endif]
