// DSNDlg.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "MDIBind.h"
#include "DSNDlg.h"
#include <sqlext.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSrcDlg dialog


CDataSrcDlg::CDataSrcDlg(CString &DSN,CString &Sql,CString &User,CString &Pw,
						 CWnd* pParent /*=NULL*/)
	: CDialog(CDataSrcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataSrcDlg)
	m_DSN = DSN;
	m_User = User;
	m_Sql = Sql;
	m_Pw = Pw;
	//}}AFX_DATA_INIT
}


void CDataSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataSrcDlg)
	DDX_Text(pDX, IDC_DATASRC, m_DSN);
	DDX_Text(pDX, IDC_USER, m_User);
	DDX_Text(pDX, IDC_SQL, m_Sql);
	DDX_Text(pDX, IDC_PASWORD, m_Pw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataSrcDlg, CDialog)
	//{{AFX_MSG_MAP(CDataSrcDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataSrcDlg message handlers

BOOL CDataSrcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	HENV henv;
	RETCODE nRetCode;
	SWORD cbName = -1;
	SWORD cbDescription = -1;
#ifdef _UNICODE
	TCHAR szName[SQL_MAX_DSN_LENGTH + 256]; //safety
	TCHAR szDesc[512+1]; //enough
	TCHAR *comboName=szName;
#else
	UCHAR szName[SQL_MAX_DSN_LENGTH + 256]; //safety
	UCHAR szDesc[512+1]; //enough
	char *comboName=(char *)szName;
#endif

	CComboBox* pCombo = (CComboBox*) GetDlgItem(IDC_DATASRC);

	// Only returns SQL_SUCCESS or SQL_ERROR, Can assume errors mem alloc errors
	if(SQLAllocEnv(&henv) != SQL_SUCCESS)
	{
		AfxMessageBox(_T("ODBC error"));
		return TRUE;
	}
	do
	{
		nRetCode = ::SQLDataSources(henv, SQL_FETCH_NEXT,
			szName, SQL_MAX_DSN_LENGTH, &cbName,
			szDesc, 512, &cbDescription);
		if(nRetCode != SQL_SUCCESS && nRetCode != SQL_SUCCESS_WITH_INFO)
			break;
		szName[cbName] = '\0';
		pCombo->AddString(comboName);
	}while(1);

	if(nRetCode == SQL_ERROR)
		AfxMessageBox(_T("Data Source Retrieve error"));
	nRetCode = SQLFreeEnv(henv);
	if(nRetCode == SQL_ERROR)
		AfxMessageBox(_T("ODBC error"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
