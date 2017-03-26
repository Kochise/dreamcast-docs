/* KallistiOS ##version##

   nehe09.c
   (c)2001 Benoit Miller

   Parts (c)2000 Jeff Molofee
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

/* Simple KGL example to demonstrate texturing. 

   Essentially the same thing as NeHe's lesson06 code.
   To learn more, go to http://nehe.gamedev.net/.
*/

#define NUM_STARS 50		/* Number Of Stars To Draw */

typedef struct			/* Create A Structure For Star */
{
	int r, g, b;		/* Stars Color */
	GLfloat dist,		/* Stars Distance From Center */
		angle;  	/* Stars Current Angle */
} stars;
static stars star[NUM_STARS];	/* Need To Keep Track Of 'NUM_STARS' Stars */

static GLboolean twinkle;	/* Twinkling Stars */

static GLfloat zoom=-15.0f;	/* Distance Away From Stars */
static GLfloat tilt=90.0f;	/* Tilt The View */
static GLfloat spin;		/* Spin Stars */

static GLuint loop;		/* General Loop Variable */
static GLuint texture[1];	/* Storage For One textures */

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
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	for (loop=0; loop<NUM_STARS; loop++) {
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,zoom);
		glRotatef(tilt,1.0f,0.0f,0.0f);
		glRotatef(star[loop].angle,0.0f,1.0f,0.0f);
		glTranslatef(star[loop].dist,0.0f,0.0f);
		glRotatef(-star[loop].angle,0.0f,1.0f,0.0f);
		glRotatef(-tilt,1.0f,0.0f,0.0f);
		
		if (twinkle)
		{
			glColor4ub(star[(NUM_STARS-loop)-1].r,star[(NUM_STARS-loop)-1].g,star[(NUM_STARS-loop)-1].b,255);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		}

		glRotatef(spin,0.0f,0.0f,1.0f);
		glColor4ub(star[loop].r,star[loop].g,star[loop].b,255);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

		spin+=0.01f;
		star[loop].angle+=(float)(loop)/NUM_STARS;
		star[loop].dist-=0.01f;
		if (star[loop].dist<0.0f)
		{
			star[loop].dist+=5.0f;
			star[loop].r=rand()%256;
			star[loop].g=rand()%256;
			star[loop].b=rand()%256;
		}
	}
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
	GLboolean yp = GL_FALSE;

	/* Initialize KOS */
        pvr_init(&params);

	printf("nehe09 beginning\n");

	/* Get basic stuff initialized */
	glKosInit();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glEnable(GL_BLEND);

	for (loop=0; loop<NUM_STARS; loop++)
	{
		star[loop].angle=0.0f;
		star[loop].dist=((float)(loop)/NUM_STARS)*5.0f;
		star[loop].r=rand()%256;
		star[loop].g=rand()%256;
		star[loop].b=rand()%256;
	}

	/* Set up the texture */
	loadtxr("/rd/Star.pcx", &texture[0]);

	c = maple_first_controller();
	while(1) {
		/* Check key status */
		if (cont_get_cond(c, &cond) < 0) {
			printf("Error reading controller\n");
			break;
		}
		if (!(cond.buttons & CONT_START))
			break;
		if (!(cond.buttons & CONT_DPAD_UP))
			tilt -= 0.5f;
		if (!(cond.buttons & CONT_DPAD_DOWN))
			tilt += 0.5f;
		if (!(cond.buttons & CONT_A))
			zoom -= 0.2f;
		if (!(cond.buttons & CONT_B))
			zoom += 0.2f;
		if (!(cond.buttons & CONT_Y) && !yp) {
			yp = GL_TRUE;
			twinkle = !twinkle;
		}
		if (cond.buttons & CONT_Y)
			yp = GL_FALSE;

		/* Begin frame */
		glKosBeginFrame();

		/* Switch to blended polygon list */
		glKosFinishList();

		/* Draw the GL "scene" */
		draw_gl();

		/* Finish the frame */
		glKosFinishFrame();
	}

	return 0;
}


