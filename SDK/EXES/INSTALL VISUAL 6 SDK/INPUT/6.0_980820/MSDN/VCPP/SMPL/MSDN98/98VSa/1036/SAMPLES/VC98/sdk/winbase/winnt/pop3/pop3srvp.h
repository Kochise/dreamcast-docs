
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       pop3svrp.h
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#include <windows.h>

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
