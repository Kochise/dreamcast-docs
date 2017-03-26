/*
   Tiki

   tikitime.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/tikitime.h"

static bool gotFreq = false;
static bool haveFreq;
static uint64 freq;

#include <MMSystem.h>

uint64 Time::gettime() {
	if (!gotFreq) {
		LARGE_INTEGER out;
		if (!QueryPerformanceFrequency(&out)) {
			Debug::printf("QueryPerformanceFrequency failed: %d\n", GetLastError());
			assert( false );
		}
		if (!out.QuadPart)
			haveFreq = false;
		else {
			haveFreq = true;
			freq = (uint64)out.QuadPart;
		}
		gotFreq = true;
	}

	if (gotFreq && !haveFreq) {
		return ((uint64)timeGetTime()) * 1000;
	}

	LARGE_INTEGER out;
	if (!QueryPerformanceCounter(&out)) {
		Debug::printf("QueryPerformanceCounter failed: %d\n", GetLastError());
		assert( false );
	}
	uint64 tv = (uint64)out.QuadPart;
	double diff = (double)freq / 1000000;

	return (uint64)(tv / diff);
}

// This is a dumb approximation of a real microsecond sleep which still
// tries to save CPU time and battery power. We do the bulk of sleeping inside
// the Sleep() function (which has ~2ms precision thanks to winmm) and then
// spin with thread yielding for the rest.
void Time::sleep(uint64 us) {
	uint64 now = gettime(), then = now + us;

	// Do we have some macro time to wait?
	if (us >= 2000) {
		DWORD millis = (DWORD)(us / 1000 - 1);
		Sleep(millis);
		now = gettime();
	}

	while (now < then) {
		Sleep(0);
		now = gettime();
	}
}











