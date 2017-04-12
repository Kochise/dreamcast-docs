/***
* fp8.c - Set default FP precision to 53 bits (8-byte double)
*
*       Copyright (c) 1993-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*
*******************************************************************************/
#include <float.h>

void  _setdefaultprecision(void);

/*
 * Routine to set default FP precision to 53 bits.
 */

void _setdefaultprecision()
{
        _controlfp(_PC_53, _MCW_PC);
}

