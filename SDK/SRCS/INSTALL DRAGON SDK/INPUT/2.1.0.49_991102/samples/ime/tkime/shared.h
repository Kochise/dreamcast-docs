/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    shared.h

Abstract:

    This file contains the prototype for DestroySharedResources().

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _SHARED_H
#define _SHARED_H

#include "input.h"
#include "display.h"

HFONT
CreateKanaFont(LONG lFontHeight);

void
DestroySharedResources(void);

BOOL
CreateSharedResources(void);

#endif  // _SHARED_H