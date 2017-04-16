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
		&IID_[!InterfaceName]
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
[!endif]
