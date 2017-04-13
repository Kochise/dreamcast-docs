// Rowset.cpp : Implementation of CRowset
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
#include "provider.h"
#include "Rowset.h"

/////////////////////////////////////////////////////////////////////////////
// CRowset

HRESULT WINAPI CDirCommand::Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams,
								 LONG * pcRowsAffected, IUnknown ** ppRowset)
{
	USES_CONVERSION;
	ATLTRACE("IN Execute\n");
	LPTSTR szCommand = OLE2T(m_strCommandText);
	CDirRowset* pDirRowset;
	CRegRowset* pRegRowset;

	if (szCommand != NULL)
	{
		const int cbRegHeader = 5;
		TCHAR szRegHeader[cbRegHeader];
		lstrcpyn(szRegHeader, szCommand, cbRegHeader);

		if (lstrcmpi(szRegHeader, _T("REG:")) == 0)
			return CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pRegRowset);
	}
	return CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pDirRowset);
}
