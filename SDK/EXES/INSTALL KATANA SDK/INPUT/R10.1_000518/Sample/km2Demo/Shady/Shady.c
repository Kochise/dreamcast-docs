/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     Shaddy
  Date :     March 1999 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
  
  Description : Projected polygons flat shadow.
  Notes:        This demo shows how to 'presort' flat-shadow projected polygons
                to avoid overlapping artifacts.
                
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
extern Struct_Texture   Texture[];

#define NUM_MESHES     3
#define	NUM_TEXTURES   3

#ifndef PI
#define PI 3.1415
#endif

/* MESHES */
#define M_GROUND  0
#define M_KNOT    1
#define M_LIGHT   2

#define M_DUMMY   3

/* SHADOW MODE */
#define SHADOW_ZBIAS_VERTICES      0
#define SHADOW_ZBIAS_POLYGONS      1
#define SHADOW_ACCUMULATION_BUFFER 2

/*************************************************/
/*	Globals                                      */
/*************************************************/

#define RT_SIZE 256

/* texture surface */
KMSURFACEDESC		Tex[256];		
		
/* Vertex context */
KMSTRIPHEAD 		StripHead[256];	

/* Vertex pointers*/
KMVERTEX_03			*KmVert[256];		

int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 500.0f, -500.0f};
km_vector CameraTo			= { 0.0f, 0.0f, -100.0f};
km_vector LightDirection	= { 0.0f, -1.0f, 1.0f};

float   nFrame = 0; 
float	fXAng, fYAng, fZAng;

BOOL    bStart = FALSE, bNoAB = FALSE, bFire = FALSE;
DWORD   nShadowMode = SHADOW_ZBIAS_VERTICES;

float   fPosX=0.0f, fPosZ=0.0, fAngleY = 0.5f, fAngleX=0.0f, fHeight = 0.0f;
float	fLAng1 = -1.0f, fLAng2 = 0.5f;

/* Memory to hold the transformed knot */
float   *pTransformedVertex;

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

void	InitMeshes					(int nObject);
void 	InitShadow 					(int nObject);
void 	LoadTextures 				(void);
void    InitMaterials       		(void);
void	RenderObject				(int Object, KMSTRIPHEAD *pStripHead);
void 	CreateWindows 				(void);

void 	ProjectAndRenderFlatShadow	(MATRIX *Matrix, int nObject, float fFloorHeight, float fLightPos[3], int nShadowType);

void 	DrawZBiasTriangles 			(PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour);
void 	DrawZBiasVertices 			(PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour);
void 	DrawAccumulationBuffer 		(PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour);

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
					 0xA0   /* Logo background translucency */
					 );
					 

	KMShellSetBuffers (	0, 			/* % Opaque  (flushed)  */
						0,			/* % ModVol Opaque */
						100,		/* % Translucent   */
						0,			/* % ModVol Trans  */
						0);	

	KMPrint3DSetTextures();
	
	LoadTextures ();
	
	InitMaterials ();
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		InitMeshes(i);
	}
	
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
 *  Description     :  Draws everything in the scene plus the texture 
 *                     created in RenderSceneInTexture ()                                           
 *----------------------------------------------------------------------*/
