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
//	Header file for VCONVIEW.CPP


#ifndef vconview_h_
#define vconview_h_

/////////////////////////////////////////////////////////////////////////////

#include "verify.h"
#include "vcdatobj.h"
#include "vcadvsnk.h"
#include "resltdlg.h" 
#include "vcprpbag.h"
#include "vcerrlog.h"
#include "vcontdoc.h"
#include "vconctnr.h"

//Total number of interfaces tested for full compatibility test.
#define NUM_INTERFACES			19

//V_PREV_FAILURE is used to show that the interface was not verified due to a previous
//dependent method failure.
#define V_PREV_FAILURE			100L
//V_NOT_APPLICABLE is used to show that the method was not verified in this situation
//since it was optional.
#define V_NOT_APPLICABLE		101L
//V_AUTO_EXCEPTION is used to show that the method was not verified due to an 
//automation exception.
#define V_AUTO_EXCEPTION		102L
//V_NOT_QI_OBTAINED is used to show that the interface pointer was not obtainerd
//through a QI call (usually as a return parameter from a method call).
#define V_NOT_QI_OBTAINED		103L


//Custom HRESULT value to signify not verified for result display processing.
// Codes 0x4000-0x40ff are reserved for OLE, so pick one way out of range.
#define HRESULT_NOT_VERIFIED	0x8000AAAA

//Names of file and stream for use whe IStream and IStorage are needed.
#define VCONTAIN_ISTREAM_NAME	TEXT ( "Contents" )
#define VCONTAIN_FILE_NAME		TEXT ( "VCONTAIN.DFL" )

//CRect used for positioning of control (left, top, right, bottom) and in many
//method calls,
#define CRECT_CONTROL CRect( 250,100,350,200 )


class CPreVerifyDlg;

class CVContainView : public CView
{
protected: // create from serialization only
	CVContainView();
	void CreateStorageObjects();
	DECLARE_DYNCREATE(CVContainView)

// Attributes
public:
	CVContainDoc* GetDocument();

	//Pre-Verify dialog flag set to TRUE if pre-verify info obtained from 
	//type lib, registry, and dialog box.
	BOOL m_bPreVerifyInfoObtained ;
	
	//Set to TRUE if all of the interfaces were tested (as opposed to specific
	//ones only) to display summary compliance message before results dialog.
	BOOL m_bAllInterfacesTested;

	//Set to TRUE following the first verification process.
	BOOL m_bVerified;
	//Pre-Verify BOOLEAN members to determine mandatory or optional interfaces
	//and methods.  
	BOOL m_bLicensed;
	//Need a variable for both ambients and mnemonics due to optional 
	//interfaces in IOleControl.
	BOOL m_bAmbients;
	BOOL m_bMnemonics;
	BOOL m_bAccelerators;
	BOOL m_bLinks;
	BOOL m_bPropsMethods;
	BOOL m_bUI;
	BOOL m_bConnPoints;
	BOOL m_bConnPtEvents;
	BOOL m_bConnPtNotify;
	BOOL m_bPropPages;
	//Prop sets means persistent properties stored in the (type, value) format
	//so that they can be read by a container.  This is not for simply 
	//persistent properties serialized in DoPropExchange.
	BOOL m_bPropSets;
	//TRUE if control is currently instantiated in container; FALSE otherwise.
	BOOL m_bControlExists;	
	//TRUE if the control is invisible at runtime.
	BOOL m_bInvisibleAtRuntime;
	
	//Dialog box to display results.
	CResultsDlg m_CResultsDlg;		
	
	//Ptr to test control object
	CVerify * m_verify;				
	
	//Ptr to control site for this object used by the container.
	COleControlSite * m_pControlSite;

	//Ptrs to objects that implement IDataObject and IAdviseSink.  Define 
	//here for scope purposes so that they exist throughout the life on the app.
	CDataObject * m_lpCDataObject;	//Holds actual instance of CDataObject
									//which exposes IDataObject
	CAdvSink * m_lpCAdviseSink;		//Holds actual instance of CAdvSink 
									//which exposes IAdviseSink
		
