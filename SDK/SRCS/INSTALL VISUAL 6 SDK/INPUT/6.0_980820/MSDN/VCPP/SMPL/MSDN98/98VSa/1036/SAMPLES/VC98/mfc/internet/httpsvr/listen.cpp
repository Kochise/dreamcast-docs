// Listen.cpp : implementation of the CListSocket class
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

#include "stdafx.h"
#include "Listen.h"
#include "ReqSock.h"
#include "HttpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CListenSocket, CAsyncSocket)

CListenSocket::CListenSocket( void )
{
	m_pDoc = NULL;
}

CListenSocket::CListenSocket( CHttpSvrDoc* pDoc )
{
	m_pDoc = pDoc;
}

void CListenSocket::OnAccept( int nErrorCode )
{
	CRequestSocket* pRequest = new CRequestSocket( m_pDoc );
	if ( Accept( *pRequest ) )
	{
		pRequest->AsyncSelect( FD_READ|FD_CLOSE );
	}
}
