/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     ShadyTexture
  Date :     Sep 1999
  Platform : Dreamcast Set5 (CLX2 + SH4) 
  
  Description : Creates a 'real' shadow using Render in a Texture.

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <math.h>
#include <shinobi.h>

#include "KMTools.h"
#include "KMShell.h"

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Mesh      Mesh[];
extern Struct_Texture   Texture[];

#define NUM_MESHES     3
#define	NUM_TEXTURES   3

/* MESHES */
#define M_LIGHT  0
#define M_FLOOR  1
#define M_TEAPOT  2

#define M_DUMMY 4
#define M_SHADOW 5


#ifndef PI
#define PI 3.1415
#endif

typedef struct boundary_sphere_struct_tag {
	float fCenter[3];
	float fRadius;
} BOUNDSPHERE;

/*************************************************/
/*	Globals                                      */
/*************************************************/

#define RT_SIZE 256

/* texture surface */
KMSURFACEDESC		Tex[256], TexSurfaceDesc[10];		
		
/* Vertex context */
KMSTRIPHEAD 		StripHead[256], TexSurfaceStripHead[10];	

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

BOUNDSPHERE        BoundSphere[256];

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 700.0f, -700.0f};
km_vector CameraTo			= { 0.0f, 0.0f, -50.0f};
km_vector LightDirection	= { 0.0f, -1.0f, 1.0f};

float   nFrame = 0; 
float	fXAng, fYAng, fZAng;

BOOL    bStart = FALSE, bNoAB = FALSE, bMoveFloor = TRUE;

float   fPosX=0.0f, fPosZ=0.0, fAngleY = 0.5f, fAngleX=0.0f, fHeight = 0.0f;
float	fLAng1 = -0.5f, fLAng2 = 0.1f;


/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Extern Globals (from KMShell.c)                */
/**************************************************/

extern KMVERTEXBUFFDESC 	VertexBufferDesc;
extern KMSYSTEMCONFIGSTRUCT	SystemConfig;

/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes					(void);
void 	LoadTextures 				(void);
void    InitMaterials       		(void);
void	RenderObject				(int Object, KMSTRIPHEAD *pStripHead);
void 	CreateWindows 				(void);
void 	InitTexturesForRender 		(void);
int 	RenderSceneInScreenBuffer 	(void);
int 	RenderShadowInTexture 		(KMSURFACEDESC *pTexTarget, int nObject);
void 	DrawShadow 					(void);
void 	CalculateBoundSphere 		(int nObject);
void 	MoveFloor 					(void);

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
 *						user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{
register i;

	KMShellSetVideo	(TRUE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0xFF   /* Logo background translucency */
					 );
					 

	KMShellSetBuffers (	0, 			/* % Opaque  (flushed)    */
						0,			/* % ModVol Opaque */
						100,		/* % Translucent   */
						0,			/* % ModVol Trans  */
						0);	

	KMPrint3DSetTextures();
	
	LoadTextures ();
	
	InitMaterials ();
	
	InitTexturesForRender ();

	CalculateBoundSphere (M_TEAPOT);
	
	InitMeshes();
	
	CreateWindows();

	LightDirection[0] = cos(fLAng2) * cos(fLAng1);
	LightDirection[1] = sin(fLAng1);
	LightDirection[2] = sin (fLAng2) * cos(fLAng1);

}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                          
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *						user to finish the application                                                
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures();

	for (i=0; i<NUM_TEXTURES; i++)
	{
		kmFreeTexture(&Tex[i]);
	}
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		syFree(KmVert[i]);
	}
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderScene                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish the app.                                              
 *  Globals Used    :                                                  
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
	RenderShadowInTexture (&TexSurfaceDesc[0], M_TEAPOT);
	
	if (bStart==FALSE)
	{
		fAngleY += 0.03f;
		fAngleX += 0.03f;
		fLAng2 -= 0.01f;
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
	}
	
	
	RenderSceneInScreenBuffer ();	
	
	nFrame++;
		
	/* RenderScene OK */
	return TRUE;

}

/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneInScreenBuffer                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish the app.                                              
 *  Globals Used    :                                                  
 *  Description     :                                        
 *----------------------------------------------------------------------*/
