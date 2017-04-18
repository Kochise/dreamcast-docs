/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRPC.cpp

Abstract:

    PC specific graphics code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCInput.h"

// Callback handler for the window.
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
#if 0
		case WM_SETCURSOR:
            if( !gAppPaused && gGraphics.IsWindowed() )
            {
                SetCursor(NULL);
                return TRUE;
            }
            break;
#endif
		case WM_MOVE:
            if( !gAppPaused && gGraphics.IsWindowed() )
				gGraphics.AppWindowMoving();
            break;
        case WM_PAINT:
            if(gGraphics.IsWindowed() )
				gGraphics.BlitBackBufferToFrontBuffer();
            break;
        case WM_CLOSE:
			gAppExit=TRUE;
			return 0L;
		case WM_DESTROY:
			gAppExit=TRUE;
            return 0L;
        case WM_SYSCOMMAND:
            switch( LOWORD(wParam) )
            {
				case SC_MONITORPOWER:
					// Prevent potential crashes when the monitor powers down
					return 1;
            }
            break;
		// Pass input to the input handling code.
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			KeyEvent(wParam,TRUE);
			return 1;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			KeyEvent(wParam,FALSE);
			return 1;
		// Handle app activate/deactivate.
//todo: [WndProc] Can't seem to make this work right.
		case WM_ACTIVATE:
			if (LOWORD(wParam)==WA_INACTIVE || (BOOL)HIWORD(wParam))
			{
				// App is minimized or not active.
//				gAppPaused=TRUE;
//				TimerPauseAppTime();
				UnacquireInput();
			}
			else
			{
				// App is active.
//				gAppPaused=FALSE;
//				TimerUnpauseAppTime();
				AcquireInput();
//				gGraphics.RestoreSurfaces();
			}
			break;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
            
