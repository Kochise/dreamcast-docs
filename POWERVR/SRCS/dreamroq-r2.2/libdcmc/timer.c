/*
**
** This file is a part of Dreamcast Media Center
** (C) Josh PH3NOM Pearson 2011
**
*/

#include <stdio.h>
#include <time.h>
#include <arch/timer.h>
#include <kos/thread.h>

#include "dc_timer.h"

/* Get current hardware timing using arch/timer.h */
int dc_get_time()
{
    uint32 s, ms;
	uint64 msec;

	timer_ms_gettime(&s, &ms);
	msec = (((uint64)s) * ((uint64)1000)) + ((uint64)ms);

	return (int)msec;
}

/* Regulate the Video Frame Rate */  
void frame_delay( float AVI_video_rate, float AVI_delay, int frameCounter )
{    
        float AVI_real_time =  frameCounter / AVI_video_rate;
        float CPU_real_time= ( ( (float)dc_get_time()- AVI_delay ) / 1000.0f );
        //printf("AVI_real_time: %f, CPU_real_time %f\n", AVI_real_time, CPU_real_time );          
        while ( CPU_real_time < AVI_real_time ) {
              CPU_real_time= ( ( (float)dc_get_time()- AVI_delay ) / 1000.0f );
              thd_pass();
        }
}
