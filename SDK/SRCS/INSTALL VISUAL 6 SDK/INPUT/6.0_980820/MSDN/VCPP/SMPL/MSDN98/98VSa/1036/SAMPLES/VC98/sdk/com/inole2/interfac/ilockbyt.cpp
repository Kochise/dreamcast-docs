/*
 * ILOCKBYT.H
 *
 * Template ILockBytes interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ilockbyt.h"


/*
 * CImpILockBytes::CImpILockBytes
 * CImpILockBytes::~CImpILockBytes
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpILockBytes::CImpILockBytes(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpILockBytes::~CImpILockBytes(void)
    {
    return;
    }



/*
 * CImpILockBytes::QueryInterface
 * CImpILockBytes::AddRef
 * CImpILockBytes::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpILockBytes.
 */

STDMETHODIMP CImpILockBytes::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpILockBytes::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpILockBytes::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }







/*
 * CImpILockBytes::ReadAt
 *
 * Purpose:
 *  Reads bytes from the byte array starting at a specific position.
 *
 * Parameters:
 *  ulOffset        ULARGE_INTEGER specifying the offset at which
 *                  to read.
 *  pv              void HUGEP * into which to read the information.
 *  cb              ULONG number of bytes to read
 *  pcbRead         ULONG * in which to store the number of bytes
 *                  read
 */

STDMETHODIMP ReadAt(ULARGE_INTEGER ulOffset, VOID HUGEP *pv
    , ULONG cb, ULONG *pcbRead)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpILockBytes::WriteAt
 *
 * Purpose:
 *  Writes bytes into the byte array starting at a specific position.
 *
 * Parameters:
 *  ulOffset        ULARGE_INTEGER specifying the offset at which
 *                  to write.
 *  pv              void HUGEP * to the information to write.
 *  cb              ULONG number of bytes to write
 *  pcbWritten      ULONG * in which to store the number of bytes
 *                  written.
 */

STDMETHODIMP WriteAt(ULARGE_INTEGER ulOffset, VOID HUGEP *pv
    , ULONG cb, ULONG *pcbWritten)
    {
    return ResultFromScode(E_NOTIMPL);
    }







/*
 * CImpILockBytes::Flush
 *
 * Purpose:
 *  Insures that any internal buffers are written to the underlying
 *  storage.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP Flush(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpILockBytes::SetSize
 *
 * Purpose:
 *  Changes the size of the byte array.
 *
 * Parameters:
 *  cb              ULARGE_INTEGER specifying the size to set.
 */

STDMETHODIMP SetSize(ULARGE_INTEGER cb)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpILockBytes::LockRegion
 *
 * Purpose:
 *  Locks a range of bytes in the byte array.
 *
 * Parameters:
 *  libOffset       ULARGE_INTEGER at which to start the lock.
 *  cb              ULARGE_INTEGER number of bytes to lock.
 *  dwLockType      DWORD the type of lock access.
 */

STDMETHODIMP LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb
    , DWORD dwLockType)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpILockBytes::UnlockRegion
 *
 * Purpose:
 *  Unlocks a range of bytes in the byte array.
 *
 * Parameters:
 *  libOffset       ULARGE_INTEGER at which to start the unlock.
 *  cb              ULARGE_INTEGER number of bytes to unlock.
 *  dwLockType      DWORD the type of lock access.
 */


STDMETHODIMP UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb
    , DWORD dwLockType)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpILockBytes::Stat
 *
 * Purpose:
 *  Returns relevant statistics about the byte array.
 *
 * Parameters:
 *  pstatstg        LPSTATSTG in which to store the statistics.
 *  grfStatFlag     DWORD specifying the level of information
 *                  requested.
 */

STDMETHODIMP Stat(STATSTG *pstatstg, DWORD grfStatFlag)
    {
    return ResultFromScode(E_NOTIMPL);
    }
