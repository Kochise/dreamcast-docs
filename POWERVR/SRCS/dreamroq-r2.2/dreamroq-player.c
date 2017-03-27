/*
* Dreamroq by Mike Melanson
* Updated by Josh Pearson to add audio support
*
* This is the sample Dreamcast player app, designed to be run under
* the KallistiOS operating system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dc/maple.h>
#include <dc/maple/controller.h>
#include <kos/mutex.h>
#include <kos/thread.h>

#include "dreamroqlib.h"

#include "pvr_driver.h"
#include "snddrv.h"
#include "dc_timer.h"

/* Audio Global variables */
#define PCM_BUF_SIZE 1024*1024
static unsigned char *pcm_buf = NULL;
static int pcm_size = 0;
static int audio_init = 0;
static mutex_t * pcm_mut;

/* Video Global variables */
static int graphics_initialized = 0;
static float video_delay;
static int frame=0;
static unsigned char *vidbuf;            /* Video Address */ 
static kthread_t * render_thread;        /* Video thread */
static volatile int render_thd=0;        /* Video thread status */   
static const float VIDEO_RATE = 25.0f;   /* Video FPS */

/* PVR Driver Handle */    
static struct pvr_frame        roq_vram_ptr;
static struct pvr_frame_vertex roq_vram_vertex;   

static void audio_thd()
{
    do
    {
        /* Wait for AICA Driver to request some samples */   
        while( snddrv.buf_status != SNDDRV_STATUS_NEEDBUF )
            thd_pass();   

        /* Wait for RoQ Decoder to produce enough samples */
        while( pcm_size < snddrv.pcm_needed )
        {
            if( snddrv.dec_status == SNDDEC_STATUS_DONE )
                goto done;   
            thd_pass();   
        }

        /* Copy the Requested PCM Samples to the AICA Driver */         
        mutex_lock( pcm_mut );
        memcpy( snddrv.pcm_buffer, pcm_buf, snddrv.pcm_needed );
       
        /* Shift the Remaining PCM Samples Back */
        pcm_size -= snddrv.pcm_needed;
        memmove( pcm_buf, pcm_buf+snddrv.pcm_needed, pcm_size );
        mutex_unlock( pcm_mut );
         
        /* Let the AICA Driver know the PCM samples are ready */
        snddrv.buf_status = SNDDRV_STATUS_HAVEBUF;
                   
    } while( snddrv.dec_status == SNDDEC_STATUS_STREAMING );     
    done:
    snddrv.dec_status = SNDDEC_STATUS_NULL;
}

static void video_thd()
{ 
    render_thd=1;  /* Signal Thread is active */

	/* Load the Texture from RAM to VRAM using DMA */
    pvr_dma_load( (unsigned char *)vidbuf, &roq_vram_ptr);
	
    /* Delay the frame to match Frame Rate */
    frame_delay( VIDEO_RATE, video_delay, ++frame );

    /* Draw the frame using the PVR */
    pvr_draw_frame_dma(&roq_vram_ptr); 

    render_thd=0;   /* Signal Thread is finished */

}

static int render_cb(unsigned short *buf, int width, int height, int stride,
    int texture_height)
{
     /* on first call, initialize textures and drawing coordinates */
    if (!graphics_initialized)
    {                    
        /* Allocate VRAM for current texture */
        pvr_malloc( &roq_vram_ptr, width, height );                             

        /* Compile the PVR Driver Handle */
        pvr_resize_resolution( roq_vram_ptr, &roq_vram_vertex );
        pvr_compile_poly(roq_vram_vertex, &roq_vram_ptr,
           PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED, 10.0f);
        
        /* Get current hardware timing */    
        video_delay = (float)dc_get_time();

        graphics_initialized = 1;
    }
       
    /* Wait for last frame to finish render */
    while( render_thd )
       thd_pass();

    /* Current decoded frame */
    vidbuf = buf;   
       
    /* Create a thread to render the current frame */   
    render_thread = thd_create( video_thd, NULL );
    
    return ROQ_SUCCESS;    
}

static int audio_cb( unsigned char *buf, int size, int channels)
{
    if(!audio_init)
    {
        /* allocate PCM buffer */
        pcm_buf = malloc(PCM_BUF_SIZE);
        if( pcm_buf == NULL )
            return ROQ_NO_MEMORY;
       
        /* Start AICA Driver */
        snddrv_start( 22050, channels );
        snddrv.dec_status = SNDDEC_STATUS_STREAMING;
       
        /* Create a thread to stream the samples to the AICA */
        thd_create( audio_thd, NULL );
       
        /* Create a mutex to handle the double-threaded buffer */
        pcm_mut = mutex_create();
       
        audio_init=1;
    }

    /* Copy the decoded PCM samples to our local PCM buffer */
    mutex_lock( pcm_mut );         
    memcpy(  pcm_buf+pcm_size, buf, size);
    pcm_size += size;
    mutex_unlock( pcm_mut );
       
    return ROQ_SUCCESS;   
}

static int quit_cb()
{
    cont_cond_t cont;

    /* check controller state */
    if (cont_get_cond(maple_first_controller(), &cont))
    {
        /* controller read error */
        return 1;
    }
    cont.buttons = ~cont.buttons;
    return (cont.buttons & CONT_START);
}

int main()
{
    int status=0;

    vid_set_mode(DM_640x480, PM_RGB565);
    pvr_init_defaults();
    pvr_dma_init();
    
    printf("dreamroq_play(C) Multimedia Mike Melanson & Josh PH3NOM Pearson 2011\n"); 

    /* To disable a callback, simply replace the function name by 0 */
    status = dreamroq_play("/cd/sample.roq", 0, render_cb, audio_cb, quit_cb);

    printf("dreamroq_play() status = %d\n", status); 
   
    if(audio_init)
    {
      snddrv.dec_status = SNDDEC_STATUS_DONE;  /* Singal audio thread to stop */
      while( snddrv.dec_status != SNDDEC_STATUS_NULL )
         thd_pass();     
      free( pcm_buf );
      pcm_buf = NULL;
      pcm_size = 0; 
      mutex_destroy(pcm_mut);                  /* Destroy the PCM mutex */
      snddrv_exit();                           /* Exit the AICA Driver */ 
    }

    if(graphics_initialized)
    {
        pvr_free( &roq_vram_ptr );             /* Free the PVR memory */
    }
    
    pvr_dma_shutdown();   
       
    return 0;
}
