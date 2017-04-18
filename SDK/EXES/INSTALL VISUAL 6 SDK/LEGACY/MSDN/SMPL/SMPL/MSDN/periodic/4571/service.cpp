/////////////////////////////////////////////////////////////////////////////
// Service.cpp : implementation of the CClient operations
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "cclient.h"
#include "webdoc.h"
#include "resource.h"	// IDS_ id's
#include "webster.h"	// CWebApp
#include "mainfrm.h"	// CMainFrame


// This routine collects the request from the client
BOOL CClient::ProcessPendingRead()
{
// Not all clients can send a block at a time (e.g., telnet). What we're
// doing here is constructing a buffer until we get either a cr/lf pair, or
// until dwBytes to read is zero.
//
// Note that since we've been called from the OnReceive notification
// handler, then if dwBytes is zero, it must mean the client has closed the
// connection.

	DWORD	dwBytes ;

	IOCtl ( FIONREAD, &dwBytes ) ;		// anything to get?
	if ( dwBytes == 0 )
		return ( TRUE ) ;	// we must be done!

	// allocate, or extend, our buffer - leave room for '\0' at end
	if ( m_irx == 0 )	// first time thru - malloc
		m_buf = (char *)malloc ( dwBytes+1 ) ;
	else				// otherwise - realloc
		m_buf = (char *)realloc ( m_buf, m_irx+dwBytes+1 ) ;
	// (so, like _when_ is C++ gonna support resizeable memory?)

	// get this chunk from the client
	if ( Receive ( &m_buf[m_irx], dwBytes, 0 ) == SOCKET_ERROR )
	{
		int err = GetLastError() ;
		if ( err == WSAECONNRESET )	// remote has terminated (gracefully)
		{
			m_pDoc->Message ( "WSAECONNERESET\n" ) ;
			return ( TRUE ) ;	// must be done!
		}
	}
	m_irx += dwBytes ;	// this much was added to our accumulating buffer

	// This is our socket equivalent of gets()
	// If we return FALSE, it means we need more input
	if ( m_irx < 2 )	 // enough to parse?
		return ( FALSE ) ;
	if ( memcmp ( &m_buf[m_irx-2], "\r\n", 2 ) != 0 )	// end of line?
		return ( FALSE ) ;

	// split this request up into the list of lines
	m_buf[m_irx] = '\0' ;	// Make this is an SZ string for parsing.
	char *pBOL = m_buf ;
	for ( char *pEOL = strpbrk ( pBOL, "\r" ) ;
			pEOL ;
			pEOL = strpbrk ( pBOL, "\r" ) )
	{
		*pEOL = '\0' ;	// make this chunk an SZ string
		m_cList.AddTail ( CString(pBOL,strlen(pBOL)) ) ; // add to list
		*pEOL++ ;		// skip '\0'
		*pEOL++ ;		// skip '\n'
		pBOL = pEOL ;	// point to next text
	}
	m_irx = 0 ;		// reset for next chunk from client
	free ( m_buf ) ;
	m_buf = NULL ;

	// are we in HTTP 1.0 mode yet?
	if ( ! m_bHTTP10 )
	{
		if ( m_cList.GetHead().Find ( "HTTP/1.0" ) != -1 )
			m_bHTTP10 = TRUE ;	// we are now...
		else
			return ( TRUE ) ;	// we must be done
	}

	// We are definitely in HTTP 1.0 mode now, so look for the terminating
	// empty line. Since we've already stripped off the cr/lf, the length
	// will be zero.
	return ( m_cList.GetTail().GetLength() == 0 ) ;
}	// ProcessPendingRead()

// This is a lookup table for translating the parsed method text string
// into a predefined token value. This token value will be used later
// to dispatch the request to an appropriate handler.
static struct CClient::_tagMethodTable MethodTable[] = {
	{ CClient::METHOD_GET   , "GET"    },
	{ CClient::METHOD_POST  , "POST"   },
	{ CClient::METHOD_HEAD  , "HEAD"   },
	{ CClient::METHOD_PUT   , "PUT"    },
	{ CClient::METHOD_DELETE, "DELETE" },
	{ CClient::METHOD_LINK  , "LINK"   },
	{ CClient::METHOD_UNLINK, "UNLINK" },
} ;
static const int MethodTableLen = sizeof(MethodTable)/
								  sizeof(struct CClient::_tagMethodTable) ;

