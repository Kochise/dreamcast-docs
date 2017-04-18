/*
 -  X P G U I D . C
 -
 *  Purpose:
 *      This file is used to build xpguid.obj, which contains the binary
 *      representation of several MAPI guid's.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#define USES_IID_IMAPIProp
#define USES_IID_IMessage
#define USES_IID_IMAPIStatus
#define USES_IID_IXPLogon
#define USES_IID_IXPProvider
#define USES_IID_IMAPITable
#define USES_IID_IMAPITableData
#define USES_IID_IMAPIPropData

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

DEFINE_OLEGUID(IID_IUnknown, 0x00000000L, 0, 0);
DEFINE_OLEGUID(IID_IStream, 0x0000000cL, 0, 0);
