// VConCtl.cpp : Implementation of the CVControlCtrl OLE control class.

#include "stdafx.h"
#include "VControl.h"
#include "VConCtl.h"
#include "VConPpg.h"
#include "Resltdlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVControlCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVControlCtrl, COleControl)
	//{{AFX_MSG_MAP(CVControlCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CVControlCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CVControlCtrl)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CVControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CVControlCtrl, COleControl)
	//{{AFX_EVENT_MAP(CVControlCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CVControlCtrl, 1)
	PROPPAGEID(CVControlPropPage::guid)
END_PROPPAGEIDS(CVControlCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVControlCtrl, "VCONTROL.VControlCtrl.1",
	0x5315d1c3, 0xc03d, 0x11ce, 0x85, 0xc3, 0, 0xaa, 0, 0x57, 0xa5, 0x40)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CVControlCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DVControl =
		{ 0xf351f21, 0x20db, 0x11cf, { 0xaa, 0xc, 0, 0x80, 0xc7, 0x8a, 0x1d, 0x7f } };
const IID BASED_CODE IID_DVControlEvents =
		{ 0xf351f22, 0x20db, 0x11cf, { 0xaa, 0xc, 0, 0x80, 0xc7, 0x8a, 0x1d, 0x7f } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwVControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_SIMPLEFRAME;


IMPLEMENT_OLECTLTYPE(CVControlCtrl, IDS_VCONTROL, _dwVControlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::CVControlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CVControlCtrl

BOOL CVControlCtrl::CVControlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VCONTROL,
			IDB_VCONTROL,
			FALSE,                      //  Not insertable
			_dwVControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::CVControlCtrl - Constructor

CVControlCtrl::CVControlCtrl()
{
	InitializeIIDs(&IID_DVControl, &IID_DVControlEvents);

	EnableSimpleFrame();
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::~CVControlCtrl - Destructor

CVControlCtrl::~CVControlCtrl()
{
	DeleteResults();
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::OnDraw - Drawing function

void CVControlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CString str;
	DoSuperclassPaint(pdc, rcBounds);
	str.LoadString( IDS_VERIFY_CONTAINER );
	SetWindowText( str );
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::DoPropExchange - Persistence support

void CVControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::OnResetState - Reset control to default state

void CVControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::AboutBox - Display an "About" box to the user

void CVControlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_VCONTROL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CVControlCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::IsSubclassedControl - This is a subclassed control

BOOL CVControlCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl::OnOcmCommand - Handle command messages

LRESULT CVControlCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	//Begin verification process when user clicks on it.
	if ( wNotifyCode == BN_CLICKED )
	{
		OnVerify();
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl message handlers
void CVControlCtrl::DeleteResults()
{
	// Destroy all the results
	for( int i = 0; i <= m_resultsInterfaceArray.GetUpperBound(); i++ )
	{
		delete m_resultsInterfaceArray[i];
	}
	m_resultsInterfaceArray.RemoveAll();
}

///////////////////////////////////////////////////////////////////
// Interface Verification routines.
// For the sake of clarity we have a routine for each interface we have to test.
// These interface verification routines first QI for the interface and assuming 
// that the interface is found they then call the methods on the interfaces and
// check the return values. If it is possible to check any additional values or
// behaviour then this is also carried out.
//
// IMPORTANT
//	This control does not and cannot verify the behaviour of the container.
//	The control simply checks the return values from method calls. This does
//	not necessarily mean that the container has honoured the method call and 
//	executed the expected behaviour.
//
///////////////////////////////////////////////////////////////////
void CVControlCtrl::OnVerify()
{

	DeleteResults();

	// Let's get the IUnknown for our container.
	// We'll use the stored IOleClientSite pointer m_pClientSite
	// to get our own seperate IUnknown
	ASSERT( m_pClientSite != NULL );

	LPUNKNOWN lpIUnknown;
	if ( m_pClientSite->QueryInterface( IID_IUnknown, (void**) &lpIUnknown ) == S_OK )
	{
		ASSERT( lpIUnknown != NULL );
	
		VerifyIOleClientSite( lpIUnknown );

		VerifyIOleInPlaceSite( lpIUnknown );
		VerifyIOleInPlaceFrame( lpIUnknown );

		VerifyIOleControlSite( lpIUnknown );
		VerifyIOleContainer( lpIUnknown );
		VerifyIAdviseSink( lpIUnknown );
		

		VerifyIDispatchAmbients( lpIUnknown );

		VerifyIDispatchEvents();
		VerifyISimpleFrameSite( lpIUnknown );
		VerifyIPropertyNotifySink();
		VerifyExtendedControl();


		// Release IUnknown
		lpIUnknown->Release();

		// let's display the results in a dialog box
		CResultsDialog dlg;

		dlg.m_pInterfaceResultsArray = &m_resultsInterfaceArray;

		dlg.DoModal();

	}

	InvalidateControl();
}


//////////////////////////////////////////////////////
// VerifyIOleClientSite - IOleClientSite verification
// Support for this interface is mandatory.
//
void CVControlCtrl::VerifyIOleClientSite( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;
	
	// Do a QI for IOleClientSite. We assume the pointer to IUnknown we have been given is valid.
	LPOLECLIENTSITE lpIOleClientSite;
	hresult = lpIUnknown->QueryInterface( IID_IOleClientSite, (void**) &lpIOleClientSite );
	// Log the result for an Interface, Mandatory.
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IOleClientSiteQI, strResult );
	if ( ( hresult == S_OK ) && ( pInterfaceResult != NULL ) )
	{
		if ( lpIOleClientSite != NULL )
		{
			// IOleClientSite::SaveObject
			// This method is not mandatory.
			hresult = lpIOleClientSite->SaveObject();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleClientSiteSaveObject, strResult );


			// IOleClientSite::GetMoniker
			// This method is not mandatory.
			// if S_OK is returned we must release the interface that we were given.
			LPMONIKER lpIMoniker;
			hresult = lpIOleClientSite->GetMoniker( OLEGETMONIKER_ONLYIFTHERE, 
														OLEWHICHMK_CONTAINER,
														&lpIMoniker );
			if ( hresult == S_OK )
			{
				if ( lpIMoniker != NULL )
				{
					lpIMoniker->Release();
				}
			}
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleClientSiteGetMoniker, strResult );
			
														
			// IOleClientSite::GetContainer
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			// if S_OK is returned we must release the interface that we were given.
			LPOLECONTAINER lpIOleContainer;
			CString strAdditional;
			hresult = lpIOleClientSite->GetContainer( &lpIOleContainer );
			if ( hresult == S_OK )
			{
				if ( lpIOleContainer != NULL )
				{
					lpIOleContainer->Release();
				}				
			}
			strAdditional.LoadString( IDS_IOleContainerAddress );
			CString strAddress;
			strAddress.Format( _T ("0x%08x"),lpIOleContainer );
			strAdditional += strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleClientSiteGetContainer, strResult + ", " + strAdditional );

 
			// IOleClientSite::ShowObject
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleClientSite->ShowObject();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleClientSiteShowObject, strResult );


			// IOleClientSite::OnShowWindow
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleClientSite->OnShowWindow(TRUE);
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleClientSiteOnShowWindow, strResult );

			
			// IOleClientSite::RequestNewObjectLayout
			// This method is NOT mandatory.
			hresult = lpIOleClientSite->RequestNewObjectLayout();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleClientSiteRequestNewObjectLayout, strResult );

			// Please release me let me go!
			lpIOleClientSite->Release();
		}
	}

}

