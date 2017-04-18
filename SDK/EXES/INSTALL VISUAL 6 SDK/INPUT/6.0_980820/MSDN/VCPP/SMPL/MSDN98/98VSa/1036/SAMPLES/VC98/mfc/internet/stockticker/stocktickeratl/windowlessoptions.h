// WindowlessOptions.h : Declaration of the CWindowlessOptions
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

#ifndef __WINDOWLESSOPTIONS_H_
#define __WINDOWLESSOPTIONS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWindowlessOptions
//
// When the control has been activated windowless a popup menu can't be created since
// there is no window handle to pass to TrackPopupMenu(), so this dialog is used instead.

class CWindowlessOptions :
	public CDialogImpl<CWindowlessOptions>
{
public:
	CWindowlessOptions();
	~CWindowlessOptions();

	enum Options { woStocks, woUpdateNow, woProperties, woNone };
	enum { IDD = IDD_WINDOWLESS_OPTIONS };

	Options     m_chosenOption;

BEGIN_MSG_MAP(CWindowlessOptions)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_WO_STOCKS, OnStocks)
	COMMAND_ID_HANDLER(IDC_WO_UPDATE_NOW, OnUpdateNow)
	COMMAND_ID_HANDLER(IDC_WO_PROPERTIES, OnProperties)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnStocks(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnUpdateNow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif //__WINDOWLESSOPTIONS_H_
