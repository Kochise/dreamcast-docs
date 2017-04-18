/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CLCD.hpp

Abstract:

   CLCD class declaration

-------------------------------------------------------------------*/

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

enum EVibCommands
{
    vib_left,
    vib_right,
    vib_up,
    vib_down,
    vib_start,
    vib_a,
    vib_b,
    vib_y    
};

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++
class CController;

class CVibPack
{
public:
    CVibPack(GUID vibGuid);
    ~CVibPack();

    // Initialize the VibPack object
    BOOL Initialize(void);

    // Tell the vibration pack to start vibrating
    BOOL Vibrate(BYTE dwSource, BOOL fContinuousVib, BYTE dwVibType, BYTE dwPower, 
                 BYTE dwDirection, BYTE dwFrequency, BYTE dwWavesPerStep);

    VIB_INFO m_pVibInfoArray[VIB_MAX_SOURCES];

private:
    UINT m_numVibSources;
    UINT m_numSimultaneousSources;
    UINT m_curSource;
    
    GUID m_guidVibPack;
    
    HANDLE m_hEvent;
    PVIB m_pvibpackApi;
};

