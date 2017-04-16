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
//	Implementation of view class.  This includes most of the processing in
//  this application since the control is created here and all of the 
//	interface/method validation occurs here	as well.


#include "stdafx.h"
#include "afx.h"
#include "vcontain.h"
#include "vcontdoc.h"
#include "vconview.h"
#include "insertd.h"
#include "verify.h"
#include "spintdlg.h"
#include "winnls.h"		//For GetUserDefaultLCID ()
#include "winreg.h"		//For registry calls
#include "prevedlg.h"
#include "vconctnr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////
// CVContainView
//Global pointer defined in VCONCTNR.CPP to point to active object.
extern LPOLEINPLACEACTIVEOBJECT g_lpIOleInPlaceActiveObject;

IMPLEMENT_DYNCREATE(CVContainView, CView) 

BEGIN_MESSAGE_MAP(CVContainView, CView) 
	//{{AFX_MSG_MAP(CVContainView) 
	ON_COMMAND(ID_INSERT_CONTROL, OnInsertControl)
	ON_COMMAND(ID_VERIFY_CONTROL, OnVerifyControl)
	ON_UPDATE_COMMAND_UI(ID_VERIFY_CONTROL, OnUpdateVerifyControl)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CONTROL, OnUpdateInsertControl)
	ON_COMMAND(ID_VERIFY_SPECIFIC, OnVerifySpecific)
	ON_UPDATE_COMMAND_UI(ID_VERIFY_SPECIFIC, OnUpdateVerifySpecific)
	ON_COMMAND(ID_VIEW_RESULTS, OnViewResults)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESULTS, OnUpdateViewResults)
	ON_UPDATE_COMMAND_UI(ID_DELETECONTROL, OnUpdateDeleteControl)
	ON_COMMAND(ID_DELETECONTROL, OnDeleteControl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////
// CVContainView construction/destruction

CVContainView::CVContainView ()
{
}
			   

CVContainView::~CVContainView()
{
	//By releasing the IStream (m_lpIStream) and IStorage (m_lpIStorage) 
	//interface pointers, the stream and file will be closed.
	if ( m_lpIStream != NULL )
	{
		m_lpIStream->Release ();
	}

	if ( m_lpIStorage != NULL )
	{
		m_lpIStorage->Release ();
	}
	
	//By releasing the m_lpIDataObject and m_lpIAdviseSink interface pointers,
	//the ref count goes to zero and the object will release itself.  Thus, 
	//we do not need to call delete explicitly on m_lpCDataObject and 
	//m_lpCAdviseSink.
	if ( m_lpIDataObject != NULL )
	{
		m_lpIDataObject->Release ();
	}

	if ( m_lpIAdviseSink != NULL )
	{
		m_lpIAdviseSink->Release ();
	}

	if ( m_verify != NULL )
	{
		delete m_verify;
	}
	
	//Delete all result objects used for holding and displaying results of 
	//each call.
	DeleteAllResultObjects ();
}


BOOL CVContainView::PreCreateWindow ( CREATESTRUCT& cs )
{
	// TODO: Modify the Window class or styles here by modifying the 
	//CREATESTRUCT cs
	return CView::PreCreateWindow ( cs );
}

int CVContainView::OnCreate ( LPCREATESTRUCT lpCreateStruct ) 
{
	if ( CView::OnCreate ( lpCreateStruct ) == -1 )
		return -1;

	//Initialize member variables.
	InitStatusMembers ();

	//Initialize interface member variables.
	InitInterfaceMembers ();

	//Create IStorage and IStream objects to be used in various method calls.
	CreateStorageObjects ();

	return 0;
}


/////////////////////////////
// CVContainView drawing
void CVContainView::OnDraw (CDC * )
{
	CVContainDoc* pDoc = GetDocument ();
	ASSERT_VALID ( pDoc );
}

/////////////////////////////
// CVContainView diagnostics

#ifdef _DEBUG
void CVContainView::AssertValid () const
{
	CView::AssertValid ();
}

void CVContainView::Dump ( CDumpContext& dc ) const
{
	CView::Dump(dc);
}

CVContainDoc* CVContainView::GetDocument () // non-debug version is inline
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS ( CVContainDoc ) ) );
	return ( CVContainDoc * ) m_pDocument;
}
#endif 


