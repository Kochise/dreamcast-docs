/* KallistiOS ##version##

   sfxmgr.h
   (c)2000 Dan Potter

   $Id: sfxmgr.h,v 1.1 2003/02/27 03:46:30 bardtx Exp $
   
*/

#ifndef __SFXMGR_H
#define __SFXMGR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

int sfx_load(const char *fn);
void sfx_play(int idx, int vol, int pan);
void sfx_unload_all();

__END_DECLS

#endif	/* __SFXMGR_H */

