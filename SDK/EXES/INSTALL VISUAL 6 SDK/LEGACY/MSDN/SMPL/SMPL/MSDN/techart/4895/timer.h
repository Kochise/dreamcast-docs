//
// timer.h
//
// Contains constants and types common to TIMER16.DLL and TIMER32.DLLx
//


// Constants (messages posted to app)
#define WM_MAX_PERIOD16     WM_USER + 0x100 // for 16-bit timer callback
#define WM_MIN_PERIOD16     WM_USER + 0x101
#define WM_REENTERED16      WM_USER + 0x102
#define WM_MAX_PERIOD32     WM_USER + 0x103 // for 32-bit timer callback
#define WM_MIN_PERIOD32     WM_USER + 0x104
#define WM_REENTERED32      WM_USER + 0x105


// Data types
typedef TIMECALLBACK MYTIMERPROCPROC;
typedef void (MYTIMERRESETPROC)(void);
typedef struct _TIMERSTATUS {
    BOOL  bStarted;     // Timer start/stop flag
    BOOL  bFirstTick;   // Set until first timer tick
    BOOL  bSoundEnabled;// Sound on/off
    UINT  uiPeriod;     // Period timer is set to
    DWORD dwMinPeriod;  // Minimum reported period
    DWORD dwMaxPeriod;  // Maximum reported period
    UINT  uiTimerID;    // Timer ID
    HMIDIOUT  hmidiout; // Midi output device handle
    HWND  hWndMessage;  // Window to post messages to
} TIMERSTATUS;

