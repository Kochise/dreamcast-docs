

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
		
		// DRAW THE TRIANGLE
	    plx_mat3d_identity();
	    plx_mat3d_translate(-1.5f, 0.0f, -6.0f);  // Move 1.5f units to the left and 6 units into the screen
  	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	
    	/* "Apply" a matrix: multiply a matrix onto the "internal" one */
    	plx_mat3d_apply(PLX_MAT_SCREENVIEW);  /** Internal screen view matrix */
	    plx_mat3d_apply(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	    plx_mat3d_apply(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	    
	    // Could also use the following line instead of the above three lines
	    //plx_mat3d_apply_all();
	    
	    plx_vert_inpm3(PLX_VERT, 0, 1, 0, plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f));       // Top (Color = Red) 
	    plx_vert_inpm3(PLX_VERT,  -1,  -1, 0, plx_pack_color(1.0f, 0.0f, 1.0f, 0.0f));   // Bottom Left (Color = Green)
	    plx_vert_inpm3(PLX_VERT_EOS,  1, -1, 0, plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f)); // Bottom Right (Color = Blue)

        // DRAW THE QUAD	
        plx_mat3d_identity();
	    plx_mat3d_translate(1.5f, 0.0f, -6.0f); // Move 1.5f units to the right and 6 units into the screen
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Apply" a matrix: multiply a matrix onto the "internal" one */
    	plx_mat3d_apply(PLX_MAT_SCREENVIEW);  /** Internal screen view matrix */
	    plx_mat3d_apply(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	    plx_mat3d_apply(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	    
	    // Could also use the following line instead of the above three lines
	    //plx_mat3d_apply_all();
		
		plx_vert_inpm3(PLX_VERT, -1,  1, 0, plx_pack_color(1.0f, 0.5f, 0.5f, 1.0f));       // Bottom Left (Color = Bluish)
	    plx_vert_inpm3(PLX_VERT, -1, -1, 0, plx_pack_color(1.0f, 0.5f, 0.5f, 1.0f));       // Top Left (Color = Bluish)
	    plx_vert_inpm3(PLX_VERT,  1,  1, 0, plx_pack_color(1.0f, 0.5f, 0.5f, 1.0f));       // Bottom Right (Color = Bluish)
	    plx_vert_inpm3(PLX_VERT_EOS,  1, -1, 0, plx_pack_color(1.0f, 0.5f, 0.5f, 1.0f));   // Top Right (Color = Bluish)
		
		pvr_scene_finish();
            
    }

	return 0;
}
