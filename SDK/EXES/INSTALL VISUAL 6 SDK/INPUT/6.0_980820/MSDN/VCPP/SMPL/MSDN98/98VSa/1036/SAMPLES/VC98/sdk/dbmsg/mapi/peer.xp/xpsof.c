/*
 -  X P S O F . C
 -
 *  Purpose:
 *      Wraps the StreamOnFile object to add buffering of the stream.
 *      The wrappered version uses an in-memory buffer, or cache, to
 *      reduce the number of actual Reads and Writes to the underlying
 *      stream.  The goal is, obviously, to improve performance.
 *      Note: This code is not thread safe.  Also, the implementation
 *      is not optimized for streams that both read and write continuously
 *      because there will be too much flushing going on.
 *
 *  Copyright 1992-1995, Microsoft Corporation.  All Rights Reserved.
 */


#include "xppch.h"
#include "xpsof.h"

/* Private support function */

HRESULT HrRewindStream(LPXPSOF, ULONG);
VOID    HMemCopy(VOID HUGEP * lpvDst, VOID HUGEP * lpvSrc, ULONG cb);


XPSOF_Vtbl VtblXPSOF =
{
    XPSOF_QueryInterface,
    XPSOF_AddRef,
    XPSOF_Release,
    XPSOF_Read,
    XPSOF_Write,
    XPSOF_Seek,
    XPSOF_SetSize,
    XPSOF_CopyTo,
    XPSOF_Commit,
    XPSOF_Revert,
    XPSOF_LockRegion,
    XPSOF_UnlockRegion,
    XPSOF_Stat,
    XPSOF_Clone
};


/*
 -  HrWrapStreamOnFile
 -
 *  Purpose:
 *      This function takes a Stream-On-File object and wraps it.  The
 *      process of wrappering involves creating a similar object,
 *      allocating memory for the buffer, AddRefing the original object,
 *      and returning this new object to the caller.
 *
 *  Parameters:
 *      lpAllocBuffer           A MAPI memory allocator function
 *      lpFreeBuffer            The corresponding FreeBuffer function
 *      ulFlags                 XPSOF_READ, XPSOF_WRITE, or XPSOF_READWRITE
 *      lpStream                The original Stream-On-File to be wrapped
 *      lppWrappedStream        The new XPSOF object.
 *
 *  Returns:
 *      HRESULT                 Indicating Success/Failure
 */

STDMETHODIMP
HrWrapStreamOnFile(
    LPALLOCATEBUFFER    lpAllocBuffer,
    LPFREEBUFFER        lpFreeBuffer,
    ULONG               ulFlags,
    LPSTREAM            lpStream,
    LPSTREAM *          lppWrappedStream)
{
    SCODE sc;
    LPXPSOF lpxpsof = NULL;

    /* Allocate the new Stream object */

    sc = lpAllocBuffer(sizeof(XPSOF), (LPVOID *)&lpxpsof);

    if (FAILED(sc))
    {
        DebugTrace("Allocation of XPSOF object failed.\n");
        goto ret;
    }

    /* Init the object */

    lpxpsof->lpVtbl = &VtblXPSOF;
    lpxpsof->lcInit = 1;
    lpxpsof->ulFlags = ulFlags;
    lpxpsof->lpstrm = lpStream;
    lpxpsof->lpvBuff = NULL;
    lpxpsof->libBuff = 0;
    lpxpsof->cbBuffMac = 0;
    lpxpsof->fDirty = FALSE;
    lpxpsof->FreeBuffer = lpFreeBuffer;

    /* Allocate the buffer or cache */

    sc = lpAllocBuffer(XPSOF_BUFF_MAX, (LPVOID *)&lpxpsof->lpvBuff);

    if (FAILED(sc))
    {
        DebugTrace("Allocation of stream buffer failed.\n");
        goto ret;
    }

    /* Now that we've succeeded, AddRef the original object */

    lpStream->lpVtbl->AddRef(lpStream);

    *lppWrappedStream = (LPSTREAM)lpxpsof;

ret:
    if (FAILED(sc))
    {
        if (lpxpsof)
        {
            lpFreeBuffer(lpxpsof->lpvBuff);
            lpFreeBuffer(lpxpsof);
        }
    }

    DebugTraceSc(HrWrapStreamOnFile, sc);
    return ResultFromScode(sc);
}


/*
 -  IUnknown::QueryInterface
 -  IUnknown::AddRef
 -  IUnknown::Release
 -
 *  Purpose:
 *      These are the XPSOF's OLE IUnknown methods.
 */

