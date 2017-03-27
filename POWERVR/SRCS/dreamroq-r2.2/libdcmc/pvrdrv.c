/* 
** 
** PVR Video Driver
** (C) Josh "PH3NOM" Pearson 2011-2012 
**
*/

#include <stdio.h>

#include "pvr_driver.h"

/* Free PVR Ram */
int pvr_free( struct pvr_frame *pvr )
{
    if(pvr->vram_tex)
    {
        pvr_mem_free(pvr->vram_tex);
        return 1;
    }
    
    return 0;
}

/* Find and allocate the smallest possible PVR VRAM texture area */
int pvr_malloc( struct pvr_frame *pvr, int width, int height )
{   
     /* Set the texture context width and height */
     pvr->tex_width  = width;
     pvr->tex_height = height;

	 /* Check if Texture resolution exceeds PVR maximum */
	 if ( pvr->tex_width > PVR_TEX_WIDTH || pvr->tex_height > PVR_TEX_HEIGHT ) {
          printf("ERROR: IMAGE Exceeds PVR maximum resolution!\n");
          return 0;
     }
     
     /* Find the smallest PVR Polygon size to fit the Texture, from 8x8 to 1024x1024 */
	 pvr->vram_width = pvr->vram_height = 0x08;
	 while( pvr->vram_width<pvr->tex_width )                         
            pvr->vram_width<<=1;
     while( pvr->vram_height<pvr->tex_height )
            pvr->vram_height<<=1;
     
     /* Allocate PVR VRAM for the current Texture */
     if(pvr->vram_tex) pvr_mem_free(pvr->vram_tex);    
	 pvr->vram_tex = pvr_mem_malloc(pvr->vram_width*pvr->vram_height*2);

     return 1;
}

/* Transfer texture data from SH4 RAM to PVR VRAM using DMA */
void pvr_dma_load( unsigned char *src, struct pvr_frame *pvr )
{
    dcache_flush_range(src, 16384);                    /* Flush the SH4 Cache */
    pvr_wait_ready();                  /* Wait for PVR to be in a ready state */
    while (!pvr_dma_ready());          /* Wait for PVR DMA to finish transfer */
    
    pvr_dma_transfer( src, pvr->vram_tex, pvr->vram_width*pvr->tex_height*2,
                      PVR_DMA_VRAM64, 1, NULL, 0 );
}

/* Copy a frame from RAM to VRAM, pixel by pixel. Mutex protected. */
void pvr_pixel_load( unsigned char *src, struct pvr_frame *pvr )
{
	 int x, y;
	 uint16 *texture;
	 uint16 *image;
     
     /* Copy the image data from RAM to VRAM, byte by byte */
	 image = (uint16 *)src;
	 texture = (uint16 *)pvr->vram_tex;
	 PVR_lock_mutex();
     for (y=0; y<pvr->tex_height; y++)
	 {
	     for (x=0; x<pvr->tex_width; x++)
	       texture[x] = image[x];
	     texture += pvr->vram_width; image += pvr->tex_width;  
	 }
     PVR_unlock_mutex();
     
     /* free the resources */    
     sq_clr(image, sizeof(image));  
     sq_clr(texture, sizeof(texture));       
}

/* Copy a frame from RAM to VRAM, 32 bytes at a time using Store-Queues */
void pvr_txr_load_sq( unsigned char *src, struct pvr_frame *pvr )
{          
    int i, n;
    unsigned int *d, *s;

    /* Make sure our video width is compatible with SQ transfers */
    uint32 count = pvr->tex_width * 2; 
	if (count % 4)
		count = (count & 0xfffffffc) + 4;

    d = (unsigned int *)(void *)
		(0xe0000000 | (((unsigned long)pvr->vram_tex) & 0x03ffffe0));
    s = (unsigned int *)src;
   
	/* Set store queue memory area as desired */
	QACR0 = ((((unsigned int)pvr->vram_tex)>>26)<<2)&0x1c;
	QACR1 = ((((unsigned int)pvr->vram_tex)>>26)<<2)&0x1c;

    for(i=0;i<pvr->tex_height;i++){                        
	  d = (unsigned int *)(void *)
		(0xe0000000 | (((unsigned long)pvr->vram_tex+(i*(pvr->vram_width*2))) & 0x03ffffe0));
	  
	  n = count>>5;
	  
	  while(n--) {
		asm("pref @%0" : : "r" (s + 8)); // prefetch 32 bytes for next loop 
		d[0] = *(s++);
		d[1] = *(s++);
		d[2] = *(s++);
		d[3] = *(s++);
		d[4] = *(s++);
		d[5] = *(s++);
		d[6] = *(s++);
		d[7] = *(s++);
		asm("pref @%0" : : "r" (d));
		d += 8;
	  }
	 
	}
	/* Wait for both store queues to complete */
	d = (unsigned int *)0xe0000000;
	d[0] = d[8] = 0;    
}

