/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     Trilinear
  Date :     July 1998 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
 
  Description : Trilinear demo.

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
extern Struct_Material Material[];
extern Struct_Texture  Texture[];

#define NUM_MESHES     6
#define NUM_MATERIALS  4
#define	NUM_TEXTURES   6

/* MESHES */
#define M_SPHERE  0
#define M_TAPE  1
#define M_BANNER1  2
#define M_BANNER2  3
#define M_BANNER3  4
#define M_BACKGROUND  5


/*************************************************/
/*	Globals                                      */
/*************************************************/

/* texture surface */
KMSURFACEDESC		Tex[256];				
/* Vertex context */
KMSTRIPHEAD		StripHead[256];		

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

extern KMVERTEXBUFFDESC VertexBufferDesc;	/* is defined in KMShell.c */

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 100.0f};
km_vector LightDirection	= { 1.0f, -1.0f, -1.0f};

float   nFrame = 0; 
float	fXPos, fYPos, SphPos[2];

KMDWORD dwMipmapLevel = 4;

KMBOOL    bStart = FALSE;

KMBOOL bIsMipmap = TRUE, bShowBanners = TRUE;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];
/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	RenderObject		(int Object, KMSTRIPHEAD *StripHead);
void 	CreateWindows 		(void);
void	CalculateMovement	(int nType);

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
 *  Returns         :                                              
 *  Globals Used    :                                                
 *  Description     :   InitApplication() is called by KMShell to enable
 *						the user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{

	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0xB0   /* Logo background translucency */
					 );

	KMShellSetBuffers (	0, 		/* % Opaque (flushed) */
						0,		/* % ModVol Opaque */
						100,	/* % Translucent   */
						0,		/* % ModVol Trans  */
						0);	

	KMPrint3DSetTextures();

	LoadTextures ();
	CreateContexts ();
	
	CreateWindows();

	InitMeshes();

}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                          
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *						the user to finish the application                                                  
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{register i;

	KMPrint3DReleaseTextures();
	
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
 *  Globals Used    :                                             
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
int i, j;
MATRIX Matrx;

   KMShellBackground (&StripHead[10]);
     

   for (j=0; j<2; j++)
   {   
	    /* 
	     * Transformations 
	     */
		CalculateMovement (j);

		for (i=0; i<NUM_MESHES;i++) 
		{

			KMMatrixReset(&Matrx);

			if (i == M_SPHERE)
			{
				KMMatrixRotate(&Matrx, -nFrame/90.0f, -nFrame/30.0f, 0.0f);
	 			KMMatrixTranslate (&Matrx, 0.0f, SphPos[1] + 20.0f,  SphPos[0]);
			}
 
			if (i==M_BANNER2 || i==M_BANNER3 || i==M_BANNER1) 
			{
				KMMatrixTranslate (&Matrx, 0.0f, SphPos[1] + 30.0f,  SphPos[0]);
			}

			/* Trilinear */
			if (j==0)	KMMatrixTranslate (&Matrx, -51.0f, 0.0f, 0.0f);

			/* Mipmap/standard */
			else		KMMatrixTranslate (&Matrx,  51.0f, 0.0f, 0.0f);
	
	
			KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
										KmVert[i], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

		}

		/* 
		 * Render 
		 */
		for (i=0; i<2;i++) 
		{
			/* Mipmap/standard */
			if (j==1)
			{
				if(bIsMipmap) RenderObject (i, &StripHead[i]);
				else		  RenderObject (i, &StripHead[i+3]);
			}

			if (j==0)
			{
		        /* Trilinear translucent */
				if (i==M_SPHERE)
				{
					
					RenderObject (i, &StripHead[20]);
					RenderObject (i, &StripHead[21]); 
					RenderObject (i, &StripHead[22]);
				
				}
				/* Trilinear opaque */
				if (i==M_TAPE)
				{
					RenderObject (i, &StripHead[30]);
					RenderObject (i, &StripHead[31]);
				}

			}
		}
		
		if (bShowBanners)
		{
			if (j==0) 
			{
				/* Trilinear banner */
				RenderObject (M_BANNER1, &StripHead[40]);
				RenderObject (M_BANNER1, &StripHead[41]);
				RenderObject (M_BANNER1, &StripHead[42]);
			}

			if (j==1)
			{
				/* Mipmap/Standard banner */
				if (bIsMipmap) RenderObject (M_BANNER3, &StripHead[2]);
				else		   RenderObject (M_BANNER2, &StripHead[5]);
			}
		}

   } /* end of j loop */
   
  /* 
   * Text windows.
   */
	if(dwDisplayWins)
	{
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	}
 
 	if(dwCurrentWin<=2) KMPrint3DWindowOutput	(InfoWin, "TRIGGERS for mipmap bias = %+2.2f\n", (float)dwMipmapLevel*0.25f);

   nFrame++;     

	/* RenderScene OK */
	return TRUE;

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : PadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : TRUE to continue, FALSE to finish the app.                                                               
 *  Globals Used    :                                   
 *  Description     : PadControl() is called by KMShell every frame to enable
 *						the user to control the joystick.                        
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static unsigned nDelay = 0;
 
    nDelay++;
 
	/* START */
	if (IsSTARTKey())
	{
		bStart = TRUE;
	} 
	
	/* UP/DOWN X-PAD */
	if (IsUPKey() || IsDOWNKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = !dwDisplayWins;
		}
		nDelay = 0;
	}

	/* LEFT X-PAD */
	if (IsLEFTKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin--;
			if (dwCurrentWin==-1) dwCurrentWin = 2;
			
		}
		nDelay =0;
								
	}

	/* RIGHT X-PAD */
	if (IsRIGHTKey())
	{
		if(nDelay>2)
		{
			dwDisplayWins = TRUE;
			dwCurrentWin++;
			if (dwCurrentWin==3) dwCurrentWin = 0;
		}
		nDelay =0;
	}

	
	/* UP */
	if (AnalogPadY()<-64)
	{

	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
	
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		
	}


	/* A button */
	if (IsAKey())
	{
		if (nDelay>10)
		{
			bIsMipmap = !bIsMipmap;
			nDelay = 0;
		}
	}
	
	/* B button */
	if (IsBKey())
	{
		if (nDelay>10)
		{
			bShowBanners = !bShowBanners;
			nDelay = 0;
		}
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
		if (nDelay>2)
		{
			if (dwMipmapLevel>1) dwMipmapLevel--;
			CreateContexts ();
		}
		nDelay=0;
		
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		if (nDelay>2)
		{
			if (dwMipmapLevel<15) dwMipmapLevel++;
			CreateContexts ();
		}	
		nDelay=0;
		
	}
	
	return TRUE;
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   : InitMeshes                                                      
 *  Inputs          : None                                                             
 *  Outputs         : None                                                             
 *  Returns         : None                                                            
 *  Globals Used    :                        
 *  Description     : Sets initials values for meshes managment.                         
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
register unsigned i,j, k=0;

	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03));
	}

	/* Setting UV values and colors for all the meshes */
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
            (KmVert[i]+j)->fU	= *(Mesh[i].pUV+j*2+0);
            (KmVert[i]+j)->fV	= *(Mesh[i].pUV+j*2+1);

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0xFFFFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0xFF000000;
		
		}     
	}
 
  
}

