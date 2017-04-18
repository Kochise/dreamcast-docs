/*****************************************************************************
  Name :     Materials 
  Author:	 Carlos Sarria
  Date :     April 1999 (Updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : BumpMap materials demo.

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

#define NUM_MESHES     5
#define NUM_MATERIALS  12
#define	NUM_TEXTURES   22

/* MESHES */
#define M_STAR  0
#define M_SPHERE  1
#define M_BOX  2
#define M_LIGHT  3
#define M_BACKGROUND  4

#define M_STARBUMP  5
#define M_SPHEREBUMP  6
#define M_BOXBUMP  7


/*************************************************/
/*	Globals                                      */
/*************************************************/

KMSURFACEDESC		Tex[256];				/* texture surface */
KMSTRIPHEAD			StripHead[256];		/* Vertex context */
KMVERTEX_03			*KmVert[256];			/* Vertex pointers*/

/* Bumpmap data */
float *pBump[256];

/* Camera data */
int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -200.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 0.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

/* Generic data */
unsigned nFrame = 0, nCurrentTexture = 6, CreationMethod = 1, CurrentObject = 1, Show=FALSE, BumpMethod = 0;

/* Object angles */
float fAng1 = 0.0f , fAng2 = 0.0f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 75.0f;

/* Light angle */
float fLAng1 = -0.5f, fLAng2 = 1.0f;

