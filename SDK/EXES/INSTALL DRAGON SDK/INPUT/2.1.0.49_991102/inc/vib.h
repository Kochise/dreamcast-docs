#ifndef _VIB_H_
#define _VIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/* error Codes */

#define VIB_OK                          S_OK
#define VIBERR_INVALIDARG               E_INVALIDARG
#define VIBERR_UNKNOWNERROR             E_FAIL
#define VIBERR_OUTOFMEMORY              E_OUTOFMEMORY
#define VIBERR_NOINTERFACE              E_NOINTERFACE
#define VIBERR_DEVICEBUSY               0x80070005L
#define VIBERR_DEVICEUNPLUGGED          0x80070006L
#define VIBERR_PENDING                  0x80070007L

#define VIB_MAX_SOURCES         15

#define VIB_POSITION_FRONT      0
#define VIB_POSITION_BACK       1
#define VIB_POSITION_LEFT       2
#define VIB_POSITION_RIGHT      3

#define VIB_AXIS_NONE           0
#define VIB_AXIS_X              1
#define VIB_AXIS_Y              2
#define VIB_AXIS_Z              3

/* this means that minFrequency ranges from 0x0 = 0.5Hz to 0xFF = 128Hz */
#define VIB_FREQ_INCREMENT_HZ      0.5

/* This means that autostop ranges from 0x0 = 0.25 seconds to 0xFF = 64.0 seconds */
#define VIB_AUTOSTOP_INCREMENT_MS 250

/* This means that a duration of 0 is equal to 10 milliseconds, 2 = 30 ms, etc. */
#define VIB_WAVEFORM_DURATION_INCREMENT_MS 10


#define VIBCAPS_VARIABLEINTENSITY   0x01
#define VIBCAPS_CONTINUOUSVIBRATION 0x02
#define VIBCAPS_DIRECTIONAL         0x04
#define VIBCAPS_ARBITRARYWAVEFORM   0x08
 
typedef struct _VIB_INFO
{
    BYTE    sourceId;
    BYTE    position;
    BYTE    axis;
    BYTE    bCaps;
    BYTE    minFrequency;
    BYTE    maxFrequency;  
} VIB_INFO, *PVIB_INFO;


#define VIB_TYPE_CONSTANT       0
#define VIB_TYPE_CONVERGENT     1
#define VIB_TYPE_DIVERGENT      2

#define VIB_POWER_NONE          0
#define VIB_POWER_MIN           1
#define VIB_POWER_MAX           7

#define VIB_DIRECTION_FORWARD   0
#define VIB_DIRECTION_REVERSE   1

typedef struct _VIB_SETTINGS
{
    BYTE    sourceId;
    BYTE    bContinuousVib;
    BYTE    vibType;
    BYTE    initialPower;
    BYTE    direction;
    BYTE    frequency;
    BYTE    wavesPerStep;
} VIB_SETTINGS, *PVIB_SETTINGS;


typedef struct _VIB_WAVEFORM_SETTINGS
{
    BYTE duration;
    BYTE direction;
    BYTE power;
} VIB_WAVEFORM_SETTINGS, *PVIB_WAVEFORM_SETTINGS;    

// {BBDFEF17-D1C9-11d2-984E-00C04F72C4D2}
DEFINE_GUID(IID_IVib, 
0xbbdfef17, 0xd1c9, 0x11d2, 0x98, 0x4e, 0x0, 0xc0, 0x4f, 0x72, 0xc4, 0xd2);


#undef INTERFACE
#define INTERFACE IVib


DECLARE_INTERFACE_(IVib, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVib methods ***/
    STDMETHOD(GetVibArbitraryWaveform)(THIS_ UINT sourceId, UINT *pNumSettings, PVIB_WAVEFORM_SETTINGS pSettingsArray) PURE;
    STDMETHOD(GetVibAutostopTimes)(THIS_ UINT *pNumTimes, BYTE *pTimesArray) PURE;
    STDMETHOD(GetVibInfo)(THIS_ UINT *pNumVibSources, UINT *pNumSimultaneousSources, PVIB_INFO pVibInfoArray) PURE;
    STDMETHOD(SetVibArbitraryWaveform)(THIS_ UINT sourceId, UINT numSettings, PVIB_WAVEFORM_SETTINGS pSettingsArray, HANDLE hEvent) PURE;
    STDMETHOD(SetVibAutostopTimes)(THIS_ UINT numVibSources, BYTE *pSourceIdArray, BYTE *pAutostopTimesArray, HANDLE hEvent) PURE;
    STDMETHOD(Vibrate)(THIS_ UINT numVibSources, PVIB_SETTINGS pVibSettingsArray, HANDLE hEvent) PURE;
};

typedef struct IVib *PVIB;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IVib_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IVib_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IVib_Release(p) (p)->lpVtbl->Release(p)
#define IVib_GetVibArbitraryWaveform(p,a,b) (p)->lpVtbl->GetVibArbitraryWaveform(p,a,b)
#define IVib_GetVibAutostopTimes(p,a,b) (p)->lpVtbl->GetVibAutostopTimes(p,a,b)
#define IVib_GetVibInfo(p,a,b,c) (p)->lpVtbl->GetVibInfo(p,a,b,c)
#define IVib_SetVibArbitraryWaveform(p,a,b,c) (p)->lpVtbl->SetVibArbitraryWaveform(p,a,b,c)
#define IVib_SetVibAutostopTimes(p,a,b,c,d) (p)->lpVtbl->SetVibAutostopTimes(p,a,b,c,d)
#define IVib_Vibrate(p,a,b,c) (p)->lpVtbl->Vibrate(p,a,b,c)
#else
#define IVib_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IVib_AddRef(p) (p)->AddRef()
#define IVib_Release(p) (p)->Release()
#define IVib_GetVibArbitraryWaveform(p,a,b) (p)->GetVibArbitraryWaveform(a,b)
#define IVib_GetAutostopTimes(p,a,b) (p)->GetAutostopTimes(a,b)
#define IVib_GetVibInfo(p,a,b,c) (p)->GetVibInfo(a,b,c)
#define IVib_SetVibArbitraryWaveform(p,a,b,c) (p)->SetVibArbitraryWaveform(a,b,c)
#define IVib_SetVibAutostopTimes(p,a,b,c,d) (p)->SetVibAutostopTimes(a,b,c,d)
#define IVib_Vibrate(p,a,b,c) (p)->Vibrate(a,b,c)
#endif




#ifdef __cplusplus
};
#endif

#endif /* _VIB_H_ */
