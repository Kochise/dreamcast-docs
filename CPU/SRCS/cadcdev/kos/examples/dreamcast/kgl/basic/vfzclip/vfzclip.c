/* KallistiOS ##version##

   vfzclip.c
   (c)2001, 2002 Trilinear@hotmail.com, Paul Boese
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pcx/pcx.h>

#define SDIFF 0.001f

#define true (1 == 1)
#define false (1 == 0)

CVSID("$Id");

/*
    A demonstration of Trilinear's NEAR-Z-Clipper that has been
    incorporated into KGL. Use the joystick to rotate the view, the D-Pad
    to move forward and back, and the A button to toggle the Z-Clipper
    on or off. Please note that the code only works with GL_TRIANGLES.

    Thanks to NeHe's tutorials for the crate image.
*/

void quad() {
	float x=-1.0f;
	float y=-1.0f;

	float incr=2.0f;


	glBegin(GL_TRIANGLES);


	while (x<=1.0f-incr) {
		while (y<=1.0f-incr) {
			/* Front face */
			glTexCoord2f(1.0f-SDIFF,0.0f+SDIFF);
			glVertex3f(x,  y+incr,     0.0f);
			glTexCoord2f(0.0f+SDIFF,0.0f+SDIFF);
			glVertex3f(x+incr, y+incr, 0.0f);
			glTexCoord2f(0.0f+SDIFF,1.0f-SDIFF);
			glVertex3f(x+incr, y, 0.0f);

			glTexCoord2f(1.0f-SDIFF,0.0f+SDIFF);
			glVertex3f(x, y+incr,      0.0f);
			glTexCoord2f(0.0f+SDIFF,1.0f-SDIFF);
			glVertex3f(x+incr, y, 0.0f);
			glTexCoord2f(1.0f-SDIFF,1.0f-SDIFF);
			glVertex3f(x, y,      0.0f);
			y+=incr;
		}
		y=-1.0f;
		x+=incr;
	}
	glEnd();
}

void cube() {

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f,1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
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

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	maple_device_t * caddr;
	cont_state_t * cont;
	GLuint	texture;
	float	z = -1.0f;
	float	rx = 0.0f;
	float	ry = 0.0f;
	int	zclip = true;
	int	a_pressed = false;

	/* Normal init */
	pvr_init_defaults();

	/* Get KGL stuff initialized */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);

	/* Expect CW verts */
	glFrontFace(GL_CW);

	/* Load a texture and make to look nice */
	loadtxr("/rd/crate.pcx", &texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);

	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

	while(1) {
		/* Check controller/key status */
		if ((caddr = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) == NULL)
			break;
		
		cont = (cont_state_t *)maple_dev_status(caddr);
		if ((cont->buttons & CONT_START))
			break;
		
		if ((cont->buttons & CONT_DPAD_UP))
			z -= 0.3f;
		if ((cont->buttons & CONT_DPAD_DOWN))
			z += 0.3f;
		if ((cont->buttons & CONT_A) && !a_pressed) {
			a_pressed = true;
			zclip = !zclip;
		}
		if (!(cont->buttons & CONT_A))
			a_pressed = false;
		
		rx+=((float)cont->joyy)/100.0f;
		ry+=((float)cont->joyx)/100.0f;

		/* Begin frame */
		glKosBeginFrame();

		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -50-z);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(rx, 1.0f, 0.0f, 0.0f);
		glRotatef(ry, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, texture);
		glScalef(50.0f, 50.0f, 50.0f);
		glTranslatef(0.0f, 0.0f, 0.75f);

		if (zclip) glEnable(GL_KOS_NEARZ_CLIPPING);
		cube();
		glDisable(GL_KOS_NEARZ_CLIPPING);

		glPopMatrix();
		
		/* Finish the frame */
		glKosFinishFrame();
	}
	return 0;
}


