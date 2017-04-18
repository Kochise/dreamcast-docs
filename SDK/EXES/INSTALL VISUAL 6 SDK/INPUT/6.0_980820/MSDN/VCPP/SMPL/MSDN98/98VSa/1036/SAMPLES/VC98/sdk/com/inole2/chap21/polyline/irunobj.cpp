/*
 * IRUNOBJ.CPP
 * Polyline Component Chapter 21
 *
 * Implementation of the IRunnableObject interface which allows
 * us to enter the "running" state which means Polyline's dialog
 * box is created, but not visible.  This is necessary so that
 * containers can ask for our extents before calling DoVerb.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIRunnableObject::CImpIRunnableObject
 * CImpIRunnableObject::~CImpIRunnableObject
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIRunnableObject::CImpIRunnableObject(PCPolyline pObj
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIRunnableObject::GetRunningClass(LPCLSID pClsID)
    {
    *pClsID=m_pObj->m_clsID;
    return NOERROR;
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIRunnableObject::Run(LPBINDCTX pBindCtx)
    {
    /*
     * Create the dialog but not show it.  This function is called
     * from OleRun which is called from within OleCreate.  So when
     * a container creates this object, we'll create the dialog
     * which is a basis for the object's extents (as returned from
     * IViewObject2::GetExtent.  Our IOleObject::DoVerb will later
     * note that the dialog is already created and will just make
     * it visible and not create it anew.
     *
     * Note that the dialog is unowned--it acts like an overlapped
     * window.
     */

    if (NULL!=m_pObj->m_hDlg)
        return NOERROR;

    //This stores the dialog handle in m_pObj.
    CreateDialogParam(m_pObj->Instance()
        , MAKEINTRESOURCE(IDD_EDITDIALOG), NULL, PolyDlgProc
        , (LPARAM)m_pObj);

    if (NULL==m_pObj->m_hDlg)
        return ResultFromScode(E_OUTOFMEMORY);

    //CHAPTER21MOD
    /*
     * Registration of the object as running happens in
     * IOleObject::SetClientSite since we need a moniker from
     * the container and we don't have a client site pointer yet.
     */
    //End CHAPTER21MOD

    return NOERROR;
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
    return (NULL!=m_pObj->m_hDlg);
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIRunnableObject::LockRunning(BOOL fLock
    , BOOL fLastUnlockCloses)
    {
    //Calling CoLockObjectExternal is all we have to do here.
    return CoLockObjectExternal(this, fLock, fLastUnlockCloses);
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
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIRunnableObject::SetContainedObject(BOOL fContained)
    {
    //We can ignore this.
    return NOERROR;
    }
