/*****************************************************************************
  Name : D3DShell.h		v2.1.7
  Date : March 1999
  Platform : ANSI compatible

  Header file to be used with D3DShell.c

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/

#ifndef _D3DSHELL_H_
#define _D3DSHELL_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Enum */
enum _D3DShellPrefs
{
	DEFAULT_SINGLE_BUFFER	=0x00000008,	// Start with single buffer by default
	DEFAULT_TRIPLE_BUFFER	=0x00000010,	// Start with triple buffer by default
	DEFAULT_CLEAR_ON		=0x00000020,	// Viewport clear is On by default
	FORCE_SINGLE_BUFFER		=0x00000800,	// Single Buffer will be forced On and will not appear in the menu
	FORCE_DOUBLE_BUFFER		=0x00001000,	// Double Buffer will be forced On and will not appear in the menu
	FORCE_TRIPLE_BUFFER		=0x00002000,	// Triple Buffer will be forced On and will not appear in the menu
	FORCE_CLEAR_ON			=0x00004000,	// Viewport clear will be forced On and will not appear in the menu
	FORCE_CLEAR_OFF			=0x00008000,	// Viewport clear will be forced Off and will not appear in the menu
} D3DShellPrefs;


/* Enum */
enum _D3DShellVariables
{
	APPLICATION_INSTANCE_HANDLE	=1,	// Handle of application (HINSTANCE type)
	PREVIOUS_INSTANCE_HANDLE,		// Handle of previous application (HINSTANCE type)
	WINDOW_HANDLE,					// Application window handle (HWND type)
	FULLSCREEN_MODE,				// Is application in FullScreen mode (BOOL type)
	PRIMARY_SURFACE,				// Primary surface (LPDIRECTDRAWSURFACE4 type)
	BACK_BUFFER,					// Back buffer surface, i.e where the rendering is generally performed (LPDIRECTDRAWSURFACE4 type)
	Z_BUFFER,						// Z Buffer surface (LPDIRECTDRAWSURFACE4 type)
	D3DDRIVER_GUID_POINTER,			// GUID pointer of D3D Driver (LPGUID type)
	FRAME_BUFFER_BIT_DEPTH,			// Rendering surface bit depth (DWORD type)
	BUFFERING_MODE,					// Current buffering mode (DWORD type)
	FRAME_RATE						// Current frame rate (DWORD type)
} D3DShellVariables;


/*******************************************
** D3DShell helper functions declarations **
*******************************************/

/* This function is used to pass preferences to the D3DShell
   If used, it must be called from InitApplication() only. */
void D3DShellSetPreferences(DWORD	dwFlags);

/* This function loads a BMP texture and returns its interface */
BOOL D3DShellLoadBMP(TCHAR	*lpName, 
					 BOOL	bTranslucent, 
					 LPDIRECT3DTEXTURE2 *lplpD3DTex2);

/* This function enables the user to retrieve rendering variables if needed */
void D3DShellGetVariable(enum D3DShellVariables nVariableName, 
						 void *pVariablePointer);


/*******************************
** User interaction functions **
*******************************/

/* These functions have to exist in the scene file (e.g. scene.c).
   They are used to interact with the D3DShell */

void InitApplication(HINSTANCE hInstance, HWND hWindow, TCHAR *pszCommandLine);
/*
This function will be called by D3DShell before anything happens, at the beginning 
of the D3DShell WinMain() function. That's the only time this function will be called. 
This function enables the user to perform any initialisation before the program is 
actually run.
From this function the user can call D3DShellSetPreferences() to set default
values or submit a menu to D3DShell. A prototype of the function is :
	
void D3DShellSetPreferences(char	*pszApplicationName, 
							HMENU	hUserMenuID, 
							HACCEL	hUserAccel,
							HICON	hUserIcon, 
							DWORD	dwFlags);
*/


void QuitApplication();
/*
This function will be called by D3DShell just before finishing the program.
It enables the user to release any memory allocated before.
*/


void UserWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
/*
This function is the user Window Procedure function. It enables the user to retrieve
menu choices, keystrokes or other messages (WM_TIMER for instance).
If you don't want to use this function, put nothing in it :
    
void UserWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Nothing !
}

D3DShell processes many window messages. If the user needs to 
process these messages in their application, they should make sure
NOT to return DefWindowProc() as it will prevent the D3DShell WindowProc
to do its own processing for these messages.
The window messages processed by D3DShell are :

WM_ENTERMENULOOP, WM_EXITMENULOOP,
WM_ACTIVATEAPP,
WM_SYSCOMMAND,
WM_SIZE, WM_MOVE, WM_SIZING, WM_MOVING,
WM_PAINT,
WM_DESTROY, WM_QUIT

Note : do NOT process the VK_ESCAPE key, as it is already used by  
  	   D3DShell to quit the application.
*/


BOOL RenderScene(LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3);
/*
That's the main user function in which you have to do your own rendering.
Pointers to the D3D device (LPDIRECT3DDEVICE3) and the D3D viewport
(LPDIRECT3DVIEWPORT3) are passed to this function so you can use them
to control your rendering (Render states, lights, etc...)
This function is called every frame by D3DShell and enable the user to
create the scene for this frame.
*/


BOOL InitView(LPDIRECTDRAW4 lpDD4, LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, 
			  LPDIRECT3DVIEWPORT3 lpView3, DWORD dwWidth, DWORD dwHeight);
/*
This function enables the user to create vertex buffers, execute buffers, 
materials, set rendering values, load textures, etc... This function will 
be called each time the surfaces and objects will be recreated (i.e. 
switching to FullScreen, enabling Z-Buffer, etc...)
dwWidth and dwHeight are the current dimensions of the rendering surface.
*/

void ReleaseView(LPDIRECT3DVIEWPORT3 lpView3);
/*
This function enables the user to release any devices he/she has created 
in the InitView function.
The function will be called each time the surfaces and variables have to 
be recreated. A pointer to the viewport is passed, as the user might 
need it to delete any lights attached to the viewport, for instance.
*/

/* Draw the Dreamcast Logo (it has to be between BeginScene() EndScene())*/
void D3DShellDCLogo (int nBackgroundIntensity);

#ifdef __cplusplus
}
#endif

#endif
