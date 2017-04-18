/*
 *  WRAP3D.H
 *  
 *  Wrapper functions for ctl3d. They are callable on WinNT, Win95
 *  (where they are no-ops), and Win16.
 *  
 */

#ifndef _WRAP3D_H_
#define _WRAP3D_H_

#include <ctl3d.h>

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

EXTERN_C LPVOID WINAPI  CTL3D_Initialize(HINSTANCE hinstMe);
EXTERN_C void   WINAPI  CTL3D_Uninitialize(LPVOID lpv);
EXTERN_C void   WINAPI  CTL3D_Subclass(LPVOID lpv, HWND hwnd, DWORD dwFlags);
EXTERN_C void   WINAPI  CTL3D_AutoSubclass(LPVOID lpv, HINSTANCE hinst, BOOL FAR * pf);
EXTERN_C BOOL   WINAPI  CTL3D_IsAutoSubclass(LPVOID lpv);
EXTERN_C void   WINAPI  CTL3D_CeaseAutoSubclass(LPVOID lpv, BOOL f);
EXTERN_C BOOL   WINAPI  CTL3D_ColorChange(LPVOID lpv);
EXTERN_C BOOL   WINAPI  CTL3D_SubclassCtl(LPVOID lpv, HWND hwnd);
EXTERN_C WORD   WINAPI  CTL3D_GetVer(LPVOID lpv);

/*  Format of the LPV */

typedef struct
{
    HINSTANCE   hinst;              /* handle of ctl3d DLL */
    HINSTANCE   hinstMe;            /* handle of caller */
    BOOL        fRegistered;        /* TRUE if we've called Ctl3dRegister */

    FARPROC     fpUnregister;       /* entry points into ctl3d DLL... */
    FARPROC     fpSubclassDlgEx;
    FARPROC     fpIsAutoSubclass;
    FARPROC     fpAutoSubclass;
    FARPROC     fpUnAutoSubclass;
    FARPROC     fpColorChange;
    FARPROC     fpSubclassCtl;
    FARPROC     fpGetVer;
} CTX3D, FAR *LPCTX3D;

#endif /* _WRAP3D_H_ */

