// StockTickerATL_.h : Declaration of the CStockTickerATL
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

#ifndef __STOCKTICKERATL_H_
#define __STOCKTICKERATL_H_

#include "resource.h"       // main symbols
#include "cpstockquotes.h"
#include "renderstocks.h"
#include "stocksymbols.h"

/////////////////////////////////////////////////////////////////////////////
// CStockTickerATL
//
// Main control class.
//
class ATL_NO_VTABLE CStockTickerATL :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStockTickerATL, &CLSID_StockTickerATL>,
	public CComControl<CStockTickerATL>,
	public CStockPropImpl<CStockTickerATL, IStockTickerATL, &IID_IStockTickerATL, &LIBID_STOCKTICKERATLLib>,
	public IProvideClassInfo2Impl<&CLSID_StockTickerATL, NULL, &LIBID_STOCKTICKERATLLib>,
	public IPersistStreamInitImpl<CStockTickerATL>,
	public IPersistStorageImpl<CStockTickerATL>,
	public IPersistPropertyBagImpl<CStockTickerATL>,
	public IQuickActivateImpl<CStockTickerATL>,
	public IOleControlImpl<CStockTickerATL>,
	public IOleObjectImpl<CStockTickerATL>,
	public IOleInPlaceActiveObjectImpl<CStockTickerATL>,
	public IViewObjectExImpl<CStockTickerATL>,
	public IOleInPlaceObjectWindowlessImpl<CStockTickerATL>,
	public IDataObjectImpl<CStockTickerATL>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStockTickerATL>,
	public IPropertyNotifySinkCP<CStockTickerATL, CComDynamicUnkArray >,
	public ISpecifyPropertyPagesImpl<CStockTickerATL>,
	public IStockEvents
{
public:
	CStockTickerATL();
	~CStockTickerATL();

	HRESULT FinalConstruct();
	void FinalRelease();

	COLORREF GetBackColor()
	{
		COLORREF    c;
		HPALETTE    p;
		GetAmbientPalette(p);
		OleTranslateColor(m_clrBackColor, p, &c);
		return c;
	}

	COLORREF GetForeColor()
	{
		COLORREF    c;
		HPALETTE    p;
		GetAmbientPalette(p);
		OleTranslateColor(m_clrForeColor, p, &c);
		return c;
	}

	void    TimerTick();

DECLARE_REGISTRY_RESOURCEID(IDR_STOCKTICKERATL)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStockTickerATL)
	COM_INTERFACE_ENTRY(IStockTickerATL)
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
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IStockEvents)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CStockTickerATL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_ENTRY("Fore Color", DISPID_FORECOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Back Color", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("Update Interval", 1, CLSID_StockTickerProp)
	PROP_ENTRY("Ticker Speed", 2, CLSID_StockTickerProp)
END_PROPERTY_MAP()


BEGIN_CONNECTION_POINT_MAP(CStockTickerATL)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()


BEGIN_MSG_MAP(CStockTickerATL)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)
	MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
	MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
	COMMAND_ID_HANDLER(ID_PROPERTIES, OnProperties)
	COMMAND_ID_HANDLER(ID_STOCKS, OnStocks)
	COMMAND_ID_HANDLER(ID_UPDATENOW, OnUpdateNow)
END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IStockEvents
//
	STDMETHOD_(void, InfoUpdate)()
	{
		m_bNeedToUpdate = true;
	}

// override CComControl methods.
//
	HRESULT IOleInPlaceObject_SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
	{
		m_bCtrlResized = true;
		return CComControl<CStockTickerATL>::IOleInPlaceObject_SetObjectRects(prcPos, prcClip);
	}

	HRESULT IOleObject_SetClientSite(IOleClientSite *pClientSite);
	HRESULT IOleObject_Close(DWORD dwSaveOption);

// Load and save control data.  Also save stock quote component's data.
//
	HRESULT IPersistStreamInit_Load(LPSTREAM pStm, ATL_PROPMAP_ENTRY* pMap);
	HRESULT IPersistStreamInit_Save(LPSTREAM pStm, BOOL fClearDirty,
									ATL_PROPMAP_ENTRY* pMap);

// propertiy change notification.
//
	HRESULT FireOnChanged(DISPID dispID)
	{
		if (dispID == DISPID_FONT)
			m_renderStocks.FontChanged(m_pFont);
		else if (dispID == DISPID_FORECOLOR || dispID == DISPID_BACKCOLOR)
			m_renderStocks.ColorsChanged(GetForeColor(), GetBackColor());

		return CComControl<CStockTickerATL>::FireOnChanged(dispID);
	}

protected:
	UINT                    m_nTimerID;     // timer id.
	CProxyIStockQuotes      m_pStockQuotes; // stock quotes component.
	DWORD                   m_dwCookie;     // connection point cookie.
	bool                    m_bNeedToUpdate;    // need to get data?
	CRenderStocks           m_renderStocks; // rendering object.
	bool                    m_bNeedToInitRenderer;  // need to init renderer?
	bool                    m_bCtrlResized; // control has resized?
	short                   m_updateInterval; // data update interval.
	short                   m_tickerSpeed;  // stock ticker speed.

	void        CreateComponetFailed();
	void        CreateTimer();
	void        DestroyTimer();
	void        ShutDown();

// message handlers
//
	// to eliminate flicker don't let Windows erase the background (since the
	// control handles this).
	//
	LRESULT     OnErasebkgnd(UINT /* nMsg */, WPARAM /* wParam */,
							 LPARAM /* lParam */, BOOL& lResult)
	{
		return 0;
	}

	LRESULT     OnRButtonUp(UINT /* nMsg */, WPARAM /* wParam */,
							LPARAM /* lParam */, BOOL& /* lResult */);

	LRESULT     OnInitMenuPopup(UINT /* nMsg */, WPARAM wParam,
								LPARAM lParam, BOOL& lResult);


	LRESULT     OnProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT     OnStocks(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT     OnUpdateNow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IStockTickerATL
public:
	STDMETHOD(get_StockSourceISAPIDllURL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_StockSourceISAPIDllURL)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_MSInvestorURL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MSInvestorURL)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_TickerSpeed)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_TickerSpeed)(/*[in]*/ short newVal);
	STDMETHOD(get_UpdateInterval)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_UpdateInterval)(/*[in]*/ short newVal);

	HRESULT     OnDraw(ATL_DRAWINFO& di);

	bool        IsUpdating()
	{
		BOOL b;
		if (!m_pStockQuotes)
			b = FALSE;
		else
			m_pStockQuotes->IsUpdating(&b);
		return b != FALSE;
	}

// properties
//
	CComPtr<IFontDisp>  m_pFont;
	OLE_COLOR           m_clrBackColor;
	OLE_COLOR           m_clrForeColor;
};

#endif //__STOCKTICKERATL_H_