DWORD	dwCurrentWin= 0, dwDisplayWins = 1, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/
void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(int Mode);
void	InitBumpmapMesh		(int Object, int OriginalMesh);
void 	CreateWindows 		(void);

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
 *  Description     :   InitApplication() is called by KMShell to enable the
 *						user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{
	KMShellSetVideo	(TRUE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );

	KMShellSetBuffers(0, 		/* % Opaque (flushed) */
					  0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					  0,		/* % ModVol Trans  */
					  0			/* % Punchthrough  */
					  );		

	KMPrint3DSetTextures();
	
	CreateWindows ();
	
	LoadTextures 	();
	CreateContexts 	(0);
 
	InitMeshes();

	InitBumpmapMesh (M_STARBUMP, 	M_STAR);
	InitBumpmapMesh (M_SPHEREBUMP, 	M_SPHERE);
	InitBumpmapMesh (M_BOXBUMP, 	M_BOX);
	

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
 *  Description     :  QuitApplication() is called by KMShell to enable the
 *						user to finish the application                                                     
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	 KMPrint3DReleaseTextures ();
	 
	for (i=0; i<NUM_MESHES; i++) 
	{
		free(KmVert[i]); 
	}

	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  KMRenderScene                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                               
 *  Globals Used    :                                 
 *  Description     :  Draws everything in the scene.                                                 
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
MATRIX		Matrx;
int			i, j, BumpmapObject;
char	*Textures[]={"BRICKS", "CRACKS","EGYPT","FIBER","GOLD","GOLF","LIZARD1","LIZARD2","STONES","WOOL"};
char	*Objects[]={"STAR", "SPHERE","SLAB"};
char	*BMethod[]={ "STANDARD", "TRANSLUCENT", "HIGHLIGHT"};


	KMShellBackground(&StripHead[21]);

   	/* CurrentObject is a standard object and CurrentObject+5 is the bumpmap object on top of the standard one.
	 * For this demo, both objects are transformed appart for clarity, but the same object can be used twice. 
	 */
	BumpmapObject = CurrentObject + M_STARBUMP; 
 
	KMMatrixReset	  (&Matrx);  
	KMMatrixRotate    (&Matrx,  0.0f, fAng1, fAng2);
	KMMatrixTranslate (&Matrx, 0.0f, 0.0f, fDist);  
   
	/* Base transformation */
	KMTransTransformProjectPerspective (&Matrx, Mesh[CurrentObject].nNumVertex, Mesh[CurrentObject].pVertex, 
										KmVert[CurrentObject], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
	/* Bummap layer transformation */
	KMTransTransformProjectPerspective (&Matrx, Mesh[CurrentObject].nNumVertex, Mesh[CurrentObject].pVertex, 
										KmVert[BumpmapObject], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

	/* Calculation of bump-map nad smooth-shading in one go */ 
	KMBumpShade (&Matrx, Mesh[CurrentObject].nNumVertex, pBump[BumpmapObject], Mesh[CurrentObject].pNormals,
						KmVert[BumpmapObject], KmVert[CurrentObject], LightDirection, BumpMethod);


	/* Render bump layer */
	KMShellStrips (&StripHead[10+nCurrentTexture],
						Mesh[CurrentObject].nNumStrips, Mesh[CurrentObject].pStripLength, 
						Mesh[CurrentObject].pStrips, (KMVERTEX_03 *)KmVert[BumpmapObject]);
						
	/* Render base layer */
	KMShellStrips (&StripHead[nCurrentTexture],
						Mesh[CurrentObject].nNumStrips, Mesh[CurrentObject].pStripLength, 
						Mesh[CurrentObject].pStrips, (KMVERTEX_03 *)KmVert[CurrentObject]);

	/* Draw the light spot */
	if (Show==TRUE)
	{
		KMMatrixReset	 (&Matrx);

		KMMatrixTranslate (&Matrx, -LightDirection[0] * 120.0f, -LightDirection[1] * 120.0f, fDist - LightDirection[2] * 120.0f);  


		KMTransTransformProjectPerspective (&Matrx, Mesh[M_LIGHT].nNumVertex, Mesh[M_LIGHT].pVertex, 
										KmVert[M_LIGHT], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

		KMShellStrips (&StripHead[20],
						Mesh[M_LIGHT].nNumStrips, Mesh[M_LIGHT].pStripLength, 
						Mesh[M_LIGHT].pStrips, (KMVERTEX_03 *)KmVert[M_LIGHT]);
						
		Show=FALSE;
	}

  
  /* 
   * Text windows.
   */
   if(dwDisplayWins)
   {
    	KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	}

	/* Update InfoWin */	
	KMPrint3DClearWindowBuffer  (InfoWin);
	KMPrint3DWindowOutput		(InfoWin, "(X) Bump method: %s\n", BMethod[BumpMethod]);
	KMPrint3DWindowOutput		(InfoWin, "(B) Texture:  %s\n", Textures[nCurrentTexture]);
	KMPrint3DWindowOutput		(InfoWin, "(Y) Object: %s", Objects[CurrentObject]);
	
	nFrame++;
  
	/* RenderScene OK */
	return TRUE;
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : KMPadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : TRUE to continue, FALSE to finish the app.                                                               
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
			/* Generic data */
			nFrame = 0;

			/* Object angles */
			fAng1 = 0.0f ; fAng2 = 0.0f; fAng3 = 0.0f;

			/* Camera distance */
			fDist = 75.0f;

			/* Light angle */
			fLAng1 = -0.5f; fLAng2 = 1.0f;

			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
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
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng1 -= 0.02f;
		}
		else fAng2 += 0.05f;   
	 }

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng1 += 0.02f;
		}
		else fAng2 -= 0.05f;
	}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng2 -= 0.02f;
		}
		
		else  fAng1  += 0.05f;
	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2) * cos(fLAng1);
			LightDirection[1] = sin(fLAng1);
			LightDirection[2] = sin (fLAng2) * cos(fLAng1);
			fLAng2 += 0.02f;
		}
		
		else   fAng1  -= 0.05f;
	}
	
	/* A button */
	if (IsAKey())
	{
		Show=TRUE;
	}
	
	/* B button */
	if (IsBKey())
	{
		if (Delay>2) {nCurrentTexture++; if(nCurrentTexture==10) nCurrentTexture=0;}
		Delay = 0;
	}
		
	/* X button */
	if (IsXKey())
	{
		if (Delay>2) {BumpMethod++; if(BumpMethod==3) BumpMethod=0; CreateContexts (BumpMethod);}
		Delay = 0;
	
	}

	/* Y button */
	if (IsYKey())
	{
		if (Delay>2)
		{
			CurrentObject++; if(CurrentObject==3) CurrentObject = 0;
		}
		Delay = 0;
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
		/* Zoom in */
		if (fDist>-40) fDist -= 10.0f; 
		
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Zooom out */
		if (fDist<250) fDist += 10.0f;
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
 *  Description     : Sets initials values for meshes managment.                           
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
			if (i==M_BOX || i==M_LIGHT)
			{
				(KmVert[i]+j)->fU = *(Mesh[i].pUV+j*2+0); 
				(KmVert[i]+j)->fV = *(Mesh[i].pUV+j*2+1); 
			}
			else
			{
				(KmVert[i]+j)->fU = *(Mesh[i].pUV+j*2+0) * 4.0f; 
				(KmVert[i]+j)->fV = *(Mesh[i].pUV+j*2+1) * 4.0f; 
			}

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0xFFFFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0x00000000;
		
		} 

   }

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitBumpmapMesh                                                  
 *  Inputs          : None                                                                 
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                 
 *  Description     : Sets the 'Tangent Space' coordinate system for every vertex to be 
 *					  bumpmapped.                            
 *-------------------------------------------------------------------------------------*/
