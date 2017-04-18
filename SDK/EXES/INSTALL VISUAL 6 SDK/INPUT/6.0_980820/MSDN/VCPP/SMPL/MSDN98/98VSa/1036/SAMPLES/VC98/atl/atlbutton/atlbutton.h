// AtlButton.h : Declaration of the CAtlButton
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

#include "resource.h"       // main symbols
#include "dibapi.h"
#include "cpatlbutn.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// CTimer
template <class Derived, class T, const IID* piid>
class CTimer
{
public:

	CTimer()
	{
		m_bTimerOn = FALSE;
	}

	HRESULT TimerOn(DWORD dwTimerInterval)
	{
		Derived* pDerived = ((Derived*)this);

		m_dwTimerInterval = dwTimerInterval;
		if (m_bTimerOn) // already on, just change interval
			return S_OK;

		m_bTimerOn = TRUE;
		m_dwTimerInterval = dwTimerInterval;
		m_pStream = NULL;

		HRESULT hRes;

		hRes = CoMarshalInterThreadInterfaceInStream(*piid, (T*)pDerived, &m_pStream);

		// Create thread and pass the thread proc the this ptr
		m_hThread = CreateThread(NULL, 0, &_Apartment, (void*)this, 0, &m_dwThreadID);

		return S_OK;
	}

	void TimerOff()
	{
		if (m_bTimerOn)
		{
			m_bTimerOn = FALSE;
			AtlWaitWithMessageLoop(m_hThread);
		}
	}


// Implementation
private:
	static DWORD WINAPI _Apartment(void* pv)
	{
		CTimer<Derived, T, piid>* pThis = (CTimer<Derived, T, piid>*) pv;
		pThis->Apartment();
		return 0;
	}

	DWORD Apartment()
	{
		CoInitialize(NULL);
		HRESULT hRes;

		m_spT.Release();

		if (m_pStream)
			hRes = CoGetInterfaceAndReleaseStream(m_pStream, *piid, (void**)&m_spT);

		while(m_bTimerOn)
		{
			Sleep(m_dwTimerInterval);
			if (!m_bTimerOn)
				break;

			m_spT->_OnTimer();
		}
		m_spT.Release();

		CoUninitialize();
		return 0;
	}

// Attributes
public:
	DWORD m_dwTimerInterval;

// Implementation
private:
	HANDLE m_hThread;
	DWORD m_dwThreadID;
	LPSTREAM m_pStream;
	CComPtr<T> m_spT;
	BOOL m_bTimerOn;
};


/////////////////////////////////////////////////////////////////////////////
// CAtlButton
class CAtlButton :
	public CComObjectRoot,
	public CTimer<CAtlButton, IAtlButton, &IID_IAtlButton>,
	public CComCoClass<CAtlButton,&CLSID_CAtlButton>,
	public CComControl<CAtlButton>,
	public IDispatchImpl<IAtlButton, &IID_IAtlButton, &LIBID_ATLBUTNLib>,
	public IPersistStreamInitImpl<CAtlButton>,
	public IOleControlImpl<CAtlButton>,
	public IOleObjectImpl<CAtlButton>,
	public IOleInPlaceActiveObjectImpl<CAtlButton>,
	public IViewObjectExImpl<CAtlButton>,
	public IOleInPlaceObjectWindowlessImpl<CAtlButton>,
	public IProvideClassInfo2Impl<&CLSID_CAtlButton, &DIID__ATLButton, &LIBID_ATLBUTNLib>,
	public IPersistPropertyBagImpl<CAtlButton>,
	public IConnectionPointContainerImpl<CAtlButton>,
	public CProxy_ATLButton<CAtlButton>,
	public IObjectSafetyImpl<CAtlButton, INTERFACESAFE_FOR_UNTRUSTED_CALLER>
{
public:
	CAtlButton()
	{
		m_nEntry = 0;
		m_hDIB[0] = NULL;
		m_hDIB[1] = NULL;
		m_hDIB[2] = NULL;
		m_hPal[0] = NULL;
		m_hPal[1] = NULL;
		m_hPal[2] = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AtlButton)


BEGIN_COM_MAP(CAtlButton)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAtlButton)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IPersist, IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CAtlButton)
	PROP_ENTRY("Static_Image", 0, CLSID_NULL)
	PROP_ENTRY("Hover_Image", 1, CLSID_NULL)
	PROP_ENTRY("Push_Image", 2, CLSID_NULL)
END_PROPERTY_MAP()

BEGIN_CONNECTION_POINT_MAP(CAtlButton)
	CONNECTION_POINT_ENTRY(DIID__ATLButton)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CAtlButton)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnErase)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnButtonUp)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