STDMETHODIMP
XPSOF_QueryInterface(LPXPSOF lpXPSOF, REFIID riid, LPVOID * lppvObj)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        IsBadReadPtr (riid, sizeof(IID)) ||
        IsBadWritePtr (lppvObj, sizeof(LPVOID)))
    {
        DebugTraceSc(XPSOF_QueryInterface, E_INVALIDARG);
        return ResultFromScode (E_INVALIDARG);
    }

    if (memcmp(riid, &IID_IUnknown, sizeof(IID))
        && memcmp(riid, &IID_IStream, sizeof(IID)))
    {
        *lppvObj = NULL;    // OLE requires zeroing [out] parameters
        DebugTraceSc(XPSOF_QueryInterface, E_NOINTERFACE);
        return ResultFromScode (E_NOINTERFACE);
    }

    lpXPSOF->lcInit++;
    *lppvObj = lpXPSOF;

    return hrSuccess;
}


STDMETHODIMP_(ULONG)
XPSOF_AddRef(LPXPSOF lpXPSOF)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_AddRef(), E_INVALIDARG);
        return 1;
    }

    return ++lpXPSOF->lcInit;
}


STDMETHODIMP_(ULONG)
XPSOF_Release (LPXPSOF lpXPSOF)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_Release(), E_INVALIDARG);
        return 1;
    }

    if (--lpXPSOF->lcInit == 0)
    {
        if (lpXPSOF->lpstrm)
            lpXPSOF->lpstrm->lpVtbl->Release(lpXPSOF->lpstrm);

        if (lpXPSOF->lpvBuff)
            lpXPSOF->FreeBuffer(lpXPSOF->lpvBuff);

        lpXPSOF->FreeBuffer(lpXPSOF);

        return 0;
    }

    return lpXPSOF->lcInit;
}


/*
 -  IStream::Read
 -
 *  Purpose:
 *      To read data from the stream.
 */

STDMETHODIMP
XPSOF_Read (LPXPSOF lpXPSOF,
    VOID HUGEP * lpvData,
    ULONG cbSize,
    ULONG * lpcbRead)
{
    HRESULT hr = hrSuccess;
    ULONG cbRead = 0;
    ULONG cbT;
    VOID HUGEP * lpvRead = NULL;

    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        IsBadHugeWritePtr (lpvData, cbSize) ||
        (lpcbRead && IsBadWritePtr (lpcbRead, sizeof(ULONG))))
    {
        hr = ResultFromScode(STG_E_INVALIDPARAMETER);
        goto ret;
    }

    if (!(lpXPSOF->ulFlags & XPSOF_READ))
    {
        hr = ResultFromScode(STG_E_ACCESSDENIED);
        goto ret;
    }

    Assert(lpXPSOF->cbBuffMac >= lpXPSOF->libBuff);

    /* First, flush the buffer if it has been written into.  This     */
    /* operation empties our buffer and zeros the offset and size.    */
    /* We do this because we also buffer writes and we need to force  */
    /* the underlying stream to point to where the caller expects.    */

    if ((lpXPSOF->ulFlags & XPSOF_WRITE) && lpXPSOF->fDirty)
    {
        hr = XPSOF_Commit(lpXPSOF, 0);

        if (HR_FAILED(hr))
            goto ret;
    }

    /* Determine if the buffer is empty (cbT == 0) or not (cbT != 0). */
    /* We consider the buffer empty if we've read past the end of it  */
    /* or if cbBuffMac and libBuff are equal to zero.                 */

    cbT = lpXPSOF->cbBuffMac - lpXPSOF->libBuff;

    /* If the buffer is empty and the caller wants to read less than  */
    /* the size of our buffer, then we'll fill the buffer from the    */
    /* underlying stream object.  Adjust our buffer offset and size.  */

    if (!cbT && (cbSize < XPSOF_BUFF_MAX))
    {
        hr = lpXPSOF->lpstrm->lpVtbl->Read(lpXPSOF->lpstrm,
                lpXPSOF->lpvBuff, XPSOF_BUFF_MAX, &cbRead);

        if (HR_FAILED(hr))
            goto ret;

        lpXPSOF->libBuff = 0;
        lpXPSOF->cbBuffMac = cbT = cbRead;
    }

    /* Now, if the buffer is *not* empty and the caller wants to read */
    /* fewer bytes than what is in the buffer, then we read it from   */
    /* our buffer, fix-up our offset, set the count read and leave.   */

    if (cbT && (cbSize <= cbT))
    {
        lpvRead = (VOID HUGEP *)((LPBYTE)lpXPSOF->lpvBuff + lpXPSOF->libBuff);
        HMemCopy(lpvData, lpvRead, cbSize);
        lpXPSOF->libBuff += cbSize;
        cbRead = cbSize;
        goto ret;
    }

    /* If we are here, then the caller has requested more bytes to be */
    /* read than what can fit in our buffer.  In this case, we copy   */
    /* the remaining data from the buffer (if any) into lpvData and   */
    /* then go straight to the underlying stream for the remainder.   */
    /* Either way, our buffer is empty after this operation.          */

    lpvRead = lpvData;

    if (cbT)
    {
        HMemCopy(lpvRead, (VOID HUGEP *)((LPBYTE)lpXPSOF->lpvBuff + lpXPSOF->libBuff), cbT);
        lpvRead = (BYTE HUGEP *)lpvRead + cbT;
        lpXPSOF->libBuff = 0;
        lpXPSOF->cbBuffMac = 0;
    }

    hr = lpXPSOF->lpstrm->lpVtbl->Read(lpXPSOF->lpstrm,
            lpvRead, cbSize-cbT, &cbRead);

    if (HR_FAILED(hr))
        goto ret;

    cbRead += cbT;

