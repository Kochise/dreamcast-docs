
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   sockcli.h
//
//  PURPOSE:  Declare globals and prototypes for sockcli.c
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wsipx.h>
#include "commdef.h"

BOOL fVerbose;
BOOL fRandom;
DWORD dwIterations;
DWORD dwTransferSize;
IN_ADDR RemoteIpAddress;

CLIENT_IO_BUFFER SendBuffer;
CHAR ReceiveBuffer[CLIENT_OUTBOUND_BUFFER_MAX];

VOID
WINAPI
ShowUsage (
             VOID
);

VOID
WINAPI
ParseSwitch (
               CHAR chSwitch,
               int *pArgc,
               char **pArgv[]
);

VOID
WINAPI
CompleteBenchmark (
                     VOID
);
