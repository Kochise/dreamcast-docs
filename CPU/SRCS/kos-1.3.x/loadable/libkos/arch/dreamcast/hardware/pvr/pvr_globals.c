/* KallistiOS ##version##

   pvr_globals.c
   (C)2002 Dan Potter

 */

#include <dc/pvr.h>
#include "pvr_internal.h"

/*

  Global variables internal to the PVR module go here.
 
*/

CVSID("$Id: pvr_globals.c,v 1.1 2003/06/19 04:20:59 bardtx Exp $");

/* Our global state -- by default it's initialized to zeros, so the
   valid flag will be zero. */
volatile pvr_state_t pvr_state;


