
#include <kos.h>
#include <math.h>
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
    printf("X-Button: NONE \n");
    printf("Y-Button: NONE \n");
    printf("A-Button: Toggles displaying the control point grid \n");
    printf("B-Button: NONE \n");
    
    printf("UP-Dir: Increase Smoothness \n");
    printf("DOWN-Dir: Decrease Smoothness \n");
    printf("LEFT-Dir: Rotate to the left \n");
    printf("RIGHT-Dir: Rotate to the right \n");
    printf("/****************************/\n\n");
}

typedef struct point_3d {			// Structure for a 3-dimensional point 
	double x, y, z;
} POINT_3D;

typedef struct bpatch {				// Structure for a 3rd degree bezier patch 
	POINT_3D	anchors[4][4];		// 4x4 grid of anchor points
	plx_texture_t *texture;			// Texture for the patch
} BEZIER_PATCH;

float			rotz = 0.0f;		// Rotation about the Z axis
BEZIER_PATCH	mybezier;			// The bezier patch we're going to use 
int			    showCPoints = 1;	// Toggles displaying the control point grid 
int				divs = 3;			// Number of intrapolations (conrols poly resolution) 
plx_dr_state_t  dr_state;
pvr_vertex_t	vertices[313];      // Holds 312 vertices
int vgenBezier = 0;                 // Generate new Bezier (True or False)
int vertnumBezier = 0;              // Holds the amount of vertices of the Bezier  

// Adds 2 points. Don't just use '+' ;)
POINT_3D pointAdd(POINT_3D p, POINT_3D q) {
	p.x += q.x;		p.y += q.y;		p.z += q.z;
	return p;
}

// Multiplies a point and a constant. Don't just use '*'
POINT_3D pointTimes(double c, POINT_3D p) {
	p.x *= c;	p.y *= c;	p.z *= c;
	return p;
}

// Function for quick point creation
POINT_3D makePoint(double a, double b, double c) {
	POINT_3D p;
	p.x = a;	p.y = b;	p.z = c;
	return p;
}
// !!!!!!!!!!!!!!!!!!!!need math.h
// Calculates 3rd degree polynomial based on array of 4 points
// and a single variable (u) which is generally between 0 and 1
POINT_3D Bernstein(float u, POINT_3D *p) {
	POINT_3D	a, b, c, d, r;

	a = pointTimes(pow(u,3), p[0]);
	b = pointTimes(3*pow(u,2)*(1-u), p[1]);
	c = pointTimes(3*u*pow((1-u),2), p[2]);
	d = pointTimes(pow((1-u),3), p[3]);

	r = pointAdd(pointAdd(a, b), pointAdd(c, d));

	return r;
}

// Generates vertices based on the data in the patch
// and the number of divisions
void genBezier(BEZIER_PATCH patch, int divs) {
	int			u = 0, v, i = 0;
	float		py, px, pyold; 
	POINT_3D	temp[4];
	POINT_3D	*last = (POINT_3D*)malloc(sizeof(POINT_3D)*(divs+1));	// array of points to mark the first line of polys
    
	temp[0] = patch.anchors[0][3];				// the first derived curve (along x axis)
	temp[1] = patch.anchors[1][3];
	temp[2] = patch.anchors[2][3];
	temp[3] = patch.anchors[3][3];

	for (v = 0; v <= divs; v++) {				// create the first line of points
		px = ((float)v)/((float)divs);			// percent along y axis
	    // use the 4 points from the derives curve to calculate the points along that curve
		last[v] = Bernstein(px, temp);
	}

	for (u = 1;u <= divs;u++) {
		py	  = ((float)u)/((float)divs);			// Percent along Y axis
		pyold = ((float)u-1.0f)/((float)divs);		// Percent along old Y axis

		temp[0] = Bernstein(py, patch.anchors[0]);	// Calculate new bezier points
		temp[1] = Bernstein(py, patch.anchors[1]);
		temp[2] = Bernstein(py, patch.anchors[2]);
		temp[3] = Bernstein(py, patch.anchors[3]);

		for (v = 0;v <= divs; v++) {
			px = ((float)v)/((float)divs);			// Percent along the X axis

			vertices[i].flags = PLX_VERT;
			vertices[i].x = last[v].x;
			vertices[i].y = last[v].y;
			vertices[i].z = last[v].z;
			vertices[i].u = pyold;
			vertices[i].v = px;
			
		    i++;
		    
			last[v] = Bernstein(px, temp);			// Generate new point
		
            vertices[i].flags = PLX_VERT;
			vertices[i].x = last[v].x;
			vertices[i].y = last[v].y;
			vertices[i].z = last[v].z;
			vertices[i].u = py;
			vertices[i].v = px;
			
			i++;
		}
	}
	vertnumBezier = i;
	vertices[--i].flags = PLX_VERT_EOS;
	free(last);	// Free the old vertices array
	return;							
}

