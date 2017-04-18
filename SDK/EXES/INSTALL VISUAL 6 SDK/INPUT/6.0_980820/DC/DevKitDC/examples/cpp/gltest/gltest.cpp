/* KallistiOS ##version##

   gltest.cpp
   (c)2001 Dan Potter
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*

This is a really simple KallistiGL example. It shows off several things:
basic matrix control, perspective, the AUTO_UV feature, and controlling
the image with maple input.

Thanks to NeHe's tutorials for the crate image.

This version is written in C++ and uses some basic C++ operations to test
various things about C++ functionality.

*/

class Object {
protected:
	float	tx, ty, tz;

public:
	Object(float dtx, float dty, float dtz) {
		tx = dtx;
		ty = dty;
		tz = dtz;
		printf("Object::Object called\n");
	}

	virtual ~Object() {
		printf("Object::~Object called\n");
	}

	virtual void draw() {
	}
};

class Cube : public Object {
private:
	float r;
	
public:
	Cube(float px, float py, float pz)
			: Object(px, py, pz) {
		r = 0.0f;
		printf("Cube::Cube called\n");
	}

	virtual ~Cube() {
		printf("Cube::~Cube called\n");
	}

	void rotate(float dr) {
		r += dr;
	}

	/* Draw a cube centered around 0,0,0. Note the total lack of glTexCoord2f(),
	   even though the cube is in fact getting textured! This is KGL's AUTO_UV
	   feature: turn it on and it assumes you're putting on the texture on
	   the quad in the order 0,0; 1,0; 1,1; 0,1. This only works for quads. */
	virtual void draw() {
		glPushMatrix();
		glTranslatef(tx, ty, tz);
		
		glBegin(GL_QUADS);
			glRotatef(r, 1.0f, 0.0f, 1.0f);

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
		
		glPopMatrix();
	}
};	

/* Note that ctors/dtors aren't really supported right now because of the
   problems related to initialization; i.e., when main() is called, ctors
   ought to have been called, but if they do any KOS specific stuff, it
   will work (or worse, crash). I'm open to suggestions on fixing it. */
class CtorDtorTest {
public:
	CtorDtorTest() {
		printf("CtorDtorTest::CtorDtorTest called\n");
	}
	virtual ~CtorDtorTest() {
		printf("CtorDtorTest::~CtorDtorTest called\n");
	}
} test_object, test_object2;

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

extern uint8 romdisk[];
int main(int argc, char **argv) {
	cont_cond_t cond;
	uint8	c;
	float	r = 0.0f;
	float	dr = 2 * F_PI / 120.0f;
	float	z = -7.19f;
	GLuint	texture;
	int	trans = 0;

	/* Initialize KOS */
	dbglog_set_level(DBG_WARNING);
	kos_init_all(THD_ENABLE | IRQ_ENABLE | TA_ENABLE, romdisk);

	printf("gltest beginning\n");

	/* Get basic stuff initialized */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);

	/* Load a texture */
	loadtxr("/rd/crate.pcx", &texture);
	printf("texture is %08x\n", texture);

	Cube *cubes[4] = {
		new Cube(-5.0f, 0.0f, 0.0f),
		new Cube(5.0f, 0.0f, 0.0f),
		new Cube(0.0f, 5.0f, 0.0f),
		new Cube(0.0f, -5.0f, 0.0f)
	};
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
			z -= 0.1f;
		if (!(cond.buttons & CONT_DPAD_DOWN))
			z += 0.1f;
		if (!(cond.buttons & CONT_DPAD_LEFT)) {
			/* If manual rotation is requested, then stop
			   the automated rotation */
			dr = 0.0f;
			for (int i=0; i<4; i++)
				cubes[i]->rotate(- 2 * F_PI / 120.0f);
			r -= 2 * F_PI / 120.0f;
		}
		if (!(cond.buttons & CONT_DPAD_RIGHT)) {
			dr = 0.0f;
			for (int i=0; i<4; i++)
				cubes[i]->rotate(+ 2 * F_PI / 120.0f);
			r += 2 * F_PI / 120.0f;
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

		for (int i=0; i<4; i++)
			cubes[i]->rotate(dr);
		r += dr;

		/* Begin frame */
		glKosBeginFrame();

		/* Draw four objects */
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, z);
		glRotatef(r, 0.0f, 1.0f, 0.5f);

		cubes[0]->draw();
		cubes[1]->draw();

		/* Potentially do two as translucent */
		if (trans & 1) {
			glKosFinishList();
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glDisable(GL_CULL_FACE);
		}

		cubes[2]->draw();
		cubes[3]->draw();

		if (trans & 1) {
		        glEnable(GL_CULL_FACE);
		}

		/* Finish the frame */
		glKosFinishFrame();
	}

	for (int i=0; i<4; i++)
		delete cubes[i];

	return 0;
}