// Creates the window for DirectDraw to use.
BOOL GraphicsClass::CreateAppWindow(void)
{
	TCHAR WindowName[0x100];

    static WNDCLASS WndClass = {CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, gHInstance,
								LoadIcon( NULL, IDI_WINLOGO ),
								LoadCursor(NULL, IDC_ARROW), 
								(HBRUSH)GetStockObject(WHITE_BRUSH),
								NULL, TEXT("DC Render Window") };

    // Register our Window class.
	if (RegisterClass( &WndClass )==0)
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

	// Resizes the window so the client rect matches our desired resolution.
	RECT ClientR,WindowR;
	GetClientRect(Window,&ClientR);
	GetWindowRect(Window,&WindowR);
	int HAdj=(WindowR.right-WindowR.left) - (ClientR.right-ClientR.left);
	int VAdj=(WindowR.bottom-WindowR.top) - (ClientR.bottom-ClientR.top);
	SetWindowPos(Window,NULL,0,0,ResX+HAdj,ResY+VAdj,SWP_NOMOVE | SWP_NOREDRAW | SWP_NOZORDER);

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
	// Should really implement this.
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

	CopyMemory(param,pddpf,sizeof(DDPIXELFORMAT));
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

	CopyMemory(param,pddpf,sizeof(DDPIXELFORMAT));
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
	DWORD CoopFlags=(Windowed) ? DDSCL_NORMAL | DDSCL_FPUSETUP :
								 DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | 
								 DDSCL_FULLSCREEN | DDSCL_FPUSETUP;
    if( FAILED( DDInterface->SetCooperativeLevel( Window, CoopFlags ) ) )
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
	if (Windowed)
	{
		// Get front buffer.
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		if( FAILED( DDInterface->CreateSurface( &ddsd, &FrontBuffer, NULL ) ) )
		{
			SetErrorMessage(IDS_ERROR_SURFACECREATE);
			return FALSE;
		}

		// Get back buffer.
		ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		ddsd.dwWidth        = ResX;
		ddsd.dwHeight       = ResY;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		if( FAILED( DDInterface->CreateSurface( &ddsd, &BackBuffer, NULL ) ) )
		{
			SetErrorMessage(IDS_ERROR_SURFACECREATE);
			return FALSE;
		}

		// Create a clipper object.
		LPDIRECTDRAWCLIPPER pcClipper;
		if( FAILED( DDInterface->CreateClipper( 0, &pcClipper, NULL ) ) )
		{
			SetErrorMessage(IDS_ERROR_CLIPPERCREATE);
			return FALSE;
		}

		// Associate the clipper with the window.
		pcClipper->SetHWnd( 0, Window );
		FrontBuffer->SetClipper( pcClipper );
		
		// Don't need to keep this anymore.
		if (pcClipper)
			pcClipper->Release();

		// Get the screen coordinates of the window client area.
		GetClientRect( Window, &WindowScreenRect );
		ClientToScreen( Window, (POINT*)&WindowScreenRect.left );
		ClientToScreen( Window, (POINT*)&WindowScreenRect.right );
	}
	else
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
		ddsd.dwBackBufferCount = (TripleBuffer) ? 2 : 1;

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


	// Don't worry about allocating a Z buffer if the hardware does Z bufferless HSR.
	if (!(devResult.ddHwDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR))
	{
		// Get format for the Z buffer.
		DDPIXELFORMAT ZPixelFormat;
		DCZeroMemory( &ZPixelFormat, sizeof(DDPIXELFORMAT) );
		ZPixelFormat.dwFlags = DDPF_ZBUFFER;

		D3DInterface->EnumZBufferFormats( devResult.guid ,
										  EnumZBufferFormatsCallback,
										  (VOID *)&ZPixelFormat);
		if (!ZPixelFormat.dwSize)
		{
			SetErrorMessage(IDS_ERROR_NOZBUFFERFORMAT);
			return FALSE; // Coult find an appropriate format.
		}

		// Create Z buffer.
		DDSURFACEDESC2 ddsd;
		DCZeroMemory(&ddsd,sizeof(DDSURFACEDESC2));
		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
		ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | 
					   DDSD_CAPS | DDSD_PIXELFORMAT;
	    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
		ddsd.dwWidth        = ResX;
		ddsd.dwHeight       = ResY;
	    memcpy( &ddsd.ddpfPixelFormat, &ZPixelFormat, sizeof(DDPIXELFORMAT) );

		// Create it.
		if( FAILED( DDInterface->CreateSurface( &ddsd, &ZBuffer, NULL ) ) )
		{
			SetErrorMessage(IDS_ERROR_ZBUFFERCREATE);
			return FALSE;
		}

		// Attach it.
	    if( FAILED( BackBuffer->AddAttachedSurface( ZBuffer ) ) )
		{
			SetErrorMessage(IDS_ERROR_ATTACHZBUFFER);
			return FALSE;
		}
	}

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

	// Set max texture dimensions.
	D3DDEVICEDESC HALCaps;
	D3DDEVICEDESC HELCaps;
	DCZeroMemory(&HALCaps,sizeof(D3DDEVICEDESC));
	DCZeroMemory(&HELCaps,sizeof(D3DDEVICEDESC));
	HALCaps.dwSize=HELCaps.dwSize=sizeof(D3DDEVICEDESC);
	if (FAILED(D3DDevice->GetCaps(&HALCaps,&HELCaps)) || 
		HALCaps.dwMaxTextureWidth < 256 || HALCaps.dwMaxTextureHeight < 256)
	{
		SetErrorMessage(IDS_ERROR_HARDWARECAPS);
		return FALSE;
	}
	MaxTextureWidth=HALCaps.dwMaxTextureWidth;
	MaxTextureHeight=HALCaps.dwMaxTextureHeight;

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
	    // Resore cooperative level.
		DDInterface->SetCooperativeLevel( Window, DDSCL_NORMAL );

		// Destroy interface.
		DDInterface->Release();

		DDInterface=NULL;
	}

#undef RELEASE
}

