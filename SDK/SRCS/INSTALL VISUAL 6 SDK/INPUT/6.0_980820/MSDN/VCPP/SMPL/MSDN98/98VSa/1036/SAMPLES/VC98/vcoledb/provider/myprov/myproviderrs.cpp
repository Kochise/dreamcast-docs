// Implementation of the CMyProviderRowset
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

#include "stdafx.h"
#include "MyProviderRS.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCommand::Execute
HRESULT WINAPI CMyProviderCommand::Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
										   LONG * pcRowsAffected, IUnknown ** ppRowset)
{
	CAgentRowset* pAgentRS;
	return CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pAgentRS);
}


template <class TInterface>
ATLCOLUMNINFO* CommonGetColInfo(IUnknown* pPropsUnk, ULONG* pcCols)
{
	static ATLCOLUMNINFO _rgColumns[5];
	ULONG ulCols = 0;

	CComQIPtr<TInterface> spProps = pPropsUnk;

	CDBPropIDSet set(DBPROPSET_ROWSET);
	set.AddPropertyID(DBPROP_BOOKMARKS);
	DBPROPSET* pPropSet = NULL;
	ULONG ulPropSet = 0;
	HRESULT hr;

	if (spProps)
		hr = spProps->GetProperties(1, &set, &ulPropSet, &pPropSet);

	// Check the property flag for bookmarks, if it is set, set the zero ordinal
	// entry in the column map with the bookmark information.

	if (pPropSet)
	{
		CComVariant var = pPropSet->rgProperties[0].vValue;
		CoTaskMemFree(pPropSet->rgProperties);
		CoTaskMemFree(pPropSet);

		if ((SUCCEEDED(hr) && (var.boolVal == VARIANT_TRUE)))
		{
			ADD_COLUMN_ENTRY_EX(ulCols, OLESTR("Bookmark"), 0, sizeof(DWORD), DBTYPE_BYTES,
				0, 0, GUID_NULL, CAgentMan, dwBookmark, DBCOLUMNFLAGS_ISBOOKMARK)
			ulCols++;
		}

	}


	// Next set the other columns up.
	ADD_COLUMN_ENTRY(ulCols, OLESTR("Command"), 1, 256, DBTYPE_STR, 0xFF, 0xFF,
		GUID_NULL, CAgentMan, szCommand)
	ulCols++;
	ADD_COLUMN_ENTRY(ulCols, OLESTR("Text"), 2, 256, DBTYPE_STR, 0xFF, 0xFF,
		GUID_NULL, CAgentMan, szText)
	ulCols++;

	ADD_COLUMN_ENTRY(ulCols, OLESTR("Command2"), 3, 256, DBTYPE_STR, 0xFF, 0xFF,
		GUID_NULL, CAgentMan, szCommand2)
	ulCols++;
	ADD_COLUMN_ENTRY(ulCols, OLESTR("Text2"), 4, 256, DBTYPE_STR, 0xFF, 0xFF,
		GUID_NULL, CAgentMan, szText2)
	ulCols++;


	if (pcCols != NULL)
		*pcCols = ulCols;

	return _rgColumns;
}



ATLCOLUMNINFO* CAgentMan::GetColumnInfo(CMyProviderCommand* pThis, ULONG* pcCols)
{
	return CommonGetColInfo<ICommandProperties>(pThis->GetUnknown(), pcCols);
}


ATLCOLUMNINFO* CAgentMan::GetColumnInfo(CAgentRowset* pThis, ULONG* pcCols)
{

	return CommonGetColInfo<IRowsetInfo>(pThis->GetUnknown(), pcCols);

}
