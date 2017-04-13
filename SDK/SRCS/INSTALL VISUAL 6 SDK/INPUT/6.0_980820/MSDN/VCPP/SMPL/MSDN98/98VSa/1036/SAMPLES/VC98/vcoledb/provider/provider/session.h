// Session.h : Declaration of the CDirSession
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

#ifndef __SESSION_H_
#define __SESSION_H_

#include "resource.h"       // main symbols
#include "rowset.h"


class CDirTRSchemaRowset;
class CDirColSchemaRowset;
class CDirPTSchemaRowset;
/////////////////////////////////////////////////////////////////////////////
// CDirSession
class ATL_NO_VTABLE CDirSession :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IGetDataSourceImpl<CDirSession>,
	public ISessionPropertiesImpl<CDirSession>,
	public IObjectWithSiteSessionImpl<CDirSession>,
	public IDBCreateCommandImpl<CDirSession, CDirCommand>,
	public IOpenRowsetImpl<CDirSession>,
	public IDBSchemaRowsetImpl<CDirSession>
{
public:

	CDirSession()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}
	STDMETHOD(OpenRowset)(IUnknown *pUnkOuter, DBID *pTableID, DBID *pIndexID, REFIID riid,
					   ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppRowset)
	{
		CDirRowset* pRowset;
		return CreateRowset(pUnkOuter, pTableID, pIndexID, riid, cPropertySets,
							rgPropertySets, ppRowset, pRowset);
	}

BEGIN_PROPSET_MAP(CDirSession)
	CHAIN_PROPERTY_SET(CDirCommand)
END_PROPSET_MAP()

BEGIN_COM_MAP(CDirSession)
	COM_INTERFACE_ENTRY(IGetDataSource)
	COM_INTERFACE_ENTRY(IDBSchemaRowset)
	COM_INTERFACE_ENTRY(ISessionProperties)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IOpenRowset)
	COM_INTERFACE_ENTRY(IDBCreateCommand)
END_COM_MAP()

BEGIN_SCHEMA_MAP(CDirSession)
	SCHEMA_ENTRY(DBSCHEMA_TABLES, CDirTRSchemaRowset)
	SCHEMA_ENTRY(DBSCHEMA_COLUMNS, CDirColSchemaRowset)
	SCHEMA_ENTRY(DBSCHEMA_PROVIDER_TYPES, CDirPTSchemaRowset)
END_SCHEMA_MAP()
};

class CDirTRSchemaRowset :
	public CRowsetImpl< CDirTRSchemaRowset, CTABLESRow, CDirSession>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		USES_CONVERSION;
		CWindowsFile wf;
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

class CDirColSchemaRowset :
	public CRowsetImpl< CDirColSchemaRowset, CCOLUMNSRow, CDirSession>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		USES_CONVERSION;
		CWindowsFile wf;
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

class CDirPTSchemaRowset :
	public CRowsetImpl< CDirColSchemaRowset, CPROVIDER_TYPERow, CDirSession>
{
public:
	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
		return S_OK;
	}
};

#endif //__SESSION_H_
