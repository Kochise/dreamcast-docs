/*****************************************************************************
  Name : D3DShell.c v2.1.7
  Date : March 1999
  Platform : ANSI compatible

  Build Info : D3DShell.c + D3DShell.h + DDRAW.LIB + DXGUID.LIB

  D3DShell is a program used to make D3D programming easier and less 
  time-consuming. D3DShell takes care of all DirectDraw and Direct3D
  initialisation for the user : handling DirectDraw and D3D devices, Fullscreen
  mode, resolution mode, window modes, buffering modes, Z-Buffer use, viewport
  creation, viewport clearing, etc...

  Although best used with DrawPrimitive, D3DShell also supports execute buffers.
  To use execute buffers, the user should just retrieve DirectX 3.0 equivalent 
  variables to the interfaces passed to InitView() and RenderScene(). An example file, 
  called SceneEB.c, shows how to use Execute buffers with D3DShell.

  D3DShell consists of only 2 files (D3DShell.c and D3DShell.h). Thus, when 
  creating your D3D application, you just have to link your files with these two, 
  plus the DirectDraw library (DDRAW.LIB), and the DirectX GUID library (DXGUID.LIB).

  The user is only responsible for creating all D3D variables that will be
  needed at rendering time (vertex buffers, lights, materials, etc..).
  
  The user can choose preferences thanks to the D3DShellSetPreferences() function.
  A list of flags that can be passed to this function can be found in the
  D3DShell.h file.
  
  For a list of functions that the user has to use to interact with D3DShell, 
  again see the D3DShell.h file.

  
  * Screen capture

  During execution, a screen capture can be performed by pressing F12.
  The current contents of the back buffer will be saved as a .BMP file
  named ScreenXX.bmp. Up to 100 different images can be saved.
  
  
  *	Helper Functions :

  3 helper functions have also been added to the shell :

  D3DShellSetPreferences(char *pszApplicationName, HMENU hUserMenuID, HACCEL hUserAccel, HICON hUserIcon, DWORD	dwFlags);
  -> This function is used to pass preferences to D3DShell. If used, it must be 
     called from InitApplication() only. 

  D3DShellLoadBMP(char *lpName, BOOL bTranslucent, LPDIRECT3DTEXTURE2 *lplpTex2)
  ->This function enables the user to load a BMP texture from a resource or a file.
    This function should be used in the InitView function. If bTranslucent is set,
	then the file t+"Name" will also be read to retrieve the alpha values (given
	by the RED channel) for this texture.
	Up to 256 textures can be loaded with this function.
	You do NOT need to restore the texture surfaces at any time, as it is already
	done by the D3D Shell.

  D3DShellGetVariable(enum D3DShellVariables nVariableName, void *pVariablePointer)
  ->This function should only be used if the user needs to retrieve some rendering 
    variables that are not already provided in InitView(...). Using flags defined 
	in D3DShell.h, one can ask a pointer to a certain type of variable. The list of 
	these variables can be found in D3DShell.h.

  The user doesn't have to use these helper functions, they are provided to make 
  common rendering tasks easier.


  * Things to do :

  - Handle 8 bpp surface screen capture.
  
			  
  * Current bugs :

  - Single buffer mode does not work the first time you select it if a 
    secondary device is used. (The screen stays with the GDI)
	If anyone has any idea why, please let me know !
  
    
  Please report any bugs or comments to me. If, for any reason, you need to
  modify the D3D Shell, please report to me so I can do the modifications
  myself.

  
  * LATEST CHANGES :
	15/09/99 : - Dreamcast Logo (by CS).
    20/08/99 : - (WCE Dreamcast) Dragon 2.0 version (by CS).
				 Full screen only (640x480).
				 No GDI.
				 No Menus, accelerators, etc.
				 No Z buffer.
				 No 8-bit palettised display modes
				 Unicode.

    11/03/99 : - Got rid of the 2D text feature. It caused a Lock() just after
			   the EndScene() call, preventing any parallelism between CPU and
			   3D hardware.
			   - Added a variable to D3DShellGetVariable() : nBufferMode. This
			   value can be equal to 1 (single buffer), 2 (double buffer), or
			   3 (triple buffer). In window mode, the application is ALWAYS
			   double buffered.
			   - Removed instantaneous frame rate computation as it will no longer
			   be displayed.
			   Versioning to 2.1.7.
	15/02/99 : - Added Multi-Monitor support.
			   - Added new flag : DISABLE_Z_CLEAR.
			   - Don't perform the Blt in D3DFERender if source rectangle is
			   not valid (due to very small render surfaces).
			   Versioning to 2.1.6.
	09/02/99 : - Microsoft NULL device is no more enumerated.
			   - File user menu will now be appended to the main one.
			   - Added command line parameters that set the window size.
			   These parameters are -width=X and -height=Y.
			   - Added command line paramater to autokill the application
			   after FRAMESBEFOREKILLING frames : -autokill.
			   - Added the possibility of retrieving the FULLSCREEN_MODE 
			   variable to know if the rendering is currently in FullScreen
			   mode. 
			   Versioning to 2.1.5.
    05/01/99 : - Removed the #define INITGUID in the source code. The
			   dxguid.lib library should now be included in any project
			   using DirectX (Microsoft recommendation).
			   Added DirectX version checker in D3DShell.c.
			   Versioning to 2.1.4.
    11/12/98 : - Fixed a bug in the display modes enumeration that could
			   make the Blt() failed in D3DFERender().
			   Increased the number of maximum display modes to 52.
			   Versioning to 2.1.3.
	08/12/98 : - The frame rate variable was not updated if DisplayInfo
			   was not enabled. This is now fixed.
			   The icon passed in D3DShellSetPreferences now works!
			   It is used as the application icon, i.e. it's displayed
			   when minimized or changing tasks.
			   Versioning to 2.1.2.
	09/11/98 : - Changed InitApplication() so that it now passes
			   the application instance and window handle.
			   Added a new flag : PREVIOUS_INSTANCE_HANDLE.
			   Versioning to 2.1.1.
	03/11/98 : - Reorganised D3DShell internal structure, making
			   it more robust and easy to add changes. Basically
			   each time a rendering variable is changed (resolution,
			   buffering mode, DirectDraw driver, etc...) all the
			   rendering variables have to pass through a filter
			   function (D3DFECheckRenderingVariables) which
			   determine if the selected rendering variables can
			   coexist together to create a new rendering context.
			   Handled GDI display changes.
			   InitApplication() is now called AFTER window creation,
			   making it possible to call window-related functions
			   in InitApplication() (instead of InitView() as before).
			   Handled 32 bpp screen captures (at last!).
			   Up to 40 different resolutions can now be enumerated.
			   D3DShell can now run in a GDI color depth of 8 bits
			   per pixel (256 colors).
			   Modified the D3DShellGetVariable so that it works(!)
			   Frame rate is now an option left to the user. D3DShell
			   can compute an average or instantaneous frame rate,
			   depending on the flag selected (SHOW_AVERAGE_FPS or
			   SHOW_INSTANTANEOUS_FPS). If neither flag is selected,
			   then no frame rate is displayed.
			   Added two flags : DEFAULT_SINGLE_BUFFER and DEFAULT_
			   TRIPLE_BUFFER.
			   Changed function definition of D3DShellSetPreferences:
			   the "enum" as a parameter is not supported in C++, so
			   I replaced it with a DWORD.
			   Versioning to 2.1Beta.
  09/10/98 : - Added one new flag : FRAME_BUFFER_BIT_DEPTH.
			   Versioning to 2.0.2.
  06/10/98 : - Added two new flags : DEFAULT_USE_RGB_DEVICE and
			   START_WINDOW_320X200.
  01/10/98 : - Added the D3DShellGetVariable() function.
			   Added a new flag : DEFAULT_DISPLAYINFO_OFF.
			   Versioning to 2.0.1.
  18/09/98 : - Added a SetCooperativeLevel to Normal when FullScreen is
			   selected in D3DFEWindowProc if current DirectDraw device
			   is a secondary device.
  09/07/98 : - First version from D3DShell for DX 5.0.


  -------------------------------------------------------------
  | READ D3DSHELL.TXT FOR FURTHER INFORMATION ABOUT D3DSHELL  |
  -------------------------------------------------------------

  Email any comments or feedback to nthibieroz@videologic.com

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef INITGUID
#define INITGUID			/* Must be set up before everything */
#endif

#define D3D_OVERLOADS
/*************************
**		  Includes	    **
*************************/
#include <windowsx.h>
#include <ddraw.h>			/* DirectDraw header */
#include <d3d.h>			/* D3D header */


#define _DEBUG 

#include "D3DShell.h"		/* D3D Shell include */


/* DirectDraw errors 
   This header can be included (and linked with the 
   DDError.c file) to report DirectDraw errors */
#include "DDError.h"
#ifndef DDERROR_H
#define DisplayHRESULTInDebug(x)
#endif

/* Dreamcast Logo */
#include "DCLogo.dat"

/*************************
**		  Defines	    **
*************************/
#define	FRAMESBEFOREKILLING	20	/* Application will auto finishes after 20 frames */

#define	DD_MAXDDDRIVERS		32	/* Maximum DD driver we ever expect to find */
#define DD_MAXDISPLAYMODES	50	/* Maximum DD display modes we ever expect to find */
#define D3D_MAXD3DDRIVERS	10	/* Maximum D3D drivers we ever expect to find */

#define TIMER_PERIOD		2000	/* Frame rate will be computed every 2 s */

#ifndef ZeroMemory
	#define ZeroMemory(ptr,size) memset(ptr, 0, size)
#endif

#define wlstrcpy(ptr1,ptr2)	lstrcpy((unsigned short *)ptr1,(unsigned short *)ptr2)

#undef RELEASE
#define RELEASE(x)	if (x) { (x)->lpVtbl->Release(x); (x)=NULL; }
//#define RELEASE(x)		if (x) { wsprintf(pszTmp, "%s released. Ref count=%d\n", #x, (x)->lpVtbl->Release(x)); DEBUG_WCE(pszTmp); (x)=NULL; }

#define DEBUG_WCE(x)	OutputDebugString(x);

/* Uncomment the lines below to display debug messages on screen in a message box (not supported by Dreamcast)*/
/*
#define DEBUG_WCE(x)	OutputDebugString(x); MessageBox(D3DFE.hwnd, x, "Debug message", MB_OK | MB_ICONERROR)
char *ErrorToString(HRESULT hres);
#undef DisplayHRESULTInDebug
#define DisplayHRESULTInDebug(x)	DEBUG_WCE(ErrorToString(x))
*/


#define MAX_NUMBER_OF_ACCELERATORS		50		/* Maximum number of accelerators */
#define MAX_NUMBER_OF_STRINGS			50		/* Maximum number of strings */
#define MAX_NUMBER_OF_TEXTURE_FORMAT	30		/* Maximum number of texture formats */
#define MAX_NUMBER_OF_TEXTURES			256		/* Maximum number of textures */


/*************************
**		  Typedefs	    **
*************************/
typedef struct _DDDriverInfo
{	
	GUID			Guid;						/* DirectDraw driver Guid */
	LPGUID			lpGuid;						/* Pointer on DirectDraw driver Guid */
	char			Name[50];					/* Name of DirectDraw driver */
	char			Description[255];			/* Description of DirectDraw driver */
	DDCAPS			DDCaps;						/* DDCAPS of DirectDraw driver */
	BOOL			bCanRenderWindowed;			/* Indicates that this DD driver can render windowed */
	BOOL			bSharedVideoMemory;			/* Indicate if Frame buffer and Z-Buffer memory are shared */
	DWORD			dwPhysicalVideoMemory;		/* Amount of physical video memory for a DirectDraw driver */
	DWORD			dwTotalMemoryForZBuffer;	/* Total video memory to create Z-Buffer (variable) */
	DWORD			dwTotalMemoryForWindow;		/* Total video memory to create window (variable) */
} DDDriverInfo;


typedef struct _DDDisplayModeInfo
{
	DWORD			dwWidth;					/* Width (in pixels) of display mode */
	DWORD			dwHeight;					/* Height (in pixels) of display mode */
	DWORD			dwBPP;						/* Displsay mode colour depth */
	BOOL			bSupportedByD3DDriver;		/* Is this mode supported by current D3D driver ? */
} DDDisplayModeInfo;


typedef struct _D3DDriverInfo
{
	BOOL			bIsHardware;				/* hw or software driver */
	D3DDEVICEDESC	Desc;						/* D3DDEVICEDESC of D3D driver */
	BOOL			bSupportPalettised;			/* Does this D3D driver supports 8-bit palettised display modes ? */
	char			Name[50];					/* Name of D3D driver */
	char			About[255];					/* Description of D3D driver */
	GUID			Guid;						/* Guid of D3D driver */
} D3DDriverInfo;


typedef struct _TextureType
{
	DDPIXELFORMAT	ddPixelFormat;				/* Pixel format of texture */	
	int				RedBPP;						/* Red bits per pixel */
	int				GreenBPP;					/* Green bits per pixel */
	int				BlueBPP;					/* Blue bits per pixel */
	int				AlphaBPP;					/* Alpha bits per pixel */
} TextureType;


typedef struct _D3DFEVariables
{
	/* Dreamcast Logo texture */
	LPDIRECT3DTEXTURE2		lpDCLogoTexture;

	/* DirectDraw variables */
	LPDIRECTDRAW            lpDD;					/* DirectDraw object */
	LPDIRECTDRAW4           lpDD4;					/* DirectDraw4 object */
	LPDIRECTDRAWSURFACE4    lpDDSPrimary;			/* DirectDraw primary surface */
	LPDIRECTDRAWSURFACE4    lpDDSBack;				/* DirectDraw back surface */
	LPDIRECTDRAWSURFACE4	lpDDSZBuffer;			/* Z-Buffer surface */
	LPDIRECTDRAWCLIPPER		lpClipper;				/* DirectDraw clipper */
	LPDIRECTDRAWPALETTE		lpPalette;				/* DirectDraw palette */
	
	/* Direct3D variables (DrawPrimitive) */
	LPDIRECT3D3             lpD3D3;					/* Direct3D3 object */
	LPDIRECT3DDEVICE3       lpD3DDev3;				/* Direct3D device 3 */
	LPDIRECT3DVIEWPORT3		lpD3DView3;				/* Direct3D viewport 3 */

	/* Window management variables */
	MSG						msg;					/* WindowProc messages */
	HWND					hwnd;					/* window handle */
	WNDCLASS				wndclass;				/* window class */
	HINSTANCE				hPreviousInstance;		/* Previous instance */
	HICON					hIcon;					/* Application icon */
	DWORD					dwGDIWidth;				/* GDI screen width */
	DWORD					dwGDIHeight;			/* GDI screen height */
	DWORD					dwGDIBPP;				/* GDI screen colour depth */
	
	/* Window information variables */
	DWORD					dwWindowStyle;			/* Style of window */
	DWORD					dwWindowPositionX;		/* Window position (X) */
	DWORD					dwWindowPositionY;		/* Window position (Y) */
	DWORD					dwWindowWidth;			/* Window width */
	DWORD					dwWindowHeight;			/* Window height */
	DWORD					dwWindowFramePositionX;	/* Window frame position (X) */
	DWORD					dwWindowFramePositionY;	/* Window frame position (Y) */
	DWORD					dwWindowFrameWidth;		/* Window frame width */
	DWORD					dwWindowFrameHeight;	/* Window frame height */
	DWORD					dwWindowSpaceX;			/* Total space between window frame width and client area width */
	DWORD					dwWindowSpaceY;			/* Total space between window frame height and client area height */
	DWORD					dwMaxWindowWidth;		/* Max window width */
	DWORD					dwMaxWindowHeight;		/* Max window height */
	DWORD					dwMinWindowWidth;		/* Min Window width */
	DWORD					dwMinWindowHeight;		/* Min window height */
	BOOL					bMenuTakesMoreThanOneLine;	/* Needed to display information text at correct location */
	
	/* Booleans */
	BOOL					bPaused;				/* FrontEnd paused ? */
	BOOL					bMinimized;				/* FrontEnd minimized ? */
	BOOL					bRenderingReady;		/* Are all the variables set up and ready to render ? */
	BOOL					bIgnoreWM_SIZE;			/* Ignore the WM_SIZE window message ? */
	BOOL					bFullScreen;			/* Are we in FullScreen mode ? */
	BOOL					bZBufferNeeded;			/* Do we need a Z-Buffer ? */
	BOOL					bClearViewport;			/* Will the viewport be cleared before each frame ? */
	BOOL					bDisplayHasChanged;		/* Needed to recreate window mode after restore from minimise state */
	BOOL					bInitViewWasCalled;		/* Needed to avoid calling ReleaseView() more than once */
	BOOL					bAutoKill;				/* Application will auto-finish after FRAMESBEFOREKILLING frames */
	BOOL					bDisableZClear;			/* Did the user specify DISABLE_Z_CLEAR ? */
	
	/* Rendering variables */
	int						nBufferingMode;			/* Single buffer, Double buffer(default) or triple buffer */
	DDPIXELFORMAT			ddpfZBufferFormat;		/* Pixel format for Z-Buffer */
	int						nCurrentDDDriver;		/* Number of current Direct Draw driver */
	int						nCurrentResolution;		/* Number of current display mode */
	int						nCurrentD3DDriver;		/* Number of current D3D driver */
	DWORD					dwFrameRate;			/* Current frame rate */
	DWORD					dwFramesElapsed;		/* Number of frames elapsed in TIMER_PERIOD ms */
	
	/* Texture variables */
	int						nTextures;
	int						nTextureFormat;
	int						nBestOpaqueFormat;
	int						nBestTransFormat;
	
	/* User variables */
	DWORD					dwUserPreferences;		/* Flag to retrieve user preferences */
	TCHAR					pszFrontEndTitle[100];	/* Title of application */
} D3DFEVariables;


