/********************************************************************
 * control.cpp
 *
 * Description
 *    Implementation of CVibrationControl class.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "stdafx.h"         // Precompiled headers
#include "control.h"        // CVibrationControl
#include "pack.h"           // CVibrationPack

/********************************************************************
 * Defines
 ********************************************************************/
#define VIB_AUTOSTOP_MIN    (VIB_AUTOSTOP_INCREMENT_MS / 1000.0)
                            // Min time for autostop vibration (1/4 sec)
#define VIB_AUTOSTOP_MAX    (256 / (1000.0 / VIB_AUTOSTOP_INCREMENT_MS))
                            // Max time for autostop vibration (64 sec)
#define VIB_FREQ_MIN        (VIB_FREQ_INCREMENT_HZ)
                            // Min frequency of vibration (.5 hz)
#define VIB_FREQ_MAX        (256 * VIB_FREQ_INCREMENT_HZ)
                            // Max frequency of vibration (128 hz)

/********************************************************************
 * Macros
 ********************************************************************/
// Return script error for impossible parameters. Return false if 
// device is not plugged in (as of last scan).
#define CHECK_PORT_DEVICE_ARGS(p, d, r)                                     \
    if (!(r)) return E_INVALIDARG;                                          \
    *(r) = 0;                                                               \
    if (((p) < 1) || ((p) > NUM_PORTS) || ((d) < 1) || ((d) > NUM_DEVICES)) \
        return E_INVALIDARG;                                                \
    p--; d--;                                                               \
    CVibrationPack *pPack = _mtxVib[p][d];                                  \
    if (!pPack)                                                             \
        return S_OK;
// Return script error for impossible parameters. Return false if 
// source is just out of range (as of last scan).
#define CHECK_SOURCE_ARGS(s)                                                \
    if (((s) < 1) || ((s) > VIB_MAX_SOURCES))                               \
        return E_INVALIDARG;                                                \
    if ((s) > pPack->_nSources)                                             \
        return S_OK;

/********************************************************************
 * CVibrationControl::CVibrationControl
 *
 * Description
 *    Constructor for CVibrationControl class. It just initializes
 *    member data to NULL.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVibrationControl::CVibrationControl(void)
{
    _pDInput = NULL;
    memset(_mtxVib, 0, sizeof(_mtxVib));
}

/********************************************************************
 * CVibrationControl::~CVibrationControl
 *
 * Description
 *    Destructor for CVibrationControl class. It just outputs a 
 *    message so that you know the control has been destroyed (and
 *    thus you have no reference count problems).
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVibrationControl::~CVibrationControl(void)
{
    OutputDebugString(L"Control destroyed\n");
}

/********************************************************************
 * CVibrationControl::FinalConstruct
 *
 * Description
 *    This is a special function that ATL calls after the constructor.
 *    If there were any objects that needed to be created, they should
 *    be created here rather than in the real constructor. That way, 
 *    if an error happens, you can return E_FAIL from this function
 *    and the defective object will be destroyed.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      object created successfully
 ********************************************************************/
HRESULT CVibrationControl::FinalConstruct(void)
{
    return S_OK;
}

/********************************************************************
 * CVibrationControl::FinalConstruct
 *
 * Description
 *    This is a special function that ATL calls before the destructor.
 *    You should do all of your clean up in this function.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      object destroyed successfully
 ********************************************************************/
HRESULT CVibrationControl::FinalRelease(void)
{
    CleanUp();

    if (_pDInput)
    {
        _pDInput->Release();
        _pDInput = NULL;
    }

    return S_OK;
}

/********************************************************************
 * CVibrationControl::CleanUp
 *
 * Description
 *    Deletes the vibration pack objects.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CVibrationControl::CleanUp(void)
{
    int p, d;
    for (p = 0; p < NUM_PORTS; p++)
    {
        for (d = 0; d < NUM_DEVICES; d++)
        {
            if (_mtxVib[p][d])
            {
                delete _mtxVib[p][d];
                _mtxVib[p][d] = NULL;
            }
        }
    }
}

/********************************************************************
 * IVibrationControl
 ********************************************************************/

