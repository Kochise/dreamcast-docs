/*****************************************************************************
  Athor:	 Carlos Sarria	
  Name :     Shaddy
  Date :     March 1999 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4) 
  
  Description : Projected polygons flat shadow.
  Notes:        This demo shows how to 'presort' flat-shadow projected polygons
                to avoid overlapping artifacts.
                
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <math.h>
#include <shinobi.h>

#include "KMTools.h"
#include "KMShell_8Passes.h"

/*************************************************/
/*	Model                                        */
/*************************************************/
#include "DataTypedef.h"

extern Struct_Mesh      Mesh[];
extern Struct_Texture   Texture[];

#define NUM_MESHES     3
#define	NUM_TEXTURES   4

#ifndef PI
#define PI 3.1415
#endif

/* MESHES */
#define M_GROUND 0
#define M_LIGHT  1
#define M_HEDRA  2

#define M_DUMMY  3

unsigned char DummyTexture[] = {
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
 	0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 0xff,0xff,0xff, 
0x00 }; 


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
km_vector LightPosition;

float   nFrame = 0; 
float	fXAng, fYAng, fZAng;

BOOL    bStart = FALSE, bNoAB = FALSE, bFire = FALSE;

float   fPosX=0.0f, fPosZ=0.0, fAngleY = 0.5f, fAngleX=0.0f, fHeight = 0.0f;
float	fLAng1 = -1.0f, fLAng2 = 0.5f;

/* Memory to hold the transformed object */
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

void 	ProjectAndDrawFlatShadow	(MATRIX *Matrix, int nObject, float fFloorHeight, float fLightPos[3], DWORD Colour);
void 	DrawZBiasTriangles 			(PKMSTRIPHEAD pStripHead, unsigned nNumFaces, unsigned short *pFaces, 
										KMVERTEX_03 *pVertices, DWORD Colour);

int 	RenderSceneFirstPass  	(void);
int 	RenderSceneSecondPass 	(void);
int 	RenderSceneThirdPass 	(void); 
int 	RenderSceneFourthPass 	(void); 
int 	RenderSceneFifthPass 	(void); 
int 	RenderSceneSixthPass 	(void); 
int 	RenderSceneSeventhPass 	(void); 
int 	RenderSceneEighthPass 	(void); 

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

	KMShellSetVideo	();

	/* Eight passes */
	KMShellSetBuffers(PASS_PRESORT, PASS_PRESORT, PASS_AUTOSORT, PASS_PRESORT,
					  PASS_NULL, PASS_NULL, PASS_NULL, PASS_NULL);		


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
 *  Inputs          :  nCurrentPass                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                                 
 *  Globals Used    :                                                 
 *  Description     :  This function is called by KMShell every pass,
 *                     8 times per frame.
 *  Notes           :  The first pass flushes opaque polygons, the remaining 
 *                     seven passes flush translucent polygons. 
 *                     The translucent polygons in different passes have to 
 *                     be correctly sorted per pass. A translucent polygon
 *                     drawn behind another translucent polygon that has been 
 *                     drawn in the previous pass will show a 'bad sorting'
 *                     artifact.
 *----------------------------------------------------------------------*/
int RenderScene (DWORD nCurrentPass)
{

	switch (nCurrentPass)
	{
		case 0: RenderSceneFirstPass  (); break;
		case 1: RenderSceneSecondPass (); break;
		case 2: RenderSceneThirdPass  (); break;
		case 3: RenderSceneFourthPass (); break;
		case 4: RenderSceneFifthPass  (); break;
		case 5: RenderSceneSixthPass  (); break;
		case 6: RenderSceneSeventhPass(); break;
		case 7: RenderSceneEighthPass (); break;
		
		default: break;
	}

	return TRUE;
}

/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneFirstPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                                
 *  Globals Used    :                                          
 *  Description     :  The first pass is used to draw all the polygons that
 *                     are not translucent.                                                 
 *----------------------------------------------------------------------*/
