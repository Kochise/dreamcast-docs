/*
 -  X P S O F . H
 -
 *  Purpose:
 *      Wraps the StreamOnFile object to add buffering of the stream.
 *      The wrappered version uses an in-memory buffer, or cache, to 
 *      reduce the number of actual Reads and Writes to the underlying 
 *      stream.  The goal is, obviously, to improve performance.  
 *
 *  Copyright 1992-1995, Microsoft Corporation.  All Rights Reserved.
 */


#define XPSOF_BUFF_MAX      ((ULONG) 1024)

#define XPSOF_READ          ((ULONG) 0x00000001)
#define XPSOF_WRITE         ((ULONG) 0x00000002)
#define XPSOF_READWRITE     ((ULONG) 0x00000003)

/* Creates the wrapped SOF object */

STDMETHODIMP HrWrapStreamOnFile(
    LPALLOCATEBUFFER    lpAllocBuffer,
    LPFREEBUFFER        lpFreeBuffer,
    ULONG               ulFlags,
    LPSTREAM            lpStream,
    LPSTREAM *          lppWrappedStream);


/* IStream Interface */

#define MAPI_ISTREAM_METHODS(IPURE)                                     \
    MAPIMETHOD(Read)                                                    \
        (THIS_  VOID HUGEP *                lpv,                        \
                ULONG                       cb,                         \
                ULONG FAR *                 lpcbRead) IPURE;            \
    MAPIMETHOD(Write)                                                   \
        (THIS_  VOID const HUGEP *          lpv,                        \
                ULONG                       cb,                         \
                ULONG FAR *                 lpcbWritten) IPURE;         \
    MAPIMETHOD(Seek)                                                    \
        (THIS_  LARGE_INTEGER               libMove,                    \
                DWORD                       dwOrigin,                   \
                ULARGE_INTEGER FAR *        lplibNewPosition) IPURE;    \
    MAPIMETHOD(SetSize)                                                 \
        (THIS_  ULARGE_INTEGER              libNewSize) IPURE;          \
    MAPIMETHOD(CopyTo)                                                  \
        (THIS_  IStream FAR *               lpstm,                      \
                ULARGE_INTEGER              cb,                         \
                ULARGE_INTEGER FAR *        lpcbRead,                   \
                ULARGE_INTEGER FAR *        lpcbWritten) IPURE;         \
    MAPIMETHOD(Commit)                                                  \
        (THIS_  DWORD                       dwCommitFlags) IPURE;       \
    MAPIMETHOD(Revert)                                                  \
        (THIS)                              IPURE;                      \
    MAPIMETHOD(LockRegion)                                              \
        (THIS_  ULARGE_INTEGER              libOffset,                  \
                ULARGE_INTEGER              cb,                         \
                DWORD                       dwLockType) IPURE;          \
    MAPIMETHOD(UnlockRegion)                                            \
        (THIS_  ULARGE_INTEGER              ulibOffset,                 \
                ULARGE_INTEGER              cb,                         \
                DWORD                       dwLockType) IPURE;          \
    MAPIMETHOD(Stat)                                                    \
        (THIS_  STATSTG FAR *               lpstatstg,                  \
                DWORD                       dwStatFlag) IPURE;          \
    MAPIMETHOD(Clone)                                                   \
        (THIS_  IStream FAR * FAR *         lppstm) IPURE;              \


/* Interface declaration */

#undef  INTERFACE
#define INTERFACE struct _XPSOF
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, XPSOF_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_ISTREAM_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, XPSOF_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_ISTREAM_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(XPSOF_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_ISTREAM_METHODS(IMPL)
};

typedef struct _XPSOF
{
    XPSOF_Vtbl *        lpVtbl;
    LONG                lcInit;
    ULONG               ulFlags;
    LPSTREAM            lpstrm;
    LPVOID              lpvBuff;
    ULONG               libBuff;
    ULONG               cbBuffMac;
    BOOL                fDirty;
    LPFREEBUFFER        FreeBuffer;

} XPSOF, FAR * LPXPSOF;
