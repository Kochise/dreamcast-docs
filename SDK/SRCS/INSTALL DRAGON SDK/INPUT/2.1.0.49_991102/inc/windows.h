/*++

Copyright (c) 1995-1998  Microsoft Corporation

Module Name: windows.h

Purpose: Master include file for Windows applications.

--*/

#ifndef __WINDOWS__
#define __WINDOWS__

#ifdef SHx
#pragma warning(disable:4710)
#endif

#include <windef.h>
#include <types.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <winreg.h>
#include <shellapi.h>
#ifndef WINCEMACRO
#include <ole2.h>
#endif

#include <imm.h>

#include <tchar.h>
#include <excpt.h>

#ifdef _WIN32_WCE_EMULATION
#include <wceemul.h>
#endif

#endif /* __WINDOWS__ */

