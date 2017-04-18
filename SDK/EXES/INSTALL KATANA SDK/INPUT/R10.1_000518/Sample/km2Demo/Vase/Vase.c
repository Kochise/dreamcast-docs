/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     Vase
  Date :     Nov 1998 (Updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
 
  Description : Accumulation buffer (a sort of multitexture) demo.

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

#define NUM_MESHES     4
#define NUM_TEXTURES   4
#define NUM_MATERIALS  3

/* MESHES */
#define M_GLASS  0
#define M_SILVER  1
#define M_GLASSREFLECT  2
#define M_BACKGROUND  3


/*************************************************/
/*	Globals                                      */
/*************************************************/

/* texture surface */
KMSURFACEDESC		Tex[256];		
		
/* Vertex context */
KMSTRIPHEAD	StripHead[256];		

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

/* Special normals for EnvironmentMap 
 * that work for flat surfaces.  
 * They are calculated in InitMeshes()
 */
float	*pEnvNormals[256];

extern KMVERTEXBUFFDESC VertexBufferDesc;	/* is defined in KMShell.c */

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -280.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 1000.0f};
km_vector LightDirection	= { 0.0f, -1.0f, 1.0f};

float   nFrame = 0; 
float	fXAng, fYAng, fZAng;

BOOL    bStart = FALSE, bNoAB = FALSE;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void 	CreateWindows 		(void);
void	RenderObject		(int Object, KMSTRIPHEAD *StripHead);

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
 *					     the user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{

	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x50   /* Logo background translucency */
					 );

	KMShellSetBuffers (	0, 		/* % Opaque (flushed)   */
						0,		/* % ModVol Opaque */
						50,		/* % Translucent   */
						0,		/* % ModVol Trans  */
						0);	

	KMPrint3DSetTextures();

	LoadTextures ();
	CreateContexts ();
	
	CreateWindows ();

	InitMeshes();

}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                          
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *					     the user to finish the application                                                
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures();
	
	/* FREE TEXTURES */
	for (i=0; i<NUM_TEXTURES; i++)
	{
		kmFreeTexture(&Tex[i]);
	}
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		syFree(KmVert[i]);
		syFree(pEnvNormals[i]);
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
static float Angle = 0.0f;

   KMShellBackground (&StripHead[M_BACKGROUND]);
   
   /* Roll-alone */
	if(bStart==FALSE)
	{
		fXAng += PI/200.0f;
		fYAng += PI/300.0f;
	}

	for (i=0; i<NUM_MESHES;i++) 
	{ 
	
		if (i==M_BACKGROUND) continue;

		KMMatrixReset(&Matrx);
		KMMatrixRotate(&Matrx, fXAng, fYAng, fZAng);
		
		KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
											KmVert[i], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));

		if (i!=M_GLASS)
		{
			KMTransEnvironmentMap (&Matrx, Mesh[i].nNumVertex, (i!=M_GLASSREFLECT) ? Mesh[i].pNormals : pEnvNormals[i], 
											KmVert[i], 	CameraFrom, CameraTo, 0.0f, 
											1.0f, 1000000.0f, 30.0f*(PI/180.0f));

		}

		if (i!=M_GLASSREFLECT)
		{
			KMLightSmoothShade (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, (KMVERTEX_03 *)KmVert[i],
								LightDirection, 0xFFFFFFFF, FALSE);
		}
					
	}
	
	/* Vase cylinder 4444 texture */
	RenderObject (M_GLASS, &StripHead[M_GLASS]);

	/* Vase metallic base */
	RenderObject (M_SILVER, &StripHead[M_SILVER]);

	/* 
	 * Special blend environtment map over vase cylinder 
	 * that is displayed where a pixel is opaque only.
	 */	
	RenderObject (M_GLASSREFLECT, &StripHead[20]); 	/* M_GLASSREFLECT coz UVs change every frame (environment-map) */
	RenderObject (M_GLASS, &StripHead[21]); 		/* M_GLASS coz we need fixed UVs to cut-out the previous pass */
	RenderObject (M_GLASS, &StripHead[22]); 		/* Flush polygons */
		

	/* 
     * Text windows.
     */
	if(dwDisplayWins)
	{
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
	}
  
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
 *  Description     : PadControl() is called by KMShell to enable
 *					     the user to control the joystick                    
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	nDelay = 0;

	nDelay++;

	/* START */
	if (IsSTARTKey())
	{
		if (nDelay>10) bStart = !bStart;
		nDelay = 0;
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

	/* No controler until START is pressed */
	if (bStart == FALSE) return TRUE;
	
	/* UP */
	if (AnalogPadY()<-64)
	{
		fXAng += 0.05f;
	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
		fXAng  -= 0.05f;
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		fYAng  += 0.05f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		fYAng  -= 0.05f;
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
register unsigned i,j, k=0;
float fTempVert[3], fModule;

	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03));
		pEnvNormals[i] = (float *)syMalloc(Mesh[i].nNumVertex*sizeof(float)*3);
	}

	/* Setting UV values and colors for all the meshes */
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
            (KmVert[i]+j)->fU	= *(Mesh[i].pUV+j*2+0);
            (KmVert[i]+j)->fV	= *(Mesh[i].pUV+j*2+1);

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0x80FFFFFF;
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0xFF000000;
		
		}     
	}

	/* Creating specials normals for flat surfaces. 
	 * These are the media between the normal and the normalized vector
	 * from the origin to the vertex.
	 */
    for (i=0; i<NUM_MESHES;i++)
	{
		for (j=0; j<Mesh[i].nNumVertex; j++)
		{
          fTempVert[0] = *(Mesh[i].pVertex+j*3+0) - Mesh[i].fCenter[0];
		  fTempVert[1] = *(Mesh[i].pVertex+j*3+1) - Mesh[i].fCenter[1];
		  fTempVert[2] = *(Mesh[i].pVertex+j*3+2) - Mesh[i].fCenter[2];

		  if (fTempVert[0] || fTempVert[1] || fTempVert[2])
		  {
			fModule = 1.0f / sqrt (fTempVert[0]*fTempVert[0]+ fTempVert[1]*fTempVert[1] +fTempVert[2]*fTempVert[2]);
			fTempVert[0] *= fModule;
			fTempVert[1] *= fModule;
			fTempVert[2] *= fModule;
		  }

		  *(pEnvNormals[i]+j*3+0) = (fTempVert[0]+*(Mesh[i].pNormals+j*3+0)) * 0.5f;
		  *(pEnvNormals[i]+j*3+1) = (fTempVert[1]+*(Mesh[i].pNormals+j*3+1)) * 0.5f;
		  *(pEnvNormals[i]+j*3+2) = (fTempVert[2]+*(Mesh[i].pNormals+j*3+2)) * 0.5f;
		
		}     
	}
 
  
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Convert 24bits Bitmap format to 16bits hardware format and load it 
 *                    in video memory.                    
 *-------------------------------------------------------------------------------------*/
