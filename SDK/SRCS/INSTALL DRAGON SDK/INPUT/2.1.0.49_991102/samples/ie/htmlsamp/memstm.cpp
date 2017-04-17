/********************************************************************
 * memstm.cpp
 *
 * Description
 *    CMemoryStream - implementation of the standard IStream interface
 *                    that writes to and read from a memory block.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers

#ifdef GAME_SAMPLE              // not needed if doing mini-browser

/********************************************************************
 * Includes
 ********************************************************************/
#include "memstm.h"             // CMemoryStream

/********************************************************************
 * Defines
 ********************************************************************/
#define GROW_MINIMUM    100     // grow memory buffer minimum

/********************************************************************
 * CMemoryStream::CMemoryStream
 *
 * Description
 *    Constructor. Initializes the stream to empty and positioned at
 *    the beginning.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CMemoryStream::CMemoryStream(void)
{
    // Initialize internal data
    _ulRefs   = 1;
    _lCurPos  = 0;
    _cbSize   = 0;
    _cbBuf    = 0;
    _pbBuf    = NULL;
}

/********************************************************************
 * CMemoryStream::~CMemoryStream
 *
 * Description
 *    Destructor. Destroy the memory buffer.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CMemoryStream::~CMemoryStream(void)
{
    // destroy memory buffer
    if (_pbBuf)
    {
        delete [] _pbBuf;
    }
}

/********************************************************************
 * IUnknown CMemoryStream
 ********************************************************************/

/********************************************************************
 * CMemoryStream::QueryInterface
 *
 * Description
 *    Return pointer to interface if request interface is supported 
 *    by this object. See COM/OLE documentation on IUnknown.
 *
 * Parameters
 *    riid              ID of requested interface
 *    ppvObj	        filled with requested interface pointer if 
 *                      supported
 * 
 * Returns
 *    S_OK              requested interface supported
 *    E_NOINTERFACE     requested interface not supported
 ********************************************************************/
HRESULT CMemoryStream::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    // check for IUnknown
    if (riid == IID_IUnknown)
    {
        *ppvObj = (IUnknown *)this;
    }
    // check for IStream
    else if (riid == IID_IStream)
    {
        *ppvObj = (IStream *)this;
    }
    // all others are unsupported
    else
    {
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }

    // add reference count and return interface pointer
    ((IUnknown *)(*ppvObj))->AddRef();

    return S_OK;
}

/********************************************************************
 * CMemoryStream::AddRef
 *
 * Description
 *    Increments reference count on object. See COM/OLE documentation
 *    on IUnknown.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    Reference count after addition
 ********************************************************************/
ULONG CMemoryStream::AddRef(void)
{
    // increment reference count & return new count
    return ++_ulRefs;
}

/********************************************************************
 * CMemoryStream::Release
 *
 * Description
 *    Decrements reference count on object; deletes object when count
 *    is zero. See COM/OLE documentation on IUnknown.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    Reference count after subtraction
 ********************************************************************/
ULONG CMemoryStream::Release(void)
{
    // decrement reference count
    _ulRefs--;

    // delete object if no more references    
    if (!_ulRefs)
    {
        delete this;
        // return new count
        return 0;
    }

    // return new count
    return _ulRefs;
}

/********************************************************************
 * IStream CMemoryStream 
 ********************************************************************/

/********************************************************************
 * CMemoryStream::Read
 *
 * Description
 *    Fill the given buffer with the contents of the memory stream
 *    from the current position in the stream. See COM/OLE 
 *    documentation on IStream.
 *
 * Parameters
 *    pv        buffer in which to return stream data
 *    cb        maximum number of bytes to read
 *    pcbRead   filled in with number of bytes actually read
 * 
 * Returns
 *    S_OK                  read some data
 *    S_FALSE               at end of data
 *    STG_E_INVALIDPOINTER  NULL pv
 ********************************************************************/
HRESULT CMemoryStream::Read(LPVOID pv, ULONG cb, ULONG *pcbRead)
{
    HRESULT hr = S_OK;

    // initialize return data    
    if (pcbRead)
    {
        *pcbRead = 0;
    }

    // validate parameters
    if (!pv)
    {
        return STG_E_INVALIDPOINTER;
    }

    // check for any data at all
    if (!_pbBuf)
    {
        return S_FALSE;
    }

    // truncate request if not enough data 
    if (_cbBuf < (_lCurPos + (long)cb))
    {
        cb = _cbBuf - _lCurPos;
    }

    // copy data to return
    memcpy(pv, _pbBuf + _lCurPos, cb);

    // increment current data position
    _lCurPos += cb;
    
    // return bytes actually read
    if (pcbRead)
    {
        *pcbRead = cb;
    }

    // return whether any bytes were read
    return cb ? S_OK : S_FALSE;
}

/********************************************************************
 * CMemoryStream::Write
 *
 * Description
 *    Add the given buffer to the contents of the memory stream
 *    at the current position in the stream. See COM/OLE 
 *    documentation on IStream.
 *
 * Parameters
 *    pv        buffer to copy to stream data
 *    cb        number of bytes to write
 *    pcbRead   filled in with number of bytes actually written
 * 
 * Returns
 *    S_OK                  wrote the data
 *    STG_E_INVALIDPOINTER  NULL pv
 *    E_OUTOFMEMORY         out of memory
 ********************************************************************/