/********************************************************************
 * CVibrationControl::Scan
 *
 * Description
 *    Creates the Direct Input object (if needed) and enumerates all
 *    of the vibration pack devices (if any).
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      devices successfully searched
 *    E_FAIL    could not create DInput object
 ********************************************************************/
STDMETHODIMP CVibrationControl::Scan(void)
{
    // Remove traces of last scan
    CleanUp();

    // Get Direct Input object
    if (!_pDInput)
    {
        if (FAILED(DirectInputCreate(_Module.GetModuleInstance(), 
                                     DIRECTINPUT_VERSION, 
                                     &_pDInput, NULL)) || 
            !_pDInput)
        {
            OutputDebugString(L"Error: Cannot create DInput object\n");
            return E_FAIL;
        }
    }

    // Find the vibration packs
    MapleEnumerateDevices(MDT_VIBRATION, VibrationEnumProc, this, 0);

    return S_OK;
}

/********************************************************************
 * CVibrationControl::IsPluggedIn
 *
 * Description
 *    Gets info on specified vibration pack to determine if it is still
 *    plugged in.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    pbPlugged     Filled with true/false for whether specified 
 *                  vibration pack is currently plugged in
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::IsPluggedIn(short nPort, short nDevice, 
                                            VARIANT_BOOL *pbPlugged)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbPlugged);

    *pbPlugged = pPack->IsPlugged();

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetNumberOfSources
 *
 * Description
 *    Returns number of sources that the specified vibration pack has.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    pnSources     Filled with number of vibration sources the 
 *                  specified pack has (0 if device was not present at
 *                  last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetNumberOfSources(short nPort, short nDevice, 
                                                   short *pnSources)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pnSources);

    *pnSources = (pPack->_pVib ? pPack->_nSources : 0);

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetNumberOfSimultaneousSources
 *
 * Description
 *    Returns number of simultaneous sources that the specified 
 *    vibration pack supports.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    pnSimSources  Filled with number of simultaneous vibration sources 
 *                  the specified pack is capable of (0 if device was 
 *                  not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetNumberOfSimultaneousSources(short nPort, 
                                                               short nDevice, 
                                                               short *pnSimSources)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pnSimSources);

    *pnSimSources = (pPack->_pVib ? pPack->_nSimSources : 0);

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetMinimumFrequency
 *
 * Description
 *    Returns minimum vibration frequency that the specified vibration 
 *    pack source supports.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pfFreq        Filled with the minimum frequency (in hertz) the
 *                  specified source in the specified pack is capable
 *                  of (0 if device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetMinimumFrequency(short nPort, short nDevice, 
                                                    short nSource, double *pfFreq)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pfFreq);
    CHECK_SOURCE_ARGS(nSource);

    // Convert frequency from internal representation to hertz
    *pfFreq = (pPack->_pVib ? pPack->_aVibInfo[nSource-1].minFrequency * VIB_FREQ_INCREMENT_HZ + VIB_FREQ_INCREMENT_HZ: 0);

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetMinimumFrequency
 *
 * Description
 *    Returns maximum vibration frequency that the specified vibration 
 *    pack source supports.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pfFreq        Filled with the maximum frequency (in hertz) the
 *                  specified source in the specified pack is capable
 *                  of (0 if device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetMaximumFrequency(short nPort, short nDevice, 
                                                    short nSource, double *pfFreq)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pfFreq);
    CHECK_SOURCE_ARGS(nSource);

    // Convert frequency from internal representation to hertz
    *pfFreq = (pPack->_pVib ? pPack->_aVibInfo[nSource-1].maxFrequency * VIB_FREQ_INCREMENT_HZ + VIB_FREQ_INCREMENT_HZ: 0);

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetAxisOfVibration
 *
 * Description
 *    Returns axis of vibration vibration pack source supports.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbstrAxis     Filled with the axis of vibration string (NULL if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetAxisOfVibration(short nPort, short nDevice, 
                                                   short nSource, BSTR *pbstrAxis)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbstrAxis);
    CHECK_SOURCE_ARGS(nSource);

    if (pPack->_pVib)
    {
        // Convert axis from internal representation to string
        LPWSTR pszAxis = L"unknown";
        switch (pPack->_aVibInfo[nSource-1].axis)
        {
            case VIB_AXIS_NONE:
                pszAxis = L"none";
                break;
            case VIB_AXIS_X:
                pszAxis = L"x";
                break;
            case VIB_AXIS_Y:
                pszAxis = L"y";
                break;
            case VIB_AXIS_Z:
                pszAxis = L"z";
                break;
        }

        *pbstrAxis = SysAllocString(pszAxis);
    }

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetPosition
 *
 * Description
 *    Returns position of vibration pack source with the vibration 
 *    pack.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbstrPos      Filled with the position of vibration source (NULL if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetPosition(short nPort, short nDevice, 
                                            short nSource, BSTR *pbstrPos)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbstrPos);
    CHECK_SOURCE_ARGS(nSource);

    if (pPack->_pVib)
    {
        // Convert position from internal representation to string
        LPWSTR pszPos = L"unknown";
        switch (pPack->_aVibInfo[nSource-1].position)
        {
            case VIB_POSITION_FRONT:
                pszPos = L"front";
                break;
            case VIB_POSITION_BACK:
                pszPos = L"back";
                break;
            case VIB_POSITION_LEFT:
                pszPos = L"left";
                break;
            case VIB_POSITION_RIGHT:
                pszPos = L"right";
                break;
        }

        *pbstrPos = SysAllocString(pszPos);
    }

    return S_OK;
}

/********************************************************************
 * CVibrationControl::HasVariableIntensityCapability
 *
 * Description
 *    Returns whether or not the vibration pack source supports
 *    variable intensity.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbCap         Filled with true if vibration source has the
 *                  capability or false if it does not (false if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::HasVariableIntensityCapability(short nPort, 
                                short nDevice, short nSource, VARIANT_BOOL *pbCap)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbCap);
    CHECK_SOURCE_ARGS(nSource);

    *pbCap = (pPack->_pVib && (pPack->_aVibInfo[nSource-1].bCaps & VIBCAPS_VARIABLEINTENSITY)) ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

/********************************************************************
 * CVibrationControl::HasContinuousVibrationCapability
 *
 * Description
 *    Returns whether or not the vibration pack source supports
 *    continuous vibration.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbCap         Filled with true if vibration source has the
 *                  capability or false if it does not (false if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::HasContinuousVibrationCapability(short nPort, 
                                short nDevice, short nSource, VARIANT_BOOL *pbCap)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbCap);
    CHECK_SOURCE_ARGS(nSource);

    *pbCap = (pPack->_pVib && (pPack->_aVibInfo[nSource-1].bCaps & VIBCAPS_CONTINUOUSVIBRATION)) ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

/********************************************************************
 * CVibrationControl::HasDirectionalCapability
 *
 * Description
 *    Returns whether or not the vibration pack source supports
 *    directional vibration.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbCap         Filled with true if vibration source has the
 *                  capability or false if it does not (false if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::HasDirectionalCapability(short nPort, 
                                short nDevice, short nSource, VARIANT_BOOL *pbCap)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbCap);
    CHECK_SOURCE_ARGS(nSource);

    *pbCap = (pPack->_pVib && (pPack->_aVibInfo[nSource-1].bCaps & VIBCAPS_DIRECTIONAL)) ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

/********************************************************************
 * CVibrationControl::HasArbitrayWaveformCapability
 *
 * Description
 *    Returns whether or not the vibration pack source supports
 *    arbitrary wave forms.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pbCap         Filled with true if vibration source has the
 *                  capability or false if it does not (false if
 *                  device was not present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::HasArbitraryWaveformCapability(short nPort, 
                                short nDevice, short nSource, VARIANT_BOOL *pbCap)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbCap);
    CHECK_SOURCE_ARGS(nSource);

    *pbCap = (pPack->_pVib && (pPack->_aVibInfo[nSource-1].bCaps & VIBCAPS_ARBITRARYWAVEFORM)) ? VARIANT_TRUE : VARIANT_FALSE;

    return S_OK;
}

/********************************************************************
 * CVibrationControl::GetAutoStopTime
 *
 * Description
 *    Returns autotime time of the specified vibration pack source.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    pfTime        Filled number of seconds for autostop for specified
 *                  vibration source (0 if device was not present at 
 *                  last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::GetAutoStopTime(short nPort, short nDevice, 
                                                short nSource, double *pfTime)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pfTime);
    CHECK_SOURCE_ARGS(nSource);

    // Convert auto stop time from internal representation to seconds
    *pfTime = pPack->_pVib ? (pPack->_aAutoStop[nSource-1] * (VIB_AUTOSTOP_INCREMENT_MS / 1000.0) + 0.25) : 0;

    return S_OK;
}

/********************************************************************
 * CVibrationControl::SetAutoStopTime
 *
 * Description
 *    Sets autotime time of the specified vibration pack source.
 *
 * Parameters
 *    nPort         Port ID (1 - 4)
 *    nDevice       Device number (1 - 2)
 *    nSource       Source number (1 - 15)
 *    fTime         Time in seconds for new autostop value for 
 *                  specified vibration source
 *    pbResult      Filled with true if setting time was successful
 *                  or false if it was not (false if device was not 
 *                  present at last scan)
 * 
 * Returns
 *    S_OK          parameters valid
 *    E_INVALIDARG  parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::SetAutoStopTime(short nPort, short nDevice, 
                                                short nSource, double fTime, 
                                                VARIANT_BOOL *pbResult)
{
    BYTE dummy;
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, &dummy);
    CHECK_SOURCE_ARGS(nSource);

    // Validate auto stop time
    if ((fTime < VIB_AUTOSTOP_MIN) || (fTime > VIB_AUTOSTOP_MAX))
    {
        return E_INVALIDARG;
    }

    if (pPack->_pVib)
    {
        // Convert auto stop time from seconds to internal representation
        BYTE source = (BYTE)nSource;
        BYTE time = (BYTE)((fTime - 0.25) * (1000.0 / VIB_AUTOSTOP_INCREMENT_MS));
        HRESULT hr = pPack->_pVib->SetVibAutostopTimes(1, &source, &time, NULL);

        if (SUCCEEDED(hr))
        {
            pPack->_aAutoStop[nSource - 1] = time;

            *pbResult = VARIANT_TRUE;
        }
    }

    return S_OK;
}

/********************************************************************
 * CVibrationControl::Vibrate
 *
 * Description
 *    Vibrates the specified vibration pack source according to 
 *    specified parameters (see doumentation on IVib for further
 *    details).
 *
 * Parameters
 *    nPort           Port ID (1 - 4)
 *    nDevice         Device number (1 - 2)
 *    nSource         Source number (1 - 15)
 *    bContinuousVib  true if vibration is to be continuous (i.e., use
 *                    auto stop time)
 *    bstrVibType     constant, convergent, or divergent
 *    nInitialPower   1-7 or 0 (and constant) to turn off vibration
 *    bstrDirection   forward or reverse
 *    fFrequency      between .5 and 128 (and within source's range)
 *    nWavesPerStep   between 0 and 255
 *    pbResult        Filled with true if vibration was sucessful or
 *                    if it was not (false if device was not present
 *                    at last scan)
 * 
 * Returns
 *    S_OK            parameters valid
 *    E_INVALIDARG    parameters invalid 
 ********************************************************************/
