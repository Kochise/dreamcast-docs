/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     DragonFly
  Date :     March 1999 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
  
  Description : PowerVR 3DStudio MAX plug-in example and motion-blur demo.

  Copyright : 1999 by VideoLogic Limited. All rights reserved.
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
extern Struct_Material  Material[];
extern Struct_Animation Animation[];
extern Struct_Texture   Texture[];

#define NUM_MESHES     25
#define NUM_MATERIALS  5
#define	NUM_TEXTURES   5

#ifndef PI
#define PI 3.1415
#endif

/* MESHES */
#define M_TORAX  0
#define M_HEAD  1
#define M_EYE2  2
#define M_EYE1  3
#define M_LEG1  4
#define M_LEG02  5
#define M_LEG03  6
#define M_LEG04  7
#define M_LEG05  8
#define M_LEG06  9
#define M_WING1  10
#define M_WING2  11
#define M_TAIL1  12
#define M_TAIL2  13
#define M_TAIL3  14
#define M_TAIL4  15
#define M_TAIL5  16
#define M_FIRE  17
#define M_SPHERE02  18
#define M_GEOSPHERE03  19
#define M_GEOSPHERE02  20
#define M_GEOSPHERE01  21
#define M_TEN03  22
#define M_FLASH  23
#define M_BACKGROUND  24

/*************************************************/
/*	Globals                                      */
/*************************************************/

#define MAX_NUM_SHOTS 100

#define RT_X 1024
#define RT_Y 512

/* texture surface */
KMSURFACEDESC		Tex[256], TexSurfaceDesc[10];		
		
/* Vertex context */
KMSTRIPHEAD 		StripHead[256], TexSurfaceStripHead[10];	

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -280.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 1000.0f};
km_vector LightDirection	= { 0.0f, -1.0f, 1.0f};

float   nFrame = 0; 
float	fXAng, fYAng, fZAng;

BOOL    bStart = FALSE, bNoAB = FALSE, bFire = FALSE;

float   fPosX=0.0f, fPosZ=0.0, fAngleY = 0.5f, fAngleX=0.0f, fHeight = 0.0f;
float	AnimCount = 0, Incr = 1.0f;

typedef struct Shot_struct_tag {
	int Active;
	int Time;
	float fPosX; 
	float fPosZ; 
	float fAngleY; 
	float fHeight;
} SHOT;

SHOT Shot[100];

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

void	InitMeshes			(void);
void 	LoadTextures 		(void);
void    InitMaterials       (void);
void	RenderObject		(int Object, KMSTRIPHEAD *pStripHead);
void	SetAnimM			(MATRIX *pMatrix, int i, unsigned Count);
void	CreateShot			(void);
void	DrawShots			(void);
void 	CreateWindows 		(void);

void 	InitTexturesForRender 	(void);
void 	DrawScreen 				(KMSTRIPHEAD *pStripHead, int SizeX, int SizeY);

int 	RenderSceneInScreenBuffer 	(void);
int 	RenderSceneInTexture 		(void);

void 	DrawFireBalls 				(float fX, float fY, float fZ);
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

	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );
					 

	KMShellSetBuffers (	0, 		    /* % Opaque  (flushed)      */
						0,			/* % ModVol Opaque */
						100,		/* % Translucent   */
						0,			/* % ModVol Trans  */
						0);	

	KMPrint3DSetTextures();
	
	LoadTextures ();
	
	InitMaterials ();
	
	InitTexturesForRender ();

	InitMeshes();
	
	CreateWindows();

	for(i=0; i<100; i++) Shot[i].Active = FALSE;

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
	/* Slow movemement of the dragonfly up and down */
	fHeight += 0.3f * sin ((float)nFrame/25.0f);

	/* Slow rectification of the dragonfly angle */
	if(fAngleX>0.0f) fAngleX -= 0.01f;
	if(fAngleX<0.0f) fAngleX += 0.01f;
	
	if(nFrame>0) RenderSceneInTexture ();
	
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
 *  Description     :  Draws everything in the scene plus the texture 
 *                     created in RenderSceneInTexture ()                                           
 *----------------------------------------------------------------------*/
