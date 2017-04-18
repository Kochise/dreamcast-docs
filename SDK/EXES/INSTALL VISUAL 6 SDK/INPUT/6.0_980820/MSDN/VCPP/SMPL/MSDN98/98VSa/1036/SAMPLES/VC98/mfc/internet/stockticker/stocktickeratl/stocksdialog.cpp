// StocksDialog.cpp : Implementation of CStocksDialog
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
#include "StocksDialog.h"
#include <algorithm>

/////////////////////////////////////////////////////////////////////////////
// CStocksDialog

CStocksDialog::CStocksDialog(CStockSymbols& symbols)
: m_srcSymbols(symbols)
{
}

CStocksDialog::~CStocksDialog()
{
}

LRESULT CStocksDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// fill listbox.
	//
	for (CStockSymbols::const_iterator i = m_srcSymbols.begin();
		 i != m_srcSymbols.end(); i++)
	{
		SendDlgItemMessage(IDC_LIST_STOCKS, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)*i);
	}

	// disable both add and remove buttons.
	//
	::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), FALSE);
	::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), FALSE);
	return 1;  // Let the system set the focus
}

LRESULT CStocksDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

// Clear the add and remove stock lists.
//
LRESULT CStocksDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_stockSymbolsAdded.clear();
	m_stockSymbolsRemoved.clear();
	EndDialog(wID);
	return 0;
}

// Add a stock to the listbox and appropriate symbol list.  Ignore duplicates.
// If a listbox item is still selected then enable the reove button.  disable
// the add button.
//
LRESULT CStocksDialog::OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != BN_CLICKED)
	{
		bHandled = FALSE;
		return 0;
	}

	CString     s;
	HWND        ctrlStockSymbol = GetDlgItem(IDC_EDIT_STOCK_SYMBOL);
	int         nLen = ::GetWindowTextLength(ctrlStockSymbol);

	::GetWindowText(ctrlStockSymbol, s.GetBufferSetLength(nLen), nLen+1);
	s.ReleaseBuffer();

	// Has stock symbol already been added?
	//
	if (std::find(m_stockSymbolsAdded.begin(),
				  m_stockSymbolsAdded.end(), s) == m_stockSymbolsAdded.end() &&
		std::find(m_srcSymbols.begin(),
				  m_srcSymbols.end(), s) == m_srcSymbols.end())
	{
		s.MakeUpper();
		SendDlgItemMessage(IDC_LIST_STOCKS, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)s);
		m_stockSymbolsAdded.push_back(s);

		// incase symbol was previously removed.
		m_stockSymbolsRemoved.remove(s);
	}
	::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), FALSE);
	::SetWindowText(ctrlStockSymbol, _T(""));
	if (SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETSELCOUNT, 0, 0))
		::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), TRUE);
	return 0;
}

// Remove stocks from listbox and appropriate symbol lists.
// Disable remove button.
//
LRESULT CStocksDialog::OnRemove(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != BN_CLICKED)
	{
		bHandled = FALSE;
		return 0;
	}

	TCHAR   buf[128];
	int     cnt = SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETSELCOUNT, 0, 0);
	int*    indexes = new int[cnt];

	SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETSELITEMS, cnt, (LPARAM)indexes);
	for (int i = cnt-1; i >= 0; i--)
	{
		SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETTEXT, indexes[i], (LPARAM)buf);
		SendDlgItemMessage(IDC_LIST_STOCKS, LB_DELETESTRING, indexes[i], 0);
		m_stockSymbolsRemoved.push_back(buf);
		m_stockSymbolsAdded.remove(buf);
	}
	delete[] indexes;
	::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), FALSE);
	return 0;
}

// Stock selection has changed, update symbol edit field.  Enable add button.
// Disable remove button if no selections, otherwise enable it.
//
LRESULT CStocksDialog::OnStockSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != LBN_SELCHANGE)
	{
		bHandled = FALSE;
		return 0;
	}

	::SetWindowText(GetDlgItem(IDC_EDIT_STOCK_SYMBOL), _T(""));
	::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), FALSE);
	if (SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETSELCOUNT, 0, 0))
		::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), TRUE);
	else
		::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), FALSE);
	return 0;
}

// Stock symbol edit field has changed, if field is now empty or the symbol
// already exists then disable add button.  If there are listbox items selected
// then enable the remove button.
//
LRESULT CStocksDialog::OnSymbolChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != EN_CHANGE)
	{
		bHandled = FALSE;
		return 0;
	}

	CString s;
	HWND    ctrlStockSymbol = GetDlgItem(IDC_EDIT_STOCK_SYMBOL);
	int     nLen = ::GetWindowTextLength(ctrlStockSymbol);
	::GetWindowText(ctrlStockSymbol, s.GetBufferSetLength(nLen), nLen+1);
	s.ReleaseBuffer();
	s.MakeUpper();
	::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), FALSE);
	if (s.IsEmpty())
	{
		::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), FALSE);
		if (SendDlgItemMessage(IDC_LIST_STOCKS, LB_GETSELCOUNT, 0, 0))
			::EnableWindow(GetDlgItem(IDC_BUTTON_REMOVE), TRUE);
		return 0;
	}
	if (std::find(m_stockSymbolsAdded.begin(),
				  m_stockSymbolsAdded.end(), s) != m_stockSymbolsAdded.end() ||
		std::find(m_srcSymbols.begin(),
				  m_srcSymbols.end(), s) != m_srcSymbols.end())
	{
		::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), FALSE);
	}
	else
		::EnableWindow(GetDlgItem(IDC_BUTTON_ADD), TRUE);
	return 0;
}
