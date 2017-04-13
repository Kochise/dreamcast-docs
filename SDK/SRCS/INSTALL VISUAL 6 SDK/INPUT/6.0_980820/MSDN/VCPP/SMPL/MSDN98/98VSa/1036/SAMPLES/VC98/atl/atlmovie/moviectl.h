// MovieCtl.h : Declaration of the CMovieCtl
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __MOVIECTL_H_
#define __MOVIECTL_H_

#include "resource.h"       // main symbols

// This is the ActiveMovie DLL. You might need to specify an explicit path
// here if the DLL isn't intalled along the PATH or INCLUDE directories on
// your machine.
#import <quartz.dll> no_namespace rename("GUID","_GUID")

/////////////////////////////////////////////////////////////////////////////
// CMovieCtl
class ATL_NO_VTABLE CMovieCtl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMovieCtl, &CLSID_MovieCtl>,
	public IDispatchImpl<IMovieCtl, &IID_IMovieCtl, &LIBID_ATLMOVIELib>,
	public CComControl<CMovieCtl>,
	public IPersistStreamInitImpl<CMovieCtl>,
	public IPersistStorageImpl<CMovieCtl>,
	public IOleControlImpl<CMovieCtl>,
	public IOleObjectImpl<CMovieCtl>,
	public IOleInPlaceActiveObjectImpl<CMovieCtl>,
	public IViewObjectExImpl<CMovieCtl>,
	public IOleInPlaceObjectWindowlessImpl<CMovieCtl>,
	public IProvideClassInfo2Impl<&CLSID_MovieCtl, NULL, &LIBID_ATLMOVIELib>,
	public IObjectSafetyImpl<CMovieCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CMovieCtl()
	{

	}

DECLARE_REGISTRY_RESOURCEID(IDR_MOVIECTL)

BEGIN_COM_MAP(CMovieCtl)
	COM_INTERFACE_ENTRY(IMovieCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CMovieCtl)
//  PROP_PAGE(CLSID_StockColorPage)
//  PROP_ENTRY("Filename", 2, CLSID_NULL)
END_PROPERTY_MAP()

BEGIN_MSG_MAP(CMovieCtl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()

// IMovieCtl
public:
	STDMETHOD(Stop)();
	STDMETHOD(Reset)();
	STDMETHOD(Pause)();
	void FinalRelease()
	{
		if (m_spVideoWindow)
		{
			// Hide the video window before we reset the owner
			m_spVideoWindow->Visible = FALSE;
			m_spVideoWindow->Owner = NULL;
		}
	}
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(Play)();
	HRESULT CreateFilterGraph(LPCOLESTR strFile);
	HRESULT OnDraw(ATL_DRAWINFO& di);

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		HRESULT hr = IOleInPlaceObjectWindowlessImpl<CMovieCtl>::SetObjectRects(prcPos, prcClip);

		// Resize the video window if we have one
		if (m_spVideoWindow)
		{
			RECT rc = m_rcPos;
			if (!m_bWndLess)
				OffsetRect(&rc, -rc.left, -rc.top);
			m_spVideoWindow->SetWindowPosition(rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
		}

		return hr;
	}

protected:
	IMediaControlPtr    m_spMediaControl;
	IVideoWindowPtr     m_spVideoWindow;
};

#endif //__MOVIECTL_H_
