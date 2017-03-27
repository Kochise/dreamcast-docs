

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
    printf("Y-Button: Toggle twinkling\n");
    printf("A-Button: Move the collection of stars into the distance \n");
    printf("B-Button: Move the collection of stars closer \n");
    
    printf("UP-Dir: Negative x rotation \n");
    printf("DOWN-Dir: Positive x rotation \n");
    printf("LEFT-Dir: NONE \n");
    printf("RIGHT-Dir: NONE \n");
    printf("/****************************/\n\n");
}


#define NUM_STARS 50	/* Number Of Stars To Draw */

typedef struct    	/* Create A Structure For Star */
{
	uint8 r, g, b;  /* Stars Color */
	float dist,		/* Stars Distance From Center */
    angle;  	    /* Stars Current Angle */
} stars;

static stars star[NUM_STARS];  /* Need To Keep Track Of 'NUM_STARS' Stars */

static int twinkle = 0;	       /* Twinkling Stars (0-false 1-true) */   

static float zoom = -15.0f;	   /* Distance Away From Stars */
static float tilt = 90.0f;	   /* Tilt The View */
static float spin;		       /* Spin Stars */

static uint16 loop;            /* General Loop Variable */
plx_texture_t *a_texture;      /* Pointer to plx_texture */

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
    
    int yp = 0;    // False (True or False: Pressed Y button last) 
    uint32 color = 0; 
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;

    printControls();
 
    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	/* Load the textures */
	a_texture = plx_txr_load("/rd/star.png", 1, PVR_TXRLOAD_16BPP);  /* The '1' enables transparency in the image */
	
	plx_txr_setfilter(a_texture, PLX_FILTER_BILINEAR);

	plx_cxt_init();                 // Initialize the plx context system
	plx_cxt_texture(a_texture);     // Texture 'a_texture' will be used with the context system
    plx_cxt_culling(PLX_CULL_NONE); // No culling
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  /* (float angle, float aspect, float znear, float zfar); */
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	/* Set up the stars */
	for (loop = 0; loop < NUM_STARS; loop++)
	{
		star[loop].angle = 0.0f;                            /* initially no rotation */
		star[loop].dist = ((float)(loop)/NUM_STARS)*5.0f;   /* calculate distance form the center */
		star[loop].r = rand()%256;     /* random red intensity */              
		star[loop].g = rand()%256;     /* random green intensity */ 
		star[loop].b = rand()%256;     /* random blue intensity */ 
	}
	
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
        if (state->buttons & CONT_Y && !yp) {
            yp = 1;          // toggle twinkling
            twinkle = !twinkle;
        } 
        if (!(state->buttons & CONT_Y)) {
			     yp = 0;
        }
        if (state->buttons & CONT_A) {
            zoom -= 0.2f;    // move the collection of stars into the distance. 
        } 
        if (state->buttons & CONT_B) {
            zoom += 0.2f;    // move the collection of stars closer.
        } 
        if (state->buttons & CONT_DPAD_UP) {
            tilt -= 0.5f;    // negative x rotation
        } 
        if (state->buttons & CONT_DPAD_DOWN) {
            tilt += 0.5f;    // positive x rotation  
        }   
                 
		pvr_wait_ready();
		pvr_scene_begin();
		
	    pvr_list_begin(PVR_LIST_TR_POLY);
	    plx_cxt_send(PVR_LIST_TR_POLY);    // Submit the Header for PVR_LIST_TR_POLY
		
		for (loop = 0; loop < NUM_STARS; loop++) {                // loop through all the stars.

            // DRAW STARS
            plx_mat3d_identity();                                  // reset the view before we draw each star.
	        plx_mat3d_translate(0.0f, 0.0f, zoom);                 // zoom into the screen.
	        plx_mat3d_rotate(tilt, 1.0f, 0.0f, 0.0f);              // tilt the view.
	        
	        plx_mat3d_rotate(star[loop].angle, 0.0f, 1.0f, 0.0f);  // rotate to the current star's angle.
	        plx_mat3d_translate(star[loop].dist, 0.0f, 0.0f);      // move forward on the X plane (the star's x plane).
	        
	        plx_mat3d_rotate(-star[loop].angle, 0.0f, 1.0f, 0.0f); // cancel the current star's angle.
	        plx_mat3d_rotate(-tilt, 1.0f, 0.0f, 0.0f);             // cancel the screen tilt.
	    
	        /* Clear internal to an identity matrix */
	        plx_mat_identity();
	    
    	    /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	        plx_mat3d_apply_all();
	        
	        if(twinkle) {            // twinkling stars enabled ... draw an additional star.
                color = plx_pack_color(1.0f, (float)(star[(NUM_STARS-loop)-1].r), (float)(star[(NUM_STARS-loop)-1].g),
                                       (float)(star[(NUM_STARS-loop)-1].b));
                
                plx_vert_ifpm3(PLX_VERT, -1.0f, 1.0f, 0.0f, color, 0.0f, 1.0f);       // Bottom Left Of The Texture and Star
                plx_vert_ifpm3(PLX_VERT, -1.0f, -1.0f, 0.0f, color, 0.0f, 0.0f);      // Top Left Of The Texture and Star
                plx_vert_ifpm3(PLX_VERT, 1.0f, 1.0f, 0.0f, color, 1.0f, 1.0f);        // Bottom Right Of The Texture and Star
                plx_vert_ifpm3(PLX_VERT_EOS, 1.0f, -1.0f, 0.0f, color, 1.0f, 0.0f);   // Top Right Of The Texture and Star
            }
            
            // DRAW STARS
            plx_mat3d_identity();                                  // reset the view before we draw each star.
	        plx_mat3d_translate(0.0f, 0.0f, zoom);                 // zoom into the screen.
	        plx_mat3d_rotate(tilt, 1.0f, 0.0f, 0.0f);              // tilt the view.
	        
	        plx_mat3d_rotate(star[loop].angle, 0.0f, 1.0f, 0.0f);  // rotate to the current star's angle.
	        plx_mat3d_translate(star[loop].dist, 0.0f, 0.0f);      // move forward on the X plane (the star's x plane).
	        
	        plx_mat3d_rotate(-star[loop].angle, 0.0f, 1.0f, 0.0f); // cancel the current star's angle.
	        plx_mat3d_rotate(-tilt, 1.0f, 0.0f, 0.0f);             // cancel the screen tilt.
	        plx_mat3d_rotate(spin, 0.0f, 0.0f, 1.0f);              // rotate the star on the z axis.
	    
	        /* Clear internal to an identity matrix */
	        plx_mat_identity();
	    
    	    /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
	        plx_mat3d_apply_all();
            
		    color = plx_pack_color(1.0f, (float)(star[loop].r), (float)(star[loop].g), (float)(star[loop].b));
		    
		    plx_vert_ifpm3(PLX_VERT, -1.0f, 1.0f, 0.0f, color, 0.0f, 1.0f);     // Bottom Left Of The Texture and Star
            plx_vert_ifpm3(PLX_VERT, -1.0f, -1.0f, 0.0f, color, 0.0f, 0.0f);    // Top Left Of The Texture and Star
            plx_vert_ifpm3(PLX_VERT, 1.0f, 1.0f, 0.0f, color, 1.0f, 1.0f);      // Bottom Right Of The Texture and Star
            plx_vert_ifpm3(PLX_VERT_EOS, 1.0f, -1.0f, 0.0f, color, 1.0f, 0.0f); // Top Right Of The Texture and Star
		     
		    spin += 0.01f;                                        // used to spin the stars.
		    star[loop].angle += (loop * 1.0f)/(NUM_STARS * 1.0f); // change star angle.
		    star[loop].dist -= 0.01f;                             // bring back to center.
		    
		    if (star[loop].dist < 0.0f)           // star hit the center
		    {
			    star[loop].dist += 5.0f;          // move 5 units from the center.
			    star[loop].r = rand()%256;        // new red color.
			    star[loop].g = rand()%256;        // new green color.
			    star[loop].b = rand()%256;        // new blue color.
	        }	
        } 
        pvr_scene_finish();      
    }
    // Clean up!!!
    plx_txr_destroy(a_texture);

	return 0;
}

