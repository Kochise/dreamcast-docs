

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
    printf("X-Button: Increase x rotation speed \n");
    printf("Y-Button: Decrease x rotation speed \n");
    printf("A-Button: Increase y rotation speed \n");
    printf("B-Button: Decrease y rotation speed \n");
    
    printf("UP-Dir: Move the cube into the distance \n");
    printf("DOWN-Dir: Move the cube closer \n");
    printf("LEFT-Dir: NONE \n");
    printf("RIGHT-Dir: NONE \n");
    printf("/****************************/\n\n");
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
    
    /* Controller Stuff */
    maple_device_t * dev;
    cont_state_t * state;
    
    float xrot = 0;   // x rotation 
    float yrot = 0;   // y rotation 
    float xspeed = 0; // x rotation speed
    float yspeed = 0; // y rotation speed
    float z = -5.0f;  // depth into the screen.
    
    uint32 color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f);  /* or (0xffffffff) Should equal this if you want images to have their original color */
    
    plx_texture_t *a_texture;  /* Pointer to plx_texture */
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();	

    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	/* Load the texture */
	a_texture = plx_txr_load("/rd/crate.png", 0, PVR_TXRLOAD_16BPP);
	
	plx_cxt_init();                // Initialize the plx context system
	plx_cxt_texture(a_texture);    // Texture 'a_texture' will be used with the context system
    plx_cxt_culling(PLX_CULL_CCW); // Enable Counter Clockwise Culling
	
	// GET SOME 3D GOING!!
	/* Init matrices */
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
        if (state->buttons & CONT_X) {
            xspeed += 0.01f; // increase x rotation speed
        } 
        if (state->buttons & CONT_Y) {
            xspeed -= 0.01f; // decrease x rotation speed
        } 
        if (state->buttons & CONT_A) {
            yspeed += 0.01f; // increase y rotation speed
        } 
        if (state->buttons & CONT_B) {
            yspeed -= 0.01f; // decrease y rotation speed
        } 
        if (state->buttons & CONT_DPAD_UP) {
            z -= 0.02f;      // move the cube into the distance. 
        } 
        if (state->buttons & CONT_DPAD_DOWN) {
            z += 0.02f;      // move the cube closer.
        } 

		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_OP_POLY);
     	
		// Submit the context
		plx_cxt_send(PVR_LIST_OP_POLY);  // Submit the Header for PVR_LIST_OP_POLY
		
        // DRAW THE BOX	
        plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, z);       // Move Z units into/outof the screen
	    plx_mat3d_rotate(xrot, 1.0f, 0.0f, 0.0f); // Rotate the BOX angle 'xrot' on the X axis   
	    plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f); // Rotate the BOX angle 'yrot' on the Y axis
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	    plx_mat3d_apply_all();
		
		// Top Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, 1, 1, color, 0, 1);     // Bottom Left Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 0);    // Top Left Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT, 1, 1, 1, color, 1, 1);      // Bottom Right Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, -1, color, 1, 0); // Top Right Of The Quad (Top)
	    
		// Bottom Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 1);   // Bottom Left Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 0, 0);    // Top Left Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT, 1, -1, -1, color, 1, 1);    // Bottom Right Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, -1, 1, color, 1, 0); // Top Right Of The Quad (Bottom)	    
		
		// Front Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 0, 1);    // Bottom Left Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT, -1, 1, 1, color, 0, 0);     // Top Left Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT, 1, -1, 1, color, 1, 1);     // Bottom Right Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, 1, color, 1, 0);  // Top Right Of The Quad (Front)
		
		// Back Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 1);    // Bottom Left Of The Quad (Back)
	    plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 0);   // Top Left Of The Quad (Back)
	    plx_vert_ifpm3(PLX_VERT, 1, 1, -1, color, 1, 1);     // Bottom Right Of The Quad (Back)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, -1, -1, color, 1, 0);// Top Right Of The Quad (Back)
		
		// Left Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 1);   // Bottom Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 0);    // Top Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 1, 1);    // Bottom Right Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT_EOS, -1, 1, 1, color, 1, 0); // Top Right Of The Quad (Left)
	    
		// Right Face of Box 
		plx_vert_ifpm3(PLX_VERT, 1, -1, 1, color, 0, 1);     // Bottom Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, 1, 1, color, 0, 0);      // Top Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, -1, -1, color, 1, 1);    // Bottom Right Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, -1, color, 1, 0); // Top Right Of The Quad (Right)

		pvr_scene_finish();
		
		xrot += xspeed;   // Increase the box's X Axis Rotation	
        yrot += yspeed;	  // Increase the box's Y Axis Rotation
    }
    // Clean up!!!
    plx_txr_destroy(a_texture);

	return 0;
}