int RenderSceneFirstPass (void)
{
int				i, j;
MATRIX			Matrx;

	fAngleY += 0.03f;
	
	
    /* Draw the floor */
	KMMatrixReset  (&Matrx);
	
	KMTransTransformProjectPerspective (&Matrx, Mesh[M_GROUND].nNumVertex, Mesh[M_GROUND].pVertex, 
											KmVert[M_GROUND], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
	RenderObject (M_GROUND, &StripHead[M_GROUND]);
	
	nFrame++;
		
	/* RenderScene OK */
	return TRUE;
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                               
 *  Globals Used    :                                          
 *  Description     :  Draws the translucent shadow using pre-sort mode.                                                
 *----------------------------------------------------------------------*/
int RenderSceneSecondPass (void)
{
MATRIX	Matrx;

	LightPosition[0] = -LightDirection[0] * 150.0f + Mesh[M_HEDRA].fCenter[0];
	LightPosition[1] = -LightDirection[1] * 150.0f + Mesh[M_HEDRA].fCenter[1];
	LightPosition[2] = -LightDirection[2] * 150.0f + Mesh[M_HEDRA].fCenter[2];
	
	KMMatrixReset  (&Matrx);
	KMMatrixRotate(&Matrx, 0.0f, fAngleY, 0.0f);
			
	ProjectAndDrawFlatShadow(&Matrx, M_HEDRA, -170.0f, LightPosition, 0x30000000);

}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                   
 *  Globals Used    :                                         
 *  Description     :  Draws the complex translucent object using hardware 
 *                     auto-sort.
 *----------------------------------------------------------------------*/
int RenderSceneThirdPass (void)
{
MATRIX	Matrx;	

	/* Draw the Hedra */					
	KMMatrixReset  (&Matrx);
	
	KMMatrixRotate(&Matrx, 0.0f, fAngleY, 0.0f);
			
	KMLightSmoothShade (&Matrx, Mesh[M_HEDRA].nNumVertex, Mesh[M_HEDRA].pNormals, (KMVERTEX_03 *)KmVert[M_HEDRA],
								LightDirection, 0xFFFFFFFF, FALSE);

	KMTransTransformProjectPerspective (&Matrx, Mesh[M_HEDRA].nNumVertex, Mesh[M_HEDRA].pVertex, 
											KmVert[M_HEDRA], ScreenWidth, ScreenHeight,
											CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));
											
	RenderObject (M_HEDRA, &StripHead[M_HEDRA]);
	
	/* Draw the light spot */
	KMMatrixReset	 (&Matrx);

	KMMatrixTranslate (&Matrx,	LightPosition[0], LightPosition[1], LightPosition[2]);
	

	KMTransTransformProjectPerspective (&Matrx, Mesh[M_LIGHT].nNumVertex, Mesh[M_LIGHT].pVertex, 
										KmVert[M_LIGHT], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 30.0f*(PI/180.0f));

	RenderObject (M_LIGHT, &StripHead[M_LIGHT]);
	
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  FALSE to finish                                   
 *  Globals Used    :                                         
 *  Description     :  Draw the front most windows with information using
 *                     user pre-sort mode.                                 
 *----------------------------------------------------------------------*/
int RenderSceneFourthPass (void)
{
	if(dwDisplayWins)
	 {
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
	 }
	
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                     
 *  Globals Used    :                                         
 *  Description     :                                   
 *----------------------------------------------------------------------*/
int RenderSceneFifthPass (void)
{

	 
}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                     
 *  Globals Used    :                                         
 *  Description     :                                   
 *----------------------------------------------------------------------*/
int RenderSceneSixthPass (void)
{


}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                     
 *  Globals Used    :                                         
 *  Description     :                                   
 *----------------------------------------------------------------------*/
int RenderSceneSeventhPass (void)
{


}
/*----------------------------------------------------------------------*
 *  Function Name   :  RenderSceneSecondPass                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :                                     
 *  Globals Used    :                                         
 *  Description     :                                   
 *----------------------------------------------------------------------*/
int RenderSceneEighthPass (void)
{
	 
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
		LightDirection[0] = cos(fLAng2) * cos(fLAng1);
		LightDirection[1] = sin(fLAng1);
		LightDirection[2] = sin (fLAng2) * cos(fLAng1);
		
		/* Vertical limit at 5 */
		if ((-sin(fLAng1-0.02f) * 150.0f + Mesh[M_HEDRA].fCenter[1]) > 5.0f)
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
		
		/* Vertical limit at 5 */
		if ((-sin(fLAng1+0.02f) * 150.0f + Mesh[M_HEDRA].fCenter[1]) > 5.0f)
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
	
	KMTextureConvertAndLoad(&Tex[M_LIGHT], Texture[1].pBitmapData, NULL, 
						Texture[1].nWidth, Texture[1].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
						
	KMTextureConvertAndLoad(&Tex[M_HEDRA], Texture[2].pBitmapData, Texture[3].pBitmapData, 
						Texture[2].nWidth, Texture[2].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_ARGB4444);
	
	KMTextureConvertAndLoad(&Tex[M_DUMMY], DummyTexture, NULL, 8, 8, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);					
	
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
	
	KMShellInitStripHead (&StripHead[M_HEDRA], &Tex[M_HEDRA], VC_TRANS);
	
	KMShellInitStripHead (&StripHead[M_LIGHT], &Tex[M_LIGHT], VC_ADDITIVE);

	KMShellInitStripHead (&StripHead[M_DUMMY], &Tex[M_DUMMY], VC_TRANS | VC_CULLING);
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
	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "FOUR PASSES   ", NULL);

 	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "FOUR PASSES (1 of 3)",
"This demo shows an example where four render passes with different translucency sorting modes are used.");
 
    /* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "FOUR PASSES (2 of 3)",
"A complex translucent object with several intersecting planes casts shadows on the floor. The best solution to draw the shadow is to use \
the Z-Bias trick (See Shady demo). This trick only works in the translucency pre-sorted mode. The complex object has to be drawn using \
hardware auto-sort. The scene consists of pre-sorted and auto-sorted polygons.");

   /* Window 3 */
	TWin[3] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 55, "FOUR PASSES (3 of 3)",
"The first pass draws the opaque polygons. The second one draws the pre-sorted shadow. The third one draws the complex auto-sorted object. \
And, finally, the last pass draws this information window as translucent pre-presorted polygons.");



}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : ProjectAndDrawFlatShadow                                                       
 *  Inputs          : None                                                             
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     :                     
 *-------------------------------------------------------------------------------------*/
 void ProjectAndDrawFlatShadow(MATRIX *pMatrix, int nObject, float fFloorHeight, float fLightPos[3], DWORD Colour)
{
int   i;
int   nNumVertices, nCurrentFace[3];
float Vx, Vy, Vz;
float Lx, Ly, Lz;
float Dist_y, Div_y;
float *pTransformedVertex, *pTransVertex;
float *pTargetVertex,      *pTargetCount;
KMVERTEX_03 *pKmShadowVertex, *pTempPtr, TempVertex[3];

	/* Allocate memory for temporal vertex data. */
	pKmShadowVertex	   = (KMVERTEX_03 *)syMalloc(Mesh[M_HEDRA].nNumVertex * sizeof(KMVERTEX_03));
	pTransformedVertex = (float *)syMalloc(Mesh[M_HEDRA].nNumVertex * sizeof(float) * 3);
	pTargetVertex      = (float *)syMalloc(Mesh[M_HEDRA].nNumVertex * sizeof(float) * 3);

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
		
	/* Render the shadow with a incremental Z */
	DrawZBiasTriangles 	(&StripHead[M_DUMMY], Mesh[nObject].nNumVertex, Mesh[nObject].pFaces, pKmShadowVertex, Colour);

	syFree(pTransformedVertex);
	syFree(pTargetVertex);
	syFree(pKmShadowVertex);



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
void DrawZBiasTriangles (PKMSTRIPHEAD pStripHead, unsigned nNumFaces, unsigned short *pFaces, KMVERTEX_03 *pVertices, DWORD Colour)
{
int nFace, nFacesCont=0, i;
float fZBias = 0.0f;
KMVERTEX_03 TempVertex;

	fZBias = nNumFaces * 0.0000001f;
	
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
		
				
		fZBias -= 0.0000001f;
	}		

}
/*-----------------------------------------------------------------------------------------*
 * END OF FILE
 *-----------------------------------------------------------------------------------------*/