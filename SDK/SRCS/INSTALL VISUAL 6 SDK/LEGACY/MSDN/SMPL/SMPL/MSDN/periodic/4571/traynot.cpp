/////////////////////////////////////////////////////////////////////////////
// TrayNot.cpp : implementation file
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//
//	Usage: This class is just a light wrapper around the Windows 95 system
//			 tray icon notification facility. The constructor requires a CWnd
//			 object pointer in order to deliver the user-defined notification
//			 message, which must also be provided. In addition, the constuctor
//			 requires a pointer to an array of icons which will be used for
//			 notifications. It is up to the caller to verify that a valid
//			 notification index is provided, this class has no knowledge
//			 of the icon array size.
//
//			 Typically, the CWinApp holds the icon list and the CMainFrame
//			 creates this object in the following manner:
//
//				CTrayNot* pTrayObject = new CTrayNot ( this,
//																	WM_MY_NOTIFY,
//																	"Application", 
//																	theApp.m_IconList ) ;
//
//			 When the object is created, it will set the initial icon to
//			 the first one in the icon list. THereafter, the SetState()
//			 member function is called with an index into the icon list array
//			 to select a new icon for the tray.
//
//			 The PTrayObject is deleted in the CMainFrame::OnClose handler.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrayNot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrayNot

CTrayNot::CTrayNot ( CWnd* pWnd, UINT uCallbackMessage,
							LPCTSTR szTip, HICON* pList )
{
	// this is only for Windows 95 (or higher)
	m_bEnabled = ( GetVersion() & 0xff ) >= 4 ;
	if ( ! m_bEnabled )
		return ;

	// load up the NOTIFYICONDATA structure
	m_tnd.cbSize = sizeof(NOTIFYICONDATA) ;
	m_tnd.hWnd = pWnd->GetSafeHwnd() ;
	m_tnd.uID = 0 ;
	m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP ;
	m_tnd.uCallbackMessage = uCallbackMessage ;
	strcpy ( m_tnd.szTip, szTip ) ;

	// save the pointer to the icon list and set the initial
	// default icon.
	m_pIconList = pList ;
	m_tnd.hIcon = m_pIconList[0] ;
	Shell_NotifyIcon ( NIM_ADD, &m_tnd ) ;
}

CTrayNot::~CTrayNot()
{
	if ( m_bEnabled )
		Shell_NotifyIcon ( NIM_DELETE, &m_tnd ) ;
}

void CTrayNot::SetState ( int id )
{
	if ( ! m_bEnabled )
		return ;
	m_tnd.hIcon = m_pIconList[id] ;
	Shell_NotifyIcon ( NIM_MODIFY, &m_tnd ) ;
}