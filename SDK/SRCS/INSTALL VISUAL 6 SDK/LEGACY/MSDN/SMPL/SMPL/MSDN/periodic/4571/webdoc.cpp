/////////////////////////////////////////////////////////////////////////////
// WebDoc.cpp : implementation of the CWebDoc class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "Webster.h"

#include "WebDoc.h"
#include "WebView.h"

#include "clisten.h"
#include "cclient.h"

#if _MFC_VER < 0x0400
// for CSocket "dead socket" race condx in MFC 3.0
#include "afxpriv.h"	// WM_SOCKET_xxx
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebDoc

IMPLEMENT_DYNCREATE(CWebDoc, CDocument)

BEGIN_MESSAGE_MAP(CWebDoc, CDocument)
	//{{AFX_MSG_MAP(CWebDoc)
	ON_COMMAND(IDM_CLEAR_VIEW, OnClearView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebDoc construction/destruction

CWebDoc::CWebDoc()
{
	m_nLines = 0 ;
	m_nMaxLines = 100 ;
	m_strInfo.Empty() ;	// make sure we start off clean
}

CWebDoc::~CWebDoc()
{
}

BOOL CWebDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CString msg ;	// we use this a lot for MessageBox() messages
	GetFocus() ;	// For MessageBox() - frame window not init'ed yet

	// open log file
	OpenLogfile() ;

	// Create our one and only listener socket.
	// OnCloseDocument() takes care of deleting m_pSocket.
	m_pSocket = new CListen ( this ) ;
	if ( ! m_pSocket )
	{
		AfxMessageBox ( "Unable to allocate memory for listener socket!" ) ;
		return ( FALSE ) ;
	}

	if ( ! m_pSocket->Create ( theApp.m_wwwPort ) )
	{
		DWORD dwErr = m_pSocket->GetLastError() ;
		switch ( dwErr )
		{
			case WSAEADDRINUSE:	// example of expected error handler
				AfxMessageBox ( "The WWW port is already in use!" ) ;
				break ;

			default:					// example of generic error handler
				msg.Format ( "Listener socket Create failed: %s\n",
							  theApp.MapErrMsg(dwErr) ) ;
				AfxMessageBox ( msg ) ;
		}
		return ( FALSE ) ;
	}

	// start listening for requests and set running state
	BOOL ret = m_pSocket->Listen() ;
	if ( ret )
	{
		theApp.m_State = CWebApp::ST_WAITING ;
		msg.Format ( "Port: %d", theApp.m_wwwPort ) ;
		SetTitle ( msg ) ;
	}
	else
	{
		DWORD dwErr = m_pSocket->GetLastError() ;
		msg.Format ( "Listener socket Listen failed: %s\n",
					 theApp.MapErrMsg(dwErr) ) ;
		AfxMessageBox ( msg ) ;
	}
	return ( ret ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CWebDoc serialization

void CWebDoc::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// CWebDoc diagnostics

#ifdef _DEBUG
void CWebDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWebDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
//
// CWebDoc Operations
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Server handlers
void CWebDoc::OnAccept()
{
#if _MFC_VER < 0x0400
	// In order to fix the 'dead socket' race problem on Win95, we need to
	// make sure that all sockets that have been closed are indeed dead
	// before requesting a new one. This prevents reallocating a socket that
	// hasn't fully run down yet.
	// This is a feature of MFC prior to 4.0 and is no longer necessary
	// in subsequent versions.
	MSG msg ;
	while ( ::PeekMessage ( &msg, NULL,
							WM_SOCKET_NOTIFY, WM_SOCKET_DEAD,
							PM_REMOVE )	)
	{
		::DispatchMessage ( &msg ) ;
	}
#endif
	time_t tNow ;	// add time tag for MikeAh
	time( &tNow ) ;
	CTime cNow ( tNow ) ;
	Message ( cNow.Format ( "%m/%d/%y %H:%M:%S" ) ) ;
	Message ( " - Connection request:" ) ;

	// create a client object
	CClient *pClient = new CClient ( this ) ;
	if ( pClient == NULL )
	{
		Message ( ">> Unable to create client socket! <<\n" ) ;
		return ;
	}

	if ( ! m_pSocket->Accept ( *pClient ) )
	{
		Message ( ">> Unable to accept client connecton! <<\n" ) ;
		delete pClient ;
		return ;
	}
	pClient->ResolveClientName ( theApp.m_bResolveClientname ) ;

	// have we hit our resource limit?
	if ( m_listConnects.GetCount() >= (int)theApp.m_nMaxConnects )
	{
		// yes, send failure msg to client
		pClient->SendCannedMsg ( 503 ) ;
		delete pClient ;
		Message ( "  Connection rejected - MaxConnects\n" ) ;
		return ;
	}
	Message ( "  Connection accepted!!!\n" ) ;

	// add this client to our list
	m_listConnects.AddTail ( pClient ) ;

	// Service Agent has the 'tater now...

}	// OnAccept()

// This routine is called periodically from the MainFrame sanity timer
// handler. We're checking to see if any clients are loitering and, if so,
// clobber them.
void CWebDoc::CheckIdleConnects()
{
	// compute the age threshold
	time_t tNow ;
	time( &tNow ) ;
	CTime cNow ( tNow ) ;
	CTimeSpan cTimeOut ( 0, 0, 0, theApp.m_nTimeOut ) ;
	cNow -= cTimeOut ;	// anyone created before this time will get zapped

	DbgMessage ( "--- Checking for idle connections ---\n" ) ;
	for ( POSITION pos = m_listConnects.GetHeadPosition() ; pos != NULL ; )
	{
		CClient* pClient = (CClient*)m_listConnects.GetNext ( pos ) ;
		// anyone lanquishing in the list?
		if ( pClient->m_bDone )
		{
			KillSocket ( pClient ) ;
		}
		// anyone timed out?
		else if ( pClient->m_LogRec.datetime < cNow )
		{
			char msg[80] ;
			wsprintf ( msg, ">>> Idle timeout on client: %s\n", pClient->m_PeerIP ) ;
			Message ( msg ) ;
			KillSocket ( pClient ) ;
		}
	}
	// flush the log file buffer, while we're at it
	if ( theApp.m_bLogEnable && m_fileLog.is_open() )
		m_fileLog.flush() ;
}	// CheckIdleConnects()

// This routine is called from the MainFrame when a client has notified the
// aforementioned that it is done. Since the document owns the client
// objects, the document is responsible for cleaning up after it.
void CWebDoc::KillSocket ( CClient* pSocket )
{
	BOOL bFoundIt = FALSE ;
	// remove this client from the connection list
	for ( POSITION pos = m_listConnects.GetHeadPosition() ; pos != NULL ; )
	{
		POSITION temp = pos ;
		CClient* pSock = (CClient*)m_listConnects.GetNext ( pos ) ;
		if ( pSock == pSocket )
		{
			bFoundIt = TRUE ;
			m_listConnects.RemoveAt ( temp ) ;
//(dec)...debug...
// looking for cause of accvio when client cancels transfer
// AsyncSelect causes accvio after Send has failed
			if ( pSocket->AsyncSelect(0) == 0 )
				DWORD err = GetLastError() ;
			pSocket->Close() ;	//...debug...
//(dec)...end of debug...
			delete pSocket ;	// destructor calls Close()
			pSocket = NULL ;	// make sure its no longer accessible
			Message ( "  Connection closed.\n" ) ;
			break ;
		}
	}
	if ( ! bFoundIt )
	{
		DbgMessage ( ">> Uh oh! - Might have a sync problem.\n" ) ;
		DbgMessage ( ">> Couldn't find delete-pending socket in client list.\n" ) ;
	}
}	// KillSocket()


/////////////////////////////////////////////////////////////////////////////
// Logging handlers
void CWebDoc::OpenLogfile()
{
	// we may have just turned logging off, so check this before m_bLogEnable
	if ( m_fileLog.is_open() )
		m_fileLog.close() ;
	if ( ! theApp.m_bLogEnable )
		return ;

	// now try to open/create the file
	m_fileLog.open ( theApp.m_LogPath,
						  ios::ate,
						  filebuf::sh_read ) ;
}

void CWebDoc::WriteLog ( COMLOGREC& LogRec )
{
	if ( theApp.m_bLogEnable && m_fileLog.is_open() )
	{
		m_fileLog << LogRec.client << " "
					 << LogRec.inetd << " "
					 << LogRec.username << " ["
					 << LogRec.datetime.Format("%d/%b/%Y %H:%M:%S") << "] \""
					 << LogRec.request << "\" "
					 << LogRec.status << " "
					 << LogRec.bytes << "\n" ;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Status message handlers

void CWebDoc::Message ( LPCTSTR lpszMessage )
{
	if ( ! theApp.m_bShowStatus )
		return ;
	Message ( CString(lpszMessage) ) ;
}

void CWebDoc::Message ( CString cStr )
{
	if ( ! theApp.m_bShowStatus )
		return ;
	if ( cStr.GetLength() == 0 )
		return ;
	m_strInfo += cStr ;
	// This chunk of code unpacks the message string into individual lines.
	// The View window code is much simpler this way.
	BOOL bUpdate = FALSE ;
	int newline ;
	while ( ( newline = m_strInfo.Find ( "\n" ) ) >= 0 )
	{
		CString cTemp = m_strInfo.Left ( newline ) ;
		m_strInfo = m_strInfo.Right ( (m_strInfo.GetLength()-newline) - 1 ) ;

		// purge excess messages
		while ( m_strList.GetCount() >= m_nMaxLines )
			m_strList.RemoveHead() ;

		m_strList.AddTail ( cTemp ) ;
		bUpdate = TRUE ;
	}
	if ( bUpdate )	// update views if any lines were added
		UpdateAllViews ( NULL ) ;
}

void CWebDoc::DbgMessage ( LPCTSTR lpszMessage )
{
	if ( theApp.m_bDebugOutput )
		Message ( lpszMessage ) ;
}

void CWebDoc::DbgMessage ( CString cStr )
{
	if ( theApp.m_bDebugOutput )
		Message ( cStr ) ;
}

// We could use the var_arg form of these functions exclusively,
// but it's a little more efficient to only use these when we
// really need them.

void CWebDoc::VMessage ( LPCTSTR lpszFormat, ... )
{
	va_list	ptr ;
	char	buf[200] ;

	va_start ( ptr, lpszFormat ) ;
	wvsprintf ( buf, lpszFormat, ptr ) ; 
	Message ( buf ) ;
}

void CWebDoc::DbgVMessage ( LPCTSTR lpszFormat, ... )
{
	va_list	ptr ;
	char	buf[200] ;

	va_start ( ptr, lpszFormat ) ;
	wvsprintf ( buf, lpszFormat, ptr ) ; 
	DbgMessage ( buf ) ;
}


/////////////////////////////////////////////////////////////////////////////
// Class-Private handlers
void CWebDoc::SetTitle(LPCTSTR lpszTitle) 
{
	CString cTitle ;
	cTitle.Format ( "Listening on port: %d", theApp.m_wwwPort ) ;
	CDocument::SetTitle(cTitle);
}

/////////////////////////////////////////////////////////////////////////////
//
// End of CWebDoc Operations
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CWebDoc commands

void CWebDoc::OnCloseDocument() 
{
	// clobber everyone still connected
	for ( POSITION pos = m_listConnects.GetHeadPosition() ; pos != NULL ; )
	{
		CClient* pClient = (CClient*)m_listConnects.GetNext ( pos ) ;
		KillSocket ( pClient ) ;
	}

	delete m_pSocket ;	// release the listening socket

	// tidy up the log file
	if ( theApp.m_bLogEnable && m_fileLog.is_open() )
		m_fileLog.close() ;

	CDocument::OnCloseDocument();
}

void CWebDoc::OnClearView() 
{
	m_strList.RemoveAll() ;
	UpdateAllViews ( NULL, 0L, 0 ) ;
}

