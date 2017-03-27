

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
    printf("START-Button: Exits program \n");
    printf("X-Button: Change Fog Type \n");
    printf("Y-Button: Toggle Fog ON/OFF \n");
    printf("A-Button: Move the cube into the distance \n");
    printf("B-Button: Move the cube closer \n");
    
    printf("UP-Dir: Decrease the cube's x rotation speed \n");
    printf("DOWN-Dir: Increase the cube's x rotation speed \n");
    printf("LEFT-Dir: Decrease the cube's y rotation speed \n");
    printf("RIGHT-Dir: Increase the cube's y rotation speed \n");
    printf("/****************************/\n\n");
}

static float xrot;		/* X Rotation */
static float yrot;		/* Y Rotation */
static float xspeed;    /* X Rotation Speed */
static float yspeed;	/* Y Rotation Speed */
static float z = -5.0f;	/* Depth Into The Screen */

/* Storage For Three Types Of Fog */
int fogType = 0; /* use PLX_EXP initially */
enum fogmodes { PLX_EXP = 0, PLX_EXP2, PLX_LINEAR };
int fogMode[] = { PLX_EXP, PLX_EXP2, PLX_LINEAR };
float fogColor[4] = { 1.0, 0.5f, 0.5f, 0.5f }; /* Fog Color */
int fog = 0;

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
	int xp = 0;
	int yp = 0;
	
    uint32 color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f);
    plx_texture_t *a_texture;
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();	

    /* Sets the background color to the color of the fog (GRAY) */
	pvr_set_bg_color(0.5f, 0.5f, 0.5f);
	
    /* Set up the fog */
	pvr_fog_table_color(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);   /* Set Fog Color */
	pvr_fog_far_depth(5.0f);
	pvr_fog_table_exp(0.35f); /* Use PLX_EXP Initially */
	
	/* Load the texture */
	a_texture = plx_txr_load("/rd/crate.png", 0, PVR_TXRLOAD_16BPP);
	plx_txr_setfilter(a_texture, PLX_FILTER_BILINEAR); // Use Bilinear filtering
	
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
		if (state->buttons & CONT_A) {
			if (z >= -15.0f) z -= 0.02f; // move the cube into the distance. 
		}
		if (state->buttons & CONT_B) {
			if (z <= 0.0f) z += 0.02f; // move the cube closer.
		}
		if ((state->buttons & CONT_X) && !xp) {
			xp = 1;
 		    fogType = ( ++fogType ) % 3;  // change fog type
            switch (fogMode[fogType]) {
            case PLX_EXP:
                pvr_fog_table_exp(0.35f);
                break;
            case PLX_EXP2:
                pvr_fog_table_exp2(0.35f);
                break;
            case PLX_LINEAR:
                pvr_fog_table_linear(0.0f, 5.0f);
                break;
            }
        }
		if (!(state->buttons & CONT_X)) {
			xp = 0;
        }
		if ((state->buttons & CONT_Y) && !yp) {
			yp = 1;
			fog = !fog;     // Toggle Fog ON/OFF
		}
		if (!(state->buttons & CONT_Y)) {
			yp = 0;
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
		
		/* Switch fog off/on */
		if (fog) {
			plx_cxt_fog(PLX_FOG_TABLE);
		} else {
			plx_cxt_fog(PLX_FOG_NONE);
		}
		
		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_TR_POLY);
     	
		// Submit the context
		plx_cxt_send(PVR_LIST_TR_POLY);  // Submit the Header for PVR_LIST_TR_POLY
		
        // DRAW THE CUBE	
        plx_mat3d_identity();
	    plx_mat3d_translate(0.0f, 0.0f, z);       // Move Z units into/outof the screen
	    plx_mat3d_rotate(xrot, 1.0f, 0.0f, 0.0f); // Rotate the Cube by angle 'xrot' on the X axis 
	    plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f); // Rotate the Cube by angle 'yrot' on the Y axis
	    
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	    
    	/* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
		
		// Top Face of Cube 
		plx_vert_ifpm3(PLX_VERT, -1, 1, 1, color, 0, 1);     // Bottom Left Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 0);    // Top Left Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT, 1, 1, 1, color, 1, 1);      // Bottom Right Of The Quad (Top)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, -1, color, 1, 0); // Top Right Of The Quad (Top)
	    
		// Bottom Face of Cube 
		plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 1);   // Bottom Left Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 0, 0);    // Top Left Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT, 1, -1, -1, color, 1, 1);    // Bottom Right Of The Quad (Bottom)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, -1, 1, color, 1, 0); // Top Right Of The Quad (Bottom)	    
		
		// Front Face of Cube 
		plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 0, 1);    // Bottom Left Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT, -1, 1, 1, color, 0, 0);     // Top Left Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT, 1, -1, 1, color, 1, 1);     // Bottom Right Of The Quad (Front)
	    plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, 1, color, 1, 0);  // Top Right Of The Quad (Front)
		
		// Back Face of Cube 
		plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 1);    // Bottom Left Of The Quad (Back)
	    plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 0);   // Top Left Of The Quad (Back)
	    plx_vert_ifpm3(PLX_VERT, 1, 1, -1, color, 1, 1);     // Bottom Right Of The Quad (Back)
		plx_vert_ifpm3(PLX_VERT_EOS, 1, -1, -1, color, 1, 0);// Top Right Of The Quad (Back)
		
		// Left Face of Cube 
		plx_vert_ifpm3(PLX_VERT, -1, -1, -1, color, 0, 1);   // Bottom Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, 1, -1, color, 0, 0);    // Top Left Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT, -1, -1, 1, color, 1, 1);    // Bottom Right Of The Quad (Left)
	    plx_vert_ifpm3(PLX_VERT_EOS, -1, 1, 1, color, 1, 0); // Top Right Of The Quad (Left)
	    
		// Right Face of Cube 
		plx_vert_ifpm3(PLX_VERT, 1, -1, 1, color, 0, 1);     // Bottom Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, 1, 1, color, 0, 0);      // Top Left Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT, 1, -1, -1, color, 1, 1);    // Bottom Right Of The Quad (Right)
	    plx_vert_ifpm3(PLX_VERT_EOS, 1, 1, -1, color, 1, 0); // Top Right Of The Quad (Right)

		pvr_scene_finish();
		
		xrot += xspeed;   // X Axis Rotation	
        yrot += yspeed;	// Y Axis Rotation 
    }
     // Clean up!!!
    plx_txr_destroy(a_texture);

	return 0;
}

