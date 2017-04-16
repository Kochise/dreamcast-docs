// waveodev.cpp : implementation file
// @doc


#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// global items
CWaveOutDevice theDefaultWaveOutDevice;

/////////////////////////////////////////////////////////////////////////////
// CWaveOutDevice

CWaveOutDevice::CWaveOutDevice()
{
    m_hOutDev = NULL;
    m_iBlockCount = 0;
}

CWaveOutDevice::~CWaveOutDevice()
{
}

BEGIN_MESSAGE_MAP(CWaveOutDevice, CWnd)
    //{{AFX_MSG_MAP(CWaveOutDevice)
    ON_MESSAGE(MM_WOM_DONE, OnWomDone)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWaveOutDevice::Create()
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

#ifndef _DEBUG
#define MMERR(n) 0
#else
void MMERR(MMRESULT mmr)
{
    switch (mmr) {
    case WAVERR_BADFORMAT:
        TRACE("No wave device supports format");
        break;
    case MMSYSERR_NOMEM:
        TRACE("Out of memory");
        break;
    case MMSYSERR_ALLOCATED:
        TRACE("Resource is already allocated");
        break;
    case MMSYSERR_BADDEVICEID:
        TRACE("Bad device id");
        break;
    case MMSYSERR_INVALHANDLE:
        TRACE("Invalid device handle");
        break;
    case MMSYSERR_HANDLEBUSY:
        TRACE("Device in use by another thread");
        break;
    case WAVERR_UNPREPARED:
        TRACE("Header not prepared");
        break;
    default:
        TRACE("Unknown error");
        break;
    }
}
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaveOutDevice message handlers

LRESULT CWaveOutDevice::OnWomDone(WPARAM w, LPARAM l)
{
    ASSERT(l);
    WAVEHDR *phdr = (WAVEHDR *) l;
    CWave *pWave = (CWave *)(phdr->dwUser);
    ASSERT(pWave->IsKindOf(RUNTIME_CLASS(CWave)));
    CWaveOutDevice *pOutDev = pWave->GetOutDevice();
    ASSERT(pOutDev);
    pOutDev->WaveOutDone(pWave, phdr);
    return 0;
}

/*
@mfunc BOOL | CWaveOutDevice | IsOpen | Test if the output device is open.
@syntax  BOOL IsOpen();
@rdesc The return value is TRUE if the device is open, FALSE if not.
@xref <c CWaveOutDevice> <c CWave> <mf CWaveOutDevice::Open>
*/

BOOL CWaveOutDevice::IsOpen()
{
    return m_hOutDev ? TRUE : FALSE;
}

/*
@mfunc BOOL | CWaveOutDevice | Open | Open an output device.
@syntax  BOOL Open(int iID, WAVEFORMAT* pFormat);
@syntax  BOOL Open(int iID, PCMWAVEFORMAT* pFormat);
@parm int | iID | The ID of the output device to open.
@parm WAVEFORMAT* | pFormat | A pointer to a WAVEFORMAT structure
describing the format the device is to be opened for.
@parm PCMWAVEFORMAT* | pFormat | A pointer to a PCMWAVEFORMAT structure
describing the format the device is to be opened for.
@rdesc The return value is TRUE if the device is opened, FALSE if not.
@comm The function will fail if the device is already open in a different
format or cannot support the format. Note that this function
uses the WAVE_MAPPER option to open any suitable output device.
@xref <c CWaveOutDevice> <c CWave>
*/

