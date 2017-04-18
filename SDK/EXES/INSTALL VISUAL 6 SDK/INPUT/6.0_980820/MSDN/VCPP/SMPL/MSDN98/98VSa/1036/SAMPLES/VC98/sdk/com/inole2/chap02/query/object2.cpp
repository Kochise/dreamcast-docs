/*
 * OBJECT2.CPP
 *
 * Object implementation using contained interface classes
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
 * CreateObject2
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

BOOL CreateObject2(IUnknown **ppUnk)
    {
    HRESULT     hr;
    CObject2   *pObj;

    if (NULL==ppUnk)
        return FALSE;

    //Create the new object, which gives us a C++ object pointer
    pObj=new CObject2();

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
 * CObject2::CObject2
 * CObject2::~CObject2
 *
 * Constructor Parameters:
 *  None
 */

CObject2::CObject2(void)
    : m_ImpISampleOne(this), m_ImpISampleTwo(this)
    {
    m_cRef=0;
    return;
    }

CObject2::~CObject2(void)
    {
    //Interfaces cleaned up automatically
    return;
    }





/*
 * CObject2::QueryInterface
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

STDMETHODIMP CObject2::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    /*
     * IUnknown comes from CObject2.  Note that here we do not need
     * to explicitly typecast the object pointer into an interface
     * pointer because the vtables are identical.  If we had
     * additional virtual member functions in the object, we would
     * have to cast in order to set the right vtable.  This is
     * demonstrated in the multiple-inheritance version, CObject3.
     */
    if (IID_IUnknown==riid)
        *ppv=this;

    //Other interfaces come from contained classes
    if (IID_ISampleOne==riid)
        *ppv=&m_ImpISampleOne;

    if (IID_ISampleTwo==riid)
        *ppv=&m_ImpISampleTwo;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    //AddRef any interface we'll return.
    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }



/*
 * CObject2::AddRef
 * CObject2::Release
 *
 * Reference counting members.  When Release sees a zero count
 * the object destroys itself.
 */

DWORD CObject2::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CObject2::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




//CObject2::CImpISampleOne interface implementation


//Constructor/destructor inline in object2.h

/*
 * CObject2::CImpISampleOne::QueryInterface
 * CObject2::CImpISampleOne::AddRef
 * CObject2::CImpISampleOne::Release
 *
 * IUnknown members that delegate to m_pObj
 */

STDMETHODIMP CObject2::CImpISampleOne::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CObject2::CImpISampleOne::AddRef(void)
    {
    /*
     * We maintain an "interface reference count" for debugging
     * purposes, because the client of an object should match
     * AddRef and Release calls through each interface pointer.
     */
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CObject2::CImpISampleOne::Release(void)
    {
    /*
     * m_cRef is again only for debugging.  It doesn't affect
     * CObject2 although the call to m_pObj->Release does.
     */
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CObject2::CImpISampleOne::GetMessage
 *
 * Purpose:
 *  Returns a string to the caller.
 *
 * Parameters:
 *  psz             LPTSTR in which to store the string.
 *  cch             UINT size of psz.
 *
 * Return Value:
 *  HRESULT         NOERROR if the string is stored, E_OUTOFMEMORY
 *                  if the buffer is too small.
 */

STDMETHODIMP CObject2::CImpISampleOne::GetMessage(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szMessage))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szMessage);
    return NOERROR;
    }







//CObject2::CImpISampleTwo interface implementation


//Constructor/destructor inline in object2.h

/*
 * CObject2::CImpISampleTwo::QueryInterface
 * CObject2::CImpISampleTwo::AddRef
 * CObject2::CImpISampleTwo::Release
 *
 * IUnknown members that delegate to m_pObj
 */

STDMETHODIMP CObject2::CImpISampleTwo::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CObject2::CImpISampleTwo::AddRef(void)
    {
    /*
     * We maintain an "interface reference count" for debugging
     * purposes, because the client of an object should match
     * AddRef and Release calls through each interface pointer.
     */
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CObject2::CImpISampleTwo::Release(void)
    {
    /*
     * m_cRef is again only for debugging.  It doesn't affect
     * CObject2 although the call to m_pObj->Release does.
     */
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CObject2::CImpISampleTwo::GetString
 *
 * Purpose:
 *  Returns a string to the caller.
 *
 * Parameters:
 *  psz             LPTSTR in which to store the string.
 *  cch             UINT size of psz.
 *
 * Return Value:
 *  HRESULT         NOERROR if the string is stored, E_OUTOFMEMORY
 *                  if the buffer is too small.
 */

STDMETHODIMP CObject2::CImpISampleTwo::GetString(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szString))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szString);
    return NOERROR;
    }
