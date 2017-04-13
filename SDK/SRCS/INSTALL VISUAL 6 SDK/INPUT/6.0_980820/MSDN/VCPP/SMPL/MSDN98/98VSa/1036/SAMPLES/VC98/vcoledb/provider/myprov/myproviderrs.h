// MyProviderRS.h : Declaration of the CMyProviderRowset
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

#ifndef __CMyProviderRowset_H_
#define __CMyProviderRowset_H_

#include <stdio.h>
#include <tchar.h>
#include "rowloc.h"
#include "resource.h"       // main symbols

class CAgentRowset;
class CMyProviderCommand;

class CAgentMan
{
public:
	DWORD dwBookmark;
	TCHAR szCommand[256];
	TCHAR szText[256];
	TCHAR szCommand2[256];
	TCHAR szText2[256];

	static ATLCOLUMNINFO* GetColumnInfo(CAgentRowset* pThis, ULONG* pcCols);
	static ATLCOLUMNINFO* GetColumnInfo(CMyProviderCommand* pThis, ULONG* pcCols);

};

#define ADD_COLUMN_ENTRY(ulCols, name, ordinal, colSize, type, precision, scale, guid, dataClass, member) \
	_rgColumns[ulCols].pwszName = (LPOLESTR)name; \
	_rgColumns[ulCols].pTypeInfo = (ITypeInfo*)NULL; \
	_rgColumns[ulCols].iOrdinal = (ULONG)ordinal; \
	_rgColumns[ulCols].dwFlags = 0; \
	_rgColumns[ulCols].ulColumnSize = (ULONG)colSize; \
	_rgColumns[ulCols].wType = (DBTYPE)type; \
	_rgColumns[ulCols].bPrecision = (BYTE)precision; \
	_rgColumns[ulCols].bScale = (BYTE)scale; \
	_rgColumns[ulCols].cbOffset = offsetof(dataClass, member); \
	memset(&(_rgColumns[ulCols].columnid), 0, sizeof(DBID)); \
	_rgColumns[ulCols].columnid.uName.pwszName = (LPOLESTR)name;



#define ADD_COLUMN_ENTRY_EX(ulCols, name, ordinal, colSize, type, precision, scale, guid, dataClass, member, flags) \
	_rgColumns[ulCols].pwszName = (LPOLESTR)name; \
	_rgColumns[ulCols].pTypeInfo = (ITypeInfo*)NULL; \
	_rgColumns[ulCols].iOrdinal = (ULONG)ordinal; \
	_rgColumns[ulCols].dwFlags = flags; \
	_rgColumns[ulCols].ulColumnSize = (ULONG)colSize; \
	_rgColumns[ulCols].wType = (DBTYPE)type; \
	_rgColumns[ulCols].bPrecision = (BYTE)precision; \
	_rgColumns[ulCols].bScale = (BYTE)scale; \
	_rgColumns[ulCols].cbOffset = offsetof(dataClass, member); \
	memset(&(_rgColumns[ulCols].columnid), 0, sizeof(DBID)); \
	_rgColumns[ulCols].columnid.uName.pwszName = (LPOLESTR)name;



// CMyProviderCommand
class ATL_NO_VTABLE CMyProviderCommand :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IAccessorImpl<CMyProviderCommand>,
	public ICommandTextImpl<CMyProviderCommand>,
	public ICommandPropertiesImpl<CMyProviderCommand>,
	public IObjectWithSiteImpl<CMyProviderCommand>,
	public IConvertTypeImpl<CMyProviderCommand>,
	public IColumnsInfoImpl<CMyProviderCommand>

{
public:
BEGIN_COM_MAP(CMyProviderCommand)
	COM_INTERFACE_ENTRY(ICommand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IAccessor)
	COM_INTERFACE_ENTRY(ICommandProperties)
	COM_INTERFACE_ENTRY(IConvertType)
	COM_INTERFACE_ENTRY(IColumnsInfo)
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
		hr = IAccessorImpl<CMyProviderCommand>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CUtlProps<CMyProviderCommand>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<CMyProviderCommand>::FinalRelease();
	}
	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
						  LONG * pcRowsAffected, IUnknown ** ppRowset);

	static ATLCOLUMNINFO* GetColumnInfo(CMyProviderCommand* pv, ULONG* pcInfo)
	{
		return CAgentMan::GetColumnInfo(pv, pcInfo);
	}