//////////////////////////////////////////////////////
// VerifyIOleInPlaceSite - IOleInPlaceSite verification
//
void CVControlCtrl::VerifyIOleInPlaceSite( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;

	CString strAdditional;

	// Do a QI for IOleInPlaceSite. We assume the pointer to IUnknown we have been given is valid.
	LPOLEINPLACESITE lpIOleInPlaceSite;
	hresult = lpIUnknown->QueryInterface( IID_IOleInPlaceSite, (void**) &lpIOleInPlaceSite );
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteQI, strResult );
	if ( ( hresult == S_OK ) && ( pInterfaceResult != NULL ) )
	{
		if ( lpIOleInPlaceSite != NULL )
		{

	
			// IOleInPlaceSite::GetWindow
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			HWND hwnd;
			hresult = lpIOleInPlaceSite->GetWindow( &hwnd );
			strAdditional.LoadString( IDS_WINDOWHANDLE );
			CString strHandle;
			strHandle.Format( _T( "0x%08x" ),hwnd );
			strAdditional += strHandle;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteGetWindow, strResult + ", " + strAdditional );



			// IOleInPlaceSite::ContextSensitiveHelp
			// This method is not mandatory.
			hresult = lpIOleInPlaceSite->ContextSensitiveHelp( TRUE );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceSiteContextSensitiveHelp, strResult );
			//Better return teh help to the way it was
			hresult = lpIOleInPlaceSite->ContextSensitiveHelp( FALSE );



			// IOleInPlaceSite::OnUIActivate
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->OnUIActivate();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteOnUIActivate, strResult );


			
			// IOleInPlaceSite::OnUIDeactivate
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->OnUIDeactivate( FALSE );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteOnUIDeactivate, strResult );



			// IOleInPlaceSite::GetWindowContext
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			LPOLEINPLACEFRAME pFrame;
			LPOLEINPLACEUIWINDOW pDoc;
			RECT rcPosRect;
			RECT rcClipRect;
			OLEINPLACEFRAMEINFO FrameInfo;
			FrameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
			hresult = lpIOleInPlaceSite->GetWindowContext( &pFrame, &pDoc, &rcPosRect, &rcClipRect, &FrameInfo );
			strAdditional.LoadString( IDS_FRAMEADDRESS );
			CString strAddress;
			strAddress.Format( _T ( "0x%08x" ),pFrame );
			strAdditional += strAddress;
			CString strText;
			strText.LoadString( IDS_DOCADDRESS );
			strAddress.Format( _T ( "0x%08x" ),pDoc );
			strAdditional += "  " + strText + strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteGetWindowContext, strResult + ", " + strAdditional );
			if ( hresult == S_OK )
			{
				// We must release the interfaces we did get
				if ( pFrame != NULL )
				{
					pFrame->Release();
				}
				if ( pDoc !=NULL )
				{
					pDoc->Release();
				}
			}

			
			// IOleInPlaceSite::Scroll
			// This method is not mandatory.
			SIZE size;
			size.cx = 0;
			size.cy = 0;
			hresult = lpIOleInPlaceSite->Scroll( size );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceSiteScroll, strResult );


			
			// IOleInPlaceSite::CanInPlaceActivate
			// This method is mandatory. A returned HRESULT of S_OK or S_FALSE is acceptable.
			hresult = lpIOleInPlaceSite->CanInPlaceActivate();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK) || (hresult == S_FALSE), IDS_IOleInPlaceSiteCanInPlaceActivate, strResult );



			// IOleInPlaceSite::OnInPlaceDeactivate
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->OnInPlaceDeactivate();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteOnInPlaceDeactivate, strResult );



			// IOleInPlaceSite::OnInPlaceActivate
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->OnInPlaceActivate();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteOnInPlaceActivate, strResult );

			

			// IOleInPlaceSite::DiscardUndoState
			// This method is not mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->DiscardUndoState();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, (hresult == S_OK), IDS_IOleInPlaceSiteDiscardUndoState, strResult );


			
			// IOleInPlaceSite::DeactivateAndUndo
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			hresult = lpIOleInPlaceSite->DeactivateAndUndo();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteDeactivateAndUndo, strResult );


			
			// IOleInPlaceSite::OnPosRectChange
			// This method is mandatory. A returned HRESULT of S_OK is acceptable.
			RECT rect;
			GetRectInContainer( &rect );
			hresult = lpIOleInPlaceSite->OnPosRectChange( &rect );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceSiteOnPosRectChange, strResult );


			// Please release me let me go!
			lpIOleInPlaceSite->Release();
		}
	}
}

