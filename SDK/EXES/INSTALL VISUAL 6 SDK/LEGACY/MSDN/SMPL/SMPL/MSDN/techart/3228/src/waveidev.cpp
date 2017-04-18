// waveidev.cpp : implementation file
// @doc


#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifndef _DEBUG
#define MMERR(n) 0
#else
extern void MMERR(MMRESULT mmr); // in WAVEODEV.CPP
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaveInDevice

CWaveInDevice::CWaveInDevice()
{
    m_hInDev = NULL;
    m_iBlockCount = 0;
    m_iBlockSize = 4096;
}

CWaveInDevice::~CWaveInDevice()
{
}

BEGIN_MESSAGE_MAP(CWaveInDevice, CWnd)
    //{{AFX_MSG_MAP(CWaveInDevice)
    ON_MESSAGE(MM_WIM_DATA, OnWimData)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWaveInDevice::Create()
{
    if (!CreateEx(0,
                  AfxRegisterWndClass(0),
                  "Wave Wnd",
                  WS_POPUP,
                  0,
                  0,
                  0,
                  0,
                  NULL,
                  NULL)) {
        TRACE("Failed to create wave notification window");
        return FALSE;
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWaveInDevice message handlers

LRESULT CWaveInDevice::OnWimData(WPARAM w, LPARAM l)
{
    ASSERT(l);
    WAVEHDR* phdr = (WAVEHDR*) l;
    CWave* pWave = (CWave*)(phdr->dwUser);
    ASSERT(pWave->IsKindOf(RUNTIME_CLASS(CWave)));
    CWaveInDevice* pInDev = pWave->GetInDevice();
    ASSERT(pInDev);
    pInDev->WaveInData(pWave, phdr);
    return 0;
}

/*
@mfunc BOOL | CWaveInDevice | IsOpen | Test if the input device is open.
@syntax  BOOL IsOpen();
@rdesc The return value is TRUE if the device is open, FALSE if not.
@xref <c CWaveInDevice> <c CWave> <mf CWaveInDevice::Open>
*/

BOOL CWaveInDevice::IsOpen()
{
    return m_hInDev ? TRUE : FALSE;
}

/*
@mfunc BOOL | CWaveInDevice | Open | Open an input device.
@syntax  BOOL Open(int iID, WAVEFORMAT* pFormat);
@syntax  BOOL Open(int iID, PCMWAVEFORMAT* pFormat);
@parm int | iID | The ID of the input device to open.
@parm WAVEFORMAT* | pFormat | A pointer to a WAVEFORMAT structure
describing the format the device is to be opened for.
@parm PCMWAVEFORMAT* | pFormat | A pointer to a PCMWAVEFORMAT structure
describing the format the device is to be opened for.
@rdesc The return value is TRUE if the device is opened, FALSE if not.
@comm The function will fail if the device is already open in a different
format or cannot support the format.
@xref <c CWaveInDevice> <c CWave>
*/

BOOL CWaveInDevice::Open(int iID, WAVEFORMAT* pFormat)
{
    MMRESULT mmr;

    // Make sure we have a callback window
    if (!m_hWnd) {
        Create(); // Create the window
        ASSERT(m_hWnd);
    }

    // See if already open for this format
    if (IsOpen()) {
        // See if it can handle this format
        if (CanDoFormat(pFormat)) {
            return TRUE;
        } else {
            TRACE("Open for different format");
            return FALSE;
        }
    }

    // See if we can open for this format
    mmr = waveInOpen(&m_hInDev,
                     iID, 
                     pFormat, 
                     (DWORD)(GetSafeHwnd()), 
                     0, 
                     CALLBACK_WINDOW);
    if (mmr != 0) {
        MMERR(mmr);
        return FALSE;
    }

    return TRUE;
}

/*
@mfunc BOOL | CWaveInDevice | CanDoFormat | Test if the input device supports
a given format.
@syntax  BOOL CanDoFormat(WAVEFORMAT* pFormat);
@parm WAVEFORMAT* | pFormat | A pointer to a WAVEFORMAT structure
describing the format.
@rdesc The return value is TRUE if the device supports the format,
FALSE if not.
@comm The function will fail if the device is not open.
@xref <c CWaveInDevice> <c CWave> <mf CWaveInDevice::Open>
*/

BOOL CWaveInDevice::CanDoFormat(WAVEFORMAT* pFormat)
{
    MMRESULT mmr;

    if (!IsOpen()) {
        TRACE("Not open");
        return FALSE;
    }
    HWAVEIN hDev = NULL;
    mmr = waveInOpen(&hDev, 
                     WAVE_MAPPER, 
                     pFormat, 
                     NULL, 
                     0, 
                     WAVE_FORMAT_QUERY);
    if (mmr != 0) {
        MMERR(mmr);
        return FALSE;
    }
    return TRUE;
}

/*
@mfunc BOOL | CWaveInDevice | Close | Close the device.
@syntax  BOOL Close();
@rdesc The return value is TRUE if the device is closed, FALSE if not.
@xref <c CWaveInDevice> <c CWave>
*/

BOOL CWaveInDevice::Close()
{
    if (m_hInDev) {
        // close the device
        waveInReset(m_hInDev);
        MMRESULT mmr = waveInClose(m_hInDev);
        if (mmr != 0) {
            MMERR(mmr);
        }
        m_hInDev = NULL;
    }
    // Destroy the window
    DestroyWindow();
    ASSERT(m_hWnd == NULL);
    return TRUE;
}

/*
@mfunc BOOL | CWaveInDevice | Record | Start recording.
@syntax  BOOL Record(CWave* pWave, int iBlockSize = 4096);
@parm CWave* | pWave | A pointer to a CWave object in which the recorded
data is to be stored.
@parm int | iBlockSize | The size of the data blocks to be used. 
@rdesc The return value is TRUE if recording is started successfully,
FALSE if not.
@comm If the device is not currently open then an attempt is made
to open any device which supports the format defined in the CWave object.
If the device is already open, a test is made to ensure that the format in the 
CWave object is supported by the device.  If the format is not suported
the function fails.
@xref <c CWaveInDevice> <c CWave> <mf CWaveInDevice::Reset>
*/

BOOL CWaveInDevice::Record(CWave* pWave,
                           int iBlockSize)
{
    // See if the device is already open
    if (IsOpen()) {
        // See if it supports this format
        if (!CanDoFormat(pWave->GetFormat())) {
            TRACE("Input device is already open and doesn't support format");
            return FALSE;
        }
    } else {
        // Try to open any device
        if (!Open(WAVE_MAPPER, pWave->GetFormat())) {
            TRACE("No input device supports format");
            return FALSE;
        }
    }

    m_iBlockSize = iBlockSize;
    // Allocate two buffers and
    // send them both to the device driver.

    // Allocate a header
    WAVEHDR* phdr = (WAVEHDR*)malloc(sizeof(WAVEHDR));
    ASSERT(phdr);
    // fill out the wave header
    memset(phdr, 0, sizeof(WAVEHDR));
    phdr->lpData = (BYTE*)malloc(iBlockSize);
    ASSERT(phdr->lpData);
    phdr->dwBufferLength = iBlockSize;
    phdr->dwUser = (DWORD)(void*)pWave;  // so we can find the object 

    // Prepare the header
    MMRESULT mmr = waveInPrepareHeader(m_hInDev,
                                       phdr,
                                       sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
        return FALSE;
    }

    // Send it to the driver
    mmr = waveInAddBuffer(m_hInDev,
                          phdr,
                          sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
        return FALSE;
    }

     // Allocate a header
    phdr = (WAVEHDR*)malloc(sizeof(WAVEHDR));
    ASSERT(phdr);
    // fill out the wave header
    memset(phdr, 0, sizeof(WAVEHDR));
    phdr->lpData = (BYTE*)malloc(iBlockSize);
    ASSERT(phdr->lpData);
    phdr->dwBufferLength = iBlockSize;
    phdr->dwUser = (DWORD)(void*)pWave;  // so we can find the object 

    // Prepare the header
    mmr = waveInPrepareHeader(m_hInDev,
                              phdr,
                              sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
        return FALSE;
    }

    // Send it to the driver
    mmr = waveInAddBuffer(m_hInDev,
                          phdr,
                          sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
        return FALSE;
    }

    // Start the recording
    mmr = waveInStart(m_hInDev);
    if (mmr) {
        MMERR(mmr);
        return FALSE;
    }

    return TRUE;
}

/*
@mfunc void | CWaveInDevice | Reset | Stop recording and free buffers.
@syntax  void Reset();
@rdesc There is no return value.
@xref <c CWaveInDevice> <c CWave>
*/

void CWaveInDevice::Reset()
{
    if (!m_hInDev) return; 
    MMRESULT mmr = waveInReset(m_hInDev);
    if (mmr) MMERR(mmr);
}

void CWaveInDevice::WaveInData(CWave* pWave, WAVEHDR* pHdr)
{
    // Send another block to the driver
    // Allocate a header
    WAVEHDR* phdrNew = (WAVEHDR*)malloc(sizeof(WAVEHDR));
    ASSERT(phdrNew);
    // fill out the wave header
    memset(phdrNew, 0, sizeof(WAVEHDR));
    phdrNew->lpData = (BYTE*)malloc(m_iBlockSize);
    ASSERT(phdrNew->lpData);
    phdrNew->dwBufferLength = m_iBlockSize;
    phdrNew->dwUser = (DWORD)(void*)pWave;  // so we can find the object 

    // Prepare the header
    MMRESULT mmr = waveInPrepareHeader(m_hInDev,
                                       phdrNew,
                                       sizeof(WAVEHDR));
    if (mmr) MMERR(mmr);

    // Send it to the driver
    mmr = waveInAddBuffer(m_hInDev,
                          phdrNew,
                          sizeof(WAVEHDR));
    if (mmr) MMERR(mmr);

    // Now handle the block that was completed
    // Unprepare the header
    mmr = waveInUnprepareHeader(m_hInDev,
                                pHdr,
                                sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
    }

    // See if it contains any data
    if (pHdr->dwBytesRecorded != 0) {
        // Create a wave block and attach it to the wave
        PCMWAVEFORMAT* pfmt = (PCMWAVEFORMAT*) pWave->GetFormat();
        ASSERT(pfmt->wf.wFormatTag = WAVE_FORMAT_PCM);
        int iSampleSize = pfmt->wBitsPerSample / 8;
        int iSamples = pHdr->dwBytesRecorded / iSampleSize;
        CWaveBlock* pWB = new CWaveBlock(pHdr->lpData,
                                         pHdr->dwBufferLength,
                                         iSamples);
        pWave->GetBlockList()->AppendBlock(pWB);
        pWave->NewData(pWB);
    } else {
        // Delete the block
        free(pHdr->lpData);
    }

    // free the header
    free(pHdr);
}

