///////////////////////////////////////////////////////////////////////////
// ROWLOC.H -- Declarations and implementations for IRowsetLocateImpl
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


///////////////////////////////////////////////////////////////////////////
// class IRowsetLocateImpl

template <class T>
class ATL_NO_VTABLE IRowsetLocateImpl : public IRowsetImpl<T, IRowsetLocate>
{
public:
	STDMETHOD (Compare)(HCHAPTER hReserved, ULONG cbBookmark1,
		const BYTE * pBookmark1, ULONG cbBookmark2, const BYTE * pBookmark2,
		DBCOMPARE * pComparison)
	{
		ATLTRACE("IRowsetLocateImpl::Compare");

		HRESULT hr = ValidateBookmark(cbBookmark1, pBookmark1);
		if (hr != S_OK)
			return hr;

		hr = ValidateBookmark(cbBookmark2, pBookmark2);
		if (hr != S_OK)
			return hr;

		// Return the value based on the bookmark values
		if (*pBookmark1 == *pBookmark2)
			*pComparison = DBCOMPARE_EQ;

		if (*pBookmark1 < *pBookmark2)
			*pComparison = DBCOMPARE_LT;

		if (*pBookmark1 > *pBookmark2)
			*pComparison = DBCOMPARE_GT;

		return S_OK;
	}

	STDMETHOD (GetRowsAt)(HWATCHREGION hReserved1, HCHAPTER hReserved2,
		ULONG cbBookmark, const BYTE * pBookmark, LONG lRowsOffset,
		LONG cRows, ULONG * pcRowsObtained, HROW ** prghRows)
	{
		ATLTRACE("IRowsetLocateImpl::GetRowsAt");
		T* pT = (T*)this;

		// Check bookmark
		HRESULT hr = ValidateBookmark(cbBookmark, pBookmark);
		if (hr != S_OK)
			return hr;

		// Check the other pointers
		if (pcRowsObtained == NULL || prghRows == NULL)
			return E_INVALIDARG;

		// Set the current row position to the bookmark.  Handle any
		// normal values
		pT->Lock();

		// We need to handle the offset as the start position is defined
		// as the bookmark + offset.  If the offset is negative, and we
		// do not have m_bCanScrollBack then return an error.  The
		// GetNextRows function handles the case where cRows is negative
		// and we don't have m_bCanFetchBack set.
		if (lRowsOffset < 0 && !pT->m_bCanScrollBack)
			return DB_E_CANTSCROLLBACKWARDS;

		LONG iRowsetTemp = pT->m_iRowset;  // Cache the current rowset
		pT->m_iRowset = *pBookmark;
		if ((cbBookmark == 1) && (*pBookmark == DBBMK_FIRST))
			pT->m_iRowset = 1;

		if ((cbBookmark == 1) && (*pBookmark == DBBMK_LAST))
			pT->m_iRowset = pT->m_rgRowData.GetSize() + 1;

		// Set the start position to m_iRowset + lRowsOffset
		pT->m_iRowset += lRowsOffset;
		if (lRowsOffset >= 0)
			(cRows >= 0) ? pT->m_iRowset -= 1 : pT->m_iRowset +=0;
		else
			(cRows >= 0) ? pT->m_iRowset -= 1 : pT->m_iRowset +=0;
//      (lRowsOffset >= 0) ? m_iRowset -= 1 : m_iRowset += 1;
		if (pT->m_iRowset < 0 || pT->m_iRowset > (DWORD)pT->m_rgRowData.GetSize())
		{
			pT->m_iRowset = iRowsetTemp;
			return DB_E_BADSTARTPOSITION;
		}

		// Call IRowsetImpl::GetNextRows to actually get the rows.
		hr = pT->GetNextRows(hReserved2, 0, cRows, pcRowsObtained, prghRows);
		pT->m_iRowset = iRowsetTemp;
		pT->Unlock();
		return hr;
	}

	STDMETHOD (GetRowsByBookmark)(HCHAPTER hReserved, ULONG cRows,
		const ULONG rgcbBookmarks[], const BYTE * rgpBookmarks[],
		HROW rghRows[], DBROWSTATUS rgRowStatus[])
	{
		HRESULT hr = S_OK;
		ATLTRACE("IRowsetLocateImpl::GetRowsByBookmark");

		T* pT = (T*)this;
		if (rgcbBookmarks == NULL || rgpBookmarks == NULL || rghRows == NULL)
			return E_INVALIDARG;

		if (cRows == 0)
			return S_OK;    // No rows fetched in this case.

		bool bErrors = false;
		pT->Lock();
		for (ULONG l=0; l<cRows; l++)
		{
			// Validate each bookmark before fetching the row.  Note, it is
			// an error for the bookmark to be one of the standard values
			hr = ValidateBookmark(rgcbBookmarks[l], rgpBookmarks[l]);
			if (hr != S_OK)
			{
				bErrors = TRUE;
				if (rgRowStatus != NULL)
				{
					rgRowStatus[l] = DBROWSTATUS_E_INVALID;
					continue;
				}
			}

			// Fetch the row, we now that it is a valid row after validation.
			ULONG ulRowsObtained = 0;
			if (pT->CreateRow((long)*rgpBookmarks[l], ulRowsObtained, &rghRows[l]) != S_OK)
			{
				bErrors = TRUE;
			}
			else
			{
				if (rgRowStatus != NULL)
					rgRowStatus[l] = DBROWSTATUS_S_OK;
			}
		}

		pT->Unlock();
		if (bErrors)
			return DB_S_ERRORSOCCURRED;
		else
			return hr;
	}

	STDMETHOD (Hash)(HCHAPTER hReserved, ULONG cBookmarks,
		const ULONG rgcbBookmarks[], const BYTE * rgpBookmarks[],
		DWORD rgHashedValues[], DBROWSTATUS rgBookmarkStatus[])
	{
		ATLTRACENOTIMPL("IRowsetLocateImpl::GetRowsByBookmark");
	}

	// Implementation
	protected:
	HRESULT ValidateBookmark(ULONG cbBookmark, const BYTE* pBookmark)
	{
		T* pT = (T*)this;
		if (cbBookmark == 0 || pBookmark == NULL)
			return E_INVALIDARG;

		// All of our bookmarks are DWORDs, if they are anything other than
		// sizeof(DWORD) then we have an invalid bookmark
		if ((cbBookmark != sizeof(DWORD)) && (cbBookmark != 1))
		{
			ATLTRACE("Bookmarks are invalid length, should be DWORDs");
			return DB_E_BADBOOKMARK;
		}

		// If the contents of our bookmarks are less than 0 or greater than
		// rowcount, then they are invalid
		UINT nRows = pT->m_rgRowData.GetSize();
		if ((*pBookmark <= 0 || *pBookmark > nRows)
			&& *pBookmark != DBBMK_FIRST && *pBookmark != DBBMK_LAST)
		{
			ATLTRACE("Bookmark has invalid range");
			return DB_E_BADBOOKMARK;
		}

		return S_OK;
	}
};
