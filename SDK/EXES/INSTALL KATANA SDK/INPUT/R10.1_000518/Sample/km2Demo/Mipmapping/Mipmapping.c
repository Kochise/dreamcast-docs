/*****************************************************************************
  Name :     Mipmapping
  Author:	 Carlos Sarria
  Date :    
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : Little test to show different mipmap methods.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <math.h>

#include "KMTools.h"
#include "KMShell.h"

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Mesh     Mesh[];
extern Struct_Texture  Texture[];

#define NUM_MESHES     2
#define NUM_TEXTURES   5

/* MESHES */
#define M_BACKGROUND  0
#define M_BOX  1

/*************************************************/
/*	Globals                                      */
/*************************************************/

KMSURFACEDESC		Tex[256];				/* texture surface */
KMSTRIPHEAD			StripHead[256];		    /* Vertex context */ 
KMVERTEX_03			*KmVert[256];			/* Vertex pointers*/

/* Camera data */
int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -200.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 0.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

/* Generic data */
unsigned nFrame = 0, dwObject = 0, nTexture = 0;

/* Object angles */
float fAng1 = 0.5f , fAng2 = 0.5f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 250.0f, fHeight = -20.0f;


/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];


/**************************************************/
/* Prototypes                                     */
/**************************************************/
void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	InitBumpmapMesh		(int Object);
void 	CreateWindows 		(void);
void 	ShowStartUpMessage 	(void);
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
	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );

	KMShellSetBuffers(0, 		/* % Opaque (flushed)  */
					  0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					  0,		/* % ModVol Trans  */
					  0			/* % Punchthrough  */
					  );		

	KMPrint3DSetTextures();

	ShowStartUpMessage 	();
	LoadTextures ();
	CreateContexts ();
 
	InitMeshes();
	
	CreateWindows ();
	
	
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
	 
	 for (i=0; i<NUM_MESHES; i++) 
	{
		syFree(KmVert[i]); 
	
	}

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
MATRIX		Matrx;
register i, j;
float CubPosX[4] = { -80.0f,  80.0f, -80.0f, 80.0f};
float CubPosY[4] = { -80.0f, -80.0f,  80.0f, 80.0f};
float PosX, PosY, LettX, LettY;
char  *MimpTx[] = {"No Mipmap","MM 2x2","   MM 4x4","Fourier"};

	KMShellBackground(&StripHead[20]);

	
										
	/* Draw four cubes (same projection) */
	for (i=0; i<4; i++)
	{
		KMMatrixReset  (&Matrx);
		KMMatrixRotate (&Matrx, fAng1, fAng2, 0.0f);  
	
		KMMatrixTranslate (&Matrx, 0.0f, 0.0f, fDist); 

	
		KMTransTransformProjectPerspective (&Matrx, Mesh[M_BOX].nNumVertex, Mesh[M_BOX].pVertex, 
										KmVert[M_BOX], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
		/* Re-locate the cube */
		PosX = CubPosX[i] * 400.0f/(fDist+200.0f);
		PosY = CubPosY[i] * 400.0f/(fDist+200.0f);						
		for (j=0; j<Mesh[M_BOX].nNumVertex; j++)
		{
			(KmVert[M_BOX]+j)->fX += PosX;
			(KmVert[M_BOX]+j)->fY += PosY;
		}
		
		/* Draw info banners */
		LettX = (CubPosX[i]-21) * 400.0f/(fDist+200.0f) * 1.0f/2.2f + 50;
		LettY = CubPosY[i] * 400.0f/(fDist+200.0f) * 1.0f/4.0f + 50;		
		
		KMPrint3D (LettX, LettY, 300.0f/(fDist+200.0f), 0xFFA0A0A0, "%s", MimpTx[i]);	
					
		KMShellStrips (&StripHead[i*4 + nTexture],
						Mesh[M_BOX].nNumStrips, Mesh[M_BOX].pStripLength, 
						Mesh[M_BOX].pStrips, (KMVERTEX_03 *)KmVert[M_BOX]);
	
	}
	
					
	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
	 }
	 
	KMPrint3D (1.0f, 88.0f, 0.7f, 0xFFFFFFFF, "(TRIGGERS) Move In/Out.");
	KMPrint3D (1.0f, 93.0f, 0.7f, 0xFFFFFFFF, "(A-B) Change texture.");
   
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
		if(Delay>2)
		{
			/* Object angles */
			fAng1 = 0.5f; fAng2 = 0.5f; fAng3 = 0.0f;
			/* Camera distance */
			fDist = 250.0f; fHeight = -20.0f;
		}
		Delay = 0;
	}

	/* UP/DOWN X-PAD */
	if (IsUPKey() || IsDOWNKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		Delay = 0;
	}


	/* LEFT X-PAD */
	if (IsLEFTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 3;
		}
		Delay =0;
								
	}

	/* RIGHT X-PAD */
	if (IsRIGHTKey())
	{
		if(Delay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin++;
			if (dwCurrentWin==4) dwCurrentWin = 0;
		}
		Delay =0;
	}

	/* UP ANALOG-PAD */
	if (AnalogPadY()<-64)
	{
		fAng1 += 0.1f;   
	}

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		fAng1 -= 0.1f;     
		
	}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
		fAng2 += 0.1f;   
	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
		fAng2 -= 0.1f;   
	}

	/* A button */
	if (IsAKey())
	{
		if(Delay>2)
		{
		 	nTexture++;
		 	if(nTexture==4) nTexture=0;
		}
		Delay =0;
	}
	
	/* B button */
	if (IsBKey())
	{
		if(Delay>2)
		{
		 	nTexture--;
		 	if(nTexture==-1) nTexture=3;
		}
		Delay =0;
	}
		
	/* X button */
	if (IsXKey())
	{
	}

	/* Y button */
	if (IsYKey())
	{
		
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
		/* Zoom in */
		if (fDist>100) fDist -= 15.0f; 
		
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Zooom out */
		 fDist += 15.0f;
	}

	return TRUE;
}
/**************************************************************************************/
/*                                                                                    */
/*                            Aplication functions                                    */
/*                                                                                    */
/**************************************************************************************/
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitMeshes                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                              
 *  Description     : Sets initials values for meshes managing                            
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
register unsigned i,j;
float fTempVert[3], fModule;


	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		/* Object */
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03)); 
		
	}


	/* Setting UV values and colors for all the meshes */
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
			(KmVert[i]+j)->fU = *(Mesh[i].pUV+j*2+0); 
			(KmVert[i]+j)->fV = *(Mesh[i].pUV+j*2+1); 
				
			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0xFFFFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0x00000000;
		
		} 

   }

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Loads 24 bits textures (stored in a *.htx file as static data) and 
 *                    converts them to CLX 16bits format.
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
	/* No mipmapped */
	KMTextureConvertAndLoad(&Tex[0], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[1], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[2], Texture[3].pBitmapData, Texture[4].pBitmapData, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444);
						
	KMTextureConvertAndLoad(&Tex[3],  Texture[5].pBitmapData, NULL, 
						Texture[5].nWidth, Texture[5].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	
	/* Mipmapped */
	KMTextureSetMipmapMethod (MIPMAP_2x2);
	
	KMTextureConvertAndLoad(&Tex[4], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[5], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[6], Texture[3].pBitmapData, Texture[4].pBitmapData, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
						
	KMTextureConvertAndLoad(&Tex[7], Texture[5].pBitmapData, NULL, 
						Texture[5].nWidth, Texture[5].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureSetMipmapMethod (MIPMAP_4x4);
	
	KMTextureConvertAndLoad(&Tex[8], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[9], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[10], Texture[3].pBitmapData, Texture[4].pBitmapData, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
						
	KMTextureConvertAndLoad(&Tex[11],  Texture[5].pBitmapData, NULL, 
						Texture[5].nWidth, Texture[5].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	
	KMTextureSetMipmapMethod (MIPMAP_FOURIER2);
	
	KMTextureConvertAndLoad(&Tex[12], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[13], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[14], Texture[3].pBitmapData, Texture[4].pBitmapData, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
						
	KMTextureConvertAndLoad(&Tex[15],  Texture[5].pBitmapData, NULL, 
						Texture[5].nWidth, Texture[5].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						

	
	/* Background */
	KMTextureConvertAndLoad(&Tex[20], Texture[0].pBitmapData, NULL, 
						Texture[0].nWidth, Texture[0].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Create all the contexts to be used by the application.                           
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
register i;

	/* BY HAND */
	for (i=0; i<16; i++)
	{
		KMShellInitStripHead (&StripHead[i], &Tex[i], ((i&3)==2)?VC_TRANS | VC_CULLING:VC_OPAQUE);
		kmChangeStripClampUV (&StripHead[i], KM_IMAGE_PARAM1, KM_CLAMP_U);
	}
	
	/* Background */
	KMShellInitStripHead (&StripHead[20], &Tex[20], VC_OPAQUE);

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateWindows                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Create info windows.                          
 *-------------------------------------------------------------------------------------*/
void CreateWindows (void)
{
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MIPMAPPING ", NULL);
	
	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MIPMAPPING (1 of 3) ", "\
2x2\n\n\
This method is the simplest one and the most widely used to perform mipmapping.\n\
Each texel of the current mipmap level is calculated as a 2 by 2 texel sample from the higher mipmap level.");

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MIPMAPPING (2 of 3) ", "\
4x4\n\n\
This method is used when a smoother sampling is needed. \
Basically 16 texels from one level are used in a weighted sum to produce a single texel in the next level.");

	/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MIPMAPPING (3 of 3) ", "\
FOURIER\n\n\
This method is the most accurate, but also slowest way of calculating lower mipmap levels. \
The calculation of every mipmap level is based in the colour frequency spectrum of the previous level and a low-pass filter.");
	

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
		
	KMPrint3D (15.0f, 45.0f, 1.0f, 0xFFFFFFFF, "Calculating Fourier mipmaps...");
		
	kmEndPass(&VertexBufferDesc);
	kmRender(KM_RENDER_FLIP);
	kmEndScene (&SystemConfig);
}

/*--------------------------------------------------------------------------------------*/
/*---------------------------------- END OF FILE ---------------------------------------*/
/*--------------------------------------------------------------------------------------*/





