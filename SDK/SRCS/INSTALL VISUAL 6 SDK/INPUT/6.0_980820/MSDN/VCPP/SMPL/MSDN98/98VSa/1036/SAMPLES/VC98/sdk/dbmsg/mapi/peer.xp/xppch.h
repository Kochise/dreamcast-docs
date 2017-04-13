/*
 -  X P P C H . H
 -
 *  Pre-Compiled Header File for Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#define _INC_OLE
#include <windows.h>
#include <windowsx.h>
#include <mapiwin.h>
#include <mapidbg.h>
#include <ole2.h>

#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapiguid.h>
#include <mapispi.h>
#include <mapiutil.h>
#include <mapival.h>
#include <imessage.h>
#include <mapiwz.h>

#ifndef MAC
#include <memory.h>
#endif
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

#include "xpdialog.h"
#include "xpbase.h"
#include "xpstatus.h"
#include "xpqueue.h"
#include "xplogger.h"