void CClient::ParseReq()
{
	CStringList cList ;	// list of parsed command tokens

	// save the request line for our log record
	if ( m_cList.IsEmpty() )	// always check IsEmpty() first
	{
		m_pDoc->DbgVMessage ( "Command list is empty!\nSending 400 error\n" ) ;
		SendCannedMsg ( 400 ) ;
		return ;
	}
	CString cReq = m_cList.GetHead() ;
	m_LogRec.request = cReq ;

	/////////////////////////////////////////////////////////////////////////////
	// parse the primary, and most important, request line

	// parse the request line into a list of tokens
	LPSTR tempmsg = new char[cReq.GetLength()+1] ;	// allow for EOS
	strcpy ( tempmsg, cReq ) ;
	char *pBOL = tempmsg ;
	for ( char *pEOL = strpbrk ( pBOL, " " ) ;
		  pEOL ;
		  pEOL = strpbrk ( pBOL, " " ) )
	{
		*pEOL = '\0' ;
		CString tempToken ( pBOL, strlen(pBOL) ) ;
		*pEOL++ ;	// skip '\0'
		pBOL = pEOL ;
		cList.AddTail ( tempToken ) ;
	}
	// save whatever's left as the last token
	CString tempToken ( pBOL, strlen(pBOL) ) ;
	cList.AddTail ( tempToken ) ;
	delete tempmsg ;

	POSITION pos = cList.GetHeadPosition() ;	// prepare to scan the request

	// 1) parse the method
	if ( pos == NULL )
	{
		m_pDoc->DbgVMessage ( "Null request method\nSending 400 error\n" ) ;
		SendCannedMsg ( 400 ) ;
		return ;		
	}
	m_cURI = cList.GetNext ( pos ) ;	// pointing to METHOD now
	for ( int i = 0 ; i < MethodTableLen ; i++ )
	{
		if ( m_cURI.CompareNoCase ( MethodTable[i].key ) == 0 )
		{
			m_nMethod = MethodTable[i].id ;
			break ;
		}
	}

	// 2) parse the URI
	if ( pos == NULL )
	{
		m_pDoc->DbgVMessage ( "Null request URI\nSending 400 error\n" ) ;
		SendCannedMsg ( 400 ) ;
		return ;		
	}
	m_cURI = cList.GetNext ( pos ) ;	// pointing to ENTITY now
	m_pDoc->VMessage ( "   Data request: %s\n", m_cURI ) ;

	// replace UNIX '/' with MS '\'
	for ( i = 0 ; i < m_cURI.GetLength() ; i++ )
	{
		if ( m_cURI[i] == '/' )
			m_cURI.SetAt ( i, '\\' ) ;
	}

	// add base path
	if ( m_cURI[0] != '\\' )
		m_cLocalFNA = theApp.m_HTMLPath + CString("\\") + m_cURI ;
	else
		m_cLocalFNA = theApp.m_HTMLPath + m_cURI ;

	// This is a real ugly little hack for MikeAh to use forms/GET
	// I just snarf the rest of the command line from the query
	// separator on...
	if ( ( i = m_cLocalFNA.Find ( '?' ) ) != -1 )
		m_cLocalFNA.GetBufferSetLength ( i ) ;


	// 3) parse the rest of the request lines
	if ( ! m_bHTTP10 )
		return ;	// if HTTP 0.9, we're done!

	// parse the client's capabilities here...
	if ( theApp.m_bDebugOutput )
	{
		POSITION pos = m_cList.GetHeadPosition() ;
		for ( int i = 0 ; i < m_cList.GetCount() ; i++ )
		{
			// For now, we'll just have a boo at them. Being such a simple
			// server, let's not get too concerned with details.
			m_pDoc->DbgVMessage ( "   %d>%s\n", i+1, m_cList.GetNext ( pos ) ) ;
		}
	}
}	// ParseReq()


/////////////////////////////////////////////////////////////////////////////
// dispatch service handler

