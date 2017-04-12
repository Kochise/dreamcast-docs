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
[!if=(ErrorInfoEnabled, "TRUE")]
STDMETHODIMP [!ClassName]::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_[!InterfaceName],
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
[!crlf]
[!endif]

[!if=(OnStartPage, "TRUE")]
STDMETHODIMP [!ClassName]::OnStartPage (IUnknown* pUnk)  
{
	if(!pUnk)
		return E_POINTER;
[!crlf]

	CComPtr<IScriptingContext> spContext;
	HRESULT hr;
[!crlf]
	// Get the IScriptingContext Interface
	hr = pUnk->QueryInterface(IID_IScriptingContext, (void **)&spContext);
	if(FAILED(hr))
		return hr;

[!if=(Request, "TRUE")]
[!crlf]
	// Get Request Object Pointer
	hr = spContext->get_Request(&m_piRequest);
	if(FAILED(hr))
	{
		spContext.Release();
		return hr;
	}
[!endif]

[!if=(Response, "TRUE")]
[!crlf]
	// Get Response Object Pointer
	hr = spContext->get_Response(&m_piResponse);
	if(FAILED(hr))
	{
[!if=(Request, "TRUE")]
		m_piRequest.Release();
[!endif]
		return hr;
	}
[!endif]
	
[!if=(Server, "TRUE")]
	// Get Server Object Pointer
	hr = spContext->get_Server(&m_piServer);
	if(FAILED(hr))
	{
[!if=(Request, "TRUE")]
		m_piRequest.Release();
[!endif]
[!if=(Response, "TRUE")]
		m_piResponse.Release();
[!endif]
		return hr;
	}
[!endif]
	
[!if=(Session, "TRUE")]
	// Get Session Object Pointer
	hr = spContext->get_Session(&m_piSession);
	if(FAILED(hr))
	{
[!if=(Request, "TRUE")]
		m_piRequest.Release();
[!endif]
[!if=(Response, "TRUE")]
		m_piResponse.Release();
[!endif]
[!if=(Server, "TRUE")]
		m_piServer.Release();
[!endif]
		return hr;
	}
[!endif]

[!if=(Application, "TRUE")]
[!crlf]
	// Get Application Object Pointer
	hr = spContext->get_Application(&m_piApplication);
	if(FAILED(hr))
	{
[!if=(Request, "TRUE")]
		m_piRequest.Release();
[!endif]
[!if=(Response, "TRUE")]
		m_piResponse.Release();
[!endif]
[!if=(Server, "TRUE")]
		m_piServer.Release();
[!endif]
[!if=(Session, "TRUE")]
		m_piSession.Release();
[!endif]
		return hr;
	}
[!endif]
	m_bOnStartPageCalled = TRUE;
	return S_OK;
}
[!crlf]

STDMETHODIMP [!ClassName]::OnEndPage ()  
{
	m_bOnStartPageCalled = FALSE;
	// Release all interfaces
[!if=(Request, "TRUE")]	m_piRequest.Release();[!endif]
[!if=(Response, "TRUE")]	m_piResponse.Release();[!endif]
[!if=(Server, "TRUE")]	m_piServer.Release();[!endif]
[!if=(Session, "TRUE")]	m_piSession.Release();[!endif]
[!if=(Application, "TRUE")]	m_piApplication.Release();[!endif]
[!crlf]
	return S_OK;
}
[!crlf]
[!endif]