int RenderSceneInScreenBuffer (void)
{
int				i, j;
MATRIX			Matrx;

	for (i=0; i<NUM_MESHES;i++) 
	{ 
		/* Don't transform these objects */
		if (i==M_FLASH || i==M_BACKGROUND) continue;
		
		/* Set the transformation matrix for animation. (Must be done before any tranformation) */
		SetAnimM (&Matrx, i,  (int)AnimCount-1);
		
		/* Special movement for legs */
		if (i>=M_LEG1 && i<=M_LEG06)
		   KMMatrixRotate(&Matrx, 0.0f, 0, PI/64 * sin((float)(nFrame*2)/(5.0f+i*2.0f)));
				
		/* Special movement for wings */
		if (i==M_WING1)
		   KMMatrixRotate(&Matrx, 0.0f, 0.0f, -PI/5.5 + PI/5.5 * cos((float)(nFrame)/1.0f));

		if (i==M_WING2)
			KMMatrixRotate(&Matrx, 0.0f, 0.0f,  PI/5.5 - PI/5.5 * cos((float)(nFrame)/1.0f));
			
		/* Rotate and translate the dragonfly */
		KMMatrixRotate(&Matrx, fAngleX, fAngleY, 0); 
				
		KMMatrixTranslate(&Matrx, fPosX, fHeight, 500.0f + fPosZ); 
	
		/* Transform all the vertices */
		KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
											KmVert[i], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));

		/*
		 * Environment map
		 */
		 if(i!=M_WING1 && i!=M_WING2)
		 {
			KMMatrixScale(&Matrx, 0.54f);
			/* Reduce displacement to avoid 'crazy' env-map */
			Matrx._41 *= 0.005f; 
			Matrx._42 *= 0.005f; 
			Matrx._43  = 0.005f; 
		
			KMTransEnvironmentMap (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, 
											KmVert[i], 	CameraFrom, CameraTo, 0.0f, 
											1.0f, 1000000.0f, 30.0f*(PI/180.0f));
		}
		
	}

	/* Background */
	KMShellBackground (&StripHead[10]);
	
	/* Draw the dragonfly */
	for (i=0; i<NUM_MESHES;i++) 
	{ 
		/* Don't transform these objects */
		if (i==M_FLASH || i==M_BACKGROUND) continue;
		
	
		if (i==M_WING1 || i==M_WING2)	RenderObject (i, &StripHead[0]);
		else							RenderObject (i, &StripHead[1]);

	}

	/* Draw all the shots in the current frame */
	DrawShots();  
	
	/* Draw the previous rendered image 
	 * Motion-blur.
	 */
	DrawScreen (&TexSurfaceStripHead[1], ScreenWidth, ScreenHeight);

	
	/* 
	 * Text windows.
	 */
	 if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
		KMPrint3DDisplayWindow(InfoWin);
	 }

	/*
	 * Animation frame-counter.
	 * There are two different animations, 
	 * one is the slow repose movement (from frame 0 to 100) 
	 * the other one is the 'fire' movement (from frame 100 to 150)
	 */
	if (!bFire)
	{
		AnimCount += Incr;
		if(AnimCount==0 || AnimCount==100) { Incr=-Incr;}
	}
	else
	{
		AnimCount++;
		if (AnimCount==150) {AnimCount=0; Incr=0.5f; bFire=FALSE;}
		if (AnimCount==108 || AnimCount==114 || AnimCount==120) CreateShot ();
	}

	return TRUE;
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneInTexture                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish the app.                                              
 *  Globals Used    :                                                  
 *  Description     :  Draws objects to be rendered in a texture.
 *  Note            :  Only draw motion-blur objects.                                                
 *----------------------------------------------------------------------*/
