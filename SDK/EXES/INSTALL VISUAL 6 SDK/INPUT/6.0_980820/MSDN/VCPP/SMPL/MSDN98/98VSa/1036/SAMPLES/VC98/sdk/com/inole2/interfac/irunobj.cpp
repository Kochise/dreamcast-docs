/*
 * IRUNOBJ.CPP
 *
 * Definitions of a template IRunnableObject interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "irunobj.h"


/*
 * CImpIRunnableObject::CImpIRunnableObject
 * CImpIRunnableObject::~CImpIRunnableObject
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIRunnableObject::CImpIRunnableObject(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIRunnableObject::~CImpIRunnableObject(void)
    {
    return;
    }



/*
 * CImpIRunnableObject::QueryInterface
 * CImpIRunnableObject::AddRef
 * CImpIRunnableObject::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIRunnableObject.
 */

STDMETHODIMP CImpIRunnableObject::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIRunnableObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIRunnableObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIRunnableObject::GetRunningClass
 *
 * Purpose:
 *  Returns the CLSID of the object.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store the CLSID.
 */

STDMETHODIMP CImpIRunnableObject::GetRunningClass(LPCLSID pClsID)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIRunnableObject::Run
 *
 * Purpose:
 *  Run an object in the given bind context, that is, put the object
 *  into the running state.
 *
 * Parameters:
 *  pBindCtx        LPBINDCTX of the bind context to use.
 */

STDMETHODIMP CImpIRunnableObject::Run(LPBINDCTX pBindCtx)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIRunnableObject::IsRunning
 *
 * Purpose:
 *  Answers whether an object is currently in the running state.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            Indicates the running state of the object.
 */

STDMETHODIMP_(BOOL) CImpIRunnableObject::IsRunning(void)
    {
    return FALSE;
    }






/*
 * CImpIRunnableObject::LockRunning
 *
 * Purpose:
 *  Locks an already running object into the running state or unlocks
 *  it from such a state.
 *
 * Parameters:
 *  fLock               BOOL indicating lock (TRUE) or unlock
 *                      (FALSE)
 *  fLastUnlockCloses   BOOL indicating if the last call to this
 *                      function with fLock==FALSE closes the
 *                      object.
 */

STDMETHODIMP CImpIRunnableObject::LockRunning(BOOL fLock
    , BOOL fLastUnlockCloses)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIRunnableObject::SetContainedObject
 *
 * Purpose:
 *  Informs the object (embedded object) that it is inside a
 *  compound document container.
 *
 * Parameters:
 *  fContained      BOOL indicating if the object is now contained.
 */

STDMETHODIMP CImpIRunnableObject::SetContainedObject(BOOL fContained)
    {
    return ResultFromScode(E_NOTIMPL);
    }
