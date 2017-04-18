// MFCRowSet.h : interface of the CMFCRowSet class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_MFCROWSET_H__2B60A706_22FC_11D1_8FD3_000000000000__INCLUDED_)
#define AFX_MFCROWSET_H__2B60A706_22FC_11D1_8FD3_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CProduct
{
public:
	long    m_nProductID;
	TCHAR   m_szName[41];

DEFINE_COMMAND(CProduct, _T("SELECT ProductID, ProductName FROM Products"))

BEGIN_ACCESSOR_MAP(CProduct, 2)
	BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_nProductID)
	END_ACCESSOR()
	BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_szName)
	END_ACCESSOR()
END_ACCESSOR_MAP()
};

class CMFCRowSet : public CCommand<CAccessor<CProduct> >
{
public:
	//CMFCRowSet();
	DECLARE_DYNAMIC(CMFCRowSet)

	HRESULT Open()
	{
		CDataSource db;
		CSession    session;
		HRESULT     hr;

		hr = db.Open(_T("MSDASQL"), _T("OLE_DB_NWind_Jet"), _T("Admin"), _T(""));
		if (FAILED(hr))
			return hr;

		hr = session.Open(db);
		if (FAILED(hr))
			return hr;

		CDBPropSet  propset(DBPROPSET_ROWSET);
		propset.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		propset.AddProperty(DBPROP_IRowsetScroll, true);
		propset.AddProperty(DBPROP_IRowsetChange, true);
		propset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

		hr = CCommand<CAccessor<CProduct> >::Open(session, NULL, &propset);
		if (FAILED(hr))
			return hr;

		return MoveNext();
	}

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCROWSET_H__2B60A706_22FC_11D1_8FD3_000000000000__INCLUDED_)
