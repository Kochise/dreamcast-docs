/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRMain.cpp

Abstract:

    Main graphics code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

// Define global here.
GraphicsClass gGraphics;

static void InitStage(LPDIRECT3DDEVICE3 D3DDevice, int Stage)
{
	D3DDevice->SetTextureStageState(Stage,D3DTSS_MINFILTER,D3DTFN_LINEAR);
	D3DDevice->SetTextureStageState(Stage,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
	D3DDevice->SetTextureStageState(Stage,D3DTSS_MIPFILTER,D3DTFP_POINT);
	D3DDevice->SetTextureStageState(Stage,D3DTSS_TEXCOORDINDEX,Stage);
}

// Initializes the graphics class.
BOOL GraphicsClass::Initialize(GUID *pDriverGUID,
							   int ResXIn,
							   int ResYIn,
							   int BitDepthIn,
							   BOOL WindowedIn,
							   BOOL TripleBufferIn)
{
	// Set variables.
	DCZeroMemory(this,sizeof(GraphicsClass));
	
	ResX=ResXIn;
	ResY=ResYIn;
	Windowed=WindowedIn;
	TripleBuffer=TripleBufferIn;

	// Create window.
	if (!CreateAppWindow())
		return FALSE;

	// Create D3D objects etc.
	if (!CreateD3D(pDriverGUID,BitDepthIn))
	{
		// Make sure we destroy anything that might have been created.
		DestroyD3D();
		DestroyAppWindow();
		return FALSE;
	}

	// Disable transforms which also sets up the viewport parameters.
	EnableTransforms();

	// Initialize texture management.
	FirstFreeTextureIndex=0;
	UseTextureCaching=FALSE;

	// Primitive handling.
	VertexType=D3DFVF_TLVERTEX;
	VertexType2L=D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX2;
	VertexFlags=D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS;
	
	// Init viewport.
	DCZeroMemory(&ViewportData,sizeof(D3DVIEWPORT2));
	ViewportData.dwSize=sizeof(D3DVIEWPORT2);
	ViewportData.dwWidth=ResX;
	ViewportData.dwHeight=ResY;
	ViewportData.dvMaxZ=1.0f;
	ViewportData.dvClipWidth=(float)ResX;
	ViewportData.dvClipHeight=(float)ResY;
	Viewport->SetViewport2(&ViewportData);

	// Initialize any other D3D state.
	D3DDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE,BitDepthIn==16); // Dither.
	D3DDevice->SetRenderState(D3DRENDERSTATE_SUBPIXEL,TRUE); // Sub pixel correction.
	for (int i=0;i<3;i++)
		InitStage(D3DDevice,i);

	// 2D Scale/Translate (this gets set properly elsewhere, once per frame).
	ScaleX2D=ScaleY2D=1.0f;
	TransX2D=TransY2D=0.0f;

	// 3D Scale/Translate.
	ScaleX3D=ResX*0.5f;
	TransX3D=ResX*0.5f;
	ScaleY3D=-ResY*0.5f;
	TransY3D=ResY*0.5f;

	Initialized=TRUE;
	return TRUE;
}

// Shut down the gaphics class.
void GraphicsClass::Shutdown(void)
{
	if (Initialized)
	{
		// Free textures.
		ReleaseTextures();

		// Free texture management stuff.
		FirstFreeTextureIndex=0;
		UseTextureCaching=FALSE;

		// Release D3D objects etc.
		DestroyD3D();
		DestroyAppWindow();
	}
}

// Sees if any surfaces are lost and if so, restores them.
void GraphicsClass::RestoreSurfaces(void)
{
	// Make sure we're initialized.
	if (!Initialized)
		return;

	// Restore our buffers.
	if (FrontBuffer->IsLost()==DDERR_SURFACELOST)
		FrontBuffer->Restore();
	if (BackBuffer->IsLost()==DDERR_SURFACELOST)
		BackBuffer->Restore();
	if (ZBuffer->IsLost()==DDERR_SURFACELOST)
		ZBuffer->Restore();

	// Restore and reload textures.
	RestoreTextures();
}

// Begins the scene.
BOOL GraphicsClass::BeginScene(void)
{
    if( FAILED( D3DDevice->BeginScene() ) )
    {
		// Even though it failed we must still call EndScene. 
		D3DDevice->EndScene();
		return FALSE;
	}
	return TRUE;
}

