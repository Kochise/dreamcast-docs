/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCTimer.h

Abstract:

    Timer functions.

-------------------------------------------------------------------*/

// System Time is relative to actual time.
// App Time only changes when the app is active.
// Game Time only changes when the game is active.
// When App Time stops, Game Time stops also.

// Timer functions.
typedef DWORD TIMEVALUE;

// Init/shutdown.
BOOL InitTimer(void);
void ShutdownTimer(void);

// Get time fuctions.
TIMEVALUE TimerGetSysTime(void);
TIMEVALUE TimerGetAppTime(void);
TIMEVALUE TimerGetGameTime(void);

// Calculates the time delta between to time values.
// Return value in seconds.
float TimerGetTimeDelta(TIMEVALUE Low,TIMEVALUE High); 

// Pauses/unpaused for app and game time.
// All timers are active after initialization.
void TimerPauseAppTime(void);
void TimerUnpauseAppTime(void);
void TimerPauseGameTime(void);
void TimerUnpauseGameTime(void);

// Wait functions. Time is in seconds.
void TimerWaitCoarse(TIMEVALUE StartTime, float WaitTime);
void TimerWaitFine(TIMEVALUE StartTime, float WaitTime);