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
//	Header file for VCONCTNR.CPP


#ifndef vconctnr_h_
#define vconctnr_h_

//Include occimpl.h so that COleControlContainer and COleControlSite members 
//can be accessed.  This can be done by using the "Tools/Options" menu item,
//then selecting the "Directories"tab and adding the MSDEV\MFC\SRC directory
//to the include files path.
//**** Note that by including occimpl.h here, there is a dependence upon this
//version of MFC, and these declarations may change in future versions of MFC.
#include "occimpl.h"


/////////////////////////////////////////////////////////////////////////////
class CVControlCtnr : public COleControlContainer
{

public:
	CVControlCtnr( CWnd* pWnd );           
	virtual ~CVControlCtnr();

// Attributes
// Operations
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataObject)
	//}}AFX_VIRTUAL

// Implementation

// Interface Maps
protected:
    DECLARE_INTERFACE_MAP()

    BEGIN_INTERFACE_PART( VOleInPlaceFrame, IOleInPlaceFrame )
		STDMETHOD ( GetWindow ) ( HWND* );
		STDMETHOD ( ContextSensitiveHelp ) ( BOOL );
		STDMETHOD ( GetBorder ) ( LPRECT );
		STDMETHOD ( RequestBorderSpace ) ( LPCBORDERWIDTHS );
		STDMETHOD ( SetBorderSpace ) ( LPCBORDERWIDTHS );
		STDMETHOD ( SetActiveObject) ( LPOLEINPLACEACTIVEOBJECT, LPCOLESTR );
		STDMETHOD ( InsertMenus ) ( HMENU, LPOLEMENUGROUPWIDTHS );
		STDMETHOD ( SetMenu ) ( HMENU, HOLEMENU, HWND );
		STDMETHOD ( RemoveMenus ) ( HMENU );
		STDMETHOD ( SetStatusText ) ( LPCOLESTR );
		STDMETHOD ( EnableModeless) ( BOOL );
		STDMETHOD ( TranslateAccelerator) ( LPMSG, WORD );
    END_INTERFACE_PART( VOleInPlaceFrame )

	BEGIN_INTERFACE_PART( VOleContainer, IOleContainer )
		STDMETHOD( ParseDisplayName )( LPBINDCTX, LPOLESTR, ULONG*, LPMONIKER* );
		STDMETHOD( EnumObjects ) ( DWORD dwFlags,LPENUMUNKNOWN* ppEnumUnknown );
		STDMETHOD( LockContainer )( BOOL );
	END_INTERFACE_PART( VOleContainer )


	// Generated message map functions
	//{{AFX_MSG(CVControlCtnr)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif