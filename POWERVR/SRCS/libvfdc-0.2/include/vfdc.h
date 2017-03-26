/****************************************************************************/
/*!
\par Project:  Video For DreamCast V 0.2
\file          vfdc.h
\author        La Cible (la.cible@free.fr)
*/
/****************************************************************************/



#ifndef VIDEO_FOR_DREAMCAST_H
#define VIDEO_FOR_DREAMCAST_H

#define VF4DC_OK           0              /* player return values */
#define VF4DC_EOF         -1
#define VF4DC_ERROR       -2
#define VF4DC_NOT_OPEN    -3
#define VF4DC_BAD_RESOL   -4


#define FRAMECB_VIDEO_NEXTFRAME	 0
#define FRAMECB_VIDEO_STOP		 1

#define VMODE_NTSC	0
#define VMODE_PAL	1	

#define PLAYMODE_LOOP -1


#ifdef __cplusplus
   extern "C" {
#endif

/**
 * Fli Player 
 */
int play_fli(char *filename,int _mode, int (*callback)(),unsigned int _flag);

/**
 * mpg m1v m2v pss player
 */
int play_mpeg(char *filename,int _mode, int (*callback)(),unsigned int _flag);

#ifdef __cplusplus
   }
#endif

#endif          /* ifndef VIDEO_FOR_DREAMCAST_H */