int RenderScene (void)
{
int				i, j;
MATRIX			Matrx;
float			fLightPosition[3];
char 			*sShadowText[] = {"ZBIAS ON VERTICES","ZBIAS ON POLYGONS","ACCUMULATION BUFFER"};
	fAngleY += 0.03f;
	
	fLightPosition[0] = -LightDirection[0] * 150.0f + Mesh[M_KNOT].fCenter[0];
	fLightPosition[1] = -LightDirection[1] * 150.0f + Mesh[M_KNOT].fCenter[1];
	fLightPosition[2] = -LightDirection[2] * 150.0f + Mesh[M_KNOT].fCenter[2];
	
	
	for (i=0; i<NUM_MESHES;i++) 
	{ 
		/* Don't transform these objects */
		if (i==M_LIGHT) continue;
		
		KMMatrixReset  (&Matrx);
	
		if(i==M_KNOT)
		{	
			KMMatrixRotate(&Matrx, 0.0f, fAngleY, 0.0f);
			
			/* Calculation of smooth-shading */ 
			KMLightSmoothShade (&Matrx, Mesh[i].nNumVertex, Mesh[i].pNormals, (KMVERTEX_03 *)KmVert[i],
								LightDirection, 0xC0FFFFFF, FALSE);
				
		}
		
			/* Transform all the vertices */
		KMTransTransformProjectPerspective (&Matrx, Mesh[i].nNumVertex, Mesh[i].pVertex, 
											KmVert[i], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
											
		RenderObject (i, &StripHead[i]);
		
    	if (i==M_KNOT) ProjectAndRenderFlatShadow(&Matrx, M_KNOT, -170.0f, fLightPosition,  nShadowMode);
	
	}
	
	/* Draw the light spot */
	KMMatrixReset	 (&Matrx);

	KMMatrixTranslate (&Matrx,	fLightPosition[0], fLightPosition[1], fLightPosition[2]);
	

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
		
	KMPrint3DWindowOutput (InfoWin, "(A) Shadow method  %s\n", sShadowText[nShadowMode]);
	
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
 *  Note            : This function is called by KMShell.c                           
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	Delay = 0;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
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
			if (dwCurrentWin==-1) dwCurrentWin = 6;
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
			if (dwCurrentWin==7) dwCurrentWin = 0;
		}
		Delay =0;
	}
	
	/* UP ANALOG-PAD */
	if (AnalogPadY()<-64)
	{
		/* Light rotation */
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
		
		/* Vertical limit at -50 */
		if ((-sin(fLAng1-0.02f) * 150.0f + Mesh[M_KNOT].fCenter[1]) > -50.0f)
		{
		 	fLAng1 -= 0.02f;
	 	}
		
	 }

	/* DOWN ANALOG-PAD */
	if (AnalogPadY()>64)
	{
		/* Light rotation */
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
		
		/* Vertical limit at -50 */
		if ((-sin(fLAng1+0.02f) * 150.0f + Mesh[M_KNOT].fCenter[1]) > -50.0f)
		{
			fLAng1 += 0.02f;
		}
		
	}

	/* LEFT ANALOG-PAD */
	if (AnalogPadX()<-64)
	{
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
		fLAng2 -= 0.02f;
		
	}

	/* RIGHT ANALOG-PAD */
	if (AnalogPadX()>64)
	{
		/* Light rotation */
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
		fLAng2 += 0.02f;
		
	}


	/* A button */
	if (IsAKey())
	{
		if(Delay>2)
		{
			nShadowMode++;
			if(nShadowMode==3) nShadowMode = 0;
		}
		Delay=0;
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
 *  Description     : Initialitation for meshes
 *-------------------------------------------------------------------------------------*/
void InitMeshes (int nObject)
{
register unsigned j;

	/* Memory allocation for KmVert */
	KmVert[nObject] = (KMVERTEX_03 *)syMalloc(Mesh[nObject].nNumVertex*sizeof(KMVERTEX_03));
	
	/* Setting UV values and colors for all the meshes reading materials or vertex colors*/
    for (j=0; j<Mesh[nObject].nNumVertex; j++)
	{
		/* UVs */
		if(Mesh[nObject].pUV != NULL)
		{
			(KmVert[nObject]+j)->fU	= *(Mesh[nObject].pUV+j*2+0);
			(KmVert[nObject]+j)->fV	= *(Mesh[nObject].pUV+j*2+1);
		}
		else
		{
			(KmVert[nObject]+j)->fU	= 0.0f;
			(KmVert[nObject]+j)->fV	= 0.0f;
		}
		
		(KmVert[nObject]+j)->uBaseRGB.dwPacked = 0xFFFFFFFF;

		/* No specular color */
		(KmVert[nObject]+j)->uOffsetRGB.dwPacked = 0x00000000;
 
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
	KMTextureConvertAndLoad(&Tex[M_GROUND], Texture[0].pBitmapData, NULL, 
						Texture[0].nWidth, Texture[0].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[M_KNOT], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
	
	KMTextureConvertAndLoad(&Tex[M_DUMMY], Texture[2].pBitmapData, NULL, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[M_LIGHT], Texture[3].pBitmapData, NULL, 
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

 	KMShellInitStripHead (&StripHead[M_GROUND], &Tex[M_GROUND], VC_OPAQUE);
	
	KMShellInitStripHead (&StripHead[M_KNOT], &Tex[M_KNOT], VC_OPAQUE);
	
	KMShellInitStripHead (&StripHead[M_LIGHT], &Tex[M_LIGHT], VC_ADDITIVE);
	
	KMShellInitStripHead (&StripHead[M_DUMMY], &Tex[M_DUMMY], VC_TRANS | VC_CULLING );

	/* 
	 * ACCUMULATION BUFFER 
	 */
	KMShellInitStripHead (&StripHead[20], &Tex[M_DUMMY], VC_TRANS | VC_CULLING );
	kmChangeStripSRCSelect		(&StripHead[20], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[20], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[20], KM_IMAGE_PARAM1, KM_ONE, KM_ZERO);
	kmChangeStripZWriteDisable	(&StripHead[20], TRUE);

	
 
	KMShellInitStripHead (&StripHead[21], &Tex[M_DUMMY], VC_TRANS | VC_CULLING );
	kmChangeStripSRCSelect		(&StripHead[21], KM_IMAGE_PARAM1, 0);
	kmChangeStripDSTSelect		(&StripHead[21], KM_IMAGE_PARAM1, 1);
	kmChangeStripBlendingMode	(&StripHead[21], KM_IMAGE_PARAM1, KM_ONE, KM_ZERO);
	kmChangeStripDepthCompareMode(&StripHead[21], KM_ALWAYS);
	kmChangeStripZWriteDisable	 (&StripHead[21], TRUE);

	KMShellInitStripHead (&StripHead[22], &Tex[M_DUMMY], VC_TRANS | VC_CULLING );
	kmChangeStripSRCSelect		(&StripHead[22], KM_IMAGE_PARAM1, 1);
	kmChangeStripDSTSelect		(&StripHead[22], KM_IMAGE_PARAM1, 0);
	kmChangeStripBlendingMode	(&StripHead[22], KM_IMAGE_PARAM1, KM_DESTCOLOR, KM_ZERO);
	kmChangeStripZWriteDisable	(&StripHead[22], FALSE);
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
	InfoWin = KMPrint3DCreateWindow (60, 1);
	
	KMPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 90.0f, 50.0f, 10.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE );


	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows   ", NULL);

 	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (1 of 6)",
"This demo shows three different methods to 'presort' flat-shadow projected polygons to avoid overlapping artefacts.");

/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (2 of 6)",
"The first two methods add a Z bias to the vertices (vertex by vertex or polygon by polygon). The third \
method uses the accumulation buffer to achieve the same result.");

/* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (3 of 6)",
"For the two Z bias methods the translucency mode must be 'User Pre-Sorted', otherwise the hardware will correctly sort \
the polygons, showing a darker shadow where they overlap.");
 
 /* Window 4 */
	TWin[4] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (4 of 6)",
"Z BIAS PER VERTEX\n\
Starting from the last polygon, a very small Z offset (about a millionth) is added per vertex. \
This will sort the polygons in the reverse sense from the submission order, so every new polygon will \
remove the overlap region of the polygons already drawn.\n\n");
 
 /* Window 5 */
	TWin[5] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (5 of 6)",
"Z BIAS PER POLYGON\n\
In this case the Z bias is added per polygon, and every polygon is sent to render \
individually. This method is slower than the Z bias by vertex, but it \
works fine with all the meshes because shadow polygons never intersect.\n\n");

 /* Window 5 */
	TWin[6] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "SHADY Flat Shadows (6 of 6)",