int RenderSceneInTexture (void)
{
int				i, j;
MATRIX			Matrx;
static float	Angle = 0.0f;

  
	/* Render again the Dragon-fly */
	for (i=0; i<NUM_MESHES;i++) 
	{ 
		if (i==M_FLASH || i==M_BACKGROUND) continue;
		if (i>=M_LEG1 && i<=M_LEG06) continue;
		
		RenderObject (i, &StripHead[0]);
	}
	
	/* Render again the shots */
	DrawShots();  

	/* Draw again the texture rendered in the last frame as a 
	 * translucent polygon on top. The scene is added again and again in 
	 * a recursive fashion, creating the motion-blur effect.
	 */
	DrawScreen (&TexSurfaceStripHead[0], ScreenWidth, ScreenHeight);
	
	/* Finish the pass (It was started in main() of KMShell.c) */
	kmEndPass(&VertexBufferDesc);

	/* Render in the previous texture the final result */
	kmRenderTexture(&TexSurfaceDesc[0], FALSE);

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
		fPosX=0.0f; fPosZ=0.0; fAngleY = 0.5f; fAngleX=0.0f; fHeight = 0.0f;
		if (Delay>10) bStart = !bStart;
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
		fHeight += 10.0f;
		fAngleX= 0.1f;
	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
		fHeight -= 10.0f;
		fAngleX = -0.1f;
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		fAngleY  += 0.1f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		fAngleY  -= 0.1f;
	}


	/* A button */
	if (IsAKey())
	{
		if (AnimCount<100) {AnimCount=100;Incr=0.5f;}
		bFire = TRUE;
		fAngleX = -0.1f;
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
		fPosX += 20.0f * sin(fAngleY);
		fPosZ += 20.0f * cos(fAngleY);

		fAngleX= 0.1f;
	}

	/* RIGHT finger button */
	if (IsRFKey())
	{
		fPosX -= 20.0f * sin(fAngleY);
		fPosZ -= 20.0f * cos(fAngleY);

		fAngleX = 0.1f;
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
unsigned int Color;

	/* Memory allocation for KmVert */
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03));
	}

	/* Setting UV values and colors for all the meshes reading materials or vertex colors*/
    for (i=0; i<NUM_MESHES;i++)
	{
		/* Default color */
		Color = 0xFFFFFFFF;
		
		/* Diffuse color from the material (if it exists) */
		if (Mesh[i].nMaterial!=-1) Color = Material[Mesh[i].nMaterial].nMatDiffuseColor;

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

			/* Colors */
			if (Mesh[i].pVertexColor!=NULL)
			{
				/* Vertex colors from 3DStudio MAX */
				(KmVert[i]+j)->uBaseRGB.dwPacked = *(Mesh[i].pVertexColor+j);
			}
			else
			{
				/* Material color (or default) */
				(KmVert[i]+j)->uBaseRGB.dwPacked = Color;
			}

			/* No specular color */
			(KmVert[i]+j)->uOffsetRGB.dwPacked	= 0x00000000;
		
		}     
	}

	/* Recalculating normals for a good env-mapping. 
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
	
		  *(Mesh[i].pNormals+j*3+0) = (fTempVert[0]+*(Mesh[i].pNormals+j*3+0)) * 0.5f;
		  *(Mesh[i].pNormals+j*3+1) = (fTempVert[1]+*(Mesh[i].pNormals+j*3+1)) * 0.5f;
		  *(Mesh[i].pNormals+j*3+2) = (fTempVert[2]+*(Mesh[i].pNormals+j*3+2)) * 0.5f;
		
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
int i, j;
int nMaterial, nTexture, nTransTexture;


	for (i=0; i<NUM_MATERIALS; i++)
	{
	
		nMaterial = i;
		
		nTexture = nTransTexture = -1;
		
		/* Looking for the texture that fits the difusse, opacity and reflection file names of the current material */
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
			if (strcmp(Material[nMaterial].sReflectionFile, Texture[j].sTextureFileName) == 0) 
			{
				nTexture = j;
			}
		}
		
		/* It's translucent */
		if(nTransTexture != -1)
		{
			KMTextureConvertAndLoad(&Tex[i],  Texture[nTexture].pBitmapData, Texture[nTransTexture].pBitmapData, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB4444);
		}
		else if(nTexture != -1) /* It's opaque */
		{

				KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
		}
	
	}
	
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
 
	/* Background */ 
	KMShellInitStripHead (&StripHead[10], &Tex[4], VC_OPAQUE);
	
	/* Wings */
	KMShellInitStripHead (&StripHead[0], &Tex[2], VC_TRANS);

	/* Reflection */
	KMShellInitStripHead (&StripHead[1], &Tex[0], VC_OPAQUE);

	/* Flash */
	KMShellInitStripHead (&StripHead[2], &Tex[3], VC_ADDITIVE);
	
	/* Flat texture */
	KMShellInitStripHead (&StripHead[3], &Tex[0], VC_OPAQUE | VC_NONTEXTURED);

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
					RT_X,					/*	IN	KMINT32			nWidth  */ 
					RT_Y,					/*	IN	KMINT32			nHeight  */
					nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
				);
				
		/* Recursive texture (translucent) */
		KMShellInitStripHead (&TexSurfaceStripHead[0], &TexSurfaceDesc[0], VC_TRANS);

		/* Texture to be on top of the main scane (additive) */
		KMShellInitStripHead (&TexSurfaceStripHead[1], &TexSurfaceDesc[0], VC_ADDITIVE);

	
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
 *  Function Name   : SetAnimM                                                    
 *  Inputs          :                                                            
 *  Outputs         :                                                             
 *  Returns         :                                                           
 *  Globals Used    :                                                                 
 *  Description     : To set a animation from 3DStudio MAX, feed the transformation matrix 
 *					  with the values exported by the PVRexp plug-in.
 *-------------------------------------------------------------------------------------*/
