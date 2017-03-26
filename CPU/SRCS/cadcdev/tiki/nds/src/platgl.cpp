/*
 *  platgl.cpp
 *  Tiki
 *
 *  Created by Dan Potter on 3/20/05.
 *  Copyright 2005 Cryptic Allusion, LLC. All rights reserved.
 *
 */

#include "Tiki/gl.h"
#include "Tiki/tikitime.h"
#include "Tiki/debug.h"

#include <unistd.h>
#include <sys/time.h>

namespace Tiki {
namespace GL {
namespace Frame {

float getFrameRate() {
	return 0.0f;
}

void setFrameRateLimit(int rate) {
}

}

extern "C" {
	
void tiki_wait_if_needed() {
}

void tiki_scene_begin_hook() {
}

void tiki_scene_finish_hook() {
}

void tiki_scene_begin_opaque_hook() {
}

void tiki_scene_finish_opaque_hook() {
}

void tiki_scene_begin_trans_hook() {
}

void tiki_scene_finish_trans_hook() {
}

}
}
}
