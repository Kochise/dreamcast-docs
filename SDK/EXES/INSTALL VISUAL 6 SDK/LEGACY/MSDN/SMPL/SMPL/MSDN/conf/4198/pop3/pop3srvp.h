//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1993.
//
//  File:       pop3svrp.h
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//  History:    12-12-94   RichardW   Created
//
//----------------------------------------------------------------------------

#include <windows.h>
#include <winsock.h>

//
// C-Runtimes
//

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


#include "debug.h"

//#define SECURE_BUILD

#include "pop3.h"
#include "pop3ctx.h"
#include "popfile.h"
#include "pop3evnt.h"

#include "protos.h"
#include "globals.h"

#define APPLICATION_NAME    TEXT("POP3Srv")

