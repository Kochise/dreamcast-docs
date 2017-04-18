// SerialDoc.cpp : implementation of the CSerialDoc class
//

#include "stdafx.h"
#include "Serial.h"
#include "SerialDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc
IMPLEMENT_DYNCREATE(CSerialDoc, CDocument)

BEGIN_MESSAGE_MAP(CSerialDoc, CDocument)
	//{{AFX_MSG_MAP(CSerialDoc)
	ON_COMMAND(ID_POPULATE, OnPopulate)
	ON_COMMAND(ID_DUMP, OnDump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CSerialDoc construction/destruction

CSerialDoc::CSerialDoc() : division( new Division )
{}

CSerialDoc::~CSerialDoc()
{
	delete division;
}
//------------------------------------------------
void CSerialDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << division;	// Must be a CObject pointer.
	}
	else
	{
		CObject *p;
		ar >> p;
		
		division = dynamic_cast<Division *>(p);
		ASSERT( division );
	}
}
//------------------------------------------------
BOOL CSerialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if( division )
	{
		delete division;
		division = new Division;
	}

	return TRUE;
}
//------------------------------------------------
void CSerialDoc::OnPopulate() 
{
	// TODO: Add your command handler code here
	
	Manager *mgr = new Manager( 1 );
	division->hire( mgr 				);
	division->hire( new Peon( 2, mgr )	);
	division->hire( new Peon( 3, mgr )	);
	division->hire( new Peon( 4, mgr )	);

	CDocument::SetModifiedFlag( TRUE );
}
//------------------------------------------------
void CSerialDoc::OnDump() 
{
	afxDump << division;
}
