/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRTex.cpp

Abstract:

	Texture management funcions. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

// Adds a texture to out list of textures and returns a handle.
HANDLE GraphicsClass::AddTexture(TEXTURE_LOAD_FUNCTION LoadFunc, HANDLE LoadFuncTextureID, BOOL IDIsText, BOOL UseMaxColor)
{
	TextureClass *Texture;

	// See if we already have this texture.
	for (int i=0;i<FirstFreeTextureIndex;i++)
	{
		Texture=&Textures[i];
	
		if (Texture->LoadFunc==LoadFunc && 
			Texture->IDIsText==IDIsText && 
			Texture->UseMaxColor==UseMaxColor)
		{
			if (Texture->LoadFuncTextureID==LoadFuncTextureID)
				return Texture;
			if (IDIsText)
				if (lstrcmpi((TCHAR *)Texture->LoadFuncTextureID,(TCHAR *)LoadFuncTextureID)==0)
					return Texture;
		}

	}

	// Get an unused texture class.
	DC_ASSERT(FirstFreeTextureIndex<=GR_MAX_TEXTURES);
	Texture=&Textures[FirstFreeTextureIndex];
	FirstFreeTextureIndex++;

	// Initialize texture class.
	DCZeroMemory(Texture,sizeof(TextureClass));
	Texture->SurfInterface=NULL;
	Texture->TexInterface=NULL;
	Texture->LoadFunc=LoadFunc;
	Texture->LoadFuncTextureID=LoadFuncTextureID;
	Texture->IDIsText=IDIsText;
	Texture->UseMaxColor=UseMaxColor;
	Texture->MaxColor=0xFFFFFFFF;

	// Return handle.
	return Texture;
}
	
// Calculates the number of mip levels of a texture based on its dimensions.
static int CalcMipmapCount(int X,int Y)
{
	int Dim=__max(X,Y);
	int Mipmaps;
	
	for (Mipmaps=0;Dim;(Dim=Dim>>1),Mipmaps++);
	
	return Mipmaps;
}

// Converts 32 bit texture data to the appropriate 16 bit format.
static void	Convert32to16(void *TextureData,int Count, BOOL Alpha)
{
	DWORD *Src=(DWORD *)TextureData;
	WORD *Dst=(WORD *)TextureData;

	if (Alpha)
	{
		// 4444.
		for (;Count;Count--,Src++,Dst++)
		{
			DWORD Val=*Src;
			*Dst=(WORD)( ((Val&0xF0000000)>>16) |
						 ((Val&0x00F00000)>>12) |
						 ((Val&0x0000F000)>>8 ) |
						 ((Val&0x000000F0)>>4 ) );
		}
	}
	else
	{
		// 565.
		for (;Count;Count--,Src++,Dst++)
		{
			DWORD Val=*Src;
			*Dst=(WORD)( ((Val&0x00F80000)>>8 ) |
						 ((Val&0x0000FC00)>>5 ) |
						 ((Val&0x000000F8)>>3 ) );
		}
	}
}

static inline DWORD Average8888ColorValues(DWORD C1, DWORD C2)
{
	return (( ((C1 & 0xFF000000)>>1) + ((C2 & 0xFF000000)>>1) + 0x00800000) & 0xFF000000) |
		   (( ((C1 & 0x00FF0000)>>1) + ((C2 & 0x00FF0000)>>1) + 0x00008000) & 0x00FF0000) |
		   (( ((C1 & 0x0000FF00)>>1) + ((C2 & 0x0000FF00)>>1) + 0x00000080) & 0x0000FF00) |
		   ( ((C1 & 0x000000FF) + (C2 & 0x000000FF) + 0x00000001) >>1);
}

static inline WORD Average4444ColorValues(DWORD C1, DWORD C2, DWORD C3, DWORD C4)
{
	return (WORD)(( (((C1 & 0x0000F000) + (C2 & 0x0000F000) + (C3 & 0x0000F000) + (C4 & 0x0000F000))>>2) & 0x0000F000 ) |
				  ( (((C1 & 0x00000F00) + (C2 & 0x00000F00) + (C3 & 0x00000F00) + (C4 & 0x00000F00))>>2) & 0x00000F00 ) |
				  ( (((C1 & 0x000000F0) + (C2 & 0x000000F0) + (C3 & 0x000000F0) + (C4 & 0x000000F0))>>2) & 0x000000F0 ) |
				  ( (((C1 & 0x0000000F) + (C2 & 0x0000000F) + (C3 & 0x0000000F) + (C4 & 0x0000000F))>>2) & 0x0000000F ) );
}

