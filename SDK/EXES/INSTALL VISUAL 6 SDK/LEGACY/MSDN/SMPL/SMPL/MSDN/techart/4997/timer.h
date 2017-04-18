// Timer.h

#ifndef _INC_TIMER
#define _INC_TIMER

// Constants
#ifndef SUCCESS
#define SUCCESS TRUE        // Error returns for all member functions
#define FAILURE FALSE
#endif // SUCCESS


typedef BOOL (*TIMERCALLBACK)(DWORD);

// Classes

// Timer
//
// Wrapper class for Windows multimedia timer services. Provides
// both periodic and one-shot events. User must supply callback
// for periodic events.
// 

class Timer
{
public:
    Timer (void);
    ~Timer (void);
    BOOL Create (UINT nPeriod, UINT nRes, DWORD dwUser,  TIMERCALLBACK pfnCallback);
protected:
    static void CALLBACK TimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
    TIMERCALLBACK m_pfnCallback;
    DWORD m_dwUser;
    UINT m_nPeriod;
    UINT m_nRes;
    UINT m_nIDTimer;
};

#endif // _INC_TIMER
