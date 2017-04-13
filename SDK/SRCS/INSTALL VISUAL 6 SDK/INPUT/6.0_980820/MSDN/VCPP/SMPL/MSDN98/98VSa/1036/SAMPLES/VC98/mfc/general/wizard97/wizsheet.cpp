// SampWizP.cpp : implementation file
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
#include "WizSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampWizP

IMPLEMENT_DYNAMIC(CWizard97Sheet, CPropertySheetEx)

CWizard97Sheet::CWizard97Sheet(UINT nIDCaption, CWnd* pParentWnd,
	UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark,
	HBITMAP hbmHeader)
: CPropertySheetEx(nIDCaption, pParentWnd, iSelectPage,
				  hbmWatermark, hpalWatermark, hbmHeader)
{
	// add all the pages of the wizard
	AddPage(&m_Intro);
	AddPage(&m_Interior1);
	AddPage(&m_Interior2);
	AddPage(&m_Completion);

	// set the WIZARD97 flag so we'll get the new look
	m_psh.dwFlags |= PSH_WIZARD97;
}

CWizard97Sheet::CWizard97Sheet(LPCTSTR pszCaption, CWnd* pParentWnd,
	UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark,
	HBITMAP hbmHeader)
: CPropertySheetEx(pszCaption, pParentWnd, iSelectPage,
					  hbmWatermark, hpalWatermark, hbmHeader)

{
	// add all the pages of the wizard
	AddPage(&m_Intro);
	AddPage(&m_Interior1);
	AddPage(&m_Interior2);
	AddPage(&m_Completion);

	// set the WIZARD97 flag so we'll get the new look
	m_psh.dwFlags |= PSH_WIZARD97;
}

CWizard97Sheet::~CWizard97Sheet()
{
}


BEGIN_MESSAGE_MAP(CWizard97Sheet, CPropertySheetEx)
	//{{AFX_MSG_MAP(CWizard97Sheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard97Sheet message handlers