ret:
    if (lpcbRead)
        *lpcbRead = cbRead;

    DebugTraceResult (XPSOF_Read(), hr);
    return hr;
}


/*
 -  IStream::Write
 -
 *  Purpose:
 *      To write data to the stream.
 */

STDMETHODIMP
XPSOF_Write (LPXPSOF lpXPSOF,
    VOID HUGEP * lpvData,
    ULONG cbSize,
    ULONG * lpcbWritten)
{
    HRESULT hr = hrSuccess;
    ULONG cbWritten = 0;
    ULONG cbT;
    VOID HUGEP * lpvWrite = NULL;

    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        IsBadHugeReadPtr (lpvData, cbSize) ||
        (lpcbWritten && IsBadWritePtr (lpcbWritten, sizeof(ULONG))))
    {
        hr = ResultFromScode(STG_E_INVALIDPARAMETER);
        goto ret;
    }

    if (!(lpXPSOF->ulFlags & XPSOF_WRITE))
    {
        hr = ResultFromScode(STG_E_ACCESSDENIED);
        goto ret;
    }

    Assert(lpXPSOF->cbBuffMac >= lpXPSOF->libBuff);

    /* First, if we've been Reading, then we need to re-wind the file  */
    /* pointer in the underlying stream to compensate for the last     */
    /* buffered Read.  Our new vacancy = the Max Size of our buffer.   */

    if (!lpXPSOF->fDirty)
    {
        if (lpXPSOF->libBuff != lpXPSOF->cbBuffMac)
        {
            hr = HrRewindStream(lpXPSOF, lpXPSOF->cbBuffMac-lpXPSOF->libBuff);

            if (HR_FAILED(hr))
                goto ret;
        }

        lpXPSOF->libBuff = 0;
        lpXPSOF->cbBuffMac = XPSOF_BUFF_MAX;
    }

    /* Determine the total vacancy of the buffer. */

    cbT = lpXPSOF->cbBuffMac - lpXPSOF->libBuff;

    /* If the caller wants to Write more bytes than the current  */
    /* vacancy of the buffer, then commit the current buffer and */
    /* Write the callers data directly to the stream.  If the    */
    /* buffer is not dirty, then the Commit call is a no-op.     */

    if (cbSize > cbT)
    {
        hr = XPSOF_Commit(lpXPSOF, 0);

        if (HR_FAILED(hr))
            goto ret;

        hr = lpXPSOF->lpstrm->lpVtbl->Write(lpXPSOF->lpstrm,
                lpvData, cbSize, &cbWritten);

        goto ret;
    }

    /* The callers data will fit in our current buffer.  Copy the */
    /* data into the buffer, mark the buffer as dirty, and adjust */
    /* the buffer offset.  Set cbWritten to cbSize and return.    */

    lpvWrite = (VOID HUGEP *)((LPBYTE)lpXPSOF->lpvBuff + lpXPSOF->libBuff);
    HMemCopy(lpvWrite, lpvData, cbSize);
    lpXPSOF->fDirty = TRUE;
    lpXPSOF->libBuff += cbSize;
    cbWritten = cbSize;

