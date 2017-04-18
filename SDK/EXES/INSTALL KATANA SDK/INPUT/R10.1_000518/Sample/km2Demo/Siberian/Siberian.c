/*****************************************************************************
  Name :     Siberian 
  Author:	 Carlos Sarria
  Date :     July 1998 (Updated June 1999)
  Platform : Dreamcast Set5 (CLX2.2 + SH4)
 
  Description : Punchtrough demo.

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

#define NUM_MESHES     11
#define NUM_MATERIALS  8
#define	NUM_TEXTURES   12

/* MESHES */
#define M_B2_TRANS  0
#define M_B2_BARK  1
#define M_B1_TRANS  2
#define M_B1_BARK  3
#define M_B3_TRANS  4
#define M_B3_BARK  5
#define M_B4_TRANS  6
#define M_B4_BARK  7
#define M_SNOW  8
#define M_LOGO  9
#define M_BACKGROUND  10

#define SCALE 1.13f
/*************************************************/
/*	Globals                                      */
/*************************************************/

KMSURFACEDESC		Tex[256];				/* texture surface */
KMSTRIPHEAD			StripHead[256];		/* Vertex context */
KMVERTEX_03			*KmVert[256];			/* Vertex pointers*/


int ScreenWidth=640, ScreenHeight=480;

km_vector CameraFrom		= { 0.0f, 0.0f, -100.0f};
km_vector CameraTo			= { 0.0f, 0.0f, 100.0f};
km_vector LightDirection	= {1.0f, -1.0f, 1.0f};

unsigned nFrame = 100;
unsigned nTrees = 170;
unsigned Type	= 0;
unsigned Cont	= 0;
unsigned nPT	= 0;
unsigned bStart = FALSE, bPause = FALSE;
float	 Ang    = 0;
float    Distance = 0;
unsigned nMode = 2;

/* Info windows control */
DWORD dwCurrentWin= 0, dwDisplayWins = TRUE, InfoWin, TWin[10];

char *sMode[] = {"OPAQUE", "TRANSLUCENT AUTOSORT", "PUNCHTROUGH"};
/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void);
void 	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	RenderObject		(MATRIX *Matrx,  int Object);
void 	CreateWindows 		(void);

