/*
   Tiki

   platgl.cpp

   Copyright (C)2005 Cryptic Allusion, LLC

   Most of this file is code created by Brian Peek for TikiTest.

*/

#include "pch.h"
#include "Tiki/glhdrs.h"
#include "Tiki/hid.h"
#include "Tiki/tikitime.h"
#include "Tiki/gl.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

using namespace Tiki::Hid;

// Windows globals
static HWND		m_hWndMain;
static HINSTANCE	m_hInstance;
static HGLRC		m_hrc, m_hThreadRc;
static DWORD		m_dwThreadID;
static HANDLE		m_hThread;
static HDC		m_hThreadDc;

static int m_targetFrameRate = 60, m_targetW = 640, m_targetH = 480;

typedef int (APIENTRY * PFNWGLSWAPINTERVALEXTPROC)(int interval);
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
typedef int (APIENTRY * PFNWGLGETSWAPINTERVALEXTPROC)(void);
static PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = NULL;

extern "C" int tiki_main(int argc, char **argv);

// Forward decls
namespace Tiki {
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	BOOL InitApplication();
	BOOL DestroyApplication();
	BOOL ErrorBox(LPCTSTR lpText);
	DWORD WINAPI GameThread(void *obj);
	void OnSize(WORD cx, WORD cy);
}

HWND Tiki::GetWin32Window()
{
	return m_hWndMain;
}

HGLRC Tiki::GetWin32MainHGLRC() {
	return m_hrc;
}

////////////////////////////////////
// Tiki::DoMain
// initialization
////////////////////////////////////
int Tiki::DoMain(const char * szAppName, HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEX wc;
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)m_targetW;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)m_targetH;		// Set Bottom Value To Requested Height
	m_hInstance = hInst;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
		return FALSE;

	AdjustWindowRect(&WindowRect, WS_POPUP|WS_CAPTION|WS_SYSMENU, FALSE);

	//Center the window
	WindowRect.left += (GetSystemMetrics(SM_CXSCREEN)/2 - m_targetW/2);
	WindowRect.right += (GetSystemMetrics(SM_CXSCREEN)/2 - m_targetW/2);
	WindowRect.top += (GetSystemMetrics(SM_CYSCREEN)/2 - m_targetH/2);
	WindowRect.bottom += (GetSystemMetrics(SM_CYSCREEN)/2 - m_targetH/2);

	m_hWndMain = CreateWindow(szAppName, szAppName, WS_POPUP|WS_CAPTION|WS_SYSMENU, WindowRect.left, WindowRect.top, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, NULL, NULL, m_hInstance, NULL);

	if(!m_hWndMain)
		return FALSE;

	if(!InitApplication())
		return FALSE;

	ShowWindow(m_hWndMain, nCmdShow);

	m_hThread = CreateThread(NULL, 0, GameThread, lpCmdLine, 0, &m_dwThreadID);

	while(m_hThread != NULL) {
		do {
			if (GetMessage(&msg, NULL, NULL, NULL)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

	   } while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE));

	   Sleep(2);
	}

	return (int)msg.wParam;
}

////////////////////////////////////
// WndProc
// Messages for our window are handled here
////////////////////////////////////
LRESULT CALLBACK Tiki::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400) //WM_MOUSEWHEEL requires Windows 98 or above
		case WM_MOUSEWHEEL:
#endif
			Tiki::RecvEvent(iMsg, wParam, lParam);
			break;
		case WM_CLOSE:
			Tiki::RecvQuit();
			return 0;
			break;
		case WM_DESTROY:
			DestroyApplication();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
	return 0L;
}

