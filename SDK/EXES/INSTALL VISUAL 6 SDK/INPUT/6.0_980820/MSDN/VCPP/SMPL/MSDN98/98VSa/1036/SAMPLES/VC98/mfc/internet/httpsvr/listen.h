// Listen.h : interface of the CListenSocket class
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

class CHttpSvrDoc;

class CListenSocket : public CAsyncSocket
{
	DECLARE_DYNCREATE(CListenSocket)
	CListenSocket( void );
public:
	CListenSocket( CHttpSvrDoc* pDoc );
protected:
	CHttpSvrDoc* m_pDoc;
	virtual void OnAccept( int nErrorCode );
};
