#ifndef D3DWIN_H
#define D3DWIN_H
/*
**-----------------------------------------------------------------------------
**  Name:       D3DWin.h
**  Purpose:    Sample D3D framework
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Includes
**-----------------------------------------------------------------------------
*/

#include "Common.h"
#include "DrvMgr.h"



/*
**-----------------------------------------------------------------------------
**  Defines
**-----------------------------------------------------------------------------
*/

// Windows messages
#define D3DWIN_GET_VALID    (WM_USER+1000)
#define D3DWIN_GET_POINTER  (WM_USER+1001)
#define D3DWIN_GET_SURFACE  (WM_USER+1002)

// Notification messages
#define D3DWIN_INIT				  (WM_USER+2000)
#define D3DWIN_FINI				  (WM_USER+2001)
#define D3DWIN_CHANGED_DRIVER	  (WM_USER+2002)
#define D3DWIN_CHANGED_MODE		  (WM_USER+2003)
#define D3DWIN_CHANGED_DEVICE	  (WM_USER+2004)

// Minimum surface size
#define D3DWIN_MIN_SIZE     64
#define D3DWIN_DEF_SIZE	   256



/*
**-----------------------------------------------------------------------------
**  Typedefs
**-----------------------------------------------------------------------------
*/

class D3DScene;						// Prevent having to include D3DScene.h
typedef D3DScene * LPD3DScene;

class D3DWindow;                    // Forward declaration
typedef D3DWindow * LPD3DWindow;



/*
**-----------------------------------------------------------------------------
**  Classes
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow
**  Purpose:    Encapsulates D3D rendering info for a window
**-----------------------------------------------------------------------------
*/

class D3DWindow {
protected:
	//
    // Flags
	//
    enum {
        DWF_VISIBLE			= 0x00000002,
        DWF_ZBUFFER			= 0x00000004,
		DWF_ACTIVE			= 0x00000008,
    } Attributes;

    enum {
        DWF_VALID_INTERFACE = 0x00000001,
		DWF_VALID_PRIMARY	= 0x00000002,
		DWF_VALID_RENDER    = 0x00000004,
		DWF_VALID_VIEWPORT  = 0x00000008,
		DWF_VALID_SCENE		= 0x00000010,
        DWF_RECALC_RECTS    = 0x00000020,
        DWF_PAINT           = 0x00000040,

		DWF_VALID		    = 0x00000007, // DWF_VALID_INTERFACE | DWF_VALID_PRIMARY | DWF_VALID_RENDER
    } Checks;

	
public:

	//
    // Creation Methods
	//
    D3DWindow (void);
    ~D3DWindow (void);

	HRESULT D3DWindow::Create (
		HWND   hWnd,			
		LPGUID lpDDGuid		= NULL,	
		DWORD  dwW			= 0L,
		DWORD  dwH			= 0L,			
		DWORD  dwBPP		= 0L,
		DWORD  dwRefresh	= 0L,
		LPGUID lpGuidD3D	= NULL,
		BOOL   fUseZBuffer	= TRUE,
		LPRECT lprSurf		= NULL);
    HRESULT Init (void);
	HRESULT Fini (void);

	//
    // Window Methods
    //
    HRESULT DrawFrame (void);

    HRESULT Move (long x, long y);
    HRESULT Resize (DWORD w, DWORD h);
	
	HRESULT RealizePalette (void);

    BOOL    isPaused (void)             { return (dwPaused != 0); }
    HRESULT Pause (BOOL fOn);

	BOOL    isActive (void)				{ return ((fAttribs & DWF_ACTIVE) ? TRUE : FALSE); }
    void	turnActiveOn (void)			{ fAttribs |= DWF_ACTIVE; }
    void	turnActiveOff (void)		{ fAttribs &= ~DWF_ACTIVE; }

    HRESULT Restore (void );

	//
	// Scene Methods
	//
	HRESULT	   AttachScene (LPD3DScene lpNewScene);
	HRESULT    DetachScene (void);

    
	//
    // Driver Methods
    //
	HRESULT ChangeDesktop (void);

