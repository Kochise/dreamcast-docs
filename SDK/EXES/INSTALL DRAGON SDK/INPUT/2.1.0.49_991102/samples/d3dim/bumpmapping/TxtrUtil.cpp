/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    TxtrUtil.cpp

Abstract:

    Contains Direct3D Texture functionality.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "bumpmapping.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadTexture

Description:

    Creates a texture map surface and texture object from the named 
    bitmap file.  This is done in a two step process.  A source 
    DirectDraw surface and bitmap are created in system memory.  A second,
    initially empty, texture surface is created (in video memory if hardware
    is present).  The source bitmap is loaded into the destination texture
    surface and then discarded. This process allows a device to compress or
    reformat a texture map as it enters video memory during the Load call.

Arguments:

    TCHAR *tstrFileName  - Name of the texture to open

Return Value:

    LPDIRECT3DTEXTURE2   - Pointer to the loaded Texture (or NULL if failure)

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2 
LoadTexture(TCHAR *tstrFileName)
{
    DDSURFACEDESC2       ddsd;
    LPDIRECTDRAWSURFACE4 pddsBitmap,     pddsTexture;
    LPDIRECT3DTEXTURE2   pd3dtextureSrc, pd3dtextureDest;

    // Create a surface in system memory and load the bitmap file into it.
    pddsBitmap = LoadBitmapToDDS(tstrFileName);
    if (!pddsBitmap)
    {
        DebugOutput(TEXT("ERROR: Unable to load texture %s\r\n"), tstrFileName);
        return NULL;
    }

    // Create an empty texture surface to load the source texture into.
    // The DDSCAPS_ALLOCONLOAD flag allows the DD driver to wait until the
    // load call to allocate the texture in memory because at this point,
    // we may not know how much memory the texture will take up (e.g. it
    // could be compressed to an unknown size in video memory).
    GetSurfaceDesc(&ddsd, pddsBitmap);

    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD | DDSCAPS_VIDEOMEMORY;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsTexture, NULL);
    if (CheckError(TEXT("Create Destination Texture Surface")))
        return NULL;

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsBitmap->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtextureSrc);
    if (CheckError(TEXT("Query D3D Texture interface")))
        return NULL;

    // Query our destination surface for a texture interface
    g_errLast = pddsTexture->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dtextureDest);
    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = pd3dtextureDest->Load(pd3dtextureSrc);
    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    // Release no-longer-necessary surfaces
    pd3dtextureSrc->Release();
    pddsBitmap->Release();

    return pd3dtextureDest;
}

#define FOURCC_PNBM MAKEFOURCC('P', 'N', 'B', 'M')

