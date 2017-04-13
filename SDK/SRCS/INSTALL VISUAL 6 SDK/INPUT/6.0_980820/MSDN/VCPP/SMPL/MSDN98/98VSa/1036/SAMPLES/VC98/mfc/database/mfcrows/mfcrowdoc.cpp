// MFCRowDoc.cpp : implementation of the CMFCRowDoc class
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
#include "MFCRow.h"

#include "MFCRowSet.h"
#include "MFCRowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCRowDoc

IMPLEMENT_DYNCREATE(CMFCRowDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCRowDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCRowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCRowDoc construction/destruction

CMFCRowDoc::CMFCRowDoc()
{
	// TODO: add one-time construction code here

}

CMFCRowDoc::~CMFCRowDoc()
{
}

BOOL CMFCRowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCRowDoc diagnostics

#ifdef _DEBUG
void CMFCRowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCRowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCRowDoc commands
