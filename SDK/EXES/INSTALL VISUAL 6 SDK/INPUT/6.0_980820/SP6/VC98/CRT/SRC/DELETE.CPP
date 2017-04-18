/***
*delete.cxx - defines C++ delete routine
*
*       Copyright (c) 1990-1998, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines C++ delete routine.
*
*******************************************************************************/

#ifndef _DEBUG

#include <cruntime.h>
#include <malloc.h>
#include <new.h>

void operator delete( void * p )
{
    free( p );
}

#endif  /* _DEBUG */
