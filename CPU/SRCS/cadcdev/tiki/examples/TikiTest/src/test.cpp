/*
 *  test.cpp
 *  TikiTest
 *
 *  Created by Dan Potter on 1/11/05.
 *  Copyright 2005 Cryptic Allusion, LLC. All rights reserved.
 *
 */

#include <Tiki/tiki.h>
#include <Tiki/plxcompat.h>
#include <Tiki/gl.h>
#include <Tiki/hid.h>

#include "testobj.h"

using namespace Tiki;
using namespace Tiki::Math;
using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;
using namespace Tiki::Hid;
using namespace Tiki::Audio::OggVorbis;

/*

This is a Parallax version of the "bubbles" KGL demo. The speed is about
the same, but it uses the Parallax functions instead of KGL.

*/

struct mouse_pos_t {
	int x;
	int y;
	int valid;
};

volatile mouse_pos_t mp[4]; //Woah, 4 mice!

//Draw the mouse pointer, parallax-style!
void draw_mouse(volatile mouse_pos_t *pos) {
	plx_vertex_t vert;

	plx_mat3d_identity();

	vert.argb = Color(0,0,0);
	vert.z = 0.3;

	vert.flags = PLX_VERT;
	vert.x = pos->x-2;
	vert.y = pos->y-4;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT;
	vert.x = pos->x+18;
	vert.y = pos->y+16;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT_EOS;
	vert.x = pos->x-2;
	vert.y = pos->y+24;
	plx_prim(&vert, sizeof(vert));

  vert.argb = Color(0.8,0.2,0.1);
	vert.z = 0.31;

	vert.flags = PLX_VERT;
	vert.x = pos->x;
	vert.y = pos->y;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT;
	vert.x = pos->x+15;
	vert.y = pos->y+15;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT_EOS;
	vert.x = pos->x;
	vert.y = pos->y+21;
	plx_prim(&vert, sizeof(vert));
}

/* Draws a sphere out of GL_QUADS according to the syntax of glutSolidSphere

   This now uses triangle strips and PVR Direct Rendering for the best
   possible performance.

   Based very loosely on a routine from James Susinno.
*/
static float phase = 0.0f;
/* static pvr_poly_cxt_t cxt;
static pvr_poly_hdr_t hdr; */
static void sphere( float radius, int slices, int stacks ) {
	int	i, j;
	float	pitch, pitch2;
	float	x, y, z, g, b;
	float	yaw, yaw2;
	plx_dr_state_t	dr_state;

	/* Initialize xmtrx with the values from KGL */
	plx_mat_identity();
	plx_mat3d_apply(PLX_MAT_SCREENVIEW);
	plx_mat3d_apply(PLX_MAT_PROJECTION);
	plx_mat3d_apply(PLX_MAT_MODELVIEW);

	/* Put our own polygon header */
	// pvr_prim(&hdr, sizeof(hdr));

	/* Iterate over stacks */
	for ( i=0; i<stacks; i++ ) {
		pitch = 2*M_PI * ( (float)i/(float)stacks );
		pitch2 = 2*M_PI * ( (float)(i+1)/(float)stacks );

		/* Iterate over slices: each entire stack will be one
		   long triangle strip. */
		for ( j=0; j<=slices/2; j++ ) {
			yaw = 2*M_PI * ( (float)j/(float)slices );
			yaw2 = 2*M_PI * ( (float)(j+1)/(float)slices );

			/* x, y+1 */
			x = radius * fcos( yaw ) * fcos( pitch2 );
			y = radius * fsin( pitch2 );
			z = radius * fsin( yaw ) * fcos( pitch2 );
			plx_mat_tfip_3d(x, y, z);			/* Use ftrv to transform */
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch2 ) / 2.0f + 0.5f;
			plx_vert_fnd(&dr_state, PLX_VERT,
				x, y, z, 1.0f,
				0.0f, g, b);

			/* x, y */
			x = radius * fcos( yaw ) * fcos( pitch );
			y = radius * fsin( pitch );
			z = radius * fsin( yaw ) * fcos( pitch );
			plx_mat_tfip_3d(x, y, z);
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch ) / 2.0f + 0.5f;

			if (j == (slices/2)) {
				plx_vert_fnd(&dr_state, PLX_VERT_EOS,
					x, y, z, 1.0f,
					0.0f, g, b);
			} else {
				plx_vert_fnd(&dr_state, PLX_VERT,
					x, y, z, 1.0f,
					0.0f, g, b);
			}
		}
	}
}

