/*****************************************************************************
  Name :     Wrace 
  Author:	 Carlos Sarria
  Date :     July 1998 (updated June 1999)
  Platform : Dreamcast Set5 (CLX2 + SH4)
 
  Description : User defined table fog demo. 

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

/* MESHES */
#define NUM_MESHES     17
#define	NUM_TEXTURES   18

/* MESHES */
#define M_GROUND  0
#define M_B2_TRANS  1
#define M_B2_BARK  2
#define M_B1_TRANS  3
#define M_B1_BARK  4
#define M_B3_TRANS  5
#define M_B3_BARK  6
#define M_B4_TRANS  7
#define M_B4_BARK  8
#define M_FRONT  9
#define M_FIRE  10
#define M_START  11
#define M__1MILE  12
#define M__2MILES  13
#define M__3MILES  14
#define M_FINISH  15
#define M_BACKGROUND  16

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

unsigned nFrame = 0;
unsigned nTrees = 200;
unsigned Type	= 0;
unsigned Cont	= 0;
unsigned nPT	= 0;
BOOL     bStart = TRUE;

int		Translucent = 1, IsBark=0, Stopped=0;

float	Ang, PosZ = 0.0f, PosX=0.0f, OffsetX= 50.0f;
float	CosA, SinA, TrX, TrY, TrZ, MovX, MovZ;

float	GrAngZ = 0.0f, GrAngX = 0.0f, GrPosZ = 0.0f, GrHigh = 0.0f;
float	Velocity = 100.0f;

int		TreeHit, BestTrees;
int		nStart, nStartCont;

float	GrWide = 1.3f;
float	Vel = 5.0f;

float	High[30*30], ZIncr, XIncr, UIncr, VIncr, Base[30], Px,Py, Pz;

int		Retro=0, TreeHit=0, nTreesH = 0, BestTrees=0, YourTrees;

int		TreeHitPos[75];
float	TreeHitOff[75];

typedef struct _pos{
	float x;
	float y;
	float z;
	int Type;
} POS;

POS TreePos[75];

double  TotalTime, YourTime, BestTime;

KMDWORD		TWin[10];
/**************************************************/
/* Prototypes                                     */
/**************************************************/

void	InitMeshes			(void);
 void	LoadTextures 		(void);
void 	CreateContexts 		(void);
void	RenderObject		(MATRIX *Matrx,  int Object);

void	CalculateGround		(void);
void	BuildGround			(void);
void	DrawRadar			(void);
void	SetFogTable			(KMDWORD FogDensity, float r, float g, float b );
void 	CreateWindows 		(void);

/************************************************************************/
/* KMShell functions:                                                   */
/*    InitApplication                                                   */
/*    QuitApplication                                                   */
/*    RenderScene                                                       */
/*    PadControl                                                        * 
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
 *  Description     :  InitApplication() is called by KMShell to enable
 *						the user to initialise the application                                           
 *----------------------------------------------------------------------*/
void InitApplication (void)
{

	KMShellSetVideo	(FALSE,  /* FALSE = Hardware Trans Sorting  TRUE = User Trans PreSort  */
					 0x00   /* Logo background translucency */
					 );
					 
	KMShellSetBuffers(	0, 			/* % Opaque (flushed)     */
						0,			/* % ModVol Opaque */
						100,		/* % Translucent   */
						0,			/* % ModVol Trans  */
						0);			/* % Punchthrough  */

	LoadTextures ();
	CreateContexts ();

	InitMeshes();

	BuildGround ();
	
	
	KMPrint3DSetTextures();
	CreateWindows ();

	/* That's Table Fog initialisation */
	SetFogTable (3, 1.0f, 1.0f, 1.0f );
}
/*----------------------------------------------------------------------*
 *  Function Name   :  QuitApplication                                 
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                          
 *  Globals Used    :                                                 
 *  Description     :  QuitApplication() is called by KMShell to enable
 *						the user to finish the application                                                
 *----------------------------------------------------------------------*/
