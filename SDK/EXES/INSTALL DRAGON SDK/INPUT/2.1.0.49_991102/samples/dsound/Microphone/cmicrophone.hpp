/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CMicrophone.hpp

Abstract:

   CMicrophone class declaration

-------------------------------------------------------------------*/

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

const DWORD gcBufferSize = 16 * 1024;
const DWORD gcSamplesPerSec = 11025;
const DWORD gcBitsPerSample = 16;
const DWORD gcNumNotifyEvents = 3;

enum EMicrophoneCommands
{
    ecmdRecord,
    ecmdPlay,
};

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

class CController;

class CMicrophone
{
public:
    CMicrophone(GUID MicrophoneGuid);
    ~CMicrophone();

    // Initialize the Microphone object
    BOOL Initialize(void);

    // Send a command to the Microphone object
    BOOL MicrophoneCommand(EMicrophoneCommands command);

    IDirectSoundCapture       *m_pdsc;
    IDirectSoundCaptureBuffer *m_pdscb;
    IDirectSoundNotify        *m_pdsn;
    IKsPropertySet            *m_pkspropset;
    DSBPOSITIONNOTIFY         m_rgdsbposnotify[gcNumNotifyEvents];
    IDirectSoundBuffer        *m_pdsb;

private:
    // The GUID of the Microphone device
    GUID m_guidMicrophone;
};    

