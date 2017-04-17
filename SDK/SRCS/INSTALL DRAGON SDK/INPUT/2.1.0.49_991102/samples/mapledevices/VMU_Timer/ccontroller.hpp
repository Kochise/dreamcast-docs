/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Controller.hpp

Abstract:

   Controller functionality for DirectInput

-------------------------------------------------------------------*/

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

const UINT g_nPorts         = 4;
const UINT g_nMaxButtons    = USAGE_LAST_BUTTON - USAGE_FIRST_BUTTON + 1;
const BYTE g_iInvalid       = 0xFF;

const UINT g_nMaxAxes       = 4;
const UINT g_uiXAxisIndex   = 0;
const UINT g_uiYAxisIndex   = 1;
const UINT g_uAn5AxisIndex  = 2;
const UINT g_uiAn6AxisIndex = 3;

const UINT g_uiXAxisOffset  = 0;
const UINT g_uiYAxisOffset  = 4;

// The different USAGE_x_BUTTON values are defined in maplusag.h
const BYTE g_iAButton     = USAGE_A_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iBButton     = USAGE_B_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iCButton     = USAGE_C_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iStartButton = USAGE_START_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iLAButton    = USAGE_LA_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iRAButton    = USAGE_RA_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iDAButton    = USAGE_DA_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iUAButton    = USAGE_UA_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iXButton     = USAGE_X_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iYButton     = USAGE_Y_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iZButton     = USAGE_Z_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iDButton     = USAGE_D_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iLBButton    = USAGE_LB_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iRBButton    = USAGE_RB_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iDBButton    = USAGE_DB_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iUBButton    = USAGE_UB_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iRTrigButton = USAGE_RTRIG_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iLTrigButton = USAGE_LTRIG_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iAn3Button   = USAGE_AN3_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iAn4Button   = USAGE_AN4_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iAn5Button   = USAGE_AN5_BUTTON - USAGE_FIRST_BUTTON;
const BYTE g_iAn6Button   = USAGE_AN6_BUTTON - USAGE_FIRST_BUTTON;

typedef enum eAxis {eXAxis, eYAxis};

typedef struct tagAxis {
    BYTE iAxis;
    eAxis eaxis;
} typeAxis;

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++
class CController
{
public:
    // Constructor
    CController(GUID guid, DWORD dwDiDevType);

    // Destructor
    ~CController();
    
    // Initialization function
    BOOL Initialize(void);

    // Device enumeration stub callback function
    static BOOL CALLBACK DIEnumDeviceObjectsProcStub(LPCDIDEVICEOBJECTINSTANCE pDIDOI,  LPVOID pvRef);

    // Polling function
    BOOL Poll(void);

    // Get Data from Controller
    BOOL GetData(void);

    // Called when an Timer is discovered to be attached to the device
    void TimerExists(GUID guidTimer);

    CTimer *GetTimer() {return m_ptimer; };

    // Get the Controller's Port
    inline UINT GetPort(void) {return m_port;};

    // Get the Controller's GUID
    inline GUID GetGuid(void) {return m_guid;};

    // Mapping of button index to DirectInput 'Usage' code
    BYTE m_buttonIndices[g_nMaxButtons];
    typeAxis m_axisIndices[g_nMaxAxes];

    // Current Button and Axis values
    BYTE m_curButtonValues[g_nMaxButtons];
    BOOL m_rgfButtonStateChanged[g_nMaxButtons];
    LONG m_curAxisValues[g_nMaxAxes];

    // The Controller's attributes (range, number of axes, number of buttons)
    DIPROPRANGE m_diprangeX;
    DIPROPRANGE m_diprangeY;
    UINT        m_nAxes;
    UINT        m_nButtons;

private:

    // Device enumeration callback function
    BOOL DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE pDIDOI);

    // The Controller's GUID
    GUID m_guid;

    // The Controller's port
    UINT m_port;

    // The type of the device
    DWORD m_dwDiDevType;

    // The device's DirectInputDevice object
    LPDIRECTINPUTDEVICE2 m_pDID;

    // The Controller's capabilities
    DIDEVCAPS m_devcaps;

    // The Controller's Timer
    CTimer *m_ptimer;
};    

// Devices structure - maintains pointers to all plugged in devices.
typedef struct tagDeviceMgr
{
    // The array of pointers to Controllers
    CController *rgpcont[g_nPorts];
} typeDeviceMgr;

BOOL IsNewDevice(GUID devGuid, typeDeviceMgr *pstDevices);
