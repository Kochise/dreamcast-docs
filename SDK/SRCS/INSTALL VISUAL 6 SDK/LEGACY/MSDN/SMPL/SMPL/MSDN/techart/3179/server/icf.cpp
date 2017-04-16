//**********************************************************************
// File name: ICF.CPP
//
//    Implementation file for the CClassFactory Class
//
// Functions:
//
//    See icf.h for a list of member functions.
//
// Copyright (c) 1994 Microsoft Corporation. All rights reserved.
//**********************************************************************

#include "pre.h"
#include "app.h"
#include "icf.h"
#include "obj.h"

//**********************************************************************
// CClassFactory::QueryInterface
//
// Parameters:
//      REFIID riid         -   Interface being queried for.
//      LPVOID FAR *ppvObj  -   Out pointer for the interface.
//
// Return Value:
//      S_OK            - Success
//      E_NOINTERFACE   - Failure
//
// Function Calls:
//      Function                    Location
//      CPDSvrApp::QueryInterface APP.CPP
//********************************************************************
STDMETHODIMP CClassFactory::QueryInterface  ( REFIID riid, LPVOID FAR* ppvObj)
{
	OutputDebugString(TEXT("In CClassFactory::QueryInterface\r\n"));

	SCODE sc = S_OK;

        // return pointer to interfaces we support
	if ((riid == IID_IUnknown) || (riid == IID_IClassFactory))
		*ppvObj = this;
	else  // request for interface we don't support
	{
		*ppvObj = NULL;
		sc = E_NOINTERFACE;
	}

	if (*ppvObj)
		((LPUNKNOWN)*ppvObj)->AddRef();

	// pass it on to the Application object
	return ResultFromScode(sc);
};

//**********************************************************************
// CClassFactory::AddRef
//
// Purpose:      Increments the ref count on CClassFactory object.
// Parameters:   None
// Return Value: The ref count on CClassFactory
//
// Function Calls:
//      Function                    Location
//      OuputDebugString            Windows API
//********************************************************************
STDMETHODIMP_(ULONG) CClassFactory::AddRef ()
{
	OutputDebugString(TEXT("In CClassFactory::AddRef\r\n"));
	return ++m_nCount;
};

//**********************************************************************
// CClassFactory::Release
//
// Purpose:      Decrements the ref count of CClassFactory object
// Parameters:   None
// Return Value: The new reference count
//      
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//********************************************************************
STDMETHODIMP_(ULONG) CClassFactory::Release ()
{
    TCHAR  szBuff[64];

	wsprintf(szBuff, 
	         TEXT("In CClassFactory::Release. m_nCount = %d\r\n"), 
	         m_nCount -1);

	OutputDebugString(szBuff);

	if (--m_nCount == 0)   // our ref count is 0; we can now free ourself
	{
		delete this;
        return 0;
    }

	return m_nCount;
};

//**********************************************************************
// CClassFactory::CreateInstance
//
// Purpose: Instantiates a new OLE object
// Parameters:
//      LPUNKNOWN pUnkOuter     - Pointer to the controlling unknown
//      REFIID riid             - The interface type to fill in ppvObject
//      LPVOID FAR* ppvObject   - Out pointer for the object
//
// Return Value:
//      S_OK                    - Creation was successful
//      CLASS_E_NOAGGREGATION   - Tried to be created as part of an aggregate
//      CLASS_E_CLASSNOTAVAILABLE - Tried to crete a second object; we only support 1.
//      E_FAIL                  - Creation failed
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//      CPDSvrApp::CreateObject     app.CPP
//********************************************************************
STDMETHODIMP CClassFactory::CreateInstance ( LPUNKNOWN pUnkOuter,
							  REFIID riid,
							  LPVOID FAR* ppvObject)
{
	HRESULT hErr = ResultFromScode(E_FAIL);

	OutputDebugString(TEXT("In CClassFactory::CreateInstance\r\n"));

	// need to NULL the out parameter
	*ppvObject = NULL;

    // We can only have one instance.  Thus we must fail this call to
    // CreateInstance
	if (m_lpApp->m_lpObj != NULL)
		return ResultFromScode(CLASS_E_CLASSNOTAVAILABLE);
	
	// we don't support aggregation...
	if (pUnkOuter)
		return ResultFromScode(CLASS_E_NOAGGREGATION);

    // create a new object
	m_lpApp->m_lpObj = new CPDSvrObj( m_lpApp );

	m_lpApp->ObjectCreated();

    // get requested interface
	if (m_lpApp->m_lpObj)
		hErr = m_lpApp->m_lpObj->QueryInterface(riid, ppvObject);

    if (FAILED(hErr))
    {
        delete m_lpApp->m_lpObj ;
        m_lpApp->m_lpObj = NULL ;
    }

	return hErr;
};

//**********************************************************************
// CClassFactory::LockServer
//
// Parameters:
//      BOOL fLock      - TRUE to lock the server, FALSE to unlock it
//
// Return Value:  S_OK
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//      CoLockObjectExternal        OLE API
//      ResultFromScode             OLE API
//********************************************************************
STDMETHODIMP CClassFactory::LockServer ( BOOL fLock)
{
	OutputDebugString(TEXT("In CClassFactory::LockServer\r\n"));
	CoLockObjectExternal(this, fLock, TRUE);

	return ResultFromScode( S_OK);
};