static inline WORD Average565ColorValues(DWORD C1, DWORD C2, DWORD C3, DWORD C4)
{
	return (WORD)(( (((C1 & 0x0000F800) + (C2 & 0x0000F800) + (C3 & 0x0000F800) + (C4 & 0x0000F800))>>2) & 0x0000F800) |
				  ( (((C1 & 0x000007E0) + (C2 & 0x000007E0) + (C3 & 0x000007E0) + (C4 & 0x000007E0))>>2) & 0x000007E0) |
				  ( (((C1 & 0x0000001F) + (C2 & 0x0000001F) + (C3 & 0x0000001F) + (C4 & 0x0000001F))>>2) & 0x0000001F) );
}

// Shrinks the input mip level by a factor of 2.
static inline void GenerateSmallerMipLevel(WORD *Data,int *X, int *Y, BOOL Alpha)
{
	int SX=*X;
	int SY=*Y;
	int DX=__max(1,*X >> 1);
	int DY=__max(1,*Y >> 1);
	WORD *Src,*Dst;

	if (DX!=SX && DY!=SY)
	{
		// Shrink in both directions. This is the code that used used 
		// most of the time so we care a bit about speed.
		Src=Data;
		Dst=Data;
		if (Alpha)
		{
			for (int Y=0;Y<DY;Y++)
			{
				for (int X=0;X<DX;X++)
				{
					*Dst=Average4444ColorValues(Src[0],Src[1],Src[SX],Src[SX+1]);
					Dst++,Src+=2;
				}
				Src+=SX;
			}
		}
		else
		{
			for (int Y=0;Y<DY;Y++)
			{
				for (int X=0;X<DX;X++)
				{
					*Dst=Average565ColorValues(Src[0],Src[1],Src[SX],Src[SX+1]);
					Dst++,Src+=2;
				}
				Src+=SX;
			}
		}
	}
	else if (DY!=SY)
	{
		// Shrink in Y direction. This only gets used for 1*m mip levels.
		Src=Data;
		Dst=Data;
		for (int Y=0;Y<DY;Y++)
		{
			for (int X=0;X<DX;X++)
			{
				if (Alpha)
					*Dst=Average4444ColorValues(Src[0],Src[0],Src[SX],Src[SX]);
				else
					*Dst=Average565ColorValues(Src[0],Src[0],Src[SX],Src[SX]);
				Dst++,Src++;
			}
			Src+=SX;
		}
	}
	else if (DX!=SX)
	{
		// Shrink in X direction. This only gets used for n*1 mip levels.
		Src=Data;
		Dst=Data;
		for (int Y=0;Y<DY;Y++)
		{
			for (int X=0;X<DX;X++)
			{
				if (Alpha)
					*Dst=Average4444ColorValues(Src[0],Src[0],Src[1],Src[1]);
				else
					*Dst=Average565ColorValues(Src[0],Src[0],Src[1],Src[1]);
				Dst++,Src+=2;
			}
		}
	}

	// Return new dimensions.
	*X=DX;
	*Y=DY;
}

