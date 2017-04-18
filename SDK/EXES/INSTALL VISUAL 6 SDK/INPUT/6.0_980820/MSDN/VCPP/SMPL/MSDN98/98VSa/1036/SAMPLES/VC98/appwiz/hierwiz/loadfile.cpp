// loadfile.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "hierwiz.h"
#include "loadfile.h"
#include "hierwaw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLoadFileDlg dialog


CLoadFileDlg::CLoadFileDlg()
	: CAppWizStepDlg(CLoadFileDlg::IDD)
{
	//{{AFX_DATA_INIT(CLoadFileDlg)
	m_strProjName = _T("mfcclass.hie");
	//}}AFX_DATA_INIT
}


void CLoadFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadFileDlg)
	DDX_Text(pDX, IDC_PROJ_NAME, m_strProjName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadFileDlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CLoadFileDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLoadFileDlg message handlers

BOOL CLoadFileDlg::OnDismiss()
{
	UpdateData(TRUE);
	// If the user specifies no path, use the default
	if (m_strProjName.IsEmpty())
	{
		m_strProjName ="mfcclass.hie" ;
		UpdateData(FALSE) ;
	}
	hierwizaw.m_Dictionary.SetAt("hiersample",m_strProjName) ;
	return TRUE;
}

// Handle the "Browse..." button by popping up a file navigator.
void CLoadFileDlg::OnBrowse()
{
	CFileDialog dlg(
		TRUE,                                       // Open File Dialog
		_T("hie"),                                  // Default extension
		NULL,                                       // No default filename
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,     // OPENFILENAME flags
		_T("Hierserver Files|*.hie|All Files|*.*||"));  // Filter strings

	if (dlg.DoModal() == IDOK)
		m_strProjName = dlg.GetPathName();

	UpdateData(FALSE);
}
