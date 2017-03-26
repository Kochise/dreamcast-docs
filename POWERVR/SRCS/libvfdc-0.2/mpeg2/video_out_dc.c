/****************************************************************************/
/*!
\par Project:  Video for DC
\file          video_out_dc.c
\brief		   Dream Cast mpeg2 32 bits video renderer 
\author        La Cible (la.cible@free.fr)
\date          Created on 24/04/2003 
*/
/****************************************************************************/

#include <kos.h>
#include "config.h"

#include <stdlib.h>
#include <inttypes.h>

#include "video_out.h"
#include "convert.h"
static int g_width;
static int g_height;
static char vid_set=0;



static void dc_draw_frame (vo_instance_t * instance,
			     uint8_t * const * buf, void * id)
{
  memcpy(vram_l,buf[0],g_width*g_height*4);
}

void dc_close(vo_instance_t * instance)
{
  vid_set=0;
}


static vo_instance_t * internal_open (int setup (vo_instance_t *, int, int,
						 vo_setup_result_t *))
{
    vo_instance_t * instance;

    instance = (vo_instance_t *) malloc (sizeof (vo_instance_t));
    if (instance == NULL)
	return NULL;

    instance->setup = setup;
    instance->setup_fbuf = NULL;
    instance->set_fbuf = NULL;
    instance->start_fbuf = NULL;
    instance->draw = dc_draw_frame;
    instance->discard = NULL;
    instance->close = dc_close;

    return instance;
}




static int ntsc_dc_setup (vo_instance_t * instance, int width, int height,
			    vo_setup_result_t * result)
{
    result->convert = convert_rgb32; 

	if(!vid_set)
	{
		vid_set=1;
		g_width = width;
		g_height = height;
		if(width==320 && height==240) 
			vid_set_mode(DM_320x240, PM_RGB888);
		else
		{
			printf("[Video For DreamCast]\nError resolution not supported ( %dx%d )\n",width,height);
			return 1;
		}
	}

    return 0;
}

static int pal_dc_setup (vo_instance_t * instance, int width, int height,
						  vo_setup_result_t * result)
{
    result->convert = convert_rgb32; 
	if(!vid_set)
	{
		vid_set=1;
		g_width = width;
		g_height = height;
		if(width==256 && height==256) 
			vid_set_mode(DM_256x256_PAL_IL, PM_RGB888);
		else
		{
			printf("[Video For DreamCast]\nError resolution not supported\n");
			return 1;
		}
	}
	
    return 0;
}

vo_instance_t * ntsc_dc_open (void)
{
    return internal_open (ntsc_dc_setup);
}

vo_instance_t * pal_dc_open (void)
{
    return internal_open (pal_dc_setup);
}