void CClient::ProcessReq()
{
	// parse the request
	ParseReq() ;

	// can only handle GETs for now
	if ( m_nMethod != METHOD_GET )
	{
		m_pDoc->VMessage ( "   Unknown method requested: %s\n", m_cURI ) ;
		SendCannedMsg ( 405, m_cURI ) ;
		return ;
	}

	// try to determine the send method based on the file type
	char *ext = strrchr ( m_cLocalFNA, '.' ) ;
	if (  m_cURI == "\\" )		// blind request?
	{
		m_pDoc->DbgVMessage ( "   Blind request\n" ) ;
		if ( ! SendFile ( m_cLocalFNA, m_cURI ) )
			return ;	// send failure!
	}
	else if ( ext )				// has an extension?
	{
		*ext++ ;	// point to start of file extension
		m_pDoc->DbgVMessage ( "   File extension: <%s>\n", ext ) ;
		if ( ! SendFile ( m_cLocalFNA, m_cURI ) )
			return ;	// send failure!
	}
	else	// must be a CGI script specification
	{
		m_pDoc->DbgVMessage ( "   CGI request: %s %s\n", m_cLocalFNA, m_cURI ) ;
		if ( ! SendCGI ( m_cLocalFNA, m_cURI ) )
		{
			// ...insert CGI-implementation dependant actions here...
			return ;
		}
	}
	SendTag() ;	// Done!!!
}	// ProcessReq()


/////////////////////////////////////////////////////////////////////////////
// CClient Service Response Operations

// this is the built-in list of MIME types we automatically recognize
static struct _tagMIME_Table
{
	char	*ext ;
	char	*type ;
} MIME_Table[] = {
	{ ".gif" , "image/gif"  },
	{ ".jpg" , "image/jpg"  },
	{ ".htm" , "text/html"  },
	{ ".html", "text/html"  },
	{ ".txt" , "text/plain" }
} ;
static const int MIME_len = sizeof(MIME_Table)
									/ sizeof(struct _tagMIME_Table) ;


BOOL CClient::SendReplyHeader ( CFile& cFile )
{
	if ( ! m_bHTTP10 )	// if HTTP 0.9, response header not used
		return ( TRUE ) ;

	// Response header components:
	// 1 - HTTP 1.0 response header
	// 2 - Server time
	// 3 - Server version
	// 4 - MIME version
	// 5 - MIME type
	// 6 - Last-modified time
	// 7 - Content length
	// 8 - HTTP 1.0 End-of-header

	CString	tmp ;
	// 1
	if ( ! SendData ( "HTTP/1.0 200 OK\r\n" ) )
		return ( FALSE ) ;	// skate from here...
	// 2
	CTime rTime = CTime::GetCurrentTime() ;
	tmp.Format ( "Date: %s\r\n",
				rTime.FormatGmt("%a, %d %b %Y %H:%M:%S %Z") ) ;
	SendData ( tmp ) ;
	// 3
	SendData ( "Server: Webster/1.0\r\n" ) ;
	// 4
	SendData ( "MIME-version: 1.0\r\n" ) ;
	// 5
	char ext[5] ;
	_splitpath ( cFile.GetFileName(), NULL, NULL, NULL, ext ) ;
	tmp = ext ;
	for ( int i = 0 ; i < MIME_len ; i++ )
	{
		if ( tmp.CompareNoCase ( MIME_Table[i].ext ) == 0 )
		{
			SendData ( "Content-type: " ) ;
			SendData ( MIME_Table[i].type ) ;
			SendData ( "\r\n" ) ;
			break ;
		}
	}
	// 6
	CFileStatus rStatus ;
	if ( cFile.GetStatus ( rStatus ) )
	{
		tmp.Format ( "Last-modified: %s\r\n",
					rStatus.m_mtime.FormatGmt("%a, %d %b %Y %H:%M:%S %Z") ) ;
		SendData ( tmp ) ;
	}
	// 7
	tmp.Format ( "Content-length: %d\r\n", cFile.GetLength() ) ;
	SendData ( tmp ) ;
	// 8
	SendData ( "\r\n" ) ;	// end-of-header
	return ( TRUE ) ;
}	// SendReplyHeader()