/************************************************************************************/

void initBezier(void) {	
	mybezier.anchors[0][0] = makePoint(-0.75,	-0.75,	-0.5);	// set the bezier vertices
	mybezier.anchors[0][1] = makePoint(-0.25,	-0.75,	0.0);
	mybezier.anchors[0][2] = makePoint(0.25,	-0.75,	0.0);
	mybezier.anchors[0][3] = makePoint(0.75,	-0.75,	-0.5);
	
	mybezier.anchors[1][0] = makePoint(-0.75,	-0.25,	-0.75);
	mybezier.anchors[1][1] = makePoint(-0.25,	-0.25,	0.5);
	mybezier.anchors[1][2] = makePoint(0.25,	-0.25,	0.5);
	mybezier.anchors[1][3] = makePoint(0.75,	-0.25,	-0.75);
	
	mybezier.anchors[2][0] = makePoint(-0.75,	0.25,	0.0);
	mybezier.anchors[2][1] = makePoint(-0.25,	0.25,	-0.5);
	mybezier.anchors[2][2] = makePoint(0.25,	0.25,	-0.5);
	mybezier.anchors[2][3] = makePoint(0.75,	0.25,	0.0);
	
	mybezier.anchors[3][0] = makePoint(-0.75,	0.75,	-0.5);
	mybezier.anchors[3][1] = makePoint(-0.25,	0.75,	-1.0);
	mybezier.anchors[3][2] = makePoint(0.25,	0.75,	-1.0);
	mybezier.anchors[3][3] = makePoint(0.75,	0.75,	-0.5);
}

// Taken from: C:\cygwin\usr\local\dc\kos\kos\examples\dreamcast\parallax\delay_cube\delay_cube.c
// and modified to draw a line instead of a point.
void drawline(plx_dr_state_t * state, POINT_3D vertex1, POINT_3D vertex2, uint32 col) {
     
    pvr_poly_hdr_t Line_Header; 
    pvr_poly_cxt_t Line_context; 
     
    pvr_poly_cxt_col(&Line_context, PVR_LIST_OP_POLY);
    Line_context.gen.culling = PVR_CULLING_NONE;
    pvr_poly_compile(&Line_Header, &Line_context);   // Convert the context into something the pvr can read
    pvr_prim(&Line_Header, sizeof(pvr_poly_hdr_t));  // Submit image header to PVR 
     
	// Transform the vector points, 
	plx_mat_tfip_3d(vertex1.x, vertex1.y, vertex1.z);
	plx_mat_tfip_3d(vertex2.x, vertex2.y, vertex2.z);
	
	// Draw it.
	plx_vert_ind(state, PLX_VERT, vertex1.x, vertex1.y+2.0f, vertex1.z, col);
	plx_vert_ind(state, PLX_VERT, vertex1.x, vertex1.y, vertex1.z, col);
	plx_vert_ind(state, PLX_VERT, vertex2.x+2.0f, vertex2.y+2.0f, vertex2.z, col);
	plx_vert_ind(state, PLX_VERT_EOS, vertex2.x+2.0f, vertex2.y, vertex2.z, col);
    
}

