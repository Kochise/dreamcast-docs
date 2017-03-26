/* KallistiOS ##version##

   tunnel.cpp
   (c)2002 Paul Boese
   
   Adapted from the Mesa tunnel demo by David Bucciarelli
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <kos.h>
#include <pcx/pcx.h>
#include "plprint.h"
#include "menu.h"

CVSID("$Id: tunnel.cpp,v 1.7 2003/03/09 01:20:06 bardtx Exp $");

#define DPAD_REPEAT_INTERVAL 7  /* frames */

/* tunnel */
#define NUMBLOC 11 
extern int striplength_skin_13[];
extern float stripdata_skin_13[];

extern int striplength_skin_12[];
extern float stripdata_skin_12[];

extern int striplength_skin_11[];
extern float stripdata_skin_11[];

extern int striplength_skin_9[];
extern float stripdata_skin_9[];

static float obs[3] = { 1000.0, 0.0, 2.0 };
static float dir[3];
static int velocity = 10;
static float v = 0.1;
static float alpha = 90.0;
static float beta = 90.0;

/* fog */
static float density = 0.04;
static float fogcolor[4] = { 0.7, 0.7, 0.7, 1.0 };
static float last_density = density;

/* misc state */
static int usefog = 1;
static int textog = 1;
static int cstrip = 0;
static int cullface = 0;
static int help = 1;
static int joyactive = 0;

/* texture */
static GLuint t1id, t2id;

static Menu* fm;

/* our own fmod cuz the newlib ieee32 version is broken! */
static float fmod(float x, float y) {
	int n;
	n = (int)(x/y);
	return x - (float)n*y;
}

#define FABS(n) ((((n) < 0.0) ? (-1.0*(n)) : (n)))

/*************************************************************************/

static void
drawobjs(int *l, float *f)
{
	int mend, j;

	if (cstrip) {
		float r = 0.33, g = 0.33, b = 0.33;

		for (; (*l) != 0;) {
			mend = *l++;

			r += 0.33;
			if (r > 1.0) {
				r = 0.33;
				g += 0.33;
				if (g > 1.0) {
					g = 0.33;
					b += 0.33;
					if (b > 1.0)
						b = 0.33;
				}
			}
			
			glColor3f(r, g, b);
			glBegin(GL_TRIANGLE_STRIP);
			for (j = 0; j < mend; j++) {
				f += 4;
				glTexCoord2fv(f);
				f += 2;
				glVertex3fv(f);
				f += 3;
			}
			glEnd();
		}
	}
	else
		for (; (*l) != 0;) {
			mend = *l++;
			
			glBegin(GL_TRIANGLE_STRIP);
			for (j = 0; j < mend; j++) {
				glColor4fv(f);
				f += 4;
				glTexCoord2fv(f);
				f += 2;
				glVertex3fv(f);
				f += 3;
			}
			glEnd();
		}
}

static void calcposobs(void) {
	dir[0] = fsin(alpha * F_PI / 180.0);
	dir[1] = fcos(alpha * F_PI / 180.0) * fsin(beta * F_PI / 180.0);
	dir[2] = fcos(beta * F_PI / 180.0);

	obs[0] += v * dir[0];
	obs[1] += v * dir[1];
	obs[2] += v * dir[2];
}

