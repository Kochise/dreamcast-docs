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
#include "stockquotes.h"
#include "StockQuotes_.h"
#include "stockupdatenotify.h"

static void CALLBACK UpdateNotifyProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);

BEGIN_MESSAGE_MAP(CStockUpdateNotify, CWinThread)
	//{{AFX_MSG_MAP(CStockUpdateNotify)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_STOCK_UPDATE_NOTIFY_NOW, OnNotifyNow)
END_MESSAGE_MAP()


IMPLEMENT_DYNCREATE(CStockUpdateNotify, CWinThread)

// used by timer proc to call back into notify object.
//
CStockUpdateNotify* CStockUpdateNotify::s_pInstance = 0;


CStockUpdateNotify::CStockUpdateNotify()
: m_bSuspendNotifications(false)
{
	m_nNotifyInterval = 15;     // default, gets reset by control.
	m_pStockQuotes = 0;
	s_pInstance = this;
}

CStockUpdateNotify::~CStockUpdateNotify()
{
}

BOOL CStockUpdateNotify::InitInstance()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CoInitialize(0);

	CWinThread::InitInstance();

	m_bAutoDelete = true;

	return TRUE;
}

int CStockUpdateNotify::ExitInstance()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	::KillTimer(0, m_nTimerID);
	s_pInstance = 0;
	// tell stock quotes object that thread has finished.
	//
	m_pStockQuotes->NotifyThreadEnding();
	CoUninitialize();
	return CWinThread::ExitInstance();
}

// Set the notification interval (time between stock info updates).
// bResume resumes the notification process.
//
void CStockUpdateNotify::SetNotifyInterval(int nNotifyInterval, bool bResume)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_nNotifyInterval = nNotifyInterval;
	if (bResume)
		m_bSuspendNotifications = false;
}

/////////////////////////////////////////////////////////////////////////////
// CStockUpdateNotify message handlers

// Start a 2 second timer.
//
int CStockUpdateNotify::Run()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// update right away.  If this gets in the way just comment it out
	// and call Update() or StartUpdating() from the control.
	//
	m_time = CTime::GetCurrentTime();
	m_time -= CTimeSpan(0, 0, m_nNotifyInterval, 0);

	m_nTimerID = ::SetTimer(0, 20031, 2000, UpdateNotifyProc);

	return CWinThread::Run();
}

// Ask stock quotes object to update its data from the net.
// Upon shutdown it may be necessary to end the thread, m_bNeedToEnd controls
// this.
//
void CStockUpdateNotify::NotifyNow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pStockQuotes->DoUpdate();
}

// Check if it is time to notify the stock quotes object to update its data.
//
void CStockUpdateNotify::DoNotify(bool bForce)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CTimeSpan   timeDiff = CTime::GetCurrentTime() - m_time;
	if ((timeDiff.GetMinutes() >= m_nNotifyInterval) || bForce)
	{
		if (!IsSuspended())
			NotifyNow();
		m_time = CTime::GetCurrentTime();
	}
}

// Message handler for notification.
//
void CStockUpdateNotify::OnNotifyNow(WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	DoNotify(true);
}

// Timer proc, just calls back into the CStockUpdateNotify object.
//
void CALLBACK UpdateNotifyProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CStockUpdateNotify::s_pInstance->DoNotify();
}