int RenderSceneInScreenBuffer (void)
{
int				i, j;
MATRIX			Matrx;
KMVERTEX_03     *ptrObject;
float			*ptrUV;
km_vector 		FloorLightDirection	= { 0.0f, -1.0f, 1.0f};
	
	/* Render the teapot */
	KMMatrixReset	  (&Matrx);
	
	KMMatrixRotate(&Matrx, fAngleX, fAngleY, 0);
	
	KMTransTransformProjectPerspective (&Matrx, Mesh[M_TEAPOT].nNumVertex, Mesh[M_TEAPOT].pVertex, 
											KmVert[M_TEAPOT], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
	/* Calculation of smooth-shading */ 
	KMLightSmoothShade (&Matrx, Mesh[M_TEAPOT].nNumVertex, Mesh[M_TEAPOT].pNormals, (KMVERTEX_03 *)KmVert[M_TEAPOT],
								LightDirection, 0xFFFFFFFF, TRUE); 
								
	/* Adjust the matrix to get a correctly 'faked' env-map */
	KMMatrixScale(&Matrx, 0.7f);
	Matrx._43  = 0.2f; 
			
	KMTransEnvironmentMap (&Matrx, Mesh[M_TEAPOT].nNumVertex, Mesh[M_TEAPOT].pNormals, 
											KmVert[M_TEAPOT], 	CameraFrom, CameraTo, 0.0f, 
											1.0f, 1000000.0f, 30.0f*(PI/180.0f));
			
	RenderObject (M_TEAPOT, &StripHead[M_TEAPOT]);
		
	
	
	/* Render the shadow on the floor using the floor mesh with the projected UVs */
	KMMatrixReset  (&Matrx);
	
	KMTransTransformProjectPerspective (&Matrx, Mesh[M_FLOOR].nNumVertex, Mesh[M_FLOOR].pVertex, 
											KmVert[M_FLOOR], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
	
	RenderObject (M_FLOOR, &TexSurfaceStripHead[0]);
			
	/* Restore the original UVs to draw the opaque floor */
	ptrObject = KmVert[M_FLOOR];
	ptrUV	 =	Mesh[M_FLOOR].pUV;		
							
	for (j=Mesh[M_FLOOR].nNumVertex; j>0; j--)
	{
		ptrObject->fU = *(ptrUV++);
		ptrObject->fV = *(ptrUV++);
		ptrObject++;
	}

	/* Render opaque floor */
	RenderObject (M_FLOOR, &StripHead[M_FLOOR]);
			
	
	
	/* Draw the light spot */
	KMMatrixReset	 (&Matrx);

	KMMatrixTranslate (&Matrx,	-LightDirection[0] * 150.0f + BoundSphere[M_TEAPOT].fCenter[0], 
								-LightDirection[1] * 150.0f + BoundSphere[M_TEAPOT].fCenter[1], 
								-LightDirection[2] * 150.0f + BoundSphere[M_TEAPOT].fCenter[2]);  


	KMTransTransformProjectPerspective (&Matrx, Mesh[M_LIGHT].nNumVertex, Mesh[M_LIGHT].pVertex, 
										KmVert[M_LIGHT], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));

	RenderObject (M_LIGHT, &StripHead[M_LIGHT]);
						
	

	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	 }
	
	return TRUE;
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderShadowInTexture                                      
 *  Inputs          :                                                 
 *  Outputs         :                                                   
 *  Returns         :                                       
 *  Globals Used    :                                                  
 *  Description     :  Projects the object to be shadowed on a texture. 
 *                     The new UVs for the 'mobile' floor are calculated
 *                     projecting the floor on the same texture than the sadow
 *                     and using the X and Y projected co-ordinates to 
 *                     calculate the new UVs.                                 
 *----------------------------------------------------------------------*/
int RenderShadowInTexture (KMSURFACEDESC *pTexTarget, int nObject)
{
int				i, j;
MATRIX			Matrx;
static float	Angle = 0.0f;
km_vector ShadowCameraFrom, ShadowCameraTo;
KMVERTEX_03     *ptrObject;

	 /* First recalculate the new floor shape */
	 MoveFloor ();
	
	 /* Calculate the camera position */
	 ShadowCameraFrom[0] = -LightDirection[0] * BoundSphere[nObject].fRadius * 4.0f + BoundSphere[nObject].fCenter[0];
	 ShadowCameraFrom[1] = -LightDirection[1] * BoundSphere[nObject].fRadius * 4.0f + BoundSphere[nObject].fCenter[1] ;
	 ShadowCameraFrom[2] = -LightDirection[2] * BoundSphere[nObject].fRadius * 4.0f + BoundSphere[nObject].fCenter[2];
	 
	 ShadowCameraTo[0] = BoundSphere[nObject].fCenter[0];
	 ShadowCameraTo[1] = BoundSphere[nObject].fCenter[1];
	 ShadowCameraTo[2] = BoundSphere[nObject].fCenter[2];

	 /* Draw the object (white-grey on black background) */
	 KMMatrixReset	  (&Matrx);
	
	 KMMatrixRotate(&Matrx, fAngleX, fAngleY, 0);

	/* Transform all the vertices */
	KMTransTransformProjectPerspective (&Matrx, Mesh[nObject].nNumVertex, Mesh[nObject].pVertex, 
											KmVert[nObject], RT_SIZE, RT_SIZE,
											ShadowCameraFrom, ShadowCameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
											
	/* Shadow colour (the more white the more darker the actual shadow)*/											
	for(i=Mesh[nObject].nNumVertex; i>=0; i--) (KmVert[nObject]+i)->uBaseRGB.dwPacked = 0xFF808080; 
	
	RenderObject (nObject, &StripHead[M_DUMMY]);
		
	/* Calculating the projection on the floor */
	KMMatrixReset	  (&Matrx);
	KMTransTransformProjectPerspective (&Matrx, Mesh[M_FLOOR].nNumVertex, Mesh[M_FLOOR].pVertex, 
											KmVert[M_FLOOR], RT_SIZE, RT_SIZE,
											ShadowCameraFrom, ShadowCameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));

	/* Re-scale the X and Y projection to get the final UVs */ 											
	ptrObject = KmVert[M_FLOOR];										
	for (i=0; i<Mesh[M_FLOOR].nNumVertex; i++)
	{
		ptrObject->fU = ptrObject->fX * (1.0f/RT_SIZE);
		ptrObject->fV = ptrObject->fY * (1.0f/RT_SIZE);
		ptrObject++;
	}
										
										 
	/* Finish the pass (It was started in main() of KMShell.c) */
	kmEndPass(&VertexBufferDesc);

	/* Render in the previous texture the final result */
	kmRenderTexture(pTexTarget, FALSE);

	/*
	 * Finish the scene (It was started in main() of KMShell.c)
	 */
    kmEndScene (&SystemConfig);

	/* Start the new scene and the new pass for rendering to the screen buffer.
	 * (that will finish in main() of KMShell.c)
	 */
	kmBeginScene(&SystemConfig);
	kmBeginPass(&VertexBufferDesc);
    
	return TRUE;
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : PadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Note            : This function is called by KMShell.c                           
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	Delay = 0;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
		if (Delay>2)
		{
			bStart = !bStart;
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
			if (dwCurrentWin==-1) dwCurrentWin = 4;
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
			if (dwCurrentWin==5) dwCurrentWin = 0;
		}
		Delay =0;
	}
	
	/* UP ANALOG-PAD */
	if (AnalogPadY()<-64)
	{
		if(IsAKey())
		{
			/* Light rotation */
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			if(fLAng1>-1.40f) fLAng1 -= 0.02f;
		}
		else
		{
			fAngleX -= 0.1f;
		}
	 }

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		if(IsAKey())
		{
			/* Light rotation */
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			if(fLAng1<-0.20) fLAng1 += 0.02f;
		}
		else
		{
			fAngleX += 0.1f;
		}
		
	}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
		if(IsAKey())
		{
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng2 -= 0.02f;
		}
		else
		{
			fAngleY -= 0.1f;
		}
	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
		if(IsAKey())
		{
			/* Light rotation */
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng2 += 0.02f;
		}
		else
		{
			fAngleY += 0.1f;
		}
	}


	/* A button */
	if (IsAKey())
	{
		
	}
	
	/* B button */
	if (IsBKey())
	{
		if(Delay>2)
		{
			bMoveFloor = !bMoveFloor;
		}
		Delay=0;
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
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
	}

	return TRUE;
}
/*-------------------------------------------------------------------------------------*
 *  Function Name   : InitMeshes
 *  Inputs          : None
 *  Outputs         : None
 *  Returns         : None
 *  Globals Used    : 
 *  Description     : Initialitation for meshes
 *-------------------------------------------------------------------------------------*/
