#ifndef __MEMSTM_H              // guard against multiple inclusion
#define __MEMSTM_H

/********************************************************************
 * memstm.h
 *
 * Description
 *    CMemoryStream
 ********************************************************************/

/********************************************************************
 * class CMemoryStream
 *
 * Description
 *    Memory buffer with the IStream interface to allow COM objects
 *    to write or read to the memory buffer.
 ********************************************************************/

class CMemoryStream : public IStream
{
    public:
        CMemoryStream(void);
        virtual ~CMemoryStream(void);

        // IUnknown methods
        STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppvObj);
        STDMETHOD_(ULONG, AddRef)(void);
        STDMETHOD_(ULONG, Release)(void);

        // IStream methods
        STDMETHOD(Read)(LPVOID pv, ULONG cb, ULONG *pcbRead);
        STDMETHOD(Write)(const void *pv, ULONG cb, ULONG *pcbWritten);
        STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
        STDMETHOD(SetSize)(ULARGE_INTEGER libNewSize);
        STDMETHOD(CopyTo)(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
        STDMETHOD(Commit)(DWORD grfCommitFlags);
        STDMETHOD(Revert)(void);
        STDMETHOD(LockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
        STDMETHOD(UnlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
        STDMETHOD(Stat)(STATSTG *pstatstg, DWORD grfStatFlag);
        STDMETHOD(Clone)(IStream **ppStm);

    private:
        // Internal functions
        HRESULT GrowBuffer(long lSize);

        ULONG  _ulRefs;         // reference count of object
        long   _lCurPos;        // current position in memory buffer
        long   _cbBuf;          // size of memory buffer (used size)
        long   _cbSize;         // size of memory buffer (actual allocated size)
        BYTE * _pbBuf;          // memory buffer
};

#endif // __MEMSTM_H
