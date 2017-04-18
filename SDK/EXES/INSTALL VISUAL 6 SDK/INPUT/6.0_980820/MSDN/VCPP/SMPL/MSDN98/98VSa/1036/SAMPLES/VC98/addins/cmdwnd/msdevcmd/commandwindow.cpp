// CommandWindow.cpp : Implementation of CCommandWindow
#include "stdafx.h"
#include "Msdevcmd.h"
#include "CommandWindow.h"

#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

extern CMsdevcmdApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CCommandWindow

STDMETHODIMP CCommandWindow::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICommandWindow,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



STDMETHODIMP CCommandWindow::DoFireClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Fire_OnClose();

	return S_OK;
}

HRESULT CCommandWindow::FindApp()
{
	HRESULT hr;
	CLSID clsid;
	CComPtr<IUnknown> pUnk;

	hr = CLSIDFromProgID(OLESTR("MSDEV.APPLICATION"), &clsid);
	if (SUCCEEDED(hr)) 
	{
		hr = GetActiveObject(clsid, NULL,  &pUnk  );
		if (SUCCEEDED(hr))
		{
			hr = pUnk->QueryInterface(IID_IApplication, (LPVOID *)&m_spApplication);
		}
		else
		{
			hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IApplication, (LPVOID *)&m_spApplication);
			m_spApplication->put_Visible(VARIANT_TRUE);
		}
	}
	return(hr);
}

STDMETHODIMP CCommandWindow::Open(IDispatch *pDispApplication)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HRESULT hr = S_OK;
	CComQIPtr<IApplication, &IID_IApplication> pApp;
	pApp = pDispApplication;
	m_spApplication = pApp;
	theApp.SetCommandWindow(this);

	return S_OK;
}

STDMETHODIMP CCommandWindow::DoClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	HRESULT hr = S_OK;
	m_spApplication.Release();
	m_spApplication = NULL;


	return S_OK;
}

IApplication * CCommandWindow::GetApp()
{
	if (m_spApplication == NULL)
	{
		FindApp();
	}
	return(m_spApplication);
}

STDMETHODIMP CCommandWindow::SetFocus()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd *pWndMain;
	HWND hwnd;

	pWndMain = theApp.GetMainWnd();
	hwnd = pWndMain->GetSafeHwnd();
	_ASSERTE(hwnd);
	if (hwnd)
	{
		SetForegroundWindow(hwnd);
	}
	return S_OK;
}
