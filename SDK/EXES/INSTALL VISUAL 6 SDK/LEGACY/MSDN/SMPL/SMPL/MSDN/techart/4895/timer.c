//
// timer.c
//
//

#include <windows.h>
#include <mmsystem.h>
#define _TIMER_
#include "timer.h"


static DWORD dwMaxPeriod = 0;		// initial value arbitrarily small
static DWORD dwMinPeriod = 0xffff;	// initial value arbitrarily large
static BOOL bFirstTick = TRUE;


void ResetMaxMin32 (void)
{   
	OutputDebugString ("TIMER32.DLL: ResetMaxMin32\n\r");

	dwMaxPeriod = 0;
	dwMinPeriod = 0xffff;
	bFirstTick = TRUE;
}

void CALLBACK TimerProc32 (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	static DWORD dwLast;
	static DWORD dwThis, dwElapsed;

	static char szDebug [128];

	dwThis = timeGetTime ();

	OutputDebugString ("TIMER32.DLL: TimerProc32\n\r");

	wsprintf (szDebug, "%ld\n\r", dwThis);
	OutputDebugString (szDebug);

	if (bFirstTick)
	{
		dwLast = dwThis;
		bFirstTick = FALSE;
	}
	else
	{
		dwElapsed = dwThis - dwLast;

		if (dwElapsed > dwMaxPeriod)
		{
			PostMessage ((HWND) dwUser, WM_MAX_PERIOD32, 0, dwElapsed);
			dwMaxPeriod = dwElapsed;
		}
		if (dwElapsed < dwMinPeriod)
		{
			PostMessage ((HWND) dwUser, WM_MIN_PERIOD32, 0, dwElapsed);
			dwMinPeriod = dwElapsed;
		}

		dwLast = dwThis;
	}
}

BOOL WINAPI DllMain (HANDLE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	OutputDebugString ("TIMER32.DLL: DllMain\n\r");

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString ("TIMER32.DLL: DLL_PROCESS_ATTACH\n\r");
		break;

	case DLL_PROCESS_DETACH:
		OutputDebugString ("TIMER32.DLL: DLL_PROCESS_DETACH\n\r");
		break;
	}

	return TRUE;
}


