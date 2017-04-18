/********************************************************************
 * sound.cpp
 *
 * Description
 *     DSound wrappers and helpers
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "sound.h"              // wrapper prototypes
#ifdef USE_FLASH                
#include "flashapi.h"           // MM Flash
#endif // USE_FLASH
				
/********************************************************************
 * Defines
 ********************************************************************/
#ifndef HSNDOBJ
#define HSNDOBJ HANDLE
#endif // HSNDOBJ

/********************************************************************
 * Global variables
 ********************************************************************/
LPDIRECTSOUND g_pds = NULL;     // DSound
				
/********************************************************************
 * CreateDirectSound
 *
 * Description
 *    Initialize DirectSound.
 *
 * Parameters
 *    hwnd     main application window
 * 
 * Returns
 *    TRUE     successfully initlized DirectSound
 *    FALSE    failed to initlize DirectSound
 ********************************************************************/
BOOL CreateDirectSound(HWND hwnd)
{
    // create the DirectSound object
    if (!SUCCEEDED(DirectSoundCreate(NULL, &g_pds, NULL)))
    {
        return FALSE;
    }
 
    // set the DirectSound cooperative level
    g_pds->SetCooperativeLevel(hwnd, DSSCL_NORMAL);

#ifdef USE_FLASH
    // tell the Flash Player
    FlashSetDirectSound(g_pds);
#endif USE_FLASH

    return TRUE;
}

/********************************************************************
 * DestroyDirectSound
 *
 * Description
 *    Uninitialize DirectSound.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void DestroyDirectSound(void)
{
    // release the DirectSound object
    if (g_pds)
    {
        g_pds->Release();
        g_pds = NULL;
    }
}

/********************************************************************
 * ParseWaveFile
 *
 * Description
 *    Parses a sound file for use in a sound buffer. See DSound 
 *    samples.
 *
 * Parameters
 *    pvWaveFile    data to parse
 *    ppWaveHeader  fill in with address of header
 *    ppbWaveData   fill in with address of sound data
 *    pcbWaveSize   fill in with size of sound data
 * 
 * Returns
 *    TRUE          parsed sucessfully
 *    FALSE         error in file
 ********************************************************************/
BOOL ParseWaveFile(void *pvWaveFile, WAVEFORMATEX **ppWaveHeader, 
                   BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    DWORD *pdw;
    DWORD *pdwEnd;
    DWORD dwRiff;
    DWORD dwType;
    DWORD dwLength;

    // initialize returned data
    if (ppWaveHeader)
    {
        *ppWaveHeader = NULL;
    }

    if (ppbWaveData)
    {
        *ppbWaveData = NULL; 
    }

    if (pcbWaveSize)
    {
        *pcbWaveSize = 0;
    }

    // get header data
    pdw = (DWORD *)pvWaveFile;
    dwRiff   = *pdw++;
    dwLength = *pdw++;
    dwType   = *pdw++;

    // check if it's a WAV format file
    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
    {
        return FALSE;
    }

    // check if it's a RIFF format file
    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
    {
        return FALSE;
    }

    // find end of data
    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    // find sound data
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
            if ((ppbWaveData && !*ppbWaveData) || 
                (pcbWaveSize && !*pcbWaveSize))
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

/********************************************************************
 * GetWaveResource
 *
 * Description
 *    Loads a sound resource and parses it. See DSound samples.
 *
 * Parameters
 *    tszName       name of sound in resources
 *    ppWaveHeader  fill in with address of header
 *    ppbWaveData   fill in with address of sound data
 *    pcbWaveSize   fill in with size of sound data
 * 
 * Returns
 *    TRUE          loaded and parsed sucessfully
 *    FALSE         error in file or in finding resource
 ********************************************************************/
BOOL GetWaveResource(LPCTSTR tszName, WAVEFORMATEX **ppWaveHeader, 
                     BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    HRSRC   hResInfo;
    HGLOBAL hResData;
    void    *pvRes;

    // find the specifed WAV resource
    hResInfo = FindResource(g_hInstance, tszName, TEXT("WAV"));
    if (hResInfo == NULL)
    {
        return FALSE;
    }

    // load the resource
    hResData = LoadResource(g_hInstance, hResInfo);
    if (hResData == NULL)
    {
        return FALSE;
    }

    // lock the resource
    pvRes = LockResource(hResData);
    if (pvRes == NULL)
    {
        return FALSE;
    }

    // read and parse the resource
    return ParseWaveFile(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize);
}

/********************************************************************
 * FillSoundBuffer
 *
 * Description
 *    Fill a DSound sound buffer with wave file data. See DSound 
 *    samples.
 *
 * Parameters
 *    pdsb          sound buffer to fill
 *    pbWaveData    wave data to put into buffer
 *    dwWaveSize    size of pbWaveData buffer
 * 
 * Returns
 *    TRUE          loaded buffer sucessfully
 *    FALSE         error loading buffer
 ********************************************************************/
BOOL FillSoundBuffer(IDirectSoundBuffer *pdsb, BYTE *pbWaveData, 
                     DWORD dwWaveSize)
{
    LPVOID pMem1, pMem2;
    DWORD  dwSize1, dwSize2;

    // validate parameters
    if (!pdsb || !pbWaveData || !dwWaveSize)
        return FALSE;

    // lock the buffer
    if (FAILED(pdsb->Lock(0, dwWaveSize, &pMem1, &dwSize1, &pMem2, 
               &dwSize2, 0)))
    {
        return FALSE;
    }

    // load the buffer
    memcpy(pMem1, pbWaveData, dwSize1);

    if (dwSize2 != 0)
    {
        memcpy(pMem2, pbWaveData+dwSize1, dwSize2); 
    }

    // unlock the buffer
    pdsb->Unlock(pMem1, dwSize1, pMem2, dwSize2);

    return TRUE;
}

/********************************************************************
 * LoadSoundBuffer
 *
 * Description
 *    Loads a sound resource into a newly created IDirectSoundBuffer.
 *
 * Parameters
 *    tszName       name of sound in resources
 * 
 * Returns
 *    NULL          error in file or in finding resource or in 
 *                  creating sound buffer
 *    NON NULL      pointer to new IDirectSoundBuffer
 ********************************************************************/
IDirectSoundBuffer *LoadSoundBuffer(LPCTSTR tszName)
{
    IDirectSoundBuffer *pdsb = NULL;
    DSBUFFERDESC dsbd = {0};
    BYTE *pbWaveData;

    // find and parse the wave resource
    if (GetWaveResource(tszName, &dsbd.lpwfxFormat, &pbWaveData, 
                        &dsbd.dwBufferBytes))
    {
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLDEFAULT | 
                       DSBCAPS_GETCURRENTPOSITION2;

        // create a new sound buffer
        if (SUCCEEDED(g_pds->CreateSoundBuffer(&dsbd, &pdsb, NULL)))
        {
            // and fill it
            if (!FillSoundBuffer(pdsb, pbWaveData, dsbd.dwBufferBytes))
            {
                pdsb->Release();
                pdsb = NULL;
            }
        }
        else
        {
            pdsb = NULL;
        }
    }

    // return new sound buffer or NULL
    return pdsb;
}
