///////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      XPSTREAM.CPP 
//
//  Description
//      Wraps the StreamOnFile object to add buffering of the stream.
//      The wrappered version uses an in-memory buffer, or cache, to
//      reduce the number of actual Reads and Writes to the underlying
//      stream.  The goal is, obviously, to improve performance.
//      This code is not thread safe.  Also, the implementation
//      is not optimized for streams that both read and write continuously
//      because there will be too much flushing going on.
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
#include "XPSTREAM.H"
#include "TRACES.H"
#include "COMWINDS.H"


CCachedStream::CCachedStream (LPSTREAM pImpStream, ULONG ulFlags)
{
    m_cRef = 1;
    m_fDirty = FALSE;
    m_ulFlags = ulFlags;
    m_libBuff = 0;
    m_cbBuffMac = 0;
    m_pvCache = HeapAlloc (GetProcessHeap(), 0, XPSOF_BUFF_MAX);
    if (NULL == m_pvCache)
    {
        throw CException (E_OUTOFMEMORY);
    }
    m_pImpStream = pImpStream;
    m_pImpStream->AddRef();
}

CCachedStream::~CCachedStream()
{
    m_pImpStream->Release();
    if (m_pvCache)
    {
        HeapFree (GetProcessHeap(), 0, m_pvCache);
    }
}

STDMETHODIMP CCachedStream::Read (LPVOID lpvData, ULONG cbSize, ULONG * lpcbRead)
{
    HRESULT hResult = S_OK;
    ULONG cbRead = 0;
    ULONG cbT;
    LPVOID lpvRead = NULL;

    if (IsBadWritePtr (lpvData, cbSize) || (lpcbRead && IsBadWritePtr (lpcbRead, sizeof(ULONG))))
    {
        hResult = STG_E_INVALIDPARAMETER;
        goto ret;
    }
    if (!(XPSOF_READ & m_ulFlags))
    {
        hResult = STG_E_ACCESSDENIED;
        goto ret;
    }
    ASSERT (m_cbBuffMac >= m_libBuff);

    // First, flush the buffer if it has been written into.  This
    // operation empties our buffer and zeros the offset and size.
    // We do this because we also buffer writes and we need to force
    // the underlying stream to point to where the caller expects.
    if ((XPSOF_WRITE & m_ulFlags) && m_fDirty)
    {
        hResult = Commit (0);
        if (hResult)
        {
            goto ret;
        }
    }

    // Determine if the buffer is empty (cbT == 0) or not (cbT != 0).
    // We consider the buffer empty if we've read past the end of it
    // or if m_cbBuffMac and m_libBuff are equal to zero.
    cbT = m_cbBuffMac - m_libBuff;

    // If the buffer is empty and the caller wants to read less than
    // the size of our buffer, then we'll fill the buffer from the
    // underlying stream object.  Adjust our buffer offset and size.
    if (!cbT && (cbSize < XPSOF_BUFF_MAX))
    {
        hResult = m_pImpStream->Read (m_pvCache, XPSOF_BUFF_MAX, &cbRead);
        if (hResult)
        {
            goto ret;
        }
        m_libBuff = 0;
        m_cbBuffMac = cbT = cbRead;
    }

    // Now, if the buffer is *not* empty and the caller wants to read
    // fewer bytes than what is in the buffer, then we read it from
    // our buffer, fix-up our offset, set the count read and leave.
    if (cbT && (cbSize <= cbT))
    {
        lpvRead = (LPVOID)((LPBYTE)m_pvCache + m_libBuff);
        CopyMemory (lpvData, lpvRead, cbSize);
        m_libBuff += cbSize;
        cbRead = cbSize;
        goto ret;
    }

    // If we are here, then the caller has requested more bytes to be
    // read than what can fit in our buffer.  In this case, we copy
    // the remaining data from the buffer (if any) into lpvData and
    // then go straight to the underlying stream for the remainder.
    // Either way, our buffer is empty after this operation.
    lpvRead = lpvData;
    if (cbT)
    {
        CopyMemory (lpvRead, (LPVOID)((LPBYTE)m_pvCache + m_libBuff), cbT);
        lpvRead = (LPBYTE)lpvRead + cbT;
        m_libBuff = 0;
        m_cbBuffMac = 0;
    }

    hResult = m_pImpStream->Read (lpvRead, cbSize - cbT, &cbRead);
    if (hResult)
    {
        goto ret;
    }
    cbRead += cbT;

ret:
    if (lpcbRead)
    {
        *lpcbRead = cbRead;
    }
    TraceResult ("CCachedStream::Read", hResult);
    return hResult;
}

