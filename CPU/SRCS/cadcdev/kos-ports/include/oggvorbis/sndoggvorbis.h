/* KallistiOS ##version##

   sndoggvorbis.h
   (c)2001 Thorsten Titze

   An Ogg/Vorbis player library using sndstream and the official Xiphophorus
   libogg and libvorbis libraries.

   $Id: sndoggvorbis.h,v 1.2 2003/04/24 02:53:30 bardtx Exp $
   
*/

#ifndef __SNDOGGVORBIS_H
#define __SNDOGGVORBIS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <stdio.h>

int sndoggvorbis_init();
int sndoggvorbis_start(const char *filename,int loop);
int sndoggvorbis_start_fd(FILE *f, int loop);
void sndoggvorbis_stop();
void sndoggvorbis_shutdown();

int sndoggvorbis_isplaying();

void sndoggvorbis_volume(int vol);

void sndoggvorbis_mainloop();
void sndoggvorbis_wait_start();

void sndoggvorbis_setbitrateinterval(int interval);
long sndoggvorbis_getbitrate();
long sndoggvorbis_getposition();

char *sndoggvorbis_getcommentbyname(const char *commentfield);
char *sndoggvorbis_getartist();
char *sndoggvorbis_gettitle();
char *sndoggvorbis_getgenre();

/* Enable/disable queued waiting */
void sndoggvorbis_queue_enable();
void sndoggvorbis_queue_disable();

/* Wait for the song to be queued */
void sndoggvorbis_queue_wait();

/* Queue the song to start if it's in QUEUED */
void sndoggvorbis_queue_go();

__END_DECLS

#endif	/* __SNDOGGVORBIS_H */

