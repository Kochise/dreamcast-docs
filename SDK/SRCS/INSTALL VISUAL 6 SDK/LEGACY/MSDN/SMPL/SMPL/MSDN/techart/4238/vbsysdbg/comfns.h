// comfns.h
// 
// COM object support

//////////////////////////////////////////////////////////////////////////
// Windows native functions (in COMPOBJ.DLL)

STDAPI vbCoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
		    DWORD dwClsContext, REFIID riid, LPVOID* ppv);

//////////////////////////////////////////////////////////////////////////
// Local COM support functions

STDAPI comQueryInterface(IUnknown* punkObject, IID& riid, void** ppvObj);
STDAPI comAddRef(IUnknown* punkObject);
STDAPI comRelease(IUnknown* punkObject);
STDAPI comCallStdMember0(IUnknown* pInterface, DWORD dwIndex);
STDAPI comCallStdMember1(IUnknown* pInterface, DWORD dwIndex,
                         DWORD dwArg1);
STDAPI comCallStdMember2(IUnknown* pInterface, DWORD dwIndex,
                         DWORD dwArg1, DWORD dwArg2);
STDAPI comCallStdMember3(IUnknown* pInterface, DWORD dwIndex,
                         DWORD dwArg1, DWORD dwArg2, DWORD dwArg3);