// Copies the texture data to the texture surface.
// Note that this destroys the source data.
void GraphicsClass::SetTextureData(LPDIRECTDRAWSURFACE4 SurfInterface,DWORD *TextureData,
								   int X, int Y, DWORD Flags)
{
	// Set up SURFACEDESC for locking surface.
	DDSURFACEDESC2 Desc;
	DCZeroMemory(&Desc,sizeof(DDSURFACEDESC2));
	Desc.dwSize=sizeof(DDSURFACEDESC2);

	// Convert texture data from 32 bit to 16 bit.
	Convert32to16(TextureData,X*Y,(Flags & TFLAG_ALPHA)!=0);

	// Figure out how many mipmap levels to do.
	int Count=(Flags & TFLAG_MIPMAPPED) ? CalcMipmapCount(X,Y) : 1;

	for (;Count;Count--)
	{
		// Create a temporary system memory surface.
		// Set up texture surface description.
		DDSURFACEDESC2 ddsd;
		DCZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
		ddsd.dwSize          = sizeof(DDSURFACEDESC2);
#ifdef DREAMCAST
		ddsd.dwFlags         = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps  = DDSCAPS_SYSTEMMEMORY|DDSCAPS_TEXTURE;
		ddsd.dwWidth         = 1;
		ddsd.dwHeight        = 1;
#else
		ddsd.dwFlags         = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_LPSURFACE|DDSD_PITCH;
		ddsd.ddsCaps.dwCaps  = DDSCAPS_SYSTEMMEMORY|DDSCAPS_TEXTURE;
		ddsd.dwWidth         = X;
		ddsd.dwHeight        = Y;
#endif
		ddsd.lpSurface		 = TextureData;
		ddsd.lPitch			 = (X>1) ? X*sizeof(WORD) : 4;
		memcpy(&ddsd.ddpfPixelFormat,
			   (Flags & TFLAG_ALPHA) ? &ARGBPixelFormat : &RGBPixelFormat,
			   sizeof(DDPIXELFORMAT));

		// Create the surface.
		LPDIRECTDRAWSURFACE4 TmpSurfInterface;
		HRESULT hr;
		if(FAILED(hr=DDInterface->CreateSurface(&ddsd,&TmpSurfInterface, NULL)))
			return;

#ifdef DREAMCAST
		// Allocation of Client memory surfaces don't work on Dragon so
		// we have to call SetSurfaceDesc.
		ddsd.ddsCaps.dwCaps  = 0;
		ddsd.dwFlags         &= ~(DDSD_CAPS|DDSD_PIXELFORMAT);
		ddsd.dwFlags         |= DDSD_LPSURFACE|DDSD_PITCH;
		ddsd.dwWidth         = X;
		ddsd.dwHeight        = Y;
		TmpSurfInterface->SetSurfaceDesc(&ddsd,0);
#endif

		// Blit temp surface to texture surface.
		SurfInterface->Blt(NULL,TmpSurfInterface,NULL,DDBLT_WAIT,NULL);

		// Release the temp surface.
		TmpSurfInterface->Release();

		if ((Flags & TFLAG_MIPMAPPED) && Count>=1)
		{
			// Get next surface.
			DDSCAPS2 Caps;
			Caps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
			if( FAILED( SurfInterface->GetAttachedSurface( &Caps, &SurfInterface ) ) )
				return;

			// Release to stop increasing the ref count.
			SurfInterface->Release();

			// Generate smaller mip level.
			GenerateSmallerMipLevel((WORD *)TextureData,&X,&Y,(Flags & TFLAG_ALPHA)!=0);
		}
	}
}

// Maximizes colors in texture.
static DWORD DoMaxColor(int X, int Y, DWORD *D)
{
	// Calculate the maximum color value for the texture.
	DWORD MaxA=0,MaxR=0,MaxG=0,MaxB=0;
	int i,Count;
	for (i=0,Count=(X * Y);i<Count;i++)
	{
		DWORD Color=D[i];
		DWORD TmpA,TmpR,TmpG,TmpB;
		
		TmpA=Color & 0xFF000000;
		if (TmpA>MaxA)
			MaxA=TmpA;
		TmpR=Color & 0x00FF0000;
		if (TmpR>MaxR)
			MaxR=TmpR;
		TmpG=Color & 0x0000FF00;
		if (TmpG>MaxG)
			MaxG=TmpG;
		TmpB=Color & 0x000000FF;
		if (TmpB>MaxB)
			MaxB=TmpB;
	}
	// Calculate maximum color value.
	DWORD RetVal=MaxA | MaxR | MaxG | MaxB;

	// Scale up color values in texture.
	MaxA=__max(MaxA,0x01000000);
	MaxR=__max(MaxR,0x00010000);
	MaxG=__max(MaxG,0x00000100);
	MaxB=__max(MaxB,0x00000001);
	DWORD ScaleA=256*256*255/(MaxA>>24);
	DWORD ScaleR=256*256*255/(MaxR>>16);
	DWORD ScaleG=256*256*255/(MaxG>>8);
	DWORD ScaleB=256*256*255/MaxB;
	for (i=0,Count=(X * Y);i<Count;i++)
	{
		DWORD Color=D[i];
		DWORD TmpA=(Color & 0xFF000000) >> 24;
		DWORD TmpR=(Color & 0x00FF0000) >> 16;
		DWORD TmpG=(Color & 0x0000FF00) >> 8;
		DWORD TmpB=(Color & 0x000000FF);
		TmpA=((TmpA*ScaleA)&0x00FF0000)<<8;
		TmpR=(TmpR*ScaleR)&0x00FF0000;
		TmpG=((TmpG*ScaleG)&0x00FF0000)>>8;
		TmpB=((TmpB*ScaleB)&0x00FF0000)>>16;
		D[i]=TmpA | TmpR | TmpG | TmpB;
	}

	// Return maximum color.
	return RetVal;
}

