[!if=(InsertIntoInitInstance, "1")]
	if (!InitATL())
		return FALSE;
[!endif]

[!if=(AddInitInstance, "1")]
	if (!InitATL())
		return FALSE;
[!crlf]
	return CWinApp::InitInstance();
[!endif]

[!if(INITATL)]
	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	return TRUE;
[!endif]

[!if(InsertAfterApp)]
[!crlf]
CComModule _Module;
[!crlf]
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
[!crlf]
[!if=(MFCOLE, "0")]
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer(TRUE); //TRUE indicates that typelib is unreg'd
	return S_OK;
}
[!else]
[!if=(MFCCTL, "1")]
STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(AfxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
	return _Module.GetClassObject(rclsid, riid, ppv);
}
[!else]
STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	_Module.UnregisterServer(TRUE); //TRUE indicates that typelib is unreg'd
	return S_OK;
}
[!endif]
[!endif]
[!endif]

[!if=(InsertIntoExitInstance, "1")]
	_Module.Term();
[!crlf]
[!endif]

[!if=(AddExitInstance, "1")]
	_Module.Term();
[!crlf]
	return CWinApp::ExitInstance();
[!endif]


[!if=(InsertInDllRegisterServer, "1")]
	return _Module.RegisterServer(TRUE);
[!endif]

[!if=(InsertInDllUnregisterServer, "1")]
	_Module.UnregisterServer(TRUE); //TRUE indicates that typelib is unreg'd
[!endif]

[!if=(InsertInDllGetClassObject, "1")]
	if (SUCCEEDED(_Module.GetClassObject(rclsid, riid, ppv)))
		return S_OK;
[!crlf]
[!endif]

[!if=(InsertInDllCanUnloadNow, "1")]
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
[!endif]