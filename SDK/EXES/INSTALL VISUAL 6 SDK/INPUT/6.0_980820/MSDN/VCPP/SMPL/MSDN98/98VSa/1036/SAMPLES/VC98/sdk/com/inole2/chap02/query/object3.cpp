/*
 * OBJECT3.CPP
 *
 * Object implementation using multiple inheritance.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#include <windows.h>
#include "query.h"


//Message strings for the interface functions
static TCHAR szMessage[]=TEXT("Message from ISampleOne::GetMessage");
static TCHAR szString[] =TEXT("Message from ISampleTwo::GetString");


/*
 * CreateObject3
 *
 * Purpose:
 *  Creates an instance of Object2 returning an IUnknown
 *  interface.
 *
 * Parameters:
 *  ppUnk           IUnknown ** in which to return the
 *                  interface pointer.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CreateObject3(IUnknown **ppUnk)
    {
    HRESULT     hr;
    CObject3   *pObj;

    if (NULL==ppUnk)
        return FALSE;

    //Create the new object, which gives us a C++ object pointer
    pObj=new CObject3();

    if (NULL==pObj)
        return FALSE;

    /*
     * Now get the IUnknown interface to this object and make
     * sure that it's reference count is correct.  We could either
     * typecast pObj to IUnknown and call AddRef explicitly, or
     * we can simply call pObj->QueryInterface and let it do the
     * typecast and the AddRef for us.
     */
    hr=pObj->QueryInterface(IID_IUnknown, (PPVOID)ppUnk);
    return SUCCEEDED(hr);
    }





/*
 * CObject3::CObject3
 * CObject3::~CObject3
 *
 * Constructor Parameters:
 *  None
 */

CObject3::CObject3(void)
    {
    m_cRef=0;
    return;
    }

CObject3::~CObject3(void)
    {
    return;
    }





/*
 * CObject3::QueryInterface
 *
 * Purpose:
 *  Manages the interfaces for this object which supports the
 *  IUnknown, ISampleOne, and ISampleTwo interfaces.
 *
 * Parameters:
 *  riid            REFIID of the interface to return.
 *  ppv             PPVOID in which to store the pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, E_NOINTERFACE if the
 *                  interface is not supported.
 */

STDMETHODIMP CObject3::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    /*
     * Since all the interfaces are part of this same object,
     * we *must* use typecasts to set up the right vtables from
     * the 'this' pointer.  Casting to an interface will give
     * us a pointer that points to exactly that interface vtable.
     *
     * Note that since we don't have an explicit IUnknown base,
     * responding to IUnknown here simply return ISampleOne, which
     * has the right IUnknown vtable anyway.
     */
    if (IID_IUnknown==riid || IID_ISampleOne==riid)
        *ppv=(ISampleOne *)this;

    if (IID_ISampleTwo==riid)
        *ppv=(ISampleTwo *)this;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    //AddRef any interface we'll return.
    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }



/*
 * CObject3::AddRef
 * CObject3::Release
 *
 * Reference counting members.  When Release sees a zero count
 * the object destroys itself.
 */

DWORD CObject3::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CObject3::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CObject3::GetMessage
 *
 * Purpose:
 *  Returns a string to the caller.  This is the implementation
 *  of ISampleOne::GetMessage.
 *
 * Parameters:
 *  psz             LPTSTR in which to store the string.
 *  cch             UINT size of psz.
 *
 * Return Value:
 *  HRESULT         NOERROR if the string is stored, E_OUTOFMEMORY
 *                  if the buffer is too small.
 */

STDMETHODIMP CObject3::GetMessage(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szMessage))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szMessage);
    return NOERROR;
    }


/*
 * CObject3::GetString
 *
 * Purpose:
 *  Returns a string to the caller.  This is the implementation
 *  of ISampleTwo::GetString.
 *
 * Parameters:
 *  psz             LPTSTR in which to store the string.
 *  cch             UINT size of psz.
 *
 * Return Value:
 *  HRESULT         NOERROR if the string is stored, E_OUTOFMEMORY
 *                  if the buffer is too small.
 */

STDMETHODIMP CObject3::GetString(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szString))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szString);
    return NOERROR;
    }
