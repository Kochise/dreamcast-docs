/* KallistiOS ##version##

   scissor.c
   (c)2002 Paul Boese

   Demonstrates the use of glScissor( ) using both the normal
   GL_SCISSOR_TEST and GL_KOS_USERCLIP_OUTSIDE clip modes.

   Use the 'A' button to cycle though the following demos.
   Use the 'DPAD' to move the clip rectangle in the first two demos.
   Demos:
   	GL_SCISSOR_TEST
	GL_KOS_USERCLIP_OUTSIDE
	DISABLE glScissor
	4 viewports not clipped
	4 viewports clipped

*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

CVSID("$Id: scissor.c,v 1.4 2002/06/30 16:28:34 axlen Exp $");

#define NUM_DEMOS 5
enum { USERCLIP_INSIDE = 0, USERCLIP_OUTSIDE, USERCLIP_DISABLED,
	QUAD_SCREEN_UNCLIPPED, QUAD_SCREEN_CLIPPED };
static char demo[NUM_DEMOS][80] = {
	{ "glEnable( GL_SCISSOR_TEST )" },
	{ "glEnable( GL_KOS_USERCLIP_OUTSIDE )" },
	{ "glDisable( GL_SCISSOR_TEST )" },
	{ "Four viewports >>> no clipping <<<" },
	{ "Four viewports >>> clipped <<<" }
};
static int selected = USERCLIP_INSIDE;
static GLint x = 0, y = 0;
static GLfloat rot = 0.0f;
static GLfloat rtri = 0.0f, rquad = 0.0f;
static GLuint texture;

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

void rect(int x, int y, int width, int height) {
	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x,y,0);
	glTexCoord2f(4.0f, 0.0f);
	glVertex3f(x+width,y,0);
	glTexCoord2f(4.0f, 4.0f);
	glVertex3f(x+width,y+height,0);
	glTexCoord2f(0.0f, 4.0f);
	glVertex3f(x,y+height,0);
	glEnd();
}

static void draw_gl(float rot, float x, float y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(rot, x, y, 0.0f);

	glPushMatrix();
	glTranslatef(-1.5f,0.0f,0.0);
	glRotatef(rtri,0.0f,1.0f,0.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f, -1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.5f,0.0f,0.0f);
	glRotatef(rquad,1.0f,1.0f,1.0f);
		
	glBegin(GL_QUADS);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glColor3f(1.0f,0.5f,0.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
	glEnd();

	glPopMatrix();
}

static void draw_ortho_scene() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0,640,0,480,-1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LESS);
	glClearColor(0.8f, 0.4f, 0.4f, 1.0f);
	
	glViewport(0, 0, 640, 480);
	glScissor(x, y, 320, 240); 
	/* draw a nice 32x32 bitsize square checkered
	   background */
	glBindTexture(GL_TEXTURE_2D, texture);
	rect(0, 0, 512, 512);
	rect(512, 0, 512, 512);
}

static void draw_perspective_scene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,320.0f/240.0f,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Draw scene - bottom left */
	glViewport(0, 0, 320, 240);
	glScissor(0, 0, 320, 240);
	draw_gl(rot, 1.0, 1.0);

	/* Draw scene - upper left */
	glScissor(0, 240, 320, 240);
	glViewport(0, 240, 320, 240);
	draw_gl(rot, -1.0f, 1.0f);

	/* Draw scene - bottom right */
	glScissor(320, 0, 320, 240);
	glViewport(320, 0, 320, 240);
	draw_gl(rot, 1.0f, -1.0f);
		
	/* Draw scene - upper right */
	glScissor(320, 240, 320, 240);
	glViewport(320, 240, 320, 240);
	draw_gl(rot, -1.0f, -1.0f);
	
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
	static GLboolean ap = GL_FALSE;

	/* Initialize KOS */
        pvr_init(&params);

	printf("texwrap beginning\n");

	/* Get basic stuff initialized */
	glKosInit();

	/* Set up the texture */
	loadtxr("/rd/checker.pcx", &texture);

	printf("\n[glScissor Demo]\n");
	printf("DPAD moves glScissor( ) defined rectangle.\n");
	printf("A button selects demo.\n");
	printf("  %s\n", demo[selected]);

	c = maple_first_controller();
	while(1) {
		/* Check key status */
		if (cont_get_cond(c, &cond) < 0) {
			printf("Error reading controller\n");
			break;
		}
		if (!(cond.buttons & CONT_START))
			break;

		if (cond.buttons & CONT_DPAD_UP)
			y-=8; if (y < -224) y = -224;
		if (cond.buttons & CONT_DPAD_DOWN)
			y+=8; if (y > 448) y = 448;
		if (cond.buttons & CONT_DPAD_LEFT)
			x+=8; if (x > 632) x = 632; 
		if (cond.buttons & CONT_DPAD_RIGHT)
			x-=8; if (x < -288) x = -288;
		
		/* Demo select button */
		if (!(cond.buttons & CONT_A) && !ap) {
			ap = GL_TRUE;
			selected++;
			selected %= NUM_DEMOS;
			printf("  %s\n", demo[selected]);
		}
		if (cond.buttons & CONT_A)
			ap = GL_FALSE;


		/* Begin frame */
		glKosBeginFrame();

		/* top row, non-alpha texture */
		glBindTexture(GL_TEXTURE_2D, texture);

		switch (selected) {
		case USERCLIP_INSIDE:
		case QUAD_SCREEN_CLIPPED:
			glEnable(GL_SCISSOR_TEST);
			break;
		case USERCLIP_OUTSIDE:
			glEnable(GL_KOS_USERCLIP_OUTSIDE);
			break;
		case USERCLIP_DISABLED:
		case QUAD_SCREEN_UNCLIPPED:
			glDisable(GL_SCISSOR_TEST);
			/* or 
			glDisable(GL_KOS_USERCLIP_OUTSIDE);
			*/
			break;
		}
		
		switch (selected) {
		case USERCLIP_INSIDE:
		case USERCLIP_OUTSIDE:
		case USERCLIP_DISABLED:
			
			draw_ortho_scene();
			
			break;
		case QUAD_SCREEN_UNCLIPPED:
		case QUAD_SCREEN_CLIPPED:
			
			draw_perspective_scene();
			
			rot += 2.0f;
			rtri += 3.0f;
			rquad += -2.5f;
			break;
		}

		/* Finish the frame */
		glKosFinishFrame();
	}

	return 0;
}