//////////////////////////////////////////////////////
// VerifyIOleInPlaceFrame - IOleInPlaceFrame verification
//
void CVControlCtrl::VerifyIOleInPlaceFrame( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;
	CString strResult;
	CString strAdditional;
	LPOLEINPLACEFRAME lpIOleInPlaceFrame = NULL;
	CInterfaceVerificationResult* pInterfaceResult = NULL;

	// We get the InPlace Frame via the InPlaceSite
	// Do a QI for IOleInPlaceSite. We assume the pointer to IUnknown we have been given is valid.
	LPOLEINPLACESITE lpIOleInPlaceSite;
	if ( lpIUnknown->QueryInterface( IID_IOleInPlaceSite, (void**) &lpIOleInPlaceSite ) == S_OK )
	{
		if ( lpIOleInPlaceSite != NULL )
		{
	
			// IOleInPlaceSite::GetWindowContext
			LPOLEINPLACEUIWINDOW pDoc;
			RECT rcPosRect;
			RECT rcClipRect;
			OLEINPLACEFRAMEINFO FrameInfo;
			FrameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
			hresult = lpIOleInPlaceSite->GetWindowContext( &lpIOleInPlaceFrame, &pDoc, &rcPosRect, &rcClipRect, &FrameInfo );
			if ( hresult == S_OK )
			{
				// We release the InPlaceDocument Window interface 
				if ( pDoc !=NULL )
				{
					pDoc->Release();
				}
			}
			strAdditional.LoadString( IDS_FRAMEADDRESS );
			CString strAddress;
			strAddress.Format( _T ( "0x%08x" ),lpIOleInPlaceFrame );
			strAdditional += strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceFrameAddress, strResult + ", " + strAdditional );

			lpIOleInPlaceSite->Release();
		}
	}


	if ( ( lpIOleInPlaceFrame != NULL ) && ( pInterfaceResult != NULL ) )
	{
		HRESULT hresult = S_OK;
		
		// IOleInPlaceFrame::GetWindow
		// This method is mandatory. A returned HRESULT of S_OK is acceptable.
		HWND hwnd;
		hresult = lpIOleInPlaceFrame->GetWindow( &hwnd );
		strAdditional.LoadString( IDS_WINDOWHANDLE );
		CString strHandle;
		strHandle.Format( _T ( "0x%08x" ),hwnd );
		strAdditional += strHandle;
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceFrameGetWindow, strResult + ", " + strAdditional );



		// IOleInPlaceFrame::ContextSensitiveHelp
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->ContextSensitiveHelp( TRUE );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameContextSensitiveHelp, strResult );
		//Better return the help to the way it was
		hresult = lpIOleInPlaceFrame->ContextSensitiveHelp( FALSE );



		// IOleInPlaceFrame::GetBorder
		// This method is not mandatory.
		RECT rect;
		hresult = lpIOleInPlaceFrame->GetBorder( &rect );
		strAdditional.LoadString( IDS_RECT );
		CString strResult;
		strResult.Format( _T ( "%d, %d, %d, %d" ), rect.left, rect.top, rect.right, rect.bottom );
		strAdditional += strResult;
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameGetBorder, strResult + " ," + strAdditional );



		// IOleInPlaceFrame::RequestBorderSpace
		// This method is not mandatory.
		BORDERWIDTHS border;
		border.top = 5;
		border.left = 5;
		border.bottom = 5;
		border.right = 5;
		hresult = lpIOleInPlaceFrame->RequestBorderSpace( &border );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameRequestBorderSpace, strResult );



		// IOleInPlaceFrame::SetBorderSpace
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->SetBorderSpace( NULL );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameSetBorderSpace, strResult );


		
		// IOleInPlaceFrame::SetActiveObject
		// This method is mandatory. A returned HRESULT of S_OK is acceptable.
		hresult = lpIOleInPlaceFrame->SetActiveObject( &m_xOleInPlaceActiveObject, NULL );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IOleInPlaceFrameSetActiveObject, strResult );



		// Now we have to test the menu integration methods InsertMenus, SetMenu, RemoveMenus
		// we do this as a sequence of calls.
		OLEMENUGROUPWIDTHS menuWidths;
		memset(&menuWidths, 0, sizeof menuWidths);
		HMENU hSharedMenu = NULL;
		HOLEMENU hOleMenu = NULL;

		// Create shared menu
		if (( hSharedMenu = ::CreateMenu()) == NULL)
		{
			// oh dear let's give up
			return;
		}


		// IOleInPlaceFrame::InsertMenus
		// This method is not mandatory.
		// Start out by getting menu from container using InsertMenus
		hresult = lpIOleInPlaceFrame->InsertMenus( hSharedMenu, &menuWidths);
		strAdditional.LoadString( IDS_MENUWIDTHS );
		strResult.Format( _T ( "%d, %d, %d, %d, %d, %d" ), menuWidths.width[0], menuWidths.width[1], menuWidths.width[2], menuWidths.width[3], menuWidths.width[4], menuWidths.width[5] );
 		strAdditional += strResult;
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameInsertMenus, strResult + ", " + strAdditional );


		// Add in our own little mundane menu
		CString s;
		::InsertMenu(hSharedMenu, menuWidths.width[0], MF_BYPOSITION, IDM_TESTMENU, _T ( "Verify Test" ) );
		menuWidths.width[1] = 1;
		hOleMenu = ::OleCreateMenuDescriptor( hSharedMenu, &menuWidths);
	
		// And Set the menu!
		// IOleInPlaceFrame::SetMenu
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->SetMenu( hSharedMenu, hOleMenu, m_hWnd);
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameSetMenu, strResult );


		// And Remove the menu!
		// IOleInPlaceFrame::RemoveMenus
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->RemoveMenus( hSharedMenu );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameRemoveMenus, strResult );


		// Return it to the way it was
		hresult = lpIOleInPlaceFrame->SetMenu( NULL, NULL, NULL);

		if ( hSharedMenu != NULL )
		{
			::DestroyMenu(hSharedMenu);
			hSharedMenu = NULL;
		}
		
		if ( hOleMenu != NULL )
		{
			::OleDestroyMenuDescriptor( hOleMenu );
		}

		// IOleInPlaceFrame::SetStatusText
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->SetStatusText( OLESTR("VControl put this here!") );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameSetStatusText, strResult );

		
		// IOleInPlaceFrame::EnableModeless
		// This method is not mandatory.
		hresult = lpIOleInPlaceFrame->EnableModeless( TRUE );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameEnableModeless, strResult );


		// IOleInPlaceFrame::TranslateAccelerator
		// This method is not mandatory.
		MSG msg;
		memset(&msg, 0, sizeof msg);
		WORD wID = 0;
		hresult = lpIOleInPlaceFrame->TranslateAccelerator( &msg, wID );
		GetSCodeDescription( hresult, strResult );
		pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleInPlaceFrameTranslateAccelerator, strResult );


		// call IOleInPlaceFrame::SetActiveObject with NULL to counteract our SetActiveObject call earlier.
		lpIOleInPlaceFrame->SetActiveObject( NULL, NULL );

		// release 
		lpIOleInPlaceFrame->Release();
	}
}