/*************************
**		  Globals	    **
*************************/

/* D3DShell variables structure */
D3DFEVariables		D3DFE;

/* Array of all the textures */
struct _TextureArray
{
    LPDIRECTDRAWSURFACE4    lpDDSTextureSurface[MAX_NUMBER_OF_TEXTURES];	/* Texture surface */
    LPDIRECT3DTEXTURE2      lpTex2[MAX_NUMBER_OF_TEXTURES];					/* Texture interface */
} TextureArray;

/* Array of all textures formats */
TextureType TextureFormat[MAX_NUMBER_OF_TEXTURE_FORMAT];

/* Enumeration callback variables */
DDDriverInfo		DDDriver[DD_MAXDDDRIVERS];			/* Array to store all DD drivers */
int					nDDNumDrivers=0;					/* Total number of Direct Draw drivers */

DDDisplayModeInfo	DDDisplayMode[DD_MAXDISPLAYMODES][DD_MAXDDDRIVERS];	/* Array to store all Display modes for a particular DirectDraw device */
int					nDDNumDisplayModes[DD_MAXDDDRIVERS];				/* Total number of display modes supported by Direct Draw driver */
int					nSafeDisplayModeNumber[DD_MAXDDDRIVERS];			/* Number of "safe" display mode (usually 640x480x16) */

D3DDriverInfo		D3DDriver[D3D_MAXD3DDRIVERS][DD_MAXDDDRIVERS];		/* Array to store all D3D drivers */
int					nD3DNumDrivers[DD_MAXDDDRIVERS];					/* Total number of D3D driver */


/* General string used to display text */
TCHAR				pszTmp[512];

														
/************************
******* Prototypes ******
************************/
void				D3DFEInitFrontEnd();
void				D3DFEFinish();
void				D3DFEReleaseAll();
void				D3DFEReleaseTextures();
BOOL				D3DFECheckForLostSurfaces();
BOOL				D3DFECheckRenderingVariables(int *pnDirectDrawDriver, BOOL *pbFullScreen, int *pnResolution, BOOL *pbZBufferNeeded, int *pnBufferingMode, int *pnDirect3DDriver, BOOL bScreenModeSelected);
BOOL				D3DFEInitialiseDirect3D(int nDirectDrawDriver, BOOL bFullScreen, int nResolution, BOOL bZBufferNeeded, int nBufferingMode, int nDirect3DDriver);
BOOL				D3DFEListTextureFormats(LPDIRECT3DDEVICE3 lpDev3);
HRESULT WINAPI		D3DFEEnumZBufferFormatsCallback(DDPIXELFORMAT *lpddPixelFormat, LPVOID lpContext);
BOOL WINAPI			D3DFEEnumDirectDrawCallback(GUID FAR* lpGuid, LPTSTR lpDriverDesc, LPTSTR lpDriverName, LPVOID lpContext);
BOOL WINAPI			D3DFEEnumDirectDrawExCallback(GUID FAR* lpGuid, LPTSTR lpDriverDesc, LPTSTR lpDriverName, LPVOID lpContext, HMONITOR hm);
HRESULT WINAPI		D3DFEEnumDisplayModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);
HRESULT CALLBACK	D3DFEEnumD3DDeviceDriverCallback(LPGUID lpGuid, LPTSTR lpDeviceDescription, LPTSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpUserArg);
HRESULT	WINAPI		D3DFEEnumTextureFormatsCallback(LPDDPIXELFORMAT lpddPixelFormat, LPVOID lpContext);
BOOL				D3DFERender();
DWORD				D3DFEFreeVideoMemoryInfo(LPDIRECTDRAW4 lpDD4, DWORD dwCaps);
DWORD				D3DFETotalVideoMemoryInfo(LPDIRECTDRAW4 lpDD4, DWORD dwCaps);
BOOL				D3DFECheckVideoMemoryForWindowMode(int nDirectDrawDriver, DWORD dwWidth, DWORD dwHeight, BOOL bZBuffer);
BOOL				D3DFECheckVideoMemoryForFullScreenMode(int nDirectDrawDriver, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, BOOL bZBuffer, int nBufferingMode, DWORD dwFrameBufferMemory, DWORD dwZBufferMemory);
int					D3DFEGetHALDriver(int nDDDriver);
int WINAPI			WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
long CALLBACK		D3DFEWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void				D3DFEDisplayText();
void CALLBACK		D3DFETimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void				D3DFEDisplayInfoAboutSurfaces();
void				D3DFEClearSurface(LPDIRECTDRAWSURFACE4 lpDDSSurface);
void				D3DFERemoveString(char *pszString, char *pszStringToRemove);
BOOL				D3DFEGuidCompare(GUID *pGuid1, GUID *pGuid2);
DWORD				D3DFEBPPToDDBD(int bpp);
void				D3DShellGetResourceBitmap(BITMAP *bm, LPCWSTR lpName);
float				GetFPS (void);
BOOL				LoadDCLogo(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPDIRECT3DTEXTURE2 *lplpD3DTexture2);

/************************
******* Functions *******
************************/


/*******************************************************************************
 * Function Name  : D3DFEInitFrontEnd
 * Returns        : Nothing
 * Global Used    : D3DFE
 * Description    : Perform variables initialisation
 *******************************************************************************/
void D3DFEInitFrontEnd()
{
	/* Init DirectDraw variables */
	D3DFE.lpDD=NULL;				
	D3DFE.lpDD4=NULL;					
	D3DFE.lpDDSPrimary=NULL;
	D3DFE.lpDDSBack=NULL;		
	D3DFE.lpDDSZBuffer=NULL;			
	D3DFE.lpClipper=NULL;				
	D3DFE.lpPalette=NULL;				
	
	/* Init Direct3D variables */
	D3DFE.lpD3D3=NULL;					
	D3DFE.lpD3DDev3=NULL;				
	D3DFE.lpD3DView3=NULL;				
	
	/* Init window variables */
	D3DFE.dwWindowStyle=0;
	D3DFE.dwWindowWidth=640;
	D3DFE.dwWindowHeight=480;
	D3DFE.dwMaxWindowWidth=1024;
	D3DFE.dwMaxWindowHeight=768;
	D3DFE.dwMinWindowWidth=128;
	D3DFE.dwMinWindowHeight=128;

	/* Init Booleans */
	D3DFE.bPaused=TRUE;
	D3DFE.bIgnoreWM_SIZE=TRUE;
	D3DFE.bMinimized=FALSE;
	D3DFE.bZBufferNeeded=FALSE;
	D3DFE.bRenderingReady=FALSE;
	D3DFE.bFullScreen=TRUE;
	D3DFE.bClearViewport=FALSE;
	D3DFE.bDisplayHasChanged=FALSE;
	D3DFE.bInitViewWasCalled=FALSE;
	D3DFE.bAutoKill=FALSE;
	D3DFE.bDisableZClear=FALSE;
	
	/* Init rendering variables */
	D3DFE.nBufferingMode=2;
	D3DFE.nCurrentDDDriver=-1;
	D3DFE.nCurrentResolution=-1;
	D3DFE.nCurrentD3DDriver=-1;
	
	/* Init texture variables */
	D3DFE.nTextures=0;
	D3DFE.nTextureFormat=0;
	D3DFE.nBestOpaqueFormat=-1;
	D3DFE.nBestTransFormat=-1;

	/* User rendering variables */
	D3DFE.dwUserPreferences=0;
	lstrcpy(D3DFE.pszFrontEndTitle, L"D3DShell");
	D3DFE.dwFrameRate=0;
	D3DFE.dwFramesElapsed=0;
}


/*******************************************************************************
 * Function Name  : D3DFEFinish
 * Returns        : Nothing
 * Global Used    : D3DFE
 * Description    : Quit program
 *******************************************************************************/
void D3DFEFinish()
{
	/* Set states */
	D3DFE.bPaused=TRUE;
	D3DFE.bRenderingReady=FALSE;

	/* Send a WM_DESTROY message to the event loop */
	DestroyWindow(D3DFE.hwnd);		
}


/*******************************************************************************
 * Function Name  : D3DFEReleaseAll
 * Returns        : Nothing
 * Global Used    : D3DFE
 * Description    : Release all memory used by DirectDraw and D3D variables
 *******************************************************************************/
void D3DFEReleaseAll()
{
   		
	/* Set state */
	D3DFE.bRenderingReady=FALSE;
	
	/* Release textures */
	D3DFEReleaseTextures();

	/* Release DCLogo texture */
	RELEASE(D3DFE.lpDCLogoTexture);
	
	/* Call ReleaseView (not more than once thanks to bInitViewWasCalled) */
	if (D3DFE.bInitViewWasCalled)
	{
		ReleaseView(D3DFE.lpD3DView3);
		D3DFE.bInitViewWasCalled=FALSE;
	}
	
	/* Delete viewport */
	if (D3DFE.lpD3DView3)
	{
		D3DFE.lpD3DDev3->lpVtbl->DeleteViewport(D3DFE.lpD3DDev3, D3DFE.lpD3DView3);
	}
	/* Release Viewport */
	RELEASE(D3DFE.lpD3DView3);
	
	/* Release 3D device */
	RELEASE(D3DFE.lpD3DDev3);
	
	/* If a Z-Buffer exists, then detach it from surface */
	if (D3DFE.lpDDSZBuffer)
	{
		if (D3DFE.lpDDSBack)
		{
			/* If there is a back buffer, then Z Buffer must be attached to it */
			if (D3DFE.lpDDSBack->lpVtbl->DeleteAttachedSurface(D3DFE.lpDDSBack, 0, D3DFE.lpDDSZBuffer)!=DD_OK)
			{
				DEBUG_WCE(L"Failed to delete Z-Buffer surface from back buffer in D3DReleaseAll()\n");
			}
		}
		else
		{
			/* No back buffer -> Z Buffer is attached to primary surface */
			if (D3DFE.lpDDSPrimary->lpVtbl->DeleteAttachedSurface(D3DFE.lpDDSPrimary, 0, D3DFE.lpDDSZBuffer)!=DD_OK)
			{
				DEBUG_WCE(L"Failed to delete Z-Buffer surface from primary surface in D3DReleaseAll()\n");
			}
		}
	}
	/* Release Z-Buffer */
	RELEASE(D3DFE.lpDDSZBuffer);
	
	
	/* Detach palette */
	if (D3DFE.lpPalette)
	{
		DEBUG_WCE(L"Releasing palettes\n");
		if (D3DFE.lpDDSBack)
		{
			D3DFE.lpDDSBack->lpVtbl->SetPalette(D3DFE.lpDDSBack, NULL);
		}
		D3DFE.lpDDSPrimary->lpVtbl->SetPalette(D3DFE.lpDDSPrimary, NULL);
	}
	/* Release palette */
	RELEASE(D3DFE.lpPalette);
	
	/* Release back buffer */
	RELEASE(D3DFE.lpDDSBack);
	
	/* Release Primary surface (will also release back buffer(s) if created for FullScreen mode) */
	RELEASE(D3DFE.lpDDSPrimary);
	
	/* Release Direct3D3 interface */
	RELEASE(D3DFE.lpD3D3);
	
	/* Release DirectDraw4 interface */
	RELEASE(D3DFE.lpDD4);
	
	/* Release main DirectDraw object */
	RELEASE(D3DFE.lpDD);

} 


/*******************************************************************************
 * Function Name  : D3DFEReleaseTextures
 * Returns        : Nothing
 * Global Used    : D3DFE
 * Description    : Release all textures
 *******************************************************************************/
void D3DFEReleaseTextures()
{
	int i;

    /* Use no texture */
	if (D3DFE.lpD3DDev3)
	{
		D3DFE.lpD3DDev3->lpVtbl->SetTexture(D3DFE.lpD3DDev3, 0, NULL);
	}
	
	/* Loop through all textures and release them */
	for (i=0; i<D3DFE.nTextures; i++)
	{
		RELEASE(TextureArray.lpTex2[i]);
		RELEASE(TextureArray.lpDDSTextureSurface[i]);
	}
	    
	/* Reset texture variables */
	D3DFE.nTextures=0;
	D3DFE.nTextureFormat=0;
	D3DFE.nBestOpaqueFormat=-1;
	D3DFE.nBestTransFormat=-1;
}


/*******************************************************************************
 * Function Name  : D3DFECheckForLostSurfaces
 * Returns        : TRUE or FALSE
 * Global Used    : D3DFE
 * Description    : Restore surfaces that might have been lost
 *******************************************************************************/
BOOL D3DFECheckForLostSurfaces()
{
	HRESULT hres;
	BOOL	bTexturesRestored=FALSE;
	BOOL	bZBufferRestored=FALSE;
	BOOL	bFrontBufferRestored=FALSE;
	BOOL	bInFlag=TRUE;
	int		i;

	/* Restore textures if lost (that should be taken care of by the D3D 
	   automatic texture management, but let's be sure) */
	for (i=0; i<D3DFE.nTextures;i++)
	{
		if (TextureArray.lpDDSTextureSurface[i]->lpVtbl->IsLost(TextureArray.lpDDSTextureSurface[i])==DDERR_SURFACELOST)
		{
			hres=TextureArray.lpDDSTextureSurface[i]->lpVtbl->Restore(TextureArray.lpDDSTextureSurface[i]);
			if (hres!=DD_OK)
			{
				wsprintf(pszTmp, L"D3DShell *ERROR* : Failed to restore texture surface %d\n", i);
				DEBUG_WCE(pszTmp);
				DisplayHRESULTInDebug(hres);
				bInFlag=FALSE;
			}
			bTexturesRestored=TRUE;
		}
	}
	
	/* Check if Z-Buffer surface is lost */
	if (D3DFE.lpDDSZBuffer) 
	{
		if (D3DFE.lpDDSZBuffer->lpVtbl->IsLost(D3DFE.lpDDSZBuffer)==DDERR_SURFACELOST)
		{
			hres=D3DFE.lpDDSZBuffer->lpVtbl->Restore(D3DFE.lpDDSZBuffer);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : Failed to restore Z-Buffer surface\n");
				DisplayHRESULTInDebug(hres);
				bInFlag=FALSE;
			}
			bZBufferRestored=TRUE;
		}
	}
	
	/* Check if Primary surface is lost 
	   If back buffer(s) have been created through the primary surface by use
	   of the DDSCAPS_COMPLEX flag, then the back buffer(s) will be
	   automatically restored when the primary surface is restored */
	if (D3DFE.lpDDSPrimary) 
	{
		if (D3DFE.lpDDSPrimary->lpVtbl->IsLost(D3DFE.lpDDSPrimary)==DDERR_SURFACELOST)
		{
			hres=D3DFE.lpDDSPrimary->lpVtbl->Restore(D3DFE.lpDDSPrimary);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : Failed to restore primary surface\n");
				DisplayHRESULTInDebug(hres);
				bInFlag=FALSE;
			}
			bFrontBufferRestored=TRUE;
		}
	}

	/* Debug info */
