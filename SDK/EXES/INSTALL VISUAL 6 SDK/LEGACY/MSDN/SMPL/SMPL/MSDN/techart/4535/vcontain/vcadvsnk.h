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
//Purpose:
//	Header file for VCADVSNK.CPP


#ifndef vadvsnk_h_
#define vadvsnk_h_

/////////////////////////////////////////////////////////////////////////////
// CAdvSink command target

class CAdvSink : public CCmdTarget
{
	DECLARE_DYNCREATE(CAdvSink)

public:
	CAdvSink();          
	virtual ~CAdvSink();

// Attributes


// Operations


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvSink)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdvSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_INTERFACE_MAP()
	
	//Return types here are void instead of STDMETHOD since these methods
	//do not return a value.
    BEGIN_INTERFACE_PART(VAdvSink, IAdviseSink)
		void __stdcall OnClose ();
		void __stdcall OnDataChange ( FORMATETC * , STGMEDIUM * );
		void __stdcall OnRename ( IMoniker * );
		void __stdcall OnSave ();
		void __stdcall OnViewChange ( DWORD , LONG );
    END_INTERFACE_PART(VAdvSink)

	DECLARE_MESSAGE_MAP()
};

#endif
