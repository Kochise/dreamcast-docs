/////////////////////////////////////////////////////////////////////////////
// CClient.h : interface of the CClient class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#ifndef __CCLIENT_H__
#define __CCLIENT_H__

#include "logger.h"		// COMLOGREC

class CWebDoc;

class CClient : public CSocket
{
	DECLARE_DYNAMIC(CClient);
private:
	CClient(const CClient& rSrc);	// no implementation
	void operator=(const CClient& rSrc);	// no implementation

// Construction
public:
	CClient(CWebDoc* m_pDoc);

// Attributes
public:
	// These are used for providing the HTTP service
	CWebDoc*			m_pDoc ;			// we use this quite a bit
	BOOL				m_bDone ;		// set when we're done
	CString			m_PeerIP ;		// requestor's IP address
	UINT				m_Port ;			// port we're connected to
	struct hostent*	m_pHE ;		// for resolving client name
	CString			m_PeerName ;	// resolved client name
	COMLOGREC		m_LogRec ;		// Common Log Format log record

	// These are used for servicing the request
	char				*m_buf ;			// current receive buffer
	DWORD				m_irx ;			// index into receive buffer
	CStringList		m_cList ;		// list of request strings
	BOOL				m_bHTTP10 ;		// HTTP 1.0 format?
 	CString			m_cURI ;			// requested file name
 	CString			m_cLocalFNA ;	// constructed (local) file name
	enum METHOD_TYPE					// the HTML request methods
	{
		METHOD_UNSUPPORTED = 0,
		METHOD_GET,
		METHOD_POST,
		METHOD_HEAD,
		METHOD_PUT,
		METHOD_DELETE,
		METHOD_LINK,
		METHOD_UNLINK
	} m_nMethod ;
	struct _tagMethodTable
	{
		enum METHOD_TYPE	id ;
		char					*key ;
	} ;
	
	// service stuff
	CSocketFile*	m_pFile ;		// socket file for reply


// Operations
public:
	///////////////////////////////////////////////////////////
	// ClntOps.Cpp module operations

	// service handling operations
	BOOL ProcessPendingRead() ;
	void ParseReq() ;
	void ProcessReq() ;
	BOOL SendReplyHeader ( CFile& cFile ) ;
	void SendTag() ;

	// service response
	BOOL SendFile ( CString& SendFNA, CString& BaseFNA,
						 BOOL bTagMsg = FALSE ) ;
	BOOL SendCGI ( CString& SendFNA, CString& BaseFNA ) ;

	// send-to-client
	BOOL SendRawData ( LPVOID lpszMessage, int count ) ;
	BOOL SendData ( LPCSTR lpszMessage ) ;
	BOOL SendData ( CString& cMessage ) ;
	BOOL SendData ( CFile& cFile ) ;

	// misc utilities
	BOOL ResolveClientName ( BOOL bUseDNS ) ;
	void SendCannedMsg ( int idErr, ... ) ;
	inline struct hostent* GetHostByAddr ( LPCSTR lpszIP )
	{
		// translate dotted string format into integer
		int uPeer[4] ;
		sscanf ( lpszIP, "%d.%d.%d.%d",
				 &uPeer[0], &uPeer[1], &uPeer[2], &uPeer[3] ) ;

		// move it into a char array for ::gethostbyaddr()
		char cPeer[4] ;
		cPeer[0] = uPeer[0] ;
		cPeer[1] = uPeer[1] ;
		cPeer[2] = uPeer[2] ;
		cPeer[3] = uPeer[3] ;
		return ( ::gethostbyaddr ( cPeer, 4, PF_INET ) ) ;
	}



// Overridable callbacks
protected:
	virtual void OnReceive(int nErrorCode);
#ifdef	_DEBUG
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
#endif

// Implementation
public:
	virtual ~CClient();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif // __CCLIENT_H__