void CClient::SendTag()
{
	// send our personalized message
	CString tagmsg ;
	BOOL ret = TRUE ;
	switch ( theApp.m_nTagType )
	{
		case CWebApp::TAG_AUTO:
			tagmsg.LoadString ( IDS_TAGSTRING ) ;
			ret = SendData ( tagmsg ) ;
			m_pDoc->Message ( " Sent auto tag\n" ) ;
			break ;
		case CWebApp::TAG_FILE:
			tagmsg = theApp.m_HTMLPath + CString("\\") + theApp.m_HTMLTag ;
			ret = SendFile ( tagmsg, theApp.m_HTMLTag, TRUE ) ;
			break ;
		case CWebApp::TAG_NONE:
			m_pDoc->Message ( " No tag\n" ) ;
			break ;
	}
	tagmsg.LoadString ( IDS_TAGCOMMENT ) ;
	if ( ret )
		SendData ( tagmsg ) ;
}	// SendTag()

/////////////////////////////////////////////////////////////////////////////
// URI file handler

BOOL CClient::SendFile ( CString& m_cLocalFNA, CString& BaseFNA,
								 BOOL bTagMsg )
{
	CFile cFile ;
	BOOL FoundIt ;

	// if our request isn't empty, then try to open the file specified
	if ( m_cLocalFNA != theApp.m_HTMLPath + CString("\\") )
	{
		m_pDoc->DbgVMessage ( "Attempting to open: %s\n", m_cLocalFNA ) ;
		FoundIt = cFile.Open ( m_cLocalFNA,
									  CFile::modeRead | CFile::typeBinary ) ;
	}
	else	// otherwise, it was a blind access. send the default file
	{
		m_pDoc->DbgMessage ( "Blank request, trying Default - " ) ;
		m_cLocalFNA = theApp.m_HTMLPath
						+ CString("\\")
						+ theApp.m_HTMLDefault ;
		FoundIt = cFile.Open ( m_cLocalFNA,
							   CFile::modeRead | CFile::typeBinary ) ;
		// if our configuration settings are hosed, use emergency plan 'B'
		if ( ! FoundIt )
		{
			m_pDoc->DbgVMessage ( "Couldn't find: %s\nTrying Bogus - ",
									m_cLocalFNA ) ;
			m_cLocalFNA = theApp.m_HTMLPath + CString("\\")
							+ theApp.m_HTMLBogus ;
			FoundIt = cFile.Open ( m_cLocalFNA,
										  CFile::modeRead | CFile::typeBinary ) ;
		}
	}
	if ( ! FoundIt )
	{
		m_pDoc->DbgVMessage ( "Couldn't find: %s\nSending 404 error\n",
								m_cLocalFNA ) ;
		SendCannedMsg ( 404, BaseFNA ) ;
		return ( TRUE ) ;;
	}
	m_pDoc->DbgMessage ( "\n" ) ;	// make debug msg readable

	// we found a file, so send it already...
	m_pDoc->VMessage ( "   Sending: %s\n", m_cLocalFNA ) ;
	BOOL ret = TRUE ;
	if ( ! bTagMsg )	// if tag message, skip the response header
		ret = SendReplyHeader ( cFile ) ;
	if ( ret )
		ret = SendData ( cFile ) ;
	cFile.Close() ;
	return ( ret ) ;
}	// SendFile()

/////////////////////////////////////////////////////////////////////////////
// CGI handler

BOOL CClient::SendCGI ( CString& m_cLocalFNA, CString& BaseFNA )
{
	// This is a hook for future development. Just send 404 error for now.
	SendCannedMsg ( 404, BaseFNA ) ;
	return ( TRUE ) ;
}

/////////////////////////////////////////////////////////////////////////////
// Data transmission operations

// this is for sending our own info and messages to the client
BOOL CClient::SendRawData ( LPVOID lpMessage, int count )
{
	// Use a CSocketFile for pumping the message out
	CSocketFile sockFile ( this, FALSE ) ;
	TRY
	{
		sockFile.Write ( lpMessage, count ) ;
	}
	CATCH(CFileException, e)
	{
		m_pDoc->VMessage ( "Failed to write raw to client socket!\n" ) ;
		m_pDoc->VMessage ( "   >>> %s\n", theApp.MapErrMsg(GetLastError()) ) ;
		return ( FALSE ) ;;
	}
	END_TRY
	sockFile.Flush() ;
	return ( TRUE ) ;
}

// this is for sending a CString message to the client
BOOL CClient::SendData ( CString& cMessage )
{
	return ( SendData ( (LPCTSTR)cMessage ) ) ;
}