// Blits the back buffer to the front buffer. This is a flip in windowed mode.
void GraphicsClass::BlitBackBufferToFrontBuffer(void)
{
	// Don't do this if we're not initialized yet.
	if (!Initialized)
		return;

	// Blit entire back buffer surface to front buffer surface.
	FrontBuffer->Blt(&WindowScreenRect,BackBuffer,NULL,DDBLT_WAIT,NULL);
}

BOOL GraphicsClass::GetScreenShot(DCRect *Region, DWORD **RetData)
{
	// Figure out rectangle to get.
	DCRect R;
	if (!Region)
	{
		R.X1=0;
		R.Y1=0;
		R.X2=ResX-1;
		R.Y2=ResY-1;
	}
	else
	{
		R=*Region;
		R.X1=__min(ResX-1,__max(0,R.X1));
		R.X2=__min(ResX-1,__max(0,R.X2));
		R.Y1=__min(ResY-1,__max(0,R.Y1));
		R.Y2=__min(ResY-1,__max(0,R.Y2));
	}
	
	// Allocate buffer to hold image.
	int Size=(R.X2-R.X1+1)*(R.Y2-R.Y1+1);
	DWORD *Buffer=(DWORD *)DCMalloc(Size*sizeof(DWORD));
	if (Buffer)
	{
		// Lock frame buffer.
		// In windowed mode we take the back buffer, 
		// full screen the front buffer.
		BOOL Front=(Windowed==FALSE) ? TRUE : FALSE;
		void *Address;
		int  Stride;
		if (LockFrameBuffer(&Address,&Stride,Front,TRUE))
		{
			// Copy image from frame buffer to our buffer.
			int BitDepth=gGraphics.GetFrameBufferBitDepth();
			DWORD *Dst=Buffer;
			for (int Y=R.Y1;Y<=R.Y2;Y++)
			{
				void *Src=(VOID *)( ((BYTE *)Address) + (ResY-Y-1)*Stride );
//				DWORD *Dst=Buffer + Y*(R.X2-R.X1+1);

				switch (BitDepth)
				{
					case 15:
						Src=((WORD *)Src)+R.X1;
						break;
					case 16:
						Src=((WORD *)Src)+R.X1;
						break;
					case 24:
						Src=((BYTE *)Src)+3*R.X1;
						break;
					case 32:
						Src=((BYTE *)Src)+4*R.X1;
						break;
				}

				for (int X=R.X1;X<=R.X2;X++)
				{
					DWORD R,G,B;

					switch (BitDepth)
					{
						case 15:
						{
							DWORD Tmp=*(WORD *)Src;
							R=(Tmp & 0x7E00) >> 7;
							G=(Tmp & 0x03E0) >> 2;
							B=(Tmp & 0x001F) << 3;
							R=R | (R>>5);
							G=G | (G>>5);
							B=B | (B>>5);
							Src=((WORD *)Src)+1;
							break;
						}
						case 16:
						{
							DWORD Tmp=*(WORD *)Src;
							R=(Tmp & 0xF800) >> 8;
							G=(Tmp & 0x07E0) >> 3;
							B=(Tmp & 0x001F) << 3;
							R=R | (R>>5);
							G=G | (G>>6);
							B=B | (B>>5);
							Src=((WORD *)Src)+1;
							break;
						}
						case 24:
						{
							R=((BYTE *)Src)[2];
							G=((BYTE *)Src)[1];
							B=((BYTE *)Src)[0];
							Src=((BYTE *)Src)+3;
							break;
						}
						case 32:
						{
							R=((BYTE *)Src)[2];
							G=((BYTE *)Src)[1];
							B=((BYTE *)Src)[0];
							Src=((BYTE *)Src)+4;
							break;
						}
					}
					*Dst=0xFF000000 | (R << 16) | (G << 8) | (B);
					Dst++;
				}
			}

			// Unlock frame buffer.
			UnlockFrameBuffer(Front);

			*RetData=Buffer;
			return TRUE;
		}
		DCFree(Buffer);
	}
	return FALSE;
}

