// WindowlessOptions.cpp : Implementation of CWindowlessOptions
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
#include "WindowlessOptions.h"

/////////////////////////////////////////////////////////////////////////////
// CWindowlessOptions

CWindowlessOptions::CWindowlessOptions()
: m_chosenOption(woNone)
{
}

CWindowlessOptions::~CWindowlessOptions()
{
}

LRESULT CWindowlessOptions::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 1;  // Let the system set the focus
}

// Simply set m_chosenOption to the appropriate user action.
//
LRESULT CWindowlessOptions::OnStocks(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != BN_CLICKED)
		bHandled = false;
	else
	{
		m_chosenOption = woStocks;
		EndDialog(IDOK);
	}
	return 0;
}

LRESULT CWindowlessOptions::OnUpdateNow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != BN_CLICKED)
		bHandled = false;
	else
	{
		m_chosenOption = woUpdateNow;
		EndDialog(IDOK);
	}
	return 0;
}

LRESULT CWindowlessOptions::OnProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode != BN_CLICKED)
		bHandled = false;
	else
	{
		m_chosenOption = woProperties;
		EndDialog(IDOK);
	}
	return 0;
}

LRESULT CWindowlessOptions::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}