#ifdef _DEBUG
	if (bTexturesRestored)
	{
		DEBUG_WCE(L"D3DShell : Textures surfaces have been restored.\n");
	}
	if (bZBufferRestored)
	{
		DEBUG_WCE(L"D3DShell : Z-Buffer surface has been restored.\n");
	}
	if (bFrontBufferRestored)
	{
		DEBUG_WCE(L"D3DShell : Front buffer surface has been restored.\n");
	}
#endif

	/* Return status */
	return (bInFlag);
}
/*******************************************************************************
 * Function Name  : D3DFEInitialiseDirect3D
 * Returns        : TRUE if no error occured
 * Global Used    : D3DFE,
 *					DDDriver[], nDDNumDisplayModes, nD3DNumDrivers
 * Description    : Initialise everything for D3D use :
 *					- Create DirectDraw object
 *					- Get DirectDraw4 interface
 *					- Create a Direct3D3 interface
 *					- Build menus
 *					- if FullScreen :
 *						- Set Cooperative level to EXCLUSIVE and FULLSCREEN
 *						- Set display mode to current selection
 *						- Create a complex Primary surface with the selected number
 *						  of back buffers (Single buffer, Double buffer or Triple buffer)
 *						- Retrieve variable to back buffer.
 *					- if Windowed :
 *						- Set Cooperative level to NORMAL
 *						- Create Primary and Back buffer (surfaces)
 *						- Create clipper and attach it to Primary surface
 *					- Create palette and attach it to front and back buffer
 *					  for 8-bit modes.
 *					- Create Z-Buffer if required.
 *					- Create Buffer Info surface if required.
 *					- Create D3D device
 *
 *******************************************************************************/
BOOL D3DFEInitialiseDirect3D(int nDirectDrawDriver, 
							 BOOL bFullScreen, int nResolution,
							 BOOL bZBufferNeeded, int nBufferingMode, 
							 int nDirect3DDriver)
{
	HRESULT			hres;
	DDSURFACEDESC2	ddsd;
	D3DVIEWPORT2	ViewData2;
	DDSCAPS2		ddscaps;
	DWORD			dwCurrentWidth, dwCurrentHeight;
	float			inv_aspect;

	/************
	** Asserts **
	************/
	ASSERT(D3DFE.lpDD==NULL);
	ASSERT(D3DFE.lpDD4==NULL);
	ASSERT(D3DFE.lpD3D3==NULL);
	ASSERT(D3DFE.nCurrentDDDriver!=-1);
	ASSERT(D3DFE.nBufferingMode>=1 && D3DFE.nBufferingMode<=3);
	ASSERT(D3DFE.lpDDSPrimary==NULL);
	ASSERT(D3DFE.lpDDSBack==NULL);
	ASSERT(D3DFE.lpClipper==NULL);
	ASSERT(D3DFE.lpDDSZBuffer==NULL);
	ASSERT(D3DFE.lpD3DDev3==NULL);
	ASSERT(D3DFE.lpD3DView3==NULL);

		
/* Debug info */
#ifdef _DEBUG
	DEBUG_WCE(L"*******************************\n");
	DEBUG_WCE(L"** D3DShell Initialising D3D **\n");
	DEBUG_WCE(L"*******************************\n");
#endif

	/* Set states */
	D3DFE.bPaused=TRUE;
	D3DFE.bRenderingReady=FALSE;

	/* Set globals */
	D3DFE.nCurrentDDDriver=		nDirectDrawDriver;
	D3DFE.bFullScreen=			bFullScreen;
	D3DFE.nCurrentResolution=	nResolution;
	D3DFE.bZBufferNeeded=		bZBufferNeeded;
	D3DFE.nBufferingMode=		nBufferingMode;
	D3DFE.nCurrentD3DDriver=	nDirect3DDriver;
	
	
	/******************************
	** DirectDraw initialisation **
	******************************/

	/* Create D3DFE.lpDD for the DirectDraw driver currently selected */
    hres=DirectDrawCreate(&DDDriver[D3DFE.nCurrentDDDriver].Guid, &D3DFE.lpDD, NULL);
    if (hres!=DD_OK)
    {
       	DEBUG_WCE(L"D3DShell *ERROR* : DirectDrawCreate failed\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
    }

	/* Query interface for DirectDraw 4 */
	hres=D3DFE.lpDD->lpVtbl->QueryInterface(D3DFE.lpDD, &IID_IDirectDraw4, &D3DFE.lpDD4);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *ERROR* : QueryInterface for DirectDraw4 failed\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}

	/* Let's get Direct3D3 */
    hres=D3DFE.lpDD4->lpVtbl->QueryInterface(D3DFE.lpDD4, &IID_IDirect3D3, &D3DFE.lpD3D3);
    if (hres!=DD_OK) 
	{
    	DEBUG_WCE(L"D3DShell *ERROR* : QueryInterface failed for Direct3D3 failed\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}



	/* Perform FullScreen */
	/*******************************
	** Initialise FullScreen mode **
	*******************************/
		
		/* Set cooperative level to exclusive, fullscreen mode 
		   Set D3DFE.bIgnoreWM_SIZE because SetCooperativeLevel causes such a message
		   and we don't need to change the buffers in that case */
		D3DFE.bIgnoreWM_SIZE=TRUE;
		hres=D3DFE.lpDD4->lpVtbl->SetCooperativeLevel(D3DFE.lpDD4, D3DFE.hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		D3DFE.bIgnoreWM_SIZE=FALSE;
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : SetCooperativeLevel() (EXCLUSIVE | FULLSCREEN) failed.\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
		}

		/* Debug output */
#ifdef _DEBUG
		wsprintf(pszTmp, L"Switching to %ux%ux%u\n",  DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth, 
													DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight, 
													DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwBPP);
		DEBUG_WCE(pszTmp);
#endif

		/* Set the video mode to current resolution */
		D3DFE.bIgnoreWM_SIZE=TRUE;
		hres=D3DFE.lpDD4->lpVtbl->SetDisplayMode(D3DFE.lpDD4, DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth,
															  DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight, 
															  DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwBPP, 0, 0);
		D3DFE.bIgnoreWM_SIZE=FALSE;
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : SetDisplayMode failed\n");
			DisplayHRESULTInDebug(hres);
			wsprintf(pszTmp, L"Unable to set display mode to %ux%ux%u\nExiting program", 
							 DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth,
							 DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight, 
							 DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwBPP);
			return FALSE;
		}

		/* Clear DDSURFACEDESC2 structure */
		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize=sizeof(ddsd);

		/* If we are using a single buffered mode, just create primary surface */
		if (D3DFE.nBufferingMode==1)
		{
			ddsd.dwFlags=DDSD_CAPS;
			ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
			hres=D3DFE.lpDD4->lpVtbl->CreateSurface(D3DFE.lpDD4, &ddsd, &D3DFE.lpDDSPrimary, NULL);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : CreateSurface() failed (D3DFE.lpDDSPrimary)\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}
			
			/* Get surface description of primary buffer */
			hres=D3DFE.lpDDSPrimary->lpVtbl->GetSurfaceDesc(D3DFE.lpDDSPrimary, &ddsd);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : GetSurfaceDesc() (Primary surface) failed.\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}
		}
		else
		{
			/* Otherwise create a primary surface with one (double buffer) 
			   or two (triple buffer) back buffers */
			ddsd.dwFlags=DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			ddsd.ddsCaps.dwCaps =	DDSCAPS_PRIMARYSURFACE | 
									DDSCAPS_FLIP |
									DDSCAPS_3DDEVICE |
									DDSCAPS_COMPLEX;
			ddsd.dwBackBufferCount=D3DFE.nBufferingMode-1;
			hres=D3DFE.lpDD4->lpVtbl->CreateSurface(D3DFE.lpDD4, &ddsd, &D3DFE.lpDDSPrimary, NULL);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : CreateSurface() failed (Primary surface).\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}

			/* Retrieve variable to back buffer */
			ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
			hres=D3DFE.lpDDSPrimary->lpVtbl->GetAttachedSurface(D3DFE.lpDDSPrimary, &ddscaps, &D3DFE.lpDDSBack);
			if( hres!=DD_OK )
			{
				DEBUG_WCE(L"D3DShell *ERROR* : GetAttachedSurface() (for Back buffer) failed\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}

			/* Get surface description of back buffer */
			hres=D3DFE.lpDDSBack->lpVtbl->GetSurfaceDesc(D3DFE.lpDDSBack, &ddsd);
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : GetSurfaceDesc() (of Back buffer) failed.\n");	
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}
		}

	

	/*****************************
	** 3D Device initialisation **
	*****************************/
	/* Do we need a Z-Buffer ? */
	if (D3DFE.bZBufferNeeded)
	{
		/* First enumerate all Z-Buffer formats */
		hres=D3DFE.lpD3D3->lpVtbl->EnumZBufferFormats(D3DFE.lpD3D3, 
													  &D3DDriver[D3DFE.nCurrentD3DDriver][D3DFE.nCurrentDDDriver].Guid, 
													  D3DFEEnumZBufferFormatsCallback,
													  NULL);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : EnumZBufferFormats() failed.\n");
			D3DFE.bZBufferNeeded=FALSE;
		}
		else
		{
			/* Clear DDSURFACEDESC2 structure */
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize=sizeof(DDSURFACEDESC2);
		
			/* Set up Z-Buffer creation info */
			ddsd.dwFlags=DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
			
			ddsd.dwWidth=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth;
			ddsd.dwHeight=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight;
			
			memcpy(&ddsd.ddpfPixelFormat, &D3DFE.ddpfZBufferFormat, sizeof(DDPIXELFORMAT));
			ddsd.ddsCaps.dwCaps=DDSCAPS_ZBUFFER;

			/* If D3D Driver is hardware, then use Video Memory for Z-Buffer */
			if (D3DDriver[D3DFE.nCurrentD3DDriver][D3DFE.nCurrentDDDriver].bIsHardware)
			{
				ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
			}
			else
			{
				ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
			}

			/* Create it */
			hres=D3DFE.lpDD4->lpVtbl->CreateSurface(D3DFE.lpDD4,  &ddsd, &D3DFE.lpDDSZBuffer, NULL);
			if (hres==DDERR_OUTOFVIDEOMEMORY || hres==DDERR_OUTOFMEMORY) 
			{
				DEBUG_WCE(L"D3DShell *ERROR* : Not enough memory to create Z-Buffer.\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}
			else
			if (hres!=DD_OK)
			{
				DEBUG_WCE(L"D3DShell *ERROR* : CreateSurface() (Z-Buffer) failed.\n");
				DisplayHRESULTInDebug(hres);
				return FALSE;
			}
		
			/* If a back buffer exists, then attach the Z-Buffer to it */
			if (D3DFE.lpDDSBack)
			{
				/* Attach the Z-buffer to the back buffer */
				hres=D3DFE.lpDDSBack->lpVtbl->AddAttachedSurface(D3DFE.lpDDSBack, D3DFE.lpDDSZBuffer);
				if (hres!=DD_OK)
				{
					DEBUG_WCE(L"D3DShell *ERROR* : AddAttachedSurface() (Z-Buffer to Back buffer) failed.\n");
					DisplayHRESULTInDebug(hres);
					return FALSE;
				}
			}
			else
			{
				/* Attach the Z-buffer to the primary buffer */
				hres=D3DFE.lpDDSPrimary->lpVtbl->AddAttachedSurface(D3DFE.lpDDSPrimary, D3DFE.lpDDSZBuffer);
				if (hres!=DD_OK)
				{
					DEBUG_WCE(L"D3DShell *ERROR* : AddAttachedSurface() (Z-Buffer to Primary surface) failed.\n");
					DisplayHRESULTInDebug(hres);
					return FALSE;
				}
			}
		}
	}

	/* DEBUG_WCE Info : display some info about surfaces */
#ifdef _DEBUG
	D3DFEDisplayInfoAboutSurfaces();
#endif

	/* If a Back Buffer exist, create and attach D3D device to it */
	if (D3DFE.lpDDSBack)
	{
		/* Create the Direct3D device 3 selected and attach it to the back buffer */
		hres=D3DFE.lpD3D3->lpVtbl->CreateDevice(D3DFE.lpD3D3, &D3DDriver[D3DFE.nCurrentD3DDriver][D3DFE.nCurrentDDDriver].Guid, 
												D3DFE.lpDDSBack, &D3DFE.lpD3DDev3, NULL);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : CreateDevice() (D3D Device 3 to Back buffer) failed.\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
		}
	}
	else
	{
		/* Create the Direct3D device 3 selected and attach it to the front buffer */
		hres=D3DFE.lpD3D3->lpVtbl->CreateDevice(D3DFE.lpD3D3, &D3DDriver[D3DFE.nCurrentD3DDriver][D3DFE.nCurrentDDDriver].Guid, 
												D3DFE.lpDDSPrimary, &D3DFE.lpD3DDev3, NULL);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : CreateDevice() (D3D Device 3 to Front buffer) failed.\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
		}
	}
		

	/**************************
	** Create view and scene **
	**************************/
	/* Create a Viewport 3 interface */
	hres=D3DFE.lpD3D3->lpVtbl->CreateViewport(D3DFE.lpD3D3, &D3DFE.lpD3DView3, NULL);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *ERROR* : CreateViewport() failed.\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}
	
	/* Add viewport */
	hres=D3DFE.lpD3DDev3->lpVtbl->AddViewport(D3DFE.lpD3DDev3, D3DFE.lpD3DView3);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *ERROR* : AddViewport() failed.\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}
	
	/* Setup the viewport for the viewing area */
	ZeroMemory(&ViewData2, sizeof(ViewData2));
	ViewData2.dwSize=sizeof(ViewData2);
	ViewData2.dwX=0;
	ViewData2.dwY=0;
	
	ViewData2.dwWidth=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth;
	ViewData2.dwHeight=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight;
	
	inv_aspect = (float)ViewData2.dwHeight/ViewData2.dwWidth;
	ViewData2.dvClipX = -1.0f;
	ViewData2.dvClipY = inv_aspect;
    ViewData2.dvClipWidth = 2.0f;
    ViewData2.dvClipHeight = 2.0f * inv_aspect;
    ViewData2.dvMinZ = 0.0f;
    ViewData2.dvMaxZ = 1.0f;

	/* Set viewport */
	hres=D3DFE.lpD3DView3->lpVtbl->SetViewport2(D3DFE.lpD3DView3, &ViewData2);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *ERROR* : SetViewport2() failed.\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}

	/* SetCurrentViewport (new to DirectX 6.0) */
	hres=D3DFE.lpD3DDev3->lpVtbl->SetCurrentViewport(D3DFE.lpD3DDev3, D3DFE.lpD3DView3);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *ERROR* : SetCurrentViewport() failed\n");
		DisplayHRESULTInDebug(hres);
		return FALSE;
	}
	 
	/* Get dimensions of rendering surface */
	dwCurrentWidth=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth;
	dwCurrentHeight=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight;
	
	/* Call user function InitView to initialise the user rendering */
	if (!(InitView(D3DFE.lpDD4, D3DFE.lpD3D3, D3DFE.lpD3DDev3, D3DFE.lpD3DView3, dwCurrentWidth, dwCurrentHeight)))
	{
		DEBUG_WCE(L"D3DShell *ERROR* : InitView() failed.\n");
		return FALSE;
	}

	/* Update status */
	D3DFE.bInitViewWasCalled=TRUE;
	 	
	/* Set status */
	D3DFE.bRenderingReady=TRUE;
	D3DFE.bPaused=FALSE;
	D3DFE.bDisplayHasChanged=FALSE;
	
	/* New rendering variables have been set up correctly */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : D3DFEListTextureFormats
 * Inputs		  : lpDev3
 * Description    : List all available texture formats for the current D3D
 *				    driver by calling the texture format enumeration callback.
 *****************************************************************************/
