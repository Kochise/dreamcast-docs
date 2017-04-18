//@doc FILE ADOUTPUT

//@class Provides buffered output functionality on top of the
// <c CFile> object.

class CAdOutput : public CFile
{
public:

    //@cmember Sets the size of the output buffer.

    int SetOutputBuffer(UINT nBufLen);

    //@cmember Flushes the output buffer, writes all remaining text
    // to the actual file.

    void FlushOutputBuffer(void);

    //@cmember Overridden <mf CFile::Write> function that incorporates
    // buffering.

    void Write(const void* lpBuf, UINT nCount);


    //@cmember Constructor.
    CAdOutput();

    //@cmember Destructor, deletes the buffer (no flushing - must call
    // <mf .FlushOutputBuffer>.

    ~CAdOutput();

private:
    //@cmember The buffer.

    char *m_szOutBuf;

    //@cmember Total buffer length.

    UINT m_nBufLen;

    //@cmember Characters currently stored in buffer.

    UINT m_nBufCur;
};

