/* KallistiOS ##version##

   texwrap.c
   (c)2002 Paul Boese
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

CVSID("$Id: texwrap.c,v 1.2 2002/04/07 02:54:04 bardtx Exp $");

/* Really simple KGL example to demonstrate the glTexParameter
   texture wrapping modes. 

   A Picture is worth a thousand words...
   
   | top row
   | |---------  |---------  |--------   |--------  |
   | |S Repeat|  |S Clamp |  |S Repeat|  |S Clamp | |
   | |T Repeat|  |T Repeat|  |T Clamp |  |T Clamp | |
   | |        |  |        |  |        |  |        | |
   | ---------|  ---------|  ---------|  ---------| |
   |        
   | bottom row
   | ...Same only transparent
   |

   To see the effects of wrapping you must use S T values greater than
   [0,1]. In this exmaple we are using 4x4 checkered pattern that is
   repeated 4 times. That is the S T (U, V) texture coordinates used
   are [0,4]. 

   e.g.:
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
	glTexCoord2f(4.0f, 0.0f); glVertex3f(1,0,0);
	glTexCoord2f(4.0f, 4.0f); glVertex3f(1,1,0);
	glTexCoord2f(0.0f, 4.0f); glVertex3f(0,1,0);
   
   Press start to quit.
*/

/* Load a texture using pcx_load_texture and glKosTex2D */
void loadtxr(const char *fn, GLuint *txr) {
	kos_img_t img;
	pvr_ptr_t txaddr;

	if (pcx_to_img(fn, &img) < 0) {
		printf("can't load %s\n", fn);
		return;
	}

	txaddr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
	kos_img_free(&img, 0);

	glGenTextures(1, txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
}

void quad(int x, int y) {
	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x,y,0);
	glTexCoord2f(4.0f, 0.0f);
	glVertex3f(x+128,y,0);
	glTexCoord2f(4.0f, 4.0f);
	glVertex3f(x+128,y+128,0);
	glTexCoord2f(0.0f, 4.0f);
	glVertex3f(x,y+128,0);
	glEnd();
}

pvr_init_params_t params = {
        /* Enable opaque and translucent polygons with size 16 */
        { PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },

        /* Vertex buffer size 512K */
        512*1024
};

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	cont_cond_t cond;
	uint8	c;
	GLuint	texture;

	/* Initialize KOS */
        pvr_init(&params);

	printf("texwrap beginning\n");

	/* Get basic stuff initialized */
	glKosInit();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,640,0,480,0,-1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	/* Set up the textures */
	loadtxr("/rd/checker.pcx", &texture);

	glClearColor(0.4f, 0.4f, 0.8f, 1.0f);

	c = maple_first_controller();
	while(1) {
		/* Check key status */
		if (cont_get_cond(c, &cond) < 0) {
			printf("Error reading controller\n");
			break;
		}
		if (!(cond.buttons & CONT_START))
			break;

		/* Begin frame */
		glKosBeginFrame();

		/* top row, non-alpha texture */
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		quad(16,275);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		quad(176,275);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		quad(336,275);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		quad(496,275);
		
		/* bottom row, alpha texture */
		glKosFinishList();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		quad(16,75);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		quad(176,75);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		quad(336,75);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		quad(496,75);

		/* Finish the frame */
		glKosFinishFrame();
	}

	return 0;
}