STDMETHODIMP CCachedStream::Write (const void * lpvData, ULONG cbSize, ULONG * lpcbWritten)
{
    HRESULT hResult = S_OK;
    ULONG cbWritten = 0;
    ULONG cbT;
    LPVOID lpvWrite = NULL;

    if (IsBadReadPtr (lpvData, cbSize) || (lpcbWritten && IsBadWritePtr (lpcbWritten, sizeof(ULONG))))
    {
        hResult = STG_E_INVALIDPARAMETER;
        goto ret;
    }
    if (!(XPSOF_WRITE & m_ulFlags))
    {
        hResult = STG_E_ACCESSDENIED;
        goto ret;
    }
    ASSERT (m_cbBuffMac >= m_libBuff);

    // First, if we've been Reading, then we need to re-wind the file
    // pointer in the underlying stream to compensate for the last
    // buffered Read.  Our new vacancy = the Max Size of our buffer.
    if (!m_fDirty)
    {
        if (m_libBuff != m_cbBuffMac)
        {
            hResult = RewindStream (m_cbBuffMac - m_libBuff);
            if (hResult)
            {
                goto ret;
            }
        }
        m_libBuff = 0;
        m_cbBuffMac = XPSOF_BUFF_MAX;
    }

    // Determine the total vacancy of the buffer.
    cbT = m_cbBuffMac - m_libBuff;

    // If the caller wants to Write more bytes than the current
    // vacancy of the buffer, then commit the current buffer and
    // Write the callers data directly to the stream.  If the
    // buffer is not dirty, then the Commit call is a no-op.
    if (cbSize > cbT)
    {
        hResult = Commit (0);
        if (hResult)
        {
            goto ret;
        }
        hResult = m_pImpStream->Write (lpvData, cbSize, &cbWritten);
        goto ret;
    }

    // The callers data will fit in our current buffer.  Copy the
    // data into the buffer, mark the buffer as dirty, and adjust
    // the buffer offset.  Set cbWritten to cbSize and return.
    lpvWrite = (LPVOID)((LPBYTE)m_pvCache + m_libBuff);
    CopyMemory (lpvWrite, lpvData, cbSize);
    m_fDirty = TRUE;
    m_libBuff += cbSize;
    cbWritten = cbSize;

ret:
    if (lpcbWritten)
    {
        *lpcbWritten = cbWritten;
    }
    TraceResult ("CCachedStream::Write", hResult);
    return hResult;
}

STDMETHODIMP CCachedStream::Seek (LARGE_INTEGER liMove, DWORD dwMode, ULARGE_INTEGER * lpliPos)
{
    HRESULT hResult = S_OK;
    if (lpliPos && IsBadWritePtr (lpliPos, sizeof(ULARGE_INTEGER)))
    {
        hResult = STG_E_INVALIDPARAMETER;
        goto ret;
    }
    ASSERT (m_cbBuffMac >= m_libBuff);

    // If our buffer is dirty, then we've been writing into it and
    // we need to flush it.  Else, if it isn't dirty and our offset
    // and buffer size are not equal, then we've been reading and we
    // need to rewind the underlying stream to match our position.
    if (m_fDirty)
    {
        hResult = Commit (0);
        if (hResult)
        {
            goto ret;
        }
    }
    else
    {
        if ((dwMode == STREAM_SEEK_CUR) && (m_libBuff != m_cbBuffMac))
        {
            hResult = RewindStream (m_cbBuffMac - m_libBuff);
            if (hResult)
            {
                goto ret;
            }
        }
        m_libBuff = 0;
        m_cbBuffMac = 0;
    }
    // Now, call the real stream's Seek method.
    hResult = m_pImpStream->Seek (liMove, dwMode, lpliPos);
ret:
    TraceResult ("CCachedStream::Seek", hResult);
    return hResult;
}

STDMETHODIMP CCachedStream::CopyTo (LPSTREAM lpStrmDst,
                                    ULARGE_INTEGER cbCopy,
                                    ULARGE_INTEGER * lpcbRead,
                                    ULARGE_INTEGER * lpcbWritten)
{
    HRESULT hResult;
    if (IsBadReadPtr (lpStrmDst, sizeof(LPVOID)) ||
        IsBadWritePtr (lpcbRead, sizeof(ULARGE_INTEGER)) ||
        IsBadWritePtr (lpcbWritten, sizeof(ULARGE_INTEGER)))
    {
        hResult = STG_E_INVALIDPARAMETER;
        goto ret;
    }
    ASSERT (m_cbBuffMac >= m_libBuff);

    // If our buffer is dirty, then we've been writing into it and
    // we need to flush it.  Else, if it isn't dirty and our offset
    // and buffer size are not equal, then we've been reading and we
    // need to rewind the underlying stream to match our position.
    if (m_fDirty)
    {
        hResult = Commit (0);
        if (hResult)
        {
            goto ret;
        }
    }
    else
    {
        if (m_libBuff != m_cbBuffMac)
        {
            hResult = RewindStream (m_cbBuffMac - m_libBuff);
            if (hResult)
            {
                goto ret;
            }
        }
        m_libBuff = 0;
        m_cbBuffMac = 0;
    }

    // Now, call the real streams CopyTo method.
    hResult = m_pImpStream->CopyTo (lpStrmDst, cbCopy, lpcbRead, lpcbWritten);
ret:
    TraceResult ("CCachedStream::CopyTo", hResult);
    return hResult;
}

STDMETHODIMP CCachedStream::Commit (ULONG ulFlags)
{
    HRESULT hResult = S_OK;
    // Flush my internal buffer if it is dirty.
    if ((XPSOF_WRITE & m_ulFlags) && m_fDirty)
    {
        hResult = m_pImpStream->Write (m_pvCache, m_libBuff, NULL);
        if (hResult)
        {
            goto ret;
        }
    }
    // Mark my buffer as empty cal clean.
    m_fDirty = FALSE;
    m_libBuff = 0;
    m_cbBuffMac = 0;
ret:
    TraceResult ("CCachedStream::Commit", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CCachedStream::RewindStream()
//
//    Parameters
//      ib      Number of bytes to rewind
//
//    Purpose
//      This gets called to back-up the file pointer when a Write operation
//      follows a Read operation.  This is necessary because the file pointer
//      is actually further ahead in the file than the buffered file pointer.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI CCachedStream::RewindStream (ULONG ib)
{
    if (ib)
    {
        LARGE_INTEGER liRewind;
        liRewind.HighPart = 0xFFFFFFFF;
        liRewind.LowPart = -((LONG)ib);
        return m_pImpStream->Seek (liRewind, STREAM_SEEK_CUR, NULL);
    }
    return S_OK;
}

// End of File for XPSTREAM.CPP
