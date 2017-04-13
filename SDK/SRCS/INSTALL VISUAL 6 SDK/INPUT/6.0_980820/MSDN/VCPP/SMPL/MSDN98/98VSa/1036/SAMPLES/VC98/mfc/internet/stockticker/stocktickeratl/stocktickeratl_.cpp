// StockTickerATL_.cpp : Implementation of CStockTickerATL
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
#include "stdafx.h"
#include "stocktickerATL.h"
#include "StockTickerATL_.h"
#include "stocksdialog.h"
#include "windowlessoptions.h"

CStockTickerATL* g_pStockTickerATL = 0; // pointer to control so CanUnloadDLLNow()
										// can call to see if we are updating.
										// also used by timer proc.

// Timer Proc.
// global timer proc is used so this control can activate both windowed and windowless.
//
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (g_pStockTickerATL)
		g_pStockTickerATL->TimerTick();
}

/////////////////////////////////////////////////////////////////////////////
// CStockTickerATL

CStockTickerATL::CStockTickerATL()
: m_dwCookie(0), m_bNeedToUpdate(false), m_bNeedToInitRenderer(true),
  m_bCtrlResized(true), m_nTimerID(0), m_tickerSpeed(50), m_updateInterval(15)
{
	m_clrBackColor = -1;    // this will cause control to get the ambient colors.
	m_clrForeColor = -1;
	g_pStockTickerATL = this;
}

CStockTickerATL::~CStockTickerATL()
{
	g_pStockTickerATL = 0;
}


STDMETHODIMP CStockTickerATL::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IStockTickerATL,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStockTickerATL::FinalConstruct()
{
	// uncomment the following to force the control to activated windowed.
//  m_bWindowOnly = TRUE;

	// create stock quotes component.
	//
	if (SUCCEEDED(m_pStockQuotes.Create()))
		return S_OK;
	CreateComponetFailed();
	return S_FALSE;
}

void CStockTickerATL::FinalRelease()
{
}

// Draw stock info.
//
HRESULT CStockTickerATL::OnDraw(ATL_DRAWINFO& di)
{
	CRect   rcBounds(di.prcBounds->left,
					 di.prcBounds->top,
					 di.prcBounds->right,
					 di.prcBounds->bottom);
	CDC     dc;
	dc.Attach(di.hdcDraw);
	if (m_bNeedToInitRenderer)      // first time.
	{
		m_renderStocks.Init(&dc, rcBounds);
		m_renderStocks.ColorsChanged(GetForeColor(), GetBackColor());
		m_renderStocks.FontChanged(m_pFont);
		m_bNeedToInitRenderer = false;
	}
	if (m_bCtrlResized)     // if control has changed size...
	{
		m_renderStocks.CtrlResized(&dc, rcBounds);
		m_bCtrlResized = false;
	}
	m_renderStocks.RenderNext();        // move stocks to the left.
	m_renderStocks.DrawOnto(&dc, rcBounds);
	dc.Detach();
	return S_OK;
}


// Initialize control when pClientSite != 0 and do cleanup when pClientSite == 0.
//
HRESULT CStockTickerATL::IOleObject_SetClientSite(IOleClientSite* pClientSite)
{
	HRESULT hr = CComControl<CStockTickerATL>::IOleObject_SetClientSite(pClientSite);

	if (m_pStockQuotes == NULL)
		return hr;

	bool    ok = SUCCEEDED(hr);

	// Setup connection point to stock quotes component. Start timer.
	//
	if (ok && pClientSite && !m_dwCookie)
	{
		AtlAdvise(m_pStockQuotes, GetUnknown(), IID_IStockEvents, &m_dwCookie);

		// set default font.
		//
		if (m_pFont == NULL)
		{
			IFont*  pFont;
			GetAmbientFont(&pFont);
			if (pFont)
			{
				pFont->QueryInterface(IID_IFontDisp, (void**) &m_pFont);
				pFont->Release();
			}
		}

		// set default back and fore colors.
		//
		if (m_clrBackColor == -1 && m_clrForeColor == -1)
		{
			GetAmbientBackColor(m_clrBackColor);
			GetAmbientForeColor(m_clrForeColor);
		}
		CreateTimer();
	}
	else if (ok && !pClientSite && m_dwCookie)
		ShutDown();

	return hr;
}

// If we haven't cleaned up yet, do so here.
//
HRESULT CStockTickerATL::IOleObject_Close(DWORD dwSaveOption)
{
	if (m_dwCookie && m_pStockQuotes != NULL)
		ShutDown();
	return CComControl<CStockTickerATL>::IOleObject_Close(dwSaveOption);
}

