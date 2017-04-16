// wave.cpp : implementation file
// @doc

#include "stdafx.h"
#include "afxpriv.h" // For CSharedFile
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWave

IMPLEMENT_SERIAL(CWave, CObject, 0 /* schema number*/ )

/*
@mfunc void | CWave | CWave | Construct a waveform object.
@syntax CWave(WAVEFLAG flag = CWave::flagDefault);
@parm WAVEFLAG | flag | Determines if reference counting will be used 
or not.
@rdesc There is no return value.
@comm If flag is set to CWave::flagDefault then no reference counting
is used.  If flag is set to CWave::flagAutoDestruct the reference counting of the 
CWave object is used and the object will destroy itself when the 
reference count falls to zero.
@xref <c CWave> <mf CWave::AddRef> <mf CWave::Release>
*/

CWave::CWave(WAVEFLAG flag)
{
    m_pcmfmt.wf.wFormatTag = WAVE_FORMAT_1M08;
    m_pcmfmt.wf.nChannels = 1;
    m_pcmfmt.wf.nSamplesPerSec = 11025;
    m_pcmfmt.wf.nAvgBytesPerSec = 11025;
    m_pcmfmt.wf.nBlockAlign = 1;
    m_pcmfmt.wBitsPerSample = 8;
    m_pOutDev = NULL;
    m_pInDev = NULL;
    m_iRefCount = 0;
    m_iPlayCount = 0;
    if (flag && CWave::flagAutoDestruct) {
        m_bAutoDestruct = TRUE;
    } else {
        m_bAutoDestruct = FALSE;
    }
    m_pNotifyObj = NULL;
}

CWave::~CWave()
{
    if (m_iPlayCount) {
        Stop();
    }
    ASSERT(!m_iPlayCount);
    m_BlockList.FreeAll();
    ASSERT(m_iRefCount == 0);
}

/*
@mfunc int | CWave | AddRef | Increment the object's reference count.
@syntax AddRef();
@rdesc The return value is the new reference count.
@xref <c CWave> <mf CWave::CWave> <mf CWave::Release>
*/

int CWave::AddRef()
{
    ASSERT(m_iRefCount < 1000);
    return ++m_iRefCount;
}

/*
@mfunc int | CWave | Release | Decrement the object's reference count.
@syntax Release();
@rdesc The return value is the new reference count.
@comm If the object was created with the CWave::flagAutoDestruct option
and the reference count becomes zero, the object will destroy itself.
@xref <c CWave> <mf CWave::CWave> <mf CWave::AddRef>  <mf CWave::Create>
*/

int CWave::Release()
{
    int i;
    i = --m_iRefCount;
    ASSERT(m_iRefCount >= 0);
    if ((m_iRefCount == 0) && m_bAutoDestruct) {
        delete this;
    }
    return i;
}

/////////////////////////////////////////////////////////////////////////////
// CWave serialization

