#include <afx.h>
#include "adoutput.h"
#include "errmsg.h"

//@doc FILE ADOUTPUT


//@mfunc Constructor. Initializes the output buffer & count vars.
CAdOutput::CAdOutput()
{ 
    m_szOutBuf = NULL;
    m_nBufLen = 0;
    m_nBufCur = 0;
}

//@mfunc Destructor. Deletes the output buffer if present.

CAdOutput::~CAdOutput()
{
    if(m_szOutBuf)
        delete m_szOutBuf;
}

//@mfunc Allocates a memory block for the output buffer and resets
// count variables. 
//@rdesc Zero if successful or errMemory if not enough memory for requested
// buffer.
int CAdOutput::SetOutputBuffer(
    UINT nBufLen)           //@parm How much memory to allocate.
{
TRY
{
    if(m_szOutBuf)
        delete m_szOutBuf;

    m_szOutBuf = new char[nBufLen];
    m_nBufLen = nBufLen;
    m_nBufCur = 0;

    return 0;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}


//@mfunc Writes all unwritten text to the output file.

void CAdOutput::FlushOutputBuffer(void)
{
    ASSERT(m_szOutBuf);

    if(m_nBufCur)
    {
        CFile::Write(m_szOutBuf, m_nBufCur);
        m_nBufCur = 0;
    }
}

//@mfunc Writes a chunk of data to the output buffer, flushing the
// buffer first if necessary. Note: Do NOT attempt to write a data
// block larger than the allocated buffer size. If you do so the
// write will be truncated, only the data equal to the buffer size
// will be written, and no error message will occur.

void CAdOutput::Write(
    const void* lpBuf,      //@parm Pointer to stuff to write
    UINT nCount)            //@parm How many bytes to write
{
    ASSERT(nCount <= m_nBufLen);
    ASSERT(m_szOutBuf);

    if(nCount + m_nBufCur <= m_nBufLen)
    {
        memcpy(m_szOutBuf+m_nBufCur, lpBuf, nCount);
        m_nBufCur += nCount;
    }
    else
    {
        FlushOutputBuffer();

        if(nCount > m_nBufLen)
            nCount = m_nBufLen;

        Write(lpBuf, nCount);
    }
}
