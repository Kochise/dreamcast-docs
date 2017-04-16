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

[!if=(ObjectControl, "TRUE")]
HRESULT [!ClassName]::Activate()
{
	HRESULT hr = GetObjectContext(&m_spObjectContext);
	if (SUCCEEDED(hr))
		return S_OK;
	return hr;
} 

[!crlf]
BOOL [!ClassName]::CanBePooled()
{
[!if=(CanBePooled, "TRUE")]
	return TRUE;
[!else]
	return FALSE;
[!endif]
} 

[!crlf]
void [!ClassName]::Deactivate()
{
	m_spObjectContext.Release();
} 
[!crlf]
[!endif]