void InitMeshes (void)
{
register unsigned i,j, k=0;
float fTempVert[3], fModule;


	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03));
	}

	/* Setting UV values and colors for all the meshes reading materials or vertex colors*/
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
			/* UVs */
			if(Mesh[i].pUV != NULL)
			{
				(KmVert[i]+j)->fU	= *(Mesh[i].pUV+j*2+0);
				(KmVert[i]+j)->fV	= *(Mesh[i].pUV+j*2+1);
			}
			else
			{
				(KmVert[i]+j)->fU	= 0.0f;
				(KmVert[i]+j)->fV	= 0.0f;
			}

			/* Material color (or default) */
			(KmVert[i]+j)->uBaseRGB.dwPacked = 0xFFFFFFFF;
			
			/* No specular color */
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
 *  Description     : Converts textures from a 24bits Bitmap format to a 16bits hardware
 *                    format and loads them in video memory.
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
	KMTextureConvertAndLoad(&Tex[M_LIGHT], Texture[0].pBitmapData, NULL, 
						Texture[0].nWidth, Texture[0].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[M_FLOOR], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[M_TEAPOT],Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[M_DUMMY], Texture[3].pBitmapData, NULL, 
						Texture[3].nWidth, Texture[3].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitMaterials                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Create all the contexts for the application.                          
 *-------------------------------------------------------------------------------------*/
void InitMaterials (void)
{

 	KMShellInitStripHead (&StripHead[M_FLOOR], &Tex[M_FLOOR], VC_OPAQUE);
	
	KMShellInitStripHead (&StripHead[M_TEAPOT], &Tex[M_TEAPOT], VC_OPAQUE | VC_SPECULAR);
	
	KMShellInitStripHead (&StripHead[M_LIGHT], &Tex[M_LIGHT], VC_ADDITIVE);
	
	KMShellInitStripHead (&StripHead[M_DUMMY], &Tex[M_DUMMY], VC_OPAQUE);


}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitTexturesForRender                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     :                        
 *-------------------------------------------------------------------------------------*/
void InitTexturesForRender (void)
{
KMINT32 nTextureType;
KMINT32	nStrideWidth;

		nTextureType = KM_TEXTURE_RECTANGLE | KM_TEXTURE_RGB565;	/* Set texture type */

		kmCreateTextureSurface(
					&TexSurfaceDesc[0],		/* OUT	PKMSURFACEDESC	pSurfaceDesc */
					RT_SIZE,				/*	IN	KMINT32			nWidth  */ 
					RT_SIZE,				/*	IN	KMINT32			nHeight  */
					nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
				);
				
		/* Shadow texture (light map) */
		KMShellInitStripHead (&TexSurfaceStripHead[0], &TexSurfaceDesc[0], VC_TRANS);
		
		kmChangeStripClampUV (&TexSurfaceStripHead[0], KM_IMAGE_PARAM1, KM_CLAMP_UV);
	    kmChangeStripBlendingMode(&TexSurfaceStripHead[0], KM_IMAGE_PARAM1,  KM_ZERO, KM_INVSRCCOLOR);

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

/*-------------------------------------------------------------------------------------* 
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
	InfoWin = KMPrint3DCreateWindow (50, 3);
	
	KMPrint3DSetWindow		(InfoWin, 0x602030FF, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput	(InfoWin, "(START) Rolling demo/Interactive\n");
	KMPrint3DWindowOutput	(InfoWin, "(A+ANALOG PAD) Move light.\n");
	KMPrint3DWindowOutput	(InfoWin, "(B) Stop surface.");
	
	
	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Render to a texture   ", NULL);
	
 	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Render to a texture (1 of 4)",
"This demo shows how to create a correct 'shadow' texture which can be projected onto any surface.\n\n");
    
    /* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Render to a texture  (2 of 4)",
"The camera is placed at the same position as the light spot. The object is then rendered in black and white on a square texture.\n\n");

    /* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Render to a texture (3 of 4)",
"The floor vertices are projected as well, and the X and Y co-ordinates are used to calculate the new UV values for the shadow projection.\n\n");

    /* Window 4 */
	TWin[4] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Render to a texture (4 of 4)",
"Finally, the floor with the shadow texture and the corrected UV values is blended on top of the actual opaque floor using a standard light-map blend mode.\n\n");

}
/*----------------------------------------------------------------------*/
/*  Function Name   :  DrawShadow                                    
/*  Inputs          :  *StripHead                                 
/*  Outputs         :  None                                             
/*  Returns         :  None                                            
/*  Globals Used    :  VertexBufferDesc                                 
/*  Description     :  
/*----------------------------------------------------------------------*/
void DrawShadow (void)
{
KMVERTEXBUFFDESC *pVertexBufferDesc;
KMVERTEX_03     V[4];
int	i, k;

	pVertexBufferDesc = KMShellGetVertexBuffer();

	V[0].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[1].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[2].ParamControlWord	= KM_VERTEXPARAM_NORMAL;
	V[3].ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;

	/* Colors */
	for (k=0;k<4;k++)
	{
	V[k].uBaseRGB.dwPacked	 = 0xFFFFFFFF;
	V[k].uOffsetRGB.dwPacked = 0x00000000;
	}

    /* Position */
    V[0].fX	= 0.0f;
	V[0].fY	= RT_SIZE;

	V[1].fX	= 0.0f;
	V[1].fY	= 0.0f;

	V[2].fX	= RT_SIZE;
	V[2].fY	= RT_SIZE;

	V[3].fX	= RT_SIZE;
	V[3].fY	= 0.0f;

	V[0].u.fZ =  200.001;
	V[1].u.fZ =  200.001;
	V[2].u.fZ =  200.001;
	V[3].u.fZ =  200.001;

	/* UVs */
	V[0].fU	=  0.0f;
	V[0].fV	=  1.0f;

	V[1].fU	=  0.0f;
	V[1].fV	=  0.0f;

	V[2].fU	=  1.0f;
	V[2].fV	=  1.0f;

    V[3].fU	=  1.0f;
	V[3].fV	=  0.0f;

	/* Strip start */
	kmStartStrip(pVertexBufferDesc, &TexSurfaceStripHead[0]);

	/* Setting vertices */
	for(i = 0; i<4; i++)
	{
		kmSetVertex (pVertexBufferDesc, (KMVERTEX_03 *)(&V[i]), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
	}

 
}

/*----------------------------------------------------------------------*/
/*  Function Name   :  CalculateBoundSphere                                    
/*  Inputs          :  nObject                                 
/*  Outputs         :  None                                             
/*  Returns         :  None                                            
/*  Globals Used    :                          
/*  Description     :  This bound-sphere is used to locate the correct 
/*                     camera distance when rendering in a texture.
/*----------------------------------------------------------------------*/
void CalculateBoundSphere (int nObject)
{
register i;
float fTempCenter[3] = {0.0f, 0.0f, 0.0f};
float fMaxDist = 0.0f, fDist, x, y, z;

	/* Calculate the center */
	for (i=0; i<Mesh[nObject].nNumVertex; i++)
	{
		fTempCenter[0] += *(Mesh[nObject].pVertex+i*3+0);
		fTempCenter[1] += *(Mesh[nObject].pVertex+i*3+1);
		fTempCenter[2] += *(Mesh[nObject].pVertex+i*3+2);
	}
	
	BoundSphere[nObject].fCenter[0] = fTempCenter[0]/(float)Mesh[nObject].nNumVertex;
	BoundSphere[nObject].fCenter[1] = fTempCenter[1]/(float)Mesh[nObject].nNumVertex;
	BoundSphere[nObject].fCenter[2] = fTempCenter[2]/(float)Mesh[nObject].nNumVertex;
	
	/* Calculate the maximun distance from the center */
	for (i=0; i<Mesh[nObject].nNumVertex; i++)
	{
		x = *(Mesh[nObject].pVertex+i*3+0) - BoundSphere[nObject].fCenter[0];
		y = *(Mesh[nObject].pVertex+i*3+1) - BoundSphere[nObject].fCenter[1];
		z = *(Mesh[nObject].pVertex+i*3+2) - BoundSphere[nObject].fCenter[2];
		
		fDist = sqrt(x*x+y*y+z*z);
		
		if (fDist>fMaxDist) fMaxDist = fDist;
	}
	    
	BoundSphere[nObject].fRadius = fMaxDist;
}
/*----------------------------------------------------------------------*/
/*  Function Name   :  MoveFloor                                    
/*  Inputs          :  None                                 
/*  Outputs         :  None                                             
/*  Returns         :  None                                            
/*  Globals Used    :                          
/*  Description     :  Wavy movement...
/*----------------------------------------------------------------------*/
void MoveFloor (void)
{
int i, j, Face[3], Int, Colour;
unsigned short *ptrFaces;
float x, y, z, h, fDP;
km_vector V1, V2, V3, N, L, LightPos;
static float nCount=0;

	LightPos[0] = -LightDirection[0] * 150.0f + BoundSphere[M_TEAPOT].fCenter[0]; 
	LightPos[1] = -LightDirection[1] * 150.0f + BoundSphere[M_TEAPOT].fCenter[1]; 
	LightPos[2] = -LightDirection[2] * 150.0f + BoundSphere[M_TEAPOT].fCenter[2];
								
	h = 0.0001f * sin (nCount/64.0f);

	for (i=0; i<Mesh[M_FLOOR].nNumVertex; i++)
	{
		x = *(Mesh[M_FLOOR].pVertex+i*3+0);
		z = *(Mesh[M_FLOOR].pVertex+i*3+2);
		
		y = 50.0f * sin(h * (x*x+z*z)) - 100.0f;
		
		*(Mesh[M_FLOOR].pVertex+i*3+1) = y;
	}

	if (bMoveFloor) nCount++;
}
/*-----------------------------------------------------------------------------------------*
 * END OF FILE
 *-----------------------------------------------------------------------------------------*/