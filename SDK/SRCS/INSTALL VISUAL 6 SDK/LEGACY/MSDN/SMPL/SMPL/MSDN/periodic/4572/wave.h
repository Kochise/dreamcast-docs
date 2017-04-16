// WAVE.H - Wave File Helper Functions

#ifndef _H_FILE_WAVE
#define _H_FILE_WAVE

typedef struct tagWAVEFILE
  {
  DWORD           cbSize;                // Size of file
  LPWAVEFORMATEX  pwfxInfo;              // Wave Header
  LPBYTE          pbData;                // Wave Bits
  }
WAVEFILE, *LPWAVEFILE;

#define WAVE_ERROR_OK   0

// Return value of these two functions is WAVE_ERROR_OK if successful

LPVOID WAVE_LoadFile(LPSTR         szFileName,  // Filename to use
                  LPWAVEFILE    pWaveFile);  // Points to the struct to fill

int WAVE_SaveFile(LPSTR         szFileName,  // Filename to use, if NULL use structs
                  LPWAVEFILE    pWaveFile);  // Points to the struct to fill

LPVOID WAVE_LoadResource(LPSTR         szFileName,  // Filename to use
                         HANDLE        hModule,
                         LPWAVEFILE    pWaveFile);  // Points to the struct to fill

#endif