/* Calculate output resolution */
void pvr_resize_resolution( struct pvr_frame pvr, struct pvr_frame_vertex *display )
{     
     /* Initialize texture width and height */
     display->width   = pvr.tex_width;
     display->height  = pvr.tex_height;
     
     /* Calculate display resolution */
     if ( pvr.tex_height  < pvr.tex_width * DISPLAY_AR ) { 
          display->top    = ( DISPLAY_HEIGHT - (( pvr.tex_height * DISPLAY_WIDTH ) / pvr.tex_width)  ) / 2;
          display->bottom = DISPLAY_HEIGHT - display->top;
          display->left   = 0; display->right = DISPLAY_WIDTH;
     }
     else { 
          display->top   = 0; display->bottom = DISPLAY_HEIGHT;        
          display->left  = ( DISPLAY_WIDTH - (( pvr.tex_width * DISPLAY_HEIGHT ) / pvr.tex_height) ) / 2;
          display->right = DISPLAY_WIDTH - display->left;      
     }              
     
     /* Calculate Top and Bottom u/v co-oridnates */ 
     display->width_ratio  = pvr.tex_width / (float)pvr.vram_width;
     display->height_ratio = pvr.tex_height / (float)pvr.vram_height;

}

/* Calculate output resolution */
int pvr_set_resolution( struct pvr_frame pvr, int x, int y, 
                        int dispWidth, int dispHeight, struct pvr_frame_vertex *display  )
{       
     /* Fill the pvr_frame_vertex structure*/
     display->top    = y;
     display->bottom = y+dispHeight;
     display->left   = x;
     display->right  = x+dispWidth; 
     display->width  = pvr.tex_width;
     display->height = pvr.tex_height;
     display->width_ratio  = pvr.tex_width / (float)pvr.vram_width;
     display->height_ratio = pvr.tex_height / (float)pvr.vram_height;
     
     return 1;
}

/* Cache our PVR verticies */
int pvr_compile_poly( struct pvr_frame_vertex display, struct pvr_frame *pvr, int mode, int fmt, float z )
{
    /* Submit the vertecies */
    pvr->vert[0].argb  = pvr->vert[1].argb  = pvr->vert[2].argb  = pvr->vert[3].argb  = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pvr->vert[0].oargb = pvr->vert[1].oargb = pvr->vert[2].oargb = pvr->vert[3].oargb = 0; 
    pvr->vert[0].z     = pvr->vert[1].z     = pvr->vert[2].z     = pvr->vert[3].z     = z;    
    pvr->vert[0].flags = pvr->vert[1].flags = pvr->vert[2].flags = PVR_CMD_VERTEX;
    pvr->vert[3].flags = PVR_CMD_VERTEX_EOL; 

	pvr->vert[0].x = display.left;
    pvr->vert[0].y = display.bottom;
	pvr->vert[0].u = 0.0f;
    pvr->vert[0].v = display.height_ratio;
 
	pvr->vert[1].x = display.left;
    pvr->vert[1].y = display.top; 
	pvr->vert[1].u = 0.0f; 
    pvr->vert[1].v = 0.0f;
    
    pvr->vert[2].x = display.right;
    pvr->vert[2].y = display.bottom;
    pvr->vert[2].u = display.width_ratio;
    pvr->vert[2].v = display.height_ratio;
	
    pvr->vert[3].x = display.right;
    pvr->vert[3].y = display.top;
    pvr->vert[3].u = display.width_ratio;
    pvr->vert[3].v = 0.0f;

    /* Compile the polygon */
	pvr_poly_cxt_txr(&pvr->cxt, mode, fmt,
		                   pvr->vram_width, pvr->vram_height, pvr->vram_tex, PVR_FILTER_BILINEAR);
	pvr_poly_compile(&pvr->poly, &pvr->cxt);

    return 1;
}

#define pvr_submit_poly( pvr  ) { \
	pvr_prim(&pvr->poly, sizeof(pvr->poly)); \
	pvr_prim(&pvr->vert[0], sizeof(pvr->vert[0])); \
	pvr_prim(&pvr->vert[1], sizeof(pvr->vert[1])); \
	pvr_prim(&pvr->vert[2], sizeof(pvr->vert[2])); \
	pvr_prim(&pvr->vert[3], sizeof(pvr->vert[3])); }

/* Render a single Opaque frame using the PVR */
void pvr_draw_frame( struct pvr_frame *pvr_frame )
{
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_OP_POLY);
    pvr_submit_poly(pvr_frame); 
    pvr_list_finish();       
    pvr_scene_finish(); 
}

/* Render a single Opaque frame using the PVR, DMA enabled */
void pvr_draw_frame_dma( struct pvr_frame *pvr_frame )
{
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_OP_POLY);
    pvr_submit_poly(pvr_frame); 
    pvr_list_finish();       
    pvr_scene_finish(); 
}