ret:
    if (lpcbWritten)
        *lpcbWritten = cbWritten;

    DebugTraceResult (XPSOF_Write(), hr);
    return hr;
}


/*
 -  IStream::Seek
 -
 *  Purpose:
 *      To move the file pointer in the stream.
 */

STDMETHODIMP
XPSOF_Seek (LPXPSOF lpXPSOF,
    LARGE_INTEGER liMove,
    DWORD dwMode,
    ULARGE_INTEGER * lpliPos)
{
    HRESULT hr = hrSuccess;

    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        (lpliPos && IsBadWritePtr (lpliPos, sizeof(ULARGE_INTEGER))))
    {
        DebugTraceSc (XPSOF_Seek(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    Assert(lpXPSOF->cbBuffMac >= lpXPSOF->libBuff);

    /* If our buffer is dirty, then we've been writing into it and   */
    /* we need to flush it.  Else, if it isn't dirty and our offset  */
    /* and buffer size are not equal, then we've been reading and we */
    /* need to rewind the underlying stream to match our position.   */

    if (lpXPSOF->fDirty)
    {
        hr = XPSOF_Commit(lpXPSOF, 0);

        if (HR_FAILED(hr))
            goto ret;
    }
    else
    {
        if ((dwMode == STREAM_SEEK_CUR) &&
            (lpXPSOF->libBuff != lpXPSOF->cbBuffMac))
        {
            hr = HrRewindStream(lpXPSOF, lpXPSOF->cbBuffMac-lpXPSOF->libBuff);

            if (HR_FAILED(hr))
                goto ret;
        }

        lpXPSOF->libBuff = 0;
        lpXPSOF->cbBuffMac = 0;
    }

    /* Now, call the real streams Seek method. */

    hr = lpXPSOF->lpstrm->lpVtbl->Seek(lpXPSOF->lpstrm,
            liMove, dwMode, lpliPos);

ret:
    return hr;
}


/*
 -  IStream::SetSize
 -
 *  Purpose:
 *      To set a max size on the file.
 */

STDMETHODIMP
XPSOF_SetSize (LPXPSOF lpXPSOF, ULARGE_INTEGER liSize)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_SetSize(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->SetSize(lpXPSOF->lpstrm, liSize);
}


/*
 -  IStream::CopyTo
 -
 *  Purpose:
 *      To copy data from one stream to another.
 */

STDMETHODIMP
XPSOF_CopyTo (LPXPSOF lpXPSOF,
    LPSTREAM lpStrmDst,
    ULARGE_INTEGER cbCopy,
    ULARGE_INTEGER * lpcbRead,
    ULARGE_INTEGER * lpcbWritten)
{
    HRESULT hr;

    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        IsBadReadPtr (lpStrmDst, sizeof(LPVOID)) ||
        IsBadWritePtr (lpcbRead, sizeof(ULARGE_INTEGER)) ||
        IsBadWritePtr (lpcbWritten, sizeof(ULARGE_INTEGER)))
    {
        DebugTraceSc (XPSOF_CopyTo(), STG_E_INVALIDPARAMETER);
        return ResultFromScode(STG_E_INVALIDPARAMETER);
    }

    Assert(lpXPSOF->cbBuffMac >= lpXPSOF->libBuff);

    /* If our buffer is dirty, then we've been writing into it and   */
    /* we need to flush it.  Else, if it isn't dirty and our offset  */
    /* and buffer size are not equal, then we've been reading and we */
    /* need to rewind the underlying stream to match our position.   */

    if (lpXPSOF->fDirty)
    {
        hr = XPSOF_Commit(lpXPSOF, 0);

        if (HR_FAILED(hr))
            goto ret;
    }
    else
    {
        if (lpXPSOF->libBuff != lpXPSOF->cbBuffMac)
        {
            hr = HrRewindStream(lpXPSOF, lpXPSOF->cbBuffMac-lpXPSOF->libBuff);

            if (HR_FAILED(hr))
                goto ret;
        }

        lpXPSOF->libBuff = 0;
        lpXPSOF->cbBuffMac = 0;
    }

    /* Now, call the real streams CopyTo method. */

    hr = lpXPSOF->lpstrm->lpVtbl->CopyTo(lpXPSOF->lpstrm, lpStrmDst,
            cbCopy, lpcbRead, lpcbWritten);

ret:
    return hr;
}


/*
 -  IStream::Commit
 -
 *  Purpose:
 *      To force a write to disk of any data that is buffered
 *      by either this object or the operating system.
 */

STDMETHODIMP
XPSOF_Commit (LPXPSOF lpXPSOF, ULONG ulFlags)
{
    HRESULT hr;

    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_Commit(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    /* Flush my internal buffer if it is dirty. */

    if ((lpXPSOF->ulFlags & XPSOF_WRITE) && (lpXPSOF->fDirty))
    {
        hr = lpXPSOF->lpstrm->lpVtbl->Write(lpXPSOF->lpstrm,
                lpXPSOF->lpvBuff, lpXPSOF->libBuff, NULL);

        if (HR_FAILED(hr))
            goto ret;
    }

    /* Call Commit on the underlying stream. */

    hr = lpXPSOF->lpstrm->lpVtbl->Commit(lpXPSOF->lpstrm, ulFlags);

    /* Mark my buffer as empty cal clean. */

    lpXPSOF->fDirty = FALSE;
    lpXPSOF->libBuff = 0;
    lpXPSOF->cbBuffMac = 0;

ret:
    return hr;
}


/*
 -  IStream::Stat
 -
 *  Purpose:
 *      To retrieve information about the stream.
 */

STDMETHODIMP
XPSOF_Stat (LPXPSOF lpXPSOF, STATSTG * lpStg, DWORD dwFlags)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)) ||
        IsBadWritePtr (lpStg, sizeof(STATSTG)))
    {
        DebugTraceSc (XPSOF_Stat(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->Stat(lpXPSOF->lpstrm, lpStg, dwFlags);
}


/*
 -  HrRewindStream
 -
 *  Purpose:
 *      This gets called to back-up the file pointer when a Write operation
 *      follows a Read operation.  This is necessary because the file pointer
 *      is actually further ahead in the file than the buffered file pointer.
 *
 *  Parameters:
 *      lpXPSOF             - Our wrapped stream-on-file object
 *      ib                  - Number of bytes to rewind
 *
 *  Returns:
 *      hr                  - Result of the underlying Seek() call
 */

HRESULT HrRewindStream(LPXPSOF lpXPSOF, ULONG ib)
{
    LARGE_INTEGER liRewind;

    if (!ib)
        return hrSuccess;

    liRewind.HighPart = 0xFFFFFFFF;
    liRewind.LowPart = -((LONG)ib);

    return lpXPSOF->lpstrm->lpVtbl->Seek(lpXPSOF->lpstrm,
            liRewind, STREAM_SEEK_CUR, NULL);
}


/* Unimplemented methods; call straight through to the underlying stream. */

STDMETHODIMP
XPSOF_Revert (LPXPSOF lpXPSOF)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_Revert(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->Revert(lpXPSOF->lpstrm);
}

STDMETHODIMP
XPSOF_LockRegion (LPXPSOF lpXPSOF,
    ULARGE_INTEGER uliOffset,
    ULARGE_INTEGER uliSize,
    DWORD dwLockType)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_LockRegion(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->LockRegion(lpXPSOF->lpstrm,
            uliOffset, uliSize, dwLockType);
}

STDMETHODIMP
XPSOF_UnlockRegion (LPXPSOF lpXPSOF,
    ULARGE_INTEGER uliOffset,
    ULARGE_INTEGER uliSize,
    DWORD dwLockType)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_UnlockRegion(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->UnlockRegion(lpXPSOF->lpstrm,
            uliOffset, uliSize, dwLockType);
}

STDMETHODIMP
XPSOF_Clone (LPXPSOF lpXPSOF, LPSTREAM * lppStm)
{
    if (IsBadWritePtr (lpXPSOF, sizeof(XPSOF)))
    {
        DebugTraceSc (XPSOF_Clone(), STG_E_INVALIDPARAMETER);
        return ResultFromScode (STG_E_INVALIDPARAMETER);
    }

    return lpXPSOF->lpstrm->lpVtbl->Clone(lpXPSOF->lpstrm, lppStm);
}


/*
 -  HMemCopy
 -
 *  Purpose:
 *      Same as memcpy but works with huge pointers.
 */

VOID
HMemCopy(VOID HUGEP * lpvDst, VOID HUGEP * lpvSrc, ULONG cb)
{
    while (cb--)
        *((BYTE HUGEP *)lpvDst)++ = *((BYTE HUGEP *)lpvSrc)++;
}
