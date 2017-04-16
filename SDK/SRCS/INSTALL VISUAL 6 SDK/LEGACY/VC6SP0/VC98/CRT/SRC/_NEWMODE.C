/***
*_newmode.c - set new() handler mode to not handle malloc failures
*
*       Copyright (c) 1994-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Sets the global flag which controls whether the new() handler
*       is called on malloc failures.  The default behavior in Visual
*       C++ v2.0 and later is not to, that malloc failures return NULL
*       without calling the new handler.  This object is linked in unless
*       the special object NEWMODE.OBJ is manually linked.
*
*       This source file is the complement of LINKOPTS/NEWMODE.C.
*
*******************************************************************************/



#include <internal.h>

/* enable new handler calls upon malloc failures */

int _newmode = 0;       /* Malloc New Handler MODE */


