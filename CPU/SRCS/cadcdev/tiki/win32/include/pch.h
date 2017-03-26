// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Dumb VS8.0 stuff
#define _CRT_SECURE_NO_DEPRECATE 1
#define _ATL_SECURE_NO_DEPRECATE 1

#include <windows.h>
#include <shellapi.h>

#define _USE_MATH_DEFINES
#include <math.h>

// This header does most of the useful work for bringing in stuff.
#include "Tiki/tiki.h"

// Don't bother with namespace poo inside the framework itself.
using namespace Tiki;

// This is the hand-off point in the library from WinMain, and HID callbacks.
namespace Tiki {
	int DoMain(const char * szAppName, HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	void RecvQuit();
	void RecvEvent(UINT iMsg, WPARAM wParam, LPARAM lParam);
}

// Packed structs need some compiler-specific foo.
#define PACKED_STRUCT_BEGIN		#pragma pack(push, 1)
#define PACKED_STRUCT_END		#pragma pack(pop)
#define PACKED_STRUCT_MEMBER
