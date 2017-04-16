/***
*cfinfo.c - clears C file info flag
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Clears the C file info flag.  By default, the openfile information
*       is NOT passed along to children on spawn/exec calls.  If the flag
*       is set, openfile information WILL get passed on to children on
*       spawn/exec calls.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>

int _fileinfo = 0;
