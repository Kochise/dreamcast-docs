/*****************************************************************************
  Name :     Wheel 
  Author:	 Carlos Sarria
  Date :     April 1999 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : BumpMap demo.

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

#define NUM_MESHES     8
#define NUM_MATERIALS  6
#define	NUM_TEXTURES   6

/* MESHES */
#define M_TIRE  0
#define M_TIREBUMP  1
#define M_GROUND  2
#define M_GROUNDBUMP  3
#define M_RIM  4
#define M_PLATES  5
#define M_PLATESBUMP  6
#define M_SUPPORT  7


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

km_vector CameraFrom		= { 0.0f, 100.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 0.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

/* Generic data */
unsigned nFrame = 500;

/* Wheel angles */
float fAng1 = 0.0f , fAng2 = -1.2f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 75.0f;

/* Light angle */
float fLAng2 = -11.0;

/* Wheel movement */
float fDistX, fDistY, fWheelCount=0, fSpeed = 1.0f, fSincro = 0.040;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/
void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	InitBumpmapMesh		(int Object);
void	CalculateGround		(void);
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
 *  Description     :  InitApplication() is called by KMShell to enable
 *						the user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{
	KMShellSetVideo	(TRUE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0xB0   /* Logo background translucency */
					 );

	KMShellSetBuffers(0, 		/* % Opaque (flushed)  */
					  0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					  0,		/* % ModVol Trans  */
					  0			/* % Punchthrough  */
					  );		

	KMPrint3DSetTextures();

	LoadTextures ();
	CreateContexts ();
 
	InitMeshes();

	InitBumpmapMesh (M_PLATESBUMP);
	InitBumpmapMesh (M_TIREBUMP);
	InitBumpmapMesh (M_GROUNDBUMP);
	
	CreateWindows ();
	
	LightDirection[0] = cos(fLAng2);
	LightDirection[1] = -0.5f;
	LightDirection[2] = sin(fLAng2);

	CalculateGround ();
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                            
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *						the user to finish the application                                                
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures();

	/* FREE TEXTURES */
	kmFreeTexture(&Tex[0]);
	kmFreeTexture(&Tex[1]);
	kmFreeTexture(&Tex[2]);
	kmFreeTexture(&Tex[3]);
	kmFreeTexture(&Tex[4]);
	kmFreeTexture(&Tex[5]);
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		syFree(KmVert[i]);
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
register	i, j;

	/* Wheel booble */
	fAng3 = (float)sin(fWheelCount) * 0.05f;

	for(i=0; i<NUM_MESHES; i++)
	{
		KMMatrixReset	  (&Matrx);

		/* Rotation */
		if(i!=M_GROUND && i!=M_GROUNDBUMP && i!=M_SUPPORT)	KMMatrixRotate    (&Matrx,  fAng1, fAng2, fAng3);
		
		else if (i == M_SUPPORT) KMMatrixRotate    (&Matrx,  0.0f, fAng2, 0.0f);

		/* Translation (Zoom) */
		KMMatrixTranslate (&Matrx, 0.0f, -fDist, fDist);  
   
		/* Vertices transformation */
		KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
										KmVert[i], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

		/* Smooth shading */
		if(i==M_RIM || i==M_SUPPORT)
		{
			KMLightSmoothShade (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, (KMVERTEX_03 *)KmVert[i],
								LightDirection, 0xFFFFFFFF, FALSE);
		}

	
		/* Environment map */
		if (i==M_PLATES || i==M_RIM || i==M_SUPPORT)
		{
			/* Reduce displacement to avoid 'crazy' env-map and add a horizontal displacement*/
			Matrx._41 = (fDistX+fDistY) * 0.2f; 
			Matrx._42 = 0.00f; 
			Matrx._43 = -5.00f;

			KMTransEnvironmentMap (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, 
											KmVert[i], 	CameraFrom, CameraTo, 0.0f, 
											1.0f, 1000000.0f, 30.0f*(PI/180.0f));
		}

		/* Calculation of smooth-shading and bump-map in one go */ 
		if (i==M_TIREBUMP)
		{
			KMBumpShade (&Matrx, Mesh[M_TIREBUMP].nNumVertex, pBump[M_TIREBUMP], Mesh[M_TIREBUMP].pNormals,
						KmVert[M_TIREBUMP], KmVert[M_TIRE],	LightDirection, BUMP_METHOD_TRANSLUCENT);
		}
	
		if (i==M_PLATESBUMP)
		{
  			KMBumpShade (&Matrx, Mesh[M_PLATESBUMP].nNumVertex, pBump[M_PLATESBUMP], Mesh[M_PLATESBUMP].pNormals,
						KmVert[M_PLATESBUMP], KmVert[M_PLATES],	LightDirection, BUMP_METHOD_HIGHLIGHT);
		}

		if (i==M_GROUNDBUMP)
		{
  			KMBumpShade (&Matrx, Mesh[M_GROUNDBUMP].nNumVertex, pBump[M_GROUNDBUMP], Mesh[M_GROUNDBUMP].pNormals,
						KmVert[M_GROUNDBUMP], NULL,	LightDirection, BUMP_METHOD_STANDARD);
		}

	
		/* Render strips */
		KMShellStrips (&StripHead[i],
						Mesh[i].nNumStrips, Mesh[i].pStripLength, 
						Mesh[i].pStrips, (KMVERTEX_03 *)KmVert[i]);

	} /* end of meshes loop */
  
	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	 }
   
  
	nFrame++;
  
	/* RenderScene OK */
	return TRUE;
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : KMPadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
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
			/* Reset values */
			fAng1 = 0.0f ; fAng2 = -1.2f; 
			fDist = 75.0f;
			fLAng2 = -11.0;
			LightDirection[0] = cos(fLAng2);
			LightDirection[1] = -0.5f;
			LightDirection[2] = sin (fLAng2);
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
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2);
			LightDirection[1] = -0.5f;
			LightDirection[2] = sin (fLAng2);
			fLAng2 -= 0.02f;
		}
		/* Wheel rotation */
		else  fAng2  += 0.05f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		/* Light rotation */
		if (IsAKey()) 
		{
			LightDirection[0] = cos(fLAng2);
			LightDirection[1] = -0.5f;
			LightDirection[2] = sin (fLAng2);
			fLAng2 += 0.02f;
		}
		/* Wheel rotation */
		else   fAng2  -= 0.05f;
	}


	/* A button */
	if (IsAKey())
	{
	}
	
	/* B button */
	if (IsBKey())
	{
	}
		
	/* X button */
	if (IsXKey())
	{
		/* Zoom in */
		if (fDist>-40) fDist -= 10.0f;
	}

	/* Y button */
	if (IsYKey())
	{
		/* Zooom out */
		if (fDist<250) fDist += 10.0f;
	}

	/* LEFT finger button */
	if (IsLFKey())
	{
		/* Wheel forward displacement */
		fAng1 += fSpeed * 0.1f;   
		fWheelCount+=0.2f;

		/* Ground displacement */
		fDistX += sin(fAng2) * fSpeed * fSincro;
		fDistY += cos(fAng2) * fSpeed * fSincro;

		if (fDistX> 10.0f) fDistX -= 10.0f;
		if (fDistY> 10.0f) fDistY -= 10.0f;

		CalculateGround ();
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		/* Wheel backward displacement */
		fAng1 -= fSpeed * 0.1f;  
		fWheelCount-=0.2f;

		/* Ground displacement */
		fDistX -= sin(fAng2) * fSpeed * fSincro;
		fDistY -= cos(fAng2) * fSpeed * fSincro;

		if (fDistX< -10.0f) fDistX += 10.0f;
		if (fDistY< -10.0f) fDistY += 10.0f;
		
		CalculateGround ();
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
 *  Description     : Sets initials values for meshes.           
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
			/* 
			 * UVs have been multiplied by a number to get a more wide
			 * range. It's neccessary for the tire model ONLY.
			 */
			if(i==M_TIREBUMP || i==M_TIRE)
			{
				(KmVert[i]+j)->fU = *(Mesh[i].pUV+j*2+0)*8.0f; 
				(KmVert[i]+j)->fV = *(Mesh[i].pUV+j*2+1); 

			}
			else
			{
				(KmVert[i]+j)->fU = (Mesh[i].pUV) ? *(Mesh[i].pUV+j*2+0) : 0.0f; 
				(KmVert[i]+j)->fV = (Mesh[i].pUV) ? *(Mesh[i].pUV+j*2+1) : 0.0f; 

			}
		
			(KmVert[i]+j)->uBaseRGB.dwPacked	= (i==M_PLATES )?0xFFFFFFFF:0xFFA0A0A0;
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
void InitBumpmapMesh (int Object)
{	
		/* 
		 * Local coordenates system for bump-mapping.
		 * 3 floats for Tanget axis and 3 floats for Binormal Axis
		 */
		pBump[Object] = (float *)syMalloc(Mesh[Object].nNumVertex*sizeof(float)*6); 
		
		/* 
		 * That is the function that calculates the local coordenate system
		 * for every single vertex. The information is stored in pBump[]
		 */
		KMBumpCalculateLocalCoords (pBump[Object], BUMP_COORDS_ANYDIRECTION,
									Mesh[Object].nNumVertex, Mesh[Object].pVertex, Mesh[Object].pNormals, Mesh[Object].pUV,
									Mesh[Object].nNumFaces, Mesh[Object].pFaces);	
	

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Converts 24 bits textures (stored in a *.htx file as static data) to 
 *                    a CLX 16bits format and loads them in video memory.
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
int i, j;
int nMaterial, nTexture, nTransTexture, nBumpTexture;


	for (i=0; i<NUM_MESHES; i++)
	{
	
		nMaterial = Mesh[i].nMaterial;
		
		if (nMaterial == -1) continue; /* No material defined for this object */
		
		nTexture = nTransTexture = nBumpTexture =-1;
		
		/* Looking for the texture that fits the difusse, opacity and bumpmap file names of the current material */
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
			if (strcmp(Material[nMaterial].sBumpFile, Texture[j].sTextureFileName) == 0) 
			{
				nBumpTexture = j;
			}
		}
		
		/* It's translucent */
		if(nTransTexture != -1)
		{
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, Texture[nTransTexture].pBitmapData, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
			continue;
		}
		
		/* It's a bumpmap */
		if(nBumpTexture != -1)
		{
		
			/* Bumpmap layer (ObjectName+10) */					
			KMTextureConvertAndLoad(&Tex[i], Texture[nBumpTexture].pBitmapData, NULL, 
						Texture[nBumpTexture].nWidth, Texture[nBumpTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_BUMP);
			
			continue;
		}
		
		if(nTexture != -1) /* It's standard opaque */
		{
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
			continue;
		}
	
	} /* i loop... carry on with the next material. */
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Loads textures and sets vertex contexts                           
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
	/* OPAQUE MATERIALS */

	/* Environment map */
	KMShellInitStripHead (&StripHead[M_RIM], &Tex[M_RIM], VC_OPAQUE | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_SUPPORT], &Tex[M_SUPPORT], VC_OPAQUE | VC_UVFLIP);
	
	/* The logo uses additive blending for 'highlight bumpmapping' */
	KMShellInitStripHead (&StripHead[M_PLATES], &Tex[M_PLATES], VC_ADDITIVE);
	

	/* Base texture for the wheel (opaque for 'translucent bumpmapping')*/
	KMShellInitStripHead (&StripHead[M_TIRE], &Tex[M_TIRE], VC_OPAQUE);

	/* Base texture for the ground (light-map blending for 'standard bumpmapping') */
	KMShellInitStripHead (&StripHead[M_GROUND], &Tex[M_GROUND],  VC_TRANS);
	kmChangeStripBlendingMode	(&StripHead[M_GROUND], KM_IMAGE_PARAM1, KM_DESTCOLOR, KM_ZERO);


	/* BUMP MATERIALS */

	/* Tire (translucent for 'translucent bumpmapping')*/
	KMShellInitStripHead (&StripHead[M_TIREBUMP], &Tex[M_TIREBUMP], VC_TRANS | VC_SPECULAR);

	/* Logo (opaque for 'highlight bumpmapping')*/
	KMShellInitStripHead (&StripHead[M_PLATESBUMP], &Tex[M_PLATESBUMP],  VC_OPAQUE | VC_SPECULAR | VC_DECALALPHA);

	/* Ground (opaque for 'standard bumpmapping')*/
	KMShellInitStripHead (&StripHead[M_GROUNDBUMP], &Tex[M_GROUNDBUMP], VC_OPAQUE | VC_SPECULAR | VC_DECALALPHA);

}

