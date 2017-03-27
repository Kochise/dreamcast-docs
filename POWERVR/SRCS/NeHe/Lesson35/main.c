
#include <kos.h>
#include <plx/prim.h>
#include <plx/matrix.h>
#include <plx/context.h>
#include <plx/texture.h>

/* PLEASEEEEEEEEEEEEEEE READDDDDDDDDDDDDDDDDDDD
 * To compile this you have to add source code to the parallax library and 
 * recompile it.
 * Add this to mat3d.c (C:\cygwin\usr\local\dc\kos\kos-ports\libparallax\src)
 * in between plx_mat3d_frustum() and plx_mat3d_push() :

static matrix_t mo __attribute__((aligned(32))) = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void plx_mat3d_ortho(float left, float right, float bottom, float top, float znear, float zfar) {

	float x, y, z;
	float tx, ty, tz;

	x = 2.0f / (right - left);
	y = 2.0f / (top - bottom);
	z = -2.0f / (zfar - znear);
	tx = -(right + left) / (right - left);
	ty = -(top + bottom) / (top - bottom);
	tz = -(zfar + znear) / (zfar - znear);

	mo[0][0] = x;
	mo[1][1] = y;
	mo[2][2] = z;
	mo[3][0] = tx;
	mo[3][1] = ty;
	mo[3][2] = tz;

	mat_load(trans_mats + matrix_mode);
	mat_apply(&mo);
	mat_store(trans_mats + matrix_mode);
}

* also add this to matrix.h(C:\cygwin\usr\local\dc\kos\kos-ports\libparallax\include)
* between plx_mat3d_frustum() and plx_mat3d_push() :
          
// Setup a orthogonal matrix 
void plx_mat3d_ortho(float left, float right, float bottom, float top, float znear, float zfar);

* and then compile this example.
*/

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

// User Defined Variables
float angle;               /* Used To Rotate The Helix */
float vertexes[4][3];	   /* Holds Float Info For 4 Sets Of Vertices */
plx_texture_t BlurTexture; /* Holds a texture */
uint32 tx_x = 1024, tx_y = 512;
plx_dr_state_t dr_state;

void EmptyTexture()	 // Create An Empty Texture
{
    pvr_poly_cxt_t cxt;
     
	// Create Storage Space For Texture Data (1024x512x2)
	BlurTexture.ptr = pvr_mem_malloc(1024 * 512 * 2);
	
	pvr_poly_cxt_txr(
		&cxt,
		PVR_LIST_TR_POLY,
		PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED,  // Change if bad
		1024,
		512,
		BlurTexture.ptr,
		PVR_FILTER_NONE
	);
	pvr_poly_compile(&BlurTexture.hdr_trans, &cxt);
}

