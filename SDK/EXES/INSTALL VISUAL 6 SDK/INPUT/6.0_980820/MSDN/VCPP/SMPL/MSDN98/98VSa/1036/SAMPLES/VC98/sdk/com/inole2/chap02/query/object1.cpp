/*
 * OBJECT1.CPP
 *
 * Object implementation using interface implementations.
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
 * CreateObject1
 *
 * Purpose:
 *  Creates an instance of CObject1 returning an IUnknown
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

BOOL CreateObject1(IUnknown **ppUnk)
    {
    HRESULT     hr;
    CObject1   *pObj;

    if (NULL==ppUnk)
        return FALSE;

    //Create the new object, which gives us a C++ object pointer
    pObj=new CObject1();

    if (NULL==pObj)
        return FALSE;

    if (!pObj->Init())
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
 * CObject1::CObject1
 * CObject1::~CObject1
 *
 * Constructor Parameters:
 *  None
 */

CObject1::CObject1(void)
    {
    m_cRef=0;

    m_pImpISampleOne=NULL;
    m_pImpISampleTwo=NULL;

    return;
    }

CObject1::~CObject1(void)
    {
    //Delete the interface implementations created in Init
    DeleteInterfaceImp(m_pImpISampleTwo);
    DeleteInterfaceImp(m_pImpISampleOne);
    return;
    }



/*
 * CObject1::Init
 *
 * Purpose:
 *  Instantiates the interface implementations for this object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeds, FALSE otherwise.
 */

BOOL CObject1::Init(void)
    {
    /*
     * Creating the interfaces means creating instances of
     * the interface implementation classes.  The constructor
     * parameters is a pointer to CObject1 that has the
     * IUnknown functions to which the interface implementations
     * delegate.
     */

    m_pImpISampleOne=new CImpISampleOne(this);

    if (NULL==m_pImpISampleOne)
        return FALSE;

    m_pImpISampleTwo=new CImpISampleTwo(this);

    if (NULL==m_pImpISampleTwo)
        return FALSE;

    return TRUE;
    }






/*
 * CObject1::QueryInterface
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

STDMETHODIMP CObject1::QueryInterface(REFIID riid, PPVOID ppv)
    {
    //Always NULL the out-parameters
    *ppv=NULL;

    /*
     * IUnknown comes from CObject1.  Note that here and in
     * the lines below we do not need to explicitly typecast
     * the object pointers into interface pointers because
     * the vtables are identical.  If we had additional virtual
     * member functions in the object, we would have to cast
     * in order to set the right vtable.  This is demonstrated
     * in the multiple-inheritance version, CObject3.
     */
    if (IID_IUnknown==riid)
        *ppv=this;

    //Other interfaces come from interface implementations
    if (IID_ISampleOne==riid)
        *ppv=m_pImpISampleOne;

    if (IID_ISampleTwo==riid)
        *ppv=m_pImpISampleTwo;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    //AddRef any interface we'll return.
    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }



/*
 * CObject1::AddRef
 * CObject1::Release
 *
 * Reference counting members.  When Release sees a zero count
 * the object destroys itself.
 */

DWORD CObject1::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CObject1::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




//CImpISampleOne interface implementation


/*
 * CImpISampleOne::CImpISampleOne
 * CImpISampleOne::~CImpISampleOne
 *
 * Constructor Parameters:
 *  pObj            PCObject1 to the outer object
 */

CImpISampleOne::CImpISampleOne(PCObject1 pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CImpISampleOne::~CImpISampleOne(void)
    {
    return;
    }



/*
 * CImpISampleOne::QueryInterface
 * CImpISampleOne::AddRef
 * CImpISampleOne::Release
 *
 * IUnknown members that delegate to m_pObj
 */

STDMETHODIMP CImpISampleOne::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CImpISampleOne::AddRef(void)
    {
    /*
     * We maintain an "interface reference count" for debugging
     * purposes, because the client of an object should match
     * AddRef and Release calls through each interface pointer.
     */
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CImpISampleOne::Release(void)
    {
    /*
     * m_cRef is again only for debugging.  It doesn't affect
     * CObject1 although the call to m_pObj->Release does.
     */
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CImpISampleOne::GetMessage
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

STDMETHODIMP CImpISampleOne::GetMessage(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szMessage))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szMessage);
    return NOERROR;
    }







//CImpISampleTwo interface implementation


/*
 * CImpISampleTwo::CImpISampleTwo
 * CImpISampleTwo::~CImpISampleTwo
 *
 * Constructor Parameters:
 *  pObj            PCObject1 to the outer object
 */

CImpISampleTwo::CImpISampleTwo(PCObject1 pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CImpISampleTwo::~CImpISampleTwo(void)
    {
    return;
    }



/*
 * CImpISampleTwo::QueryInterface
 * CImpISampleTwo::AddRef
 * CImpISampleTwo::Release
 *
 * IUnknown members that delegate to m_pObj
 */

STDMETHODIMP CImpISampleTwo::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CImpISampleTwo::AddRef(void)
    {
    /*
     * We maintain an "interface reference count" for debugging
     * purposes, because the client of an object should match
     * AddRef and Release calls through each interface pointer.
     */
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CImpISampleTwo::Release(void)
    {
    /*
     * m_cRef is again only for debugging.  It doesn't affect
     * CObject1 although the call to m_pObj->Release does.
     */
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CImpISampleTwo::GetString
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

STDMETHODIMP CImpISampleTwo::GetString(LPTSTR psz, UINT cch)
    {
    if (NULL==psz)
        return ResultFromScode(E_POINTER);

    if (cch < (UINT)lstrlen(szString))
        return ResultFromScode(E_OUTOFMEMORY);

    lstrcpy(psz, szString);
    return NOERROR;
    }
