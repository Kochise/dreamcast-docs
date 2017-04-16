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
//	Header file for VCERRLOG.CPP


#ifndef vcerror_h_
#define vcerror_h_

/////////////////////////////////////////////////////////////////////////////
// CErrorLog command target

class CErrorLog : public CCmdTarget
{
	DECLARE_DYNCREATE(CErrorLog)

	CErrorLog();           // protected constructor used by dynamic creation
	virtual ~CErrorLog();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorLog)
	//}}AFX_VIRTUAL

// Implementation
protected:
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(VErrorLog, IErrorLog)
			STDMETHOD( AddError )( LPCOLESTR, LPEXCEPINFO );
	END_INTERFACE_PART(VErrorLog)

	// Generated message map functions
	//{{AFX_MSG(CErrorLog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif

