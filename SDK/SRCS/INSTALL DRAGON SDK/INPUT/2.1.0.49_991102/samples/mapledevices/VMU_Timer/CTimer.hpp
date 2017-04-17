/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CTimer.hpp

Abstract:

   CTimer class declaration

-------------------------------------------------------------------*/

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// Alarm Masks
#define ALM1_MASK   0x40
#define ALM2_MASK   0x80

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++
class CTimer
{
public:
    CTimer(GUID guidTimer);
    ~CTimer();

    // Initialize the timer object
    BOOL Initialize();

    // Reads the current time of the timer device
    void ReadTime(TMR_CURR_TIME *ptmrcurrtime) {m_ptmr->TmrGetTime(ptmrcurrtime);};

    // Sets the time of the timer device to the desired value
    void SetTime(TMR_CURR_TIME *ptmrcurrtime)  {m_ptmr->TmrSetTime(ptmrcurrtime);};

    // Determines if the timer device has the specified alarm
    BOOL HasAlarm(int nAlarm);

    // Starts the alarm sound for the specified alarm
    void SoundAlarm(int nAlarm, int nAlarmFreq, int nAlarmVol);

    // Stops all alarms on the timer device
    void StopAlarm();

private:
    // Pointer to the timer device's Maple interface
    PTMR m_ptmr;

    // GUID of the timer device
    GUID m_guidTimer;

    // Caps bits and other related information about the timer device
    TMR_INFO m_tmrinfo;
};    

