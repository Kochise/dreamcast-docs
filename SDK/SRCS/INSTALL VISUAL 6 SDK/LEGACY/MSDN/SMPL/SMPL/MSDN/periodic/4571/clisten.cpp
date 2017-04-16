/////////////////////////////////////////////////////////////////////////////
// CListen.cpp : implementation of the CListener class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "stdafx.h"
#include "clisten.h"
#include "webdoc.h"

CListen::CListen(CWebDoc* pDoc)
{
	m_pDoc = pDoc ;	// save doc pointer for later use
}

/////////////////////////////////////////////////////////////////////////////
// CListen Overridable callbacks

void CListen::OnAccept(int nErrorCode)
{
	CSocket::OnAccept(nErrorCode);
	m_pDoc->OnAccept() ;	// process this in the context of the document
}

/////////////////////////////////////////////////////////////////////////////
// CListen Implementation

CListen::~CListen()
{
}

#ifdef _DEBUG
void CListen::AssertValid() const
{
	CSocket::AssertValid();
}

void CListen::Dump(CDumpContext& dc) const
{
	CSocket::Dump(dc);
}
#endif //_DEBUG

IMPLEMENT_DYNAMIC(CListen, CSocket)
