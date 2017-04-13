/*
 * INOLE.CPP
 * Inside OLE Utilities DLL
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "inoledll.h"


/*
 * LibMain(32)
 *
 * Purpose:
 *  Entry point for the DLL, conditionally compiled.
 */

#ifdef WIN32

BOOL __stdcall LibMain32(HINSTANCE hInstance, ULONG ulReason
    , PCONTEXT pContext)
    {
    UNREFERENCED_PARAMETER(pContext);

    if (DLL_PROCESS_DETACH==ulReason)
        {
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    return Initialize(hInstance);
    }

#else

int WINAPI LibMain(HANDLE hInstance, WORD wDataSeg
    , WORD cbHeapSize, LPTSTR lpCmdLine)
    {
     //Perform global initialization.
    if (Initialize((HINSTANCE)hInstance))
        {
        if (0!=cbHeapSize)
            UnlockData(0);
        }

    return (int)hInstance;
    }

#endif



/*
 * Initialize
 *
 * Purpose:
 *  Registers the control classes contained in this library
 *  and performs other initialization.
 *
 * Parameters:
 *  hInst           HINSTANCE of the DLL that will own this class.
 *
 * Return Value:
 *  BOOL            TRUE all if successful, FALSE otherwise.
 */

BOOL Initialize(HINSTANCE hInst)
    {
    static BOOL     fInitialized=FALSE;
    WNDCLASS        wc;

    if (fInitialized)
        return TRUE;

    wc.cbClsExtra    =0;
    wc.hInstance     =hInst;
    wc.hIcon         =NULL;
    wc.hCursor       =LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground =(HBRUSH)(COLOR_BTNFACE+1);
    wc.lpszMenuName  =NULL;
    wc.style         =CS_DBLCLKS | CS_GLOBALCLASS
                      | CS_VREDRAW | CS_HREDRAW;

    wc.lpfnWndProc   =GizmoBarWndProc;
    wc.cbWndExtra    =CBEXTRAGIZMOBAR;
    wc.lpszClassName =CLASS_GIZMOBAR;

    RegisterClass(&wc);

    wc.lpfnWndProc   =StatStripWndProc;
    wc.cbWndExtra    =CBEXTRASTATSTRIP;
    wc.lpszClassName =CLASS_STATSTRIP;

    RegisterClass(&wc);

    ToolButtonInit(hInst);
    CursorsCache(hInst);

    fInitialized=TRUE;
    return TRUE;
    }
