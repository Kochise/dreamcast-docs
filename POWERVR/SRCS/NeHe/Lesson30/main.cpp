

#include <kos.h>
#include <plx/prim.h>
#include <plx/matrix.h>
#include <plx/context.h>

#include "MilkshapeModel.h"		// Header File For Milkshape File

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

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);

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
    
    Model *pModel = NULL;	// Holds The Model Data
    float  yrot = 0.0f;		// Y Rotation
    
    /* vector_t defined in C:\cygwin\usr\local\dc\kos\kos\addons\include\kos\vector.h */
    /* Holds 3 floats */
    vector_t eye = {75.0f, 75.0f, 75.0f};
    vector_t center = {0.0f, 0.0f, 0.0f};
    vector_t up = {0.0f, 1.0f, 0.0f};
    
	/* Init PVR API */
	if (pvr_init(&params) < 0)
		return -1;
    
    printControls();
    
    /* Sets the background color to black */
	pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	/* Load the model */
	pModel = new MilkshapeModel(); 
	if ( pModel->loadModelData( "/rd/model.ms3d" ) == false )		// Loads The Model And Checks For Errors
	{
		printf("Couldn't load the model data /rd/model.ms3d \n");
		return 0;													// If Model Didn't Load Quit
	}
	
	// GET SOME 3D GOING!!
	plx_mat3d_init();                    /* Clear internal to an identity matrix */
	plx_mat3d_mode(PLX_MAT_PROJECTION);  /** Projection (frustum, screenview) matrix */
	plx_mat3d_identity();                /** Load an identity matrix */
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);  // (float angle, float aspect, float znear, float zfar);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);   /** Modelview (rotate, scale) matrix */
	
	pModel->reloadTextures();	// Loads Model Textures
	
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
		
		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_OP_POLY);
		
	    plx_mat3d_identity();
	    plx_mat3d_lookat(&eye,&center,&up);  /* Do a camera "look at" */
	    plx_mat3d_rotate(yrot, 0.0f, 1.0f, 0.0f);  /* Rotate the model by 'yrot' degrees on the Y-Axis */
  
	    /* Clear internal to an identity matrix */
	    plx_mat_identity();
	
	    /* "Apply" all matrices */
	    plx_mat3d_apply_all();
	    
	    /* Draw the Model */
	    pModel->draw();	
        
		pvr_scene_finish();
		
		yrot += 1.0f;	// Increase the 'yrot' angle
    }
    // Clean Up!!!
    pModel->destroyModel();
    
	return 0;
}

