/*+----------------------------------------------------------------------------

Microsoft Windows Sample Program
Copyright (C) 1994 - 1997 Microsoft Corporation.  All rights reserved.

FILE:       CHello.cxx

PURPOSE:    Implements the CHello object and class factory.

CLASSES:    CHello
            CHelloClassFactory

FUNCTIONS:  RegisterClassFactory
            RevokeClassFactory

-----------------------------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include "ohello.h"

void DecrementLockCount();
void IncrementLockCount();
void ObjectCreated();
void ObjectDestroyed();

extern "C" const CLSID CLSID_OHello;

long    g_fClassRegistered  = FALSE;
DWORD   g_dwRegister        = 0;

//The CHello class implements the server object.
class CHello : public IHello
{
private:
    unsigned long    m_cRef;

    //destructor
    ~CHello()
    {
        DecrementLockCount();
        ObjectDestroyed();
    }
    
public:
    //constructor
    CHello()
    {
        m_cRef = 1;
        ObjectCreated();
        IncrementLockCount();
    }
    
	HRESULT STDMETHODCALLTYPE QueryInterface(
		REFIID iid,
	    void **ppv);
	
	ULONG STDMETHODCALLTYPE AddRef();
	
	ULONG STDMETHODCALLTYPE Release();
	
	HRESULT STDMETHODCALLTYPE HelloProc(unsigned char *pszString);
};

//+-------------------------------------------------------------------------
//
//  Method:     CHello::AddRef, public
//
//  Synopsis:   Increment reference count
//
//  See Also:   IUnknown::AddRef
//
//--------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE 
CHello::AddRef()
{
    InterlockedIncrement((long *) &m_cRef);
    return m_cRef;
}

//+---------------------------------------------------------------------------
//
//  Method:     CHello::HelloProc()
//
//  Synopsis:   Displays the specified string.
//
//  See Also:   IHello::HelloProc
//
//----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE
CHello::HelloProc(unsigned char *pszString)
{
    printf("HelloProc: %s \n", pszString);
    return S_OK;
}

//+-------------------------------------------------------------------------
//
//  Method:     CHello::QueryInterface, public
//
//  Synopsis:   Query for an interface on the class factory.
//
//  See Also:   IUnknown:QueryInterface
//
//--------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE 
CHello::QueryInterface (
    REFIID iid,
    void **ppv )
{
    HRESULT hr;

    if ( IsEqualGUID( iid, IID_IUnknown ) ||
         IsEqualGUID( iid, IID_IHello ) )
    {
        *ppv = (IHello *) this;
        AddRef();
	    hr = S_OK;
    }
    else
    {
        *ppv = 0;
        hr = E_NOINTERFACE;
    }

    return hr;
}

//+-------------------------------------------------------------------------
//
//  Method:     CHello::Release, public
//
//  Synopsis:   Decrement DLL reference count
//
//  Notes:      After the m_cRef is decremented, the object may be 
//              deleted by another thread.  In order to make this code safe
//              for multiple threads, we have to access the object state 
//              before decrementing m_cRef.
//
//  See Also:   IUnknown::Release.
//
//--------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE
CHello::Release()
{
    unsigned long count;
    
    count = m_cRef - 1;

    if(InterlockedDecrement((long *) &m_cRef) == 0)
    {
        count = 0;
        delete this;
    }

    return count;
}



// this is the class factory for the CHello server object.
// it manufactures CHello server objects in response to a CreateInstance
// call

class CHelloClassFactory : public IClassFactory
{
private:
    unsigned long    m_cRef;

    //destructor
    ~CHelloClassFactory()
    {
        ObjectDestroyed();
    }

public:
    //constructor
    CHelloClassFactory()
    {
        m_cRef = 1;
        ObjectCreated();
    }

	HRESULT STDMETHODCALLTYPE QueryInterface(
		REFIID iid,
	    void **ppv);
	
	ULONG STDMETHODCALLTYPE AddRef();
	
	ULONG STDMETHODCALLTYPE Release();
	
	HRESULT STDMETHODCALLTYPE CreateInstance(
	    IUnknown *punkOuter,
	    REFIID riid,
	    void **ppv);

   HRESULT STDMETHODCALLTYPE LockServer(
        BOOL fLock );

};

//+-------------------------------------------------------------------------
//
//  Method:     CHelloClassFactory::AddRef, public
//
//  Synopsis:   Increment DLL reference counts
//
//  See Also:   IUnknown::AddRef
//
//--------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE 
CHelloClassFactory::AddRef()
{
    InterlockedIncrement((long *) &m_cRef);
    return m_cRef;
}

//+-------------------------------------------------------------------------
//
//  Method:     CHelloClassFactory::CreateInstance, public
//
//  Synopsis:   Create an instance of CHello.
//
//  See Also:   IClassFactory::CreateInstance
//
//--------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE 
CHelloClassFactory::CreateInstance
(
    IUnknown *punkOuter,
    REFIID riid,
    void **ppv
)
{
    HRESULT hr;
    CHello *pHello;

    if(punkOuter != 0)
    {
        //The CHello class doesn't support aggregation.
        return CLASS_E_NOAGGREGATION;
    }

    pHello = new CHello();
    if(pHello != 0)
    {
        hr = pHello->QueryInterface(riid, ppv);
        pHello->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
        *ppv = 0;
    }

    return hr;
}

//+-------------------------------------------------------------------------
//
//  Method:     CHelloClassFactory::LockServer, public
//
//  Synopsis:   Lock the server in memory (by adding an extra reference)
//
//  Notes:      The class factory will be revoked when the lock count
//              is decremented to zero.  LockServer(TRUE) will increment the
//              lock count and ensure that the class factory will
//              not be revoked.
//
//  See Also:   IClassFactory::LockServer
//
//--------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE 
CHelloClassFactory::LockServer(
    BOOL fLock )
{
    if (fLock == TRUE)
        IncrementLockCount();
    else
        DecrementLockCount();

    return S_OK;
}


//+-------------------------------------------------------------------------
//
//  Method:     CHelloClassFactory::QueryInterface, public
//
//  Synopsis:   Query for an interface on the class factory.
//
//  See Also:   IUnknown::QueryInterface
//
//--------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE 
CHelloClassFactory::QueryInterface (
    REFIID iid,
    void **ppv )
{
    HRESULT hr;

    if ( IsEqualGUID( iid, IID_IUnknown) ||
         IsEqualGUID( iid, IID_IClassFactory ) )
    {
        *ppv = this;
        AddRef();
        hr = S_OK;
    }
    else
    {
        *ppv = 0;
        hr = E_NOINTERFACE;
    }

    return hr;
}
//+-------------------------------------------------------------------------
//
//  Method:     CHelloClassFactory::Release, public
//
//  Synopsis:   Decrement DLL reference count
//
//  See Also:   IUnknown::Release
//
//--------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE
CHelloClassFactory::Release()
{
    unsigned long count;
    
    count = m_cRef - 1;

    if(InterlockedDecrement((long *) &m_cRef) == 0)
    {
        count = 0;

        ObjectDestroyed();
    }

    return count;
}

//+-------------------------------------------------------------------------
//
//  Function:   RegisterClassFactory.
//
//  Synopsis:   Register the class factory if it is not currently registered.
//
//--------------------------------------------------------------------------
HRESULT RegisterClassFactory()
{
    HRESULT hr;
    CHelloClassFactory *pClassFactory;

    if(InterlockedExchange(&g_fClassRegistered, TRUE) == FALSE)
    {
        pClassFactory = new CHelloClassFactory;
        
        if(pClassFactory != 0)
        {
            hr = CoRegisterClassObject(CLSID_OHello,
	   	        		               (IUnknown *) pClassFactory,
	    	        	               CLSCTX_LOCAL_SERVER,
		    	                       REGCLS_MULTIPLEUSE,
			                           &g_dwRegister);
          	pClassFactory->Release();
        }
        else
        {
           hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        hr = S_OK;
    }
    return hr;  
}

//+-------------------------------------------------------------------------
//
//  Function:   RevokeClassFactory.
//
//  Synopsis:   Revoke the registered class factories if they have not
//              already been revoked.
//
//--------------------------------------------------------------------------
HRESULT RevokeClassFactory()
{
    HRESULT hr;

    if(InterlockedExchange(&g_fClassRegistered, FALSE) == TRUE)
    {
        hr = CoRevokeClassObject(g_dwRegister);
    }
    else
    {
        hr = S_OK;
    }
    return hr;
}


