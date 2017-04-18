
/*****************************************************************
 *
 *  Copyright (c) 1996 Microsoft Corporation
 *
 *  File:       wave.cpp
 *  Content:    Routines for getting waves from resources
 *  Author:     Dave Edson; modified by Peter Donnelly
 *
 ******************************************************************/

#include <windows.h>
#include "wave.h"

typedef struct tagWAVEFILE
  {
  DWORD           cbSize;                // Size of file
  LPWAVEFORMATEX  pwfxInfo;              // Wave Header
  LPBYTE          pbData;                // Wave Bits
  }
WAVEFILE, *LPWAVEFILE;

extern LPDIRECTSOUND  lpds;

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
  (int           ID,         // ID of resource
   HANDLE        hModule,    // hInst of app with WAVE
   LPWAVEFILE    pWaveFile)  // Points to the struct to fill
{
    HRSRC   hResInfo;
    HGLOBAL hResData;
    void    *pvRes;
    DWORD   dwSize;
    LPVOID  lpMemory;

    // Find the resource and load into memory
    if (((hResInfo = FindResource(hModule, MAKEINTRESOURCE(ID), "WAVE")) != NULL) &&
        ((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
        ((pvRes = LockResource(hResData)) != NULL))
        {
        // If we found it, copy the bits from the resource into
        // our own chunk of memory
        dwSize = SizeofResource(hModule, hResInfo);
        lpMemory = malloc (dwSize);
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

  // Failed! If we made it here, we did not get all the pieces
  // of the wave
  return FALSE;
} // wave_ParseWaveMemory


//////////////////////////////////////////////////////////////////
//
// LoadWave
//   Gets the sound data and loads it into a DirectSound
//   secondary buffer.
//                          
//
//////////////////////////////////////////////////////////////////

void LoadWave(HINSTANCE hinst, int ResourceID, 
              LPDIRECTSOUNDBUFFER &lpDSB)
  {
// These variables are used in Steps 1 and 2
  LPVOID              lpWaveData;
  WAVEFILE            WaveFile;
  DSBUFFERDESC        dsbd;
  
  // These variables are used in step 3, further down below
  BYTE              *pbData         = NULL;
  BYTE              *pbData2        = NULL;
  DWORD             dwLength;
  DWORD             dwLength2;


  lpWaveData = WAVE_LoadResource (ResourceID, hinst, &WaveFile );

  // Step 1: Set up the direct sound buffer. 
  memset(&dsbd, 0, sizeof(DSBUFFERDESC));

  dsbd.dwSize                 = sizeof(DSBUFFERDESC);
  // We want a buffer that lives on the sound card's memory 
  // (DSBCAPS_STATIC) and can have the pan, volume, and 
  // frequency adjusted (DSBCAPS_CTRLDEFAULT)
  dsbd.dwFlags                = DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC ;

  // Set up the size and format
  dsbd.dwBufferBytes          = WaveFile.cbSize; 
  dsbd.lpwfxFormat            = WaveFile.pwfxInfo;  // Must be a PCM format!

  // Step 2: Create the buffer
  if (DS_OK != lpds->CreateSoundBuffer(&dsbd, &lpDSB, NULL))
    {
    OutputDebugString("Failed to create sound buffer\n");
    return;
    }
// Once this code succeeds, lpDSB will point to a DirectSoundBuffer. 
// At this point, you can copy blocks of sound data into the buffer, 
// using the Lock and Unlock interfaces on the DirectSoundBuffer:

  // Lock down the DirectSound buffer
  if (DS_OK == lpDSB->Lock
            (0,               // Offset into buffer to start writing
             WaveFile.cbSize, // Size of wave file to copy in
             &pbData,         // Points to first block of sound data
             &dwLength,       // Length of first block of data
             &pbData2,        // Points to second block of sound data
             &dwLength2,      // Length of second block of data
             0L))             // Flags
    {
    // Copy first chunk
    memcpy(pbData, WaveFile.pbData, dwLength);

    // Copy second chunk
    if (dwLength2) 
      memcpy(pbData2, WaveFile.pbData+dwLength , dwLength2);

    // Free up the memory allocated in the WAVE_LoadFile function, since we
    // have copied it to the buffer
    free (lpWaveData);

    // Unlock the buffer
    if (DS_OK != lpDSB->Unlock(pbData, dwLength, pbData2, dwLength2))
      OutputDebugString("Unlock failed");
    }
  else
    {
    OutputDebugString("Lock failed");
    }
  } // LoadWave