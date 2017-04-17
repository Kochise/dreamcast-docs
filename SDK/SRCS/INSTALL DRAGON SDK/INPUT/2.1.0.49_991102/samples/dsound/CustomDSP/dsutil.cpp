/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996, 1997 Microsoft Corporation

Module Name:

    DSUtil.cpp

Abstract:

   Contains routines for handling sounds from resources

-------------------------------------------------------------------*/


#include "CustomDSP.hpp"

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
    g_pds->SetCooperativeLevel(g_hwndApp, DSSCL_NORMAL);

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

    Load a WAV file from the executable's Resource file or the specified file.
    
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
    HANDLE  hFile;
    BYTE    *rgbyFileTemp;
    unsigned long cbRead;
    DWORD   dwSize;

    // Find the specifed WAV resource
    hResInfo = FindResource(g_hinst, tszName, TEXT("WAV"));
    if (hResInfo == NULL)
        goto TryFile;

    // Load the Resource
    hResData = LoadResource(g_hinst, hResInfo);
    if (hResData == NULL)
        goto TryFile;

    // Lock the Resource
    pvRes = LockResource(hResData);
    if (pvRes == NULL)
        goto TryFile;

    // Read and parse the Resource
    if (ParseWaveFile(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize) != NULL)
        return TRUE;

TryFile:

    // Failed to load as a resource - try it as a file
    hFile = CreateFile(tszName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    dwSize = GetFileSize(hFile, NULL);

    rgbyFileTemp = (BYTE*) malloc(dwSize);
    if (!rgbyFileTemp)
        return FALSE;

    ReadFile (hFile, rgbyFileTemp, dwSize, &cbRead, NULL);
    CloseHandle(hFile);
    if (cbRead != dwSize)
        return FALSE;

    if (ParseWaveFile(rgbyFileTemp, ppWaveHeader, ppbWaveData, pcbWaveSize) == NULL)
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

    TRUE on success, FALSE on failure.

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
