/*
 * INOLEDLL.H
 * Inside OLE Utilities DLL
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _INOLEDLL_H_
#define _INOLEDLL_H_

#include <inole.h>
#include <bttncur.h>
#include <gizmobar.h>
#include <stastrip.h>

#ifndef WIN32
#include <shellapi.h>
#ifndef RC_INVOKED
#include <dos.h>
#endif
#endif

//Private definitions
#include "bttncuri.h"
#include "gizmoint.h"
#include "statint.h"

BOOL Initialize(HINSTANCE);
void DrawHandle(HDC, int, int, UINT, BOOL, BOOL);
BOOL GetFileTimes(LPTSTR, FILETIME *);

HRESULT ConvertStringAlloc(ULONG, void **);

#endif //_INOLEDLL_H_
