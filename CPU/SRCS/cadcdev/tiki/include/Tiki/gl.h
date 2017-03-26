/*
   Tiki

   gl.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_GL_H
#define __TIKI_GL_H

#include "Tiki/glhdrs.h"

namespace Tiki {
namespace GL {
namespace Frame {

// Wait until we're ready, and set everything up for a frame.
void begin();

// Finish up anything hanging around from the frame.
void finish();

// Enable / disable translucency settings (default is disabled).
void transEnable();
void transDisable();

// Switch to GL 2D/Ortho mode.
void set2d();

// Switch to GL 3D/Perspective mode.
void set3d();

// Get the current approximate frame rate.
float getFrameRate();

// Set the frame rate limiter. Whatever is set will be the maximum
// number of frames per second allowed. The default is 60.
void setFrameRateLimit(int rate);

}
}
}

#endif	// __TIKI_GL_H

