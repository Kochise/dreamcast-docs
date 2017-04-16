/***
*heapdump.c -  Output the heap data bases
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Display the heap data bases.
*
*       NOTE:  This module is NOT released with the C libs.  It is for
*       debugging purposes only.
*
*******************************************************************************/

#ifndef WINHEAP

#ifdef _WIN32


#include <cruntime.h>
#include <heap.h>
#include <malloc.h>
#include <mtdll.h>
#include <stdio.h>



#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#include <cruntime.h>
#include <heap.h>
#include <malloc.h>
#include <stdio.h>
#include <macos\memory.h>               // Mac OS interface header
#include <macos\errors.h>
#include <macos\types.h>
#include <macos\traps.h>

extern Handle hHeapRegions;
extern int _heap_region_table_cur;



#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */

#endif  /* WINHEAP */