/************************************************************************/
/* KMShell functions:                                                   */
/*    InitApplication                                                 */
/*    QuitApplication                                                 */
/*    RenderScene                                                     */
/*    PadControl                                                      * 
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

	
	KMShellSetVideo	(FALSE, /* TRUE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );
					 

	KMShellSetBuffers (	0, 		/* % Opaque (flushed) */
						0,	    /* % ModVol Opaque */
						60,		/* % Translucent   */
						0,		/* % ModVol Trans  */
						40);	/* % Punchthrough  */
		

	KMPrint3DSetTextures();
	
	LoadTextures 	();
	CreateContexts 	();
	
	CreateWindows ();

	InitMeshes();
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

	KMPrint3DReleaseTextures ();

	/* FREE TEXTURES */
	kmFreeTexture(&Tex[M_SNOW]);
	kmFreeTexture(&Tex[M_BACKGROUND]);
	kmFreeTexture(&Tex[M_B1_BARK]);
	kmFreeTexture(&Tex[M_B1_TRANS]);
	kmFreeTexture(&Tex[M_B2_BARK]);
	kmFreeTexture(&Tex[M_B2_TRANS]);
	kmFreeTexture(&Tex[M_B3_BARK]);
	kmFreeTexture(&Tex[M_B3_TRANS]);
	kmFreeTexture(&Tex[M_B4_BARK]);
	kmFreeTexture(&Tex[M_B4_TRANS]);
	
	for (i=0; i<NUM_MESHES; i++) 
	{
		KmVert[i] = (KMVERTEX_03 *)syMalloc(Mesh[i].nNumVertex*sizeof(KMVERTEX_03)); 
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
MATRIX			Matrx;
int				j;
unsigned		TreeCont = 21, BiCont=0;
float			Radius;
static unsigned	PathCont = 0;

	
	if (bStart == FALSE)
	{
		Ang += PI/80.0f;
		Distance += PI/60.0f;
	}

	Radius = 500 + 350 * sin ((double)Distance);

	CameraFrom[0] = cos(Ang) * Radius;
	CameraFrom[1] = 400;
	CameraFrom[2] = sin(Ang) * Radius;

	CameraTo[0] = *(Mesh[M_LOGO].pVertex+0);
	CameraTo[1] = *(Mesh[M_LOGO].pVertex+1);
	CameraTo[2] = *(Mesh[M_LOGO].pVertex+2);

	
	/* Drawing the background */
	KMShellBackground (&StripHead[M_BACKGROUND]);

	/* Drawing the trees (there are 4 different models) */
	for (j=0; j<nTrees; j++)
	{
      KMMatrixReset(&Matrx);
      
      KMMatrixScale(&Matrx, SCALE);
      
	  /* Reads one of the ground vertices and places a tree there */
	  KMMatrixTranslate (&Matrx,	*(Mesh[M_SNOW].pVertex+TreeCont*3+0), 
								*(Mesh[M_SNOW].pVertex+TreeCont*3+1) + 90, 
								*(Mesh[M_SNOW].pVertex+3*TreeCont+2)
						);
						
	
	  TreeCont+=8;
	 
	  if(j%4==0) Type = (BiCont++&1)?2:0;
	  if(j%4==1) Type = 1;
	  if(j%4 >1) Type = 2;
	 
	  
      switch (Type)
	  {
		case 0:
		RenderObject (&Matrx, M_B2_TRANS);
		nPT = 0;
		RenderObject (&Matrx, M_B2_BARK);
		break;

		case 1:
		RenderObject (&Matrx, M_B1_TRANS);
		RenderObject (&Matrx, M_B1_BARK);
		break;


		case 2:
		RenderObject (&Matrx, M_B4_TRANS);
		RenderObject (&Matrx, M_B4_BARK);
		break;

	
		}
	}

   /* Drawing the ground */
   KMMatrixReset(&Matrx);
   KMMatrixScale(&Matrx, SCALE);
   RenderObject (&Matrx, M_SNOW);

   /* Drawing the logo */
   KMMatrixReset(&Matrx);
   KMMatrixScale(&Matrx, SCALE);
   RenderObject (&Matrx, M_LOGO);

   /* 
	* Text windows.
	*/
	if(dwDisplayWins)
	{
		KMPrint3DDisplayWindow(TWin[dwCurrentWin]);
	}

	KMPrint3DDisplayWindow(InfoWin);
			 
 
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
 *						the user to cotrol the joystick                           
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	Delay = 0, PolyType;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
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
			if (dwCurrentWin==-1) dwCurrentWin = 2;
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
			if (dwCurrentWin==3) dwCurrentWin = 0;
		}
		Delay =0;
	}
	
	/* A button */
	if (IsAKey())
	{
		if (Delay>10)
		{
			nMode++; if (nMode==3) nMode=0;
		
			KMShellInitStripHead (&StripHead[M_B1_TRANS], &Tex[M_B1_TRANS], nMode | VC_UVFLIP);
			KMShellInitStripHead (&StripHead[M_B2_TRANS], &Tex[M_B2_TRANS], nMode | VC_UVFLIP);
			KMShellInitStripHead (&StripHead[M_B3_TRANS], &Tex[M_B3_TRANS], nMode | VC_UVFLIP);
			KMShellInitStripHead (&StripHead[M_B4_TRANS], &Tex[M_B4_TRANS], nMode | VC_UVFLIP);
			
			KMPrint3DWindowOutput (InfoWin, " (A) Polygon type: %s \n", sMode[nMode]);
			Delay = 0;
		}
		
	}

	
	/* No controler until START is pressed */
	if (bStart == FALSE) return TRUE;
	
	/* UP */
	if (AnalogPadY()<-64)
	{
		Distance -= 0.1f;
	}

	/* DOWN */
	if (AnalogPadY()>64)
	{
		Distance -= 0.1f;
	}

	/* LEFT */
	if (AnalogPadX()<-64)
	{
		Ang  += 0.1f;
	}

	/* RIGHT */
	if (AnalogPadX()>64)
	{
		Ang  -= 0.1f;
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
 *  Description     : Sets initials values for meshes managment                           
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
            (KmVert[i]+j)->fU = *(Mesh[i].pUV+j*2+0);
            (KmVert[i]+j)->fV = *(Mesh[i].pUV+j*2+1);

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
 *  Description     : Convert 24bits Bitmap format to 16bits hardware format and loads 
 *                    it in video memory.                    
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
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_ARGB1555);
		}
		else if(nTexture != -1) /* It's opaque */
		{
			if (i==M_BACKGROUND || i==M_LOGO) /* No mipmap for the background and logo*/
			{
				KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565);
			}
			else
			{
				KMTextureConvertAndLoad(&Tex[i], Texture[nTexture].pBitmapData, NULL, 
						Texture[nTexture].nWidth, Texture[nTexture].nHeight, KM_TEXTURE_TWIDDLED_MM | KM_TEXTURE_RGB565);
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
 *  Description     : All the contexts needed by the application.                        
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{
	/* OPAQUE MATERIALS */
	KMShellInitStripHead (&StripHead[M_SNOW], &Tex[M_SNOW], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_BACKGROUND], &Tex[M_BACKGROUND], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_LOGO], &Tex[M_LOGO], VC_OPAQUE);

	KMShellInitStripHead (&StripHead[M_B1_BARK], &Tex[M_B1_BARK], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_B2_BARK], &Tex[M_B2_BARK], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_B3_BARK], &Tex[M_B3_BARK], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_B4_BARK], &Tex[M_B4_BARK], VC_OPAQUE);
	
	/* PUNCHTROUGH LEAVES */
	KMShellInitStripHead (&StripHead[M_B1_TRANS], &Tex[M_B1_TRANS], VC_PUNCHTHROUGH | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_B2_TRANS], &Tex[M_B2_TRANS], VC_PUNCHTHROUGH | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_B3_TRANS], &Tex[M_B3_TRANS], VC_PUNCHTHROUGH | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_B4_TRANS], &Tex[M_B4_TRANS], VC_PUNCHTHROUGH | VC_UVFLIP);
	
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : RenderObject                                                       
 *  Inputs          : Matrx Object                                                             
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Sending a set of striops to render.                              
 *-------------------------------------------------------------------------------------*/
