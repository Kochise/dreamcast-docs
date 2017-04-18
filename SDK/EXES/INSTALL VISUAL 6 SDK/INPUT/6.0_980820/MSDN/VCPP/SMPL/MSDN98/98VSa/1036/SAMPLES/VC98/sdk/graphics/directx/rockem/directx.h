/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: directx.h
 *
 ***************************************************************************/

#ifndef __DIRECTX_H_
#define __DIRECTX_H_

// Includes....
#include "d3drmwin.h"
#include "dsound.h"     
#include "stdio.h"

// Defines....
#define NUM_SOUNDS      30

#define INTRO           0
#define PLAYER1_PUNCH1  1
#define PLAYER1_PUNCH2  2
#define PLAYER2_PUNCH1  3
#define PLAYER2_PUNCH2  4
#define PLAYER1_WALK    5
#define PLAYER2_WALK    6
#define WHOOSH1         7
#define WHOOSH2         8
#define PLAYER1_OUCH    9
#define PLAYER2_OUCH    10
#define HEAD_SPRING     11      
#define BLOCK1          12
#define BLOCK2          13
#define BLOCK3          14
#define VICTORY_BOO     15
#define VICTORY_YEAH    16
#define CROWD_LOOP      17
#define SERVO_DOWN_1    18
#define SERVO_DOWN_2    19
#define SERVO_DOWN_3    20
#define SERVO_UP_1      21
#define SERVO_UP_2      22
#define SERVO_UP_3      23
#define RANDOM1			24
#define RANDOM2			25
#define RANDOM3			26
#define RANDOM4 		27
#define RANDOM5			28
#define RANDOM6			29

#define NUM_VID_MODES   50

// Macros

// The following macros are used for proper error handling for DirectDraw,
// DirectSound, Direct3D and Direct3D retained mode
#define TRY_DD(exp) { { HRESULT rval = exp; if (rval != DD_OK) { TraceErrorDD(rval, __FILE__, __LINE__); return FALSE; } } }
#define TRY_DS(exp) { { HRESULT rval = exp; if (rval != DS_OK) { TraceErrorDS(rval, __FILE__, __LINE__); return FALSE; } } }
#define TRY_D3D(exp) { { HRESULT rval = exp; if (rval != D3D_OK) { TraceErrorD3D(rval, __FILE__, __LINE__); return FALSE; } } }
#define TRY_D3DRM(exp) { { HRESULT rval = exp; if (rval != D3DRM_OK) { TraceErrorD3DRM(rval, __FILE__, __LINE__); return FALSE; } } }

// Structures....
typedef struct _D3DDeviceInfo
{
    D3DCOLORMODEL cm;
    LPGUID        lpHWGuid;
    D3DDEVICEDESC HWDeviceDesc;
    LPGUID        lpSWGuid;
    D3DDEVICEDESC SWDeviceDesc;
} D3DDeviceInfo;

#pragma pack(1)
struct WaveHeader
{
    BYTE        RIFF[4];          // "RIFF"
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[4];          // "DATA"
    DWORD       dwDSize;          // Number of Samples
};
#pragma pack()

struct VideoMode
{
    int         width;
    int         height;
    int         bpp;
    BOOL        bUsable;
};

// Prototypes....

// Error handling
void TraceErrorDD(HRESULT hErr, char *sFile, int nLine);
void TraceErrorDS(HRESULT hErr, char *sFile, int nLine);
void TraceErrorD3D(HRESULT hErr, char *sFile, int nLine);
void TraceErrorD3DRM(HRESULT hErr, char *sFile, int nLine);

// Callbacks
BOOL FAR PASCAL  DDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext);
HRESULT CALLBACK DDEnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID Context);
HRESULT WINAPI   D3DEnumDeviceCallBack(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, 
                                                                           LPD3DDEVICEDESC lpHWDesc,  LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext);

// Initialisation
BOOL InitD3DDevice();

BOOL InitDirectX();
BOOL SetDirectDrawExclusiveMode();

// Termination
void TermDirectX();

void SortDisplayModes();

BOOL EnterVideoMode(int mode);
BOOL EnterVideoModeWHBD(int width, int height, int bitdepth);
BOOL EnterNextVideoMode();
BOOL EnterPrevVideoMode();
BOOL EnterLowestVideoMode();
BOOL EnterHighestVideoMode();
BOOL ReenterCurrentVideoMode();
void CleanUp();

BOOL DoSplashScreen(DWORD delay);
void ReleaseSplashScreen();

BOOL RestoreSurfaces();

BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo, BOOL bStaticBuf);
BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos);
BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf);
BOOL StopAllSounds();
BOOL PlaySoundDS(DWORD dwSound, D3DVECTOR d3dvPos, DWORD dwFlags = 0);
IDirectSoundBuffer *CreateSoundBuffer3D(void);
VOID CALLBACK PlayRandomWave( HWND hwnd, UINT uMsg,UINT idEvent, DWORD dwTime );
void RecalcPowerBars(DWORD player1health, DWORD player2health);

#endif

