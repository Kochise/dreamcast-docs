/********************************************************************
 * pack.cpp
 *
 * Description
 *    Implementation of CVibrationPack class.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "stdafx.h"
#include "pack.h"

/********************************************************************
 * CVibrationPack::CVibrationPack
 *
 * Description
 *    Constructor for CVibrationPack class. It creates a maple device
 *    object for the specified vibration pack, and it initializes the
 *    data for the pack.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVibrationPack::CVibrationPack(LPCMAPLEDEVICEINSTANCE pMDI)
{
    _pVib = NULL;

    IUnknown *pUnknown = NULL;
    HRESULT hr = MapleCreateDevice(&pMDI->guidDevice, &pUnknown);
    if (SUCCEEDED(hr) && pUnknown)
    {
        pUnknown->QueryInterface(IID_IVib, (LPVOID *)&_pVib);
        pUnknown->Release();
    }

    IsPlugged();
}

/********************************************************************
 * CVibrationPack::~CVibrationPack
 *
 * Description
 *    Destructor for CVibrationPack class. It releases the maple
 *    device object for the vibration pack.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVibrationPack::~CVibrationPack(void)
{
    if (_pVib)
    {
        _pVib->Release();
        _pVib = NULL;
    }
}

/********************************************************************
 * CVibrationPack::IsOkay
 *
 * Description
 *    Returns whether or not the object was initialized correctly.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    true      object initialized successfully
 *    false     object not initialized successfully
********************************************************************/
CVibrationPack::IsOkay(void)
{
    return (_pVib != NULL);
}

/********************************************************************
 * CVibrationPack::IsPlugged
 *
 * Description
 *    Gets info on vibration pack to determine if it is still plugged in.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    true      vibration pack still plugged in
 *    false     vibration pack has been removed
 ********************************************************************/
VARIANT_BOOL CVibrationPack::IsPlugged(void)
{
    if (_pVib)
    {
        // Get vibration pack data
        UINT nSources = VIB_MAX_SOURCES;
        UINT nSimSources;
        HRESULT hr = _pVib->GetVibInfo(&nSources, &nSimSources, _aVibInfo);
        _nSources = (short)nSources;
        _nSimSources = nSimSources;

        // If it is not plugged in anymore, destroy the IVib object
        if (FAILED(hr))
        {
            _pVib->Release();
            _pVib = NULL;
        }
    }

    // Get the autostop times for the vibration pack
    if (_pVib)
    {
        UINT nSources = VIB_MAX_SOURCES;
        _pVib->GetVibAutostopTimes(&nSources, _aAutoStop);
    }

    return (_pVib ? VARIANT_TRUE : VARIANT_FALSE);
}