//////////////////////////////////////////////////////
// VerifyIOleControlSite - IOleControlSite verification
//
void CVControlCtrl::VerifyIOleControlSite( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;
	CString strAdditional;
	
	// Do a QI for IOleControlSite. We assume the pointer to IUnknown we have been given is valid.
	LPOLECONTROLSITE lpIOleControlSite;
	hresult = lpIUnknown->QueryInterface( IID_IOleControlSite, (void**) &lpIOleControlSite );
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IOleControlSiteQI, strResult );
	if ( hresult == S_OK )
	{
		if ( lpIOleControlSite != NULL )
		{

			// IOleControlSite::OnControlInfoChanged
			// This method is mandatory.
			hresult = lpIOleControlSite->OnControlInfoChanged();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult != E_NOTIMPL), IDS_IOleControlSiteOnControlInfoChanged, strResult );


			// IOleControlSite::LockInPlaceActive
			// This method is not mandatory.
			hresult = lpIOleControlSite->LockInPlaceActive( TRUE );
			// unlock it
			hresult = lpIOleControlSite->LockInPlaceActive( FALSE );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleControlSiteLockInPlaceActive, strResult );


			// IOleControlSite::GetExtendedControl
			// This method is not mandatory.
			LPDISPATCH lpIDispatch;
			hresult = lpIOleControlSite->GetExtendedControl( &lpIDispatch );
			strAdditional.LoadString( IDS_IDISPATCHADDRESS );
			CString strAddress;
			strAddress.Format( _T ( "0x%08x" ),lpIDispatch );
			strAdditional += strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleControlSiteGetExtendedControl, strResult + ", " + strAdditional );
			if ( hresult == S_OK )
			{
				if ( lpIDispatch != NULL )
				{
					lpIDispatch->Release();
				}
			}

		
			// IOleControlSite::TransformCoords
			// This method is mandatory.
			POINTL PtlHiMetric;
			POINTF PtfContainer; 
			memset(&PtlHiMetric, 0, sizeof PtlHiMetric);
			memset(&PtfContainer, 0, sizeof PtfContainer);
			hresult = lpIOleControlSite->TransformCoords( &PtlHiMetric, &PtfContainer, XFORMCOORDS_POSITION | XFORMCOORDS_HIMETRICTOCONTAINER );
			strAdditional.LoadString( IDS_HIMETRIC );
			CString strResult;
			strResult.Format( _T ( " %d, %d" ),PtlHiMetric.x, PtlHiMetric.y );
			strAdditional += strResult;
			strResult.LoadString( IDS_CONTAINER );
			strAdditional += "  " +strResult;
			strResult.Format( _T ( " %f, %f"),PtfContainer.x, PtfContainer.y );
			strAdditional += strResult;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult != E_NOTIMPL), IDS_IOleControlSiteTransformCoords, strResult + ", " + strAdditional );



			// IOleControlSite::TranslateAccelerator
			// This method is not mandatory.
			MSG msg;
			memset(&msg, 0, sizeof msg);
			DWORD grfModifiers = 0;
			hresult = lpIOleControlSite->TranslateAccelerator( &msg, grfModifiers );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleControlSiteTranslateAccelerator, strResult );



			// IOleControlSite::OnFocus
			// This method is mandatory.
			hresult = lpIOleControlSite->OnFocus( TRUE );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult != E_NOTIMPL), IDS_IOleControlSiteOnFocus, strResult );

		

			// IOleControlSite::ShowPropertyFrame
			// This method is not mandatory.
			hresult = lpIOleControlSite->ShowPropertyFrame();
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleControlSiteShowPropertyFrame, strResult );


			// Don't forget
			lpIOleControlSite->Release();
		}
	}

}
																 