/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CalculateGround                                                       
 *  Inputs          : None                                                            
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Moves UVs of the ground to simulate that the ground is moving.                            
 *-------------------------------------------------------------------------------------*/
void CalculateGround (void)
{
	(KmVert[M_GROUNDBUMP]+0)->fU = (KmVert[M_GROUND]+0)->fU = 15.0f + fDistX; 
	(KmVert[M_GROUNDBUMP]+0)->fV = (KmVert[M_GROUND]+0)->fV = 15.0f + fDistY; 

	(KmVert[M_GROUNDBUMP]+1)->fU = (KmVert[M_GROUND]+1)->fU = 15.0f + fDistX; 
	(KmVert[M_GROUNDBUMP]+1)->fV = (KmVert[M_GROUND]+1)->fV =  0.0f + fDistY; 

	(KmVert[M_GROUNDBUMP]+2)->fU = (KmVert[M_GROUND]+2)->fU =  0.0f + fDistX; 
	(KmVert[M_GROUNDBUMP]+2)->fV = (KmVert[M_GROUND]+2)->fV =  0.0f + fDistY; 

	(KmVert[M_GROUNDBUMP]+3)->fU = (KmVert[M_GROUND]+3)->fU =  0.0f + fDistX; 
	(KmVert[M_GROUNDBUMP]+3)->fV = (KmVert[M_GROUND]+3)->fV = 15.0f + fDistY; 
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
	
	KMPrint3DSetWindow		(InfoWin, 0x80A00000, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 50.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput		(InfoWin, "(ANALOG PAD, TRIGGERS) Move Wheel\n");
	KMPrint3DWindowOutput		(InfoWin, "(A+CURSOR) Move Light\n");
	KMPrint3DWindowOutput		(InfoWin, "(X,Y) Zoom");

	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "WHEEL Bump-mapping    ", NULL);

 	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "WHEEL Bump-mapping  (1 of 3)",
"The bump-mapping technique is based on a 2D map that stores information about the roughness of a surface.\n\n");
 
 /* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "WHEEL Bump-mapping  (2 of 3)",
"The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
 be applied to the texture underneath, creating high-definition shading over a flat surface. \n\n");
 
  	/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "WHEEL Bump-mapping  (3 of 3)",
"This demo uses three different bump-mapping methods: standard for the ground,\
 translucent for the tire and highlight for the logo on the wheel.\n\n");

}
/*--------------------------------------------------------------------------------------*/
/*---------------------------------- END OF FILE ---------------------------------------*/
/*--------------------------------------------------------------------------------------*/