static void draw(void)
{
	int i;
	float base, offset;
	if (usefog & 1) {
		glEnable(GL_FOG);
	} else
		glDisable(GL_FOG);
		
	if (textog & 1) {
		glEnable(GL_TEXTURE_2D);
	} else
		glDisable(GL_TEXTURE_2D);

	if (cullface & 1) {
		glEnable(GL_CULL_FACE);
	} else
		glDisable(GL_CULL_FACE);

	glPushMatrix();
	calcposobs();
	gluLookAt(obs[0], obs[1], obs[2],
		obs[0] + dir[0], obs[1] + dir[1], obs[2] + dir[2],
		0.0, 0.0, 1.0);

	if (dir[0] > 0) {
		offset = 8.0;
		base = obs[0] - fmod(obs[0], 8.0);
	} else {
		offset = -8.0;
		base = obs[0] + (8.0 - fmod(obs[0], 8.0));
	}

	glPushMatrix();
	glTranslatef((base - offset / 2.0), 0.0, 0.0);
	for (i = 0; i < NUMBLOC; i++) {
		glTranslatef(offset, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, t1id);
		drawobjs(striplength_skin_11, stripdata_skin_11);
		glBindTexture(GL_TEXTURE_2D, t2id);
		drawobjs(striplength_skin_12, stripdata_skin_12);
		drawobjs(striplength_skin_9, stripdata_skin_9);
		drawobjs(striplength_skin_13, stripdata_skin_13);
	}
	glPopMatrix();
	glPopMatrix();
}

/*************************************************************************/

static void rect(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glVertex3f(x,y,0);
	glVertex3f(x+w,y,0);
	glVertex3f(x+w,y+h,0);
	glVertex3f(x,y+h,0);
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
       /* Enable opaque and punchthru polygons with size 16 */
       { PVR_BINSIZE_32, PVR_BINSIZE_0, PVR_BINSIZE_32, PVR_BINSIZE_0, PVR_BINSIZE_0 },

        /* Vertex buffer size 512K */
        512*1024
};

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

static void do_init() {
        pvr_init(&params);
	printf("[DCTunnel] KGL Initialing\n");

	/* Setup KGL */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 640.0f/480.0f, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	
	/* fog */
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogcolor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	/* textures */
	printf("[DCTunnel] Loading Textures\n");
	loadtxr("/rd/tile.pcx", &t1id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
	loadtxr("/rd/bw.pcx", &t2id);

	/* PLIB for fonts */
	plinit();

	/* Setup Menu */
	printf("[DCTunnel] Initializing Menu\n");
	fm = (Menu*) malloc(sizeof(Menu));
	/*      min   max  amt  pvalue          format */
	fm->add(0,    1,    1,  &cstrip,	"See Strips....... %d");
	fm->add(0,    1,    1,  &usefog,	"Fog.............. %d");
	fm->add(0.0,  1.0,  0.001, &density,	"Fog Density...... %1.3f");
	fm->add(0,    1,    1,  &textog, 	"Texture.......... %d");
	fm->add(0,    1,    1,  &cullface, 	"Cull Backface.... %d");
	fm->add(-100, 100,  1,  &velocity,	"Velocity......... %+03d");

	calcposobs();
}

static void reset_view() {
	velocity = 10;
	alpha = 90.0;
	beta = 90.0;
	obs[0] = 1000.0;
	obs[1] = 0.0;
	obs[2] = 2.0;
}

void do_help() {
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,640,0,480,-1,0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0, 0.0, 0.0, 0.5);
	rect(150, 120, 340, 220);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	fm->draw(11, 11, 2);
}

static void do_text() {
	plprint(1, 1, 1.0f, 0.0f, 0.0f,
			"Tunnel V1.5 Written by David Bucciarelli", 0);
	if (help) {
		plprint(1, 29, 1.0f, 0.0f, 0.0f,
			"[Y][D-Pad] help  [A] Reset  [L/R] Velocity", 0);
		plprint(1, 27, 1.0f, 0.0f, 0.0f, "[Joystick]", 0);
	}
}

typedef struct JOYINFO {
	float wXpos;
	float wYpos;
};

