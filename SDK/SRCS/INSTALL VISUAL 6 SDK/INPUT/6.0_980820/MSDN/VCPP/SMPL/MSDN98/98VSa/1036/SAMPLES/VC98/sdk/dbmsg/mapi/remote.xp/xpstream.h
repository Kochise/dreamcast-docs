///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPSTREAM.H
//
//  Description
//      Interface declaraction file for CCachedStream.
//
//  Author
//      Irving De la Cruz
//
//  Note: This file is the C++ version of the buffered IStream wrapper
//        developed originally for the C-based MSPEER transport in
//        the MAPI SDK samples.
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#ifndef _XPSTREAM_H
#define _XPSTREAM_H

#define STRICT
#include <WINDOWS.H>
#include <MAPIWIN.H>
#include <MAPISPI.H>
#include <MAPIUTIL.H>

#define XPSOF_BUFF_MAX      4096
#define XPSOF_READ          0x00000001
#define XPSOF_WRITE         0x00000002
#define XPSOF_READWRITE     (XPSOF_WRITE | XPSOF_READ)

class CCachedStream : public IStream
{
public:
///////////////////////////////////////////////////////////////////////////////
// IUnknown virtual member functions
//
    inline STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj)
                    { *ppvObj = NULL;
                      if (riid == IID_IStream || riid == IID_IUnknown)
                      {
                          *ppvObj = (LPVOID)this;
                          // Increase usage count of this object
                          AddRef();
                          return S_OK;
                      }
                      return E_NOINTERFACE;
                    };
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
///////////////////////////////////////////////////////////////////////////////
// IStream virtual member functions
//
    STDMETHODIMP Read
                    (void *                     pv,
                     ULONG                      cb,
                     ULONG *                    pcbRead);
    STDMETHODIMP Write
                    (const void *               pv,
                     ULONG                      cb,
                     ULONG *                    pcbWritten);
    STDMETHODIMP Seek
                    (LARGE_INTEGER              dlibMove,
                     DWORD                      dwOrigin,
                     ULARGE_INTEGER *           plibNewPosition);
    STDMETHODIMP CopyTo
                    (IStream *                  pstm,
                     ULARGE_INTEGER cb,
                     ULARGE_INTEGER *           pcbRead,
                     ULARGE_INTEGER *           pcbWritten);
    STDMETHODIMP Commit
                    (DWORD                      grfCommitFlags);
    inline STDMETHODIMP SetSize
                    (ULARGE_INTEGER             libNewSize)
                     { return m_pImpStream->SetSize (libNewSize); };
    inline STDMETHODIMP Revert
                    ()
                     { return m_pImpStream->Revert(); };
    inline STDMETHODIMP LockRegion
                    (ULARGE_INTEGER             libOffset,
                     ULARGE_INTEGER             cb,
                     DWORD                      dwLockType)
                     { return m_pImpStream->LockRegion (libOffset, cb, dwLockType); };
    inline STDMETHODIMP UnlockRegion
                    (ULARGE_INTEGER             libOffset,
                     ULARGE_INTEGER             cb,
                     DWORD                      dwLockType)
                     { return m_pImpStream->UnlockRegion (libOffset, cb, dwLockType); };
    inline STDMETHODIMP Stat
                    (STATSTG *                  pstatstg,
                     DWORD                      grfStatFlag)
                     { return m_pImpStream->Stat (pstatstg, grfStatFlag); };
    inline STDMETHODIMP Clone
                    (IStream **                 ppstm)
                     { return m_pImpStream->Clone (ppstm); };

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this class
//
private:
    HRESULT WINAPI RewindStream
                    (ULONG                      ib);
    
///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
public :
    CCachedStream   (LPSTREAM                   pImpStream,
                     DWORD                      ulFlags);
    ~CCachedStream  ();

///////////////////////////////////////////////////////////////////////////////
// Data members
public :
    ULONG               m_cRef;
    BOOL                m_fDirty;
    LPSTREAM            m_pImpStream;
    ULONG               m_ulFlags;
    LPVOID              m_pvCache;
    ULONG               m_libBuff;
    ULONG               m_cbBuffMac;
};

#endif // _XPSTREAM_H

// End of file for XPSTREAM.H
