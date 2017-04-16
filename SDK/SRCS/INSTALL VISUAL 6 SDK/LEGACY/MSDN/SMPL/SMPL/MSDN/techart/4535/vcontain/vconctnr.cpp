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
//	Implementation of CVControlCtnr which overrides the IOleInPlaceFrame interface through 
//	XVOleInPlaceFrame.  This allows us to implement SetActiveObject to save the 
//	IOleInPlaceActiveObject pointer passed in to be used to validate all methods on that
//	interface.  This is since we should not QI for it directly.


#include "stdafx.h"
#include "vcontain.h"
#include "vconctnr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Global variable to hold ptr to IOleInPlaceActiveObject that is passed into
//the XVOleInPlaceFrame::SetActiveObject member function called by the control 
//to establish a direct communication link between itself and the document and frame windows.

LPOLEINPLACEACTIVEOBJECT g_lpIOleInPlaceActiveObject;

CVControlCtnr::CVControlCtnr( CWnd* pWnd ) : COleControlContainer ( pWnd )
{
}

CVControlCtnr::~CVControlCtnr()
{
}


BEGIN_MESSAGE_MAP(CVControlCtnr, COleControlContainer)
	//{{AFX_MSG_MAP(CVControlCtnr)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(CVControlCtnr, CCmdTarget)
    INTERFACE_PART(CVControlCtnr, IID_IOleInPlaceFrame, VOleInPlaceFrame)
    INTERFACE_PART(CVControlCtnr, IID_IOleContainer, VOleContainer)
END_INTERFACE_MAP()


ULONG  EXPORT CVControlCtnr::XVOleInPlaceFrame::AddRef()
{
    METHOD_PROLOGUE ( CVControlCtnr, VOleInPlaceFrame )
    return pThis->ExternalAddRef ();
}

ULONG  EXPORT CVControlCtnr::XVOleInPlaceFrame::Release ()
{
    METHOD_PROLOGUE( CVControlCtnr, VOleInPlaceFrame )
    return pThis->ExternalRelease ();
}

HRESULT  EXPORT CVControlCtnr::XVOleInPlaceFrame::QueryInterface(REFIID iid, 
															void ** ppvObj)
{
    METHOD_PROLOGUE ( CVControlCtnr, VOleInPlaceFrame )
    return ( HRESULT ) pThis->ExternalQueryInterface ( &iid, ppvObj );
}


STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::GetWindow(HWND * phWnd)
{
	METHOD_PROLOGUE_EX_(CVControlCtnr, VOleInPlaceFrame)

	*phWnd = pThis->m_pWnd->m_hWnd;
	return S_OK;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::ContextSensitiveHelp ( BOOL )
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::GetBorder ( LPRECT )
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::RequestBorderSpace 
												( LPCBORDERWIDTHS )
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::SetBorderSpace 
												( LPCBORDERWIDTHS )
{
	return ( HRESULT ) E_NOTIMPL;
}


//***************************************************************************
//METHOD NAME:			
//	CVControlCtnr::XVOleInPlaceFrame::SetActiveObject
//PURPOSE:	
//	IOleInPlaceUIWindow::SetActiveObject is called by the object to establish
//  a direct communication link between itself and the document and frame 
//	windows.  When deactivating, the object calls IOleInPlaceUIWindow::
//	SetActiveObject, passing NULL for the pActiveObject and pszObjName 
//	parameters.  An object must call IOleInPlaceUIWindow::SetActiveObject
//	before calling IOleInPlaceFrame::SetMenu to give the container the pointer
//	to the active bject. OTE:  The MFC COleControlSite class contains a member
//	of LPIOLEINPLACEACTIVEOBJECT named _pActiveObject whose value is set by 
//	QI for IOleInPlaceActiveObject at control creation ime.  It is better to
//	obtain this value from the SetActiveObject call in case we have a ontrol
//	that is embedded within another control.  As a reference, please see 
//	KBase article #Q98678  on the Microsoft TechNet CD.	 
//INPUT PARAMETER(s):	
//	LPOLEINPLACEACTIVEOBJECT lpOleInPlaceActiveObject - 
//											Points to active in-place object
//  LPCOLESTR  -  Points to name describing the object; ingnored here.
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	HRESULT of call; here always returns S_OK.
//***************************************************************************
STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::SetActiveObject
			( LPOLEINPLACEACTIVEOBJECT lpOleInPlaceActiveObject, LPCOLESTR)
{
	//Save the pointer to lpOleInPlaceActiveObject passed in here.  This is 
	//the correct way to get a valid IOleInPlaceActiveObject pointer as 
	//opposed to from QueryInterface.
	if ( lpOleInPlaceActiveObject == NULL )
	{
		//Object is deactivating
		g_lpIOleInPlaceActiveObject = NULL;
	}
	else
	{
		//Object is becoming the active object.
		g_lpIOleInPlaceActiveObject = lpOleInPlaceActiveObject;
	}

	return S_OK;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::InsertMenus(HMENU, 
												LPOLEMENUGROUPWIDTHS)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::SetMenu(HMENU, HOLEMENU, HWND)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::RemoveMenus(HMENU)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::SetStatusText(LPCOLESTR)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::EnableModeless(BOOL)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleInPlaceFrame::TranslateAccelerator(LPMSG, 
																	WORD)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleContainer::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CVControlCtnr, VOleContainer)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(ULONG) CVControlCtnr::XVOleContainer::Release()
{
	METHOD_PROLOGUE_EX_(CVControlCtnr, VOleContainer)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP_(ULONG) CVControlCtnr::XVOleContainer::AddRef()
{
	METHOD_PROLOGUE_EX_(CVControlCtnr, VOleContainer)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP CVControlCtnr::XVOleContainer::ParseDisplayName(LPBINDCTX,
	LPOLESTR, ULONG*, LPMONIKER*)
{
	return ( HRESULT ) E_NOTIMPL;
}

STDMETHODIMP CVControlCtnr::XVOleContainer::EnumObjects(DWORD, LPENUMUNKNOWN*)
{
	//**** NORMAL CONTAINERS MUST IMPLEMENT THIS, BUT SINCE WE ONLY HOST ONE
	//CONTROL AT ANY TIME, THERE IS REALLY NOT A NEED TO IMPLEMENT THIS.  
	//ADDITIONALLY, THIS IS A PARTIALLY FUNCTIONAL CONTAINER SOLELY DESIGNED 
	//FOR THE PURPOSE OF VERIFYING INTERFACES, SO FOR SIMPLICITY SAKE, WE 
	//RETURN S_OK.  NORMALLY, YOU WOULD RETURN E_NOTIMPL IF NO IMPLEMENTATION.
	return ( HRESULT ) S_OK;
}

STDMETHODIMP CVControlCtnr::XVOleContainer::LockContainer(BOOL)
{
	return ( HRESULT ) E_NOTIMPL;
}


