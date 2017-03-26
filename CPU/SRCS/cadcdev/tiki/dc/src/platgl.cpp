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

#include <sys/time.h>

using namespace Tiki;

float Tiki::GL::Frame::getFrameRate() {
	pvr_stats_t stats;
	pvr_get_stats(&stats);
	return stats.frame_rate;
}

void Tiki::GL::Frame::setFrameRateLimit(int rate) {
}

extern "C" {

void tiki_wait_if_needed() {
	pvr_wait_ready();
}

void tiki_scene_begin_hook() {
	glKosBeginFrame();
}

void tiki_scene_finish_hook() {
	glKosFinishFrame();
}

void tiki_scene_begin_opaque_hook() {
}

void tiki_scene_finish_opaque_hook() {
	glKosFinishList();
}

void tiki_scene_begin_trans_hook() {
}

void tiki_scene_finish_trans_hook() {
	glKosFinishList();
}
}
