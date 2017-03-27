

#include <kos.h>
#include <plx/prim.h>
#include <plx/matrix.h>
#include <plx/context.h>
#include <plx/texture.h>

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);

void printControls() {
    printf("\n/**********Controls**********/\n");
    printf("START-Button: Exits program\n");
    printf("X-Button: NONE \n");
    printf("Y-Button: NONE \n");
    printf("A-Button: NONE \n");
    printf("B-Button: NONE \n");
    
    printf("UP-Dir: NONE \n");
    printf("DOWN-Dir: NONE \n");
    printf("LEFT-Dir: NONE \n");
    printf("RIGHT-Dir: NONE \n");
    printf("/****************************/\n\n");
}

plx_texture_t *textures[2]; /* Holds two textures */

/* Has all the characters that are available to draw from the font.png image */
const char fontstr[] = " ! #$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_` abcdefghijklmnopqrstuvwxyz{|}~ ÇüéâäàåçêëïîìÄÂÉæÆôöòûùÿÖÜø£Ø×ƒ";

/* Draws a specified area of a texture, to act like a tileset */
/* Taken and modified from a post of JS Lemming: http://dcemulation.org/phpBB/viewtopic.php?p=736314#p736314 */
void DrawTile(plx_texture_t *Image, int x, int y, int tile_width, int tile_height, uint32 color, int index) {

    pvr_poly_cxt_t cxt; 
    pvr_poly_hdr_t hdr; 
    pvr_vertex_t vert; 

    float inc_x = ((float)(tile_width) / (float)(Image->w));
    float inc_y = ((float)(tile_height) / (float)(Image->h));
    
    float index_x;
    float index_y = 1.0f;
    int tiles_wide = (Image->w / tile_width);
    
    //Convert the index into a coordinate index_x and index_y
    while(index >= tiles_wide * index_y)
    {
       index_y++;
    }
    index_y--;
    index_x = index - (tiles_wide*index_y);
    
    pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB1555, Image->w, Image->h, Image->ptr, PVR_FILTER_NONE);
    pvr_poly_compile(&hdr,&cxt); 
    pvr_prim(&hdr,sizeof(hdr)); 
    
    vert.argb = color;    
    vert.oargb = 0; 
    
    vert.flags = PVR_CMD_VERTEX; 
    vert.x = x; 
    vert.y = y;
    vert.z = 1; //z 
    vert.u = index_x*inc_x; 
    vert.v = index_y*inc_y; 
    pvr_prim(&vert,sizeof(vert)); 
    
    vert.x = x + tile_width;
    vert.y = y;
    vert.u = index_x*inc_x+inc_x; 
    pvr_prim(&vert,sizeof(vert)); 
    
    vert.x = x;
    vert.y = y + tile_height;
    vert.u = index_x*inc_x; 
    vert.v = index_y*inc_y+inc_y; 
    pvr_prim(&vert,sizeof(vert)); 
    
    vert.x = x + tile_width;
    vert.y = y + tile_height;
    vert.u = index_x*inc_x+inc_x; 
    vert.flags = PVR_CMD_VERTEX_EOL; 
    pvr_prim(&vert, sizeof(vert));   
}

/* Where The Printing Happens  */
/* Taken and modified from Cool Herders (font.c). Full source can be found here: http://www.boob.co.uk/games.html */
void TextPrint( int x, int y, const char *string, uint32 color, int set) {
    
    int x_sub = x; /* Where on the screen to draw the string(X-Coordinate) */
    int y_sub = y; /* Where on the screen to draw the string(Y-Coordinate) */
    int index;     /* Used to tell the DrawTile() which area of the image to draw */
    char *ptr = NULL;

	while (*string) {
		if(set) {
			index = 128;  /* Using second set of fonts*/
		} else {
			index = 0;    /* Using first set of fonts */
		}
		
		ptr = fontstr;    /* Set pointer equal to the avaiable characters in the font */
		
		while (*ptr) {    /* While going through the available characters */ 
			if (*ptr == *string) { /* Check if any match a character in the string */
				break;    /* Found one. Leave the while loop to go draw it */
			}
			ptr++;        /* Go to the next available character */
			index++;      /* Incrementing to the next space in the image */
		}

		if (*ptr) {
            DrawTile(textures[1], x_sub, y_sub, 16.0f, 16.0f, color, index); /* Draw the character */
		}

		string++;       /* Go to the next character in the string */
		x_sub += 11.0f; /* Increase the x parameter so a string of letters can be drawn next to each */
                        /* other and not on top of each other */ 
	}
}

/**
  Like plx_vert_ifdm3, but uses plx_prim.
 */
static inline void plx_vert_ifpm3(int flags, float x, float y, float z, uint32 color, float u, float v) {
	plx_mat_tfip_3d(x, y, z);
	plx_vert_ifp(flags, x, y, z, color, u, v);
}

pvr_init_params_t params = {
	/* Enable opaque and translucent polygons with size 16 */
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	
	/* Vertex buffer size 512K */
	512*1024
};

