/*
 *  WEP.C
 *
 *  WEP function for MAPI DLLs.  This function is placed in a separate
 *  segment so marking the segment as FIXED is not hard on the system.
 *
 *
 *  Copyright 1993-1995 Microsoft Corporation. All Rights Reserved.
 */ 

#if defined ( WIN16 )

#include <windows.h>
#include <mapidbg.h>

#pragma warning(disable:4100)   /* unreferenced formal parameter */

#pragma code_seg("WEP_TEXT")

/*--------------------------------------------------------------------------
 * Synopsis:    WEP
 *
 * Description: Required DLL exit function.  Does nothing.
 *
 * Parameters:  
 * Returns:
 * Effects:
 * Notes:
 * Revision:
 *-------------------------------------------------------------------------*/
int FAR PASCAL __loadds  WEP( int nParam )
{
    return TRUE;
}

#endif

