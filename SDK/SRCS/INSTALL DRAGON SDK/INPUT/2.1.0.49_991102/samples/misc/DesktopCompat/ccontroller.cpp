/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Controller.cpp

Abstract:

    Controller functionality for the Desktop Compatibility program.

-------------------------------------------------------------------*/

#include "DesktopCompat.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::CController

Description:

    Constructor for the CController class.

Arguments:

    GUID          guid          - Guid of the device

    LPDIRECTINPUT pDI           - Pointer to the global DirectInput object

    DWORD         dwDiDevType   - The device type.

Return Value:

    None

-------------------------------------------------------------------*/
CController::CController(GUID guid, DWORD dwDiDevType)
{
    m_guid        = guid;
    m_port        = 0xFF;
    m_pDID        = NULL;
    m_nAxes       = 0;
    m_nButtons    = 0;
    m_dwDiDevType = GET_DIDEVICE_TYPE(dwDiDevType);

    // Clear out the current state.
    memset(m_buttonIndices, g_iInvalid, g_nMaxButtons);
    memset(m_axisIndices,   g_iInvalid, g_nMaxAxes * sizeof(typeAxis));

    memset(m_curButtonValues,       0, g_nMaxButtons);
    memset(m_rgfButtonStateChanged, 0, g_nMaxButtons);
    memset(m_curAxisValues,         0, g_nMaxAxes * sizeof(LONG));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::~CController

Description:

    Destructor for the CController class.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
CController::~CController()
{
    if (m_pDID != NULL)
    {
        m_pDID->Unacquire();
        m_pDID->Release();
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::DIEnumDeviceObjectsProcStub

Description:

    This is a stub function for the EnumerateObjects callback.  Static stubs 
    like this are needed for callbacks that are C++ object member functions.

Arguments:

    LPCDIDEVICEOBJECTINSTANCE pDIDOI - The object being enumerated
    
    LPVOID context                   - pointer to the controller object

Return Value:

    TRUE to continue, FALSE to stop

-------------------------------------------------------------------*/
BOOL CALLBACK
CController::DIEnumDeviceObjectsProcStub(LPCDIDEVICEOBJECTINSTANCE pDIDOI, LPVOID pvContext)
{
    CController *pController = (CController*)pvContext;
    return(pController->DIEnumDeviceObjectsProc(pDIDOI));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::Initialize

Description:

    Call this on a CController object immediately after creating it.  
    If it fails delete the object.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CController::Initialize(void)
{
    LPDIRECTINPUTDEVICE pDID1;
    DIPROPDWORD         dipropdword;
	HRESULT hr;
	DWORD cl;
    // Create the DirectInput device
    hr = g_pdi->CreateDevice(m_guid, &pDID1, NULL);
   	if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Create Device"));
        return FALSE;
	}
    
    // Get a DirectInput2 interface to the device
    hr = pDID1->QueryInterface(IID_IDirectInputDevice2, (LPVOID*)&m_pDID);
   	if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Query Interface for DirectInputDevice2"));
        pDID1->Release();
        return FALSE;
	}
   
	// As per COM-rules, release the interface we created and no longer need.
    pDID1->Release();

	// If under the Dreamcast, Get the port number of the device

#ifdef UNDER_CE
	dipropdword.diph.dwSize       = sizeof(DIPROPDWORD);
    dipropdword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipropdword.diph.dwObj = 0;
    dipropdword.diph.dwHow = DIPH_DEVICE;



    	
	hr = m_pDID->GetProperty(DIPROP_PORTNUMBER, &dipropdword.diph);
   	if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Get Port Number"));
        return FALSE;
	}

	m_port = dipropdword.dwData;
#endif  //UNDER_CE      
    // Get the device's capabilities
    m_devcaps.dwSize = sizeof(DIDEVCAPS);
    hr = m_pDID->GetCapabilities(&m_devcaps);
   	if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Get Device Capabilities"));
        return FALSE;
	}

    // Check if it's a keyboard, mouse,  or joystick 
    if (m_dwDiDevType == DIDEVTYPE_KEYBOARD)
    {
		cl = DISCL_NONEXCLUSIVE;
        hr = m_pDID->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(hr)){
			ErrorMessage(NULL, TEXT("Set Data Format (Keyboard)"));
			return FALSE;
		}
        
    }
    else if (m_dwDiDevType == DIDEVTYPE_MOUSE){
		cl = DISCL_EXCLUSIVE;
		hr = m_pDID->SetDataFormat(&c_dfDIMouse);
		if(FAILED(hr)){
			ErrorMessage(NULL, TEXT("Set Data Format (Mouse)"));
			return FALSE;
		}
	}
	else if (m_dwDiDevType == DIDEVTYPE_JOYSTICK) {
        cl = DISCL_NONEXCLUSIVE;
		// EnumObjects is how we determine how many buttons and axes this controller
        // has.  By interpreting this data correctly we can automatically work with
        // new controllers that have a different number of buttons, etc.
        // DirectInput will call our DIEnumDeviceObjectsProcStub (which will then
        // call our DIEnumDeviceObjectsProc) once for each object (button or axis)
        // on the device.
        hr = m_pDID->EnumObjects(DIEnumDeviceObjectsProcStub, this, 0);
		if(FAILED(hr)){
			ErrorMessage(NULL, TEXT("Enumerate Objects"));
			return FALSE;
		}   
		
		
		hr = m_pDID->SetDataFormat(&c_dfDIJoystick);
		if(FAILED(hr)){
			ErrorMessage(NULL, TEXT("Set Data Format (Joystick)"));
			return FALSE;
		}   
		
		// Set up the axes
		for (int i = 0; i < g_nMaxAxes; i++)
		{
			if (m_axisIndices[i].iAxis != g_iInvalid)
			{
				// There is an axis here!
				dipropdword.diph.dwSize = sizeof(DIPROPDWORD);
				dipropdword.diph.dwHeaderSize = sizeof(DIPROPHEADER);
				dipropdword.diph.dwHow = DIPH_BYOFFSET;
				dipropdword.dwData = 1000;  //10% (5 on either side)
				switch (m_axisIndices[i].eaxis)
				{
				case eXAxis:
					// Get the range and dead zone for the X axis.
					m_diprangeX.diph.dwSize = sizeof(DIPROPRANGE);
					m_diprangeX.diph.dwHeaderSize = sizeof(DIPROPHEADER);
					m_diprangeX.diph.dwHow = DIPH_BYOFFSET;
					m_diprangeX.diph.dwObj = g_uiXAxisOffset;
					hr = m_pDID->GetProperty(DIPROP_RANGE, (LPDIPROPHEADER)&m_diprangeX);
					if(FAILED(hr)){
						ErrorMessage(NULL, TEXT("Get Digital X Range"));
						return FALSE;
					}
					
					
					dipropdword.diph.dwObj = g_uiXAxisOffset;
					hr = m_pDID->SetProperty(DIPROP_DEADZONE, &dipropdword.diph);
					if(FAILED(hr)){
						ErrorMessage(NULL, TEXT("Set X DeadZone"));
						return FALSE;
					}
					break;
					
				case eYAxis:
					// Get the range and dead zone for the Y axis.
					m_diprangeY.diph.dwSize = sizeof(DIPROPRANGE);
					m_diprangeY.diph.dwHeaderSize = sizeof(DIPROPHEADER);
					m_diprangeY.diph.dwHow = DIPH_BYOFFSET;
					m_diprangeY.diph.dwObj = g_uiYAxisOffset;
					hr = m_pDID->GetProperty(DIPROP_RANGE, (LPDIPROPHEADER)&m_diprangeY);
					if(FAILED(hr)){
						ErrorMessage(NULL, TEXT("Get Digital Y Range"));
						return FALSE;
					}
					
					dipropdword.diph.dwObj = g_uiYAxisOffset;
					hr = m_pDID->SetProperty(DIPROP_DEADZONE, &dipropdword.diph);
					if(FAILED(hr)){
						ErrorMessage(NULL, TEXT("Set Y DeadZone"));
						return FALSE;
					}
					break;
				}
			}
		}
    
	}