void InitBumpmapMesh (int Object, int OriginalMesh)
{	
register j;

		/* Memory allocation for KmVert */ 
		KmVert[Object] = (KMVERTEX_03 *)syMalloc(Mesh[OriginalMesh].nNumVertex*sizeof(KMVERTEX_03)); 
		
		/* Setting UV values for the mesh */
   		for (j=0; j<Mesh[OriginalMesh].nNumVertex; j++)
		{
			if (OriginalMesh==M_BOX)
			{
				(KmVert[Object]+j)->fU = *(Mesh[OriginalMesh].pUV+j*2+0); 
				(KmVert[Object]+j)->fV = *(Mesh[OriginalMesh].pUV+j*2+1); 
			}
			else
			{
				(KmVert[Object]+j)->fU = *(Mesh[OriginalMesh].pUV+j*2+0) * 4.0f; 
				(KmVert[Object]+j)->fV = *(Mesh[OriginalMesh].pUV+j*2+1) * 4.0f; 
			}

		} 

		/* 
		 * Local coordenates system for bump-mapping.
		 * 3 floats for Tanget axis, 3 floats for Binormal Axis
		 */
		pBump[Object] = (float *)syMalloc(Mesh[OriginalMesh].nNumVertex*sizeof(float)*6); 
		
		/* 
		 * That is the function that calculates the local coordenate system
		 * for every single vertex. The information is stored in pBump[]
		 */
		KMBumpCalculateLocalCoords (pBump[Object], BUMP_COORDS_ANYDIRECTION,
									Mesh[OriginalMesh].nNumVertex, Mesh[OriginalMesh].pVertex, Mesh[OriginalMesh].pNormals,
									Mesh[OriginalMesh].pUV,	Mesh[OriginalMesh].nNumFaces, Mesh[OriginalMesh].pFaces);	


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
int i, j;
int nMaterial, nTexture, nTransTexture, nBumpTexture;

	/* Bumpmap materials (Textures 0-19) */
	for (i=0; i<10; i++)
	{
		nTexture = i*2;
		nBumpTexture = nTexture + 1;
		
		KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, 
						KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
						
		KMTextureConvertAndLoad(&Tex[i+10], Texture[nBumpTexture].pBitmapData, NULL, 
						Texture[nBumpTexture].nWidth, Texture[nBumpTexture].nHeight,
						KM_TEXTURE_TWIDDLED | KM_TEXTURE_BUMP);				
			
	}

	/* Light */
	KMTextureConvertAndLoad(&Tex[20], Texture[20].pBitmapData, NULL, 
						Texture[20].nWidth, Texture[20].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	
	/* Background */
	KMTextureConvertAndLoad(&Tex[21], Texture[21].pBitmapData, NULL, 
						Texture[21].nWidth, Texture[21].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : Mode                                                              
 *  Outputs         : None                                                
 *  Returns         : None                                                           
 *  Globals Used    :                                   
 *  Description     : Creates context for the different bumpmap modes on the fly.             
 *-------------------------------------------------------------------------------------*/
void CreateContexts (int Mode)
{
register i;

	/* Background */
	KMShellInitStripHead (&StripHead[21], &Tex[21], VC_OPAQUE);
	
	/* Light */
	KMShellInitStripHead (&StripHead[20], &Tex[20], VC_ADDITIVE);

	for (i=0; i<10; i++)
	{
		switch (Mode)
		{
			case 0: 
			/* STANDARD */
				/* Bump Materials */
				KMShellInitStripHead (&StripHead[10+i], &Tex[10+i], VC_OPAQUE | VC_SPECULAR | VC_DECALALPHA);
				/* Base Materials */
				KMShellInitStripHead (&StripHead[i], &Tex[i], VC_TRANS);
				kmChangeStripBlendingMode	( &StripHead[i], KM_IMAGE_PARAM1,  KM_DESTCOLOR, KM_ZERO );
				break;
				
			case 1: 
			/* TRANSLUCENT */
				/* Bump Materials */
				KMShellInitStripHead (&StripHead[10+i], &Tex[10+i], VC_TRANS | VC_SPECULAR);
				/* Base Materials */
				KMShellInitStripHead (&StripHead[i], &Tex[i], VC_OPAQUE);
				break;
			
			case 2: 
			/* ADDITIVE */
				/* Bump Materials */
				KMShellInitStripHead (&StripHead[10+i], &Tex[10+i], VC_OPAQUE | VC_SPECULAR | VC_DECALALPHA);
				/* Base Materials */
				KMShellInitStripHead (&StripHead[i], &Tex[i], VC_ADDITIVE);
				break;
				
			}
	}
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
	
	KMPrint3DSetWindow		(InfoWin, 0x80A00000, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput		(InfoWin, "(X) Bump method: STANDARD\n");
	KMPrint3DWindowOutput		(InfoWin, "(B) Texture:  WOOD\n");
	KMPrint3DWindowOutput		(InfoWin, "(Y) Object: SPHERE");

	/* Text Windows */
	/* Window 0 */
	/* Window 1 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MATERIALS Bump-mapping   ", NULL);


	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MATERIALS Bump-mapping  (1 of 4)","\
The bump-mapping technique is based on a 2D map that stores information about the roughness of a surface.\n\n\
The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
be applied to the texture underneath, creating high-definition shading over a flat surface.\n\n");

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MATERIALS Bump-mapping  (2 of 4)","\
The standard method for blending bumpmap surfaces is to make \
the bumpmap surface opaque and to blend the base texture on top using as blend factors DESTCOLOR for the source \
and ZERO for the destination.\n\n"); 

	/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MATERIALS Bump-mapping  (3 of 4)","\
Another combination that works really well is when the base texture is opaque and the bump map texture is translucent \
(SRCALPHA / INVSRCALPHA) with all the vertex colours set to 0. With this method you can change the strength of the bump map \
by just changing the value in the alpha channel. Values around 0xA0 are best for the majority of applications.  \
K1 and K2 have been fixed to 0 and 128 (medium intensity).\n\n"); 

		/* Window 3 */
	TWin[4] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "MATERIALS Bump-mapping  (4 of 4)","\
To get highlights on a bumpmap surface invert the K3 value (K3 = 255 -K3) \
and set K1 and K2 to 0. Blend the base texture on top of the opaque bumpmap layer using additive blending (ONE/ONE). \
This trick gives a very nice shiny effect. \n\
There is a problem: the few polygons that are perpendicular to the light direction \
change their shading very quickly. To avoid this problem the best solution is to 'burn' that conflictive \
zone with strong highlights in the base colour of the bumpmap vertices.\n\n"); 

}
/*--------------------------------------------------------------------------------------*/
/*---------------------------------- END OF FILE ---------------------------------------*/
/*--------------------------------------------------------------------------------------*/





