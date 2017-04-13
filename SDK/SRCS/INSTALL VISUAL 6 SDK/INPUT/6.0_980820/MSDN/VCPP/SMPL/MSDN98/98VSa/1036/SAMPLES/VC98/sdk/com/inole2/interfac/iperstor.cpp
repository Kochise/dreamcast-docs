/*
 * IPERSTOR.CPP
 *
 * Template IPersistStorage interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iperstor.h"


/*
 * CImpIPersistStorage:CImpIPersistStorage
 * CImpIPersistStorage::~CImpIPersistStorage
 *
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStorage::CImpIPersistStorage(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    m_psState=PSSTATE_UNINIT;
    return;
    }

CImpIPersistStorage::~CImpIPersistStorage(void)
    {
    return;
    }



/*
 * CImpIPersistStorage::QueryInterface
 * CImpIPersistStorage::AddRef
 * CImpIPersistStorage::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistStorage.
 */

STDMETHODIMP CImpIPersistStorage::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistStorage::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistStorage::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }








/*
 * CImpIPersistStorage::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 */

STDMETHODIMP CImpIPersistStorage::GetClassID(LPCLSID pClsID)
    {
    if (PSSTATE_UNINIT==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    return NOERROR;
    }





/*
 * CImpIPersistStorage::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this object since
 *  it was loaded or initialized new.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Contains S_OK if we ARE dirty, S_FALSE if
 *                  NOT dirty.
 */

STDMETHODIMP CImpIPersistStorage::IsDirty(void)
    {
    if (PSSTATE_UNINIT==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    return ResultFromScode(S_FALSE);
    }





/*
 * CImpIPersistStorage::InitNew
 *
 * Purpose:
 *  Provides the object with the IStorage to hold on to while the
 *  object is running.  Here we initialize the structure of the
 *  storage and AddRef it for incremental access. This function will
 *  only be called once in the object's lifetime in lieu of Load.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE for the object.
 */

STDMETHODIMP CImpIPersistStorage::InitNew(LPSTORAGE pIStorage)
    {
    if (PSSTATE_UNINIT!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    m_psState=PSSTATE_SCRIBBLE;

    //Hold on to pIStorage for Save(..., TRUE)
    return NOERROR;
    }





/*
 * CImpIPersistStorage::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStorage that was handled by Save in another object lifetime.
 *  This function will only be called once in the object's lifetime
 *  in lieu of InitNew. The object should hold on to pIStorage here
 *  for incremental access and low-memory saves in Save.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE from which to load.
 */

STDMETHODIMP CImpIPersistStorage::Load(LPSTORAGE pIStorage)
    {
    if (PSSTATE_UNINIT!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    m_psState=PSSTATE_SCRIBBLE;

    //Hold on to pIStorage for Save(..., TRUE)
    return NOERROR;
    }








/*
 * CImpIPersistStorage::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStorage which may
 *  or may not be the same as the one previously passed to
 *  Load, indicated with fSameAsLoad.  After this call we may
 *  not write into the storage again until SaveCompleted is
 *  called, although we may still read.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE in which to save our data.
 *  fSameAsLoad     BOOL indicating if this is the same pIStorage
 *                  that was passed to Load.  If TRUE, then the
 *                  object should write whatever it has *without
 *                  *using any extra memory* as this may be a low
 *                  memory save attempt.  That means that you must
 *                  not try to open or create streams.  If FALSE
 *                  you need to regenerate your whole storage
 *                  structure, being sure to also release any
 *                  pointers held from InitNew and Load.
 */

STDMETHODIMP CImpIPersistStorage::Save(LPSTORAGE pIStorage
    , BOOL fSameAsLoad)
    {
    //Have to come here from scribble state.
    if (PSSTATE_SCRIBBLE!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * Save your data to your open storages and streams if
     * fSameAsLoad is FALSE, otherwise save to the new pIStorage
     * but don't change your held pointers--you only do that in
     * SaveCompleted if given a different pIStorage.
     *
     * Also, do not call pIStorage->Commit.  That's the caller's
     * responsibility.
     */

    m_psState=PSSTATE_ZOMBIE;

    //Clear your dirty flag.
    return NOERROR;
    }








/*
 * CImpIPersistStorage::SaveCompleted
 *
 * Purpose:
 *  Notifies the object that the storage in pIStorage has been
 *  completely saved now.  This is called when the user of this
 *  object wants to save us in a completely new storage, and if
 *  we normally hang on to the storage we have to reinitialize
 *  ourselves here for this new one that is now complete.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE of the new storage in which we live.
 */

STDMETHODIMP CImpIPersistStorage::SaveCompleted(LPSTORAGE pIStorage)
    {
    //Must be called in no-scribble or hands-off state
    if (PSSTATE_ZOMBIE!=m_psState || PSSTATE_HANDSOFF!=m_psState)
        return ResultFromScode(E_UNEXPECTED);

    //If we're coming from Hands-Off, we'd better get a storage
    if (NULL==pIStorage && PSSTATE_HANDSOFF==m_psState)
        return ResultFromScode(E_UNEXPECTED);

    /*
     * If in Hands-Off state and pIStorage is non-NULL, then
     * reopen storages and streams and hold the pointers,
     * returning to scribble state.
     *
     * If in no-scribble state and pIStorage is non-NULL, then
     * release currently held pointers and reopen pointers
     * in pIStorage.
     *
     * If in no-scribble state and pIStorage is NULL, do not
     * change your held pointers.
     */

    //Return to scribble if there are no errors
    m_psState=PSSTATE_SCRIBBLE;
    return NOERROR;
    }








/*
 * CImpIPersistStorage::HandsOffStorage
 *
 * Purpose:
 *  Instructs the object that another agent is interested in having
 *  total access to the storage we might be hanging on to from
 *  InitNew or SaveCompleted.  In this case we must release our hold
 *  and await another call to SaveCompleted before we have a hold
 *  again.  Therefore we cannot read or write after this call until
 *  SaveCompleted.
 *
 *  Situations where this might happen arise in compound document
 *  scenarios where this object might be in-place active but the
 *  application wants to rename and commit the root storage.
 *  Therefore we are asked to close our hold, let the container
 *  party on the storage, then call us again later to tell us the
 *  new storage we can hold.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIPersistStorage::HandsOffStorage(void)
    {
    /*
     * Must come from scribble or no-scribble.  A repeated call
     * to HandsOffStorage is an unexpected error (bug in client).
     */
    if (PSSTATE_UNINIT==m_psState || PSSTATE_HANDSOFF==m_psState)
        return ResultFromScode(E_UNEXPECTED);


    /*
     * Release all held pointers regardless.
     */

    m_psState=PSSTATE_HANDSOFF;
    return NOERROR;
    }
