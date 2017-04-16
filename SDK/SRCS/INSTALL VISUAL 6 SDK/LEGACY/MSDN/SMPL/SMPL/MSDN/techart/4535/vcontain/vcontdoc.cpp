//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//	AppWizard generated file for CDocument derived class.


#include "stdafx.h"
#include "vcontain.h"
#include "vcontdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVContainDoc

IMPLEMENT_DYNCREATE(CVContainDoc, CDocument)

BEGIN_MESSAGE_MAP(CVContainDoc, CDocument)
	//{{AFX_MSG_MAP(CVContainDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVContainDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CVContainDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVConta to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9E794301-D1C6-11CE-AA09-0080C78A1D7F}
static const IID IID_IVConta =
{ 0x9e794301, 0xd1c6, 0x11ce, { 0xaa, 0x9, 0x0, 0x80, 0xc7, 0x8a, 0x1d, 0x7f } };

BEGIN_INTERFACE_MAP(CVContainDoc, CDocument)
	INTERFACE_PART(CVContainDoc, IID_IVConta, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVContainDoc construction/destruction

CVContainDoc::CVContainDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CVContainDoc::~CVContainDoc()
{
	AfxOleUnlockApp();
}

BOOL CVContainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVContainDoc serialization

void CVContainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVContainDoc diagnostics

#ifdef _DEBUG
void CVContainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVContainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVContainDoc commands

