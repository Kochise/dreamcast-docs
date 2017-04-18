/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CTimer.cpp

Abstract:

    Member functions for the CTimer class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_Timer.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::CTimer

Description:

    CTimer constructor

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CTimer::CTimer(GUID guidTimer)
{
    m_guidTimer = guidTimer;
    m_ptmr = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::~CTimer

Description:

    CTimer destructor

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CTimer::~CTimer()
{
    if (m_ptmr != NULL)
    {
        m_ptmr->Release();
        m_ptmr = NULL;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::Initialize

Description:

    CTimer initializer. Gets a pointer to the ITmr interface

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
CTimer::Initialize()
{
    IUnknown *pIUnknown;

    g_errLast = MapleCreateDevice(&m_guidTimer, &pIUnknown);
    if (CheckError(TEXT("Create Maple Device")))
        return FALSE;

    pIUnknown->QueryInterface(IID_ITmr, (PVOID*)&m_ptmr);
    pIUnknown->Release();
    if (m_ptmr == NULL)
        return FALSE;

    // Get the caps information
    m_ptmr->TmrGetDeviceInfo(&m_tmrinfo);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::HasAlarm

Description:

    Determines if the timer device has Alarm functionality. 

Arguments:

    int     nAlarm      - The alarm to check for.  Must be 1 or 2.

Return Value:

    TRUE if alarm exists, FALSE if it doesn't

-------------------------------------------------------------------*/
BOOL
CTimer::HasAlarm(int nAlarm)
{
    switch(nAlarm) {
    case 1:
        if ((m_tmrinfo.tmrAlmCaps & ALM1_MASK) == ALM1_MASK)
            return TRUE;
        break;

    case 2:
        if ((m_tmrinfo.tmrAlmCaps & ALM2_MASK) == ALM2_MASK)
            return TRUE;
        break;
    }

    return FALSE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::SoundAlarm

Description:

    Begins playing the specified Alarm at the desired frequency, at 
    the desired volume.  The app should wait for the desired time and
    then call CTimer::StopAlarm to stop the alarm

Arguments:

    int     nAlarm          - The alarm to sound

    int     nAlarmFreq      - The frequency to play the alarm at

    int     nAlarmVol       - The volume to play the alarm at

Return Value:

    None

-------------------------------------------------------------------*/
void
CTimer::SoundAlarm(int nAlarm, int nAlarmFreq, int nAlarmVol)
{
    switch(nAlarm) {
    case 1:
        m_ptmr->TmrSoundAlarm(nAlarmFreq, nAlarmVol, 0, 0);
        break;

    case 2:
        m_ptmr->TmrSoundAlarm(0, 0, nAlarmFreq, nAlarmVol);
        break;

    default:
        RetailOutput(TEXT("Invalid Alarm number specified\r\n"));
        break;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTimer::StopAlarm

Description:

    Stops all alarms on the timer device

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CTimer::StopAlarm()
{
    m_ptmr->TmrSoundAlarm(0, 0, 0, 0);
}
