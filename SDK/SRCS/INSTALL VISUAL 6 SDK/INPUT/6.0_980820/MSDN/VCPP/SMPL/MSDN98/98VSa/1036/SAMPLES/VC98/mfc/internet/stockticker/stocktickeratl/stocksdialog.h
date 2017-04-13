// StocksDialog.h : Declaration of the CStocksDialog
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

#ifndef __STOCKSDIALOG_H_
#define __STOCKSDIALOG_H_

#include "resource.h"       // main symbols
#include "stocksymbols.h"

/////////////////////////////////////////////////////////////////////////////
// CStocksDialog
//
class CStocksDialog :
	public CDialogImpl<CStocksDialog>
{
public:
	CStocksDialog(CStockSymbols& symbols);
	~CStocksDialog();

	enum { IDD = IDD_STOCKSDIALOG };

BEGIN_MSG_MAP(CStocksDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDC_BUTTON_ADD, OnAdd)
	COMMAND_ID_HANDLER(IDC_BUTTON_REMOVE, OnRemove)
	COMMAND_ID_HANDLER(IDC_LIST_STOCKS, OnStockSelChange)
	COMMAND_ID_HANDLER(IDC_EDIT_STOCK_SYMBOL, OnSymbolChange)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnRemove(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStockSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSymbolChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	CStockSymbols   m_stockSymbolsAdded;        // symbols to add.
	CStockSymbols   m_stockSymbolsRemoved;      // symbols to remove.

protected:
	CStockSymbols&  m_srcSymbols;               // original list.

};

#endif //__STOCKSDIALOG_H_