BOOL D3DFEListTextureFormats(LPDIRECT3DDEVICE3 lpDev3)
{
	HRESULT hres;
	int		i;
	int		tr=0, tg=0, tb=0, ta=0;
	int		r=0,g=0,b=0,a=0;
	int		bUse16BitsTextures=TRUE;
    
	/* Set default values */
	D3DFE.nBestOpaqueFormat=-1;
    D3DFE.nBestTransFormat=-1;
    D3DFE.nTextureFormat=0;

    /* Call texture format enumeration function */
	hres=lpDev3->lpVtbl->EnumTextureFormats(lpDev3, D3DFEEnumTextureFormatsCallback, NULL);
    if (hres!=DD_OK) 
	{
        DEBUG_WCE(L"D3DShell *ERROR* : Enumeration of texture formats failed.");
        return FALSE;
    }

	/* Because all texture formats were enumerated in a row, go to next line */
#ifdef _DEBUG
	DEBUG_WCE(L"\n");
#endif

	/* Parse all enumerated texture format to pick best opaque format */
	for (i=0;i<D3DFE.nTextureFormat;i++)
	{
		tr=TextureFormat[i].RedBPP;
		tg=TextureFormat[i].GreenBPP;
		tb=TextureFormat[i].BlueBPP;
		ta=TextureFormat[i].AlphaBPP;
				
		/* Select best opaque format */
		if (ta==0)
		{
			/* Check if current texture format channels are larger than the previous choice */
			if (tr+tg+tb>r+g+b)
			{
				/* If 16 bits textures have to be used, use them */
				if (bUse16BitsTextures)
				{
					if (tr+tg+tb<=16)
					{
						D3DFE.nBestOpaqueFormat=i;
						r=tr;
						g=tg;
						b=tb;
						a=0;
					}
				}
				else
				{
					/* Otherwise just pick the best format (with the most bits per colour channel) */
					D3DFE.nBestOpaqueFormat=i;
					r=tr;
					g=tg;
					b=tb;
					a=0;
				}
			}
		}
	}

	/* Reset values to 0 */
	r=0; g=0; b=0; a=0;

	/* Parse all enumerated texture format to pick best translucent format */
	for (i=0;i<D3DFE.nTextureFormat;i++)
	{
		tr=TextureFormat[i].RedBPP;
		tg=TextureFormat[i].GreenBPP;
		tb=TextureFormat[i].BlueBPP;
		ta=TextureFormat[i].AlphaBPP;
		
		/* Check if current alpha channel is larger than the previous choice */
		if (ta>a)
		{
			/* If 16 bits textures have to be used, use them */
			if (bUse16BitsTextures)
			{
				if (tr+tg+tb+ta<=16)
				{
					D3DFE.nBestTransFormat=i;
					r=tr;
					g=tg;
					b=tb;
					a=ta;
				}
			}
			else
			{
				/* Otherwise just pick the best format (with the most bits in the alpha channel) */
				D3DFE.nBestTransFormat=i;
				r=tr;
				g=tg;
				b=tb;
				a=ta;
			}
		}
	}

	/* If best opaque format has not been found */
	if (D3DFE.nBestOpaqueFormat==-1) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : No opaque texture format was found.\n");
	}

	/* If best translucent format has not been found */
	if (D3DFE.nBestTransFormat==-1) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : No translucent texture format was found.\n");
	}
		
	/* No problem occured */
	return TRUE;
}


/*****************************************************************************
 * Function Name  : D3DFEEnumZBufferFormatsCallback
 * Inputs		  : *lpddPixelFormat, lpContext
 * Description    : D3D Callback function used to enumerate all Z-Buffer
 *					surfaces.
 *****************************************************************************/
HRESULT WINAPI D3DFEEnumZBufferFormatsCallback(DDPIXELFORMAT *lpddPixelFormat, LPVOID lpContext)
{
    /* If pixel format is NULL, then stop enumeration */
	if (!lpddPixelFormat)
	{
		return D3DENUMRET_CANCEL;
	}

    /* Pick up first Z-Buffer format available */
    if(lpddPixelFormat->dwFlags & DDPF_ZBUFFER)
    {
        memcpy(&D3DFE.ddpfZBufferFormat, lpddPixelFormat, sizeof(DDPIXELFORMAT));
		return D3DENUMRET_CANCEL;
    }

    /* Continue enumeration */
	return D3DENUMRET_OK;
}


/*******************************************************************************
 * Function Name  : D3DFEEnumDirectDrawCallback
 * Description    : Callback function which enumerates all available display
 *					modes for a DirectDraw device (for WIN95).
 ******************************************************************************/
BOOL WINAPI D3DFEEnumDirectDrawCallback(GUID FAR* lpGuid, LPTSTR lpDriverDesc, 
									    LPTSTR lpDriverName, LPVOID lpContext)
{
	LPDIRECTDRAW lpLocalDD;
	DDCAPS       DDCaps, HELCaps;
      
	/* Check that we do not exceed maximum number of DirectDraw drivers */
	if (nDDNumDrivers>=DD_MAXDDDRIVERS)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Reached maximum number of DirectDraw drivers.\n\n");
		return DDENUMRET_CANCEL;
	}
	
	/* Try to create a DD device using the specified GUID */
	if (DirectDrawCreate(lpGuid, &lpLocalDD, NULL )!=DD_OK)
	{
		/* Failed, so ignore this device */
		return DDENUMRET_OK;
	}

    /* Get caps of this DD driver. If it fails, move on to the next driver */
	memset(&DDCaps, 0, sizeof(DDCaps));
	DDCaps.dwSize=sizeof(DDCaps);
	memset(&HELCaps, 0, sizeof(HELCaps));
	HELCaps.dwSize=sizeof(HELCaps);
	if (lpLocalDD->lpVtbl->GetCaps(lpLocalDD, &DDCaps, &HELCaps)!=DD_OK)
	{
		RELEASE(lpLocalDD);
		return DDENUMRET_OK;
	}

	/* Everything's OK, so save this driver's info */
	if (lpGuid==NULL)
	{
		DDDriver[nDDNumDrivers].lpGuid=0;
	}
	else
	{
		DDDriver[nDDNumDrivers].lpGuid=&DDDriver[nDDNumDrivers].Guid;
		memcpy(&DDDriver[nDDNumDrivers].Guid, lpGuid, sizeof(GUID));
	}
	wlstrcpy (DDDriver[nDDNumDrivers].Name, lpDriverName);
	wlstrcpy (DDDriver[nDDNumDrivers].Description, lpDriverDesc);
	memcpy (&DDDriver[nDDNumDrivers].DDCaps, &DDCaps, sizeof(DDCAPS));

	/* Find out if this driver can render in a window */
	if ( (DDCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED) && lpGuid==NULL)
	{
		DDDriver[nDDNumDrivers].bCanRenderWindowed=TRUE;
	}
	else
	{
		DDDriver[nDDNumDrivers].bCanRenderWindowed=FALSE;
	}

	/* Debug output */
#ifdef _DEBUG
	wsprintf(pszTmp, L"DD Driver #%d :\nGuid=%u %u %u %s\nName=%s\nDescription=%s\n\n", nDDNumDrivers, 
			DDDriver[nDDNumDrivers].Guid.Data1, DDDriver[nDDNumDrivers].Guid.Data2, DDDriver[nDDNumDrivers].Guid.Data3, 
			DDDriver[nDDNumDrivers].Guid.Data4, DDDriver[nDDNumDrivers].Name, DDDriver[nDDNumDrivers].Description);
	DEBUG_WCE(pszTmp);
#endif

	/* Increase number of drivers found */
	nDDNumDrivers++;
		
	/* Release local memory */
	RELEASE(lpLocalDD);

	/* Continue enumeration */
	return DDENUMRET_OK;
}


/*******************************************************************************
 * Function Name  : D3DFEEnumDirectDrawExCallback
 * Description    : Callback function which enumerates all available display
 *					modes for a DirectDraw device (for WIN98+ only).
 ******************************************************************************/
BOOL WINAPI D3DFEEnumDirectDrawExCallback(GUID FAR* lpGuid, LPTSTR lpDriverDesc, 
										  LPTSTR lpDriverName, LPVOID lpContext, HMONITOR hm)
{
	LPDIRECTDRAW lpLocalDD;
	DDCAPS       DDCaps, HELCaps;
      
	/* Check that we do not exceed maximum number of DirectDraw drivers */
	if (nDDNumDrivers>=DD_MAXDDDRIVERS)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Reached maximum number of DirectDraw drivers.\n\n");
		return DDENUMRET_CANCEL;
	}
	
	/* Try to create a DD device using the specified GUID */
	if (DirectDrawCreate(lpGuid, &lpLocalDD, NULL )!=DD_OK)
	{
		/* Failed, so ignore this device */
		return DDENUMRET_OK;
	}

    /* Get caps of this DD driver. If it fails, move on to the next driver */
	memset(&DDCaps, 0, sizeof(DDCaps));
	DDCaps.dwSize=sizeof(DDCaps);
	memset(&HELCaps, 0, sizeof(HELCaps));
	HELCaps.dwSize=sizeof(HELCaps);
	if (lpLocalDD->lpVtbl->GetCaps(lpLocalDD, &DDCaps, &HELCaps)!=DD_OK)
	{
		RELEASE(lpLocalDD);
		return DDENUMRET_OK;
	}

	/* Everything's OK, so save this driver's info */
	if (lpGuid==NULL)
	{
		DDDriver[nDDNumDrivers].lpGuid=0;
	}
	else
	{
		DDDriver[nDDNumDrivers].lpGuid=&DDDriver[nDDNumDrivers].Guid;
		memcpy(&DDDriver[nDDNumDrivers].Guid, lpGuid, sizeof(GUID));
	}
	wlstrcpy (DDDriver[nDDNumDrivers].Name, lpDriverName);
	wlstrcpy (DDDriver[nDDNumDrivers].Description, lpDriverDesc);
	memcpy (&DDDriver[nDDNumDrivers].DDCaps, &DDCaps, sizeof(DDCAPS));

	/* Find out if this driver can render in a window */
	if ( (DDCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED) && lpGuid==NULL)
	{
		DDDriver[nDDNumDrivers].bCanRenderWindowed=TRUE;
	}
	else
	{
		DDDriver[nDDNumDrivers].bCanRenderWindowed=FALSE;
	}

	/* Debug output */
#ifdef _DEBUG
	wsprintf(pszTmp, L"DD Driver #%d :\nGuid=%u %u %u %s\nName=%s\nDescription=%s\nMonitor handle=0x%X\n\n", nDDNumDrivers, 
			DDDriver[nDDNumDrivers].Guid.Data1, DDDriver[nDDNumDrivers].Guid.Data2, DDDriver[nDDNumDrivers].Guid.Data3, 
			DDDriver[nDDNumDrivers].Guid.Data4, DDDriver[nDDNumDrivers].Name, DDDriver[nDDNumDrivers].Description,
			hm);
	DEBUG_WCE(pszTmp);
#endif

	/* Increase number of drivers found */
	nDDNumDrivers++;
		
	/* Release local memory */
	RELEASE(lpLocalDD);

	/* Continue enumeration */
	return DDENUMRET_OK;
}


/*******************************************************************************
 * Function Name  : D3DFEEnumDisplayModesCallback
 * Description    : Callback function which enumerates all available display
 *					modes for a DirectDraw device.
 ******************************************************************************/
HRESULT WINAPI D3DFEEnumDisplayModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
	/* Check if we reached maximum number of display modes */
	if (nDDNumDisplayModes[D3DFE.nCurrentDDDriver]>=DD_MAXDISPLAYMODES)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Reached maximum number of display modes.\n\n");
		return DDENUMRET_CANCEL;
	}

	/* Fill the DDDisplayMode structure with relevant information */
	DDDisplayMode[nDDNumDisplayModes[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].dwWidth=lpDDSurfaceDesc->dwWidth;
	DDDisplayMode[nDDNumDisplayModes[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].dwHeight=lpDDSurfaceDesc->dwHeight;
	DDDisplayMode[nDDNumDisplayModes[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].dwBPP=lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;

	/* Increase number of display modes found */
	nDDNumDisplayModes[D3DFE.nCurrentDDDriver]++;

	/* Continue enumeration */
	return DDENUMRET_OK;
}


/*******************************************************************************
 * Function Name  : D3DFEEnumD3DDeviceDriverCallback
 * Description    : Callback function which enumerates all D3D available drivers
 ******************************************************************************/
HRESULT CALLBACK D3DFEEnumD3DDeviceDriverCallback(LPGUID lpGuid, LPTSTR lpDeviceDescription,
												  LPTSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc,
												  LPD3DDEVICEDESC lpHELDesc, LPVOID lpUserArg)
{
	/* Check that we do not exceed maximum number of 3D drivers */
	if (nD3DNumDrivers[D3DFE.nCurrentDDDriver]>=D3D_MAXD3DDRIVERS)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Reached maximum number of D3D drivers.\n\n");
		return DDENUMRET_CANCEL;
	}

	/* We don't want to enumerate the Microsoft NULL device */
	if (D3DFEGuidCompare(lpGuid, (GUID *)&IID_IDirect3DNullDevice))
	{
		return DDENUMRET_OK;
	}
	
	/* Save this driver's info */
    memcpy (&D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].Guid, lpGuid, sizeof(GUID));
    wlstrcpy (D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].About, lpDeviceDescription);
    wlstrcpy (D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].Name, lpDeviceName);
    
	/* If the color model for a HW (HAL) driver is invalid or 0, then the 
	   driver must be a SW (HEL) driver, so use this as a test to see 
	   which type of driver we just saved */
    if (lpHWDesc->dcmColorModel)
	{
        D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].bIsHardware=TRUE;
        memcpy (&D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].Desc, lpHWDesc, sizeof(D3DDEVICEDESC));
    }
	else
	{
        D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].bIsHardware=FALSE;
        memcpy (&D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].Desc, lpHELDesc, sizeof(D3DDEVICEDESC));
	}

	/* Check if 3D driver can render onto a palettised surface */
	if (D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].Desc.dwDeviceRenderBitDepth & DDBD_8)
	{
		D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].bSupportPalettised=TRUE;
	}
	else
	{
		D3DDriver[nD3DNumDrivers[D3DFE.nCurrentDDDriver]][D3DFE.nCurrentDDDriver].bSupportPalettised=FALSE;
	}

	/* Increase number of D3D drivers found */
    nD3DNumDrivers[D3DFE.nCurrentDDDriver]++;
	
	/* Continue enumeration */
	return (D3DENUMRET_OK);
}


/*****************************************************************************
 * Function Name  : D3DFEEnumTextureFormatsCallback
 * Description    : Callback function which enumerates all available texture
 *				    formats for the current D3D driver.
 *					Compute the "best" opaque and translucent formats.
 *****************************************************************************/
