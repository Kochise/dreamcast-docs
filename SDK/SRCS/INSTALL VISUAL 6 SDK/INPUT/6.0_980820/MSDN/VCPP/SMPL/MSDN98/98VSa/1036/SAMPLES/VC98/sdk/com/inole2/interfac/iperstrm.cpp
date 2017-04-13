/*
 * IPERSTRM.CPP
 *
 * Template IPersistStream interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iperstrm.h"


/*
 * CImpIPersistStream:CImpIPersistStream
 * CImpIPersistStream::~CImpIPersistStream
 *
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStream::CImpIPersistStream(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPersistStream::~CImpIPersistStream(void)
    {
    return;
    }



/*
 * CImpIPersistStream::QueryInterface
 * CImpIPersistStream::AddRef
 * CImpIPersistStream::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistStream.
 */

STDMETHODIMP CImpIPersistStream::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersistStream::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersistStream::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIPersistStream::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 */

STDMETHODIMP CImpIPersistStream::GetClassID(LPCLSID pClsID)
    {
    return NOERROR;
    }





/*
 * CImpIPersistStream::IsDirty
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

STDMETHODIMP CImpIPersistStream::IsDirty(void)
    {
    return ResultFromScode(S_FALSE);
    }







/*
 * CImpIPersistStream::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStream that was handled by Save in another object lifetime.
 *  The seek pointer in this stream will be exactly the same as
 *  it was when Save was called, and this function must leave
 *  the seek pointer the same as it was on exit from Save, regardless
 *  of success or failure.  This function should not hold on to
 *  pIStream.
 *
 * Parameters:
 *  pIStream        LPSTREAM from which to load.
 */

STDMETHODIMP CImpIPersistStream::Load(LPSTREAM pIStream)
    {
    return NOERROR;
    }





/*
 * CImpIPersistStream::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStream.  Be sure not
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

STDMETHODIMP CImpIPersistStream::Save(LPSTREAM pIStream
    , BOOL fClearDirty)
    {
    return NOERROR;
    }








/*
 * CImpIPersistStream::GetSizeMax
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

STDMETHODIMP CImpIPersistStream::GetSizeMax(ULARGE_INTEGER
    *pcbSize)
    {
    return NOERROR;
    }
