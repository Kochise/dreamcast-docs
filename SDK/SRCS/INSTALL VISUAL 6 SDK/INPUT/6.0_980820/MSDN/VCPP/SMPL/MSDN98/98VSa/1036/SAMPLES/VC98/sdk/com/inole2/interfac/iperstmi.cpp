/*
 * IPERSTMI.CPP
 *
 * Template IPersistStreamInitInit interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iperstmi.h"


/*
 * CImpIPersistStreamInit:CImpIPersistStreamInit
 * CImpIPersistStreamInit::~CImpIPersistStreamInit
 *
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStreamInit::CImpIPersistStreamInit(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPersistStreamInit::~CImpIPersistStreamInit(void)
    {
    return;
    }



/*
 * CImpIPersistStreamInit::QueryInterface
 * CImpIPersistStreamInit::AddRef
 * CImpIPersistStreamInit::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistStreamInit.
 */

STDMETHODIMP CImpIPersistStreamInit::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistStreamInit::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistStreamInit::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIPersistStreamInit::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 */

STDMETHODIMP CImpIPersistStreamInit::GetClassID(LPCLSID pClsID)
    {
    return NOERROR;
    }





/*
 * CImpIPersistStreamInit::IsDirty
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

STDMETHODIMP CImpIPersistStreamInit::IsDirty(void)
    {
    return ResultFromScode(S_FALSE);
    }







/*
 * CImpIPersistStreamInit::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStreamInit that was handled by Save in another object lifetime.
 *  The seek pointer in this stream will be exactly the same as
 *  it was when Save was called, and this function must leave
 *  the seek pointer the same as it was on exit from Save, regardless
 *  of success or failure.  This function should not hold on to
 *  pIStream.
 *
 *  This function is called in lieu of IPersistStreamInit::InitNew
 *  when the object already has a persistent state.
 *
 * Parameters:
 *  pIStream        LPSTREAM from which to load.
 */

STDMETHODIMP CImpIPersistStreamInit::Load(LPSTREAM pIStream)
    {
    return NOERROR;
    }





/*
 * CImpIPersistStreamInit::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStreamInit.  Be sure not
 *  to change the position of the seek pointer on entry to this
 *  function: the caller will assume that you write from the
 *  current offset.  Leave the stream's seek pointer at the end
 *  of the data written on exit.
 *
 * Parameters:
 *  pIStream        LPSTREAM in which to save our data.
 *  fClearDirty     BOOL indicating if this call should clear
 *                  the object's dirty flag (TRUE) or leave it
 *                  unchanged (FALSE).
 */

STDMETHODIMP CImpIPersistStreamInit::Save(LPSTREAM pIStream
    , BOOL fClearDirty)
    {
    return NOERROR;
    }








/*
 * CImpIPersistStreamInit::GetSizeMax
 *
 * Purpose:
 *  Returns the size of the data we would write if Save was
 *  called right now.
 *
 * Parameters:
 *  pcbSize         ULARGE_INTEGER * in which to save the size
 *                  of the stream an immediate call to Save would
 *                  write.
 */

STDMETHODIMP CImpIPersistStreamInit::GetSizeMax(ULARGE_INTEGER
    *pcbSize)
    {
    return NOERROR;
    }




/*
 * CImpIPersistStreamInit::InitNew
 *
 * Purpose:
 *  Informs the object that it is being created new instead of
 *  loaded from a persistent state.  This will be called in lieu
 *  of IPersistStreamInit::Load.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIPersistStreamInit::InitNew(void)
    {
    return NOERROR;
    }
