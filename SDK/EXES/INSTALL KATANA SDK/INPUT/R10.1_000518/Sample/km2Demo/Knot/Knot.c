/*****************************************************************************
  Name :     Knot 
  Author:	 Carlos Sarria
  Date :     August 1998 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : BumpMap demo.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <math.h>

#include "KMTools.h"
#include "KMShell.h"

#define	  BUMP_START 10
 
/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Mesh     Mesh[];
extern Struct_Texture  Texture[];

#define NUM_MESHES     1
#define NUM_TEXTURES   1

/* MESHES */
#define M_KNOT  0

/*************************************************/
/*	Globals                                      */
/*************************************************/

KMSURFACEDESC		Tex[256];				/* texture surface */
KMSTRIPHEAD			StripHead[256];		/* Vertex context */
KMVERTEX_03			*KmVert[256];			/* Vertex pointers*/

float *pBump[256];

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 100.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

unsigned nFrame = 500;

BOOL bStart = FALSE;

float fAng1 = 0.0f , fAng2 = 0.0f, fAng3 = 0.0f, fZ;
float fLAng1 = -1.0 , fLAng2 = 1.0;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/
void	InitMeshes			(void);
void	InitMaterials		(void);
void	RenderBumpmap		(MATRIX *Matrx, int Object);
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
 *  Description     :   InitApplication() is called by KMShell to enable
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

	InitMaterials ();

	InitMeshes();
	
	CreateWindows ();
}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                  
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                            
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *					  the user to finish the application                                                
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	 KMPrint3DReleaseTextures ();

	/* FREE TEXTURES */
	kmFreeTexture(&Tex[M_KNOT]);
	kmFreeTexture(&Tex[M_KNOT+BUMP_START]);
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		/* Object */
		free(KmVert[i]); 
		
		/* Bump-map */ 
		free(KmVert[i+BUMP_START]);
		
		free(pBump[i]);
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
static float	fAngleOffset = 0.0f, fLightOffset = 0.0f;
extern unsigned Pad;

	/* Roll-alone stuff */
	if (bStart==FALSE)
	{
		if ((nFrame%1000) < 300) fAngleOffset++;
		else					 fLightOffset++;

		fLAng1 = cos(fLightOffset/60.0f) * 1.5f;
		fLAng2 = sin(fLightOffset/30.0f) * 1.5f;

		fAng1 = cos(fAngleOffset/200.0f) * PI*2.0f;
		fAng2 = sin(fAngleOffset/200.0f) * PI*2.0f;
	}

   LightDirection[0] = fLAng2;
   LightDirection[1] = fLAng1;
   LightDirection[2] = 1.0f;

   KMMatrixReset(&Matrx);

   if (bStart==FALSE)
   {
	   fAng1 += 0.01f;
	   fAng2 += 0.01f;
   }
  
   /* Transformations */
   KMMatrixRotate    (&Matrx, 0.0f, fAng1, fAng2);
   KMMatrixTranslate (&Matrx, 0.0f, 0.0f, 200.0f);  

   /* Draws the bumpmap object */
   RenderBumpmap   (&Matrx, M_KNOT);
     
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
 *  Function Name   : PadControl()                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : PadControl() is called by KMShell every frame to enable
 *					  the user to read the joystick.                                
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
	
	
	/* Roll-alone */
	if (!bStart) return TRUE;
	
	

	/* UP ANALOG-PAD */
	if (AnalogPadY()<-64)
	{
  		if (IsAKey())  fLAng1 -= 0.1f;
		else           fAng1 += 0.05f;
	}

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		if (IsAKey())  fLAng1 += 0.1f;
		else           fAng1  -= 0.05f;
	}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
		if (IsAKey()) fLAng2 += 0.1f;
		else          fAng2  += 0.05f;

	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
		if (IsAKey()) fLAng2 -= 0.1f;
		else          fAng2  -= 0.05f;
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


	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		/* Object */
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03)); 
		
		/* Bump-map */ 
		KmVert[i+BUMP_START] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03)); 
	
		/* 
		 * Local coordenates system for bump-mapping.
		 * 3 floats for Tanget axis, 3 floats for Binormal Axis
		 */
		pBump[i] = (float *)syMalloc(Mesh[i].nNumVertex*sizeof(float)*6); 
	}


	/* Setting UV values and colors for all the meshes */
    for (j=0; j<Mesh[M_KNOT].nNumVertex; j++)
	{
		/* 
		 * UVs have been multiplied by a number to get a more wide
		 * range. It's neccessary for this model ONLY.
		 */
		(KmVert[M_KNOT]+j)->fU = *(Mesh[M_KNOT].pUV+j*2+0)*18.0f; 
        (KmVert[M_KNOT]+j)->fV = *(Mesh[M_KNOT].pUV+j*2+1)*2.0f; 

		(KmVert[M_KNOT+BUMP_START]+j)->fU = *(Mesh[M_KNOT].pUV+j*2+0)*18.0f; 
        (KmVert[M_KNOT+BUMP_START]+j)->fV = *(Mesh[M_KNOT].pUV+j*2+1)*2.0f; 
		
		(KmVert[M_KNOT]+j)->uBaseRGB.dwPacked	= 0xFFFFFFFF;
		(KmVert[M_KNOT]+j)->uOffsetRGB.dwPacked	= 0xFF000000;
		
	} 

	/* 
	 * That is the function that calculates the local coordenate system
	 * for every single vertex. The information is stored in pBump[]
	 */
	KMBumpCalculateLocalCoords (pBump[M_KNOT], BUMP_COORDS_ANYDIRECTION,
									Mesh[M_KNOT].nNumVertex, Mesh[M_KNOT].pVertex, Mesh[M_KNOT].pNormals,  Mesh[M_KNOT].pUV, 
								  	Mesh[M_KNOT].nNumFaces, Mesh[M_KNOT].pFaces);	
	
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : InitMaterials                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Loads textures and sets vertex contexts                           
 *-------------------------------------------------------------------------------------*/
