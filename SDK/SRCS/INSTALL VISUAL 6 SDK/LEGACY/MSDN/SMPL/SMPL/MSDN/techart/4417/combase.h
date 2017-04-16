
#ifndef __COMBASE_H__
#define __COMBASE_H__


//////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_IUNKNOWN                                        \
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {      \
        return GetOwner()->QueryInterface(riid,ppv);            \
    };                                                          \
    STDMETHODIMP_(ULONG) AddRef() {                             \
        return GetOwner()->AddRef();                            \
    };                                                          \
    STDMETHODIMP_(ULONG) Release() {                            \
        return GetOwner()->Release();                           \
    };


///////////////////////////////////////////////////////////////////////////////////

DECLARE_INTERFACE(INonDelegatingUnknown)
{
    STDMETHOD(NonDelegatingQueryInterface) (THIS_ REFIID, LPVOID *) PURE;
    STDMETHOD_(ULONG, NonDelegatingAddRef)(THIS) PURE;
    STDMETHOD_(ULONG, NonDelegatingRelease)(THIS) PURE;
};


///////////////////////////////////////////////////////////////////////////////////

class CUnknown : 	public INonDelegatingUnknown
{
public:
	// NonDelegatingIUnknown Implementation...
    virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv);
    virtual ULONG __stdcall NonDelegatingAddRef();
    virtual ULONG __stdcall NonDelegatingRelease();

	// Constructor
	CUnknown(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CUnknown() ;

	// Initialization (esp for aggregates)
	BOOL Init() ;
	virtual BOOL OnInit() {return TRUE ;}

	// Support for delegation
	IUnknown* GetOwner() const
		{ return m_pUnkOwner; }

	// CreateInstance --- Define in derived classes 
	//static  CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) = 0 ;

	static LONG ObjectsActive() 
		{return m_ObjectCount;}

	HRESULT GetInterface(IUnknown* pUnk, void** ppv) ;
	
private:
	IUnknown* m_pUnkOwner ;
	static LONG m_ObjectCount ; // Count of active objects.

protected:
	LONG m_RefCount ;
} ;

/////////////////////////////////////////////////////////////////////////////////////

typedef CUnknown* (*PFNNewCOMObject)(IUnknown* pUnkOuter, HRESULT* phr) ;

//////////////////////////////////////////////////////////////////////////////////////

class CFactoryTemplate
{
public:
	const CLSID* m_ClsID ;
	PFNNewCOMObject m_pfnNew ;

	BOOL IsClassID(REFCLSID rclsid) const
		{return IsEqualCLSID(*m_ClsID, rclsid) ;}

	CUnknown *CreateInstance(IUnknown* pUnk, HRESULT* phr) const
		{ return m_pfnNew(pUnk, phr) ; }		
} ;

//////////////////////////////////////////////////////////////////////////////////////

class CClassFactory : public IClassFactory
{
public:
	CClassFactory(const CFactoryTemplate* pTemplate) ;
	
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
	const CFactoryTemplate* m_pTemplate ;
	ULONG m_RefCount ;			
	static int m_LockCount ;
};
#endif //FACTORY