HRESULT WINAPI D3DFEEnumTextureFormatsCallback(LPDDPIXELFORMAT lpddPixelFormat, LPVOID lpContext)
{
	DWORD	m;
	int		r=0, g=0, b=0, a=0, i;
  
    /* Check that we do not exceed maximum number of texture formats */
	if (D3DFE.nTextureFormat>=MAX_NUMBER_OF_TEXTURE_FORMAT)
	{
		return DDENUMRET_CANCEL;
	}

	/* Clear structure */
	ZeroMemory(&TextureFormat[D3DFE.nTextureFormat], sizeof(TextureType));
	
	/* Copy current pixel format to texture formats array */
	memcpy(&TextureFormat[D3DFE.nTextureFormat].ddPixelFormat, lpddPixelFormat, sizeof(DDPIXELFORMAT));
   
    /* We don't want palettised textures */
	if (lpddPixelFormat->dwFlags & (DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED4 | DDPF_PALETTEINDEXED8 | DDPF_PALETTEINDEXEDTO8))
	{
        return DDENUMRET_OK;
	}

	/* We don't want luminance, FOURCC, Compressed, Bump, YUV texture formats */
	if (lpddPixelFormat->dwFlags & (DDPF_LUMINANCE | DDPF_FOURCC | DDPF_COMPRESSED | DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV | DDPF_YUV | DDPF_RGBTOYUV))
	{
        return DDENUMRET_OK;
	}
	
    /* Calculate the number of bits available for each channel R,G,B,A */
	m=lpddPixelFormat->dwRBitMask; 
	for (i=0; i<32; i++)
	{
		if ((1<<i) & m)
		{
			r++;
		}
	}
    m=lpddPixelFormat->dwGBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m) 
		{
			g++;
		}
	}
	m=lpddPixelFormat->dwBBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m) 
		{
			b++;
		}
	}
	if (lpddPixelFormat->dwFlags & DDPF_ALPHAPIXELS) 
	{
  		m = lpddPixelFormat->dwRGBAlphaBitMask; 
		for (i=0; i<32; i++) 
		{
			if (m & (1<<i)) 
			{
				a++;
			}
		}
		/* We don't want to enumerate this "weird" format for now */
		if (r==3 && g==3 && b==2 && a==8)
		{
			return DDENUMRET_OK;

		}
		TextureFormat[D3DFE.nTextureFormat].AlphaBPP=a;
    } 

	/* Fill the structure with texture format channel information */
	TextureFormat[D3DFE.nTextureFormat].RedBPP=r;
    TextureFormat[D3DFE.nTextureFormat].GreenBPP=g;
    TextureFormat[D3DFE.nTextureFormat].BlueBPP=b;
	    
    /* Debug output */
#ifdef _DEBUG
	if (D3DFE.nTextureFormat==0)
	{
		DEBUG_WCE(L"Texture formats : ");
	}
	wsprintf(pszTmp, L"%d%d%d%d  ", r, g, b, a);
	DEBUG_WCE(pszTmp);
#endif
	
	/* Increase total number of texture format */
	D3DFE.nTextureFormat++;

	/* Enumeration OK */
	return DDENUMRET_OK;
}


/*******************************************************************************
 * Function Name  : D3DFEGetDirectDrawConfig
 * Inputs		  : None
 * Global Used    : D3DFE
 * Description    : List all DirectDraw devices, all display modes and 3D devices.
 *					This function should only gets called ONCE in Winmain().
 *******************************************************************************/
BOOL D3DFEGetDirectDrawConfig()
{
	HRESULT				hres;
	LPDIRECTDRAW		lpLocalDD;
	LPDIRECTDRAW4		lpLocalDD4;
	LPDIRECT3D3			lpLocalD3D3;
	DDDisplayModeInfo	Dummy;
	int					i, j;
	int					BackCount;
	BOOL				bSwap=FALSE;
	
	/* DirectDraw drivers */
	
	/* Reset DirectDraw drivers array */
	nDDNumDrivers=0;
	ZeroMemory(DDDriver, sizeof(DDDriver));

	/* Enumerate all DirectDraw drivers */
	hres=DirectDrawEnumerate(D3DFEEnumDirectDrawCallback, NULL);
	if (hres!=DD_OK)
	{
			DEBUG_WCE(L"D3DShell *ERROR* : DirectDrawEnumerate() failed.\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
	}
	

	/* Reset Display modes arrays */
	ZeroMemory(DDDisplayMode, sizeof(DDDisplayMode));
	ZeroMemory(nDDNumDisplayModes, sizeof(nDDNumDisplayModes));
	for (i=0; i<nDDNumDrivers; i++)
	{
		nSafeDisplayModeNumber[i]=-1;
	}

	/* Reset 3D drivers arrays */
	ZeroMemory(D3DDriver, sizeof(D3DDriver));
	ZeroMemory(nD3DNumDrivers, sizeof(nD3DNumDrivers));

	/* Enumerate all display modes and 3D drivers for each different DirectDraw drivers */
	for (i=0; i<nDDNumDrivers; i++)
	{
		/* Create DirectDraw for this driver */
		hres=DirectDrawCreate(&DDDriver[i].Guid, &lpLocalDD, NULL);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : DirectDrawCreate() failed.\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
		}

		/* Query interface for DirectDraw 4 */
		hres=lpLocalDD->lpVtbl->QueryInterface(lpLocalDD, &IID_IDirectDraw4, &lpLocalDD4);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : QueryInterface() (for DirectDraw4) failed.\n");
			DisplayHRESULTInDebug(hres);
			RELEASE(lpLocalDD);
			return FALSE;
		}

		/* Just for EnumDisplayModes callback */
		D3DFE.nCurrentDDDriver=i;

		/* Enumerate all display modes for this driver */
		hres=lpLocalDD4->lpVtbl->EnumDisplayModes(lpLocalDD4, 0, NULL, NULL, D3DFEEnumDisplayModesCallback);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : EnumDisplayModes() failed.\n");
			DisplayHRESULTInDebug(hres);
			RELEASE(lpLocalDD4);
			RELEASE(lpLocalDD);
			return FALSE;
		}
	
		/* Test if any display modes were found */
		if (nDDNumDisplayModes[i]==0)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : No display modes were found for that DirectDraw device\n");
			RELEASE(lpLocalDD4);
			RELEASE(lpLocalDD);
			return FALSE;
		}

		/* Sort all the display mode. That's a crap sorting method (bubble sort), 
		   but for a small amount of numbers it's all right, so who cares ?! */
		BackCount=0;
		do
		{
			bSwap=FALSE;
			BackCount++;
			for (j=0; j<nDDNumDisplayModes[i]-BackCount; j++)
			{
				if (1000*DDDisplayMode[j][i].dwBPP+DDDisplayMode[j][i].dwWidth+DDDisplayMode[j][i].dwHeight<
					1000*DDDisplayMode[j+1][i].dwBPP+DDDisplayMode[j+1][i].dwWidth+DDDisplayMode[j+1][i].dwHeight)
				{
					/* Swap required */
					Dummy=DDDisplayMode[j+1][i];
					DDDisplayMode[j+1][i]=DDDisplayMode[j][i];
					DDDisplayMode[j][i]=Dummy;
					bSwap=TRUE;
				}
			}
		}
		while (bSwap && BackCount<nDDNumDisplayModes[i]);

		/* Calculate video card physical memory */
		DDDriver[i].dwPhysicalVideoMemory=D3DFETotalVideoMemoryInfo(lpLocalDD4, DDSCAPS_PRIMARYSURFACE);
		
		/* If Direct Draw driver is primary, memory is already used by GDI so
		   add GDI memory to dwMaxVideoMemory */
		if (i==0)
		{
			DDDriver[i].dwPhysicalVideoMemory+=D3DFE.dwGDIWidth*D3DFE.dwGDIHeight*D3DFE.dwGDIBPP/8;
		}
	
		/* Find display mode number corresponding to 640x480x16 */
		for (j=0; j<nDDNumDisplayModes[i]; j++)
		{
			if (DDDisplayMode[j][i].dwWidth==640 && DDDisplayMode[j][i].dwHeight==480 && DDDisplayMode[j][i].dwBPP==16)
			{
				nSafeDisplayModeNumber[i]=j;
			}
		}


		/* Direct3D Driver */
	
		/* Let's get Direct3D 3 */
		hres=lpLocalDD4->lpVtbl->QueryInterface(lpLocalDD4, &IID_IDirect3D3, (LPVOID *)&lpLocalD3D3);
		if (hres!=DD_OK) 
		{
			DEBUG_WCE(L"D3DShell *ERROR* : QueryInterface() (for Direct3D3) failed.\n");
			DisplayHRESULTInDebug(hres);
			RELEASE(lpLocalDD4);
			RELEASE(lpLocalDD);
			return FALSE;
		}

		/* Enumerate available D3D devices */
		hres=lpLocalD3D3->lpVtbl->EnumDevices(lpLocalD3D3, D3DFEEnumD3DDeviceDriverCallback, NULL);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : EnumDevices() failed.\n");
			DisplayHRESULTInDebug(hres);
			RELEASE(lpLocalD3D3);
			RELEASE(lpLocalDD4);
			RELEASE(lpLocalDD);
			return FALSE;
		}
		
		/* Test if at least one D3D driver has been found */
		if (nD3DNumDrivers[i]==0)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : No Direct3D driver has been found\n");
			RELEASE(lpLocalD3D3);
			RELEASE(lpLocalDD4);
			RELEASE(lpLocalDD);
			return FALSE;
		}

		/* Release local memory */
		RELEASE(lpLocalDD4);
		RELEASE(lpLocalDD);
		RELEASE(lpLocalD3D3);

		/* We're done with this DirectDraw driver */
	}


	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DFERender
 * Returns        : TRUE if no error occured
 * Global Used    : D3DFE
 * Description    : Render D3D scene.
 *					Full Screen : call Flip() to update display.
 *******************************************************************************/
BOOL D3DFERender()
{
	HRESULT		hres;
	D3DRECT		dummy;
	RECT		rect;
	static int	nFramesElapsed=0;

	/* Has Autokill been specified in the command line ? */
	if (D3DFE.bAutoKill)
	{
		if (++nFramesElapsed>FRAMESBEFOREKILLING)
		{
			/* Auto-terminate */
			wsprintf(pszTmp, L"D3DShell AUTOKILL : %d frames elapsed, quitting application\n", nFramesElapsed-1);
			OutputDebugString(pszTmp);
			D3DFEFinish();
			return TRUE;
		}
	}

	/* Clear values for rectangles */
	dummy.x1=0;
	dummy.y1=0;
	rect.left=0;
	rect.top=0;
	
	/* Retrieve blitting rectangle information */
	dummy.x2=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwWidth;
	dummy.y2=DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwHeight;
	rect.right=dummy.x2;
	rect.bottom=dummy.y2;
	
	/* Clear the target surface if requested */
	if (D3DFE.bClearViewport)
	{
		/* Clear viewport */
		/* The following commented out line is for very quick renders only 
		   i.e the scene renders so fast that it finishes before the clear! */
		/* D3DFEClearSurface(D3DFE.lpDDSBack);
		   while (D3DFE.lpDDSBack->lpVtbl->GetBltStatus(D3DFE.lpDDSBack, DDGBS_ISBLTDONE)!=DD_OK); */
		
		/* Clear frame buffer */
		hres=D3DFE.lpD3DView3->lpVtbl->Clear(D3DFE.lpD3DView3, 1, &dummy, D3DCLEAR_TARGET);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *WARNING* : Viewport clear failed in D3DFERender()\n");
			DisplayHRESULTInDebug(hres);
		}
	}

	/* Always clear Z-buffer */
	if (D3DFE.lpDDSZBuffer && !D3DFE.bDisableZClear)
	{
		/* Clear z-buffer if it exists */
		hres=D3DFE.lpD3DView3->lpVtbl->Clear(D3DFE.lpD3DView3, 1, &dummy, D3DCLEAR_ZBUFFER);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *WARNING* : Z-Buffer clear failed in D3DFERender()\n");
			DisplayHRESULTInDebug(hres);
		}
	}
		
	/* Check for lost surfaces */
	if (!D3DFECheckForLostSurfaces())
	{
		DEBUG_WCE(L"D3DShell *ERROR* : CheckForLostSurfaces() failed in D3DFERender()\n");
		return FALSE;
	}

	/* Call user rendering routine */
	if (!RenderScene(D3DFE.lpD3DDev3, D3DFE.lpD3DView3))
	{
		return FALSE;
	}

	/* If at least 2 surfaces (front and back buffers) */
	if (D3DFE.nBufferingMode>1)
	{
		/* Fullscreen mode : update the primary surface by performing a flip */
		hres=D3DFE.lpDDSPrimary->lpVtbl->Flip(D3DFE.lpDDSPrimary, NULL, DDFLIP_WAIT);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"D3DShell *ERROR* : Flip() failed in D3DFERender()\n");
			DisplayHRESULTInDebug(hres);
			return FALSE;
		}
	}

	
	/* Increase the number of frames */
	D3DFE.dwFramesElapsed++;

	/* No problem occured */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DFEFreeVideoMemoryInfo
 * Inputs		  : lpDD4, dwCaps
 * Returns		  :	Amount of free video memory
 * Global Used    : D3DFE
 * Description    : Returns amount of free video memory that can be used by
 *					a surface
 *******************************************************************************/
DWORD D3DFEFreeVideoMemoryInfo(LPDIRECTDRAW4 lpDD4, DWORD dwCaps)
{
	HRESULT		hres;
	DDSCAPS2	ddsCaps;
	DWORD		dwFree=0;

	/* Initialise DDSCAPS2 structure */
	ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));


	/* Call this function to retrieve the amount of video memory */
	ddsCaps.dwCaps=dwCaps;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, NULL, &dwFree);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : GetAvailableVidMem() failed in D3DFEFreeVideoMemoryInfo()\n");
		DisplayHRESULTInDebug(hres);
	}
	
	/* Return resulting amount in bytes */
	return dwFree;
}
/*******************************************************************************
 * Function Name  : D3DFETotalVideoMemoryInfo
 * Inputs		  : lpDD4, dwCaps
 * Returns		  :	Amount of total video memory
 * Global Used    : D3DFE
 * Description    : Returns amount of total video memory that can be used by
 *					a surface
 *******************************************************************************/
DWORD D3DFETotalVideoMemoryInfo(LPDIRECTDRAW4 lpDD4, DWORD dwCaps)
{
	DDSCAPS2	ddsCaps;
	HRESULT		hres;
	DWORD		dwTotal=0;
	
	/* Initialise DDSCAPS2 structure */
	ZeroMemory(&ddsCaps, sizeof(DDSCAPS2));

	/* Call this function to retrieve the amount of video memory */
	ddsCaps.dwCaps=dwCaps;
	hres=lpDD4->lpVtbl->GetAvailableVidMem(lpDD4, &ddsCaps, &dwTotal, NULL);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : GetAvailableVidMem() failed in D3DFETotalVideoMemoryInfo()\n");
		DisplayHRESULTInDebug(hres);
	}
		
	/* Return resulting amount in bytes */
	return dwTotal;
}


/*******************************************************************************
 * Function Name  : D3DFECheckVideoMemoryForFullScreenMode
 * Returns		  :	TRUE if memory is OK for this mode
 * Global Used    : D3DFE
 * Description    : Check if there is enough video memory (both surface and
 *					Z-Buffer) to set display mode
 *******************************************************************************/
BOOL D3DFECheckVideoMemoryForFullScreenMode(int nDirectDrawDriver,
											DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, 
											BOOL bZBuffer, int nBufferingMode,
											DWORD dwFrameBufferMemory, DWORD dwZBufferMemory)
{

	/* Memory is shared between frame buffer and Z-buffer */
	if (DDDriver[nDirectDrawDriver].bSharedVideoMemory)
	{
		/* Check if display mode has enough frame buffer memory */
		if (bZBuffer)
		{
			/* Use GDI colour depth for surface and 16 bit surface for Z-Buffer */
			if ( (nBufferingMode*dwWidth*dwHeight*dwBPP/8) + (dwWidth*dwHeight*2) > dwFrameBufferMemory)
			{
				/* Not enough memory for Z-Buffer */
				DEBUG_WCE(L"D3DShell *WARNING* : Not enough memory for Z-Buffer.\n");
				return FALSE;				   
			}
		}
		else
		{
			/* No Z-Buffer needed, just check if there is enough memory for frame buffer */
			if (nBufferingMode*dwWidth*dwHeight*dwBPP/8>dwFrameBufferMemory)
			{
				/* Not enough memory for surface */
				DEBUG_WCE(L"D3DShell *WARNING* : Not enough memory for frame buffer.\n");
				return FALSE;
			}
		}
	}
	else
	{
		/* Surface memory and Z-Buffer memory are separate */
		if (bZBuffer)
		{
			/* Check if display mode has enough Z-Buffer 16 bit surface memory for this size */
			if (dwWidth*dwHeight*2>dwZBufferMemory)
			{
				/* Not enough memory for Z-Buffer */
				DEBUG_WCE(L"D3DShell *WARNING* : Not enough memory for Z-Buffer.\n");
				return FALSE;
			}
		}
		/* Check if display mode has enough frame buffer memory for this size */
		if (nBufferingMode*dwWidth*dwHeight*D3DFE.dwGDIBPP/8>dwFrameBufferMemory)
		{
			/* Not enough memory for frame buffer */
			DEBUG_WCE(L"D3DShell *WARNING* : Not enough memory for frame buffer.\n");
			return FALSE;
		}
	}

	/* There is enough video memory to support this window size */
	return TRUE;
}


