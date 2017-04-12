/* KallistiOS 1.1.6

   sndmp3.h
   (c)2000 Dan Potter

   $Id: sndmp3.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
   
*/

#ifndef __SNDMP3_H
#define __SNDMP3_H

#include <sys/cdefs.h>
__BEGIN_DECLS

int sndmp3_init(const char *fn, int loop);

/* Initialize the MP3 driver; takes an input filename and starts the
   decoding process. */
int sndmp3_start(const char *fn, int loop);

/* Shut everything down */
void sndmp3_shutdown();

__END_DECLS

#endif	/* __SNDMP3_H */