void ProcessHelix()												// Draws A Helix
{
	float x;	 // Helix x Coordinate
	float y;	 // Helix y Coordinate
	float z;	 // Helix z Coordinate
	float phi;	 // Angle
	float theta; // Angle
	float v, u;	 // Angles
	float r;	 // Radius Of Twist
	int twists = 5;	 // 5 Twists
	uint32 color = plx_pack_color(1.0f, 1.0f, 1.0f, 1.0f); //{1.0f, 0.4f, 0.2f, 0.8f};	Set The Material Color1
	
	pvr_poly_cxt_t	cxt_helix;
    pvr_poly_hdr_t  hdr_helix;
	
	/* vector_t defined in C:\cygwin\usr\local\dc\kos\kos\addons\include\kos\vector.h */
    /* Holds 3 floats */
    vector_t eye = {0.0f, 5.0f, 50.0f};
    vector_t center = {0.0f, 0.0f, 0.0f};
    vector_t up = {0.0f, 1.0f, 0.0f};		
    
    pvr_poly_cxt_col(&cxt_helix, PVR_LIST_OP_POLY);
    pvr_poly_compile(&hdr_helix, &cxt_helix);
    pvr_prim(&hdr_helix, sizeof(pvr_poly_hdr_t));	
				
    plx_mat3d_identity();                // Reset The Modelview Matrix
    plx_mat3d_lookat(&eye,&center,&up);  // Eye Position (0,5,50) Center Of Scene (0,0,0), Up On Y Axis
    
    plx_mat3d_push();   // Push The Modelview Matrix
    
    plx_mat3d_translate(0.0f, 0.0f, -50.0f);        // Move 50 units into the screen
    plx_mat3d_rotate(angle/2.0f, 1.0f, 0.0f, 0.0f); // Rotate the quad 45 degrees on the Z-axis
    plx_mat3d_rotate(angle/3.0f, 0.0f, 1.0f, 0.0f); // Rotate the quad cnt1*30.0f degress on the X&Y-Axis
    
    /* "Applying" all matrixs */
    plx_mat3d_apply_all();
	
	r = 1.5f;    // Radius
	plx_dr_init(&dr_state);   // Initialize a state variable for Direct Rendering

	for(phi=0; phi <= 360; phi+=20.0)							// 360 Degrees In Steps Of 20
	{
		for(theta = 0; theta <= 360*twists; theta += 20.0)		// 360 Degrees * Number Of Twists In Steps Of 20
		{
			v = (phi/180.0f*3.142f);							// Calculate Angle Of First Point	(  0 )
			u = (theta/180.0f*3.142f);							// Calculate Angle Of First Point	(  0 )

			x = (float)(fcos(u)*(2.0f+fcos(v) ))*r;				// Calculate x Position (1st Point)
			y = (float)(fsin(u)*(2.0f+fcos(v) ))*r;				// Calculate y Position (1st Point)
			z = (float)((( u-(2.0f*3.142f)) + fsin(v) ) * r);	// Calculate z Position (1st Point)

			vertexes[0][0]=x;									// Set x Value Of First Vertex
			vertexes[0][1]=y;									// Set y Value Of First Vertex
			vertexes[0][2]=z;									// Set z Value Of First Vertex

			v = (phi/180.0f*3.142f);							// Calculate Angle Of Second Point	(  0 )
			u = ((theta+20)/180.0f*3.142f);						// Calculate Angle Of Second Point	( 20 )

			x = (float)(fcos(u)*(2.0f+fcos(v) ))*r;				// Calculate x Position (2nd Point)
			y = (float)(fsin(u)*(2.0f+fcos(v) ))*r;				// Calculate y Position (2nd Point)
			z = (float)((( u-(2.0f*3.142f)) + fsin(v) ) * r);	// Calculate z Position (2nd Point)

			vertexes[1][0]=x;									// Set x Value Of Second Vertex
			vertexes[1][1]=y;									// Set y Value Of Second Vertex
			vertexes[1][2]=z;									// Set z Value Of Second Vertex

			v = ((phi+20)/180.0f*3.142f);						// Calculate Angle Of Third Point	( 20 )
			u = ((theta+20)/180.0f*3.142f);						// Calculate Angle Of Third Point	( 20 )

			x = (float)(fcos(u)*(2.0f+fcos(v) ))*r;				// Calculate x Position (3rd Point)
			y = (float)(fsin(u)*(2.0f+fcos(v) ))*r;				// Calculate y Position (3rd Point)
			z = (float)((( u-(2.0f*3.142f)) + fsin(v) ) * r);		// Calculate z Position (3rd Point)

			vertexes[2][0]=x;									// Set x Value Of Third Vertex
			vertexes[2][1]=y;									// Set y Value Of Third Vertex
			vertexes[2][2]=z;									// Set z Value Of Third Vertex

			v = ((phi+20)/180.0f*3.142f);						// Calculate Angle Of Fourth Point	( 20 )
			u = ((theta)/180.0f*3.142f);						// Calculate Angle Of Fourth Point	(  0 )

			x = (float)(fcos(u)*(2.0f+fcos(v) ))*r;				// Calculate x Position (4th Point)
			y = (float)(fsin(u)*(2.0f+fcos(v) ))*r;				// Calculate y Position (4th Point)
			z = (float)((( u-(2.0f*3.142f)) + fsin(v) ) * r);		// Calculate z Position (4th Point)

			vertexes[3][0]=x;									// Set x Value Of Fourth Vertex
			vertexes[3][1]=y;									// Set y Value Of Fourth Vertex
			vertexes[3][2]=z;									// Set z Value Of Fourth Vertex

			// Render The Quad
			plx_vert_indm3(&dr_state, PLX_VERT, vertexes[0][0], vertexes[0][1], vertexes[0][2], color);
            plx_vert_indm3(&dr_state, PLX_VERT, vertexes[1][0], vertexes[1][1], vertexes[1][2], color);
	        plx_vert_indm3(&dr_state, PLX_VERT, vertexes[2][0], vertexes[2][1], vertexes[2][2], color);
	        plx_vert_indm3(&dr_state, PLX_VERT_EOS, vertexes[3][0], vertexes[3][1], vertexes[3][2], color);
	
		}
	}
	angle += 8.0f;
	plx_mat3d_pop();	// Pop The Matrix
}

