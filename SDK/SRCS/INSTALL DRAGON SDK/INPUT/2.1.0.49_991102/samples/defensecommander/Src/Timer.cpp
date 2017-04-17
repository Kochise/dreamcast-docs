/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Timer.cpp

Abstract:

    Timer functions.

-------------------------------------------------------------------*/

// In this implementation TIMEVALUE is a count in microseconds.

#include "DC.h"

BOOL			UsePerfCounter;
LARGE_INTEGER	PerfFrequency;
BOOL			AppTimePaused;
TIMEVALUE		AppTimePauseStart;
TIMEVALUE		AppTimeDelta;
BOOL			GameTimePaused;
TIMEVALUE		GameTimePauseStart;
TIMEVALUE		GameTimeDelta;

// Initialize timer functions.
BOOL InitTimer(void)
{
	// Get performance frequency and if high
	//precision counter is available.
	if (QueryPerformanceFrequency(&PerfFrequency))
	{
		UsePerfCounter=TRUE;
		// Convert frequency to ticks/microsecond.
		PerfFrequency.QuadPart/=1000000;
	}
	else
	{
		UsePerfCounter=FALSE;
	}

	// Init other variables.
	AppTimePaused=FALSE;
	AppTimeDelta=0;
	GameTimePaused=FALSE;
	GameTimeDelta=0;

	return TRUE;
}


// Shutdown timer funcitons.
void ShutdownTimer(void)
{
	// Nothing to do.
}

// Returns current system time.
TIMEVALUE TimerGetSysTime(void)
{
	if (UsePerfCounter)
	{
		LARGE_INTEGER Time;

		QueryPerformanceCounter(&Time);
		// Convert count to ms.
		Time.QuadPart/=PerfFrequency.QuadPart;
		// Return low DWORD.
		return Time.LowPart;
	}
	else
	{
		return GetTickCount()*1000;
	}
	return 0;
}

// Returns current app time.
TIMEVALUE TimerGetAppTime(void)
{
	if (AppTimePaused)
	{
		return AppTimePauseStart-AppTimeDelta;
	}
	else
	{
		return TimerGetSysTime()-AppTimeDelta;
	}
}

// Returns current game time.
TIMEVALUE TimerGetGameTime(void)
{
	if (GameTimePaused)
	{
		return GameTimePauseStart-GameTimeDelta;
	}
	else
	{
		return TimerGetSysTime()-GameTimeDelta;
	}
}

// Calculates the time delta between to time values.
// Return value in seconds.
float TimerGetTimeDelta(TIMEVALUE Low,TIMEVALUE High)
{
	TIMEVALUE Delta=High-Low;

	return (float)Delta * 0.000001f;
}

// Enable/Disables for app and game time.
// All timers are active after initialization.
void TimerPauseAppTime(void)
{
	if (!AppTimePaused)
	{
		AppTimePaused=TRUE;
		AppTimePauseStart=TimerGetSysTime();
	}
}
\
void TimerUnpauseAppTime(void)
{
	if (AppTimePaused)
	{
		AppTimePaused=FALSE;
		AppTimeDelta+=TimerGetSysTime()-AppTimePauseStart;
	}
}

void TimerPauseGameTime(void)
{
	if (!GameTimePaused)
	{
		GameTimePaused=TRUE;
		GameTimePauseStart=TimerGetSysTime();
	}
}

void TimerUnpauseGameTime(void)
{
	if (GameTimePaused)
	{
		GameTimePaused=FALSE;
		GameTimeDelta+=TimerGetSysTime()-GameTimePauseStart;
	}
}

// Wait functions. Time is in seconds.
void TimerWaitCoarse(TIMEVALUE StartTime, float WaitTime)
{
	for (;;)
	{
		// See if waited long enough.
		TIMEVALUE CurrentTime=TimerGetSysTime();
		if (TimerGetTimeDelta(StartTime,CurrentTime)>WaitTime)
			return;
		// Sleep for a while.		
		Sleep(100);
	}
}


void TimerWaitFine(TIMEVALUE StartTime, float WaitTime)
{
	for (;;)
	{
		// See if waited long enough.
		TIMEVALUE CurrentTime=TimerGetSysTime();
		if (TimerGetTimeDelta(StartTime,CurrentTime)>WaitTime)
			return;
	}
}