    HRESULT ChangeDriver (LPGUID		lpGuidDD,
						  LPD3DDevInfo	lpDevHint);
    HRESULT ChangeDevice (LPGUID		lpGuidD3D);


	//
	// Misc. Methods
	//
	BOOL isValid (void)         { return (((fChecks & DWF_VALID) == DWF_VALID) ? TRUE : FALSE); }

    BOOL isCreateZBuffer (void) { return (fAttribs & DWF_ZBUFFER); }
    void createZBufferOn (void) { fAttribs |= DWF_ZBUFFER; }
    void createZBufferOff (void){ fAttribs &= ~DWF_ZBUFFER; }
    

	//
	// Member methods
	//
	HWND		  GetWindow (void)		{ return hWindow; }

	LPDDDrvInfo	  GetDriverInfo (void)	{ return lpCurrDriver; }
	LPDDModeInfo  GetModeInfo (void)	{ return lpCurrMode; }
	LPD3DDevInfo  GetDeviceInfo (void)	{ return lpCurrDevice; }

	LPGUID		  GetDDGuid (void)		{ return ((lpCurrDriver) ? lpCurrDriver->GetGuid () : NULL); }
	BOOL		  GetModeInfo (DWORD & w, DWORD & h, 
							   DWORD & bpp, DWORD & refresh)
					{
						if (! lpCurrMode)
							return FALSE;

						lpCurrMode->GetMode (w, h , bpp, refresh);
						return TRUE;
					}
	LPGUID		  GetD3DGuid (void)		{ return ((lpCurrDevice) ? &(lpCurrDevice->guid) : NULL); }

	LPDIRECTDRAW  GetDD (void)			{ return lpDD; }
	LPDIRECTDRAW2 GetDD2 (void)			{ return lpDD2; }
	LPDIRECT3D2   GetD3D (void)			{ return lpD3D; }

	LPDIRECTDRAWSURFACE GetPrimary (void)		{ return lpddsPrimary; }
	LPDIRECTDRAWSURFACE GetFrontBuffer (void)	{ return lpddsPrimary; }
	LPDIRECTDRAWSURFACE GetBackBuffer (void)	{ return lpddsRender; }
	LPDIRECTDRAWPALETTE	GetPalette (void)		{ return lpddpPalette; }

	LPDIRECTDRAWSURFACE GetRender (void)		{ return lpddsRender; }
	LPDIRECTDRAWSURFACE GetZBuffer (void)		{ return lpddsZBuff; }
	LPDIRECT3DDEVICE2   GetD3DDevice (void)		{ return lpd3dDevice; }
	LPDIRECT3DVIEWPORT2	GetViewport (void)		{ return lpd3dViewport; }

	HRESULT GetSurfaceRect (RECT & rSurface);
    HRESULT GetPrimaryRect (RECT & rPrimary);
	HRESULT GetSrcRect (RECT & rSrc);
    HRESULT GetDestRect (RECT & rDest);

	LPD3DScene GetScene (void)					{ return lpd3dScene; }

protected:

	//
	// Protected Methods
	//

    HRESULT ValidateDefaults (void);

	HRESULT CreateInterfaces (LPGUID lpGuidDD);
    HRESULT InitInterfaces (void);
    HRESULT FiniInterfaces (void);

	HRESULT InitWindow (void);
	HRESULT FiniWindow (void);

	HRESULT InitPrimary (void);
    HRESULT FiniPrimary (void);

    HRESULT InitPalette (void);
    HRESULT FiniPalette (void);

	HRESULT ValidateSize (void);

    HRESULT CreateRender (LPGUID lpD3DGuid, LPRECT lprSurf);
	HRESULT InitRender (void);
    HRESULT FiniRender (void);

	HRESULT InitViewport (void);
	HRESULT FiniViewport (void);
	HRESULT UpdateViewport (void);

    // Recalculate src,dest drawing rectangles
    BOOL checkCalcRects (void)	{ return (fChecks & DWF_RECALC_RECTS); }
    void turnCalcRectsOn (void) { fChecks |= DWF_RECALC_RECTS; }
    void turnCalcRectsOff(void) { fChecks &= ~DWF_RECALC_RECTS; }

