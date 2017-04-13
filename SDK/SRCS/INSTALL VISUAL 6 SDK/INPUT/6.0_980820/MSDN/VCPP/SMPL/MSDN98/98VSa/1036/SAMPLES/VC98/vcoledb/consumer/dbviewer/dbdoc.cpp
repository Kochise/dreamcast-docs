// DBDoc.cpp : implementation of the CDBViewDoc class
//
// This is a part of the Microsoft Foundation Classes and
// Templates (MFC&T).
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// MFC&T Reference and related electronic documentation provided
// with the library.  See these sources for detailed information
// regarding the MFC&T product.
//

#include "stdafx.h"
#include "DBViewer.h"

#include "DBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBViewDoc

IMPLEMENT_DYNCREATE(CDBViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBViewDoc, CDocument)
	//{{AFX_MSG_MAP(CDBViewDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBViewDoc construction/destruction

CDBViewDoc::CDBViewDoc()
{
	m_pListView = NULL;
	m_pTreeView = NULL;
}

CDBViewDoc::~CDBViewDoc()
{
	m_pListView = NULL;
	m_pTreeView = NULL;
}

BOOL CDBViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDBViewDoc serialization

void CDBViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBViewDoc diagnostics

#ifdef _DEBUG
void CDBViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBViewDoc commands

void CDBViewDoc::RefreshViews()
{
	if (m_pListView)
		m_pListView->EraseList();

	if (m_pTreeView)
		m_pTreeView->PopulateTree();
}

BOOL CDBViewDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (m_Session.m_spOpenRowset != NULL)
		m_Session.m_spOpenRowset.Release();

	m_strConnect = _T("");

	if (m_Connect.Open(AfxGetMainWnd()->GetSafeHwnd()) != S_OK)
	{
		AfxMessageBox(_T("Unable to connect to data source"));
		return FALSE;
	}
	else
	{
		USES_CONVERSION;

		if (m_Session.Open(m_Connect) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			return FALSE;
		}

		CComVariant var;
		m_Connect.GetProperty(DBPROPSET_DATASOURCEINFO, DBPROP_DATASOURCENAME, &var);
		m_strConnect = OLE2T(var.bstrVal);

		m_pTreeView->m_pSession = &m_Session;
		m_pListView->m_pSession = &m_Session;
		RefreshViews();
		return TRUE;
	}

	return FALSE;
}

CString CDBViewDoc::GetDSN()
{
	// pull DSN from database connect string
	CString string = m_strConnect;
//  string = string.Right(string.GetLength() - (string.Find(_T("DSN=")) + 4));
//  string = string.Left(string.Find(_T(";")));
	return string;
}

CString CDBViewDoc::GetConnect()
{
	return m_strConnect;
}

void CDBViewDoc::OnFileOpen()
{
	OnOpenDocument(NULL);
}

CDataSource* CDBViewDoc::GetDataSource()
{
	return &m_Connect;

}
