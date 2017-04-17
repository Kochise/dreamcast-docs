/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRCE.cpp

Abstract:

    Windows CE specific graphics code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCInput.h"
#include "PlatUtil.h"

// Callback handler for the window.
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_CLOSE:
			gAppExit=TRUE;
			return 0L;
		case WM_DESTROY:
			gAppExit=TRUE;
            return 0L;
		// Pass input to the input handling code.
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			KeyEvent(wParam,TRUE);
			return 1;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			KeyEvent(wParam,FALSE);
			return 1;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
            
// Creates the window for DirectDraw to use.
BOOL GraphicsClass::CreateAppWindow(void)
{
	TCHAR WindowName[0x100];

	// Set up class structure.
    WNDCLASS  cls;          
    cls.hCursor        = NULL;
    cls.hIcon          = NULL;
    cls.lpszMenuName   = NULL;
    cls.hbrBackground  = NULL;
    cls.hInstance      = gHInstance;
    cls.lpszClassName  = TEXT("DC Render Window");
    cls.lpfnWndProc    = (WNDPROC)WndProc;
    cls.style          = 0;
    cls.cbWndExtra     = 0;
    cls.cbClsExtra     = 0;

    // Register our Window class.
    if (!RegisterClass(&cls))
	{
		SetErrorMessage(IDS_ERROR_WINDOWCREATE);
		return FALSE;
	}

	// Get window name.
    LoadString(gHInstance, IDS_APP_TITLE, WindowName, 0x100);

	// Create the window.
    Window = CreateWindow( TEXT("DC Render Window"), WindowName,
                              WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
							  CW_USEDEFAULT, CW_USEDEFAULT, 
							  ResX, ResY, 0L, 0L, gHInstance, 0L );
	if (!Window)
	{
		SetErrorMessage(IDS_ERROR_WINDOWCREATE);
		return FALSE;
	}

	// Make the window visible.
    ShowWindow( Window, SW_SHOWNORMAL );
    UpdateWindow( Window );

	return TRUE;
}

// Destroys the window.
void GraphicsClass::DestroyAppWindow(void)
{
	// Destroy the window.
	if (Window)
		DestroyWindow(Window);
	Window=NULL;
}

// Returns the window handle.
HWND GraphicsClass::GetAppWindow(void)
{
	return Window;
}

// Updates the front buffer destination rectangle in response to the window being moved.
void GraphicsClass::AppWindowMoving(void)
{
	// Don't do this if we're not initialized yet.
	if (!Initialized)
		return;

	// Get the screen coordinates of the window client area.
	GetClientRect( Window, &WindowScreenRect );
	ClientToScreen( Window, (POINT*)&WindowScreenRect.left );
	ClientToScreen( Window, (POINT*)&WindowScreenRect.right );
}

// Returns the screen coordinates of the centre of our window.
void GraphicsClass::GetAppWindowCentre(int *X, int *Y)
{
	if (Windowed)
	{
		*X=(WindowScreenRect.right+WindowScreenRect.left)/2;
		*Y=(WindowScreenRect.top+WindowScreenRect.bottom)/2;
	}
	else
	{
		*X=ResX/2;
		*Y=ResY/2;
	}
}

// Checks the capabilities of a hardware device to see if it is good enough.
static BOOL CheckHardwareCaps(D3DDEVICEDESC *Desc)
{
	// Not necessary on Dreamcast.
	return TRUE;
}

// Callback function to enumerate Z buffer formats.
static HRESULT WINAPI EnumZBufferFormatsCallback( DDPIXELFORMAT* pddpf,
                                                  VOID* pddpfDesired )
{
    if( NULL==pddpf || NULL==pddpfDesired )
        return D3DENUMRET_CANCEL;

    // If the current pixel format's match the desired ones (DDPF_ZBUFFER and
    // possibly DDPF_STENCILBUFFER), lets copy it and return. This function is
    // not choosy...it accepts the first valid format that comes along.
    if( pddpf->dwFlags == ((DDPIXELFORMAT*)pddpfDesired)->dwFlags )
    {
        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );

		// We're happy with a 16-bit z-buffer. Otherwise, keep looking.
		if( pddpf->dwZBufferBitDepth == 16 )
			return D3DENUMRET_CANCEL;
    }

    return D3DENUMRET_OK;
}