/*******************************************************************************
 * Function Name  : WinMain 
 * Description    : Main function of the program
 *******************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	int				idle;
	int				done = FALSE;
	static int		nRenderFailed=0;
	TCHAR			pszOrgCommandLine[500];
	

	/* Initialise D3D Shell variables */
	D3DFEInitFrontEnd();

	/* Set up and register window class */
	if (!hPrevInstance)	
	{
		D3DFE.wndclass.style=0;
		D3DFE.wndclass.lpfnWndProc=(WNDPROC)D3DFEWindowProc;
		D3DFE.wndclass.cbClsExtra=0;
		D3DFE.wndclass.cbWndExtra=0;
		D3DFE.wndclass.hInstance=hInstance;
		D3DFE.wndclass.hIcon=NULL;
		D3DFE.wndclass.hCursor=NULL;
		D3DFE.wndclass.hbrBackground=NULL; 
		D3DFE.wndclass.lpszMenuName=NULL;
		D3DFE.wndclass.lpszClassName=L"D3DShellClass";
		RegisterClass(&D3DFE.wndclass);
	}

	/* Get previous instance handle */
	D3DFE.hPreviousInstance=hPrevInstance;

	/* Compute Window style */
	D3DFE.dwWindowStyle=0;
	
	/* Get Screen default dimensions and bpp */
	D3DFE.dwGDIBPP=GetDeviceCaps(NULL, BITSPIXEL);
		
	/* window position (screen centre) */
	D3DFE.dwWindowPositionX=320;
	D3DFE.dwWindowPositionY=240;
	
	/* Set window frame values */
	D3DFE.dwWindowFramePositionX=0;
	D3DFE.dwWindowFramePositionY=0;

	D3DFE.dwWindowFrameWidth=640;
	D3DFE.dwWindowFrameHeight=480;
	
		/* create a window */
    D3DFE.hwnd = CreateWindowEx(0,
								L"D3DShellClass",
								D3DFE.pszFrontEndTitle,
								D3DFE.dwWindowStyle,
								D3DFE.dwWindowFramePositionX,
								D3DFE.dwWindowFramePositionY,
								D3DFE.dwWindowFrameWidth,
								D3DFE.dwWindowFrameHeight,
								NULL,
								NULL,
								hInstance,
								NULL );

	/* If window could not be created */
    if (D3DFE.hwnd==NULL)
    {
        DEBUG_WCE(L"D3DShell *ERROR* : Window could not be created\n");
		return 0;
    }

	
	/****************************************
	** At this point the window is created **
	****************************************/

	/*******************************
	** Get DirectDraw information **
	*******************************/
	
	if (!D3DFEGetDirectDrawConfig())
	{
		DEBUG_WCE(L"D3DShell *ERROR* : D3DFEGetDirectDrawConfig() failed.\n");
		return 0;
	}

	/*********************************
	** Set default rendering values **
	*********************************/
	/* Use primary driver */
	D3DFE.nCurrentDDDriver=0;
									  
	/* Start in a window */
	D3DFE.bFullScreen=TRUE;

	/* Use safe resolution for fullscreen mode */
	D3DFE.nCurrentResolution=nSafeDisplayModeNumber[D3DFE.nCurrentDDDriver];

	/* Don't use a Z-Buffer by default */
	D3DFE.bZBufferNeeded=FALSE;

	/* Default buffering mode (for FullScreen) is double buffer */
	D3DFE.nBufferingMode=2;

	/* Default Direct3D driver is HAL is available, RGB otherwise */
	D3DFE.nCurrentD3DDriver=D3DFEGetHALDriver(D3DFE.nCurrentDDDriver);

	D3DFE.bClearViewport=FALSE;

	
	/**************************************************
	** Call InitApplication to retrieve user choices **
	**************************************************/
	InitApplication(D3DFE.wndclass.hInstance, D3DFE.hwnd, pszOrgCommandLine);


	/************************************************
	** Update rendering variables with user choice **
	************************************************/
	/* Buffering mode choice */
	if (D3DFE.dwUserPreferences & (FORCE_SINGLE_BUFFER | DEFAULT_SINGLE_BUFFER))
	{
		D3DFE.nBufferingMode=1;
	}
	if (D3DFE.dwUserPreferences & FORCE_DOUBLE_BUFFER)
	{
		D3DFE.nBufferingMode=2;
	}
	if (D3DFE.dwUserPreferences & (FORCE_TRIPLE_BUFFER | DEFAULT_TRIPLE_BUFFER))
	{
		D3DFE.nBufferingMode=3;
	}

	/******************************************
	** Here starts DirectDraw initialisation **
	******************************************/
	/* Initialise D3D with these defaults */
	if (!D3DFEInitialiseDirect3D(D3DFE.nCurrentDDDriver,
								 D3DFE.bFullScreen, D3DFE.nCurrentResolution,
								 D3DFE.bZBufferNeeded, D3DFE.nBufferingMode,
								 D3DFE.nCurrentD3DDriver))
	{
		DEBUG_WCE(L"D3DShell *ERROR* : D3DFEInitialiseDirect3D() failed in Winmain().\n");
		QuitApplication();
		D3DFEReleaseAll();
		return 0;
	}



	/* D3D Initialisation complete! */

	/************************
	** Load Dreamcast Logo **
	*************************/
	LoadDCLogo(D3DFE.lpD3DDev3, D3DFE.lpDD4, &D3DFE.lpDCLogoTexture);


	/* Create a timer used to calculate frame rate .
	   (we use 99 for the counter ID, as we don't want the user 
	   to set a personal timer with an obvious 1 for an ID) */
	SetTimer(D3DFE.hwnd, 99, TIMER_PERIOD, (TIMERPROC)D3DFETimerProc);
		
			
	/**********************
	** Main message loop **
	**********************/
	while (!done)
    {   
		idle = TRUE;
		while (PeekMessage(&D3DFE.msg, NULL, 0, 0, PM_REMOVE))
		{
			idle=FALSE;
			if (D3DFE.msg.message==WM_QUIT)
			{	
				done=TRUE;
				break;
			}
			
		}
		
		/* If we are not minimised nor paused and the rendering is ready */
		if (!D3DFE.bMinimized && !D3DFE.bPaused && D3DFE.bRenderingReady)
		{
			/* Call the rendering routine */
			if (!D3DFERender())
			{
				D3DFE.bRenderingReady=FALSE;
				D3DFE.bPaused=TRUE;
				DEBUG_WCE(L"Application finished!\n");
				D3DFEFinish();
			}
		}
    }

	/* Give time to free all variables and erase windows */
	Sleep(100);
	
	/* Release memory */
	QuitApplication();
	D3DFEReleaseAll();

	/* End of program */
	DEBUG_WCE(L"D3DShell : End of program\n");
    return D3DFE.msg.wParam;
}


/*******************************************************************************
 * Function Name  : D3DFEWindowProc
 * Description    : Messages handling function
 *******************************************************************************/
long CALLBACK D3DFEWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  
	/* Let the user process window message (menus and keystrokes) */
	UserWindowProc(hWnd, message, wParam, lParam);
	
	switch(message)
    {
	case	WM_DESTROY :		/* Handle window destroying */
								PostQuitMessage(0);
								break;

	case	WM_QUIT :			/* Quit program */
								DEBUG_WCE(L"Quitting D3DFrontEnd\n");
								break;
  
    case WM_KEYDOWN:
						switch (wParam) 
						{

								case VK_ESCAPE:
								case VK_F12:
										D3DFE.bPaused=TRUE;
										D3DFEFinish();
										return 0;
						}
						break;

    default:	return DefWindowProc(hWnd, message, wParam, lParam);
    }

    /* Message handled OK */
	return 0;
}


/*******************************************************************************
 * Function Name  : D3DFEGetHALDriver
 * Input		  : nDDDriver
 * Global Used    : nD3DNumDrivers[]
 * Description    : Return 3D device number corresponding to a HAL driver
 *******************************************************************************/
int D3DFEGetHALDriver(int nDDDriver)
{
	int i;

	/* Look for the first HAL 3D driver */
	for (i=0; i<nD3DNumDrivers[nDDDriver]; i++)
	{
		if (D3DDriver[i][nDDDriver].bIsHardware)
		{
			return i;
		}
	}

	/* No HAL found, return 0 (RGB driver) */
	return 0;
}


/*******************************************************************************
 * Function Name  : D3DShellGetVariable
 * Input		  : nVariableName
 * Output		  : pVariablePointer
 * Global Used    : D3DFE
 * Description    : Function called by the user to retrieve a variable used by
 *					D3DShell.
 *					A list of variables that can be retrieved is in D3DShell.h
 *******************************************************************************/
void D3DShellGetVariable(enum D3DShellVariables nVariableName, void *pVariablePointer)
{
	/* Check that the variable name is valid */
	if (nVariableName>FRAME_RATE)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Invalid variable name.\n");
		return;
	}
	
	/* Fill pointer's content with appropriate value */
	switch(nVariableName)
	{
		/* pVariablePointer points to a HINSTANCE variable */
		case APPLICATION_INSTANCE_HANDLE :	*(HINSTANCE *)pVariablePointer=D3DFE.wndclass.hInstance; break;
		/* pVariablePointer points to a HINSTANCE variable */
		case PREVIOUS_INSTANCE_HANDLE :		*(HINSTANCE *)pVariablePointer=D3DFE.hPreviousInstance; break;
		/* pVariablePointer points to a HWND variable */
		case WINDOW_HANDLE :				*(HWND *)pVariablePointer=D3DFE.hwnd; break;
		/* pVariablePointer points to a BOOL variable */
		case FULLSCREEN_MODE :				*(BOOL *)pVariablePointer=D3DFE.bFullScreen; break;
		/* pVariablePointer points to a LPDIRECTDRAWSURFACE4 variable */
		case PRIMARY_SURFACE :				*(LPDIRECTDRAWSURFACE4 *)pVariablePointer=D3DFE.lpDDSPrimary; break;
		/* pVariablePointer points to a HINSTANCE variable */
		case BACK_BUFFER :					*(LPDIRECTDRAWSURFACE4 *)pVariablePointer=D3DFE.lpDDSBack; break;
		/* pVariablePointer points to a HINSTANCE variable */
		case Z_BUFFER :						*(LPDIRECTDRAWSURFACE4 *)pVariablePointer=D3DFE.lpDDSZBuffer; break;
		/* pVariablePointer points to a LPGUID (Pointer to GUID) variable */
		case D3DDRIVER_GUID_POINTER :		*(LPGUID *)pVariablePointer=&D3DDriver[D3DFE.nCurrentD3DDriver][D3DFE.nCurrentDDDriver].Guid; break;
		/* pVariablePointer points to a DWORD variable */
		case FRAME_BUFFER_BIT_DEPTH :		*(DWORD *)pVariablePointer=(D3DFE.bFullScreen ? DDDisplayMode[D3DFE.nCurrentResolution][D3DFE.nCurrentDDDriver].dwBPP : D3DFE.dwGDIBPP); break;
		/* pVariablePointer points to a DWORD variable */
		case BUFFERING_MODE :				*(DWORD *)pVariablePointer=(D3DFE.bFullScreen ? D3DFE.nBufferingMode : 2); break;
		/* pVariablePointer points to a DWORD variable */
		case FRAME_RATE :					*(DWORD *)pVariablePointer=D3DFE.dwFrameRate; break;
	}
}


/*******************************************************************************
 * Function Name  : D3DShellSetPreferences
 * Global Used    : D3DFE
 * Description    : Function called by the user to submit a menu and set
 *					preferences.
 *******************************************************************************/
void D3DShellSetPreferences(DWORD dwFlags)
{
		
	/* Retrieve user's preferences */
	D3DFE.dwUserPreferences|=dwFlags;

	/* If Clear viewport On as been chosen as a default, enable it */
	if (D3DFE.dwUserPreferences & DEFAULT_CLEAR_ON)
	{
		D3DFE.bClearViewport=TRUE;
	}

	/* If clear viewport is forced On or Off, then set
	   the state of the corresponding BOOL variable */
	if (D3DFE.dwUserPreferences & FORCE_CLEAR_ON)
	{
		D3DFE.bClearViewport=TRUE;
	}
	if (D3DFE.dwUserPreferences & FORCE_CLEAR_OFF)
	{
		D3DFE.bClearViewport=FALSE;
	}


}


/*******************************************************************************
 * Function Name  : D3DShellLoadBMP
 * Returns		  : TRUE or FALSE
 * Inputs		  : lpName, bTranslucent
 * Output		  : *lplpD3DTex2
 * Global Used    : D3DFE
 * Description    : Simple texture loading function which load BMP textures.
 *					The BMP file can either be loaded from the resource or as
 *					a file. 
 *					RGB and OS/2 formats are supported. RLE encoded format 
 *					is NOT supported by this function.
 *					Does NOT support palletised formats.
 *******************************************************************************/
BOOL D3DShellLoadBMP(TCHAR *lpName, BOOL bTranslucent, LPDIRECT3DTEXTURE2 *lplpD3DTex2)
{
	HRESULT					hres;
	LPDIRECTDRAWSURFACE4	lpDDSSrcTextureSurf;
	LPDIRECTDRAWSURFACE4	lpDDS;
	LPDIRECT3DTEXTURE2		lpTex2SrcTexture;
	DDSURFACEDESC2			ddsd;
	DDPIXELFORMAT			PixelFormat;
	HBITMAP					Bitmap, BitmapTrans;
	BITMAP					bm, bmTrans;
	DWORD					x, y;
	DWORD					r=0, g=0, b=0, a=0, m=0;
	DWORD					dwMemoryUsedByTexture=0;
	unsigned				R, G, B, A;
	unsigned				Cont = 0;
	unsigned char			*lp8b;
	unsigned short			*lp16b;
	unsigned int			*lp32b;
	int						i, j, Mode, nFormat;
	char					*pLineBuffer, *pLineBufferTrans;
	char					LeftR,LeftG,LeftB,LeftA; 
	char					RightR,RightG,RightB,RightA;
	TCHAR					pszString[400];
	HDC		                hdcBitmap;  // DC for bitmap

			
	/* If D3DFE.nBestOpaque is equal to -1, then texture formats 
	   have not been enumerated yet */
	if (D3DFE.nBestOpaqueFormat==-1) 
	{
		if (!D3DFEListTextureFormats(D3DFE.lpD3DDev3))
		{
			DEBUG_WCE(L"D3DShell *WARNING* : No texture format supported.\n");
			(*lplpD3DTex2)=NULL;
			return FALSE;
		}
	}

	/* Pick the "best" opaque format */
	nFormat=D3DFE.nBestOpaqueFormat;
	
	/* Load texture : first try to load from resource */
	D3DShellGetResourceBitmap(&bm, lpName);


	/* If translucent, then also read the file t+lpName */
	if (bTranslucent)
	{
		/* Translucent file name = t+lpName */
		wsprintf (pszString, TEXT("t%s"), lpName);
	
		/* Load translucent texture : first try to load from resource */
		D3DShellGetResourceBitmap(&bmTrans, pszString);
		nFormat=D3DFE.nBestTransFormat;
	}
	
	/* Get width and height of bitmap (square texture implied) */
	x=bm.bmWidth;
	y=bm.bmWidth;

	/* Calculate memory used by texture */
	dwMemoryUsedByTexture=x*y*TextureFormat[nFormat].ddPixelFormat.dwRGBBitCount/8;

	/* See if there is enough video texture memory to load this texture
	   For device that store texture into System memory, this function
	   will never fail as the video texture memory size won't be changed */
	if (D3DFEFreeVideoMemoryInfo(D3DFE.lpDD4, DDSCAPS_TEXTURE)<dwMemoryUsedByTexture)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Not enough memory to allocate texture.\n");
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans);
		}
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}


	/* If translucent texture has also been loaded, check that both 
	   widths and heights are equal */
	if (bTranslucent)
	{
		if (bm.bmWidth!=bmTrans.bmWidth || bm.bmHeight!=bmTrans.bmHeight)
		{
			/* Dimensions are not the same : abort */
			DEBUG_WCE(L"D3DShell *WARNING* : Dimensions of texture and translucent texture do not match.\n");
			DeleteObject(Bitmap);
			DeleteObject(BitmapTrans);
			(*lplpD3DTex2)=NULL;
			return FALSE;
		}
	}
	
	/* Security : discard any size above 1024 pixels */
	if (x>1024 || y>1024)
	{
		DEBUG_WCE(L"Texture size too large\n");
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans);
		}
		return 0;
	}

	/* Allocate memory so that we can read data */
	pLineBuffer=(char *)malloc(bm.bmWidthBytes*sizeof(char));
	pLineBufferTrans=(char *)malloc(bm.bmWidthBytes*sizeof(char));

	/* Initialise PixelFormat structure */
	// The 2 following lines are useless
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize=sizeof(DDPIXELFORMAT);

	/* Copy the texture format used into PixelFormat */
	memcpy(&PixelFormat, &TextureFormat[nFormat].ddPixelFormat, sizeof(DDPIXELFORMAT));

	/* Display texture format used in Debug */
	m=PixelFormat.dwRBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m ) r++;
	}
    m=PixelFormat.dwGBitMask; 
	for (i=0; i<32; i++) 
	{
		if ((1<<i) & m ) g++;
	}
	m=PixelFormat.dwBBitMask; 
	for (i=0; i<32; i++)
	{
		if ((1<<i) & m ) b++;
	}
	if (bTranslucent)
	{
		m=PixelFormat.dwRGBAlphaBitMask; 
		for (i=0; i<32; i++) 
		{
			if ((1<<i) & m ) a++;
		}
	}

	/* Debug output */