#ifndef UNDER_CE
   if ( FAILED( m_pDID->SetCooperativeLevel( g_hwndApp, cl | DISCL_FOREGROUND ) ) )
   {
        ErrorMessage(NULL, TEXT( "Failed to set game device cooperative level.\n" ));
        return FALSE;
   }
#endif //ndef UNDER_CE
		
	// Finally, Acquire the port
    hr = m_pDID->Acquire();
    if(FAILED(hr)){
		ErrorMessage(NULL, TEXT("Acquire port"));
		return FALSE;
	}
	
    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::Poll

Description:

    Poll for data

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CController::Poll(void)
{
    HRESULT hr;
	hr = m_pDID->Poll();
	if(FAILED(hr))
		return FALSE;
	
	
	return TRUE;
}    

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::GetData

Description:

    This is where all the real work is done.  The app calls this every time it 
    wants new data from a controller.
    This supports the ability to handle any button in the Maple FT0 format.  
    It will skip anything that does not exist on the currently plugged
    in controller.  Because I don't know what Analog Axis 5 and 6 will be used 
    for, I don't know how to support them here.

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CController::GetData(void)
{
    DIJOYSTATE dijoystate;
    char keys[256];
	int MIDRANGE;
    LONG lData;
    BYTE index;    
    HRESULT hr;


    // If keyboards for this sample
    if (m_dwDiDevType == DIDEVTYPE_KEYBOARD){
		hr = m_pDID->GetDeviceState(sizeof(keys), keys);
		if(FAILED(hr))
			return FALSE;

		if ( BUTTONDOWN( keys[DIK_LEFT] ) )
			MoveImage(-10, 0);
		if ( BUTTONDOWN( keys[DIK_RIGHT] ) )
			MoveImage(10, 0);
		if ( BUTTONDOWN( keys[DIK_UP] ) )
			MoveImage(-10, 1);
		if ( BUTTONDOWN( keys[DIK_DOWN] ) )
			MoveImage(10, 1);
		return true;
	}
    
	// If Joystick
	DWORD dwNumButtons = m_devcaps.dwButtons;
	hr = m_pDID->GetDeviceState(sizeof(DIJOYSTATE), &dijoystate);
    if (hr == DIERR_UNPLUGGED)
    {
        DebugOutput(TEXT("port %d unplugged\n"), m_port);
        return FALSE;
    }
    else if (FAILED(hr))
        return FALSE;

    // Check Buttons.
	// Under the dreamcast, buttons are marked as g_iAButton, g_iBButton.... as
	// defined in CController.hpp.  Meanwhile,  there is no way of defining which 
	// button is A, B or X under the Desktop. this sample plays a sound when the A button 
	// is pressedon any Dreamcast controller, or when the 0 button of any 
	// joystick attached to teh desktop is pressed.

#ifdef UNDER_CE
	for (int iButton = g_iAButton; iButton <= g_iAn6Button; iButton++)
    {
        index = m_buttonIndices[iButton];
        if (index != g_iInvalid)
        {
            m_rgfButtonStateChanged[index] = (m_curButtonValues[index] != dijoystate.rgbButtons[index]);
			m_curButtonValues[index] = dijoystate.rgbButtons[index];
			if(iButton ==  g_iAButton && m_curButtonValues[index]  && m_rgfButtonStateChanged[index])
				g_pdsbuffer2->Play(0, 0, 0);

		}
    }
#else //Desktop
	for (int iButton = 0; iButton < g_nMaxButtons; iButton++)
    {
        index = m_buttonIndices[iButton];
        if (index != g_iInvalid)
        {
            m_rgfButtonStateChanged[index] = (m_curButtonValues[index] != dijoystate.rgbButtons[index]);
			m_curButtonValues[index] = dijoystate.rgbButtons[index];
			if(index == 0 && m_curButtonValues[index]  && m_rgfButtonStateChanged[index])
				g_pdsbuffer2->Play(0, 0, 0);
		}
    }
#endif	//UNDER_CE
    // Check Axes
    for (int i = 0; i < g_nMaxAxes; i++)
    {
        index = m_axisIndices[i].iAxis;
			
		if (index != g_iInvalid)
        {
            
			switch (m_axisIndices[i].eaxis) {
            case eXAxis:
				MIDRANGE = (m_diprangeX.lMax - m_diprangeX.lMin) >> 1;
				lData = dijoystate.lX;
                MoveImage( 10 * (lData - MIDRANGE) / MIDRANGE , 0);
				break;
            
            case eYAxis:
                MIDRANGE = (m_diprangeY.lMax - m_diprangeY.lMin) >> 1;
				lData = dijoystate.lY;
                MoveImage(10 * (lData - MIDRANGE ) / MIDRANGE , 1);
				break;
            }
            
        }
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CController::DIEnumDeviceObjectsProc

Description:

    DirectInput will call this (by way of DIEnumDeviceObjectsProc) one time for
    each of the objects (buttons, axes, etc) on the controller.

Arguments:

    LPCDIDEVICEOBJECTINSTANCE pDIDOI        - The object being enumerated

Return Value:

    TRUE to continue, FALSE to stop

-------------------------------------------------------------------*/
BOOL
CController::DIEnumDeviceObjectsProc(LPCDIDEVICEOBJECTINSTANCE pDIDOI)
{
    if ((LOBYTE(LOWORD(pDIDOI->dwType)) & DIDFT_AXIS) != 0)
    {
        if (IsEqualGUID(pDIDOI->guidType, GUID_XAxis))
            m_axisIndices[m_nAxes].eaxis = eXAxis;
        else
            m_axisIndices[m_nAxes].eaxis = eYAxis;

        m_axisIndices[m_nAxes].iAxis = m_nAxes;
        m_nAxes++;
    }
    else if ((LOBYTE(LOWORD(pDIDOI->dwType)) & DIDFT_BUTTON) != 0)
    {
        // USAGE_FIRST_BUTTON is defined in maplusag.h
#ifdef UNDER_CE
		m_buttonIndices[pDIDOI->wUsage - USAGE_FIRST_BUTTON] = m_nButtons;
#else  //DESKTOP
		m_buttonIndices[pDIDOI->wUsage ] = m_nButtons;
#endif // UNDER_CE

        m_nButtons++;
    }
    else
        DebugOutput(TEXT("Port %d EnumObjects -- UnknownObject 0x%X\n"), m_port, pDIDOI->dwType);

	return(TRUE);
}