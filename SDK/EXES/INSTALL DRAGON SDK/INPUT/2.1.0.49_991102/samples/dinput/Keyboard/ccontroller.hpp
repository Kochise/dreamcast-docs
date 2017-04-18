/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Keyboard.hpp

Abstract:

   Keyboard functionality for DirectInput

-------------------------------------------------------------------*/

// The enum devices callback
BOOL CALLBACK DIEnumProc(LPCDIDEVICEINSTANCE lpdidi, LPVOID pvRef);

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

const DWORD g_cGetDataTime = 3;
const DWORD g_cSleepAmount = 1000 / 30; 
const DWORD g_cEnumCount = 1000 / g_cSleepAmount; //once per second.

const UINT g_cNumPorts = 4;

class CKeyboard
{
public:
    // Constructor
    CKeyboard(GUID guid, DWORD dwDiDevType);

    // Destructor
    ~CKeyboard();
    
    // Initialization function
    BOOL Initialize(void);

    // Device enumeration stub callback function
    static BOOL CALLBACK DIEnumDeviceObjectsProcStub(LPCDIDEVICEOBJECTINSTANCE pDIDOI,  LPVOID pvRef);

    // Polling function
    BOOL Poll(void);

    // Get Data from device
    BOOL GetData(void);

    // Get the Device's Port
    inline UINT GetPort(void) {return m_port;};

    // Get the device's GUID
    inline GUID GetGuid(void) {return m_guid;};

private:

    // Device enumeration callback function
    BOOL DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE pDIDOI);

    // The Device's GUID
    GUID m_guid;

    // The Device's port
    UINT m_port;

    // The device's DirectInputDevice object
    LPDIRECTINPUTDEVICE2 m_pDID;

    // The device's capabilities
    DIDEVCAPS m_devcaps;
};    

// Devices structure - maintains pointers to all plugged in devices.
typedef struct tagDeviceMgr
{
    // The array of pointers to Controllers
    CKeyboard *rgpcont[g_cNumPorts];
} typeDeviceMgr;

BOOL IsNewDevice(GUID devGuid, typeDeviceMgr *pstDevices);
