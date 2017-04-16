// binddoc.cpp : implementation of the DocObject 
//	OLE server document class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

//BINDER
// CDocObjectServerDoc subclasses MFC's COleServerDoc to add binder-compatible
// OLE interfaces to the class.  The code here declares those extra
// interfaces, provides a rudimentary default command map, and manages
// any IOleDocumentViews active against this document instance.
//BINDER_END

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocObjectServerDoc

IMPLEMENT_DYNAMIC(CDocObjectServerDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CDocObjectServerDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CDocObjectServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CDocObjectServerDoc, COleServerDoc)
   INTERFACE_PART(CDocObjectServerDoc, IID_IOleObject, DocOleObject)
   INTERFACE_PART(CDocObjectServerDoc, IID_IOleDocument, OleDocument)
   INTERFACE_PART(CDocObjectServerDoc, IID_IOleDocumentView, OleDocumentView)
   INTERFACE_PART(CDocObjectServerDoc, IID_IOleCommandTarget, OleCommandTarget)
   INTERFACE_PART(CDocObjectServerDoc, IID_IPrint, Print)
END_INTERFACE_MAP()

// root of OLECMD map can't use BEGIN_OLECMD_MAP macro
const AFX_DATADEF OLE_CMDMAP CDocObjectServerDoc::commandMap =
{
#ifdef _AFXDLL
	&CDocObjectServerDoc::_GetBaseCommandMap,
#else
	NULL,
#endif
	&CDocObjectServerDoc::_commandEntries[0]
};

#ifdef _AFXDLL
const OLE_CMDMAP* CDocObjectServerDoc::_GetBaseCommandMap()
{
	return NULL;
}
#endif

const OLE_CMDMAP* CDocObjectServerDoc::GetCommandMap() const
{
	return &CDocObjectServerDoc::commandMap;
}

const OLE_CMDMAP_ENTRY CDocObjectServerDoc::_commandEntries[] =
{
   { NULL, OLECMDID_SAVEAS, ID_FILE_SAVE_AS },  // ON_OLECMD()
   { NULL, 0, 0 }                               // END_OLECMD_MAP()   
};

CDocObjectServerDoc::CDocObjectServerDoc()
{
   // Initialize DocObject data
   m_pDocSite  = NULL;
   m_pViewSite = NULL;

   // All Binder-Compatible documents use Compound Files as their 
   // storage mechanism
   EnableCompoundFile(TRUE);
}

CDocObjectServerDoc::~CDocObjectServerDoc()
{
	if (m_pDocSite)
      m_pDocSite->Release();
}

void CDocObjectServerDoc::OnCloseDocument() 
{
	// Clean up pointer to document site, if any
	if (m_pDocSite)
	{
      m_pDocSite->Release();
      m_pDocSite = NULL;
	}	
	COleServerDoc::OnCloseDocument();
}

void CDocObjectServerDoc::ActivateDocObject()
{
   if (IsDocObject())
   {
      ASSERT(m_pDocSite != NULL);
      m_pDocSite->ActivateMe(NULL);
   }
}

#ifdef _DEBUG
void CDocObjectServerDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CDocObjectServerDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
	dc << "m_pDocSite = " << m_pDocSite << "\n";
	dc << "m_pViewSite = " << m_pViewSite << "\n";
}
#endif //_DEBUG


