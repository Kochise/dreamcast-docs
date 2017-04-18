// OpenGLObj.h : Declaration of the COpenGLObj
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
#include <atlctl.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

/////////////////////////////////////////////////////////////////////////////
// OpenGL

class COpenGLObj :
	public CComObjectRoot,
	public CComCoClass<COpenGLObj,&CLSID_COpenGLObj>,
	public CComControl<COpenGLObj>,
	public IDispatchImpl<IOpenGLObj, &IID_IOpenGLObj, &LIBID_OPENGLLib>,
	public IPersistStreamInitImpl<COpenGLObj>,
	public IPersistStorageImpl<COpenGLObj>,
	public IOleControlImpl<COpenGLObj>,
	public IOleObjectImpl<COpenGLObj>,
	public IOleInPlaceActiveObjectImpl<COpenGLObj>,
	public IOleInPlaceObjectWindowlessImpl<COpenGLObj>,
	public IViewObjectExImpl<COpenGLObj>,
	public IObjectSafetyImpl<COpenGLObj, INTERFACESAFE_FOR_UNTRUSTED_CALLER>
{
public:
	COpenGLObj()
	{
		m_bActive = FALSE;
		m_bMouseCaptured = FALSE;
		m_bstrCaption = _T("ATL 3.0");
		m_bWindowOnly = TRUE;
		m_wAngleY = 10.0f;
		m_wAngleX = 1.0f;
		m_wAngleZ = 5.0f;
		m_pPal = NULL;
		m_hPal = NULL;
		m_hrc = NULL;
		joyposX = 0x3000;
		joyposY = 0x4000;
		joyposZ = 0x5000;
	}
	~COpenGLObj()
	{
		if (m_pPal)
		{
			delete[] m_pPal;
			m_pPal = NULL;
		}
		if (m_hPal)
			DeleteObject(m_hPal);
	}


BEGIN_MSG_MAP(COpenGLObj)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
	MESSAGE_HANDLER(MM_JOY1MOVE, OnJoyMove)
	MESSAGE_HANDLER(MM_JOY1ZMOVE, OnJoyZMove)
END_MSG_MAP()

BEGIN_COM_MAP(COpenGLObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOpenGLObj)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(COpenGLObj)
END_CONNECTION_POINT_MAP()

BEGIN_PROPERTY_MAP(COpenGLObj)
END_PROPERTY_MAP()

//DECLARE_NOT_AGGREGATABLE(COpenGLObj)
DECLARE_GET_CONTROLLING_UNKNOWN()
//DECLARE_CONTROL_INFO(CLSID_COpenGLObj)
DECLARE_REGISTRY_RESOURCEID(IDR_OpenGLObj)

	float m_fRadius;
	BOOL m_bActive;
	BOOL m_bMouseCaptured;
	int m_xPos;
	int m_yPos;
	CComBSTR m_bstrCaption;
	GLfloat  m_wAngleY;
	GLfloat  m_wAngleX;
	GLfloat  m_wAngleZ;
	HGLRC m_hrc;
	HPALETTE m_hPal;
	LOGPALETTE *m_pPal;
	WORD joyposX;
	WORD joyposY;
	WORD joyposZ;

// IOpenGLObj
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	BOOL bSetupPixelFormat(HDC hdc);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::wglMakeCurrent(NULL,  NULL);
		if (m_hrc)
		{
			::wglDeleteContext(m_hrc);
			m_hrc = NULL;
		}
		HDC hdc = GetDC();
		RECT rc;
		GetClientRect(&rc);
		CreateContext(hdc, rc);
		return 0;
	}
	LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		FireViewChange();
		return 1;
	}
	LRESULT OnJoyMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		joyposX = LOWORD(lParam);
		joyposY = HIWORD(lParam);
		return 0;
	}
	LRESULT OnJoyZMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		joyposZ = LOWORD(lParam);
		return 0;
	}

	STDMETHODIMP put_Caption(BSTR pCaption)
	{
		USES_CONVERSION;
		ATLTRACE(_T("IOpenGL::put_Caption\n"));
		m_bstrCaption = pCaption;
		return S_OK;
	}
	STDMETHODIMP get_Caption(BSTR* ppCaption)
	{
		ATLTRACE(_T("IOpenGL::get_Caption\n"));
		*ppCaption = m_bstrCaption.Copy();
		return S_OK;
	}

	STDMETHOD(GetColorSet)(DWORD dwDrawAspect,LONG lindex, void* pvAspect, DVTARGETDEVICE* ptd, HDC hicTargetDev, LOGPALETTE** ppColorSet)
	{
		ATLTRACE(_T("GetColorSet\n"));
		if (ppColorSet == NULL)
			return E_POINTER;
		HRESULT hr = S_FALSE;
		*ppColorSet = NULL;
		if (m_pPal != NULL)
		{
			int nSize = sizeof(LOGPALETTE) + m_pPal->palNumEntries * sizeof(PALETTEENTRY);
			*ppColorSet = (PLOGPALETTE) CoTaskMemAlloc(nSize);
			if (*ppColorSet == NULL)
				hr = E_OUTOFMEMORY;
			else
			{
				memcpy(*ppColorSet, m_pPal, nSize);
				hr = S_OK;
			}
		}
		return hr;
	}

	void CreateContext(HDC hdc, RECT& rc);
	void CreateRGBPalette(HDC hdc);
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
};
