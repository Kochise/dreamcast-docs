// pressdlg.cpp : implementation file
//
// This class looks a whole lot like the one in MFC sample ctrltest
// with a few name changes.  It is included here as an example of
// how to add additional classes during app creation from a custom
// AppWizard.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "resource.h"
#include "pressdlg.h"

BEGIN_MESSAGE_MAP(CPressMeDlg, CDialog)
	//{{AFX_MSG_MAP(CPressMeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPressMeDlg::CPressMeDlg()
	: CDialog(CPressMeDlg::IDD)
{
	if (!m_buttonOk.LoadBitmaps(IDB_SMILE_UP, IDB_SMILE_DOWN, IDB_SMILE_FOCUS) ||
		!m_buttonCancel.LoadBitmaps(IDB_FROWN_UP, IDB_FROWN_DOWN, IDB_FROWN_FOCUS))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}
}

BOOL CPressMeDlg::OnInitDialog()
{
	// each dialog control has special bitmaps
	VERIFY(m_buttonOk.SubclassDlgItem(IDOK, this));
	m_buttonOk.SizeToContent();
	VERIFY(m_buttonCancel.SubclassDlgItem(IDCANCEL, this));
	m_buttonCancel.SizeToContent();

	return TRUE;
}