void HeightToBump_Wrap
(
	unsigned char *pHeight,
	unsigned short *pBump,
	int rows,
	int cols
)
{
	int u,v,u1,v1;			// U,V coordinates
	unsigned char h,h10,h01;// Heights at (u,v),(u+1,v),(u,v+1)
	float dH01,dH10;		// (h-h01) and (h-h10) scaled
	unsigned char R,S;		

	for(v=0;v<rows;v++)
	{
		v1=(v+1)%rows;	// for clamp this can be: max(v,(v+1)%rows)
		for(u=0;u<cols;u++)
		{
			u1=(u+1)%cols;	// for clamp this can be: max(u,(u+1)%rows)
			// Read the height map
			h=pHeight[v*cols+u];
			h10=pHeight[v*cols+u1];
			h01=pHeight[v1*cols+u];
			// Check for special case first
			if( ( h == h01 ) && ( h == h10 ) )
			{
				// height map is flat here
				*pBump++ = 0xFF00;	// S=90 degrees
			}
			else
			{
				// Derive the delta heights
				dH10 = ((float)h - (float)h10)/16.0f;
				dH01 = ((float)h - (float)h01)/16.0f;
				// R = atan(dH01/dH10)...
				R = (unsigned char)(int)
					(atan2(dH01,dH10)
					*128.0f/3.14159f);	// -pi..0..+pi -> 0x80..0x00..0x7f
				// S = atan( 1 / ( sqrt ( dH01 ^ 2 + dH10 ^ 2 ) ) )
				S = (unsigned char)(int)
					(atan2(1.0f,sqrt(dH01*dH01+dH10*dH10))
					*255.0f*2.0f/3.14159f);		// 0..+pi/2 -> 0..0xff
				*pBump++ = (((unsigned short)S)<<8) | (((unsigned short)R)<<0);
			}
		}
	}
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateBrickBumpMapTexture

Description:

    Creates a Bump Map.  

Arguments:

    None

Return Value:

    LPDIRECT3DTEXTURE2   - Pointer to the generated Bumpmap (or NULL if failure)

-------------------------------------------------------------------*/
LPDIRECT3DTEXTURE2
CreateBumpMapTexture()
{
    DDSURFACEDESC2       ddsd;
    LPDIRECTDRAWSURFACE4 pddsBumpMap,       pddsTexture;
    LPDIRECT3DTEXTURE2  pd3dtextureBitMap, pd3dtextureBumpMap;

	int bmWidth = 128;	// make the bumpmapping map 128x128  ( need not match size of conventional texture )
	int bmHeight = 128;

	RETAILMSG(1,(TEXT("hbitmap = (HBITMAP)LoadImage\r\n")));

    // create a fourcc DirectDrawSurface for this bumpmapping map
    memset(&ddsd, 0, sizeof(ddsd));

    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
    ddsd.ddsCaps.dwCaps2 = 0;
    ddsd.dwWidth        = bmWidth;
    ddsd.dwHeight       = bmHeight;
    ddsd.ddpfPixelFormat.dwSize = sizeof(ddsd.ddpfPixelFormat);
    ddsd.ddpfPixelFormat.dwFlags = DDPF_FOURCC;
    ddsd.ddpfPixelFormat.dwFourCC = FOURCC_PNBM;
    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsBumpMap, NULL);
    if (CheckError(TEXT("Create DDTexture surface")))
        return NULL;

    // Lock the bits to the bumpmap fourcc surface
    pddsBumpMap->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    BYTE *pbyBump = (BYTE*)ddsd.lpSurface;

#if 0
    // Fill the bumpmap with our generated surface information
    int i,j;

    // Put a square in the middle of the bumpmapping map
    for (i = 0; i < bmHeight; i++)
    {
        for (j = 0; j < bmWidth; j++)
        {
            if (i < 20 || i > bmHeight - 20 || j < 20 || j > bmWidth - 20)
            {
                *(pbyBump++) = 0;   // "Around" angle
                *(pbyBump++) = 0x20;   // "Up" angle;
            }
            else
            {
                *(pbyBump++) = 0;   // "Around" angle
                *(pbyBump++) = 0xc0; // "Up" angle
            }
        }
    }
#else
    int i,j,x,y,h;

	// create a height map

	unsigned char *heightMap = (unsigned char *)malloc( bmHeight * bmWidth );
	
	// Fill with flat level 0
    for (i = 0; i < bmHeight; i++)
    {
        for (j = 0; j < bmWidth; j++)
        {
			heightMap[ i * bmWidth + j ] = 0;
		}
	}

	// now, add pyramids and a hemispheres

	for( x=-15; x<=15; x++ )
	{
		for( y=-15; y<=15; y++ )
		{

			if( abs(x) > abs(y) )
				h = ( 15 - abs(x) ) * 16;
			else
				h = ( 15 - abs(y) ) * 16;

			// add pyramids
			i = x + 20;
			j = y + 20;
			heightMap[ i * bmWidth + j ] = h;
			i = bmWidth + x - 20;
			heightMap[ i * bmWidth + j ] = h;
			j = bmHeight + y - 20;
			heightMap[ i * bmWidth + j ] = h;
			i = x + 20;
			heightMap[ i * bmWidth + j ] = h;

			// center pyramid has flat top:
			if( h > 120 )
				h = 120;

			i = (bmWidth>>1) + x;
			j = (bmHeight>>1) + y;
			heightMap[ i * bmWidth + j ] = h;


			// add hemispheres

			if( x*x+y*y < 15*15 )
			{
				h = (int)( 16.f * sqrt( 15.f*15.f-x*x-y*y ) );

				i = (bmWidth>>1) + x;
				j = y + 20;
				heightMap[ i * bmWidth + j ] = h;
				j = bmHeight + y - 20;
				heightMap[ i * bmWidth + j ] = h;
				i = x + 20;
				j = (bmHeight>>1) + y;
				heightMap[ i * bmWidth + j ] = h;
				i = bmWidth + x - 20;
				heightMap[ i * bmWidth + j ] = h;
			}
		}
	}

	// now convert that to bumpmapping-map bits:

	HeightToBump_Wrap( heightMap, (unsigned short *)pbyBump, bmHeight, bmWidth );

	// and discard the height map

	free( (void *)heightMap );


#endif

    pddsBumpMap->Unlock(NULL);


    // ++++++++++ Finally, copy the bumpmap into the destination texture. ++++++++++
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD | DDSCAPS_VIDEOMEMORY;

    g_errLast = g_pdd->CreateSurface(&ddsd, &pddsTexture, NULL);
    if (CheckError(TEXT("Create Destination Texture Surface")))
        return NULL;

    // Query our source surface for a texture interface.  This is necessary for the 'Load()' command.
    g_errLast = pddsBumpMap->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pd3dtextureBitMap);
    if (CheckError(TEXT("Query D3D Texture interface")))
        return NULL;

    // Query our destination surface for a texture interface
    g_errLast = pddsTexture->QueryInterface(IID_IDirect3DTexture2,(LPVOID*)&pd3dtextureBumpMap);
    if (CheckError(TEXT("Query D3D Texture Interface")))
        return NULL;

    // Load the source texture into the destination.  During this call, a
    // driver could compress or reformat the texture surface and put it in video memory.
    g_errLast = pd3dtextureBumpMap->Load(pd3dtextureBitMap);
    if (CheckError(TEXT("Load Source Texture into Destination Texture")))
        return NULL;

    // Release no-longer-necessary surfaces
    pd3dtextureBitMap->Release();
    pddsBumpMap->Release();

    return pd3dtextureBumpMap;
}
