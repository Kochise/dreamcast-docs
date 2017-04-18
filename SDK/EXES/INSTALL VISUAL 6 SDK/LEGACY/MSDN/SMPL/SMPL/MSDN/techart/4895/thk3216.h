//
// thk3216.h
//

// Function prototypes
#ifdef _THK3216_
#define TIMERAPI __declspec(dllexport)
#else
#define TIMERAPI __declspec(dllimport)
#endif

// Exports
TIMERAPI BOOL FAR PASCAL StartTimer3216  (UINT uiPeriod, HWND hWnd);
TIMERAPI void FAR PASCAL StopTimer3216   (void);
TIMERAPI void FAR PASCAL ResetMaxMin3216 (void);
TIMERAPI void FAR PASCAL EnableSound3216 (void);
TIMERAPI void FAR PASCAL DisableSound3216 (void);