static float max[2] = { 0.0, 0.0 };
static float min[2] = { 255.0, 255.0 }, center[2];
static void do_joy(cont_cond_t *cond) {
	
	JOYINFO joy;

	joy.wXpos = (float)cond->joyx;
	joy.wYpos = (float)cond->joyy;

	if (!joyactive) {
		/* save joystick center */
		if (max[0] < joy.wXpos)
			max[0] = joy.wXpos;
		if (min[0] > joy.wXpos)
			min[0] = joy.wXpos;
		center[0] = (max[0] + min[0]) / 2.0;

		if (max[1] < joy.wYpos)
			max[1] = joy.wYpos;
		if (min[1] > joy.wYpos)
			min[1] = joy.wYpos;
		center[1] = (max[1] + min[1]) / 2.0;
		joyactive = 1;
	} 

	if (joyactive){
		/* use joystick values */
		if (FABS(center[0] - joy.wXpos) > 5.0 )
			alpha -= (center[0] - joy.wXpos)/100.0f;
		if (FABS(center[1] - joy.wYpos) > 5.0 )
			beta +=  (center[1] - joy.wYpos)/100.0f;
	}
		
	
	/* left/right trigger control velocity */
	if ((cond->rtrig > 128) && (velocity < 100))
		velocity += 1;
	if ((cond->ltrig > 128) && (velocity > -100))
		velocity -= 1;
	/* both triggers - full stop */
	if ((cond->ltrig > 128) && (cond->rtrig > 128))
		velocity = 0;
}

static GLboolean yp = GL_FALSE;
int do_controller(uint8 c) {
	static int dpad = 0;
	static int dpadrep = DPAD_REPEAT_INTERVAL;
	static cont_cond_t cond;

	/* Check key status */
	if (cont_get_cond(c, &cond) < 0)
		return 0;
	if (!(cond.buttons & CONT_START))
		return 0;

	/* DPAD Menu controls */
	if (!(cond.buttons & CONT_DPAD_UP)) {
		if (dpad == 0) {
			dpad |= 0x1000;
			if (help) {
				fm->prev();
			} else
				;
		}
	} else
		dpad &= ~0x1000;

	if (!(cond.buttons & CONT_DPAD_DOWN)) {
		if (dpad == 0) {
			dpad |= 0x0100;
			if (help) {
				fm->next();
			} else
				;
		}
	} else
		dpad &= ~0x0100;
	
	if (!(cond.buttons & CONT_DPAD_LEFT)) {
		if (dpad == 0) {
			dpad |= 0x0001;
			if (help) {
				fm->dec();
			} else
				;
		}
	} else
		dpad &= ~0x0001;

	if (!(cond.buttons & CONT_DPAD_RIGHT)) {
		if (dpad == 0) {
			dpad |= 0x0010;
			if (help) {
				fm->inc();
			} else
				;
		}
	} else
		dpad &= ~0x0010;
	
	// cheap dpad hold and repeat...
	if (dpad != 0) {
		dpadrep--;
		if (dpadrep < 0) {
			dpadrep = DPAD_REPEAT_INTERVAL;
			dpad = 0;
		}
	} else
		dpadrep = DPAD_REPEAT_INTERVAL;
	
	/* Help toggle */
	if (!(cond.buttons & CONT_Y) && !yp) {
		yp = GL_TRUE;
		help = !help;
	}
	if (cond.buttons & CONT_Y)
		yp = GL_FALSE;

	/* Reset view */
	if (!(cond.buttons & CONT_A))
		reset_view();
	
	do_joy(&cond);
	
	v = (float)(velocity/100.0f);
		
	if (last_density != density) {
		glFogf(GL_FOG_DENSITY, density);
		last_density = density;
	}
	return 1;
} /* do_controller */

extern uint8 romdisk[];
int main(void) {
	uint8 c;
	pvr_stats_t stats;

	do_init();

	c = maple_first_controller();
	
	printf("[DCTunnel] Entering Main Loop\n");
	while(1) {
		if (!do_controller(c))
			break;

		/* Begin frame */
		glKosBeginFrame();
		glLoadIdentity();

		draw();

		/* Done with Opaque Polys */
		glKosFinishList();
		glDisable(GL_FOG);
		
		if (help)
			do_help();
		do_text();
		
		/* Finish the frame */
		glKosFinishFrame();
	}

	pvr_get_stats(&stats);
	printf("VBL Count: %d, last_time: %f, frame rate: %f fps\n",
		stats.vbl_count, stats.frame_last_time, stats.frame_rate);

	printf("[DCTunnel] Exited main loop\n");
	return 0;
}
