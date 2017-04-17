/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996, 1997 Microsoft Corporation

Module Name:

    DSUtil.cpp

Abstract:

   Contains routines for handling sounds from resources

-------------------------------------------------------------------*/


#include "StreamingSound.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTSOUND	    g_pds;              // The DirectSound object

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirectSound

Description:

    Initialize the DirectSound object

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
InitDirectSound()
{
    // Create the DirectSound object
    g_errLast = DirectSoundCreate(NULL, &g_pds, NULL);
    if (CheckError(TEXT("DirectSoundCreate")))
        return FALSE;

    // Set the DirectSound cooperative level
    g_errLast = g_pds->SetCooperativeLevel(g_hwndApp, DSSCL_NORMAL);
    if (CheckError(TEXT("DirectSoundCreate")))
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateSoundBuffer

Description:

    Creates an empty DirectSoundBuffer
    
Arguments:

    int     nSamplesPerSec      - Recording resolution (ex: 11025)

    WORD    wBitsPerSample      - Recording resoultion (ex: 16)

    DWORD   dwBufferSize        - length of recording time (ex: 16 * 1024)

Return Value:

    Pointer to the created buffer (NULL on failure)

-------------------------------------------------------------------*/
IDirectSoundBuffer *
CreateSoundBuffer(int nSamplesPerSec, WORD wBitsPerSample, DWORD dwBufferSize)
{
    IDirectSoundBuffer *pdsb        = NULL;
    DSBUFFERDESC       dsbd         = {0};
    WAVEFORMATEX       waveformatex = {0};

    // Set up the Wave format description
    waveformatex.wFormatTag      = WAVE_FORMAT_PCM;
    waveformatex.nChannels       = 2;
    waveformatex.nSamplesPerSec  = nSamplesPerSec;
    waveformatex.wBitsPerSample  = wBitsPerSample;
    waveformatex.nBlockAlign     = (waveformatex.nChannels * waveformatex.wBitsPerSample) / 8;
    waveformatex.nAvgBytesPerSec = waveformatex.nSamplesPerSec * waveformatex.nBlockAlign;
    waveformatex.cbSize          = 0;
    dsbd.dwSize                  = sizeof(dsbd);
    dsbd.dwBufferBytes           = dwBufferSize;
    dsbd.dwFlags                 = DSBCAPS_CTRLDEFAULT | DSBCAPS_LOCSOFTWARE;
    dsbd.lpwfxFormat             = &waveformatex;

    g_errLast = g_pds->CreateSoundBuffer(&dsbd, &pdsb, NULL);
    if (CheckError(TEXT("Create DirectSound Buffer")))
        return NULL;

    return pdsb;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PrepareForStreaming

Description:

    Prepares the specified buffer for streaming by setting up events
    to notify the app when the buffer has reached the halfway point or
    the end point - at either of those, it starts filling in one side of
    the buffer while playing the other side of the buffer (assuming it's
    repeating).
    
Arguments:

    IDirectSoundBuffer *pdsb        - The sound buffer to prepare

    DWORD dwBufferSize;             - Size of the buffer

    HANDLE *phEventNotify           - This event set when halfway or at end

    HANDLE *phEventDone             - This event set when sound is done playing

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
PrepareForStreaming(IDirectSoundBuffer *pdsb, DWORD dwBufferSize, HANDLE *phEventNotify, HANDLE *phEventDone)
{
    IDirectSoundNotify *pdsn;
	DSBPOSITIONNOTIFY  rgdsbpn[3];

    // Get a DirectSoundNotify interface so that we can set the events.
    g_errLast = pdsb->QueryInterface(IID_IDirectSoundNotify, (void **)&pdsn);
    if (CheckError(TEXT("IDirectSoundBuffer::QueryInterface")))
        return FALSE;

    *phEventNotify = CreateEvent( NULL, FALSE, FALSE, NULL );

    rgdsbpn[0].hEventNotify = *phEventNotify;
    rgdsbpn[1].hEventNotify = *phEventNotify;
    rgdsbpn[2].hEventNotify = *phEventNotify;
    rgdsbpn[0].dwOffset     = dwBufferSize / 2;
    rgdsbpn[1].dwOffset     = dwBufferSize - 2;
    rgdsbpn[2].dwOffset     = DSBPN_OFFSETSTOP;

    *phEventDone = CreateEvent( NULL, FALSE, FALSE, NULL );

    g_errLast = pdsn->SetNotificationPositions(3, rgdsbpn);
    if (CheckError(TEXT("Set Notification Positions")))
        return FALSE;

    // No longer need the DirectSoundNotify interface, so release it
    pdsn->Release();

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ParseWaveFile

Description:

    Get the Wave File header, size, and data pointer...
    
Arguments:

    void         *pvWaveFile     -  Pointer to the wav file to parse

    WAVEFORMATEX **ppWaveHeader  -  Fill this with pointer to wave header

    BYTE         **ppbWaveData   -  Fill this with pointer to wave data

    DWORD        **pcbWaveSize   -  Fill this with wave data size.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
ParseWaveFile(void *pvWaveFile, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    DWORD *pdw;
    DWORD *pdwEnd;
    DWORD dwRiff;
    DWORD dwType;
    DWORD dwLength;

    if (ppWaveHeader)
        *ppWaveHeader = NULL;

    if (ppbWaveData)
        *ppbWaveData = NULL;

    if (pcbWaveSize)
        *pcbWaveSize = 0;

    pdw = (DWORD *)pvWaveFile;
    dwRiff   = *pdw++;
    dwLength = *pdw++;
    dwType   = *pdw++;

    // Check if it's a WAV format file
    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
        return FALSE;

    // Check if it's a RIFF format file
    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
        return FALSE;

    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    while (pdw < pdwEnd)
    {
        dwType = *pdw++;
        dwLength = *pdw++;

        switch (dwType)
        {
        case mmioFOURCC('f', 'm', 't', ' '):
            if (ppWaveHeader && !*ppWaveHeader)
            {
                if (dwLength < sizeof(WAVEFORMAT))
                    return FALSE;

                *ppWaveHeader = (WAVEFORMATEX *)pdw;

                if ((!ppbWaveData || *ppbWaveData) && (!pcbWaveSize || *pcbWaveSize))
                    return TRUE;
            }
            break;

        case mmioFOURCC('d', 'a', 't', 'a'):
            if ((ppbWaveData && !*ppbWaveData) || (pcbWaveSize && !*pcbWaveSize))
            {
                if (ppbWaveData)
                    *ppbWaveData = (LPBYTE)pdw;

                if (pcbWaveSize)
                    *pcbWaveSize = dwLength;

                if (!ppWaveHeader || *ppWaveHeader)
                    return TRUE;
            }
            break;
        }

        pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
    }

    return FALSE;
}

