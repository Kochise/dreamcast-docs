// CmdWnd.cpp : Implementation of CCmdWnd
#include "stdafx.h"
#include "Cmdstub.h"
#include "CmdWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CCmdWnd
CCmdWnd::CCmdWnd()
{
	m_dwCookie = NULL;
}

CCmdWnd::~CCmdWnd()
{
	if (m_pCommandWindow)
	{
		m_pCommandWindow.Release();
		m_pCommandWindow = NULL;
	}

}


HRESULT CCmdWnd::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	m_spApplication = pApp;
	m_dwAddInID = dwAddInID;

	// Connect up to application event sink
	AtlAdvise(pApp, GetUnknown(), IID_IApplicationEvents, &m_dwAppEvents);

	// Connect up to debugger event sink
	CComPtr<IDispatch> pDebugger;
	hr = m_spApplication->get_Debugger(&pDebugger);
	if (SUCCEEDED(hr))
		AtlAdvise(pDebugger, GetUnknown(), IID_IDebuggerEvents, &m_dwDbgEvents);

	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<ICmdWnd*>(this), IDB_TOOLBAR_MEDIUM_CMDWND, IDB_TOOLBAR_LARGE_CMDWND, dwAddInID);
	LPCTSTR szCommand = _T("Command Window");
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		hr = pApp->AddCommand(CComBSTR(_T("Command Window\nCommand Window\nCommand Window\nCommand Window")),CComBSTR(_T("DoCmdWnd")), 0, dwAddInID, &bRet);
	}

	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("Command Window")), dwAddInID);
		}
	}

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}

HRESULT CCmdWnd::OnDisconnection(VARIANT_BOOL bLastTime)
{
	AtlUnadvise(m_spApplication, IID_IApplicationEvents, m_dwAppEvents);
	AtlUnadvise(m_spApplication, IID_IDebuggerEvents, m_dwDbgEvents);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Application events
HRESULT CCmdWnd::BeforeBuildStart()
{
	return S_OK;
}
HRESULT CCmdWnd::BuildFinish(long nNumErrors, long nNumWarnings)
{
	return S_OK;
}
HRESULT CCmdWnd::BeforeApplicationShutDown()
{
	if (m_pCommandWindow)
	{
		m_pCommandWindow->DoClose();
	}
	return S_OK;
}
HRESULT CCmdWnd::DocumentOpen(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CCmdWnd::BeforeDocumentClose(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CCmdWnd::DocumentSave(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CCmdWnd::NewDocument(IDispatch* theDocument)
{
	return S_OK;
}
HRESULT CCmdWnd::WindowActivate(IDispatch* theWindow)
{
	return S_OK;
}
HRESULT CCmdWnd::WindowDeactivate(IDispatch* theWindow)
{
	return S_OK;
}
HRESULT CCmdWnd::WorkspaceOpen()
{
	return S_OK;
}
HRESULT CCmdWnd::WorkspaceClose()
{
	return S_OK;
}
HRESULT CCmdWnd::NewWorkspace()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Debugger event
HRESULT CCmdWnd::BreakpointHit(IDispatch* pBreakpoint)
{
	return S_OK;
}

HRESULT CCmdWnd::DoCmdWnd()
{
	HRESULT hr = E_FAIL;
	if (m_pCommandWindow == NULL)
	{
		hr = CoCreateInstance(CLSID_CommandWindow, NULL, CLSCTX_ALL, IID_ICommandWindow, (LPVOID *)&m_pCommandWindow);
		if (SUCCEEDED(hr) && m_pCommandWindow != NULL) // if m_pCommandWindow is null, proxy problem or interface. Try rebuild ALL
		{
			hr = m_pCommandWindow->Open(m_spApplication);
			_ASSERTE(SUCCEEDED(hr));
			if (SUCCEEDED(hr))
			{
				CComQIPtr<_ICommandWindowEvents, &DIID__ICommandWindowEvents> pEvents;
				CComQIPtr<IUnknown, &IID_IUnknown> pUnkThis;
				CComQIPtr<IUnknown, &IID_IUnknown> pUnkCmdWnd = m_pCommandWindow;
				pUnkThis = (ICmdWnd *)this;
				pEvents = pUnkThis;
				_ASSERTE(pEvents);
				hr = AtlAdvise(pUnkCmdWnd, GetUnknown(), DIID__ICommandWindowEvents,  &m_dwCookie);
			}

		}
		if (FAILED(hr))
		{
			m_pCommandWindow.Release(); // don't hold onto this if we can't get told when it closes.
			m_pCommandWindow = NULL;
		}
	}
	else
	{
			m_pCommandWindow->SetFocus();
	}
	return S_OK;
}


HRESULT _stdcall CCmdWnd::OnClose()
{ // called when IShinc is closing down.
	HRESULT hr = S_OK;

	m_pCommandWindow.Release();
	m_pCommandWindow = NULL;
	return(hr);
}


