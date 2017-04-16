#include "stdafx.h"
#include "combase.h"

//
// External Globals - Define these in the DLLs main file
//
extern CFactoryTemplate g_Templates[] ;
extern int g_cTemplates;

//
// Count of active objects. Use to determine if we can unload the DLL.
//
LONG CUnknown::m_ObjectCount = 0;

//
// Constructor
//
CUnknown::CUnknown(IUnknown* pUnk, HRESULT* phr)
{
	InterlockedIncrement(&m_ObjectCount) ;

	if (pUnk == NULL)
		m_pUnkOwner = (IUnknown*)(INonDelegatingUnknown*) this ;	 // NOTE THIS!
	else
		m_pUnkOwner = pUnk ;

	m_RefCount = 0 ;
} 

//
// Destructor
//
CUnknown::~CUnknown()
{
	InterlockedDecrement(&m_ObjectCount) ;
}

//
//	 Init - Calls OnInit. 
//
BOOL CUnknown::Init()
{
	// We haven't done anything to the reference count yet.
	// So bump it up to protect the object.
	m_RefCount++ ;
	BOOL bResult = OnInit() ;
	m_RefCount-- ;
	return bResult ;
}

//
// NonDelegatingIUnknown - Override to handle custom interfaces.
//
HRESULT __stdcall CUnknown::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	// Only know about IUnknown
	if (riid == IID_IUnknown)
	{
		return GetInterface((IUnknown*)(INonDelegatingUnknown*)this, ppv) ;
	}	
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
}

//
// AddRef
//
ULONG __stdcall CUnknown::NonDelegatingAddRef()
{
	LONG lRef = InterlockedIncrement(&m_RefCount) ;
	ASSERT(lRef > 0) ;
	return (ULONG)lRef ;
}

//
// Release
//
ULONG __stdcall CUnknown::NonDelegatingRelease()
{
	LONG lRef = InterlockedDecrement(&m_RefCount) ;
	ASSERT(lRef >= 0) ;
	if (lRef == 0)
	{
		delete this ;
		return (ULONG) 0 ;
	}
	else
	{
		return (ULONG) lRef ;
	}
}

//
// GetInterface - Helper function to simplify overriding NonDelegatingIUnknown
//
HRESULT CUnknown::GetInterface(IUnknown* pUnk, void** ppv) 
{
	*ppv = pUnk ;
	((IUnknown*)pUnk)->AddRef() ;
	return NOERROR ;
}


/////////////////////////////////////////////////////////////////////////////////////
//
// ClassFactory Implementation
//

int CClassFactory::m_LockCount = 0 ;

//
// Constructor
//
CClassFactory::CClassFactory(const CFactoryTemplate* pTemplate)
{
	m_RefCount = 0 ;
	m_pTemplate = pTemplate ;
}

//
// GetClassObject - Creates a class factory based on CLSID
//
HRESULT CClassFactory::GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    if (!(riid == IID_IUnknown) && !(riid == IID_IClassFactory))
    {
            return E_NOINTERFACE;
    }

    // traverse the array of templates looking for one with this
    // class id
    for (int i = 0; i < g_cTemplates; i++)
    {
        const CFactoryTemplate * pT = &g_Templates[i];
        if (pT->IsClassID(rclsid))
        {

            // found a template - make a class factory based on this
            // template
		    *ppv = (void*) (IUnknown*) new CClassFactory(pT);
            if (*ppv == NULL)
            {
                return E_OUTOFMEMORY;
            }
            ((IUnknown*)*ppv)->AddRef();
            return NOERROR;
        }
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

//
// CanUnloadNow 
//
HRESULT CClassFactory::CanUnloadNow()
{
    if (IsLocked() || CUnknown::ObjectsActive())
		return S_FALSE;    
    else
        return S_OK;    
}

//
// CreateInstance
//
STDMETHODIMP CClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
    // Enforce the normal OLE rules regarding interfaces and delegation
    if ((pUnkOuter != NULL) &&  
   		(riid != IID_IUnknown))
    {
		// Aggregated objects can only query IUnknown
          return ResultFromScode(CLASS_E_NOAGGREGATION);
    }

    // Create the new object through the derived class's create function
    HRESULT hr = NOERROR ;
    CUnknown *pObj = m_pTemplate->CreateInstance(pUnkOuter, &hr);
    if (pObj == NULL) return hr;
    // Delete the object if we got a construction error 
    if (FAILED(hr))
    {
        delete pObj;
        return hr;
    }

   // Initialize the Object. Used mainly for aggregating objects.
	if (!pObj->Init())
	{
		delete pObj ;
		return E_OUTOFMEMORY ;
	}

   	// Get a reference counted interface on the object 
	hr = pObj->NonDelegatingQueryInterface(riid, ppv);
   if (FAILED(hr))
   {
       delete pObj;
       return hr;
   }

   ASSERT(*ppv);
   return hr;
}

//
// LockServer
//
STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        m_LockCount++;
    }
    else
    {
        m_LockCount--;
    }
    return NOERROR;
}

//
// QueryInterface
//
STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = NULL;

    // any interface on this object is the object pointer.
    if (IsEqualIID(riid, IID_IUnknown) || 
    	IsEqualIID(riid, IID_IClassFactory))
	{
        *ppv = (void*) this;
	}

    // AddRef returned interface pointer
    if (*ppv != NULL)
    {
        ((IUnknown*) *ppv)->AddRef();
        return NOERROR;
    }

    return ResultFromScode(E_NOINTERFACE);
}

//
// AddRef
//
STDMETHODIMP_(ULONG) CClassFactory::AddRef()
{
    return ++m_RefCount;
}

//
// Release
//
STDMETHODIMP_(ULONG) CClassFactory::Release()
{
    if (--m_RefCount == 0)
    {
        delete this;
        return 0;
    } 
    else
    {
        return m_RefCount;
    }
}

