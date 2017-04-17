/****************************************************************************
 *
 *  Copyright (C) 1998 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       mapledev.h
 *  Content:    MAPLE device support header file
 *
 ****************************************************************************/


#ifndef __MAPLEDEV_INCLUDED__
#define __MAPLEDEV_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


typedef DWORD MAPLEDEVTYPE;

#define MDT_ALLDEVICES      0x00000000
#define MDT_CONTROLLER      0x00000001
#define MDT_STORAGE         0x00000002
#define MDT_LCD             0x00000004
#define MDT_TIMER           0x00000008
#define MDT_AUDIO_IN        0x00000010
#define MDT_LIGHTGUN        0x00000080
#define MDT_VIBRATION       0x00000100

#define MAPLEDEV_REGION_NORTH_AMERICA 0x01
#define MAPLEDEV_REGION_JAPAN         0x02
#define MAPLEDEV_REGION_ASIA          0x04
#define MAPLEDEV_REGION_EUROPE        0x08

#define MAPLEDEV_EXPDIR_TOP       0x00
#define MAPLEDEV_EXPDIR_BOTTOM    0x01
#define MAPLEDEV_EXPDIR_LEFT      0x02
#define MAPLEDEV_EXPDIR_RIGHT     0x03


typedef struct MAPLEDEVICEINSTANCE
{
    GUID guidDevice;
    MAPLEDEVTYPE devType;
    DWORD dwPort;            // MAPLE port Number
    DWORD dwDevNum;          // Maple device number
    DWORD dwFcnNum;          // Maple function number
    DWORD dwWorldRegion;     // Region value
    DWORD dwDirection;       // Device direction
    DWORD dwCurrent;         // Standby and max current properties
    TCHAR tszInstanceName[MAX_PATH]; // Name (in text) of the device
    TCHAR tszProductName[MAX_PATH]; // Name (in text) of the device
} MAPLEDEVICEINSTANCE, *LPMAPLEDEVICEINSTANCE;

typedef const MAPLEDEVICEINSTANCE *LPCMAPLEDEVICEINSTANCE;

typedef BOOL (PASCAL * LPFNMAPLEENUMDEVICECALLBACK)(LPCMAPLEDEVICEINSTANCE, LPVOID);

extern HRESULT WINAPI MapleEnumerateDevices( MAPLEDEVTYPE mapledevtype,
                                             LPFNMAPLEENUMDEVICECALLBACK pfn,
                                             PVOID pvContext,
                                             DWORD dwFlags);

extern HRESULT WINAPI MapleCreateDevice(
                                        const GUID *pguidDevice,
                                        IUnknown **ppIUnknown);

extern VOID WINAPI MapleFreeLibraries( VOID );

// Error codes
#define MD_OK                           S_OK
#define MDERR_INVALIDPARAM              E_INVALIDARG
#define MDERR_GENERIC                   E_FAIL
#define MDERR_OUTOFMEMORY               E_OUTOFMEMORY


#ifdef __cplusplus
};
#endif


#endif  /* __MAPLEDEV_INCLUDED__ */