STDMETHODIMP CVibrationControl::Vibrate(short nPort, short nDevice, short nSource, 
                                        VARIANT_BOOL bContinuousVib, BSTR bstrVibType, 
                                        short nInitialPower, BSTR bstrDirection, 
                                        double fFrequency, short nWavesPerStep, 
                                        VARIANT_BOOL *pbResult)
{
    CHECK_PORT_DEVICE_ARGS(nPort, nDevice, pbResult);
    CHECK_SOURCE_ARGS(nSource);
    short nVibType;
    short nDirection;

    // Validate vibration type and convert to internal representation
    if (!_wcsicmp(bstrVibType, L"constant"))
    {
        nVibType = VIB_TYPE_CONSTANT;
    }
    else if (!_wcsicmp(bstrVibType, L"convergent"))
    {
        nVibType = VIB_TYPE_CONVERGENT;
    }
    else if (!_wcsicmp(bstrVibType, L"divergent"))
    {
        nVibType = VIB_TYPE_DIVERGENT;
    }
    else
    {
        return E_INVALIDARG;
    }

    // Validate direction and convert to internal representation
    if (!_wcsicmp(bstrDirection, L"forward"))
    {
        nDirection = VIB_DIRECTION_FORWARD;
    }
    else if (!_wcsicmp(bstrDirection, L"reverse"))
    {
        nDirection = VIB_DIRECTION_REVERSE;
    }
    else
    {
        return E_INVALIDARG;
    }

    // Validate initial power
    if (nInitialPower == VIB_POWER_NONE)
    {
        if (nVibType != VIB_TYPE_CONSTANT)
        {
            return E_INVALIDARG;
        }
    }
    else if ((nInitialPower < VIB_POWER_NONE) || (nInitialPower > VIB_POWER_MAX))
    {
        return E_INVALIDARG;
    }

    // Validate waves per step
    if ((nWavesPerStep > 255) || (nWavesPerStep < 0))
    {
        return E_INVALIDARG;
    }
        
    // Validate frequency and convert to internal representation
    if ((fFrequency < VIB_FREQ_MIN) || (fFrequency > VIB_FREQ_MAX))
    {
        return E_INVALIDARG;
    }
    BYTE nFreq = (BYTE)((fFrequency - VIB_FREQ_INCREMENT_HZ) / VIB_FREQ_INCREMENT_HZ);

    if (pPack->_pVib)
    {
        // Fill vibration structure
        VIB_SETTINGS vibsettings;

        vibsettings.vibType        = (BYTE)nVibType;
        vibsettings.sourceId       = (BYTE)nSource;
        vibsettings.direction      = (BYTE)nDirection;
        vibsettings.frequency      = (BYTE)nFreq;
        vibsettings.initialPower   = (BYTE)nInitialPower;
        vibsettings.wavesPerStep   = (BYTE)nWavesPerStep;
        vibsettings.bContinuousVib = (BYTE)(bContinuousVib ? 1 : 0);

        // Do the vibration
        HRESULT hr = pPack->_pVib->Vibrate(1, &vibsettings, NULL); 
        if (SUCCEEDED(hr))
        {
            *pbResult = VARIANT_TRUE;
        }
    }

    return S_OK;
}

