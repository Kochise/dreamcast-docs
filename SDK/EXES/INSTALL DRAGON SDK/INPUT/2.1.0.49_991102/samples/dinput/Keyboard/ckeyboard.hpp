/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CKeyboard.hpp

Abstract:

    CKeyboard functionality for DirectInput

-------------------------------------------------------------------*/

// The enum devices callback
BOOL CALLBACK DIEnumProc(LPCDIDEVICEINSTANCE lpdidi, LPVOID pvRef);

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

const UINT g_nPorts = 4;
const int  g_nMaxKeys = 256;

// ++++ Global Typedefs +++++++++++++++++++++++++++++++++++++++++++++

typedef struct tagCell {
    int     nElement;
    tagCell *pcellNext;
} typeCell;

typedef struct tagKeyState {
    BYTE byCurState;    // pressed or released
    int  dwPressedTime; // Time key was pressed
    BOOL fRepeating;    // Key is currently in a repeat state
} typeKeyState;

// ++++ Global Classes ++++++++++++++++++++++++++++++++++++++++++++++

// Simple implementation of a integer queue
class CQueue {
public:
    // Constructor
    CQueue();
    
    // Destructor
    ~CQueue();

    // Add element to end of queue
    void Enqueue(int iValue);

    // Remove an element from the front of the queue.  
    BOOL Dequeue(int *pnValue);

    // Is the Queue empty?
    BOOL IsEmpty();

private:
    typeCell *m_pcellHead;
    typeCell *m_pcellTail;
};

class CKeyboard
{
public:
    // Constructor
    CKeyboard(GUID guid);

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

    // Queue of pressed keys
    CQueue *m_pqPressedKeys;

private:

    // The Device's GUID
    GUID m_guid;

    // The Device's port
    UINT m_port;

    // The device's DirectInputDevice object
    LPDIRECTINPUTDEVICE2 m_pDID;

    // The device's capabilities
    DIDEVCAPS m_devcaps;

    // Current Key state
    typeKeyState m_keystate[g_nMaxKeys];
};    

// Devices structure - maintains pointers to all plugged in devices.
typedef struct tagDeviceMgr
{
    // The array of pointers to Keyboards
    CKeyboard *rgpcont[g_nPorts];
} typeDeviceMgr;

BOOL IsNewDevice(GUID devGuid, typeDeviceMgr *pstDevices);
