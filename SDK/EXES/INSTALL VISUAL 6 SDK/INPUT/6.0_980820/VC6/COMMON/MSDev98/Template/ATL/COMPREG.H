// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
	public IDispatchImpl<IComponentRegistrar, &IID_IComponentRegistrar, &LIBID_[!LibName]>
{
public:
	[!ClassName]()
	{
	}

[!crlf]
DECLARE_NO_REGISTRY()

[!crlf]
BEGIN_COM_MAP([!ClassName])
	COM_INTERFACE_ENTRY(IComponentRegistrar)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

[!crlf]
// IComponentRegistrar
public:
    STDMETHOD(Attach)(BSTR bstrPath)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(RegisterAll)()
	{
		return _Module.RegisterServer(TRUE);
	}
	STDMETHOD(UnregisterAll)()    
	{
		_Module.UnregisterServer(TRUE);
		return S_OK;
	}
	STDMETHOD(GetComponents)(SAFEARRAY **ppCLSIDs, SAFEARRAY **ppDescriptions)
	{
		_ATL_OBJMAP_ENTRY* pEntry = _Module.m_pObjMap;
		int nComponents = 0;
		while (pEntry->pclsid != NULL)
		{
			LPCTSTR pszDescription = pEntry->pfnGetObjectDescription();
			if (pszDescription)
				nComponents++;
			pEntry++;
		}
		SAFEARRAYBOUND rgBound[1];
		rgBound[0].lLbound = 0;
		rgBound[0].cElements = nComponents;
		*ppCLSIDs = SafeArrayCreate(VT_BSTR, 1, rgBound);
		*ppDescriptions = SafeArrayCreate(VT_BSTR, 1, rgBound);
		pEntry = _Module.m_pObjMap;
		for (long i=0; pEntry->pclsid != NULL; pEntry++)
		{
			LPCTSTR pszDescription = pEntry->pfnGetObjectDescription();
			if (pszDescription)
			{
				LPOLESTR pszCLSID;
				StringFromCLSID(*pEntry->pclsid, &pszCLSID);
				SafeArrayPutElement(*ppCLSIDs, &i, OLE2BSTR(pszCLSID));
				CoTaskMemFree(pszCLSID);
				SafeArrayPutElement(*ppDescriptions, &i, T2BSTR(pszDescription));
				i++;
			}
		}

		return S_OK;
	}
	STDMETHOD(RegisterComponent)(BSTR bstrCLSID)
	{
		CLSID clsid;
		CLSIDFromString(bstrCLSID, &clsid);
		_Module.RegisterServer(TRUE, &clsid);
		return S_OK;
	}
	STDMETHOD(UnregisterComponent)(BSTR bstrCLSID)
	{
		CLSID clsid;
		CLSIDFromString(bstrCLSID, &clsid);
		_Module.UnregisterServer(&clsid);
		return S_OK;
	}
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
