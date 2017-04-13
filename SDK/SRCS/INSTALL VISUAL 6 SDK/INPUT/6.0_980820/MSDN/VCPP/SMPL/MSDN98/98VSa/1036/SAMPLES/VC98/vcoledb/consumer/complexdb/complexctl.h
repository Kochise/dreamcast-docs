// ComplexCtl.h : Declaration of the CComplexCtl
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

#ifndef __COMPLEXCTL_H_
#define __COMPLEXCTL_H_

#include "resource.h"       // main symbols

// Used to get the data when using CManualAccessor
struct mydata
{
	BYTE    bookmark[4];
	BSTR    bstrData;
};

/////////////////////////////////////////////////////////////////////////////
// CComplexCtl
class ATL_NO_VTABLE CComplexCtl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComplexCtl, &CLSID_ComplexCtl>,
	public CComControl<CComplexCtl>,
	public IDispatchImpl<IComplexCtl, &IID_IComplexCtl, &LIBID_COMPLEXDBLib>,
	public IProvideClassInfo2Impl<&CLSID_ComplexCtl, NULL, &LIBID_COMPLEXDBLib>,
	public IPersistStreamInitImpl<CComplexCtl>,
	public IPersistStorageImpl<CComplexCtl>,
	public IPersistPropertyBagImpl<CComplexCtl>,
	public IQuickActivateImpl<CComplexCtl>,
	public IOleControlImpl<CComplexCtl>,
	public IOleObjectImpl<CComplexCtl>,
	public IOleInPlaceActiveObjectImpl<CComplexCtl>,
	public IViewObjectExImpl<CComplexCtl>,
	public IOleInPlaceObjectWindowlessImpl<CComplexCtl>,
	public IDataObjectImpl<CComplexCtl>,
	public ISpecifyPropertyPagesImpl<CComplexCtl>,
	public IPerPropertyBrowsingImpl<CComplexCtl>,
	public IRowPositionChange,
	public CAccessorRowset<CManualAccessor>
{
public:
	CContainedWindow m_ctlListBox;


	CComplexCtl() :
		m_ctlListBox(_T("ListBox"), this, 1)
	{

		m_bWindowOnly    = TRUE;
		m_dwCookie       = 0;
		m_bHaveBookmarks = false;
		m_pColumnInfo    = NULL;
		m_pStrings       = NULL;
		m_nColumns       = 0;
	}
	~CComplexCtl()
	{
		CoTaskMemFree(m_pColumnInfo);
		CoTaskMemFree(m_pStrings);
		FreeBookmarkMemory();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPLEXCTL)

BEGIN_COM_MAP(CComplexCtl)
	COM_INTERFACE_ENTRY(IComplexCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(IRowPositionChange)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CComplexCtl)
	// Example entries
	PROP_ENTRY("DataMember", 2, CLSID_NULL)
	PROP_ENTRY("FieldName", 3, CLSID_NULL)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CComplexCtl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
ALT_MSG_MAP(1)
	// Replace this with message map entries for subclassed ListBox
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		m_ctlListBox.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VSCROLL);
		return 0;
	}
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CComplexCtl>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlListBox.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IRowPositionChange
	STDMETHOD(OnRowPositionChange)(DBREASON eReason, DBEVENTPHASE ePhase, BOOL bCantDeny)
	{
		if (ePhase == DBEVENTPHASE_DIDEVENT)
		{
			DBPOSITIONFLAGS dwPositionFlags;
			HRESULT hr;
			HCHAPTER hChapter = DB_NULL_HCHAPTER;

			hr = m_spRowPosition->GetRowPosition(&hChapter, &m_hRow, &dwPositionFlags);
			if (FAILED(hr) || m_hRow == DB_NULL_HROW)
				return S_OK;

			hr = CRowset::GetData();
			if (FAILED(hr))
				return S_OK;

			// Now we need to find a match based upon the bookmark;
			int i, nRows = m_apBookmark.GetSize();
			for (i = 0; i < nRows; i++)
			{
				if (memcmp(m_apBookmark[i], &m_data.bookmark, m_pColumnInfo->ulColumnSize) == 0)
				{
					m_ctlListBox.SendMessage(LB_SETCURSEL, i, 0);
					break;
				}
			}
			FreeRecordMemory();
			ReleaseRows();
		}
		return S_OK;
	}

