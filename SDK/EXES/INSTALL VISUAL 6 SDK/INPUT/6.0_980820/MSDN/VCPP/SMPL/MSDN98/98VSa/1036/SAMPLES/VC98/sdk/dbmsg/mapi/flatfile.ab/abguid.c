/**********************************************************************
 *
 *  ABGUID.C
 *
 *  Defines GUIDs for use in the Sample Address Book
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 **********************************************************************/


#define USES_IID_IUnknown
#define USES_IID_IStream

#define USES_IID_IMAPITableData
#define USES_IID_IMAPIPropData
#define USES_IID_IMAPITable
#define USES_IID_IMAPIControl
#define USES_IID_IABProvider
#define USES_IID_IABLogon
#define USES_IID_IMailUser
#define USES_IID_IMAPIContainer
#define USES_IID_IABContainer
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIStatus

#ifdef _WIN32                   /* Must include WINDOWS.H on Win32 */
#ifndef _WINDOWS_
#define INC_OLE2                /* Get the OLE2 stuff */
#define INC_RPC
#define _INC_OLE
#include <windows.h>
#include <ole2.h>
#endif
#endif

#ifdef WIN16
#include <compobj.h>
#endif

#define INITGUID
#include <initguid.h>

DEFINE_OLEGUID(IID_IUnknown, 0x00000000L, 0, 0);
DEFINE_OLEGUID(IID_IStream,  0x0000000cL, 0, 0);

#include "mapiguid.h"
