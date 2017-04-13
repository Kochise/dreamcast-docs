/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    LibMain.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/

#ifndef _LIBMAIN_H_
#define _LIBMAIN_H_

//+------------------------------------------------------------------------
//
//  Globals in DLL
//
//-------------------------------------------------------------------------

extern HINSTANCE g_hInst;           // Instance of dll
extern CRITICAL_SECTION g_csMem;    // for MemAlloc

//
// Functions to manipulate object count variable g_ulObjCount.  This variable
// is used in the implementation of DllCanUnloadNow.
// NOTE: Please leave the externs within the functions so that it is not
// visible outside the dll project.
//

inline void
INC_OBJECT_COUNT(void)
{
    extern ULONG g_ulObjCount;
    g_ulObjCount++;
}

inline void
DEC_OBJECT_COUNT(void)
{
    extern ULONG g_ulObjCount;
    ADsAssert(g_ulObjCount > 0);
    g_ulObjCount--;
}

inline ULONG
GET_OBJECT_COUNT(void)
{
    extern ULONG g_ulObjCount;
    return g_ulObjCount;
}

#endif // #ifndef _LIBMAIN_H_