END_MSG_MAP()

	LRESULT OnErase(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnButtonDown(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nEntry = 2;
		FireViewChange();
		OnClick();
		return 0;
	}
	LRESULT OnButtonUp(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nEntry = 1;
		FireViewChange();
		OnClick();
		return 0;
	}
	LRESULT OnMouseMove(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_nEntry == 0)
		{
			m_nEntry = 1;
			FireViewChange();
		}
		return 0;
	}

// IAtlButton
public:
	CComBSTR m_bstrFilename[3];
	RECT m_rcDIB[3];
	HDIB m_hDIB[3];
	HPALETTE m_hPal[3];
	int m_nEntry;

	void PutImage(BSTR strFilename, int nEntry)
	{
		USES_CONVERSION;
		m_bstrFilename[nEntry] = strFilename;
		if (m_hDIB[nEntry])
			GlobalFree(m_hDIB[nEntry]);
		if (m_hPal[nEntry])
			GlobalFree(m_hPal[nEntry]);
		m_hDIB[nEntry] = NULL;
		m_hPal[nEntry] = NULL;
		m_hDIB[nEntry] = ReadDIBFile(OLE2T(strFilename));
		if (m_hDIB[nEntry])
		{
			CreateDIBPalette(m_hDIB[nEntry], &m_hPal[nEntry]);
			LPSTR pDIB = (LPSTR)GlobalLock(m_hDIB[nEntry]);
			m_rcDIB[nEntry].left = 0;
			m_rcDIB[nEntry].top = 0;
			m_rcDIB[nEntry].right = DIBWidth(pDIB);
			m_rcDIB[nEntry].bottom = DIBHeight(pDIB);
			GlobalUnlock((HGLOBAL)m_hDIB[nEntry]);
		}
	}
	STDMETHOD(put_ImageStatic)(BSTR strFilename)
	{
		PutImage(strFilename, 0);
		return S_OK;
	}
	STDMETHOD(get_ImageStatic)(BSTR* pstrFilename)
	{
		*pstrFilename = m_bstrFilename[0].Copy();
		return S_OK;
	}
	STDMETHOD(put_ImageHover)(BSTR strFilename)
	{
		PutImage(strFilename, 1);
		return S_OK;
	}
	STDMETHOD(get_ImageHover)(BSTR* pstrFilename)
	{
		*pstrFilename = m_bstrFilename[1].Copy();
		return S_OK;
	}
	STDMETHOD(put_ImagePush)(BSTR strFilename)
	{
		PutImage(strFilename, 2);
		return S_OK;
	}
	STDMETHOD(get_ImagePush)(BSTR* pstrFilename)
	{
		*pstrFilename = m_bstrFilename[2].Copy();
		return S_OK;
	}
	STDMETHOD(_OnTimer)()
	{
		POINT pos;
		GetCursorPos(&pos);
		if (m_bInPlaceActive)
		{
			HWND hwnd;
			m_spInPlaceSite->GetWindow(&hwnd);
			::ScreenToClient(hwnd, &pos);

			if (!PtInRect(&m_rcPos, pos))
			{
				if (m_nEntry > 0)
				{
					m_nEntry = 0;
					FireViewChange();
				}
			}
		}

		return S_OK;
	}
	HRESULT InPlaceActivate(LONG iVerb, const RECT* prcPosRect = NULL)
	{
		HRESULT hr;

		hr = CComControl<CAtlButton>::InPlaceActivate(iVerb, prcPosRect);
		TimerOn(250);
		return hr;
	}
	STDMETHOD(InPlaceDeactivate)(void)
	{
		TimerOff();
		return IOleInPlaceObjectWindowlessImpl<CAtlButton>::InPlaceDeactivate();
	}

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		USES_CONVERSION;

		if (m_hDIB[m_nEntry])
		{
			HPALETTE hPal = SelectPalette(di.hdcDraw, m_hPal[m_nEntry], TRUE);
			RealizePalette(di.hdcDraw);
			PaintDIB(di.hdcDraw, (LPRECT) di.prcBounds, m_hDIB[m_nEntry], &m_rcDIB[m_nEntry], m_hPal[m_nEntry]);
			SelectPalette(di.hdcDraw, hPal, TRUE);
		}
		return 0;
	}

	STDMETHOD(QueryHitPoint)(DWORD dwAspect, LPCRECT pRectBounds, POINT ptlLoc, LONG /* lCloseHint */, DWORD *pHitResult)
	{
		if (dwAspect == DVASPECT_CONTENT)
		{
			*pHitResult = PtInRect(pRectBounds, ptlLoc) ? HITRESULT_HIT : HITRESULT_OUTSIDE;
			if (m_nEntry == 0)
			{
				m_nEntry = 1;
				FireViewChange();
			}
			return S_OK;
		}
		ATLTRACE(_T("Wrong DVASPECT\n"));
		return E_FAIL;
	}
};
