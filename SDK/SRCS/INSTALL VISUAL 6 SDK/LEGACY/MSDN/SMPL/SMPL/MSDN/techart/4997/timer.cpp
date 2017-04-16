// Timer.cpp

#define VC_EXTRALEAN
#define STRICT

#include <windows.h>
#include <mmsystem.h>
#include "assert.h"
#include "debug.h"
#include "Timer.h"

// constructor
Timer::Timer (void)
{
    DOUT ("Timer::Timer\n\r");

    m_nIDTimer = NULL;
}


// Destructor
Timer::~Timer (void)
{
    DOUT ("Timer::~Timer\n\r");

    if (m_nIDTimer)
    {
        timeKillEvent (m_nIDTimer);
    }
}


// Create
BOOL Timer::Create (UINT nPeriod, UINT nRes, DWORD dwUser, TIMERCALLBACK pfnCallback)
{
    BOOL bRtn = SUCCESS;    // assume success
    
    DOUT ("Timer::Create\n\r");

    ASSERT (pfnCallback);
    ASSERT (nPeriod > 10);
    ASSERT (nPeriod >= nRes);

    m_nPeriod = nPeriod;
    m_nRes = nRes;
    m_dwUser = dwUser;
    m_pfnCallback = pfnCallback;

    if ((m_nIDTimer = timeSetEvent (m_nPeriod, m_nRes, TimeProc, (DWORD) this, TIME_PERIODIC)) == NULL)
    {
        bRtn = FAILURE;
    }

    return (bRtn);
}


// Timer proc for multimedia timer callback set with timeSetTime().
//
// Calls procedure specified when Timer object was created. The 
// dwUser parameter contains "this" pointer for associated Timer object.
// 
void CALLBACK Timer::TimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    // dwUser contains ptr to Timer object
    Timer * ptimer = (Timer *) dwUser;

    // Call user-specified callback and pass back user specified data
    (ptimer->m_pfnCallback) (ptimer->m_dwUser);
}
