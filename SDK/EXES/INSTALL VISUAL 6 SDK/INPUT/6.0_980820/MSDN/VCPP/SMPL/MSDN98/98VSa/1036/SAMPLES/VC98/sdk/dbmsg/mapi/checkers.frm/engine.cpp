/* --------------------------------------------------------------------------

Basic Forms example of a custom sendable form.  It is an EXE server
rather than a DLL.  It implements the minimum form interface required
to launch and send a form.

Copyright (C) 1995 Microsoft Corporation

-------------------------------------------------------------------------- */

/* facilitate compilation accross modules without losing any optimizations
   of the engine */

#define WINDOWS

#include <windows.h>  // user interface stuff follows
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <malloc.h>
#include <memory.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <search.h>
#include <stdarg.h>

#ifdef _WIN32
#include <winver.h>
#else
#include <ver.h>
#endif

extern struct   rCheckConfigRec rConfig;
extern class    CMoveList CMoves;
extern struct   rGameStateRec rGameState;


extern unsigned int _charmax;


//---[ Local header user interface dependencies ]-----------------------------------------

#include "check.h"
#include "dlg.h"
#include "wcheck.h"
#include "checkdta.h"
#include "movelist.h"
#define DEBUG_CODE
#include "dbugit.h"

/* user interface externals */
#ifdef DEBUG
ASSERTDATA
#endif

/* --------------------------------------------------------------------------
Global variables
-------------------------------------------------------------------------- */

int debug=0;              /* these variables should not be used outside the
                             scope of the checkers engine */

int computer_color = BLACK;
int depth_maximum = 5;


#ifndef DEBUG
#pragma optimize("agtw",on)
#endif

#include ".\engine\lut.cpp"
#include ".\engine\debugio.cpp"
#include ".\engine\quality.cpp"
#include ".\engine\check.cpp"
#include ".\engine\prune.cpp"
#include ".\engine\valid.cpp"