#ifdef _DEBUG
	wsprintf(pszString, L"Loading texture from %s : %s%s (%u*%u) %u%u%u%u  -> %u Bytes\n", 
						"resource", bTranslucent ? "(t)" : "", 
						lpName, x, y, r, g, b, a, dwMemoryUsedByTexture);
	DEBUG_WCE(pszString);
#endif
  
	/* Find right shifting values */
	RightR=8 - TextureFormat[nFormat].RedBPP;
	RightG=8 - TextureFormat[nFormat].GreenBPP;
	RightB=8 - TextureFormat[nFormat].BlueBPP;

    /* Find left shifting values */
	for (i=0; (PixelFormat.dwRBitMask & (1<<i))==0 ; i++); LeftR = i; 
    for (i=0; (PixelFormat.dwGBitMask & (1<<i))==0 ; i++); LeftG = i;
    for (i=0; (PixelFormat.dwBBitMask & (1<<i))==0 ; i++); LeftB = i;

	/* If texture is translucent, also find the right and 
	   left shifting value corresponding to alpha */
	if (bTranslucent) 
	{
        RightA=8 - TextureFormat[nFormat].AlphaBPP;
		for (i=0; (PixelFormat.dwRGBAlphaBitMask & (1<<i))==0 ; i++);
		LeftA=i;
	}

	/* Create texture surface */
    memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
    ZeroMemory(&ddsd.ddsCaps.dwCaps, sizeof(DDSCAPS2));
	ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
	ddsd.ddsCaps.dwCaps2=0;
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
    ZeroMemory(&ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));
	memcpy(&ddsd.ddpfPixelFormat, &PixelFormat, sizeof(DDPIXELFORMAT));
	
	hres=D3DFE.lpDD4->lpVtbl->CreateSurface(D3DFE.lpDD4, &ddsd, &lpDDS, NULL);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Failed to create texture surface.\n");
		DisplayHRESULTInDebug(hres);
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans);
		}
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}

	/* Initialise surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_WAIT, NULL); 
    if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Failed to lock texture surface.\n");
		DisplayHRESULTInDebug(hres);
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans);
		}
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}

	/* Compute mode used */
	Mode=PixelFormat.dwRGBBitCount + (int)bTranslucent;
	
	hdcBitmap = CreateCompatibleDC (NULL);
	SelectObject (hdcBitmap, Bitmap);

	for (i=y; i!=0; i--)
	{
		/* Calculate pointers corresponding to texture format (8, 16 or 32 bits) */
		lp8b  = (unsigned char *) (((char *)ddsd.lpSurface) + x*i-1);
		lp16b = (unsigned short *)(((char *)ddsd.lpSurface) + x*i*2-2);
		lp32b = (unsigned int *)  (((char *)ddsd.lpSurface) + x*i*4-4);

		/* Copy the current line from the bitmap to pLineBuffer */
		/* Texture was upside down so I changed the following line */
		/* memcpy(pLineBuffer, ((char *)bm.bmBits+(y-i)*bm.bmWidthBytes), bm.bmWidthBytes); */
		memcpy(pLineBuffer, ((char *)bm.bmBits+(i-1)*bm.bmWidthBytes), bm.bmWidthBytes);
		if (bTranslucent)
		{
			/* Copy the current line from the transparent bitmap to pLineBuffer */
			/* Texture was upside down so I changed the following line */
			/* memcpy(pLineBufferTrans, ((char *)bmTrans.bmBits+(y-i)*bmTrans.bmWidthBytes), bmTrans.bmWidthBytes); */
			memcpy(pLineBufferTrans, ((char *)bmTrans.bmBits+(i-1)*bmTrans.bmWidthBytes), bmTrans.bmWidthBytes);
		}

        /* Has been changed to x*3-1 because last value is NOT x*3, it's x*3-1 */
		Cont=x*3-1;
		
		for (j=0; (DWORD)j<x; j++)
		{ 
			R = *(pLineBuffer+Cont--) & 255;
			G = *(pLineBuffer+Cont--) & 255;
			B = *(pLineBuffer+Cont--) & 255;
														
			switch (Mode)
			{
			case 8: 
				/* 8 Bits Opaque */
				*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 9: 
				/* 8 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3) & 255;
				*(lp8b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			case 16:
				/* 16 Bits Opaque */
				*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 17:
				/* 16 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3) & 255;
				*(lp16b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			case 32:
				/* 32 Bits Opaque */
				*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB ;
				break;

			case 33:
				/* 32 Bits Translucent */
				A = *(pLineBufferTrans+Cont+3) & 255;
				*(lp32b--) = (R>>RightR)<<LeftR | (G>>RightG)<<LeftG | (B>>RightB)<<LeftB | (A>>RightA)<<LeftA;
				break;

			default:
				/* Unknow pixel format : free memory and abort */
				lpDDS->lpVtbl->Unlock(lpDDS, NULL);
				free(pLineBuffer);
				free(pLineBufferTrans);
				DeleteObject(Bitmap);
				if (bTranslucent) 
				{
					DeleteObject(BitmapTrans);
				}
                RELEASE(lpDDS);
                DEBUG_WCE(L"D3DShell *WARNING* : Unknown pixel format.\n");
				(*lplpD3DTex2)=NULL;
                return FALSE;
			}
		}
	}

	DeleteDC (hdcBitmap);

    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Unlock() failed.\n");
		DisplayHRESULTInDebug(hres);
	}
    
	lpDDSSrcTextureSurf=lpDDS;
	
	/* QueryInterface for a Direct3DTexture2 interface */
	hres=lpDDSSrcTextureSurf->lpVtbl->QueryInterface(lpDDSSrcTextureSurf, &IID_IDirect3DTexture2,(LPVOID*)&lpTex2SrcTexture);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : QueryInterface() (for Direct3DTexture2) failed.\n");
		DisplayHRESULTInDebug(hres);
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans);
		}
		RELEASE(lpDDSSrcTextureSurf);
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}

	/* Get surface description */
	hres=lpDDSSrcTextureSurf->lpVtbl->GetSurfaceDesc(lpDDSSrcTextureSurf, &ddsd);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : GetSurfaceDesc() (for system memory texture surface) failed.\n");
		DisplayHRESULTInDebug(hres);
		DeleteObject(Bitmap);
		if (bTranslucent) 
		{
			DeleteObject(BitmapTrans); 
		}
		RELEASE(lpDDSSrcTextureSurf);
		RELEASE(lpTex2SrcTexture);
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}
    
    /* Create texture surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD  | DDSCAPS_VIDEOMEMORY;
	/* Let D3D manage textures */
	ddsd.ddsCaps.dwCaps2= 0;
    ddsd.dwWidth=x;
	ddsd.dwHeight=y;
	ddsd.ddpfPixelFormat=PixelFormat;
	ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    hres=D3DFE.lpDD4->lpVtbl->CreateSurface(D3DFE.lpDD4, &ddsd, &TextureArray.lpDDSTextureSurface[D3DFE.nTextures], NULL);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : CreateSurface() (video memory texture surface)failed.\n");
		DisplayHRESULTInDebug(hres);
		RELEASE(lpDDSSrcTextureSurf);
		RELEASE(lpTex2SrcTexture);
		RELEASE(TextureArray.lpDDSTextureSurface[D3DFE.nTextures]);
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=TextureArray.lpDDSTextureSurface[D3DFE.nTextures]->lpVtbl->QueryInterface(TextureArray.lpDDSTextureSurface[D3DFE.nTextures], 
												&IID_IDirect3DTexture2,(LPVOID*)&TextureArray.lpTex2[D3DFE.nTextures]);
    if (hres!=DD_OK) 
	{
		DEBUG_WCE(L"D3DShell *WARNING* : QueryInterface() (for Direct3DTexture2) failed.\n");
		DisplayHRESULTInDebug(hres);
		RELEASE(lpDDSSrcTextureSurf);
		RELEASE(lpTex2SrcTexture);
		RELEASE(TextureArray.lpDDSTextureSurface[D3DFE.nTextures]);
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}

	/* Now assign the texture interface to the passed parameter (New to DirectX 6) */
	*(lplpD3DTex2)=TextureArray.lpTex2[D3DFE.nTextures];
	
	/* Load texture into memory */
	hres=TextureArray.lpTex2[D3DFE.nTextures]->lpVtbl->Load(TextureArray.lpTex2[D3DFE.nTextures], lpTex2SrcTexture);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"D3DShell *WARNING* : Load() (texture interface) failed.\n");
		DisplayHRESULTInDebug(hres);
		RELEASE(lpDDSSrcTextureSurf);
		RELEASE(lpTex2SrcTexture);
		RELEASE(TextureArray.lpDDSTextureSurface[D3DFE.nTextures]);
		RELEASE(TextureArray.lpTex2[D3DFE.nTextures]);
		(*lplpD3DTex2)=NULL;
		return FALSE;
	}
      
	/* Release surfaces and interfaces */
	RELEASE(lpDDSSrcTextureSurf);
	RELEASE(lpTex2SrcTexture);
    	
	/* Release memory */
	free(pLineBuffer);
	free(pLineBufferTrans);
	DeleteObject(Bitmap);
	if (bTranslucent) 
	{
		DeleteObject(BitmapTrans);
	}	

	/* Increase texture count */
	D3DFE.nTextures++;
	
	/* No problem occured */
    return TRUE;
}


/*******************************************************************************
 * Function Name  : D3DFETimerProc
 * Inputs		  : hwnd, uMsg, idEvent, dwTime
 * Global Used    : D3DFE
 * Description    : Timer callback procedure
 *******************************************************************************/
void CALLBACK D3DFETimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	/* Compute frame rate if ready */
	if (D3DFE.bRenderingReady && !D3DFE.bPaused && !D3DFE.bMinimized)
	{
		D3DFE.dwFrameRate=(D3DFE.dwFramesElapsed * 1000) / TIMER_PERIOD;
		D3DFE.dwFramesElapsed=0;
	}
	else
	{
		D3DFE.dwFrameRate=0;
		D3DFE.dwFramesElapsed=0;
	}
}


/*******************************************************************************
 * Function Name  : D3DFEDisplayInfoAboutSurfaces
 * Global Used    : D3DFE
 * Description    : Useful function which reports if surfaces are located 
 *					in Video memory or in System memory.
 *******************************************************************************/
void D3DFEDisplayInfoAboutSurfaces()
{
	DDSURFACEDESC2	ddsd;
	HRESULT			hres;

	/* Set DDSURFACEDESC2 structure to 0 */
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);

	/* Get surface description of Primary buffer */
	hres=D3DFE.lpDDSPrimary->lpVtbl->GetSurfaceDesc(D3DFE.lpDDSPrimary, &ddsd);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(L"GetSurfaceDesc failed for primary surface in D3DFEDisplayInfoAboutSurfaces()\n");	
		DisplayHRESULTInDebug(hres);
	}
	wsprintf(pszTmp, L"\nPrimary surface is in %s memory\n", (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? ((ddsd.ddsCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM) ? "AGP" : "VIDEO") : "SYSTEM");
	DEBUG_WCE(pszTmp);

	/* Get surface description of Back buffer */
	if (D3DFE.lpDDSBack)
	{
		hres=D3DFE.lpDDSBack->lpVtbl->GetSurfaceDesc(D3DFE.lpDDSBack, &ddsd);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"GetSurfaceDesc failed for back buffer in D3DFEDisplayInfoAboutSurfaces()\n");	
			DisplayHRESULTInDebug(hres);
		}
		wsprintf(pszTmp, L"Back surface is in %s memory\n", (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? ((ddsd.ddsCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM) ? "AGP" : "VIDEO") : "SYSTEM");
		DEBUG_WCE(pszTmp);
	}

	/* Get surface description of Z-Buffer */
	if (D3DFE.lpDDSZBuffer)
	{
		hres=D3DFE.lpDDSZBuffer->lpVtbl->GetSurfaceDesc(D3DFE.lpDDSZBuffer, &ddsd);
		if (hres!=DD_OK)
		{
			DEBUG_WCE(L"GetSurfaceDesc failed for Z Buffer in D3DFEDisplayInfoAboutSurfaces()\n");	
			DisplayHRESULTInDebug(hres);
		}
		wsprintf(pszTmp, L"Z-Buffer surface is in %s memory\n", (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? ((ddsd.ddsCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM) ? "AGP" : "VIDEO") : "SYSTEM");
		DEBUG_WCE(pszTmp);
	}
}


/*******************************************************************************
 * Function Name  : D3DFEClearSurface
 * Inputs		  : lpDDSSurface
 * Global Used    : D3DFE
 * Description    : Clear a surface to black
 *******************************************************************************/
void D3DFEClearSurface(LPDIRECTDRAWSURFACE4 lpDDSSurface)
{
   RECT				dst;
   DDBLTFX			ddbltfx;
   DDSURFACEDESC2	ddsd;
   HRESULT			hres;

   /* Initialise DDSURFACEDESC2 structure */
   ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
   ddsd.dwSize=sizeof(ddsd);
   
   /* Get surface description */
   lpDDSSurface->lpVtbl->GetSurfaceDesc(lpDDSSurface, &ddsd);   

   /* Initialise DDBLTFX structure */
   memset(&ddbltfx, 0, sizeof(ddbltfx));
   ddbltfx.dwSize = sizeof(DDBLTFX);
   
   /* Set data in DDBLTFX structure */
   ddbltfx.dwFillColor = 0;
   dst.left = dst.top = 0;
   dst.right = ddsd.dwWidth;
   dst.bottom = ddsd.dwHeight;

   /* Colorfill blit */
   hres=lpDDSSurface->lpVtbl->Blt(lpDDSSurface, &dst, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx );
   if (hres!=DD_OK)
   {
      DEBUG_WCE(L"D3DFE *WARNING* : ClearSurface() failed.\n");
	  DisplayHRESULTInDebug(hres);
   }
}


