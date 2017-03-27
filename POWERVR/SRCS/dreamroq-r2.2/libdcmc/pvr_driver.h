/* 
** 
** PVR Video Driver
** (C) Josh "PH3NOM" Pearson 2011-2012 
**
*/

#ifndef PVR_DRIVER_H
#define PVR_DRIVER_H

#include <dc/pvr.h>
#include <dc/video.h>
//#include <cache.h>

#define PVR_TEX_WIDTH  1024.0f
#define PVR_TEX_HEIGHT 1024.0f
#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 480
#define DISPLAY_AR 4/3

#include <kos/mutex.h>
mutex_t * pvr_mutex;
#define PVR_create_mutex()  { pvr_mutex = mutex_create(); }
#define PVR_lock_mutex()    { mutex_lock( pvr_mutex );    }
#define PVR_unlock_mutex()  { mutex_unlock( pvr_mutex );  }
#define PVR_destroy_mutex() { mutex_destroy( pvr_mutex ); }

struct pvr_frame
{
       int            tex_width;
       int            tex_height;
       int            vram_width;
       int            vram_height;
       int            texFmt;
       int            texColor;
       pvr_ptr_t *    vram_tex;
       pvr_vertex_t   vert[4];
       pvr_poly_hdr_t poly;
       pvr_poly_cxt_t cxt;
};

struct pvr_frame_vertex
{
       int   top;
       int   bottom;
       int   left;
       int   right;
       int   width;
       int   height;
       float height_ratio;
       float width_ratio;
};

/* PVR Driver - Public Function Protocols */
/* Driver functions require using above structures pvr_frame/pvr_frame_vertex */


/* Allocate VRAM for the texture. Must be done before any PVR driver function */
int pvr_malloc( struct pvr_frame *pvr, int width, int height );

/* Free allocated VRAM for the texture. Should be done when finished. */
int pvr_free( struct pvr_frame *pvr );


/* Automatically set polygon co-ordinates for fullscreen, before compiling */
void pvr_resize_resolution( struct pvr_frame pvr, struct pvr_frame_vertex *display );

/* Manually set polygon co-ordinates, before compiling the polygon */
int  pvr_set_resolution( struct pvr_frame pvr, int x, int y, 
                        int dispWidth, int dispHeight, struct pvr_frame_vertex *display  );                       


/* Compile the polygon.  Only needs to be done once, before display */                       
int pvr_compile_poly( struct pvr_frame_vertex display, struct pvr_frame *pvr, int mode, int fmt, float z );


/* Load Texture Data from RAM to VRAM, Pixel by Pixel */
/* To use this function, first PVR_create_mutex() must be called. */
/* When finished, PVR_destroy_mutex() should be called */
/* This function is intended for use with pvr_draw_frame() */
void pvr_pixel_load( unsigned char *src, struct pvr_frame *pvr );

/* Load Texture Data from RAM to VRAM, 32bytes at a time */
/* This function is intended for use with pvr_draw_frame() */
void pvr_txr_load_sq( unsigned char *src, struct pvr_frame *pvr );

/* Load Texture Data from RAM to VRAM, using fast DMA */
/* This function is intended for use with pvr_draw_frame_dma() */
void pvr_dma_load( unsigned char *src, struct pvr_frame *pvr );

/* Draw a single Opaqe Polygon */
void pvr_draw_frame( struct pvr_frame *pvr_frame );

/* Draw a single Opaqe Polygon with DMA enabled */
void pvr_draw_frame_dma( struct pvr_frame *pvr_frame );

#endif
