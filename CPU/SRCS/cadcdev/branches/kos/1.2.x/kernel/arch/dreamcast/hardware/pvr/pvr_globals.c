/* KallistiOS ##version##

   pvr_globals.c
   (C)2002 Dan Potter

 */

#include <dc/pvr.h>
#include "pvr_internal.h"

/*

  Global variables internal to the PVR module go here.
 
*/

CVSID("$Id: pvr_globals.c,v 1.2 2002/01/28 04:09:52 bardtx Exp $");

/* Our global state -- by default it's initialized to zeros, so the
   valid flag will be zero. */
volatile pvr_state_t pvr_state;