HRESULT CMemoryStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
    // validate parameters
    if (!pv)
    {
        return STG_E_INVALIDPOINTER;
    }

    // ensure enough space in the buffer
    if (FAILED(GrowBuffer(_lCurPos + cb)))
    {
        return E_OUTOFMEMORY;
    }

    // copy the data into the buffer
    memcpy(_pbBuf + _lCurPos, pv, cb);

    // return bytes actually written
    if (pcbWritten)
    {
        *pcbWritten = cb;
    }

    // increment current data position and size of data buffer
    _lCurPos += cb;
    _cbBuf   += cb;

    return S_OK;
}

/********************************************************************
 * CMemoryStream::Seek
 *
 * Description
 *    Set the current position in the stream to the requested position. 
 *    This object cannot handle very large files, so the high order
 *    dword must always be 0. See COM/OLE documentation on IStream.
 *
 * Parameters
 *    dlibMove          position to move to
 *    dwOrigin          starting place (origin, current position, end)
 *    plibNewPosition   filled in with actual new position
 * 
 * Returns
 *    S_OK                  wrote the data
 *    E_INVALIDARG          bad positon
 *    STG_E_ACCESSDENIED    bad position
 *    STG_E_INVALIDFUNCTION bad dwOrigin
 *    E_OUTOFMEMORY         out of memory
 ********************************************************************/
HRESULT CMemoryStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, 
                            ULARGE_INTEGER *plibNewPosition)
{
    // set the default return positon as the current position
    if (plibNewPosition)
    {
        plibNewPosition->LowPart  = _lCurPos;
        plibNewPosition->HighPart = 0;
    }

    switch (dwOrigin)
    {
    case STREAM_SEEK_SET:
        if (dlibMove.HighPart)
        {
            return E_INVALIDARG;
        }
        _lCurPos = dlibMove.LowPart;
        break;

    case STREAM_SEEK_CUR:
        if (dlibMove.HighPart && (dlibMove.HighPart != -1))
        {
            return E_INVALIDARG;
        }
        _lCurPos += (int) dlibMove.LowPart;
        break;

    case STREAM_SEEK_END:
        if (dlibMove.HighPart && (dlibMove.HighPart != -1))
        {
            return STG_E_ACCESSDENIED;
        }
        _lCurPos = _cbBuf + (int) dlibMove.LowPart;
        break;

    default:
        return STG_E_INVALIDFUNCTION;
    }

    // if went too far back, set to origin
    if (_lCurPos < 0)
    {
        _lCurPos = 0;
        if (plibNewPosition)
        {
            plibNewPosition->LowPart = 0;
        }
        return E_INVALIDARG;
    }

    // if went too far forward, try to grow the buffer
    if (_lCurPos > _cbBuf)
    {
        if (FAILED(GrowBuffer(_lCurPos)))
        {
            _lCurPos = _cbBuf;
            return E_OUTOFMEMORY;
        }

        _cbBuf = _lCurPos;
    }

    // return the final new position
    if (plibNewPosition)
    {
        plibNewPosition->LowPart = _lCurPos;
    }

    return S_OK;
}

/********************************************************************
 * CMemoryStream::SetSize
 *
 * Description
 *    Not implemented for this object. See COM/OLE documentation on 
 *    IStream.
 *
 * Parameters
 *    libNewSize        new size of memory buffer
 * 
 * Returns
 *    E_NOTIMPL         not implemented
 ********************************************************************/
HRESULT CMemoryStream::SetSize(ULARGE_INTEGER libNewSize)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CMemoryStream::CopyTo
 *
 * Description
 *    Copies the requested data into the given stream.
 *
 * Parameters
 *    pstm          destination IStream
 *    cb            number of bytes to copy
 *    pcbRead       filled with number of bytes read
 *    pcbWritten    filled with number of bytes written
 * 
 * Returns
 *    S_OK          copied successfully
 *    E_INVALIDARG  bad number of bytes
 *    Other         result of Write
 ********************************************************************/
HRESULT CMemoryStream::CopyTo(IStream *pstm, ULARGE_INTEGER cb, 
                              ULARGE_INTEGER *pcbRead, 
                              ULARGE_INTEGER *pcbWritten)
{
    // validate parameters
    if (cb.HighPart)
    {
        return E_INVALIDARG;
    }

    ULONG   ulWritten, ulToWrite, ulAvailable;

    // truncate to bytes available
    ulToWrite = cb.LowPart;
    ulAvailable = _cbBuf - _lCurPos;
    if (ulToWrite > ulAvailable)
    {
        ulToWrite = ulAvailable;
    }

    // write to given stream
    HRESULT hr = pstm->Write(_pbBuf + _lCurPos, ulToWrite, &ulWritten);

    // advance current position
    _lCurPos += ulWritten; 

    // return bytes read and written    
    if (pcbRead)
    {
        pcbRead->LowPart = ulWritten;
        pcbRead->HighPart = 0;
    }

    if (pcbWritten)
    {
        pcbWritten->LowPart = ulWritten;
        pcbWritten->HighPart = 0;
    }

    return hr;
}


