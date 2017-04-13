// Welcome.cpp : implementation file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


#include "stdafx.h"
#include "API2Help.h"
#include "Welcome.h"
#include "options.h"
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcome dialog


CWelcome::CWelcome(CString strAPIFunc, CWnd* pParent /*=NULL*/)
	: CDialog(CWelcome::IDD, pParent)
{
	m_strSelected = strAPIFunc;
	//{{AFX_DATA_INIT(CWelcome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWelcome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcome)
	DDX_Control(pDX, IDC_SELECTED, m_Selected);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcome, CDialog)
	//{{AFX_MSG_MAP(CWelcome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcome message handlers

BOOL CWelcome::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strSelected2 = m_strSelected;
	for (int i = 0 ; i < strSelected2.GetLength() ; i++)
		if ((strSelected2.GetAt(i) == '\n') || (strSelected2.GetAt(i) == '\t') ||
				(strSelected2.GetAt(i) == '\r'))
		{
			strSelected2 = strSelected2.Left(i) +
					strSelected2.Right(strSelected2.GetLength()-i-1);
			i--;    //Because the character was removed, the next char
					//  Drops into it's place. But this character needs to
					//  be examined also, so we need to back up
		}
	m_Selected.SetWindowText(strSelected2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CWelcome::OnOK()
{
	COptions FileOpt(m_strSelected, this);
	FileOpt.DoModal();
	CDialog::OnOK();
}
