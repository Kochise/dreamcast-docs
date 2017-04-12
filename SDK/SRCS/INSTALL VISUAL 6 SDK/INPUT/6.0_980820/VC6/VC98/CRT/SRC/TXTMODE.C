/***
*txtmode.c - set global text mode flag
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Sets the global file mode to text.  This is the default.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>

int _fmode = 0;                 /* set text mode */
