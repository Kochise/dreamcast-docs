/*
 * STASTRIP.H
 * StatStrip Version 1.00
 *
 * Public class and definitions for the StatStrip control.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */



#ifndef _STASTRIP_H_
#define _STASTRIP_H_

#include <book1632.h>

#ifdef __cplusplus
extern "C"
    {
#endif //__cplusplus


#define CYSTATSTRIP     23
#define CLASS_STATSTRIP TEXT("StatStrip")


//External APIs.
BOOL WINAPI StatStripMessageMap(HWND, HWND, HINSTANCE, UINT, UINT
    , UINT, UINT, USHORT, USHORT, USHORT, USHORT, USHORT);
void WINAPI StatStripMenuSelect(HWND, WPARAM, LPARAM);
void WINAPI StatStripMessageDisplay(HWND, USHORT);

//Message equivalents
#define STATM_MESSAGEMAP        (WM_USER+0)
#define STATM_MENUSELECT        (WM_USER+1)
#define STATM_MESSAGEDISPLAY    (WM_USER+2)


//Structure for STATM_MESSAGEMAP
typedef struct tagSTATMESSAGEMAPINIT
    {
    HWND        hWndOwner;
    HINSTANCE   hInst;
    UINT        uIDRMap;
    UINT        idsMin;
    UINT        idsMax;
    UINT        cchMax;
    USHORT      uIDPopupMin;
    USHORT      uIDPopupMax;
    USHORT      uIDStatic;
    USHORT      uIDBlank;
    USHORT      uIDSysMenu;
    } STATMESSAGEMAPINIT, FAR *LPSTATMESSAGEMAPINIT;


#ifdef __cplusplus
    }
#endif //__cplusplus

#endif //_STASTRIP_H_
