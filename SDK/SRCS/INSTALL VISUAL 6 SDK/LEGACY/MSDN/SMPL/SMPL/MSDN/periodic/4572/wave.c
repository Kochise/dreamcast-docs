// WAVE.C

#include "windonut.h"

/*=================================================================
 *
 *  File:       wave.c
 *  Content:    Routines for getting waves from files or resources
 *
 ******************************************************************/

#include <windowsx.h>
#include <mmsystem.h>
#include <memory.h>

static const char c_szWAV[] = "WAV";

// Function Prototypes  
BOOL wave_ParseWaveMemory(void *pvRes, 
                          WAVEFORMATEX **ppWaveHeader, 
                          BYTE **ppbWaveData,
                          DWORD *pcbWaveSize);


/////////////////////////////////////////////////////////////////
//
// WAVE_LoadResource: Gets a wave file into the memory pointed 
//                    to by pWaveFile from a resource.
//
/////////////////////////////////////////////////////////////////

LPVOID WAVE_LoadResource
  (LPSTR         lpName,     // Filename to use
   HANDLE        hModule,    // hInst of app with WAVE
   LPWAVEFILE    pWaveFile)  // Points to the struct to fill
{
    HRSRC   hResInfo;
    HGLOBAL hResData;
    void    *pvRes;
    DWORD   dwSize;
    LPVOID  lpMemory;

    // Find the resource and load into memory
    if (((hResInfo = FindResource(hModule, lpName, c_szWAV)) != NULL) &&
        ((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
        ((pvRes = LockResource(hResData)) != NULL))
        {
        // If we found it, copy the bits from the resource into
        // our own chunk of memory
        dwSize = GlobalSize(pvRes);
        lpMemory = MEMORY_New (dwSize);
        memcpy (lpMemory, pvRes, dwSize);
        UnlockResource(hResData);
        FreeResource(hResData);

        // Parse it out
        if (wave_ParseWaveMemory(lpMemory, 
                                 &(pWaveFile->pwfxInfo), 
                                 &(pWaveFile->pbData), 
                                 &(pWaveFile->cbSize)))
          {
          return lpMemory;  // OK
          }
        }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// WAVE_LoaFile: Gets a wave file into the memory 
//               pointed to by pWaveFile from a file
//
///////////////////////////////////////////////////////////////////////////////

LPVOID WAVE_LoadFile    
  (LPSTR         szFileName,  // Filename to use
   LPWAVEFILE    pWaveFile)   // Points to the struct to fill
{
    HANDLE   hFile;
    OFSTRUCT of;
    LPVOID   lpMemory;
    DWORD    dwSize, dwSizeRead;

    // Open da file and read da bits
    hFile = (HANDLE)OpenFile ( szFileName, &of, OF_READ );
    dwSize = _llseek ( (HFILE)hFile, 0, FILE_END );
    _llseek ( (HFILE)hFile, 0, FILE_BEGIN );
    lpMemory = MEMORY_New (dwSize);
    if (!ReadFile(hFile, lpMemory, dwSize, &dwSizeRead, NULL ))
      MessageBox ( NULL, "Readfile failed", "", MB_OK );
    _lclose ( (HFILE)hFile );

    // Parse it out
    if (wave_ParseWaveMemory(lpMemory, 
                             &(pWaveFile->pwfxInfo), 
                             &(pWaveFile->pbData), 
                             &(pWaveFile->cbSize)))
        {
        return lpMemory;  // OK
        }

    return NULL; // Failure
}

//////////////////////////////////////////////////////////////////
//
// wave_ParseWaveMemory
//   Parses a chunk of memory into the header and samples.
//   This is done by looking for the "fmt " and "data"
//   fields in the memory.
//
//////////////////////////////////////////////////////////////////

BOOL wave_ParseWaveMemory

  (LPVOID          lpChunkOfMemory, // Points to raw ram
   LPWAVEFORMATEX  *lplpWaveHeader, // Points to pointer to header
   LPBYTE          *lplpWaveSamples,// Points to pointer to samples
   LPDWORD         lpcbWaveSize)    // Points to size
{
    LPDWORD pdw;
    LPDWORD pdwEnd;
    DWORD   dwRiff;
    DWORD   dwType;
    DWORD   dwLength;

    // Set defaults to NULL or zero
    if (lplpWaveHeader)
        *lplpWaveHeader = NULL;

    if (lplpWaveSamples)
        *lplpWaveSamples = NULL;

    if (lpcbWaveSize)
        *lpcbWaveSize = 0;

    // Set up DWORD pointers to the start of the chunk
    // of memory.
    pdw = (DWORD *)lpChunkOfMemory;

    // Get the type and length of the chunk of memory
    dwRiff = *pdw++;
    dwLength = *pdw++;
    dwType = *pdw++;

    // Using the mmioFOURCC macro (part of Windows SDK), ensure
    // that this is a RIFF WAVE chunk of memory
    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
      return FALSE;      // not even RIFF

    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
      return FALSE;      // not a WAV

    // Find the pointer to the end of the chunk of memory
    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    // Run through the bytes looking for the tags
    while (pdw < pdwEnd)
      {
      dwType   = *pdw++;
      dwLength = *pdw++;

      switch (dwType)
        {
        // Found the format part
        case mmioFOURCC('f', 'm', 't', ' '):

          if (lplpWaveHeader && !*lplpWaveHeader)
            {
            if (dwLength < sizeof(WAVEFORMAT))
              return FALSE; // something's wrong! Not a WAV

            // Set the lplpWaveHeader to point to this part of
            // the memory chunk
            *lplpWaveHeader = (LPWAVEFORMATEX)pdw;

            // Check to see if the other two items have been
            // filled out yet (the bits and the size of the
            // bits). If so, then this chunk of memory has
            // been parsed out and we can exit
            if ((!lplpWaveSamples || *lplpWaveSamples) &&
                (!lpcbWaveSize || *lpcbWaveSize))
              {
              return TRUE;
              }
            }
          break;

        // Found the samples
        case mmioFOURCC('d', 'a', 't', 'a'):

          if ((lplpWaveSamples && !*lplpWaveSamples) ||
              (lpcbWaveSize && !*lpcbWaveSize))
            {
            // Point the samples pointer to this part of the
            // chunk of memory.
            if (lplpWaveSamples) *lplpWaveSamples = (LPBYTE)pdw;

            // Set the size of the wave
            if (lpcbWaveSize)    *lpcbWaveSize = dwLength;

            // Make sure we have our header pointer set up.
            // If we do, we can exit
            if (!lplpWaveHeader || *lplpWaveHeader)
              return TRUE;
            }
          break;

        } // End case

      // Move the pointer through the chunk of memory
      pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
      }

  // Failed! If we made it here, we did not get all the peices
  // of the wave
  return FALSE;
}

BOOL WAVE_SaveFile    (LPSTR         szFileName,  // Filename to use
                       LPWAVEFILE    pWaveFile)  // Points to the struct to fill
{
  return FALSE;
}                       