// Shrinks map in X dimension by factor of 2.
void ShrinkMapX(DWORD *Data, int *X, int Y)
{

	int SX=*X;
	int SY=Y;
	int DX=*X>>1;
	int DY=Y;
	DWORD *Src,*Dst;

	{
		Src=Data;
		Dst=Data;
		for (int Y=0;Y<DY;Y++)
		{
			for (int X=0;X<DX;X++)
			{
				*Dst=Average8888ColorValues(Src[0],Src[1]);
				Dst++,Src+=2;
			}
		}
	}
	*X=DX;
}

// Shrinks map in Y dimension by factor of 2.
void ShrinkMapY(DWORD *Data, int X, int *Y)
{
	int SX=X;
	int SY=*Y;
	int DX=X;
	int DY=*Y>>1;
	DWORD *Src,*Dst;

	{
		Src=Data;
		Dst=Data;
		for (int Y=0;Y<DY;Y++)
		{
			for (int X=0;X<DX;X++)
			{
				*Dst=Average8888ColorValues(Src[0],Src[SX]);
				Dst++,Src++;
			}
			Src+=SX;
		}
	}
	*Y=DY;
}

// Loads all textures in our texture list. Creates or restores surfaces as necessary.
// Textures which don't need loading are skipped.
BOOL GraphicsClass::LoadTextures(void)
{
	int i;
	TextureClass *Texture;
	DWORD *TextureData;
	int X,Y;
	DWORD Flags;

	// Walk through our texture list, allocating textures and loading as necessary.
	for (i=0;i<FirstFreeTextureIndex;i++)
	{
		// Get the texture class.
		Texture=&Textures[i];

		// If the texture has already been created, move on.
		if (Texture->SurfInterface)
			continue;
		
		// Load the texture data.
		if (!Texture->LoadFunc(Texture->LoadFuncTextureID,&X,&Y,&Flags,&TextureData))
		{
			DC_WARNING(("Could not load data for texture.\n"));
			continue;
		}

		// Maximize color values if enabled.
		if (Texture->UseMaxColor)
			Texture->MaxColor=DoMaxColor(X,Y,TextureData);
		else
			Texture->MaxColor=0xFFFFFFFF;

		// Clamp texture dimensions.
		while (X > MaxTextureWidth)
			ShrinkMapX(TextureData,&X,Y);
		while (Y > MaxTextureHeight)
			ShrinkMapY(TextureData,X,&Y);

		// Set up texture surface description.
		DDSURFACEDESC2 ddsd;
		DCZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
		ddsd.dwSize          = sizeof(DDSURFACEDESC2);
		ddsd.dwFlags         = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
#ifdef DREAMCAST
		ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY | DDSCAPS_OPTIMIZED;
#else
		ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE | DDSCAPS_VIDEOMEMORY;
#endif
		ddsd.ddsCaps.dwCaps2 = 0;
		ddsd.dwWidth         = X;
		ddsd.dwHeight        = Y;
		if (UseTextureCaching)
		{
			ddsd.ddsCaps.dwCaps&=~DDSCAPS_VIDEOMEMORY;
			ddsd.ddsCaps.dwCaps2|=DDSCAPS2_TEXTUREMANAGE;
		}
		if (Flags & TFLAG_MIPMAPPED)
		{
			ddsd.dwFlags|=DDSD_MIPMAPCOUNT;
			ddsd.ddsCaps.dwCaps|=DDSCAPS_COMPLEX|DDSCAPS_MIPMAP;
			ddsd.dwMipMapCount = CalcMipmapCount(X,Y);
		}
		memcpy(&ddsd.ddpfPixelFormat,
			   (Flags & TFLAG_ALPHA) ? &ARGBPixelFormat : &RGBPixelFormat,
			   sizeof(DDPIXELFORMAT));

		// Create texture surface.
		HRESULT hr;

		if(FAILED(hr=DDInterface->CreateSurface(&ddsd,&Texture->SurfInterface, NULL)))
		{
			// If texture could not be allocate because out of memory AND
			// we aren't already in caching mode, free all textures
			// and reload with caching.
#ifndef DREAMCAST // Don't want to use texture caching on Dreamcast.
			if (hr==DDERR_OUTOFVIDEOMEMORY && !UseTextureCaching)
			{
				DCFree(TextureData);
				ReleaseTextures();
				UseTextureCaching=TRUE;
				return LoadTextures();
			}
			else
#endif
			{
				DCFree(TextureData);
				DC_WARNING(("Could not create a texture surface.\n"));
				continue;
			}
		}

		// Get texture interface.
		if(FAILED(Texture->SurfInterface->QueryInterface(IID_IDirect3DTexture2,
														 (VOID**)&Texture->TexInterface)))
		{
			DCFree(TextureData);
			DC_WARNING(("Could not query texture interface.\n"));
			SetErrorMessage(IDS_ERROR_TEXTURECREATE);
			return FALSE;
		}

		// Pack texture type data into a DWORD.
		Texture->TextureType=(X & 0x00003FFF) | ((Y << 14) & 0x0FFFC000);
		if (Flags & TFLAG_MIPMAPPED)	Texture->TextureType|=0x40000000;
		if (Flags & TFLAG_ALPHA)		Texture->TextureType|=0x80000000;

		// Copy texture data to surface.
		SetTextureData(Texture->SurfInterface,TextureData,X,Y,Flags);

		// Free the texture data.
		DCFree(TextureData);
	}
	
	return TRUE;
}

