// ComplexCtl.cpp : Implementation of CComplexCtl
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "stdafx.h"
#include "ComplexDB.h"
#include "ComplexCtl.h"

/////////////////////////////////////////////////////////////////////////////
// CComplexCtl

HRESULT CComplexCtl::OnDraw(ATL_DRAWINFO& di)
{
	return S_OK;
}

STDMETHODIMP CComplexCtl::get_DataSource(DataSource** ppDataSource)
{
	*ppDataSource = m_spDataSource;

	return S_OK;
}

STDMETHODIMP CComplexCtl::putref_DataSource(DataSource* pDataSource)
{
	m_spDataSource = pDataSource;
	UpdateControl();

	return S_OK;
}

STDMETHODIMP CComplexCtl::get_DataMember(DataMember * pVal)
{
	*pVal = m_strDataMember.Copy();

	return S_OK;
}

STDMETHODIMP CComplexCtl::put_DataMember(DataMember newVal)
{
	m_strDataMember = newVal;
	UpdateControl();

	return S_OK;
}

STDMETHODIMP CComplexCtl::get_FieldName(BSTR * pVal)
{
	*pVal = m_strFieldName.Copy();

	return S_OK;
}

STDMETHODIMP CComplexCtl::put_FieldName(BSTR newVal)
{
	m_strFieldName = newVal;

	if (newVal != NULL)
		UpdateControl();

	return S_OK;
}

HRESULT CComplexCtl::GetRowset()
{
	ATLASSERT(m_spDataSource != NULL);
	HRESULT hr;

	// Close anything we had open and unadvise if necessary
	if (m_dwCookie != 0)
		AtlUnadvise(m_spRowPosition, IID_IRowPositionChange, m_dwCookie);
	CAccessorRowset<CManualAccessor>::Close();
	m_spRowPosition.Release();

	hr = m_spDataSource->getDataMember(m_strDataMember, IID_IRowPosition,
		(IUnknown**)&m_spRowPosition);
	if (FAILED(hr))
		return hr;

	return m_spRowPosition->GetRowset(IID_IRowset, (IUnknown**)&m_spRowset);
}

HRESULT CComplexCtl::UpdateControl()
{
	USES_CONVERSION;
	CBookmark<> bookmark;
	HRESULT     hr;
	BOOL        bUserMode;
	BYTE*       pBookmarkCopy;
	ULONG       nBookmarkSize;
	ULONG       nColumn, nEntries, nLength;

	// We can't do anything if the datasource hasn't been set
	if (m_spDataSource == NULL)
		return S_OK;

	m_nColumns = 0; // Reset the column count
	// Get the rowset from the data control
	hr = GetRowset();
	if (FAILED(hr))
		return hr;

	// Get the column information so we know the column names etc.
	hr = CAccessorRowset<CManualAccessor>::GetColumnInfo(&m_nColumns, &m_pColumnInfo, &m_pStrings);

	// If the field name hasn't been set then there is no data to retrieve
	if (m_strFieldName.m_str == NULL)
		return S_OK;

	// Check if we have bookmarks we can store
	if (m_pColumnInfo->iOrdinal == 0)
	{
		m_bHaveBookmarks = true;
		FreeBookmarkMemory();
		nBookmarkSize = m_pColumnInfo->ulColumnSize;
	}
	else
		m_bHaveBookmarks = false;

	GetAmbientUserMode(bUserMode);
	if (bUserMode == FALSE)
		return S_OK;    // Don't do anything else at design mode

	// Now we can create the accessor and bind the data
	// First of all we need to find the column ordinal from the name
	for (nColumn = 0; nColumn < m_nColumns; nColumn++)
	{
		if (m_pColumnInfo[nColumn].pwszName != NULL)
		{
			nLength = ocslen(m_pColumnInfo[nColumn].pwszName) + 1;
			if (memcmp(m_pColumnInfo[nColumn].pwszName, m_strFieldName.m_str, nLength * sizeof(OLECHAR)) == 0)
				break;
		}
	}

	// If we didn't find a match then return
	if (nColumn == m_nColumns)
		return S_OK;

	if (m_bHaveBookmarks)
		nEntries = 2;
	else
		nEntries = 1;
	CreateAccessor(nEntries, &m_data, sizeof(m_data));
	if (m_bHaveBookmarks)
		AddBindEntry(0, DBTYPE_BYTES, sizeof(m_data.bookmark), &m_data.bookmark);

	AddBindEntry(nColumn, DBTYPE_BSTR, sizeof(BSTR), &m_data.bstrData);
	hr = Bind();
	if (FAILED(hr))
		return hr;

	// Loop around and store each record in our list control
	m_ctlListBox.SendMessage(LB_RESETCONTENT, 0, 0);
	hr = MoveFirst();
	while (hr == S_OK)
	{
		if (m_bHaveBookmarks)
		{
			pBookmarkCopy = new BYTE[nBookmarkSize];
			if (pBookmarkCopy != NULL)
				memcpy(pBookmarkCopy, &m_data.bookmark, nBookmarkSize);

			m_apBookmark.Add(pBookmarkCopy);
		}
		m_ctlListBox.SendMessage(LB_ADDSTRING, 0, (LPARAM)OLE2T(m_data.bstrData));

		FreeRecordMemory();
		hr = MoveNext();
	}
	// Set the cursor to the beginning
	m_ctlListBox.SendMessage(LB_SETCURSEL, 0, 0);

	// Set up the sink so we know when the rowset is repositioned
	AtlAdvise(m_spRowPosition, GetUnknown(), IID_IRowPositionChange, &m_dwCookie);

	return S_OK;
}