BEGIN_PROPSET_MAP(CMyProviderCommand)
	BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
		PROPERTY_INFO_ENTRY_EX(IAccessor,VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IColumnsInfo, VT_BOOL,   DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IConvertType, VT_BOOL,   DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IRowset, VT_BOOL,    DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IRowsetIdentity,VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IRowsetInfo, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(IRowsetLocate,   VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(BOOKMARKS,       VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE , VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(BOOKMARKSKIPPED,VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, 0, 0)
		PROPERTY_INFO_ENTRY_EX(BOOKMARKTYPE,    VT_I4, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, 0, 0)
		PROPERTY_INFO_ENTRY_EX(CANFETCHBACKWARDS,VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, 0, 0)
		PROPERTY_INFO_ENTRY_EX(CANHOLDROWS, VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(CANSCROLLBACKWARDS, VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(LITERALBOOKMARKS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
		PROPERTY_INFO_ENTRY_EX(ORDEREDBOOKMARKS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
	END_PROPERTY_SET(DBPROPSET_ROWSET)
END_PROPSET_MAP()
};

template <class T, class Storage, class CreatorClass, class ArrayType = CSimpleArray<Storage> >
class CMyRowsetImpl:
	public CRowsetImpl<T, Storage, CreatorClass, ArrayType, CSimpleRow, IRowsetLocateImpl< T > >
{

BEGIN_COM_MAP(CMyRowsetImpl)
	COM_INTERFACE_ENTRY(IRowsetLocate)
	COM_INTERFACE_ENTRY_CHAIN(_RowsetBaseClass)
END_COM_MAP()

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

};


class CAgentRowset : public CMyRowsetImpl<CAgentRowset, CAgentMan, CMyProviderCommand>
{
public:

	virtual DBSTATUS GetDBStatus(CSimpleRow* , HACCESSOR)
	{
		return DBSTATUS_S_ISNULL;
	}

	HRESULT Execute(DBPARAMS * pParams, LONG* pcRowsAffected)
	{
		USES_CONVERSION;
		FILE* pFile;
		TCHAR szString[256];
		TCHAR szFile[MAX_PATH];
		size_t nLength;
		ObjectLock lock(this);


		// From a filename, passed in as a command text, scan the file placing data
		// in the data array.
		if (m_strCommandText == (BSTR)NULL)
		{
			ATLTRACE("No filename specified");
			return E_FAIL;
		}

		// Open the file
		_tcscpy(szFile, OLE2T(m_strCommandText));
		if (szFile[0] == _T('\0') || ((pFile = fopen(&szFile[0], "r")) == NULL))
		{
			ATLTRACE("Could not open file");
			return DB_E_NOTABLE;
		}

		// scan and parse the file.  The file should contain two strings per record
		LONG cFiles = 0;
		while (fgets(szString, 256, pFile) != NULL)
		{
			nLength = strlen(szString);
			szString[nLength-1] = '\0'; // Strip off trailing CR/LF
			CAgentMan am;
			_tcscpy(am.szCommand, szString);
			_tcscpy(am.szCommand2, szString);

			if (fgets(szString, 256, pFile) != NULL)
			{
				nLength = strlen(szString);
				szString[nLength-1] = '\0'; // Strip off trailing CR/LF
				_tcscpy(am.szText, szString);
				_tcscpy(am.szText2, szString);
			}

			am.dwBookmark = ++cFiles;
			if (!m_rgRowData.Add(am))
			{
				ATLTRACE("Couldn't add data to array");
				fclose(pFile);
				return E_FAIL;
			}
		}

		if (pcRowsAffected != NULL)
			*pcRowsAffected = cFiles;
		return S_OK;
	}

	HRESULT OnPropertyChanged(ULONG iCurSet, DBPROP* pDBProp)
	{
		ATLASSERT(pDBProp != NULL);

		DWORD dwPropertyID = pDBProp->dwPropertyID;

		if (dwPropertyID == DBPROP_IRowsetLocate ||
			dwPropertyID == DBPROP_LITERALBOOKMARKS ||
			dwPropertyID == DBPROP_ORDEREDBOOKMARKS)
		{
			CComVariant var = pDBProp->vValue;

			if (var.boolVal == VARIANT_TRUE)
			{
				// Set the bookmarks property as these are chained
				CComVariant bookVar(true);
				CDBPropSet set(DBPROPSET_ROWSET);
				set.AddProperty(DBPROP_BOOKMARKS, bookVar);

				// If you set IRowsetLocate to true, then the rowset can
				// handle backward scrolling
				if (dwPropertyID == DBPROP_IRowsetLocate)
					set.AddProperty(DBPROP_CANSCROLLBACKWARDS, bookVar);

				const GUID* ppGuid[1];
				ppGuid[0] = &DBPROPSET_ROWSET;

				return SetProperties(0, 1, &set, 1, ppGuid);
			}
		}

		return S_OK;
	}
};



#endif //__CMyProviderRowset_H_