    // Nothing to draw
    BOOL checkPaint (void)		{ return (fChecks & DWF_PAINT); }
    void turnPaintOn (void)		{ fChecks |= DWF_PAINT; }
    void turnPaintOff(void)		{ fChecks &= ~DWF_PAINT; }

	// Track initialization
    void turnValidInterfaceOn (void)	{ fChecks |= DWF_VALID_INTERFACE; }
    void turnValidInterfaceOff(void)	{ fChecks &= ~DWF_VALID_INTERFACE; }

    void turnValidPrimaryOn (void)		{ fChecks |= DWF_VALID_PRIMARY; }
    void turnValidPrimaryOff (void)		{ fChecks &= ~DWF_VALID_PRIMARY; }

    void turnValidRenderOn (void)		{ fChecks |= DWF_VALID_RENDER; }
    void turnValidRenderOff(void)		{ fChecks &= ~DWF_VALID_RENDER; }

    void turnValidViewportOn (void)		{ fChecks |= DWF_VALID_VIEWPORT; }
    void turnValidViewportOff(void)		{ fChecks &= ~DWF_VALID_VIEWPORT; }

	void turnValidSceneOn (void)		{ fChecks |= DWF_VALID_SCENE; }
	void turnValidSceneOff (void)		{ fChecks &= ~DWF_VALID_SCENE;}

    // Flags
    BOOL isValidDefaults (void)	{ return ((lpCurrDriver && lpCurrMode && lpCurrDevice) ? TRUE : FALSE); }
    BOOL isValidInterface (void){ return ((fChecks & DWF_VALID_INTERFACE) ? TRUE : FALSE); }
    BOOL isValidPrimary (void)  { return ((fChecks & DWF_VALID_PRIMARY) ? TRUE : FALSE); }
    BOOL isValidRender (void)   { return ((fChecks & DWF_VALID_RENDER) ? TRUE : FALSE); }
	BOOL isValidViewport (void) { return ((fChecks & DWF_VALID_VIEWPORT) ? TRUE : FALSE); }
	BOOL isValidScene (void)	{ return ((fChecks & DWF_VALID_SCENE) ? TRUE : FALSE); }

    HRESULT CalcRects (void);


	//
	// Data members
	//
    DWORD           dwSize;             // Structure Size
    DWORD           fAttribs;           // Attribute Flags
    DWORD           fChecks;            // Programming flags

    // Window Data
	HWND            hWindow;            // Window handle
    DWORD           dwPaused;           // Paused Semaphore

    // Driver Defaults
	LPDDDrvInfo		lpCurrDriver;		// Current Driver
	LPDDModeInfo	lpCurrMode;			// Current Mode
	LPD3DDevInfo	lpCurrDevice;		// Current Device
    
	// Interfaces
    LPDIRECTDRAW    lpDD;               // DirectDraw Interface
    LPDIRECTDRAW2   lpDD2;              // DirectDraw2 Interface
    LPDIRECT3D2     lpD3D;              // Direct3D2 Interface
    
    // Primary Surface
    LPDIRECTDRAWSURFACE  lpddsPrimary;  // Primary Surface
    LPDIRECTDRAWPALETTE  lpddpPalette;  // Primary Palette
    PALETTEENTRY *       lppePalette;   // Saved System palette entries

    // Render Surface
    LPDIRECTDRAWSURFACE  lpddsRender;   // Rendering surface
    LPDIRECTDRAWSURFACE  lpddsZBuff;    // Z-Buffer surface
    LPDIRECT3DDEVICE2    lpd3dDevice;	// D3D Device
	LPDIRECT3DVIEWPORT2  lpd3dViewport;	// D3D Viewport

    // Misc.
    RECT                rPrim;          // Current primary pos,size
    RECT                rSurf;          // Current surface pos,size

    RECT                rDrawDest;		// Destination rectangle
    RECT                rDrawSrc;		// Source Rectangle

	// D3D Scene
	LPD3DScene			lpd3dScene;		// D3D Scene


	// Friends
	friend	class D3DScene;

}; // End D3DWindow


   
/*
**-----------------------------------------------------------------------------
**  End of File
**-----------------------------------------------------------------------------
*/
#endif // D3DWIN_H
