/*****************************************************************************
  Name :     CheapBump 
  Author:	 Carlos Sarria
  Date :     April 1999 
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : Easy, fast but limited BumpMapping method.

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

#define NUM_MESHES     3
#define NUM_MATERIALS  3
#define NUM_TEXTURES   4

/* MESHES */
#define M_LIGHT  0
#define M_OBJECT  1
#define M_BACKGROUND  2

/*************************************************/
/*	Globals                                      */
/*************************************************/

KMSURFACEDESC		Tex[256];				/* texture surface */
KMSTRIPHEAD			StripHead[256];		/* Vertex context */ 
KMVERTEX_03			*KmVert[256];			/* Vertex pointers*/

/* Camera data */
int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -200.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 0.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

/* Generic data */
unsigned nFrame = 0, nCurrentTexture = 0, CreationMethod = 1, CurrentObject = 2;

/* Object angles */
float fAng1 = 0.0f , fAng2 = 0.0f, fAng3 = 0.0f;

/* Camera distance */
float fDist = 75.0f;

/* Light angle */
float fLAng1 = -0.5f, fLAng2 = 1.0f;

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
					 0xA0   /* Logo background translucency */
					 );

	KMShellSetBuffers(0, 		/* % Opaque (flushed) */
					  0,		/* % ModVol Opaque */
					  100,		/* % Translucent   */
					  0,		/* % ModVol Trans  */
					  0			/* % Punchthrough  */
					  );		

	KMPrint3DSetTextures();

	LoadTextures ();
	CreateContexts ();
 
	InitMeshes();
	
	CreateWindows ();
	
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
 *  Description     :  QuitApplication is called by KMShell to enable the
 *						user to finish the application                                             
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	 KMPrint3DReleaseTextures ();
	 
	 kmFreeTexture(&Tex[M_OBJECT]);
	 kmFreeTexture(&Tex[M_OBJECT+10]);
	 kmFreeTexture(&Tex[M_LIGHT]);
	 kmFreeTexture(&Tex[M_BACKGROUND]);
	 
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
int			i, j;
km_vector   Light;

	KMShellBackground(&StripHead[M_BACKGROUND]);
	

  	KMMatrixReset	  (&Matrx);
	KMMatrixRotate    (&Matrx,  0.0f, fAng1, fAng2);
	KMMatrixTranslate (&Matrx, 0.0f, 0.0f, fDist);  
	
	/* Vertices transformation */
	KMTransTransformProjectPerspective (&Matrx, Mesh[M_OBJECT].nNumVertex, Mesh[M_OBJECT].pVertex, 
										KmVert[M_OBJECT], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
	
	/* Calculation of smooth-shading */ 
	KMLightSmoothShade (&Matrx, Mesh[M_OBJECT].nNumVertex, Mesh[M_OBJECT].pNormals, (KMVERTEX_03 *)KmVert[M_OBJECT],
								LightDirection, 0xC0FFFFFF, FALSE);

	/* Render strips (Base texture) */
	KMShellStrips (&StripHead[M_OBJECT],
						Mesh[M_OBJECT].nNumStrips, Mesh[M_OBJECT].pStripLength, 
						Mesh[M_OBJECT].pStrips, (KMVERTEX_03 *)KmVert[M_OBJECT]);
					
	/* calculate 'cheap' bumpmap on the fly */
	 KMCheapBumpShade(&Matrx,  Mesh[M_OBJECT].nNumVertex, KmVert[M_OBJECT], LightDirection, BUMP_METHOD_TRANSLUCENT);
	
	KMShellStrips (&StripHead[M_OBJECT + 10],
						Mesh[M_OBJECT].nNumStrips, Mesh[M_OBJECT].pStripLength, 
						Mesh[M_OBJECT].pStrips, (KMVERTEX_03 *)KmVert[M_OBJECT]);

	/* Draw the light spot */
	KMMatrixReset	  (&Matrx);

	KMMatrixTranslate (&Matrx, -LightDirection[0] * 120.0f, -LightDirection[1] * 120.0f, fDist - LightDirection[2] * 120.0f);  


	KMTransTransformProjectPerspective (&Matrx, Mesh[M_LIGHT].nNumVertex, Mesh[M_LIGHT].pVertex, 
										KmVert[M_LIGHT], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));

	KMShellStrips (&StripHead[M_LIGHT],
					Mesh[M_LIGHT].nNumStrips, Mesh[M_LIGHT].pStripLength, 
					Mesh[M_LIGHT].pStrips, (KMVERTEX_03 *)KmVert[M_LIGHT]);

  
	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	 }
   
	 
	/* If the light is close to 0 display a warning message */	
	Light[0] = -LightDirection[0];
	Light[1] = -LightDirection[1];
	Light[2] = -LightDirection[2];

	KMMatrixNormalize (Light);

	if (sqrt(Light[0]*Light[0] + Light[1]*Light[1]) < 0.1f)
		KMPrint3D (60.0f, 93.75f, 0.6f, 0xFFFFFF00, "WRONG LIGHTING AREA");

	
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
			if(i==M_LIGHT)
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
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB1555);
			continue;
		}
		
		/* It's a bumpmap */
		if(nBumpTexture != -1)
		{
			/* Opaque layer */
			if (nTexture != -1)
			{
				KMTextureConvertAndLoad(&Tex[i],  Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
			}
	
			/* Bumpmap layer (ObjectName+10) */					
			KMTextureConvertAndLoad(&Tex[i+10], Texture[nBumpTexture].pBitmapData, NULL, 
						Texture[nBumpTexture].nWidth, Texture[nBumpTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_BUMP);
			
			continue;
		}
		
		else /* It's standard opaque */
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
 *  Description     : Create all the contexts to be used by the application.                           
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{

	/* BUMP MATERIALS */
	KMShellInitStripHead (&StripHead[M_OBJECT + 10], &Tex[M_OBJECT + 10], VC_TRANS | VC_SPECULAR);

	/* OPAQUE MATERIALS */
	KMShellInitStripHead (&StripHead[M_OBJECT],  &Tex[1], VC_OPAQUE);

	KMShellInitStripHead (&StripHead[M_BACKGROUND],  &Tex[M_BACKGROUND], VC_OPAQUE);

	KMShellInitStripHead (&StripHead[M_LIGHT],  &Tex[M_LIGHT], VC_ADDITIVE);

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
	/* Info Window */
	InfoWin = KMPrint3DCreateWindow (50, 3);
	
	KMPrint3DSetWindow		(InfoWin, 0x602030FF, 0xFFFFFFFF, 0.5f, 1.0f, 87.0f, 45.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput	(InfoWin, "(A+ANALOG PAD) To move light\n");
	KMPrint3DWindowOutput	(InfoWin, "(ANALOG PAD) To move object\n");
	KMPrint3DWindowOutput	(InfoWin, "(START) Reset");

	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "CHEAPBUMP Bump-map  ", NULL);
	
	/* Adjustement only once, and no automatic resize */
	KMPrint3DSetWindowFlags	(TWin[0], PRINT3D_DEACTIVATE_WIN);
	KMPrint3DAdjustWindowSize (TWin[0], 0);


	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "CHEAPBUMP Bump-mapping (1 of 3) ", "\
This method doesn't use a local co-ordinate system per vertex and is very simple and fast. \
It doesn't look as good as the Tangent Space methods but for many applications it works fine. \
This method calculates only one bump map angle for all the vertices in an object, so the bump map effect \
will be the same over the whole mesh.\n");

	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "CHEAPBUMP Bump-mapping (2 of 3) ", "\
K1, K2 and K3 are fixed and Q is calculated as the angle between the XY projection of the light vector and \
the XY projection of an upright axis that has been transformed with the object transformation matrix.\n");

	/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "CHEAPBUMP Bump-mapping (3 of 3) ", "\
One of the problems of this method is that the bump mapping effect jumps very quickly when the light \
projection is very close to (0, 0). Another limitation is that this method only works with a uniform mapping that looks upright and without flipped surfaces. \
A standard planar (non-flipped), spherical or cylindrical mapping works fine.\n");

}
/*--------------------------------------------------------------------------------------*/
/*---------------------------------- END OF FILE ---------------------------------------*/
/*--------------------------------------------------------------------------------------*/





