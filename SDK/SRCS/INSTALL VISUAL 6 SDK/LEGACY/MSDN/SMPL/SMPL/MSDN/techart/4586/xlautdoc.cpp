/*****************************************************************************
  File: xlautodoc.cpp

  Purpose: Standard AppWizard generated COleDocument implementation

  Functions:

  Development Team: Steve Roeder

  Written by Microsoft Product Support Services, Languages Developer Support
  Copyright (c) 1995 Microsoft Corporation. All rights reserved.
\****************************************************************************/

// XlAutdoc.cpp : implementation of the CXlAutoDoc class
//

#include "stdafx.h"
#include "XlAuto.h"

#include "XlAutdoc.h"
#include "cntritem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXlAutoDoc

IMPLEMENT_DYNCREATE(CXlAutoDoc, COleDocument)

BEGIN_MESSAGE_MAP(CXlAutoDoc, COleDocument)
	//{{AFX_MSG_MAP(CXlAutoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleDocument::OnUpdateObjectVerbMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CXlAutoDoc, COleDocument)
	//{{AFX_DISPATCH_MAP(CXlAutoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXlAutoDoc construction/destruction

CXlAutoDoc::CXlAutoDoc()
{
	// For most containers, using compound files is a good idea.
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CXlAutoDoc::~CXlAutoDoc()
{
	AfxOleUnlockApp();
}

BOOL CXlAutoDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoDoc serialization

void CXlAutoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoDoc diagnostics

#ifdef _DEBUG
void CXlAutoDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CXlAutoDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXlAutoDoc commands
