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
//	Header file for VCDATOBJ.CPP

#ifndef vcdatobj_h_
#define vcdatobj_h_

/////////////////////////////////////////////////////////////////////////////
// CDataObject command target
class CDataObject : public CCmdTarget
{
DECLARE_DYNCREATE(CDataObject)

public:
	CDataObject();           
	virtual ~CDataObject();

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

    BEGIN_INTERFACE_PART(VDataObject, IDataObject)
		STDMETHOD( GetData ) ( LPFORMATETC, LPSTGMEDIUM );
	    STDMETHOD( GetDataHere ) ( LPFORMATETC , LPSTGMEDIUM );
		STDMETHOD( QueryGetData ) ( LPFORMATETC );
		STDMETHOD( GetCanonicalFormatEtc ) ( LPFORMATETC , LPFORMATETC );
		STDMETHOD( SetData ) ( LPFORMATETC , STGMEDIUM * , BOOL );
		STDMETHOD( EnumFormatEtc ) ( DWORD , LPENUMFORMATETC FAR* );
		STDMETHOD( DAdvise ) ( FORMATETC * , DWORD , LPADVISESINK , DWORD * );
		STDMETHOD( DUnadvise ) ( DWORD );
		STDMETHOD( EnumDAdvise ) ( LPENUMSTATDATA * );
    END_INTERFACE_PART(VDataObject)

	// Generated message map functions
	//{{AFX_MSG(CDataObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif