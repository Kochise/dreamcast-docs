/*************************************************************************
* NOTE: For some reason, which ever face of the box I decide to draw first 
* does not have transparency when it is enabled.  I have no idea
* why and I can not fix it.  
*************************************************************************/

#include <kos.h>
#include <plx/dr.h>
#include <plx/list.h>
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
    printf("X-Button: Toggle filtering \n");
    printf("Y-Button: Toggle blending\n");
    printf("A-Button: Move the cube into the distance \n");
    printf("B-Button: Move the cube closer \n");
    
    printf("UP-Dir: Decrease x rotation speed \n");
    printf("DOWN-Dir: Increase x rotation speed \n");
    printf("LEFT-Dir: Decrease y rotation speed \n");
    printf("RIGHT-Dir: Increase y rotation speed \n");
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
    int xp = 0;    // False (True or False: Pressed X button last) Toggles Filtering
    int yp = 0;    // False (True or False: Pressed Y button last) Toggles Transparency
    int blend = 0; // False (True or False: Blending)
    
    /* Rotation and depth into screen */
    float xrot = 0;   // x rotation 
    float yrot = 0;   // y rotation 
    float xspeed = 0; // x rotation speed
    float yspeed = 0; // y rotation speed
    float z = -5.0f;  // depth into the screen.
    
    int filter = 0; // Start with no filtering
    uint32 color = plx_pack_color(0.5f, 1.0f, 1.0f, 1.0f); // plx_pack_color(a, r, g, b) a = 0.5 meaning it is see through
    plx_texture_t *textures[2];  /* Array of pointers to plx_texture(Holds two textures) */
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
	
	printControls();

    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	/* Load the textures */
	textures[0] = plx_txr_load("/rd/glass.png", 0, PVR_TXRLOAD_16BPP);  
	textures[1] = plx_txr_load("/rd/glass.png", 0, PVR_TXRLOAD_16BPP);  

	plx_cxt_init();                   // Initialize the plx context system
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	/* Set the filtering for each texture */
	plx_txr_setfilter(textures[0], PLX_FILTER_NONE);
	plx_txr_setfilter(textures[1], PLX_FILTER_BILINEAR);
	
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
        if (state->buttons & CONT_X && !xp) {
            xp = 1;           
            filter += 1;     // Toggle Filter 
            if (filter > 1)
                filter = 0;
        } 
        if (!(state->buttons & CONT_X)) {
            xp = 0;
        }
        if (state->buttons & CONT_Y && !yp) {
            yp = 1;
            blend = !blend;  // Toggle Blending
        } 
        if (!(state->buttons & CONT_Y)) {
            yp = 0;
        }
        if (state->buttons & CONT_A) {
            z -= 0.02f;      // move the cube into the distance.
        } 
        if (state->buttons & CONT_B) {
            z += 0.02f;      // move the cube closer.
        } 
        if (state->buttons & CONT_DPAD_UP) {
            xspeed -= 0.01f; // decrease x rotation speed 
        } 
        if (state->buttons & CONT_DPAD_DOWN) {
            xspeed += 0.01f; // increase x rotation speed   
        }   
        if (state->buttons & CONT_DPAD_LEFT) {
            yspeed -= 0.01f; // decrease y rotation speed
        } 
        if (state->buttons & CONT_DPAD_RIGHT) {
            yspeed += 0.01f; // increase y rotation speed  
        }         
      
		pvr_wait_ready();
	    pvr_scene_begin();
		
		// Texture 'textures[filter]' will be used with the context system.  Depends on which filter is selected.    
        plx_cxt_texture(textures[filter]); 
		
		if(blend) {
          plx_list_begin(PVR_LIST_TR_POLY);
          plx_cxt_culling(PVR_CULLING_NONE); // No culling
          plx_cxt_blending(PLX_BLEND_SRCALPHA, PLX_BLEND_INVSRCALPHA);
          plx_cxt_send(PVR_LIST_TR_POLY);   
        }
        else {
          plx_list_begin(PVR_LIST_OP_POLY);
          plx_cxt_culling(PVR_CULLING_CCW); // Enable Counter-clockwise culling
          plx_cxt_blending(PLX_BLEND_ONE, PLX_BLEND_ZERO);
          plx_cxt_send(PVR_LIST_OP_POLY);
        }  
  
        // DRAW THE BOX	
        plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, z);        // Move Z units into/outof the screen
	    plx_mat3d_rotate(xrot, 1.0f, 0.0f, 0.0f);  // Rotate the BOX angle 'xrot' on the X axis   
	    plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f);  // Rotate the BOX angle 'yrot' on the Y axis
	    
  	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
      
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	    plx_mat3d_apply_all();    
	    
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
		
		// Right Face of Box 
		plx_vert_ifpm3(PLX_VERT, 1, -1, 1, color, 0, 1);     // Bottom Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, 1, 1, color, 0, 0);      // Top Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, -1, -1, color, 1, 1);    // Bottom Right Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, -1, color, 1, 0); // Top Right Of The Quad (Right)
		
		// Left Face of Box 
		plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 1);   // Bottom Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 0);    // Top Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 1, 1);    // Bottom Right Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT_EOS, -1, 1, 1, color, 1, 0); // Top Right Of The Quad (Left)
	    
		pvr_scene_finish();
		
		xrot += xspeed;   // Increase box's X Axis Rotation	
        yrot += yspeed;	  // Increase box's Y Axis Rotation
    }
    // Clean UP!!!
    plx_txr_destroy(textures[0]);
    plx_txr_destroy(textures[1]);

	return 0;
}