//***************************************************************************
//METHOD NAME:			
//	CVContainView::InitInterfaceMembers
//PURPOSE:
//	Initializes member variables of the view class that represent the 
//  implementations of
//	interfaces the container is supporting outside of those of the 
//	COleControlContainer class.
//INPUT PARAMETER(s):	
//	None.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::InitInterfaceMembers()
{
	//Initialize interface and object pointers.
	m_lpIUnknown = NULL;
	m_lpCDataObject = NULL;
	m_lpCAdviseSink = NULL;
	m_lpIAdviseSink = NULL;
	m_lpIDataObject = NULL;

	//Create an instance of CDataObject which exposes IDataObject, then get the 
	//IDataObject interface pointer for it.
	try
	{
		m_lpCDataObject = new CDataObject;
	}
	catch ( CMemoryException e )
	{
		e.Delete ();

		//Set this to NULL to ensure that proper processing occurs later on.
		m_lpCDataObject = NULL;
	}

	if ( m_lpCDataObject != NULL )
	{
		m_lpIDataObject = ( LPDATAOBJECT ) m_lpCDataObject->GetInterface 
														( &IID_IDataObject );
		ASSERT_POINTER ( m_lpIDataObject, IDataObject );
	}

	//Create an instance of CAdvSink which exposes IAdviseSink, then get the 
	//IAdviseSink interface pointer for it.
	try
	{
		m_lpCAdviseSink = new CAdvSink;
	}
	catch ( CMemoryException  e )
	{
		e.Delete();
		//Set this to NULL to ensure that proper processing occurs later on.
		m_lpCAdviseSink = NULL;
	}

	if ( m_lpCAdviseSink != NULL )
	{
		m_lpIAdviseSink = ( LPADVISESINK ) m_lpCAdviseSink->GetInterface 
													( &IID_IAdviseSink );
		ASSERT_POINTER ( m_lpIAdviseSink, IAdviseSink );
	}

	//Set a pointer to the view class in the results dlg object.
	m_CResultsDlg.SetView ( this );
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::InitQuestionMembers
//PURPOSE:
//	Initializes the question variables.  These determine which questions are
//	shown in the pre-verify dialog box, to TRUE.  This will ensure they are
//	displayed if an error occurs during pre-verification information and the
//	information is not obtained.
//INPUT PARAMETER(s):	
//	CPreVerifyDlg * dlg - Ptr to pre-verify dialog object.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::InitQuestionMembers ( CPreVerifyDlg * dlg )
{
	dlg->m_bEnableConnPtQuestion = TRUE; 
	dlg->m_bEnableLicensedQuestion = TRUE;
	dlg->m_bEnableUIQuestion = TRUE;
	dlg->m_bEnableLinksQuestion = TRUE;
	dlg->m_bEnablePropMethodQuestion = TRUE;
	dlg->m_bEnablePropPagesQuestion = TRUE;
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::InitStatusMembers
//PURPOSE:
//	Initializes the members that provide information about the state of the 
//	control in the container.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::InitStatusMembers ()
{
	//Ptr to control object.
	m_verify = NULL;
	
	//Members that reflect status of control in container.
	m_bControlExists = FALSE;
	m_bVerified = FALSE;
	m_bPreVerifyInfoObtained = FALSE;

	//Ptr to active object that will be set later during in-place activation.
	g_lpIOleInPlaceActiveObject = NULL;
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::OnInsertControl
//PURPOSE:
//	Create an instance of the control to be verified.  Before creating the 
//	object, check to see if it supports the IClassFactory2 interface that is
//	used for licensing.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::OnInsertControl() 
{
	ASSERT( this != NULL );

	m_lpIUnknown = NULL; 

	if ( m_pCtrlCont == NULL )
	{
		m_pCtrlCont = new CVControlCtnr ( this );
		InitControlContainer ();
	}

	//Display the insert object dialog to select a control.
	CInsertDialog insObjDlg;
	if( insObjDlg.DoModal () == IDOK )
	{
		BeginWaitCursor ();

		//Before we create the control, test for IClassFactory2. If it exists,
		//then the normal IClassfactory exists since ICF is derived from ICF2.
		LPCLASSFACTORY2 lpCF2;
		HRESULT hResult;
			
		if ( SUCCEEDED  ( hResult = CoGetClassObject ( 
						( REFIID ) insObjDlg.m_io.clsid, CLSCTX_INPROC_SERVER 
				| CLSCTX_INPROC_HANDLER, NULL, IID_IClassFactory2, 	
						( void ** ) &lpCF2 ) ) && ( lpCF2 != NULL ) ) 
		{
			ASSERT ( lpCF2 != NULL );
			ASSERT_POINTER ( lpCF2, IClassFactory2 );

			//Set flag for later when type lib is read for 'licensed' keyword 
			//to determine if ICF2 is mandatory or not.
			m_bLicensed = TRUE;

			//Release ICF2 pointer since MFC CreateControl will handle the 
			//loading and unloading of the class factory.
			lpCF2->Release ();
		}
		else
		{
			//The control cannot support licensing.
			m_bLicensed = FALSE;
		}

		//Create new CWnd derived object each time a control is created.
		try
		{
			m_verify = new CVerify;
		
			//Save CLSID for later use in pre-verification process, then 
			//create control..
			m_verify->m_clsid = insObjDlg.m_io.clsid;
			m_bControlExists = m_verify->CreateControl( m_verify->m_clsid,
				NULL, WS_VISIBLE, CRECT_CONTROL, this, 122 );

			if ( ! m_bControlExists )
			{						
				//Display message saying the control was not created 
				//successfully, primarily for those controls that are 
				//invisible at runtime.
				AfxMessageBox ( IDS_E_CANT_CREATE_CONTROL );
			
				//Delete the CWnd derived m_verify object so we can create
				//another control at a later point if desired.
				delete m_verify;
				m_verify = NULL;
			}
			else
			{
				//Display message saying the control was created successfully,
				//primarily for those controls that are invisible at runtime.
				AfxMessageBox ( IDS_CONTROL_CREATED );

				//Get the control site to use if control creates successfully 
				//or to release if the control didn't create successfully to 
				//allow another control to be created.
				m_pControlSite = m_verify->GetControlSite ();
			}
		}
		catch ( CMemoryException e )
		{
			//Inform user control not created and set flag to show control 
			//does not exist.
			e.Delete ();
			AfxMessageBox ( IDS_E_CANT_CREATE_CONTROL );
			m_bControlExists = FALSE;
		}

		EndWaitCursor ();
	} 
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::OnVerifyControl
//PURPOSE:	
//	Verifies all interfaces, both optional and mandatory, all in one command.	
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::OnVerifyControl () 
{
	ASSERT( this != NULL );
	
	if( m_lpIUnknown == NULL )
	{
		//The control exists but its main IUnknown has not yet been placed 
		//into m_lpIUnknown so obtain its IUnknown pointer.  From this, we
		//can then call all other interfaces.
		//Note that this pointer is not AddRef'd so do not call Release on it.
		m_lpIUnknown = m_verify->GetControlUnknown ();
		ASSERT_POINTER ( m_lpIUnknown, IUnknown );
	}

	if ( m_lpIUnknown != NULL )
	{
		//Get pre-verification information if it has not already been obtained.
		if ( ! m_bPreVerifyInfoObtained )
			{
				if ( ! GetPreVerifyInfo () )
				{
					AfxMessageBox ( IDS_E_NO_PRE_VERIFY_INFO );
					return;
				}
			}

 		//Pre-verify info exists so begin verification process.
		BeginWaitCursor ();

		//Initialize counters for results.
		InitResultObjects ();

		//Verify applicable methods on each interface.
		VerifyConnectionPointInterfaces ();
		VerifyIDataObject (); 
		VerifyIDispatch ();
		VerifyIExternalConnection ();
		VerifyIOleCache ();
		VerifyIOleCache2 ();
		VerifyIOleCacheControl ();
		VerifyIOleControl ();
		VerifyIOleInPlaceActiveObject ();
		VerifyIOleInPlaceObject ();
		VerifyIOleObject ();
		VerifyIProvideClassInfo ();
		VerifyIPersistPropertyBag ();
		VerifyIPersistStorage ();
		VerifyIPersistStream ();
		VerifyIPersistStreamInit ();
		VerifyIRunnableObject ();
		VerifyISpecifyPropertyPages ();
		VerifyIViewObject2 ();
		
		EndWaitCursor ();
	
		//Set member showing all interfaces tested and display results 
		//of verification of all interfaces.
		m_bAllInterfacesTested = TRUE;
		OnViewResults ();
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::OnVerifySpecific
//PURPOSE:
//	Verify specific interfaces that are selected by the user.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::OnVerifySpecific () 
{
	ASSERT( this != NULL );

	int iNumInterfacesTested = 0;

	//Dialog object that displays interface check boxes to select from.
	CSpecInterfaceDlg dlg;

	if ( dlg.DoModal () == IDOK )
	{
		if( m_lpIUnknown == NULL )
		{
			//The control exists but its main IUnknown has not yet been 
			//placed into m_lpIUnknown; get its main IUnknown pointer.
			m_lpIUnknown = m_verify->GetControlUnknown ();
		}
		
		if ( m_lpIUnknown != NULL )
		{
			//Obtain pre-verification information to determine if certain 
			//interfaces and methods are mandatory if the dialog has not
			//already been shown once.
			if ( ! m_bPreVerifyInfoObtained )
			{
				if ( ! GetPreVerifyInfo () )
				{
					AfxMessageBox ( IDS_E_NO_PRE_VERIFY_INFO  );
					return;
				}
			}

			//Pre-verify info exists so begin verification process.
			BeginWaitCursor ();
			
			//Initialize counters for results.
			InitResultObjects ();
			
			if( dlg.m_bConnInterfaces )
			{
				VerifyConnectionPointInterfaces ();
				iNumInterfacesTested ++;
			}
				
			if ( dlg.m_bDataObject ) 
			{
				VerifyIDataObject (); 
				iNumInterfacesTested ++;
			}
		
			if ( dlg.m_bDispatch ) 
			{
				VerifyIDispatch ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bExtConn ) 
			{
				VerifyIExternalConnection ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleCache ) 
			{
				VerifyIOleCache ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleCache2 ) 
			{
				VerifyIOleCache2 ();
				iNumInterfacesTested ++;
			}
					
			if ( dlg.m_bOleCacheControl ) 
			{
				VerifyIOleCacheControl ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleControl ) 
			{
				VerifyIOleControl ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleInPlaceActiveObject ) 
			{
				VerifyIOleInPlaceActiveObject ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleInPlaceObject ) 
			{
				VerifyIOleInPlaceObject ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bOleObject ) 
			{
				VerifyIOleObject ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bProvideClassInfo ) 
			{
				VerifyIProvideClassInfo ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bPersistPropBag ) 
			{
				VerifyIPersistPropertyBag ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bPersistStorage ) 
			{
				VerifyIPersistStorage ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bPersistStream ) 
			{
				VerifyIPersistStream ();
				iNumInterfacesTested ++;
			}
			
			if ( dlg.m_bPersistStreamInit ) 
			{
				VerifyIPersistStreamInit ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bRunObject ) 
			{
				VerifyIRunnableObject ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bSpecPropPages ) 
			{
				VerifyISpecifyPropertyPages ();
				iNumInterfacesTested ++;
			}
	
			if ( dlg.m_bViewObject2 )
			{
				VerifyIViewObject2 ();
				iNumInterfacesTested ++;
			}
	
			EndWaitCursor ();
			
			//Initialize flag to display summary message at end of tes
			//and display results of specific verifications.
			if ( iNumInterfacesTested == NUM_INTERFACES )
			{
				m_bAllInterfacesTested = TRUE;
			}
			else 
			{
				m_bAllInterfacesTested = FALSE;
			}
			
			OnViewResults ();
		}	
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleInPlaceObject
//PURPOSE:
//	Verifies the existence of the IOleInPlaceObject interface by calling all 
//	of its member functions. The IOleInPlaceObject interface manages the 
//	activation and deactivation of in-place objects, and determines how much
//	of the in-place object should be visible. 
//INPUT PARAMETER ( s):	
//	None
//OUTPUT PARAMETER ( s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleInPlaceObject ()
{
	ASSERT ( this != NULL );

	LPOLEINPLACEOBJECT lpIOleInPlaceObject = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleInPlaceObject, 
										 ( void ** )  &lpIOleInPlaceObject );
	VerifyInterfaceOrMethod ( hResult, IDS_OLEINPLACEOBJECT_QI, TRUE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleInPlaceObject != NULL ) )
	{
		ASSERT_POINTER ( lpIOleInPlaceObject, IOleInPlaceObject );
		
		//IOleWindow::GetWindow returns the window handle to one of the 
		//windows participating in in-place activation (frame, document, 
		//parent, or in-place object window).
		HWND hWnd;
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->GetWindow ( &hWnd ),
								IDS_OLEINPLACEOBJECT_GW, TRUE );

		//SetObjectsRects indicates how much of the in-place object is visible.
		LPCRECT lprcPosRect = CRECT_CONTROL;
		LPCRECT lprcClipRect = CRECT_CONTROL;
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->SetObjectRects 
								( lprcPosRect,lprcClipRect ),
								IDS_OLEINPLACEOBJECT_SOR, TRUE );
		
		//IOleWindow::ContextSensitiveHelp determines whether context-sensitive
		//help mode should be entered during an in-place activation session.
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->ContextSensitiveHelp 
								( FALSE ), IDS_OLEINPLACEOBJECT_CSH, FALSE );

		//InPlaceActivate deactivates an active in-place object and discards 
		//the object's undo state.
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->InPlaceDeactivate (), 
							IDS_OLEINPLACEOBJECT_IPD, TRUE );

		//UIDeactivate deactivates and removes the user interface that supports
		//in-place activation.
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->UIDeactivate (), 
								IDS_OLEINPLACEOBJECT_UID, TRUE );

		//ReactivateAndUndo reactivates a previously deactivated object, 
		//undoing the last state of the object.
		VerifyInterfaceOrMethod ( lpIOleInPlaceObject->ReactivateAndUndo (), 
								IDS_OLEINPLACEOBJECT_RAU, FALSE );

		//If the control is not hidden at runtime, show control from the 
		//loaded state since previous call to InPlaceDeactivate deactivated it.
		if ( ! m_bInvisibleAtRuntime )
		{
			ASSERT ( m_pControlSite->m_pObject != NULL );

			if ( m_pControlSite->m_pObject != NULL )
			{
				//Use the IOleObject ptr provided by COleControlSite to 
				//save a QI call.
				m_pControlSite->m_pObject->DoVerb ( OLEIVERB_INPLACEACTIVATE, 
					NULL, ( LPOLECLIENTSITE ) m_pControlSite->GetInterface 
					( &IID_IOleClientSite ), 0, this->m_hWnd,CRECT_CONTROL );
			}
		}

		lpIOleInPlaceObject->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleObject
//PURPOSE:
//	Verifies the existence of the IOleObject interface by calling all of its
//  member functions. The IOleObject interface is the central interface by 
//  which an OLE control object provides 
//  functionality to its container.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleObject ()
{
	ASSERT ( this != NULL );

	LPOLEOBJECT lpIOleObject = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleObject, 
										 ( void ** )  &lpIOleObject );
	VerifyInterfaceOrMethod ( hResult, IDS_OLEOBJECT_QI, TRUE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleObject != NULL ) )
	{
		ASSERT_POINTER ( lpIOleObject, IOleObject );

		//GetExtent retrieves the object’s current natural compositional 
		//extent, the one that the object will in fact use.	 Mandatory only
		//for DVASPECT_CONTENT
		SIZEL sizel;
		VerifyInterfaceOrMethod ( lpIOleObject->GetExtent ( DVASPECT_CONTENT,
								&sizel ), IDS_OLEOBJECT_GE, TRUE );
		
		//SetExtent sets the rectangular extent of the OLE object. Containers
		//call this function to inform objects how much space is available to
		//them. Both of these are mandatory only for DVASPECT_CONTENT.	 
		VerifyInterfaceOrMethod ( lpIOleObject->SetExtent ( DVASPECT_CONTENT,
								&sizel ), IDS_OLEOBJECT_SE, TRUE );

		//Close transitions the object back to the loaded state.
		VerifyInterfaceOrMethod ( lpIOleObject->Close ( OLECLOSE_NOSAVE ), 
								IDS_OLEOBJECT_C, TRUE );
	
		//GetMiscStatus returns a set of miscellaneous status information 
		//about the object.	Must be called before DoVerb to determine if the
		//control can be active or UI active.
		DWORD dwStatus;
		VerifyInterfaceOrMethod ( lpIOleObject->GetMiscStatus 
								( DVASPECT_CONTENT, &dwStatus ),
								IDS_OLEOBJECT_GMS, TRUE );
		
		//GetClientSite asks the object to return its current client site.
		LPOLECLIENTSITE lpOleClientSite;	
		VerifyInterfaceOrMethod ( hResult = lpIOleObject->GetClientSite 
								( &lpOleClientSite ),
								IDS_OLEOBJECT_GCS, TRUE );

		//SetClientSite informs the embedded object of its client site.  This
		//is, in fact, the only way through which the embedded object gets an
		//IOleClientSite pointer to the container's site object.
		VerifyInterfaceOrMethod ( lpIOleObject->SetClientSite 
								( lpOleClientSite ),
								IDS_OLEOBJECT_SCS, TRUE );
		
		//DoVerb informs the object that it should now perform one of its 
		//verbs.  
		if ( lpOleClientSite != NULL )
		{
			ASSERT_POINTER ( lpOleClientSite, IOleClientSite );

			//If the control is not hidden, activate it.  Otherwise, keep 
			//it hidden.
			if ( ! m_bInvisibleAtRuntime )
			{
				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_INPLACEACTIVATE , NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ), IDS_OLEOBJECT_DV_SHOW, 
								FALSE );
			}
			else
			{
				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_HIDE, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ),IDS_OLEOBJECT_DV_HIDE, 
								FALSE );
			}

			//If the control supports property pages, it must support 
			//OLEIVERB_PROPERTIES and OLEIVERB_PRIMARY.
			if ( m_bPropPages )
			{
				AfxMessageBox ( IDS_CLOSE_PROP_PAGES );

				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_PROPERTIES, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ), IDS_OLEOBJECT_DV_PROPS,
								TRUE );

				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_PRIMARY, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ), IDS_OLEOBJECT_DV_PRIMARY,
								TRUE );
			}
		
			//A control that can be in-place active must support the 
			//OLEIVERB_INPLACEACTIVATE verb. If one of the misc status bits 
			//is OLEMISC_INSIDEOUT, this means that the control	can be 
			//in-place active without being UI active; the object is capable
			//of activating	in place, without requiring installation of menus
			//and toolbars to run.
			if ( dwStatus & OLEMISC_INSIDEOUT )
			{
				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_INPLACEACTIVATE, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ), IDS_OLEOBJECT_DV_INSIDEOUT,
								TRUE );
			}
			
			//A control that can be UI active must support OLEIVERB_UIACTIVATE.
			//From the preverification process,	m_bUI is set if the can be UI
			//active depending upon this flag.
			if ( dwStatus & ~OLEMISC_NOUIACTIVATE )
			{
				VerifyInterfaceOrMethod ( lpIOleObject->DoVerb 
								( OLEIVERB_UIACTIVATE, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL ),IDS_OLEOBJECT_DV_UIACTIVE,
								TRUE );
				
				//OLEIVERB_UIACTIVATE can cause an exception based upon the 
				//value of its client site under certain circumstances.  
				//OLEIVERB_HIDE will ensure this does not happen, 
				//OLEIVERB_INPLACEACTIVATE simply redisplays it for the
				//remainder of the verification process.
				lpIOleObject->DoVerb ( OLEIVERB_HIDE, NULL, lpOleClientSite,
								0, this->m_hWnd, CRECT_CONTROL );
				lpIOleObject->DoVerb ( OLEIVERB_INPLACEACTIVATE, NULL, 
								lpOleClientSite, 0, this->m_hWnd, 
								CRECT_CONTROL );
			}

			//Hide the control again if it is invisible at runtime since 
			//some controls simply count on	never being visible at runtime.
			if ( m_bInvisibleAtRuntime )
			{
				lpIOleObject->DoVerb ( OLEIVERB_HIDE, NULL, 
									lpOleClientSite, 0, this->m_hWnd, 
									CRECT_CONTROL );
			}

			lpOleClientSite->Release ();
		}
		else
		{
			//Unable to test DoVerb since could not obtain a valid client site.
			//Record the fact that we cannot verify certain verbs. We have 
			//used OLEIVERB_SHOW as the test case for DoVerb if the control
			//is visible at run time; otherwise, we would have used 
			//OLEIVERB_HIDE.
			if ( ! m_bInvisibleAtRuntime )
			{
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_SHOW, TRUE, FALSE );
			}
			else
			{
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_HIDE, TRUE, FALSE );
			}

			if ( m_bPropPages )
			{
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_PROPS, TRUE, FALSE );
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_PRIMARY, TRUE, FALSE );
			}

			if ( dwStatus & OLEMISC_INSIDEOUT )
			{
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_INSIDEOUT, TRUE, FALSE );
			}
	
			if ( dwStatus & ~OLEMISC_NOUIACTIVATE )
			{
				NonStandardVerification ( IDS_OLEOBJECT_GCS, hResult, 
					V_PREV_FAILURE, IDS_OLEOBJECT_DV_UIACTIVE, TRUE, FALSE );
			}
		}

		//Advise establishes an advisory connection through which the
		//container receives notification tha the control object is renamed,
		//saved, or closed.
		DWORD dwConnection;		//Token to identify and release the 
								//connection at a later point.
		VerifyInterfaceOrMethod ( hResult = lpIOleObject->Advise 
					( m_lpIAdviseSink, &dwConnection ), 
					IDS_OLEOBJECT_A, TRUE );

		//EnumAdvise enumerates the advisory connections registered for an
		//object.  A container normally would call this function so that it
		//can instruct an object to release each of its advisory connections
		//prior to closing down.
		LPENUMSTATDATA lpEnumStatData = NULL;
		VerifyInterfaceOrMethod ( lpIOleObject->EnumAdvise ( &lpEnumStatData ), 
									IDS_OLEOBJECT_EA, FALSE );
		if ( lpEnumStatData != NULL )
		{
			lpEnumStatData->Release ();
		}
		
		//Unadvise deletes a previously established advisory connection 
		//created by Advise. Do not call this if Advise fails.
		if ( SUCCEEDED  ( hResult ) )
		{
			VerifyInterfaceOrMethod ( lpIOleObject->Unadvise ( dwConnection ),
									IDS_OLEOBJECT_U, TRUE );
		}
		else
		{
			//V_PREV_FAILURE is a custom error code for this application and 
			//is used to show that the interface was not verified.
			NonStandardVerification ( IDS_OLEOBJECT_EA, hResult, V_PREV_FAILURE,
								IDS_OLEOBJECT_U, TRUE, FALSE );
		}

		//SetHostNames specifies information to be used in window titles of 
		//the object when it is open for editing
		VerifyInterfaceOrMethod ( lpIOleObject->SetHostNames ( NULL, NULL ), 
									IDS_OLEOBJECT_SHN, TRUE );
	
		//GetMoniker answers a moniker which, when bound, will connect to the
		//object. OLEGETMONIKER_TEMPFORUSER indicates that if a moniker for 
		//the object does not exist, IOleObject::GetMoniker can create a 
		//temporary moniker that can be used for display purposes 
		//(IMoniker::GetDisplayName) but not for binding. This enables the 
		//object server to return a descriptive name for the object without
		//incurring the overhead of creating and maintaining a moniker until
		//a link is actually created. 
		LPMONIKER lpIMoniker = NULL;
		VerifyInterfaceOrMethod ( hResult = lpIOleObject->GetMoniker 
						( OLEGETMONIKER_TEMPFORUSER, 
						OLEWHICHMK_CONTAINER, &lpIMoniker ), 
						IDS_OLEOBJECT_GM, FALSE );
	
		if ( ( SUCCEEDED  ( hResult ) ) && ( lpIMoniker != NULL ) )
		{
			//SetMoniker informs the object of either its own moniker or 
			//its container’s moniker.  The OLEWHICHMK enumeration constants
			//indicate which part of an object's moniker is being set or 
			//retrieved. 
			VerifyInterfaceOrMethod ( lpIOleObject->SetMoniker 
								( OLEWHICHMK_OBJFULL, lpIMoniker ), 
								IDS_OLEOBJECT_SM, FALSE );
		}
		else
		{
			NonStandardVerification ( IDS_OLEOBJECT_GM, hResult, V_PREV_FAILURE, 
								IDS_OLEOBJECT_SM, FALSE, FALSE );
		}

		//InitFromData initializes the contents of the object from the various 
		//formats, etc., which are available from the passed pDataObject.
		VerifyInterfaceOrMethod ( lpIOleObject->InitFromData 
								( NULL, FALSE, 0 ),
								IDS_OLEOBJECT_IFD, FALSE );
		
		//GetClipboardData returns a Clipboard Data Object contains exactly 
		//what would have been passed to OleSetClipboard() if the contents
		//of the object were to be selected and Edit / Copy chosen. 
		VerifyInterfaceOrMethod ( lpIOleObject->GetClipboardData 
								( 0, &m_lpIDataObject ), 
								IDS_OLEOBJECT_GCD, FALSE );
		
		//EnumVerbs enumerates all the verbs available on this object in 
		//increasing order by verb number. 
		LPENUMOLEVERB lpIEnumOLEVERB;
		VerifyInterfaceOrMethod ( lpIOleObject->EnumVerbs ( &lpIEnumOLEVERB ), 
									IDS_OLEOBJECT_EV, TRUE );
	
		//Update ensures that any data or view caches maintained inside the
		//object are up to date
		VerifyInterfaceOrMethod ( lpIOleObject->Update (), 
									IDS_OLEOBJECT_UP, TRUE );
		
		//IsUpToDate recursively checks whether the object's link(s) are 
		//up-to-date.
		VerifyInterfaceOrMethod ( lpIOleObject->IsUpToDate (), 
									IDS_OLEOBJECT_IUTD, TRUE );
		
		//GetUserClassID returns the class whose registration database entries
		//regarding verbs, etc., are the appropriate ones to show to the user.
		CLSID pClsid;
		VerifyInterfaceOrMethod ( lpIOleObject->GetUserClassID ( &pClsid ),
									IDS_OLEOBJECT_GUCID, TRUE );
		
		//SetColorScheme informs the object of the color palette recommended
		//by the container application
		LOGPALETTE Logpal;
		VerifyInterfaceOrMethod ( lpIOleObject->SetColorScheme ( &Logpal ), 
									IDS_OLEOBJECT_SCSC, FALSE );
		
	
		//GetUserType answers a user presentable identification of this 
		//object’s type: "Word Document", "Microsoft Drawing", etc.; 
		//Here we choose to return the full class name.
		unsigned short *  pszUserType;
		VerifyInterfaceOrMethod ( lpIOleObject->GetUserType 
								( USERCLASSTYPE_FULL, &pszUserType ), 
								IDS_OLEOBJECT_GUT, TRUE );

		lpIOleObject->Release ();
	}  
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIDataObject
//PURPOSE:
//	Verifies the existence of the IDataObject interface by calling all of its
//  member functions. The IDataObject interface provides data transfer 
//	capabilities and notification of changes in data. The format of the 
//	transferred data is specified along with the medium through which OLE
//  transfers the data. Optionally, the data can be rendered for a specific
//  target device. In addition to retrieving and storing data, the IDataObject
//  interface contains methods to enumerate available formats and to set up an
//  advisory sink for handling change notifications.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIDataObject ()
{
	ASSERT ( this != NULL );

	LPDATAOBJECT lpIDataObject = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IDataObject, 
											 ( void ** ) &lpIDataObject );
	VerifyInterfaceOrMethod ( hResult, IDS_DATAOBJECT_QI, m_bPropSets );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIDataObject != NULL ) )
	{
		ASSERT_POINTER ( lpIDataObject, IDataObject );

		FORMATETC formatEtc, formatEtcOut, formatEtcIn;
		FORMATETC myFormat;
		LPENUMFORMATETC lpEnumFormatEtc = NULL;
		STGMEDIUM stgMedium;

		//The FORMATETC structure is used to describe the data to be 
		//transferred. Use CF_METAFILEPICT since this is mandatory in the
		//guidelines.
		formatEtc.cfFormat = CF_TEXT;
		formatEtcIn.cfFormat = CF_TEXT;

		//Points to a DVTARGETDEVICE structure to obtain information about
		//the target device that data was composed; NULL if don't care.	
		formatEtc.ptd = NULL;
		formatEtcIn.ptd = NULL;
		
		//One of the DVASPECT enumeration constants that indicate how much
		//detail should be contained in the rendering.
		formatEtc.dwAspect = DVASPECT_CONTENT;
		formatEtcIn.dwAspect = DVASPECT_CONTENT;

		//Identifies part of the aspect when the data must be split across 
		//page boundaries. The most common value is -1, which identifies all 
		//of the data.
		formatEtc.lindex = -1;
		formatEtcIn.lindex = -1;

		//Specifies one of the TYMED enumeration constants which indicate
		//the type of storage medium used to transfer the object's data.  
		formatEtc.tymed = TYMED_HGLOBAL;
		formatEtcIn.tymed = TYMED_HGLOBAL;

		//The STGMEDIUM structure is a generalized global memory handle for
		//data xfer. Indicate the type of storage medium through the TYMED
		//enumeration.
		stgMedium.tymed = TYMED_HGLOBAL;

		//Specifies a handle, string, or interface pointer that the receiving
		//process can use to access the data being transferred.  Here, use the
		//IStream pointer created during initialization in the call to 
		//CreateStorageObjects.
		ASSERT ( m_lpIStream != NULL );
		ASSERT_POINTER ( m_lpIStream, IStream );
		stgMedium.pstm = NULL;

		//Points to an interface instance that allows the sending process to 
		//control the way the storage is released when the receiving process
		//calls the ReleaseStgMedium function. If pUnkForRelease is NULL, 
		//ReleaseStgMedium uses default procedures to release the storage;
		stgMedium.pUnkForRelease = NULL;
		
		ASSERT ( AfxIsValidAddress ( &formatEtc, sizeof ( FORMATETC ), 
																FALSE ) );
		ASSERT ( AfxIsValidAddress ( &formatEtcIn, sizeof ( FORMATETC ),
																FALSE ) );
		ASSERT ( AfxIsValidAddress ( &stgMedium, sizeof ( STGMEDIUM), 
																FALSE ) );
		
		//DAdvise sets up an advisory connection, and DUnadvise cancels it.
		DWORD dwConnection;
		VerifyInterfaceOrMethod ( hResult = lpIDataObject->DAdvise 
						( &formatEtc, ADVF_NODATA, m_lpIAdviseSink, 
						&dwConnection ), IDS_DATAOBJECT_DA, m_bPropSets );
	
		if ( SUCCEEDED  ( hResult ) )
		{
			VerifyInterfaceOrMethod ( lpIDataObject->DUnadvise 
						( dwConnection ),IDS_DATAOBJECT_DU, m_bPropSets );
		}
		else
		{
			NonStandardVerification ( IDS_DATAOBJECT_DA, hResult, V_PREV_FAILURE, 
								IDS_DATAOBJECT_DU, m_bPropSets, FALSE );
		}
		
		//EnumDAdvise enumerate the advisory connections currently found on
		//this object
		LPENUMSTATDATA penumAdvise;
		VerifyInterfaceOrMethod ( lpIDataObject->EnumDAdvise ( &penumAdvise ), 
								IDS_DATAOBJECT_EDA, m_bPropSets );

		//EnumFormatEtc enumerates the forms in which data can be stored into
		//or retrieved from this object with SetData and GetData, respectively.
		//DATADIR_GET enumerates formats that can be passed by GetData.
		VerifyInterfaceOrMethod ( hResult = lpIDataObject->EnumFormatEtc 
								( DATADIR_GET, &lpEnumFormatEtc ), 
								IDS_DATAOBJECT_EFE, m_bPropSets );

		if ( lpEnumFormatEtc != NULL )
		{
			hResult = lpEnumFormatEtc->Next ( 1, &myFormat, NULL );
			lpEnumFormatEtc->Release ();
		}
		
		//Make the format the same as the control.
		stgMedium.tymed = myFormat.tymed;

		//QueryGetData gets information that if this FORMATETC were to be 
		//passed to GetData() then data would be successfully retrieved. 
		VerifyInterfaceOrMethod ( lpIDataObject->QueryGetData ( &myFormat ), 
								IDS_DATAOBJECT_QGD, m_bPropSets );

		//GetData retrieves data for a certain aspect of the object in a 
		//certain clipboard format formatted for a certain target device 
		//conveyed on a certain storage medium.
		VerifyInterfaceOrMethod ( lpIDataObject->GetData 
								( &myFormat, &stgMedium ), 
								IDS_DATAOBJECT_GD, m_bPropSets );

		//GetDataHere is almost identical to ::GetData(), but the caller 
		//provides the medium instead of the callee; the callee just copies
		//data into the medium that the caller provides. 
		VerifyInterfaceOrMethod ( lpIDataObject->GetDataHere 
								( &myFormat, &stgMedium ), 
								IDS_DATAOBJECT_GDH, m_bPropSets );

		//SetData sends data in a specified format, etc., to this object.  
		VerifyInterfaceOrMethod ( lpIDataObject->SetData 
								( &myFormat, &stgMedium, FALSE ),	
								IDS_DATAOBJECT_SD, m_bPropSets );

		//A data object can return exactly the same data even though you have
		//specified different FORMATETC structures in subsequent requests to
		//retrieve data. For example, the same data can be returned for 
		//different target devices if the data is not sensitive to the target
		//devices.  The data returned is insensitive to the particular target 
		//device.  This allows consumers to more efficiently store the data
		//that is returned.
		VerifyInterfaceOrMethod ( lpIDataObject->GetCanonicalFormatEtc 
								( &formatEtcIn, &formatEtcOut ), 
								IDS_DATAOBJECT_GCFE, m_bPropSets );

		lpIDataObject->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIViewObject2
//PURPOSE:
//	Verifies the existence of the IViewObject2 interface by calling all of 
//	its member functions. The IViewObject2 interface is an extension to the
//  IViewObject2 interface which returns the size of the drawing for a given
//  view of an object.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIViewObject2 ()
{
	ASSERT ( this != NULL );

	LPVIEWOBJECT2 lpIViewObject2 = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IViewObject2, 
											 ( void ** )  &lpIViewObject2 );
	VerifyInterfaceOrMethod ( hResult, IDS_VIEWOBJECT2_QI, TRUE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIViewObject2 != NULL ) )
	{
		ASSERT_POINTER ( lpIViewObject2, IViewObject2 );

		//Freeze freezes a certain aspect of the object's presentation so 
		//that it does not change until the Unfreeze method is called.
		DWORD dwFreeze;	 //Points to identifying key used later used to 
						 //cancel the freeze through Unfreeze.

		VerifyInterfaceOrMethod ( hResult = lpIViewObject2->Freeze 
								( DVASPECT_CONTENT, -1, 
								NULL, &dwFreeze ), IDS_VIEWOBJECT2_F, FALSE );

		if ( SUCCEEDED ( hResult ) )
		{
			VerifyInterfaceOrMethod ( lpIViewObject2->Unfreeze ( dwFreeze ), 
									IDS_VIEWOBJECT2_U, FALSE );
		}
		else
		{
			NonStandardVerification ( IDS_VIEWOBJECT2_F, hResult, V_PREV_FAILURE, 
								IDS_VIEWOBJECT2_U, FALSE, FALSE );
		}

		//SetAdvise sets up a connection between the view object and an 
		//advise sink so that the advise sink can be notified about changes
		//in the object's view.
		VerifyInterfaceOrMethod ( hResult = lpIViewObject2->SetAdvise 
								( DVASPECT_CONTENT, ADVF_PRIMEFIRST, NULL ),
									IDS_VIEWOBJECT2_SA, TRUE );

		//GetAdvise retrieves the existing advisory connection on the object
		//if there is one.This method simply returns the parameters used in 
		//the most recent call to SetAdvise method.
		if ( FAILED ( hResult ) )
		{
			//V_PREV_FAILURE is a custom error code for this application and
			//is used to show that the interface was not verified.
			NonStandardVerification ( IDS_VIEWOBJECT2_SA, hResult, 
								V_PREV_FAILURE, IDS_VIEWOBJECT2_GA, TRUE, FALSE );
		}
		else
		{
			DWORD dwAspect;	//Points to location of dwAspect parameter from
							//previous SetAdvise
			DWORD advf;		//Points to location of advf parameter from 
							//previous SetAdvise
			LPADVISESINK lpAdvSink = NULL;	//Points to location of pAdvSink
											//parameter from previous SetAdvise
			VerifyInterfaceOrMethod ( lpIViewObject2->GetAdvise 
								( &dwAspect, &advf, &lpAdvSink ),
								IDS_VIEWOBJECT2_GA, TRUE );

			if ( lpAdvSink != NULL )
			{
				lpAdvSink->Release ();
			}
		}
		
		//GetColorSet returns the logical palette that the object will use 
		//for drawing in its method with the corresponding parameters. 
	    LOGPALETTE * colorSet;
		VerifyInterfaceOrMethod ( lpIViewObject2->GetColorSet 
								( DVASPECT_CONTENT, -1, NULL, NULL,
								NULL, &colorSet ), IDS_VIEWOBJECT2_GCS, FALSE );
		
		//GetExtent returns the size that the specified view object will be
		//drawn on the specified target device.  To prevent the object from 
		//being run if it isn't already running, you can call 
		//IViewObject2::GetExtent rather than IOleObject::GetExtent to 
		//determine the size of the presentation to be drawn.
		SIZEL sizel;
		VerifyInterfaceOrMethod ( lpIViewObject2->GetExtent 
								( DVASPECT_CONTENT, -1, NULL, &sizel ), 
								IDS_VIEWOBJECT2_GE, TRUE );
		
		//Draw will draw a representation of an object onto the specified 
		//device context. If the control is invisible at runtime, there is
		//no need to call this.
		if ( m_bInvisibleAtRuntime )
		{
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_VIEWOBJECT2_D, FALSE, FALSE );
		}
		else
		{
			CClientDC dc ( this );
			dc.GetSafeHdc ();
			RECTL rectl;
			rectl.top = 100;   
			rectl.left = 250;
			rectl.right = 350;
			rectl.bottom = 200;
			VerifyInterfaceOrMethod ( lpIViewObject2->Draw 
									( DVASPECT_CONTENT, -1, NULL, NULL, 
									0, dc.m_hDC, &rectl, NULL, NULL, 0 ),
									IDS_VIEWOBJECT2_D, TRUE );
		}

		lpIViewObject2->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIDispatch 