int main(int argc, char **argv) {
    
    float	cnt1;	/* 1st Counter Used To Move Text & For Coloring */
    float	cnt2;	/* 2nd Counter Used To Move Text & For Coloring */

    /* Controller Stuff */
    maple_device_t * dev;
    cont_state_t * state;
    
    uint32 color = 0;

	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();		

    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	/* Load the textures */
	textures[0] = plx_txr_load("/rd/bumps.png", 0, PVR_TXRLOAD_16BPP);
	textures[1] = plx_txr_load("/rd/font.png", 1, PVR_TXRLOAD_16BPP);
	plx_txr_setfilter(textures[0], PLX_FILTER_BILINEAR);  // Use Bilinear filtering for the first texture
	
	plx_cxt_init();                  // Initialize the plx context system
    plx_cxt_culling(PLX_CULL_NONE);  // No Culling

	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	while(1) {
        
        /* Check key status */
		dev = maple_enum_dev(0, 0);
		if(dev == NULL) {
            printf("Error: Could not find controller in first port.\n");
            break;
        }
	    state = (cont_state_t *)maple_dev_status(dev);
	    if (state->buttons & CONT_START) {
		    break;           // exit the program
        }        
		
		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_OP_POLY);
     	
     	// Select the texture
     	plx_cxt_texture(textures[0]);
     	
		// Submit the context
		plx_cxt_send(PVR_LIST_OP_POLY);  
		
		// Draw QAUD 1
        plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, -5.0f);         // Move 5 units into the screen
	    plx_mat3d_rotate(45.0f, 0.0f, 0.0f, 1.0f);      // Rotate the quad 45 degrees on the Z-axis
	    plx_mat3d_rotate(cnt1*30.0f, 1.0f, 1.0f, 0.0f); // Rotate the quad cnt1*30.0f degress on the X&Y-Axis
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
		
		color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f);
		
		// Draw the first Quad
		plx_vert_ifpm3(PLX_VERT, -1.0f, -1.0f, 0, color, 0, 1);    
		plx_vert_ifpm3(PLX_VERT, -1.0f, 1.0f, 0, color, 0, 0);    
		plx_vert_ifpm3(PLX_VERT, 1.0f, -1.0f, 0, color, 1, 1);      
		plx_vert_ifpm3(PLX_VERT_EOS, 1.0f, 1.0f, 0, color, 1, 0); 
		
	    // Draw QAUD 2
     	plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, -5.0f);                 // Move 5 units into the screen
	    plx_mat3d_rotate(45.0f, 0.0f, 0.0f, 1.0f);              // Rotate the quad 45 degrees on the Z-axis
	    plx_mat3d_rotate((cnt1*30.0f)+90.0f, 1.0f, 1.0f, 0.0f); // Rotate the quad cnt1*30.0f+90 degress on the X&Y-Axis
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
		
		// Draw the second Quad perpendicular to the first
		plx_vert_ifpm3(PLX_VERT, -1.0f, -1.0f, 0, color, 0, 1);    
		plx_vert_ifpm3(PLX_VERT, -1.0f, 1.0f, 0, color, 0, 0);    
		plx_vert_ifpm3(PLX_VERT, 1.0f, -1.0f, 0, color, 1, 1);      
		plx_vert_ifpm3(PLX_VERT_EOS, 1.0f, 1.0f, 0, color, 1, 0); 
		
		pvr_list_finish();
		
     	pvr_list_begin(PVR_LIST_TR_POLY);
		
		// Draw the Bitmap Font
		
        /* Pulsing Colors Based On Text Position  */
	    color = plx_pack_color(1.0f, 1.0f*(float)(fcos(cnt1)), 1.0f*(float)(fsin(cnt2)), 1.0f-0.5f*(float)(fcos(cnt1+cnt2)));
	    TextPrint((int)((280+250*fcos(cnt1))), (int)(235+200*fsin(cnt2)), "Dreamcast", color, 0);		
	    
	    color = plx_pack_color(1.0f, 1.0f*(float)(fsin(cnt2)),1.0f-0.5f*(float)(fcos(cnt1+cnt2)), 1.0f*(float)(fcos(cnt1)));
	    TextPrint((int)((280+230*fcos(cnt2))), (int)(235+200*fsin(cnt1)), "Parallax", color, 1);	
	    
	    color = plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f);
	    TextPrint((int)(240+85*fcos((cnt2+cnt1)/5)), 446, "Baby Bonnie Hood", color, 0);
	    
	    color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f); 
	    TextPrint((int)(242+85*fcos((cnt2+cnt1)/5)), 446, "Baby Bonnie Hood", color, 0);  

		pvr_scene_finish();
		
		cnt1 += 0.01f;			/* Increase The First Counter  */
	    cnt2 += 0.0081f;		/* Increase The Second Counter  */
            
    }
    // Clean up!!!
    plx_txr_destroy(textures[0]);
    plx_txr_destroy(textures[1]);

	return 0;
}