void SetAnimM (MATRIX *pMatrix, int i, unsigned Count)
{
	/* If the frame is out of range return the identity matrix */
	if (Count<0 || Count > Animation[i].nNumFrames) 
	{
		KMMatrixReset (pMatrix);
		return;
	}

	/*
	 *  Every chunk has 12 floats so, for example, the data for frame 32 of the object 2 starts at
	 *  (Animation[2].pData + 32*12 + 0) and carrys on for 12 floats.
	 *  Note: M_14 = 0, M_24 = 0, M_34 = 0 and M_44 =1 are fixed values.
	 */
	Count = Count*12;

    pMatrix->_11 = *(Animation[i].pData + Count + 0);
	pMatrix->_12 = *(Animation[i].pData + Count + 1);
	pMatrix->_13 = *(Animation[i].pData + Count + 2);
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = *(Animation[i].pData + Count + 3);
	pMatrix->_22 = *(Animation[i].pData + Count + 4);
	pMatrix->_23 = *(Animation[i].pData + Count + 5);
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = *(Animation[i].pData + Count + 6);
	pMatrix->_32 = *(Animation[i].pData + Count + 7); 
	pMatrix->_33 = *(Animation[i].pData + Count + 8);
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = *(Animation[i].pData + Count + 9); 
	pMatrix->_42 = *(Animation[i].pData + Count + 10);
	pMatrix->_43 = *(Animation[i].pData + Count + 11);
	pMatrix->_44 = 1.0f;

}
/*-------------------------------------------------------------------------------------
 *  Function Name   : DrawShots                                                    
 *  Inputs          : None                                                           
 *  Outputs         : None                                                            
 *  Returns         : None                                                         
 *  Globals Used    :                                                                 
 *  Description     : If a shot is on, moves and draws it.
 *-------------------------------------------------------------------------------------*/
