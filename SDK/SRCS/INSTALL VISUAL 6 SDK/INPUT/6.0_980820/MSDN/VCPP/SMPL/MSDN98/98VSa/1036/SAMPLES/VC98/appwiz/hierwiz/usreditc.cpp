// usreditc.cpp : implementation file
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
#include "UsrEditC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsrEditClass

CUsrEditClass::CUsrEditClass()
{
}

CUsrEditClass::~CUsrEditClass()
{
}


BEGIN_MESSAGE_MAP(CUsrEditClass, CEdit)
	//{{AFX_MSG_MAP(CUsrEditClass)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUsrEditClass message handlers

void CUsrEditClass::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// We need to trap the tab key and replace it with the tab character because otherwise Windows
// assumes that we are tabbing from the edit control to the next one in the tabbing order.
	if (VK_TAB == nChar )
	{
		ReplaceSel("\t") ;
		return ;
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
