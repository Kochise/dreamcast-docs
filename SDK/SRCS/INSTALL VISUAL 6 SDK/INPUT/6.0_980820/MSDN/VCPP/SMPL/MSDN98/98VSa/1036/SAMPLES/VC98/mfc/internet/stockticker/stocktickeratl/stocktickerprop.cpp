// StockTickerProp.cpp : Implementation of CStockTickerProp
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
#include "StockTickerProp.h"
#include <wininet.h>

/////////////////////////////////////////////////////////////////////////////
// CStockTickerProp

// Tell control to change the ticker speed and URLs.
//
HRESULT CStockTickerProp::Apply()
{
	ATLTRACE(_T("CStockTickerProp::Apply\n"));
	short tickerSpeed = (short)SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_GETPOS, 0, 0);
	short updateInterval = (short)GetDlgItemInt(IDC_EDIT_MINUTES);
	for (UINT i = 0; i < m_nObjects; i++)
	{
		CComQIPtr<IStockTickerATL, &IID_IStockTickerATL> pStockTicker(m_ppUnk[i]);
		if FAILED(pStockTicker->put_UpdateInterval(updateInterval))
		{
			DisplayPropError();
			return E_FAIL;
		}

		if FAILED(pStockTicker->put_TickerSpeed(tickerSpeed))
		{
			DisplayPropError();
			return E_FAIL;
		}
		m_origTickerSpeed = tickerSpeed;

		// Update URLS.
		//
		USES_CONVERSION;
		TCHAR   buf[INTERNET_MAX_URL_LENGTH];
		buf[0] = 0;
		SendDlgItemMessage(IDC_EDIT_MSINVESTOR_URL, WM_GETTEXT,
						   INTERNET_MAX_URL_LENGTH, (LPARAM)buf);
		pStockTicker->put_MSInvestorURL(T2BSTR(buf));
		SendDlgItemMessage(IDC_EDIT_ISAPI_DLL_URL, WM_GETTEXT,
						   INTERNET_MAX_URL_LENGTH, (LPARAM)buf);
		pStockTicker->put_StockSourceISAPIDllURL(T2BSTR(buf));
	}
	m_bDirty = FALSE;
	return S_OK;
}


// Create property page.
//
HWND CStockTickerProp::Create(HWND hWndParent)
{
	HWND hWnd = CDialogImpl<CStockTickerProp>::Create(hWndParent);
	if (hWnd)
	{
		CComQIPtr<IStockTickerATL, &IID_IStockTickerATL> pStockTicker(m_ppUnk[0]);
		short updateInterval;
		short tickerSpeed;

		// get property info from control.
		//
		pStockTicker->get_UpdateInterval(&updateInterval);
		pStockTicker->get_TickerSpeed(&tickerSpeed);
		m_origTickerSpeed = tickerSpeed;  // for dynamic update of ticker speed.

		SetDlgItemInt(IDC_EDIT_MINUTES, updateInterval);

		// setup slider.
		//
		SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_SETPAGESIZE, 0, (long)10);
		SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_SETRANGE, 1, MAKELONG(0, 200));
		SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_SETPOS, 1, (long)tickerSpeed);

		// set URLs.
		//
		USES_CONVERSION;
		BSTR    bstr;
		pStockTicker->get_MSInvestorURL(&bstr);
		SendDlgItemMessage(IDC_EDIT_MSINVESTOR_URL, WM_SETTEXT, 0, (LPARAM)OLE2T(bstr));
		::SysFreeString(bstr);
		pStockTicker->get_StockSourceISAPIDllURL(&bstr);
		SendDlgItemMessage(IDC_EDIT_ISAPI_DLL_URL, WM_SETTEXT, 0, (LPARAM)OLE2T(bstr));
		::SysFreeString(bstr);
	}
	m_bCreating = false;
	return hWnd;
}

// If update interval field has changed set dirty flag.  Because we set this
// field in Create() there is a check for whether we are being created.  If
// so then do nothing.
//
LRESULT CStockTickerProp::OnUpdateIntervalChange(WORD wNotify, WORD nID,
												 HWND hWnd, BOOL& bHandled)
{
	if (!m_bCreating)
		SetDirty(TRUE);
	return 0;
}

// Just set dirty flag unless set by create.
//
LRESULT CStockTickerProp::OnUpdateMSInvestorURL(WORD wNotify, WORD nID,
												HWND hWnd, BOOL& bHandled)
{
	if (!m_bCreating)
		SetDirty(TRUE);
	return 0;
}

LRESULT CStockTickerProp::OnUpdateISAPIDllURL(WORD wNotify, WORD nID,
											  HWND hWnd, BOOL& bHandled)
{
	if (!m_bCreating)
		SetDirty(TRUE);
	return 0;
}

// As the slider moves tell control to change the ticker speed.
//
LRESULT CStockTickerProp::OnTickerSpeedChange(UINT /* nMsg */, WPARAM /* wParam */,
											  LPARAM /* lParam */, BOOL& /* lResult */)
{
	if (!m_bCreating)
	{
		short tickerSpeed = (short)SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_GETPOS, 0, 0);
		for (UINT i = 0; i < m_nObjects; i++)
		{
			CComQIPtr<IStockTickerATL, &IID_IStockTickerATL> pStockTicker(m_ppUnk[i]);
			pStockTicker->put_TickerSpeed(tickerSpeed);
		}
		SetDirty(TRUE);
	}
	return 0;
}

// If the user has canceled the dialog then reset control's ticker speed to
// its original value.
//
LRESULT CStockTickerProp::OnDestroy(UINT /* nMsg */, WPARAM /* wParam */,
									LPARAM /* lParam */, BOOL& lResult)
{
	short tickerSpeed = (short)SendDlgItemMessage(IDC_SLIDER_TICKER_SPEED, TBM_GETPOS, 0, 0);
	if (m_origTickerSpeed != tickerSpeed)
	{
		for (UINT i = 0; i < m_nObjects; i++)
		{
			CComQIPtr<IStockTickerATL, &IID_IStockTickerATL> pStockTicker(m_ppUnk[i]);
			pStockTicker->put_TickerSpeed(m_origTickerSpeed);
		}
	}
	lResult = FALSE;
	return 0;
}

// Display message box indicating a property change was invalid.
//
void CStockTickerProp::DisplayPropError()
{
	USES_CONVERSION;
	CComPtr<IErrorInfo> pError;
	CComBSTR            bstrError;
	GetErrorInfo(0, &pError);
	pError->GetDescription(&bstrError);
	MessageBox(OLE2T(bstrError), _T("Property Error"), MB_ICONEXCLAMATION);
}
