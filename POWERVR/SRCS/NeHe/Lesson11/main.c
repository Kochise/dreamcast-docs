

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
    
    printf("UP-Dir: Rotate the crates upward \n");
    printf("DOWN-Dir: Rotate the crates downward \n");
    printf("LEFT-Dir: Rotate the crates to the (Dark Top: Left)/(Light Top: Right) \n");
    printf("RIGHT-Dir: Rotate the crates to the (Dark Top: Right)/(Light Top: Left) \n");
    printf("/****************************/\n\n");
}

plx_texture_t *a_texture;     // storage for 1 texture;

float xrot;        // x rotation
float yrot;        // y rotation
int xloop;         // loop for x axis.
int yloop;         // loop for y axis.

// Colors for boxes.
static float boxcol[5][4]=
{
    {1.0, 1.0f, 0.0f, 0.0f}, {1.0, 1.0f, 0.5f, 0.0f}, {1.0, 1.0f, 1.0f, 0.0f}, {1.0, 0.0f, 1.0f, 0.0f}, {1.0, 0.0f, 1.0f, 1.0f}
};

// Colors for tops of boxes.
static float topcol[5][4]=
{
    {1.0, 0.5f, 0.0f, 0.0f}, {1.0, 0.5f, 0.25f, 0.0f}, {1.0, 0.5f, 0.5f, 0.0f}, {1.0, 0.0f, 0.5f, 0.0f}, {1.0, 0.0f, 0.5f, 0.5f}
};

pvr_init_params_t params = {
	/* Enable opaque and translucent polygons with size 16 */
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	
	/* Vertex buffer size 512K */
	512*1024
};

int main(int argc, char **argv) {
    
    /* Controller Stuff */
    maple_device_t * dev;
    cont_state_t * state;
    
    /* Vertex stuff(direct rendering) */
    plx_dr_state_t dr_state;
  
    uint32 color = 0;

	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;

    printControls();

    /* Sets the background color to blue */
	pvr_set_bg_color(0.0f, 0.0f, 1.0f);
	
	/* Load the textures */
	a_texture = plx_txr_load("/rd/cube.png", 0, PVR_TXRLOAD_16BPP); 

	plx_cxt_init();                 // Initialize the plx context system
	plx_cxt_texture(a_texture);     // Texture 'a_texture' will be used with the context system
    plx_cxt_culling(PLX_CULL_NONE); // No Culling
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	while(1) {
        
        // Check for the user pressing START
		dev = maple_enum_dev(0, 0);
		if(dev == NULL) {
            printf("Error: Could not find controller in first port.\n");
            break;
        }
	    state = (cont_state_t *)maple_dev_status(dev);
	    if (state->buttons & CONT_START) {
		    break;           // exit the program
        }        
        if (state->buttons & CONT_DPAD_UP) {
            xrot -= 1.5f;    // Rotate the crates upward in the negative direction (away from you)
        } 
        if (state->buttons & CONT_DPAD_DOWN) {
            xrot += 1.5f;    // Rotate the crates downward in the positive direction (toward you)  
        }   
        if (state->buttons & CONT_DPAD_LEFT) {
            yrot -= 1.5f;    // Rotate the crates to the left (depends on the top of the crate)
        } 
        if (state->buttons & CONT_DPAD_RIGHT) {
            yrot += 1.5f;    // Rotate the crates to the right	(depends on the top of the crate)
        }         
                 
		pvr_wait_ready();
		pvr_scene_begin();	
	    
        pvr_list_begin(PVR_LIST_OP_POLY);
	    plx_cxt_send(PVR_LIST_OP_POLY);    // Submit the Header for PVR_LIST_OP_POLY
	    
	    plx_dr_init(&dr_state);     // Initialize a state variable for Direct Rendering
		
		for (yloop = 1; yloop < 6; yloop++) { // 5 rows of cubes.
	        for (xloop = 0; xloop < yloop; xloop++) {
	            plx_mat3d_identity(); 
                plx_mat3d_translate(1.4f+(((float)xloop)*2.8f)-(((float)yloop)*1.4f),((6.0f-((float)yloop))*2.4f)-7.0f,-20.0f);   
	            plx_mat3d_rotate(45.0f - (2.0f*yloop)+xrot, 1.0f, 0.0f, 0.0f);       
	            plx_mat3d_rotate(45.0f + yrot, 0.0f, 1.0f, 0.0f);      
                
                /* Clear internal to an identity matrix */
                plx_mat_identity();
	    
	            /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	            plx_mat3d_apply_all();

	            color = plx_pack_color(boxcol[yloop-1][0], boxcol[yloop-1][1], boxcol[yloop-1][2], boxcol[yloop-1][3]);
	            
	            // Bottom Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, -1.0f, -1.0f, color, 0.0f, 1.0f);     // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, -1.0f, 1.0f, color, 0.0f, 0.0f);      // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, -1.0f, -1.0f, color, 1.0f, 1.0f);    // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, -1.0f, -1.0f, 1.0f, color, 1.0f, 0.0f); // Top Right Of The Texture and Quad 
	    	    
	            // Front Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, 1.0f, color, 0.0f, 1.0f);      // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, -1.0f, 1.0f, color, 0.0f, 0.0f);     // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, 1.0f, 1.0f, color, 1.0f, 1.0f);       // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, 1.0f, -1.0f, 1.0f, color, 1.0f, 0.0f);  // Top Right Of The Texture and Quad  	    

                // Back Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, 1.0f, -1.0f, color, 0.0f, 1.0f);      // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, -1.0f, -1.0f, color, 0.0f, 0.0f);     // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, -1.0f, color, 1.0f, 1.0f);     // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, -1.0f, -1.0f, -1.0f, color, 1.0f, 0.0f);// Top Right Of The Texture and Quad   	 
              
                // Right Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, 1.0f, 1.0f, color, 0.0f, 1.0f);       // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, -1.0f, 1.0f, color, 0.0f, 0.0f);      // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, 1.0f, -1.0f, color, 1.0f, 1.0f);      // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, 1.0f, -1.0f, -1.0f, color, 1.0f, 0.0f); // Top Right Of The Texture and Quad   
    
                // Left Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, -1.0f, color, 0.0f, 1.0f);     // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, -1.0f, -1.0f, color, 0.0f, 0.0f);    // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, 1.0f, color, 1.0f, 1.0f);      // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, -1.0f, -1.0f, 1.0f, color, 1.0f, 0.0f); // Top Right Of The Texture and Quad   
    
	            color = plx_pack_color(topcol[yloop-1][0], topcol[yloop-1][1], topcol[yloop-1][2], topcol[yloop-1][3]);
	            
	            // Top Face
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, -1.0f, color, 0.0f, 1.0f);     // Bottom Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, -1.0f, 1.0f, 1.0f, color, 0.0f, 0.0f);      // Top Left Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT, 1.0f, 1.0f, -1.0f, color, 1.0f, 1.0f);      // Bottom Right Of The Texture and Quad
	            plx_vert_ifdm3(&dr_state, PLX_VERT_EOS, 1.0f, 1.0f, 1.0f, color, 1.0f, 0.0f);   // Top Right Of The Texture and Quad 
	            
            }
        }
        pvr_scene_finish();      
    }
    // Clean up!!!
    plx_txr_destroy(a_texture);
    
	return 0;
}

