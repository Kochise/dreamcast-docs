#ifndef __CClassFactory__
#define __CClassFactory__

class CClassFactory : public IClassFactory
{
public:
	CClassFactory() ;
	
	// IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

	// IClassFactory
	STDMETHODIMP  CreateInstance(IUnknown* pUnkOunter, REFIID riid, void** ppv) ;
	STDMETHODIMP  LockServer(BOOL fLock) ;

	// Entry Points 
	static HRESULT GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) ;
	static HRESULT CanUnloadNow() ;

	//
	static BOOL IsLocked()
		{ return (m_LockCount > 0) ; }

protected:
	ULONG m_RefCount ;			
	static int m_LockCount ;
};

#endif
