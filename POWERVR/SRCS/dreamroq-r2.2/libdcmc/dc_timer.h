/*
**
** This File is a part of Dreamcast Media Center
** (C) Josh "PH3NOM" Pearson 2011
**
*/
		
/* 'Public' Function Protocols */

#ifndef DCTIMER_H
#define DCTIMER_H

/* Returns hardware time in miliseconds */
int dc_get_time();   

/* Regulate the Video Frame Rate */  
void frame_delay( float AVI_video_rate, float AVI_delay, int frameCounter );

#endif
