/*
 * ILOCKBYT.H
 *
 * Definitions of a template ILockBytes interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ILOCKBYT_H_
#define _ILOCKBYT_H_

#include <inole.h>

class CImpILockBytes;
typedef class CImpILockBytes *PCImpILockBytes;

class CImpILockBytes : public ILockBytes
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //Fr delegation

    public:
        CImpILockBytes(LPVOID, LPUNKNOWN);
        ~CImpILockBytes(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ReadAt(ULARGE_INTEGER, VOID HUGEP *, ULONG
            , ULONG *);
        STDMETHODIMP WriteAt(ULARGE_INTEGER, VOID const HUGEP *
            , ULONG, ULONG *);
        STDMETHODIMP Flush(void);
        STDMETHODIMP SetSize(ULARGE_INTEGER);
        STDMETHODIMP LockRegion(ULARGE_INTEGER, ULARGE_INTEGER
            , DWORD);
        STDMETHODIMP UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER
            , DWORD);
        STDMETHODIMP Stat(STATSTG *, DWORD);
    };


#endif //_ILOCKBYT_H_