/********************************************************************
 * CVibrationControl::FoundPack
 *
 * Description
 *    When vibration pack is found, a CVibrationPack object for it
 *    is created, initialized, and stored.
 *
 * Parameters
 *    pMDI          device data for current device being enumerated
 * 
 * Returns
 *    None
 ********************************************************************/
void CVibrationControl::FoundPack(LPCMAPLEDEVICEINSTANCE pMDI)
{
    // Validate port and device
    if ((pMDI->dwPort >= NUM_PORTS) || ((pMDI->dwDevNum - 1) >= NUM_DEVICES))
    {
        return;
    }

    // Check for existing pack (should not happen)
    if (_mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1])
    {
        delete _mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1];
        _mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1] = NULL;
    }

    // Create new Vibration Pack object and validate it
    _mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1] = new CVibrationPack(pMDI);
    if (!_mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1] || 
        !_mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1]->IsOkay())
    {
        // On error, just get rid of the Vibration Pack object
        delete _mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1];
        _mtxVib[pMDI->dwPort][pMDI->dwDevNum - 1] = NULL;
    }
}

/********************************************************************
 * CVibrationControl::VibrationEnumProc
 *
 * Description
 *    Callback function for MapleEnumerateDevices. Uses the context
 *    data to find the control that is doing the enumerating and 
 *    hands off responsibility to it.
 *
 * Parameters
 *    pMDI          device data for current device being enumerated
 *    pvContext     pointer to owning CVibrationControl
 * 
 * Returns
 *    TRUE          continue enumerating
 *    FALSE         an error happened, stop enumerating
 ********************************************************************/
BOOL CALLBACK CVibrationControl::VibrationEnumProc(LPCMAPLEDEVICEINSTANCE pMDI, 
                                                   LPVOID pvContext)
{
    // Convert function data to this pointer for CVibrationControl
    CVibrationControl *pThis = (CVibrationControl *)pvContext;
    if (!pThis)
    {
        return FALSE;
    }

    // Notify control that we have a vibration pack
    if (pMDI->devType == MDT_VIBRATION)
    {
        pThis->FoundPack(pMDI);
    }
    
    return TRUE;
}
