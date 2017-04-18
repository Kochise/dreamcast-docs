// Int2.cpp : implementation file
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
#include "Wizard97.h"
#include "Int2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Interior2 property page

IMPLEMENT_DYNCREATE(CInterior2, CPropertyPageEx)

CInterior2::CInterior2()
	: CPropertyPageEx(CInterior2::IDD, 0, IDS_HEADERTITLE, IDS_HEADERSUBTITLE)
{
	//{{AFX_DATA_INIT(CInterior2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInterior2::~CInterior2()
{
}

void CInterior2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterior2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterior2, CPropertyPageEx)
	//{{AFX_MSG_MAP(CInterior2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterior2 message handlers

BOOL CInterior2::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	return CPropertyPageEx::OnSetActive();
}