"ACCUMULATION BUFFER\n\
This is an example of how the accumulation buffer can be used forr something more than multitexturing. \
Z bias isn't needed because everything is rendered as (ONE,ZERO) in the accumulation buffer, so there are no overlapping artefacts. \
The content of the accumulation buffer is blended on top of the opaque floor.");


}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : ProjectAndRenderFlatShadow                                                       
 *  Inputs          : None                                                             
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     :                     
 *-------------------------------------------------------------------------------------*/
 void ProjectAndRenderFlatShadow(MATRIX *pMatrix, int nObject, float fFloorHeight, float fLightPos[3], int nShadowType)
{
int   i;
int   nNumVertices;
float Vx, Vy, Vz;
float Lx, Ly, Lz;
float Dist_y, Div_y;
float *pTransformedVertex, *pTransVertex;
float *pTargetVertex,      *pTargetCount;
KMVERTEX_03 *pKmShadowVertex, *pTempPtr;

	/* Allocate memory for temporal vertex data. */
	pKmShadowVertex	   = (KMVERTEX_03 *)syMalloc(Mesh[nObject].nNumVertex * sizeof(KMVERTEX_03));
	pTransformedVertex = (float *)syMalloc(Mesh[nObject].nNumVertex * sizeof(float) * 3);
	pTargetVertex      = (float *)syMalloc(Mesh[nObject].nNumVertex * sizeof(float) * 3);

	pTransVertex = pTransformedVertex;
	pTargetCount = pTargetVertex;

	nNumVertices = Mesh[nObject].nNumVertex;
	
	Lx = fLightPos[0];
	Ly = fLightPos[1];
	Lz = fLightPos[2];
	 
	Dist_y = fFloorHeight - Ly;

	/* Transform the object without projection */
	KMTransTransformVertices(pMatrix, nNumVertices, Mesh[nObject].pVertex, pTransVertex);

	/* Project every vertex on the floor */
	for (i=nNumVertices; i!=0; i--)
	{
		Vx = *(pTransVertex++);
		Vy = *(pTransVertex++);
		Vz = *(pTransVertex++);
		
		/* Y slamming: if a vertex is above the light position, we force  
		 * it to be a bit below the light height.
		 */
		if (Vy>=Ly) Vy = Ly -  0.1f;
		
		Div_y = Dist_y/(Vy - Ly);
		
		*(pTargetCount++) = (Vx-Lx) * Div_y + Lx;
		*(pTargetCount++) = fFloorHeight;
		*(pTargetCount++) = (Vz-Lz) * Div_y + Lz;
		
	}

	/* Transform and project the shadow as a usual object,
	 */
	KMMatrixReset	  (pMatrix);
	
	KMTransTransformProjectPerspective (pMatrix, nNumVertices,  pTargetVertex, 
										pKmShadowVertex, ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
	switch(nShadowType)
	{
		default:
		case SHADOW_ZBIAS_VERTICES:
				DrawZBiasVertices (&StripHead[M_DUMMY], nObject, pKmShadowVertex, 0x80000000);
				break;
		
		case SHADOW_ZBIAS_POLYGONS:
				DrawZBiasTriangles (&StripHead[M_DUMMY], nObject, pKmShadowVertex, 0x80000000);
				break;
			
		case SHADOW_ACCUMULATION_BUFFER:
				/* Draw the floor to clean the accumulation buffer */
				RenderObject (M_GROUND,  &StripHead[20]);
				
				/* Draw the flat shadow as (ONE,ZERO) so the overlap is invisible */
				DrawAccumulationBuffer ( &StripHead[21], nObject, pKmShadowVertex, 0xFF808080);
				
				/* Flush the content of the accumulation buffer using the floor polygons
				   blend it as (DESCOLOR,ZERO) so it is blended on top of the opaque floor */
				RenderObject (M_GROUND,  &StripHead[22]);
				break;
	}
		

	syFree(pTransformedVertex);
	syFree(pTargetVertex);
	syFree(pKmShadowVertex);



}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : DrawAccumulationBuffer                                                       
 *  Inputs          : pStripHead nObject pVertices Colour                                                          
 *  Outputs         : None                                                               
 *  Returns         : Mesh                                                               
 *  Globals Used    :                                                                    
 *  Description     : Set the colour and render the polygons. Z bias isn't needed because
 *                    everything is rendered as (ONE,ZERO) so there aren't overlaping artifacts.
 *                    The accumulation buffer method is slower than the Z bias methods because
 *                    the area to fill is bigger (a translucent floor is blend on top of the opaque one)
 *                    but, on the other hand, it works with the translucency autosort mode.
 * 
 *                    Besides, this is an example of how to use the accumulation buffer for something 
 *                    more than multitexture ;-)
 *-------------------------------------------------------------------------------------*/
