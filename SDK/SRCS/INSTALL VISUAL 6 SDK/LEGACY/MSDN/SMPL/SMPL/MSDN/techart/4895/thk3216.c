//
// thk3216.c
//
// Source for THK3216.DLL. This DLL provides the 32-bit side of the thunk
// to TIMER16.DLL.

#include <windows.h>
#include "debug.h"
#define _THK3216_
#include "thk3216.h"

// Prototypes for 16-bit side of thunk (linked via THK32.OBJ)
BOOL PASCAL StartTimer16  (UINT uiPeriod, HWND hWnd);
void PASCAL StopTimer16   (void);
void PASCAL ResetMaxMin16 (void);
void PASCAL EnableSound16 (void);
void PASCAL DisableSound16 (void);



TIMERAPI BOOL FAR PASCAL StartTimer3216  (UINT uiPeriod, HWND hWnd)
{
    BOOL bRtn;

    DOUT ("THK3216.DLL: StartTimer3216\n\r");
    bRtn = StartTimer16 (uiPeriod, hWnd);
    return (bRtn);

}

TIMERAPI void FAR PASCAL StopTimer3216   (void)
{
    DOUT ("THK3216.DLL: StopTimer3216\n\r");
    StopTimer16 ();
}

TIMERAPI void FAR PASCAL ResetMaxMin3216 (void)
{
    DOUT ("THK3216.DLL: ResetMaxMin3216\n\r");
    ResetMaxMin16 ();
}

TIMERAPI void FAR PASCAL EnableSound3216 (void)
{
    DOUT ("THK3216.DLL: EnableSound3216\n\r");
    EnableSound16 ();
}

TIMERAPI void FAR PASCAL DisableSound3216 (void)
{
    DOUT ("THK3216.DLL: DisableSound3216\n\r");
    DisableSound16 ();
}



//------------------------------ tear here -----------------------------------//

// You can use the following code as a starting point for the 32-bit DLL
// providing the 32-bit side of a 32-16 thunk.


// Prototype for functions in THUNK32.LIB
BOOL _stdcall thk_ThunkConnect32 (LPSTR pszDll16, LPSTR pszDll32, HINSTANCE hInst, DWORD dwReason);


BOOL WINAPI DllMain (HANDLE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    DOUT ("THK3216.DLL: DllMain\n\r");

    if (!(thk_ThunkConnect32 ("TIMER16.DLL", "THK3216.DLL", hModule, fdwReason)))
    {
        DOUT ("THK3216.DLL: thk_ThunkConnect32 ret FALSE\n\r");
        return FALSE;
    }
    DOUT ("THK3216.DLL: thk_ThunkConnect32 ret TRUE\n\r");

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DOUT ("THK3216.DLL: DLL_PROCESS_ATTACH\n\r");
        break;

    case DLL_PROCESS_DETACH:
        DOUT ("THK3216.DLL: DLL_PROCESS_DETACH\n\r");
        break;
    }

    return TRUE;
}



