// editdlg.cpp : implementation file
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
#include "editdlg.h"
#include "hierwaw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg()
	: CAppWizStepDlg(CEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_SampleTxt = _T("");
	//}}AFX_DATA_INIT
}


//DDX_Control(pDX, IDC_SAMPLETXT, m_EditCtrl);

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Text(pDX, IDC_SAMPLETXT, m_SampleTxt);
	//}}AFX_DATA_MAP
}

BOOL CEditDlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;
	if ((m_SampleTxt.IsEmpty())== 0)
	{
		hierwizaw.m_Dictionary.SetAt("USER_INPUT_DATA",m_SampleTxt) ;
		hierwizaw.m_Dictionary.RemoveKey("NO_INPUT_DATA") ;
	}
	else
	{
		CString strNoTxt;
		strNoTxt.LoadString(IDS_NOSAMPLETXT) ;
		if(IDNO == (AfxMessageBox(strNoTxt,MB_YESNO)))
		{
			return FALSE ;
		}
		else
		{
			// No text data is entered.
			hierwizaw.m_Dictionary.RemoveKey("USER_INPUT_DATA") ;
			hierwizaw.m_Dictionary.SetAt("NO_INPUT_DATA","YES") ;
		}
	}
	return TRUE;    // return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers


BOOL CEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	VERIFY(m_EditData.SubclassDlgItem(IDC_SAMPLETXT,this)) ;
	m_EditData.SetTabStops(10) ;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