//PURPOSE:
//	Verifies the existence of the IDispatch interface by calling all of its
//	member functions.  OLE Automation objects may implement the IDispatch 
//	interface for access by OLE Automation controllers, such as Visual Basic.
//	The object's properties and methods can be accessed using 
//	IDispatch::GetIDsOfNames and IDispatch::Invoke.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIDispatch ()
{
	ASSERT ( this != NULL );
	
	LPDISPATCH lpIDispatch = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IDispatch, 
											 ( void ** )  &lpIDispatch );
	VerifyInterfaceOrMethod ( hResult, IDS_DISPATCH_QI, m_bPropsMethods );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIDispatch != NULL ) )
	{
		ASSERT_POINTER ( lpIDispatch, IDispatch );

		//GetTypeInfoCount retrieves the number of type information interfaces
		//an object provides.  If the object provides type information, this
		//number is 1; otherwise the number is 0.
		UINT nCtInfo;
		VerifyInterfaceOrMethod ( lpIDispatch->GetTypeInfoCount ( &nCtInfo ), 
						IDS_DISPATCH_GTIC, m_bPropsMethods );

		//GetTypeInfo retrieves a type information object, which can be used 
		//to get the type information for an interface
		LPTYPEINFO lpTypeInfo = NULL;			//Ptr to TypeInfo object 
		VerifyInterfaceOrMethod ( lpIDispatch->GetTypeInfo ( 
						0,						//0 retrieves type info 
												//for the IDispatch 
						LOCALE_SYSTEM_DEFAULT,	//Locale ID for the type info
						&lpTypeInfo ),			//Ptr to the type info object.
						IDS_DISPATCH_GTI, 
						m_bPropsMethods );

		//GetIDsOfNames retrieves a corresponding set of integer DISPIDs for 
		//the indicated method or property. 
		DISPID dispid;
		OLECHAR * rgszNames[] = { OLESTR ( "Dummyname" ) };
		VerifyInterfaceOrMethod ( lpIDispatch->GetIDsOfNames ( 
						IID_NULL,	//Reserved for future use;must be NULL.
						rgszNames,	//Passed-in array of names to be mapped.		
						1,			//Count of the names to be mapped.
						LOCALE_SYSTEM_DEFAULT,	//Locale context.
						&dispid ),				//Return value of dispid.
						IDS_DISPATCH_GIDON,
						m_bPropsMethods );

		//Invoke uses the dispid returned by GetIDsOfNames to invoke a method
		//or get/set property.
		VARIANT lpVarResult;	//Dummy variable to hold result from Invoke.
		EXCEPINFO excepInfo;
		UINT nArgErr;
		DISPPARAMS dispparams;

		dispparams.rgvarg = 0;
		dispparams.rgdispidNamedArgs = 0;
    	dispparams.cArgs = 0;
    	dispparams.cNamedArgs = 0;

		//Code to handle automation exceptions.	 This will handle any hResult, 
		//then the exception will be handled.  
		try
		{
		hResult = lpIDispatch->Invoke ( 
					222,		//Dummy Dispid of method or property.
					IID_NULL,	//Reserved for future use; must be NULL.
					LOCALE_SYSTEM_DEFAULT,	//Locale context in which to 
											//interpret the names.
					DISPATCH_PROPERTYGET,	//To signify invoking a method 
											//vice get/set a property.
					&dispparams,	//Array of information on parameters 
									//to the method.
					&lpVarResult,	//Return value from call
					&excepInfo, 
					&nArgErr );
		}
		catch ( COleDispatchException e )
		{
			//If Invoke is not implemented, an exception will not occur so we
			//can be sure that we have an hResult (success or failure) if this
			//happens.  Therefore, there is not a need to classify result as 
			//not verified.
			e.Delete ();
		}

		//Record result of calling Invoke regardless of whether exception 
		//occurred or not.
		VerifyInterfaceOrMethod ( hResult, IDS_DISPATCH_I, m_bPropsMethods );

		lpIDispatch->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIProvideClassInfo 
//PURPOSE:
//	Verifies the existence of the IProvideClassInfo interface by calling its
//  only member function, GetClassInfo, to return a CoClass TypeInfo that 
//  describes the connectable object.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIProvideClassInfo ()
{
	ASSERT ( this != NULL );
	
	LPPROVIDECLASSINFO lpIProvideClassInfo = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IProvideClassInfo, 
										( void ** )  &lpIProvideClassInfo );
	VerifyInterfaceOrMethod ( hResult, IDS_PROVIDECLASSINFO_QI, TRUE );
		
	if ( SUCCEEDED  ( hResult )  &&  ( lpIProvideClassInfo != NULL ) )
	{
		ASSERT_POINTER ( lpIProvideClassInfo, IProvideClassInfo );

		//GetClassInfo returns a CoClass TypeInfo describing connectable object. 
		LPTYPEINFO lpTypeInfo = NULL;
		VerifyInterfaceOrMethod ( lpIProvideClassInfo->GetClassInfo 
								( &lpTypeInfo ), 
								IDS_PROVIDECLASSINFO_GCI, TRUE );
		
		lpIProvideClassInfo->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIPersistStorage 
//PURPOSE:
//	Verifies the existence of the IPersistStorage interface by calling its 
//	member functions.	The IPersistStorage interface enables a container 
//	application to pass a storage object to one of its contained objects and
//	to load and save the storage object. This interface	supports the 
//	structured storage scheme in which each component object has its own 
//	storage that is nested within the container's storage.  
//	There is a mention of two terms here:
//	"NoScribble mode" - The object must not write to its file.
//	"HandsOff mode" - The object cannot do anything except a close operation.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIPersistStorage ()
{
	ASSERT ( this != NULL );
	
	LPPERSISTSTORAGE lpIPersistStorage = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IPersistStorage, 
											( void ** )  &lpIPersistStorage );
	VerifyInterfaceOrMethod ( hResult, IDS_PERSISTSTORAGE_QI, TRUE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIPersistStorage != NULL ) )
	{
		ASSERT_POINTER ( lpIPersistStorage, IPersistStorage );
		ASSERT ( m_lpIStorage != NULL );
		ASSERT_POINTER ( m_lpIStorage, IStorage );

		//IsDirty indicates whether the object has changed since it was last
		//saved to its current storage.	
		VerifyInterfaceOrMethod ( lpIPersistStorage->IsDirty (),
							IDS_PERSISTSTORAGE_ID, TRUE );
		
		//NOTE; The order matters here for InitNew, Save, and Load or Load 
		//will fail. InitNew initializes a new storage object.
		VerifyInterfaceOrMethod ( lpIPersistStorage->InitNew ( m_lpIStorage ), 
							IDS_PERSISTSTORAGE_IN, TRUE );
		
		//Save saves an object, and any nested objects that it contains, into
		//the specified storage object. The object is placed in NoScribble 
		//mode, and it must not write to the specified storage until it 
		//receives a call to SaveCompleted
		VerifyInterfaceOrMethod ( lpIPersistStorage->Save ( m_lpIStorage, 
							TRUE ), IDS_PERSISTSTORAGE_S, TRUE );
		
		//Load initializes an object from its existing storage.
		VerifyInterfaceOrMethod ( lpIPersistStorage->Load ( m_lpIStorage ), 
							IDS_PERSISTSTORAGE_L, TRUE );
			
		//SaveCompleted notifies the object that it can revert from NoScribble
		//or HandsOff mode, in which it must not write to its storage object,
		//to Normal mode, in which it can. The component object enters 
		//NoScribble mode when it receives an Save call. 
		VerifyInterfaceOrMethod ( lpIPersistStorage->SaveCompleted 
							( m_lpIStorage ), 
							IDS_PERSISTSTORAGE_SC, TRUE );
		
		//HandsOffStorage instructs the object to release all storage objects
		//that have been passed to it by its container and to enter HandsOff
		//mode, in which the object cannot do anything and the only operation
		//that works is a close operation.
		VerifyInterfaceOrMethod ( lpIPersistStorage->HandsOffStorage (), 
							IDS_PERSISTSTORAGE_HOS, TRUE );

		lpIPersistStorage->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleInPlaceActiveObject 
//PURPOSE:
//	Verifies the existence of the IOleInPlaceActiveObject interface by 
//	calling all of its member functions.  The IOleInPlaceActiveObject provides
//	a direct channel of communication between an in-place object and the 
//	associated application's outer-most frame window and the document window
//	within the application that contains the embedded object. The 
//	communication involves the translation of messages, the state of the frame
//	window (activated or deactivated), and the state of the document window 
//	(activated or deactivated). It also informs the object when its needs to
//	resize its borders, and manages modeless dialog boxes. This also includes
//	IOleWindow methods of GetWindow and ContextSensitiveHelp, which are called
//	above in VerifyIOleInPlaceObject. For controls without a user interface
//	this is an optional interface.	Certain methods will fail if called on a
//	hidden control and are noted in the code.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None						
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleInPlaceActiveObject ()
{
	ASSERT ( this != NULL );

	LPOLEINPLACEACTIVEOBJECT lpIOleInPlaceActiveObject = NULL;
	HRESULT hResult = S_OK;
	BOOL bQI = FALSE;	//Set to TRUE if we obtain ptr through QI; FALSE if 
						//from SetActiveObject.
	  	
	if ( g_lpIOleInPlaceActiveObject == NULL )				   
	{
		//The object has not yet been made active via a call to 
		//CVControlCtnr::XVOleInPlaceFrame::SetActiveObject.  Therefore, set
		//focus (activate it), causing it to be called.
		m_pControlSite->SetFocus ();					 
	}

	//At this point, setting the control to an active state should have set 
	//g_lpIOleInPlaceActiveObject to the control's IOleInPlaceActiveObject 
	//interface.  If for some reason this did not work, try to QI for this as
	//a last resort.
	if ( g_lpIOleInPlaceActiveObject != NULL )
	{
		lpIOleInPlaceActiveObject = g_lpIOleInPlaceActiveObject;
		
		NonStandardVerification ( IDS_SETACTIVEOBJECT, S_OK, 
						V_NOT_QI_OBTAINED, IDS_OLEINPLACEACTIVEOBJECT,
						m_bUI, TRUE );
	}
	else
	{
		//If run against a correctly written control, this should never be called.
		LPOLEINPLACEACTIVEOBJECT lpIOleInPlaceActiveObject = NULL;
		HRESULT hResult = m_lpIUnknown->QueryInterface 
							( IID_IOleInPlaceActiveObject, 
							( void ** )  &lpIOleInPlaceActiveObject );
		VerifyInterfaceOrMethod ( hResult, IDS_OLEINPLACEACTIVEOBJECT, m_bUI );

		bQI = TRUE;		//For purposes of releasing later.
	}

	if ( SUCCEEDED ( hResult ) && ( lpIOleInPlaceActiveObject != NULL ) )
	{
		//At this point, we have a pointer to the control's 
		//IOleInPlaceActiveObject interface, whether it was obtained from 
		//SetActiveObject or QI.
		ASSERT_POINTER ( lpIOleInPlaceActiveObject, IOleInPlaceActiveObject );

		//IOleWindow::GetWindow returns the window handle to one of the windows
		//participating in in-place activation (frame, document, parent, or 
		//in-place object window).
		HWND hWnd;
		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->GetWindow 
								( &hWnd ), IDS_OLEINPLACEACTIVEOBJECT_GW, m_bUI );

		//TranslateAccelerator processes menu accelerator-key messages from 
		//the container's message queue, and is only mandatory if the control 
		//supports accelerator keys.
		MSG msg;		//Message that might need to be translated.
		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->
							TranslateAccelerator ( &msg ),
							IDS_OLEINPLACEACTIVEOBJECT_TA, 
							m_bAccelerators );
		
		//EnableModeless enables or disables modeless dialog boxes when the 
		//container creates or destroys a modal dialog box.
		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->EnableModeless
							( FALSE ), IDS_OLEINPLACEACTIVEOBJECT_EM, m_bUI );
		
		//OnDocWindowActivate notifies the active in-place object when the 
		//container's document window is activated or deactivated
		//NOTE: This will fail on hidden controls so do not call it if the 
		//control is invisible at runtime.
		if ( ! m_bInvisibleAtRuntime )
		{
			VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->
								OnDocWindowActivate ( TRUE ), 
								IDS_OLEINPLACEACTIVEOBJECT_ODWA, TRUE );
		}
		else 
		{
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_OLEINPLACEACTIVEOBJECT_ODWA, FALSE, FALSE );
		}

		//OnFrameWindowActivate notifies the object when the container's 
		//top-level frame window is activated or deactivated.
		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->
							OnFrameWindowActivate ( TRUE ),
							IDS_OLEINPLACEACTIVEOBJECT_OFWA, m_bUI );

		//IOleWindow::ContextSensitiveHelp determines whether context-sensitive 
		//help mode should be entered during an in-place activation session.
		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->
							ContextSensitiveHelp ( FALSE ), 
							IDS_OLEINPLACEACTIVEOBJECT_CSH, FALSE );
		
		//ResizeBorder alerts the object that it needs to resize its border 
		//space. A ptr to the container's IOleInPlaceUIWindow must be passed 
		//in.  The MFC COleControlContainer class does not support this 
		//interface but it does support	IOleInPlaceFrame, which is derived
		//from this. Therefore, simply cast the pointer into an 
		//IOleInPlaceWindow ptr.
		LPOLEINPLACEUIWINDOW lpIOleInPlaceUIWindow =  
			( LPOLEINPLACEUIWINDOW ) m_pCtrlCont->GetInterface 
							( &IID_IOleInPlaceFrame );

		RECT rcBorder;	//Outer rectangle for border space
		rcBorder.left = 100;
		rcBorder.top = 100; 
		rcBorder.right = 200; 
		rcBorder.bottom = 200;

		VerifyInterfaceOrMethod ( lpIOleInPlaceActiveObject->ResizeBorder  
						(&rcBorder, lpIOleInPlaceUIWindow, FALSE),
						IDS_OLEINPLACEACTIVEOBJECT_RB, m_bUI );
	}			
	else
	{
		//Log the fact that this interface is not implemented on the control.
		VerifyInterfaceOrMethod ( hResult, IDS_OLEINPLACEACTIVEOBJECT, m_bUI );
	}

	
	//Release the interface pointer if we obtained if from QI as a last resort.
	if ( ( lpIOleInPlaceActiveObject != NULL ) && ( bQI ) ) 
	{
		lpIOleInPlaceActiveObject->Release ();
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleControl
//PURPOSE:
//	Verifies the existence of the IOleControl interface by calling all of its
//	member functions.  OLE controls introduce a pair of interfaces used for 
//  communication between the control and its container that goes beyond the 
//	normal communication defined by the OLE Compound Documents interfaces. 
//	The control implements an interface IOleControl, and the container
//  implements an interface IOleControlSite on its site objects:
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleControl ()
{
	ASSERT ( this != NULL );

	LPOLECONTROL lpIOleControl = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleControl, 
											 ( void ** )  &lpIOleControl );
	//IOleControl is mandatory if the control uses ambient properties or 
	//mnemonics.
	VerifyInterfaceOrMethod ( hResult, IDS_OLECONTROL_QI,  
								m_bAmbients || m_bMnemonics );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleControl != NULL ) )
	{
		ASSERT_POINTER ( lpIOleControl, IOleControl );
		
		//At load time, a control container asks each embedded control for
		//CONTROLINFO via GetControlInfo. The control uses the struct to 
		//return an accelerator table containing the mnemonics it wants to
		//expose when not UI active.
		CONTROLINFO ctlInfo;
		VerifyInterfaceOrMethod ( lpIOleControl->GetControlInfo ( &ctlInfo ), 
							IDS_OLECONTROL_GCI, m_bMnemonics );

		//OnMnemonic is called when a mnemonic key of the OLE control has 
		//been pressed.
		MSG msg;
		VerifyInterfaceOrMethod ( lpIOleControl->OnMnemonic ( &msg ), 
							IDS_OLECONTROL_OM, m_bMnemonics );

		//OnAmbientPropertyChange notifies the control that an ambient 
		//property is changed.
		VerifyInterfaceOrMethod ( lpIOleControl->OnAmbientPropertyChange 
							( DISPID_UNKNOWN ), 
							IDS_OLECONTROL_OAPC, m_bAmbients );

		//FreezeEvents is called if a container wishes to stop receiving event
		//notifications, or to start receiving them again.
		VerifyInterfaceOrMethod ( lpIOleControl->FreezeEvents ( FALSE ), 
							IDS_OLECONTROL_FE, FALSE );

		lpIOleControl->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIExternalConnection 
//PURPOSE:
//	Verifies the existence of the IExternalConnection interface by calling 
//	all of its member functions.  The IExternalConnection interface enables an
//	embedded object to keep track of external locks on it, thereby enabling 
//	the safe and orderly shutdown of the object following silent updates.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIExternalConnection ()
{
	ASSERT ( this != NULL );

	LPEXTERNALCONNECTION lpIExternalConnection = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IExternalConnection, 
										( void ** )  &lpIExternalConnection );
	VerifyInterfaceOrMethod ( hResult, IDS_EXTERNAL_CONNECTION_QI, m_bLinks );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIExternalConnection != NULL ) )
	{
		ASSERT_POINTER ( lpIExternalConnection, IExternalConnection );
	
		//AddConnection increments an object's count of its strong external
		//connections (links).
		VerifyInterfaceOrMethod ( lpIExternalConnection->AddConnection 
								( EXTCONN_STRONG, 0 ), 
								IDS_EXTERNAL_CONNECTION_AC, m_bLinks );

		//ReleaseConnection decrements an object's count of its strong 
		//external connections (links).
		VerifyInterfaceOrMethod ( lpIExternalConnection->ReleaseConnection 
								( EXTCONN_STRONG, 0, FALSE ), 
								IDS_EXTERNAL_CONNECTION_RC, m_bLinks );

		lpIExternalConnection->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyConnectionPointInterfaces
//PURPOSE:
//	Verifies the existence of the IConnectionPointContainer and 
//	IConnectionPoint interfaces by calling all of its member functions.  If 
//	IConnectionPointContainer does not exist,	then IConnectionPoint will not
//  as well.  IConnectionPointContainer provides access to the control's 
//	connection points. A control typically has two connection points: one for 
//	its events, and one for its property notifications.  There can be 
//	additional ones, but we will not consider them in our testing.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyConnectionPointInterfaces ()
{
	ASSERT ( this != NULL );

	LPCONNECTIONPOINT lpIConnectionPoint = NULL;
	LPCONNECTIONPOINTCONTAINER lpIConnectionPointContainer = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface 
								( IID_IConnectionPointContainer, 
								( void ** )  &lpIConnectionPointContainer );
	VerifyInterfaceOrMethod ( hResult, IDS_CONNECTIONPOINTCONTAINER_QI,
								m_bConnPoints );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIConnectionPointContainer != NULL ) )
	{
		ASSERT_POINTER ( lpIConnectionPointContainer, 
								IConnectionPointContainer );

		//First call all methods on IConnectionPointContainer, then on 
		//IConnectionPoint.
		LPENUMCONNECTIONPOINTS lpEnumConnPoints = NULL;
		
		//EnumConnectionPoints  enumerates all of the connection point
		//subobjects contained by the connectable object. Note that these are
		//true subobjects, with independent	ref-counts and parallel to the 
		//site objects maintained by an OLE container. 
		VerifyInterfaceOrMethod ( 
							lpIConnectionPointContainer->EnumConnectionPoints 
							( &lpEnumConnPoints ), 
							IDS_CONNECTIONPOINTCONTAINER_ECP, m_bConnPoints );
		if ( lpEnumConnPoints != NULL )
		{
			lpEnumConnPoints->Release ();
		}

		//Call methods on IConnectionPoint.
		if ( ( m_pControlSite->m_dwPropNotifySink != NULL ) && 
							( m_bConnPtNotify ) )
		{
			//The control says it supports IPropertyNotifySink and we have 
			//its IID.
			CallConnPtMethods ( lpIConnectionPointContainer, 
							IID_IPropertyNotifySink,  
							&( m_pControlSite->m_xPropertyNotifySink ) );
		}
		else if ( ( m_pControlSite->m_dwEventSink != NULL ) && 
							( m_bConnPtEvents ) )
		{
			//The control says it supports IDispatch for events and we have 
			//its IID.
			CallConnPtMethods ( lpIConnectionPointContainer, 
								m_pControlSite->m_iidEvents, 
								&( m_pControlSite->m_xEventSink ) );
		}
		else
		{
			//The control does not support event or property notifications
			//so we cannot test any of the IConnectionPoint interfaces.
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_CONNECTIONPOINT_A, m_bConnPoints, FALSE );
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_CONNECTIONPOINT_U, m_bConnPoints, FALSE );
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_CONNECTIONPOINT_EC, m_bConnPoints, FALSE );
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_CONNECTIONPOINT_GCI, m_bConnPoints, FALSE );
			NonStandardVerification ( NULL, NULL, V_NOT_APPLICABLE, 
								IDS_CONNECTIONPOINT_GCPC, m_bConnPoints, FALSE );
		}
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::CallConnPtMethods
//PURPOSE:
//	Calls all the IConnectionPoint methods using either the event sink or the
//  proprerty notify sink.
//INPUT PARAMETER(s):	
//	LPCONNECTIONPOINTCONTAINER lpIConnectionPointContainer - Ptr to 
//  IConnectionPointContainer
//	REFIID iidSink - The IID of the event sink or IPropertyNotifySink
//	LPUNKNOWN lpIUnkSink - Ptr to the IPropertyNotifySink or IDispatch events
//  interface.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::CallConnPtMethods ( 
					LPCONNECTIONPOINTCONTAINER lpIConnectionPointContainer,
					REFIID iidSink, LPUNKNOWN lpIUnkSink )
{
	ASSERT ( lpIUnkSink != NULL );
	ASSERT ( lpIConnectionPointContainer != NULL );
	ASSERT_POINTER ( lpIConnectionPointContainer, IConnectionPointContainer );

	HRESULT hResult;
	LPCONNECTIONPOINT lpIConnectionPoint = NULL;

	//The FindConnectionPoint method returns the connection point associated 
	//with a particular IID;
	VerifyInterfaceOrMethod ( hResult = lpIConnectionPointContainer->
							FindConnectionPoint	
							( iidSink, &lpIConnectionPoint ), 
							IDS_CONNECTIONPOINTCONTAINER_FCP, m_bConnPoints );

	if ( SUCCEEDED  ( hResult ) &&  ( lpIConnectionPoint != NULL ) )
	{
		ASSERT ( lpIConnectionPoint != NULL );
		ASSERT_POINTER ( lpIConnectionPoint, IConnectionPoint );
		
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, 
						hResult, V_NOT_QI_OBTAINED, IDS_CONNECTIONPOINT,
						m_bConnPoints, TRUE );

		//GetConnectionPointContainer allows code to navigate back to the
		//container object from the subobject.
		LPCONNECTIONPOINTCONTAINER lpCPC = NULL;

		VerifyInterfaceOrMethod ( lpIConnectionPoint->
							GetConnectionPointContainer ( &lpCPC ), 
							IDS_CONNECTIONPOINT_GCPC, m_bConnPoints );
		if ( lpCPC != NULL )
		{
			lpCPC->Release ();
		}

		//GetConnectionInterface names the interface for which this connection
		//point is able to call implementations. This interface ID (IID) also
		//effectively distinguishes this connection point from its siblings; 
		//it acts as the "name" of the connection point. With each 
		//IConnectionPoint, the caller can then use GetConnectionInterface
		//to learn the IID of that connection point.
		IID iidCP;
		VerifyInterfaceOrMethod ( lpIConnectionPoint->GetConnectionInterface 
							( &iidCP ), 
							IDS_CONNECTIONPOINT_GCI, m_bConnPoints );

		//Advise and Unadvise follow normal OLE conventions,that is, allow
		//connections to be established and broken
		DWORD dwConnID;
		VerifyInterfaceOrMethod ( hResult = lpIConnectionPoint->Advise 
							( lpIUnkSink, &dwConnID ), 
							IDS_CONNECTIONPOINT_A, m_bConnPoints );
			
		if ( SUCCEEDED  ( hResult ) )
		{
			VerifyInterfaceOrMethod ( lpIConnectionPoint->Unadvise 
							( dwConnID ), 
							IDS_CONNECTIONPOINT_U, m_bConnPoints );
		}
		else 
		{
			NonStandardVerification ( IDS_CONNECTIONPOINT_A, hResult, V_PREV_FAILURE, 
							IDS_CONNECTIONPOINT_U, m_bConnPoints, FALSE );
		}

		//EnumConnections is useful for "multicasting: scenarios, where a 
		//single connection point is capable of connectiong to multiple sinks. 
		//Whenever any function in one sink is called, the same function in 
		//every other sink is called as well. This enumerates the currently
		//connected sinks along with the connection IDs for them.
		LPENUMCONNECTIONS lpEnum = NULL;
		VerifyInterfaceOrMethod ( lpIConnectionPoint->EnumConnections 
							( &lpEnum ), 
							IDS_CONNECTIONPOINT_EC, FALSE );
		if ( lpEnum != NULL )
		{
			lpEnum->Release ();
		}

		lpIConnectionPoint->Release ();
	}
	else
	{
		//Cannot get a valid connection point and IConnectionPoint cannot 
		//be verified.
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, hResult,
					V_PREV_FAILURE, IDS_CONNECTIONPOINT_A, m_bConnPoints, FALSE );
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, hResult, 
					V_PREV_FAILURE, IDS_CONNECTIONPOINT_U, m_bConnPoints, FALSE );
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, hResult, 
					V_PREV_FAILURE, IDS_CONNECTIONPOINT_EC, m_bConnPoints, FALSE );
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, hResult, 
					V_PREV_FAILURE,	IDS_CONNECTIONPOINT_GCI, m_bConnPoints, FALSE );
		NonStandardVerification ( IDS_CONNECTIONPOINTCONTAINER_FCP, hResult, 
					V_PREV_FAILURE, IDS_CONNECTIONPOINT_GCPC, m_bConnPoints, FALSE );
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyISpecifyPropertyPages
//PURPOSE:
//	Verifies the existence of the ISpecifyPropertyPages by calling its one 
//	member function. An important issue is how a particular object specifies 
//	which set of pages should be used to browse the object’s properties. An
//	 object specifies pages by supporting the ISpecifyPropertyPages interface:
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyISpecifyPropertyPages ()
{
	ASSERT ( this != NULL );

	LPSPECIFYPROPERTYPAGES lpISpecifyPropertyPages = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface 
								( IID_ISpecifyPropertyPages, 
								( void ** )  &lpISpecifyPropertyPages );
	VerifyInterfaceOrMethod ( hResult, IDS_SPECIFYPROPERTYPAGES_QI, TRUE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpISpecifyPropertyPages != NULL ) )
	{
		ASSERT_POINTER ( lpISpecifyPropertyPages , ISpecifyPropertyPages );
	
		//GetPages asks an object what set of property pages should be used
		//to browse it.  This is equivalent to listing the CLSID’s for the 
		//object’s pages. GetPages which returns a counted array (as per 
		//OLE Automation) of the CLSID’s for the object's pages. To actually
		//create the pages, CoCreateInstance is called for each CLSID.
		CAUUID pages;
		VerifyInterfaceOrMethod ( lpISpecifyPropertyPages->GetPages ( &pages ), 
								IDS_SPECIFYPROPERTYPAGES_GP, TRUE );

		lpISpecifyPropertyPages->Release ();
	}
}