// IPerPropertyBrowsing
	STDMETHOD(GetPredefinedStrings)(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
	{
		ATLTRACE("CComplexCtl::GetPredefinedStrings\n");
		if (pCaStringsOut == NULL || pCaCookiesOut == NULL)
			return E_POINTER;

		// Only have our custom processing if it is the FieldName property and we
		// have retrieved some columns
		if (dispID != 3 || m_nColumns == 0)
			return IPerPropertyBrowsingImpl<CComplexCtl>::GetPredefinedStrings(dispID, pCaStringsOut, pCaCookiesOut);

		LPOLESTR*   ppStr;
		LPOLESTR    pName;
		ULONG       nLength;
		DWORD*      pCookie;
		ULONG       nColumns = m_nColumns;
		ULONG       nStart;

		// We don't bind to the bookmark column
		if (m_bHaveBookmarks)
		{
			nStart = 1;
			nColumns--;
		}
		else
			nStart = 0;

		pCaStringsOut->cElems = nColumns;
		pCaCookiesOut->cElems = nColumns;

		pCaStringsOut->pElems = (LPOLESTR*)CoTaskMemAlloc(sizeof(LPOLESTR) * nColumns);
		if (pCaStringsOut->pElems == NULL)
			return E_OUTOFMEMORY;

		pCaCookiesOut->pElems = (DWORD*)CoTaskMemAlloc(sizeof(DWORD) * nColumns);
		if (pCaCookiesOut->pElems == NULL)
		{
			CoTaskMemFree(pCaStringsOut->pElems);
			return E_OUTOFMEMORY;
		}

		ppStr = pCaStringsOut->pElems;
		pCookie = pCaCookiesOut->pElems;
		for (ULONG i = nStart; i < m_nColumns; i++)
		{
			pName = m_pColumnInfo[i].pwszName;
			nLength = ocslen(pName) + 1;    // Remember the NULL

			*ppStr = (LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR) * nLength);
			if (*ppStr != NULL)
				memcpy(*ppStr, pName, sizeof(OLECHAR) * nLength);

			*pCookie = i;

			ppStr++;
			pCookie++;
		}
		return S_OK;
	}
	STDMETHOD(GetPredefinedValue)(DISPID dispID, DWORD dwCookie, VARIANT* pVarOut)
	{
		if (pVarOut == NULL)
			return E_POINTER;

		LPOLESTR pName = m_pColumnInfo[dwCookie].pwszName;

		if (dispID == 3 && pName != NULL)
		{
			pVarOut->vt = VT_BSTR;
			pVarOut->bstrVal = ::SysAllocString(pName);
		}
		else
			pVarOut->vt = VT_EMPTY;

		return S_OK;
	}

// IOleObject::Close
	STDMETHOD(Close)(DWORD dwSaveOption)
	{
		// Unhook everything before we go away
		if (m_dwCookie != 0)
			AtlUnadvise(m_spRowPosition, IID_IRowPositionChange, m_dwCookie);

		m_spDataSource.Release();
		m_spRowPosition.Release();

		return IOleObjectImpl<CComplexCtl>::Close(dwSaveOption);
	}

	void FreeBookmarkMemory()
	{
		int i, nSize = m_apBookmark.GetSize();
		for (i=0; i<nSize; i++)
		{
			delete [] m_apBookmark[i];
		}
		m_apBookmark.RemoveAll();
	}

// IComplexCtl
public:
	HRESULT UpdateControl();
	STDMETHOD(get_FieldName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FieldName)(/*[in]*/ BSTR newVal);
	HRESULT GetRowset();
	STDMETHOD(get_DataMember)(/*[out, retval]*/ DataMember *pVal);
	STDMETHOD(put_DataMember)(/*[in]*/ DataMember newVal);
	STDMETHOD(get_DataSource)(/*[out, retval]*/ DataSource **pDataSource);
	STDMETHOD(putref_DataSource)(/*[in]*/ DataSource* pDataSource);
	HRESULT OnDraw(ATL_DRAWINFO& di);

	CSimpleArray<BYTE*>     m_apBookmark;
	CComPtr<IDataSource>    m_spDataSource;
	CComPtr<IRowPosition>   m_spRowPosition;
	CComBSTR                m_strDataMember;
	CComBSTR                m_strFieldName;
	DWORD                   m_dwCookie;
	bool                    m_bHaveBookmarks;
	ULONG                   m_nColumns;
	DBCOLUMNINFO*           m_pColumnInfo;
	LPOLESTR                m_pStrings;
	mydata                  m_data;
};

#endif //__COMPLEXCTL_H_
