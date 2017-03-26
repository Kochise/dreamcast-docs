/* KallistiOS ##version##

   vq-example.c

   This is a modified nehe06.c that shows the capabilities of
   VQ compression. Original code (c)2001 Benoit Miller
   Modified version (c)2002 Gil Megidish
   
   Texture is copyright (c)2002 Mayang Murni Adnin; for more
   incredible textures, go to www.mayang.com
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

GLfloat xrot;	/* X Rotation */
GLfloat yrot;	/* Y Rotation */
GLfloat zrot;	/* Z Rotation */

GLuint texture[1];	

/* external vq-texture storage */
extern unsigned char fruit[];
extern unsigned char fruit_end[];

/* Load a texture and glKosTex2D */
static int loadtxr() {
	GLuint size;
	pvr_ptr_t txaddr;

	size = fruit_end - fruit;
	txaddr = pvr_mem_malloc(size);
	if (txaddr == NULL)
		return -1;

	/* all writes to vram must be 16/32 bit */
	memcpy2(txaddr, fruit, size);	

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glKosTex2D(GL_RGB565_TWID | GL_VQ_ENABLE, 512, 512, txaddr);
	return 0;
}

void draw_gl(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	glBegin(GL_QUADS);
		
		/* Front Face */
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

		/* Back Face */
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

		/* Top Face */
		glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

		/* Bottom Face */
		glColor3f(1.0f, 0.0f, 0.0f); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

		/* Right face */
		glColor3f(0.0f, 1.0f, 0.0f); glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glColor3f(0.3f, 0.5f, 1.0f); glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glColor3f(1.0f, 0.3f, 0.5f); glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glColor3f(0.5f, 0.5f, 0.5f); glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

		/* Left Face */
		glColor3f(1.0f, 0.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(1.0f, 1.0f, 0.0f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glColor3f(0.0f, 1.0f, 1.0f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

	glEnd();

	xrot+=0.3f;
	yrot+=0.2f;
	zrot+=0.4f;
}

int main(int argc, char **argv) {
	cont_cond_t cond;
	uint8	c;
	
	/* Initialize KOS */
	pvr_init_defaults();

	/* Get basic stuff initialized */
	glKosInit();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 640.0f/480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	/* Set up the texture */
	if (loadtxr() < 0) { 
		printf("loadtxr() failed\n");
		return 0;
	}

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

		/* Draw the GL "scene" */
		draw_gl();

		/* Finish the frame */
		glKosFinishFrame();
	}

	return 0;
}