/********************************************************************
 * CMemoryStream::Commit
 *
 * Description
 *    Not implemented for this object. See COM/OLE documentation on 
 *    IStream.
 *
 * Parameters
 *    grfCommitFlags    flags
 * 
 * Returns
 *    E_NOTIMPL         not implemented
 ********************************************************************/
HRESULT CMemoryStream::Commit(DWORD grfCommitFlags)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CMemoryStream::Revert
 *
 * Description
 *    Not implemented for this object. See COM/OLE documentation on 
 *    IStream.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL         not implemented
 ********************************************************************/
HRESULT CMemoryStream::Revert(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CMemoryStream::LockRegion
 *
 * Description
 *    Not implemented for this object. See COM/OLE documentation on 
 *    IStream.
 *
 * Parameters
 *    libOffset         beginning of lock position
 *    cb                number of bytes to lock
 *    dwLockType        type of lock
 * 
 * Returns
 *    E_NOTIMPL         not implemented
 ********************************************************************/
HRESULT CMemoryStream::LockRegion(ULARGE_INTEGER libOffset, 
                                  ULARGE_INTEGER cb, DWORD dwLockType)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CMemoryStream::UnlockRegion
 *
 * Description
 *    Not implemented for this object. See COM/OLE documentation on 
 *    IStream.
 *
 * Parameters
 *    libOffset         beginning of lock position
 *    cb                number of bytes to lock
 *    dwLockType        type of lock
 * 
 * Returns
 *    E_NOTIMPL         not implemented
 ********************************************************************/
HRESULT CMemoryStream::UnlockRegion(ULARGE_INTEGER libOffset, 
                                    ULARGE_INTEGER cb, DWORD dwLockType)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CMemoryStream::Stat
 *
 * Description
 *    Minimally implemented for this object. See COM/OLE documentation 
 *    on IStream.
 *
 * Parameters
 *    pstatstg          filled with storage information
 *    grfStatFlag	flags
 * 
 * Returns
 *    S_OK              returned data
 ********************************************************************/
HRESULT CMemoryStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
    // validate parameters
    if (pstatstg)
    {
        // set return data
        memset(pstatstg, 0, sizeof(STATSTG));
        pstatstg->type = STGTY_STREAM;
        ULISet32(pstatstg->cbSize, _cbBuf);
        pstatstg->grfMode = STGM_READ;
    }

    return S_OK;
}

/********************************************************************
 * CMemoryStream::Clone
 *
 * Description
 *    Copy memory buffer to a new IStream. See COM/OLE documentation 
 *    on IStream.
 *
 * Parameters
 *    ppStm             filled with new IStream
 * 
 * Returns
 *    S_OK              sucessfully cloned
 *    E_POINTER         NULL ppStm
 *    E_OUTOFMEMORY     out of memeory
 ********************************************************************/
HRESULT CMemoryStream::Clone(IStream **ppStm)
{
    // validate parameters
    if (!ppStm)
    {
        return E_POINTER;
    }

    // create new stream
    *ppStm = new CMemoryStream();
    if (!*ppStm)
    {
        return E_OUTOFMEMORY;
    } 

    // copy memory buffer data
    HRESULT hr = (*ppStm)->Write(_pbBuf, _cbBuf, NULL);

    // set new stream's position to beginning
    LARGE_INTEGER li = { 0 };
    (*ppStm)->Seek(li, STREAM_SEEK_SET, NULL);

    return hr;

}

/********************************************************************
 * Internal functions CMemoryStream 
 ********************************************************************/

/********************************************************************
 * CMemoryStream::GrowBuffer
 *
 * Description
 *    Increase size of memory buffer (if needed) to accomodate 
 *    requested number of bytes 
 *
 * Parameters
 *    lSize             size in bytes of memory buffer
 * 
 * Returns
 *    S_OK              already large enough or grew sucessfully
 *    E_OUTOFMEMORY     out of memeory
 ********************************************************************/
HRESULT CMemoryStream::GrowBuffer(long lSize)
{
    // check if already have enough memory
    if (_cbSize >= lSize)
    {
        return S_OK;
    }

    // dont grow in very small chunks
    if ((lSize - _cbSize) < GROW_MINIMUM)
    {
        lSize = _cbSize + GROW_MINIMUM;
    }

    // allocate new buffer
    LPBYTE pNewBuf = new BYTE[lSize];
    if (!pNewBuf)
    {
        return E_OUTOFMEMORY;
    }

    // copy data into new buffer, delete old buffer
    if (_pbBuf)
    {
        memcpy(pNewBuf, _pbBuf, _cbSize);
        delete [] _pbBuf;
    }

    // set internals to new buffer and size
    _pbBuf  = pNewBuf;
    _cbSize = lSize;

    return S_OK;
}

#endif // GAME_SAMPLE
