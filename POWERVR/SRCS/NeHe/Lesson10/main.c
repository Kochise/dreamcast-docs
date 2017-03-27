

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
    
    int x, y;
    float xrot = 0;	/* X Rotation */
    float yrot = 0;	/* Y Rotation */
    float zrot = 0;	/* Z Rotation */
    float points[45][45][3];    // The Array For The Points On The Grid Of Our "Wave"
    int wiggle_count = 0;		// Counter Used To Control How Fast Flag Waves
    float hold;					// Temporarily Holds A Floating Point Value
    
    uint32 color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f);  // Pure white color.  Used for images to keep original color
    plx_texture_t *a_texture;  // Storage for 1 texture
    
    float float_x, float_y, float_xb, float_yb;       // loop counters.
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;

    printControls();

    /* Sets the background color to blue */
	pvr_set_bg_color(0.0f, 0.0f, 1.0f);
	
	/* Load the texture */
	a_texture = plx_txr_load("/rd/tim.png", 0, PVR_TXRLOAD_16BPP);
	
	plx_cxt_init();                  // Initialize the plx context system
	plx_cxt_texture(a_texture);      // Texture 'a_texture' will be used with the context system 
    plx_cxt_culling(PLX_CULL_NONE);  // No culling
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )	{
	    for(float_y = 0.0f; float_y < 9.0f; float_y += 0.2f)		{
	        points[ (int) (float_x*5) ][ (int) (float_y*5) ][0] = float_x - 4.4f;
	        points[ (int) (float_x*5) ][ (int) (float_y*5) ][1] = float_y - 4.4f;
	        points[ (int) (float_x*5) ][ (int) (float_y*5) ][2] = (float) (fsin( ( (float_x*5*8)/360 ) * 3.14159 * 2));
	    }
    }
	
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
		plx_cxt_send(PVR_LIST_OP_POLY);     // Submit the Header for PVR_LIST_OP_POLY 
		
        // DRAW THE BOX	
        plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, -12.0f);  // Move 12 units into the screen
	    plx_mat3d_rotate(xrot, 1.0f, 0.0f, 0.0f); // Rotate the Wavy texture angle 'xrot' on the X axis  
	    plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f); // Rotate the Wavy texture angle 'yrot' on the Y axis  
	    plx_mat3d_rotate(zrot, 0.0f, 0.0f, 1.0f); // Rotate the Wavy texture angle 'zrot' on the Z axis  
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
	    
        // Draw each section of the image
    	for (x = 0; x < 44; x++) {
	        for (y = 0; y < 44; y++) {
	            float_x  = (float) (x)/44;
	            float_y  = (float) (y)/44;
	            float_xb = (float) (x+1)/44;
	            float_yb = (float) (y+1)/44;
             
                plx_vert_ifpm3(PLX_VERT, points[x][y+1][0], points[x][y+1][1], points[x][y+1][2], color, float_x, float_yb);         
                plx_vert_ifpm3(PLX_VERT, points[x][y][0], points[x][y][1], points[x][y][2], color, float_x, float_y);                
                plx_vert_ifpm3(PLX_VERT, points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2], color, float_xb, float_yb);  
                plx_vert_ifpm3(PLX_VERT_EOS, points[x+1][y][0], points[x+1][y][1], points[x+1][y][2], color, float_xb, float_y);     
	        }
        }

		pvr_scene_finish();
        
        
        if (wiggle_count == 2) {            // Used To Slow Down The Wave (Every 2nd Frame Only)
	        for( y = 0; y < 45; y++ )		// Loop Through The Y Plane
		    {
			    hold = points[0][y][2];		// Store Current Value One Left Side Of Wave
			    for( x = 0; x < 44; x++)	// Loop Through The X Plane
			    {
				    // Current Wave Value Equals Value To The Right
				    points[x][y][2] = points[x+1][y][2];
			    }
			    points[44][y][2] = hold;	// Last Value Becomes The Far Left Stored Value
		    }
		    wiggle_count = 0;				// Set Counter Back To Zero
    	}
	    wiggle_count++;						// Increase The Counter

        xrot += 0.3f;  // Increase the Wavy Texture's angle(x-axis) rotation
        yrot += 0.2f;  // Increase the Wavy Texture's angle(y-axis) rotation
        zrot += 0.4f;  // Increase the Wavy Texture's angle(z-axis) rotation
    }
    // Clean up!!!
    plx_txr_destroy(a_texture);
    
	return 0;
}

