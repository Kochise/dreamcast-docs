//
// timer16.c
//
//

#include <windows.h>
#include <mmsystem.h>
#include "debug.h"
#include "timer.h"
#include "timer16.h"

TIMECALLBACK TimerProc16;

// Global data
TIMERSTATUS timerstatus16 = {FALSE, TRUE, FALSE, 0, 0xffff, 0, 0, 0};   // timer state data
UINT uiError;
HANDLE ghDLLInst;

void FAR PASCAL __export ResetMaxMin16 (void)
{   
    DOUT ("TIMER16.DLL: ResetMaxMin16\n\r");

    timerstatus16.dwMaxPeriod = 0;      // arbitrarily small value
    timerstatus16.dwMinPeriod = 0xffff; // arbitrarily large value
    timerstatus16.bFirstTick = TRUE;
}

BOOL FAR PASCAL __export StartTimer16 (UINT uiPeriod, HWND hWnd)
{
    DOUT ("TIMER16.DLL: StartTimer16\n\r");

    // Stop and reset current timer
    StopTimer16 ();
    ResetMaxMin16 ();


    // Start new timer
    timerstatus16.hWndMessage = hWnd;
    timerstatus16.uiPeriod = uiPeriod;
    timeBeginPeriod (timerstatus16.uiPeriod);
    timerstatus16.uiTimerID = timeSetEvent (timerstatus16.uiPeriod, 0, TimerProc16, 0, TIME_PERIODIC);
    if (timerstatus16.uiTimerID)
    {
        timerstatus16.bStarted = TRUE;
    }
    return (timerstatus16.bStarted);
}


void FAR PASCAL __export StopTimer16 (void)
{
    DOUT ("TIMER16.DLL: StopTimer16\n\r");

    if (timerstatus16.bStarted)
    {
        timeKillEvent (timerstatus16.uiTimerID);
        timeEndPeriod (timerstatus16.uiPeriod);
        timerstatus16.bStarted = FALSE;
    }
}


// packed DWORD for note-on, ch 10 (percussion), key #42 (hihat), velocity 127
#define MAKEWORD(low, high) \
    ((WORD)(((BYTE)(low)) | ((WORD)((BYTE)(high))) << 8))
#define HIHAT   ((DWORD) (MAKELONG (MAKEWORD (0x99, 42), MAKEWORD (127, 0))))
static BOOL  bInProc = FALSE;

void CALLBACK __export TimerProc16 (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    static DWORD dwLast;
    static DWORD dwThis, dwElapsed;
    static UINT  uiRtn;

    // Check for reentry
    if (bInProc)
    {
        PostMessage (timerstatus16.hWndMessage, WM_REENTERED16, 0, 0);
        return;
    }
    bInProc = TRUE;

    // Get time stamp
    dwThis = timeGetTime ();

    if (timerstatus16.bSoundEnabled && timerstatus16.hmidiout)
    {
        uiRtn = midiOutShortMsg (timerstatus16.hmidiout, HIHAT);
    }
    
    DOUT ("TIMER16.DLL: TimerProc16\n\r");
    
    if (timerstatus16.bFirstTick)
    {
        dwLast = dwThis;
        timerstatus16.bFirstTick = FALSE;
    }
    else
    {
        dwElapsed = dwThis - dwLast;

        if (dwElapsed > timerstatus16.dwMaxPeriod)
        {
            PostMessage (timerstatus16.hWndMessage, WM_MAX_PERIOD16, 0, dwElapsed);
            timerstatus16.dwMaxPeriod = dwElapsed;
        }
        if (dwElapsed < timerstatus16.dwMinPeriod)
        {
            PostMessage (timerstatus16.hWndMessage, WM_MIN_PERIOD16, 0, dwElapsed);
            timerstatus16.dwMinPeriod = dwElapsed;
        }

        dwLast = dwThis;
    }
    bInProc = FALSE;
}

void FAR PASCAL __export EnableSound16  (void)
{
    UINT uiRtn;
    HMIDIOUT hmidiout;
    
    if (!timerstatus16.bSoundEnabled)
    {
        uiRtn = midiOutOpen (&hmidiout, (UINT) MIDI_MAPPER, 0, 0, 0);
        if (uiRtn != MMSYSERR_NOERROR)
        {
            // Midi device open failed
            timerstatus16.hmidiout = NULL;
            timerstatus16.bSoundEnabled = FALSE;
        }
        else
        {
            // Midi device open succeded
            timerstatus16.hmidiout = hmidiout;
            timerstatus16.bSoundEnabled = TRUE;
        }
    }
}

void FAR PASCAL __export DisableSound16(void)
{
    if (timerstatus16.bSoundEnabled)
    {
        midiOutClose (timerstatus16.hmidiout);
        timerstatus16.bSoundEnabled = FALSE;
        timerstatus16.hmidiout = NULL;
    }
}


//------------------------------ tear here -----------------------------------//

// You can use the following code as a starting point for any 16-bit DLL that
// you want to use with a Win 95 application. Remember that DLL must be marked
// as a Windows 4.0 executable with the resource compiler.

BOOL FAR PASCAL __export DllEntryPoint (DWORD dwReason,
                               WORD  hInst,
                               WORD  wDS,
                               WORD  wHeapSize,
                               DWORD dwReserved1,
                               WORD  wReserved2);

// Prototype for thunk-related function that lives in THK16.OBJ
BOOL FAR PASCAL thk_ThunkConnect16(LPSTR pszDll16,
                                   LPSTR pszDll32,
                                   WORD  hInst,
                                   DWORD dwReason);


// Basic LibMain for 16-bit DLL
int FAR PASCAL LibMain (HANDLE hInstance,
                        WORD   wDataSeg,
                        WORD   wHeapSize,
                        LPSTR  lpszCmdLine)
{
    ghDLLInst = hInstance;

    if (wHeapSize != 0)   // If DLL data seg is MOVEABLE
        UnlockData (0);

    return (1);
}


// This entry point function is required for a 16-bit DLL to
// run with 32-bit app on Win 95
BOOL FAR PASCAL __export DllEntryPoint (DWORD fdwReason,
                               WORD  hInst,
                               WORD  wDS,
                               WORD  wHeapSize,
                               DWORD dwReserved1,
                               WORD  wReserved2)
{
    DOUT ("In 16bit DllEntryPoint: Calling thkThunkConnect16");
    if (!thk_ThunkConnect16("TIMER16.DLL",
                            "THK3216.DLL",
                            hInst,
                            fdwReason))
    {

        DOUT ("\n\rIn 16bit DllEntryPoint: thkThunkConnect16 ret FALSE");
        return FALSE;
    }

    DOUT ("\n\rIn 16bit DllEntryPoint: thkThunkConnect16 ret TRUE");

    return TRUE;
}