	LPUNKNOWN m_lpIUnknown;			//IUnknown pointer used to call QI on to 
									//verify other interfaces
	LPDATAOBJECT m_lpIDataObject;	//Holds the IDataObject ptr to use in 
									//various method calls
	LPSTORAGE m_lpIStorage;			//Holds the IStorage ptr to use in various 
									//method calls.
	LPSTREAM m_lpIStream;			//Holds the IStream ptr to use in various 
									//method calls.
	LPADVISESINK m_lpIAdviseSink;	//Holds the IAdviseSink ptr to use in 
									//various method calls.

	// Operations
public:
	virtual ~CVContainView();

	//Initialize, Read, compute, and display results.
	void InitResultObjects ();
	void InitStatusMembers ();
	void InitInterfaceMembers ();
	void InitQuestionMembers ( CPreVerifyDlg * dlg );
	CResultsObj * CreateResultObject ();

	void NonStandardVerification ( const int iPrevFailedMethod, 
		const HRESULT hResultPrev, const long lReason, 
		const int iNotVerifiedMethod, const BOOL bMandatory, const BOOL bVerified );
	void VerifyInterfaceOrMethod ( HRESULT hResult, const int iStringID, 
			const BOOL bMandatory );
	int  GetManOrOptStringID ( const BOOL bMandatory );
	int  GetHResultStringID ( HRESULT hResult );
	void DeleteAllResultObjects ();

	//Pre-verification operations.
	BOOL GetPreVerifyInfo();
	void ReadVerifyDlg( CPreVerifyDlg * dlg );
	void PreVerifyUsingTypeLib( CPreVerifyDlg * dlg );
	void PreVerifyPropertyPages ( CPreVerifyDlg * dlg );
	BOOL ParseVersion ( TCHAR szVerBuff[], WORD * wVerMajor, WORD * wVerMinor );
	BOOL CheckCoClassInfo ( LPTYPEINFO lpCoClassTypeInfo, int nImplTypeFlags, 
			LPTYPEATTR pta, BOOL * bQuestion );
	BOOL CheckBindableAttribute ( LPTYPEINFO lpPropMethodTypeInfo, 
			LPTYPEATTR pta );
	BOOL LoadTypeLibFromCLSID ( LPTYPELIB * lpPropMethodTypeLib );
	void CheckMiscStatusBits ( CPreVerifyDlg * dlg );

	//Methods to verify each individual interface and its methods.
	void VerifyIOleObject ();
	void VerifyIOleInPlaceObject ();
	void VerifyIDataObject ();
	void VerifyIViewObject2 ();
	void VerifyIDispatch ();
	void VerifyIProvideClassInfo ();
	void VerifyIPersistStorage ();
	void VerifyIOleInPlaceActiveObject ();
	void VerifyIOleControl ();
	void VerifyIExternalConnection ();
	void VerifyConnectionPointInterfaces ();
	void CallConnPtMethods 
		( LPCONNECTIONPOINTCONTAINER lpIConnectionPointContainer, 
		  REFIID iidSink, LPUNKNOWN lpIUnkSink );
	void VerifyISpecifyPropertyPages ();
	void VerifyIPersistStream ();
	void VerifyIPersistStreamInit ();
	void VerifyIPersistPropertyBag ();
	void VerifyIOleCache ();
	void VerifyIOleCache2 ();
	void VerifyIOleCacheControl ();
	void VerifyIRunnableObject ();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVContainView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
  
// Implementation
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CVContainView)
	afx_msg void OnInsertControl();
	afx_msg void OnVerifyControl();
	afx_msg void OnUpdateVerifyControl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsertControl(CCmdUI* pCmdUI);
	afx_msg void OnVerifySpecific();
	afx_msg void OnUpdateVerifySpecific(CCmdUI* pCmdUI);
	afx_msg void OnViewResults();
	afx_msg void OnUpdateViewResults(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteControl(CCmdUI* pCmdUI);
	afx_msg void OnDeleteControl();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VContainView.cpp
inline CVContainDoc* CVContainView::GetDocument()
   { return (CVContainDoc*)m_pDocument; }
#endif


#endif

/////////////////////////////////////////////////////////////////////////////
