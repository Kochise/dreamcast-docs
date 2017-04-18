//
// timer16.h
//
// Prototypes for TIMER16.DLL
//


// Exports
BOOL FAR PASCAL __export StartTimer16  (UINT uiPeriod, HWND hWnd);
void FAR PASCAL __export StopTimer16   (void);
void FAR PASCAL __export ResetMaxMin16 (void);
void FAR PASCAL __export EnableSound16 (void);
void FAR PASCAL __export DisableSound16 (void);