// Returns the number of bits in a bitmask.
int GetNumberOfBits( DWORD dwMask )
{
    int wBits = 0;
    while( dwMask )
    {
        dwMask = dwMask & ( dwMask - 1 );  
        wBits++;
    }
    return wBits;
}

// Looks for a suitable RGB texture format, currently 565.
static HRESULT CALLBACK RGBTextureSearchCallback( DDPIXELFORMAT* pddpf, VOID* param )
{
	// Don't want any of these.
	if (pddpf->dwFlags & (DDPF_ALPHA | DDPF_ALPHAPREMULT | 
						  DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV |
						  DDPF_COMPRESSED | DDPF_FOURCC |
						  DDPF_LUMINANCE | 
						  DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 |
						  DDPF_PALETTEINDEXED4 | DDPF_PALETTEINDEXED8 |
						  DDPF_PALETTEINDEXEDTO8 | DDPF_RGBTOYUV |
						  DDPF_STENCILBUFFER | DDPF_YUV |
						  DDPF_ZBUFFER | DDPF_ZPIXELS))
		return DDENUMRET_OK;
	// Must have this.
	if (!(pddpf->dwFlags & DDPF_RGB))
		return DDENUMRET_OK;
	// Don't want this.
	if (pddpf->dwFlags & DDPF_ALPHAPIXELS )
		return DDENUMRET_OK;
	// Check bit counts.
	if (GetNumberOfBits(pddpf->dwRBitMask)!=5)
		return DDENUMRET_OK;
	if (GetNumberOfBits(pddpf->dwGBitMask)!=6)
		return DDENUMRET_OK;
	if (GetNumberOfBits(pddpf->dwBBitMask)!=5)
		return DDENUMRET_OK;

	DCCopyMemory(param,pddpf,sizeof(DDPIXELFORMAT));
	return DDENUMRET_CANCEL;
}

// Looks for a suitable ARGB texture format, currently 4444.
static HRESULT CALLBACK ARGBTextureSearchCallback( DDPIXELFORMAT* pddpf, VOID* param )
{
	// Don't want any of these.
	if (pddpf->dwFlags & (DDPF_ALPHA | DDPF_ALPHAPREMULT | 
						  DDPF_BUMPLUMINANCE | DDPF_BUMPDUDV |
						  DDPF_COMPRESSED | DDPF_FOURCC |
						  DDPF_LUMINANCE | 
						  DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 |
						  DDPF_PALETTEINDEXED4 | DDPF_PALETTEINDEXED8 |
						  DDPF_PALETTEINDEXEDTO8 | DDPF_RGBTOYUV |
						  DDPF_STENCILBUFFER | DDPF_YUV |
						  DDPF_ZBUFFER | DDPF_ZPIXELS))
		return DDENUMRET_OK;
	// Must have this.
	if (!(pddpf->dwFlags & DDPF_RGB))
		return DDENUMRET_OK;
	// Must have this.
	if (!(pddpf->dwFlags & DDPF_ALPHAPIXELS))
		return DDENUMRET_OK;
	// Check bit counts.
	if (GetNumberOfBits(pddpf->dwRBitMask)!=4)
		return DDENUMRET_OK;
	if (GetNumberOfBits(pddpf->dwGBitMask)!=4)
		return DDENUMRET_OK;
	if (GetNumberOfBits(pddpf->dwBBitMask)!=4)
		return DDENUMRET_OK;
	if (GetNumberOfBits(pddpf->dwRGBAlphaBitMask)!=4)
		return DDENUMRET_OK;

	DCCopyMemory(param,pddpf,sizeof(DDPIXELFORMAT));
	return DDENUMRET_CANCEL;
}

