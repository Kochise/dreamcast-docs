/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

	dxsample.hpp
    

Abstract:

   Header file for DXsample.cpp: a program that demonstrates using direct draw,
   direct input and direct sound.



-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <string.h>
#include "resource.h"
#include "CController.hpp"



// main.cpp variables
extern HWND                g_hwndApp;                   // HWND of the application
extern HINSTANCE           g_hinst;                     // HINSTANCE of the application

#ifdef UNDER_CE

static WINWIDTH = 640;
static WINHEIGHT = 480;

#else //Desktop

static WINWIDTH = 800;
static WINHEIGHT = 600;

#endif //UNDER_CE

extern int g_imageX, g_imageY;							//Global Coordinates of image
extern int ImageWidth, ImageHeight;						//Size of Image
extern RECT rcWindow;									//Rectangle to Blt image into

//main.cpp functions
void ErrorMessage(HWND hWnd, LPTSTR lpText);
int  MoveImage(int value, bool direction);
void DebugOutput(TCHAR *tszErr, ...);



// DDrawvariables
extern LPDIRECTDRAW        g_pdd;                       // The DirectDraw object
extern LPDIRECTDRAWSURFACE g_pddsPrimary;               // Primary directdraw surface
extern LPDIRECTDRAWSURFACE g_pddsSecondary;             // Back directdraw surface
extern LPDIRECTDRAWCLIPPER  g_lpDDClipper;              // The DirectDraw Clipper


// DDraw functions
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
BOOL InitDirectDraw();
LPDIRECTDRAWSURFACE LoadBitmapToDDS(LPTSTR tszBitmap);


//Dinput variables
#define MAX_CONTROLLERS    4
#define BUTTONDOWN(b) (b & 0x80)
extern LPDIRECTINPUT       g_pdi;                    // The DirectInput object
extern CController         *g_rgpcont[MAX_CONTROLLERS]; // The list of active input devices




//Dinput functions

extern BOOL InitDirectInput( void );
void CheckNewDevices();
void PollDevices();
void GetDeviceData();


//Dsound variables
extern LPDIRECTSOUND g_pds;                                 //The DSound Device
extern LPDIRECTSOUNDBUFFER g_pdsbuffer;						//The Sound Buffer for hitting edge
extern LPDIRECTSOUNDBUFFER g_pdsbuffer2;					//The Sound Buffer for fire button

//Dsound functions
bool  InitDirectSound();
BOOL ParseWaveFile(void *pvWaveFile, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize);
BOOL GetWaveResource(LPCTSTR tszName, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize);
BOOL FillSoundBuffer(IDirectSoundBuffer *pdsb, BYTE *pbWaveData, DWORD dwWaveSize);
IDirectSoundBuffer * LoadSoundBuffer(LPCTSTR tszName);