void LoadTextures (void)
{
int i, j;
int nMaterial, nTexture, nTransTexture;


	for (i=0; i<NUM_MESHES; i++)
	{
	
		nMaterial = Mesh[i].nMaterial;
		
		if (nMaterial == -1) continue; /* No material defined for this object */
		
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
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, Texture[nTransTexture].pBitmapData, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
		}
		else /* It's opaque */
		{
			KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);

		}
	
	}
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CreateContexts                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : All the contexts for this application.       
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
 
	/* STANDARD MIPMAP */ 
	KMShellInitStripHead (&StripHead[M_BACKGROUND],   &Tex[M_BACKGROUND], 	VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_GLASS], 		  &Tex[M_GLASS],		VC_TRANS);
	KMShellInitStripHead (&StripHead[M_SILVER], 	  &Tex[M_SILVER], 		VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_GLASSREFLECT], &Tex[M_GLASSREFLECT], VC_TRANS | VC_CULLING);

	/* 
	 * ACCUMULATION BUFFER
	 */
	/* This is the environment-map texture */
	KMShellInitStripHead (&StripHead[20], &Tex[M_GLASSREFLECT], VC_TRANS | VC_CULLING);
	kmChangeStripSRCSelect		(&StripHead[20], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[20], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[20], KM_IMAGE_PARAM1, KM_ONE, KM_ZERO);
 

	/*  This is the flowers texture.
	 *  In this case we use the alpha chanel just to cut out 
	 *  the environment-map.
	 */
	KMShellInitStripHead (&StripHead[21], &Tex[M_GLASS], VC_TRANS | VC_CULLING);
	kmChangeStripSRCSelect		(&StripHead[21], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[21], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[21], KM_IMAGE_PARAM1, KM_INVSRCALPHA, KM_SRCALPHA);
	

	/* The final map will be a translucent one */
	KMShellInitStripHead (&StripHead[22], NULL, VC_TRANS | VC_CULLING);
	kmChangeStripSRCSelect		(&StripHead[22], KM_IMAGE_PARAM1, 1);
	kmChangeStripDSTSelect		(&StripHead[22], KM_IMAGE_PARAM1, 0);
	kmChangeStripBlendingMode	(&StripHead[22], KM_IMAGE_PARAM1, KM_SRCALPHA, KM_INVSRCALPHA);

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
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "VASE Accumulation buffer  ", NULL);


	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "VASE Accumulation buffer (1 of 2) ",
"This demo shows one of the several uses of the accumulation buffer for blended polygons.\n\n \
The reflections on the cylidrical surface are applied only where the pixels in the 4444 base texture are opaque.\n\n\
(START) Rolling demo/Interactive\n(DIGITAL PAD) Move vase.\n\n");


	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 50, "VASE Accumulation buffer (2 of 2) ",
"The first pass in the accumulation buffer defines a 'full' environment-map cylinder (with UVs changing every frame).\n\
The second pass adds the translucent channel that comes from the base texture (4444) cutting-out the previous pass.\n\
The last pass just flushes' polygons used to draw the result stored in the accumulation buffer.\n\n");

}