// End scene.
BOOL GraphicsClass::EndScene(void)
{
	if (FAILED(D3DDevice->EndScene()))
		return FALSE;
	return TRUE;
}

// Flip buffers.
void GraphicsClass::Flip(void)
{
	if (Windowed)
		BlitBackBufferToFrontBuffer();
	else
		FrontBuffer->Flip(NULL,DDFLIP_WAIT);
}

// Frame buffer lock.
BOOL GraphicsClass::LockFrameBuffer(void **Address, int *Stride, BOOL Front, BOOL Read)
{
	LPDIRECTDRAWSURFACE4 Buffer=(Front) ? FrontBuffer : BackBuffer;
	DDSURFACEDESC2 Desc;
	DCZeroMemory(&Desc,sizeof(DDSURFACEDESC2));
	Desc.dwSize=sizeof(DDSURFACEDESC2);
	DWORD Flags=DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR;
	RECT *Rect=(Windowed && Front) ? &WindowScreenRect : NULL;

	if (!Read)
		Flags|=DDLOCK_WRITEONLY;

	if (FAILED(Buffer->Lock(Rect,&Desc,Flags,NULL)))
		return FALSE;

	*Address=Desc.lpSurface;
	*Stride=Desc.lPitch;

	return TRUE;
}

// Frame buffer unlock.
void GraphicsClass::UnlockFrameBuffer(BOOL Front)
{
	LPDIRECTDRAWSURFACE4 Buffer=(Front) ? FrontBuffer : BackBuffer;

	Buffer->Unlock(NULL);
}


// Returns the frame buffer bit depth which must be either 555, 565, 888 or 8888.
int GraphicsClass::GetFrameBufferBitDepth(void)
{
	DDPIXELFORMAT Format;
	int Bpp;

	DCZeroMemory(&Format,sizeof(DDPIXELFORMAT));
	Format.dwSize=sizeof(DDPIXELFORMAT);
	if (FAILED(FrontBuffer->GetPixelFormat(&Format)))
	{
		DC_ERROR(("IDirectDrawSurface4::GetPixelFormat failed.\n"));
		return 0;
	}
		
	// Default to zero
	Bpp=0;
	// Figure it out from the returned data
	if (Format.dwFlags & DDPF_RGB)
	{
		switch (Format.dwRGBBitCount) /* 4 8 16 24 or 32 */
		{
			case 16:
				if (Format.dwGBitMask & 0x0400)
					Bpp = 16;	// 565
				else
					Bpp = 15;	// Bit 15 not red implies 555
				break;
			case 24:
			case 32:
				Bpp = Format.dwRGBBitCount;
				break;
		}
	}
	
	// Make sure format was ok.
	if (Bpp==0)
	{
		DC_ERROR(("Frame buffer format is not valid.\n"));
		return 0;
	}
	
	// Done, so return value.
	return Bpp;
}

// Clears the selected buffer(s) to the specified value(s).
void GraphicsClass::Clear(DCRect *Rect,
						  BOOL FrameBuffer, DWORD Color, 
						  BOOL ZBuffer, float ZValue,
						  BOOL StencilBuffer, DWORD StencilValue)
{
	// Make sure there is something to clear.
	if (!FrameBuffer && !ZBuffer && !StencilBuffer)
		return;

	// Set rectangle to clear (everything).
	D3DRECT R;
	if (Rect)
	{
		R.x1=Rect->X1;
		R.y1=Rect->Y1;
		R.x2=Rect->X2;
		R.y2=Rect->Y2;
	}
	else
	{
		R.x1=0;
		R.x2=ResX;
		R.y1=0;
		R.y2=ResY;
	}
    
	// Set flags for which buffers to clear.
	DWORD Flags=0;
	if (FrameBuffer)
		Flags|=D3DCLEAR_TARGET;
	if (ZBuffer)
		Flags|=D3DCLEAR_ZBUFFER;
	if (StencilBuffer)
		Flags|=D3DCLEAR_STENCIL;

	// Clear it.
	Viewport->Clear2(1UL, &R, Flags, Color, ZValue, StencilValue);
}

