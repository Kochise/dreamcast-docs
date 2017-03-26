/* KallistiOS ##version##

   gltest.c
   (c)2001 Dan Potter
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

/*

This is a really simple KallistiGL example. It shows off several things:
basic matrix control, perspective, the AUTO_UV feature, and controlling
the image with maple input.

Thanks to NeHe's tutorials for the crate image.

*/

/* Draw a cube centered around 0,0,0. Note the total lack of glTexCoord2f(),
   even though the cube is in fact getting textured! This is KGL's AUTO_UV
   feature: turn it on and it assumes you're putting on the texture on
   the quad in the order 0,0; 1,0; 1,1; 0,1. This only works for quads. */
void cube(float r) {
	glRotatef(r, 1.0f, 0.0f, 1.0f);
	
	glBegin(GL_QUADS);

		/* Front face */
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		/* Back face */
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
			
		/* Left face */
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		/* Right face */
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		/* Top face */
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		/* Bottom face */
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
}

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
	float	r = 0.0f;
	float	dr = 2;
	float	z = -14.0f;
	GLuint	texture;
	GLuint  dummy;
	int	trans = 0;
	pvr_stats_t	stats;

	/* Initialize KOS */

	/* Use this to test other video modes */
	/* vid_init(DM_320x240, PM_RGB565); */

	/* Normal init */
	pvr_init(&params);

	printf("gltest beginning\n");

	/* Get basic stuff initialized */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);

	/* Expect CW verts */
	glFrontFace(GL_CW);

        /* Enable Transparancy */
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/* Load a texture and make to look nice */
	loadtxr("/rd/crate.pcx", &texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATEALPHA);

	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

	while(1) {
		/* Check key status */
		c = maple_first_controller();
		if (c) {
			if (cont_get_cond(c, &cond) < 0) {
				printf("Error reading controller\n");
			}
			if (!(cond.buttons & CONT_START))
				break;
			if (!(cond.buttons & CONT_DPAD_UP))
				z -= 0.1f;
			if (!(cond.buttons & CONT_DPAD_DOWN))
				z += 0.1f;
			if (!(cond.buttons & CONT_DPAD_LEFT)) {
				/* If manual rotation is requested, then stop
				   the automated rotation */
				dr = 0.0f;
				r -= 2.0f;
			}
			if (!(cond.buttons & CONT_DPAD_RIGHT)) {
				dr = 0.0f;
				r += 2.0f;
			}
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
		}

		r += dr;

		/* Begin frame */
		glKosBeginFrame();

		/* Draw four cubes */
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, z);
		glRotatef(r, 0.0f, 1.0f, 0.5f);
		glPushMatrix();
		
		glTranslatef(-5.0f, 0.0f, 0.0f);
		cube(r);

		glPopMatrix();
		glPushMatrix();
		glTranslatef(5.0f, 0.0f, 0.0f);
		cube(r);

		/* Potentially do two as translucent */
		if (trans & 1) {
			glKosFinishList();
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glDisable(GL_CULL_FACE);
		}

		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 5.0f, 0.0f);
		cube(r);

		glPopMatrix();
		glTranslatef(0.0f, -5.0f, 0.0f);
		cube(r);

		if (trans & 1) {
		        glEnable(GL_CULL_FACE);
		}

		/* Finish the frame */
		glKosFinishFrame();
	}

	pvr_get_stats(&stats);
	printf("VBL Count: %d, last_time: %f, frame rate: %f fps\n",
		stats.vbl_count, stats.frame_last_time, stats.frame_rate);

	return 0;
}