void InitMaterials (void)
{
	/* OPAQUE MATERIALS (Texture 0) */
	KMTextureConvertAndLoad(&Tex[0], Texture[0].pBitmapData, NULL, 
						Texture[0].nWidth, Texture[0].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
	KMShellInitStripHead (&StripHead[M_KNOT], &Tex[0], VC_OPAQUE | VC_UVFLIP);


	/* BUMP MATERIALS (Texture 1) */
	KMTextureConvertAndLoad(&Tex[1], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight,KM_TEXTURE_TWIDDLED | KM_TEXTURE_BUMP );
	KMShellInitStripHead (&StripHead[M_KNOT+BUMP_START], &Tex[1], VC_TRANS | VC_SPECULAR);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : RenderBumpmap                                                       
 *  Inputs          : Object                                                             
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Calculates bumpmap angles (per vertex) on the fly and draws the base
 *                    and the bumpmap layers.                              
 *-------------------------------------------------------------------------------------*/
void RenderBumpmap (MATRIX *Matrix, int Object)
{
register i;

	/* Transforming our object */
	KMTransTransformProjectPerspective (Matrix, Mesh[Object].nNumVertex, Mesh[Object].pVertex, 
										KmVert[Object], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

	/* Copiying the information into the bumpmap object */
	for (i=0; i<Mesh[Object].nNumVertex; i++)
	{
		(KmVert[Object+BUMP_START]+i)->fX   = (KmVert[Object]+i)->fX;
		(KmVert[Object+BUMP_START]+i)->fY   = (KmVert[Object]+i)->fY;
		(KmVert[Object+BUMP_START]+i)->u.fZ = (KmVert[Object]+i)->u.fZ; 
	}

	/* Calculation of smooth-shading and bump-map in one go */ 
	KMBumpShade (Matrix, Mesh[Object].nNumVertex, pBump[Object], Mesh[Object].pNormals,
				KmVert[Object+BUMP_START], KmVert[Object],	LightDirection, BUMP_METHOD_TRANSLUCENT);
				
	
	/* Smooth shaded solid object */
	KMShellStrips (&StripHead[Object],
					Mesh[Object].nNumStrips, Mesh[Object].pStripLength, 
					Mesh[Object].pStrips, (KMVERTEX_03 *)KmVert[Object]);

	/* Bumpmap */
	KMShellStrips (&StripHead[Object+BUMP_START],
					Mesh[Object].nNumStrips, Mesh[Object].pStripLength, 
					Mesh[Object].pStrips, (KMVERTEX_03 *)KmVert[Object+BUMP_START]);


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
	InfoWin = KMPrint3DCreateWindow (50, 4);
	
	KMPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput		(InfoWin, "(START) rolling demo/interactive\n");
	KMPrint3DWindowOutput		(InfoWin, "(A + ANALOG PAD) To move light\n");
	KMPrint3DWindowOutput		(InfoWin, "(ANALOG PAD) To move object\n");

	/* Text Windows */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "KNOT Bump-mapping   ", NULL);

	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "KNOT Bump-mapping  (1 of 4) ", "\
The bump mapping technique is based on a 2D map that stores \
information about the roughness of a surface. \
The render engine scans this map pixel by pixel and calculates the corresponding intensity value that will \
be applied on the texture underneath, creating high-definition shading over a flat surface.\n");

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "KNOT Bump-mapping  (2 of 4) ", "\
PowerVR Series2 technology uses a special bump map format that is optimised for its hardware.  \
Instead of storing coloured pixels, a couple of polar co-ordinates are stored in each pixel.\n");

	/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "KNOT Bump-mapping  (3 of 4) ", "\
These co-ordinates (S and R) are the elevation and azimuth of the normal vector in each point of the texture surface. \
These values are packed together in a 16-bit format where 8 bits express R and 8 bits express S.\n");

	/* Window 4 */
	TWin[4] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 40, "KNOT Bump-mapping  (4 of 4) ", "\
Once you have mapped the texture onto your object, the light source vector \
has to be expressed in a local co-ordinate system for each vertex and passed to the hardware as the specular colour of that vertex.\n");

}
/*---------------------------- END OF FILE --------------------------------*/






