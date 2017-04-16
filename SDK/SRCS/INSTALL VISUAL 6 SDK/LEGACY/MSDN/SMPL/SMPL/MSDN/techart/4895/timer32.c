//
// timer32.c
//
//

#include <windows.h>
#include <mmsystem.h>
#include "debug.h"
#include "timer.h"
#define _TIMER32_
#include "timer32.h"


TIMECALLBACK TimerProc32;

// Global data
TIMERSTATUS timerstatus32 = {FALSE, TRUE, FALSE, 0, 0xffff, 0, 0,0};

TIMERAPI void ResetMaxMin32 (void)
{   
    DOUT ("TIMER32.DLL: ResetMaxMin32\n\r");

    timerstatus32.dwMaxPeriod = 0;      // arbitrarily small value
    timerstatus32.dwMinPeriod = 0xffff; // arbitrarily large value
    timerstatus32.bFirstTick = TRUE;
}

TIMERAPI BOOL StartTimer32 (UINT uiPeriod, HWND hWnd)
{
    // Stop and reset current timer
    StopTimer32 ();
    ResetMaxMin32 ();


    // Start new timer
    timerstatus32.hWndMessage = hWnd;
    timerstatus32.uiPeriod = uiPeriod;
    timeBeginPeriod (timerstatus32.uiPeriod);
    timerstatus32.uiTimerID = timeSetEvent (timerstatus32.uiPeriod, 0, TimerProc32, 0, TIME_PERIODIC);
    if (timerstatus32.uiTimerID)
    {
        timerstatus32.bStarted = TRUE;
    }
    return (timerstatus32.bStarted);
}


TIMERAPI void StopTimer32 (void)
{
    if (timerstatus32.bStarted)
    {
        timeKillEvent (timerstatus32.uiTimerID);
        timeEndPeriod (timerstatus32.uiPeriod);
        timerstatus32.bStarted = FALSE;
    }
}

// packed DWORD for note-on, ch 10 (percussion), key #42 (hihat), velocity 127
#define HIHAT   MAKELONG (MAKEWORD (0x99, 42), MAKEWORD (127, 0))
static BOOL  bInProc = FALSE;

void CALLBACK TimerProc32 (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    static DWORD dwLast;
    static DWORD dwThis, dwElapsed;
    
    // Check for reentry
    if (bInProc)
    {
        PostMessage (timerstatus32.hWndMessage, WM_REENTERED32, 0, 0);
        return;
    }
    bInProc = TRUE;
    
#if 0
    // I tried to brute-force the priority up to max, but this didn't really
    // seem to affect timer latency. Note that Win 95 creates a thread for this
    // callback. Setting priority here doesn't change priority for thread of main app.
    SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
    SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
#endif

    // Get time stamp
    dwThis = timeGetTime ();


    // Play sound
    if (timerstatus32.bSoundEnabled && timerstatus32.hmidiout)
    {
        midiOutShortMsg (timerstatus32.hmidiout, HIHAT);
    }
    
    DOUT ("TIMER32.DLL: TimerProc32\n\r");

    if (timerstatus32.bFirstTick)
    {
        dwLast = dwThis;
        timerstatus32.bFirstTick = FALSE;
    }
    else
    {
        dwElapsed = dwThis - dwLast;

        if (dwElapsed > timerstatus32.dwMaxPeriod)
        {
            PostMessage (timerstatus32.hWndMessage, WM_MAX_PERIOD32, 0, dwElapsed);
            timerstatus32.dwMaxPeriod = dwElapsed;
        }
        if (dwElapsed < timerstatus32.dwMinPeriod)
        {
            PostMessage (timerstatus32.hWndMessage, WM_MIN_PERIOD32, 0, dwElapsed);
            timerstatus32.dwMinPeriod = dwElapsed;
        }

        dwLast = dwThis;
    }
    bInProc = FALSE;
}


TIMERAPI void EnableSound32 (void)
{
    UINT uiRtn;
    HMIDIOUT hmidiout;
    
    if (!timerstatus32.bSoundEnabled)
    {
        uiRtn = midiOutOpen (&hmidiout, MIDI_MAPPER, 0, 0, CALLBACK_NULL);
        if (uiRtn != MMSYSERR_NOERROR)
        {
            // Midi device open failed
            timerstatus32.hmidiout = NULL;
            timerstatus32.bSoundEnabled = FALSE;
        }
        else
        {
            // Midi device open succeded
            timerstatus32.hmidiout = hmidiout;
            timerstatus32.bSoundEnabled = TRUE;
        }
    }
}

TIMERAPI void DisableSound32(void)
{
    if (timerstatus32.bSoundEnabled)
    {
        midiOutClose (timerstatus32.hmidiout);
        timerstatus32.bSoundEnabled = FALSE;
        timerstatus32.hmidiout = NULL;
    }
}



BOOL WINAPI DllMain (HANDLE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    DOUT ("TIMER32.DLL: DllMain\n\r");
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DOUT ("TIMER32.DLL: DLL_PROCESS_ATTACH\n\r");
        break;

    case DLL_PROCESS_DETACH:
        DOUT ("TIMER32.DLL: DLL_PROCESS_DETACH\n\r");
        break;
    }

    return TRUE;
}


