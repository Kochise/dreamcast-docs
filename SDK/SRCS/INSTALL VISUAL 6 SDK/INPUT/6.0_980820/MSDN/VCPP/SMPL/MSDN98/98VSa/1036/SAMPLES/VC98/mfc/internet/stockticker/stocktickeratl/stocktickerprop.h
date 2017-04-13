// StockTickerProp.h : Declaration of the CStockTickerProp
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

#ifndef __STOCKTICKERPROP_H_
#define __STOCKTICKERPROP_H_

#include "resource.h"       // main symbols
#include "stocktickeratl.h"

EXTERN_C const CLSID CLSID_StockTickerProp;

/////////////////////////////////////////////////////////////////////////////
// CStockTickerProp
//
class ATL_NO_VTABLE CStockTickerProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStockTickerProp, &CLSID_StockTickerProp>,
	public IPropertyPageImpl<CStockTickerProp>,
	public CDialogImpl<CStockTickerProp>
{
public:
	CStockTickerProp()
	: m_bCreating(true)
	{
		m_dwTitleID = IDS_TITLEStockTickerProp;
		m_dwHelpFileID = IDS_HELPFILEStockTickerProp;
		m_dwDocStringID = IDS_DOCSTRINGStockTickerProp;
	}

	enum {IDD = IDD_STOCKTICKERPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_STOCKTICKERPROP)

BEGIN_COM_MAP(CStockTickerProp)
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CStockTickerProp)
	COMMAND_HANDLER(IDC_EDIT_MINUTES, EN_CHANGE, OnUpdateIntervalChange)
	COMMAND_HANDLER(IDC_EDIT_MSINVESTOR_URL, EN_CHANGE, OnUpdateMSInvestorURL)
	COMMAND_HANDLER(IDC_EDIT_ISAPI_DLL_URL, EN_CHANGE, OnUpdateISAPIDllURL)
	MESSAGE_HANDLER(WM_HSCROLL, OnTickerSpeedChange)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	CHAIN_MSG_MAP(IPropertyPageImpl<CStockTickerProp>)
END_MSG_MAP()

	STDMETHOD(Apply)(void);

// overrides
//
	HWND    Create(HWND hWndParent);

protected:
	// set in Create() so message handlers don't do SetDirty().
	bool    m_bCreating;
	short   m_origTickerSpeed;      // for reseting if user cancels dialog.

	void    DisplayPropError();

// message handlers
//
	LRESULT OnUpdateIntervalChange(WORD wNotify, WORD nID, HWND hWnd, BOOL& bHandled);
	LRESULT OnUpdateMSInvestorURL(WORD wNotify, WORD nID, HWND hWnd, BOOL& bHandled);
	LRESULT OnUpdateISAPIDllURL(WORD wNotify, WORD nID, HWND hWnd, BOOL& bHandled);
	LRESULT OnTickerSpeedChange(UINT /* nMsg */, WPARAM /* wParam */,
								LPARAM /* lParam */, BOOL& /* lResult */);
	LRESULT OnDestroy(UINT /* nMsg */, WPARAM /* wParam */,
					  LPARAM /* lParam */, BOOL& lResult);
};

#endif //__STOCKTICKERPROP_H_