/*******************************************************************************
 * Function Name  : D3DFERemoveString
 * Inputs		  : pszStringToRemove
 * Input/Output	  : pszString
 * Global Used    : 
 * Description    : Remove string pszStringToRemove from pszString
 *******************************************************************************/
void D3DFERemoveString(char *pszString, char *pszStringToRemove)
{
	char	pszTmpString[300];
	char	*c;
	int		nPos;
	int		nStringLength=strlen(pszString);
	int		nStringTRLength=strlen(pszStringToRemove);

	/* Copy string */
	strcpy(pszTmpString, pszString);

	/* Find occurence of string to remove */
	c=strstr(pszTmpString, pszStringToRemove);

	/* If found, then remove it (actually copy the contents of the string before
	   and after the string to look for) */
	if (c)
	{
		/* Compute position of pszStringToRemove in pszString */
		nPos=c-pszTmpString;
		
		/* If a string is before pszStringToRemove, copy it to the new buffer */
		if (nPos)
		{
			strncpy(pszString, pszTmpString, nPos);
		}
		
		/* Copy the rest of the string */
		strncpy(&pszString[nPos], &pszTmpString[nPos+nStringTRLength+1], nStringLength-nStringTRLength);
		
		/* Append a zero to specify end of string */
		pszString[nStringLength-nStringTRLength]='\0';
	}
}


/*******************************************************************************
 * Function Name  : D3DFEGuidCompare
 * Inputs		  : *pGuid1, *pGuid2
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Compare two GUID. Returns TRUE if the two GUIDS are identical,
 *					FALSE otherwise.
 *******************************************************************************/
BOOL D3DFEGuidCompare(GUID *pGuid1, GUID *pGuid2)
{
	/* Test if pointers are valid */
	if (!pGuid1 || !pGuid2)
	{
		return FALSE;
	}
	
	/* Test all fields in GUID structure */
	if (pGuid1->Data1==pGuid2->Data1 &&
		pGuid1->Data2==pGuid2->Data2 &&
		pGuid1->Data3==pGuid2->Data3 &&
		*(DWORD *)&pGuid1->Data4[0]==*(DWORD *)&pGuid2->Data4[0] &&
		*(DWORD *)&pGuid1->Data4[4]==*(DWORD *)&pGuid2->Data4[4])
	{
		/* Both GUIDs are identical */
		return TRUE;
	}

	/* GUIDs have different values */
	return FALSE;
}


/*******************************************************************************
 * Function Name  : D3DFEBPPToDDBD
 * Inputs		  : bpp
 * Returns		  : DDBD-equivalent for bpp
 * Global Used    : None
 * Description    : Convert an integer bit per pixel number to a DirectDraw 
 *					bit depth flag.
 *******************************************************************************/
DWORD D3DFEBPPToDDBD(int bpp)
{
    switch(bpp)
	{
		case 1 :	return DDBD_1;
        case 2 :	return DDBD_2;
        case 4 :	return DDBD_4;
        case 8 :	return DDBD_8;
        case 16 :	return DDBD_16;
        case 24 :	return DDBD_24;
        case 32 :	return DDBD_32;
		default :	return 0;
    }
}
/*******************************************************************************
 * Function Name  : D3DShellGetResourceBitmap
 * Inputs		  : 
 * Global Used    : 
 * Description    : This function has been done to replace LoadImage()+GetObject()
 *					that are not fully implemented yet in DRAGON.
 *******************************************************************************/
void D3DShellGetResourceBitmap(BITMAP *bm, LPCWSTR lpName)
{
HRSRC hrcBMP;
HGLOBAL hgBMP;
LPBITMAPINFOHEADER lpbi;
BYTE	*prgb;

	hrcBMP = FindResource(GetModuleHandle(NULL), lpName, RT_BITMAP);

	hgBMP = LoadResource(GetModuleHandle(NULL),hrcBMP);

	lpbi = (LPBITMAPINFOHEADER)LockResource(hgBMP);

	prgb = (BYTE *) ((LPBYTE)lpbi + lpbi->biSize);

	// Output to our BITMAP structure.
	bm->bmType			= (int)0;
    bm->bmWidth			= (int)lpbi->biWidth;    
	bm->bmHeight		= (int)lpbi->biHeight;
    bm->bmWidthBytes	= (int)(lpbi->biWidth) * (lpbi->biBitCount/8);    
	bm->bmPlanes		= (BYTE)lpbi->biPlanes;    
	bm->bmBitsPixel		= (BYTE)lpbi->biBitCount;
 	bm->bmBits		    = (void *)(prgb);
}
/*******************************************************************************
 * Function Name  : LoadDCLogo
 * Inputs		  : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
BOOL LoadDCLogo(LPDIRECT3DDEVICE3 lpDev3, LPDIRECTDRAW4 lpDD4, LPDIRECT3DTEXTURE2 *lplpD3DTexture2)
{
HRESULT					hres;
LPDIRECTDRAWSURFACE4	lpDDSTextureSurface=NULL;
LPDIRECTDRAWSURFACE4	lpSrcTextureSurf=NULL;
LPDIRECTDRAWSURFACE4	lpDDS=NULL;
LPDIRECT3DTEXTURE2		lpSrcTexture=NULL;
DDSURFACEDESC2			ddsd;
DDPIXELFORMAT			PixelFormat;
DWORD					x, y, i;
unsigned short			*ptrTarget, *ptrSource;

	
	
	/* Set width and height of bitmap */
	x = 128;
	y = 128;

	/* Initialise PixelFormat structure */
	/* 4444 format */
	memset(&PixelFormat, 0, sizeof(DDPIXELFORMAT));
	PixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	PixelFormat.dwFlags				= DDPF_RGB | DDPF_ALPHAPIXELS;
	PixelFormat.dwRGBBitCount		= 16;
	PixelFormat.dwRGBAlphaBitMask	= 0x0000F000;
	PixelFormat.dwRBitMask			= 0x00000F00;
	PixelFormat.dwGBitMask			= 0x000000F0;
	PixelFormat.dwBBitMask			= 0x0000000F;
	
	/* Create texture surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
	ddsd.dwSize			=	sizeof(DDSURFACEDESC2);
	ddsd.dwFlags		=	DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps	=	DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
	ddsd.ddsCaps.dwCaps2=	0;
	ddsd.dwWidth		=	x;
	ddsd.dwHeight		=	y;
	ddsd.ddpfPixelFormat=	PixelFormat;
	

	hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, &lpDDS, NULL);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo Failed to create Bumpmap surface\n"));
		return 0;
	}
	
    /* Initialise surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
	
	/* Lock texture surface to fill it */
    hres=lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, DDLOCK_WAIT, NULL); 
    if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo Failed to lock texture surface\n"));
		return 0;
	}

	/* Convert and write data */
	ptrTarget = (unsigned short *)ddsd.lpSurface;
	ptrSource = (unsigned short *)(DCLogo+16); /* data already formated */

	for (i=0; i<x*y; i++)
	{
		*(ptrTarget+i) = *(ptrSource+i);
	}


    /* Unlock texture surface because we're done filling it */
	hres=lpDDS->lpVtbl->Unlock(lpDDS, NULL);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(TEXT("DCLogo Unlock failed in LoadTexture\n"));
		return 0;
	}
    
	lpSrcTextureSurf=lpDDS;

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=lpSrcTextureSurf->lpVtbl->QueryInterface(lpSrcTextureSurf, &IID_IDirect3DTexture2,(LPVOID*)&lpSrcTexture);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo QueryInterface failed\n"));
		return 0;
	}

	/* Get surface description */
	hres=lpSrcTextureSurf->lpVtbl->GetSurfaceDesc(lpSrcTextureSurf, &ddsd);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo GetSurfaceDesc failed\n"));
		return 0;
	}
    
    /* Create texture surface */
	memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
    ddsd.dwSize=sizeof(DDSURFACEDESC2);
    ddsd.ddsCaps.dwCaps=DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD |DDSCAPS_VIDEOMEMORY;
    ddsd.dwHeight=x;
    ddsd.dwWidth=y;
	ddsd.ddpfPixelFormat=PixelFormat;
	ddsd.dwFlags=DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    hres=lpDD4->lpVtbl->CreateSurface(lpDD4, &ddsd, (LPDIRECTDRAWSURFACE4 *)&lpDDSTextureSurface, NULL);
	if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo CreateSurface failed\n"));
		return 0;
	}

	/* QueryInterface for a Direct3DTexture2 interface */
	hres=lpDDSTextureSurface->lpVtbl->QueryInterface(lpDDSTextureSurface, &IID_IDirect3DTexture2,(LPVOID*)lplpD3DTexture2);
   if (hres!=DD_OK) 
	{
		DEBUG_WCE(TEXT("DCLogo QueryInterface failed\n"));
		return 0;
	}

	/* Load texture into memory */
	hres=(*lplpD3DTexture2)->lpVtbl->Load((*lplpD3DTexture2), lpSrcTexture);
	if (hres!=DD_OK)
	{
		DEBUG_WCE(TEXT("DCLogo Load failed\n"));
		return 0;
	}
      
	/* Release surfaces and memory */
	RELEASE(lpSrcTexture);
    RELEASE(lpSrcTextureSurf);
	RELEASE(lpDDSTextureSurface);
	
	/* Return OK */
    return TRUE;
}
/*******************************************************************************
 * Function Name  : Background
 * Input		  : 
 * Returns        : 
 * Global Used    : 
 * Description    : 
 *******************************************************************************/
void D3DShellDCLogo (int nBackgroundIntensity)
{
int i;
D3DTLVERTEX Plane[4];
WORD pFaces[] = {0,1,2, 0,2,3};
static LPDIRECT3DTEXTURE2 TextureStage0; 
static unsigned	dwAlphaBlend, dwSrc, dwDest, dwSpecular, dwFog, dwZComp, dwZCompMode;
static unsigned	ColorOp0, ColorOp1, AlphaOp0, AlphaOp1, dwMagFilt, dwMinFilt;
static unsigned	ColorArg1, ColorArg2, AlphaArg1, AlphaArg2;
static unsigned dwRenderMagFilt, dwRenderMinFilt, dwShadeMode;

     Plane[0].sx		= 530.0f;
	 Plane[0].sy		= 10.0f;
	 Plane[0].rhw		= 1.0f - 0.001f;
	 Plane[0].sz		= 0.001f;
	 Plane[0].color     = 0xFFFF3C28;
	 Plane[0].tu		= 0.0f;
     Plane[0].tv		= 1.0f;

	 Plane[1].sx		= 630.0f;
	 Plane[1].sy		= 10.0f;
	 Plane[1].rhw		= 1.0f - 0.001f;
	 Plane[1].sz		= 0.001f;
	 Plane[1].color     = 0xFFFF3C28;
	 Plane[1].tu		= 100.0f/128.0f;
     Plane[1].tv		= 1.0f;

	 Plane[2].sx		= 630.0f;
	 Plane[2].sy		= 110.0f;
	 Plane[2].rhw		= 1.0f - 0.001f;
	 Plane[2].sz		= 0.001f;
	 Plane[2].color     = 0xFFFF3C28;
	 Plane[2].tu		= 100.0f/128.0f;
     Plane[2].tv		= 1.0f-100.0f/128.0f;

	 Plane[3].sx		= 530.0f;
	 Plane[3].sy		= 110.0f;
	 Plane[3].rhw		= 1.0f - 0.001f;
	 Plane[3].sz		= 0.001f;
	 Plane[3].color     = 0xFFFF3C28;
	 Plane[3].tu		= 0.0f;
     Plane[3].tv		= 1.0f-100.0f/128.0f;
	

	  D3DFE.lpD3DDev3->lpVtbl->GetTexture(D3DFE.lpD3DDev3, 0, &TextureStage0);
	  if(TextureStage0) TextureStage0->lpVtbl->Release(TextureStage0); 

	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLOROP,		&ColorOp0);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState (D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAOP,		&AlphaOp0);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG1,		&ColorArg1);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG2,		&ColorArg2);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState (D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG1,		&AlphaArg1);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG2,		&AlphaArg2);

	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_MAGFILTER,		&dwMagFilt);
	  D3DFE.lpD3DDev3->lpVtbl->GetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_MINFILTER,		&dwMinFilt);

	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_TEXTUREMAG,		&dwRenderMagFilt);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_TEXTUREMIN,		&dwRenderMinFilt);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_FOGENABLE,		&dwFog);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZENABLE,          &dwZComp);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZFUNC,            &dwZCompMode);

	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SPECULARENABLE,	&dwSpecular);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ALPHABLENDENABLE, &dwAlphaBlend);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SRCBLEND,			&dwSrc);
      D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_DESTBLEND,		&dwDest);
	  D3DFE.lpD3DDev3->lpVtbl->GetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SHADEMODE,		&dwShadeMode);


	 /* Set render states and texture stage 0 states */
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZENABLE,			TRUE);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZFUNC,			D3DCMP_ALWAYS);

	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLOROP,		D3DTOP_MODULATE );
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );
      D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG1,		D3DTA_TEXTURE );
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG2,		D3DTA_DIFFUSE ); 
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG2,		D3DTA_TEXTURE );
  	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG2,		D3DTA_DIFFUSE );
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_MINFILTER ,		D3DTFN_LINEAR);	
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState (D3DFE.lpD3DDev3, 0, D3DTSS_MAGFILTER ,		D3DTFG_LINEAR);

	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_FOGENABLE,		FALSE);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SPECULARENABLE,	FALSE);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SRCBLEND,			D3DBLEND_SRCALPHA );
      D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_DESTBLEND,		D3DBLEND_INVSRCALPHA);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SHADEMODE,		D3DSHADE_GOURAUD);

	  /* Logo */
	  D3DFE.lpD3DDev3->lpVtbl->SetTexture(D3DFE.lpD3DDev3, 0, D3DFE.lpDCLogoTexture);
	  D3DFE.lpD3DDev3->lpVtbl->DrawIndexedPrimitive(D3DFE.lpD3DDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Plane, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	  /* Background */
	  if ((nBackgroundIntensity & 0xFF) == 0xFF)
	  {
		  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	  }
	  for (i=0; i<4; i++)
	  {
		Plane[i].color  = (nBackgroundIntensity & 0xFF) << 24 | 0x00FFFFFF;
		Plane[i].rhw		= 1.0f - 0.0011f;
		Plane[i].sz		= 0.0011f;
	  }

	  D3DFE.lpD3DDev3->lpVtbl->SetTexture(D3DFE.lpD3DDev3, 0, NULL);
	  if(nBackgroundIntensity>0)
		 D3DFE.lpD3DDev3->lpVtbl->DrawIndexedPrimitive(D3DFE.lpD3DDev3, D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, 
										  Plane, 4,  pFaces, 6, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

	 /* Restore render states */
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_TEXTUREMAG,       dwRenderMagFilt);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_TEXTUREMIN,       dwRenderMinFilt);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZENABLE,          dwZComp);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ZFUNC,            dwZCompMode);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_FOGENABLE,		dwFog);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SPECULARENABLE,	dwSpecular);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_ALPHABLENDENABLE, dwAlphaBlend);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SRCBLEND,			dwSrc);
      D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_DESTBLEND,		dwDest);
	  D3DFE.lpD3DDev3->lpVtbl->SetRenderState(D3DFE.lpD3DDev3, D3DRENDERSTATE_SHADEMODE,		dwShadeMode);

	  D3DFE.lpD3DDev3->lpVtbl->SetTexture(D3DFE.lpD3DDev3, 0,  TextureStage0);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLOROP,		ColorOp0);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAOP,		AlphaOp0);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG1,		ColorArg1);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_COLORARG2,		ColorArg2);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState (D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG1,		AlphaArg1);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_ALPHAARG2,		AlphaArg2);
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState	(D3DFE.lpD3DDev3, 0, D3DTSS_MINFILTER ,		dwMinFilt);	
	  D3DFE.lpD3DDev3->lpVtbl->SetTextureStageState (D3DFE.lpD3DDev3, 0, D3DTSS_MAGFILTER ,		dwMagFilt);

}