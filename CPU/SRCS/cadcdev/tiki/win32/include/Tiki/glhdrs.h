#pragma once

#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

namespace Tiki {
	// Returns a handle to the Win32 window.
	HWND GetWin32Window();

	// Returns a handle to the primary GL context.
	HGLRC GetWin32MainHGLRC();
};