void DrawAccumulationBuffer (PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour)
{
int i, NumVertices;
KMVERTEX_03 *pTempPtr;

	NumVertices = Mesh[nObject].nNumVertex;

	pTempPtr = pVertices ;
	
	/* Set the colour */
	for (i=NumVertices; i!=0; i--)
	{
		pTempPtr->uBaseRGB.dwPacked = Colour;
		pTempPtr++;
	}				

	KMShellStrips (pStripHead, Mesh[nObject].nNumStrips, Mesh[nObject].pStripLength,
		          Mesh[nObject].pStrips, pVertices);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : DrawZBiasTriangles                                                       
 *  Inputs          : pStripHead nObject pVertices Colour                                                              
 *  Outputs         : None                                                               
 *  Returns         : Mesh                                                               
 *  Globals Used    :                                                                    
 *  Description     : The translucency mode must be 'User Pre-Sorted', otherwise the hardware would sort
 *                    correctly the polygons, showing a darker shadow where they overlap.
 *                    Starting from the last polygon, a very small Z offset (about a millionth) is added per vertex. 
 *                    (It must be smaller is the number of vertices is high, as in this example).
 *                    That will sort the polygons in the oposite order they are sent, so every new polygon will
 *                    remove the overlap region of the polygons already drawn.  
 *
 *	                  In this case the Z bias is added to the vertices, so we don't need to
 *                    draw the polygons one by one. It is much faster, but some meshes might show
 *                    crossing polygon artifacts.                  
 *-------------------------------------------------------------------------------------*/
void DrawZBiasVertices (PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour)
{
int i, NumVertices;
KMVERTEX_03 *pTempPtr;
float fZBias = 0.0f;

	NumVertices = Mesh[nObject].nNumVertex;

	pTempPtr = pVertices + NumVertices - 1;
	
	for (i=NumVertices; i!=0; i--)
	{
		pTempPtr->uBaseRGB.dwPacked = Colour;
		pTempPtr->u.fZ += fZBias;
		
		pTempPtr--;
		fZBias += 0.00000001f;
	}				

	KMShellStrips (pStripHead, Mesh[nObject].nNumStrips, Mesh[nObject].pStripLength,
		          Mesh[nObject].pStrips, pVertices);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : DrawZBiasTriangles                                                       
 *  Inputs          : pStripHead nObject pVertices Colour                                                              
 *  Outputs         : None                                                               
 *  Returns         : VertexBufferDesc  Mesh                                                             
 *  Globals Used    :                               
 *  Description     : Starting from the last polygon, a very small Z offset (about a millionth) is added per vertex. 
 *                    That will sort the polygons in the oposite order they are sent, so every new polygon will
 *                    remove the overlap region of the polygons already drawn.  
 *
 *	                  In this case the Z bias is added per polygon, and every polygon is sent to render
 *                    as a strip of 1. This method is slower than the Z bias by vertex, but it
 *                    works fine with all the meshes because there is no crossing polygons.  
 *-------------------------------------------------------------------------------------*/
void DrawZBiasTriangles (PKMSTRIPHEAD pStripHead, int nObject, KMVERTEX_03 *pVertices, DWORD Colour)
{
int nFace, nFacesCont=0, i;
float fZBias = 0.0f;
KMVERTEX_03 TempVertex;
unsigned nNumFaces;
unsigned short *pFaces;

    nNumFaces = Mesh[nObject].nNumFaces;
	pFaces    = Mesh[nObject].pFaces;
	
	fZBias = nNumFaces * 0.00000001f;
	
	/* Strips start */
	kmStartStrip(&VertexBufferDesc, pStripHead);

	for(i = 0; i < nNumFaces; i++)
	{
			
		/* Vertex 1 */
		nFace = *(pFaces+nFacesCont++);
		TempVertex.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		TempVertex.fX = (pVertices+nFace)->fX;
		TempVertex.fY = (pVertices+nFace)->fY;
		TempVertex.u.fZ = (pVertices+nFace)->u.fZ + fZBias;
		TempVertex.uBaseRGB.dwPacked = Colour;
		
		kmSetVertex (&VertexBufferDesc, &TempVertex, KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		
		/* Vertex 2 */
		nFace = *(pFaces+nFacesCont++);
		TempVertex.ParamControlWord	= KM_VERTEXPARAM_NORMAL;
		TempVertex.fX = (pVertices+nFace)->fX;
		TempVertex.fY = (pVertices+nFace)->fY;
		TempVertex.u.fZ = (pVertices+nFace)->u.fZ + fZBias;
		TempVertex.uBaseRGB.dwPacked = Colour;
		
		kmSetVertex (&VertexBufferDesc, &TempVertex, KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
			
		/* Vertex 3 */
		nFace = *(pFaces+nFacesCont++);
		TempVertex.ParamControlWord	= KM_VERTEXPARAM_ENDOFSTRIP;
		TempVertex.fX = (pVertices+nFace)->fX;
		TempVertex.fY = (pVertices+nFace)->fY;
		TempVertex.u.fZ = (pVertices+nFace)->u.fZ + fZBias;
		TempVertex.uBaseRGB.dwPacked = Colour;
		
		kmSetVertex (&VertexBufferDesc, &TempVertex, KM_VERTEXTYPE_03, sizeof (KMVERTEX_03));
		
				
		fZBias -= 0.00000001f;
	}		

}
/*-----------------------------------------------------------------------------------------*
 * END OF FILE
 *-----------------------------------------------------------------------------------------*/