void CWave::Serialize(CArchive& ar)
{
    ar.Flush();
    CFile *fp = ar.GetFile();

    if (ar.IsStoring()) {
        ar.Write(&m_pcmfmt, sizeof(m_pcmfmt));
    } else {
        ar.Read(&m_pcmfmt, sizeof(m_pcmfmt));
    }
    m_BlockList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CWave commands

/*
@mfunc BOOL | CWave | Create | Create a new waveform.
@syntax BOOL Create(int samprate = 11025, int sampsize = 8,
int iSamples = 0);
@syntax BOOL Create(PCMWAVEFORMAT* pFmt, int iSamples = 0);
@parm int | nSamples | The number of samples in the new waveform.
@parm int | samprate | The sample rate in samples per second.
@parm int | sampsize | The sample sits in bits per sample.
@rdesc The return value is TRUE if the object is created, FALSE if not.
@comm The sample rate must currently be one of: 11025, 22050 or 44100.
The sample size must be 8 or 16. The format is always mono. A single
CWaveBlock is allocated as the buffer.
@xref <c CWave> <c CWaveBlock> <mf CWave::CWave>
*/

BOOL CWave::Create(PCMWAVEFORMAT* pFmt, int nSamples)
{
    return Create(pFmt->wf.nSamplesPerSec,
                  pFmt->wBitsPerSample,
                  nSamples);
}

BOOL CWave::Create(int samprate, int sampsize, int nsamples)
{
    // validate the args
    if ((samprate != 11025)
    && (samprate != 22050)
    && (samprate != 44100)) {
        TRACE("Invalid sample rate: %d", samprate);
        return FALSE;
    }
    if ((sampsize != 8) && (sampsize != 16)) {
        TRACE("Invalid sample size: %d", sampsize);
        return FALSE;
    }

    // free any existing memory
    m_BlockList.FreeAll();

    // allocate a wave block for the samples if required
    if (nsamples > 0) {
        int iBytes = nsamples * sampsize / 8;
        CWaveBlock* pBlock = new CWaveBlock(iBytes);
        if (!pBlock) {
            TRACE("Out of memory for samples");
            return FALSE;
        }
        // Add the block to the list
        m_BlockList.AppendBlock(pBlock);
    }

    // fill out the format info
    m_pcmfmt.wf.wFormatTag = WAVE_FORMAT_PCM;
    m_pcmfmt.wf.nChannels = 1; // we only do mono
    m_pcmfmt.wf.nSamplesPerSec = samprate;
    m_pcmfmt.wf.nAvgBytesPerSec = samprate;
    m_pcmfmt.wf.nBlockAlign = sampsize / 8; // no of bytes
    m_pcmfmt.wBitsPerSample = sampsize; 

    return TRUE;
}

void CWave::DecPlayCount() 
{
    ASSERT(m_iPlayCount > 0);
    m_iPlayCount--;
    if (m_iPlayCount == 0) {
        // See if there is anyone who wants to be notified
        if (m_pNotifyObj) {
            m_pNotifyObj->EndPlayback(this);
        }
        if (m_bAutoDestruct) {
            Release(); // and maybe die
        }
    }
}

/*
@mfunc BOOL | CWave | Play | Start playing.
@syntax BOOL Play(CWaveOutDevice* pWaveDevice = NULL,
CWaveNotifyObj = NULL);
@parm CWaveOutDevice* | pWaveDevice | A pointer to a
CWaveOutDevice object to be used to play the waveform.
@parm CWaveNotifyObj* | pNotify | A pointer to an optional
notification object.
@rdesc The return value is TRUE if playback starts, FALSE if not.
@comm If no output device is specified then the default device is used.
@xref <c CWave> <mf CWave::Stop>
*/

BOOL CWave::Play(CWaveOutDevice* pWaveDevice, CWaveNotifyObj* pNotify)
{
    if (pWaveDevice != NULL) {
        m_pOutDev = pWaveDevice;
    } else {
        m_pOutDev = &theDefaultWaveOutDevice;
    }
    if (m_bAutoDestruct) {
        AddRef();
    }
    m_pNotifyObj = pNotify;
    BOOL bRes = m_pOutDev->Play(this);
    if (m_bAutoDestruct) {
        Release();
    }
    return bRes;
}

/*
@mfunc BOOL | CWave | Record | Start recording.
@syntax BOOL Record(CWaveInDevice* pDev, int iBlockSize = 4096,
CWaveNotifyObj* pNotify = NULL);
@parm CWaveInDevice* | pDev | A pointer to a
CWaveInDevice object to be used to record the waveform from.
@parm int | iBlockSize | The size of the CWaveBlock objects to be 
used for the recording.
@parm CWaveNotifyObj* | pNotify | A pointer to a CWaveNotifyObj object to
be used to handle notification events such as the arrival of a new data
block.
@rdesc The return value is TRUE if recording starts, FALSE if not.
@xref <c CWave> <mf CWave::Stop>
*/

BOOL CWave::Record(CWaveInDevice* pDev,
                   int iBlockSize,
                   CWaveNotifyObj* pNotify)
{
    ASSERT(pDev);
    m_pInDev = pDev;
    m_pNotifyObj = pNotify;
    return pDev->Record(this, iBlockSize);
}

/*
@mfunc BOOL | CWave | Stop | Start playing or recording.
@syntax BOOL Stop();
@rdesc There is no return value.
@xref <c CWave>
*/

void CWave::Stop()
{
    if (m_pOutDev) m_pOutDev->Reset();
    if (m_pInDev) m_pInDev->Reset();
    m_pNotifyObj = NULL;
}

/*
@mfunc BOOL | CWave | Load | Load a waveform from a file.
@syntax BOOL Load(const char* pszFileName = NULL);
@syntax BOOL Load(CFile* fp);
@syntax BOOL Load(UINT hFile);
@syntax BOOL Load(HMMIO hmmio);
@parm char* | pszFileName | The path of a file to load from.  If NULL a
dialog box is shown to select the file.
@parm CFile* | fp | An open CFile object to load the waveform from.
@parm UINT | hFile | An open system file handle to load the waveform from.
@parm HMMIO | hmmio | An open HMMIO handle to load the waveform from.
@rdesc The return value is TRUE if the waveform is loaded, FALSE if not.
@comm Waveforms are contained in file conforming to the RIFF architecture.
@xref <c CWave> <mf CWave::LoadResource>
*/

BOOL CWave::Load(const char *pszFileName)
{
    CString strFile;    

    if ((pszFileName == NULL) 
    ||  (strlen(pszFileName) == 0)) {

        // Show an open file dialog to get the name
        CFileDialog dlg   (TRUE,    // open
                           NULL,    // no default extension
                           NULL,    // no initial file name
                           OFN_FILEMUSTEXIST
                             | OFN_HIDEREADONLY,
                           "Wave files (*.WAV)|*.WAV|All files (*.*)|*.*||");
        if (dlg.DoModal() == IDOK) {
            strFile = dlg.GetPathName();
        } else {
            return FALSE;
        }
    } else {    
        // copy the supplied file path
        strFile = pszFileName;                    
    }

    // Try to open the file for read access
    CFile file;
    if (! file.Open(strFile,
                    CFile::modeRead | CFile::shareDenyWrite)) {
        AfxMessageBox("Failed to open file");
        return FALSE;
    }

    BOOL bResult = Load(&file);
    file.Close();
    if (!bResult) AfxMessageBox("Failed to load file");
    return bResult;
}

BOOL CWave::Load(CFile *fp)
{
    return Load(fp->m_hFile);
}

BOOL CWave::Load(UINT hFile)
{
    HMMIO hmmio;
    MMIOINFO info;
    memset(&info, 0, sizeof(info));
    info.adwInfo[0] = hFile;
    hmmio = mmioOpen(NULL,
                     &info,
                     MMIO_READ | MMIO_ALLOCBUF);
    if (!hmmio) {
        TRACE("mmioOpen failed");
        return FALSE;
    }
    BOOL bResult = Load(hmmio);
    mmioClose(hmmio, MMIO_FHOPEN);
    return bResult;
}

BOOL CWave::Load(HMMIO hmmio)
{
    // Nuke any existing data in the object
    m_BlockList.FreeAll();
    // Check it's a RIFF WAVE file
    MMCKINFO ckFile;
    ckFile.fccType = mmioFOURCC('W','A','V','E');
    if (mmioDescend(hmmio,
                    &ckFile,
                    NULL,
                    MMIO_FINDRIFF) != 0) {
        TRACE("Not a RIFF or WAVE file");
        return FALSE;
    }
    // Find the 'fmt ' chunk
    MMCKINFO ckChunk;
    ckChunk.ckid = mmioFOURCC('f','m','t',' ');
    if (mmioDescend(hmmio,
                    &ckChunk,
                    &ckFile,
                    MMIO_FINDCHUNK) != 0) {
        TRACE("No fmt chunk in file");
        return FALSE;
    }
    // allocate some memory for the fmt chunk
    int iSize = ckChunk.cksize;
    WAVEFORMAT *pfmt = (WAVEFORMAT *) malloc(iSize);
    ASSERT(pfmt);
    // read the fmt chunk
    if (mmioRead(hmmio,
                 (char *)pfmt,
                 iSize) != iSize) {
        TRACE("Failed to read fmt chunk");
        free(pfmt);
        return FALSE;
    }
    // Check it's in PCM format
    if (pfmt->wFormatTag != WAVE_FORMAT_PCM) {
        TRACE("Not a PCM file");
        free(pfmt);
        return FALSE;
    }
    // get out of the fmt chunk
    mmioAscend(hmmio, &ckChunk, 0);
    // Find the 'data' chunk
    ckChunk.ckid = mmioFOURCC('d','a','t','a');
    if (mmioDescend(hmmio,
                    &ckChunk,
                    &ckFile,
                    MMIO_FINDCHUNK) != 0) {
        TRACE("No data chunk in file");
        free(pfmt);
        return FALSE;
    }
    // allocate some memory for the data chunk
    iSize = ckChunk.cksize;
    void *pdata = malloc(iSize);
    if (!pdata) {
        TRACE("No mem for data");
        free(pfmt);
        return FALSE;
    }
    // read the data chunk
    if (mmioRead(hmmio,
                 (char *)pdata,
                 iSize) != iSize) {
        TRACE("Failed to read data chunk");
        free(pfmt);
        free(pdata);
        return FALSE;
    }
    // Copy the header info
    memcpy(&m_pcmfmt, pfmt, sizeof(m_pcmfmt));
    // Wrap a CWaveBlock object around what we have
    CWaveBlock* pBlock = new CWaveBlock(pdata,
                                        iSize,
                                        iSize/(m_pcmfmt.wBitsPerSample / 8));
    ASSERT(pBlock);
    m_BlockList.AppendBlock(pBlock);

    return TRUE;
}

/*
@mfunc BOOL | CWave | LoadResource | Load a waveform from a resource.
@syntax BOOL LoadResource(WORD wID);
@parm WORD | wID | A WAVE resource id to load the waveform from.
@rdesc The return value is TRUE if the waveform is loaded, FALSE if not.
@comm Waveforms must be included in the resource script as type WAVE.
@xref <c CWave> <mf CWave::Load>
*/

BOOL CWave::LoadResource(WORD wID)
{
    ASSERT(wID);
    HINSTANCE hInst = AfxGetResourceHandle();
    HRSRC hrsrc = ::FindResource(hInst,
                                 MAKEINTRESOURCE(wID), "WAVE");
    if (!hrsrc) {
        TRACE("WAVE resource not found");
        return FALSE;
    }
    HGLOBAL hg = ::LoadResource(hInst,
                                hrsrc);
    if (!hg) {
        TRACE("Failed to load WAVE resource");
        return FALSE;
    }
    char* pRes = (char*) ::LockResource(hg);
    ASSERT(pRes);
    int iSize = ::SizeofResource(hInst, hrsrc);

    // Mark the resource pages as read/write so the mmioOpen
    // won't fail
    DWORD dwOldProt;
    BOOL b = ::VirtualProtect(pRes,
                              iSize,
                              PAGE_READWRITE,
                              &dwOldProt);
    ASSERT(b);

    // Open the memory block as an HMMIO object
    HMMIO hmmio;
    MMIOINFO info;
    memset(&info, 0, sizeof(info));
    info.fccIOProc = FOURCC_MEM;
    info.pchBuffer = pRes;
    info.cchBuffer = iSize;

    hmmio = mmioOpen(NULL,
                     &info,
                     MMIO_READ);
    if (!hmmio) {
        TRACE("mmioOpen failed. Error %d\n", info.wErrorRet);
        return FALSE;
    }
    BOOL bResult = Load(hmmio);
    mmioClose(hmmio, MMIO_FHOPEN);

    // Note: not required to unlock or free the resource in Win32
    return bResult;
}


/*
@mfunc int | CWave | GetNumSamples | Get the number of samples in
the waveform.
@syntax int GetNumSamples();
@rdesc The return value is the total number of samples in the waveform.
This is the sum of the number of samples in all the CWaveBlocks 
associated with the CWave object.
@xref <c CWave> <c CWaveBlock>
*/

int CWave::GetNumSamples()
{
    int iSamples = 0;
    // Walk the block list adding each sample count
    POSITION pos = m_BlockList.GetHeadPosition();
    while (pos) {
        CWaveBlock* pBlock = m_BlockList.GetNext(pos);
        iSamples += pBlock->GetNumSamples();
    }
    return iSamples;
}

/*
@mfunc int | CWave | GetSample | Get a single sample from
the waveform.
@syntax int GetSample(int iSample);
@parm int | iSample | The sample number to retrieve.
@rdesc The return value is the sample at the given position or
zero if the sample number is out of range. the sample is always returned 
as a 16 bit signed value.
Note that this function isn't very speedy and for better performance
you should get the block list and manipulate the data from the blocks
directly.
@xref <c CWave> <c CWaveBlock> <mf CWave::GetNumSamples>
*/

int CWave::GetSample(int iIndex)
{
    int iBlockSamples = 0;
    // Walk the block list until we get to the block
    // containing the sample we want
    POSITION pos = m_BlockList.GetHeadPosition();
    while (pos) {
        CWaveBlock* pBlock = m_BlockList.GetNext(pos);
        ASSERT(pBlock);
        iBlockSamples = pBlock->GetNumSamples();
        if (iBlockSamples > iIndex) {
            // it's in this block
            switch (m_pcmfmt.wBitsPerSample) {
            case 8: {
                BYTE *p = (BYTE *) pBlock->GetSamples();
                int i = p[iIndex]; // 0 - 255;
                return (i - 128) * 256;
                } break;
            case 16: {
                ASSERT(sizeof(short int) == 2);
                short int *p = (short int *) pBlock->GetSamples();
                return p[iIndex];
                } break;
            default:
                ASSERT(0); // bogus sample size
                return 0;
            }
        } else {
            // Move on to the next block
            iIndex -= iBlockSamples;
        }
    }
    ASSERT(0); // Sample out of range
    return 0;
}

void CWave::NewData(CWaveBlock* pBlock)
{
    if (m_pNotifyObj) {
        m_pNotifyObj->NewData(this, pBlock);
    }
}

/*
@mfunc void | CWave | DeleteAll | Delete all the data in the waveform
releasing all the CWaveBlock objects it owns.
@syntax void ReleaseAll();
@rdesc There is no return value.
@xref <c CWave> <c CWaveBlock>
*/

void CWave::DeleteAll()
{
    m_BlockList.FreeAll();
}

/////////////////////////////////////////////////////////////////////////////
// CWaveBlock

IMPLEMENT_SERIAL(CWaveBlock, CObject, 0 /* schema number*/ )

/*
@mfunc void | CWaveBlock | CWaveBlock | Constructor.
@syntax CWaveBlock();
@syntax CWaveBlock(int iSize);
@syntax CWaveBlock(void* pData, int iSize, int iSamples);
@parm int | iSize | The size of the block in bytes.
@parm void* | pData | A pointer to a memory block containing the data.
@parm int | iSamples | The number of samples in the memory block.
@rdesc There is no return value.
@xref <c CWaveBlock>
*/

CWaveBlock::CWaveBlock()
{
    m_pSamples = NULL;
    m_iSize = 0;
    m_iNumSamples = 0;
}

CWaveBlock::CWaveBlock(int iSize)
{
    m_pSamples = malloc(iSize);
    if (m_pSamples) {
        m_iSize = iSize;
    }
    m_iNumSamples = 0;
}

CWaveBlock::CWaveBlock(void* pData, int iSize, int iSamples)
{
    ASSERT(pData);
    ASSERT(iSize);
    m_pSamples = pData;
    m_iSize = iSize;
    m_iNumSamples = iSamples;
}

CWaveBlock::~CWaveBlock()
{
    if (m_pSamples) free(m_pSamples);
}

void CWaveBlock::Serialize(CArchive& ar)
{
    ar.Flush();
    CFile *fp = ar.GetFile();

    if (ar.IsStoring()) {
        ar.Write(&m_iNumSamples, sizeof(m_iNumSamples));
        ar.Write(&m_iSize, sizeof(m_iSize));
        if (m_iSize) {
            ASSERT(m_pSamples);
            ar.Write(m_pSamples, m_iSize);
        }
    } else {
        ar.Read(&m_iNumSamples, sizeof(m_iNumSamples));
        ar.Read(&m_iSize, sizeof(m_iSize));
        if (m_iSize) {
            m_pSamples = malloc(m_iSize);
            if (m_pSamples) {
                ar.Read(m_pSamples, m_iSize);
            }
        }
    }
}

/*
@mfunc int | CWaveBlock | GetSample | Get a single sample from
the block.
@syntax int GetSample(int iSample, int iSampleSize);
@parm int | iSample | The sample number to retrieve.
@parm int | iSampleSize | the number of bits per sample.
@rdesc The return value is the sample at the given position or
zero if the sample number is out of range. the sample is always returned 
as a 16 bit signed value.
Note that this function isn't very speedy and for better performance
you should get the data pointer and manipulate the data from the block
directly.
@xref <c CWave> <c CWaveBlock> <mf CWaveBlock::GetNumSamples>
<mf CWave::GetSampleSize>
*/

int CWaveBlock::GetSample(int iIndex, int iSampleSize)
{
    ASSERT(iIndex >= 0);
    ASSERT(iIndex < m_iNumSamples);
    switch (iSampleSize) {
    case 8: {
        BYTE *p = (BYTE *) m_pSamples;
        int i = p[iIndex]; // 0 - 255;
        return (i - 128) * 256;
        } break;
    case 16: {
        ASSERT(sizeof(short int) == 2);
        short int *p = (short int *) m_pSamples;
        return p[iIndex];
        } break;
    default:
        break;
    }
    ASSERT(0); // bogus sample size
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWaveBlockList

IMPLEMENT_SERIAL(CWaveBlockList, CObList, 0 /* schema number*/ )

CWaveBlockList::CWaveBlockList()
{
}

CWaveBlockList::~CWaveBlockList()
{
}


void CWaveBlockList::Serialize(CArchive& ar)
{
    CObList::Serialize(ar);
}

/*
@mfunc void | CWaveBlockList | FreeAll | Remove and delete all 
wave blocks from the list.
@syntax FreeAll();
@rdesc There is no return value.
@xref <c CWaveBlockList> <c CWaveBlock>
*/

void CWaveBlockList::FreeAll()
{
    while(!IsEmpty()) {
        CWaveBlock* ptr = RemoveHead();
        ASSERT(ptr);
        delete ptr;
    }
}
    
