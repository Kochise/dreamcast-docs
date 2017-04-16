#include "stdafx.h"
#include "GUIDS.h"
#include "ISimple.h"
#include "CSimpleObject.h"
#include "CClassFactory.h"

/////////////////////////////////////////////////////////////////////////////////////
//
// ClassFactory Implementation
//

int CClassFactory::m_LockCount = 0 ;

//
// DLL Entry Points
//
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return CClassFactory::GetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	return CClassFactory::CanUnloadNow();
}


//
// Constructor
//
CClassFactory::CClassFactory()
{
	m_RefCount = 0 ;
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

    if (CLSID_SimpleObject == rclsid)
    {
		   *ppv = (void*) (IUnknown*) new CClassFactory();
         if (*ppv == NULL)
         {
             return E_OUTOFMEMORY;
         }
         ((IUnknown*)*ppv)->AddRef();
         return NOERROR;
    }
    else
    {
      return CLASS_E_CLASSNOTAVAILABLE;
    }
}

//
// CanUnloadNow 
//
HRESULT CClassFactory::CanUnloadNow()
{
    if (IsLocked() || CSimpleObject::ObjectsActive())
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
          return CLASS_E_NOAGGREGATION;
    }

    // Create the new object through the derived class's create function
    HRESULT hr = NOERROR ;
    CSimpleObject *pObj = CSimpleObject::CreateInstance(pUnkOuter, &hr);
    if (pObj == NULL) return hr;
    // Delete the object if we got a construction error 
    if (FAILED(hr))
    {
        delete pObj;
        return hr;
    }

  	// Get a reference counted interface on the object 
	hr = pObj->QueryInterface(riid, ppv);
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
   if ((riid == IID_IUnknown) || 
       (riid== IID_IClassFactory))
	{
      *ppv = (void*) this;
	}

    // AddRef returned interface pointer
    if (*ppv != NULL)
    {
        ((IUnknown*) *ppv)->AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
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

