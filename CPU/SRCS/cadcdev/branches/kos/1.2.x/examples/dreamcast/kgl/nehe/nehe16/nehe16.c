/* KallistiOS ##version##

   nehe16.c
   (c)2001 Paul Boese

   Parts (c)2000 Tom Stanis/Jeff Molofee/Benoit Miller
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

/* Simple GL example to demonstrate fog (PVR table fog).

   Essentially the same thing as NeHe's lesson16 code.
   To learn more, go to http://nehe.gamedev.net/.

   There is no lighting yet in GL, so it has not been included.

   DPAD controls the cube rotation, button A & B control the depth
   of the cube, button X toggles fog on/off, and button Y toggles fog type. 
*/

static GLfloat xrot;		/* X Rotation */
static GLfloat yrot;		/* Y Rotation */
static GLfloat xspeed;		/* X Rotation Speed */
static GLfloat yspeed;		/* Y Rotation Speed */
static GLfloat z=-5.0f;		/* Depth Into The Screen */

static GLuint  texture;	        /* Storage For Texture */

/* Storage For Three Types Of Fog */
GLuint fogType = 0; /* use GL_EXP initially */
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };
char cfogMode[3][10] = {"GL_EXP   ", "GL_EXP2  ", "GL_LINEAR" };
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; /* Fog Color */
int fog = GL_TRUE;


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

void draw_gl(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,z);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		/* Front Face */
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		/* Back Face */
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		/* Top Face */
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		/* Bottom Face */
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		/* Right face */
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		/* Left Face */
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	xrot+=xspeed;
	yrot+=yspeed;
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
	GLboolean xp = GL_FALSE;
	GLboolean yp = GL_FALSE;
	GLboolean ap = GL_FALSE;
	GLboolean bp = GL_FALSE;
	GLboolean blend = GL_FALSE;

	/* Initialize KOS */
        pvr_init(&params);

	printf("nehe16 beginning\n");

	/* Get basic stuff initialized */
	glKosInit();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	/* Set up the fog */
	glFogi( GL_FOG_MODE, fogMode[fogType] );   /* Fog Mode */
	glFogfv( GL_FOG_COLOR, fogColor );         /* Set Fog Color */
	glFogf (GL_FOG_DENSITY, 0.35f );           /* How Dense The Fog is */
	glHint( GL_FOG_HINT, GL_DONT_CARE );       /* Fog Hint Value */
	glFogf( GL_FOG_START, 0.0f );              /* Fog Start Depth */
	glFogf( GL_FOG_END, 5.0f );                /* Fog End Depth */
	glEnable( GL_FOG );                        /* Enables GL_FOG */

	/* Set up the textures */
	loadtxr("/rd/crate.pcx", &texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);

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
			if (z >= -15.0f) z -= 0.02f;
		}
		if (!(cond.buttons & CONT_B)) {
			if (z <= 0.0f) z += 0.02f;
		}
		if (!(cond.buttons & CONT_X) && !xp) {
			xp = GL_TRUE;
	    		fogType = ( ++fogType ) % 3;
	    		glFogi( GL_FOG_MODE, fogMode[fogType] );
	    		printf("%s\n", cfogMode[fogType]);
		}
		if (cond.buttons & CONT_X)
			xp = GL_FALSE;
		if (!(cond.buttons & CONT_Y) && !yp) {
			yp = GL_TRUE;
			fog = !fog;
		}
		if (cond.buttons & CONT_Y)
			yp = GL_FALSE;
		if (!(cond.buttons & CONT_DPAD_UP))
			xspeed -= 0.01f;
		if (!(cond.buttons & CONT_DPAD_DOWN))
			xspeed += 0.01f;
		if (!(cond.buttons & CONT_DPAD_LEFT))
			yspeed -= 0.01f;
		if (!(cond.buttons & CONT_DPAD_RIGHT))
			yspeed += 0.01f;

		/* Begin frame */
		glKosBeginFrame();

		/* Switch fog off/on */
		if (fog) {
			glEnable(GL_FOG);
		} else {
			glDisable(GL_FOG);
		}

		/* Draw the GL "scene" */
		draw_gl();

		/* Finish the frame */
		glKosFinishFrame();
	}
	return 0;
}