void QuitApplication (void)
{
register i;

	KMPrint3DReleaseTextures();

	/* FREE TEXTURES */
	kmFreeTexture(&Tex[M_GROUND]);
	kmFreeTexture(&Tex[20]);
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
		syFree(KmVert[i]); 
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
int				j, i;
int				Cont = 100;
int				NumEntries = 0;
static int nFire = 0;

  
	KMShellBackground (&StripHead[M_BACKGROUND]);
	
    /*
	 * Drawing our trees
	 */
	for (i=0;i<75; i++) 
	{
		
		TreeHit = FALSE;
		
		/* Start a 'flying' tree. */
		if (TreePos[i].z<100.0f && TreePos[i].z>0.0f && fabs(PosX+TreePos[i].x)<100.0f && nStartCont>1) 
		{ 
			TreeHit = TRUE; 
			nTreesH++;
		}

		if (TreeHitPos[i]>0) 
		{ 
			 
			 TreeHitPos[i]--; 
			 TreePos[i].x -= TreeHitOff[i];
			 TreePos[i].y -=  40.0 * sin((float)TreeHitPos[i]*(PI/50.0f));
			 TreePos[i].z += 250.0f;

             if (TreeHitPos[i]==10) 
			 { 
				 TreeHitPos[i] = 0; 
			     TreePos[i].x = 0;
			     TreePos[i].y = -500;
			     TreePos[i].z = -700.0f;
			 }
	
		 }
	
		/* Transformatios */
		KMMatrixReset (&Matrx);
		KMMatrixScale (&Matrx, 1.2f);

		if  (TreeHitPos[i]>0) /* Flying */
		{
	 		KMMatrixRotate (&Matrx, (float)(TreeHitPos[i])/7.0f, 0.0f,(float)(TreeHitPos[i])/20.0f+PI/2);
		}
		KMMatrixTranslate (&Matrx, PosX+TreePos[i].x, 20.0f-GrHigh+TreePos[i].y, 100+TreePos[i].z);

		/* Four different trees */
		switch (TreePos[i].Type)
		{
      
		case 0:
			RenderObject (&Matrx, M_B2_TRANS);
			RenderObject (&Matrx, M_B2_BARK);
			break;

		case 1:
			RenderObject (&Matrx, M_B3_TRANS);
			RenderObject (&Matrx, M_B3_BARK);
			break;

		case 2:
			RenderObject (&Matrx, M_B1_TRANS);
			RenderObject (&Matrx, M_B1_BARK);
			break;

		case 3:
			RenderObject (&Matrx, M_B4_TRANS);
			RenderObject (&Matrx, M_B4_BARK);
			break;
		}
	 

		if (TreeHit==TRUE && TreeHitPos[i]==0)
		{
			TreeHitPos[i] = 100;
			TreeHitOff[i] = OffsetX*1.0f;
			TreePos[i].z = 0;
			TreeHit = FALSE;
			nFire=2;
		}
	} 

	/* New position */
	CalculateGround ();
	
	/* Banners */
	if (nStart)
	{
		KMMatrixReset (&Matrx);
		KMMatrixTranslate (&Matrx, PosX, -GrHigh, 100+TreePos[75].z);
		RenderObject (&Matrx, M_START+(nStart-1));
	}
  
  	/* Ground */
	KMMatrixReset (&Matrx);
	KMMatrixTranslate (&Matrx, PosX, -20.0f-GrHigh, 100-GrPosZ);
	RenderObject (&Matrx, M_GROUND);

	/* Explosion at the front */
	if (nFire>0)
	{
		KMMatrixReset (&Matrx);
		RenderObject (&Matrx, M_FIRE);
		nFire--;
	}

	/* little radar :-) */
	DrawRadar();
	
	
	/* Control panel */
	KMMatrixReset (&Matrx);
	RenderObject (&Matrx, M_FRONT);
	
	/* 
	 * Text windows.
	 */
	KMPrint3DDisplayWindow(TWin[0]);
  
	KMPrint3D (4.68f, 84.79f, 1.5f, 0xFF005000, "%03d", nTreesH);


	if (nStartCont<=1)
	{
	 	KMPrint3D (28.1f, 60.41f, 2.0f, 0xFFFF0000, "Get Ready");
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
 *  Description     : PadControl() is called by KMShell every frame to enable
 *						the user to control the joystick                            
 *-------------------------------------------------------------------------------------*/
int PadControl (void)
{	
static	int	Delay = 0;

	Delay++;

	/* START */
	if (IsSTARTKey())
	{
	}
	
	/* UP */
	if (IsUPKey() || AnalogPadY()<-64)
	{
	}

	/* DOWN */
	if (IsDOWNKey() || AnalogPadY()>64)
	{
	}

	/* LEFT */
	if (IsLEFTKey() || AnalogPadX()<-64)
	{
		if(OffsetX<=0) OffsetX = 10.0f; 
		OffsetX+=5.0f;
	}

	/* RIGHT */
	if (IsRIGHTKey() || AnalogPadX()>64)
	{
		if(OffsetX>=0) OffsetX = -10.0f; 
		OffsetX-=5.0f;
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

    for (j=0; j<Mesh[M_FRONT].nNumVertex; j++)
	{
            (KmVert[M_FRONT]+j)->fX = -*(Mesh[M_FRONT].pVertex+j*3+0);
            (KmVert[M_FRONT]+j)->fY = *(Mesh[M_FRONT].pVertex+j*3+1);
			(KmVert[M_FRONT]+j)->u.fZ = 250.0f;
	} 

	for (j=0; j<Mesh[M_FIRE].nNumVertex; j++)
	{
            (KmVert[M_FIRE]+j)->fX = -*(Mesh[M_FIRE].pVertex+j*3+0);
            (KmVert[M_FIRE]+j)->fY = *(Mesh[M_FIRE].pVertex+j*3+1) - 30.0f;
			(KmVert[M_FIRE]+j)->u.fZ = 249.0f;

			(KmVert[i]+j)->uBaseRGB.dwPacked	= 0x00FFFFFF;
			
	} 

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : LoadTextures                                                         
 *  Inputs          : None                                                               
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                   
 *  Description     : Converts 24bits Bitmap format to 16bits hardware format and loads it
 *                     in video memory.                  
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
		else /* It's opaque */
		{
			if (i>=M_START) /* No mipmap for the banners and the background */
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
 *  Description     : Sets all the vertex contexts for this application.                           
 *-------------------------------------------------------------------------------------*/
void CreateContexts (void)
{

	/* OPAQUE MATERIALS */
	KMShellInitStripHead (&StripHead[M_GROUND], &Tex[M_GROUND], VC_OPAQUE | VC_FOGTABLE);

	/* background */
	KMShellInitStripHead (&StripHead[M_BACKGROUND], &Tex[M_BACKGROUND], VC_OPAQUE);

	/* Triangles in the radar */
	KMShellInitStripHead (&StripHead[21], NULL, VC_OPAQUE | VC_NONTEXTURED);

	/* Control Panel */
	KMShellInitStripHead (&StripHead[M_FIRE], &Tex[M_FIRE], VC_ADDITIVE);
	KMShellInitStripHead (&StripHead[M_FRONT], &Tex[M_FRONT], VC_OPAQUE);

	/* Banners */
	KMShellInitStripHead (&StripHead[M_START], &Tex[M_START], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M__1MILE], &Tex[M__1MILE], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M__2MILES], &Tex[M__2MILES], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M__3MILES], &Tex[M__3MILES], VC_OPAQUE);
	KMShellInitStripHead (&StripHead[M_FINISH], &Tex[M_FINISH], VC_OPAQUE);

	/* TREES */
	KMShellInitStripHead (&StripHead[M_B1_BARK], &Tex[M_B1_BARK], VC_OPAQUE| VC_FOGTABLE);
	KMShellInitStripHead (&StripHead[M_B2_BARK], &Tex[M_B2_BARK], VC_OPAQUE| VC_FOGTABLE);
	KMShellInitStripHead (&StripHead[M_B3_BARK], &Tex[M_B3_BARK], VC_OPAQUE| VC_FOGTABLE);
	KMShellInitStripHead (&StripHead[M_B4_BARK], &Tex[M_B4_BARK], VC_OPAQUE| VC_FOGTABLE);

	/* TRANSLUCENT MATERIALS */
	KMShellInitStripHead (&StripHead[M_B1_TRANS], &Tex[M_B1_TRANS],VC_TRANS| VC_FOGTABLE | VC_UVFLIP);
	KMShellInitStripHead  (&StripHead[M_B2_TRANS], &Tex[M_B2_TRANS], VC_TRANS| VC_FOGTABLE | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_B3_TRANS], &Tex[M_B3_TRANS], VC_TRANS| VC_FOGTABLE | VC_UVFLIP);
	KMShellInitStripHead (&StripHead[M_B4_TRANS], &Tex[M_B4_TRANS], VC_TRANS| VC_FOGTABLE | VC_UVFLIP);

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : RenderObject                                                       
 *  Inputs          : Matrx Object                                                             
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Sending a set of strips to render.                              
 *-------------------------------------------------------------------------------------*/
void RenderObject (MATRIX *Matrx, int Object)
{
	if(Object!=M_FRONT && Object!=M_FIRE)
	KMTransTransformProjectPerspective (Matrx, Mesh[Object].nNumVertex, Mesh[Object].pVertex, 
										KmVert[Object], ScreenWidth, ScreenHeight,
										CameraFrom, CameraTo, 0.0f, -1.0f, 1000000.0f, 60.0f*(PI/180.0f));

	KMShellStrips (&StripHead[Object],Mesh[Object].nNumStrips, 
					Mesh[Object].pStripLength, Mesh[Object].pStrips, (KMVERTEX_03 *)KmVert[Object]);
}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : BuildGround                                                       
 *  Inputs          : None                                                           
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Startup for ground vertices.                              
 *-------------------------------------------------------------------------------------*/
#define GRID_SIZE 25

void BuildGround (void)  
{ 
register i, j;
unsigned Cont = 0, Val;
float Rel;

	KMMiscSeedRand(0x01234567);    

    XIncr =  *(Mesh[M_GROUND].pVertex+0+3*1) - *(Mesh[M_GROUND].pVertex+0+3*0);
    ZIncr =  *(Mesh[M_GROUND].pVertex+2+3*GRID_SIZE) - *(Mesh[M_GROUND].pVertex+2+3*0);

	UIncr =  (KmVert[M_GROUND]+0)->fU - (KmVert[M_GROUND]+1)->fU;
    VIncr =  (KmVert[M_GROUND]+0)->fV - (KmVert[M_GROUND]+GRID_SIZE)->fV;

	for (j=0; j<GRID_SIZE; j++)
	{
		Rel = (float) (KMMiscRand()%100-50);
		for (i=0; i<GRID_SIZE; i++)
		{
		Base[i] =  700.0f * (float)(sin((float)i*(PI/9.0f) + 0.3) );
    	High[i+j*25]    =  -Rel + (float) (KMMiscRand()%100-50)  + Base[i];
	   
		*(Mesh[M_GROUND].pVertex+(GRID_SIZE*GRID_SIZE-i-j*GRID_SIZE)*3+1) = High[i+j*GRID_SIZE];
		*(Mesh[M_GROUND].pVertex+(GRID_SIZE*GRID_SIZE-i-j*GRID_SIZE)*3+0) *= GrWide;

	     (KmVert[M_GROUND]+Cont)->uBaseRGB.dwPacked  = 0xFFFFFFFF;
	     (KmVert[M_GROUND]+Cont++)->uOffsetRGB.dwPacked  = 0x00000000;
		 
		}
	}

	for (i=0;i<75; i++)
	{
		TreePos[i].Type = (i%4);
		
		Val = 8+ (KMMiscRand()%8) + (i%24)*GRID_SIZE;

		TreePos[i].x = *(Mesh[M_GROUND].pVertex+Val*3+0);
		TreePos[i].y = *(Mesh[M_GROUND].pVertex+Val*3+1);
		TreePos[i].z = *(Mesh[M_GROUND].pVertex+Val*3+2) - ZIncr / 10.0f;
	}

}
/*-------------------------------------------------------------------------------------* 
 *  Function Name   : CalculateGround                                                       
 *  Inputs          : None                                                            
 *  Outputs         : None                                                               
 *  Returns         : None                                                               
 *  Globals Used    :                                                                    
 *  Description     : Updates ground vertices every frame.                              
 *-------------------------------------------------------------------------------------*/
void CalculateGround (void)
{
register i, j;
float Rel, Xset;
int IsTree[200];
static int  Val=8+(GRID_SIZE-1)*GRID_SIZE;
	
    GrPosZ +=  ZIncr / Vel;

	Xset = 0.5f+((GRID_SIZE-1)*(PosX/GrWide+3500.0f)/7000.0f);

	GrHigh = Base[(int)Xset] - (Base[(int)Xset]-Base[(int)Xset+1])*(Xset-(int)Xset)  + 150;
	

	PosX += OffsetX;	 
	if (PosX>1300.0f*GrWide) {OffsetX  =-15.0f;PosX=1300.0f*GrWide;}
	if (PosX<-1300.0f*GrWide) {OffsetX = 15.0f;PosX=-1300.0f*GrWide;}


	for (i=0;i<=75; i++)
	{
	    TreePos[i].z -= ZIncr / Vel;
	}
   

	if (GrPosZ >= ZIncr)
	{
	
		GrPosZ =  0;
		
		/*  Move UV to origin */
	        if ((KmVert[M_GROUND]+GRID_SIZE*GRID_SIZE)->fV <= -4.0)
		  {
			for (i=0; i<=GRID_SIZE*GRID_SIZE; i++) 
					{
					(KmVert[M_GROUND]+i)->fU += 4.0f;
					(KmVert[M_GROUND]+i)->fV += 4.0f;
					}
		  }
	

		/* Move everything one step */
		for (i=0; i<GRID_SIZE*(GRID_SIZE-1); i++)
		{
			*(Mesh[M_GROUND].pVertex+i*3+1) = *(Mesh[M_GROUND].pVertex+(i+GRID_SIZE)*3+1);
		

		}
	    for (i=0; i<GRID_SIZE*(GRID_SIZE-1); i++) 
		{
		 (KmVert[M_GROUND]+i)->fU = (KmVert[M_GROUND]+GRID_SIZE+i)->fU;
	     (KmVert[M_GROUND]+i)->fV = (KmVert[M_GROUND]+GRID_SIZE+i)->fV;
		}
	
        Rel = (float) (KMMiscRand()%100-50);
      
		
        /* New back row */
		for (i=0; i<GRID_SIZE; i++)
		{
          
           if (Rel>0) High[i]   =  *(Mesh[M_GROUND].pVertex+(GRID_SIZE*GRID_SIZE-i)*3+1) + (float) (KMMiscRand()%100-50);
		   else   High[i]   =  Rel + (float) (KMMiscRand()%70-35)  +  Base[i];
		   
		   *(Mesh[M_GROUND].pVertex+(GRID_SIZE*GRID_SIZE-i)*3+1) = High[i];
		 
          (KmVert[M_GROUND]+GRID_SIZE*GRID_SIZE-i)->fU += UIncr;
          (KmVert[M_GROUND]+GRID_SIZE*GRID_SIZE-i)->fV += UIncr;
	 
		 
		  (KmVert[M_GROUND]+25*24+i)->uBaseRGB.dwPacked = 0xFFFFFFFF;
	  
		}

        for (i=0; i<=75; i++) IsTree[i]=FALSE;
        
        
		/* Trees allocation on the ground */
        for (j=0;j<=75; j++)
		{
			if (TreePos[j].z<-280.0f)
			{
			if (j==75) 
			{
				nStart=0;
				if (nStartCont==0) nStart=1;
				if (nStartCont==1) {TotalTime=0.0f; nTreesH=0;};
				if (nStartCont==4)  nStart=2;
				if (nStartCont==8)  nStart=3;
				if (nStartCont==12) nStart=4;
				if (nStartCont==16) nStart=5;
				if (nStartCont==17) 
				{
					nStartCont=-5; YourTime=TotalTime;if (YourTime<BestTime) BestTime=YourTime;
				
				}
				nStartCont++; 
			}

      		Val++;if (Val>16+(GRID_SIZE-1)*GRID_SIZE) Val=8+(GRID_SIZE-1)*GRID_SIZE;
			if ((KMMiscRand()%100)>50) Val++;

			TreePos[j].x = *(Mesh[M_GROUND].pVertex+Val*3+0);
			TreePos[j].y = *(Mesh[M_GROUND].pVertex+Val*3+1);
			TreePos[j].z = *(Mesh[M_GROUND].pVertex+Val*3+2);
			}
		}

	}

}
/*----------------------------------------------------------------------*
 *  Function Name   :  DrawRadar                                      
 *  Inputs          :  None                                               
 *  Outputs         :  None                                                 
 *  Returns         :  None                                     
 *  Globals Used    :                      
 *  Description     :  Draw small triangles on the green screen.                    
 *----------------------------------------------------------------------*/
 void DrawRadar (void)
{
register j;
float RadarPos[2];
KMVERTEX_03 RadarV[3];
unsigned short RadarFaces[3] = { 0,1,2 };
int TreeColor;

    
	for (j=0;j<=75; j++)
	{
		TreeColor = 0xFF008000;
		if(TreeHitPos[j]>0) TreeColor = 0xFFFF0000;
	
		RadarPos[0] = (TreePos[j].x + PosX) / 20.0f + 570.0f;
		RadarPos[1] = 438 - TreePos[j].z / 75.0f;

		if ( RadarPos[0]>535 && RadarPos[0]<610 && RadarPos[1]>390 && RadarPos[1]<440)
		{
		RadarV[0].fX = RadarPos[0];
		RadarV[0].fY = RadarPos[1];
		RadarV[0].u.fZ = 260.0f;
		RadarV[0].uBaseRGB.dwPacked	= TreeColor;
		
		RadarV[1].fX = RadarPos[0] - 3.0f;
		RadarV[1].fY = RadarPos[1] - 3.0f;
		RadarV[1].u.fZ = 260.0f;
		RadarV[1].uBaseRGB.dwPacked	= TreeColor;
		
		RadarV[2].fX = RadarPos[0] + 3.0f;
		RadarV[2].fY = RadarPos[1] - 3.0f;
		RadarV[2].u.fZ = 260.0f;
		RadarV[2].uBaseRGB.dwPacked	= TreeColor;
		}

		KMShellTriangles (&StripHead[21], 1, RadarFaces, RadarV);
	}
 }
/*----------------------------------------------------------------------*
 *  Function Name   : SetFogTable                                       
 *  Inputs          : FogDensity r g b                                                 
 *  Outputs         : None                                                  
 *  Returns         : None                                                 
 *  Globals Used    :                                                   
 *  Description     :                                                   
 *  Note			: FogDensity from 0=No Fog to 6=Full Fog			
 *----------------------------------------------------------------------*/
void SetFogTable (KMDWORD FogDensity, float r, float g, float b )
{
	int				i;
	KMPACKEDARGB	fogcol;
	KMFLOAT			FogTable[128];

	/* Fog Color */
	fogcol.byte.bBlue	= b * 255;
	fogcol.byte.bGreen	= g * 255;
	fogcol.byte.bRed	= r * 255;
	kmSetFogTableColor(fogcol);
	

	/* Fog Density */
	if (FogDensity > 6) FogDensity = 6;
	kmSetFogDensity(0xFF0F - FogDensity); /* FF09 - FF0D */


	/* Fog Table */
	for(i = 0; i < 128; i++) {
		/***************************/
		/*  MY FOG TABLE           */
		/***************************/
		if (i<20) FogTable[i] = 1.0f - (float)i/22.0;
		else  FogTable[i] = 0.1f;
	
		/***************************/
		/*  SOME USEFUL FOG TABLES */
		/***************************/
		/*  Linear Fog table  */
			/* FogTable[i] = 1.0f - ((float)i / 128.0f); */
		
		/* Slope Fog table */
			/* #define	FOG_MIN		(-0.8f) */
			/* FogTable[i] = 1.0f - (float)i * ((1.0f - FOG_MIN) / 128.0f); */
			/* if(FogTable[i] < 0.0f) FogTable[i] = 0.0f;					*/	
	}

	kmSetFogTable(&FogTable[0]);
}
/*----------------------------------------------------------------------*
 *  Function Name   : CreateWindows                                       
 *  Inputs          : None                                                 
 *  Outputs         : None                                                  
 *  Returns         : None                                                 
 *  Globals Used    :                                                   
 *  Description     :                                                   
 *  Note			: Info Windows.		
 *----------------------------------------------------------------------*/
void CreateWindows (void)
{
	
	/* Text Windows */
	/* Window 0 */
	TWin[0] = KMPrint3DCreateWindow (50, 20);
	
	KMPrint3DSetTitle		(TWin[0], (KMDWORD)0x902030FF, 0.6f, (KMDWORD)0xFFFFFFFF, "WINTER RACE   User Defined Table Fog", 
										(KMDWORD)0xFFFFFFFF, NULL);
	KMPrint3DSetWindow		(TWin[0], 0xFFFFFFFF, 0xFFFFFFFF, 0.5f, 1.0f, 1.0f, 36.0f, 40.0f);
	KMPrint3DSetWindowFlags	(TWin[0], PRINT3D_ADJUST_SIZE_ALWAYS | PRINT3D_DEACTIVATE_WIN);	


}

