/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CLCD.cpp

Abstract:

    Member functions for the CLCD class.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_LCD.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::CLCD

Description:

    Constructor for CLCD Class.

Arguments:

    GUID        guidLCD    - GUID of the LCD device

    CController *pcont     - Controller to which the LCD device is attached

Return Value:

    None

-------------------------------------------------------------------*/
CLCD::CLCD(GUID guidLCD, CController *pcont)
{
    m_nCurX        = 0;
    m_nCurY        = 0;
    m_dwBufId      = 0;
    m_guidLCD      = guidLCD;
    m_fPenDown     = TRUE;
    m_pbyLCDBuffer = NULL;
    m_hEvent       = NULL;
    m_plcdApi      = NULL;

    if (pcont->m_fInvertedVMU)
        m_fInverted = TRUE;
    else
        m_fInverted = FALSE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::~CLCD

Description:

    Destructor for CLCD class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CLCD::~CLCD()
{
    if (m_hEvent != NULL)
    {
        // Make sure there are no LCD writes outstanding.
        // WaitForSingleObject(m_hEvent, INFINITE);

        CloseHandle(m_hEvent);
        m_hEvent = NULL;
    }

    if (m_plcdApi != NULL)
    {
        if (m_dwBufId != 0)
        {
            m_pbyLCDBuffer = NULL;
            m_plcdApi->FreeLcdBuffer(m_dwBufId);
        }

        m_plcdApi->Release();
        m_plcdApi = NULL;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::Initialize

Description:

    Initializes the CLCD object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CLCD::Initialize()
{
    BOOL fStandard;
    IUnknown *pIUnknown;

    g_errLast = MapleCreateDevice(&m_guidLCD, &pIUnknown);
    if (CheckError(TEXT("Create Maple Device")))
        return FALSE;

    pIUnknown->QueryInterface(IID_ILcd, (PVOID*)&m_plcdApi);
    pIUnknown->Release();
    if (m_plcdApi == NULL)
        return FALSE;

    fStandard = m_plcdApi->IsStandardLcd();
    if (!fStandard)
    {
        OutputDebugString(TEXT("This program only supports the standard LCD.\n"));
        m_plcdApi->Release();
        m_plcdApi = NULL;
        return FALSE;
    }

    g_errLast = m_plcdApi->GetLcdBuffer(&m_pbyLCDBuffer, &m_dwBufId, g_uiStdLCDBufferSize);
    if (CheckError(TEXT("get LCD Buffer")))
        return FALSE;

    memset(m_pbyLCDBuffer, 0, g_uiStdLCDBufferSize);

    // Note, this event must be manually reset.
    m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // Clear the LCD screen.
    g_errLast = m_plcdApi->SendLcdBuffer(m_dwBufId, g_byPtForLCD1, g_byPhaseForStdLCD, g_usBlockForStdLCD, m_hEvent);
    if (g_errLast == S_OK)
    {
        // This means the event was never set, so we're going to set it
        // ourselves since we assume we can go if it's set.
        SetEvent(m_hEvent);
    }
    else if (g_errLast != E_PENDING)
    {
        // This was some sort of error.
        CheckError(TEXT("Send buffer to LCD"));
        return FALSE;
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::LCDCommand

Description:

    Call this when you want to send a command to the LCD.  This function
    encapsulates functionality which is pretty specific to this sample;
    for instance, you may not need the Current (X,Y) location information
    which the class maintains, and the 'PenUp/PenDown' state is 
    useless in a real game.  The user should remove this code as appropriate.

Arguments:

    ELCDCommands ecmd       - The command to perform.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CLCD::LCDCommand(ELCDCommands ecmd)
{
    BOOL fCleared = FALSE;

    switch (ecmd)
    {
    case ecmdLeft:
        // Move the cursor left
        if (m_nCurX > 0)
            m_nCurX--;
        break;

    case ecmdRight:
        // Move the cursor right
        if (m_nCurX < (g_uiStdLCDXPixels - 1))
            m_nCurX++;
        break;

    case ecmdUp:
        // Move the cursor up
        if (m_nCurY > 0)
            m_nCurY--;
        break;

    case ecmdDown:
        // Move the cursor down
        if (m_nCurY < (g_uiStdLCDYPixels - 1))
            m_nCurY++;
        break;

    case ecmdPenUp:
        // Raise the pen (don't draw while moving)
        m_fPenDown = FALSE;
        break;

    case ecmdPenDown:
        // Lower the pen (draw while moving)
        m_fPenDown = TRUE;
        break;

    case ecmdClear:
        // Clear the LCD display buffer
        fCleared = TRUE;
        memset(m_pbyLCDBuffer, 0x00, g_uiStdLCDBufferSize);
        break;
    }

    // Update the LCD buffer with the new pixel
    if (m_fPenDown && !fCleared)
        SetBit(m_nCurX, m_nCurY, TRUE);

    // Send the updated buffer to the LCD
    return SendLCDBuffer();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::SendLCDBuffer

Description:

    Sends the system-side LCD buffer to the LCD to display.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CLCD::SendLCDBuffer()
{
    HRESULT hr;
    DWORD dwWaitReturn;

    // First make sure the previous send is finished
    dwWaitReturn = WaitForSingleObject(m_hEvent, g_dwMaxLCDWait);
    if (dwWaitReturn == WAIT_TIMEOUT)
    {
        m_fNeedRedraw = TRUE;
        return TRUE;
    }

    ResetEvent(m_hEvent);
    hr = m_plcdApi->SendLcdBuffer(m_dwBufId, g_byPtForLCD1, g_byPhaseForStdLCD, g_usBlockForStdLCD, m_hEvent);
    if (hr == S_OK)
    {
        // This means the event was never set, so we're going to set it
        // ourselves since we assume we can go if it's set.
        SetEvent(m_hEvent);
    }
    else if (hr != E_PENDING)
    {
        // This was some sort of error.
        OutputDebugString(TEXT("Failed to send a buffer to the LCD\n"));
 
        // This means the event was never set, We're going to have to set it ourselves.
        SetEvent(m_hEvent); 
        return FALSE;
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::XYtoBuffer

Description:

    Sets or clears a bit on the buffer at the current cursor location

Arguments:

    BOOL        fSet        - Whether to set or clear the bit

Return Value:

    None

-------------------------------------------------------------------*/
void
CLCD::SetBit(int nX, int nY, BOOL fSet)
{
    int  i;
    BYTE byData;
    BYTE byBit;
    BYTE byMask = 0;

    // The LCD is plugged in upside down, so we need to reverse our coordinates
    if (m_fInverted)
    {
        nX = (g_uiStdLCDXPixels - 1) - nX;
        nY = (g_uiStdLCDYPixels - 1) - nY;
    }

    i = nY * g_uiStdBytesPerRow + nX / g_uiBitsPerByte;
    byBit = (g_uiBitsPerByte - 1) - nX % g_uiBitsPerByte;

    byMask = 1 << byBit;

    byData = m_pbyLCDBuffer[i];

    if (fSet)
        byData |= byMask;
    else
        byData &= (~byMask);

    m_pbyLCDBuffer[i] = byData;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CLCD::GetBit

Description:

    Checks if the specified bit of the LCD display is set or not

Arguments:

    int     nX      - X coordinate to check

    int     nY      - Y coordiante to check

Return Value:

    TRUE if the bit is set, FALSE if the bit is not set

-------------------------------------------------------------------*/
BOOL
CLCD::GetBit(int nX, int nY)
{
    int  i;
    BYTE byData;
    BYTE byBit;
    BYTE byMask = 0x00;

    if (m_fInverted)
    {
        nX = (g_uiStdLCDXPixels - 1) - nX;
        nY = (g_uiStdLCDYPixels - 1) - nY;
    }

    i = nY * g_uiStdBytesPerRow + nX / g_uiBitsPerByte;
    byBit = (g_uiBitsPerByte - 1) - nX % g_uiBitsPerByte;

    byMask = 1 << byBit;

    byData = m_pbyLCDBuffer[i];

    return byData & byMask;
}