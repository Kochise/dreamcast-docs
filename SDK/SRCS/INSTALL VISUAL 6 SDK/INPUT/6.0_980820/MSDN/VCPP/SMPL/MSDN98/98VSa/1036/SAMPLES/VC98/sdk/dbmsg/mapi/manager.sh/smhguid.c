/*
 *  S H M G U I D . C
 *
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#define USES_IID_IUnknown
#define USES_IID_ISpoolerHook
#define USES_IID_IMAPISession
#define USES_IID_IMAPITableData
#define USES_IID_IRichEditOleCallback
#define USES_IID_IMessage

#define STRICT

#ifdef _WIN32                   /* Must include WINDOWS.H on Win32 */
#ifndef _WINDOWS_
#define INC_OLE2                /* Get the OLE2 stuff */
#define INC_RPC                 /* harmless on Windows NT; Windows 95 needs it */
#define _INC_OLE                /* Windows 95 will include OLE1 without this */
#include <windows.h>
#include <ole2.h>
#endif
#endif

#ifdef WIN16
#include <compobj.h>
#endif

#define INITGUID
#include <initguid.h>
#include "mapiguid.h"

DEFINE_OLEGUID (IID_IRichEditOleCallback, 0x00020D03, 0, 0);


