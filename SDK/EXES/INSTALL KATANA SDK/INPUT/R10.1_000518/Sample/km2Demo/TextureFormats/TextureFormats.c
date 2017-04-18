/*****************************************************************************
  Name :     TextureFormats 
  Author:	 Nicolas Thibieroz (Kamui2 version by Carlos Sarria)
  Date :     Aug 1999 
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : Basic hardware texture formats converted on the fly from 24 bits 
  				bitmaps. All the code for the creation of the different formats is
  				in KMTexture.c

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <math.h>

#include "KMTools.h"
#include "KMShell.h"

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Texture  Texture[];

#define NUM_TEXTURES   8

/*************************************************/
/*	Defines                                      */
/*************************************************/
#define SWAP(x)		if (x) { x=FALSE; } else x=TRUE

#ifndef PI
#define PI	3.14159f
#endif

#define SGLRGB(r, g, b) ((sgl_uint32) (((r) << 16) | ((g) << 8) | (b)))
#define SGLRGBA(r, g, b, a) ((sgl_uint32) (((a) << 24) || ((r) << 16) | ((g) << 8) | (b)))
#define DEBUG(x)	OutputDebugString(x)

/*************************************************/
/*	Globals                                      */
/*************************************************/

/* Background KMVERTEX_03 Vertices */
KMVERTEX_03	SkyTLVertices[4]={
    { 0,  0.0f,	  0.0f, 0.0001f, 0.0f, 1.0f, 0xFFFFFFFF, 0xFF000000 },
	{ 0, 640.0f,  0.0f, 0.0001f, 1.0f, 1.0f, 0xFFFFFFFF, 0xFF000000 },
	{ 0, 640.0f,480.0f, 0.0001f, 1.0f, 0.0f, 0xFFFFFFFF, 0xFF000000 },
	{ 0,   0.0f,480.0f, 0.0001f, 0.0f, 0.0f, 0xFFFFFFFF, 0xFF000000 }	};

/* Untransformed texture vertices */
float PlaneVertices[3*4]={ 
	-100.0f, 100.0f,  0.0f,
	 100.0f, 100.0f,  0.0f,
	 100.0f, -100.0f, 0.0f,
	-100.0f, -100.0f, 0.0f };

/* Transformed texture vertices */
KMVERTEX_03	PlaneTLVertices[4]={
	{ 0, 0.0f, 0.0f, 0.9f, 0.0f, 1.0f, 0xFFFFFFFF, 0xFF000000	},
	{ 0, 0.0f, 0.0f, 0.9f, 1.0f, 1.0f, 0xFFFFFFFF, 0xFF000000	},
	{ 0, 0.0f, 0.0f, 0.9f, 1.0f, 0.0f, 0xFFFFFFFF, 0xFF000000	},
	{ 0, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f, 0xFFFFFFFF, 0xFF000000	}	};

/* Texture triangle list */
WORD		PlaneTriangles[2][3]={ { 0, 1, 2 }, {2, 3, 0}  };

/* Texture variables */
KMSURFACEDESC	nTexture565;
KMSURFACEDESC	nTexture1555;
KMSURFACEDESC	nTexture4444;
KMSURFACEDESC	nTextureYUV422;
KMSURFACEDESC	nTexturePal8;
KMSURFACEDESC	nTextureVQ48;
KMSURFACEDESC	nBackgroundTexture;

KMSTRIPHEAD	nSHTexture565;
KMSTRIPHEAD	nSHTexture1555;
KMSTRIPHEAD	nSHTexture4444;
KMSTRIPHEAD	nSHTextureYUV422;
KMSTRIPHEAD	nSHTexturePal8;
KMSTRIPHEAD	nSHTextureVQ48;
KMSTRIPHEAD	nSHCurrentTexture;
KMSTRIPHEAD	nSHBackgroundTexture;

int				nCurrentTexture=1;

/* Booleans values indicating what's enabled or not */
BOOL				bSkyOn =		TRUE;
BOOL				bMovingCamera =	FALSE;
BOOL				bWobbleOn =		TRUE;
BOOL				bSoundOn =		TRUE;
BOOL				bBilinearOn =	TRUE;
BOOL				bTextOn =		TRUE;
BOOL				bNewChoice =	TRUE;

/* Rendering variables */
DWORD				dwCurrentWidth = 640, dwCurrentHeight = 480;
float				fMipMapOffset=0.0f;
DWORD				dwTextureWindow[6];
int					nFrame=0;

/*************************************************/
/*	Prototypes                                   */
/*************************************************/

void LoadTextures (void);
void ShowStartUpMessage (void);
void MoveSky (void);

