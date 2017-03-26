/* sidc.cc
** Space Invaders DC - Test Code
** (c)2001 Paul Boese
** Major portions of code taken from Kallistios examples.
*/

#include "headers.h"
extern "C" {
	#include "text.h"
}
#include "enn.h"
#include "xxx.h"
#include "stars.h"
#include "TDObject.h"

/* Load a texture using pcx_load_texture and glKosTex2D */
void loadtxr(const char *fn, GLuint *txr) {
	uint32 txaddr;
	int w, h;
	if (pcx_load_texture(fn, 1, 0, &txaddr, &w, &h) < 0) {
		printf("can't load %s\n", fn);
		return;
	}

	glGenTextures(1, txr);
	glBindTexture(GL_TEXTURE_2D, *txr);
	glKosTex2D(GL_RGB565_TWID, w, h, txaddr);
}

void fleet(float r, TDObject* obj) {
	float x, y, z, c;

	for(z=-2.0f; z<=2.0f; z+=1.0f) {
		for(x=-2.0f; x<=2.0f; x+=2.0f) {
			for(y=-2.0f; y<=2.0f; y+=2.0f) {
				if (x != y != z) {
					glPushMatrix();
					glTranslatef(x*3, y*3, z*6);
					glRotatef(r, 0.0f, 0.0f, 2.0f);
					//glScalef(0.4f, 0.4f, 0.4f);
					c = ((z+2)/5)+ 0.2f;
					obj->setColor(c, c, c);
					obj->draw();
					glPopMatrix();
				}
			}
		}
	}
}

static int fps_count = 0;
static char fps[64];

void thd_fps(void *v) {
	while(1) {
		thd_sleep(1000);
		sprintf(fps, "%3d fps", fps_count);
		fps_count = 0;
	}
}

extern uint8 romdisk[];
int main(void) {
	uint8 c;
	cont_cond_t cond;
	int fx = 0; int fy = 0; int cx, cy;
	int rz = 0; int clz, crz;
	float r = 0.0f;
	float dr = 2 * F_PI /120.0f;
	float z = -24.0f;
	
	/* Initialize KOS */
	printf("[sidc] Kos Initialing\n");

	kos_init_all(THD_ENABLE | TA_ENABLE, romdisk);

	printf("[sidc] glKos Initialing\n");

	/* Get basic stuff initialized */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(30.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	gluPerspective(30.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	printf("[sidc] Loading Textures and 3D Objects\n");

	// something is amis when I use the Text module. the first
	// texture is getting trashed.  just load it twice for now.
	GLuint tex_enn, tex_xxx, tex_dummy, tex_stars;
	loadtxr("/rd/xxx.pcx", &tex_dummy);
	Xxx dummy(tex_dummy);
	
	loadtxr("/rd/xxx.pcx", &tex_xxx);
	Xxx xxx(tex_xxx);

	loadtxr("/rd/enn.pcx", &tex_enn);
	Enn enn(tex_enn);
	
	loadtxr("/rd/0121w.pcx", &tex_stars);
	Stars stars(tex_stars);
	
	text_init();
	
	/* XXX More setup */
	thd_create(thd_fps, NULL);
	
	irq_enable();
	
	printf("[sidc] Entering main loop\n");

	/* XXX Main loop */
	c = maple_first_controller();
	while(1) {
		/* Check key status */
		if (cont_get_cond(c, &cond) < 0)
			break;
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
			r -= 2 * F_PI / 120.0f;
		}
		if (!(cond.buttons & CONT_DPAD_RIGHT)) {
			dr = 0.0f;
			r += 2 * F_PI / 120.0f;
		}

		cx = (128-cond.joyx)/20;
		cy = (128-cond.joyy)/20;
		fx += cx;
		fy += cy;
		if (fx >230) fx = 230;
		if (fx <-230) fx = -230;
		if (fy >230) fy = 230;
		if (fy <-230) fy = -230;
		
		clz = (cond.ltrig)/10;
		crz = (cond.rtrig)/10;
		rz += -clz + crz;
		
		r += dr;

		/* Begin frame */
		glKosBeginFrame();

		glLoadIdentity();

		/* Players Ship */
		glPushMatrix();
		glTranslatef(0.0f, -2.0f, -6.0f);
		glRotatef(F_PI, 0.0f, 1.0f, 0.0f);
		xxx.draw();
		glPopMatrix();

		/* Stars */
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -200.0f);
		glRotatef((float)rz/10, 0.0f, 0.0f, 0.01f);
		glScalef(200.0f, 200.0f, 20.0f);
		stars.setColor(0.5f, 0.5f, 0.5f);
		stars.draw();
		glPopMatrix();
		
		/* Fleet */	
		glTranslatef((float)fx/10.0f, (float)fy/10.0f, z);
		glRotatef((float)rz/10, 0.0f, 0.0f, 0.01f);
		fleet(r, &enn);

		glRotatef(r, 0.5f, 0.0f, 1.0f);
		xxx.draw();

		/* Finish the frame */
		//glKosFinishFrame();
		ta_commit_eol();
		font_draw_string(10,10,0.1f,0.9f,1.0f,0.9f,1.0f, fps);
		//pvr_dummy_poly(TA_TRANSLUCENT);
		ta_commit_eol();
		ta_finish_frame();
		fps_count++;
	}


	printf("[sidc] Exited main loop\n");

	return 0;
}

/* vi:tabstop=4
*/
