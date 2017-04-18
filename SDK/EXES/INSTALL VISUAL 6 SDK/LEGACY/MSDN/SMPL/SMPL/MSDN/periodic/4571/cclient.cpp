/////////////////////////////////////////////////////////////////////////////
// CClient.cpp : implementation of the CClient class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "cclient.h"
#include "webdoc.h"
#include "webster.h"	// CWebApp
#include "mainfrm.h"	// CMainFrame

/////////////////////////////////////////////////////////////////////////////
// CClient Construction

CClient::CClient(CWebDoc* m_pParentDoc)
{
	m_pDoc = m_pParentDoc ;	// cache this for lots of use later
	m_bDone = FALSE ;
	m_irx = 0 ;
	m_buf = NULL ;
	m_bHTTP10 = FALSE ;		// assume HTTP 0.9
	m_nMethod = METHOD_UNSUPPORTED ;

	time_t tNow ;
	time ( &tNow ) ;
	CTime cNow ( tNow ) ;
	m_LogRec.datetime	= cNow ;	// this is our birth date
	m_LogRec.client	= "" ;
	m_LogRec.inetd		= "-" ;
	m_LogRec.username	= "-" ;
	m_LogRec.request	= "" ;
	m_LogRec.status	= 200 ;
	m_LogRec.bytes		= 0 ;

	m_pHE = NULL ;
}

CClient::~CClient()
{
	if ( m_buf )
	{
		free ( m_buf ) ;
		m_buf = NULL ;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSocket Implementation

#ifdef _DEBUG
void CClient::AssertValid() const
{
	CSocket::AssertValid();
}

void CClient::Dump(CDumpContext& dc) const
{
	CSocket::Dump(dc);
}
#endif //_DEBUG

IMPLEMENT_DYNAMIC(CClient, CSocket)

/////////////////////////////////////////////////////////////////////////////
// CClient Overridable callbacks

void CClient::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

	// If the read processing was successful, then we've done our job.
	// If not, the service request has not completed yet.
	// Caution: The bDone boolean is used elsewhere,
	//				don't try to tighten up this check.
	if ( ProcessPendingRead() )
	{
		AfxGetMainWnd()->PostMessage ( WM_NEW_CLIENT,
									   (WPARAM)0,
						 			   (LPARAM)this ) ;
		// send request off for processing
		ProcessReq() ;	// process the request
		m_bDone = TRUE ;
		if ( theApp.m_bLogEnable )
		{
			m_pDoc->WriteLog ( m_LogRec ) ;
		}
		AfxGetMainWnd()->PostMessage ( WM_KILL_SOCKET,
									   (WPARAM)0,
						 			   (LPARAM)this ) ;
	}
}

#ifdef	_DEBUG
// This is called to notify a blocked sender that the socket is unblocked
// now. Not required for retail operation.
void CClient::OnSend(int nErrorCode)
{
	CSocket::OnSend(nErrorCode);

	if ( theApp.m_bDebugOutput )
	{
		if ( m_cList.GetCount() == 0 )
		{
			m_pDoc->DbgMessage ( "OnSend:: No request yet.\n" ) ;
			return ;	// no request yet, keep reading
		}
		m_pDoc->DbgMessage ( "OnSend::Ready to send data.\n" ) ;
	}
}

// This is called when the client wants to abort the data download.
// Also not required for retail operation.
void CClient::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	m_pDoc->Message ( "OnClose::\n" ) ;
}
#endif	// _DEBUG