// Creates stuff required for Direct3D.
// i.e. DirectDraw surfaces and a Direct3D device.
BOOL GraphicsClass::CreateD3D(GUID *pDriverGUID, int BitDepth)
{
    // Create the DirectDraw interface, and query for the DD4 interface.
    LPDIRECTDRAW pDD;
    if( FAILED( DirectDrawCreate( pDriverGUID, &pDD, NULL ) ) )
	{
		SetErrorMessage(IDS_ERROR_DDCREATE);
		return FALSE;
	}

    if( FAILED( pDD->QueryInterface( IID_IDirectDraw4, (VOID**)&DDInterface ) ) )
    {
        pDD->Release();
		SetErrorMessage(IDS_ERROR_DD4CREATE);
        return FALSE;
    }
    pDD->Release();

    // Set the Windows cooperative level.
    if( FAILED( DDInterface->SetCooperativeLevel( Window, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) ) )
	{
		SetErrorMessage(IDS_ERROR_SETCOOPLEVEL);
		return FALSE;
	}

	// Get Direct3D interface.
    if( FAILED( DDInterface->QueryInterface( IID_IDirect3D3, (VOID**)&D3DInterface ) ) )
	{
		SetErrorMessage(IDS_ERROR_D3DCREATE);
		return FALSE;
	}

	// Find the appropriate Direct3D device.
    D3DFINDDEVICERESULT  devResult;
    D3DFINDDEVICESEARCH  devSearch;
    DCZeroMemory( &devResult, sizeof(D3DFINDDEVICERESULT) );
    devResult.dwSize  = sizeof(D3DFINDDEVICERESULT);
    DCZeroMemory( &devSearch, sizeof(D3DFINDDEVICESEARCH) );
    devSearch.dwSize  = sizeof(D3DFINDDEVICESEARCH);
	devSearch.dwFlags = D3DFDS_COLORMODEL | 
						D3DFDS_HARDWARE;
	devSearch.bHardware=TRUE;
	devSearch.dcmColorModel = D3DCOLOR_RGB;

    if( FAILED( D3DInterface->FindDevice( &devSearch, &devResult ) ) )
	{
		SetErrorMessage(IDS_ERROR_NOD3DDEVICE);
		return FALSE;
	}

	// Check hardware capabilities.
	if (!CheckHardwareCaps(&devResult.ddHwDesc))
	{
		SetErrorMessage(IDS_ERROR_HARDWARECAPS);
		return FALSE;
	}

	// Create buffers.
	DDSURFACEDESC2 ddsd;
	DCZeroMemory(&ddsd,sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
    ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

	// Different depending on whether windowed or not.
	// But on Dreamcast windowed is not possible so just use
	// full screen code.
	{
		// Set display mode.
		if( FAILED( DDInterface->SetDisplayMode(ResX, ResY, 
												BitDepth,
												0,0) ) )
		{
			SetErrorMessage(IDS_ERROR_SETDISPLAYMODE);
			return FALSE;
		}
		// Create flipping surface.
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE |
							  DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;

		if( FAILED( DDInterface->CreateSurface( &ddsd, &FrontBuffer, NULL ) ) )
		{
			SetErrorMessage(IDS_ERROR_SURFACECREATE);
			return FALSE;
		}

		// Get back buffer.
		DDSCAPS2 ddscaps;
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

		if( FAILED( FrontBuffer->GetAttachedSurface( &ddscaps, 
													 &BackBuffer ) ) )
		{
			SetErrorMessage(IDS_ERROR_SURFACECREATE);
			return FALSE;
		}
	}

	// Clear the front and back buffer surfaces.
	DDBLTFX BltFx;
	BltFx.dwSize = sizeof( DDBLTFX );
	BltFx.dwFillColor = 0;
	FrontBuffer->Blt(NULL,                   // dest rect
					 NULL,                   // src surface
					 NULL,                   // src rect
					 DDBLT_COLORFILL | DDBLT_WAIT,
					 &BltFx);
	BackBuffer ->Blt(NULL,                   // dest rect
					 NULL,                   // src surface
					 NULL,                   // src rect
					 DDBLT_COLORFILL | DDBLT_WAIT,
					 &BltFx);

	// Create D3D device.
    if( FAILED( D3DInterface->CreateDevice( devResult.guid, BackBuffer,
											&D3DDevice, NULL ) ) )
	{
		SetErrorMessage(IDS_ERROR_D3DDEVICECREATE);
		return FALSE;
	}

	// Create viewport.
	if (FAILED( D3DInterface->CreateViewport( &Viewport, NULL) ) )
	{
		SetErrorMessage(IDS_ERROR_VIEWPORTCREATE);
		return FALSE;
	}

	// Add viewport to rendering device.
	if (FAILED( D3DDevice->AddViewport( Viewport ) ) )
	{
		SetErrorMessage(IDS_ERROR_ADDVIEWPORT);
		return FALSE;
	}

	// Note: We don't set the viewport paramters here.

    // Finally, set the current viewport for the rendering device.
    if( FAILED( D3DDevice->SetCurrentViewport( Viewport ) ) )
	{
		SetErrorMessage(IDS_ERROR_SETVIEWPORT);
		return FALSE;
	}

	// Find some texture formats which are suitable for us.
	// Do RGB format.
	D3DDevice->EnumTextureFormats(RGBTextureSearchCallback,&RGBPixelFormat);
	if (RGBPixelFormat.dwSize!=sizeof(DDPIXELFORMAT))
	{
		SetErrorMessage(IDS_ERROR_TEXTUREFORMAT);
		return FALSE;
	}
	
	// Do ARGB format.
	D3DDevice->EnumTextureFormats(ARGBTextureSearchCallback,&ARGBPixelFormat);
	if (ARGBPixelFormat.dwSize!=sizeof(DDPIXELFORMAT))
	{
		SetErrorMessage(IDS_ERROR_TEXTUREFORMAT);
		return FALSE;
	}
	
	// See if running on a TV.
	if (GetVideoOutputFormat()!=VIDFMT_VGA)
		TV=TRUE;

	// Set max texture dimensions. Might as well hard code it on Dreamcast.
	MaxTextureWidth=MaxTextureHeight=1024;
		
	return TRUE;
}

// Destroys all the Direct3D stuff.
void GraphicsClass::DestroyD3D(void)
{
#define RELEASE(A) if (A) { (A)->Release(); (A)=NULL; }

	// Release everything.
	RELEASE(Viewport);
	RELEASE(D3DDevice);
	RELEASE(ZBuffer);
	RELEASE(BackBuffer);
	RELEASE(FrontBuffer);
	RELEASE(D3DInterface);
	
	// DirectDraw interface.
	if (DDInterface)
	{
		// Destroy interface.
		DDInterface->Release();

		DDInterface=NULL;
	}

#undef RELEASE
}

// Blits the back buffer to the front buffer. This is a flip in windowed mode.
void GraphicsClass::BlitBackBufferToFrontBuffer(void)
{
}

// Not implemented - no need on Dreamcast.
BOOL GraphicsClass::GetScreenShot(DCRect *Region, DWORD **RetData)
{
	return FALSE;
}

// Dump a screenshot to disk.
void GraphicsClass::DumpScreenShot(void)
{
}

// Locks the depth buffer.
BOOL GraphicsClass::LockDepthBuffer(void **Address, int *Stride)
{
	return FALSE;
}

// Unlocks the depth buffer.
void GraphicsClass::UnlockDepthBuffer(void)
{
}

// Returns the bit depth of the depth buffer.
int GraphicsClass::GetDepthBufferBitDepth(void)
{
	DDPIXELFORMAT Format;

	DCZeroMemory(&Format,sizeof(DDPIXELFORMAT));
	Format.dwSize=sizeof(DDPIXELFORMAT);
	if (FAILED(ZBuffer->GetPixelFormat(&Format)))
	{
		DC_ERROR(("IDirectDrawSurface4::GetPixelFormat failed.\n"));
		return 0;
	}
		
	return Format.dwRGBBitCount;
}

// Dump a depth buffer screenshot to disk.
void GraphicsClass::DumpDepthBufferShot(void)
{
}
