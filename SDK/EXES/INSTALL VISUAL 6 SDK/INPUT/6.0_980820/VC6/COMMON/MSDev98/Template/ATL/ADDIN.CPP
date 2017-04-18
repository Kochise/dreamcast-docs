[!if=(FileExists, "FALSE")]
// [!CPPName] : Implementation of [!ClassName]

#include "stdafx.h"
#include "[!ProjectName].h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]
[!crlf]

/////////////////////////////////////////////////////////////////////////////
// [!ClassName]
[!crlf]

HRESULT [!ClassName]::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr = S_OK;
	m_spApplication = pApp;
	m_dwAddInID = dwAddInID;

[!if=(ApplicationEvents, "TRUE")]
[!crlf]
	// Connect up to application event sink
	AtlAdvise(pApp, GetUnknown(), IID_IApplicationEvents, &m_dwAppEvents);
[!endif]
[!if=(DebuggerEvents, "TRUE")]
[!crlf]
	// Connect up to debugger event sink
	CComPtr<IDispatch> pDebugger;
	hr = m_spApplication->get_Debugger(&pDebugger);
	if (SUCCEEDED(hr))
		AtlAdvise(pDebugger, GetUnknown(), IID_IDebuggerEvents, &m_dwDbgEvents);
[!endif]

[!crlf]
[!if=(Toolbar, "TRUE")]
	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<[!InterfaceName]*>(this), IDB_TOOLBAR_MEDIUM_[!UpperShortName], IDB_TOOLBAR_LARGE_[!UpperShortName], dwAddInID);
[!else]
	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		static_cast<[!InterfaceName]*>(this), -1, -1, dwAddInID);
[!crlf]
[!endif]

[!if=(Toolbar, "TRUE")]
[!if!=(CommandName, "")]
	LPCTSTR szCommand = _T("[!CommandName]");
[!else]
	LPCTSTR szCommand = _T("SampleCommand");
[!endif]
	VARIANT_BOOL bRet;
	if (SUCCEEDED(hr))
	{
		hr = pApp->AddCommand(CComBSTR([!if!=(CommandName, "")]_T("[!CommandName][!else]_T("SampleCommand[!endif]\n[!if!=(ToolbarButton, "")][!ToolbarButton][!else]Sample toolbar button text[!endif]\n[!if!=(StatusBar, "")][!StatusBar][!else]Sample status bar text[!endif]\n[!if!=(ToolTips, "")][!ToolTips][!else]Sample tool tips[!endif]")),CComBSTR([!if!=(CommandName, "")]_T("[!MethodName]")[!else]_T("Sample Method")[!endif]), 0, dwAddInID, &bRet);
	}
[!crlf]
	// Add toolbar buttons only if this is the first time the add-in
	// is being loaded.  Toolbar buttons are automatically remembered
	// by Developer Studio from session to session, so we should only
	// add the toolbar buttons once.
	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR([!if!=(CommandName, "")]_T("[!CommandName]")[!else]_T("SampleCommand")[!endif]), dwAddInID);
		}
	}
[!crlf]
[!endif]

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}
[!crlf]


HRESULT [!ClassName]::OnDisconnection(VARIANT_BOOL bLastTime)
{
[!if=(ApplicationEvents, "TRUE")]
	AtlUnadvise(m_spApplication, IID_IApplicationEvents, m_dwAppEvents);
[!endif]
[!if=(DebuggerEvents, "TRUE")]
	AtlUnadvise(m_spApplication, IID_IDebuggerEvents, m_dwDbgEvents);
[!endif]
	return S_OK;
}
[!crlf]


[!if=(ApplicationEvents, "TRUE")]
/////////////////////////////////////////////////////////////////////////////
// Application events

HRESULT [!ClassName]::BeforeBuildStart()
{
	return S_OK;
}

HRESULT [!ClassName]::BuildFinish(long nNumErrors, long nNumWarnings)
{
	return S_OK;
}

HRESULT [!ClassName]::BeforeApplicationShutDown()
{
	return S_OK;
}

HRESULT [!ClassName]::DocumentOpen(IDispatch* theDocument)
{
	return S_OK;
}

HRESULT [!ClassName]::BeforeDocumentClose(IDispatch* theDocument)
{
	return S_OK;
}

HRESULT [!ClassName]::DocumentSave(IDispatch* theDocument)
{
	return S_OK;
}

HRESULT [!ClassName]::NewDocument(IDispatch* theDocument)
{
	return S_OK;
}

HRESULT [!ClassName]::WindowActivate(IDispatch* theWindow)
{
	return S_OK;
}

HRESULT [!ClassName]::WindowDeactivate(IDispatch* theWindow)
{
	return S_OK;
}

HRESULT [!ClassName]::WorkspaceOpen()
{
	return S_OK;
}

HRESULT [!ClassName]::WorkspaceClose()
{
	return S_OK;
}

HRESULT [!ClassName]::NewWorkspace()
{
	return S_OK;
}
[!crlf]
[!endif]


[!if=(DebuggerEvents, "TRUE")]
/////////////////////////////////////////////////////////////////////////////
// Debugger event

HRESULT [!ClassName]::BreakpointHit(IDispatch* pBreakpoint)
{
	return S_OK;
}
[!crlf]
[!endif]

[!if=(Toolbar, "TRUE")]
[!if!=(MethodName, "")]
HRESULT [!ClassName]::[!MethodName]()
[!else]
HRESULT [!ClassName]::SampleMethod()
[!endif]
{
	// Replace this with the actual code to execute this command
	// Use m_spApplication to access the Developer Studio Application object
	return S_OK;
}
[!crlf]
[!endif]