// this is for sending a LPSTR message to the client
BOOL CClient::SendData ( LPCSTR lpszMessage )
{
	m_pDoc->DbgVMessage ( ">>>Sending client message: %s\n", lpszMessage ) ;
	return ( SendRawData ( (LPVOID)lpszMessage, strlen(lpszMessage) ) ) ;
}

// this is for sending file data to the client
#define	BUF_SIZE	4096	// same as default for CSocket as CArchive

BOOL CClient::SendData ( CFile& cFile )
{
	char	buf[BUF_SIZE] ;
	int		nBytes ;

	// Use a CSocketFile for pumping the data out
	CSocketFile sockFile ( this, FALSE ) ;
	while ( ( nBytes = cFile.Read ( buf, BUF_SIZE ) ) > 0 )
	{
		TRY
		{
			sockFile.Write ( (LPVOID)buf, nBytes ) ;
			m_LogRec.bytes += nBytes ;
		}
		CATCH(CFileException, e)
		{
			m_pDoc->VMessage ( "Failed to write data to client socket!\n%s\n",
										theApp.MapErrMsg(GetLastError()) ) ;
			return ( FALSE ) ;
		}
		END_TRY
	}
	sockFile.Flush() ;
	return ( TRUE ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CClient Utility Operations

BOOL CClient::ResolveClientName ( BOOL bUseDNS )
{
	if ( ! GetPeerName ( m_PeerIP, m_Port ) )
	{
		m_pDoc->Message ( " Can't get client name\n" ) ;
		return ( FALSE ) ;
	}
	m_LogRec.client = m_PeerIP ;

	if ( bUseDNS )
	{
		if ( m_PeerIP == "127.0.0.1" )	// hey, it's me!!!
		{
			m_LogRec.client = "Local loopback" ;
			m_pDoc->VMessage ( " Local loopback (%s)\n", m_PeerIP ) ;
		}
		else
		{
			if ( m_pHE = GetHostByAddr ( (LPCSTR)m_PeerIP ) )
			{
				m_LogRec.client = m_pHE->h_name ;
				m_pDoc->VMessage ( " %s (%s)\n", m_pHE->h_name, m_PeerIP ) ;
			}
			else
			{
				int err = WSAGetLastError() ;
				m_pDoc->VMessage ( " Unable to get host name: %s. Err: %d\n",
											m_PeerIP, err ) ;
				return ( FALSE ) ;
			}
		}
	}
	else
	{
		m_pDoc->VMessage ( " %s\n", m_PeerIP ) ;
	}
	return ( TRUE ) ;
}

//
//	The following code is used for sending predefined messages.
//

// table of canned messages that we can handle
static struct _tagMsgTable
{
	int	id ;
	int	idStr ;
} MsgTable[] =
{
	{ 400, IDS_400_MESSAGE },
	{ 404, IDS_404_MESSAGE },
	{ 405, IDS_405_MESSAGE },
	{ 503, IDS_503_MESSAGE }
} ;
static const int MsgTableSize = sizeof(MsgTable)
										  / sizeof(struct _tagMsgTable) ;

void CClient::SendCannedMsg ( int idErr, ... )
{
	BOOL bGotIt = FALSE ;
	for ( int i = 0 ; i < MsgTableSize ; i++ )
	{
		if ( MsgTable[i].id == idErr )
		{
			bGotIt = TRUE ;
			break ;
		}
	}

	CString fmt ;
	char	buf[200] ;
	if ( ! bGotIt )	// idErr is a bogus code!
	{
		fmt.LoadString ( IDS_500_MESSAGE ) ;
		wsprintf ( buf, fmt, idErr ) ;
	}
	else
	{
		fmt.LoadString ( MsgTable[i].idStr ) ;
		va_list	ptr ;
		va_start ( ptr, idErr ) ;
		wvsprintf ( buf, fmt, ptr ) ; 
	}
	Send ( buf, strlen(buf), 0 ) ;

	// write log record
 	m_LogRec.status = idErr ;
	if ( theApp.m_bLogEnable )
		m_pDoc->WriteLog ( m_LogRec ) ;

	// write status message
	m_pDoc->DbgVMessage ( "   Sent %03d status message to client\n", idErr ) ;
}
