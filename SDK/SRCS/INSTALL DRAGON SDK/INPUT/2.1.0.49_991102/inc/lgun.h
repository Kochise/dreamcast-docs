#ifndef _LGUN_H_
#define _LGUN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* error Codes */

#define LGUN_OK                          S_OK
#define LGUNERR_INVALIDARG               E_INVALIDARG
#define LGUNERR_UNKNOWNERROR             E_FAIL
#define LGUNERR_OUTOFMEMORY              E_OUTOFMEMORY
#define LGUNERR_NOINTERFACE              E_NOINTERFACE
#define LGUNERR_DEVICEBUSY               0x80070005L
#define LGUNERR_DEVICEUNPLUGGED          0x80070006L
#define LGUNERR_PENDING                  0x80070007L

// Invalid X or Y value.  If GetGunPosition returns this
// value in either the X or Y position, the gun is not 
// pointing at the screen.
#define LGUN_INVALID_VALUE  -65535

typedef struct _LGUN_POSITION
{
    DWORD   dwReserved;
    long    nX;
    long    nY;
} LGUN_POSITION, *PLGUN_POSITION;
 
// {78BB4C0D-F385-11d2-985F-00C04F72C4D2}
DEFINE_GUID(IID_ILGun, 
0x78bb4c0d, 0xf385, 0x11d2, 0x98, 0x5f, 0x0, 0xc0, 0x4f, 0x72, 0xc4, 0xd2);


#undef INTERFACE
#define INTERFACE ILGun


DECLARE_INTERFACE_(ILGun, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** ILGun methods ***/
    STDMETHOD(GetGunPosition)(THIS_ PLGUN_POSITION pLGunPosition, HANDLE hEvent) PURE;
    STDMETHOD(Calibrate)(THIS_ long nXAimedFor, long nYAimedFor, long nXHit, long nYHit) PURE;
};

typedef struct ILGun *PLGUN;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define ILGun_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define ILGun_AddRef(p) (p)->lpVtbl->AddRef(p)
#define ILGun_Release(p) (p)->lpVtbl->Release(p)
#define ILGun_GetGunPosition(p,a,b) (p)->lpVtbl->GetGunPosition(p,a,b)
#define ILGun_Calibrate(p,a,b,c,d) (p)->lpVtbl->GetGunPosition(p,a,b,c,d)
#else
#define ILGun_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define ILGun_AddRef(p) (p)->AddRef()
#define ILGun_Release(p) (p)->Release()
#define ILGun_GetGunPosition(p,a,b) (p)->GetGunPosition(a,b)
#define ILGun_Calibrate(p,a,b,c,d) (p)->GetGunPosition(a,b,c,d)
#endif




#ifdef __cplusplus
};
#endif

#endif /* _LGUN_H_ */
