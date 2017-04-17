/********************************************************************
 * control.h
 *
 * Description
 *   CVibrationControl class.
 ********************************************************************/

#ifndef __CONTROL_H     // Prevent multiple inclusions
#define __CONTROL_H

/********************************************************************
 * Includes
 ********************************************************************/
#include <dinput.h>     // Direct Input
#include <mapledev.h>   // Maple device functions
#include <vib.h>        // IVib
#include "vibectrl.h"   // IVibrationControl

/********************************************************************
 * Defines
 ********************************************************************/
#define NUM_PORTS       4       // Maximum number of controllers
#define NUM_DEVICES     2       // Maximum number of devices per controller

/********************************************************************
 * Forwards
 ********************************************************************/
class CVibrationPack;

/********************************************************************
 * class CVibrationControl
 *
 * Description
 *   Handles everything that needs to be handled to make this class
 *   an ActiveX control (with the help of ATL).
 ********************************************************************/
class ATL_NO_VTABLE CVibrationControl :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CVibrationControl, &CLSID_VibrationControl>,
    public CComControl<CVibrationControl>,
    public IDispatchImpl<IVibrationControl, &IID_IVibrationControl, &LIBID_VIBECTRLLib>,
    public IPersistStreamInitImpl<CVibrationControl>,
    public IPersistStorageImpl<CVibrationControl>,
    public IOleControlImpl<CVibrationControl>,
    public IOleObjectImpl<CVibrationControl>,
    public IOleInPlaceActiveObjectImpl<CVibrationControl>,
    public IViewObjectExImpl<CVibrationControl>,
    public IOleInPlaceObjectWindowlessImpl<CVibrationControl>
{
public:

    // Not used in this DLL, but needs to be here for ATL
DECLARE_REGISTRY_RESOURCEID(100)

    // Interfaces implemented by CVibrationControl (QueryInterface table)
BEGIN_COM_MAP(CVibrationControl)
    COM_INTERFACE_ENTRY(IVibrationControl)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY_IMPL(IOleControl)
    COM_INTERFACE_ENTRY_IMPL(IOleObject)
    COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
    COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
END_COM_MAP()

    // Not used in this DLL, but needs to be here for ATL
BEGIN_PROPERTY_MAP(CVibrationControl)
END_PROPERTY_MAP()

    // Not used in this DLL, but needs to be here for ATL
BEGIN_MSG_MAP(CVibrationControl)
END_MSG_MAP()

    // IVibrationControl
    STDMETHOD(Scan)(void);
    STDMETHOD(IsPluggedIn)(short nPort, short nDevice, VARIANT_BOOL *pbPlugged);
    STDMETHOD(GetNumberOfSources)(short nPort, short nDevice, short *pnSources);
    STDMETHOD(GetNumberOfSimultaneousSources)(short nPort, short nDevice, short *pnSimSources);
    STDMETHOD(GetMinimumFrequency)(short nPort, short nDevice, short nSource, double *pfFreq);
    STDMETHOD(GetMaximumFrequency)(short nPort, short nDevice, short nSource, double *pfFreq);
    STDMETHOD(GetAxisOfVibration)(short nPort, short nDevice, short nSource, BSTR *pbstrAxis);
    STDMETHOD(GetPosition)(short nPort, short nDevice, short nSource, BSTR *pbstrPos);
    STDMETHOD(HasVariableIntensityCapability)(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
    STDMETHOD(HasContinuousVibrationCapability)(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
    STDMETHOD(HasDirectionalCapability)(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
    STDMETHOD(HasArbitraryWaveformCapability)(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
    STDMETHOD(GetAutoStopTime)(short nPort, short nDevice, short nSource, double *pfTime);
    STDMETHOD(SetAutoStopTime)(short nPort, short nDevice, short nSource, double fTime, VARIANT_BOOL *pbResult);
    STDMETHOD(Vibrate)(short nPort, short nDevice, short nSource, VARIANT_BOOL bContinuousVib, BSTR bstrVibType, short nInitialPower, BSTR bstrDirection, double fFrequency, short nWavesPerStep, VARIANT_BOOL *pbResult);

    // Constructor/Destructor
                CVibrationControl(void);
    virtual    ~CVibrationControl(void);

    HRESULT     FinalConstruct(void);
    HRESULT     FinalRelease(void);

private:
    // Helper functions
    void        FoundPack(LPCMAPLEDEVICEINSTANCE pMDI);
    void        CleanUp(void);
    static BOOL VibrationEnumProc(LPCMAPLEDEVICEINSTANCE pMDI, LPVOID pvContext);

    // Member data
    IDirectInput   *_pDInput;                           // DirectInput
    CVibrationPack *_mtxVib[NUM_PORTS][NUM_DEVICES];    // Vibration Packs
};

#endif // __CONTROL_H
