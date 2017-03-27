

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
    printf("X-Button: Toggles filtering \n");
    printf("Y-Button: Toggle blending\n");
    printf("A-Button: Look up \n");
    printf("B-Button: Look down \n");
    
    printf("UP-Dir: Walk forward \n");
    printf("DOWN-Dir: Walk backward \n");
    printf("LEFT-Dir: Turn left \n");
    printf("RIGHT-Dir: Turn right \n");
    printf("/****************************/\n\n");
}

uint8 loop;                     // general loop variable
plx_texture_t *textures[2];     // storage for 2 textures

float xrot;            // x rotation
float yrot;            // y rotation
float xspeed;          // x rotation speed
float yspeed;          // y rotation speed

float walkbias = 0.0f;
float walkbiasangle = 0.0f;

float lookupdown = 0.0f;
const float piover180 = 0.0174532925f;   // pie/180 degrees

float xpos, zpos;     

typedef struct {       // vertex coordinates - 3d and texture
    float x, y, z;     // 3d coords.
    float u, v;        // texture coords.
} VERTEX;

typedef struct {         // triangle
    VERTEX vertex[3];    // 3 vertices array
} TRIANGLE;

typedef struct {         // sector of a 3d environment
    int numtriangles;    // number of triangles in the sector
    TRIANGLE* triangle;  // pointer to array of triangles.
} SECTOR;

SECTOR sector1;

// Helper for SetupWorld.  reads a file into a string until a nonblank, non-comment line
// is found ("/" at the start indicating a comment); assumes lines < 255 characters long.
void readstr(FILE *f, char *string)
{
    do {                             // Start A Loop
	    fgets(string, 255, f);       // Read one line
    } while ((string[0] == '/') || (string[0] == '\n'));  // See If It Is Worthy Of Processing
    return;
}