// Save and restore persistent data.
//
HRESULT CStockTickerATL::IPersistStreamInit_Load(LPSTREAM pStm, ATL_PROPMAP_ENTRY* pMap)
{
	HRESULT hr = IPersistStreamInitImpl<CStockTickerATL>::IPersistStreamInit_Load(pStm, pMap);
	pStm->Commit(STGC_DEFAULT);
	m_pStockQuotes->Load(pStm);
	m_renderStocks.SetTextToWaiting();
	m_pStockQuotes->StartUpdating(m_updateInterval);
	return hr;
}

HRESULT CStockTickerATL::IPersistStreamInit_Save(LPSTREAM pStm, BOOL fClearDirty,
												 ATL_PROPMAP_ENTRY* pMap)
{
	HRESULT hr = IPersistStreamInitImpl<CStockTickerATL>::IPersistStreamInit_Save(pStm, fClearDirty, pMap);
	pStm->Commit(STGC_DEFAULT);
	m_pStockQuotes->Save(pStm);
	pStm->Commit(STGC_DEFAULT);
	return hr;
}


// Called if Stock Quotes component could not be created.  Display error
// message.
//
void CStockTickerATL::CreateComponetFailed()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strError;
	CString strTitle;
	VERIFY(strError.LoadString(IDS_CREATE_COMPONENT_FAILED));
	::MessageBox(0, strError, _T("Stock Ticker Control"), MB_OK|MB_ICONERROR);
}

// Timer managment.
//
void CStockTickerATL::CreateTimer()
{
	m_nTimerID = ::SetTimer(0, 1, m_tickerSpeed, TimerProc);
}

void CStockTickerATL::DestroyTimer()
{
	::KillTimer(0, m_nTimerID);
}

// Helper function to take care of cleanup.
// Kill timer and remove connection point.  Tell stock quotes component to
// stop updating the stock data.  Finally, release the stock quotes component.
//
//
void CStockTickerATL::ShutDown()
{
	DestroyTimer();
	AtlUnadvise(m_pStockQuotes, IID_IStockEvents, m_dwCookie);
	m_pStockQuotes->StopUpdating();
	m_pStockQuotes.Release();
	m_dwCookie = 0;
}

// Check if the stock info data has changed (notified through connection point).
// If so, get IEnumString from stock quotes component and give to rendering
// object.
//
void CStockTickerATL::TimerTick()
{
	if (m_bNeedToUpdate && m_pStockQuotes != NULL)
	{
		m_bNeedToUpdate = false;
		IEnumString* pEnum = 0;
		HRESULT hr = m_pStockQuotes->EnumAsString(&pEnum);
		ASSERT(SUCCEEDED(hr));
		if (SUCCEEDED(hr))
			m_renderStocks.SetData(pEnum);
		pEnum->Release();
	}
	FireViewChange();
}

// Display popup menu.  Allows the user to add stocks or goto the control
// properties.  If activated windowless then a dialog box is displayed instead.
//
LRESULT CStockTickerATL::OnRButtonUp(UINT /* nMsg */, WPARAM /* wParam */,
									 LPARAM lParam, BOOL& /* lResult */)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_hWnd)    // windowless
	{
		CWindowlessOptions      dialog;

		if (dialog.DoModal() == IDOK &&
			dialog.m_chosenOption != CWindowlessOptions::woNone)
		{
			BOOL    b;
			if (dialog.m_chosenOption == CWindowlessOptions::woStocks)
				OnStocks(0,0,0,b);
			else if (dialog.m_chosenOption == CWindowlessOptions::woUpdateNow)
				OnUpdateNow(0,0,0,b);
			else if (dialog.m_chosenOption == CWindowlessOptions::woProperties)
				OnProperties(0,0,0,b);
		}
	}
	else
	{
		CMenu   popup;

		CPoint  point(LOWORD(lParam), HIWORD(lParam));
		::ClientToScreen(m_hWnd, &point);

		BOOL    b = popup.LoadMenu(IDR_MENU_STOCKCTRL);
		ASSERT(b);
		if (b)
		{
			CMenu*  pSubMenu = popup.GetSubMenu(0);
			ASSERT(pSubMenu);
			if (pSubMenu)
			{
				CWnd    wnd;
				wnd.Attach(m_hWnd);
				pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, &wnd);
				wnd.Detach();
			}
		}
	}
	return 0;
}

