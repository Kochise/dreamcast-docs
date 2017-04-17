/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996, 1997 Microsoft Corporation

Module Name:

    DSUtil.cpp

Abstract:

   Contains routines for handling sounds from resources

-------------------------------------------------------------------*/


#include "Microphone.hpp"

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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetWaveResource

Description:

    Load a WAV file from the executable's Resource file.
    
Arguments:

    LPCTSTR      tszName         -  Name of the WAV file to load

    WAVEFORMATEX **ppWaveHeader  -  Fill this with pointer to wave header

    BYTE         **ppbWaveData   -  Fill this with pointer to wave data

    DWORD        **pcbWaveSize   -  Fill this with wave data size.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
GetWaveResource(LPCTSTR tszName, WAVEFORMATEX **ppWaveHeader,
                BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    HRSRC   hResInfo;
    HGLOBAL hResData;
    void    *pvRes;

    // Find the specifed WAV resource
    hResInfo = FindResource(g_hinst, tszName, TEXT("WAV"));
    if (hResInfo == NULL)
        return FALSE;

    // Load the Resource
    hResData = LoadResource(g_hinst, hResInfo);
    if (hResData == NULL)
        return FALSE;

    // Lock the Resource
    pvRes = LockResource(hResData);
    if (pvRes == NULL)
        return FALSE;

    // Read and parse the Resource
    if (ParseWaveFile(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize) == NULL)
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FillSoundBuffer

Description:

    Copies the Sound data to the specified DirecSoundBuffer's data file
    
Arguments:

    LPCTSTR      tszName         -  Name of the WAV file to load

    WAVEFORMATEX **ppWaveHeader  -  Fill this with pointer to wave header

    BYTE         **ppbWaveData   -  Fill this with pointer to wave data

    DWORD        **pcbWaveSize   -  Fill this with wave data size.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
FillSoundBuffer(IDirectSoundBuffer *pdsb, BYTE *pbWaveData, DWORD dwWaveSize)
{
    LPVOID pMem1, pMem2;
    DWORD  dwSize1, dwSize2;

    if (!pdsb || !pbWaveData || !dwWaveSize)
        return FALSE;

    g_errLast = pdsb->Lock(0, dwWaveSize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
    if (CheckError(TEXT("Lock SoundBuffer")))
        return FALSE;

    memcpy(pMem1, pbWaveData, dwSize1);

    if (dwSize2 != 0)
        memcpy(pMem2, pbWaveData+dwSize1, dwSize2);

    pdsb->Unlock(pMem1, dwSize1, pMem2, dwSize2);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadSoundBuffer

Description:

    Creates a DirectSoundBuffer and loads the specified file into it.
    
Arguments:

    LPCTSTR      tszName         -  Name of the WAV file to load

Return Value:

    Pointer to the created buffer (NULL on failure)

-------------------------------------------------------------------*/
IDirectSoundBuffer *
LoadSoundBuffer(LPCTSTR tszName)
{
    IDirectSoundBuffer *pdsb = NULL;
    DSBUFFERDESC dsbd = {0};
    BYTE *pbWaveData;

    if (GetWaveResource(tszName, &dsbd.lpwfxFormat, &pbWaveData, &dsbd.dwBufferBytes))
    {
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2;

        if (SUCCEEDED(g_pds->CreateSoundBuffer(&dsbd, &pdsb, NULL)))
        {
            if (!FillSoundBuffer(pdsb, pbWaveData, dsbd.dwBufferBytes))
            {
                pdsb->Release();
                pdsb = NULL;
            }
        }
        else
            pdsb = NULL;
    }

    return pdsb;
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
    IDirectSoundBuffer *pdsb = NULL;
    DSBUFFERDESC       dsbd;
    WAVEFORMATEX       waveformatex;

    // Set up the Wave format description
    waveformatex.wFormatTag      = WAVE_FORMAT_PCM;
    waveformatex.nChannels       = 1;
    waveformatex.nSamplesPerSec  = gcSamplesPerSec;
    waveformatex.wBitsPerSample  = gcBitsPerSample;
    waveformatex.nBlockAlign     = (waveformatex.nChannels * waveformatex.wBitsPerSample) / 8;
    waveformatex.nAvgBytesPerSec = waveformatex.nSamplesPerSec * waveformatex.nBlockAlign;
    waveformatex.cbSize          = 0;

    // Set up the DirectSoundCapture buffer description
    dsbd.dwSize        = sizeof(DSCBUFFERDESC);
    dsbd.dwFlags       = DSBCAPS_CTRLDEFAULT;
    dsbd.dwBufferBytes = gcBufferSize;
    dsbd.dwReserved    = 0;
    dsbd.lpwfxFormat   = &waveformatex;

    g_errLast = g_pds->CreateSoundBuffer(&dsbd, &pdsb, NULL);
    if (CheckError(TEXT("Create DirectSound Buffer")))
        return NULL;

    return pdsb;
}

BOOL
ClearSoundBuffer(IDirectSoundBuffer *pdsb)
{
    PBYTE pOutBuf1, pOutBuf2;
    DWORD dwOutBuf1Size, dwOutBuf2Size;

    g_errLast = pdsb->Lock(0, gcBufferSize, (PVOID*)&pOutBuf1, &dwOutBuf1Size, (PVOID*)&pOutBuf2, &dwOutBuf2Size, 0);
    if (CheckError(TEXT("Lock Output Buffer")))
        return FALSE;

    memset(pOutBuf1, 0, dwOutBuf1Size);

    if (pOutBuf2 != NULL)
    {
        memset(pOutBuf2, 0, dwOutBuf2Size);
    }

    g_errLast = pdsb->Unlock(pOutBuf1, dwOutBuf1Size, pOutBuf2, dwOutBuf2Size);
    if (CheckError(TEXT("Lock Output Buffer")))
        return FALSE;

    return TRUE;
}

// Copies the contents of the DSound buffer's input buffer to the same DSound buffer's output buffer.
BOOL
CopyInputToOutput(IDirectSoundCaptureBuffer *pdscb, IDirectSoundBuffer *pdsb, int nHalf)
{
    PBYTE pInBuf1, pInBuf2;
    DWORD dwInBuf1Size, dwInBuf2Size;
    PBYTE pOutBuf1, pOutBuf2;
    DWORD dwOutBuf1Size, dwOutBuf2Size;

    // Lock down the two buffers.
    if (nHalf == 0)
        g_errLast = pdscb->Lock(0, gcBufferSize/2, (PVOID*)&pInBuf1, &dwInBuf1Size, (PVOID*)&pInBuf2, &dwInBuf2Size, 0);
    else
        g_errLast = pdscb->Lock(gcBufferSize/2, gcBufferSize/2, (PVOID*)&pInBuf1, &dwInBuf1Size, (PVOID*)&pInBuf2, &dwInBuf2Size, 0);
    if (CheckError(TEXT("Lock Input Buffer")))
    {
        RetailOutput(TEXT("Microphone unplugged\r\n"));
        return FALSE;
    }
    
    g_errLast = pdsb->Lock(0, gcBufferSize / 2, (PVOID*)&pOutBuf1, &dwOutBuf1Size, (PVOID*)&pOutBuf2, &dwOutBuf2Size, DSBLOCK_FROMWRITECURSOR);
    if (CheckError(TEXT("Lock Output buffer")))
        return FALSE;

    // Copy the memory from the input to the output buffer
    memcpy(pOutBuf1, pInBuf1, dwOutBuf1Size);
    if (dwOutBuf1Size < dwInBuf1Size && pOutBuf2 != NULL)
        memcpy(pOutBuf2, pInBuf1 + dwOutBuf1Size, dwInBuf1Size - dwOutBuf1Size);

    // Unlock the two buffers
    g_errLast = pdsb->Unlock(pOutBuf1, dwOutBuf1Size, pOutBuf2, dwOutBuf2Size);
    if (CheckError(TEXT("Unlock output buffer")))
        return FALSE;

    g_errLast = pdscb->Unlock(pInBuf1, dwInBuf1Size, pInBuf2, dwInBuf2Size);
    if (CheckError(TEXT("Unlock input buffer")))
    {
        RetailOutput(TEXT("Microphone unplugged\r\n"));
        return FALSE;
    }

    return TRUE;
}