BOOL CWaveOutDevice::Open(WAVEFORMAT *pFormat)
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
    mmr = waveOutOpen(&m_hOutDev,
                      WAVE_MAPPER, 
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
@mfunc BOOL | CWaveOutDevice | CanDoFormat | Test if the output device supports
a given format.
@syntax  BOOL CanDoFormat(WAVEFORMAT* pFormat);
@parm WAVEFORMAT* | pFormat | A pointer to a WAVEFORMAT structure
describing the format.
@rdesc The return value is TRUE if the device supports the format,
FALSE if not.
@comm The function will fail if the device is not open.
@xref <c CWaveOutDevice> <c CWave> <mf CWaveOutDevice::Open>
*/

BOOL CWaveOutDevice::CanDoFormat(WAVEFORMAT *pFormat)
{
    MMRESULT mmr;

    if (!IsOpen()) {
        TRACE("Not open");
        return FALSE;
    }
    HWAVEOUT hDev = NULL;
    mmr = waveOutOpen(&hDev, 
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
@mfunc BOOL | CWaveOutDevice | Close | Close the device.
@syntax  BOOL Close();
@rdesc The return value is TRUE if the device is closed, FALSE if not.
@xref <c CWaveOutDevice> <c CWave>
*/

BOOL CWaveOutDevice::Close()
{
    if (m_hOutDev) {
        // close the device
        waveOutReset(m_hOutDev);
        MMRESULT mmr = waveOutClose(m_hOutDev);
        if (mmr != 0) {
            MMERR(mmr);
        }
        m_hOutDev = NULL;
    }
    // Destroy the window
    DestroyWindow();
    ASSERT(m_hWnd == NULL);
    return TRUE;
}

/*
@mfunc BOOL | CWaveOutDevice | Play | Start playing.
@syntax  BOOL Record(CWave* pWave);
@parm CWave* | pWave | A pointer to a CWave object to be played.
@rdesc The return value is TRUE if playing is started successfully,
FALSE if not.
@xref <c CWaveOutDevice> <c CWave> <mf CWaveOutDevice::Reset>
*/

BOOL CWaveOutDevice::Play(CWave *pWave)
{
    if (!Open(pWave->GetFormat())) {
        return FALSE;
    }

    CWaveBlockList* pBL = pWave->GetBlockList();
    if (!pBL) return FALSE;

    POSITION pos = pBL->GetHeadPosition();
    if (!pos) return FALSE;
    
    // Inc the ref count if we're using it
    if (pWave->m_bAutoDestruct) pWave->AddRef();
    while (pos) {
        CWaveBlock* pBlock = pBL->GetNext(pos);
        ASSERT(pBlock);

        // Allocate a header
        WAVEHDR* phdr = (WAVEHDR*)malloc(sizeof(WAVEHDR));
        ASSERT(phdr);
        // fill out the wave header
        memset(phdr, 0, sizeof(WAVEHDR));
        phdr->lpData = (BYTE*) pBlock->GetSamples();
        phdr->dwBufferLength = pBlock->GetSize();
        phdr->dwUser = (DWORD)(void*)pWave;    // so we can find the object 

        // Prepare the header
        MMRESULT mmr = waveOutPrepareHeader(m_hOutDev,
                                            phdr,
                                            sizeof(WAVEHDR));
        if (mmr) {
            MMERR(mmr);
            return FALSE;
        }
        // Mark the wave as busy playing
        pWave->IncPlayCount();

        // Start it playing
        mmr = waveOutWrite(m_hOutDev,
                           phdr,
                           sizeof(WAVEHDR));
        if (mmr) {
            MMERR(mmr);
            return FALSE;
        }

        // Add one to the block count
        m_iBlockCount++;
    } // next block

    return TRUE;
}

/*
@mfunc void | CWaveOutDevice | Reset | Stop playing and free buffers.
@syntax  void Reset();
@rdesc There is no return value.
@xref <c CWaveOutDevice> <c CWave>
*/

void CWaveOutDevice::Reset()
{
    if (!m_hOutDev) return; 
    MMRESULT mmr = waveOutReset(m_hOutDev);
    if (mmr) MMERR(mmr);
}

void CWaveOutDevice::WaveOutDone(CWave *pWave, WAVEHDR *pHdr)
{
    // Unprepare the header
    MMRESULT mmr = waveOutUnprepareHeader(m_hOutDev,
                                          pHdr,
                                          sizeof(WAVEHDR));
    if (mmr) {
        MMERR(mmr);
    }
    // free the header
    free(pHdr);

    // decrement the block count
    ASSERT(m_iBlockCount > 0);
    m_iBlockCount--;
    if (m_iBlockCount == 0) {
        // Close the device
        Close();
    }

    pWave->DecPlayCount();
}