// Dump a screenshot to disk.
void GraphicsClass::DumpScreenShot(void)
{
	DWORD *Buffer;

	if (GetScreenShot(NULL,&Buffer))
	{
		// Figure out name for the screenshot.
		TCHAR Name[0x100];
		for (int i=0;i<9999;i++)
		{
			wsprintf(Name,TEXT("SHOT%04i.bmp"),i);

			if (!DoesFileExist(ROOT_DIRECTORY,Name))
				break;
		}
	
		// Write image to disk.
		wsprintf(Name,TEXT("SHOT%04i"),i);
		WriteImageFile(Name,ResX,ResY,FALSE,Buffer,TEXT("."));

		// Release buffer.	
		DCFree(Buffer);
	}
}

// Locks the depth buffer.
BOOL GraphicsClass::LockDepthBuffer(void **Address, int *Stride)
{
	DDSURFACEDESC2 Desc;
	DCZeroMemory(&Desc,sizeof(DDSURFACEDESC2));
	Desc.dwSize=sizeof(DDSURFACEDESC2);
	DWORD Flags=DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR;

	if (FAILED(ZBuffer->Lock(NULL,&Desc,Flags,NULL)))
		return FALSE;

	*Address=Desc.lpSurface;
	*Stride=Desc.lPitch;

	return TRUE;
}

// Unlocks the depth buffer.
void GraphicsClass::UnlockDepthBuffer(void)
{
	ZBuffer->Unlock(NULL);
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
#ifdef _DEBUG // This code is a bit dodgy with bit depths so leave out of release builds.
	// Allocate buffer to hold image.
	DWORD *Buffer=(DWORD *)DCMalloc(ResX*ResY*sizeof(DWORD));
	if (Buffer)
	{
		int BitDepth=gGraphics.GetDepthBufferBitDepth();

		// Lock buffer.
		void *Address;
		int  Stride;
		if (LockDepthBuffer(&Address,&Stride))
		{
			// Copy image from frame buffer to our buffer.
			DWORD *Dst=Buffer;
			for (int Y=0;Y<ResY;Y++)
			{
				void *Src=(VOID *)( ((BYTE *)Address) + (ResY-Y-1)*Stride );
				DWORD *Dst=Buffer + Y*ResX;
				for (int X=0;X<ResX;X++)
				{
					DWORD Val;

					switch (BitDepth)
					{
						case 16:
						{
							Val=((WORD *)Src)[0];
							Src=((BYTE *)Src)+2;
							break;
						}
						default:
							Val=0;
					}
					// Val is now between 0 and 65535
#if 1
					*Dst=0xFF000000 | ((Val & 0xFF00) << 8);
					if ((Val & 0xFF00)==0xFF00)
						*Dst|=(Val & 0x00FF) | ((Val & 0x00FF)<<8);
#else
					if (Val==0)
						Val=1;
					float Tmp=(float)(log((float)Val)/log(1.044451f));
					DWORD Tmp2=(DWORD)Tmp;

					if (Tmp2> 255) Tmp2=255;
					if (Tmp2< 0) Tmp2=0;
					
					*Dst=0xFF000000 | (Tmp2 << 16) |
						 (Tmp2 << 8) | (Tmp2);
#endif
					Dst++;
				}
			}

			// Unlock frame buffer.
			UnlockDepthBuffer();

			// Figure out name for the screenshot.
			TCHAR Name[0x100];
			for (int i=0;i<9999;i++)
			{
				wsprintf(Name,TEXT("ZShot%04i"),i);

				if (!DoesFileExist(ROOT_DIRECTORY,Name))
					break;
			}
		
			// Write image to disk.
			WriteImageFile(Name,ResX,ResY,FALSE,Buffer,TEXT("."));

		}
		// Release buffer.	
		DCFree(Buffer);
	}
#endif
}
