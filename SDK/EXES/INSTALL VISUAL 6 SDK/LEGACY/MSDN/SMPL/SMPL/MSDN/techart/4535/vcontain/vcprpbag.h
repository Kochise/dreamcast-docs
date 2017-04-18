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
//	Header file for VCPRPBAG.CPP


#ifndef vcprpbag_h_
#define vcprpbag_h_

/////////////////////////////////////////////////////////////////////////////
// CPropertyBag command target

class CPropertyBag : public CCmdTarget
{
	DECLARE_DYNCREATE(CPropertyBag)

	CPropertyBag();           // protected constructor used by dynamic creation
	virtual ~CPropertyBag();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyBag)
	//}}AFX_VIRTUAL

// Implementation
protected:

	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(VPropertyBag, IPropertyBag)
		STDMETHOD ( Read )( LPCOLESTR , LPVARIANT , LPERRORLOG );
		STDMETHOD ( Write )( LPCOLESTR , LPVARIANT );
	END_INTERFACE_PART(VPropertyBag)

	// Generated message map functions
	//{{AFX_MSG(CPropertyBag)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif