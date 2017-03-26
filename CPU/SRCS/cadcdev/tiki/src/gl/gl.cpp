/*
   Tiki

   gl.cpp

   Copyright (C)2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/gl.h"

using namespace Tiki::GL;

extern "C" {
	void tiki_scene_begin_hook();
	void tiki_scene_finish_hook();
}

void Frame::begin() {
	tiki_scene_begin_hook();

	// This sets up an OpenGL environment approximately the same
	// as a PVR.
#if TIKI_PLAT != TIKI_NDS
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
#if TIKI_PLAT != TIKI_DC //KGL doesn't have these constants
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_STENCIL_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthFunc(GL_GREATER);
#else
	glDepthFunc(GL_LEQUAL);
#endif
	glDepthMask(GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_CULL_FACE);

#endif
	set2d();

//	glViewport((GLsizei)m_x1, (GLsizei)m_y1, (GLsizei)m_x2, (GLsizei)m_y2);
		
#if TIKI_PLAT != TIKI_NDS
	glViewport(0, 0, 640, 480);

	glClearDepth(0.0f);
#if TIKI_PLAT != TIKI_DC
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT+GL_STENCIL_BUFFER_BIT);
#else   //KGL doesn't have GL_STENCIL_BUFFER_BIT
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT);
#endif

#else // TIKI_NDS
	glViewPort(0, 0, 255, 191);

	glClearDepth(0x7FFFF);
	glClearColor(0,0,0);
#endif

	glLoadIdentity();
	
	transDisable();
}

void Frame::set2d() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Frame::set3d() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Frame::finish() {
	tiki_scene_finish_hook();
}

void Frame::transEnable() {
	// This will leave the depth testing enabled (to not overdraw
	// opaque objects) but not update the depth buffer.
#if TIKI_PLAT != TIKI_NDS
	glDepthMask(GL_FALSE);
#endif

#if TIKI_PLAT == TIKI_DC
	glKosFinishList();
#endif
	
	// Turn on blending with a sensible alpha function default.
	glEnable(GL_BLEND);
#if TIKI_PLAT != TIKI_NDS
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
}

void Frame::transDisable() {
	// glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