//////////////////////////////////////////////////////
// VerifyIOleContainer - IOleContainer verification
//
void CVControlCtrl::VerifyIOleContainer( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;
	CString strAdditional;

	// Get the IOleContainer interface
	// We do this from the IOleClientSite Interface
	// I know we did that before as part of another test but
	// this control is written for clarity (although you probably wouldn't think it). 
	// Do a QI for IOleClientSite. We assume the pointer to IUnknown we have been given is valid.
	LPOLECLIENTSITE lpIOleClientSite;
	hresult = lpIUnknown->QueryInterface( IID_IOleClientSite, (void**) &lpIOleClientSite );
	if ( hresult == S_OK )
	{
		if ( lpIOleClientSite != NULL )
		{

											
			LPOLECONTAINER lpIOleContainer;
			hresult = lpIOleClientSite->GetContainer( &lpIOleContainer );
			CString strResult;
			GetSCodeDescription( hresult, strResult );
			CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IOleContainerQI, strResult );
			if ( hresult == S_OK )
			{
				if ( lpIOleContainer != NULL )
				{

					// IOleContainer::ParseDisplayName
					// This method is not mandatory
					LPBC lpbc;
					CreateBindCtx( 0, &lpbc );
  					ULONG ulLength;
					IMoniker* pmkOut;
					hresult = lpIOleContainer->ParseDisplayName( lpbc, OLESTR("ASTRING"), &ulLength, &pmkOut );
					if ( hresult == S_OK )
					{
						if ( pmkOut != NULL )
						{
							pmkOut->Release();
						}
					}
					GetSCodeDescription( hresult, strResult );
					pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleContainerParseDisplayName, strResult );



					// IOleContainer::EnumObjects
					// This method is mandatory
					LPENUMUNKNOWN lpIEnumUnknown;
					hresult = lpIOleContainer->EnumObjects( OLECONTF_EMBEDDINGS, &lpIEnumUnknown );
					strAdditional.LoadString( IDS_IENUMUNKNOWNADDRESS );
					CString strAddress;
					strAddress.Format( _T ( "0x%08x" ),lpIEnumUnknown );
					strAdditional += strAddress;
					GetSCodeDescription( hresult, strResult );
					pInterfaceResult->LogMethodResult( TRUE, (hresult != E_NOTIMPL), IDS_IOleContainerEnumObjects, strResult + ", " + strAdditional );
					if ( hresult == S_OK )
					{
						if ( lpIEnumUnknown != NULL )
						{
							lpIEnumUnknown->Release();
						}
					}


					// IOleContainer::LockContainer
					// This method is not mandatory
					hresult = lpIOleContainer->LockContainer( FALSE );
					GetSCodeDescription( hresult, strResult );
					pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IOleContainerLockContainer, strResult );


					lpIOleContainer->Release();
				}				
			}
			lpIOleClientSite->Release();
		}
	}

}