BOOL Tiki::InitApplication()
{
	HDC hdc = GetDC(m_hWndMain);

	// Fill in a pixel format descriptor.
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags =	PFD_DOUBLEBUFFER |
			PFD_SUPPORT_OPENGL |
			PFD_DRAW_TO_WINDOW |
			PFD_GENERIC_ACCELERATED;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int chosen = ChoosePixelFormat(hdc, &pfd);

	// Check to see if we got accelerated.
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	DescribePixelFormat(hdc, chosen, sizeof(pfd), &pfd);
	if (pfd.dwFlags & PFD_GENERIC_FORMAT) {
		MessageBox(NULL, "No accelerated GL seems to be available.", "Error", MB_ICONERROR | MB_OK);
		// return FALSE;
	}

	// Set the format into the DC.
	if (!SetPixelFormat(hdc, chosen, &pfd)) {
		ErrorBox("Couldn't set pixel format into DC.");
		return FALSE;
	}

	// Create rendering context to use.
	HGLRC hrc = wglCreateContext(hdc);
	if (!hrc) {
		ErrorBox("Couldn't create WGL context.");
		return FALSE;
	}
	m_hrc = hrc;

	// Make the context current so we can do some twiddling.
	wglMakeCurrent(hdc, m_hrc);

	// Query for the swap interval extensions.
	wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	// If we got the Get function, display the old sync setting.
	if (wglGetSwapIntervalEXT) {
		Debug::printf("Vertical sync state was %d\n", wglGetSwapIntervalEXT());
	} else {
		Debug::printf("WARNING! wglGetSwapIntervalEXT is NULL\n");
	}

	// If we got the Set function, change sync to OFF. It causes big problems on
	// nVidia cards.
	if (wglSwapIntervalEXT) {
		Debug::printf("Turning off vertical sync\n");
		wglSwapIntervalEXT(0);
	} else {
		Debug::printf("WARNING! wglSwapIntervalEXT is NULL\n");
	}

	// Turn off the context and release the DC.
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(m_hWndMain, hdc);

	return TRUE;
}

BOOL Tiki::DestroyApplication()
{
	if(WaitForSingleObject(m_hThread, INFINITE) != WAIT_OBJECT_0)
		ErrorBox("Couldn't wait for game thread to terminate.");

	if(!CloseHandle(m_hThread))
		ErrorBox("Couldn't terminate game thread.");

	m_hThread = NULL;
	Tiki::shutdown();

	return TRUE;
}

BOOL Tiki::ErrorBox(LPCTSTR lpText)
{
	MessageBox(m_hWndMain, lpText, "Error", MB_ICONERROR);
	return FALSE;
}

DWORD WINAPI Tiki::GameThread(void *obj)
{
	Debug::printf( "GameThread beginning\n" );

	// Set up our GL context so that texture loading and such works as well.
	m_hThreadDc = GetDC(m_hWndMain);
	m_hThreadRc = wglCreateContext(m_hThreadDc);
	wglShareLists(m_hrc, m_hThreadRc);
	wglMakeCurrent(m_hThreadDc, m_hThreadRc);

	int argc = 0;
	LPWSTR *args = CommandLineToArgvW(GetCommandLineW(), &argc);
	// if we have 1 or more command line args, pass it down nicely to tiki_main
	if(argc > 0)
	{
		char ** argv = new char*[argc];
		for(int i = 0; i < argc; i++)
		{
			argv[i] = new char[wcslen(args[i]) + 2];
			sprintf(argv[i], "%ws", args[i]);
		}
		LocalFree(args);

		tiki_main(argc, argv);

		// cleanup allocated memory for cmd line args
		for(int i = 0; i < argc; i++)
		{
			delete [] argv[i];
		}
		delete [] argv;
	}
	else
	{
		tiki_main(0, NULL);
	}

	wglDeleteContext(m_hThreadRc);
	ReleaseDC(m_hWndMain, m_hThreadDc);
	m_hThreadDc = NULL;
	m_hThread = NULL;
	Debug::printf( "GameThread exiting\n" );
	return 0;
}


static uint64 lastFrame = 0;
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
	m_targetFrameRate = rate;
}

extern "C" void tiki_scene_begin_hook() {
	// Set up our GL context for painting, if needed. If this is another
	// thread besides the main game thread, it might have its own.
	if ( wglGetCurrentContext() == NULL )
		wglMakeCurrent(m_hThreadDc, m_hrc);

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

#ifdef _DEBUG
	if (frameCnt && !(frameCnt % 250)) {
		Debug::printf("frame %d, fps = %.2f\n", (int)frameCnt,
			(double)Tiki::GL::Frame::getFrameRate());
	}
#endif

	if (lastFrame == 0) {
		lastFrame = Tiki::Time::gettime();
		return;
	}

	uint64 now;
	now = Tiki::Time::gettime();
	uint64 diff = now - lastFrame;
	if (diff < (1000*1000 / m_targetFrameRate)) {
		Tiki::Time::sleep((1000*1000 / m_targetFrameRate) - diff);
	}
	lastFrame = Tiki::Time::gettime();
}

extern "C" void tiki_scene_finish_hook() {
	// Flush any remaining GL commands and swap buffers.
	glFlush();
	SwapBuffers(m_hThreadDc);

	// Deactivate GL context.
	// NOTE: We do NOT do this because otherwise a lot of stuff done outside
	//   the frame proper e.g. loading textures will not work.
	// wglMakeCurrent(NULL, NULL);
}









