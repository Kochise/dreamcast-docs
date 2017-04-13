// denrldoc.cpp : implementation of the CDaoEnrolDoc class
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
#include "DaoEnrol.h"

#include "sectset.h"
#include "coursese.h"
#include "denrldoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateHint

IMPLEMENT_DYNAMIC(CUpdateHint, CObject)

CUpdateHint::CUpdateHint()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDaoEnrolDoc

IMPLEMENT_DYNCREATE(CDaoEnrolDoc, CDocument)

BEGIN_MESSAGE_MAP(CDaoEnrolDoc, CDocument)
	//{{AFX_MSG_MAP(CDaoEnrolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaoEnrolDoc construction/destruction

CDaoEnrolDoc::CDaoEnrolDoc()
{
	// TODO: add one-time construction code here

}

CDaoEnrolDoc::~CDaoEnrolDoc()
{
}


BOOL CDaoEnrolDoc::OnNewDocument()
{
	if (!m_database.IsOpen())
	{
		// First assume stdreg32.mdb file is in current directory
		try
		{
			m_database.Open(_T("stdreg32.mdb"));
		}
		catch (CDaoException* e)
		{
			// Assume failure is becauase we couldn't find the file
			e->Delete();
		}
	}
	if (!m_database.IsOpen())
	{
		// Now pop-up file-open dlg to ask for location
		CFileDialog dlgFile(
			TRUE,
			_T(".mdb"),
			NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("Access Files (*.mdb)|*.mdb|All Files (*.*)|*.*||"));
		if (dlgFile.DoModal() == IDCANCEL)
			return FALSE;
		try
		{
			m_database.Open(dlgFile.GetFileName());
		}
		catch (CDaoException* e)
		{
			// Tell them the reason it failed to open
			AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
			return FALSE;
		}
	}
	if (!m_database.IsOpen())
		return FALSE;
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoEnrolDoc diagnostics

#ifdef _DEBUG
void CDaoEnrolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDaoEnrolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDaoEnrolDoc commands