// loads the world from a text file.
void SetupWorld() 
{
    float x, y, z, u, v;
    int vert;
    int numtriangles;    // Number Of Triangles In Sector
    FILE *filein;        // file to load the world from
    char oneline[255];   // String To Store Data In

    filein = fopen("/rd/world.txt", "rt");

    readstr(filein, oneline);     // Get Single Line Of Data           
    sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);     // Read In Number Of Triangles

    sector1.numtriangles = numtriangles;    // Define The Number Of Triangles In Sector 1
    sector1.triangle = (TRIANGLE *) malloc(sizeof(TRIANGLE)*numtriangles);  // Allocate Memory For numtriangles And Set Pointer
    
    for (loop = 0; loop < numtriangles; loop++) {    // Loop Through All The Triangles
	    for (vert = 0; vert < 3; vert++) {
	        readstr(filein,oneline);   // Read String To Work With
	        sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);  // Read Data Into Respective Vertex Values
	        sector1.triangle[loop].vertex[vert].x = x;
	        sector1.triangle[loop].vertex[vert].y = y;
	        sector1.triangle[loop].vertex[vert].z = z;
	        sector1.triangle[loop].vertex[vert].u = u;
	        sector1.triangle[loop].vertex[vert].v = v;
	    }
    }

    fclose(filein);
    return;
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
    int blend = 0; // blending on/off
    
    float x_m, y_m, z_m, u_m, v_m;
    float xtrans, ztrans, ytrans;
    float sceneroty;
    int numtriangles;
    
    int filter = 0;   // texture filtering method to use (NONE or BILINEAR)
    uint32 color = plx_pack_color(0.5f, 1.0f, 1.0f, 1.0f);

	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();	
    
    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);

	/* load our world from romdisk */
    SetupWorld();
	
	/* Load the textures */
	textures[0] = plx_txr_load("/rd/mud.png", 0, PVR_TXRLOAD_16BPP | PVR_TXRLOAD_INVERT_Y);  
	textures[1] = plx_txr_load("/rd/mud.png", 0, PVR_TXRLOAD_16BPP | PVR_TXRLOAD_INVERT_Y);  

	plx_cxt_init();                 // Initialize the plx context system
    plx_cxt_culling(PLX_CULL_NONE); // No culling
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	/* Set the filters for each texture */
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
            lookupdown -= 1.0f;  // look up
        } 
        if (state->buttons & CONT_B) {
            lookupdown += 1.0f;  // look down
        } 
        if (state->buttons & CONT_DPAD_UP) {
            xpos -= fsin(yrot*piover180) * 0.05f;  // moves you forward(bobbing head)
            zpos -= fcos(yrot*piover180) * 0.05f;	
            if (walkbiasangle >= 359.0f) {
                walkbiasangle = 0.0f;	
            } else {
                walkbiasangle += 10.0f;
            }
            walkbias = fsin(walkbiasangle * piover180)/20.0f;
        } 
        if (state->buttons & CONT_DPAD_DOWN) {
            xpos += fsin(yrot*piover180) * 0.05f;  // moves you backward(bobbing head)
            zpos += fcos(yrot*piover180) * 0.05f;	
            if (walkbiasangle <= 1.0f) {
                walkbiasangle = 359.0f;	
            } else {
                walkbiasangle -= 10.0f;
            }
            walkbias = fsin(walkbiasangle * piover180)/20.0f;
        }   
        if (state->buttons & CONT_DPAD_LEFT) {
            yrot += 1.5f;    // Turn Left
        } 
        if (state->buttons & CONT_DPAD_RIGHT) {
            yrot -= 1.5f;	  // Turn Right   
        }         
                 
		pvr_wait_ready();
		pvr_scene_begin();
		
	    if(blend) {
		    pvr_list_begin(PVR_LIST_TR_POLY);
		    plx_cxt_send(PVR_LIST_TR_POLY);     // Submit the Header for PVR_LIST_TR_POLY
        } else {
            pvr_list_begin(PVR_LIST_OP_POLY);
		    plx_cxt_send(PVR_LIST_OP_POLY);     // Submit the Header for PVR_LIST_OP_POLY 
        }
		
		/* Select texture according to filter */
		plx_cxt_texture(textures[filter]);
		
	    xtrans = -xpos;   // Used For Player Translation On The X Axis    
        ztrans = -zpos;   // Used For Player Translation On The Z Axis
        ytrans = -walkbias - 0.25f;  // Used For Bouncing Motion Up And Down
        sceneroty = 360.0f - yrot;   // 360 Degree Angle For Player Direction
        
        plx_mat3d_identity();                                           
        plx_mat3d_rotate(lookupdown, 1.0f, 0.0f, 0.0f); // Rotate Up And Down To Look Up And Down             
        plx_mat3d_rotate(sceneroty, 0.0f, 1.0f, 0.0f);  // Rotate Depending On Direction Player Is Facing 
        plx_mat3d_translate(xtrans, ytrans, ztrans);    // Translate The Scene Based On Player Position          
	    
        /* Clear internal to an identity matrix */
        plx_mat_identity();
	    
	    /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
		    
		numtriangles = sector1.numtriangles;    
	
        for (loop = 0; loop < numtriangles; loop++) {        // loop through all the triangles
 
	        // Vertex 1
	        x_m = sector1.triangle[loop].vertex[0].x;
	        y_m = sector1.triangle[loop].vertex[0].y;
	        z_m = sector1.triangle[loop].vertex[0].z;
	        u_m = sector1.triangle[loop].vertex[0].u;
	        v_m = sector1.triangle[loop].vertex[0].v;
	        plx_vert_ifpm3(PLX_VERT, x_m, y_m, z_m, color, u_m, v_m);
	        
	        // Vertex 2
	        x_m = sector1.triangle[loop].vertex[1].x;
	        y_m = sector1.triangle[loop].vertex[1].y;
	        z_m = sector1.triangle[loop].vertex[1].z;
	        u_m = sector1.triangle[loop].vertex[1].u;
	        v_m = sector1.triangle[loop].vertex[1].v;
	        plx_vert_ifpm3(PLX_VERT, x_m, y_m, z_m, color, u_m, v_m);
	        
	         // Vertex 3
	        x_m = sector1.triangle[loop].vertex[2].x;
	        y_m = sector1.triangle[loop].vertex[2].y;
	        z_m = sector1.triangle[loop].vertex[2].z;
	        u_m = sector1.triangle[loop].vertex[2].u;
	        v_m = sector1.triangle[loop].vertex[2].v;
	        plx_vert_ifpm3(PLX_VERT_EOS, x_m, y_m, z_m, color, u_m, v_m);
	        
        }
        pvr_scene_finish();      
    }
    // Clean up!!!
    free(sector1.triangle);
    plx_txr_destroy(textures[0]);
    plx_txr_destroy(textures[1]);
    
	return 0;
}