void RenderObject (MATRIX *Matrx, int Object)
{
int ret;

	ret = KMTransTransformProjectPerspective (Matrx, Mesh[Object].nNumVertex, Mesh[Object].pVertex, 
										KmVert[Object], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, 1.0f, 1000000.0f, 60.0f*(PI/180.0f));
	
	if(ret) KMShellStrips (&StripHead[Object],Mesh[Object].nNumStrips, Mesh[Object].pStripLength, Mesh[Object].pStrips, (KMVERTEX_03 *)KmVert[Object]);
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
	InfoWin = KMPrint3DCreateWindow (50, 1);
	
	KMPrint3DSetWindow		(InfoWin, 0xFFA00000, 0xFFFFFFFF, 0.5f, 1.0f, 93.0f, 50.0f, 10.0f);
	KMPrint3DSetWindowFlags	(InfoWin, PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_TITLE | PRINT3D_FULL_OPAQUE);
	KMPrint3DWindowOutput (InfoWin, " (A) Polygon type: %s \n", sMode[nMode]);
	
	/* Text Windows */
	/* Window 0 */
	/* Window 1 */
	TWin[0] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "SIBERIAN Punchthrough ", NULL);
	
	/* Window 1 */
	TWin[1] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "SIBERIAN Punchthrough (1 of 2)","\
Punchthrough is a special type of 'cut-out' texture where the texture pixels are treated as either full translucent or full opaque.\n\n\
These polygons can be handled by the graphics processor more efficiently than 'autosorted' translucent polygons.\n\n\
(START) Rolling demo/Interactive\n (ANALOG PAD) Move camera.\n\n");
	
	/* Window 2 */
	TWin[2] = KMPrint3DCreateDefaultWindow (1.0f, 1.0f, 45, "SIBERIAN Punchthrough (2 of 2)","\
Thanks to the 'Deferred Texturing' architecture of the PowerVR graphics chips, punchthrough polygons give a much \
higher fill-rate than the standard translucency.\n\n");
}



