/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CVibPack.cpp

Abstract:

    Member functions for the CVibPack class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VibrationPack.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CVibPack::CVibPack

Description:

    Constructor for CVibPack Class.

Arguments:

    GUID        guidVibPack    - GUID of the VibPack device

Return Value:

    None

-------------------------------------------------------------------*/
CVibPack::CVibPack(GUID guidVibPack)
{
    m_guidVibPack = guidVibPack;
    m_hEvent = NULL;
    
    m_numVibSources = 0;
    m_numSimultaneousSources = 0;
    m_curSource = 0;

    m_pvibpackApi = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CVibPack::~CVibPack

Description:

    Destructor for CVibPack class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CVibPack::~CVibPack()
{
    if (m_hEvent != NULL)
    {
        // Make sure there are no VibPack writes outstanding.
        WaitForSingleObject(m_hEvent, INFINITE);

        CloseHandle(m_hEvent);
        m_hEvent = NULL;
    }

    if (m_pvibpackApi != NULL)
    {
        m_pvibpackApi->Release();
        m_pvibpackApi = NULL;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CVibPack::Initialize

Description:

    Initializes the CVibPack object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CVibPack::Initialize()
{
    IUnknown *pIUnknown;
    BYTE *pAutostops = NULL;
    BYTE *pSourceIds = NULL;
    PVIB_WAVEFORM_SETTINGS pWaveform = NULL;
    UINT value;

    g_errLast = MapleCreateDevice(&m_guidVibPack, &pIUnknown);
    if (CheckError(TEXT("Create VibPack device")))
        return FALSE;

    pIUnknown->QueryInterface(IID_IVib, (PVOID*)&m_pvibpackApi);
    pIUnknown->Release();

    if (m_pvibpackApi == NULL)
        return FALSE;

    m_numVibSources = VIB_MAX_SOURCES;
    g_errLast = m_pvibpackApi->GetVibInfo(&m_numVibSources, &m_numSimultaneousSources, m_pVibInfoArray);
    if (CheckError(TEXT("Get Information for Vibration source(s)")))
        return FALSE;

    pSourceIds = new BYTE[m_numVibSources];
    pAutostops = new BYTE[m_numVibSources];
    value = m_numVibSources;
    
    for (UINT index = 0; index < m_numVibSources; index++)
    {
        pSourceIds[index] = index + 1;
        pAutostops[index] = 10 + 10 * index;
    }
    
    m_pvibpackApi->SetVibAutostopTimes(value, pSourceIds, pAutostops, NULL);
    
    m_pvibpackApi->GetVibAutostopTimes(&value, pAutostops);
      
    // None of the initial vibration devices support arbitrary waveforms, so
    // this sample doesn't do anything with them. 
                  
    // Note, this event must be manual reset.  Start it signaled.
    m_hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

    if (pSourceIds != NULL)
    {
        delete[] pSourceIds;
    }    

    if (pAutostops != NULL)
    {
        delete[] pAutostops;
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CVibPack::Vibrate

Description:

    This function causes the Vibration pack to start vibrating.

Arguments:

    DWORD   dwSource        -

    BOOL    fContinuousVib  -

    DWORD   dwVibType       -

    DWORD   dwInitialPower  -

    DWORD   dwDirection     -

    DWORD   dwFrequency     -

    DWORD   dwWavesPerStep  -

Return Value:

    FALSE if the vibration pack has been removed.  TRUE otherwise

-------------------------------------------------------------------*/
BOOL
CVibPack::Vibrate(BYTE dwSource, BOOL fContinuousVib, BYTE dwVibType, BYTE dwInitialPower, 
                  BYTE dwDirection, BYTE dwFrequency, BYTE dwWavesPerStep)
{
    DWORD        dwWaitReturn;
    VIB_SETTINGS vibsettings;

    // There are currently no vibration devices which support multiple
    // simultaneous sources, so this sample only deals with one.  If you
    // need to support multiple simultaneous sources, then simply modify the
    // VibSettings struct to be an array, and pass that array to Vibrate().
    vibsettings.vibType        = dwVibType;
    vibsettings.sourceId       = dwSource;
    vibsettings.direction      = dwDirection;
    vibsettings.frequency      = dwFrequency;
    vibsettings.initialPower   = dwInitialPower;
    vibsettings.wavesPerStep   = dwWavesPerStep;
    vibsettings.bContinuousVib = fContinuousVib;

    // We have a manual reset event that was created in the signaled state.
    // So, the first time through here, the Wait will return immediately.
    // We pass that event to Vibrate.  Because the parameter is not NULL,
    // Vibrate will return quickly with VIBERR_PENDING.  We then go off 
    // and do other things.  When the command to the device finishes, 
    // the Api will signal our event.  So, the next time we get here 
    // that Wait will return immediately again.  If, however, we tried to
    // call the api again very quickly (before it finished the last call)
    // we'd wait here until the previous call was finished.  The calls
    // shouldn't take more than 2 frames to complete, and it's unlikely
    // that we'll tell the device to vibrate twice in that time frame (a
    // human won't be able to feel changes that quick), so this is okay.
 
    // First make sure the previous send is finished
    dwWaitReturn = WaitForSingleObject(m_hEvent, 32);
    
    ResetEvent(m_hEvent);

    // Start the vibration.
    g_errLast = m_pvibpackApi->Vibrate(1, &vibsettings, m_hEvent);
    if (g_errLast == VIBERR_DEVICEUNPLUGGED)
    {
        // Since there was an error, our event was never signaled.
        SetEvent(m_hEvent);
        return FALSE;
    }
    else if (g_errLast != VIB_OK &&  g_errLast != VIBERR_PENDING)
    {
        // Since there was an error, our event was never signaled.
        SetEvent(m_hEvent);
        return TRUE;
    }

    return TRUE;
}
