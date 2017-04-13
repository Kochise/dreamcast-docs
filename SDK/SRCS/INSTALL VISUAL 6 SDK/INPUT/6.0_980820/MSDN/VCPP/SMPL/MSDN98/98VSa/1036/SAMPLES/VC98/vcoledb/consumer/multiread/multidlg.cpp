// MultiDlg.cpp : Implementation of CMultiDlg
#include "stdafx.h"
#include "MultiDlg.h"
#include "DBRead.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiDlg

CMultiDlg::CMultiDlg()
{
}

CMultiDlg::~CMultiDlg()
{
}

LRESULT CMultiDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow();
	return 1;  // Let the system set the focus
}

LRESULT CMultiDlg::OnRun(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR   szMsg[256];
	long    nThreads = GetDlgItemInt(IDC_THREADS);
	DWORD   dwTime, dwRows;

	if (nThreads < 1 || nThreads > MAXIMUM_WAIT_OBJECTS)
	{
		wsprintf(szMsg, _T("Must have between 1 and %d threads."), MAXIMUM_WAIT_OBJECTS);
		MessageBox(szMsg, _T("Error"), 0);
		return 0;
	}

	// Clear text first so we know when it's finished
	SetDlgItemText(IDC_MESSAGE, _T(""));
	ReadRecords(nThreads, &dwTime, &dwRows);

	wsprintf(szMsg, _T("%d records in %ld ms"), dwRows, dwTime);
	SetDlgItemText(IDC_MESSAGE, szMsg);

	return 0;
}

LRESULT CMultiDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
