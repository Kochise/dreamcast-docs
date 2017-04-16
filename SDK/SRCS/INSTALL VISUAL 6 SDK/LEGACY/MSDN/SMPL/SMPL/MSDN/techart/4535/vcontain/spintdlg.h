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
//	Header file for SPINTDLG.CPP


#ifndef spintdlg_h_
#define spintdlg_h_

/////////////////////////////////////////////////////////////////////////////
// CSpecInterfaceDlg dialog

class CSpecInterfaceDlg : public CDialog
{
// Construction
public:
	CSpecInterfaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpecInterfaceDlg)
	enum { IDD = IDD_SPECIFIC_INTERFACES };
	BOOL	m_bConnInterfaces;
	BOOL	m_bDataObject;
	BOOL	m_bDispatch;
	BOOL	m_bExtConn;
	BOOL	m_bOleCache;
	BOOL	m_bOleCache2;
	BOOL	m_bOleCacheControl;
	BOOL	m_bOleControl;
	BOOL	m_bOleInPlaceActiveObject;
	BOOL	m_bOleInPlaceObject;
	BOOL	m_bOleObject;
	BOOL	m_bPersistStorage;
	BOOL	m_bPersistStream;
	BOOL	m_bPersistStreamInit;
	BOOL	m_bProvideClassInfo;
	BOOL	m_bRunObject;
	BOOL	m_bSpecPropPages;
	BOOL	m_bViewObject2;
	BOOL	m_bPersistPropBag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecInterfaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpecInterfaceDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif