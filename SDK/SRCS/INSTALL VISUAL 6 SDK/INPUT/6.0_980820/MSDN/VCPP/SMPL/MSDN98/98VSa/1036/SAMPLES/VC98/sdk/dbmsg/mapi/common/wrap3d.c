/*
 *  WRAP3D.C
 */

#include <windows.h>
#include <mapix.h>
#ifdef  WIN16
#include <memory.h>
#endif  
#include <mapiwin.h>
#include "wrap3d.h"

STDAPI_(LPVOID)
CTL3D_Initialize(HINSTANCE hinstMe)
{
    UINT        fuErr;
    HINSTANCE   hinst = 0;
    BOOL        fRegistered = FALSE;    /* assume failure */
    FARPROC     fpEnabled;
    FARPROC     fpRegister;
    LPCTX3D     pctx = NULL;
    DWORD       dwVer;

    /*
     * //$ If the Win 4 shell is present, don't even look for the DLL.
     * //$ Need to verify this algorithm.
     */

    dwVer = GetVersion();
    if (LOBYTE(LOWORD(dwVer)) >= 4)
        goto fail;

#ifdef _WIN32
    pctx = LocalAlloc(LPTR, sizeof(CTX3D));
    if (!pctx)
        goto fail;
#else
    if (MAPIAllocateBuffer(sizeof(CTX3D), &pctx))
        goto fail;
#endif
    ZeroMemory(pctx, sizeof(CTX3D));

    /* Attempt to load the DLL. Do not allow any error messages. */
    fuErr = SetErrorMode(SEM_NOOPENFILEERRORBOX);
#ifdef  _WIN32
    hinst = LoadLibraryA("CTL3D32.DLL");
    SetErrorMode(fuErr);
    if (!hinst)
        goto fail;
#else
    hinst = LoadLibrary("CTL3DV2.DLL");
    SetErrorMode(fuErr);
    if (hinst < HINSTANCE_ERROR)
        goto fail;
#endif

    /* Get the entry points we need. */
    if (!(fpEnabled = GetProcAddress(hinst, "Ctl3dEnabled")))
        goto fail;
    if (!(fpRegister = GetProcAddress(hinst, "Ctl3dRegister")))
        goto fail;
    if (!(pctx->fpUnregister = GetProcAddress(hinst, "Ctl3dUnregister")))
        goto fail;
    if (!(pctx->fpSubclassDlgEx = GetProcAddress(hinst, "Ctl3dSubclassDlgEx")))
        goto fail;
    if (!(pctx->fpColorChange = GetProcAddress(hinst, "Ctl3dColorChange")))
        goto fail;
    if ((pctx->fpIsAutoSubclass = GetProcAddress(hinst, "Ctl3dIsAutoSubclass")) &&
        (!(pctx->fpAutoSubclass = GetProcAddress(hinst, "Ctl3dAutoSubclass")) ||
        !(pctx->fpUnAutoSubclass = GetProcAddress(hinst, "Ctl3dUnAutoSubclass"))))
        goto fail;
    if (!(pctx->fpSubclassCtl = GetProcAddress(hinst, "Ctl3dSubclassCtl")))
        goto fail;
    if (!(pctx->fpGetVer = GetProcAddress(hinst, "Ctl3dGetVer")))
        goto fail;

    /* If we were not already registered, do so. */
    if (!(*fpEnabled)())
        pctx->fRegistered = (*fpRegister)(hinstMe);

    /* Remember the library handle. */
    pctx->hinst = hinst;
    pctx->hinstMe = hinstMe;

ret:
    return pctx;

fail:
    if (hinst)
        FreeLibrary(hinst);
#ifdef  _WIN32
    if (pctx)
        LocalFree(pctx);
#else
    MAPIFreeBuffer(pctx);
#endif  
    pctx = NULL;
    goto ret;
}

STDAPI_(void)
CTL3D_Uninitialize(LPVOID lpv)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv))
        return;

    if (pctx->fRegistered)
        (*(pctx->fpUnregister))(pctx->hinstMe);

    FreeLibrary(pctx->hinst);

#ifdef  _WIN32
    LocalFree(pctx);
#else
    MAPIFreeBuffer(pctx);
#endif  
}

STDAPI_(void)
CTL3D_Subclass(LPVOID lpv, HWND hwnd, DWORD dwFlags)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv))
        return;

    (*(pctx->fpSubclassDlgEx))(hwnd, dwFlags);
}

STDAPI_(void)
CTL3D_AutoSubclass(LPVOID lpv, HINSTANCE hinst, BOOL FAR * lpfAuto)
{
    LPCTX3D pctx;

    *lpfAuto = FALSE;
    if (!(pctx = (LPCTX3D) lpv) || !pctx->fpIsAutoSubclass)
        return;

    if (*lpfAuto = !pctx->fpIsAutoSubclass())
        pctx->fpAutoSubclass (hinst);

    return;
}

STDAPI_(BOOL)
CTL3D_IsAutoSubclass(LPVOID lpv)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv) || !pctx->fpIsAutoSubclass)
        return FALSE;

    return pctx->fpIsAutoSubclass();
}

STDAPI_(void)
CTL3D_CeaseAutoSubclass(LPVOID lpv, BOOL fAuto)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv) || !fAuto)
        return;

    pctx->fpUnAutoSubclass ();
    return;
}

STDAPI_(BOOL)
CTL3D_ColorChange(LPVOID lpv)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv))
        return FALSE;

    return pctx->fpColorChange();
}

STDAPI_(BOOL)
CTL3D_SubclassCtl(LPVOID lpv, HWND hwnd)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv))
        return FALSE;

    return pctx->fpSubclassCtl(hwnd);
}

STDAPI_(WORD)
CTL3D_GetVer(LPVOID lpv)
{
    LPCTX3D pctx;

    if (!(pctx = (LPCTX3D) lpv))
        return 0;

    return pctx->fpGetVer();
}
