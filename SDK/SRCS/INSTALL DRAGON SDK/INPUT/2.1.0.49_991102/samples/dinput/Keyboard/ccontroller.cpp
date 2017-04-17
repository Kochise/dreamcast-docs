/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CKeyboard.cpp

Abstract:

    CKeyboard functionality for DirectInput

-------------------------------------------------------------------*/

#include "Keyboard.hpp"

class CQueue {
public:
    CQueue() {m_head = NULL;}
    ~CQueue() { while (m_head) Remove(); } 
    void Add(int i);
    int Remove();

private:
    
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CKeyboard::CKeyboard

Description:

    Constructor for the CKeyboard class.

Arguments:

    GUID          guid          - Guid of the device

    LPDIRECTINPUT pDI           - Pointer to the global DirectInput object

    DWORD         dwDiDevType   - The device type.

Return Value:

    None

-------------------------------------------------------------------*/
CKeyboard::CKeyboard(GUID guid, DWORD dwDiDevType)
{
    m_guid        = guid;
    m_port        = 0xFF;
    m_pDID        = NULL;
    m_dwDiDevType = GET_DIDEVICE_TYPE(dwDiDevType);

    // Create the pressed key queue
    m_pqPressedKeys = new CQueue();
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

    CKeyboard::DIEnumDeviceObjectsProcStub

Description:

    This is a stub function for the EnumerateObjects callback.  Static stubs 
    like this are needed for callbacks that are C++ object member functions.

Arguments:

    LPCDIDEVICEOBJECTINSTANCE pDIDOI - The object being enumerated
    
    LPVOID context                   - pointer to the Keyboard object

Return Value:

    TRUE to continue, FALSE to stop

-------------------------------------------------------------------*/
BOOL CALLBACK
CKeyboard::DIEnumDeviceObjectsProcStub(LPCDIDEVICEOBJECTINSTANCE pDIDOI, LPVOID context)
{
    CKeyboard *pKeyboard = (CKeyboard*)context;
    return(pKeyboard->DIEnumDeviceObjectsProc(pDIDOI));
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

    // Check if it's a keyboard or joystick
    if (m_dwDiDevType == DIDEVTYPE_KEYBOARD)
    {
        g_errLast = m_pDID->SetDataFormat(&c_dfDIKeyboard);
        if (CheckError(TEXT("Set Data Format (Keyboard)")))
            return FALSE;
    }
    else
    {
        // This sample doesn't handle non-keyboard input devices.  Ignore this device
    }

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
    const cMaxKeys = 256;

    BYTE pBuffer[cMaxKeys];
    UINT index;    

    memset(pBuffer, 0, cMaxKeys);

    g_errLast = m_pDID->GetDeviceState(cMaxKeys, pBuffer);
    if (g_errLast == DIERR_UNPLUGGED)
    {
        DebugOutput(TEXT("port %d unplugged\n"), m_port);
        return FALSE;
    }
    else if (CheckError(TEXT("GetDeviceState")))
        return FALSE;

    // Check each key state; if set, add to the unprocessed letters queue.
    for (index = 0; index < cMaxKeys; index++)
        if (pBuffer[index] != 0)
        {
            // The key at 'index' has been pressed.  Add it to the queue.  The program 
            // itself can decide if it wants to handle it or ignore it.
            g_pqPressedKeys->Add(index);
//            DebugOutput(TEXT("port %d keyboard key %d set to 0x%02X\n"), m_port, index, pBuffer[index]);

    return TRUE;
}