// Sets the blend mode state.
void GraphicsClass::BlendMode(BlendFuncType Src, BlendFuncType Dst)
{
	D3DBLEND SrcTable[]=
	{
		D3DBLEND_ZERO,
		D3DBLEND_ONE,
		D3DBLEND_DESTCOLOR,
		D3DBLEND_INVDESTCOLOR,
		D3DBLEND_SRCALPHA,
		D3DBLEND_INVSRCALPHA,
		D3DBLEND_DESTALPHA,
		D3DBLEND_INVDESTALPHA
	};
	D3DBLEND DstTable[]=
	{
		D3DBLEND_ZERO,
		D3DBLEND_ONE,
		D3DBLEND_SRCCOLOR,
		D3DBLEND_INVSRCCOLOR,
		D3DBLEND_SRCALPHA,
		D3DBLEND_INVSRCALPHA,
		D3DBLEND_DESTALPHA,
		D3DBLEND_INVDESTALPHA
	};

	// Set both source and destination blend modes. 
	// Get D3D values quickly by indexing into the tables.
	// Assumbe value Src and Dst values are passed in.
	D3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,SrcTable[Src]);
	D3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,DstTable[Dst]);
}

// Enables transforms.
void GraphicsClass::EnableTransforms(void)
{
	// Use lit vertex type.
	VertexType=D3DFVF_LVERTEX;
	VertexType2L=D3DFVF_XYZ | D3DFVF_RESERVED1 | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX2;

	// Must change viewport parameters so clipping works correctly.
    D3DVIEWPORT2 ViewportData;
	DCZeroMemory(&ViewportData,sizeof(D3DVIEWPORT2));
	ViewportData.dwSize=sizeof(D3DVIEWPORT2);
	ViewportData.dwWidth=ResX;
	ViewportData.dwHeight=ResY;
	ViewportData.dvMaxZ=1.0f;
	ViewportData.dvClipX=-1.0f;
	ViewportData.dvClipWidth=2.0f;
	ViewportData.dvClipY=1.0f;
	ViewportData.dvClipHeight=2.0f;
	
	Viewport->SetViewport2(&ViewportData);
}

// Disables transforms.
void GraphicsClass::DisableTransforms(void)
{
	// Use transformed and lit vertex type.
	VertexType=D3DFVF_TLVERTEX;
	VertexType2L=D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX2;

	// Must change viewport parameters so clipping works correctly.
    D3DVIEWPORT2 ViewportData;
	DCZeroMemory(&ViewportData,sizeof(D3DVIEWPORT2));
	ViewportData.dwSize=sizeof(D3DVIEWPORT2);
	ViewportData.dwWidth=ResX;
	ViewportData.dwHeight=ResY;
	ViewportData.dvMaxZ=1.0f;
	ViewportData.dvClipWidth=(float)ResX;
	ViewportData.dvClipHeight=(float)ResY;

	Viewport->SetViewport2(&ViewportData);
}

// Returns the maximum visible deflections in the horiziontal
// and vertical directions. This depends both on the specified
// field of view and the screens aspect ratio.
void GraphicsClass::GetViewMaxAngles(float FOVIn,float *HorzOut,float *VertOut)
{
	// Horizontal angles assume 4:3 aspect ratio for the screen.
	*HorzOut=FOVIn*(0.5f*4.0f/3.0f);
	*VertOut=FOVIn*0.5f;
}

// Sets the 2D scale/translate values.
void GraphicsClass::Setup2DScaleTranslate(float Left, float Right, float Top, float Bottom)
{
	// These ones are the same whether running on a TV or not.
	ScaleX2DNoShrink=ResX/(Right-Left);
	TransX2DNoShrink=-ScaleX2D*Left;
	ScaleY2DNoShrink=ResY/(Bottom-Top);
	TransY2DNoShrink=-ScaleY2D*Top;

	// On a TV scale down because TV's bezel covers the screen.
	if (TV)
	{
#define SCALE 0.15f
		ScaleX2D=ResX*(SCALE-1.0f)/(Left-Right);
		TransX2D=ResX*0.5f*SCALE - ScaleX2D*Left;
		ScaleY2D=ResY*(SCALE-1.0f)/(Top-Bottom);
		TransY2D=ResY*0.5f*SCALE - ScaleY2D*Top;
	}
	else
	{
		ScaleX2D=ScaleX2DNoShrink;
		TransX2D=TransX2DNoShrink;
		ScaleY2D=ScaleY2DNoShrink;
		TransY2D=TransY2DNoShrink;
	}
}