// Releases the surfaces for all our textures.
void GraphicsClass::ReleaseTextures(void)
{
	TextureClass *Texture;

#define RELEASE(a) \
	{ \
		if (a) \
		{ \
			(a)->Release(); \
			(a)=NULL; \
		} \
	}
	
	// Walk through our texture list.
	for (int i=0;i<FirstFreeTextureIndex;i++)
	{
		// Get the texture class.
		Texture=&Textures[i];
		
		// Release interfaces.
		RELEASE(Texture->SurfInterface);
		RELEASE(Texture->TexInterface);
	}
}

// Reloads a texture.
void GraphicsClass::ReloadTexture(HANDLE Texture)
{
	TextureClass *Tex=(TextureClass *)Texture;
	DWORD *TextureData;
	int X,Y;
	DWORD Flags;

	// Load the texture data.
	if (!Tex->LoadFunc(Tex->LoadFuncTextureID,&X,&Y,&Flags,&TextureData))
	{
		DC_WARNING(("Could not load data for texture.\n"));
		return;
	}

	// Make sure existing texture characteristics match our new ones.
	int TX=Tex->TextureType & 0x00007FFF;
	int TY=(Tex->TextureType & 0x3FFF8000) >> 15;
	DWORD TF=0;
	if (Tex->TextureType & 0x40000000)
		TF|=TFLAG_MIPMAPPED;
	if (Tex->TextureType & 0x80000000)
		TF|=TFLAG_ALPHA;
	DC_ASSERT(X==TX && Y==TY && Flags==TF);

	// Copy texture data to surface.
	SetTextureData(Tex->SurfInterface,TextureData,X,Y,Flags);

	// Free the texture data.
	DCFree(TextureData);
}

// Restores all textures.
void GraphicsClass::RestoreTextures(void)
{
	TextureClass *Texture;

	// Walk through our texture list, allocating textures and loading as necessary.
	for (int i=0;i<FirstFreeTextureIndex;i++)
	{
		// Get the texture class.
		Texture=&Textures[i];

		// We must have a texture interface.
		if (!Texture->TexInterface)
			continue;

		// If the texture is not lost move on to the next texture.
		if (Texture->SurfInterface->IsLost()!=DDERR_SURFACELOST)
			continue;

		// Restore.
		if (FAILED(Texture->SurfInterface->Restore()))
		{
			DC_WARNING(("Could not restore a texture surface.\n"));
			continue;
		}

		// Reload the texture data.
		ReloadTexture(Texture);
	}
}