void ViewOrtho() {		// Set Up An Ortho View

    plx_mat3d_mode(PLX_MAT_PROJECTION);
    plx_mat3d_push();
    plx_mat3d_identity();
    plx_mat3d_ortho( 0, 640 , 480 , 0, -1, 1 );	// Select Ortho Mode (640x480)
    plx_mat3d_mode(PLX_MAT_MODELVIEW); 
    plx_mat3d_push();
    plx_mat3d_identity();
}

void ViewPerspective() {				// Set Up A Perspective View

    plx_mat3d_mode(PLX_MAT_PROJECTION); // Select Projection
    plx_mat3d_pop();                    // Pop The Matrix
    plx_mat3d_mode(PLX_MAT_MODELVIEW);  // Select Modelview
    plx_mat3d_pop();                    // Pop The Matrix
}

void RenderToTexture() { 				// Renders To A Texture    
    
    /* Sets the background color to Medium Blue */
	pvr_set_bg_color(0.0f, 0.0f, 0.5f);   
	pvr_scene_begin_txr(BlurTexture.ptr, &tx_x, &tx_y);
	pvr_list_begin(PVR_LIST_OP_POLY);
	ProcessHelix();	                    // Render The Helix onto the texture	
    pvr_list_finish();
	pvr_scene_finish(); 	
    									
}

void DrawBlur(int times, float inc)								// Draw The Blurred Image
{
    int num; 
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alphainc = 0.9f / times;								// Fade Speed For Alpha Blending
	float alpha = 0.2f;		                                    // Starting Alpha Value
    uint32 color = 0;									

    pvr_prim(&BlurTexture.hdr_trans, sizeof(pvr_poly_hdr_t));
	ViewOrtho();												// Switch To An Ortho View

	alphainc = alpha / times;	// alphainc=0.2f / Times To Render Blur
    
    plx_dr_init(&dr_state);   // Initialize a state variable for Direct Rendering
    
		// Begin Drawing Quads
		for (num = 0;num < times;num++)						// Number Of Times To Render Blur
		{
			color = plx_pack_color(alpha, 1.0f, 1.0f, 1.0f); 
			
			plx_vert_ifd(&dr_state, PLX_VERT, 0.0f, 512.0f, 1.0f, color, 0.0f+spost, 1.0f-spost);      
			plx_vert_ifd(&dr_state, PLX_VERT, 0.0f, 0.0f, 1.0f, color, 0.0f+spost, 0.0f+spost);        
			plx_vert_ifd(&dr_state, PLX_VERT, 1024.0f, 512.0f , 1.0f, color, 1.0f-spost, 1.0f-spost );    
			plx_vert_ifd(&dr_state, PLX_VERT_EOS, 1024.0f, 0.0f , 1.0f, color, 1.0f-spost, 0.0f+spost); 
			
			spost += inc;								// Gradually Increase spost (Zooming Closer To Texture Center)
			alpha = alpha - alphainc;					// Gradually Decrease alpha (Gradually Fading Image Out)
		}												

	ViewPerspective();	   // Switch To A Perspective View
}

void Draw (void)	       // Draw The Scene
{
    pvr_wait_ready();
	plx_mat3d_identity();  // Reset The Modelview Matrix											
	RenderToTexture();	   // Render To A Texture
    
    pvr_wait_ready();
    pvr_scene_begin();
    pvr_list_begin(PVR_LIST_OP_POLY); 
    ProcessHelix();		   // Draw Our Helix
	pvr_list_finish();
	pvr_list_begin(PVR_LIST_TR_POLY);
	pvr_prim(&BlurTexture.hdr_trans, sizeof(pvr_poly_hdr_t));
	DrawBlur(13,0.02f);	   // Draw The Blur Effect
	pvr_list_finish();
	pvr_scene_finish();   
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
    
    EmptyTexture();
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(50.0f, 640.0f / 480.0f, 0.1f, 2000.0f);  // (float angle, float aspect, float znear, float zfar);
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
                 
	    Draw();   
    }
    // Clean Up!!!
    plx_txr_destroy(&BlurTexture);
   
	return 0;
}








