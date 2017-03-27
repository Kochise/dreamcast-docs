

#include <kos.h>
#include <plx/prim.h>
#include <plx/matrix.h>
#include <plx/context.h>

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

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
    
    int rquad = 0;
    int rtri = 0;
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();	

    /* Sets the background color to black */
	pvr_set_bg_color(0.0f,0.0f,0.0f);
	
	plx_cxt_init();                 // Initialize the plx context system
	plx_cxt_texture(NULL);          // No texture will be used
    plx_cxt_culling(PLX_CULL_NONE); // No culling
	
	// GET SOME 3D GOING!!
	/* Init matrices */
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
		
		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_OP_POLY);
     	
		// Submit the context
		plx_cxt_send(PVR_LIST_OP_POLY);  // Submit the Header for PVR_LIST_OP_POLY
		
		// DRAW THE PYRAMID
	    plx_mat3d_identity();
	    plx_mat3d_translate(-1.5f, 0.0f, -6.0f);  // Move 1.5f units to the left and 6 units into the screen
	    plx_mat3d_rotate(rtri, 0.0f, 1.0f, 0.0f); // Rotate the pyramid angle 'rtri' on the Y axis
  	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	    plx_mat3d_apply_all();
	    
	    // Front Face of Pyramid
	    plx_vert_inpm3(PLX_VERT, 0, 1, 0, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));       // Red: Top Of Triangle (Front)
	    plx_vert_inpm3(PLX_VERT, -1, -1, 1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));     // Green: Left Of Triangle (Front)
	    plx_vert_inpm3(PLX_VERT_EOS, 1, -1, 1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));  // Blue: Right Of Triangle (Front)
	    
	    // Right Face of Pyramid
	    plx_vert_inpm3(PLX_VERT, 0, 1, 0, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));       // Red: Top Of Triangle (Right)
	    plx_vert_inpm3(PLX_VERT, 1, -1, 1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));      // Blue: Left Of Triangle (Right)
	    plx_vert_inpm3(PLX_VERT_EOS, 1, -1, -1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f)); // Green: Right Of Triangle (Right)
	    
	    // Back Face of Pyramid
	    plx_vert_inpm3(PLX_VERT, 0, 1, 0, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));       // Red: Top Of Triangle (Back)
	    plx_vert_inpm3(PLX_VERT, 1, -1, -1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));     // Green: Left Of Triangle (Back)
	    plx_vert_inpm3(PLX_VERT_EOS, -1, -1, -1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));// Blue: Right Of Triangle (Back)
	    
	    // Left Face of Pyramid
	    plx_vert_inpm3(PLX_VERT, 0, 1, 0, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));       // Red: Top Of Triangle (Left)
	    plx_vert_inpm3(PLX_VERT, -1, -1, -1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));    // Blue: Left Of Triangle (Left)
	    plx_vert_inpm3(PLX_VERT_EOS, -1, -1, 1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f)); // Green: Right Of Triangle (Left)
	    
        // DRAW THE BOX	
        plx_mat3d_identity();
	    plx_mat3d_translate(1.5f, 0.0f, -6.0f);    // Move 1.5f units to the right and 6 units into the screen
	    plx_mat3d_rotate(rquad, 1.0f, 0.0f, 0.0f); // Rotate the box angle 'rquad' on the X axis 
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	    plx_mat3d_apply_all();
		
		// Top Face of Box (GREEN)
		plx_vert_inpm3(PLX_VERT, -1, 1, 1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));     // Bottom Left Of The Quad (Top)
		plx_vert_inpm3(PLX_VERT, -1, 1, -1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));    // Top Left Of The Quad (Top)
		plx_vert_inpm3(PLX_VERT, 1, 1, 1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));      // Bottom Right Of The Quad (Top)
		plx_vert_inpm3(PLX_VERT_EOS, 1, 1, -1, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f)); // Top Right Of The Quad (Top)
	    
		// Bottom Face of Box (ORANGE)
		plx_vert_inpm3(PLX_VERT, -1, -1, -1, plx_pack_color(1.0f, 1.0f, 0.5f, 0.0f));   // Bottom Left Of The Quad (Bottom)
		plx_vert_inpm3(PLX_VERT, -1, -1, 1, plx_pack_color(1.0f, 1.0f, 0.5f, 0.0f));    // Top Left Of The Quad (Bottom)
		plx_vert_inpm3(PLX_VERT, 1, -1, -1, plx_pack_color(1.0f, 1.0f, 0.5f, 0.0f));    // Bottom Right Of The Quad (Bottom)
		plx_vert_inpm3(PLX_VERT_EOS, 1, -1, 1, plx_pack_color(1.0f, 1.0f, 0.5f, 0.0f)); // Top Right Of The Quad (Bottom)	    
		
		// Front Face of Box (RED)
		plx_vert_inpm3(PLX_VERT, -1, -1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));    // Bottom Left Of The Quad (Front)
	    plx_vert_inpm3(PLX_VERT, -1, 1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));     // Top Left Of The Quad (Front)
	    plx_vert_inpm3(PLX_VERT, 1, -1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));     // Bottom Right Of The Quad (Front)
	    plx_vert_inpm3(PLX_VERT_EOS, 1, 1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));  // Top Right Of The Quad (Front)
		
		// Back Face of Box (YELLOW)
		plx_vert_inpm3(PLX_VERT, -1, 1, -1, plx_pack_color(1.0f, 1.0f, 1.0f, 0.0f));    // Bottom Left Of The Quad (Back)
	    plx_vert_inpm3(PLX_VERT, -1, -1, -1, plx_pack_color(1.0f, 1.0f, 1.0f, 0.0f));   // Top Left Of The Quad (Back)
	    plx_vert_inpm3(PLX_VERT, 1, 1, -1, plx_pack_color(1.0f, 1.0f, 1.0f, 0.0f));     // Bottom Right Of The Quad (Back)
		plx_vert_inpm3(PLX_VERT_EOS, 1, -1, -1, plx_pack_color(1.0f, 1.0f, 1.0f, 0.0f));// Top Right Of The Quad (Back)
		
		// Left Face of Box (BLUE)
		plx_vert_inpm3(PLX_VERT, -1, -1, -1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));   // Bottom Left Of The Quad (Left)
	    plx_vert_inpm3(PLX_VERT, -1, 1, -1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));    // Top Left Of The Quad (Left)
	    plx_vert_inpm3(PLX_VERT, -1, -1, 1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f));    // Bottom Right Of The Quad (Left)
	    plx_vert_inpm3(PLX_VERT_EOS, -1, 1, 1, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f)); // Top Right Of The Quad (Left)
	    
		// Right Face of Box (VIOLET)
		plx_vert_inpm3(PLX_VERT, 1, -1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 1.0f));     // Bottom Left Of The Quad (Right)
	    plx_vert_inpm3(PLX_VERT, 1, 1, 1, plx_pack_color(1.0f, 1.0f, 0.0f, 1.0f));      // Top Left Of The Quad (Right)
	    plx_vert_inpm3(PLX_VERT, 1, -1, -1, plx_pack_color(1.0f, 1.0f, 0.0f, 1.0f));    // Bottom Right Of The Quad (Right)
	    plx_vert_inpm3(PLX_VERT_EOS, 1, 1, -1, plx_pack_color(1.0f, 1.0f, 0.0f, 1.0f)); // Top Right Of The Quad (Right)

		pvr_scene_finish();
		
		rquad -= 2.0f;  // Increases the box's rotation angle
		rtri += 2.0f;   // Increases the pyramid's rotation angle
    }

	return 0;
}

