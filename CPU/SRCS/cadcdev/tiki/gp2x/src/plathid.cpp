#include "pch.h"
#include "Tiki/glhdrs.h"
#include "Tiki/hid.h"

namespace Tiki::Hid {

EGLDisplay g_display;
EGLSurface g_surface;
EGLContext g_context;

bool platInit() {
	
	g_display = elgGetDisplay(0);

	EGLint major, minor;

	if(!eglInitialize(g_display, &major, &minor))
	{
		printf("Unable to initialize EGL: %s\n", eglQueryString(g_display, eglGetError()));
		return false;
	}

	EGLConfig configs[10];
	EGLint matchingConfigs;
	EGLint attribList[] = {0};

	if(!eglChooseConfig(g_display, attribList, &configs[0], 10, &matchingConfigs))
	{
		printf("Unable to find suitable configuration: %s\n", eglQueryString(g_display, eglGetError()));
		return false;
	}
	if(matchingConfigs < 1)
	{
		printf("no suitable configurations returned.\n");
		return false;
	}

	EGLConfig config = configs[0];
	g_surface = eglCrateWindowSurface(g_display, config, (NativeWindowType)0, attribList);

	g_context = eglCreateContext(g_display, config, 0, attribList);
	eglMakeCurrent(g_display, g_surface, g_surface, g_context);

	if(!eglGetError() == EGL_SUCCESS)
	{
		printf("Failed to create context: %s\n", eglQueryString(g_display, eglGetError()));
		return false;
	}

	return true;
}

void platShutdown() {
}

}

extern "C" void TikiRecvQuit() {
	Event evt(Event::EvtQuit);
	sendEvent(evt);
}