#define SPHERE_CNT 12
static float r = 0;
static int dir = 1;
static void sphere_frame_opaque() {
	int i;

//	vid_border_color(255, 0, 0);
	Frame::begin();
//	vid_border_color(0, 255, 0);

	//Draw the mice

	for (i=0; i<4; i++) {
		if(mp[i].valid) {
			draw_mouse(&mp[i]);
		}
	}

	plx_mat3d_identity();
	plx_mat3d_translate(0.0f, 0.0f, -12.0f);
	plx_mat3d_rotate(r * 2, 0.75f, 1.0f, 0.5f);
	plx_mat3d_push();

	for (i=0; i<SPHERE_CNT; i++) {
		plx_mat3d_translate(6.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 6.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		plx_mat3d_rotate(r, 1.0f, 1.0f, 1.0f);
		sphere(1.2f, 20, 20);
		if (i < (SPHERE_CNT-1))
			plx_mat3d_peek();
	}
	plx_mat3d_pop();

	plx_mat3d_identity();
	plx_mat3d_translate(0.0f, 0.0f, -12.0f);
	plx_mat3d_rotate(-r * 2, 0.75f, 1.0f, 0.5f);
	plx_mat3d_push();

	for (i=0; i<SPHERE_CNT; i++) {
		plx_mat3d_translate(3.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 3.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		plx_mat3d_rotate(r, 1.0f, 1.0f, 1.0f);
		sphere(0.8f, 20, 20);
		if (i < (SPHERE_CNT-1))
			plx_mat3d_peek();
	}
	plx_mat3d_pop();

//	vid_border_color(0, 0, 255);
	Frame::finish();

	r+=dir;
	phase += 2*M_PI / 240.0f;
}

volatile bool quitting = false;
void tkCallback(const Hid::Event & evt, void * data) {
	if (evt.type == Hid::Event::EvtQuit) {
		quitting = true;
	} else if (evt.type == Event::EvtKeypress || (evt.type == Event::EvtBtnRelease && evt.btn == Event::MouseLeftBtn)) {
		dir = -dir;
	}
	int port = evt.port;
	if(evt.port < 0 && evt.port > 4) {
		port = 0;
	}
	if (evt.type == Event::EvtAttach) {
		printf("Device attached: %s\n",evt.dev->getName().c_str());
		if(evt.dev->getType() == Device::TypeMouse) {
			mp[port].valid=1;
			mp[port].x=320;
			mp[port].y=240;
		}
	}
	if (evt.type == Event::EvtDetach) {
		printf("Device detached: %s\n",evt.dev->getName().c_str());
		mp[port].valid=0;
	}
	if (evt.type == Event::EvtMouseMove) {
		mp[port].x=evt.x;
		mp[port].y=evt.y;
	}
}

extern "C" int tiki_main(int argc, char **argv) {
	// Init Tiki
	if(!Tiki::init(argc, argv))
	{
		exit(-1);
	}
	Tiki::setName("TikiTest", NULL);
	Tiki::GL::showCursor(false);
	Hid::callbackReg(tkCallback, NULL);

	Debug::printf("argc: %i\n", argc);
	for(int i=0; i<argc; i++) {
		Debug::printf("argv[%i]: %s\n",i,argv[i]);
	}
	
#if TIKI_PLAT != TIKI_DC
	//Attach events happen before we start :(
	mp[0].valid=1;
	mp[0].x=320;
	mp[0].y=240;
#endif

	RefPtr<TestObject> test = new TestObject("1");
	RefPtr<TestObject> test2 = new TestObject("2");
	test->connect("testevent", test2);
	test->perform("testmessage", NULL, NULL);
	test->perform("anothermessage", NULL, NULL);

	plx_mat3d_mode(PLX_MAT_PROJECTION);
	plx_mat3d_identity();
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);

	while (!quitting)
		sphere_frame_opaque();

	// Shut down Tiki
	/* OggVorbis::stop();
	OggVorbis::shutdown(); */
	Tiki::shutdown();

	return 0;
}