/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Converts a 24bits Bitmap format to a 16bits hardware format and load it 
 *                     in video memory.              
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
int i, j;
int nMaterial, nTexture, nTransTexture;


	for (i=0; i<NUM_MATERIALS; i++)
	{
	
		nMaterial = i;
		
		nTexture = nTransTexture = -1;
		
		/* Looking for the texture that fits the difusse and opacity file names of the current material */
		for (j=0; j<NUM_TEXTURES; j++)
		{
			if (strcmp(Material[nMaterial].sDifusseFile, Texture[j].sTextureFileName) == 0) 
			{
				nTexture = j;
			}
			if (strcmp(Material[nMaterial].sOpacityFile, Texture[j].sTextureFileName) == 0) 
			{
				nTransTexture = j;
			}
		}
		
		/* It's translucent */
		if(nTransTexture != -1)
		{
			/* Mipmapped */
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, Texture[nTransTexture].pBitmapData, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
				
			/* No mipmapped */		
			KMTextureConvertAndLoad(&Tex[i+3], Texture[nTexture].pBitmapData, Texture[nTransTexture].pBitmapData, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444);
		}
		
		else /* It's opaque */
		{
			if (i==3) /* No mipmap for the background */
			{
				KMTextureConvertAndLoad(&Tex[10], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
			}
			else
			{
				/* Mipmapped */
				KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
				
				/* No mipmapped */
				KMTextureConvertAndLoad(&Tex[i+3], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
						
			}
		}
	
	}

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Sets vertex contexts                           
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
 
	/* STANDARD MIPMAP */ 
	KMShellInitStripHead (&StripHead[0], &Tex[0], VC_TRANS);
	kmChangeStripMipmapAdjust	(&StripHead[0], KM_IMAGE_PARAM1, dwMipmapLevel);


	KMShellInitStripHead (&StripHead[1], &Tex[1], VC_OPAQUE);
	kmChangeStripMipmapAdjust	(&StripHead[1], KM_IMAGE_PARAM1, dwMipmapLevel);

	KMShellInitStripHead (&StripHead[2], &Tex[2], VC_TRANS);
	kmChangeStripMipmapAdjust	(&StripHead[2], KM_IMAGE_PARAM1, dwMipmapLevel);

	/* STANDARD NO MIPMAP */
	KMShellInitStripHead (&StripHead[3], &Tex[3], VC_TRANS);

	KMShellInitStripHead (&StripHead[4], &Tex[4], VC_OPAQUE);

	KMShellInitStripHead (&StripHead[5], &Tex[5], VC_TRANS);

	KMShellInitStripHead (&StripHead[10], &Tex[10], VC_OPAQUE);


	/* 
	 * TRILINEAR
	 * IMPORTANT NOTE: Use mipmapped textures always.
	 */
	/* TRILINEAR TRANSLUCENT*/
	KMShellInitStripHead (&StripHead[20], &Tex[0], VC_TRANS);
	kmChangeStripFilterMode 	(&StripHead[20], KM_IMAGE_PARAM1, KM_TRILINEAR_A);
	kmChangeStripSRCSelect		(&StripHead[20], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[20], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[20], KM_IMAGE_PARAM1, KM_ONE, KM_ZERO);
	kmChangeStripMipmapAdjust	(&StripHead[20], KM_IMAGE_PARAM1, dwMipmapLevel);


	KMShellInitStripHead (&StripHead[21], &Tex[0], VC_TRANS);
	kmChangeStripFilterMode 	(&StripHead[21], KM_IMAGE_PARAM1, KM_TRILINEAR_B);
	kmChangeStripSRCSelect		(&StripHead[21], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[21], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[21], KM_IMAGE_PARAM1, KM_ONE, KM_ONE);
	kmChangeStripMipmapAdjust	(&StripHead[21], KM_IMAGE_PARAM1, dwMipmapLevel);


	KMShellInitStripHead (&StripHead[22], NULL, VC_TRANS);
	kmChangeStripSRCSelect		(&StripHead[22], KM_IMAGE_PARAM1, 1);
	kmChangeStripDSTSelect		(&StripHead[22], KM_IMAGE_PARAM1, 0);
	kmChangeStripMipmapAdjust	(&StripHead[22], KM_IMAGE_PARAM1, dwMipmapLevel);
	
	/* TRILINEAR OPAQUE */
	/* 
	 * IMPORTANT NOTE: For Translucency PreSort TrilinearA must be Translucent ONE-ZERO)
	 * to avoid sorting artefacts.
	 */
	KMShellInitStripHead (&StripHead[30], &Tex[1], VC_OPAQUE);
	kmChangeStripFilterMode 	(&StripHead[30], KM_IMAGE_PARAM1, KM_TRILINEAR_A);
	kmChangeStripMipmapAdjust	(&StripHead[30], KM_IMAGE_PARAM1, dwMipmapLevel);


	KMShellInitStripHead (&StripHead[31], &Tex[1], VC_TRANS);
	kmChangeStripFilterMode 	(&StripHead[31], KM_IMAGE_PARAM1, KM_TRILINEAR_B);
	kmChangeStripBlendingMode	(&StripHead[31], KM_IMAGE_PARAM1, KM_ONE, KM_ONE);
	kmChangeStripMipmapAdjust	(&StripHead[31], KM_IMAGE_PARAM1, dwMipmapLevel);


	/* BANNER (TRANSLUCENT TRILINEAR) */
	KMShellInitStripHead (&StripHead[40], &Tex[2], VC_TRANS);
	kmChangeStripFilterMode 	(&StripHead[40], KM_IMAGE_PARAM1, KM_TRILINEAR_A);
	kmChangeStripSRCSelect		(&StripHead[40], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[40], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[40], KM_IMAGE_PARAM1, KM_ONE, KM_ZERO);
	kmChangeStripMipmapAdjust	(&StripHead[40], KM_IMAGE_PARAM1, dwMipmapLevel);


	KMShellInitStripHead (&StripHead[41], &Tex[2], VC_TRANS);
	kmChangeStripFilterMode 	(&StripHead[41], KM_IMAGE_PARAM1, KM_TRILINEAR_B);
	kmChangeStripSRCSelect		(&StripHead[41], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[41], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[41], KM_IMAGE_PARAM1, KM_ONE, KM_ONE);
	kmChangeStripMipmapAdjust	(&StripHead[41], KM_IMAGE_PARAM1, dwMipmapLevel);

	KMShellInitStripHead (&StripHead[42], NULL, VC_TRANS);
	kmChangeStripSRCSelect		(&StripHead[42], KM_IMAGE_PARAM1, 1);
	kmChangeStripDSTSelect		(&StripHead[42], KM_IMAGE_PARAM1, 0);
	kmChangeStripMipmapAdjust	(&StripHead[42], KM_IMAGE_PARAM1, dwMipmapLevel);


}
/*-------------------------------------------------------------------------------------
 *  Function Name   : RenderObject                                                    
 *  Inputs          : Object pStripHead                                                          
 *  Outputs         : None                                                             
 *  Returns         : None                                                          
 *  Globals Used    :                                                                 
 *  Description     : Sending a set of strips to render.                            
 *-------------------------------------------------------------------------------------*/
void RenderObject (int Object, KMSTRIPHEAD *pStripHead)
{
	KMShellStrips (pStripHead, Mesh[Object].nNumStrips, Mesh[Object].pStripLength,
		          Mesh[Object].pStrips, KmVert[Object]);

}
/*-------------------------------------------------------------------------------------
 *  Function Name   : CalculateMovement                                                    
 *  Inputs          : nType                                                           
 *  Outputs         : None                                                             
 *  Returns         : None                                                          
 *  Globals Used    :                                                                 
 *  Description     : Calculates the 'waving' movement of the balls (...ejem, 
 *                    I mean the spheres) and the tape.                            
 *-------------------------------------------------------------------------------------*/
void CalculateMovement (int nType)
{
register i;
float fZPos, fOffset;

	fOffset = nFrame/20.0f;

	if (nType)
	{
		SphPos[0] = 500.0f * sin(nFrame/100.0f) + 500.0f;
		SphPos[1] = sin((SphPos[0]/100.0f + fOffset)) * 20.0f - 30.0f;
	}

	else
	{
		SphPos[0] = 420.0f * sin(nFrame/100.0f) + 500.0f;
		SphPos[1] = cos((SphPos[0]/100.0f + fOffset)) * 20.0f - 30.0f;
	}

	for (i=0; i<Mesh[M_TAPE].nNumVertex; i++) 
	{
		fZPos = *(Mesh[M_TAPE].pVertex+ i*3 + 2); 

		if (nType)
			*(Mesh[M_TAPE].pVertex+ i*3 + 1) = sin((fZPos/100.0f + fOffset)) * 20.0f - 30.0f;
		else
			*(Mesh[M_TAPE].pVertex+ i*3 + 1) = cos((fZPos/100.0f + fOffset)) * 20.0f - 30.0f;
	}

}
/*-------------------------------------------------------------------------------------
 *  Function Name   : CreateWindows                                                    
 *  Inputs          : None                                                    
 *  Outputs         : None                                                             
 *  Returns         : None                                                          
 *  Globals Used    :                                                                 
 *  Description     : Info windows.                            
 *-------------------------------------------------------------------------------------*/
void CreateWindows (void)
{
	/* Info Window */
	InfoWin = KMPrint3DCreateDefaultWindow (2.0f, 93.0f, 150, NULL, " ");

	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "TRILINEAR          ", NULL);
	
		/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "TRILINEAR (1 of 2) ",
"Trilinear is a special filter for mip-mapped textures. \
Every texel in a polygon is calculated as the linear interpolation between two mipmap levels.\n\n\
The texel color is a weighted blend between the color of that pixel in two adjacent mipmap levels based on the Z distance to them.\n");

		/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "TRILINEAR (2 of 2) ",
"Trilinear filtering helps to avoid the otherwise visible boundary lines between different mipmap levels.\n\n\
However, this improvement in image quality carries a performance penalty as trilinear filtering requires an additional pass.\n");
}
