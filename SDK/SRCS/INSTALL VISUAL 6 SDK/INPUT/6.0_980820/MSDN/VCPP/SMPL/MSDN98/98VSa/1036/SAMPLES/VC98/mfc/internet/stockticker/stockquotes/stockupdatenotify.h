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
#if !defined(__STOCKUPDATENOTIFY_H__)
#define __STOCKUPDATENOTIFY_H__

#include "msg.h"

class CStockQuotes;

///////////////////////////////////////////////////////////////////////////////
// CStockUpdateNotify
//
// Thread to tell stock quotes object to update its data from net when
// a wait interval elapses.
//
class CStockUpdateNotify : public CWinThread
{
	DECLARE_DYNCREATE(CStockUpdateNotify)
protected:
	CStockUpdateNotify();           // protected constructor used by dynamic creation

// Attributes
public:
	static CStockUpdateNotify* s_pInstance; // pointer to ourselves for timer.

// Operations
public:
	void                NotifyNow();
	void                Init(CStockQuotes* pStockQuotes)
		{ m_pStockQuotes = pStockQuotes; }
	void                SetNotifyInterval(int nNotifyInterval, bool bResume = true);
	void                SuspendNotifications()
		{ m_bSuspendNotifications = true; }
	bool                IsSuspended() { return m_bSuspendNotifications; }
	void                DoNotify(bool bForce = false);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockUpdateNotify)
	public:
	virtual BOOL    InitInstance();
	virtual int     ExitInstance();
	virtual int     Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStockUpdateNotify();

	CTime                   m_time;             // time to compare to.
	int                     m_nNotifyInterval;  // when to notify.
	CStockQuotes*           m_pStockQuotes;     // pointer to stock quotes obj.
	bool                    m_bSuspendNotifications; // stop notifications?
	UINT                    m_nTimerID;         // timer id.

	// Generated message map functions
	//{{AFX_MSG(CStockUpdateNotify)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	void                OnNotifyNow(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	friend void CALLBACK UpdateProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
};


#endif // __STOCKUPDATENOTIFY_H__
