/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CLCD.hpp

Abstract:

   CLCD class declaration

-------------------------------------------------------------------*/

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// LCD Consts
const BYTE   g_byPtForLCD1        = 0;
const BYTE   g_byPhaseForStdLCD   = 0;
const USHORT g_usBlockForStdLCD   = 0;
const UINT   g_uiStdLCDBufferSize = 192;
const UINT   g_uiStdLCDXPixels    = 48;
const UINT   g_uiStdLCDYPixels    = 32;
const UINT   g_uiBitsPerByte      = 8;
const UINT   g_uiStdBytesPerRow   = g_uiStdLCDXPixels / g_uiBitsPerByte;
const DWORD  g_dwMaxLCDWait       = 5;

enum ELCDCommands
{
    ecmdLeft,
    ecmdRight,
    ecmdUp,
    ecmdDown,
    ecmdPenUp,
    ecmdPenDown,
    ecmdClear,
    ecmdRedraw
};

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

class CController;

class CLCD
{
public:
    CLCD(GUID LCDGuid, CController *pcont);
    ~CLCD();

    // Initialize the LCD object
    BOOL Initialize(void);

    // Send a command to the LCD object
    BOOL LCDCommand(ELCDCommands command);

    // The LCD display needs to be refreshed
    BOOL m_fNeedRedraw;

    // The current pen state (up/down)
    BOOL m_fPenDown;

    // The current cursor location
    int m_nCurX, m_nCurY;
          
    // Determine if the specified bit is set or not
    BOOL GetBit(int nX, int nY);

    // TRUE if The LCD is inserted in the controller in an inverted fashion
    BOOL m_fInverted;

private:
    // Send the system-side LCD buffer to the LCD device for display
    BOOL SendLCDBuffer();

    // Set or clera the specified bit
    void SetBit(int nX, int nY, BOOL fSet);
    
    // The system-side copy of the LCD device's display contents
    PBYTE m_pbyLCDBuffer;

    // The LCD's ID
    DWORD m_dwBufId;

    // The GUID of the LCD device
    GUID m_guidLCD;

    HANDLE m_hEvent;
    PLCD m_plcdApi;
};    

