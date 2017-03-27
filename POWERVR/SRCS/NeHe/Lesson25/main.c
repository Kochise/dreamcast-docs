
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
    printf("X-Button: Morph to Torus \n");
    printf("Y-Button: Morph to Tube \n");
    printf("A-Button: Morph to Sphere \n");
    printf("B-Button: Morph to Space \n");
    printf("R-Trigger: Rotate the shapes CCW(Counter-clockwise) \n");
    printf("L-Trigger: Rotate the shapes CW(Clockwise) \n");
    
    printf("UP-Dir: Rotate the shapes upward \n");
    printf("DOWN-Dir: Rotate the shapes downward \n");
    printf("LEFT-Dir: Rotate the shapes to the left \n");
    printf("RIGHT-Dir: Rotate the shapes to the right \n");
    printf("/****************************/\n\n");
}

/* Build Our Vertex Structure */
typedef struct {
	float x, y, z; /* 3D Coordinates */
} vertex;

/* Build Our Object Structure */
typedef struct {
	int verts;      /* Number Of Vertices For The Object */
	vertex *points; /* One Vertice (Vertex x,y & z)      */
} object;

float xrot, yrot, zrot;        /* Camera rotation variables                */
float cx, cy, cz = -15;        /* Camera pos variable                      */
float xspeed, yspeed, zspeed;  /* Spin Speed                               */

int key = 1;                     /* Make Sure Same Morph Key Not Pressed     */
int step = 0, steps = 200;       /* Step Counter And Maximum Number Of Steps */
int morph = 0;                   /* Default morph To False (Not Morphing)    */

int maxver;                            /* Holds The Max Number Of Vertices   */
object morph1, morph2, morph3, morph4, /* Our 4 Morphable Objects            */
	helper, *sour, *dest;              /* Helper, Source, Destination Object */

#define MORPHS 4

/* function to allocate memory for an object */
void objallocate( object *k, int n ) {
	/* Sets points Equal To VERTEX * Number Of Vertices */
	k->points = ( vertex* )malloc( sizeof( vertex ) * n );
}

/* function deallocate memory for an object */
void objfree( object *k ) {
	free( k->points );
}

/* function to release/destroy our resources and restoring the old desktop */
void Quit() {

	/* deallocate the objects' memory */
	objfree( &morph1 );
	objfree( &morph2 );
	objfree( &morph3 );
	objfree( &morph4 );
	objfree( &helper );
}

/* function Loads Object From File (name) */
void objload( char *name, object *k ) {

	int ver;           /* Will Hold Vertice Count                */
	float rx, ry, rz;  /* Hold Vertex X, Y & Z Position          */
	FILE *filein;      /* Filename To Open                       */
	int i;             /* Simple loop variable                   */
    
	printf("  [objload] file: %s\n", name);

	/* Opens The File For Reading */
	filein = fopen( name, "r" );
	/* Reads the number of verts in the file */
	fread(&ver, sizeof(int), 1, filein);
	/* Sets Objects verts Variable To Equal The Value Of ver */
	k->verts = ver;
	/* Jumps To Code That Allocates Ram To Hold The Object */
	objallocate( k,ver );
    
	/* Loops Through The Vertices */
	for ( i = 0; i < ver; i++ ) {
		/* Reads the next three verts */
		fread(&rx, sizeof(float), 1, filein);
		fread(&ry, sizeof(float), 1, filein);
		fread(&rz, sizeof(float), 1, filein);
		/* Set our object's x, y, z points */
		k->points[i].x = rx;
		k->points[i].y = ry;
		k->points[i].z = rz;
	}

	/* Close The File */
	fclose( filein );

	/* If ver Is Greater Than maxver Set maxver Equal To ver */
	if( ver > maxver )
		maxver = ver;
}

/* function to calculate Movement Of Points During Morphing */
vertex calculate( int i ) {

	vertex a; /* Temporary Vertex Called a */

	/* Calculate x, y, and z movement */
	a.x = ( sour->points[i].x - dest->points[i].x ) / steps;
	a.y = ( sour->points[i].y - dest->points[i].y ) / steps;
	a.z = ( sour->points[i].z - dest->points[i].z ) / steps;

	return a;
} 