//
// Disable all the menu items if updating stock information.
//
LRESULT CStockTickerATL::OnInitMenuPopup(UINT /* nMsg */, WPARAM wParam,
										 LPARAM lParam, BOOL& lResult)
{
	if (IsUpdating() || m_pStockQuotes == NULL)
	{
		CMenu   popup;
		BOOL    b;
		VERIFY(b = popup.Attach((HMENU)wParam));
		if (b)
		{
			popup.EnableMenuItem(ID_STOCKS, MF_GRAYED);
			popup.EnableMenuItem(ID_PROPERTIES, MF_GRAYED);
			popup.EnableMenuItem(ID_UPDATENOW, MF_GRAYED);
		}
		popup.Detach();
	}
	else
		lResult = FALSE;
	return 0;
}


// Handler for properties menu item - just display the property page.
//
LRESULT CStockTickerATL::OnProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoVerbProperties(0, m_hWnd);
	return 0;
}

// Handler for add/remove stocks dialog.
//
LRESULT CStockTickerATL::OnStocks(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	IEnumString*    pEnum = 0;
	HRESULT         hr = m_pStockQuotes->EnumAsString(&pEnum);
	ASSERT(SUCCEEDED(hr));
	USES_CONVERSION;
	LPOLESTR        s;

	CString         str;
	CStockSymbols   stockSymbols;
	while (pEnum->Next(1, &s, 0) == S_OK)
	{
		str = s;
		stockSymbols.push_back(str.Left(str.Find(':')));
		::CoTaskMemFree(s);
	}

	pEnum->Release();
	CStocksDialog   stocksDialog(stockSymbols);

	// tell stock quotes component to add new stocks and remove existing ones.
	//
	if (stocksDialog.DoModal() == IDOK)
	{
		CStockSymbols::iterator i1 = stocksDialog.m_stockSymbolsAdded.begin();
		CStockSymbols::iterator e1 = stocksDialog.m_stockSymbolsAdded.end();
		CStockSymbols::iterator i2 = stocksDialog.m_stockSymbolsRemoved.begin();
		CStockSymbols::iterator e2 = stocksDialog.m_stockSymbolsRemoved.end();

		for (; i1 != e1; i1++)
			m_pStockQuotes->Add(T2OLE((LPTSTR)(LPCTSTR)*i1));

		for (; i2 != e2; i2++)
			m_pStockQuotes->Remove(T2OLE((LPTSTR)(LPCTSTR)*i2));
		m_pStockQuotes->StartUpdating(m_updateInterval);
		m_pStockQuotes->Update();
	}
	return 0;
}

//
// Update stock information now.
//
LRESULT CStockTickerATL::OnUpdateNow(WORD wNotifyCode, WORD wID, HWND hWndCtl,
									 BOOL& bHandled)
{
	m_pStockQuotes->Update();
	return 0;
}

// Update interval property get method.
//
STDMETHODIMP CStockTickerATL::get_UpdateInterval(short * pVal)
{
	*pVal = m_updateInterval;
	return S_OK;
}

// Update interval property put method.  Does bounds checking.  Does nothing
// if value is not different from current value.
//
STDMETHODIMP CStockTickerATL::put_UpdateInterval(short newVal)
{
	if (newVal < 1)
		return Error(_T("Update interval must be 1 minute or greater"));
	if (newVal != m_updateInterval)
	{
		m_updateInterval = newVal;
		m_pStockQuotes->StartUpdating(m_updateInterval);
		FireViewChange();
	}
	return S_OK;
}

// Stock ticker speed property get method.
//
STDMETHODIMP CStockTickerATL::get_TickerSpeed(short * pVal)
{
	*pVal = m_tickerSpeed;
	return S_OK;
}

// Stock ticker speed property put method.  Does bounds checking.  if new
// value is not different from current value then nothing happens.
//
STDMETHODIMP CStockTickerATL::put_TickerSpeed(short newVal)
{
	if (newVal < 0 || newVal > 200)
		return Error(_T("Ticker speed must be between 0 and 200"));
	if (newVal != m_tickerSpeed)
	{
		m_tickerSpeed = newVal;

		DestroyTimer();
		CreateTimer();
		FireViewChange();
	}
	return S_OK;
}

STDMETHODIMP CStockTickerATL::get_MSInvestorURL(BSTR * pVal)
{
	return m_pStockQuotes->GetMSInvestorURL(pVal);
}

STDMETHODIMP CStockTickerATL::put_MSInvestorURL(BSTR newVal)
{
	return m_pStockQuotes->SetMSInvestorURL(newVal);
}

STDMETHODIMP CStockTickerATL::get_StockSourceISAPIDllURL(BSTR * pVal)
{
	return m_pStockQuotes->GetStockSourceISAPIDllURL(pVal);
}

STDMETHODIMP CStockTickerATL::put_StockSourceISAPIDllURL(BSTR newVal)
{
	return m_pStockQuotes->SetStockSourceISAPIDllURL(newVal);
}
