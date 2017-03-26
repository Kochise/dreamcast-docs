/* KallistiOS ##version##

   sndserver.h
   (c)2000 Dan Potter

   $Id: sndserver.h,v 1.1 2003/02/27 03:46:30 bardtx Exp $
   
*/

#ifndef __SNDSERVER_H
#define __SNDSERVER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <mp3/sndmp3.h>
#include <mp3/sfxmgr.h>

/* Starts the MP3 server thread */
int mp3_init();

/* Starts a song playing */
int mp3_start(const char *fn, int loop);

/* Stops the playing song */
int mp3_stop();

/* Shuts down the MP3 server thread */
int mp3_quit();

__END_DECLS

#endif	/* __SNDSERVER_H */

