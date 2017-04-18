/*
 * OLEGLOBL.C
 *
 * Declarations of OLE-specific global variables.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#ifdef MAKEOLESERVER

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"


XOLEGLOBALS      stOLE;
LPXOLEGLOBALS    pOLE=&stOLE;


#endif //MAKEOLESERVER