//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIPersistStream
//PURPOSE:
//	Verifies the existence of the IPersistStream by calling its member 
//	functions. The IPersistStream interface provides methods for saving and 
//	loading objects that use a simple serial stream for their storage needs. 
//	The primary purpose of this interface is to support OLE moniker 
//	implementations. Each of the OLE-provided moniker interfaces provide an 
//	IPersistStream implementation through which the moniker saves or loads 
//	itself.	An instance of the OLE generic composite moniker class calls the 
//	IPersistStream methods of its component monikers to load or save the 
//	components in the proper sequence in a single stream.
//INPUT PARAMETER(s):	
//	None.
//OUTPUT PARAMETER(s):
//	None.
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::VerifyIPersistStream ()
{
	ASSERT ( this != NULL );

	LPPERSISTSTREAM lpIPersistStream = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IPersistStream, 
											 ( void ** )  &lpIPersistStream );
	VerifyInterfaceOrMethod ( hResult, IDS_PERSISTSTREAM_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIPersistStream != NULL ) )
	{
		ASSERT_POINTER ( lpIPersistStream, IPersistStream );
	
		//IsDirty checks the object for changes since it was last saved.
		VerifyInterfaceOrMethod ( lpIPersistStream->IsDirty (), 
								IDS_PERSISTSTREAM_ID, FALSE );

		//GetSizeMax returns the size in bytes of the stream needed to save 
		//the object.
		ULARGE_INTEGER cbSize;
		VerifyInterfaceOrMethod ( lpIPersistStream->GetSizeMax ( &cbSize ), 
								IDS_PERSISTSTREAM_GSM, FALSE );

		//Save saves an object to the specified stream.
		if ( m_lpIStream != NULL ) 
		{
			VerifyInterfaceOrMethod ( lpIPersistStream->Save 
								( m_lpIStream, FALSE ), 
								IDS_PERSISTSTREAM_S, FALSE );
		
			//Load initializes an object from the stream where it was 
			//previously saved.
			VerifyInterfaceOrMethod ( lpIPersistStream->Load ( m_lpIStream ), 
								IDS_PERSISTSTREAM_L, FALSE );
		}
		else 
		{
			//m_lpIStream is NULL and does not point to a valid IStream object.  
			//These methods can thus not be tested.
			VerifyInterfaceOrMethod ( E_FAIL, IDS_PERSISTSTREAM_S, FALSE );
			VerifyInterfaceOrMethod ( E_FAIL, IDS_PERSISTSTREAM_L, FALSE );
		}

		lpIPersistStream->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIPersistStreamInit 
//PURPOSE:
//	Verifies the existence of the IPersistStreamInit interface by calling its
//	member functions. OLE 2 compound document objects use IPersistStorage for
//	persistence. This makes sense for the relatively heavyweight document 
//	editor applications OLE focuses on, but makes less sense for controls. 
//	Consequently, OLE Controls allow controls to support persistence to 
//	streams. New containers written for OLE controls can detect this support
//	and save embedded controls to streams rather than storages.  
//	Of course, existing compound document containers only support 
//	IPersistStorage. Controls will normally want to support being embedded in
//	compound document containers, and should therefore support 
//	IPersistStorage as well. Controls support persistence to streams through
//	the new interface IPersistStreamInit.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIPersistStreamInit ()
{
	#define MAX_ISTREAM_NAME_LEN	20

	ASSERT ( this != NULL );

	DWORD dwModeStream =	STGM_READWRITE |	//Allow read & write access
				STGM_SHARE_EXCLUSIVE | //Combo of STGM_SHARE_DENY_READ 
									   //and STGM_SHARE_DENY_WRITE.
				STGM_CREATE;

	//View class stream and storage members.
	LPSTREAM lpIStream = NULL;		

	if ( m_lpIStorage != NULL )
	{
		OLECHAR szoleName[MAX_ISTREAM_NAME_LEN];
		TCHAR   szName[MAX_ISTREAM_NAME_LEN] = TEXT ( "MYSTREAM" );

		
#ifndef UNICODE
		//Convert ANSI string to Unicode
		mbstowcs ( szoleName, szName, MAX_ISTREAM_NAME_LEN );
#else
		//Cannot use strcpy since C Runtime is not Unicode.
		lstrcpy ( szoleName, szName );
#endif			
		
		//Create a new stream object.
		HRESULT hResult = m_lpIStorage->CreateStream ( 
				szoleName,		//Name of the new stream object
				dwModeStream,	//Access modes
				0, 				//Reserved; must be zero
				0, 				//Reserved; must be zero
				&lpIStream );	//If successful, member pointer to new stream 
								//object
	
		ASSERT ( lpIStream != NULL );
		ASSERT_POINTER ( lpIStream, IStream );

		if ( FAILED ( hResult ) )
			{
			//Unable to create stream object.
			AfxMessageBox ( IDS_E_CANT_CREATE_ISTREAM );
			m_lpIStream = NULL;
			}
	}	

	LPPERSISTSTREAMINIT lpIPersistStreamInit = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IPersistStreamInit,
								 ( void ** ) &lpIPersistStreamInit );
	VerifyInterfaceOrMethod ( hResult, IDS_PERSISTSTREAMINIT_QI, FALSE );

	if ( SUCCEEDED  ( hResult ) && ( lpIPersistStreamInit != NULL ) )
	{
		ASSERT_POINTER ( lpIPersistStreamInit, IPersistStreamInit );

		//InitNew allows the container to tell the control to freshly 
		//initialize itself.
		VerifyInterfaceOrMethod  ( lpIPersistStreamInit->InitNew (), 
			IDS_PERSISTSTREAMINIT_IN, FALSE );
	
		//IsDirty checks the object for changes since it was last saved.
		VerifyInterfaceOrMethod ( lpIPersistStreamInit->IsDirty (),			
			IDS_PERSISTSTREAMINIT_ID, FALSE );

		//GetSizeMax returns the size in bytes of the stream needed to save 
		//the object. If the control supports IPersistStream and can return 
		//an accurate value,then it should do so
		ULARGE_INTEGER cbSize,mySeek;
		LARGE_INTEGER seekBegin;

		VerifyInterfaceOrMethod ( lpIPersistStreamInit->GetSizeMax 
								( &cbSize ),
								IDS_PERSISTSTREAMINIT_GSM, FALSE );
	
		if ( lpIStream != NULL )
		{
			//Save saves an object to the specified stream.
			VerifyInterfaceOrMethod ( lpIPersistStreamInit->Save 
									( lpIStream, TRUE ),
									IDS_PERSISTSTREAMINIT_S, FALSE );
		
			seekBegin.LowPart=0;
			seekBegin.HighPart=0;
			hResult=lpIStream->Seek ( seekBegin,STREAM_SEEK_SET,&mySeek );	
		
			//Load initializes an object from the stream where it was 
			//previously saved.
			VerifyInterfaceOrMethod ( lpIPersistStreamInit->Load 
									( lpIStream ),
									IDS_PERSISTSTREAMINIT_L, FALSE );

			lpIStream->Release ();
		}
		else
		{	
			//m_lpIStream is NULL and does not point to a valid IStream object.
			//These methods can thus not be tested.
			VerifyInterfaceOrMethod ( E_FAIL, IDS_PERSISTSTREAMINIT_S, FALSE );
			VerifyInterfaceOrMethod ( E_FAIL, IDS_PERSISTSTREAMINIT_L, FALSE );
		}

		lpIPersistStreamInit->Release ();	
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIPersistPropertyBag 
//PURPOSE:
//	Verifies the existence of the IPersistPropertyBag interface by calling 
//	its member functions.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIPersistPropertyBag ()
{
	ASSERT ( this != NULL );

	LPPERSISTPROPERTYBAG lpIPersistPropertyBag = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IPersistPropertyBag, 
										( void ** )  &lpIPersistPropertyBag );
	VerifyInterfaceOrMethod ( hResult, IDS_PERSISTPROPERTYBAG_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIPersistPropertyBag != NULL ) )
	{
		ASSERT_POINTER ( lpIPersistPropertyBag, IPersistPropertyBag );
	
		//InitNew
		VerifyInterfaceOrMethod ( lpIPersistPropertyBag->InitNew (), 
								IDS_PERSISTPROPERTYBAG_IN, FALSE );
		//GetClassID
		CLSID classID;
		VerifyInterfaceOrMethod ( lpIPersistPropertyBag->GetClassID 
								( &classID ), 
								IDS_PERSISTPROPERTYBAG_GCID, FALSE );

		//Create IErrorLog and IPropertyBag objects for Load and Save.
		LPPROPERTYBAG lpIPropertyBag = NULL;
		CPropertyBag * propBag = NULL;
		LPERRORLOG lpIErrorLog = NULL;
		CErrorLog * errorLog = NULL;

		try	
		{
			propBag = new CPropertyBag;
		}
		catch ( CMemoryException e )
		{
			e.Delete ();
			//By setting this to NULL, the proper messages will be displayed 
			//and processing will occur.
			propBag = NULL;
		}

		ASSERT ( propBag != NULL );

		if ( propBag != NULL )
		{
			lpIPropertyBag =  ( LPPROPERTYBAG ) propBag->GetInterface 
							  ( &IID_IPropertyBag );
			
			if ( lpIPropertyBag != NULL )
			{
				ASSERT_POINTER ( lpIPropertyBag, IPropertyBag );
	
				//Save
				VerifyInterfaceOrMethod ( lpIPersistPropertyBag->Save 
										( lpIPropertyBag, FALSE, FALSE ), 
										IDS_PERSISTPROPERTYBAG_S, FALSE );
				try
				{
					errorLog = new CErrorLog;
						
					if ( errorLog != NULL )
					{
						lpIErrorLog = ( LPERRORLOG ) errorLog->GetInterface 
									  ( &IID_IErrorLog );
					}

					if ( lpIErrorLog != NULL )
					{
						ASSERT_POINTER ( lpIErrorLog, IErrorLog );
	
						//Load
						VerifyInterfaceOrMethod ( lpIPersistPropertyBag->Load 
									( lpIPropertyBag, lpIErrorLog ), 
									IDS_PERSISTPROPERTYBAG_L, FALSE );
					
						lpIErrorLog->Release ();
					}
					else
					{
					//Unable to verify Load since cannot get a valid 
					//IErrorLog pointer.
					NonStandardVerification ( NULL, NULL, V_PREV_FAILURE, 
										IDS_PERSISTPROPERTYBAG_L, FALSE, FALSE );
					}
				}
				catch ( CMemoryException e )
				{
					e.Delete ();
					
					//Unable to verify Load since cannot get a valid 
					//IErrorLog pointer.
					NonStandardVerification ( NULL, NULL, V_PREV_FAILURE, 
										IDS_PERSISTPROPERTYBAG_L, FALSE, FALSE );
				}
			}
			
			delete propBag;
		}	
		else
		{
			//Unable to verify Load and Save.
			NonStandardVerification ( NULL, NULL, V_PREV_FAILURE, 
								IDS_PERSISTPROPERTYBAG_S, FALSE, FALSE );
			NonStandardVerification ( NULL, NULL, V_PREV_FAILURE, 
								IDS_PERSISTPROPERTYBAG_L, FALSE, FALSE );
		}

		lpIPersistPropertyBag->Release ();
	}	
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleCache 
//PURPOSE:
//	Verifies the existence of the IOleCache interface by calling its member 
//	functions.  The IOleCache interface provides control of the presentation 
//	data that gets cached inside of an object. Cached presentation data is 
//	available to the container of the object even when server application is
//	 not running or is unavailable. The IOleCache interface can be 
//	implemented by an object handler and an in-process server. However, you 
//	typically use or aggregate the OLE-provided implementation.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleCache ()
{
	ASSERT ( this != NULL );

	LPOLECACHE lpIOleCache = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleCache,  
												( void ** )  &lpIOleCache );
	VerifyInterfaceOrMethod ( hResult, IDS_OLECACHE_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleCache != NULL ) )
	{
		ASSERT_POINTER ( lpIOleCache, IOleCache );

		DWORD dwConnection;
		FORMATETC myFormatGet;
		STGMEDIUM stgMedium;
		LPDATAOBJECT lpIDataObject = NULL;		

		//Need an IDataObject pointer for some method calls to IOleCache.
		hResult = m_lpIUnknown->QueryInterface ( IID_IDataObject,  
												( void ** ) &lpIDataObject );
		if ( lpIDataObject != NULL )
		{
			ASSERT_POINTER ( lpIDataObject, IDataObject );
	
			LPENUMFORMATETC pEnumFormatEtcGet = NULL;
	
			lpIDataObject->EnumFormatEtc ( DATADIR_GET, &pEnumFormatEtcGet );
	
			if ( pEnumFormatEtcGet != NULL )
			{
				hResult = pEnumFormatEtcGet->Next ( 1, &myFormatGet, NULL );
				pEnumFormatEtcGet->Release ();
			}
			
			if ( SUCCEEDED  ( hResult) )
			{
				stgMedium.tymed = myFormatGet.tymed;
				//Specifies a handle, string, or interface pointer that the 
				//receiving process can use to access the data being transferred.
				stgMedium.pstm = NULL;
				//Points to an interface instance that allows the sending 
				//process to control the way the storage is released when the
				//receiving process calls the ReleaseStgMedium function. If 
				//pUnkForRelease is NULL, ReleaseStgMedium uses default 
				//procedures to release the storage;
				stgMedium.pUnkForRelease = NULL;
		
				//InitCache fills the cache as needed using the data provided
				//by the specified data object. 
				VerifyInterfaceOrMethod ( lpIOleCache->InitCache 
										( lpIDataObject ), 
										IDS_OLECACHE_IC, FALSE );
		
				//EnumCache returns an object that can be used to enumerate 
				//the current cache connections.
				IEnumSTATDATA * lpEnumSTATDATA=NULL;	
				VerifyInterfaceOrMethod ( lpIOleCache->EnumCache 
										( &lpEnumSTATDATA ), 
										IDS_OLECACHE_EC, FALSE );
		
				//Cache specifies the format and other data to be cached 
				//inside an embedded object.
				VerifyInterfaceOrMethod ( lpIOleCache->Cache 
										( &myFormatGet, ADVF_NODATA, 
										&dwConnection ), 
										IDS_OLECACHE_C, FALSE );
		
				//GetData retrieves data for a certain aspect of the object in
				//a certain clipboard format formatted for a certain target 
				//device conveyed on a certain storage medium.
				hResult = lpIDataObject->GetData ( &myFormatGet, &stgMedium );
		
				//SetData initializes the cache with data in a specified format 
				//on a specified medium. 
				VerifyInterfaceOrMethod ( lpIOleCache->SetData 
										( &myFormatGet, &stgMedium, FALSE ), 
										IDS_OLECACHE_SD, FALSE );
		
				//Uncache removes a cache connection created in a prior call 
				//to Cache.
				VerifyInterfaceOrMethod ( lpIOleCache->Uncache 
										( dwConnection ), 
										IDS_OLECACHE_U, FALSE );
					
				if ( lpEnumSTATDATA != NULL )
				{
					lpEnumSTATDATA->Release ();
				}
			}
			lpIDataObject->Release ();
		}
	lpIOleCache->Release ();
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleCache2 
//PURPOSE:
//	Verifies the existence of the IOleCache2 interface by calling its member 
//	functions. IOleCache2 allows object clients to selectively update each 
//	cache that was created with IOleCache::Cache.
//INPUT PARAMETER( s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleCache2 ()
{
	ASSERT ( this != NULL );

	LPOLECACHE2 lpIOleCache2 = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleCache2, 
											 ( void ** )  &lpIOleCache2 );
	VerifyInterfaceOrMethod ( hResult, IDS_OLECACHE2_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleCache2 != NULL ) )
	{
		ASSERT_POINTER ( lpIOleCache2, IOleCache2 );
	

		//Updates specified cache(s) when the application needs precise 
		//control over caching.
		VerifyInterfaceOrMethod ( lpIOleCache2->UpdateCache 
								( m_lpIDataObject, 
								UPDFCACHE_NODATACACHE, NULL ), 
								IDS_OLECACHE2_UC, FALSE );
		
		//DiscardCache discards the caches in memory.  Here, discard without
		//saving.
		VerifyInterfaceOrMethod ( lpIOleCache2->DiscardCache 
								( DISCARDCACHE_NOSAVE ), 
								IDS_OLECACHE2_DC, FALSE );

		lpIOleCache2->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIOleCacheControl 
//PURPOSE:
//	Verifies the existence of the IOleCacheControl interface by calling its 
//	member functions. IOleCacheControl provides proper maintenance of caches.
//	It maintains the caches by connecting the running object's IDataObject 
//	implementation to the cache allowing the cache to receive notifications 
//	from the running object.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIOleCacheControl ()
{
	ASSERT ( this != NULL );

	LPOLECACHECONTROL lpIOleCacheControl = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IOleCacheControl, 
											 ( void ** )  &lpIOleCacheControl );
	VerifyInterfaceOrMethod ( hResult, IDS_OLECACHECONTROL_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIOleCacheControl != NULL ) )
	{
		ASSERT_POINTER ( lpIOleCacheControl, IOleCacheControl );

		//OnRun notifies the cache that the data source object has entered 
		//its running state.
		VerifyInterfaceOrMethod ( lpIOleCacheControl->OnRun 
								( m_lpIDataObject ), 
								IDS_OLECACHECONTROL_OR, FALSE );

		//OnStop notifies the cache it should terminate any existing 
		//connection previously given to it by using OnRun. No indication is
		//given as to whether a connection existed or not.
		VerifyInterfaceOrMethod ( lpIOleCacheControl->OnStop (), 
								IDS_OLECACHECONTROL_OS, FALSE );

		lpIOleCacheControl->Release ();
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyIRunnableObject 
//PURPOSE:
//	Verifies the existence of the IRunnableObject interface by calling its 
//	member functions. IRunnableObject enables a container to control the 
//	running of its embedded objects. In the case of an object implemented with
//	a local server, calling Run launches the server's .EXE file. In the case
//	of an object implemented with an in-process server, calling the Run 
//	method causes the object .DLL file to transition into the running state.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyIRunnableObject ()
{
	ASSERT ( this != NULL );

	LPRUNNABLEOBJECT lpIRunnableObject = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface ( IID_IRunnableObject, 
											 ( void ** )  &lpIRunnableObject );
	VerifyInterfaceOrMethod ( hResult, IDS_RUNNABLEOBJECT_QI, FALSE );

	if ( SUCCEEDED  ( hResult )  &&  ( lpIRunnableObject != NULL ) )
	{
		ASSERT_POINTER ( lpIRunnableObject, IRunnableObject );
	
		//GetRunningClass Returns the CLSID of a running object.
		CLSID runClsid;
		VerifyInterfaceOrMethod ( lpIRunnableObject->GetRunningClass 
								( &runClsid ), 
								IDS_RUNNABLEOBJECT_GRC, FALSE );

		//IsRunning determines whether an object is currently in the running 
		//state.
		VerifyInterfaceOrMethod ( lpIRunnableObject->IsRunning (), 
								IDS_RUNNABLEOBJECT_IR, FALSE );

		//LockRunning locks an already-running object into its running state 
		//or unlocks it from its running state.
		VerifyInterfaceOrMethod ( lpIRunnableObject->LockRunning 
								( FALSE, FALSE ), 
								IDS_RUNNABLEOBJECT_LR, FALSE );

		//Run forces an object to enter the running state.
		VerifyInterfaceOrMethod ( lpIRunnableObject->Run ( NULL ), 
								IDS_RUNNABLEOBJECT_R, FALSE );

		//SetContainedObject notifies an object that it is embedded in an 
		//OLE container, which ensures that reference counting is done 
		//correctly for containers that support links to embedded objects.
		VerifyInterfaceOrMethod ( lpIRunnableObject->SetContainedObject 
								( TRUE ),
								IDS_RUNNABLEOBJECT_SCO, FALSE );
			
		lpIRunnableObject->Release ();
	}
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::NonStandardVerification
//PURPOSE:
//	Called when a method was not verified.
//INPUT PARAMETER(s):	
//	const int iPrevDependentMethod - ID of string resource for name of previous 
//	method that failed and was responsible for this dependent method not being
//	processed normally.  NULL means there was not a previous method, or the method was
//	one internal to this program (suce as IErrorLog) that is not known to the
//	user.
//	const HRESULT hResultPrev - hResult of previous failed dependent method.
//	long lReason - Reason code why the method non-standard in processing. 
//  const int iNonStandardMethod - Resource id for the method name
//	bMandatory - FALSE if method was optional; TRUE if mandatory.
//	bVerified - FALSE if method not verified; TRUE if it was.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::NonStandardVerification ( const int iPrevDependentMethod, 
	const HRESULT hResultPrev, const long lReason, const int iNonStandardMethod,
	const BOOL bMandatory, const BOOL bVerified )
{
	CString sNonStandardText;  //Holds explanation of non-standard behavior.
	CString sMandatory;		   //Holds "MANDATORY" or "OPTIONAL" string.
	CString sFormatString;	   //Holds formatted
	CString sPrevDependentMethod;
	CString sNonStandardMethod;

	sFormatString.GetBuffer ( 100 );

	sNonStandardMethod.LoadString ( iNonStandardMethod ); 
		
	switch ( lReason )
	{
		//Display the name of the previous method as well to assist the user
		//in determining why the method was not verified.  We have to check
		//for NULL here since the previous method may have been an interal
		//interface or method that we do not want to display on the screen
		//since it may confuse the user.
		case V_PREV_FAILURE:
			if ( iPrevDependentMethod != NULL )
			{
				//Load the name of the previous method.
				sPrevDependentMethod.LoadString ( iPrevDependentMethod ); 
		
				if ( hResultPrev == E_NOTIMPL )
				{
					//Not verified due to previous verified method not 
					//being implemented..
					sNonStandardText.LoadString ( IDS_NV_PREV_NOT_IMPL );
				}
				else
				{
					//Not verified due previous verified method failure, 
					//or an internal method failure..
					sNonStandardText.LoadString ( IDS_NV_PREV_FAILURE );
				}
			}
			else
			{
				//It was an internal method or interface that failed.
				sNonStandardText.LoadString ( IDS_NV_PREV_FAILURE );
			}

		break;

		//Custom error code for method not called due to optional but not
		//called in this situation since it does not make sense to do so.
		case V_NOT_APPLICABLE:
			sNonStandardText.LoadString ( IDS_NV_NOT_APPLICABLE );
			break;

		//Custom error code for automation exception.
		case V_AUTO_EXCEPTION:
			sNonStandardText.LoadString ( IDS_NV_AUTO_EXCEPTION );
			break;

		//Interface pointer not obtained through QI.
		case V_NOT_QI_OBTAINED:
			sNonStandardText.LoadString ( IDS_NOT_QI_OBTAINED );
			break;

		default:
			sNonStandardText.LoadString ( IDS_NV_UNKNOWN_REASON );
	}

	if ( ! bVerified )
	{		
		//Increment counter of not verified methods for results dialog.
		if ( ! bMandatory ) 
		{
			m_CResultsDlg.m_uOptNotVerified ++;
		}
		else 
		{
			m_CResultsDlg.m_uManNotVerified ++;
		}
	}
	else
	{
		//This block will only be called if an interface was obtained by
		//some other means than QI successfully (and thus is verified).
		//Increment counter of mandatory/optional successes.
		if ( bMandatory ) 
		{
			m_CResultsDlg.m_uManSuccesses ++;
		}
		else 
		{
			m_CResultsDlg.m_uOptSuccesses ++;
		}
	}

	//Create result object and format result string in form of:
	//"Int::MethodName [MANDATORY/OPTIONAL]: Not Verified (Comment)
	CResultsObj * pResObj = CreateResultObject ();
	
	if ( pResObj != NULL )
	{
		//Load the "OPTIONAL" or "MANDATORY" string.
		CString sManOrOptText;
		sManOrOptText.LoadString ( GetManOrOptStringID ( bMandatory) );

		if ( iPrevDependentMethod == NULL )
		{
			//No previous dependent method.
			pResObj->sResultString.Format ( _T ( "\t%s [%s]: %s" ),
										sNonStandardMethod, sManOrOptText,
										sNonStandardText );
		}
		else
		{
			//There was a previous dependent method.
			if ( ! bVerified )
			{
			sFormatString.Format ( IDS_NOT_VERIFIED, sNonStandardText, 
										sPrevDependentMethod );
			pResObj->sResultString.Format ( _T ( "\t%s [%s]: Not verified - %s" ),
										sNonStandardMethod, sManOrOptText,
										sFormatString );
			}
			else 
			{
			//Interface ptr not obtained through QI.
			//Load the name of the previous method.
			sPrevDependentMethod.LoadString ( iPrevDependentMethod ); 
			pResObj->sResultString.Format ( _T ( "%s [%s]: %s %s" ),
										sNonStandardMethod, sManOrOptText, 
										sNonStandardText, sPrevDependentMethod );
			}
		}

		//If Interface::Method was mandatory or optional
		pResObj->bMandatory = bMandatory;

		//dummy value since never used for not verified methods
		pResObj->hResult = hResultPrev;	
	
		//Was Interface::Method verified?  Set flag used for totals in results dlg..
		pResObj->bVerified = bVerified;

		//Meaningless initialization value at this point since this is 
		//determined later.
		pResObj->bSave = FALSE;			

		m_CResultsDlg.m_ResultList.AddTail ( pResObj );
	}

	sFormatString.ReleaseBuffer ();
}




//***************************************************************************
//METHOD NAME:			
//	CVContainView::VerifyInterfaceOrMethod
//PURPOSE:
//	Tests the HRESULT return value and logs result for the method's 
//	implementation status.
//INPUT PARAMETER(s):	
//	HRESULT hResult - Result of the invocation of this method.
//	const int iStringID - Resource id of string resource for name of the 
//	method being verified in format "Interface::Method"
//	bMandatory - TRUE if mandatory; FALSE if optional.
//	bInterface - TRUE if call was to get an interface pointer 
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::VerifyInterfaceOrMethod ( HRESULT hResult,
		const int iStringID, const BOOL bMandatory )
{
	ASSERT ( this != NULL );
		
	CString sHResultText;
	CString sIntOrMethodName;
	CString sMandatory;
	//iPassFail holds string id of IDS_PASSED/IDS_FAILED for result string.
	int iPassFail;

	//Increment totals for results dialog. 
	if ( bMandatory )
	{
		if ( ( hResult == E_NOTIMPL ) || ( hResult == E_NOINTERFACE ) )
		{
			//A mandatory interface returning E_NOINTERFACE or a mandatory 
			//method returning E_NOINTERFACE is a failure.
			m_CResultsDlg.m_uManFailures ++;
			iPassFail = IDS_FAILED;
		}
		else
		{
			//A mandatory interface returning anything but E_NOINTERFACE or
			//a mandatory method returning anything but E_NOINTERFACE is a 
			//success. Remember, we are not testing functionality.
			m_CResultsDlg.m_uManSuccesses ++;
			iPassFail = IDS_PASSED;
		}
	}
	else
	{
		//Handle optional calls.  There is no such thing as an optional 
		//failure so as long as it was verified (this function would not
		//have been called unless it was), it is a success.
		m_CResultsDlg.m_uOptSuccesses ++;
		iPassFail = IDS_PASSED;
	}

	
	//Create result object and format result string in form of:
	//"Int::MethodName [MANDATORY/OPTIONAL]:0xHRESULT=HRESULTTEXT.
	CResultsObj * pResObj = CreateResultObject ();

	if ( pResObj != NULL )
	{
		CString sManOrOptText;
		CString sResultString;

		//Load the "Interface::MethodName" text.
		sIntOrMethodName.LoadString ( iStringID ); 
	
		//Load the hResult text.
		sHResultText.LoadString ( GetHResultStringID ( hResult ) );

		//Load the "OPTIONAL" or "MANDATORY" string.
		sManOrOptText.LoadString ( GetManOrOptStringID( bMandatory) );
		
		//Format the string to appear in the results dialog or the file.
		sResultString.GetBuffer ( MAX_RESULT_STRING );
		pResObj->sResultString.Format ( _T ( "%s [%s]: 0x%08x=%s" ),
							sIntOrMethodName, sManOrOptText,
							hResult, sHResultText);

		//Indent all calls in results dialog except QI.
		int i = sIntOrMethodName.Find ( _T ( "QueryInterface" ) );
		if ( i == -1 )
		{
			CString s;
			s.GetBuffer ( MAX_RESULT_STRING );
			s.Format ( _T ( "\t%s" ), pResObj->sResultString );
			pResObj->sResultString = s;
			s.ReleaseBuffer ();
		}

		pResObj->bMandatory = bMandatory;
		pResObj->hResult = hResult;
		pResObj->bVerified = TRUE;
		//Meaningless initialization value at this point; determined later.
		pResObj->bSave = FALSE;		

		m_CResultsDlg.m_ResultList.AddTail ( pResObj );	
		
		sResultString.ReleaseBuffer ();
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::GetManOrOptStringID
//PURPOSE:
//	Returns the resource string id of the optional or mandatory keyword text.
//INPUT PARAMETER(s):	
//	bMandatory - FALSE or TRUE 
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	int - String resource id 
//***************************************************************************
int CVContainView::GetManOrOptStringID ( const BOOL bMandatory )
{
	if ( bMandatory )
	{
		return IDS_MANDATORY;
	}
	else
	{
		return IDS_OPTIONAL;
	}
}




//***************************************************************************
//METHOD NAME:			
//	CVContainView::CreateResultObject 
//PURPOSE:
//	Creates a result object for the result array.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	A pointer to the newly created result object.
//***************************************************************************
CResultsObj * CVContainView::CreateResultObject ()
{
	CResultsObj * pResObj = NULL;
	try
	{
		pResObj = new CResultsObj;
	}
	catch ( CMemoryException e )
	{
		e.Delete ();
		return NULL;
	}

	ASSERT ( pResObj != NULL );
	ASSERT_POINTER ( pResObj, CResultsObj );

	return pResObj;
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::GetHResultStringID
//PURPOSE:
//	Returns the resource string id of the hResult text.
//INPUT PARAMETER(s):	
//	HRESULT hResult - hResult of method or interface call to obtain string 
//	id for.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	int - String resource id 
//***************************************************************************
int CVContainView::GetHResultStringID ( HRESULT hResult )
{
	switch ( hResult )
	{
		case E_UNEXPECTED:
			return IDS_E_UNEXPECTED;
			break;
		
		case E_OUTOFMEMORY:
			return IDS_E_OUTOFMEMORY;
			break;
		
		case E_INVALIDARG:
			return IDS_E_INVALIDARG;
			break;
		
		case E_NOINTERFACE:
			return IDS_E_NOINTERFACE;
			break;
		
		case E_POINTER:
			return IDS_E_POINTER;
			break;

		case E_HANDLE:
			return IDS_E_HANDLE;
			break;

		case E_ABORT:
			return IDS_E_ABORT;
			break;

		case E_ACCESSDENIED:
			return IDS_E_ACCESSDENIED;
			break;
		
		case E_NOTIMPL:
			return IDS_E_NOTIMPL;
			break;
		
		case E_FAIL:
			return IDS_E_FAIL_UNSPECIFIED;
			break;

		case S_OK:
			return IDS_S_OK;
			break;

		case S_FALSE:
			return IDS_S_FALSE;
			break;

		//IDataObject possible hResult return values.
		case DV_E_FORMATETC:
			return IDS_DV_E_FORMATETC;
			break;

		case DV_E_DVTARGETDEVICE:
			return IDS_DV_E_DVTARGETDEVICE;
			break;

		case DV_E_STGMEDIUM:
			return IDS_DV_E_STGMEDIUM;
			break;

		case DV_E_STATDATA:
			return IDS_DV_E_STATDATA;
			break;

		case DV_E_LINDEX:
			return IDS_DV_E_LINDEX;
			break;

		case DV_E_TYMED:
			return IDS_DV_E_TYMED;
			break;

		case DV_E_CLIPFORMAT:
			return IDS_DV_E_CLIPFORMAT;
			break;

		case DV_E_DVASPECT:
			return IDS_DV_E_DVASPECT;
			break;

		case DATA_S_SAMEFORMATETC:
			return IDS_DATA_S_SAMEFORMATEC;
			break;

		//IDispatch possible hResult return values.
		case DISP_E_UNKNOWNINTERFACE:
			return IDS_DISP_E_UNKNOWNINTERFACE;
			break;

		case DISP_E_MEMBERNOTFOUND:
			return IDS_DISP_E_MEMBERNOTFOUND;
			break;

		case DISP_E_PARAMNOTFOUND:
			return IDS_DISP_E_PARAMNOTFOUND;
			break;

		case DISP_E_TYPEMISMATCH:
			return IDS_DISP_E_TYPEMISMATCH;
			break;

		case DISP_E_UNKNOWNNAME:
			return IDS_DISP_E_UNKNOWNNAME;
			break;

		case DISP_E_NONAMEDARGS:
			return IDS_DISP_E_NONAMEDARGS;
			break;

		case DISP_E_BADVARTYPE:
			return IDS_DISP_E_BADVARTYPE;
			break;

		case DISP_E_EXCEPTION:
			return IDS_DISP_E_EXCEPTION;
			break;

		case DISP_E_OVERFLOW          :
			return IDS_DISP_E_OVERFLOW;
			break;

		case DISP_E_BADINDEX:
			return IDS_DISP_E_BADINDEX;
			break;

		case DISP_E_UNKNOWNLCID:
			return IDS_DISP_E_UNKNOWNLCID;
			break;

		case DISP_E_ARRAYISLOCKED:
			return IDS_DISP_E_ARRAYISLOCKED;
			break;

		case DISP_E_BADPARAMCOUNT:
			return IDS_DISP_E_BADPARAMCOUNT;
			break;

		case DISP_E_PARAMNOTOPTIONAL:
			return IDS_DISP_E_PARAMNOTOPTIONAL;
			break;

		case DISP_E_BADCALLEE:
			return IDS_DISP_E_BADCALLEE;
			break;

		case DISP_E_NOTACOLLECTION:
			return IDS_DISP_E_NOTACOLLECTION;
			break;

		default:
			return IDS_UNSPECIFIED;
			break;
	}
	
}	
	

//***************************************************************************
//METHOD NAME:			
//	CVContainView::CreateStorageObjects
//PURPOSE:
//	Creates an IStorage object, then an accompanying IStream object to be 
//	used in the various interface method calls as input parameters.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None, but sets the m_lpIStream and m_lpIStorage member variables.
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::CreateStorageObjects ()
{
	//Max size of buffer to hold IStream name.
	#define MAX_ISTREAM_NAME_LEN	20

	ASSERT ( this != NULL );

	OLECHAR pwcsFile[MAX_PATH];
	TCHAR szFile[20] = VCONTAIN_FILE_NAME;
	DWORD dwModeStorage = STGM_DIRECT |		//Changes happen immediately
					STGM_READWRITE |		//Allow read & write access
					STGM_SHARE_EXCLUSIVE|	//Combo of STGM_SHARE_DENY_READ
											//and STGM_SHARE_DENY_WRITE. 
					STGM_CREATE; 			//Creates new file, overwriting 
											//existing one if there.
	DWORD dwModeStream = STGM_READWRITE |	//Allow read & write access
					STGM_SHARE_EXCLUSIVE|	//Combo of STGM_SHARE_DENY_READ 
											//and STGM_SHARE_DENY_WRITE. 
					STGM_CREATE;

	//View class stream and storage members.
	m_lpIStream = NULL;		
	m_lpIStorage = NULL;

	#ifndef UNICODE
		//Convert ANSI string to Unicode
		mbstowcs ( pwcsFile, szFile, MAX_PATH );
	#else
		//Cannot use strcpy since CRT is not Unicode.
		lstrcpy ( pwcsFile, szFile);
	#endif

	//Create a new root docfile. 
	HRESULT hResult = StgCreateDocfile ( 
			pwcsFile,			//Name of the new storage object
			dwModeStorage,		//Access modes
			0,					//Reserved; must be zero
			&m_lpIStorage );	//If successful, member pointer to opened 
								//storage object
	
	ASSERT ( m_lpIStorage != NULL );
	ASSERT_POINTER ( m_lpIStorage, IStorage );

	if ( SUCCEEDED  ( hResult ) && ( m_lpIStorage != NULL ) )
	{
		OLECHAR szoleName[MAX_ISTREAM_NAME_LEN];
		TCHAR   szName[MAX_ISTREAM_NAME_LEN] = VCONTAIN_ISTREAM_NAME;

		#ifndef UNICODE
			mbstowcs ( szoleName, szName, MAX_ISTREAM_NAME_LEN );
		#else
			//Cannot use strcpy since CRT is not Unicode.
			lstrcpy ( szoleName, szName );
		#endif

		//Create a new stream object.
		hResult = m_lpIStorage->CreateStream ( 
				szoleName,			//Name of the new stream object
				dwModeStream,		//Access modes
				0, 					//Reserved; must be zero
				0, 					//Reserved; must be zero
				&m_lpIStream );		//If successful, member pointer to new
									//stream object
	
		ASSERT ( m_lpIStream != NULL );
		ASSERT_POINTER ( m_lpIStream, IStream );

		if ( FAILED ( hResult ) )
		{
			//Unable to create stream object.
			AfxMessageBox ( IDS_E_CANT_CREATE_ISTREAM );
			m_lpIStream = NULL;
		}
		
	}
	else
	{
		//Unable to create storage object.
		AfxMessageBox ( IDS_E_CANT_CREATE_ISTORAGE );
		m_lpIStorage = NULL;
	}
		
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::InitResultObjects
//PURPOSE:
//	Initialize counters for results.  If a result array exists, initialize it.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::InitResultObjects ()
{
	ASSERT ( this != NULL );

	//Delete any objects that exist from previous verification during this session.
	DeleteAllResultObjects ();

	//Reinitialize result counters.
	m_CResultsDlg.m_uManSuccesses = 0;
	m_CResultsDlg.m_uManNotVerified = 0;
	m_CResultsDlg.m_uManFailures = 0;
	m_CResultsDlg.m_uOptSuccesses = 0; 
	m_CResultsDlg.m_uOptNotVerified = 0;
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::DeleteAllResultObjects
//PURPOSE:
//	If a result array exists, initialize it by deleting all members.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::DeleteAllResultObjects ()
{
	ASSERT ( this != NULL );

	if ( m_CResultsDlg.m_ResultList.GetCount () > 0 )
	{
		//Elements exist so delete them.
		POSITION pos = m_CResultsDlg.m_ResultList.GetHeadPosition ();

		while ( pos != NULL )
		{
			delete m_CResultsDlg.m_ResultList.GetNext ( pos );
		}
	
		m_CResultsDlg.m_ResultList.RemoveAll ();
	}
 }



//***************************************************************************
//METHOD NAME:			
//	CVContainView::OnViewResults
//PURPOSE:
//	Invokes the results dialog box to show results of verification process.
//INPUT PARAMETER(s):	
//	None	
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::OnViewResults () 
{
	ASSERT ( this != NULL );

	//Use itoa instead of CString::GetBuffer and ::ReleaseBuffer for speed.
	char buffer[4];

	//Convert result counters to characters.
	m_CResultsDlg.m_ManFailures = itoa ( m_CResultsDlg.m_uManFailures, 
										buffer, 10 );
	m_CResultsDlg.m_ManSuccesses = itoa ( m_CResultsDlg.m_uManSuccesses, 
										buffer, 10 );
	m_CResultsDlg.m_ManNotVerified = itoa ( m_CResultsDlg.m_uManNotVerified, 
										buffer, 10 );
	m_CResultsDlg.m_OptSuccesses = itoa ( m_CResultsDlg.m_uOptSuccesses, 
										buffer, 10 );
	m_CResultsDlg.m_OptNotVerified = itoa ( m_CResultsDlg.m_uOptNotVerified, 
										buffer, 10 );

	m_CResultsDlg.DoModal ();

	//Set flag for menu item to "View Results"
	m_bVerified = TRUE;
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::GetPreVerifyInfo
//PURPOSE:
//	Displays the pre-verify dialog to obtain information on the control that
//	 will be used to determine if certain interfaces and methods are 
//	mandatory or optional.  Other information can be obtained through reading
//	 the type library or reading certain registry keys.  We are trying to 
//	determine, without actually calling the interfaces,	if a control indeed
//	 implements what it says it supports in its TLB or the registry.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	TRUE - Pre-verify info obtained and user wants to continue with 
//	verification
//	FALSE - Pre-verify info NOT obtained or user does not want to continue 
//	with verification
//***************************************************************************
BOOL CVContainView::GetPreVerifyInfo ()
{
	ASSERT ( this != NULL );

	CPreVerifyDlg dlg;

	//Init all question variables to TRUE so that by default pre-verification 
	//questions will be asked if we cannot read the type lib or the registry 
	//correctly.
	InitQuestionMembers ( &dlg );

	//Set to FALSE since the dialog is being displayed to obtain pre-verify 
	//information as opposed to displaying it in the results dialog.
	dlg.m_bResultsOfPreverify = FALSE;

	//Read type lib to verify licensing, exposed props/methods and events and
	//prop notifications.  Based upon what can be determined, certain 
	//questions will not need to be asked in the pre-verify dialog box.
	PreVerifyUsingTypeLib ( &dlg );
				
	//Check for the existence of property pages to see if IOleObject::DoVerb
	//using OLEIVERB_PRIMARY and OLEIVERB_PROPERTIES are mandatory.  This is
	//done by querying for ISpecifyPropertyPages.
	PreVerifyPropertyPages ( &dlg );

	//Read certain misc status bits from the registry to determine if some
	//interfaces and methods are mandatory.
	CheckMiscStatusBits ( &dlg );

	//Display dialog to obtain information unable to obtain from type lib.  
	//This at a minimum will be property sets and use of ambients or 
	//mnemonics.
	if ( dlg.DoModal () == IDOK )
	{
		ReadVerifyDlg ( &dlg );
		m_bPreVerifyInfoObtained = TRUE;
		return TRUE;
	}
	else
	{
		//Do not continue with verification.
		m_bPreVerifyInfoObtained = FALSE;
		return FALSE;
	}
	
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::PreVerifyPropertyPages
//PURPOSE:
//	Checks for existence of ISpecifyPropertyPages interface to see if the 
//	control supports property pages.
//INPUT PARAMETER(s):	
//	CPreVerifyDlg * dlg - Ptr to pre-verify dialog object.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::PreVerifyPropertyPages ( CPreVerifyDlg * dlg )
{
	ASSERT ( this != NULL );

	LPSPECIFYPROPERTYPAGES lpISpecifyPropertyPages = NULL;
	HRESULT hResult = m_lpIUnknown->QueryInterface 
									( IID_ISpecifyPropertyPages, 
									( void ** )  &lpISpecifyPropertyPages );

	if ( SUCCEEDED ( hResult ) && ( lpISpecifyPropertyPages != NULL ) )
	{
		//The control supports this interface and thus prop pages.
		m_bPropPages = TRUE;
		dlg->m_bEnablePropPagesQuestion = FALSE;
	}
	else if ( hResult == E_NOTIMPL )
	{	
		//The control does not implement this interface
		m_bPropPages = FALSE;
		dlg->m_bEnablePropPagesQuestion = FALSE;
	}
	else
	{
		//Unable to determine if prop pages are supported or not for sure
		//so we need to ask the question to the user.
		m_bPropPages = FALSE;
		dlg->m_bEnablePropPagesQuestion = TRUE;
	}

	if ( lpISpecifyPropertyPages != NULL )
		lpISpecifyPropertyPages->Release ();
}

	
//***************************************************************************
//METHOD NAME:			
//	CVContainView::PreVerifyUsingTypeLib
//PURPOSE:
//	Reads type library to see if control exposes props or methods, events or
//  property notifications (connection points), licensing, and visible UI.
//INPUT PARAMETER(s):	
//	CPreVerifyDlg * dlg - Ptr to pre-verify dialog object.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::PreVerifyUsingTypeLib ( CPreVerifyDlg * dlg )
{
	ASSERT ( this != NULL );
	ASSERT ( dlg != NULL );
	ASSERT_POINTER ( &dlg, CPreVerifyDlg );
	
	HRESULT hResult;
	LPTYPEINFO lpPropMethodTypeInfo = NULL;
	LPTYPELIB  lpPropMethodTypeLib = NULL;

	//If we can obtain DispInterface TypeInfo we can check the methods and 
	//properties.  This is the typeinfo returned by IDispatch::GetTypeInfo. 
	//If the control does not have any properties or methods, IDispatch is 
	//optional and may not exist.  We want to verify that if the type library
	//exposes props and methods that IDispatch exists.  Therefore, we cannot
	//use IDipatch to get the typeinfo here, but must do it manually through
	//the call to GetControlTypeInfo.
	if ( LoadTypeLibFromCLSID ( &lpPropMethodTypeLib ) && 
							  ( lpPropMethodTypeLib != NULL ) )
	{
		ASSERT_POINTER ( lpPropMethodTypeLib, ITypeLib );

		//Get type info from the typelib.  Using 0 for the index parameter
		//retrieves type info for the IDispatch implementation, which is what
		//we need to find out about props and methods.
		if ( SUCCEEDED  ( lpPropMethodTypeLib->GetTypeInfo 
							( 0, &lpPropMethodTypeInfo ) )  
						&& ( lpPropMethodTypeInfo != NULL) )
		{	
			ASSERT_POINTER ( lpPropMethodTypeInfo, ITypeInfo );

			//Check for props and methods existence for IDispatch, as well as
			//the  bindable attribute for any of the properties or methods.
			LPTYPEATTR pta = NULL;

			if ( SUCCEEDED  ( lpPropMethodTypeInfo->GetTypeAttr ( &pta ) ) )
			{
				ASSERT_POINTER ( pta, TYPEATTR );

				if ( ( pta->cVars > 0 ) || ( pta->cFuncs > 0 ) )
				{
					//There is at least one property or method so IDispatch 
					//is mandatory.
					m_bPropsMethods = TRUE;

					//Check for the 'bindable' property attribute.  If it 
					//exists on at least one property, or one bound property
					//that is implemented through get/set methods, the control
					//supports IPropertyNotifySink.
					m_bConnPtNotify = CheckBindableAttribute 
											( lpPropMethodTypeInfo, pta );
				}
				else 
				{
					//IDispatch is optional since no props or methods.
					m_bPropsMethods = FALSE;
				}
				
				//No need to ask question for props and methods 
				dlg->m_bEnablePropMethodQuestion = FALSE; 
			}
			
			if ( ( lpPropMethodTypeInfo != NULL ) && ( pta != NULL ) )
			{
				lpPropMethodTypeInfo->ReleaseTypeAttr ( pta );
				lpPropMethodTypeInfo->Release ();
			}

		lpPropMethodTypeLib->Release ();
		}
	}

	//Check for events or property notifications (connection points).  By 
	//calling the GetClassInfo method of IProvideClassInfo you get a CoClass
	//TypeInfo object that describes the connectable object in the object’s
	//type information. You can look at all its interfaces, both incoming
	//and outgoing, and check for connection points for events or property
	//notifications.
	LPPROVIDECLASSINFO lpIProvideClassInfo = NULL;
	hResult = m_lpIUnknown->QueryInterface ( IID_IProvideClassInfo, 
										( void ** )  &lpIProvideClassInfo );
	
	if ( SUCCEEDED  ( hResult )  && ( lpIProvideClassInfo != NULL ) )
	{
		ASSERT_POINTER ( lpIProvideClassInfo, IProvideClassInfo );

		LPTYPEINFO lpCoClassTypeInfo = NULL;

		if ( SUCCEEDED  ( lpIProvideClassInfo->GetClassInfo 
						( &lpCoClassTypeInfo ) ) 
						&& lpCoClassTypeInfo != NULL )
		{	
			//The ITypeInfo interface returned from GetClassInfo is the 
			//interface on the object's entire type library. With this pointer
			//you can call ITypeInfo::GetTypeAttr to look for an interface 
			//with the Source attributes and call GetRefTypeOfImplType and 
			//GetRefTypeInfo to retrieve the ITypeInfo interface for that 
			//particular interface. Outgoing interfaces can be standard COM
			//type interfaces or dispinterfaces. Only one, however, can be 
			//marked with the Default attribute that makes it the primary
			//IMPLTYPEFLAG_FDEFAULT	- interface represents default for the 
			//source or sink.
			//IMPLTYPEFLAG_FSOURCE	- member of a coclass is called rather 
			//than implemented.
			//IMPLTYPEFLAG_FRESTRICTED - member should not be displayed or 
			//programmable by users. 
			#define IMPLTYPE_MASK \
				 ( IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE | IMPLTYPEFLAG_FRESTRICTED ) 

			#define IMPLTYPE_DEFAULTSOURCE \
				 ( IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE ) 

			//Regardless of if IClassFactory2 is implemented, IClassFactory
			//is mandatory and the control would not have created if it did 
			//not exist.
			VerifyInterfaceOrMethod ( S_OK, IDS_CLASSFACTORY, TRUE );
				
			LPTYPEATTR pta = NULL;
			if ( SUCCEEDED  ( lpCoClassTypeInfo->GetTypeAttr ( &pta ) ) )
			{
				ASSERT_POINTER ( pta, TYPEATTR );

				if( ( pta != NULL ) && ( pta->typekind == TKIND_COCLASS ) )
				{
					ASSERT ( pta->typekind == TKIND_COCLASS );

					//Check for the events interface.
					m_bConnPtEvents = CheckCoClassInfo ( lpCoClassTypeInfo, 
								IMPLTYPE_DEFAULTSOURCE, pta, 
								&dlg->m_bEnableConnPtQuestion );
				
					//Combines flags into one for simplicity to show if the
					//control supports connection points.  
					m_bConnPoints = m_bConnPtNotify || m_bConnPtEvents;


					//Prior to control creation, we checked to see if ICF2 
					//was implemented. The flag m_bLicensed was set to TRUE if
					//it was implemented.  Now, read the type library to see if
					//the 'licensed' keyword is present. Specically, look or
					//the TYPEFLAG_FLICENSED in the TYPEFLAGS structure. If yes,
					//then ICF2 is mandatory.
					if ( pta->wTypeFlags & TYPEFLAG_FLICENSED )
					{
						if ( m_bLicensed )
						{
							//IClassFactory2 is mandatory.
							VerifyInterfaceOrMethod 
									( S_OK, IDS_CLASSFACTORY2, TRUE );
						}
						else
						{
							VerifyInterfaceOrMethod 
									( E_NOTIMPL, IDS_CLASSFACTORY2, TRUE );
						}
					}
					else
					{
						if ( m_bLicensed )
						{
							//IClassFactory2 is optional
							VerifyInterfaceOrMethod 
										( S_OK, IDS_CLASSFACTORY2, FALSE );
						}
						else
						{
							VerifyInterfaceOrMethod 
									( E_NOTIMPL, IDS_CLASSFACTORY2, FALSE );
						}
					}
						
					//No need to ask question about licensing.
					dlg->m_bEnableLicensedQuestion = FALSE;

					if ( ( lpCoClassTypeInfo != NULL ) && ( pta != NULL ) )
					{
						lpCoClassTypeInfo->ReleaseTypeAttr ( pta );
						lpCoClassTypeInfo->Release ();
					}

				}	
			}  

			lpIProvideClassInfo->Release ();
		}

	}	
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::CheckBindableAttribute
//PURPOSE:
//	Looks through each property in the 'properties' section with a bindable 
//	attribute, or each method in the 'methods' section in the typelib for 
//	the propget/propset methods with the bindable attribute. If present, this
//	control will have to support the IPropertyNotifySink outgoing connection
//	point.
//INPUT PARAMETER(s):
//	LPTYPEINFO lpPropMethodTypeInfo	- Type info for props and methods
//	LPTYPEATTR pta - The type attribute object.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	TRUE - If a property or method is found with the bindable attribute.
//	FALSE -  If no property or method is found with the bindable attribute.
//***************************************************************************
BOOL CVContainView::CheckBindableAttribute ( LPTYPEINFO lpPropMethodTypeInfo, 
															LPTYPEATTR pta )
{
	if ( pta->cVars > 0 )
	{
		VARDESC * lpVarDesc;

		//Loop through each property until we find a bindable one.
		for ( int i = 0; i < pta->cVars; i++ )
		{
			lpPropMethodTypeInfo->GetVarDesc ( i, &lpVarDesc );
			
			if ( lpVarDesc->wVarFlags & FUNCFLAG_FBINDABLE )
			{
				//Property is bindable.
				lpPropMethodTypeInfo->ReleaseVarDesc ( lpVarDesc );
				return TRUE;
			}

			lpPropMethodTypeInfo->ReleaseVarDesc ( lpVarDesc );
		}
	}
	
	//At this point, no bindable props were found so look for bindable methods.
	if ( pta->cFuncs > 0 )
	{
		FUNCDESC * lpFuncDesc;											  

		//Loop through each method until we find a bindable one.
		for ( int i = 0; i < pta->cFuncs; i++ )
		{
			lpPropMethodTypeInfo->GetFuncDesc ( i, &lpFuncDesc );
			
			//Check to see if the method is bindable.  Also check to see if 
			//it is a propget/propset method.  This second criteria is 
			//actually not necessary in a correct type library but we check
			//it just the same since the information is easily available and
			//it may prevent an error if the type library is incorrect.
			if ( ( lpFuncDesc->wFuncFlags & FUNCFLAG_FBINDABLE )
				&& ( ( lpFuncDesc->invkind == INVOKE_PROPERTYGET ) ||
					  ( lpFuncDesc->invkind == INVOKE_PROPERTYPUT ) ) )
			{
				//Method is a bindable propget/propset method.
				lpPropMethodTypeInfo->ReleaseFuncDesc( lpFuncDesc );
				return TRUE;
			}

			lpPropMethodTypeInfo->ReleaseFuncDesc( lpFuncDesc );
		}
	}
	
	//At this point, no bindable props or methods were found.
	return FALSE;
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::CheckCoClassInfo
//PURPOSE:
//	Compares flags from the typelib to determine is certain characteristics 
//	exist for control.
//INPUT PARAMETER(s):	
//	LPTYPEINFO lpCoClassTypeInfo - Ptr to existing TypeInfo object 
//	int nImplTypeFlags - Flags to compare to see if this characteristic exists.
//	LPTYPEATTR pta - Ptr to the type attributes
//	BOOL * lpbQuestion - Ptr to pre-verify member variable that determines if 
//	this pre-verify question will be asked.
//OUTPUT PARAMETER(s):
//	BOOL * bQuestion - Set to TRUE to show that pre-veriy question must be 
//	asked since there was a problem getting this info from typelib.
//RETURN VALUE:
//  TRUE - If this characteristic exists
//  FALSE - If this characteristic does not exist
//***************************************************************************
BOOL CVContainView::CheckCoClassInfo ( LPTYPEINFO lpCoClassTypeInfo, 
				int nImplTypeFlags, LPTYPEATTR pta,	BOOL * lpbQuestion )
{
	ASSERT ( this != NULL );
	ASSERT ( lpCoClassTypeInfo != NULL );
	ASSERT ( pta != NULL );
	ASSERT ( lpbQuestion != NULL );
	ASSERT_POINTER ( lpCoClassTypeInfo, ITypeInfo );
	ASSERT_POINTER ( pta, TYPEATTR );
	ASSERT_POINTER ( &lpbQuestion, BOOL );

	//Return value if cannot find this info from type lib so question will be 
	//asked in preverify dialog box.
	*lpbQuestion = TRUE;
	BOOL bRetVal = TRUE;  //Arbitrary default return value.
	int nFlags;
	HREFTYPE hRefType;

	for  ( unsigned int i = 0; i < pta->cImplTypes; i++ ) 
	{
		if  ( SUCCEEDED ( lpCoClassTypeInfo->GetImplTypeFlags 
						( i, &nFlags ) )  &&
						( ( nFlags & IMPLTYPE_MASK ) == nImplTypeFlags ) )
		{
			//Get IID to find its attributes.
			LPTYPEINFO lpTypeInfo = NULL;

			//Since this type description describes a component object class,
			//retrieve the type description of the specified implemented 
			//interface types using GetRefTypeOfImplType.  The handle hRefType
			//can be passed to GetRefTypeInfo to get the type description.
			if  ( SUCCEEDED ( lpCoClassTypeInfo->GetRefTypeOfImplType 
							( i, &hRefType ) ) &&
							SUCCEEDED ( lpCoClassTypeInfo->GetRefTypeInfo 
									  ( hRefType, &lpTypeInfo ) ) )
			{
				ASSERT ( lpTypeInfo != NULL );
				ASSERT_POINTER ( lpTypeInfo, ITypeInfo );

				LPTYPEATTR lpAttr = NULL;
                
				if  ( SUCCEEDED  ( lpTypeInfo->GetTypeAttr ( &lpAttr ) ) )
				{
					//The characteristic exists.
					ASSERT ( lpAttr != NULL );
					ASSERT_POINTER ( lpAttr, LPTYPEATTR );
	
					bRetVal =  TRUE;

					if ( lpTypeInfo != NULL )
					{
						lpTypeInfo->ReleaseTypeAttr ( lpAttr );
					}
				}
				else
				{
					bRetVal = FALSE;
				}
					
				//Preverify question does not need to be asked.
				*lpbQuestion = FALSE;
				
				lpTypeInfo->Release ();
			}
			break;	//Stop iterating through loop
		}	
	}	
	
	return bRetVal;
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::LoadTypeLibFromCLSID
//PURPOSE:
//	Reads type library manually (without calling IDispatch, just as a type 
//	library browser does) to see if control exposes props or methods to 
//	determine if IDispatch is mandatory 
//	or optional.  
//INPUT PARAMETER(s):	
//	LPTYPELIB * lpPropMethodTypeLib - Ptr to empty typelib object
//OUTPUT PARAMETER(s):
//	None.
//RETURN VALUE:
//	TRUE - If the type library info was obtained and placed int 
//	lpPropMethodTypeInfo.
//	FALSE -	Unable to obtain type library information.
//***************************************************************************
BOOL CVContainView::LoadTypeLibFromCLSID ( LPTYPELIB * lpPropMethodTypeLib )
{
	ASSERT ( this != NULL );
	ASSERT ( lpPropMethodTypeLib != NULL );
	ASSERT_POINTER ( lpPropMethodTypeLib, ITypeLib );

	LPOLESTR lpClsid = NULL;
	HKEY hRegKey;
	CString sRegSubKey;
	TCHAR szTypeLibClsid[50];
	LONG cb = sizeof ( szTypeLibClsid );
	
	//Using the CLSID of the control, read under 
	//HKEY_CLASSES_ROOT\CLSID\m_clsid\TypeLib to get the CLSID of the type lib.  
	//Get a string containing the class name.  
	if ( FAILED ( StringFromCLSID ( m_verify->m_clsid, &lpClsid ) ) )
	{
		return FALSE;
	}
	
	ASSERT ( lpClsid != NULL );
	ASSERT_POINTER ( lpClsid, LPOLESTR );

	sRegSubKey = "CLSID\\";
   	sRegSubKey += lpClsid;
    
	//Read from HKEY_CLASSES_ROOT\CLSID\m_clsid\TYPELIB to get the classid 
	//of type lib.  Read the key value into hRegKey.
    if ( RegOpenKey ( HKEY_CLASSES_ROOT, ( LPCTSTR ) sRegSubKey, &hRegKey )
														== ERROR_SUCCESS ) 
	{
	    if ( RegQueryValue ( hRegKey, TEXT ( "TYPELIB"), szTypeLibClsid, &cb ) 
													== ERROR_SUCCESS )
		{
			ASSERT ( szTypeLibClsid != NULL );

			//We now have the CLSID for the control's type library.  Read 
			//from HKEY_CLASSES_ROOT\CLSID\m_clsid\VERSION to get the version
			//info of the type library to pass into the LoadRegTypeLib call. 
			//szVerBuff holds the verion # in the format of 
			//majorversion.minorversion (ex. "1.0").
			TCHAR szVerBuff[6];	

			if ( RegQueryValue ( hRegKey, TEXT ( "VERSION" ), szVerBuff, &cb )
												   == ERROR_SUCCESS )
			{
				ASSERT ( szVerBuff != NULL );

				WORD wVerMajor; 
				WORD wVerMinor;
				WCHAR szAnsiClsid[50];
				CLSID typeLibClsid;
				
				ASSERT ( hRegKey != NULL );
				RegCloseKey( hRegKey );

				//Prepare the clsid to be passed in.
#ifndef UNICODE
	if ( MultiByteToWideChar ( CP_ACP, 0, szTypeLibClsid, -1,  szAnsiClsid, 50 ) )
#else
	lstrcpy (szAnsiClsid, szTypeLibClsid );
#endif

					{
					ASSERT ( szAnsiClsid != NULL );

					//Parse the version number.
					if ( ParseVersion ( szVerBuff, &wVerMajor, &wVerMinor ) )
					{
						ASSERT ( &wVerMajor != NULL );
						ASSERT ( &wVerMinor != NULL );

						if ( SUCCEEDED  ( CLSIDFromString ( szAnsiClsid,  
									( LPCLSID )  &typeLibClsid ) ) )
						{
							ASSERT ( typeLibClsid != GUID_NULL );
							
							//The type library is registered so load it..
							if ( SUCCEEDED  ( LoadRegTypeLib 
									( typeLibClsid, wVerMajor, wVerMinor, 
									GetUserDefaultLCID (), 
									lpPropMethodTypeLib ) ) )
							{
								return TRUE;
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}


//***************************************************************************
//METHOD NAME:			
//	CVContainView::CheckMiscStatusBits
//PURPOSE:
//	Checks certain misc status bits for the control in the registry to determine
//	if certain interfaces/methods are mandatory.   
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::CheckMiscStatusBits ( CPreVerifyDlg * dlg )
{
	ASSERT ( m_pControlSite != NULL );

	if ( m_pControlSite->m_dwMiscStatus	> 0 ) 
	{
		//Check the misc status bits to determine if questions need to be
		//asked or not that determine mandatory or optional for certain 
		//calls.  If the misc status bits cannot be found, then the question
		//will be asked.
		
		//See if the OLEMISC_CANTLINKINSIDE bit is present. If it is, 
		//this means that the control DOES NOT support external links.
		if ( m_pControlSite->m_dwMiscStatus & OLEMISC_CANTLINKINSIDE ) 
		{
			m_bLinks = FALSE;
		}
		else
		{
			m_bLinks = TRUE;
		}

		//No need to ask questions about external links.
		dlg->m_bEnableLinksQuestion = FALSE;


		//See if the control is visible at runtime for certain methods calls.  
		if ( m_pControlSite->m_dwMiscStatus & OLEMISC_INVISIBLEATRUNTIME )
		{
			m_bInvisibleAtRuntime = TRUE;
		}
		else
		{
			m_bInvisibleAtRuntime = FALSE;
		}

		//OLEMISC_NOUIACTIVATE says a control doesn’t support UI Activation. 
		if (  ( m_pControlSite->m_dwMiscStatus & OLEMISC_NOUIACTIVATE )
			|| ( m_bInvisibleAtRuntime ) )
		{
			m_bUI = FALSE;
		}
		else
		{
			m_bUI = TRUE;
		}

		//No need to ask question about UI.
		dlg->m_bEnableUIQuestion = FALSE;
	}
	else
	{
		//The misc status bits cannot be found so we must ask certain questions.
		dlg->m_bEnableUIQuestion = TRUE;
		dlg->m_bEnableLinksQuestion = TRUE;
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::ReadVerifyDlg
//PURPOSE:
//	Determines Yes (or No) response to pre-verification questions about the 
//control's characteristics.  The value of a checked box is 1, while unchecked
// is 0. This matches up with our constants FALSE = 0 and TRUE = 1.
//INPUT PARAMETER(s):	
//	CPreVerifyDlg * dlg - Ptr to pre-verification dialog.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CVContainView::ReadVerifyDlg ( CPreVerifyDlg * dlg ) 
{
	ASSERT ( this != NULL );
	ASSERT ( dlg != NULL );
	ASSERT_POINTER ( dlg, CPreVerifyDlg );

	//These questions are always asked since this information is not in the 
	//type lib or registry.
	m_bAmbients = dlg->m_Ambients_Yes;
	m_bMnemonics = dlg->m_Mnemonics_Yes;
	m_bPropSets = dlg->m_Prop_Set_Yes;
	m_bAccelerators = dlg->m_Accelerators_Yes;

	//These questions are sometimes asked since there may be a problem getting
	//it from the type lib for many reasons.  If these controls were visible
	//(meaning the information was not available from the type lib), read in
	//these values.
	if ( dlg->m_bEnableConnPtQuestion )
	{
		m_bConnPoints = dlg->m_Notifications_Yes;
	}

	if ( dlg->m_bEnablePropMethodQuestion )
	{
		m_bPropsMethods = dlg->m_PropsMethods_Yes;
	}
	
	if ( dlg->m_bEnableLicensedQuestion )
	{
		m_bLicensed = dlg->m_Licensing_Yes;
	}

	if ( dlg->m_bEnableLinksQuestion )
	{
		m_bLinks = dlg->m_Links_Yes;
	}

	if ( dlg->m_bEnableUIQuestion )
	{
		m_bUI = dlg->m_UI_Yes;
	}

	if ( dlg->m_bEnablePropPagesQuestion )
	{
		m_bPropPages = dlg->m_Prop_Pages_Yes;
	}
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::ParseVersion
//PURPOSE:
//	Convert the version of the type lib from char[] to WORD to pass into 
//	LoadRegTypeLib. 
//INPUT PARAMETER(s):
//	char szVerBuff[] - Char representation of version in 
//	"majorversion.minorversion"format.
//	WORD * wVerMajor - Ptr to major version number.
//	WORD * wVerMinor - Ptr to minor version number.
//OUTPUT PARAMETER(s):
//	WORD * wVerMajor - Will hold major version when function returns.
//	WORD * wVerMinor - Will hold minor version when function returns.
//RETURN VALUE:
//	TRUE - If conversion was successful
//	FALSE - If conversion was not successful
//***************************************************************************
BOOL CVContainView::ParseVersion ( TCHAR szVerBuff[], 
										WORD * wVerMajor, WORD * wVerMinor )
{
	//Max buffer size for converting version information.
	#define MAXBUFSIZE	10

	ASSERT ( this != NULL );
	ASSERT ( szVerBuff != NULL );
	ASSERT ( ( wVerMajor != NULL ) && ( wVerMinor != NULL ) );
	ASSERT_POINTER ( wVerMajor, WORD );
	ASSERT_POINTER ( wVerMinor, WORD );

	TCHAR szBufMajor[MAXBUFSIZE];
	TCHAR szBufMinor[MAXBUFSIZE];
	int iVerBufIndex = 0, iMinorBufIndex = 0;

	//Clear out buffers.
	memset ( szBufMajor, 0, MAXBUFSIZE );
	memset ( szBufMinor, 0, MAXBUFSIZE );

	//Loop until we find the period since the major version # may be >1 digit.
	while ( szVerBuff[iVerBufIndex] != '.' )
	{
		szBufMajor[iVerBufIndex] = szVerBuff[iVerBufIndex];	
		iVerBufIndex++;
	}
	
	//When loop exits, we are at the period so add the null terminator.
	szBufMajor[iVerBufIndex] = NULL;

	//Loop starting with the first digit to the right of the period until 
	//null terminator.
	iVerBufIndex++;
	while ( szVerBuff[iVerBufIndex] != NULL )
	{	
		szBufMinor[iMinorBufIndex] = szVerBuff[iVerBufIndex];
		iVerBufIndex++;
		iMinorBufIndex++;
	}

	//When loop exits, we are at end of minor versio number so add the 
	//null terminator.
	szBufMinor[iMinorBufIndex] = NULL;

	//We must call atoi since we pass the version numbers as WORD types 
	//to LoadRegTypeLib.
#ifndef UNICODE
	*wVerMajor =  ( WORD )  atoi ( szBufMajor );
	*wVerMinor =  ( WORD )  atoi ( szBufMinor );
#else
	*wVerMajor =  ( WORD )  _wtoi ( szBufMajor );
	*wVerMinor =  ( WORD )  _wtoi ( szBufMinor );
#endif	
	
	return TRUE;
}



//***************************************************************************
//METHOD NAME:			
//	CVContainView::OnDeleteControl
//PURPOSE:
//	Deactivates the control, then deletes it, frees heap memory, and 
//	reinitializes the boolean member variables.
//INPUT PARAMETER(s):
//	None.
//OUTPUT PARAMETER(s):
//	None.
//RETURN VALUE:
//	None.
//***************************************************************************
void CVContainView::OnDeleteControl () 
{
	ASSERT ( m_pControlSite != NULL );
	
	//Delete the control and release memory held by its CWnd derived object.
	m_pControlSite->DestroyControl ();
	delete m_verify;
		
	//Reinitialize the boolean members of the view class that reflect the 
	//status of a control in the container's window.
	InitStatusMembers ();
}


//***************************************************************************
//Menu enabling rountines:
//***************************************************************************
void CVContainView::OnUpdateInsertControl ( CCmdUI* pCmdUI )  
{
	//Deactivate the "Insert Control" menu item once the control has been 
	//instantiated.
	pCmdUI->Enable ( !m_bControlExists );
}

void CVContainView::OnUpdateVerifyControl ( CCmdUI* pCmdUI )  
{
	//Activate the "Verify All Interfaces" menu item only if the control is 
	///instantiated.
	pCmdUI->Enable ( m_bControlExists );
}

void CVContainView::OnUpdateVerifySpecific ( CCmdUI* pCmdUI )  
{
	//Activate the "Verify Specific Interfaces" menu item only if the control 
	//is instantiated.
	pCmdUI->Enable ( m_bControlExists );
}

void CVContainView::OnUpdateViewResults ( CCmdUI* pCmdUI )  
{
	//Activate the "View Results" menu item only if at least one verification 
	//rocess has run.
	pCmdUI->Enable ( m_bVerified );
}

void CVContainView::OnUpdateDeleteControl ( CCmdUI* pCmdUI )  
{
	//Activate the "Delete Control" menu item only if the control is 
	//instantiated.
	pCmdUI->Enable ( m_bControlExists );
}


