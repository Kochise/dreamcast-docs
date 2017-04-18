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
//	Dialog box to prompt user which specific interfaces to verify.

#include "stdafx.h"
#include "vcontain.h"
#include "spintdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecInterfaceDlg dialog


CSpecInterfaceDlg::CSpecInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecInterfaceDlg)
	m_bConnInterfaces = FALSE;
	m_bDataObject = FALSE;
	m_bDispatch = FALSE;
	m_bExtConn = FALSE;
	m_bOleCache = FALSE;
	m_bOleCache2 = FALSE;
	m_bOleCacheControl = FALSE;
	m_bOleControl = FALSE;
	m_bOleInPlaceActiveObject = FALSE;
	m_bOleInPlaceObject = FALSE;
	m_bOleObject = FALSE;
	m_bPersistStorage = FALSE;
	m_bPersistStream = FALSE;
	m_bPersistStreamInit = FALSE;
	m_bProvideClassInfo = FALSE;
	m_bRunObject = FALSE;
	m_bSpecPropPages = FALSE;
	m_bViewObject2 = FALSE;
	m_bPersistPropBag = FALSE;
	//}}AFX_DATA_INIT
}


void CSpecInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecInterfaceDlg)
	DDX_Check(pDX, IDC_CONNINTERFACES, m_bConnInterfaces);
	DDX_Check(pDX, IDC_DATAOBJECT, m_bDataObject);
	DDX_Check(pDX, IDC_DISPATCH, m_bDispatch);
	DDX_Check(pDX, IDC_EXTCONN, m_bExtConn);
	DDX_Check(pDX, IDC_OLECACHE, m_bOleCache);
	DDX_Check(pDX, IDC_OLECACHE2, m_bOleCache2);
	DDX_Check(pDX, IDC_OLECACHECONTROL, m_bOleCacheControl);
	DDX_Check(pDX, IDC_OLECONTROL, m_bOleControl);
	DDX_Check(pDX, IDC_OLEINPLACEACTIVEOBJECT, m_bOleInPlaceActiveObject);
	DDX_Check(pDX, IDC_OLEINPLACEOJBECT, m_bOleInPlaceObject);
	DDX_Check(pDX, IDC_OLEOBJECT, m_bOleObject);
	DDX_Check(pDX, IDC_PERSISTSTORAGE, m_bPersistStorage);
	DDX_Check(pDX, IDC_PERSISTSTREAM, m_bPersistStream);
	DDX_Check(pDX, IDC_PERSISTSTREAMINIT, m_bPersistStreamInit);
	DDX_Check(pDX, IDC_PROVIDECLASSINFO, m_bProvideClassInfo);
	DDX_Check(pDX, IDC_RUNOBJECT, m_bRunObject);
	DDX_Check(pDX, IDC_SPECPROPPAGES, m_bSpecPropPages);
	DDX_Check(pDX, IDC_VIEWOBJECT2, m_bViewObject2);
	DDX_Check(pDX, IDC_PERSISTPROPBAG, m_bPersistPropBag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CSpecInterfaceDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecInterfaceDlg message handlers