//////////////////////////////////////////////////////
// VerifyIDispatchAmbients - IDispatch verification for container's Ambient properties
//
void CVControlCtrl::VerifyIDispatchAmbients( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;
	CString strAdditional;

	// First of all let's get the IDispatch for ambient properties
	// This is mandatory
	// Do a QI for IDispatch. We assume the pointer to IUnknown we have been given is valid.
	LPDISPATCH lpIDispatch;
	hresult = lpIUnknown->QueryInterface( IID_IDispatch, (void**) &lpIDispatch );
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IDispatchAmbientsQI, strResult );
	if ( hresult == S_OK )
	{
		if ( lpIDispatch != NULL )
		{
			
			// IDispatch::GetTypeInfoCount
			// This method is not mandatory
			UINT n;
			hresult = lpIDispatch->GetTypeInfoCount( &n );
			strAdditional.LoadString( IDS_NUMBER );
			CString strResult;
			strResult.Format( _T ( "%d" ),n );
			strAdditional += strResult;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchAmbientsGetTypeInfoCount, strResult + ", " + strAdditional );
			

			// IDispatch::GetTypeInfo
			// This method is not mandatory
			LPTYPEINFO lpTypeInfo;
			hresult = lpIDispatch->GetTypeInfo( 0, LOCALE_SYSTEM_DEFAULT, &lpTypeInfo );
			strAdditional.LoadString( IDS_ITYPEINFOADDRESS );
			CString strAddress;
			strAddress.Format( _T ( "0x%08x" ),lpTypeInfo );
			strAdditional += strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchAmbientsGetTypeInfo, strResult + ", " + strAdditional );



			// IDispatch::GetIDsOfNames
			// This method is not mandatory
			OLECHAR FAR* szMember = (OLECHAR*)"UserMode"; // May not exist but so what!
			DISPID dispid;
			hresult = lpIDispatch->GetIDsOfNames( IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchAmbientsGetIDsOfNames, strResult );


			// IDispatch::Invoke
			// We call invoke to Get the four mandatory ambient properties in turn
			// DISPID_AMBIENT_LOCALEID
			// Lots of parameters!!			
			DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
			LCID lcid = 0;
			COleVariant varResult;
			EXCEPINFO excepinfo;
			unsigned int  uArgErr;
			hresult = lpIDispatch->Invoke( DISPID_AMBIENT_LOCALEID,
											IID_NULL,
											LOCALE_SYSTEM_DEFAULT,
											DISPATCH_PROPERTYGET,
											&dispparamsNoArgs,
											&varResult,
											&excepinfo,
											&uArgErr );
			strAdditional.Format( _T ( " 0x%08x" ), varResult.lVal );			
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IDispatchAmbientsInvokeLocaleID, strResult + ", " + strAdditional );



			// IDispatch::Invoke
			// DISPID_AMBIENT_USERMODE
			hresult = lpIDispatch->Invoke( DISPID_AMBIENT_USERMODE,
											IID_NULL,
											LOCALE_SYSTEM_DEFAULT,
											DISPATCH_PROPERTYGET,
											&dispparamsNoArgs,
											&varResult,
											&excepinfo,
											&uArgErr );
			strAdditional.Format( _T ( " 0x%08x" ), varResult.iVal );			
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IDispatchAmbientsInvokeUserMode, strResult + ", " + strAdditional );



			// IDispatch::Invoke
			// DISPID_AMBIENT_SUPPORTSMNEMONICS
			hresult = lpIDispatch->Invoke( DISPID_AMBIENT_SUPPORTSMNEMONICS,
											IID_NULL,
											LOCALE_SYSTEM_DEFAULT,
											DISPATCH_PROPERTYGET,
											&dispparamsNoArgs,
											&varResult,
											&excepinfo,
											&uArgErr );
			strAdditional.Format( _T ( " 0x%08x" ), varResult.iVal );			
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IDispatchAmbientsInvokeSupportsMnemonics, strResult + ", " + strAdditional );


			// IDispatch::Invoke
			// DISPID_AMBIENT_DISPLAYASDEFAULT
			hresult = lpIDispatch->Invoke( DISPID_AMBIENT_DISPLAYASDEFAULT,
											IID_NULL,
											LOCALE_SYSTEM_DEFAULT,
											DISPATCH_PROPERTYGET,
											&dispparamsNoArgs,
											&varResult,
											&excepinfo,
											&uArgErr );
			strAdditional.Format( _T ( " 0x%08x" ), varResult.iVal );			
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IDispatchAmbientsInvokeDisplayAsDefault, strResult + ", " + strAdditional );


			// Don't forget....
			lpIDispatch->Release();
		}
	}

}

//////////////////////////////////////////////////////
// VerifyIDispatchEvents - IDispatch verification for the control's events
//
void CVControlCtrl::VerifyIDispatchEvents( void )
{

	HRESULT hresult = 0;
	CString strAdditional;

	// Our control has a click event set up using classwizard
	// Let's get our IConnectionPointContainer
	// from that we can get our IConnectionPoint for our click event
	// from that we get the IDispatch that the container provides for our
	// click event.
	// We have to assume that the container provides a similar IDispatch
	// for all events that an object may have!
	// We actually take a short cut here using the dispatch functionality
	// that MFC and the CDK provide, but that doesn't matter as what we are
	// trying to get is the events IDispatch on the container side of the fence

	
	const CPtrArray* pConnections = m_xEventConnPt.GetConnections();
	ASSERT(pConnections != NULL);

	int nConnections = pConnections->GetSize();
	LPDISPATCH pDispatch;
	CString strResult;
	strResult.Format( _T ( "0x%02x" ),nConnections );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( TRUE, (hresult == S_OK), IDS_IDISPATCHEVENTS, strResult );

	for ( int i = 0; i < nConnections; i++ )
	{
		pDispatch = (LPDISPATCH)(pConnections->GetAt( i ));

		if ( pDispatch != NULL )
		{
			// Here we have the IDispatch for the event
			
			// IDispatch::GetTypeInfoCount
			UINT n;
			hresult = pDispatch->GetTypeInfoCount( &n );
			strAdditional.LoadString( IDS_NUMBER );
			strResult.Format( _T ( "%d" ),n );
			strAdditional += strResult;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchEventsGetTypeInfoCount, strResult + ", " + strAdditional );

			

			// IDispatch::GetTypeInfo
			LPTYPEINFO lpTypeInfo;
			hresult = pDispatch->GetTypeInfo( 0, LOCALE_SYSTEM_DEFAULT, &lpTypeInfo );
			strAdditional.LoadString( IDS_ITYPEINFOADDRESS );
			CString strAddress;
			strAddress.Format( _T ( "0x%08x" ),lpTypeInfo );
			strAdditional += strAddress;
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchEventsGetTypeInfo, strResult + ", " + strAdditional );


			// IDispatch::GetIDsOfNames
			OLECHAR FAR* szMember = (OLECHAR*)"UserMode"; // May not exist but so what!
			DISPID dispid;
			hresult = pDispatch->GetIDsOfNames( IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchEventsGetIDsOfNames, strResult );


			// IDispatch::Invoke
			// We call invoke the method the click event
			// DISPID_CLICK
			// Lots of parameters!!			
			DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
			VARIANT varResult;
			EXCEPINFO excepinfo;
			unsigned int uArgErr;
			hresult = pDispatch->Invoke( DISPID_CLICK,
												IID_NULL,
												LOCALE_SYSTEM_DEFAULT,
												DISPATCH_METHOD,
												&dispparamsNoArgs,
												&varResult,
												&excepinfo,
												&uArgErr );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IDispatchEventsInvoke, strResult );

		}
	}
	
}