// Taken from: C:\cygwin\usr\local\dc\kos\kos\examples\dreamcast\parallax\delay_cube\delay_cube.c
// Draw a single point in 3D space. Uses the currently loaded matrix.
void drawpnt(plx_dr_state_t * state, float x, float y, float z, uint32 col) {
     
	// Transform the point, clip the Z plane to avoid artifacts.
	plx_mat_tfip_3d(x, y, z);
	if (z <= 0.00001f) z = 0.00001f;

	// Draw it.
	plx_vert_ind(state, PLX_VERT, x, y+1.0f, z, col);
	plx_vert_ind(state, PLX_VERT, x, y, z, col);
	plx_vert_ind(state, PLX_VERT, x+1.0f, y+1.0f, z, col);
	plx_vert_ind(state, PLX_VERT_EOS, x+1.0f, y, z, col);
}


pvr_init_params_t params = {
	/* Enable opaque and translucent polygons with size 16 */
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	
	/* Vertex buffer size 512K */
	512*1024
};

#define NOT_LAST (!(state->buttons & last))

int main(int argc, char **argv) {
    
    /* Controller Stuff */
    maple_device_t * dev;
    cont_state_t * state;
    uint32	last = CONT_A;
    
    xrot = yrot = zrot = 0.0f;
	xspeed = yspeed = zspeed = 0.0f;
  
    uint32 color = 0;
    plx_dr_state_t dr_state;
    
    float tx, ty, tz; /* Temp X, Y & Z Variables                     */
	vertex q;         /* Holds Returned Calculated Values For One Vertex */
	int i;            /* Simple Looping Variable                         */
	
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
		
	printControls();	

    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
    
	plx_cxt_init();                  // Initialize the plx context system
	plx_cxt_texture(NULL);           // No texture will be used with the context system
    plx_cxt_culling(PLX_CULL_NONE);  // No Culling
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	/* Sets Max Vertices To 0 By Default */
	maxver = 0;
	/* Load The First Object Into morph1 From File sphere.bin */
	objload( "/rd/sphere.bin", &morph1 );
	/* Load The Second Object Into morph2 From File torus.bin */
	objload( "/rd/torus.bin", &morph2 );
	/* Load The Third Object Into morph3 From File tube.bin */
	objload( "/rd/tube.bin", &morph3 );

	/* Manually Reserve Ram For A 4th 486 Vertice Object (morph4) */
	objallocate( &morph4, 486 );
	
	/* Loop Through All 468 Vertices */
	for( i = 0; i < 486; i++ ) {
		/* Generate a random point in xyz space for each vertex */
		/* Values range from -7 to 7                            */
		morph4.points[i].x = (( float )( rand( ) % 14000 ) / 1000 ) - 7;
		morph4.points[i].y = (( float )( rand( ) % 14000 ) / 1000 ) - 7;
		morph4.points[i].z = (( float )( rand( ) % 14000 ) / 1000 ) - 7;
	}

	/* Load sphere.txt Object Into Helper (Used As Starting Point) */
	objload( "/rd/sphere.bin", &helper );
	/* Source & Destination Are Set To Equal First Object (morph1) */
	sour = dest = &morph1;
	
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
        if (state->buttons & CONT_X && !morph && NOT_LAST) {
            morph = 1;       // morph to torus
            dest = &morph2;
            last = CONT_X;
		}
        if (state->buttons & CONT_Y && !morph && NOT_LAST) {
            morph = 1;       // morph to tube
            dest = &morph3;
            last = CONT_Y;
		}
		if (state->buttons & CONT_A && !morph && NOT_LAST) { 
            morph = 1;       // morph to sphere
	        dest = &morph1;
            last = CONT_A;
		}
        if (state->buttons & CONT_B && !morph && NOT_LAST) {
            morph = 1;       // morph to space
            dest = &morph4;
            last = CONT_B;
		}
        if (state->buttons & CONT_DPAD_UP) {
            xspeed -= 0.01f;   // decrease x rotation speed (away from you)
        }
        if (state->buttons & CONT_DPAD_DOWN) {
            xspeed += 0.01f;   // increase x rotation speed (toward you)
        }
        if (state->buttons & CONT_DPAD_LEFT) {
            yspeed -= 0.01f;   // decrease y rotation speed (left)
        }
        if (state->buttons & CONT_DPAD_RIGHT) {
            yspeed += 0.01f;   // increase y rotation speed (right)
        }
		if (state->rtrig) {
            zspeed += 0.01f;   // increase z rotation speed (CCW)
        }
		if (state->ltrig) {
            zspeed -= 0.01f;   // decrease z rotation speed (CW)
        }
                 
		pvr_wait_ready();
		pvr_scene_begin();	
	    
        pvr_list_begin(PVR_LIST_OP_POLY);
	    plx_cxt_send(PVR_LIST_OP_POLY);   // Submit the Header for PVR_LIST_OP_POLY
	    
	    plx_dr_init(&dr_state);   // Initialize a state variable for Direct Rendering
		
        plx_mat3d_identity(); 
        plx_mat3d_translate(cx, cy, cz);   
        plx_mat3d_rotate(xrot, 1.0f, 0.0f, 0.0f);  // Rotate the Shape by angle 'xrot' on the X axis      
        plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f);  // Rotate the Shape by angle 'yrot' on the Y axis  
        plx_mat3d_rotate(zrot, 0.0f, 0.0f, 1.0f);  // Rotate the Shape by angle 'zrot' on the Z axis
                
        /* Clear internal to an identity matrix */
        plx_mat_identity();
	    
        /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
        
        /* Increase xrot,yrot & zrot by xspeed, yspeed & zspeed */
	    xrot += xspeed;
	    yrot += yspeed;
	    zrot += zspeed;
	    
	    /* Loop Through All The Verts Of morph1 (All Objects Have
	     * * The Same Amount Of Verts For Simplicity, Could Use maxver Also)
	     * */
        for( i = 0; i < morph1.verts; i++ ) {
		    /* If morph Is True Calculate Movement Otherwise Movement=0 */
		    if ( morph )
			    q = calculate( i );
		    else
		    	q.x = q.y  = q.z = 0.0f;

		    /* Subtract the calculated unitx from the point's xyz coords */
		    helper.points[i].x -= q.x;
		    helper.points[i].y -= q.y;
		    helper.points[i].z -= q.z;

		    /* Set the temp xyz vars the the helper's xyz vars */
		    tx = helper.points[i].x;
		    ty = helper.points[i].y;
		    tz = helper.points[i].z;

		    /* Set Color To A Bright Shade Of Off Blue */
		    color = plx_pack_color(1.0f, 0.0f, 1.0f, 1.0f);
		    /* Draw A Point At The Current Temp Values (Vertex) */
		    drawpnt(&dr_state, tx, ty, tz, color);
		    
		    /* Calculate Two Positions Ahead */
		    tx -= 2.0f * q.x;
		    ty -= 2.0f * q.y;
		    tz -= 2.0f * q.z;
            
            /* Darken Color A Bit */
		    color = plx_pack_color(1.0f, 0.0f, 0.5f, 1.0f);
		    /* Draw A Second Point At The Newly Calculate Position */
		    drawpnt(&dr_state, tx, ty, tz, color);
				    
		    /* Calculate Two More Positions Ahead */
		    tx -= 2.0f * q.x;
		    ty -= 2.0f * q.y;
		    tz -= 2.0f * q.z;
		    
		    /* Set Color To A Very Dark Blue */
		    color = plx_pack_color(1.0f, 0.0f, 0.0f, 1.0f);
		    /* Draw A Third Point At The Second New Position */
		    drawpnt(&dr_state, tx, ty, tz, color);

        }
        
       /* If We're Morphing And We Haven't Gone Through All 200 Steps
	    * Increase Our Step Counter
	    * Otherwise Set Morphing To False, Make Source=Destination And
	    * Set The Step Counter Back To Zero.
	    */
	
    	if( morph && step <= steps ) {
	    	step++;
	    }
	    else {
	    	morph = 0;
	    	step  = 0;
	    	sour  = dest;
	    }
	    
        pvr_scene_finish();      
    }
    // Clean Up!!!
    Quit();
    
	return 0;
}








