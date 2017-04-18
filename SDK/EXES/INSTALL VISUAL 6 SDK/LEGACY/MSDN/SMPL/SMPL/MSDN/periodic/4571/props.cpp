/////////////////////////////////////////////////////////////////////////////
// Props.cpp : implementation file
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "resource.h"
#include "Props.h"
#include "Webster.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebProps

IMPLEMENT_DYNAMIC(CWebProps, CPropertySheet)

CWebProps::CWebProps(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
	AddPage(&m_Page5);
}

CWebProps::~CWebProps()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWebProps helpers

void CWebProps::GetProps()
{
	m_Page1.m_nPort			= theApp.m_wwwPort ;
	m_Page1.m_nMaxConnects	= theApp.m_nMaxConnects ;
	m_Page1.m_nTimeOut		= theApp.m_nTimeOut ;
	m_Page1.m_nSanityTime	= theApp.m_nSanityTime ;

	m_Page2.m_DefaultPath	= theApp.m_HTMLPath ;
	m_Page2.m_DefaultName	= theApp.m_HTMLDefault ;
	m_Page2.m_TagFile			= theApp.m_HTMLTag ;
	m_Page2.m_nTagType		= theApp.m_nTagType ;

	m_Page3.m_bLogEnable		= theApp.m_bLogEnable ;
	m_Page3.m_LogPath			= theApp.m_LogPath ;

	m_Page4.m_bStatusEnable	= theApp.m_bShowStatus ;
	m_Page4.m_bHostName		= theApp.m_bResolveClientname ;
	m_Page4.m_bDebugEnable	= theApp.m_bDebugOutput ;

	m_Page5.m_bEnableSound	= theApp.m_bEnableSound ;
	m_Page5.m_bEnableIcon	= theApp.m_bEnableIcon ;
	m_Page5.m_hIdle			= theApp.m_pIconList[1] ;
	m_Page5.m_hActive			= theApp.m_pIconList[2] ;
}

void CWebProps::SetProps()
{
	// changing the port will require a shutdown/restart
	if ( theApp.m_wwwPort != m_Page1.m_nPort )
		AfxMessageBox ( "Service port has changed.\nServer restart is required." ) ;
	theApp.m_wwwPort			= m_Page1.m_nPort ;
	theApp.m_nMaxConnects	= m_Page1.m_nMaxConnects ;
	theApp.m_nTimeOut			= m_Page1.m_nTimeOut ;
	if ( m_Page1.m_nSanityTime != theApp.m_nSanityTime )
	{
		theApp.m_nSanityTime	= m_Page1.m_nSanityTime ;
		// timer notification causes new time value to take effect
		AfxGetMainWnd()->PostMessage ( WM_TIMER,
												 (WPARAM)IDT_SANITY_TIME,
						 						 (LPARAM)0 ) ;
	}

	theApp.m_HTMLPath			= m_Page2.m_DefaultPath ;
	theApp.m_HTMLDefault		= m_Page2.m_DefaultName	;
	theApp.m_HTMLTag			= m_Page2.m_TagFile ;
	theApp.m_nTagType			= (enum CWebApp::TAG_TYPE)m_Page2.m_nTagType ;

	// a change in either of these causes a OpenLogfile() call,
	//    but only after the new values have been set.
	BOOL bReOpen = m_Page3.m_bLogEnable != theApp.m_bLogEnable ||
						m_Page3.m_LogPath    != theApp.m_LogPath ;
	theApp.m_bLogEnable		= m_Page3.m_bLogEnable ;
	theApp.m_LogPath			= m_Page3.m_LogPath ;
	if ( bReOpen )
	{
		// see the notes in CMainFrame::OnTimer handler
		AfxGetMainWnd()->PostMessage ( WM_NEW_LOGFILE,
												 (WPARAM)0,
												 (LPARAM)0 ) ;
	}

	theApp.m_bShowStatus 			= m_Page4.m_bStatusEnable ;
	theApp.m_bResolveClientname	= m_Page4.m_bHostName ;
	theApp.m_bDebugOutput			= m_Page4.m_bDebugEnable ;

	theApp.m_bEnableSound			= m_Page5.m_bEnableSound ;
	theApp.m_bEnableIcon				= m_Page5.m_bEnableIcon ;

	// save now!!!
	theApp.SaveProps() ;
}

BEGIN_MESSAGE_MAP(CWebProps, CPropertySheet)
	//{{AFX_MSG_MAP(CWebProps)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWebProps message handlers


