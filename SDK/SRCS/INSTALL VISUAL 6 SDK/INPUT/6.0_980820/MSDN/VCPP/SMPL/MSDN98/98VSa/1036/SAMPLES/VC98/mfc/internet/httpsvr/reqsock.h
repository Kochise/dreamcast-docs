// ReqSock.h : interface of the CRequestSocket class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1997-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#define MAX_DIR_FILENAME    24
class CRequest;
class CHttpSvrDoc;

class CRequestSocket : public CAsyncSocket
{
	DECLARE_DYNCREATE(CRequestSocket)
	CRequestSocket( void );

protected:
	void StuffFileType( void );
	BOOL m_bKeepOpen;
	BOOL m_bWantKeepOpen;
	enum REQSTATUS
	{
		REQ_REQUEST=0, REQ_HEADER, REQ_BODY, REQ_SIMPLE, REQ_DONE
	};

	CRequest*   m_pRequest; // request object

	CByteArray  m_buf;
	int         m_cbOut;
	CString     m_strLine;
	REQSTATUS   m_reqStatus;
	HANDLE      m_hFile;
	int         m_nRefs;
	BOOL        m_bKilled;

public:
	CHttpSvrDoc* m_pDoc;
	BOOL CheckExt( const CString& strExt, CString& strAvail, DWORD dwType );
	BOOL IsSvrApp( void );
	BOOL CheckDefault( UINT uList, BOOL bExecute );
	CString StripLast( CString& strPath );
	int StuffStatus( const CString& strStatus );
	CRequestSocket( CHttpSvrDoc* pDoc );
	~CRequestSocket( void );
	virtual int AddRef( void );
	virtual int Release( void );

#ifdef IMPL_CGI
	BOOL        CGIStart( void );
	void        CGIDone( void );
	CWinThread* m_pThread;
	CEvent*     m_pCancel;
#endif // IMPL_CGI

protected:
	BOOL StartSvrApp( void );
	BOOL FromHttpTime( const CString& strHttp, CTime& timeHttp );
	BOOL IfModSince( const CTime& timeIfMod );
	CString GetHttpDate( LPFILETIME pft = NULL );
	BOOL GetLine( const CByteArray& bytes, int nBytes, int& ndx );
	void ProcessLine( void );
	BOOL BodySent( void );
	void AddToBody( int nBytes, int ndx );
	BOOL StartResponse( void );
	BOOL FindTarget( CString& strFile );
	BOOL URLtoPath( CString& strFile );
	BOOL PathToURL( CString& strFile );
	BOOL StuffHeading( void );
	void StartTargetStuff( void );

	int StuffString( const CString& );
	int StuffString( UINT uId );
	int StuffStatus( UINT uMsg );
	int StuffError( UINT uMsg );
	int StuffHeader( CString strName, CString strValue );
	int StuffHeader( CString strName, int nValue );

	// methods not supported by Mac version....
	void StuffListing( void );
	int  StuffListingFile( WIN32_FIND_DATA* fd, const CString& strDir, BOOL bIcons );

protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	friend UINT CGIThread( LPVOID );
};

CString Decode( const CString& str, BOOL bQuery = FALSE );

#ifdef IMPL_CGI
void HeaderToEnvVar( CString& strVar );

class CEnvironment
{
public:
	CStringList m_list;
	int         m_nSize;

	CEnvironment( void );
	~CEnvironment( void );
	BOOL Add( CString name, CString value );
	LPVOID GetBlock( void );
};
#endif
