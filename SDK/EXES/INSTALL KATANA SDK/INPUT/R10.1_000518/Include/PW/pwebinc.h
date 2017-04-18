/*
 * $Id: pwebinc.h,v 1.1 1999/09/27 18:18:56 taborm Exp $
 *
 * Unpublished Copyright (1999) Segasoft Networks Inc.
 * All rights reserved
 *
 * Author: Michael Tabor (michael.tabor@segasoft.com)
 *
 * $Log: pwebinc.h,v $
 * Revision 1.1  1999/09/27 18:18:56  taborm
 * Initial checkin
 *
 */

#ifndef _PWEBINC_H_
#define _PWEBINC_H_

/*
 * This file wraps the PlanetWeb include files to help cut down on the complexity of dealing with them.
 */

#ifdef KGTRN_PLANET_WEB

   #include	<shinobi.h>

   /*
    * The PlanetWeb incude files use #if a lot. Unfortunately, the SHC compiler does not handle #if when
    * the referenced symbol is not defined. For this reason we need to explicitely #define as 0 all of
    * the symbols used by PlanetWeb for detecting the target platform.
    */
   #ifdef __KATANA__
   #undef __KATANA__       /* Definition must be numerical for #if to work for SHC. */
   #define __KATANA__ 1

   #define __BIG_ENDIAN__      0
   #define __LITTLE_ENDIAN__   1
   #define INLINES_BROKEN
   #endif

   #define __LUXSONOR__ 0
   #define __SATURN__ 0
   #define __PSX__ 0
   #define __PUMA__ 0
   #define __VSURF__ 0
   #define __MMATICS__ 0
   #define __TOSHIBA__ 0
   #define __8x8__ 0
   #define __WIN32__ 0

   #include <sys/types.h>
   #include <sys/types2.h>

   #ifndef __GNUC__	/* Standard GNU errno.h conflicts with PlanetWeb definitions. */
   #include <errno.h>
   #endif

   #include <errno2.h>

   /*
    PlanetWeb does not define ssize_t because it thinks that GNU defines it.
    Unfortunately for this theory, the PlanetWeb sys/types.h file masks the
    gnu sys/types.h file so the GNU definitions are never used.

    This is why it is defined here. (It must be defined before including pweb_net.h)
    */
   #ifdef __GNUC__
   typedef long ssize_t;
   #endif

   #include <pweb_net.h>
   #include <arpa/inet.h>

   /*
    PlanetWeb defines timeval in both socket.h and select.h. They include a protection macro in select.h
    but unfortunately don't define it in socket.h so we have to define it ourselves here.
    */
   #define PW_TIMEVAL_DEFINED

   #include <sys/select.h>
   #include <fcntl2.h>

   #ifndef errno
   #define errno _errno
   #endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

   /* PlanetWeb defines missing from standard header files. */
   void ConnectToNet (void);
   void DisconnectFromNet (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#endif