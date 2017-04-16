//
// timer32.h
//
// Prototypes for TIMER32.DLL
//


// Function prototypes
#ifdef _TIMER32_
#define TIMERAPI __declspec(dllexport)
#else
#define TIMERAPI __declspec(dllimport)
#endif

TIMERAPI BOOL StartTimer32  (UINT uiPeriod, HWND hWnd);
TIMERAPI void StopTimer32   (void);
TIMERAPI void ResetMaxMin32 (void);
TIMERAPI void EnableSound32 (void);
TIMERAPI void DisableSound32(void);