void DrawShots (void)
{
register i;
float fX, fY;
MATRIX Matrix;

	for (i=0; i<MAX_NUM_SHOTS; i++)
	{
		/* If the shot is not active, don't draw it */
		if (Shot[i].Active==FALSE) continue;

		/* Limited time for displaying the same shot */
		Shot[i].Time++; 
		if(Shot[i].Time > 200) Shot[i].Active = FALSE;

		/* Update the position */
		Shot[i].fPosX -= 8.0f * sin(Shot[i].fAngleY);
		Shot[i].fPosZ -= 8.0f * cos(Shot[i].fAngleY); 
		Shot[i].fHeight -= 1.0f;

		/* Transform */
		KMMatrixReset (&Matrix);
		KMMatrixTranslate(&Matrix, Shot[i].fPosX, Shot[i].fHeight, 500.0f +Shot[i].fPosZ);
	 
		KMTransTransformProjectPerspective (&Matrix, Mesh[M_FLASH].nNumVertex, Mesh[M_FLASH].pVertex, 
											KmVert[M_FLASH], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
	
		/* Draw */
		RenderObject (M_FLASH, &StripHead[2]);

	}
}
/*-------------------------------------------------------------------------------------
 *  Function Name   : CreateShot                                                    
 *  Inputs          : None                                                           
 *  Outputs         : None                                                            
 *  Returns         : None                                                         
 *  Globals Used    :                                                                 
 *  Description     : This function is called just once to initialize the data.                     
 *-------------------------------------------------------------------------------------*/
void CreateShot (void)
{
register i;
float fX, fY;
MATRIX Matrix;

	for (i=0; i<MAX_NUM_SHOTS; i++)
	{ 
		/* Select the first one that is free */
		if (Shot[i].Active==TRUE) continue;

		/* Feed the structure with the current position data */
		Shot[i].Active	= TRUE;
		Shot[i].Time	= 0; 
		Shot[i].fAngleY = fAngleY;	
		Shot[i].fPosX	= fPosX - 35.0f * sin(Shot[i].fAngleY);
		Shot[i].fPosZ	= fPosZ - 35.0f * cos(Shot[i].fAngleY);
		Shot[i].fHeight = fHeight;

		/* done */
		break;
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
	
	KMPrint3DSetWindow		(InfoWin, 0x40A00000, 0xFFFFFFFF, 0.5f, 1.0f, 86.0f, 55.0f, 12.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_DEACTIVATE_TITLE );
	KMPrint3DWindowOutput	(InfoWin, "(ANALOG PAD + TRIGGERS) Move Dragonfly\n");
	KMPrint3DWindowOutput	(InfoWin, "(A) Fire button.\n");
	KMPrint3DWindowOutput	(InfoWin, "(START) Reset.\n");
	
	
	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "DRAGONFLY Motion Blur   ", NULL);

 	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "DRAGONFLY Motion Blur  (1 of 3)",
"This motion-blur effect has been created by rendering recursively to a texture.\n\n");
 
 /* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "DRAGONFLY Motion Blur  (2 of 3)",
"A target texture is created which contains the motion blurred object along with the previous texture contents\
 blended into it. This results in a recursive motion blur effect as previous renders of the motion blurred\
 object are slowly fading out due to the alpha component.\n\n");

/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "DRAGONFLY Motion Blur  (3 of 3)",
"This texture containing the motion blurred object is blended into the current frame containing the rest of the\
 3D scene by additive blending.\n\n");


}

/*----------------------------------------------------------------------*/
/*  Function Name   :  DrawScreen                                       */
/*  Inputs          :  *StripHead                                   */  
/*  Outputs         :  None                                             */
/*  Returns         :  None                                             */
/*  Globals Used    :  VertexBufferDesc                                 */
/*  Description     :  Draws a polygon that covers the screen.          */
/*  Note            :  The translucency of this polygon gives the number*/
/*                     of repetitions in the motion-bur effect.         */
/*----------------------------------------------------------------------*/
void DrawScreen (KMSTRIPHEAD *pStripHead, int SizeX, int SizeY)
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
	V[k].uBaseRGB.dwPacked	 = 0xE0FFFFFF; /* Set translucency here */
	V[k].uOffsetRGB.dwPacked = 0x00000000;
	}

    /* Position */
    V[0].fX	= 0.0f;
	V[0].fY	= SizeY;

	V[1].fX	= 0.0f;
	V[1].fY	= 0.0f;

	V[2].fX	= SizeX;
	V[2].fY	= SizeY;

	V[3].fX	= SizeX;
	V[3].fY	= 0.0f;

	V[0].u.fZ =  0.0001;
	V[1].u.fZ =  0.0001;
	V[2].u.fZ =  0.0001;
	V[3].u.fZ =  0.0001;

	/* UVs */
	V[0].fU	=  0.0f;
	V[0].fV	=  480.0f/RT_Y;

	V[1].fU	=  0.0f;
	V[1].fV	=  0.0f;

	V[2].fU	=  640.0f/RT_X;
	V[2].fV	=  480.0f/RT_Y;

    V[3].fU	=  640.0f/RT_X;
	V[3].fV	=  0.0f;

	/* Strip start */
	kmStartStrip(pVertexBufferDesc, pStripHead);

	/* Setting vertices */
	for(i = 0; i<4; i++)
	{
		kmSetVertex (pVertexBufferDesc, (KMVERTEX_03 *)(&V[i]), KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
	}

    /* Strip end */
    kmEndStrip (pVertexBufferDesc);
}

/*-----------------------------------------------------------------------------------------*
 * END OF FILE
 *-----------------------------------------------------------------------------------------*/