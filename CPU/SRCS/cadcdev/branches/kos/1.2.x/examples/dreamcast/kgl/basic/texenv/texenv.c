/* KallistiOS ##version##

   texenv.c
   (c)2001 Benoit Miller
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>
#include <tga/tga.h>

/* Really simple KGL example to demonstrate the various glTexEnv modes. 

   The top row shows what happens with a texture without any alpha 
   components (RGB565 in this case). The bottom row shows the same thing
   but with a texture that includes alpha information (ARGB4444).

   Press button A to toggle alpha blending on/off, start to quit.
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

void loadtxr_tga(const char *fn, GLuint *txr) {
	kos_img_t img;
	pvr_ptr_t txaddr;

	if (tga_to_img(fn, &img) < 0) {
		printf("can't load %s\n", fn);
		return;
	}

	txaddr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
	kos_img_free(&img, 0);

	glGenTextures(1, txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	glKosTex2D(GL_ARGB4444_TWID, img.w, img.h, txaddr);
}

void quad(int x, int y) {
	glBegin(GL_QUADS);
	glColor4f(1,0,0,0.75);
	glVertex3f(x,y,0);
	glColor4f(0,1,0,0.75);
	glVertex3f(x+150,y,0);
	glColor4f(0,0,1,0.75);
	glVertex3f(x+150,y+150,0);
	glColor4f(1,1,1,0.75);
	glVertex3f(x,y+150,0);
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
	int     trans = 0;
	GLuint	texture1, texture2, texture3;

	/* Initialize KOS */
        pvr_init(&params);

	printf("texenv beginning\n");

	/* Get basic stuff initialized */
	glKosInit();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,640,0,480,0,-1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	/* Set up the textures */
	loadtxr("/rd/checker.pcx", &texture1);
	loadtxr("/rd/crate.pcx", &texture2);
	loadtxr_tga("/rd/kgl.tga", &texture3);

	c = maple_first_controller();
	while(1) {
		/* Check key status */
		if (cont_get_cond(c, &cond) < 0) {
			printf("Error reading controller\n");
			break;
		}
		if (!(cond.buttons & CONT_START))
			break;
		if (!(cond.buttons & CONT_A)) {
			/* This weird logic is to avoid bouncing back
			   and forth before the user lets go of the
			   button. */
			if (!(trans & 0x1000)) {
				if (trans == 0)
					trans = 0x1001;
				else
					trans = 0x1000;
			}
		} else {
			trans &= ~0x1000;
		}

		/* Begin frame */
		glKosBeginFrame();

		glDisable(GL_KOS_AUTO_UV);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor4f(0,0,0,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0);
		glTexCoord2f(20,0);
		glVertex3f(640,0,0);
		glTexCoord2f(20,15);
		glVertex3f(640,480,0);
		glTexCoord2f(0,15);
		glVertex3f(0,480,0);
		glEnd();

		if (trans & 1) {
			glKosFinishList();
		}

		/* top row, non-alpha texture */
		glEnable(GL_KOS_AUTO_UV);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		quad(5,250);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		quad(165,250);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
		quad(325,250);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATEALPHA);
		quad(485,250);

		/* bottom row, alpha texture */
		glBindTexture(GL_TEXTURE_2D, texture3);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		quad(5,50);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		quad(165,50);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
		quad(325,50);

		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATEALPHA);
		quad(485,50);

		/* Finish the frame */
		glKosFinishFrame();
	}

	return 0;
}