void drawBezier() {
    int i = 0; 
    
    while(i != vertnumBezier) {  
        // Submit the vertex one at a time
        plx_vert_ifdm3(&dr_state, vertices[i].flags, vertices[i].x, vertices[i].y, vertices[i].z, 0xffffffff, vertices[i].u, vertices[i].v);            
		i++;
    }
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
    int ap = 0;    // False (True or False: Pressed A button last) Toggles displaying the control point grid
    int up = 0;    // False (True or False: Pressed up button last) Increase smoothness
    int dp = 0;    // False (True or False: Pressed down button last) Decrease smoothness

    int i = 0;
    uint32 color = 0;

	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
    
    printControls();	

    /* Sets the background color to green */
	pvr_set_bg_color(0.0f, 1.0f, 0.0f);
    
    initBezier();		// Initialize the Bezier's control grid
	mybezier.texture = plx_txr_load("/rd/logo.png", 0, PVR_TXRLOAD_16BPP | PVR_TXRLOAD_INVERT_Y); // Load the texture
	genBezier(mybezier, divs);  // Generate Bezier
    
	plx_cxt_init();                    // Initialize the plx context system
	plx_cxt_texture(mybezier.texture); // Use texture 'mybezier.texture' with the context system
    plx_cxt_culling(PLX_CULL_NONE);    // No Culling
	
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
        if (state->buttons & CONT_A && !ap) {
            ap = 1;                 
            showCPoints = !showCPoints;	// Toggles displaying the control point grid
        }
        if (!(state->buttons & CONT_A)) {
            ap = 0;
        }
        if (state->buttons & CONT_DPAD_UP && !up) {
            up = 1;               
            divs++;                     // Increase smoothness
            if(divs > 12) { 
                divs = 12;
            }
            vgenBezier = !vgenBezier;
        }
        if (!(state->buttons & CONT_DPAD_UP)) {
            up = 0;
        }
        if (state->buttons & CONT_DPAD_DOWN && !dp) {
            dp = 1;               
            divs--;                     // Decrease smoothness 
            if(divs < 1) { 
                divs = 1;
            }
            vgenBezier = !vgenBezier;
        }
        if (!(state->buttons & CONT_DPAD_DOWN)) {
            dp = 0;
        }
        if (state->buttons & CONT_DPAD_LEFT) {
            rotz -= 0.8f;		// Rotate left
        }
        if (state->buttons & CONT_DPAD_RIGHT) {
            rotz += 0.8f;		// Rotate right
        }
        
        if(vgenBezier) {
            genBezier(mybezier, divs);  // Generate new Bezier)
            vgenBezier = !vgenBezier;
        }
        
		pvr_wait_ready();
		pvr_scene_begin();	
	    
        pvr_list_begin(PVR_LIST_OP_POLY);
	    plx_cxt_send(PVR_LIST_OP_POLY);    // Submit the Header for PVR_LIST_OP_POLY
	    
	    plx_dr_init(&dr_state);    // Initialize a state variable for Direct Rendering
		
        plx_mat3d_identity(); 
        plx_mat3d_translate(0.0f, 0.0f, -4.0f);     // Move 4 units into the screen
        plx_mat3d_rotate(-75.0f, 1.0f, 0.0f, 0.0f); // Rotate -75 degrees on the X-Axis      
        plx_mat3d_rotate(rotz, 0.0f, 0.0f, 1.0f);   // Rotate 'rotz' degrees on the Z-Axis
                
        /* Clear internal to an identity matrix */
        plx_mat_identity();
	    
        /* "Applying" all matrixs: multiply a matrix onto the "internal" one */
        plx_mat3d_apply_all();
        
        drawBezier();
        
	    if (showCPoints) {									 // If drawing the grid is toggled on
     
		    color = plx_pack_color(1.0f, 1.0f, 0.0f, 0.0f);  // Red colored lines
		    for(i = 0; i < 4; i++) {								 
	            // draw the horizontal lines
	            drawline(&dr_state, mybezier.anchors[i][0], mybezier.anchors[i][1], color);
	            drawline(&dr_state, mybezier.anchors[i][1], mybezier.anchors[i][2], color);
	            drawline(&dr_state, mybezier.anchors[i][2], mybezier.anchors[i][3], color);
		    }
		    for(i = 0; i < 4; i++) {								 
			    // draw the vertical lines
			    drawline(&dr_state, mybezier.anchors[0][i], mybezier.anchors[1][i], color);
	            drawline(&dr_state, mybezier.anchors[1][i], mybezier.anchors[2][i], color);
	            drawline(&dr_state, mybezier.anchors[2][i], mybezier.anchors[3][i], color);
		    }
		    color = plx_pack_color(1.0f, 1.0f,1.0f,1.0f);
	    }
	    
        pvr_scene_finish();      
    }
    // Clean up!!!
    plx_txr_destroy(mybezier.texture);

	return 0;
}




