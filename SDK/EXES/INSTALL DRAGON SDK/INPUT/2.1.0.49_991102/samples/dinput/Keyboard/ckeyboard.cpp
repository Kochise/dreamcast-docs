/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CKeyboard.cpp

Abstract:

    CKeyboard functionality for DirectInput

-------------------------------------------------------------------*/

#include "Keyboard.hpp"

// Array to map DIK code to ASCII codes
BYTE g_byDIKtoASCII[255] = {0x0, 27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x8, 0x9,
                            'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\r', 0x0,
                            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 0x0, 0x0, '\\',
                            'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0x0, '*', 0x0, ' '};

int g_nInitRepeatDelay = 400;   // Hold for 400 ms, then start repeating
int g_nRepeatTime      = 75;    // Once repeating, repeat key every 75 ms.

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::CKeyboard

Description:

    Constructor for the CKeyboard class.

Arguments:

    GUID          guid - Guid of the device

Return Value:

    None

-------------------------------------------------------------------*/
CKeyboard::CKeyboard(GUID guid)
{
    int iKey;

    m_guid = guid;
    m_port = 0xFF;
    m_pDID = NULL;

    // Create the pressed key queue
    m_pqPressedKeys = new CQueue();

    // Clear out the current key state
    for (iKey = 0; iKey < g_nMaxKeys; iKey++)
    {
        m_keystate[iKey].byCurState    = 0;
        m_keystate[iKey].dwPressedTime = 0;
        m_keystate[iKey].fRepeating    = 0;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::~CKeyboard

Description:

    Destructor for the CKeyboard class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CKeyboard::~CKeyboard()
{
    // Delete the key queue
    if (m_pqPressedKeys)
        delete m_pqPressedKeys;

    // Delete the DirectInputDevice object
    if (m_pDID != NULL)
    {
        m_pDID->Unacquire();
        m_pDID->Release();
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::Initialize

Description:

    Call this on a CKeyboard object immediately after creating it.  
    If it fails delete the object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CKeyboard::Initialize(void)
{
    LPDIRECTINPUTDEVICE pDID1;
    DIPROPDWORD         dipropdword;

    // Create the DirectInput device
    g_errLast = g_pdi->CreateDevice(m_guid, &pDID1, NULL);
    if (CheckError(TEXT("Create Device")))
        return FALSE;
    
    // Get a DirectInput2 interface to the device
    g_errLast = pDID1->QueryInterface(IID_IDirectInputDevice2, (LPVOID*)&m_pDID);
    if (CheckError(TEXT("Query Interface for DirectInputDevice2")))
    {
        pDID1->Release();
        return FALSE;
    }

    // As per COM-rules, release the interface we created and no longer need.
    pDID1->Release();

    // Get the port number of the device
    dipropdword.diph.dwSize       = sizeof(DIPROPDWORD);
    dipropdword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipropdword.diph.dwObj = 0;
    dipropdword.diph.dwHow = DIPH_DEVICE;
    g_errLast = m_pDID->GetProperty(DIPROP_PORTNUMBER, &dipropdword.diph);
    if (CheckError(TEXT("Get Port Number")))
        return FALSE;                                              

    m_port = dipropdword.dwData;
    
    // Get the device's capabilities
    m_devcaps.dwSize = sizeof(DIDEVCAPS);
    g_errLast = m_pDID->GetCapabilities(&m_devcaps);
    if (CheckError(TEXT("Get Device Capabilities")))
        return FALSE;

    g_errLast = m_pDID->SetDataFormat(&c_dfDIKeyboard);
    if (CheckError(TEXT("Set Data Format (Keyboard)")))
        return FALSE;

    // Finally, Acquire the port
    g_errLast = m_pDID->Acquire();
    if (CheckError(TEXT("Acquire port")))
        return FALSE;
    
    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::Poll

Description:

    Poll for data

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CKeyboard::Poll(void)
{
    g_errLast = m_pDID->Poll();
    if (CheckError(TEXT("Poll")))
        return FALSE;

    return TRUE;
}    

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::GetData

Description:

    Get the device's state

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CKeyboard::GetData(void)
{
    BYTE pBuffer[g_nMaxKeys];
    UINT iKey;    

    memset(pBuffer, 0, g_nMaxKeys);

    g_errLast = m_pDID->GetDeviceState(g_nMaxKeys, pBuffer);
    if (g_errLast == DIERR_UNPLUGGED)
        return FALSE;
    else if (CheckError(TEXT("GetDeviceState")))
        return FALSE;

    // Check each key's state; if up, ignore it.  If down, check to see if it was previously down. Do repeat checking
    for (iKey = 0; iKey < g_nMaxKeys; iKey++)
    {
        if (pBuffer[iKey] == 0)
            m_keystate[iKey].byCurState = 0;
        else
        {
            BOOL fAddKey = FALSE;
            typeKeyState *pksCur = &m_keystate[iKey];
            // The key at 'iKey' is down.  Check to see if it's newly pressed
            if (pksCur->byCurState == 0)
            {
                // newly pressed
                pksCur->dwPressedTime = GetTickCount();
                m_keystate[iKey].fRepeating = FALSE;               
                pksCur->byCurState = 1;
                fAddKey = TRUE;
            }
            else
            {
                // Key was already pressed - check if we should repeat the key
                int dwCurTime = GetTickCount();

                if (pksCur->fRepeating)
                {
                    // Already repeating, check against re-repeating delay
                    if (dwCurTime - pksCur->dwPressedTime >= g_nRepeatTime)
                    {
                        fAddKey = TRUE;
                        pksCur->dwPressedTime = dwCurTime;
                    }
                }
                else
                {
                    // Not yet repeating.  Check against initial repeat delay
                    if (dwCurTime - pksCur->dwPressedTime >= g_nInitRepeatDelay)
                    {
                        pksCur->fRepeating = TRUE;
                        fAddKey = TRUE;
                        pksCur->dwPressedTime = dwCurTime;
                    }
                }
            }
            
            if (fAddKey)
            {
                // The program itself can decide if it wants to handle it or ignore it.            
                m_pqPressedKeys->Enqueue(g_byDIKtoASCII[iKey]);
            }
        }
    }

    return TRUE;
}
