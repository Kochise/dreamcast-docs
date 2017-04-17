/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CMicrophone.cpp

Abstract:

    Member functions for the CMicrophone class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Microphone.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CMicrophone::CMicrophone

Description:

    Constructor for CMicrophone Class.

Arguments:

    GUID        guidMicrophone    - GUID of the Microphone device

    CController *pcont     - Controller to which the Microphone device is attached

Return Value:

    None

-------------------------------------------------------------------*/
CMicrophone::CMicrophone(GUID guidMicrophone)
{
    m_guidMicrophone = guidMicrophone;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CMicrophone::~CMicrophone

Description:

    Destructor for CMicrophone class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CMicrophone::~CMicrophone()
{
    UINT count = 0;

    if (m_pkspropset != NULL)
    {
        m_pkspropset->Release();
        m_pkspropset = NULL;
    }

    if (m_pdsn != NULL)
    {
        m_pdsn->Release();
        m_pdsn = NULL;
    }

    if (m_pdscb != NULL)
    {
        m_pdscb->Release();
        m_pdscb = NULL;
    }

    if (m_pdsc != NULL)
    {
        m_pdsc->Release();
        m_pdsc = NULL;
    }

    for (count = 0; count < gcNumNotifyEvents; count++)
    {
        if (m_rgdsbposnotify[count].hEventNotify != NULL)
        {
            CloseHandle(m_rgdsbposnotify[count].hEventNotify);
            m_rgdsbposnotify[count].hEventNotify = NULL;
        }
    }

    if (m_pdsb != NULL)
    {
        m_pdsb->Release();
        m_pdsb = NULL;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CMicrophone::Initialize

Description:

    Initializes the CMicrophone object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CMicrophone::Initialize()
{
    IUnknown *pIUnknown;
    DSCBUFFERDESC dscbd;
    WAVEFORMATEX waveformatex;
    int nGain;

    // Create the Microphone Maple Device
    g_errLast = MapleCreateDevice(&m_guidMicrophone, &pIUnknown);
    if (CheckError(TEXT("Create Microphone device")))
        return FALSE;
    
    // Get the IDirectSoundCapture interface
    pIUnknown->QueryInterface(IID_IDirectSoundCapture, (PVOID*)&m_pdsc);
    pIUnknown->Release();

    if (m_pdsc == NULL)
    {
        RetailOutput(TEXT("Device does not support Direct Sound Capture interface\n"));
        return FALSE;
    }

    // Set up the Wave format description
    waveformatex.wFormatTag      = WAVE_FORMAT_PCM;
    waveformatex.nChannels       = 1;
    waveformatex.nSamplesPerSec  = gcSamplesPerSec;
    waveformatex.wBitsPerSample  = gcBitsPerSample;
    waveformatex.nBlockAlign     = (waveformatex.nChannels * waveformatex.wBitsPerSample) / 8;
    waveformatex.nAvgBytesPerSec = waveformatex.nSamplesPerSec * waveformatex.nBlockAlign;
    waveformatex.cbSize          = 0;

    // Set up the DirectSoundCapture buffer description
    dscbd.dwSize        = sizeof(DSCBUFFERDESC);
    dscbd.dwFlags       = 0;
    dscbd.dwBufferBytes = gcBufferSize;
    dscbd.dwReserved    = 0;
    dscbd.lpwfxFormat   = &waveformatex;

    // Get the IDirectSoundCaptureBuffer interface
    g_errLast = m_pdsc->CreateCaptureBuffer(&dscbd, &m_pdscb, NULL);
    if (CheckError(TEXT("Create Capture Buffer")))
        return FALSE;

    // Get the IDirectSoundNotify interface
    g_errLast = m_pdscb->QueryInterface(IID_IDirectSoundNotify, (PVOID*)&m_pdsn);
    if (CheckError(TEXT("Get Notification interface")))
        return FALSE;

    m_rgdsbposnotify[0].dwOffset     = gcBufferSize / 2;
    m_rgdsbposnotify[0].hEventNotify = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_rgdsbposnotify[1].dwOffset     = gcBufferSize - 1;
    m_rgdsbposnotify[1].hEventNotify = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_rgdsbposnotify[2].dwOffset     = DSBPN_OFFSETSTOP;
    m_rgdsbposnotify[2].hEventNotify = CreateEvent(NULL, FALSE, FALSE, NULL);

    g_errLast = m_pdsn->SetNotificationPositions(gcNumNotifyEvents, m_rgdsbposnotify);
    if (CheckError(TEXT("Set NotificationPositions")))
    {
        RetailOutput(TEXT("Microphone was unplugged\r\n"));
        return FALSE;
    }

    // Get the IKsPropertySet interface.  This is for setting the gain.
    g_errLast = m_pdscb->QueryInterface(IID_IKsPropertySet, (PVOID*)&m_pkspropset);
    if (CheckError(TEXT("Get PropertySet interface")))
        return FALSE;

    // Set the gain.  The actual range for the gain is around -15 to 16, but
    // the interface will take out of range values and convert them to the
    // appropriate maximum (or minimum).  So, to set the gain up, just send it
    // a very large number.
    nGain = 100000;

    g_errLast = m_pkspropset->Set(DSPROPSETID_Gain, 0, NULL, 0, (PVOID)&nGain, sizeof(int));
    if (CheckError(TEXT("Set Gain")))
        return FALSE;

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CMicrophone::MicrophoneCommand

Description:

    Call this when you want to send a command to the Microphone.  This function
    encapsulates functionality which is pretty specific to this sample;
    for instance, you may not need the Current (X,Y) location information
    which the class maintains, and the 'PenUp/PenDown' state is 
    useless in a real game.  The user should remove this code as appropriate.

Arguments:

    EMicrophoneCommands ecmd       - The command to perform.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CMicrophone::MicrophoneCommand(EMicrophoneCommands ecmd)
{
    return TRUE;
}