//////////////////////////////////////////////////////
// VerifyIAdviseSink - IAdviseSink verification
//
void CVControlCtrl::VerifyIAdviseSink( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;

	// Do a QI for IAdviseSink. We assume the pointer to IUnknown we have been given is valid.
	LPADVISESINK lpIAdviseSink;
	hresult = lpIUnknown->QueryInterface( IID_IAdviseSink, (void**) &lpIAdviseSink );
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( FALSE, TRUE, IDS_IAdviseSinkQI, strResult );
	if ( hresult == S_OK )
	{
		if ( lpIAdviseSink != NULL )
	 	{

			// For IAdviseSink all the methods are notifications that return void
			// So there is no point in calling them as we cannot see whether
			// they worked. We always assume the methods are there to be called.
			// IAdviseSink::OnDataChange	// Advises that data has changed.
			// IAdviseSink::OnViewChange	// Advises that view of object has changed.
			// IAdviseSink::OnRename		// Advises that name of object has changed.
			// IAdviseSink::OnSave			// Advises that object has been saved to disk.
			// IAdviseSink::OnClose			// Advises that object has been closed.

			// Please release me let me go!
			lpIAdviseSink->Release();
		}
	}

}


//////////////////////////////////////////////////////
// VerifyISimpleFrameSite - ISimpleFrameSite verification
// This interface is not Mandatory
//
void CVControlCtrl::VerifyISimpleFrameSite( LPUNKNOWN lpIUnknown )
{
	ASSERT( lpIUnknown != NULL );

	HRESULT hresult;

	// First of all let's try and get a pointer to the ISimpleFrameSite 

	// Do a QI for ISimpleFrameSite. We assume the pointer to IUnknown we have been given is valid.
	LPSIMPLEFRAMESITE lpISimpleFrameSite;
	hresult = lpIUnknown->QueryInterface( IID_ISimpleFrameSite, (void**) &lpISimpleFrameSite );
	CString strResult;
	GetSCodeDescription( hresult, strResult );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( FALSE, (hresult == S_OK) || (hresult == E_NOINTERFACE), IDS_ISimpleFrameSiteQI, strResult );
	if ( hresult == S_OK )
	{
		if ( lpISimpleFrameSite != NULL )
		{


			// ISimpleFrameSite::PreMessageFilter
			DWORD dwCookie;
			LRESULT lResult;
			hresult = lpISimpleFrameSite->PreMessageFilter(	m_hWnd, WM_NULL, 0, 0, &lResult, &dwCookie);
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_ISimpleFrameSitePreMessageFilter, strResult );


			// ISimpleFrameSite::PostMessageFilter
			hresult = lpISimpleFrameSite->PostMessageFilter( m_hWnd, WM_NULL, 0, 0, &lResult, dwCookie);
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_ISimpleFrameSitePostMessageFilter, strResult );
	

			// Don't forget...
			lpISimpleFrameSite->Release();
		}
	}
}

//////////////////////////////////////////////////////
// VerifyIPropertyNotifySink - IPropertyNotifySink verification
// This interface is not Mandatory
//
void CVControlCtrl::VerifyIPropertyNotifySink( void )
{

	HRESULT hresult = 0;

	// Use the CDK provided connection for IPropertyNotifySink
	const CPtrArray* pConnections = m_xPropConnPt.GetConnections();
	ASSERT(pConnections != NULL);

	int nConnections = pConnections->GetSize();
	LPPROPERTYNOTIFYSINK pPropNotifySink;
	CString strResult;
	strResult.Format( _T ( "0x%02x" ),nConnections );
	CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( FALSE, TRUE, IDS_IPROPERTYNOTIFYSINK, strResult );

	for (int i = 0; i < nConnections; i++)
	{
		pPropNotifySink = (LPPROPERTYNOTIFYSINK)(pConnections->GetAt(i));
		if ( pPropNotifySink != NULL )
		{

			// IPropertyNotifySink::OnChanged
			// only returns a void so we won't bother calling it
			//void    OnChanged(DISPID dispid);

			
			// IPropertyNotifySink::OnRequestEdit
			hresult = pPropNotifySink->OnRequestEdit( DISPID_UNKNOWN );
			GetSCodeDescription( hresult, strResult );
			pInterfaceResult->LogMethodResult( TRUE, (hresult == S_OK), IDS_IPropertyNotifySinkOnRequestEdit, strResult );

		}
	}
}