/************************************************************************/
/* KMShell functions:                                                   */
/*    KMInitApplication                                                 */
/*    KMQuitApplication                                                 */
/*    KMRenderScene                                                     */
/*    KMPadControl                                                      * 
/*                                                                      */
/* WARNING : These functions must be created always because are called  */
/*           by KMShell.											    */
/************************************************************************/
/*----------------------------------------------------------------------*
 *  Function Name   :  InitApplication                              
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                            
 *  Globals Used    :                                                
 *  Description     :   InitApplication() is called by KMShell to enable
 *						user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{
	KMShellSetVideo	(TRUE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x60   /* Logo background translucency */
					 );

	KMShellSetBuffers(0, 		/* % Opaque (flushed)  */
					  0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					  0,		/* % ModVol Trans  */
					  0			/* % Punchthrough  */
					  );
	

	KMPrint3DSetTextures();
	
	ShowStartUpMessage ();
	LoadTextures();

	dwTextureWindow[5]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : 565", 
		"The 565 format has a larger range of greens available than \
the red or blue channels. This means it is useful when using textures that need extra colour resolution.");

	dwTextureWindow[1]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : 1555", 
		"Only one bit of alpha is used to determine what is visible or not. The \
texture can be forced opaque in order to use a generic 16 bits 555 RGB format. This format \
is useful for genarating a smooth greyscale sequence without having alternate bands having \
slight amounts of too much green in them."); 

	dwTextureWindow[0]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : 4444", 
		"This is the generic 16 bits translucent format. It can be used to generate smooth \
translucent edges in a texture."); 

	dwTextureWindow[3]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : YUV422", 
		"The YUV format offers a very high image quality for real-world images like photographs, captured images, video, etc...");
		
	dwTextureWindow[2]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : Palettize8", 
		"The Palettize8 format stores 8-bit indices to a color table. The texture quality depends \
on the source image, but the final size of this format is about half of the standard 16-bits texture size.");
		
	dwTextureWindow[4]=KMPrint3DCreateDefaultWindow(3.0f, 78.0f, 80, "TEXTURE FORMAT : VQ", 
		"Vector Quantisation (VQ) is a method of compression that finds similar sections or blocks \
of an image, creates a table of the blocks and then encodes the image using indices into that code \
book table. It performs well on high frequency images like text and also on texture surface images.");

}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                         
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication is called by KMShell to enable the
 *						user to finish the application                                             
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	 KMPrint3DReleaseTextures ();
	 
	 kmFreeTexture(&nTexture565);
	 kmFreeTexture(&nTexture1555);
	 kmFreeTexture(&nTexture4444);
	 kmFreeTexture(&nTextureYUV422);
	 kmFreeTexture(&nTexturePal8);
	 kmFreeTexture(&nTextureVQ48);
	 kmFreeTexture(&nBackgroundTexture);
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderScene                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                               
 *  Globals Used    :  nFrame, CameraTo, CameraFrom, nPT                                                
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
	DWORD				dwRenderID;
	MATRIX				WorldMatrix;
	km_vector			CamFrom={ 0.0f, 0.0f, 0.0f };
	int					i;
	static km_vector	CamTo={ 0.0f, 0.0f, 1000.0f };
	static float		r;
	static int			nDelta=0;
	
	
	/* Draw sky */
	if (bSkyOn)
	{
		MoveSky ();
		KMShellTriangles(&nSHBackgroundTexture, 2, (unsigned short *)PlaneTriangles, SkyTLVertices);
	}


	/* Display all textures */
	for (i=0; i<6; i++)
	{
		
		KMMatrixReset(&WorldMatrix);
		if (i==nCurrentTexture && bWobbleOn) 
			KMMatrixRotate(&WorldMatrix, 0.2f*(float)sin(sin(r)), 0.2f*(float)sin(cos(r)), 0.0f);
			
		KMMatrixTranslate(&WorldMatrix, (i%3)*300.0f-300.0f, (i/3)*270.0f-70.0f, 1000.0f);
		
		/* Highlight current texture */
		if (i==nCurrentTexture)
		{
			static int		nPreviousTexture=-1;
			static float	fDestX, fDestY, fGapX, fGapY;
			int				nSteps=30;

			/* A new texture has been selected */
			if (nCurrentTexture!=nPreviousTexture) 
			{
				r=0.0f;
				nPreviousTexture=nCurrentTexture;
				
				/* Code for moving camera */
				nDelta=0;
				fDestX=(nCurrentTexture%3)*300.0f-300.0f;
				fDestY=(nCurrentTexture/3)*270.0f-70.0f;
				fGapX=fDestX-CamTo[0];
				fGapY=fDestY-CamTo[1];
			}
			
			/* Move camera destination so it can reach its final position */
			if (bMovingCamera)
			{
				CamFrom[2] =  500;
						
				if (nDelta<nSteps)
				{
					CamTo[0]+=fGapX/nSteps;
					CamTo[1]+=fGapY/nSteps;
					nDelta++;
				}
			}
			else
			{
				CamTo[0]=0.0f;
				CamTo[1]=0.0f;
				fGapX=fDestX;
				fGapY=fDestY;
				nDelta=0;
			}

			/* Make the texture "wobble" if requested */
			if (bWobbleOn)
			{
				KMMatrixTranslate(&WorldMatrix, 0.0f, 0.0f, -100.0f*(float)sin(r));
				r+=0.25f;
			}
			else
			{
				KMMatrixTranslate(&WorldMatrix, 0.0f, 0.0f, -100.0f);
			}
		}
		
		/* Transform texture */
		KMTransTransformProjectPerspective(&WorldMatrix,
											 4, PlaneVertices, PlaneTLVertices,
											 dwCurrentWidth, dwCurrentHeight,
											 CamFrom, CamTo, 0.0f,
											 1.0f, 10000.0f, 50.0f*PI/180.0f);

		switch(i)
		{
		case 0 :	nSHCurrentTexture =		nSHTexture4444;//nSHTexture565;
					break;

		case 1 :	nSHCurrentTexture =		nSHTexture1555;
					break;

		case 2 :	nSHCurrentTexture =		nSHTexturePal8;//nSHTexture4444;
					break;

		case 3 :	nSHCurrentTexture =		nSHTextureYUV422;
					break;

		case 4 :	nSHCurrentTexture =		nSHTextureVQ48;//nSHTexturePal8;
					break;

		case 5 :	nSHCurrentTexture =		nSHTexture565;//nSHTextureVQ48;
					break;
		}

		/* Draw texture plane */
		KMShellTriangles(&nSHCurrentTexture, 2, (unsigned short *)PlaneTriangles, PlaneTLVertices);
	}

	/* Display 3D text if required */
	if (bTextOn)
	{
		/* Display current texture information window */
		KMPrint3DDisplayWindow(dwTextureWindow[nCurrentTexture]);
	}
	
	nFrame++;
	
	/* RenderScene OK */
	return TRUE;
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : PadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : TRUE to continue, FALSE to finish the application.                                                               
 *  Globals Used    :                                   
 *  Description     : This function is called by KMShell to control the Pad.                           
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	Delay = 0;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
		if (Delay>10)
		{
		}
		Delay = 0;
	}

	/* UP/DOWN X-PAD */
	if (IsUPKey() || AnalogPadY()<-64)
	{
		if(Delay>2)
		{
			if (nCurrentTexture<3) nCurrentTexture+=3;
		}
		Delay = 0;
	}
	/* UP/DOWN X-PAD */
	if (IsDOWNKey() || AnalogPadY()>64)
	{
		if(Delay>2)
		{
		  if (nCurrentTexture>2) nCurrentTexture-=3;
		}
		Delay = 0;
	}



	/* LEFT X-PAD */
	if (IsLEFTKey()  || AnalogPadX()<-64)
	{
		if(Delay>2)
		{
			nCurrentTexture--;
			if (nCurrentTexture==-1) nCurrentTexture = 3;
		}
		Delay =0;
								
	}

	/* RIGHT X-PAD */
	if (IsRIGHTKey() ||AnalogPadX()>64)
	{
		if(Delay>2)
		{
			nCurrentTexture++;
			if (nCurrentTexture==6) nCurrentTexture = 0;
		}
		Delay =0;
	}

	/* UP ANALOG-PAD */
	if (AnalogPadY()<-64)
	{

	}

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
	}

	/* A button */
	if (IsAKey())
	{
		/* DYNAMIC_CAMERA */
		if (Delay>5)
		{
			bNewChoice=TRUE;
			SWAP(bMovingCamera);
			
			bWobbleOn = (bMovingCamera)?FALSE:TRUE;
		}
		Delay = 0;			
	}
	
	/* B button */
	if (IsBKey())
	{
						
	}
		
	/* X button */
	if (IsXKey())
	{
		/* SCENE_BACKGROUND */
		if (Delay>5)
		{
			bNewChoice=TRUE;
			SWAP(bSkyOn); 
		}
		Delay = 0;								
							
	}

	/* Y button */
	if (IsYKey())
	{
		/* TEXTURE_WOBBLE */
		if (Delay>5)
		{
			bNewChoice=TRUE;
			SWAP(bWobbleOn); 
		}
		Delay = 0;
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
	}

	return TRUE;
}
/**************************************************************************************/
/*                                                                                    */
/*                            Aplication functions                                    */
/*                                                                                    */
/**************************************************************************************/
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Load all textures and create all the contexts to be used by the 
 *                    application.                           
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
	/* Sky/Background (Texture n0) */
	KMTextureConvertAndLoad(&nBackgroundTexture, Texture[0].pBitmapData, NULL,
							 Texture[0].nWidth, Texture[0].nHeight,
							 KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
							 
	KMShellInitStripHead (&nSHBackgroundTexture, &nBackgroundTexture, VC_OPAQUE | VC_UVFLIP);
	
	/* YUV422 (Texture n1) */
	KMTextureConvertAndLoad(&nTextureYUV422, Texture[1].pBitmapData, NULL, 
							 Texture[1].nWidth, Texture[1].nHeight,
							 KM_TEXTURE_TWIDDLED  | KM_TEXTURE_YUV422);
							 
	KMShellInitStripHead (&nSHTextureYUV422, &nTextureYUV422, VC_OPAQUE);
	
	/* Texture4444 (Texture n2-3) */
	KMTextureConvertAndLoad(&nTexture4444, Texture[2].pBitmapData, Texture[3].pBitmapData,
							 Texture[2].nWidth, Texture[2].nHeight,
							 KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444);
							 
	KMShellInitStripHead (&nSHTexture4444, &nTexture4444, VC_TRANS);
	
	/* Texture565 (Texture n4) */
	KMTextureConvertAndLoad(&nTexture565, Texture[4].pBitmapData, NULL,
							 Texture[4].nWidth, Texture[4].nHeight,
							 KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
							 
	KMShellInitStripHead (&nSHTexture565, &nTexture565, VC_OPAQUE);
	
	/* Texture1555 (Texture n5-6) */
	KMTextureConvertAndLoad(&nTexture1555, Texture[5].pBitmapData, Texture[6].pBitmapData,
							 Texture[5].nWidth, Texture[5].nHeight,
							 KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB1555);
							 
	KMShellInitStripHead (&nSHTexture1555, &nTexture1555, VC_TRANS);

	/* VQTexture (Texture n7) */
	KMTextureConvertAndLoad(&nTextureVQ48, Texture[7].pBitmapData, NULL,
							 Texture[7].nWidth, Texture[7].nHeight,
							 KM_TEXTURE_VQ | KM_TEXTURE_RGB565);
							 
	KMShellInitStripHead (&nSHTextureVQ48, &nTextureVQ48, VC_OPAQUE);
	
	/* TexturePal8 (Texture n2-3) */
	KMTextureConvertAndLoad(&nTexturePal8, Texture[2].pBitmapData, NULL,
							 Texture[2].nWidth, Texture[2].nHeight,
							 KM_TEXTURE_VQ | KM_TEXTURE_RGB565);
							 
	KMShellInitStripHead (&nSHTexturePal8, &nTexturePal8, VC_TRANS);

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : ShowStartUpMessage                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Display the 'waiting...' message.                           
 *-------------------------------------------------------------------------------------*/
void ShowStartUpMessage (void)
{
extern KMSYSTEMCONFIGSTRUCT	SystemConfig; /* defined in KMShell.c */
extern KMVERTEXBUFFDESC 	VertexBufferDesc; /* defined in KMShell.c */

	kmBeginScene(&SystemConfig);
	kmBeginPass(&VertexBufferDesc);
		
	KMPrint3D (15.0f, 45.0f, 1.5f, 0xFFFFFFFF, "Creating VQ format...");
		
	kmEndPass(&VertexBufferDesc);
	kmRender(KM_RENDER_FLIP);
	kmEndScene (&SystemConfig);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : MoveSky                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Display the 'waiting...' message.                           
 *-------------------------------------------------------------------------------------*/
void MoveSky (void)
{
static float fSkyRoll;

	fSkyRoll += 0.001f;
	if(fSkyRoll>=10.0f) fSkyRoll=0.0f;
	
	SkyTLVertices[0].fU = 0.0f + fSkyRoll;
	SkyTLVertices[1].fU = 1.0f + fSkyRoll;
	SkyTLVertices[2].fU = 1.0f + fSkyRoll;
	SkyTLVertices[3].fU = 0.0f + fSkyRoll;
}
/*--------------------------------------------------------------------------------------*/
/*---------------------------------- END OF FILE ---------------------------------------*/
/*--------------------------------------------------------------------------------------*/