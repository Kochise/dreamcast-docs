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

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

using namespace Tiki;

static struct timeval lastFrame = { 0,0 };
static int targetFrameRate = 60, targetW = 640, targetH = 480;
static uint64 firstFrame = 0;
static uint64 frameCnt = 0, totalFrameCnt = 0;

float Tiki::GL::Frame::getFrameRate() {
	uint64 cur = Tiki::Time::gettime();

	// Avoid divzero
	if (cur == firstFrame)
		return 0.0f;

	return (float)((frameCnt * 1000000.0) / (cur - firstFrame));
}

void Tiki::GL::Frame::setFrameRateLimit(int rate) {
	targetFrameRate = rate;
}

extern "C" {
	
void tiki_wait_if_needed() {
	// Every so often we should reset the frame counters, to avoid
	// having a super long term averaging effect.
	if (frameCnt >= 500) {
		firstFrame = 0;
		frameCnt = 0;
	}

	// Update frame counters.
	if (!firstFrame)
		firstFrame = Tiki::Time::gettime();
	frameCnt++;
	totalFrameCnt++;

	if (lastFrame.tv_sec == 0) {
		gettimeofday(&lastFrame, NULL);
		return;
	}

	struct timeval now;
	gettimeofday(&now, NULL);
	long long nowu = ((long long)now.tv_sec) * 1000 * 1000 + now.tv_usec;
	long long lastu = ((long long)lastFrame.tv_sec) * 1000 * 1000 + lastFrame.tv_usec;
	long long diffu = nowu - lastu;
	if (diffu < (1000*1000 / targetFrameRate)) {
		usleep((1000*1000 / targetFrameRate) - diffu);
	}
	gettimeofday(&lastFrame, NULL);
}

void tiki_scene_begin_hook() {
	tiki_wait_if_needed();
}

void tiki_scene_finish_hook() {
	SDL_GL_SwapBuffers();
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