//////////////////////////////////////////////////////
// VerifyExtendedControl - Extended control verification
// Support for extended control is not Mandatory
//
void CVControlCtrl::VerifyExtendedControl( void )
{

	// Get the IOleControlSite to get the extended interface
	if ( m_pControlSite != NULL )
	{
		// We just assume that our helpful MFC CDK gives us the correct
		// IOleControlSite interface

		HRESULT hresult;
		CString strAdditional;

		// GetExtendedControl
		LPDISPATCH lpIDispatch;
		hresult = m_pControlSite->GetExtendedControl( &lpIDispatch );
		CString strResult;
		GetSCodeDescription( hresult, strResult );
		CInterfaceVerificationResult* pInterfaceResult = LogInterfaceResult( FALSE, TRUE, IDS_EXTENDEDCONTROL, strResult );
		if ( hresult == S_OK )
		{
			if ( lpIDispatch != NULL )
			{

				// IDispatch::GetTypeInfoCount
				UINT n;
				hresult = lpIDispatch->GetTypeInfoCount( &n );
				strAdditional.LoadString( IDS_NUMBER );
				strResult.Format( _T ( "%d" ), n );
				strAdditional += strResult;
				GetSCodeDescription( hresult, strResult );
				pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchExtendedGetTypeInfoCount, strResult + ", " + strAdditional );
				

				// IDispatch::GetTypeInfo
				LPTYPEINFO lpTypeInfo;
				hresult = lpIDispatch->GetTypeInfo( 0, LOCALE_SYSTEM_DEFAULT, &lpTypeInfo );
				strAdditional.LoadString( IDS_ITYPEINFOADDRESS );
				CString strAddress;
				strAddress.Format( _T ( "0x%08x" ),lpTypeInfo );
				strAdditional += strAddress;
				GetSCodeDescription( hresult, strResult );
				pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchExtendedGetTypeInfo, strResult + ", " + strAdditional );


				// IDispatch::GetIDsOfNames
				OLECHAR FAR* szMember = (OLECHAR*)"UserMode"; // May not exist but so what!
				DISPID dispid;
				hresult = lpIDispatch->GetIDsOfNames( IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid );
				GetSCodeDescription( hresult, strResult );
				pInterfaceResult->LogMethodResult( FALSE, TRUE, IDS_IDispatchExtendedGetIDsOfNames, strResult );


				// IDispatch::Invoke
				// We call invoke the method the click event
				// DISPID_CLICK just for the hell of it as I can't think what else to do!
				// Lots of parameters!!			
				DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
				VARIANT varResult;
				EXCEPINFO excepinfo;
				unsigned int uArgErr;
				hresult = lpIDispatch->Invoke( DISPID_CLICK,
												IID_NULL,
												LOCALE_SYSTEM_DEFAULT,
												DISPATCH_METHOD,
												&dispparamsNoArgs,
												&varResult,
												&excepinfo,
												&uArgErr );
				GetSCodeDescription( hresult, strResult );
				pInterfaceResult->LogMethodResult( FALSE, (hresult != E_NOTIMPL), IDS_IDispatchExtendedInvoke, strResult );


				lpIDispatch->Release();
			}
		}
	}
}



CInterfaceVerificationResult* CVControlCtrl::LogInterfaceResult( BOOL bMandatory, BOOL bSuccess, UINT nDescriptionID, const CString& rstrResult)
{
	CInterfaceVerificationResult* pResult = NULL;
	try
	{
		pResult = new CInterfaceVerificationResult;
		CString strDescription;
		strDescription.LoadString( nDescriptionID );
		pResult->SetResult( bMandatory, bSuccess, strDescription, rstrResult );
		m_resultsInterfaceArray.Add(pResult);

	}
	catch ( CMemoryException e )
	{
		AfxMessageBox( IDS_NOTENOUGHMEMORY );
		pResult = NULL;
	}
	return pResult;
}

void CVControlCtrl::GetSCodeDescription( HRESULT hresult, CString& strLine ) 
{
	strLine.Format( _T ( "0x%08x" ),hresult );

	UINT nID = 0;
	switch( hresult )
	{
		case S_OK:
			nID = IDS_SOK;
			break;

		case S_FALSE:
			nID = IDS_SFALSE;
			break;

		case E_NOTIMPL:
			nID = IDS_ENOTIMPL;
			break;

		case E_FAIL:
			nID = IDS_EFAIL;
			break;

		case E_NOINTERFACE:
			nID = IDS_ENOINTERFACE;
			break;

		case E_UNEXPECTED:
			nID = IDS_EUNEXPECTED;
			break;

		case E_INVALIDARG:
			nID = IDS_EINVALIDARG;
			break;

		case DISP_E_UNKNOWNNAME:
			nID = IDS_DISPEUNKNOWNNAME;
			break;

		case DISP_E_MEMBERNOTFOUND:
			nID = IDS_DISPEMEMBERNOTFOUND;
			break;

		case INPLACE_E_NOTOOLSPACE:
			nID = IDS_INPLACEENOTOOLSPACE;
			break;

		default:
			nID = IDS_SCODEUNKNOWN;
			break;
	}

	CString strDescription;
	strDescription.LoadString(nID);
	strLine += "=" + strDescription;
}


/////////////////////////////////////////////////////////
//	CInterfaceVerificationResult class
//
CInterfaceVerificationResult::~CInterfaceVerificationResult()
{
	// delete the method result objects
	for( int i = 0; i <= m_resultMethodArray.GetUpperBound(); i++ )
	{
		delete m_resultMethodArray[i];
	}
	m_resultMethodArray.RemoveAll();
}


void CInterfaceVerificationResult::LogMethodResult( BOOL bMandatory, BOOL bSuccess, UINT nDescriptionID, const CString& rstrResult)
{
	try
	{
		CVerificationResult* pResult = new CVerificationResult;
		CString strDescription;
		strDescription.LoadString( nDescriptionID );
		pResult->SetResult( bMandatory, bSuccess, strDescription, rstrResult );
		m_resultMethodArray.Add(pResult);
	}
	catch ( CMemoryException e )
	{
		AfxMessageBox( IDS_NOTENOUGHMEMORY );
	}
}
