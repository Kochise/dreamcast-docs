// Http.h : structures, functions and definitions for http service
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

class CRequest;

class CHitDoc : public CObject
{
protected: // create from serialization only
	CHitDoc();
	DECLARE_DYNCREATE(CHitDoc)

	void ParseFileName( const CString& strFullPath );
public:
	CHitDoc( CString strFile );
	CHitDoc( CRequest* pRequest );
	int operator==( CHitDoc* pHit );

public:
	CString     m_strFile;
	CString     m_strFolder;
	CString     m_strCommand;
	CString     m_strURL;
	CTime       m_timeLastHit;
	BOOL        m_bFolder;
	DWORD       m_dwExecute;
	int         m_nHits;
	int         m_nStatus;
};
